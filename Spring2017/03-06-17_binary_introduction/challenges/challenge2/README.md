# Challenge 2

From the disassembly, it looks like this binary asks for a password, read one in using `scanf`, calls the `secret` function, and then calls `strcmp` on the read in string against a constant string in memory.

We first find out what `secret` does. It reads the address of the user-inputted string into `[rbp-0x18]` and initializes `[rbp-0x4]` with 0. Let's call these variables `str` and `i` respectively. Based on the control flow, it looks like this function loops from `i = 0` to `i = 9` inclusive, and then quits. 

We can reasonbly guess that it is looping over the 10 characters of the inputted string. In the body of the loop, it first computes `str + i = &str[i]` and stores this in both `rdx` and `rax`. Then, it stores `str[i]` (the ASCII value of the character) in `rax`, computes `0xffffffdb - rax` and stores the last byte of the result (`al`) back in `rdx` = `str[i]`.

Essentially this function does:

```
for(int i = 0; i <=9; i++) {
    str[i] = (0xffffffdb - str[i]) % 256;
}
return;
```

Once the program returns from `secret`, it compares the transformed string with the string at address `0x400823`. We can find this string using `objdump -s challenge2` and see that it is `wzbwivznvi`.


To finish, we can un-transform this string with a bit of python:

```
Python 2.7.6
>>> ''.join([chr((0xffffffdb - ord(c)) % 256) for c in "wzbwivznvi"])
'daydreamer'
>>> 
```

Thus, the password is `daydreamer`. Entering this password produces the congratulatory message.

It turns out that `0xffffffdb - x` is equal to `'a' + (25 - (x - 'a'))` modulo 256. Thus, this transformation is equivalent to a simple [Atbash](https://en.wikipedia.org/wiki/Atbash) cipher.