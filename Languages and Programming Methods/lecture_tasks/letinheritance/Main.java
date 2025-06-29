import java.util.Stack;
class A{
    public String valA;
    public A(String a){
        this.valA=a;
    }
    public String toString(){
        return valA;
    }
}
class B extends A{
    public String valB;
    public B(String a, String b){
        super(a);
        this.valB=b;
    }
    public String toString(){
        return valA + " " + valB;
    }
}
class C extends A{
    public String valC;
    public C(String a, String c){
        super(a);
        this.valC=c;
    }
    public String toString(){ return valA + " " + valC; }
}
class D extends B{
    public String valD;
    public D(String a, String b, String d){
        super(a, b);
        this.valD=d;
    }
    public String toString(){
        return valA + " " + valB + " " + valD;
    }
}
class E extends B{
    public String valE;
    public E(String a, String b, String e){
        super(a, b);
        this.valE=e;
    }
    public String toString(){
        return valA + " " + valB + " " + valE;
    }
}
class F extends C{
    public String valF;
    public F(String a, String c, String f){
        super(a, c);
        this.valF=f;
    }
    public String toString(){
        return valA + " " + valC + " " + valF;
    }
}
class G extends D{
    public String valG;
    public G(String a, String b, String d, String g){
        super(a, b, d);
        this.valG=g;
    }
    public String toString(){
        return valA + " " + valB + " " + valD + " " + valG;
    }
}
class J extends D{
    public String valJ;
    public J(String a, String b, String d, String j){
        super(a, b, d);
        this.valJ=j;
    }
    public String toString(){return valA + " " + valB + " " + valD + " " + valJ;}
}
class K extends D{
    public String valK;
    public K(String a, String b, String d, String k){
        super(a, b, d);
        this.valK=k;
    }
    public String toString(){
        return valA + " " + valB + " " + valD + " " + valK;
    }
}

public class Main {
    public static void pushReversed(
            Stack<? super D> dest,
            Stack<? extends D> src)
    {
        while(!src.empty()){
            dest.push(src.pop());
        }
    }
    public static void main(String[] args) {
        Stack<A> dest=new Stack();
        Stack<D> src=new Stack();
        src.push(new D("1", "2", "3"));
        src.push(new D("4", "5", "6"));
        src.push(new D("7", "8", "9"));
        pushReversed(dest, src);
        while(!dest.empty()){
            System.out.println(dest.pop());
        }
    }
}
