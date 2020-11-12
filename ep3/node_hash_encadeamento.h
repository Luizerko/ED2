#ifndef HEADER_node_hash_encadeamento

#define HEADER_node_hash_encadeamento

typedef struct node_hash_encadeamento {
    char* palavra;
    int frequencia;
    struct node_hash_encadeamento* prox;
}Node_hash_encadeamento;

#endif