#include <stdio.h>
#define IMPLEMENT_ADD //se colocar isso em alguma parte do codigo, 
//somente ira ser compilado se existir essa parte aqui em cima

void getTerms(int * addr1, int * addr2, char * msg1, char * msg2);



int main(){

    // static char string[200] = "Hello world";
    // //string[1] = 'E';
    
    // *string = 'Z';
    // puts(string);



    int arg1, arg2, res;

    getTerms(&arg1, &arg2, "Insira o primeiro termo", 
                           "Insira o segundo termo");
    
    res = arg1 + arg2;
    
    printf("%d+%d=%d", arg1, arg2, res);

    return 0; 
}

#ifdef IMPLEMENT_ADD
void getTerms(int * addr1, int * addr2, char * msg1, char * msg2){

    puts(msg1);

    fflush(stdin); 
    scanf("%d", addr1);

    puts(msg2);
    fflush(stdin); 
    scanf("%d", addr2);

}
#endif