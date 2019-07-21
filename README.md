# CMPLS
CMPLS - Complete the Sequence. 
Pure C project to solve https://www.spoj.com/problems/CMPLS/ problem.

https://en.wikipedia.org/wiki/Difference_engine#Method_of_differences
Sequence of length S must be extrapolated C steps
1: Derive sequence until D != 0
P(n)    -> 1 2 4 7 11 16 22 29 -> D > 0
P'(n)   -> 1 2 3 4  5  6  7    -> D > 0
P''(n)  -> 1 1 1 1  1  1       -> D = 0 ()
P'''(n) -> 0 0 0 0  0          -> D = -1 (can be ignored)

2: Take values last in orders
29 7 1

3: Append all values from back to front. Repeat C times
37 8 1
46 9 1

