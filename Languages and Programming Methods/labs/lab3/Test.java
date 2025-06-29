import java.util.Arrays;
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Введите количество множеств: ");
        int len = scan.nextInt();
        Points arr[] = new Points[len];
        for(int i=0; i<len; ++i){
            System.out.println("Введите количество точек в множестве: ");
            int size = scan.nextInt();
            int tochki[][] = new int[size][3];
            for(int j=0; j<size; ++j){
                System.out.println("Введите координаты точки: ");
                for(int k=0; k<3; ++k){
                    tochki[j][k] = scan.nextInt();
                }
            }
            arr[i] = new Points(tochki);
        }
        Arrays.sort(arr);
        for (Points s: arr){
            System.out.println(s);
        }
    }
}
