public class Test {
    public static void main(String[] args) {
        int len = args.length;
        String message = "Введите длину первого массива и его " +
                "аргументы, затем длину второго массива и его аргументы.";
        if (len == 0) {
            System.out.println(message);
        } else {
            int curr = 0;
            int len1 = Integer.parseInt(args[curr]);
            ++curr;

            if (len < len1 + 2) {
                System.out.println(message);
            } else {
                int[] data1 = new int[len1];
                for (int i = 0; i < len1; ++i) {
                    data1[i] = Integer.parseInt(args[curr]);
                    ++curr;
                }

                int len2 = Integer.parseInt(args[curr]);
                ++curr;
                if (len < len1 + len2 + 2) {
                    System.out.println(message);
                } else {
                    int[] data2 = new int[len2];
                    for (int i = 0; i < len2; ++i) {
                        data2[i] = Integer.parseInt(args[curr]);
                        ++curr;
                    }

                    Set set1 = new Set(data1);
                    Set set2 = new Set(data2);

                    System.out.print("Пересечение множеств: ");
                    set1.findIntersection(set2);
                }
            }
        }
    }
}

