** General Interview Questions

1. When should you use shared_ptr vs. unique_ptr? List as many considerations as you can.
2. Why should you almost always use make_shared to create an object to be owned by shared_ptrs? Explain.
3. Why should you almost always use make_unique to create an object to be initially owned by a unique_ptr? Explain.
4. What’s the deal with auto_ptr?
https://herbsutter.com/2013/05/29/gotw-89-solution-smart-pointers/

5. What is unit,integration,smoke,regression testing 
6. C++ supports multiple inheritance. What is the “diamond problem” that can occur with multiple inheritance? Give an example.
7. Lambda function
8. how is exception handling done? ex: stack unwinding
9. what is polymorphism
10. different types of casting
11. what is template
12. what is multiple inheritence
13. What is smart pointers and different types of it
14. What is mocking
15. What is the difference between c style array, std::vector and std::list
16. Explain the difference between std::map and std::unordered_map
17. . What is the use of the "override" and "final" keyword ?
18. .What is the importance of "constexpr" ?
19. How to avoid narrowing conversion ?
20. What is Rvalue reference and what do you understand by move semantics ?

** NetApp :

** Program 1:
Alice has invented a new card game to play with Bob. Alice made a deck of cards with random values between 1 and 52.
Bob picks 5 cards. Then, he has to rearrange the cards so that by utilizing the operations plus, minus, or times, the
value of the cards reach Alice's favorite number, 42. More precisely,
find operations such that ((((val1 op1 val2) op2 val3) op3 val4) op4 val5) = 42.

Help Bob by writing a program to determine whether it is possible to reach 42 given 5 card values.

For example, Bob picks 5 cards out of the deck containing 60, 1, 3, 5, and 20. Bob rearranges the cards and supplies
four operations, so that 5 * 20 - 60 + 3 - 1 = 42.

INPUT SAMPLE:

The input consists of five integers on a line, separated by spaces. Each integer V is 0 <= V <= 52.

* 44 6 1 49 47
* 34 1 49 2 21
* 31 38 27 51 18

OUTPUT SAMPLE:

For each test case print a line containing "YES" if it is possible to reach the value 42 according to the rules of the
game, or "NO" otherwise.

* NO
* YES
* NO
"""

** Program 2:
Given a list of numbers and a positive integer k, reverse the elements of the list, k items at a time. If the number of elements is not a multiple of k, then the remaining items in the end should be left as is.
Input:
Your program should read lines from standard input. Each line contains a list of numbers and the number k, separated by a semicolon. The list of numbers are comma delimited.
Output:
Print out the new comma separated list of numbers obtained after reversing.
Test 1
Test Input b
1,2, 3, 4,5;2
Expected Output D
2,1,4,3,5
Test 2
Test Input B
1,2,3,4,5;3
Expected Output D
3,2,1, 4, 5


