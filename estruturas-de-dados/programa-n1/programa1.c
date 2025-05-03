#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <locale.h>

#define NOME_ARQUIVO 50
#define SENSOR 5

typedef struct {
    char id_sensor[SENSOR];
    long long timestamp;
    float valor;
} Sensores;

void abrir_arquivo(const char *arq_nome, int n_linhas, Sensores *sensor){
    FILE *arquivo_entrada = fopen(arq_nome, "r");
    if (arquivo_entrada == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Sensores temp;
    int i = 0;
    while (i < n_linhas &&
        fscanf(arquivo_entrada, "%4[^;];%lld;%f\n", temp.id_sensor, &temp.timestamp, &temp.valor) == 3){
        sensor[i] = temp;
        i++;
    }
    fclose(arquivo_entrada);
}

void ordenar_sensores_alfabetico(Sensores *sensor, int size){
    for(int i=0; i < size - 1; i++){
        for(int j = i+1; j < size; j++){
            if(strcmp(sensor[i].id_sensor, sensor[j].id_sensor) > 0){
                Sensores temp = sensor[i];
                sensor[i] = sensor[j];
                sensor[j] = temp;
            }
        }
    }
}

void ordenar_sensores_timestamp(Sensores *sensor, int size){
    for(int i=0; i < size - 1; i++){
        for(int j = i+1; j < size; j++){
            if(sensor[i].timestamp > sensor[j].timestamp){
                Sensores temp = sensor[i];
                sensor[i] = sensor[j];
                sensor[j] = temp;
            }
        }
    }
}

void salvar_arq(FILE *arquivo, Sensores *sensor, int size){
    for (int i = 0; i < size; i++){
        fprintf(arquivo, "%s;%lld;%.2f\n", sensor[i].id_sensor, sensor[i].timestamp, sensor[i].valor);
    }
    fclose(arquivo);
}

void criar_novo_arquivo(int nome_arq, Sensores *sensor, int size){
    const char *nomes_arquivos[] = { "FLUX.txt", "PRES.txt", "TEMP.txt", "UMID.txt", "VIBR.txt" };

    if (nome_arq < 0 || nome_arq >= 5) {
        printf("Erro: tipo de sensor inválido.\n");
        return;
    }

    FILE *arquivo_saida = fopen(nomes_arquivos[nome_arq], "w");
    if (arquivo_saida == NULL){
        printf("Erro ao criar novo arquivo %s.\n", nomes_arquivos[nome_arq]);
        return;
    }

    salvar_arq(arquivo_saida, sensor, size);
    printf("Arquivo (%s) criado com sucesso.\n", nomes_arquivos[nome_arq]);
}

void continuar_no_switch(){
    printf("Para continuar, aperte Enter...\n");
    while (getchar() != '\n');
}

int posicao_lista_sensores(Sensores *sensor, int size, int inicio){
    for (int i = inicio + 1; i < size; i++) {
        if (strcmp(sensor[i].id_sensor, sensor[inicio].id_sensor) != 0) {
            return i;
        }
    }
    return size;
}

int main(){
    int numero_sensores = 5000;
    int qtd_sensores = 5;
    int posicao_lista;
    int inicio = 0;

    Sensores sensor[numero_sensores];
    Sensores alfa[numero_sensores];

    abrir_arquivo("sensores_novo.txt", numero_sensores, sensor);
    ordenar_sensores_alfabetico(sensor, numero_sensores);

    for(int sensor_atual = 0; sensor_atual < qtd_sensores; sensor_atual++){
        posicao_lista = posicao_lista_sensores(sensor, numero_sensores, inicio);
        int p = 0;

        for(int i = inicio; i < posicao_lista; i++){
            alfa[p++] = sensor[i];
        }

        ordenar_sensores_timestamp(alfa, p);
        criar_novo_arquivo(sensor_atual, alfa, p);

        inicio = posicao_lista;
        continuar_no_switch();
        printf("Programa será finalizado.");
    }
    
    return 0;
}
