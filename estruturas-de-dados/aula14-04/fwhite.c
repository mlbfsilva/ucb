#include <stdio.h>

int main(){

    int a = 10;
    FILE * fd = fopen("helloworld.txt", "w"); 
    if(fd == NULL){
        printf("\r\n Erro ao abrir o arquivo!");
        return -1;
    }

    fputs("Hello World!", fd); //fputs é uma função para escrever no arquivo
    fprintf(fd, "\r a=%d\r", a);

    
    if (fflush(fd) != 0){
        printf("\r\n Erro ao escrever no arquivo");
    }
    
    fclose(fd);




}