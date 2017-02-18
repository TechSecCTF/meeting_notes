# Solution to `crackme_2`

Once again, we can get some information on the binary using `file`:

```
$ file crackme_2
crackme_2: ELF 64-bit LSB  executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=8cd6c8c02cb8f79563e77ad89d1b21a1d025843e, not stripped
$
```

Like `crackme_1`, it's a 64-bit ELF executable. When we run it on an appropriate machine (athena should work) we see:

```
$ ./crackme_2
Please enter the password
foobar
Try again... You can do it!
$
```

So far it looks pretty similar to `crackme_1`. However, this time neither `xxd` nor `strings` seem to show anything useful.

To make more progress, we'll need to see what the program is actually doing. We can use the `objdump` to disassemble the file (convert the raw bytes into assembly instructions):

```
objdump -d crackme_2 > crackme_2.S
```

The `-d` flag stands for "disassemble" and the `> crackme_2.S` saves the disassembled output to a file named `crackme_2.S`.

Reading disassembly can be fairly intimidating; it often helps to start with `main`:

```
00000000004006b2 <main>:
  4006b2:	55                   	push   %rbp
  4006b3:	48 89 e5             	mov    %rsp,%rbp
  4006b6:	48 83 ec 30          	sub    $0x30,%rsp
  4006ba:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4006c1:	00 00
  4006c3:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  4006c7:	31 c0                	xor    %eax,%eax
  4006c9:	bf c4 07 40 00       	mov    $0x4007c4,%edi
  4006ce:	e8 3d fe ff ff       	callq  400510 <puts@plt>
  4006d3:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
  4006d7:	48 89 c6             	mov    %rax,%rsi
  4006da:	bf de 07 40 00       	mov    $0x4007de,%edi
  4006df:	b8 00 00 00 00       	mov    $0x0,%eax
  4006e4:	e8 67 fe ff ff       	callq  400550 <__isoc99_scanf@plt>
  4006e9:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
  4006ed:	48 89 c7             	mov    %rax,%rdi
  4006f0:	e8 58 ff ff ff       	callq  40064d <secret_transform>
  4006f5:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
  4006f9:	ba 1f 00 00 00       	mov    $0x1f,%edx
  4006fe:	48 89 c6             	mov    %rax,%rsi
  400701:	bf 60 10 60 00       	mov    $0x601060,%edi
  400706:	e8 f5 fd ff ff       	callq  400500 <strncmp@plt>
  40070b:	85 c0                	test   %eax,%eax
  40070d:	75 0c                	jne    40071b <main+0x69>
  40070f:	bf e3 07 40 00       	mov    $0x4007e3,%edi
  400714:	e8 f7 fd ff ff       	callq  400510 <puts@plt>
  400719:	eb 0a                	jmp    400725 <main+0x73>
  40071b:	bf 00 08 40 00       	mov    $0x400800,%edi
  400720:	e8 eb fd ff ff       	callq  400510 <puts@plt>
  400725:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  400729:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  400730:	00 00
  400732:	74 05                	je     400739 <main+0x87>
  400734:	e8 e7 fd ff ff       	callq  400520 <__stack_chk_fail@plt>
  400739:	c9                   	leaveq
  40073a:	c3                   	retq   
  40073b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
```

For now, just focus on the `callq` instructions, which simply call other functions. The program first calls `puts` which simply prints a string to standard output. This string is simply `Please enter the password\n`. You can verify this by running `objdump -s crackme_2`.

The next `callq` is to `__isoc99_scanf`. This function simply accepts user input. This function writes the string to the address specified in the `%eax` register. This address is `-0x30(%rbp)`. The next call is very interesting. It's to a function called `secret_transform` and it accepts an argument through the `%rdi` register, which happens to have the address of the string the user supplied. 

We can surmise that this function transforms this string in some way. Then, this new string is compared against a string at address `0x601060` using the `strncmp` function (our next `callq`). This function returns 0 if the strings are identical and a nonzero value otherwise through `%eax`. This function also takes an additional argument in comparison to `strcmp`: the number of characters to compare the two strings up to. This argument is passed through `%rsi` and equals `0x1f`, or 31 in decimal. This suggests that we're interested in a 31-character password.

The remaining logic simply jumps to `0x40071b` if the strings were not equal, where it prints a failure message and then exits. Otherwise, it prints the message `You're getting good at this!`.

Let's take a look at what resides at address `0x601060`:

```
$ objdump -s crackme_2
        .
        .  (more stuff here)
        .
Contents of section .data:
 601050 00000000 00000000 00000000 00000000  ................
 601060 5566656b 586d7090 999f89ef 4ddac850  UfekXmp.....M..P
 601070 ae77bea2 21952282 419fa3d6 18915a    .w..!.".A.....Z 
        .
        .  (more stuff here)
        .
$
```

It starts out with a bunch of ASCII characters, but then it seems to go out of range. The 31 character string, in hex, is: 

```
5566656b586d7090999f89ef4ddac850ae77bea221952282419fa3d618915a
```

We'll come back to it later. Meanwhile, let's take a look at the `secret_transform` function. I've annotated some comments on the right to explain what's going on a little better.

```
000000000040064d <secret_transform>:
  40064d:	55                   	push   %rbp
  40064e:	48 89 e5             	mov    %rsp,%rbp
  400651:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)  // s = user string
  400655:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)   // a = 0
  40065c:	c7 45 f8 01 00 00 00 	movl   $0x1,-0x8(%rbp)   // b = 1
  400663:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)   // c = 0
  40066a:	eb 3d                	jmp    4006a9 <secret_transform+0x5c>
  40066c:	8b 45 fc             	mov    -0x4(%rbp),%eax
  40066f:	48 63 d0             	movslq %eax,%rdx
  400672:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400676:	48 01 c2             	add    %rax,%rdx         // %rdx = &s[i]
  400679:	8b 45 fc             	mov    -0x4(%rbp),%eax
  40067c:	48 63 c8             	movslq %eax,%rcx
  40067f:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400683:	48 01 c8             	add    %rcx,%rax         // %rax = &s[i]
  400686:	0f b6 00             	movzbl (%rax),%eax       // %eax = s[i]
  400689:	89 c1                	mov    %eax,%ecx
  40068b:	8b 45 f8             	mov    -0x8(%rbp),%eax
  40068e:	01 c8                	add    %ecx,%eax         // %eax = s[i] + b
  400690:	88 02                	mov    %al,(%rdx)        // s[i] = s[i] + b
  400692:	8b 45 f4             	mov    -0xc(%rbp),%eax   // %eax = a
  400695:	01 45 f8             	add    %eax,-0x8(%rbp)   // b = b + a
  400698:	8b 45 f4             	mov    -0xc(%rbp),%eax   // %eax = a
  40069b:	8b 55 f8             	mov    -0x8(%rbp),%edx   // %edx = b
  40069e:	29 c2                	sub    %eax,%edx         // %edx = b - a
  4006a0:	89 d0                	mov    %edx,%eax
  4006a2:	89 45 f4             	mov    %eax,-0xc(%rbp)   // a = b - a
  4006a5:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)   // c++
  4006a9:	83 7d fc 1e          	cmpl   $0x1e,-0x4(%rbp)  // c <= 30
  4006ad:	7e bd                	jle    40066c <secret_transform+0x1f>
  4006af:	90                   	nop
  4006b0:	5d                   	pop    %rbp
  4006b1:	c3                   	retq  
```

Recall that the address to the user string was passed through `%rdi`. This is then being moved to `-0x18(%rbp)`. Next there are three `movl` instructions which initialize three stack variables to 0, 1, and 0 respectively. Let's call these variables a, b, and c.

Then, the program jumps all the way down to `0x4006a9`, where it compares `0x1e` to c. If c is less than or equal to `0x1e` = 30, we jump back up to `0x40066c`. Otherwise, we continue and then return out of the function.

From `0x40066c` we execute a bunch of instructions that don't affect the program's control flow, until we reach `0x4006a5` where we increment c by 1, and then redo our comparison check. 

This is a simple loop: we are iterating from c = 0 until c = 30, after which we exit. Since we think our string is 31 characters long, it would make sense that this loop is iterating over one character of our string at a time, transforming it somehow.

If we parse through the loop body instructions carefully, we can determine that it's doing something equivalent to the following pseudocode (where `s` is the user string):

```
s[c] = s[c] + b
b = a + b
a = b - a
```

So essentially what it's doing is computing some sequence of b's, and adding each to each character of our user string. It then compares this transformed string against the string at address `0x601060`. 

We can find out what sequence is being generated with a few lines of python:

```
$ python
Python 2.7.6
>>> a = 0
>>> b = 1
>>> for c in range(31):
...     print(b)
...     b = a + b
...     a = b - a
... 
1
1
2
3
5
8
13
21
34
55
89
144
233
377
610
987
1597
2584
4181
6765
10946
17711
28657
46368
75025
121393
196418
317811
514229
832040
1346269
>>> 
$ 
```

Looks like the Fibonacci sequence. So, all we need to do is subtract the ith Fibonacci number from the ith character of the string at `0x601060` to recover the correct password. This too can be accomplished easily with a few lines of python:


```
$ python
Python 2.7.6
>>> s = "5566656b586d7090999f89ef4ddac850ae77bea221952282419fa3d618915a"
>>> import binascii
>>> s = binascii.unhexlify(s) # turn a hex string into raw characters
>>> s
'UfekXmp\x90\x99\x9f\x89\xefM\xda\xc8P\xaew\xbe\xa2!\x95"\x82A\x9f\xa3\xd6\x18\x91Z'
>>> fibs = [0] * 31
>>> a = 0
>>> b = 1
>>> for c in range(31):
...     fibs[c] = b
...     b = a + b
...     a = b - a
... 
>>> fibs
[1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269]
>>> chars = [ord(char) for char in s] # ord goes from char to ASCII value
>>> offset_chars = [(chars[i] - fibs[i]) % 256 for i in range(31)]
>>> offset_chars
[84, 101, 99, 104, 83, 101, 99, 123, 119, 104, 48, 95, 100, 97, 102, 117, 113, 95, 105, 53, 95, 102, 49, 98, 48, 110, 97, 99, 99, 105, 125]
>>> ''.join([chr(c) for c in offset_chars]) # chr goes from ASCII value to char
'TechSec{wh0_dafuq_i5_f1b0nacci}'
>>> 
```

Recall that we need to modulo the subtraction by 256 because of integer overflow. The subtraction produces the string `TechSec{wh0_dafuq_i5_f1b0nacci}` which we can verify is the correct password and flag:

```
$ ./crackme_2
Please enter the password
TechSec{wh0_dafuq_i5_f1b0nacci}
You're getting good at this!
$ 
```