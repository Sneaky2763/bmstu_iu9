void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)){

            int fib[92] = {1, 2};
            int start=0;
            for (int i=2; i<92; ++i){
                fib[i]=fib[i-1]+fib[i-2];
                if (fib[i]>=nel){
                    start=i-1;
                    break;
                }
            }

            for(int i=start; i>=0; --i){
                int j=fib[i];
                while(j<nel){
                    int k=j;
                    while(k-fib[i]>=0 && compare(k-fib[i], k)==1){ /*ой*/
                        swap(k-fib[i], k);
                        k-=fib[i];
                    }
                    j+=1;
                }
            }
}