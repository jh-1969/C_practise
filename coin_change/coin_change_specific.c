#include <stdio.h>

int change(int sum, int coin) {
  sum -= coin;

  if (sum == 0)
    return 1;
  if (sum < 0)
    return 0;

  if (coin == 5)
    return change(sum, 5) + change(sum, 2) + change(sum, 1);
  if (coin == 2)
    return change(sum, 2) + change(sum, 1);
  return change(sum, 1);
}

int main() {
  int sum = 20;
  int result = change(sum, 5) + change(sum, 2) + 1;

  printf("the sum %i can be changed in %i ways using the coins: 1 2 5\n", sum,
         result);
}
