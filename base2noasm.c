#include<stdlib.h>
#include<stdint.h>
#include<math.h>

#define count 10000000

int numbers[count*2];
int result[count];

int main(void) {
  int i;
  for (i = 0; i < count*2; i++) {
    numbers[i] = rand();
  }
  for (i = 0; i < count; i++) {
    result[i] = (numbers[i] << (int) log2(numbers[i+1])) + numbers[i+1];
  }
}
