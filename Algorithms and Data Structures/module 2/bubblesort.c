void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)){
            if (nel<=1){
                return;
            }
            for(int i=0; i<nel/2+1; ++i){
                for(int j=0; j<nel-1-i; ++j){
                    if(compare(j, j+1)==1){
                        swap(j, j+1);
                    }
                }
                for(int j=nel-2; j>=i; --j){
                    if(compare(j, j+1)==1){
                        swap(j, j+1);
                    }
                }
            }
        }