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

fila_prioridade.h
*/

#include "processo.h"

#define bool int

void fila_prioridade_init();

void fila_prioridade_insert(Processo*);

Processo* fila_prioridade_remove();

void fila_prioridade_heapifica(int);

bool fila_prioridade_empty();

int fila_prioridade_size();

void fila_prioridade_imprime();

void fila_prioridade_free();