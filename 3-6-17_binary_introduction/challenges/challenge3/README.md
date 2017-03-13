# Challenge 3

Instead of describing the reverse engineering process in detail, I'll simply outline what the binary does. 

The user is given 5 numbers (the last of which is usually much larger than the former four). Then the binary blocks until it receives 3 numbers from the user. These three numbers encode specific operations: namely 0 encodes addition, 1 encodes subtraction, and 2 encodes multiplication.

Call the three operations entered by the user op1, op2, and op3. Call the five numbers printed by the program a, b, c, d, and e.

If it is true that: (((a op1 b) op2 c) op3 d) = e, another set of five numbers are printed and the process repeats.

After 10 successes, the congratulatory message is printed and the program exits.