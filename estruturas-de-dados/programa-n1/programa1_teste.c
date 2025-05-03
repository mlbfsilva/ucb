#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <string.h>

#define NOME_ARQUIVO 15
#define SENSOR 5

typedef struct {
    char id_sensor[SENSOR];
    long long timestamp;
    float valor;
} Sensores;

void abrir_arquivo(char arq_nome[NOME_ARQUIVO], int n_linhas, Sensores *sensor){
    FILE *arquivo_entrada = fopen(arq_nome, "r");
    if (arquivo_entrada = NULL){
        printf("Erro ao abrir arquivo.");
        return;
    }
    Sensores temp;
    int i=0;
    while (fscanf (arquivo_entrada, "%s[^;];%lld;%f\n", temp.id_sensor, temp.timestamp, temp.valor)==3){
    sensor[i] = temp;
    i++;
    }
    fclose(arquivo_entrada);
    return;
}

void ordenar_sensores_alfabetico(Sensores *sensor, int size){
    int i;
    int j;
    int indx;

    Sensores temp;
    
    for(i=0; i < size; i++){
        indx = i;
        for(j = i+1; j < size; j++){
            if(strcmp(sensor[j].id_sensor, sensor[indx].id_sensor)<0)
            indx = j;
        }
    }
    if(indx != i){
        temp = sensor[i];
        sensor[i] = sensor[indx];
        sensor[indx]= temp;
    }
}
void ordenar_sensores_alfabetico_(Sensores *sensor, int size){
    for(int i=0; i<size; i++){
        ordenar_sensores_alfabetico(sensor, size -i);
    }
}

void ordenar_sensores_timestamp(Sensores *sensor, int size){
    int i;
    int j;
    int indx;

    Sensores temp;

    for(i =0; i < size; i++){
        indx = i;
        for(j = i+1; j < size; j++){
            if(sensor[j].timestamp < sensor[indx].timestamp){
                indx = j;
            }
        }
        if(indx != i){
            temp = sensor[i];
            sensor[i] = sensor[indx];
            sensor[indx] = temp;
        }
    }
}
void ordenar_sensores_timestamp_(Sensores *sensor, int size){
    for(int i=0; i<size; i++){
        ordenar_sensores_timestamp(sensor, size -i);
    }
}

void salvar_arq(FILE * arquivo, Sensores *sensor, int size){
    for (int i = 0; i<size-1; i++){
        fprintf(arquivo, "%s;%lld;%.2f\n", sensor[i].id_sensor, sensor[i].timestamp, sensor[i].valor);
    }
    fprintf(arquivo, "%s;%lld;%.2f\n", sensor[size-1].id_sensor, sensor[size-1].timestamp, sensor[size-1].valor);
    fclose(arquivo);
}

/* void criar_novo_arquivo(int nome_arq, Sensores *sensor, int size){
    FILE *arquivo_saida = fopen("FLUX.txt", "w");
    switch(nome_arq){
        case 0:
            arquivo_saida = fopen("FLUX.txt", "w");
            if(arquivo_saida ==NULL){
                printf("Erro ao criar novo arquivo.\n");
                return;
            }
    }
    
} */

int main(){

    int numero_sensores = 5000;
    int qtd_sensores;
    
    Sensores sensor[numero_sensores];
    abrir_arquivo("sensores_novo.txt", numero_sensores, sensor);

    ordenar_sensores_alfabetico_(sensor, numero_sensores);
    

    

}