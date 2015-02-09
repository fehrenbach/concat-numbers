#include<stdlib.h>
#include<stdint.h>

static inline uint32_t log2(const uint32_t x) {
  uint32_t y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}

#define count 10000000

unsigned numbers[count*2];
unsigned result[count];

int main(void) {
  int i;
  for (i = 0; i < count*2; i++) {
    numbers[i] = rand();
  }
  for (i = 0; i < count; i++) {
    result[i] = (numbers[i] << log2(numbers[i+1])) ^ numbers[i+1];
  }
}

/*
stefan@stefan-work:~/src/concat-numbers$ clang -O3 -lm base2.c 
stefan@stefan-work:~/src/concat-numbers$ gdb -batch -ex 'file a.out' -ex 'disassemble main'
Dump of assembler code for function main:
   0x00000000004005a0 <+0>:     push   %rbx
   0x00000000004005a1 <+1>:     xor    %ebx,%ebx
   0x00000000004005a3 <+3>:     data16 data16 data16 nopw %cs:0x0(%rax,%rax,1)
   0x00000000004005b0 <+16>:    callq  0x400490 <rand@plt>
   0x00000000004005b5 <+21>:    mov    %eax,0x2c26420(%rbx)
   0x00000000004005bb <+27>:    add    $0x4,%rbx
   0x00000000004005bf <+31>:    cmp    $0x4c4b400,%rbx
   0x00000000004005c6 <+38>:    jne    0x4005b0 <main+16>
   0x00000000004005c8 <+40>:    mov    0x2825e52(%rip),%edx        # 0x2c26420 <numbers>
   0x00000000004005ce <+46>:    mov    $0x4,%eax
   0x00000000004005d3 <+51>:    data16 data16 data16 nopw %cs:0x0(%rax,%rax,1)
   0x00000000004005e0 <+64>:    mov    0x2c26420(%rax),%esi
   0x00000000004005e6 <+70>:    bsr    %esi,%ecx
   0x00000000004005e9 <+73>:    shl    %cl,%edx
   0x00000000004005eb <+75>:    add    %esi,%edx
   0x00000000004005ed <+77>:    mov    %edx,0x600a1c(%rax)
   0x00000000004005f3 <+83>:    add    $0x4,%rax
   0x00000000004005f7 <+87>:    cmp    $0x2625a04,%rax
   0x00000000004005fd <+93>:    mov    %esi,%edx
   0x00000000004005ff <+95>:    jne    0x4005e0 <main+64>
   0x0000000000400601 <+97>:    xor    %eax,%eax
   0x0000000000400603 <+99>:    pop    %rbx
   0x0000000000400604 <+100>:   retq   
End of assembler dump.
*/
