** Scoped enums Vs Unscoped ones:

Enums or Enumerated type (enumeration) is a user-defined data type that can be assigned some limited values. These values are defined by the programmer at the time of declaring the enumerated type.
C++11 has introduced enum classes (also called scoped enumerations), that makes enumerations both strongly typed and strongly scoped. Class enum doesn’t allow implicit conversion to int, and also doesn’t compare enumerators from different enumerations.
1.Two enumerations cannot share the same names: 
2.No variable can have a name which is already in some enumeration:
3.Enums are not type-safe:
