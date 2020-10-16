#include <stdio.h>
#include <stdlib.h>
#include "processo.h"
#include "fila_CPU.h"

static Processo* first;
static Processo* last;
static int n;

/* Inicializa a fila de CPU. A fila é circular duplamente ligada e com cabeça. */
void fila_CPU_init() {
    first = malloc(sizeof(Processo));
    last = first;
    first->proximo = NULL;
    first->anterior = NULL;
    n = 0;
}

/* Checa se a fila está vazia. */
int fila_CPU_vazia() {
    if(n == 0)
        return 1;
    return 0;
}

/* Checa se a fila está cheia uma vez que tem limite. */
int fila_CPU_cheia(int max) {
    if(n == max)
        return 1;
    return 0;
}

/* Retorna o primeiro da fila. */
Processo* fila_CPU_primeiro() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não há primeiro!\n");
        return NULL;
    }
    return first->proximo;
}

/* Adiciona um processo ao final da fila. Casos particulares: fila vazia e caso geral quando fila tem um elemento ou mais. */
void fila_CPU_entra(Processo* processo, int max) {
    if(fila_CPU_cheia(max)) {
        printf("Erro! A fila está cheia, não se pode adicionar!\n");
    }
    else if(fila_CPU_vazia()) {
        first->proximo = processo;
        first->anterior = processo;
        processo->proximo = first;
        processo->anterior = first;
        last = processo;
        n++;
    }
    else {
        last->proximo = processo;
        processo->anterior = last;
        last = last->proximo;
        last->proximo = first;
        first->anterior = last;
        n++;
    }
}

/* Retira o primeiro elemento da fila e retorna-o. Casos especiais: fila vazia, fila com um elemento, fila com dois elementos e 
caso comtrês elementos ou mais. */
Processo* fila_CPU_sai() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode remover!\n");
        return NULL;
    }
    else if(n == 1) {
        Processo* auxiliar;
        auxiliar = first->proximo;
        first->proximo = NULL;
        first->anterior = NULL;
        last = first;
        n--;

        return auxiliar;
    }
    else if(n == 2) {
        Processo* auxiliar;
        auxiliar = first->proximo;
        first->proximo = auxiliar->proximo;
        last->anterior = first;
        n--;

        return auxiliar;
    }
    else {
        Processo* auxiliar;
        auxiliar = first->proximo;
        auxiliar->anterior->proximo = auxiliar->proximo;
        auxiliar->proximo->anterior = auxiliar->anterior;
        n--;

        return auxiliar;
    }
}

/* Itera sobre a fila para atualizar os devidos contadores. */
Processo* fila_CPU_itera() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode iterar!\n");
        return NULL;
    }
    else {
        Processo* auxiliar = first->proximo;

        auxiliar->permanencia_CPU++;
        auxiliar->permanencia_total++;
        auxiliar->ut--;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != first) {
            auxiliar->permanencia_CPU++;
            auxiliar->permanencia_total++;
            auxiliar = auxiliar->proximo;
        }

        return first->proximo;
    }
}

/* Passa o primeiro elemento para o final da fila e o segundo elemento da fila torna-se o primeiro. */
void fila_CPU_troca() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode trocar!\n");
    }
    else if(n > 1) {
        Processo* auxiliar = first->proximo;
        auxiliar->anterior->proximo = auxiliar->proximo;
        auxiliar->proximo->anterior = auxiliar->anterior;

        auxiliar->proximo = first;
        first->anterior = auxiliar;
        auxiliar->anterior = last;
        last->proximo = auxiliar;
        last = auxiliar;
    }
}

/* Retorna o tamanho da fila. */
int fila_CPU_tamanho() {
    return n;
}

/* Itera sobre a fila de CPU e imprime todo seu conteúdo. */
void fila_CPU_imprime() {
    if(fila_CPU_vazia()) {
        printf("Erro! A fila está vazia, não se pode imprimir!\n");
    }
    else {
        Processo* auxiliar = first->proximo;
        long int contador = 1;
        printf("\n---------- Iterando sobre a fila da CPU: ----------");
        while(auxiliar != first) {
            printf("\nProcesso%ld: \n", contador);
            printf("    unidades de tempo -> %d\n", auxiliar->ut);
            printf("    linhas de impressão -> %d\n", auxiliar->li);
            auxiliar = auxiliar->proximo;
            contador++;
        }
        printf("--------------------------------------------------\n");
    }
}

/* Itera sobre a fila liberando a memória de seus nós. */
void fila_CPU_free() {
    Processo* auxiliar = first;
    while(fila_CPU_tamanho() > 0) {
        first = first->proximo;
        free(auxiliar);
        auxiliar = first;
        n--;
    }
}