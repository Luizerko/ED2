#include <stdio.h>
#include <stdlib.h>
#include "fila_impressora.h"
#include "processo.h"

static Processo* first;
static Processo* last;
static int n;

void fila_impressora_init() {
    first = NULL;
    last = NULL;
    n = 0;
}

int fila_impressora_vazia() {
    if(n == 0)
        return 1;
    return 0;
}

Processo* fila_impressora_primeiro() {
    if(fila_impressora_vazia()) {
        printf("Erro! A fila está vazia, não há primeiro!\n");
        return NULL;
    }
    return first;
}

void fila_impressora_entra(Processo* processo) {
    if(fila_impressora_vazia()) {
        first = processo;
        last = processo;
        first->proximo = NULL;
        first->anterior = NULL;
        n++;
    }
    else {
        last->proximo = processo;
        last->proximo->anterior = last;
        last = last->proximo;
        last->proximo = first;
        first->anterior = last;
        n++;
    }
}

Processo* fila_impressora_sai(int iterador) {
    if(fila_impressora_vazia()) {
        printf("Erro! A fila está vazia, não se pode remover!\n");
        return NULL;
    }
    else if(iterador > n) {
        printf("Erro! Tentando remover um objeto que não está na lista!\n");
        return NULL;
    }
    else if(n == 1) {
        Processo* auxiliar;
        auxiliar = first;

        first = NULL;
        last = NULL;
        n--;

        return auxiliar;
    }
    else if(n ==2) {
        Processo* auxiliar;
        auxiliar = first;
        while(iterador > 1) {
            auxiliar = auxiliar->proximo;
            iterador--;
        }

        auxiliar->anterior->proximo = NULL;
        auxiliar->proximo->anterior = NULL;
        if(auxiliar == first)
            first = first->proximo;
        else if(auxiliar == last)
            last = last->anterior;
        n--;

        return auxiliar;        
    }
    else {
        Processo* auxiliar;
        auxiliar = first;
        while(iterador > 1) {
            auxiliar = auxiliar->proximo;
            iterador--;
        }

        auxiliar->anterior->proximo = auxiliar->proximo;
        auxiliar->proximo->anterior = auxiliar->anterior;
        if(auxiliar == first)
            first = first->proximo;
        else if(auxiliar == last)
            last = last->anterior;
        n--;

        return auxiliar;
    }
}

Processo** fila_impressora_itera() {
    if(fila_impressora_vazia()) {
        printf("Erro! A fila está vazia, não se pode iterar!\n");
        return NULL;
    }
    else {
        int contador = 2;
        Processo** vetor_impressoras;
        if(n == 1)
            vetor_impressoras = malloc(sizeof(Processo*));
        else if(n == 2)
            vetor_impressoras = malloc(2*sizeof(Processo*));
        else
            vetor_impressoras = malloc(3*sizeof(Processo*));
        
        Processo* auxiliar = first;

        auxiliar->permanencia_impressao++;
        auxiliar->permanencia_total++;
        auxiliar->li -= 10;
        vetor_impressoras[0] = auxiliar;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != first) {
            if(contador > 0) {
                auxiliar->li -= 10;
                vetor_impressoras[3-contador] = auxiliar;
                contador--;
            }
            auxiliar->permanencia_impressao++;
            auxiliar->permanencia_total++;
            auxiliar = auxiliar->proximo;
        }

        return vetor_impressoras;
    }
}

int fila_impressora_tamanho() {
    return n;
}

void fila_impressora_free() {
    Processo* auxiliar = first;
    while(auxiliar != NULL) {
        first = first->proximo;
        free(auxiliar);
        auxiliar = first;
    }
}