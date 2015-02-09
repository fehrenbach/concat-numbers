#include<stdlib.h>
#include<math.h>
#include<stdio.h>

#define count 10000000

int numbers[count*2];
char result[count];

int main(void) {
  int i;
  for (i = 0; i < count*2; i++) {
    numbers[i] = rand();
  }
  for (i = 0; i < count; i++) {
    // this is really stupid, but I don't care enough to figure out what size of string I need. Anyways, I don't think this should be faster than doing math.
    sprintf(result, "%d%d", numbers[i], numbers[i+1]);
  }
}
