#pragma once

#include <stddef.h>

typedef struct Block {
  struct Block *next;
  char *data;
} Block;

typedef struct {
  Block *firstBlock;
  Block *lastBlock;
  char *top;
  size_t maxBlockSize;
  size_t currSize;
} ArenaAllocator;

ArenaAllocator *arena_allocator_new(size_t maxBlockSize);
void arena_allocator_free(ArenaAllocator *arena);
char *arena_allocator_allocate(ArenaAllocator *arena, size_t size);
