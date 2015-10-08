/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

package nl.bluejayeindhoven.bjcomm;

import org.zeromq.ZMQ;

/**
 * Provide error handling for the communication layer
 *
 * <p>Defines a error that shall be thrown when something happen that shall never happen
 * (for example reading from an subscriber that is not running) or are very unlikely
 * (for example a protocol error in ZMQ)</p>
 *
 * @author Koen Wolters
 */

public class CommunicationError extends RuntimeException{
    static final long serialVersionUID = 76995899L;
    
    /** 
     * Create error with message
     *
     * @param msg message to identify the error
     */
    public CommunicationError(String msg) {
        super(msg);
    }
}