/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  addr_t i = 0;
  flush_cache();
  access_cache(i);
  while (1) {
    if (!access_cache(i)) {
        break;
    }
    i++;
  }
  return i;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  int psize = 1;
  int i, se;
  flush_cache();
  while (1) {
    if (psize >= size) {
        se = psize / size;
        for (i = 0; i < se; i++) {
            access_cache(i*size);
        }
        for (i = 0; i < psize; i++) {
            if (!access_cache(i)) {
                return psize >> 1;
            }
        }
    }
    psize = psize << 1;
  }
  return -1;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  addr_t i, j;
  flush_cache();
  for (i = 0; 1; i += size) {
     access_cache(i);
     for (j = 0; j <= i; j+= size) {
        if (!access_cache(j)) {
            return i / size;
        }
     }
  }
  return -1;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
