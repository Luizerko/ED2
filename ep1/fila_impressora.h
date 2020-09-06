#include "processo.h"

void fila_impressora_init();

int fila_impressora_vazia();

Processo* fila_impressora_primeiro();

void fila_impressora_entra(Processo*);

Processo* fila_impressora_sai(int);

Processo** fila_impressora_itera();

int fila_impressora_tamanho();

void fila_impressora_free();