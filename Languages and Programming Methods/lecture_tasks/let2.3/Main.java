public class Main{
    public static void main(String[] args) {
        WheelPlatform first = new WheelPlatform(123, 3);
        WheelPlatform second = new WheelPlatform(321, 35);
        WheelPlatform third = new WheelPlatform(100, 10);

        Stack<WheelPlatform> stack = new Stack<WheelPlatform>();

        stack.push(first);
        stack.push(second);
        stack.push(third);

        while(!stack.empty()){
            System.out.println(stack.pop());
        }
    }
}
