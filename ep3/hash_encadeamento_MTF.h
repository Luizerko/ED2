/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

hash_encadeamento_MTF.h
*/

#include "node_hash_encadeamento.h"

Node_hash_encadeamento** hash_encadeamento_MTF_init();

Node_hash_encadeamento* hash_encadeamento_MTF_get(Node_hash_encadeamento**, char*);

Node_hash_encadeamento** hash_encadeamento_MTF_put(Node_hash_encadeamento**, char*);

void hash_encadeamento_MTF_imprime(Node_hash_encadeamento**);

void hash_encadeamento_MTF_imprime_chaves();

void hash_encadeamento_MTF_free(Node_hash_encadeamento**);