#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <string.h>

typedef struct 
{
    int dia;
    int mes;
    int ano;
} Data; 

time_t converterData(Data data){
    struct tm t;
    t.tm_year = data.ano - 1900;
    t.tm_mon = data.mes - 1;
    t.tm_mday = data.dia;
    return mktime(&t);
    
}

time_t geradorTimestampAleatorio(time_t periodo_dia){
    return periodo_dia + (rand() % 86400); // é o periodo do dia em segundos 
}

int main(){
    Data data; 
    char *sensores[] = {"TEMP", "PRES", "VIBR", "UMID", "FLUX"};
    int n_sensores= 5;
    int qtd_leitura_sensores= 1000;

    srand(time(NULL)); 

    printf("PROGRAMA 3:\n");
    printf("Digite a data com os valores solicitados.\n");
    printf("Digite o dia: ");
    scanf("%d", &data.dia);
    printf("Digite o mes: ");
    scanf("%d", &data.mes);
    printf("Digite o ano: ");
    scanf("%d", &data.ano);

    converterData(data);
    time_t dia_usuario = converterData(data);

    FILE *arquivo = fopen("sensores_novo.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    for (int i = 0; i < n_sensores; i++)
    {
        for (int j =0; j < qtd_leitura_sensores; j++)
        {
            time_t timestamp = geradorTimestampAleatorio(dia_usuario); 

            char *sensores_aleatorio= sensores[rand()% n_sensores];

            float valor = rand() % 100; 

            fprintf(arquivo, "%s;%ld;%.2f\n", sensores_aleatorio, timestamp, valor);
        } 
    }
}
