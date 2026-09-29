#pragma once

#include <stdint.h>

typedef struct Node {
  struct Node *prev;
  struct Node *next;
  char *data;
} Node;

typedef struct {
  Node *first;
  Node *last;
  uint16_t length;
} LinkedList;

LinkedList *linked_list_new();
void linked_list_free(LinkedList *list);
int linked_list_push(LinkedList *list, char *data);
void linked_list_pop(LinkedList *list);
Node *linked_list_get_nth(LinkedList *list, int index);
int linked_list_insert_nth(LinkedList *list, char *data, int index);
void linked_list_remove_nth(LinkedList *list, int index);
void linked_list_map(LinkedList *list, void (*func)(Node *node));
