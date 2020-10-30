#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARN.h"

static Node_ARN* first;
static int n;

static int is_red(Node_ARN* raiz) {
    if(raiz == NULL)
        return 0;
    return raiz->cor;
}

static void flip_color(Node_ARN* raiz) {
    raiz->cor = 1 - raiz->cor;
    raiz->dir->cor = 1 - raiz->dir->cor;
    raiz->esq->cor = 1 - raiz->esq->cor;
    
    if(raiz == first)
        raiz->cor = 0;
}

static Node_ARN* rotate_left(Node_ARN* raiz) {
    Node_ARN* aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    
    int aux2 = raiz->cor;
    raiz->cor = aux->cor;
    aux->cor = aux2;
    
    if(raiz == first)
        first = aux;

    return aux;
}

static Node_ARN* rotate_right(Node_ARN* raiz) {
    Node_ARN* aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;

    int aux2 = raiz->cor;
    raiz->cor = aux->cor;
    aux->cor = aux2;

    if(raiz == first)
        first = aux;

    return aux;
}

static Node_ARN* balance(Node_ARN* raiz) {
    if(is_red(raiz->dir) && !is_red(raiz->esq))
        raiz = rotate_left(raiz);
    if(is_red(raiz->esq) && is_red(raiz->esq->esq))
        raiz = rotate_right(raiz);
    if(is_red(raiz->esq) && is_red(raiz->dir))
        flip_color(raiz);
    
    return raiz;
}

Node_ARN* ARN_init() {
    first = NULL;
    n = 0;

    return first;
}

Node_ARN* ARN_get(Node_ARN* raiz, char* palavra) {
    if(raiz == NULL)
        return NULL;
    if(strcmp(raiz->palavra, palavra) < 0) {
        return ARN_get(raiz->dir, palavra);
    }
    else if(strcmp(raiz->palavra, palavra) > 0) {
        return ARN_get(raiz->esq, palavra);
    }
    else {
        return raiz;
    }
}

Node_ARN* ARN_put(Node_ARN* raiz, char* palavra) {
    if(raiz == NULL) {
        Node_ARN* novo = malloc(sizeof(Node_ARN));
        novo->palavra = palavra;
        novo->frequencia = 1;
        novo->cor = 1;
        novo->dir = NULL;
        novo->esq = NULL;

        if(n == 0)
            first = novo;
        n++;
        return novo;
    }
    if(strcmp(raiz->palavra, palavra) < 0) {
        raiz->dir = ARN_put(raiz->dir, palavra);
    }
    else if(strcmp(raiz->palavra, palavra) > 0) {
        raiz->esq = ARN_put(raiz->esq, palavra);
    }
    else {
        raiz->frequencia++;
    }
    raiz = balance(raiz);
    return raiz;
}

void ARN_imprime(Node_ARN* raiz) {
    if(raiz == NULL) return;

    ARN_imprime(raiz->esq);
    
    printf("+---------------+\n");
    printf("     | %s |\n", raiz->palavra);
    printf("     |  %d  |\n", raiz->frequencia);
    printf("+---------------+\n");
    printf("\n");

    ARN_imprime(raiz->dir);
}

void ARN_imprime_chaves() {
    printf("Número de chaves na ARN: %d\n", n);
}