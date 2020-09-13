#include <stdio.h>
#include <stdlib.h>
#include "fila_ei.h"
#include "processo.h"
#include "fila.h"

Fila* fila_ei_init() {
    Fila* fila_aux = malloc(sizeof(Fila));
    fila_aux->first = NULL;
    fila_aux->n = 0;
    return fila_aux;
}

int fila_ei_vazia(Fila* fila_aux) {
    if(fila_aux->n == 0)
        return 1;
    return 0;
}

Processo* fila_ei_primeiro(Fila* fila_aux) {
    if(fila_ei_vazia(fila_aux)) {
        printf("Erro! A fila está vazia, não há primeiro!\n");
        return NULL;
    }
    return fila_aux->first;
}

void fila_ei_entra(Fila* fila_aux, Processo* processo) {
    if(fila_ei_vazia(fila_aux)) {
        fila_aux->first = processo;
        fila_aux->first->proximo = NULL;
        fila_aux->first->anterior = NULL;
        fila_aux->n++;
    }
    else if(fila_aux->n == 1) {
        fila_aux->first->proximo = processo;
        processo->proximo = fila_aux->first;
        processo->anterior = fila_aux->first;
        fila_aux->first->anterior = processo;
        fila_aux->n++;
    }
    else {
        fila_aux->first->anterior->proximo = processo;
        processo->anterior = fila_aux->first->anterior;
        processo->proximo = fila_aux->first;
        fila_aux->first->anterior = processo;
        fila_aux->n++;
    }
}

Processo* fila_ei_sai(Fila* fila_aux, int iterador) {
    if(fila_ei_vazia(fila_aux)) {
        printf("Erro! A fila está vazia, não se pode remover!\n");
        return NULL;
    }
    else if(iterador > fila_aux->n) {
        printf("Erro! Tentando remover um objeto que não está na lista!\n");
        return NULL;
    }
    else if(fila_aux->n == 1) {
        Processo* auxiliar;
        auxiliar = fila_aux->first;

        fila_aux->first = NULL;
        
        fila_aux->n--;
        return auxiliar;
    }
    else if(fila_aux->n == 2) {
        Processo *auxiliar;
        auxiliar = fila_aux->first;
        while(iterador > 1) {
            auxiliar = auxiliar->proximo;
            iterador--;
        }

        if(auxiliar == fila_aux->first) {
            fila_aux->first = fila_aux->first->proximo;
            fila_aux->first->anterior = NULL;
            fila_aux->first->proximo = NULL;
        }

        else {
            fila_aux->first->proximo = NULL;
            fila_aux->first->anterior = NULL;
        }

        fila_aux->n--;
        return auxiliar;
    }
    else {
        Processo *auxiliar;
        auxiliar = fila_aux->first;
        while(iterador > 1) {
            auxiliar = auxiliar->proximo;
            iterador--;
        }

        if(auxiliar == fila_aux->first) {
            fila_aux->first->anterior->proximo = fila_aux->first->proximo;
            fila_aux->first->proximo->anterior = fila_aux->first->anterior;
            fila_aux->first = fila_aux->first->proximo;
        }
            

        else if(auxiliar == fila_aux->first->anterior) {
            fila_aux->first->anterior = auxiliar->anterior;
            auxiliar->anterior->proximo = fila_aux->first;
        }

        else {
            auxiliar->anterior->proximo = auxiliar->proximo;
            auxiliar->proximo->anterior = auxiliar->anterior;
        }

        fila_aux->n--;
        return auxiliar;
    }
}

Processo** fila_ei_itera(Fila* fila_aux, int espera) {
    if(fila_ei_vazia(fila_aux)) {
        printf("Erro! A fila está vazia, não se pode iterar!\n");
        return NULL;
    }
    else if(espera == 0) {
        int contador = 2;
        Processo** vetor_impressoras;
        if(fila_aux->n == 1)
            vetor_impressoras = malloc(sizeof(Processo*));
        else if(fila_aux->n == 2)
            vetor_impressoras = malloc(2*sizeof(Processo*));
        else
            vetor_impressoras = malloc(3*sizeof(Processo*));
        
        Processo* auxiliar = fila_aux->first;

        auxiliar->permanencia_impressao++;
        auxiliar->permanencia_total++;
        auxiliar->li -= 10;
        vetor_impressoras[0] = auxiliar;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != fila_aux->first) {
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
    else if(espera == 1){
        Processo* auxiliar = fila_aux->first;
        auxiliar->permanencia_espera++;
        auxiliar->permanencia_total++;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != fila_aux->first) {
            auxiliar->permanencia_espera++;
            auxiliar->permanencia_total++;
            auxiliar = auxiliar->proximo;
        }

        return;
    }
}

int fila_ei_tamanho(Fila* fila_aux) {
    return fila_aux->n;
}

void fila_ei_free(Fila* fila_aux) {
    Processo* auxiliar = fila_aux->first;
    while(fila_ei_tamanho(fila_aux) > 0) {
        fila_aux->first = fila_aux->first->proximo;
        free(auxiliar);
        auxiliar = fila_aux->first;
        fila_aux->n--;
    }
    free(fila_aux);
}