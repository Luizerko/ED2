#include "node_ARN.h"

Node_ARN* ARN_init();

Node_ARN* ARN_get(Node_ARN*, char*);

Node_ARN* ARN_put(Node_ARN*, char*);

void ARN_imprime();

void ARN_imprime_chaves();

void ARN_free();