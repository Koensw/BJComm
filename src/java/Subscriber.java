package nl.bluejayeindhoven.bjcomm;

import org.zeromq.ZMQ;
import org.zeromq.ZMQException;
import java.util.concurrent.TimeUnit;
import java.nio.charset.StandardCharsets;


import nl.bluejayeindhoven.bjcomm.Message;

public class Subscriber extends CommunicationInterface{
    private String address;
    
    public Subscriber(String address){
        this.address = address;
    }
    
    public boolean start(){
        //if already started return false (ALERT: should not happen)
        if(running) return false;
        
        socket = context.socket(ZMQ.SUB);
        
        try{
            socket.bind(address);
            
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
    
    public Message receive(){
        while(!running) {
            //wait forever if no socket is started (FIXME: we should just throw an exception ?)
            try {
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        
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