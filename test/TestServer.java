import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import nl.bluejayeindhoven.bjcomm.*;

class TestServer
{
    public static void main (String [] args)
    {
        Publisher pub = new Publisher("tcp://localhost:5556");
        boolean ret = pub.start();
        
        System.out.print("Started ");
        System.out.println(ret);
        
        for(int i=0; true; ++i){
            Message msg = new Message("position");
            
            int x = i, y = 2, z = 1;
            
            String str = String.format("%d %d %d", x, y, z);
            msg.setData(str);
            
            pub.send(msg);
            
            try {
                TimeUnit.MILLISECONDS.sleep(10);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
