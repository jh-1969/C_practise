#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

void node_free(Node *node);

LinkedList *linked_list_new() {
  LinkedList *list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

void linked_list_free(LinkedList *list) {
  Node *node = list->first;

  while (node != NULL) {
    Node *t = node;
    node = node->next;
    node_free(t);
  }

  free(list);
}

void linked_list_push(LinkedList *list, char *data) {
  if (list->length == 0) {
    Node *first = malloc(sizeof(Node));

    first->data = data;
    first->next = NULL;
    first->prev = NULL;

    list->first = first;
    list->last = first;
  } else {
    Node *next = malloc(sizeof(Node));

    next->data = data;
    next->next = NULL;
    next->prev = list->last;

    list->last->next = next;
    list->last = next;
  }
  list->length++;
}

void linked_list_pop(LinkedList *list) {
  if (list->length == 0) {
    printf("linked list: nothing to pop, linked list is already empty\n");
    return;
  }

  if (list->length == 1) {
    node_free(list->last);
    list->last = NULL;
    list->first = NULL;
  } else {
    list->last = list->last->prev;
    node_free(list->last->next);
    list->last->next = NULL;
  }
  list->length--;
}

Node *linked_list_get_nth(LinkedList *list, int index) {
  if (index >= list->length || index < 0) {
    printf("linked list: index out of range\n");
    return NULL;
  }

  Node *node = list->first;
  for (int i = 0; i < index; i++)
    node = node->next;

  return node;
}

void linked_list_insert_nth(LinkedList *list, char *data, int index) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;

  if (index == 0) {
    newNode->next = list->first;
    list->first->prev = newNode;
    list->first = newNode;
    return;
  }

  Node *oldNode = linked_list_get_nth(list, index);
  if (oldNode == NULL)
    return;

  newNode->prev = oldNode->prev;
  oldNode->prev->next = newNode;

  newNode->next = oldNode;
  oldNode->prev = newNode;
}

void linked_list_remove_nth(LinkedList *list, int index) {
  if (index == 0) {
    list->first = list->first->next;
    node_free(list->first->prev);
    list->first->prev = NULL;
    return;
  }

  if (index == list->length - 1) {
    list->last = list->last->prev;
    node_free(list->last->next);
    list->last->next = NULL;
    return;
  }

  Node *node = linked_list_get_nth(list, index);
  if (node == NULL)
    return;

  node->next->prev = node->prev;
  node->prev->next = node->next;
  node_free(node);
}

void linked_list_map(LinkedList *list, void (*func)(Node *node)) {
  for (Node *n = list->first; n != NULL; n = n->next)
    func(n);
}

void node_free(Node *node) {
  free(node->data);
  free(node);
}
