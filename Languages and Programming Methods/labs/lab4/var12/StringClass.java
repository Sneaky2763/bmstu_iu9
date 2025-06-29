import java.util.Iterator;
import java.util.ArrayList;

public class StringClass implements Iterable<String>{
    private ArrayList<String> strings;

    public StringClass(ArrayList<String> a){
        this.strings = new ArrayList<String>();
        for(int i=0; i<a.size(); ++i){
            strings.add(a.get(i));
        }
    }

    public void setStrings(ArrayList<String> b){
        this.strings = new ArrayList<String>();
        for(int i=0; i<b.size(); ++i){
            strings.add(b.get(i));
        }
    }

    public Iterator iterator(){
        return new StringIter();
    }

    public boolean intersecting(String a, String b){
        boolean intersecting = false;
        for(int i=0; i<a.length(); ++i){
            for(int j=0; j<b.length(); ++j){
                if(a.charAt(i)==b.charAt(j)){
                    intersecting=true;
                }
            }
        }
        return intersecting;
    }

    private class StringIter implements Iterator<String>{
        private int start=0;
        private int finish=0;

        public boolean hasNext(){
            return start<strings.size()-1;
        }

        public String next(){
            while(intersecting(strings.get(start), strings.get(finish))){
                finish++;
                if(finish>=strings.size()){
                    start++;
                    finish=start+1;
                    if (start >= strings.size() - 1){
                        return "";
                    }
                }
            }

            String res = new String();
            res+=(strings.get(start)) + " ";
            res+=(strings.get(finish));

            finish++;
            if(finish>=strings.size()){
                start++;
                finish=start+1;
            }
            return res;
        }
    }
}

