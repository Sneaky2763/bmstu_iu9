import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class sumNums {
    ArrayList<Integer> nums;

    public sumNums(ArrayList<Integer> a) {
        this.nums = new ArrayList(a);
    }

    public void add(int a){
        this.nums.add(a);
    }

    public Stream<Integer> gettableSum(){
        ArrayList<Integer> res = new ArrayList<>();
        this.nums.stream()
                .filter(x -> nums.stream()
                .anyMatch(a -> nums.contains(x - a)))
                .forEach(x -> res.add(x));
        return res.stream();
    }

    public Optional<Integer> findNum(){
        List<Integer> sorted = nums.stream()
                .sorted(Comparator.reverseOrder())
                .collect(Collectors.toList());

        return IntStream.range(0, sorted.size())
                .filter(i -> {
                    return sorted.subList(0, i).stream()
                            .noneMatch(x -> nums.stream()
                                    .anyMatch(a -> nums.contains(x - a)));
                })
                .mapToObj(sorted::get)
                .findFirst();
    }
}
