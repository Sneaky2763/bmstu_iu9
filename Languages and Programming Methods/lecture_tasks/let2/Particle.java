public class Particle {
    private double velocity;
    private double mass;

    public Particle(double x, double y){
        this.velocity=y;
        this.mass=x;
    }
    public double findEnergy(){
        return (this.mass*this.velocity*this.velocity)/2;
    }
}
