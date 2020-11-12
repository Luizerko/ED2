#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_encadeamento.h"
#include "ARN.h"
#include "node_ARN.h"

static int n;
static int tam;
static int colisao = 0;
static int primes[16] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869};
static int indice_prime = 0;

static int hash_function(char* palavra) {
    
    //djb2 hashing
    unsigned long int hash = 5381;
    int key;
    for(int contador = 0; contador < strlen(palavra); contador++) {
        key = palavra[contador];
        hash = ((hash << 5) + hash) + key;
    }

    return hash%primes[indice_prime];

    //hashing por multiplicação
    /*
    int key = 0;
    for(int contador = 0; contador < strlen(palavra); contador++) {
        key += palavra[contador];
    }

    float A = 0.6106154;
    return floor((((float)key*A) - (int)((float)key*A))*primes[indice_prime]);
    */

    /*
    //Apenas resto da divisão
    int key = 0;
    for(int contador = 0; contador < strlen(palavra); contador++) {
        key += palavra[contador];
    }

    return key%primes[indice_prime];
    */

}

static Node_hash_encadeamento** resize(Node_hash_encadeamento** vetor , int novo_tamanho) {
    Node_hash_encadeamento** auxiliar = malloc(novo_tamanho*sizeof(Node_hash_encadeamento*));
    for(int i = 0; i < novo_tamanho; i++)
        auxiliar[i] = NULL;

    for(int i = 0; i < tam; i++) {
        Node_hash_encadeamento* aux = vetor[i];
        Node_hash_encadeamento* anterior = NULL;
        while(aux != NULL) {
            int hash = hash_function(aux->palavra);

            Node_hash_encadeamento* aux2 = auxiliar[hash];
            Node_hash_encadeamento* anterior2 = NULL;
            while(aux2 != NULL) {
                anterior2 = aux2;
                aux2 = aux2->prox;
            }


            if(anterior2 == NULL) {
                auxiliar[hash] = aux;
            }

            else if(anterior2 != NULL) {
                anterior2->prox = aux;

                colisao++;
            }

            anterior = aux;
            aux = aux->prox;
            anterior->prox = NULL;
        }
    }

    free(vetor);
    return auxiliar;
}

Node_hash_encadeamento** hash_encadeamento_init() {
    Node_hash_encadeamento** first = malloc(53*sizeof(Node_hash_encadeamento*));
    for(int i = 0; i < 53; i++)
        first[i] = NULL;
    n = 0;
    tam = 53;

    return first;
}

Node_hash_encadeamento* hash_encadeamento_get(Node_hash_encadeamento** vetor, char* palavra) {
    int hash = hash_function(palavra);
    
    Node_hash_encadeamento* aux = vetor[hash];
    while(aux != NULL && strcmp(palavra, aux->palavra) != 0) {
        aux = aux->prox;
    }

    if(aux == NULL)
        return NULL;
    
    else
        return aux;

}

Node_hash_encadeamento** hash_encadeamento_put(Node_hash_encadeamento** vetor, char* palavra) {
    int hash = hash_function(palavra);
    
    Node_hash_encadeamento* auxiliar = vetor[hash];
    Node_hash_encadeamento* anterior = NULL;
    while(auxiliar != NULL && strcmp(auxiliar->palavra, palavra) != 0) {
        anterior = auxiliar;
        auxiliar = auxiliar->prox;
    }

    if(auxiliar == NULL) {
        Node_hash_encadeamento* novo = malloc(sizeof(Node_hash_encadeamento));
        novo->palavra = palavra;
        novo->frequencia = 1;
        novo->prox = NULL;

        if(anterior == NULL) {
            vetor[hash] = novo;
        }

        else if(anterior != NULL) {
            anterior->prox = novo;

            colisao++;
        }

        n++;
        if(n >= 10*tam) {
            indice_prime++;
            vetor = resize(vetor, primes[indice_prime]);
            tam = primes[indice_prime];
        }
    }

    else
        auxiliar->frequencia++;

    return vetor;

}

void hash_encadeamento_imprime(Node_hash_encadeamento** vetor) {
    Node_ARN* raiz_auxiliar = ARN_init();
    for(int i = 0; i < tam; i++) {
        Node_hash_encadeamento* aux = vetor[i];
        if(aux != NULL) {
            for(int j = 0; j < aux->frequencia; j++)
                raiz_auxiliar = ARN_put(raiz_auxiliar, aux->palavra);
            aux = aux->prox;
        }
    }
    ARN_imprime(raiz_auxiliar);
}

void hash_encadeamento_imprime_chaves() {
    printf("Número de chaves no vetor com hashing encadeamento: %d\n", n);
    printf("Número de colisões no vetor com hashing encadeamento: %d\n", colisao);
}