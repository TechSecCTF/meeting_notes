# Stack Smashing
Today we'll be exploring stack smashing, one of the oldest and most fundamental
techniques of exploitation.

## Unsafe Writes
The premise of this bug is simple: When data is written to memory in C, there
is no concept of a "buffer", let alone the size of a buffer. This means that if
a function is instructed to write past the end of a buffer, it will happily do
so, overwriting any other data that happens to be sitting in the way. For
example, consider the manpage entry for `gets()`:

```
SYNOPSIS
       #include <stdio.h>

       char *gets(char *s);

DESCRIPTION
       Never use this function.

       gets()  reads  a  line from stdin into the buffer pointed to by s until
       either a terminating newline or EOF, which it replaces with a null byte
       ('\0').  No check for buffer overrun is performed (see BUGS below).
```

From the first sentence of the description, the manpage makes it blatantly
obvious how unsafe the function is, for the same reason described above. There
is no check for a buffer overrun. Consider the snippet of code below:

```C
#include <stdio.h>

int main(void) {
    int num = 1443;
    char buf[50];

    gets(buf);

    printf("%d\n", num);

    return 0;
}
```

Below is a diagram of the stack just before the call to `gets()`.

![Stack before gets()](./stack_smashing_example1.png)

If we were to enter a string of length 49 or less (remember the terminating
null byte), we would expect this program to print 1443. But what if we were to
enter 50 or more characters? Since `gets()` doesn't do any bounds checking, we
expect `num` to be overwritten. Lets see this happen in practice. Compile the
program above with `gcc -fno-stack-protector prog.c` and run `python -c 'print
"A"*49' | ./a.out`:

```
devneal@nealscape:~/techsec/meeting_notes/04-03-17_stack_smashing$ python -c 'print "A"*49' | ./a.out
1443
devneal@nealscape:~/techsec/meeting_notes/04-03-17_stack_smashing$ python -c 'print "A"*50' | ./a.out
1443
devneal@nealscape:~/techsec/meeting_notes/04-03-17_stack_smashing$
```

Well, so much for that. Though it may seem like the input was unsuccessful, the
truth is that the size of the buffer is being padded to a multiple of 8 bytes
(a machine word) for better performance. So the "real" size of the buffer is
56 bytes, not 50. Knowing this, lets try again:

```
devneal@nealscape:~/techsec/meeting_notes/04-03-17_stack_smashing$ python -c 'print "A"*55' | ./a.out
1443
devneal@nealscape:~/techsec/meeting_notes/04-03-17_stack_smashing$ python -c 'print "A"*56' | ./a.out
1280
devneal@nealscape:~/techsec/meeting_notes/04-03-17_stack_smashing$
```

Just as expected, `num` is being overwritten. Below is a diagram of the stack
after the call to `gets()`:

![Stack after gets()](./stack_smashing_example2.png)

Since `num` is stored in little-endian byte order, the least significant bit is
overwritten first, changing the value from `0x00000005A3` to `0x0000000500`.
You can verify in python that these are equal to 1443 and 1280, respectively.
Additionally, you can simply write a ton of 'A' characters to overwrite the
return address, causing the program to crash.

## Targeted writes
Since we can overwrite `num` with arbitrary bytes, we can effectively change it
to be any value we want. The classical way to do this is to use python's
`struct` module. However, we have better tools available to us now. This is how
to write arbitrary bytes in 2017:

```python
#!/usr/bin/python
from pwn import *

your_val_here = 12345
p = process('./a.out')
p.sendline('A' * 56 + p64(your_val_here))
print p.readline()
```
If you want to write negative arguments, you'll have to use something like
`p64(-1, sign="signed", endinanness="little")`.

## Control hijacking
Overwriting variables is fun, but overwriting the return address is of
particular interest, since doing so allows us to control which function is
called next. In the program above, if we substitute `p.sendline('A' * 56 +
p64(your_val_here))` with `p.sendline('A' * 72 + p64(your_address_here))`, the
program will start executing instructions at `your_address_here` after
returning from `main()`. We need only supply the location in memory of the
desired function.

### Symbols
When a program is compiled, the locations of global variables and functions are
named (unless you tell the compiler not to do this). These names are called
*symbols*, and we can view them with a tool called `readelf`. Run `readelf
--symbols a.out | less` to view the symbols of `a.out`. My output from
`readelf --symbols a.out` is below:

```
[truncated]
59: 0000000000601030     0 NOTYPE  GLOBAL DEFAULT   25 __data_start
60: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
61: 0000000000601038     0 OBJECT  GLOBAL HIDDEN    25 __dso_handle
62: 0000000000400620     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used
63: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND gets@@GLIBC_2.2.5
64: 00000000004005a0   101 FUNC    GLOBAL DEFAULT   14 __libc_csu_init
65: 0000000000601048     0 NOTYPE  GLOBAL DEFAULT   26 _end
66: 0000000000400470    42 FUNC    GLOBAL DEFAULT   14 _start
67: 0000000000601040     0 NOTYPE  GLOBAL DEFAULT   26 __bss_start
68: 0000000000400566    57 FUNC    GLOBAL DEFAULT   14 main
69: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _Jv_RegisterClasses
70: 0000000000601040     0 OBJECT  GLOBAL HIDDEN    25 __TMC_END__
71: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
72: 0000000000400400     0 FUNC    GLOBAL DEFAULT   11 _init
```
From this output, we can see that `main()` is located at `0x400566`. If there
were other functions in the program (like in challenge 3), they would be
included here too, and you could read off their memory locations.

# Shellcode
Shellcoding is the oldest trick in the binary exploitation book. It's
essentially a clever way to handle the fact that overwriting the return
address only allows us to execute functions that are already in the program.
The trick is to write our own instructions to memory *in addition to* the
address to jump to. The attack is best summarized with a diagram. We craft our
input such that the resulting stack has the following form:

![Shellcode Input](./shellcode_diagram.png)

If we overwrite the start of `buf` with our shellcode and the return address
with the address of `buf`, then when the program will begin executing the
shellcode when the function returns. And since the purpose of shellcode is to
spawn a shell, we can then run arbitrary commands on the machine that was
exploited, a disastrous result for a bug as innocent as an incorrect write.

# Mitigation Techniques
Since buffer overflows are so common and so dangerous, many mitigation
techniques have been invented to make them more difficult to exploit. The most
common ones are stack canaries, non-executable stacks, and ASLR.

## Stack Canaries
These are random word-sized values written to the stack between local variables
and the saved frame pointer. Before the function returns, the stack canary is
checked to ensure it still has the same value that it did originally. If not,
an error is thrown.

## Non-Executable Stack
An error is thrown whenever the program attempts to execute instructions from
the stack.

## Address Space Layout Randomization (ASLR)
The segments composing the program's memory are randomized before each run,
making it much more difficult to find the address of functions.

These techniques make stack smashing much more difficult in practice, but they
do not make it impossible. At its core, exploitation requires an attention to
detail greater than even the original authors, not rote memorization of
techniques.

# Challenges
There are 4 challenges, each running at `lox.xvm.mit.edu:800X`, where `X` is
the number of the challenge (starting from 1). You can interact with the
programs from the command line with `netcat` (`echo "input" | nc
lox.xvm.mit.edu 8001`) or `telnet` (`telnet lox.xvm.mit.edu 8001`). From a
python script, you may find the following useful:

* `from pwn import *` - import all the `pwn` modules
* `s = remote('lox.xvm.mit.edu', 8001)` - create a `remote` object
* `remote.sendline()` - send a line of input to the port specified by `remote`
* `remote.readline()` - read a line of input from the port specified by `remote`
* `remote.interactive()` - interact with the port specified by `remote`
directly
* `shellcode = asm(shellcraft.i386.linux.sh())` - save 32-bit shellcode to
`shellcode`
* `addr = p32(0xffaaddee)` - pack a 32-bit address into a python string

Finally here are some notes / tips for the challenges:

* We've provided the binaries (and in some cases the source code) for the four challenges in `./challenges/`.
* For an extra challenge, try to solve them without looking at the source code.
* For each one you're looking for a `flag{}`.
* If you try to run the binaries locally, remember to first create a `flag.txt` file with a dummy flag inside.
* The first two binaries are 64-bit, and the last two are 32-bit.
* The last two binaries are compiled with `-fno-stack-protector -m32 -z execstack`
* ASLR has been turned off on the server.

# Further Reading / Exercises

* [Smashing The Stack For Fun And Profit](http://insecure.org/stf/smashstack.html) - The article that brought buffer overflows to the masses
* [narnia@overthewire](http://overthewire.org/wargames/narnia/) - A war game that teaches the basics of binary exploitation
* [microcorruption](https://microcorruption.com/) - An "embedded security CTF"
