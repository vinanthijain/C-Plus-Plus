## Pointers:

What are Wild Pointers? How can we avoid?
Uninitialized pointers are known as wild pointers because they point to some arbitrary memory location and may cause a program to crash or behave badly.

int main()
{
  int *p;  /* wild pointer */
   /* Some unknown memory location is being corrupted. 
   This should never be done. */
  *p = 12;
}
Please note that if a pointer p points to a known variable then it’s not a wild pointer. In the below program, p is a wild pointer till this points to a.

int main()
{
  int  *p; /* wild pointer */
  int a = 10;
  p = &a;  /* p is not a wild pointer now*/
  *p = 12; /* This is fine. Value of a is changed */
}
If we want pointer to a value (or set of values) without having a variable for the value, we should explicitly allocate memory and put the value in allocated memory.

int main()
{
   int *p = malloc(sizeof(int));
  *p = 12; /* This is fine (assuming malloc doesn't return NULL) */
}


## Difference between pointers and References:

C and C++ support pointers which is different from most of the other programming languages. Other languages including C++, Java, Python, Ruby, Perl and PHP support references.

On the surface, both references and pointers are very similar, both are used to have one variable provide access to another. With both providing lots of same capabilities, it’s often unclear what is different between these different mechanisms. In this article, I will try to illustrate the differences between pointers and references.

Pointers: A pointer is a variable that holds memory address of another variable. A pointer needs to be dereferenced with * operator to access the memory location it points to.

References : A reference variable is an alias, that is, another name for an already existing variable. A reference, like a pointer is also implemented by storing the address of an object.
A reference can be thought of as a constant pointer (not to be confused with a pointer to a constant value!) with automatic indirection, i.e the compiler will apply the * operator for you. 

int i = 3; 

// A pointer to variable i (or stores address of i)
int *ptr = &i; 

// A reference (or alias) for i.
int &ref = i; 
Differences :

Reassignment: A pointer can be re-assigned. This property is useful for implementation of data structures like linked list, tree, etc. See the following examples:
int x = 5;
int y = 6;
int *p;
p =  &x;
p = &y;
On the other hand, a reference cannot be re-assigned, and must be assigned at initialization.

int x = 5;
int y = 6;
int &r = x;
Memory Address: A pointer has its own memory address and size on the stack whereas a reference shares the same memory address (with the original variable) but also takes up some space on the stack. References may be passed to functions, stored in classes, etc. in a manner very similar to pointers.  Pointer is an independent variable and can be assigned NEW address values; whereas a reference, once assigned, can never refer to any new object until the variable goes out of scope.
NULL value: Pointer can be assigned NULL directly, whereas reference cannot. The constraints associated with references (no NULL, no reassignment) ensure that the underlying operations do not run into exception situation.
Indirection: You can have pointers to pointers to pointers offering extra levels of indirection. Whereas references only offer one level of indirection.
Arithmetic operations: Various arithmetic operations can be performed on pointers whereas there is no such thing called Reference Arithmetic.(but you can take the address of an object pointed by a reference and do pointer arithmetics on it as in &obj + 5).)
When to use What

The performances are exactly the same, as references are implemented internally as pointers. But still you can keep some points in your mind to decide when to use what :

Use references
In function parameters and return types.
Use pointers:
To implement data structures like linked list, tree, etc and their algorithms.
Use pointers if  pointer arithmetic or passing NULL-pointer is needed. For example for arrays (Note that array access is implemented using pointer arithmetic).
Quoted in C++ FAQ Lite : Use references when you can, and pointers when you have to. References are usually preferred over pointers whenever you don’t need “reseating”. This usually means that references are most useful in a class’s public interface. References typically appear on the skin of an object, and pointers on the inside.

The exception to the above is where a function’s parameter or return value needs a “sentinel” reference — a reference that does not refer to an object. This is usually best done by returning/taking a pointer, and giving the NULL pointer this special significance (references must always alias objects, not a dereferenced null pointer).

A pointer can be declared as void but a reference can never be void
For example

int a = 10;
void* aa = &a;. //it is valid
void &ar = a; // it is not valid


References are less powerful than pointers
1) Once a reference is created, it cannot be later made to reference another object; it cannot be reseated. This is often done with pointers.
2) References cannot be NULL. Pointers are often made NULL to indicate that they are not pointing to any valid thing.
3) A reference must be initialized when declared. There is no such restriction with pointers

Due to the above limitations, references in C++ cannot be used for implementing data structures like Linked List, Tree, etc. In Java, references don’t have above restrictions, and can be used to implement all data structures. References being more powerful in Java, is the main reason Java doesn’t need pointers.

References are safer and easier to use:
1) Safer: Since references must be initialized, wild references like wild pointers are unlikely to exist. It is still possible to have references that don’t refer to a valid location 
2) Easier to use: References don’t need dereferencing operator to access the value. They can be used like normal variables. ‘&’ operator is needed only at the time of declaration. Also, members of an object reference can be accessed with dot operator (‘.’), unlike pointers where arrow operator (->) is needed to access members.

Together with the above reasons, there are few places like copy constructor argument where pointer cannot be used. Reference must be used pass the argument in copy constructor. Similarly references must be used for overloading some operators like ++.

** Smart Pointers:
A smart pointer is an object that manages the lifetime of another object through a pointer and provides automatic memory management.
    1.std::unique_ptr:
    Ownership: Sole (unique) ownership of the object.
    Transfer of Ownership: Can be transferred using std::move.
    Usage: Suitable for managing resources that should not be shared, ensuring that only one std::unique_ptr can own the object at any time.
    std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>();
    std::unique_ptr<MyClass> ptr2 = std::move(ptr); // Transfer ownership to ptr2

    2.std::shared_ptr:
    Ownership: Shared ownership among multiple std::shared_ptr instances.
    Reference Counting: Uses reference counting to keep track of how many std::shared_ptr instances own the object. The object is destroyed when the last std::shared_ptr owning it is destroyed or reset.
    Usage: Suitable for situations where shared ownership is required, such as in observer patterns or resource pools
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    {
        std::shared_ptr<MyClass> ptr2 = ptr1; // Shared ownership
    } // ptr2 goes out of scope, but the object is not destroyed

    3.std::weak_ptr:
    Ownership: Non-owning reference to an object managed by std::shared_ptr.
    Reference Counting: Does not contribute to the reference count of std::shared_ptr.
    Usage: Suitable for breaking cyclic dependencies and for scenarios where you need a weak reference to an object without extending its lifetime.
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> wptr = ptr1; // Non-owning reference

When you use std::make_shared, a single memory allocation is performed for both the control block (which keeps track of reference counts and other metadata) and the object itself. This reduces the overhead compared to the two separate allocations that occur when using std::shared_ptr with the new keyword
    Exception Safety:
    std::make_shared is exception-safe because the allocation of the control block and the managed object are done in a single step. If an exception occurs during object construction, no memory leak will happen since the allocation is atomic:
    Code Readability and Maintainance:
    std::make_shared is more concise and avoids explicit use of the new keyword, leading to clearer and more maintainable code:

Prefer smart pointers: For automatic memory management, exception safety, clear ownership semantics, improved readability, and standardized support.
    Use raw pointers: For non-owning references or in performance-critical code where you can ensure correct manual management.

