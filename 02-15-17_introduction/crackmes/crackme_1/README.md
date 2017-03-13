# Solution to `crackme_1`

We first can get some information on the binary using `file`:

```
$ file crackme_1
crackme_1: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.24, BuildID[sha1]=82e0ad760f38fa5792e0b63a270a67fec99b876f, not stripped
```

It looks like it's a 64-bit ELF executable. When we run it on an appropriate machine (athena should work) we see:

```
$ ./crackme_1
Please enter the password!
foobar
Try again!
$
```

We can guess that the program reads a string from standard input, and compares it against a password. If the two strings are different, it tells us to try again and quits.

Assuming nothing tricky is going on, the real password that our input is being compared against must reside somewhere in the executable. Let's find it.

One way to view the contents of an executable is with the `xxd` unix command which shows you a hexdump of the binary:

```
$ xxd crackme_1 | head
0000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............
0000010: 0200 3e00 0100 0000 6005 4000 0000 0000  ..>.....`.@.....
0000020: 4000 0000 0000 0000 9011 0000 0000 0000  @...............
0000030: 0000 0000 4000 3800 0900 4000 1e00 1b00  ....@.8...@.....
0000040: 0600 0000 0500 0000 4000 0000 0000 0000  ........@.......
0000050: 4000 4000 0000 0000 4000 4000 0000 0000  @.@.....@.@.....
0000060: f801 0000 0000 0000 f801 0000 0000 0000  ................
0000070: 0800 0000 0000 0000 0300 0000 0400 0000  ................
0000080: 3802 0000 0000 0000 3802 4000 0000 0000  8.......8.@.....
0000090: 3802 4000 0000 0000 1c00 0000 0000 0000  8.@.............
$
```

If we go through the entire hexdump we can pretty quickly find the relevant string, but there's an even easier path forward: The `strings` command displays all sufficiently long runs of ASCII readable characters in the file. Our password should be somewhere in its output:

```
$ strings crackme_1 | head -20
/lib64/ld-linux-x86-64.so.2
libc.so.6
strncmp
__isoc99_scanf
puts
__stack_chk_fail
__libc_start_main
__gmon_start__
GLIBC_2.7
GLIBC_2.4
GLIBC_2.2.5
UH-X
UH-X
[]A\A]A^A_
Please enter the password!
%25s
TechSec{w0w_much_str1ngz}
Nice work!
Try again!
;*3$"
$
```

The one string that stands out is `TechSec{w0w_much_str1ngz}`. This is indeed the password:

```
$ ./crackme_1
Please enter the password!
TechSec{w0w_much_str1ngz}
Nice work!
$
```

It is also our flag, and the answer to this challenge.
