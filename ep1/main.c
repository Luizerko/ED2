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
    int max_impressora = 10000;
    fila_CPU_init();

    int i = 0;
    for(i = 0; i < duracao; i++) {
        if(rand()%10 == 0) {

            Processo *novo_processo = malloc(sizeof(Processo));
            novo_processo->ut = rand()%60 + 1;
            novo_processo->li = rand()%501;
            novo_processo->permanencia_total = 0;
            novo_processo->permanencia_espera = 0;
            novo_processo->permanencia_CPU = 0;
            novo_processo->permanencia_impressao = 0;
            novo_processo->proximo = NULL;
            novo_processo->anterior = NULL;
            
            printf("\nNovo processo chegou!\n");
            printf("Unidades de tempo para processá-lo: %d\n", novo_processo->ut);
            printf("Linhas a serem impressas para o processo: %d\n", novo_processo->li);

            if(!fila_CPU_cheia(max_CPU)) {
                fila_CPU_entra(novo_processo, max_CPU);
            }
            else {
                fila_espera_entra(novo_processo);
            }

        }
        
        Processo* auxiliar_CPU = fila_CPU_itera();
        Processo* auxiliar_espera;

        if(auxiliar_CPU != NULL && (auxiliar_CPU->ut == 0 || conta_tempo == 20)) {
            conta_tempo = -1;
            if(auxiliar_CPU->ut == 0) {
                auxiliar_CPU = fila_CPU_sai();
                total_processos++;
                if(!fila_espera_vazia()) {
                    auxiliar_espera = fila_espera_sai();
                    fila_CPU_entra(auxiliar_espera, max_CPU);
                }
            }
            else {
                fila_CPU_troca();
            }
        }

        conta_tempo++;
    }

    printf("Tamanho CPU: %d\n", fila_CPU_tamanho());
    printf("Tamanho espera: %d\n", fila_espera_tamanho());
    printf("%d\n", total_processos);

    return 0;
}