/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

hash_encadeamento_MTF.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_encadeamento_MTF.h"
#include "ARN.h"
#include "node_ARN.h"

//Inicializa as variáveis globais: número de palavras na estrutura (n), tamanho do vetor (tam), número de colisões
//(colisao), primos que definem os tamanhos padrão que o vetor poderá ter em caso de resizing (primes[16]) e o primo
//dessa lista que está sendo utilizado (indice_prime).
static int n;
static int tam;
static int colisao = 0;
static int primes[16] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869};
static int indice_prime = 0;

//Função de hashing a ser utilizada. Aqui implementei três delas para perceber as diferenças no número de colisões. Como
//a djb2 teve um número de colisões substancialmente menor que as outras duas, foi a que permaneceu implementada.
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

    //Apenas resto da divisão
    /*
    int key = 0;
    for(int contador = 0; contador < strlen(palavra); contador++) {
        key += palavra[contador];
    }

    return key%primes[indice_prime];
    */

}

//Faz um resize do vetor de hashing, fazendo rehashing em todos os nós de todas as listas de todas as posições do vetor.
//O novo tamanho será o próximo primo escolhido da lista de primos primes para minimizar as colisões do algoritmo.
//Note que esse rehashing só sera feito caso o fator de ocupação da estrutura chegue a 10, ou seja, número de palavras
//10 vezes maior do que o tamanho do vetor.
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

            if(aux2 == NULL) {
                auxiliar[hash] = aux;
                
                anterior = aux;
                aux = aux->prox;
                anterior->prox = NULL;
            }

            else {
                anterior = aux;
                aux = aux->prox;

                anterior->prox = auxiliar[hash];
                auxiliar[hash] = anterior;

                colisao++;
            }

        }
    }

    free(vetor);
    return auxiliar;
}

//Inicializa o vetor de hashing com encadeamento e MTF, alocando 53 espaços - primeiro primo a ser utilizado para minimizar
//o número de colisões na estrutura quando da adição de novas palavras - e inicializando todos eles com NULL.
Node_hash_encadeamento** hash_encadeamento_MTF_init() {
    Node_hash_encadeamento** first = malloc(53*sizeof(Node_hash_encadeamento*));
    for(int i = 0; i < 53; i++)
        first[i] = NULL;
    n = 0;
    tam = 53;

    return first;
}

//Busca a palavra na lista localizada no hash da palavra passada como parâmetro. Se encontra, retorna o nó dessa palavra,
//contendo a próprio palavra e sua frequência, e coloca a palavra encontradano início da lista - por conta do MTF.
//Se não encontra, retorna NULL.
Node_hash_encadeamento* hash_encadeamento_MTF_get(Node_hash_encadeamento** vetor, char* palavra) {
    int hash = hash_function(palavra);
    
    Node_hash_encadeamento* aux = vetor[hash];
    Node_hash_encadeamento* anterior = NULL;
    while(aux != NULL && strcmp(palavra, aux->palavra) != 0) {
        anterior = aux;
        aux = aux->prox;
    }

    if(aux == NULL)
        return NULL;
    
    else {

        if(anterior != NULL) {
            anterior->prox = aux->prox;
            aux->prox = vetor[hash];
            vetor[hash] = aux;
        }

        return aux;
    }

}

//Adiciona palavra na estrutura. Busca o hash da palavra e checa se existe espaço vazio ou se existe alguma lista naquela
//posição do vetor. Caso o espaço esteja vazio, cria uma nova lista com um único nó e frequência de palavra 1. Caso haja
//uma lista naquela posição, procura pela palavra na lista, se encontra aumenta a frequência, se não encontra cria um novo
//nó no início da lista - por conta do MTF.
Node_hash_encadeamento** hash_encadeamento_MTF_put(Node_hash_encadeamento** vetor, char* palavra) {
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
            novo->prox = vetor[hash];
            vetor[hash] = novo;

            colisao++;
        }

        n++;
        if(n >= 10*tam) {
            indice_prime++;
            vetor = resize(vetor, primes[indice_prime]);
            tam = primes[indice_prime];
        }
    }

    else {
        auxiliar->frequencia++;
        
        if(anterior != NULL) {
            anterior->prox = auxiliar->prox;
            auxiliar->prox = vetor[hash];
            vetor[hash] = auxiliar;
        }
    }

    return vetor;

}

//Imprime todas as palavras na estrutura em ordem alfabética com suas respectivas frequências.
void hash_encadeamento_MTF_imprime(Node_hash_encadeamento** vetor) {
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

//Imprime o número de chaves na estrutura.
void hash_encadeamento_MTF_imprime_chaves() {
    printf("Número de chaves no vetor com hashing encadeamento com MTF: %d\n", n);
    printf("Número de colisões no vetor com hashing encadeamento com MTF: %d\n", colisao);
}

//Libera a estrutura.
void hash_encadeamento_MTF_free(Node_hash_encadeamento** vetor) {
    for(int i = 0; i < tam; i++) {
        Node_hash_encadeamento* aux = vetor[i];
        Node_hash_encadeamento* proximo = NULL;
        
        while(aux != NULL) {
            proximo = aux->prox;
            free(aux);
            aux = proximo;
        }
    }
    free(vetor);
}