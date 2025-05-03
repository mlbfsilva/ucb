#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <string.h>

#define MAX_LINHAS 5000

typedef struct {
    long long timestamp;
    float valor;
} Leitura_sensor;

typedef struct {
    char id_sensor[5];
    int count;
    Leitura_sensor * leituras;
} Sensores;

int encontrar_sensores(Sensores sensores[], int n, const char *id){
    for(int i = 0; i < n; i++){
        if(strcmp(sensores[i].id_sensor, id)==0)
        return i;
    }
    return -1;
}


void ordenar_sensores_timestamp(Leitura_sensor *leituras, int size){
    int i;
    int j;
    int indx;

    Leitura_sensor temp;

    for(i =0; i < size; i++){
        indx = i;
        for(j = i+1; j < size; j++){
            if(leituras[j].timestamp < leituras[indx].timestamp){
                indx = j;
            }
        }
        if(indx != i){
            temp = leituras[i];
            leituras[i] = leituras[indx];
            leituras[indx] = temp;
        }
    }
}

int main(){

    FILE *arquivo = fopen("sensores_novo.txt", "r");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo\n");
        return -1; 
    }

    Sensores sensores[MAX_LINHAS];
    int total_sensores =5000;

    char linha[MAX_LINHAS];
    while (fgets(linha, sizeof(linha), arquivo)){
        long long timestamp;
        char id_sensor[5];
        float valor;

        if(sscanf(linha, "%ld;%s;%f", timestamp, id_sensor, valor)==3){
            int i=encontrar_sensores(sensores, total_sensores, id_sensor);
        }
    }
    fclose(arquivo);

    for(int i=0; i < total_sensores; i++){
        ordenar_sensores_timestamp(sensores[i].leituras, sensores[i].count);

        char nome_arquvo_novo[5];
        sprintf(nome_arquvo_novo, "%s.txt", sensores[i].id_sensor);

        FILE *arquivo_saida = fopen (nome_arquvo_novo, "w+");
        if (arquivo_saida = NULL){
            printf ("Erro ao tentar gerar novo arquivo");
            continue;
        }
        for(int j=0; j < sensores[i].count; j++){
            fprintf(arquivo_saida, "%ld;%s;%.2f", sensores[i].leituras[j].timestamp, sensores[i].leituras->valor);
        }
        fclose(arquivo_saida);
    }
    printf("Arquivos gerados com sucesso!");

}