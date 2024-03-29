/*
Exercício Programa 2
Disciplina: Algoritmos e Estruturas de Dados II (MAC-0323)
Nome: Luis Vitor Pedreira Iten Zerkowski
NUSP: 9837201

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

ep2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processo.h"
#include "fila.h"
#include "fila_CPU.h"
#include "fila_ei.h"
#include "fila_prioridade.h"

int main() {
	/* Pega a entrada do usuário para unidades de tempo do programa e tipo de saída. */
    int duracao=-1, saida=0;
    while(duracao < 0) {
        printf("Digite a duração do programa em UT: ");
        scanf("%d", &duracao);
    }
    while(saida != 1 && saida != 2) {
        printf("Escolha agora entre uma saída simplificada (1) ou completa (2): ");
        scanf("%d", &saida);
    }

    /* Inicialização dos contadores. */
    int total_processos = 0;
    int total_processos_media = 0;
    int permanencia_total = 0;
    int permanencia_espera = 0;
    long int espera_prioridade[10];
    long int numero_prioridade[10];
    int x;
    for(x = 0; x < 10; x++) {
        espera_prioridade[x] = 0;
        numero_prioridade[x] = 0;
    }
    int permanencia_CPU = 0;
    int permanencia_impressao = 0;
    float soma_razao = 0;
    int conta_tempo = 0;
    int flag_tempo_prioridade = 1;
    srand(time(NULL));

    /* Inicialização das filas e limite da fila de CPU. */
    int max_CPU = 10;
    fila_CPU_init();
    Fila* f_espera = fila_ei_init();
    fila_prioridade_init();
    Fila* f_impressora = fila_ei_init();

    /* Laço de unidades de tempo. */
    int i = 0;
    for(i = 0; i < duracao; i++) {
        if(rand()%100 < 5) {

        	/* Inicialização de um novo processo. */
            Processo *novo_processo = malloc(sizeof(Processo));
            novo_processo->ut = rand()%60 + 1;
            novo_processo->li = rand()%501;
            /* Cálculo especial de prioridade para garantir que processos que entraram primeiro na fila sejam retirados
            antes de processos que entraram depois, no caso de processos de mesma prioridade */ 
            novo_processo->prioridade = (rand()%10 + 1)*duracao - i;
            novo_processo->indice_heap = -1;
            novo_processo->ut_inicial = novo_processo->ut;
            novo_processo->li_inicial = novo_processo->li;
            novo_processo->permanencia_total = i;
            novo_processo->permanencia_espera = i;
            novo_processo->permanencia_CPU = i;
            novo_processo->permanencia_impressao = i;
            novo_processo->proximo = NULL;
            novo_processo->anterior = NULL;
            
            printf("\n---------- Novo processo chegou ----------\n");
            printf("Prioridade do processo: %d\n", ((novo_processo->prioridade + i)/duracao) - 1);
            printf("Unidades de tempo para processá-lo: %d\n", novo_processo->ut);
            printf("Linhas a serem impressas para o processo: %d\n", novo_processo->li);

            /* Insere novo processo na fila de CPU caso não esteja cheia ou insere na fila de espera, caso a fila de CPU esteja cheia.  */
            if(!fila_CPU_cheia(max_CPU)) {
                novo_processo->permanencia_espera = 0;
                /* Ajuste do tempo de permanência em CPU para processos que são "processados" - iterados na fila da CPU -
                já quando entram. Esse ajuste deve-se ao fato de que processos que passam pela fila de espera devem
                esperar uma UT para começarem a ser iterados e, poranto, deve-se padronizar a contagem. */
                novo_processo->permanencia_CPU--;
                fila_CPU_entra(novo_processo, max_CPU);
            }
            /* Insere novo processo na fila de espera por tempo e na fila de espera por prioridade. */
            else {
                fila_ei_entra(f_espera, novo_processo);
                fila_prioridade_insert(novo_processo);
            }

        }

        /* Itera sobre a fila de impressão. */
        if(!fila_ei_vazia(f_impressora)) {
            Processo** auxiliar_impressora = fila_ei_itera(f_impressora, 0);
            Processo** auxiliar_impressora_2 = malloc(3*sizeof(Processo*));
            int iterador = 0;

            /* Checa o tamanho da fila de impressão e,para cada caso, estuda as possibilidades das primeiras impressões da fila - até no máximo
            três - terem terminado de processar. Se alguma dessas - ou múltiplas dessas - terminaram de processar, são devidamente retiradas da
            fila de impressão. */
            if(auxiliar_impressora != NULL) {
                if(fila_ei_tamanho(f_impressora) == 1) {
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                }
                else if(fila_ei_tamanho(f_impressora) == 2) {
                    int sai_1 = 0;
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                        sai_1 = 1;
                    }

                    if(auxiliar_impressora[1]->li <= 0 && sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[1]->li <= 0 && !sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                }
                else if(fila_ei_tamanho(f_impressora) >= 3) {
                    int sai_1 = 0, sai_2 = 0;
                    if(auxiliar_impressora[0]->li <= 0) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                        sai_1 = 1;
                    }

                    if(auxiliar_impressora[1]->li <= 0 && sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                        sai_2 = 1;
                    }
                    else if(auxiliar_impressora[1]->li <= 0 && !sai_1) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                        sai_2 = 1;
                    }

                    if(auxiliar_impressora[2]->li <= 0 && sai_1 && sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 1);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && sai_1 && !sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && !sai_1 && sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 2);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                    else if(auxiliar_impressora[2]->li <= 0 && !sai_1 && !sai_2) {
                        auxiliar_impressora_2[iterador] = fila_ei_sai(f_impressora, 3);
                        iterador++;
                        if(i >= 99)
                            total_processos_media++;
                        total_processos++;
                    }
                }
            }

            /* Imprime as impressões que foram retiradas da fila e atualiza os devidos contadores. Foram adicionadas as 
            devidas atualizações sobre os parâmetros de contagem retirando, desse modo, os laços desnecessários e ineficientes
            nas funções "itera" de cada uma das filas. Agora os parâmetros de cada fila recebem um certo valor inicial - esse valor
            depende de quando o processo entrou em cada uma das filas - e os processos atualizam seus parâmetros de contagem 
            novamente apenas em sua saída da fila.*/
            int j;
            for(j = 0; j < iterador; j++) {
                /* Ajuste de prioridade para padrão estabelecido no enunciado */
                auxiliar_impressora_2[j]->prioridade = auxiliar_impressora_2[j]->prioridade + auxiliar_impressora_2[j]->permanencia_total;
                auxiliar_impressora_2[j]->prioridade = auxiliar_impressora_2[j]->prioridade/duracao;
                auxiliar_impressora_2[j]->prioridade -= 2;

                auxiliar_impressora_2[j]->permanencia_total = i - auxiliar_impressora_2[j]->permanencia_total;
                auxiliar_impressora_2[j]->permanencia_impressao = i - auxiliar_impressora_2[j]->permanencia_impressao;
                /* Ajuste do tempo de permanência total para aqueles processos cujo tempo na CPU fora ajustado porque entraram
                direto na fila_CPU sem passar na fila de espera. */
                if(auxiliar_impressora_2[j]->permanencia_total != auxiliar_impressora_2[j]->permanencia_espera + 
                    auxiliar_impressora_2[j]->permanencia_CPU + auxiliar_impressora_2[j]->permanencia_impressao)
                    auxiliar_impressora_2[j]->permanencia_total++;

                printf("\n---------- Processo terminado - com impressão ----------\n");
                printf("Dados iniciais: \n");
                printf("        Prioridade do processo: %d\n", auxiliar_impressora_2[j]->prioridade);
                printf("        Tempo de processamento: %d\n", auxiliar_impressora_2[j]->ut_inicial);
                printf("        Número de linhas: %d\n", auxiliar_impressora_2[j]->li_inicial);
                printf("Tempo de permanência no sistema: %d\n", auxiliar_impressora_2[j]->permanencia_total);
                printf("Tempo na fila de espera: %d\n", auxiliar_impressora_2[j]->permanencia_espera);
                printf("Tempo na fila da CPU: %d\n", auxiliar_impressora_2[j]->permanencia_CPU);
                printf("Tempo na fila de impressão: %d\n", auxiliar_impressora_2[j]->permanencia_impressao);
                printf("Razão entre tempo de processamento e o tempo total: %.4f\n",
                    (float)auxiliar_impressora_2[j]->ut_inicial/(float)auxiliar_impressora_2[j]->permanencia_total);

                if(i >= 99) {
                    espera_prioridade[auxiliar_impressora_2[j]->prioridade] += auxiliar_impressora_2[j]->permanencia_espera;
                    numero_prioridade[auxiliar_impressora_2[j]->prioridade] += 1;
                    permanencia_total += auxiliar_impressora_2[j]->permanencia_total;
                    permanencia_espera += auxiliar_impressora_2[j]->permanencia_espera;
                    permanencia_CPU += auxiliar_impressora_2[j]->permanencia_CPU;
                    permanencia_impressao += auxiliar_impressora_2[j]->permanencia_impressao;
                    soma_razao += (float)auxiliar_impressora_2[j]->ut_inicial/(float)auxiliar_impressora_2[j]->permanencia_total;
                }
                free(auxiliar_impressora_2[j]);
            }

            free(auxiliar_impressora_2);
        }
        
        /* Checa o tamanho da fila de espera antes de qualquer processo ser retirado. Serve trocar a flag_tempo_prioridade
        no final do laço. */
        int tam_fila_espera = fila_ei_tamanho(f_espera);

        /* Itera sobre a fila de espera. */
        if(!fila_ei_vazia(f_espera))
            fila_ei_itera(f_espera, 1);
        Processo* auxiliar_espera;

        /* Itera sobre a fila de CPU. */
        if(!fila_CPU_vazia()) {
            Processo* auxiliar_CPU = fila_CPU_itera();

            /* Checa se o primeiro processa da fila já acabou de ser processado ou se esse mesmo processo econtra-se por vinte unidades de tempo
            seguidas na primeira posição. Caso o processo esteja lá por vinte unidades de tempo e ainda precise ser processado, ele vai para o
            fim da fila. Caso ele tenha termiado, ele é retirado da fila e concluído, se não houverem linhas de impressão, ou retirado da fila
            e colocado na fila de impressão, se houverem linhas de impressão. Após essa retirada, o primeiro processo da fila de espera entra
            na fila da CPU. Foram adicionadas as devidas atualizações sobre os parâmetros de contagem retirando, desse modo,
            os laços desnecessários e ineficientes nas funções "itera" de cada uma das filas. Agora os parâmetros de cada fila recebem um
            certo valor inicial - esse valor depende de quando o processo entrou em cada uma das filas - e os processos atualizam seus parâmetros
            de contagem novamente apenas em sua saída da fila.*/
            if(auxiliar_CPU->ut == 0 || conta_tempo == 20) {
                conta_tempo = -1;
                if(auxiliar_CPU->ut == 0) {

                    auxiliar_CPU = fila_CPU_sai();
                    auxiliar_CPU->permanencia_CPU = i - auxiliar_CPU->permanencia_CPU;

                    if(!fila_ei_vazia(f_espera)) {
                        if(flag_tempo_prioridade) {
                            auxiliar_espera = fila_ei_sai(f_espera, 1);
                            auxiliar_espera->prioridade = (10 + 1)*duracao;
                            fila_prioridade_heapifica(auxiliar_espera->indice_heap);
                            fila_prioridade_remove();
                        }

                        else {
                            auxiliar_espera = fila_prioridade_remove();
                            auxiliar_espera->proximo->anterior = auxiliar_espera->anterior;
                            auxiliar_espera->anterior->proximo = auxiliar_espera->proximo;
                            fila_ei_remove_externo(f_espera);
                        }

                        auxiliar_espera->permanencia_espera = i - auxiliar_espera->permanencia_espera;
                        auxiliar_espera->permanencia_CPU = i;
                        fila_CPU_entra(auxiliar_espera, max_CPU);
                    }

                    if(auxiliar_CPU->li > 0) {
                        auxiliar_CPU->permanencia_impressao = i;
                        fila_ei_entra(f_impressora, auxiliar_CPU);
                    }

                    /* Imprime o processo que foi retirado da fila e não tinha linhas de impressão e atualiza os devidos contadores. */
                    else {
                        /* Ajuste de prioridade para padrão estabelecido no enunciado */
                        auxiliar_CPU->prioridade = auxiliar_CPU->prioridade + auxiliar_CPU->permanencia_total;
                        auxiliar_CPU->prioridade = auxiliar_CPU->prioridade/duracao;
                        auxiliar_CPU->prioridade -= 2;

                        auxiliar_CPU->permanencia_total = i - auxiliar_CPU->permanencia_total;
                        auxiliar_CPU->permanencia_impressao = 0;
                        
                        printf("\n---------- Processo terminado - sem impressão ----------\n");
                        printf("Dados iniciais: \n");
                        printf("        Prioridade do processo: %d\n", auxiliar_CPU->prioridade);
                        printf("        Tempo de processamento: %d\n", auxiliar_CPU->ut_inicial);
                        printf("        Número de linhas: %d\n", auxiliar_CPU->li_inicial);
                        printf("Tempo de permanência no sistema: %d\n", auxiliar_CPU->permanencia_total);
                        printf("Tempo na fila de espera: %d\n", auxiliar_CPU->permanencia_espera);
                        printf("Tempo na fila da CPU: %d\n", auxiliar_CPU->permanencia_CPU);
                        printf("Tempo na fila de impressão: %d\n", auxiliar_CPU->permanencia_impressao);
                        printf("Razão entre tempo de processamento e o tempo total: %.4f\n",
                            (float)auxiliar_CPU->ut_inicial/(float)auxiliar_CPU->permanencia_total);
                        
                        total_processos++;
                        
                        if(i >= 99) {
                            espera_prioridade[auxiliar_CPU->prioridade] += auxiliar_CPU->permanencia_espera;
                            numero_prioridade[auxiliar_CPU->prioridade] += 1;
                            total_processos_media++;
                            permanencia_total += auxiliar_CPU->permanencia_total;
                            permanencia_espera += auxiliar_CPU->permanencia_espera;
                            permanencia_CPU += auxiliar_CPU->permanencia_CPU;
                            soma_razao += (float)auxiliar_CPU->ut_inicial/(float)auxiliar_CPU->permanencia_total;
                        }

                        free(auxiliar_CPU);
                    }
                }
                else {
                    fila_CPU_troca();
                }
            }
        }

        /* Imprime dados da saída completa. */
        if(saida == 2) {
            fila_ei_imprime(f_espera, 1);
            /*fila_prioridade_imprime();*/
            fila_CPU_imprime();
            fila_ei_imprime(f_impressora, 0);
            printf("\n---------- Estado das filas ----------\n");
            printf("Tamanho da fila de espera: %d\n", fila_ei_tamanho(f_espera));
            printf("Tamanho da fila da CPU: %d\n", fila_CPU_tamanho());
            printf("Tamanho da fila de impressão: %d\n", fila_ei_tamanho(f_impressora));
            printf("Número total de processos computados: %d\n", total_processos);
        }

        /* Atualiza o contador de tempo apenas quando existem processos na CPU. */
        if(!fila_CPU_vazia())
            conta_tempo++;

        /* Inverte flag_tempo_prioridade para garantir que os processos sejam retirados da fila de tempo e da fila de
        prioridade de maneira alternada. */
        if(tam_fila_espera != fila_ei_tamanho(f_espera))
            flag_tempo_prioridade = 1 - flag_tempo_prioridade;
    }

    /* Imprime um sumário final de tudo que fora feito durante as unidades de tempo do programa. */
    printf("\n-------------------- Sumário --------------------\n");
    if(total_processos_media > 0) {
        printf("Número total de processos computados: %d\n", total_processos);
        for(x = 0; x < 10; x++) {
            printf("Número total de processos computados para prioridade %d: %ld\n", x, numero_prioridade[x]);
        }
        printf("\n");
        printf("Média de permanência total: %.4f\n", (float)permanencia_total/(float)total_processos_media);
        printf("\n");
        printf("Média de permanência na espera: %.4f\n", (float)permanencia_espera/(float)total_processos_media);
        for(x = 0; x < 10; x++) {
            if(numero_prioridade[x] > 0)
                printf("Média de permanência na espera para prioridade %d: %.4f\n", x, (float)espera_prioridade[x]/(float)numero_prioridade[x]);
            else
                printf("Média de permanência na espera para prioridade %d: 0.0000\n", x);
        }
        printf("\n");
        printf("Média de permanência na CPU: %.4f\n", (float)permanencia_CPU/(float)total_processos_media);
        printf("\n");
        printf("Média de permanência na impressão: %.4f\n", (float)permanencia_impressao/(float)total_processos_media);
        printf("\n");
        printf("Média da razão entre o processamento e a permanência: %.4f\n", soma_razao/(float)total_processos_media);
    }
    else {
        printf("Número total de processos computados: %d\n", total_processos);
        printf("Média de permanência total: 0 (menos de 100 UTs)\n");
        printf("Média de permanência na espera: 0 (menos de 100 UTs)\n");
        printf("Média de permanência na espera por prioridade: 0 (menos de 100 UTs)\n");
        printf("Média de permanência na CPU: 0 (menos de 100 UTs)\n");
        printf("Média de permanência na impressão: 0 (menos de 100 UTs)\n");
        printf("Média da razão entre o processamento e a permanência: 0 (menos de 100 UTs)\n");
    }

    /* Libera filas */
    fila_ei_free(f_espera);
    fila_prioridade_free();
    fila_ei_free(f_impressora);
    fila_CPU_free();

    return 0;
}