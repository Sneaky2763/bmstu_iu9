public class Parse {
    private char Sym;
    private String input;
    private int curr;
    private boolean panic;

    public Parse(String a){
        this.input = a;
        curr=0;
        panic = false;
    }

    public void Next(){
        this.Sym = input.charAt(curr);
        curr++;
    }

    public boolean isNumber(char a){
        return Character.isDigit(a);
    }

    public boolean isLetter(char a){
        return Character.isLetter(a);
    }

    public void Panic(){
        System.out.println("Ошибка в " + curr + " позиции ");
        panic = true;
    }

    public void Ident(){
        Next();
        while(Sym!=',' && Sym!='}' && curr<input.length()){
            if(isNumber(Sym) || isLetter(Sym)){
                Next();
            } else {
                Panic();
                break;
            }
        }
        if(!panic){
            System.out.println("<Item>::= IDENT");
            if(Sym==','){
                System.out.println("<Tail>::= , <List>");
            }
            if(Sym=='}'){
                if(curr==input.length()){
                    System.out.println("<Tail>::= ε");
                } else {
                    Next();
                    if (Sym == ',') {
                        System.out.println("<Tail>::= ε");
                        System.out.println("<Tail>::= , <List>");
                    } else {
                        Panic();
                    }
                }
            }
        }
    }

    public void ParseAll(){
        System.out.println("<List>::= <Item> <Tail> ");
        while(curr!=input.length()){
            Next();

            if(panic){
                break;
            }

            if(isLetter(Sym)){
                Ident();
                continue;
            }

            if(Sym==' '){
                continue;
            }

            if(Sym=='{'){
                System.out.println("<Item>::= { <List> }");
                Ident();
                continue;
            }

            Panic();
            break;
        }
        if(!panic){
            System.out.println("<Tail>::= ε");
        }
    }
}
