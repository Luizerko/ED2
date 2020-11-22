/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

hash_linear.h
*/

#include "node_hash_linear.h"

Node_hash_linear** hash_linear_init();

Node_hash_linear* hash_linear_get(Node_hash_linear**, char*);

Node_hash_linear** hash_linear_put(Node_hash_linear**, char*);

void hash_linear_imprime(Node_hash_linear**);

void hash_linear_imprime_chaves();

void hash_linear_free(Node_hash_linear**);