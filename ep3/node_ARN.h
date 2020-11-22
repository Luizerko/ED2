/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

node_ARN.h
*/

#ifndef HEADER_node_ARN

#define HEADER_node_ARN

typedef struct node_ARN {
    char* palavra;
    int frequencia;
    int cor;
    struct node_ARN *dir;
    struct node_ARN *esq;
}Node_ARN;

#endif