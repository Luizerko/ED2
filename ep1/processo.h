#ifndef HEADER_processo

#define HEADER_processo

typedef struct processo {
    int ut_inicial;
    int li_inicial;
    int ut;
    int li;
    int permanencia_total;
    int permanencia_espera;
    int permanencia_CPU;
    int permanencia_impressao;

    struct processo* anterior;
    struct processo* proximo;
} Processo;

#endif