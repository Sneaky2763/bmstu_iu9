import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println(" Введите строку: ");
        String s = scan.nextLine();
        StringBuilder a = new StringBuilder(s);
        StringClass b = new StringClass(a);
        System.out.println(" Итерация по строке до изменения: ");
        for(StringBuilder k: b){
            System.out.println(k);
        }

        System.out.println(" Измените строку: ");
        s = scan.nextLine();
        StringBuilder f = new StringBuilder(s);
        b.SetString(f);
        System.out.println(" Итерация по строке после изменения: ");
        for(StringBuilder k: b){
            System.out.println(k);
        }
    }
}
