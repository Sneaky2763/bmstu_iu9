import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Введите число частиц: ");
        int len = scan.nextInt();
        Universe a = new Universe(len);
        System.out.println("Средняя энергия: " + a.findAverage());
    }
}
