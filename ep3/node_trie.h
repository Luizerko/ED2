/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

node_trie.h
*/

#ifndef HEADER_node_trie

#define HEADER_node_trie

typedef struct node_trie {
    char palavra;
    int frequencia;
    struct node_trie *dir;
    struct node_trie *esq;
    struct node_trie *meio;
}Node_trie;

#endif