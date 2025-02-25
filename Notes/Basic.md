** C Vs C++:
1) In C++, it is a compiler error to call a function before it is declared. But in C, it may compile
2) In C++, it is compiler error to make a normal pointer to point a const variable, but it is allowed in C
3) In C, a void pointer can directly be assigned to some other pointer like int *, char *. But in C++, a void pointer must be explicitly typcasted.
4) const variable in C++ must be initialized but in c it isn’t necessary.
5) This is the worst answer among all, but still a valid answer. We can use one of the C++ specific keywords as variable names. The program won’t compile in C++, but would compiler in C.
4) Return type of malloc() is void *. In C++, we must explicitly typecast return value of malloc() to appropriate type, e.g., “int *p = (int *)malloc(sizeof(int))”. In C, typecasting is not necessary.

** Class Vs Struct:

Class                                                                       Structure

1. Members of a class are private by default.               1. Members of a structure are public by default. 
2. An instance of a class is called an ‘object’.            2. An instance of structure is called the ‘structure variable’.
3. Member classes/structures of a class are private 
by default but not all programming languages have 
this default behavior eg Java etc.                          3. Member classes/structures of a structure are public by default.
4. It is declared using the class keyword.                  4. It is declared using the struct keyword.
5. It is normally used for data abstraction and             5. It is normally used for the grouping of data
further inheritance.                                                        
6. NULL values are possible in Class.                       6. NULL values are not possible.
7. Syntax:

 class class_name{
         data_member;
         member_function;
  };

