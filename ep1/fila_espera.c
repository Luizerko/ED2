#include <stdio.h>
#include <stdlib.h>
#include "fila_espera.h"
#include "processo.h"

static Processo* first;
static Processo* last;
static int n;

void fila_espera_init() {
    first = NULL;
    last = NULL;
    n = 0;
}

int fila_espera_vazia() {
    if(n == 0)
        return 1;
    return 0;
}

Processo* fila_espera_primeiro() {
    if(fila_espera_vazia()) {
        printf("Erro! A fila está vazia, não há primeiro!\n");
        return NULL;
    }
    return first;
}

void fila_espera_entra(Processo* processo) {
    if(fila_espera_vazia()) {
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

Processo* fila_espera_sai() {
    if(fila_espera_vazia()) {
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

void fila_espera_itera() {
    if(fila_espera_vazia()) {
        printf("Erro! A fila está vazia, não se pode iterar!\n");
        return NULL;
    }
    else {
        Processo* auxiliar = first;
        auxiliar->permanencia_espera++;
        auxiliar->permanencia_total++;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != first) {
            auxiliar->permanencia_espera++;
            auxiliar->permanencia_total++;
            auxiliar = auxiliar->proximo;
        }
    }
}

int fila_espera_tamanho() {
    return n;
}

void fila_espera_free() {
    Processo* auxiliar = first;
    while(auxiliar != NULL) {
        first = first->proximo;
        free(auxiliar);
        auxiliar = first;
    }
}