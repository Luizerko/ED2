#include "processo.h"

void fila_espera_init();

int fila_espera_vazia();

Processo* fila_espera_primeiro();

void fila_espera_entra(Processo*);

Processo* fila_espera_sai();

Processo* fila_espera_itera();

int fila_espera_tamanho();

void fila_espera_free();