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
static int ini;
static int fim;
static int n;

static void resize(int novo_tamanho) {
    Processo** auxiliar = malloc((novo_tamanho+1)*sizeof(Processo*));
    int iterador = 1;
    if(n == tam) {
        while(iterador <= tam) {
            auxiliar[iterador] = vetor[ini];
            iterador++;
            ini = (ini + 1)%(tam+1);
            if(ini == 0)
                ini++;
        }
        ini = 1;
        fim = n+1;
        tam = novo_tamanho;
        free(vetor);
        vetor = auxiliar;
    }
    else {
        while(ini != fim) {
            auxiliar[iterador] = vetor[ini];
            iterador++;
            ini = (ini + 1)%(tam+1);
            if(ini == 0)
                ini++;
        }
        ini = 1;
        fim = n+1;
        tam = novo_tamanho;
        free(vetor);
        vetor = auxiliar;
    }
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
    ini = 0;
    fim = 0;
    n = 0;
}

void fila_prioridade_insert(Processo* processo) {
    if(tam == 0) {
        vetor = malloc(sizeof(Processo*));
        tam = 1;
        n = 1;
        vetor[fim] = processo;
        fim = (fim+1)%(tam+1);
        if(fim == 0)
            fim++;
    }
    else {
        if(!fila_prioridade_empty() && fim == ini)
            resize(2*tam);
        vetor[fim] = processo;
        swim(fim);
        fim = (fim+1)%(tam+1);
        if(fim == 0)
            fim++;
        n++;
    }
}

Processo* fila_prioridade_remove() {
    if(!fila_prioridade_empty()) {
        if(n <= tam/4)
            resize(tam/2);
        n--;
        Processo* auxiliar = vetor[ini];
        if(fim-1 == 0) {
            vetor[ini] = vetor[(fim-2)%(tam+1)];
            fim = (fim-2)%(tam+1);
        }
        else {
            vetor[ini] = vetor[(fim-1)];
            fim--;
        }
        sink(fim);
        return auxiliar;
    }
}

bool fila_prioridade_empty() {
    if(n > 0)
        return 0;
    return 1;
}

int fila_prioridade_size() {
    return n;
}

void fila_prioridade_free() {

    int i = 0;
    for(i = ini; i < fim; i = (i+1)%(tam+1)) {
        if(i == 0)
            i++;
        free(vetor[i]);
    }

    free(vetor);
}