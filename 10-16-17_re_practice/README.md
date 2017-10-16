# Reverse Engineering Practice

The goal of (most) of these is to figure out how to interact with the binary to get it to print "Congratulations". `add` and `notsorandom` are a little different...

You can also interact with a server, which will spit the challenges back out at you in order... `nc laredo-44.mit.edu`.

Here are some tips:
 * `objdump -d <binary>`
 * start with `main`
 * [x86 instruction set reference](http://www.felixcloutier.com/x86/)
 * [reverse engineering cheatsheet](http://r00ted.com/cheat%20sheet%20reverse%20v6.png)
