# Challenge 1

From the disassembly, it looks like this function never really leaves `main`. It first prints out `Guess what number I'm thinking of:` then it calls `scanf` to input a number. 

Next, it compares this number with 0x53 = 83. If it's different, it prints `Nope!` and quits.

Otherwise, it asks for another number. This time it adds it to itself twice and then checks that the result equals 48. Thus, the second number is 16.

Finally, it asks for a third number. It first checks that this number squared equals 121, and then *also* checks that it is less than 10. Thus, this number must be -11.

Entering all three of these numbers produces the congratulatory statement.