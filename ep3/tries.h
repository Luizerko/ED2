/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

tries.h
*/

#include "node_trie.h"

Node_trie* trie_init();

Node_trie* trie_get(Node_trie*, char*, int, int);

Node_trie* trie_put(Node_trie*, char*, int, int);

void trie_imprime(Node_trie*, int);

void trie_imprime_chaves();

Node_trie* trie_free(Node_trie*);