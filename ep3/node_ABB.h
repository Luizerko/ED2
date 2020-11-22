/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

node_ABB.h
*/

#ifndef HEADER_node_ABB

#define HEADER_node_ABB

typedef struct node_ABB {
    char* palavra;
    int frequencia;
    struct node_ABB *dir;
    struct node_ABB *esq;
}Node_ABB;

#endif