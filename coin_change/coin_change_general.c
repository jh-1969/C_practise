#include <stdio.h>

int change(int sum, int coin, const int *coins, const int coinsLength) {
  sum -= coin;

  if (sum == 0)
    return 1;
  if (sum < 0)
    return 0;

  int return_sum = 0;
  for (int i = 0; i < coinsLength; i++) {
    if (coin >= coins[i])
      return_sum += change(sum, coins[i], coins, coinsLength);
  }
  return return_sum;
}

int main() {
  const int sum = 100;
  const int coins[3] = {1, 2, 5};
  const int coinsLength = 3;

  int result = 0;
  for (int i = 0; i < coinsLength; i++) {
    result += change(sum, coins[i], coins, coinsLength);
  }

  printf("the sum %i can be changed in %i ways using the coins:\n", sum,
         result);
  for (int i = 0; i < coinsLength; i++) {
    printf("%i ", coins[i]);
  }
  printf("\n");
}
