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

/* Função para aumentar ou diminuir o tamanho do vetor do maxheap dependendo do parâmetro novo_tamanho passado. */
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

/* Função para "subir" o elemento em vetor[indice] até a sua devida posição no maxheap. */
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

/* Função para "descer" o elemento da raiz até a sua devida posição no maxheap. */
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

/* Inicializa a fila de prioridade num vetor redimensionável. */
void fila_prioridade_init() {
    vetor = NULL;
    tam = 0;
    fim = 0;
    n = 0;
}

/* Insere no fim da fila de prioridade e depois, caso haja mais de um elemento na fila, "sobe" o elemento respeitando
a propriedade de maxheap. */
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

/* Remove o primeiro elemento da fila de prioridade e depois ajuta o heap passando o último elemento para a raiz da
estrutura e depois o "descendo" respeitando a propriedade de maxheap. */
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

/* Conserta o erro de heap causado pela remoção em tempo e não em prioridade. O processo cuja prioriade fora aumentada
apenas para que possa ser removido normalmente da primeira posição do heap é colocado em seu devido lugar. */
void fila_prioridade_heapifica() {
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
}

/* Retorna 1 se a fila de prioridade está vazia e zero caso não esteja vazia */
bool fila_prioridade_empty() {
    if(n > 0)
        return 0;
    return 1;
}

/* Retorna o tamanho da fila de prioridade. */
int fila_prioridade_size() {
    return n;
}

/* Itera sobre a fila de prioridade e imprime todos os seus processos. */
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

/* Libera o vetor de prioridade, uma vez que a fila de espera já liberou todos os processos em aguardo. */
void fila_prioridade_free() {
    free(vetor);
}