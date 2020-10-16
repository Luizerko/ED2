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

fila_ei.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "fila_ei.h"
#include "processo.h"
#include "fila.h"

/* Inicializa a fila que serve para espera (e) e para impressão (i). Retorna ponteiro para essa fila para que se possa "instanciá-la".
A fila é circular, duplamente ligada e com cabeça de fila. fila_aux->first é sua cabeça e, por padrão, proximo e anterior
de fila_aux->first são NULL quando a fila está vazia.*/
Fila* fila_ei_init() {
    Fila* fila_aux = malloc(sizeof(Fila));
    fila_aux->first = malloc(sizeof(Processo));
    fila_aux->first->proximo = NULL;
    fila_aux->first->anterior = NULL;
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
    return fila_aux->first->proximo;
}

/* Insere um processo no final da fila passada como parâmetro. Casos especiais: fila vazia e fila com um elemento ou mais. */
void fila_ei_entra(Fila* fila_aux, Processo* processo) {
    if(fila_ei_vazia(fila_aux)) {
        fila_aux->first->proximo = processo;
        fila_aux->first->anterior = processo;
        processo->proximo = fila_aux->first;
        processo->anterior = fila_aux->first;
        fila_aux->n++;
    }
    else {
        processo->proximo = fila_aux->first;
        processo->anterior = fila_aux->first->anterior;
        fila_aux->first->anterior->proximo = processo;
        fila_aux->first->anterior = processo;
        fila_aux->n++;
    }
}

/* Retira o elemento indexado por iterador da fila passada como parâmetro e retorna-o. Casos especiais: fila vazia, fila com indexação maior que
seu tamanho, fila com um elemento e fila com dois elementos ou mais. */
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
        auxiliar = fila_aux->first->proximo;

        fila_aux->first->proximo = NULL;
        fila_aux->first->anterior = NULL;
        
        fila_aux->n--;
        return auxiliar;
    }
    else {
        Processo *auxiliar;
        auxiliar = fila_aux->first->proximo;
        while(iterador > 1) {
            auxiliar = auxiliar->proximo;
            iterador--;
        }

        if(auxiliar == fila_aux->first->proximo) {
            fila_aux->first->proximo = auxiliar->proximo;
            auxiliar->proximo->anterior = fila_aux->first;
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

/* Itera sobre a fila passada como parâmetro. A variável espera escolhe se a função vai fazer iteração do tipo fila de espera
ou se a iteração será do tipo fila de impressão. Essa função retorna os três primeiros processos dessa fila, aqueles que
estão sendo processados, caso a opção de impressão seja escolhida. Caso a opção de espera seja escolhida, nada é feito. */
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
        
        Processo* auxiliar = fila_aux->first->proximo;

        auxiliar->li -= 2;
        vetor_impressoras[0] = auxiliar;
        auxiliar = auxiliar->proximo;

        while(auxiliar != NULL && auxiliar != fila_aux->first) {
            if(contador > 0) {
                auxiliar->li -= 2;
                vetor_impressoras[3-contador] = auxiliar;
                contador--;
            }
            auxiliar = auxiliar->proximo;
        }

        return vetor_impressoras;
    }
    return;
}

/* Retorna o tamanho atual da fila passada como parâmetro */
int fila_ei_tamanho(Fila* fila_aux) {
    return fila_aux->n;
}

/* Imprime toda a fila passada como parâmetro. */
void fila_ei_imprime(Fila* fila_aux, int espera) {
    if(fila_ei_vazia(fila_aux)) {
        printf("\nErro! A fila está vazia, não se pode imprimir!\n");
    }
    else {
        Processo* auxiliar = fila_aux->first->proximo;
        long int contador = 1;

        if(espera == 0)
            printf("\n---------- Iterando sobre a fila de impressão: ----------");
        else if(espera == 1)
            printf("\n---------- Iterando sobre a fila de espera: ----------");

        printf("\nProcesso%ld: \n", contador);
        if(espera == 1)
            printf("    prioridade -> %d\n", auxiliar->prioridade);
        printf("    unidades de tempo -> %d\n", auxiliar->ut);
        printf("    linhas de impressão -> %d\n", auxiliar->li);
        auxiliar = auxiliar->proximo;
        contador++;

        while(auxiliar != NULL && auxiliar != fila_aux->first) {
            printf("\nProcesso%ld: \n", contador);
            if(espera == 1)
                printf("    prioridade -> %d\n", auxiliar->prioridade);
            printf("    unidades de tempo -> %d\n", auxiliar->ut);
            printf("    linhas de impressão -> %d\n", auxiliar->li);
            auxiliar = auxiliar->proximo;
            contador++;
        }
        printf("\n----------------------------------------------------\n");
    }
}

/* Para o caso em que um elemento foi removido por prioridade e não por tempo, essa função é chamada para manter atualizado
o tamanho da fila e, caso a fila torne-se vazia, atualizar os ponteiros da cabeça para o padrao NULL de próximo e anterior.*/
void fila_ei_remove_externo(Fila* fila_aux) {
    fila_aux->n--;
    if(fila_aux->first->proximo == fila_aux->first) {
        fila_aux->first->proximo = NULL;
        fila_aux->first->anterior = NULL;
    }
}

/* Libera a memória de todos os nós da fila passada como parâmetro. */
void fila_ei_free(Fila* fila_aux) {
    Processo* auxiliar = fila_aux->first;
    while(fila_ei_tamanho(fila_aux) >= 0) {
        fila_aux->first = fila_aux->first->proximo;
        free(auxiliar);
        auxiliar = fila_aux->first;
        fila_aux->n--;
    }
    free(fila_aux);
}