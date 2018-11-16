# Reverse Engineering
## CTF
- solving RE takes time and patience
- Goal: understand program work flow or program logic to get the flag
## High level
Scenario: the source codes are given to us
### How to Tackle
1. find the way to run program properly
2. understand the source code
3. if the source code is obfuscated, find tools to deobfuscated it
    - Example of Hello TechSec obfuscated with [Obfuscator](https://obfuscator.io)
    ```js
        var _0x392a=['Hello\x20TechSec','log'];(function(_0x57a406,_0xbbe3d0){var _0x163691=function(_0x38c1e6){
        while(--_0x38c1e6){_0x57a406['push'](_0x57a406['shift']());}};_0x163691(++_0xbbe3d0);}(_0x392a,0x143));
        var _0x30a8=function(_0x4ef801,_0x29ca7a){_0x4ef801=_0x4ef801-0x0;var _0x32dbe4=_0x392a[_0x4ef801];
        return _0x32dbe4;};function _0x50c9e1(){console[_0x30a8('0x0')](_0x30a8('0x1'));}_0x50c9e1();
    ```

<details><summary>Show original source codes</summary>
<p>

### Different levels of obfuscation

```js
    function greeting() {
      console.log("Hello TechSec");
    }
    greeting();
```

```js
    function c(){console['log']('Hello\x20TechSec');}c();
```

```js
    var a=['log'];(function(c,d){var e=function(f){while(--f){c['push'](c['shift']());}};e(++d);}(a,0x143));
    var b=function(c,d){c=c-0x0;var e=a[c];return e;};function c(){console[b('0x0')]('Hello\x20TechSec');}c();
```
```js
    var a=['Hello\x20TechSec','log'];(function(c,d){var e=function(f){while(--f){c['push'](c['shift']());}};e(++d);
    }(a,0x79));var b=function(c,d){c=c-0x0;var e=a[c];return e;};function c(){console[b('0x0')](b('0x1'));}c();
```

```js
    var _0x392a=['Hello\x20TechSec','log'];(function(_0x57a406,_0xbbe3d0){var _0x163691=function(_0x38c1e6){
    while(--_0x38c1e6){_0x57a406['push'](_0x57a406['shift']());}};_0x163691(++_0xbbe3d0);}(_0x392a,0x143));
    var _0x30a8=function(_0x4ef801,_0x29ca7a){_0x4ef801=_0x4ef801-0x0;var _0x32dbe4=_0x392a[_0x4ef801];
    return _0x32dbe4;};function _0x50c9e1(){console[_0x30a8('0x0')](_0x30a8('0x1'));}_0x50c9e1();
```


</p>
</details>
    
- JS Deobfuscator Tools
    - [JS Nice](http://jsnice.org)
    - [Unminify](https://unminify.com)
### Challenge 1: JS Obfuscation
- Get a flag from this code
- Author: Cattalyya Nuengsigkapian
```
var a=['charCodeAt','length','push'];(function(c,d){var e=function(f){while(--f){c['push'](c['shift']());}};
e(++d);}(a,0x1c9));var b=function(c,d){c=c-0x0;var e=a[c];return e;};function c(){var d=[0x3e,0x16,0x9,0x1b,
0x39,0x16,0x9,0x8,0x2e,0x16,0x25,0x31,0xc,0x6,0x19,0x10,0x2a,0x7,0x3,0x1c,0x4,0x2c,0x20,0x46,0x35,0x3a,0x4e,
0x2c,0x4,0x43,0x1e,0x2c,0x2,0x32,0x18,0x37,0x17];var e=[];for(var f=0x0;f<d[b('0x0')];f++){if(f%0x2==0x0){
e[b('0x1')](d[f]^'j'[b('0x2')](0x0));}else{e[b('0x1')](d[f]^'s'[b('0x2')](0x0));}}}
```
### Challenge 2: Useless Python
- Get a flag from [challenges/useless.py](challenges/useless.py)
- Source: EasyCTF 2017


## Lower level
Scenario: only binary (compiled programs) are given. No source code available.

### Challenge 3: Lucky Number
- Get a flag from this [lucky number Python program](challenges/luckynumber.pyc)
- Author: Cattalyya Nuengsigkapian

### How to Tackle with Easy Challenges
1. Understand file type `file <binary>` and architecture (x86, x86_64)
2. Disassembling or decompiling 
  - `gdb <binary>`
  - `objdump -D <binary>`
3. Run & play around with program + start with Dynamic Analysis
4. If dynamic analysis doesn't work, do Static Analysis - read assembly!


### Analysis
#### Static Analysis
- understand a program without executing it
- read assembly code
#### Dynamic Analysis
- run binary and monitor its behavior with tools such as debugger like GDB and IDA pro.
- see changes of variables and registers while executing each part
- check the flow of a program from one function to the other

### Challenge 4: Practice Challenge
- Give correct inputs to make [the program](challenges/challenge1) output "Congratulations! You win!"
- Author: Rahul Sridhar & Ray Wang, Source: TechSec Meeting FA2017

### Challenge 5: Crackme 0 
> Find a valid key for [crackme_0](challenges/crackme_0). Source code for every function besides decrypt is available at [crackme_0_empty.c](challenges/crackme_0_empty.c)
- Note: Flag is not in CTF{} format
- Source: C2C 2016 (Practice)
`(gdb) set disassembly-flavor intel`

```c
(gdb) disass decrypt
Dump of assembler code for function decrypt:
   0x080484eb <+0>: push   ebp
   0x080484ec <+1>: mov    ebp,esp
   0x080484ee <+3>: sub    esp,0x10
   0x080484f1 <+6>: mov    DWORD PTR [ebp-0x4],0x0
   0x080484f8 <+13>:  jmp    0x8048539 <decrypt+78>
   0x080484fa <+15>:  mov    eax,0xf
   0x080484ff <+20>:  sub    eax,DWORD PTR [ebp-0x4]
   0x08048502 <+23>:  movzx  eax,BYTE PTR [eax+0x8049a97]
   0x08048509 <+30>:  mov    BYTE PTR [ebp-0x5],al
   0x0804850c <+33>:  mov    eax,0xf
   0x08048511 <+38>:  sub    eax,DWORD PTR [ebp-0x4]
   0x08048514 <+41>:  mov    edx,DWORD PTR [ebp-0x4]
   0x08048517 <+44>:  add    edx,0x8049a97
   0x0804851d <+50>:  movzx  edx,BYTE PTR [edx]
   0x08048520 <+53>:  mov    BYTE PTR [eax+0x8049a97],dl
   0x08048526 <+59>:  mov    eax,DWORD PTR [ebp-0x4]
   0x08048529 <+62>:  lea    edx,[eax+0x8049a97]
   0x0804852f <+68>:  movzx  eax,BYTE PTR [ebp-0x5]
   0x08048533 <+72>:  mov    BYTE PTR [edx],al
   0x08048535 <+74>:  add    DWORD PTR [ebp-0x4],0x1
   0x08048539 <+78>:  cmp    DWORD PTR [ebp-0x4],0x7
   0x0804853d <+82>:  jle    0x80484fa <decrypt+15>
   0x0804853f <+84>:  leave
   0x08048540 <+85>:  ret
End of assembler dump.
```

## Assembly Ref
- [x86 Assembly Guide](http://www.cs.virginia.edu/~evans/cs216/guides/x86.html)
- [Function calling convention](https://wiki.osdev.org/Calling_Conventions)
## Tools
### Disassembler
- Objdump
- Binary Ninja
- IDA pro
### Debugger
- GDB
- radare2
