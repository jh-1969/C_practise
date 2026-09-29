#include "arena_allocator.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Block *block_new(size_t size);
void block_free(Block *block);

ArenaAllocator *arena_allocator_new(size_t maxBlockSize) {
  ArenaAllocator *arena = malloc(sizeof(ArenaAllocator));
  if (arena == NULL)
    return NULL;

  arena->maxBlockSize = maxBlockSize;
  arena->currSize = 0;

  do {
    arena->firstBlock = block_new(arena->maxBlockSize);
  } while (arena->firstBlock == NULL);

  arena->lastBlock = arena->firstBlock;
  arena->top = arena->firstBlock->data;

  return arena;
}

void arena_allocator_free(ArenaAllocator *arena) {
  Block *block = arena->firstBlock;

  while (block != NULL) {
    Block *t = block;
    block = block->next;
    block_free(t);
  }

  free(arena);
}

char *arena_allocator_allocate(ArenaAllocator *arena, size_t size) {
  if (size > arena->maxBlockSize) {
    printf("arena cannot allocate more than block size\n");
    return NULL;
  }

  arena->currSize += size;

  if (arena->currSize > arena->maxBlockSize) {
    do {
      arena->lastBlock->next = block_new(arena->maxBlockSize);
    } while (arena->lastBlock->next == NULL);

    arena->lastBlock = arena->lastBlock->next;
    arena->top = arena->lastBlock->data;
    arena->currSize = 0;
  }

  char *currTop = arena->top;
  arena->top += size;
  return currTop;
}

Block *block_new(size_t size) {
  Block *block = malloc(sizeof(Block));
  if (block == NULL)
    goto blockAllocFailed;

  block->next = NULL;
  block->data = malloc(size);
  if (block->data == NULL)
    goto dataAllocFailed;

  return block;

dataAllocFailed:
  free(block);
blockAllocFailed:
  return NULL;
}

void block_free(Block *block) {
  free(block->data);
  free(block);
}
