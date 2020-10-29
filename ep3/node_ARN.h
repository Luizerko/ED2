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