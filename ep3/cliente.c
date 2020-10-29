#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"
#include "ARN.h"
#include "node_ABB.h"
#include "node_ARN.h"

Node_ABB* raiz_ABB;
Node_ARN* raiz_ARN;

void adiciona_palavra(char* palavra, int contador) {
    raiz_ABB = ABB_put(raiz_ABB, palavra);
    //raiz_ARN = ARN_put(raiz_ARN, palavra);
}

void imprime_palavras() {
    ABB_imprime(raiz_ABB);
    ARN_imprime(raiz_ARN);
}

void imprime_numero_chaves() {
    ABB_imprime_chave();
    ARN_imprime_chave();
}

int main(int argc, char* argv[]) {

    char* texto = argv[1];
    printf("\n%s\n", texto);

    raiz_ABB = ABB_init();
    raiz_ARN = ARN_init();

    FILE* file;
    char c;
    int contador = 0;
    char palavra_aux[50];

    file = fopen(texto, "r");
    if(file == NULL)
        exit(EXIT_FAILURE);

    clock_t ini, fim;
    ini = clock();

    while((c = getc(file)) != EOF) {
        if(c >= 65 && c <= 90) {
            c += 32;
        }
        if(c >= 97 && c <= 122) {
            palavra_aux[contador] = c;
            contador++;
        }
        else {
            char* palavra = malloc(contador*sizeof(char));
            for(int i = 0; i < contador; i++) {
                palavra[i] = palavra_aux[i];
            }
            adiciona_palavra(palavra, contador);
            contador = 0;
        }
        /*
        printf("%c -> ", c);
        for(int i = 0; i < contador; i++) {
            printf("%c", palavra_aux[i]);
        }

        printf("\n");
        sleep(1);
        */
    }

    //imprime_palavras();
    imprime_numero_chaves();

    fclose(file);

    fim = clock();

    printf("Tempo de execução: %lf\n", (double)(fim - ini)/CLOCKS_PER_SEC);

    return 0;
}