# Christopher Orsini Talk

# Introduction to Reverse Engineering

Reverse engineering is the process of understanding and gaining knowledge from
anything man-made through analysis. You can reverse engineer just about anything:
mechanical devices, electronics, chemical processes; at TechSec, we're of course
mostly concerned with reverse engineering software.

If you have the source code for a software program, it's usually pretty easy to
understand what it does and how it works, depending on how well documented it is.
However, if you're just provided access to a compiled binary, your task is much
more difficult. In CTFs, reverse engineering challenges often take the form of
"crackmes", which are small programs that are designed to test your reversing skills.
The program usually takes the form of an elaborate password-checker. By reverse
engineering the checking process, you can determine a string that the program
will accept. This string is usually your flag.

Before we tackle compiled Linux binaries, we thought we'd start with something
a little easier. `challenge.pyc` is a compiled Python program. Reverse it to
determine the flag.
