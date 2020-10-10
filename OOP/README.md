
## Initalizer list
* is not a generalized container like std::vector. It's primary purpose is object initialization.
* is a lightweight proxy object that provides access to an array of objects

**Uniform initialization** is pretty simple: you can initialize practically everything with arguments in curly braces. The compiler then will do just the right thing.

##Overloading

C++ allows you to specify more than one definition for a **function** name or an **operator** in the same scope, which is called **function overloading** and **operator overloading** respectively.

When you call an overloaded **function** or **operator**, the compiler determines the most appropriate definition to use, by comparing the argument types you have used to call the function or operator with the parameter types specified in the definitions. The process of selecting the most appropriate overloaded function or operator is called **[overload resolution](http://cpp.arh.pub.ro/cpp/language/overload_resolution)**.

#### Function Overloading

You can have multiple definitions for the same function name in the same scope. The definition of the function must differ from each other by the types and/or the number of arguments in the argument list. You cannot overload function declarations that differ only by return type.

#### Operators Overloading

You can redefine or overload most of the built-in operators available in C++. Thus, a programmer can use operators with user-defined types as well.

Overloaded operators are functions with special names: the keyword "operator" followed by the symbol for the operator being defined. Like any other function, an overloaded operator has a return type and a parameter list.

## Overriding
**Method overriding** is a language feature that allows a subclass or child class to provide a specific implementation of a method that is already provided by one of its superclasses or parent classes. 

The implementation in the subclass overrides (replaces) the implementation in the superclass by providing a method that has same name, same parameters or signature, and same return type as the method in the parent class.

The version of a method that is executed will be determined by the object that is used to invoke it. 
* If an object of a **parent class** is used to invoke the method, then the version in the parent class will be executed
* If an object of the **subclass** is used to invoke the method, then the version in the child class will be executed.

> **_NOTE :_**   From C++11, similar to Java:
>* A method that is declared **final** in the super class **cannot** be overridden.
>* A method can be **declared override** to make the compiler check that it overrides a method in the base class.

## Stack Unwinding

The process of removing function entries from function call stack at run time is called Stack Unwinding. 


When an exception occurs, the function call stack is linearly searched for the exception handler, and all the entries before the function with exception handler are removed from the function call stack.
> **_Note:_**
>  Exception handling involves **stack unwinding** ***only if*** exception is **not** handled in same function (where it is thrown).

For example, output of the following program is:
```
f3() Start
f2() Start
f1() Start
Caught Exception: 100
f3() End
```
    
```c++
#include <iostream> 

using namespace std; 

// A sample function f1() that throws an int exception 
void f1() throw (int) { 
cout<<"\n f1() Start "; 
throw 100; 
cout<<"\n f1() End "; 
} 

// Another sample function f2() that calls f1() 
void f2() throw (int) { 
cout<<"\n f2() Start "; 
f1(); 
cout<<"\n f2() End "; 
} 

// Another sample function f3() that calls f2() and handles exception thrown by f1() 
void f3() { 
cout<<"\n f3() Start "; 
try { 
	f2(); 
} 
catch(int i) { 
cout<<"\n Caught Exception: "<<i; 
} 
cout<<"\n f3() End"; 
} 

// A driver function to demonstrate Stack Unwinding process 
int main() { 
f3(); 

getchar(); 
return 0; 
} 
```
In the above program, when f1() throws exception, its entry is removed from the function call stack (because it f1() doesn’t contain exception handler for the thrown exception), then next entry in call stack is looked for exception handler. The next entry is f2(). Since f2() also doesn’t have handler, its entry is also removed from function call stack. The next entry in function call stack is f3(). Since f3() contains exception handler, the catch block inside f3() is executed, and finally the code after catch block is executed. Note that the following lines inside f1() and f2() are not executed at all.
> **_Note:_**
>  If there were some local class objects inside the unwinded functions, destructors for those local objects would have been called in Stack Unwinding process.


Encapsulation, Data Abstraction, Polymorphism and Inheritance

# Object-Oriented Programming

Object-oriented programming is a programming paradigm where everything is represented as an object.

A class is a user-defined data type that we can use in our program, and it works as an object constructor, or a "blueprint" for creating objects.
A class holds its own data members and member functions, which can be accessed and used by creating an instance of that class.

An object is an instance of a class.

## Principles 

* **Encapsulation** 
    is the mechanism of hiding of data implementation by restricting access to public methods. 
    Instance variables are kept private and accessor methods are made public to achieve this.
* **Abstraction**.
    Abstract means a concept or an idea which is not associated with any particular instance. 
    Using abstract class/Interface we express the intent of the class rather than the actual implementation. 
    In a way, one class should not know the inner details of another in order to use it, just knowing the interfaces should be good enough.
* **Inheritance** 
    expresses “is-a” and/or “has-a” relationship between two objects. 
    Using inheritance, In derived classes we can reuse the code of existing base classes.
* **Polymorphism**.
    It means one name many forms. It is further of two types — static and dynamic. 
    * **Static polymorphism** is achieved using method overloading
    
    * **Dynamic polymorphism** using method overriding. It is closely related to inheritance. 
    We can write a code that works on the superclass, and it will work with any subclass type as well.
    
####Polymorphism

```c++
class Person {
public:
    virtual void teach(){
      cout << "Person can teach" << endl;
    }
};

class Teacher: public Person{
public:
   virtual void teach() override {
      cout << "Teacher can teach in a school" << endl;
   }
};

int main()
{
    // C++ polymorphism works with 1) virtual functions and 2) pointers / references to objects
    Person person{}; //Person reference and object
    Teacher teacher{};

    Person& another_person{teacher}; //Person reference, Teacher object
    Teacher& another_teacher{teacher}; //Teacher reference and obj.

    person.teach();//output: Person can teach
    teacher.teach();//output: Teacher can teach in a school.

    // Here you can see Teacher object's method is executed even-though the Person reference was used
    another_person.teach();//output: Teacher can teach in a school

    teacher.teach();//output: Teacher can teach in a school
}
```

Pure method