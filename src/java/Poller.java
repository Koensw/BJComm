package nl.bluejayeindhoven.bjcomm;

import nl.bluejayeindhoven.bjcomm.CommunicationInterface;

import org.zeromq.ZMQ;

public class Poller{
    private ZMQ.Poller poller;
    
    public Poller(){
        poller = new ZMQ.Poller(0);
    }
    
    public int add(CommunicationInterface comm){
        return poller.register(comm.socket, ZMQ.Poller.POLLIN);
    }
    
    public void poll(){
        //NOTE: not fully compatbile with C++ currently, should properly give error if socket not started
        poller.poll(-1);
    }
    
    public boolean hasMsg(int id){
        return poller.pollin(id);
    }
}