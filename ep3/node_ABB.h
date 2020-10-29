#ifndef HEADER_node_ABB

#define HEADER_node_ABB

typedef struct node_ABB {
    char* palavra;
    int frequencia;
    struct node_ABB *dir;
    struct node_ABB *esq;
}Node_ABB;

#endif