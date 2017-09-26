# Christopher Orsini Talk

Contact christopher.orsini@navy.mil if you are interested in learning more about NCWDG.

# Introduction to Reverse Engineering

Reverse engineering is the process of understanding and gaining knowledge from
anything man-made through analysis. You can reverse engineer just about anything:
mechanical devices, electronics, chemical processes; at TechSec, we're mostly
concerned with reverse engineering software.

If you have the source code for a software program, it's usually pretty easy to
understand what it does and how it works, depending on how well documented it is.
However, if you're just provided access to a compiled binary, your task is much
more difficult. In CTFs, reverse engineering challenges often take the form of
"crackmes", which are small programs that are designed to test your reversing skills.
These programs usually take the form of elaborate password-checkers. By reverse
engineering the checking process, you can determine a string that the program
will accept. This string is your flag.

Before we tackle compiled Linux binaries, we thought we'd start with something
a little easier. `challenge.pyc` is a compiled Python program. Reverse it to
determine the flag.

# Solution

The file we're given is a compiled Python program. When run, we see:

```
[09-25-17_python_challenge]> python challenge.pyc
Enter the password: asdfasdfasdf
Nope.
[09-25-17_python_challenge]>
```

Clearly we want to determine the password. Since it's compiled, opening and
reading the file isn't very helpful. It turns out there's an easy way to turn
a compiled Python file back into Python code with a python module called
`uncompyle6`:

```
[09-25-17_python_challenge]> sudo pip install uncompyle6
Collecting uncompyle6
  Downloading uncompyle6-2.11.5.tar.gz (1.4MB)
    100% |████████████████████████████████| 1.4MB 1.2MB/s
Collecting spark-parser<1.7.0,>=1.6.1 (from uncompyle6)
  Downloading spark_parser-1.6.1.tar.gz (134kB)
    100% |████████████████████████████████| 143kB 7.0MB/s
Collecting xdis<3.6.0,>=3.5.5 (from uncompyle6)
  Downloading xdis-3.5.5.tar.gz (126kB)
    100% |████████████████████████████████| 133kB 6.7MB/s
Requirement already satisfied: six in /System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python (from uncompyle6)
Collecting click (from spark-parser<1.7.0,>=1.6.1->uncompyle6)
  Downloading click-6.7-py2.py3-none-any.whl (71kB)
    100% |████████████████████████████████| 71kB 8.4MB/s
Installing collected packages: click, spark-parser, xdis, uncompyle6
  Running setup.py install for spark-parser ... done
  Running setup.py install for xdis ... done
  Running setup.py install for uncompyle6 ... done
Successfully installed click-6.7 spark-parser-1.6.1 uncompyle6-2.11.5 xdis-3.5.5
[09-25-17_python_challenge]> uncompyle6 challenge.pyc > challenge.py
```

The file [challenge.py](challenge.py) contains the source code of the program. I've excerpted the relevant function below:

```python
compare_to = '505b603b8f3ed1e82f8e2e29a3c4a35f886f'

def check_password(s):
    if len(s) < 4:
        return False
    if struct.unpack('<I', s[0:4])[0] != 1734437990:
        return False
    if ord(s[4]) + ord(s[-1]) != 248:
        return False
    if ord(s[4]) * ord(s[-1]) != 15375:
        return False
    if len(s) % 4 != 2:
        return False
    try:
        s = base64.b64decode(s[5:-1])
    except TypeError:
        return False

    random.seed(1234)
    q = ''.join([ chr(ord(c) ^ random.randint(0, 255)) for c in s ])
    return binascii.hexlify(q) == compare_to
```

To understand the function and reverse it, you need to have a good understanding of the different ways of manipulating binary data in python. Specifically you need to know:

* `struct.pack` and `struct.unpack`
* `base64.b64encode` and `base64.b64decode`
* `binascii.hexlify` and `binascii.unhexlify`
* `ord` and `chr`
* `^` (xor)

Read the documentation of these functions to find out what they all do. Once you understand them, finding a password that meets the requirements is as simple as undoing each of the functions. You can read a succint solution script in [solution.py](solution.py).

Some things to keep in mind:
* When we seed `random` with `1234`, we're ensuring that it always produces the same set of numbers regardless of where or when the program is run. All versions of python2 should produce the same set of numbers with that seed.
* Both the challenge and the solution use a [list comprehension](http://www.secnetix.de/olli/Python/list_comprehensions.hawk), a common syntactic construct in python.
* The [XOR operation](https://en.wikipedia.org/wiki/Exclusive_or), `^`, is it's own inverse. Namely: if `a ^ b == c`, then `a ^ c == b`. For this reason, it's a common function used in cryptography.


Running the solution script produces the flag:

```
[09-25-17_python_challenge]> python solution.py
flag{pyth0n+rev3rsing+1s+eaZy}
```

When we pass the flag as our password, the challenge confirms that it's correct:

```
[09-25-17_python_challenge]> python challenge.pyc
Enter the password: flag{pyth0n+rev3rsing+1s+eaZy}
Nice work!
```

Over the next few workshops, we'll be covering the basics of x86 assembly. Reverse engineering challenges written in assembly will be similar in spirit to this one, but with the added challenge of needing to read assembly instead of python.
