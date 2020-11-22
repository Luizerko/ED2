/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

ARN.h
*/

#include "node_ARN.h"

Node_ARN* ARN_init();

Node_ARN* ARN_get(Node_ARN*, char*);

Node_ARN* ARN_put(Node_ARN*, char*);

void ARN_imprime(Node_ARN*);

void ARN_imprime_chaves();

Node_ARN* ARN_free(Node_ARN*);