# Binary Workshop (Part 2)
In this workshop, we're going to explore a number of useful tools for reverse engineering more complex binaries. 

## gdb
So far, we've only used *static* analysis techniques to reverse engineer
binaries. These techniques allow us to learn about the binary without having to
run it. To perform *dynamic* analysis, we will need to use a debugger, which
will allow us to step through individual instructions, examine memory, and
alter program execution while the program runs.

For this guide we'll use GDB, the Gnu Debugger. This basic yet powerful
debugger can be found on virtually any system, which makes it a good tool to be
familiar with.

# zeller
Run the zeller program to find what day of the week you were born on (or any
other significant event occurred). Just from running zeller, you can get an
idea of what it does, but not the way it does it. ou could easily find the
formula online, but don't do that (yet)! Instead, we'll try to recover the
formula from the binary.

# `disassemble`
Run `gdb zeller` to open zeller from within GDB. You'll get a rather long
welcome message (which can be suppressed with the `-q` flag) and a `(gdb)`
prompt. At this point the `zeller` program has been loaded into memory, but no
commands have been run. You can view the disassembly of zeller's `main()`
function by running `disassemble main` at the gdb prompt. To view it in Intel
syntax rather than AT&T syntax, you must first run `set disassembly-flavor
intel`. Your output will look something like this:

```
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
   0x000000000040080a <+0>:     push   rbp
   0x000000000040080b <+1>:     mov    rbp,rsp
   0x000000000040080e <+4>:     push   rbx
   0x000000000040080f <+5>:     sub    rsp,0x18
   0x0000000000400813 <+9>:     mov    edi,0x400a38
   0x0000000000400818 <+14>:    call   0x400590 <puts@plt>
   0x000000000040081d <+19>:    mov    edi,0x400a60
   0x0000000000400822 <+24>:    call   0x400590 <puts@plt>
   0x0000000000400827 <+29>:    mov    edi,0x400a38
   0x000000000040082c <+34>:    call   0x400590 <puts@plt>
   ...
End of assembler dump.
(gdb)
```

From the disassembly above, we can tell that there are several calls to
`puts()` before any input is even read. We can infer that this is the welcome
banner at the beginning of the program.

# `break`
To actually run the program we first have to set a breakpoint. The syntax is
either `break <function>` or `break *<address>`. Since we want to analyze the
execution of the `main()` function, run `break main`. You can view information
about breakpoints with `info breakpoints`. You can then start the program from
the beginning with the `run` command. If you've already hit a breakpoint, you
can continue to the next breakpoint with the `continue` command.

```
(gdb) break main
Breakpoint 1 at 0x40080e
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040080e <main+4>
(gdb) run
Starting program: /home/devneal/techsec/meeting_notes/03-13-17_binaries_part2/zeller

Breakpoint 1, 0x000000000040080e in main ()
(gdb)
```
# `x` and `display`
The program has just stopped at the start of the `main()` function in `zeller`.
However, there isn't much to indicate it. You can view the contents of the
registers by running `info registers`.

```
(gdb) info registers
rax            0x40080a 4196362
rbx            0x0      0
rcx            0x0      0
rdx            0x7fffffffde88   140737488346760
rsi            0x7fffffffde78   140737488346744
rdi            0x1      1
rbp            0x7fffffffdd90   0x7fffffffdd90
rsp            0x7fffffffdd90   0x7fffffffdd90
r8             0x4009e0 4196832
r9             0x7ffff7de78e0   140737351940320
r10            0x846    2118
r11            0x7ffff7a2e740   140737348036416
r12            0x400610 4195856
r13            0x7fffffffde70   140737488346736
r14            0x0      0
r15            0x0      0
rip            0x40080e 0x40080e <main+4>
eflags         0x246    [ PF ZF IF ]
cs             0x33     51
ss             0x2b     43
ds             0x0      0
es             0x0      0
fs             0x0      0
gs             0x0      0
(gdb)
```

The output shows that `rip` contains the value `0x40080e`. We can view the next
few instructions located at `0x40080e` with the `x` (examine) command. The
syntax for the `x` command is `x/<number><format><size> <address>`. `<number>`
is the number of elements of data you want to view, `<format>` is the way you
want to read them, and `<size>` is the size of one element. `<format>` may be
any of the following:
* `x` - hexadecimal
* `d` - signed decimal
* `u` - unsigned decimal
* `c` - char
* `s` - string
* `t` - binary (two)
* `o` - octal

Similarly, `<size>` may be any of:
* `b` - byte
* `w` - word (4 bytes)
* `g` - giant (8 bytes)

We can also use the syntax `x/<number>i address` to read the memory as assembly
instructions:

```
gdb) x/10i 0x40080e
=> 0x40080e <main+4>:   push   rbx
   0x40080f <main+5>:   sub    rsp,0x18
   0x400813 <main+9>:   mov    edi,0x400a38
   0x400818 <main+14>:  call   0x400590 <puts@plt>
   0x40081d <main+19>:  mov    edi,0x400a60
   0x400822 <main+24>:  call   0x400590 <puts@plt>
   0x400827 <main+29>:  mov    edi,0x400a38
   0x40082c <main+34>:  call   0x400590 <puts@plt>
   0x400831 <main+39>:  mov    edi,0xa
   0x400836 <main+44>:  call   0x400580 <putchar@plt>
(gdb)
```

You could also run `x/10i $rip` to achieve the same result. It would be helpful
to display the next few instructions as we step through the program. This can
be achieved with `display/10i $rip`. In fact, we can continually view any
location in memory with the syntax `display/<number><format> <address>`.

# `nexti` and `stepi`
Now we're ready to begin stepping through the program. The `nexti` instruction
will execute a single assembly instruction, unless that instruction is a
function call, in which case it will step over the call. `stepi` works
similarly, but will step into function calls. Run `nexti` a few times and see
how the output instructions change. You'll also see the `zeller` welcome banner
being printed.

Stop just before one of the calls to `printf()`, like so:

```
(gdb)
0x0000000000400822 in main ()
3: x/10i $rip
=> 0x400822 <main+24>:  call   0x400590 <puts@plt>
   0x400827 <main+29>:  mov    edi,0x400a38
   0x40082c <main+34>:  call   0x400590 <puts@plt>
   0x400831 <main+39>:  mov    edi,0xa
   0x400836 <main+44>:  call   0x400580 <putchar@plt>
   0x40083b <main+49>:  mov    edi,0x400a87
   0x400840 <main+54>:  mov    eax,0x0
   0x400845 <main+59>:  call   0x4005b0 <printf@plt>
   0x40084a <main+64>:  mov    esi,0x601160
   0x40084f <main+69>:  mov    edi,0x400a96
(gdb)
```

## pwntools
pwntools is the de-facto library for CTF challenges. It includes a raft of utilities for communicating with processes, writing exploits, and dealing with various encodings. 

Today we're just going to one part of the pwntools library dealing with interacting with the binary you're reversing. Specifically we're interested in the `pwnlib.tubes` module.

Before we get into the details, we need to install pwntools. Simply follow the instructions listed [here](http://docs.pwntools.com/en/stable/install.html). Let us know if you have any difficulties.

Before pwntools, the only way to interact with remote challenges or local binaries was to use python's socket and subprocess modules respectively. These modules are super difficult to use reliably and the source of much frustration. You would often find that you spent more getting the communication to work than solving the damn challenge.

pwntools' docs are pretty good, so you should just read what it has to say [about its tubes module](http://docs.pwntools.com/en/stable/intro.html#making-connections).

Basically, interacting with a local binary (named `foo.bin` for this example) is as simple as:

```python
from pwn import *

foo = process('foo.bin')
foo.sendline('hello')
x = foo.recvline()
if x == 'goodbye':
    foo.close()
else:
    foo.interactive()
```

The only 3 functions that are really important to remember are `recvline`, `sendline` and `interactive`, and happily these are all pretty self-explanatory and work exactly as you'd expect them to.

In this directory, we've included a copy of the `challenge3` binary from the last workshop, but modified to make it infeasible to complete manually. (If you haven't yet reverse engineered the binary yet, talk to us and we can explain the solution). Your task is to use pwntools to solve this new challenge. (Again, your goal is to get it to print the congratulatory message). The binary is called `automate_me`.

Finally, frequently CTF challenges (particularly in the pwn category) will ask you to interact with a running process on a remote server. Instead of printing out a congratulatory message, it might read the flag from a file on the server and print it out. 

In pwntools, this is as simple as changing `process('foo.bin')` to `remote('foo.challenge.ctf', 1337)`; all the `recvline`'s and `sendline`s should continue to function.

## IDA

## Challenges

# Resources

This was a lot of information. Feel free to go through this entire guide at your own pace, and email us with any questions. If you want an alternate take or extra information on these topics check out these links:

* [RMS's gdb Tutorial](http://www.unknownroad.com/rtfm/gdbtut/gdbtoc.html) - tutorial on gdb from the creator himself
* [pwntools documentation](https://docs.pwntools.com/en/stable/) - the "getting started" section is particularly informative
* [ ] [The IDA Pro Book](https://www.nostarch.com/idapro2.htm) - "the unofficial guide to the world's most popular disassembler". You read this as an e-book online if you're an MIT affiliate at this [link](https://search.ebscohost.com/login.aspx?direct=true&db=cat00916a&AN=mit.002013005&site=eds-live&scope=site&custid=s8978330&authtype=sso) (click "Get this @ MIT").
