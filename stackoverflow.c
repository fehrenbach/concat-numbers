#include<stdlib.h>
#include<math.h>

#define count 10000000

unsigned numbers[count*2];
unsigned result[count];

/* http://stackoverflow.com/a/12700533 */

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

int main(void) {
  int i;
  for (i = 0; i < count*2; i++) {
    numbers[i] = rand();
  }
  for (i = 0; i < count; i++) {
    result[i] = concatenate(numbers[i], numbers[i+1]);
  }
}

