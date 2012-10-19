#include "linkedlist.h"
#include <stdio.h>


/*our global variables*/
struct queue *first = NULL;
int size = 0;

/**
 * Checks if the list is empty
 * @return if size is true
 */
int is_empty() {
    return size == 0;
}

/**
 * enqueues the person data inside the datastructure
 * @param p
 */
void enqueue(person *p) {
    struct queue *current;

    struct queue *new_node = malloc(sizeof (struct queue));
    new_node->pers = p;
    new_node->next = NULL;

    if (size == 0) {
        first = new_node;
    } else {
        current = first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    size++;
}

/**
 * searches for the given name of the person
 * @return 1 if successful else -1
 */
int search(const char *name) {
    struct queue *q = first;

    while (q != NULL) {
        if (strcmp(q->pers->name, name) == 0) {
            return 1;
        }
    }
    return -1;

}

/**
 * prints the current items on the list
 *
 */
void print_q() {
    struct queue *current = first;
    while (current != NULL) {
        printf("%d, %s\n", current->pers->id, current->pers->name);
        current = current->next;
    }
}

/**
 * removes the node from the list
 * @param name
 * @return 1 if successful else -1
 */
int remove_node(char *name) {
    struct queue *current;
    struct queue *tmp;
    
    if(is_empty()) {
        return -1;
    }

    if (strcmp(name,first->pers->name) == 0) {
        size--;
        first = first->next;
        return 1;
    } else {
        size--;
        current = first;
        while (strcmp(current->next->pers->name,name) != 0) {
            current = current->next;
        }
        tmp = current->next;
        current->next = current->next->next;
        free(tmp);
        return 1;
    }
    return -1;
}

/**
 * cleaning up the allocated memory space that has been malloced
 */

void free_memory() {
    struct queue *tmp;
    struct queue *tmp2;

    for(tmp = first; tmp != NULL; tmp = tmp2) {
        tmp2 = tmp->next;
        free(tmp);
    }
}

