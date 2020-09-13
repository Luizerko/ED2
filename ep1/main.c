/*
Exercício Programa 1
Disciplina: Algoritmos e Estruturas de Dados II (MAC-0323)
Nome: Luis Vitor Pedreira Iten Zerkowski
NUSP: 9837201
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processo.h"
#include "fila.h"
#include "fila_CPU.h"
#include "fila_ei.h"

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
    int permanencia_total = 0;
    int permanencia_espera = 0;
    int permanencia_CPU = 0;
    int permanencia_impressao = 0;
    float soma_razao = 0;
    int conta_tempo = 0;
    srand(1);

    int max_CPU = 10;
    fila_CPU_init();
    Fila* f_espera = fila_ei_init();
    Fila* f_impressora = fila_ei_init();

    int i = 0;
    for(i = 0; i < duracao; i++) {
        if(rand()%100 < 6) {

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
            
            printf("\n---------- Novo processo chegou ----------\n");
            printf("Unidades de tempo para processá-lo: %d\n", novo_processo->ut);
            printf("Linhas a serem impressas para o processo: %d\n", novo_processo->li);

            if(!fila_CPU_cheia(max_CPU)) {
                fila_CPU_entra(novo_processo, max_CPU);
            }
            else {
                fila_ei_entra(f_espera, novo_processo);
            }

        }

        if(!fila_ei_vazia(f_impressora)) {
            Processo** auxiliar_impressora = fila_ei_itera(f_impressora, 0);
            Processo** auxiliar_impressora_2 = malloc(3*sizeof(Processo*));
            int iterador = 0;

            if(auxiliar_impressora != NULL) {
                if(fila_ei_tamanho(f_impressora) == 1) {
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        total_processos++;
                    }
                }
                else if(fila_ei_tamanho(f_impressora) == 2) {
                    int sai_1 = 0;
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        total_processos++;
                        sai_1 = 1;
                    }

                    if(auxiliar_impressora[1]->li <= 0 && sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[1]->li <= 0 && !sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        total_processos++;
                    }
                }
                else if(fila_ei_tamanho(f_impressora) >= 3) {
                    int sai_1 = 0, sai_2 = 0;
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        total_processos++;
                        sai_1 = 1;
                    }

                    if(auxiliar_impressora[1]->li <= 0 && sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        total_processos++;
                        sai_2 = 1;
                    }
                    else if(auxiliar_impressora[1]->li <= 0 && !sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        total_processos++;
                        sai_2 = 1;
                    }

                    if(auxiliar_impressora[2]->li <= 0 && sai_1 && sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && sai_1 && !sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && !sai_1 && sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && !sai_1 && !sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 3);
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

                permanencia_total += auxiliar_impressora_2[j]->permanencia_total;
                permanencia_espera += auxiliar_impressora_2[j]->permanencia_espera;
                permanencia_CPU += auxiliar_impressora_2[j]->permanencia_CPU;
                permanencia_impressao += auxiliar_impressora_2[j]->permanencia_impressao;
                soma_razao += (float)auxiliar_impressora_2[j]->ut_inicial/(float)auxiliar_impressora_2[j]->permanencia_total;
            
                free(auxiliar_impressora_2[j]);
            }

            free(auxiliar_impressora_2);
        }
        
        if(!fila_ei_vazia(f_espera)) fila_ei_itera(f_espera, 1);
        Processo* auxiliar_espera;

        if(!fila_CPU_vazia()) {
            Processo* auxiliar_CPU = fila_CPU_itera();

            if(auxiliar_CPU->ut == 0 || conta_tempo == 20) {
                conta_tempo = -1;
                if(auxiliar_CPU->ut == 0) {
                    auxiliar_CPU = fila_CPU_sai();
                    if(!fila_ei_vazia(f_espera)) {
                        auxiliar_espera = fila_ei_sai(f_espera, 1);
                        fila_CPU_entra(auxiliar_espera, max_CPU);
                    }
                    if(auxiliar_CPU->li > 0) {
                        fila_ei_entra(f_impressora, auxiliar_CPU);
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

                        permanencia_total += auxiliar_CPU->permanencia_total;
                        permanencia_espera += auxiliar_CPU->permanencia_espera;
                        permanencia_CPU += auxiliar_CPU->permanencia_CPU;
                        soma_razao += (float)auxiliar_CPU->ut_inicial/(float)auxiliar_CPU->permanencia_total;

                        free(auxiliar_CPU);
                    }
                }
                else {
                    fila_CPU_troca();
                }
            }
        }

        if(saida == 2) {
            printf("\n---------- Estado das filas ----------\n");
            printf("Tamanho da fila de espera: %d\n", fila_ei_tamanho(f_espera));
            printf("Tamanho da fila da CPU: %d\n", fila_CPU_tamanho());
            printf("Tamanho da fila de impressão: %d\n", fila_ei_tamanho(f_impressora));
            printf("Número total de processos computados: %d\n", total_processos);
        }

        conta_tempo++;
    }

    printf("\n---------- Sumário ----------\n");
    printf("Número total de processos computados: %d\n", total_processos);
    printf("Média de permanência total: %.4f\n", (float)permanencia_total/(float)total_processos);
    printf("Média de permanência na espera: %.4f\n", (float)permanencia_espera/(float)total_processos);
    printf("Média de permanência na CPU: %.4f\n", (float)permanencia_CPU/(float)total_processos);
    printf("Média de permanência na impressão: %.4f\n", (float)permanencia_impressao/(float)total_processos);
    printf("Média da razão entre o processamento e a permanência: %.4f\n", soma_razao/(float)total_processos);

    fila_ei_free(f_espera);
    fila_ei_free(f_impressora);
    fila_CPU_free();

    return 0;
}