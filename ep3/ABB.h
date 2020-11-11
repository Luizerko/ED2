#include "node_ABB.h"

Node_ABB* ABB_init();

Node_ABB* ABB_get(Node_ABB*, char*);

Node_ABB* ABB_put(Node_ABB*, char*);

void ABB_imprime(Node_ABB*);

void ABB_imprime_chaves();

void ABB_free();