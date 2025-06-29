import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<Integer> test = new ArrayList();
        test.add(0);
        test.add(1);
        test.add(3);
        test.add(7);
        test.add(15);
        test.add(31);
        test.add(63);
        test.add(65);
        test.add(0);
        test.add(71);
        subNums nums = new subNums(test);
        nums.getSubNums(3)
                .sorted(new subComparator())
                .forEach((x) -> System.out.println(x));
        System.out.println(nums.getMinSum(3).get());
    }
}
