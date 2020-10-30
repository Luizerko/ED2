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