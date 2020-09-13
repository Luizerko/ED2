#include <stdio.h>
#include <stdlib.h>
#include "processo.h"
#include "fila_CPU.h"

static Processo* first;
static Processo* last;
static int n;

void fila_CPU_init() {
    first = NULL;
    last = NULL;
    n = 0;
}

int fila_CPU_vazia() {
    if(n == 0)
        return 1;
    return 0;
}

int fila_CPU_cheia(int max) {
    if(n == max)
        return 1;
    return 0;
}

Processo* fila_CPU_primeiro() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não há primeiro!\n");
        return NULL;
    }
    return first;
}

void fila_CPU_entra(Processo* processo, int max) {
    if(fila_CPU_cheia(max)) {
        printf("Erro! A fila está cheia, não se pode adicionar!\n");
    }
    else if(fila_CPU_vazia()) {
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

Processo* fila_CPU_sai() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode remover!\n");
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
    else if(n == 2) {
        Processo* auxiliar;
        auxiliar = first;
        auxiliar->anterior->proximo = NULL;
        auxiliar->proximo->anterior = NULL;
        first = first->proximo;
        n--;

        return auxiliar;
    }
    else {
        Processo* auxiliar;
        auxiliar = first;
        auxiliar->anterior->proximo = first->proximo;
        auxiliar->proximo->anterior = first->anterior;
        first = first->proximo;
        n--;

        return auxiliar;
    }
}

Processo* fila_CPU_itera() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode iterar!\n");
        return NULL;
    }
    else {
        Processo* auxiliar = first;

        auxiliar->permanencia_CPU++;
        auxiliar->permanencia_total++;
        auxiliar->ut--;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != first) {
            auxiliar->permanencia_CPU++;
            auxiliar->permanencia_total++;
            auxiliar = auxiliar->proximo;
        }

        return first;
    }
}

void fila_CPU_troca() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode trocar!\n");
    }
    else if(n > 1) {
        last = first;
        first = first->proximo;
    }
}

int fila_CPU_tamanho() {
    return n;
}

void fila_CPU_free() {
    Processo* auxiliar = first;
    while(fila_CPU_tamanho() > 0) {
        first = first->proximo;
        free(auxiliar);
        auxiliar = first;
        n--;
    }
}