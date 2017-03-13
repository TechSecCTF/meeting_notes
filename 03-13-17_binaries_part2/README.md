# Binary Workshop (Part 2)
In this workshop, we're going to explore a number of useful tools for reverse engineering more complex binaries. 

## gdb

## pwntools
pwntools is the de-facto library for CTF challenges. It includes a raft of utilities for communicating with processes, writing exploits, and dealing with various encodings. 

Today we're just going to one part of the pwntools library dealing with interacting with the binary you're reversing. Specifically we're interested in the `pwnlib.tubes` module.

Before we get into the details, we need to install pwntools. Simply follow the isntructions listed [here](http://docs.pwntools.com/en/stable/install.html). Let us know if you have any diffculties.

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

* [RMS's gdb Tutorial](http://www.unknownroad.com/rtfm/gdbtut/gdbtoc.html) - tutorial on gdb from the creater himself
* [pwntools documentation](https://docs.pwntools.com/en/stable/) - the "getting started" section is particularly informative
* [The IDA Pro Book](https://www.nostarch.com/idapro2.htm) - "the unoficial guide to the world's most popular disassembler". You read this as an e-book online if you're an MIT affiliate at this [link](https://search.ebscohost.com/login.aspx?direct=true&db=cat00916a&AN=mit.002013005&site=eds-live&scope=site&custid=s8978330&authtype=sso) (click "Get this @ MIT").