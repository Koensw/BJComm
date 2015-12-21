/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */
package nl.bluejayeindhoven.bjcomm;

import java.io.File;

import org.zeromq.ZMQ;
import org.zeromq.ZMQException;

import nl.bluejayeindhoven.bjcomm.Message;
import nl.bluejayeindhoven.bjcomm.CommunicationError;

/**
 * Interface that send a message asynchronously on a socket it connects
 *
 * @see Subscriber
 * @author Koen Wolters
 */
public class Publisher extends CommunicationInterface{
    /**
     * Address of the socket
     */
    private String address;
    
    /**
     * Constructs a publisher that shall communicate over the supplied address
     *
     * @param address address of the socket
     */
    public Publisher(String address){
        this.address = address;
    }
    
    /**
     * {@inheritDoc}
     *
     * Creates a socket and connects to it (not blocking if not binded yet)
     */
    public boolean start(){
        //if already started return false
        if(running) return false;
        
        socket = context.socket(ZMQ.PUB);
        
        try{
			new File(COMMON_PATH+address).mkdirs();
			
            socket.connect("ipc://"+COMMON_PATH+address);
        }catch(ZMQException e){
            socket.close();
            socket = null;
            return false;
        }
        
        running = true;
        return true;
    }
    
    /**
     * Send a message over the channel
     *
     * @param msg message to send over the channel
     *
     * @throws CommunicationError if interface is not started
     */
    public void send(Message msg){
        //throw exception if trying to send message on closed channel
        if(!running) throw new CommunicationError("Trying to send message on channel that is not running!");
        
        //send message
        String str = msg.getType()+" "+msg.getData();
        socket.send(str);
    }
}