/*
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

fila_ei.h
*/

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

void fila_ei_remove_externo(Fila*);

void fila_ei_free(Fila*);