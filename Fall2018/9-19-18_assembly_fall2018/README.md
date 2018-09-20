Notes for Fall 2018 meeting 2, digital logic/hardware/assembly

# Processor Hardware and Assembly
## Miscellaneous Things
* If you weren't sure why there were letters in your numbers: [here](https://www.electronics-tutorials.ws/binary/bin_3.html) is why
* If the logic gate stuff looked interesting but I skipped too many details for it to make sense: [here's](https://whatis.techtarget.com/definition/logic-gate-AND-OR-XOR-NOT-NAND-NOR-and-XNOR) more about that
* If you're already comfortable with x86 and want to know more about bootloaders: check out Appendix B [here](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev10.pdf) (and check out the rest of the book if you're interested in operating systems)
* If you want to skip right to learning the details of an instruction set: ARM is simpler than x86, and [this](https://azeria-labs.com/writing-arm-assembly-part-1/) guide is beginner-friendly and eventually teaches exploitation. ARM is common in smaller/embedded devices and is good to know if you're interested in IoT stuff.
* If you just really want the details of x86: [here's](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf) a quick guide and [here](https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf) is more than you ever wanted to know
* If you are salty that the activity lightly insulted you for doing it at the beginning: my bad, I forgot it said that, and I politely disagree with the challenge author equating "beginner" to "freshman".

## Physical representation of information
In processor-land, all data is expressed as 1s and 0s, which in turn directly correspond to high and low voltages on physical wires. The magic of processor design is hooking wires up in the right way so that as the laws of physics do their thing, what pops out (i.e. the voltages on whatever wires we've defined as our result) is the answer we want, once we interpret those voltages back into information.

## Logic Gates
Logic gates are the building blocks of the processor. (They're made of other, smaller building blocks called MOSFETs, which aren't important right now and are Yet Another 6.004 Thing.) They're a physical implementation of basic logical operations: AND, NOT, NAND, XOR, and so on. Two wires with voltages go in (except NOT, which only has one), and something sensible comes out the one wire on the other end.

True AND True is True <-> 1 AND 1 is 1

True OR  True is True <-> 1 OR  0 is 1

     NOT True is False <-> NOT 1 is 0
     
... and so on.

From logic gates, you can build things like adder units, comparators, switches (multiplexers), and so on. [Here's](https://en.wikipedia.org/wiki/Adder_(electronics)) a good place to start if this is new but you're curious about exactly how to go about combining gates into more complicated logic.

What problems exactly can be solved using hardware like this (or any other kind of hardware)? That's what 6.045 is about.

## How Computation Happens
One piece of information the processor needs to do a calculation is what calculation it should be doing. Different types of processors have slightly different lists of operations that they know how to do, that is, operations that have been physically implemented in their hardware.

### Operations
Somewhere in the processor is a table listing all the operations. For each operation, the table holds what voltages need to be put on what wires to make the right calculation happen--the 1s and 0s that decide the state of switches throughout the processor, determining how information will flow. These voltages correspond to true/false values that might define something like whether the output should be written to memory, or which calculation's result the arithmetic module should pass along. 

The processor actually does a ton of operations in parallel, since it has different hardware for most different calculations (remember, the arrangement of the hardware _is_ the calculation). The arithmetic module may have simultaneously calculated the sum of the operands, one of the operands right- and left-shifted by the other, the comparison of the operands, and so on. The little blob of gates that does addition doesn't know or care whether the processor is actually executing an add instruction. It will take whatever's on its input wires (which could be complete garbage), happily add them, and put the result on its output wires. But those control signals will make sure that that meaningless result will eventually run into a switch that has been set not to let it through.

(The details of how one voltage signal can operate a switch that decides whether or not to let another signal through is a very interesting question, and one that you should ask a semiconductor engineer and not me. Or just treat it as a magical blackbox. Discretion is the better part of valor.)

### Data
So the various calculation units throughout the processor read their inputs, do whatever they're built to do with them, and pass along the result. Where do those inputs come from?

#### Registers
The processor has a bank of registers, each of which is, as you can probably guess, another particular arrangement of logic gates. Registers are interesting because they don't just react instantaneously to whatever signals are on their inputs. They can hold voltages over time. They have incoming control signals that tell them when to change the value they're holding (and steadily outputting). In the context of assembly, a register holds 8 to 64 bits. 

[Here](https://www.allaboutcircuits.com/textbook/digital/chpt-10/s-r-latch/) are [two](https://www.youtube.com/watch?v=bJOrwZ5oqKo) places to start for a more concrete explanation of how they physically work, but you can definitely get by just thinking of a register as a variable holding some value.

The processor has registers for everything from tracking whether it's in [user or kernel mode](https://blog.codinghorror.com/understanding-user-and-kernel-mode/) to doing [floating point](http://fabiensanglard.net/floating_point_visually_explained/) math to tracking whether it's running 16 or 32 or 64-bit code. The ones most commonly seen in assembly are the 8 general-purpose registers: eax, ebx, ecx, edx, esi, edi, ebp, and esp (with slightly different names if you're not in 32-bit land). [Here](https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture) are more details.

#### Memory
Memory is slower than registers, but there's more of it. It acts like a huge lookup table. The processor specifies an address over the wires connecting it to the memory, and the memory sends back the value at that address (or stores what the processor tell it to). [Here's](https://www.explainthatstuff.com/how-computer-memory-works.html) more about how memory works.

When the processor reads in the next instruction, in the form of a string of 1s and 0s, some will be interpreted as the operation and some will specify the operand(s). That same concept of voltages routing each other around applies, and the "operand" pard of the input flips switches so the correct register contents, value from memory, or constant value will be routed into all that calculation hardware as its input.

## Assembly code
So the processor executes code by reading in chunks of bits (in x86, up to 15 bytes per instruction). Assembly language is a human-readable version of these strings of bits. If you want to add a constant to the value in a 16-bit register, it's a lot easier to write `ADD` than remember that this is operation 0x05, and easier to write `esp` than remember that this is register 0x07. 

(We care about making assembly (relatively) understandable because, while you can certainly have a long and prosperous programming career without ever touching it, hand-coded assembly still comes up in contexts like embedded devices, compilers, bootloaders, some parts of the OS, and of course exploits.)

The punchline is that you end up with something like this:

```
	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	leaq	L_.str(%rip), %rdi
	movl	$0, -4(%rbp)
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movl	%ecx, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Hello, World!\n"


.subsections_via_symbols
```
which has a (more or less) 1-to-1 relationship with the actual ones-and-zeroes machine code the processor will read.

The above is the compiled version of this Hello World source code:

```
#include <stdio.h>
int main()
{
   printf("Hello, World!\n");
   return 0;
}
```
(By default [gcc](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html) just goes all the way from source to machine code, but the -S flag will make it stop just a bit short of machine code and give you assembly instead.)

A lot of the assembly above won't mean anything if this is all new, just pay attention to what lines like `movb	$0, %al` and `xorl	%ecx, %ecx` are doing. Those one-letter suffixes like _b_ and _l_ denote the size of the operands.

Some of those details, like prefixing registers with `%` and constants with `$`, depend on the [syntax](https://banisterfiend.wordpress.com/2008/08/17/att-vs-intel-assembly-syntax/) you're using.

[Here's](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf) a quick overview (also linked at the top) of x86.

## A Few More Miscellaneous Things
* [How is all of this synchronized?](https://en.wikipedia.org/wiki/Clock_signal)
* [How do processors run so fast?](https://cs.stanford.edu/people/eroberts/courses/soco/projects/risc/pipelining/index.html)
* [How else do they run so fast?](https://danluu.com/branch-prediction/)
* [That's so complicated, is that safe?](https://spectreattack.com/spectre.pdf)
* [Still, that's really cool.](http://student.mit.edu/catalog/search.cgi?search=6.175&style=verbatim)

## The In-Class Activity
This is a challenge taken from the CSAW '18 qualifying round. Take a look at stage-1.asm. Open a terminal and try `nc rev.chal.csaw.io 9003`. If it works, awesome, it's hopefully self-explanatory from here. 

If your terminal says "command not found", you need to install netcat. Google can help you with this more than I can because I don't know what OS you're using.

If you get a result complaining about nodename/servname, the organizers aren't running their server anymore, so here are the questions they were going to ask you (corresponding to lines marked "Question" in stage-1.asm:

1. What is the value of dh after line 129 executes? (Answer with a one-byte hex value, prefixed with '0x')


2. What is the value of gs after line 145 executes? (Answer with a one-byte hex value, prefixed with '0x')


3. What is the value of si after line 151 executes? (Answer with a two-byte hex value, prefixed with '0x')


4. What is the value of ax after line 169 executes? (Answer with a two-byte hex value, prefixed with '0x')


5. What is the value of ax after line 199 executes for the first time? (Answer with a two-byte hex value, prefixed with '0x')

The answers are in answers.txt.
