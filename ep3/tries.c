/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

tries.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tries.h"

//Declara os parâmetros estáticos da estrutura: o número de palavras (n) e um auxíliar de palavras (palavra_aux[50]).
static int n;
static char palavra_aux[50];

//Inicializa a estrutura com um nó NULL.
Node_trie* trie_init() {
    Node_trie* first = NULL;
    n = 0;

    return first;
}

//Percorre a estrutura em busca da palavra passada como parâmetro. Assim como na inserção, a busca é feita letra a letra
//e segue a mesma lógica de caminho esquerdo direito ou do meio: se a letra é menor do que a letra atual da estrutura,
//a função segue para o nó esquerdo, se é maior, segue para o nó direito, se é igual, checa se a palavra acabou e, caso
//não tenha terminado, segue para o meio. Se a função encontrar um nó NULL antes da palavra ter sido terminada, a função
//retorna NULL e a palavra não foi encontrada. Caso a palavra termine antes de encontrar um nó NULL, o último nó econtrado
//tem sua frequência checada. Se a frequência desse nó for 0, a palavra não fora encontrada e a função retorna NULL. Caso
//seja diferente de zero a palavra fora encontrada e o nó é retornado com a devida frequência da palavra e a última letra
//da mesma.
Node_trie* trie_get(Node_trie* raiz, char* palavra, int iterador, int tamanho) {
    if(raiz == NULL)
        return NULL;
    if(raiz->palavra < palavra[iterador])
        return trie_get(raiz->dir, palavra, iterador, tamanho);
    else if(raiz->palavra > palavra[iterador])
        return trie_get(raiz->esq, palavra, iterador, tamanho);
    else {
        iterador++;
        if(iterador == tamanho) {
            if(raiz->frequencia > 0)
                return raiz;
            return NULL;
        }
        return trie_get(raiz->meio, palavra, iterador, tamanho);
    }


}

//Adiciona a palavra passada como parâmetro na estrutura. Para isso, a função itera por cada letra da palavra através do
//índice dado por iterador e checa se a letra é maior, menor ou igual a letra atual em que a função se encontra - maior
//ou menor é dado de maneira alfabética. Caso seja menor, a função caminha para o nó esquerdo da letra, repetindo o mesmo
//processo. Caso seja maior, a função faz a mesma coisa, só que agora para o nó direito. Caso seja igual, a função entende
//que a letra fora encontrada e checa se está no fim da palavra (iterador == tamanho). Se sim, a frequência da palavra é
//aumentada, se não, continua a percorrer a palavra agora para o nó do meio. Toda vez que um nó NULL é alcançado, seja ele
//fruto de nó esquerdo, direito ou do meio, e a palavra ainda não foi terminada, um novo nó é criado para a letra em
//questão.
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

//Imprime todas as palavras na estrutura em ordem alfabética com suas respectivas frequências.
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

//Imprime o número de chaves na estrutura.
void trie_imprime_chaves() {
    printf("Número de chaves na tries: %d\n", n);
}

//Libera a estrutura.
Node_trie* trie_free(Node_trie* raiz) {
    if(raiz == NULL)
        return NULL;
    raiz->esq = trie_free(raiz->esq);
    raiz->meio = trie_free(raiz->meio);
    raiz->dir = trie_free(raiz->dir);
    
    free(raiz);

    return NULL;
}