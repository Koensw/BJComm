/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

package nl.bluejayeindhoven.bjcomm;

import org.zeromq.ZMQ;

/**
 * Main abstract interface for interfaces that can communicate
 *
 * <p>All other interfaces need to extend this class. It contains the ZMQ context and the socket
 * that the communication interface uses. Also provides a way to identify that an interface is running
 * (the socket is available). Subclasses shall ensure that the running boolean is set correctly.</p>
 *
 * @author Koen Wolters
 */
public abstract class CommunicationInterface{
    /**
     * Tune the amount of threads the interface shall use. 
     * In normal cases using more than one thread will not increase performance.
     */
    public static final int IO_THREADS = 1;

    /**
     * The context of ZMQ to access other objects. This class will ensure that this object is available 
     */
    protected ZMQ.Context context;
    
    /**
     * Socket that will internally be used by interface. Will be initialized to a null pointer.
     * Shall be pointed to a working socket if start finished properly. Shall be deinitialized after stop is called.
     */
    protected ZMQ.Socket socket;
    
    /**
     * Determines if this interface is usable. At least the socket should work properly before this is set to true.
     * The interface is free to trigger any error if any other method any than start/stop/isRunning is called before this is true.
     */
    protected boolean running;
    
    /**
     * Initializes communication interface
     */
    public CommunicationInterface(){
        this.running = false;
        
        this.context = ZMQ.context (IO_THREADS);
        this.socket = null;
    }
    
    /**
     * Check if the interface is running
     *
     * @return if the interface is running (the running boolean has been set to true by subclasses)
     */
    public final boolean isRunning(){
        return running;
    }
    
    /**
     * Starts the interface. If this succeeds isRunning shall also return true from that moment.
     *
     * @return if the interface was succesfully started (shall return false if already started)
     */
    public abstract boolean start();
    
    /**
     * Stops the interface. If this succeeds isRunning shall also return false. 
     * Normally this shall never fail, in an invalid state the interface shall still be closed
     *
     * @return if the interface was succesfully stopped (shall return false if already stopped)
     */
    public boolean stop(){
        //do not do anything if already closed
        if(running) return false;
        
        //close the socket
        socket.close();
        socket = null;
        
        running = false;
        return true;
    }
}