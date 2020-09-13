/*
Exercício 1
Disciplina: Algoritmos e Estruturas de Dados II (MAC-0323)
Nome: Luis Vitor Pedreira Iten Zerkowski
NUSP: 9837201
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static Item* vetor;
static int tam;
static int ini;
static int fim;
static int n;

static void resize(int novo_tamanho) {
    Item* auxiliar = malloc(novo_tamanho*sizeof(Item));
    int iterador = 0;
    if(n == tam) {
        while(iterador < tam) {
            auxiliar[iterador] = vetor[ini];
            iterador++;
            ini = (ini + 1)%tam;
        }
        ini = 0;
        fim = n;
        tam = novo_tamanho;
        free(vetor);
        vetor = auxiliar;
    }
    else {
        while(ini != fim) {
            auxiliar[iterador] = vetor[ini];
            iterador++;
            ini = (ini + 1)%tam;
        }
        ini = 0;
        fim = n;
        tam = novo_tamanho;
        free(vetor);
        vetor = auxiliar;
    }
}

void queueInit() {
    vetor = NULL;
    tam = 0;
    ini = 0;
    fim = 0;
    n = 0;
}

void queueInsert(Item item) {
    if(tam == 0) {
        vetor = malloc(sizeof(Item));
        tam = 1;
        n = 1;
        vetor[fim] = item;
        fim = (fim+1)%tam;
    }
    else {
        if(!queueEmpty() && fim == ini)
            resize(2*tam);
        vetor[fim] = item;
        fim = (fim+1)%tam;
        n++;
    }
}

Item queueRemove() {
    if(!queueEmpty()) {
        if(n <= tam/4)
            resize(tam/2);
        n--;
        Item auxiliar = vetor[ini];
        ini = (ini+1)%tam;
        return auxiliar;
    }
}

bool queueEmpty() {
    if(n > 0)
        return 0;
    return 1;
}

int queueSize() {
    return n;
}

void queueFree() {
    /*

    Não usamos esse laço aqui por conta do Item utilizado com inteiros

    for(int i = ini; i < fim; i++) {
        free(vetor[i]);
    }
    */
    free(vetor);
}

/* Teste de fila redimensionável em vetor circular*/

int main() {

    queueInit();

    for(int i = 0; i < 100000000; i++) {
        queueInsert(i);
    }
    for(int i = 0; i < 90000000; i++) {
        queueRemove();
    }
    for(int i = 0; i < 50000000; i++) {
        queueInsert(i);
    }

    queueFree();

    return 0;
}