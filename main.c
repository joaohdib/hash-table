#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLACA_SIZE 10
#define HASH_TABLE_SIZE 1031

struct placa {
    char* idPlaca;
    int numColisoes;
};
typedef struct placa Placa;

int calculaHash(char* placa) {
    int hash = 0;
    int base = 13;

    for (int i = 0; i < (PLACA_SIZE - 2); i++) {
        hash = (hash * base + placa[i]) % HASH_TABLE_SIZE;
    }

    return hash;
}

void insereHashTable(Placa* placa, char* HashTable[], int hash,
    int* qtdColisoes) {
    int originalHash = hash;
    int step = 1;

    if (hash >= HASH_TABLE_SIZE) {
        return;
    }
    while (HashTable[hash] != NULL) {
        if (strcmp(HashTable[hash], placa->idPlaca) == 0) {
            return;
        }
        (*qtdColisoes)++;
        hash = (originalHash + step * step) % HASH_TABLE_SIZE;
        step++;
        if (step > HASH_TABLE_SIZE) {
            return;
        }
    }

    HashTable[hash] = placa->idPlaca;
}

void printaColisoes(int* qtdColisoes) {
    printf("--- QTD COLISOES: %d ---\n", *qtdColisoes);
    return;
}

int procuraColisao(char* placa, char* hashTable[]) {
    int hash = calculaHash(placa);
    int originalHash = hash;
    int step = 1;

    while (hashTable[hash] != placa) {
        hash = (originalHash + step * step) % HASH_TABLE_SIZE;
        step++;
        if (step > HASH_TABLE_SIZE) {
            printf("------------------ FIM DA HASH ------------------\n");
            return -1;
        }
    }

    return hash;
}

int procuraHashTable(char* placa, char* hashTable[]) {
    int hash = calculaHash(placa);
    int hashCorreto;
    if (hashTable[hash] != placa) {
        hashCorreto = procuraColisao(placa, hashTable);
        if (hashCorreto < 0) {
            return 0;
        }
    }
    else {
        hashCorreto = hash;
    }
    return hashCorreto;
}

void deleteHashTable(char* placa, char* hashTable[]) {
    int hash = procuraHashTable(placa, hashTable);
    free(hashTable[hash]);
    hashTable[hash] = NULL;

    return;
}

int main(void) {
    clock_t start, end, diff;
    double tempo;
    int numTeste;
    int* qtdColisoes;
    int numColisoes = 0;
    qtdColisoes = &numColisoes;
    char placa[PLACA_SIZE];
    char placaVerdadeira[8];
    char* HashTablePlacas[HASH_TABLE_SIZE] = { NULL };
    char* placa2;
    int hash;

    FILE* file = fopen("placas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", "placas.txt");
        exit(1);
    }
    printf("--- INSERINDO PLACA ---\n\n");
    start = clock();
    while (fgets(placa, sizeof(placa), file) != NULL) {
        // Remove \r e \n da string
        int len = strlen(placa);
        if (len > 0 && placa[len - 1] == '\n') {
            placa[len - 1] = '\0'; // Remove o \n
            len--;
        }
        if (len > 0 && placa[len - 1] == '\r') {
            placa[len - 1] = '\0'; // Remove o \r
        }

        if (len <= 1) {
            continue;
        }

        Placa novaPlaca;
        novaPlaca.idPlaca = strdup(placa);
        novaPlaca.numColisoes = 0;

        hash = calculaHash(novaPlaca.idPlaca);
        insereHashTable(&novaPlaca, HashTablePlacas, hash, qtdColisoes);
    }
    end = clock();
    diff = end - start;
    tempo = (double)diff / CLOCKS_PER_SEC;
    printf("TEMPO DO INSERT: %f\n\n", tempo);

    fclose(file);

    printf("--- BUSCANDO PLACA ---\n\n");
    start = clock();
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (HashTablePlacas[i] != NULL) {
            procuraHashTable(HashTablePlacas[i], HashTablePlacas);
        }
    }
    end = clock();
    diff = end - start;
    tempo = (double)diff / CLOCKS_PER_SEC;
    printf("TEMPO DA BUSCA: %f\n\n", tempo);

    printf("--- DELETANDO PLACA: --- \n\n");
    start = clock();
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (HashTablePlacas[i] != NULL) {
            deleteHashTable(HashTablePlacas[i], HashTablePlacas);
        }
    }
    end = clock();

    diff = end - start;
    tempo = (double)diff / CLOCKS_PER_SEC;
    printf("TEMPO DO DELETE: %f\n\n", tempo);

    printaColisoes(qtdColisoes);

    return 0;
}
