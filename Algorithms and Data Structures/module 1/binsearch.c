unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)){
    
    unsigned long L = 0;
    unsigned long R = nel;
    unsigned long M;
    
    while(R-L>1){
        
        M = (L+R)/2;
        
        if (compare(M)==0){
            return M;
        }
        if (compare(M)==1){
            R=M;
        } else {
            L=M;
        }
    }
    
    if(compare(L)==0){
        return L;
    }
    
    return nel;
}