# Cpp-Nimpo-Calculator
This is a Command line Calculator called Nimpo
Currently only support 5 operations

//-------------------Sample run-----------------------//
Nimpo v. 1, an RPN calculator by Barth. Feudong
type:
'help' for a list of commnads
'exit' to end program

help

undo: undo last operation
redo: redo last operation
+: Addion the top and the next element onto the Stack!
-: Substract one number to the Stack!
cos: Replace the first element, x, on the stack with cos(x). x must be in radians

+
Stack must have 2 elements
12

Top element of stack (size = 1):
1:      12

65

Top 2 elements of stack (size = 2):
2:      12
1:      65

45

Top 3 elements of stack (size = 3):
3:      12
2:      65
1:      45

+

Top 2 elements of stack (size = 2):
2:      12
1:      65


Top element of stack (size = 1):
1:      12


Top 2 elements of stack (size = 2):
2:      12
1:      110

-

Top element of stack (size = 1):
1:      12


Stack currently empty.


Top element of stack (size = 1):
1:      -98

21

Top 2 elements of stack (size = 2):
2:      -98
1:      21

+

Top element of stack (size = 1):
1:      -98


Stack currently empty.


Top element of stack (size = 1):
1:      -77

