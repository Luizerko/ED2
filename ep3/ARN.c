/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

ARN.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ARN.h"

//Declara os parâmetros estáticos da estrutura: o número de palavras (n) e um nó inicial (first).
static Node_ARN* first;
static int n;

//Checa se um nó é vermelho ou não.
static int is_red(Node_ARN* raiz) {
    if(raiz == NULL)
        return 0;
    return raiz->cor;
}

//Troca a cor da raiz e dos filhos dessa raiz.
static void flip_color(Node_ARN* raiz) {
    raiz->cor = 1 - raiz->cor;
    raiz->dir->cor = 1 - raiz->dir->cor;
    raiz->esq->cor = 1 - raiz->esq->cor;
    
    if(raiz == first)
        raiz->cor = 0;
}

//Roda a subárvore para a esquerda e ajeita as cores para manter a propriedade dos caminhos negros.
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

//Roda a subárvore para a direita e ajeita as cores para manter a propriedade dos caminhos negros.
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

//Checa todos os casos de balanceamento da árvore e faz as devidas rotações e trocas de cores dependendo dos casos
//detectados pelo código.
static Node_ARN* balance(Node_ARN* raiz) {
    if(is_red(raiz->dir) && !is_red(raiz->esq))
        raiz = rotate_left(raiz);
    if(is_red(raiz->esq) && is_red(raiz->esq->esq))
        raiz = rotate_right(raiz);
    if(is_red(raiz->esq) && is_red(raiz->dir))
        flip_color(raiz);
    
    return raiz;
}

//Inicializa a estrutura com um nó NULL.
Node_ARN* ARN_init() {
    first = NULL;
    n = 0;

    return first;
}

//Procura a palavra passada como parâmetro. Para isso, a função caminha para o nó esquerdo se a palavra é menor - sempre
//em termos alfabéticos -, do que a raiz atual da função, ou para o lado direito se a palavra é maior do que a raiz atual
//da função. Se a palavra for encontrada, seu nó é devolvido contendo a própria palavra e sua frequência no texto. Caso
//a função chegue num nó NULL, a palavra não fora encontrada e o próprio NULL é retornado.
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

//Adiciona a palavra passada como parâmetro na estrutura. Para isso, a função itera por cada nó e checa se a palavra desse
//nó é maior, menor ou igual a palavra atual em que a função se encontra - maior ou menor é dado de maneira alfabética. 
//Caso seja menor, a função caminha para o nó esquerdo da palavra, repetindo o mesmo processo. Caso seja maior, a função
//faz a mesma coisa, só que agora para o nó direito. Caso seja igual, a função entende que a palavra fora encontrada e
//simplesmente aumenta a frequência da mesma. Toda vez que um nó NULL é alcançado, seja ele fruto de nó esquerdo ou
//direito, e a palavra ainda não foi encontrada, um novo nó é criado com frequência 1 e já pintado de vermelho. A
//estrutura, então, é rebalanceada através da função balance e depois o devida raiz é devolvida para a chamada anterior da
//função para manter a estrutura de árvore.
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

//Imprime todas as palavras na estrutura em ordem alfabética com suas respectivas frequências.
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

//Imprime o número de chaves na estrutura.
void ARN_imprime_chaves() {
    printf("Número de chaves na ARN: %d\n", n);
}

//Libera a estrutura.
Node_ARN* ARN_free(Node_ARN* raiz) {
    if(raiz == NULL)
        return NULL;
    
    raiz->esq = ARN_free(raiz->esq);
    raiz->dir = ARN_free(raiz->dir);

    free(raiz);

    return NULL;
}