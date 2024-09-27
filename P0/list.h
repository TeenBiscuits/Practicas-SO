// Pablo Portas López
// Pablo Míguez Mouiño

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2048
#define LNULL NULL
#define MAXSIZE 1000

typedef struct tNode *tPosL;

typedef char tItemL[MAX];

struct tNode {
    tItemL comando;
    tPosL siguiente;
};

typedef struct tList {
    int contador;
    tPosL start;
} tList;

void createEmptyList(tList *lista);

bool isEmptyList(tList lista);

tPosL first(tList lista);

tPosL last(tList lista);

tPosL next(tPosL posicion, tList lista);

tPosL previous(tPosL posicion, tList lista);

bool insertItem(tItemL item, tPosL posicion, tList *lista);

void deleteAtPosition(tPosL posicion, tList *lista);

#endif //LIST_H
