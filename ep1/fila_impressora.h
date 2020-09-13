#include "processo.h"
#include "fila.h"

Fila* fila_impressora_init();

int fila_impressora_vazia(Fila*);

Processo* fila_impressora_primeiro(Fila*);

void fila_impressora_entra(Fila*, Processo*);

Processo* fila_impressora_sai(Fila*, int);

Processo** fila_impressora_itera(Fila*, int);

int fila_impressora_tamanho(Fila*);

void fila_impressora_free(Fila*);