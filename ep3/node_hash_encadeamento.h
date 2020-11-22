/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

node_hash_encadeamento.h
*/

#ifndef HEADER_node_hash_encadeamento

#define HEADER_node_hash_encadeamento

typedef struct node_hash_encadeamento {
    char* palavra;
    int frequencia;
    struct node_hash_encadeamento* prox;
}Node_hash_encadeamento;

#endif