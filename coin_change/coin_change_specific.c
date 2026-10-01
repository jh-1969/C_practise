#include <stdio.h>

int change(int sum, int coin) {
  sum -= coin;

  if(sum == 0) return 1;
  if(sum < 0) return 0;

  if(coin == 5) return change(sum, 5) + change(sum, 2) + change(sum, 1);
  if(coin == 2) return change(sum, 2) + change(sum, 1);
  return change(sum, 1);
}

int main() {
  int result = change(20, 5) + change(20, 2) + 1;

  printf("%i\n", result);
}
