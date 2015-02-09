#include<stdlib.h>
#include<math.h>

#define count 10000000

unsigned numbers[count*2];
unsigned result[count];

int main(void) {
  int i;
  for (i = 0; i < count*2; i++) {
    numbers[i] = rand();
  }
  for (i = 0; i < count; i++) {
    result[i] = numbers[i]*pow(10, log10(numbers[i+1])) + numbers[i+1];
  }
}

/* more bit twiddling to get log10 to be fast. what about pow? http://stackoverflow.com/questions/10723295/counting-number-of-digits-in-a-number-in-o1 */
