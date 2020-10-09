[Promotion](https://en.cppreference.com/w/cpp/language/implicit_conversion#Numeric_promotions)
-------------

A promotion is a specific kind of conversion for built-in types that is guaranteed not to change the value.

The type you are promoting to must be able to accurately represent any possible value of the type you are promoting from.

There are two things that are called promotions: 
* **integral promotions** refers to integral types (including bitfields and enums) being converted to "larger" integral types.

* **floating point promotions** promotion is specifically just float to double.

Both types of promotions are subsets of a wider range of conversions.
[Here is a list](https://en.cppreference.com/w/cpp/language/implicit_conversion#Numeric_conversions) of the applicable conversions.


* char -> int: integral promotion
* float -> double: floating point promotion
* int -> char: [narrowing] conversion (not a promotion)
* int -> float: conversion
* const char* -> std::string: conversion
* Foo -> Bar: possibly undefined conversion?
* etc.

[Type conversions](http://www.cplusplus.com/doc/tutorial/typecasting/)
=
Implicit conversion
-
Implicit conversions are automatically performed when a value is copied to a compatible type. For example:
```c++
short a=2000;
int b;
b=a;
```
Implicit conversions with classes
-
In the world of classes, implicit conversions can be controlled by means of three member functions:
* Single-argument constructors: allow implicit conversion from a particular type to initialize an object.
* Assignment operator: allow implicit conversion from a particular type on assignments.
* Type-cast operator: allow implicit conversion to a particular type.

```c++
// implicit conversion of classes:
#include <iostream>
using namespace std;

class A {};

class B {
public:
  // conversion from A (constructor):
  B (const A& x) {}
  // conversion from A (assignment):
  B& operator= (const A& x) {return *this;}
  // conversion to A (type-cast operator)
  operator A() {return A();}
};

int main ()
{
  A foo;
  B bar = foo;    // calls constructor
  bar = foo;      // calls assignment
  foo = bar;      // calls type-cast operator
  return 0;
}
```
Type casting
-
C++ is a strong-typed language. Many conversions, specially those that imply a different interpretation of the value, require an explicit conversion, known in C++ as type-casting. 

There exist two main syntaxes for generic type-casting: 
* functional
* c-like
```c++
double x = 10.3;
int y;
y = int (x);    // functional notation
y = (int) x;    // c-like cast notation 
```

The functionality of these generic forms of type-casting is enough for most needs with fundamental data types. 
However, these operators can be applied indiscriminately on classes and pointers to classes, which can lead to code that -while being syntactically correct- can cause runtime errors.

In order to control these types of conversions between classes, we have four specific casting operators: **dynamic_cast**, **reinterpret_cast**, **static_cast** and **const_cast**.

Dynamic cast
-
Dynamic_cast can only be used with pointers and references to classes (or with void*). Its purpose is to ensure that the result of the type conversion points to a valid complete object of the destination pointer type.

If the cast is successful, dynamic_cast returns a value of type new-type. If the cast fails and new-type is a pointer type, it returns a null pointer of that type. If the cast fails and new-type is a reference type, it throws an exception that matches a handler of type std::bad_cast.

Static cast
-
Static cast can perform conversions between pointers to related classes, not only upcasts (from pointer-to-derived to pointer-to-base), but also downcasts (from pointer-to-base to pointer-to-derived). 
No checks are performed during runtime to guarantee that the object being converted is in fact a full object of the destination type. 
Therefore, **it is up to the programmer** to ensure that the conversion is safe. 

On the other side, it does not incur the overhead of the type-safety checks of dynamic_cast.

Reinterpret cast
-
Reinterpret cast converts any pointer type to any other pointer type, even of unrelated classes. 
The operation result is a simple binary copy of the value from one pointer to the other. All pointer conversions are allowed: neither the content pointed nor the pointer type itself is checked.

```c++
class A { /* ... */ };
class B { /* ... */ };
A * a = new A;
B * b = reinterpret_cast<B*>(a);
```


This code compiles, although it does not make much sense, since now b points to an object of a totally unrelated and likely incompatible class. Dereferencing b is unsafe.

Const cast
-
This type of casting manipulates the constness of the object pointed by a pointer, either to be set or to be removed. For example, in order to pass a const pointer to a function that expects a non-const argument:
```c++
#include <iostream>
using namespace std;

void print (char * str)
{
  cout << str << '\n';
}

int main () {
  const char * c = "sample text";
  print ( const_cast<char *> (c) );
  return 0;
}
```



The example above is guaranteed to work because function print does not write to the pointed object. Note though, that removing the constness of a pointed object to actually write to it causes undefined behavior.
