#include <stdio.h>


int main(){

    int a = 10;
    char str[124];
    
    printf("Hello");
    FILE * fd = fopen("helloworld.txt", "r"); 
    if(fd == NULL){
        printf("\r\n Erro ao abrir o arquivo!");
        return -1;
    }
    

    int linha =0;
    fgets(str, 124, fd);

        
        
        printf("%d: %s", linha++, str);
        fseek(fd, SEEK_SET, 2);
        
    
    fclose(fd);
    
}