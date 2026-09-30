#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  int key;
  int value;
} Node;

typedef struct {
  Node *first;
  Node *last;
} LinkedList;

typedef struct {
  LinkedList *entries;
  int entriesLength;
} HashTable;

int list_push(LinkedList *list, int key, int value);
void list_free(LinkedList *list);

HashTable *ht_create(int *nums, int length);
int ht_hash(int value, int length);
int ht_get(HashTable *ht, int key);
void ht_free(HashTable *ht);

int twoSum(int *nums, int numsLength, int target, int *output) {
  HashTable *ht = ht_create(nums, numsLength);
  if (ht == NULL)
    return -1;

  for (int i = 0; i < numsLength; i++) {
    int diff = target - nums[i];

    int diffIndex = ht_get(ht, diff);
    if (diffIndex != -1) {
      output[0] = i;
      output[1] = diffIndex;

      ht_free(ht);
      return EXIT_SUCCESS;
    };
  }

  ht_free(ht);
  return EXIT_FAILURE;
}

int main() {
  int sum = 12;
  int nums[] = {2, 8, 4, 9, 11, 7, 50, 34};
  int numsLenght = 8;

  printf("from the numbers: ");
  for (int i = 0; i < numsLenght; i++) {
    printf("%i ", nums[i]);
  }
  printf("\n");

  int *output = calloc(2, sizeof(int));
  if (twoSum(nums, numsLenght, sum, output) == EXIT_FAILURE)
    printf("there are no two numbers that add up the target %i\n", sum);
  else
    printf("the two that add up to the target %i, are nums[%i] = %i and "
           "nums[%i] = %i\n",
           sum, output[0], nums[output[0]], output[1], nums[output[1]]);

  free(output);
}

HashTable *ht_create(int *nums, int length) {
  HashTable *ht = malloc(sizeof(HashTable));
  if (ht == NULL)
    goto htAllocFailed;

  ht->entriesLength = round((float)length * 1.3);
  ht->entries = calloc(ht->entriesLength, sizeof(LinkedList));
  if (ht->entries == NULL)
    goto entriesAllocFailed;

  int indexOfAllocFail = 0;
  for (int i = 0; i < length; i++) {
    int hi = ht_hash(nums[i], ht->entriesLength);
    if (list_push(&ht->entries[hi], nums[i], i) == EXIT_FAILURE) {
      indexOfAllocFail = i;
      goto listAllocFailed;
    }
  }
  return ht;

listAllocFailed:
  for (int i = 0; i < indexOfAllocFail + 1; i++) {
    int hi = ht_hash(nums[i], ht->entriesLength);
    list_free(&ht->entries[hi]);
  }
  free(ht->entries);
entriesAllocFailed:
  free(ht);
htAllocFailed:
  return NULL;
}

int ht_hash(int key, int length) {
  return (int)((sin(304 * key) + 1) * 1000.0f) % length;
}

int ht_get(HashTable *ht, int key) {
  LinkedList list = ht->entries[ht_hash(key, ht->entriesLength)];

  if (list.first != NULL) {
    for (Node *n = list.first; n != NULL; n = n->next) {
      if (n->key == key)
        return n->value;
    }
  }
  return -1;
}

void ht_free(HashTable *ht) {
  for (int i = 0; i < ht->entriesLength; i++) {
    if (ht->entries[i].first != NULL) {
      list_free(&ht->entries[i]);
    }
  }
  free(ht->entries);
  free(ht);
}

int list_push(LinkedList *list, int key, int value) {
  if (list->first == NULL) {
    list->first = malloc(sizeof(Node *));
    if (list->first == NULL)
      return EXIT_FAILURE;

    list->first->key = key;
    list->first->value = value;
    list->first->next = NULL;
    list->last = list->first;

    return EXIT_SUCCESS;
  }

  list->last->next = malloc(sizeof(Node *));
  if (list->last->next == NULL)
    return EXIT_FAILURE;

  list->last->next->key = key;
  list->last->next->value = value;
  list->last->next->next = NULL;
  list->last = list->last->next;

  return EXIT_SUCCESS;
}

void list_free(LinkedList *list) {
  Node *n = list->first;

  while (n != NULL) {
    Node *t = n;
    n = n->next;
    free(t);
  }
}
