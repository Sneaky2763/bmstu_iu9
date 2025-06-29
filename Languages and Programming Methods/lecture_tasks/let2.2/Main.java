interface DistanceCalc{
    double findDistance(Point p1, Point p2);
}

public class Main {
    public static void main(String[] args) {

        Point p1 = new Point(1.0, 1.0, 1.0);
        Point p2 = new Point(2.0, 2.0, 2.0);

        DistanceCalc calc = new DistanceCalc(){
            public double findDistance(Point p1, Point p2) {
                double dx=p1.getx()-p2.getx();
                double dy=p1.gety()-p2.gety();
                double dz=p1.gety()-p2.getz();
                return Math.sqrt(dx*dx + dy*dy + dz*dz);
            }
        };
        System.out.println("Расстояние между точками: " + calc.findDistance(p1, p2));
    }
}
