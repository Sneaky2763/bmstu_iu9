import java.util.ArrayList;
import java.util.Comparator;
import java.util.Optional;
import java.util.stream.IntStream;
import java.util.stream.Stream;

class subComparator implements Comparator<ArrayList<Integer>>{
    public int compare(ArrayList<Integer> a, ArrayList<Integer> b){
        int min1 = a.get(0);
        int min2 = b.get(0);
        for(int i=0; i<a.size(); ++i){
            if(a.get(i)<min1){
                min1 = a.get(i);
            }
        }
        for(int i=0; i<b.size(); ++i){
            if(b.get(i)<min2){
                min2 = b.get(i);
            }
        }

        if(min1>min2){
            return 1;
        }
        if(min1==min2){
            return 0;
        }

        return -1;
    }
}

public class subNums {
    ArrayList<Integer> nums;

    public subNums(ArrayList<Integer> a) {
        this.nums = new ArrayList(a);
    }

    public int sum(ArrayList<Integer> a){
        int total=0;
        for(int i=0; i<a.size(); ++i){
            total+=a.get(i);
        }
        return total;
    }

    public Stream<ArrayList<Integer>> getSubNums(int k){
        ArrayList<ArrayList<Integer>> res = new ArrayList();
        int size = nums.size();

        IntStream.range(0, (size + k - 1) / k)
                .mapToObj(i -> nums.subList(
                        i * k,
                        Math.min((i + 1) * k, size)
                ))
                .forEach(x -> res.add(new ArrayList<>(x)));

        return res.stream();
    }

    public Optional<Integer> getMinSum(int k){
        ArrayList<Integer> sums = new ArrayList<>();
        Optional<Integer> res = Optional.empty();
        int size = this.nums.size();

        IntStream.range(0, (size + k - 1) / k)
                .mapToObj(i -> nums.subList(
                        i * k,
                        Math.min((i + 1) * k, size)
                ))
                .forEach(x -> sums.add(sum(new ArrayList<>(x))));

        res = sums.stream().sorted().findFirst();
        return res;
    }
}
