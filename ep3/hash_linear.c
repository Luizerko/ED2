#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_linear.h"
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

static Node_hash_linear** resize(Node_hash_linear** vetor , int novo_tamanho) {
    Node_hash_linear** auxiliar = malloc(novo_tamanho*sizeof(Node_hash_linear*));
    for(int i = 0; i < novo_tamanho; i++)
        auxiliar[i] = NULL;

    for(int i = 0; i < tam; i++) {
        int hash = hash_function(vetor[i]->palavra);

        int flag_colisao = 0;
        int aux = hash;
        while(auxiliar[aux] != NULL) {
            aux = (aux + 1)%primes[indice_prime];
            if(!flag_colisao) {
                colisao++;
                flag_colisao = 1;
            }
        }

        if(auxiliar[aux] == NULL) {
            auxiliar[aux] = vetor[i];
        }

    }

    free(vetor);
    return auxiliar;
}

Node_hash_linear** hash_linear_init() {
    Node_hash_linear** first = malloc(53*sizeof(Node_hash_linear*));
    for(int i = 0; i < 53; i++)
        first[i] = NULL;
    n = 0;
    tam = 53;

    return first;
}

Node_hash_linear* hash_linear_get(Node_hash_linear** vetor, char* palavra) {
    int hash = hash_function(palavra);
    
    int aux = hash;
    while(vetor[aux] != NULL && strcmp(palavra, vetor[aux]->palavra) != 0) {
        aux = (aux + 1)%tam;
    }

    if(vetor[aux] == NULL)
        return NULL;
    
    else
        return vetor[aux];

}

Node_hash_linear** hash_linear_put(Node_hash_linear** vetor, char* palavra) {
    int hash = hash_function(palavra);
    
    int flag_colisao = 0;
    int aux = hash;
    while(vetor[aux] != NULL && strcmp(palavra, vetor[aux]->palavra) != 0) {
        aux = (aux + 1)%tam;
        if(!flag_colisao) {
            colisao++;
            flag_colisao = 1;
        }
    }

    if(vetor[aux] == NULL) {
        vetor[aux] = malloc(sizeof(Node_hash_linear));
        vetor[aux]->palavra = palavra;
        vetor[aux]->frequencia = 1;

        n++;
        if(n == tam) {
            indice_prime++;
            //printf("colisões: %d\n", colisao);
            //exit(0);
            vetor = resize(vetor, primes[indice_prime]);
            tam = primes[indice_prime];
        }
    }

    else
        vetor[aux]->frequencia++;

    return vetor;

}

void hash_linear_imprime(Node_hash_linear** vetor) {
    Node_ARN* raiz_auxiliar = ARN_init();
    for(int i = 0; i < tam; i++) {
        if(vetor[i] != NULL) {
            for(int j = 0; j < vetor[i]->frequencia; j++)
                raiz_auxiliar = ARN_put(raiz_auxiliar, vetor[i]->palavra);
        }
    }
    ARN_imprime(raiz_auxiliar);
}

void hash_linear_imprime_chaves() {
    printf("Número de chaves no vetor com hashing linear: %d\n", n);
    printf("Número de colisões no vetor com hashing linear: %d\n", colisao);
}