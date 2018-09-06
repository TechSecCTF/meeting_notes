# Command Line Workshop (9/18)

## Caveat Emptor
The things we're gonna talk about today are simultaneously *critical* and *mostly uninteresting*. It's not at all clear that you can gain all the knowledge you need just by showing up to this workshop and trying to absorb everything we're gonna throw at you in the next hour. Ideally you'd already know about 50-80% of what we're gonna talk about today. If you don't, take in as much as you can and remember these three things:

* practice doing more and more of your tasks in the command line
* StackOverflow is your friend
* pay attention to how your more experienced friends use the command line and learn from them

## [Command Line Bullshittery](http://www.pgbovine.net/command-line-bullshittery.htm)
* how to get a command line working on windows
    * maybe talk about linux subsystem
* iTerm2 vs Terminal.app
* netcat (vs `nc` vs `ncat`)
    * use `lox.xvm.mit.edu` as an example
    * you can also show off the cool trick that allows you to transfer files between two people:
        * `nc -l 9876 > file.txt`
        * `nc <other ip> 9876 < file.txt`
* command line shortcuts
    * ctrl-e, ctrl-a, middle click, option-left, option-right
    * up-arrow, down-arrow
* locating shit
    * `find`, `locate` 
* file system traversal
    * `pwd`, `ls` (with options), `cd`, `mv`, `copy`
    * `..` vs `.` vs `/` vs `\`
* file manipulation
    * `touch`, `mkdir`, `echo`, `cat`, `<` vs `>` vs `|`
    * `less` and `more`
* permissions
    * `chmod`
* miscellaneous commands
    * `man`, `APROPOS` baby, `zsh`, `z`
    * terminal customization
        * `.bash_profile`, `.bashrc`, 
        * white on black
        * directory coloring
        * for OS X, use option as meta key (in preferences)
        * `history`, reverse-search (ctrl-R), `.bash_history`
* text-editing
    * `nano`
    * `vim`
* ssh
    * get everyone to ssh into athena
    * `scp`, with `-r`
* the internet
    * `curl`, `wget`

## Python scripting
* String operations like slicing, index, 
* List comprehensions, itertools like zip 
* `binascii.unhexlify` and `hexlify`
* `base64.b64decode` and `b64encode`
* `chr` and `ord`, ASCII
* `struct.pack` and `unpack`
* little and big endian 
* Python 3
    * bytes, bytearray
    * strings vs bytestrings (and how to convert between them)
        * .encode() for strings to bytes
        * .decode() for bytes to strings

* Briefly mention virtualenv

## Pwntools
* How to install
* `from pwn import *`
* sockets, remote and process
* pack and unpack

