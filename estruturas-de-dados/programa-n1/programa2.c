#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define SENSOR 5
#define MAX_SENSORES 5000

typedef struct {
    char id_sensor[SENSOR];
    long long timestamp;
    float valor;
} Sensores;

long long converter_para_timestamp(int ano, int mes, int dia, int hora, int min, int seg) {
    struct tm data = {0};
    data.tm_year = ano - 1900;
    data.tm_mon = mes - 1;
    data.tm_mday = dia;
    data.tm_hour = hora;
    data.tm_min = min;
    data.tm_sec = seg;
    return (long long)mktime(&data);
}

int carregar_dados(const char *arquivo, Sensores *dados) {
    FILE *arquivo_dados = fopen(arquivo, "r");
    if (!arquivo_dados) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo);
        return 0;
    }
    int i = 0;
    while (fscanf(arquivo_dados, "%4[^;];%lld;%f\n", dados[i].id_sensor, &dados[i].timestamp, &dados[i].valor) == 3) {
        i++;
        if (i >= MAX_SENSORES) break;
    }
    fclose(arquivo_dados);
    return i; 
}

int busca_binaria_mais_proxima(Sensores *dados, int size, long long alvo) {
    int inicio = 0, fim = size - 1;
    int melhor_indice = -1;
    long long menor_diferenca = 100000000000000;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        long long diff = llabs(dados[meio].timestamp - alvo);

        if (diff < menor_diferenca) {
            menor_diferenca = diff;
            melhor_indice = meio;
        }
        if (dados[meio].timestamp < alvo) {
            inicio = meio + 1;
        } else if (dados[meio].timestamp > alvo) {
            fim = meio - 1;
        } else {
            return meio; 
        }
    }
    return melhor_indice;
}

int main() {
    char nome_sensor[15];
    int dia, mes, ano, hora, minuto, segundo;

    printf("Informe o nome do sensor (TEMP, PRES, VIBR, UMID, FLUX): ");
    scanf("%s", nome_sensor);

    printf("Informe a data e hora (DD MM AAAA HH MM SS): ");
    scanf("%d %d %d %d %d %d", &dia, &mes, &ano, &hora, &minuto, &segundo);

    long long timestamp_alvo = converter_para_timestamp(ano, mes, dia, hora, minuto, segundo);

    char nome_arquivo[20];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", nome_sensor);

    Sensores dados[MAX_SENSORES];
    int total = carregar_dados(nome_arquivo, dados);

    if (total == 0) {
        printf("Nenhum dado carregado.\n");
        return 1;
    }

    int indice = busca_binaria_mais_proxima(dados, total, timestamp_alvo);
    if (indice != -1) {
        printf("\nLeitura mais próxima encontrada:\n");
        printf("Sensor: %s\nTimestamp: %lld\nValor: %.2f\n", dados[indice].id_sensor, dados[indice].timestamp, dados[indice].valor);
    } else {
        printf("Nenhuma leitura encontrada.\n");
    }
    return 0;
}
