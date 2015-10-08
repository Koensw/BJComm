import java.util.Scanner;

import nl.bluejayeindhoven.bjcomm.*;

/* Test of a default subscriber client */
class Test
{
    public static void main (String [] args)
    {
        Subscriber sub = new Subscriber("tcp://*:5556");
        
        boolean ret = sub.start();
        
        System.out.print("Started ");
        System.out.println(ret);
        
        Poller poller = new Poller();
        int SUBSCRIBER = poller.add(sub);
        
        while(!Thread.currentThread().isInterrupted()){
            poller.poll();
            
            if(poller.hasMsg(SUBSCRIBER)){
                Message msg;
                msg = sub.receive();
                
                switch(msg.getType()){
                    case "position":
                        Scanner scan = msg.getScanner();
                        int x = scan.nextInt();
                        int y = scan.nextInt();
                        int z = scan.nextInt();
                        
                        System.out.format("Set position to (%d,%d,%d)", x, y, z);
                        System.out.println();
                        break;
                    default:
                        System.out.print("INCORRECT MESSAGE: ");
                        System.out.format("%s - %s", msg.getType(), msg.getData());
                        System.out.println();
                }
            }else{
                System.out.println("INCORRECT POLL");
            }
        }
        
        sub.stop();
    }
}
