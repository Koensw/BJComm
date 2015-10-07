package nl.bluejayeindhoven.bjcomm;

import java.util.Scanner;

public class Message{
    private String type;
    private String data;
    
    public Message(){
        this.type = "default";
        this.data = "";
    }
    public Message(String type){
        this.type = type.trim();
        this.data = "";
    }
    public Message(String type, String data){
        this.type = type.trim();
        this.data = data.trim();
    }
    
    public void setType(String type){
        if(type.isEmpty()) type = "default";
        type = type.trim();
        this.type = type;
    }
    public String getType(){
        return type;
    }
    
    public void setData(String data){
        data = data.trim();
        this.data = data;
    }
    public String getData(){
        return data;
    }
    
    public Scanner getScanner(){
        return new Scanner(data);
    }
    
    public void clear(){
        data = "";
    }
}