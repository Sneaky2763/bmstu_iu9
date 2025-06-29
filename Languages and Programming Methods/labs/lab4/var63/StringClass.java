import java.util.Iterator;

public class StringClass implements Iterable<StringBuilder>{
    private StringBuilder s;

    public StringClass(StringBuilder s){
        this.s = s;
    }

    public Iterator iterator(){
        return new StringIter();
    }

    public boolean isVovel(char a){
        return a=='a' || a=='e' || a=='i' || a=='o' || a=='u';
    }

    public void SetString(StringBuilder a){
        this.s = a;
    }
    private class StringIter implements Iterator<StringBuilder>{
        private StringBuilder allVovels;
        public StringIter(){
            StringBuilder vovels = new StringBuilder();
            for(int i=0; i<s.length(); ++i){
                if(isVovel(s.charAt(i))){
                    vovels.append(s.charAt(i));
                }
            }
            this.allVovels = vovels;
        }

        private int start=0;
        private int finish=0;

        public boolean hasNext(){
            return start<allVovels.length()-1;
        }

        public StringBuilder next(){
            finish++;
            if(finish>allVovels.length()){
                start++;
                finish=start+1;
            }
            StringBuilder res = new StringBuilder(allVovels.substring(start, finish));
            return res;
        }
    }
}
