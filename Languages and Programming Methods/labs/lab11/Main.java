//<List>::= <Item> <Tail>
//<Tail>::= , <List> |ε
//<Item>::= IDENT | { <List> }

public class Main {
    public static void main(String[] args) {
        String a = "alpha, {beta, gamma}, delta";
        Parse parser = new Parse(a);
        parser.ParseAll();
    }
}