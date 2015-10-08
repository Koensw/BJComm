/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */
package nl.bluejayeindhoven.bjcomm;

import java.util.Scanner;

/**
 * Data class that contains a message with a type that can be send and received
 *
 * <p>This class makes sure that the message follow the defined format
 * A message should start with an non-empty string (printable ASCII) that defines the type (default if not set).
 * Then comes one space followed by any non-space character that starts the data. The end of the data is a printable character</p>
 *
 * @author Koen Wolters
 */
public class Message{
    /**
     * Type of the message
     */
    private String type;
    /**
     * Data of the message
     */
    private String data;
    
    /**
     * Initialize a default message
     */
    public Message(){
        this.type = "default";
        this.data = "";
    }
    /**
     * Initialize message with a type
     *
     * @param type type of the message
     */
    public Message(String type){
        this.type = type.trim();
        if(type.isEmpty()) type = "default";
        this.data = "";
    }
    /**
     * Initialize message with a type and data
     *
     * @param type type of the message
     * @param data data of the message
     */
    public Message(String type, String data){
        this.type = type.trim();
        if(type.isEmpty()) type = "default";
        this.data = data.trim();
    }
    
    /**
     * Set the type of the message 
     *
     * @param type the type of the message (becomes default if type is empty string)
     */
    public void setType(String type){
        type = type.trim();
        if(type.isEmpty()) type = "default";
        this.type = type;
    }
    /**
     * Get the type of the message
     *
     * @return the type of the message
     */
    public String getType(){
        return type;
    }
    
    /**
     * Set the data of the message as string
     *
     * @param data the data of the message
     */
    public void setData(String data){
        data = data.trim();
        this.data = data;
    }
    
    /**
     * Get the data of the message as string
     *
     * @return the data of the message
     */
    public String getData(){
        return data;
    }
    
    /**
     * Returns a Scanner object that can be used to read the data. Does not modify internal data
     *
     * @return object to read the message data 
     */
    public Scanner getScanner(){
        return new Scanner(data);
    }
    
    /**
     * Clears the message data
     */
    public void clear(){
        data = "";
    }
}