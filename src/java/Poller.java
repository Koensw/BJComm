/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */
package nl.bluejayeindhoven.bjcomm;

import nl.bluejayeindhoven.bjcomm.CommunicationInterface;

import org.zeromq.ZMQ;
import org.zeromq.ZMQException;

/**
 * Implement simple poller that divides load between several channels
 *
 * @author Koen Wolters
 */
public class Poller{
    private ZMQ.Poller poller;
    boolean polled;
    
    /**
     * Initializes a poller
     */
    public Poller(){
        poller = new ZMQ.Poller(0);
        polled = false;
    }
    
    /**
     * Adds an interface to the poller. Make sure the interface is loaded before adding it. Only add interfaces that support polling.
     * 
     * @param comm interface to add to the poller
     * @return identifier for the added interface or -1 if failed
     */
    public int add(CommunicationInterface comm){
        if(comm.socket == null) return -1;
        return poller.register(comm.socket, ZMQ.Poller.POLLIN);
    }
    
    /** 
     * Poll all registered interfaces. Blocks until at least one of them has a message to process.
     *
     * @throws CommunicationError if an added interface is not started
     */
    public void poll(){
        if(poller.getSize() == 0) throw new CommunicationError("Polling without any interfaces added!");
        
        polled = false;
        try{
            poller.poll(-1);
            polled = true;
        }catch(ZMQException zex){
            throw new CommunicationError("Polling on an channel that is not running!");
        }
    }
    
    /**
     * Check if the supplied interface has a message to read
     *
     * @param id identifier of an interface returned by {@link #add(CommunicationInterface) add} method.
     * @return if the interface has a message to read
     *
     * @throws IllegalStateException if called before {@link #poll() poll()} is called
     * @throws IllegalArgumentException if called with an invalid identifier
     */
    public boolean hasMsg(int id){
        //check if id exists and poll has been called
        if(id < 0 || id >= poller.getSize()) throw new IllegalArgumentException("Checking for message of an invalid identifier!");
        else if(!polled) throw new IllegalStateException("Checking for a message before poller is called!");
        
        return poller.pollin(id);
    }
}