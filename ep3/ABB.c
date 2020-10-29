#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABB.h"

static int n;

Node_ABB* ABB_init() {
    Node_ABB* first = NULL;
    n = 0;

    return first;
}

Node_ABB* ABB_get(Node_ABB* raiz, char* palavra) {
    if(raiz == NULL)
        return NULL;
    if(strcmp(raiz->palavra, palavra) < 0) {
        return ABB_get(raiz->dir, palavra);
    }
    else if(strcmp(raiz->palavra, palavra) > 0) {
        return ABB_get(raiz->esq, palavra);
    }
    else {
        return raiz;
    }
}

Node_ABB* ABB_put(Node_ABB* raiz, char* palavra) {
    if(raiz == NULL) {
        Node_ABB* novo = malloc(sizeof(Node_ABB));
        novo->palavra = palavra;
        novo->frequencia = 1;
        novo->dir = NULL;
        novo->esq = NULL;
        n++;
        return novo;
    }
    if(strcmp(raiz->palavra, palavra) < 0) {
        raiz->dir = ABB_put(raiz->dir, palavra);
    }
    else if(strcmp(raiz->palavra, palavra) > 0) {
        raiz->esq = ABB_put(raiz->esq, palavra);
    }
    else {
        raiz->frequencia++;
    }
    return raiz;
}

void ABB_imprime(Node_ABB* raiz) {
    if(raiz == NULL) return;

    ABB_imprime(raiz->esq);
    
    printf("+---------------+\n");
    printf("     | %s |\n", raiz->palavra);
    printf("     |  %d  |\n", raiz->frequencia);
    printf("+---------------+\n");
    printf("\n");

    ABB_imprime(raiz->dir);

}

void ABB_imprime_chave() {
    printf("Número de chaves na ABB: %d\n", n);
}