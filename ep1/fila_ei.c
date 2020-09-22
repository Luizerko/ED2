#include <stdio.h>
#include <stdlib.h>
#include "fila_ei.h"
#include "processo.h"
#include "fila.h"

/* Inicializa a fila que serve para espera (e) e para impressão (i). Retorna ponteiro para essa fila para que se possa "instanciá-la".
A fila é circular e duplamente ligada, mas sem cabeça de fila.*/
Fila* fila_ei_init() {
    Fila* fila_aux = malloc(sizeof(Fila));
    fila_aux->first = NULL;
    fila_aux->n = 0;
    return fila_aux;
}

/* Checa se a fila passada como parâmetro está vazia. */
int fila_ei_vazia(Fila* fila_aux) {
    if(fila_aux->n == 0)
        return 1;
    return 0;
}

/* Retorna o primeiro da fila passada como parâmetro. */
Processo* fila_ei_primeiro(Fila* fila_aux) {
    if(fila_ei_vazia(fila_aux)) {
        printf("Erro! A fila está vazia, não há primeiro!\n");
        return NULL;
    }
    return fila_aux->first;
}

/* Insere um processo no final da fila passada como parâmetro. Casos especiais: fila vazia, fila com um elemento e caso com dois elementos
ou mais. */
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

/* Retira o elemento indexado por iterador da fila passada como parâmetro e retorna-o. Casos especiais: fila vazia, fila com indexação maior que
seu tamanho, fila com um elemento, fila com dois elementos e caso com três elementos ou mais. */
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

/* Itera sobre a fila passada como parâmetro para atualizar os devidos contadores. A variável espera escolhe se a função vai fazer iteração
do tipo fila de espera ou se a iteração será do tipo fila de impressão. Essa função retorna os três primeiros processos dessa fila, aqueles que
estão sendo processados. */
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

/* Retorna o tamanho atual da fila passada como parâmetro */
int fila_ei_tamanho(Fila* fila_aux) {
    return fila_aux->n;
}

void fila_ei_imprime(Fila* fila_aux, int espera) {
    if(fila_ei_vazia(fila_aux)) {
        printf("\nErro! A fila está vazia, não se pode imprimir!\n");
    }
    else {
        Processo* auxiliar = fila_aux->first;
        long int contador = 1;

        if(espera == 0)
            printf("\n---------- Iterando sobre a fila de impressão: ----------");
        else if(espera == 1)
            printf("\n---------- Iterando sobre a fila de espera: ----------");

        printf("\nProcesso%ld: \n", contador);
        printf("    unidades de tempo -> %d\n", auxiliar->ut);
        printf("    linhas de impressão -> %d\n", auxiliar->li);
        auxiliar = auxiliar->proximo;
        contador++;

        while(auxiliar != NULL && auxiliar != fila_aux->first) {
            printf("\nProcesso%ld: \n", contador);
            printf("    unidades de tempo -> %d\n", auxiliar->ut);
            printf("    linhas de impressão -> %d\n", auxiliar->li);
            auxiliar = auxiliar->proximo;
            contador++;
        }
        printf("\n----------------------------------------------------\n");
    }
}

/* Libera a memória de todos os nós da fila passada como parâmetro. */
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