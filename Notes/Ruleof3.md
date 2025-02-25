*** Rule of three/five
The rule of three is a rule that specify that if a class has the need to implement one among the copy
constructor, the destructor or the copy assignment operator then you will have to ensure that all
of these three are implemented. Such a need typically arise when you have to manually handle
dynamic resources (e.g. memory) and therefore the developer must ensure that this resources is used
properly
The rule of five instead is an extension of the rule of three, saying that in such cases you also have to
define the move constructor and the move assignment operator

