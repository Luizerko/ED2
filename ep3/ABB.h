/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

ABB.h
*/

#include "node_ABB.h"

Node_ABB* ABB_init();

Node_ABB* ABB_get(Node_ABB*, char*);

Node_ABB* ABB_put(Node_ABB*, char*);

void ABB_imprime(Node_ABB*);

void ABB_imprime_chaves();

Node_ABB* ABB_free(Node_ABB*);