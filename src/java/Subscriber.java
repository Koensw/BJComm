/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */
package nl.bluejayeindhoven.bjcomm;

import java.io.File;
import java.nio.charset.StandardCharsets;

import org.zeromq.ZMQ;
import org.zeromq.ZMQException;

import nl.bluejayeindhoven.bjcomm.Message;
import nl.bluejayeindhoven.bjcomm.CommunicationError;

/**
 * Interface that subscribes to all messages on a socket it binds
 *
 * @see Publisher
 * @author Koen Wolters
 */
public class Subscriber extends CommunicationInterface{
    /**
     * Address of the socket
     */
    private String address;
    
    /**
     * Constructs a subscriber that shall communicate over the supplied address
     *
     * @param address address of the socket
     */
    public Subscriber(String address){
        this.address = COMMON_PATH+address;
    }
    
    /**
     * {@inheritDoc}
     *
     * Creates a socket, bind the address and subscribe to all channels
     */
    public boolean start(){
        //if already started return false (ALERT: should not happen)
        if(running) return false;
        
        socket = context.socket(ZMQ.SUB);
        
        try{
            //create file if not exists
            new File(COMMON_PATH+address).mkdirs();
        
            //bind socket
            socket.bind("ipc://"+COMMON_PATH+address);
            
            //FIXME: currently binding to all sockets
            socket.subscribe(new byte[0]);
        }catch(ZMQException e){
            socket.close();
            socket = null;
            return false;
        }
        
        running = true;
        return true;
    }
    
    /**
     * Receive a message over the channel. Blocks until message is received.
     *
     * @return msg message that is received on the channel
     *
     * @throws CommunicationError if interface is not started
     */
    public Message receive(){
        //throw exception if trying to receive message on closed channel
        if(!running) throw new CommunicationError("Trying to receive message on channel that is not running!");
        
        //read type and data
        String str = socket.recvStr(StandardCharsets.US_ASCII);
        str = str.trim();
        
        String[] parts = str.split(" ", 2);
        
        String type;
        String data;
        if(parts.length < 2){
            type = parts[0];
            data = "";
        }else{
            type = parts[0];
            data = parts[1];
            data = data.trim();
        }
        Message msg = new Message(type, data);
        
        return msg;
    }
}