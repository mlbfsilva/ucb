#include <stdio.h>

int bubble(int *v, int size)
{
    
     
         for (int i = 0; i < size -1; i++)
    {
        if(v[i] > v[i+1])
        {
            
            int transferencia = v[i];
            v[i] = v[i+1];
            v[i+1] = transferencia;
            i = -1;


        }
    }  
   
}

int main(){
    int vetor[] = {10, -8, -78, 91, 1, 9, 0};
    int len = sizeof(vetor)/sizeof(vetor[0]);

    bubble(vetor, len);
    printf("\r\n");
    for (int i = 0; i < len; i++){
        printf("%2d ", vetor[i]);
    }

    return 0;
}