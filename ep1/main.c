#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processo.h"
#include "fila_CPU.h"
#include "fila_espera.h"
#include "fila_impressora.h"

int main() {
    int duracao=-1, saida=0;
    while(duracao < 0) {
        printf("Digite a duração do programa em UT: ");
        scanf("%d", &duracao);
    }
    while(saida != 1 && saida != 2) {
        printf("Escolha agora entre uma saída simplificada (1) ou completa (2): ");
        scanf("%d", &saida);
    }

    int total_processos = 0;
    int conta_tempo = 0;
    srand(1);

    int max_CPU = 10;
    fila_CPU_init();

    int i = 0;
    for(i = 0; i < duracao; i++) {
        if(rand()%10 != 0) {

            Processo *novo_processo = malloc(sizeof(Processo));
            novo_processo->ut = rand()%60 + 1;
            novo_processo->li = rand()%501;
            novo_processo->ut_inicial = novo_processo->ut;
            novo_processo->li_inicial = novo_processo->li;
            novo_processo->permanencia_total = 0;
            novo_processo->permanencia_espera = 0;
            novo_processo->permanencia_CPU = 0;
            novo_processo->permanencia_impressao = 0;
            novo_processo->proximo = NULL;
            novo_processo->anterior = NULL;
            
            /*
            printf("\nNovo processo chegou!\n");
            printf("Unidades de tempo para processá-lo: %d\n", novo_processo->ut);
            printf("Linhas a serem impressas para o processo: %d\n", novo_processo->li);
            */

            if(!fila_CPU_cheia(max_CPU)) {
                fila_CPU_entra(novo_processo, max_CPU);
            }
            else {
                fila_espera_entra(novo_processo);
            }

        }

        if(!fila_impressora_vazia()) {
            Processo** auxiliar_impressora = fila_impressora_itera();
            Processo** auxiliar_impressora_2 = malloc(3*sizeof(Processo*));
            int iterador = 0;

            if(auxiliar_impressora != NULL) {
                if(fila_impressora_tamanho() == 1) {
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(1);
                        iterador++;
                        total_processos++;
                    }
                }
                else if(fila_impressora_tamanho() == 2) {
                    int sai_1 = 0;
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(1);
                        iterador++;
                        total_processos++;
                        sai_1 = 1;
                    }

                    if(auxiliar_impressora[1]->li <= 0 && sai_1) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(1);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[1]->li <= 0 && !sai_1) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(2);
                        iterador++;
                        total_processos++;
                    }
                }
                else if(fila_impressora_tamanho() >= 3) {
                    int sai_1 = 0, sai_2 = 0;
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(1);
                        iterador++;
                        total_processos++;
                        sai_1 = 1;
                    }

                    if(auxiliar_impressora[1]->li <= 0 && sai_1) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(1);
                        iterador++;
                        total_processos++;
                        sai_2 = 1;
                    }
                    else if(auxiliar_impressora[1]->li <= 0 && !sai_1) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(2);
                        iterador++;
                        total_processos++;
                        sai_2 = 1;
                    }

                    if(auxiliar_impressora[2]->li <= 0 && sai_1 && sai_2) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(1);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && sai_1 && !sai_2) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(2);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && !sai_1 && sai_2) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(2);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && !sai_1 && !sai_2) {
                        auxiliar_impressora_2[iterador] = fila_impressora_sai(3);
                        iterador++;
                        total_processos++;
                    }
                }
            }
            int j;
            for(j = 0; j < iterador; j++) {
                printf("\n---------- Processo terminado - com impressão ----------\n");
                printf("Dados iniciais: \n");
                printf("        Tempo de processamento: %d\n", auxiliar_impressora_2[j]->ut_inicial);
                printf("        Número de linhas: %d\n", auxiliar_impressora_2[j]->li_inicial);
                printf("Tempo de permanência no sistema: %d\n", auxiliar_impressora_2[j]->permanencia_total);
                printf("Tempo na fila de espera: %d\n", auxiliar_impressora_2[j]->permanencia_espera);
                printf("Tempo na fila da CPU: %d\n", auxiliar_impressora_2[j]->permanencia_CPU);
                printf("Tempo na fila de impressão: %d\n", auxiliar_impressora_2[j]->permanencia_impressao);
                printf("Razão entre tempo de processamento e o tempo total: %.4f\n",
                    (float)auxiliar_impressora_2[j]->ut_inicial/(float)auxiliar_impressora_2[j]->permanencia_total);
            }
        }
        
        if(!fila_espera_vazia()) fila_espera_itera();
        Processo* auxiliar_espera;

        if(!fila_CPU_vazia()) {
            Processo* auxiliar_CPU = fila_CPU_itera();

            if(auxiliar_CPU->ut == 0 || conta_tempo == 20) {
                conta_tempo = -1;
                if(auxiliar_CPU->ut == 0) {
                    auxiliar_CPU = fila_CPU_sai();
                    if(!fila_espera_vazia()) {
                        auxiliar_espera = fila_espera_sai();
                        fila_CPU_entra(auxiliar_espera, max_CPU);
                    }
                    if(auxiliar_CPU->li > 0) {
                        fila_impressora_entra(auxiliar_CPU);
                    }
                    else {
                        printf("\n---------- Processo terminado - sem impressão ----------\n");
                        printf("Dados iniciais: \n");
                        printf("        Tempo de processamento: %d\n", auxiliar_CPU->ut_inicial);
                        printf("        Número de linhas: %d\n", auxiliar_CPU->li_inicial);
                        printf("Tempo de permanência no sistema: %d\n", auxiliar_CPU->permanencia_total);
                        printf("Tempo na fila de espera: %d\n", auxiliar_CPU->permanencia_espera);
                        printf("Tempo na fila da CPU: %d\n", auxiliar_CPU->permanencia_CPU);
                        printf("Tempo na fila de impressão: %d\n", auxiliar_CPU->permanencia_impressao);
                        printf("Razão entre tempo de processamento e o tempo total: %.4f\n",
                            (float)auxiliar_CPU->ut_inicial/(float)auxiliar_CPU->permanencia_total);
                        total_processos++;
                    }
                }
                else {
                    fila_CPU_troca();
                }
            }
        }

        conta_tempo++;
    }

    printf("\n---------- Informações finais ----------\n");
    printf("Tamanho da fila de espera: %d\n", fila_espera_tamanho());
    printf("Tamanho da fila da CPU: %d\n", fila_CPU_tamanho());
    printf("Tamanho da fila de impressão: %d\n", fila_impressora_tamanho());
    printf("Número total de processos computados: %d\n", total_processos);

    return 0;
}