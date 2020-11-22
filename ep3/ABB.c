/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

ABB.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABB.h"

//Declara os parâmetros estáticos da estrutura: o número de palavras (n).
static int n;

//Inicializa a estrutura com um nó NULL.
Node_ABB* ABB_init() {
    Node_ABB* first = NULL;
    n = 0;

    return first;
}

//Procura a palavra passada como parâmetro. Para isso, a função caminha para o nó esquerdo se a palavra é menor - sempre
//em termos alfabéticos -, do que a raiz atual da função, ou para o lado direito se a palavra é maior do que a raiz atual
//da função. Se a palavra for encontrada, seu nó é devolvido contendo a própria palavra e sua frequência no texto. Caso
//a função chegue num nó NULL, a palavra não fora encontrada e o próprio NULL é retornado.
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

//Adiciona a palavra passada como parâmetro na estrutura. Para isso, a função itera por cada nó e checa se a palavra desse
//nó é maior, menor ou igual a palavra atual em que a função se encontra - maior ou menor é dado de maneira alfabética. 
//Caso seja menor, a função caminha para o nó esquerdo da palavra, repetindo o mesmo processo. Caso seja maior, a função
//faz a mesma coisa, só que agora para o nó direito. Caso seja igual, a função entende que a palavra fora encontrada e
//simplesmente aumenta a frequência da mesma. Toda vez que um nó NULL é alcançado, seja ele fruto de nó esquerdo ou
//direito, e a palavra ainda não foi encontrada, um novo nó é criado com frequência 1 e devolvido para as chamadas
//anteriores, mantendo a estrutura de árvore.
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

//Imprime todas as palavras na estrutura em ordem alfabética com suas respectivas frequências.
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

//Imprime o número de chaves na estrutura.
void ABB_imprime_chaves() {
    printf("Número de chaves na ABB: %d\n", n);
}

//Libera a estrutura.
Node_ABB* ABB_free(Node_ABB* raiz) {
    if(raiz == NULL)
        return NULL;
    
    raiz->esq = ABB_free(raiz->esq);
    raiz->dir = ABB_free(raiz->dir);

    free(raiz);

    return NULL;
}