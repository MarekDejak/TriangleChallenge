# TriangleChallenge
C code determining if the given triangle is scalene, isosceles or equilateral <br />
Running "gcc triangles.c -o triangles" will compile. The output can be run by ./triangles
<br /><br />
- I have prepared the program for unspecified input by reading the input character by character with fgetc. Each time the number of characters exceeds the chunk size, more memory is allocated. This way an arbitrary number of characters can be processed
- After the input is read with the getString function, the validation is performed in getSide using the strtold function, excluding all non-numeric and incorrect inputs.
- If the input is a number, it is passed to the removeZeroes, where prefix and suffix zeroes are removed.
- Finally, the output is passed to the decideTriangle function, which compares the strings to see if they are the same

I have chosen to use string comparison, as storing the side lengths as numbers limits the amount of digits that can be entered to the length of the long long double. By removing the zeroes I ended up with a unified represenation of each number, so the string comparison always yields the same result for same numbers regardless of the pre and postfix zeroes.
