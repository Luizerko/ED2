#include "processo.h"

#ifndef HEADER_fila

#define HEADER_fila

typedef struct fila {
    Processo* first;
    int n;
} Fila;

#endif