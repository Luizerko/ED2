#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tries.h"

static int n;
static char palavra_aux[50];

Node_trie* trie_init() {
    Node_trie* first = NULL;
    n = 0;

    return first;
}

Node_trie* trie_put(Node_trie* raiz, char* palavra, int iterador, int tamanho) {
    if(raiz == NULL) {
        Node_trie* novo = malloc(sizeof(Node_trie));
        novo->palavra = palavra[iterador];
        iterador++;
        novo->frequencia = 0;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->meio = NULL;

        if(iterador == tamanho) {
            novo->frequencia = 1;
            n++;
            return novo;
        }

        novo->meio = trie_put(novo->meio, palavra, iterador, tamanho);
        return novo;
    }

    if(raiz->palavra < palavra[iterador]) {
        raiz->dir = trie_put(raiz->dir, palavra, iterador, tamanho);
    }
    else if(raiz->palavra > palavra[iterador]) {
        raiz->esq = trie_put(raiz->esq, palavra, iterador, tamanho);
    }
    else {
        iterador++;
        if(iterador == tamanho) {
            if(raiz->frequencia == 0)
                n++;
            raiz->frequencia++;
            return raiz;
        }
        raiz->meio = trie_put(raiz->meio, palavra, iterador, tamanho);
    }

    return raiz;
}


void trie_imprime(Node_trie* raiz, int iterador) {
    if(raiz == NULL)
        return;
    trie_imprime(raiz->esq, iterador);
    palavra_aux[iterador] = raiz->palavra;
    iterador++;
    if(raiz->frequencia != 0) {
        printf("+---------------+\n");
        printf("     |  ");
        for(int i = 0; i < iterador; i++) {
            printf("%c", palavra_aux[i]);
        }
        printf("  |\n");
        printf("     |  %d  |\n", raiz->frequencia);
        printf("+---------------+\n");
        printf("\n");
    }
    trie_imprime(raiz->meio, iterador);
    iterador--;
    trie_imprime(raiz->dir, iterador);
    
}

void trie_imprime_chaves() {
    printf("Número de chaves na tries: %d\n", n);
}