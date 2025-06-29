public class Set {
    private int[] nums;
    private int len;
    private boolean isSet;

    public Set(int[] data){
        this.isSet=true;
        this.len = data.length;
        this.nums = new int[len];
        for(int i=0; i<len; ++i) {
            for(int j=0; j<len; ++j) {
                if (data[i]==data[j] && i!=j){
                    System.out.println("Not a set");
                    this.isSet=false;
                    break;
                }
            }
            if (isSet==false){
                this.nums = new int[len];
                break;
            }
            this.nums[i] = data[i];
        }
    }

    public void findIntersection(Set a){
        boolean intersectionFound = false;
        for (int i=0; i<len; ++i){
            for(int j=0; j<a.len; ++j){
                if (this.nums[i]==a.nums[j]){
                    System.out.print(this.nums[i]);
                    System.out.print(" ");
                    intersectionFound = true;
                }
            }
        }

        if (!intersectionFound){
            System.out.println("не найдено," +
                    " или одно из множеств задано неверно.");
        }
    }

    public String toString(){
        String res = "";
        for(int i=0; i<len; ++i){
            res+=this.nums[i];
            if (i!=len-1){
                res+=", ";
            }
        }
        return res;
    }
}
