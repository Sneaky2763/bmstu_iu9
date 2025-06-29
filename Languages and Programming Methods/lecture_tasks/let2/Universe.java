import java.util.Scanner;

public class Universe{
    private static int count;
    private int len;
    static{
        count=0;
    }
    private Particle array[];

    public Universe (int len){
        this.array=new Particle[len];
        this.len=len;
        for (int i=0; i<len; ++i){
            count++;
            System.out.println("Масса и скорость частицы: ");
            Scanner scan = new Scanner(System.in);
            double mass = scan.nextInt();
            double vel = scan.nextInt();
            array[i]=new Particle(mass, vel);
        }
    }

    public int getCount(){
        return count;
    }

    public double findAverage(){
        double ans=0;
        for (int i=0; i<len; ++i){
            ans+=this.array[i].findEnergy();
        }
        return ans/this.getCount();
    }
}
