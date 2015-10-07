package nl.bluejayeindhoven.bjcomm;

import org.zeromq.ZMQ;
import org.zeromq.ZMQException;
import java.util.concurrent.TimeUnit;

import nl.bluejayeindhoven.bjcomm.Message;

public class Publisher extends CommunicationInterface{
    private String address;
    
    public Publisher(String address){
        this.address = address;
    }
    
    public boolean start(){
        //if already started return false (ALERT: should not happen)
        if(running) return false;
        
        socket = context.socket(ZMQ.PUB);
        
        try{
            socket.connect(address);
        }catch(ZMQException e){
            socket.close();
            socket = null;
            return false;
        }
        
        running = true;
        return true;
    }
    
    public void send(Message msg){
        while(!running) {
            //wait forever if no socket is started (FIXME: we should just throw an exception ?)
            try {
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        
        //send message
        String str = msg.getType()+" "+msg.getData();
        socket.send(str);
    }
}