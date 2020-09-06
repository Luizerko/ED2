#include "processo.h"

void fila_CPU_init();

int fila_CPU_vazia();

int fila_CPU_cheia(int);

Processo* fila_CPU_primeiro();

void fila_CPU_entra(Processo*, int);

Processo* fila_CPU_sai();

Processo* fila_CPU_itera();

void fila_CPU_troca();

int fila_CPU_tamanho();

void fila_CPU_free();