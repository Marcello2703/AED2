#include <stdio.h>
#include <stdlib.h>

void primo_check(int x){
    int i, cont=0;
    if(x==1){ //caso base 1
        printf("%d 0\n", x);
    }else if(x==2){ //caso base 2
        printf("%d 1\n", x);
    }else{
        for(i=2; i<x; i++){
            if(x % i == 0){
                cont++;
            }
        }
        if(cont == 0){
            printf("%d 1\n", x);
        }else{
            printf("%d 0\n", x);
        }
    }
} 

int main(){
    int nCasos, num, i, *vetN;
    scanf("%d", &nCasos);

    vetN = (int *)malloc(nCasos*sizeof(int));

    for(i=0; i<nCasos; i++){
        scanf("%d", &vetN[i]);
    }
    
    for(i=0; i<nCasos; i++){
        primo_check(vetN[i]);
    }
    
    free(vetN);
    return 0;
}
