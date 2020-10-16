/*
AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO-PROGRAMA (EP) FORAM 
DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
REPROVAÇÃO DIRETA NA DISCIPLINA.

Nome: Luis Vitor Pedreira Iten Zerkowski
NUSP: 9837201

fila_prioridade.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "fila_prioridade.h"

static Processo** vetor;
static int tam;
static int fim;
static int n;

static void resize(int novo_tamanho) {
    Processo** auxiliar = malloc((novo_tamanho+1)*sizeof(Processo*));
    int iterador = 1;
    if(n == tam) {
        while(iterador <= tam) {
            auxiliar[iterador] = vetor[iterador];
            iterador++;
        }
    }
    else {
        while(iterador <= n) {
            auxiliar[iterador] = vetor[iterador];
            iterador++;
        }
    }
    fim = n+1;
    tam = novo_tamanho;
    free(vetor);
    vetor = auxiliar;
}

static void swim(int indice) {
    int pai = indice/2;
    Processo* auxiliar = vetor[indice];
    while(indice > 1 && vetor[pai]->prioridade < auxiliar->prioridade) {
        vetor[indice] = vetor[pai];
        indice = pai;
        pai = indice/2;
    }
    vetor[indice] = auxiliar;
}

static void sink(int indice) {
    int pai = 1;
    Processo* auxiliar = vetor[pai];
    while(2*pai < indice-1) {
        if(2*pai+1 >= indice-1 || vetor[2*pai]->prioridade >  vetor[2*pai+1]->prioridade) {
            if(vetor[2*pai]->prioridade > auxiliar->prioridade) {
                vetor[pai] = vetor[2*pai];
                pai = 2*pai;
            }
            else
                break;
            
        }
        else {
            if(vetor[2*pai+1]->prioridade > auxiliar->prioridade) {
                vetor[pai] = vetor[2*pai+1];
                pai = 2*pai+1;
            }
            else
                break;
        }
    }
    vetor[pai] = auxiliar;
}

void fila_prioridade_init() {
    vetor = NULL;
    tam = 0;
    fim = 0;
    n = 0;
}

void fila_prioridade_insert(Processo* processo) {
    if(tam == 0) {
        vetor = malloc(sizeof(Processo*));
        tam = 1;
        n = 1;
        fim = 1;
        vetor[fim] = processo;
        fim++;
    }
    else {
        if(fim > tam)
            resize(2*tam);
        vetor[fim] = processo;
        swim(fim);
        fim++;
        n++;
    }
}

Processo* fila_prioridade_remove() {
    if(!fila_prioridade_empty()) {
        if(n <= tam/4)
            resize(tam/2);
        n--;
        Processo* auxiliar = vetor[1];
        fim--;
        vetor[1] = vetor[fim];
        sink(fim);
        return auxiliar;
    }
}

void fila_prioridade_heapifica() {
    printf("\ncomecou\n");
    fila_prioridade_imprime();
    int i;
    for(i = 1; i < fim; i++) {
        if(2*i < fim && vetor[i]->prioridade < vetor[2*i]->prioridade) {
            swim(2*i);
            break;
        }
        else if(2*i+1 < fim && vetor[i]->prioridade < vetor[2*i+1]->prioridade) {
            swim(2*i+1);
            break;
        }
    }
    fila_prioridade_imprime();
    printf("\nterminou\n");
}

bool fila_prioridade_empty() {
    if(n > 0)
        return 0;
    return 1;
}

int fila_prioridade_size() {
    return n;
}

void fila_prioridade_imprime() {
    if(fila_prioridade_empty()) {
        printf("\nErro! A fila está vazia, não se pode imprimir!\n");
    }
    else {
        printf("\n---------- Iterando sobre a fila de espera prioritária: ----------");
        int i;
        int contador = 1;
        for(i = 1; i < fim; i++) {
            printf("\nProcesso%d \n", i);
            printf("    prioridade -> %d\n", vetor[i]->prioridade);
            printf("    unidades de tempo -> %d\n", vetor[i]->ut);
            printf("    linhas de impressão -> %d\n", vetor[i]->li);
        }
    }
}

void fila_prioridade_free() {

    int i;
    for(i = 1; i < fim; i++) {
        free(vetor[i]);
    }

    free(vetor);
}