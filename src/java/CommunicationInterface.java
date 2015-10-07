package nl.bluejayeindhoven.bjcomm;

import org.zeromq.ZMQ;

public abstract class CommunicationInterface{
    public static final int IO_THREADS = 1;

    protected ZMQ.Context context;
    protected ZMQ.Socket socket;
    
    protected boolean running;
    
    public CommunicationInterface(){
        this.running = false;
        
        this.context = ZMQ.context (IO_THREADS);
        this.socket = null;
    }
    
    public final boolean isRunning(){
        return running;
    }
    
    public abstract boolean start();
    public boolean stop(){
        //do not do anything if already closed (ALERT: should not happen)
        if(running) return false;
        
        //close the socket
        socket.close();
        socket = null;
        
        running = false;
        return true;
    }
    
    public static void main(String[] args){
        System.out.println("TEST");
    }
}