#include "node_trie.h"

Node_trie* trie_init();

Node_trie* trie_get(Node_trie*, char*);

Node_trie* trie_put(Node_trie*, char*, int, int);

void trie_imprime(Node_trie*, int);

void trie_imprime_chaves();

void trie_free();