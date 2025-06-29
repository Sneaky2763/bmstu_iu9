import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<Integer> test = new ArrayList();
        test.add(2);
        test.add(3);
        test.add(5);
        test.add(7);

        sumNums nums = new sumNums(test);
        nums.add(50);
        nums.gettableSum().forEach((x) -> System.out.println(x));
        System.out.println(nums.findNum().get());
    }
}