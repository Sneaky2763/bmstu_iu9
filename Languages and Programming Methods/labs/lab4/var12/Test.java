import java.util.ArrayList;
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Введите количество строк: ");
        int len = scan.nextInt();

        ArrayList<String> a = new ArrayList<String>();
        String endl = scan.nextLine();
        for(int i=0; i<len; ++i){
            System.out.println("Введите строку: ");
            String s = scan.nextLine();
            a.add(s);
        }

        StringClass cl = new StringClass(a);
        for(String k: cl){
            System.out.println(k);
        }
    }
}

