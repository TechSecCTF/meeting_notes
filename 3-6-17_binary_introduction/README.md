# Architecture and Machine Code
The first step in learning to exploit programs is understanding how they work.
This guide is going to cover ELF executables specifically, but the knowledge is
generally applicable to other types of executables. We colloquially refer to
compiled programs as *binaries*. Binaries are composed of machine code, an
extremely rudimentary set of instructions that are specific to the CPU.

## hello.c
First we'll write a simple program and look at it's machine code. Write the
program below (or a similar one), compile it, and run it if you want:

```C
#include <stdio.h>

int main(void) {
    printf("Welcome to TechSec\n");
    return 0;
}
```

To compile the source code into a binary, run `gcc -o intro intro.c`. You can
also run the program with `./intro` if desired.

We'll view the binary's machine code with `objdump`. Run `objdump -M intel -d
./into intro | less` and your screen will fill with machine code. From here,
you can scroll line by line with `j` and `k`, or scroll page by page with the
spacebar and `b`. You can search for text with `/$text`, jump to the next
occurrence with `n`, and jump to the previous occurrence with `N`. Search for
`<main>` to see the machine code for `main()`.  It will look something like
this:

```
0000000000400526 <main>:
  400526:       55                      push   rbp
  400527:       48 89 e5                mov    rbp,rsp
  40052a:       bf c4 05 40 00          mov    edi,0x4005c4
  40052f:       e8 cc fe ff ff          call   400400 <puts@plt>
  400534:       b8 00 00 00 00          mov    eax,0x0
  400539:       5d                      pop    rbp
  40053a:       c3                      ret
  40053b:       0f 1f 44 00 00          nop    DWORD PTR [rax+rax*1+0x0]
```

The line at the top is the name of the current symbol (`main`) and it's
location in memory. A *symbol* is a location in memory that the compiler
decided to name. Functions and global variables in C code become symbols in
machine code.The following lines are the location of a machine code
instruction, the bytes representing that instruction, and the "human readable"
assembly code corresponding to that instruction.

## Intel vs. AT&T
The assembly pictured above is written in Intel syntax. If
you chanced to run `objdump` without the `-M intel` flag, you would have seen
assembly written in AT&T syntax. AT&T syntax is easy to recognize due to the
cacophony of `$` and `%` characters prefixing everything. People tend to find
Intel syntax easier to read, so for the purposes of this guide, we will use it.

## Reading Assembly
Assembly instructions in Intel syntax have the form `<instruction>
<destination> <source>`, or just `<instruction> <argument>` if there is no
destination and source. The disassembly of `main()` in `intro.c` contains the
following instructions:

* `mov` - write data specified by `source` to `destination`
* `push` - decrement the stack pointer, then write data specified by `argument` to the top of the stack
* `pop` - write data at the top of the stack to `argument`, then increment the
  stack pointer
* `call` - `push` the location of the next instruction, then begin executing
  instructions at the location specified by `argument`
* `ret` - begin executing instructions at the location at the top of the stack,
then increment the stack pointer
* `nop` - do absolutely nothing
