#include "item.h"

#define bool int

void queueInit();

void queueInsert(Item);

Item queueRemove();

bool queueEmpty();

int queueSize();

void queueFree();