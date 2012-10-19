#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <string.h>
#include "person.h"

struct queue{
    person *pers;
    struct queue *next;
};


int is_empty();
void enqueue(person *p);
int search(const char *name);
void print_q();
int remove_node(char *name);
void free_memory();
















#endif
