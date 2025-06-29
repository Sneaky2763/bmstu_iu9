public class WheelPlatform{
    private int num;
    private int speed;

    public WheelPlatform(int x, int y){
        this.num=x;
        this.speed=y;
    }
    public int getnum(){
        return this.num;
    }

    public int getspeed(){
        return this.speed;
    }
    public String toString(){
        String res = "";
        res+="Номер: " + this.num +", скорость: " + this.speed;
        return res;
    }
}
