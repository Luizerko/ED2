#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"
#include "ARN.h"
#include "tries.h"
#include "node_ABB.h"
#include "node_ARN.h"
#include "node_trie.h"

Node_ABB* raiz_ABB;
Node_ARN* raiz_ARN;
Node_trie* raiz_trie;

void adiciona_palavra(char* palavra, int contador) {
    //raiz_ABB = ABB_put(raiz_ABB, palavra);
    //raiz_ARN = ARN_put(raiz_ARN, palavra);
    raiz_trie = trie_put(raiz_trie, palavra, 0, contador);
}

void imprime_palavras() {
    ABB_imprime(raiz_ABB);
    ARN_imprime(raiz_ARN);
    trie_imprime(raiz_trie, 0);
}

void imprime_numero_chaves() {
    ABB_imprime_chaves();
    ARN_imprime_chaves();
    trie_imprime_chaves();
}

int main(int argc, char* argv[]) {

    char* texto = argv[1];
    printf("\n%s\n", texto);

    raiz_ABB = ABB_init();
    raiz_ARN = ARN_init();
    raiz_trie = trie_init();

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
            if(contador > 0) {
                char* palavra = malloc(contador*sizeof(char));
                for(int i = 0; i < contador; i++) {
                    palavra[i] = palavra_aux[i];
                }
                adiciona_palavra(palavra, contador);
                //imprime_palavras();
                contador = 0;
            }
        }
        
        /*
        printf("%c -> ", c);
        for(int i = 0; i < contador; i++) {
            printf("%c", palavra_aux[i]);
        }

        printf("\n");
        //sleep(1);
        */
    }

    //imprime_palavras();
    imprime_numero_chaves();

    fclose(file);

    fim = clock();

    printf("Tempo de execução: %lf\n", (double)(fim - ini)/CLOCKS_PER_SEC);

    return 0;
}