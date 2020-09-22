#include "processo.h"
#include "fila.h"

Fila* fila_ei_init();

int fila_ei_vazia(Fila*);

Processo* fila_ei_primeiro(Fila*);

void fila_ei_entra(Fila*, Processo*);

Processo* fila_ei_sai(Fila*, int);

Processo** fila_ei_itera(Fila*, int);

int fila_ei_tamanho(Fila*);

void fila_ei_imprime(Fila*, int);

void fila_ei_free(Fila*);