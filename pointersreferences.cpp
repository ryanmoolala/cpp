#include <iostream>
using namespace std;

int main() {
    // char x {};
    // char& ref { x };

    int x {5};
    cout << x << endl;//basic variable of 5
    cout << &x << endl; //mem addr of 5

    /*
    When following a type name, & denotes an lvalue reference

    unary context in an expression, & is the address-of operator

    binary context in an expression, & is the Bitwise AND operator
    */

    cout << *(&x) << endl; //* means dereferencing here

    /*
    The address-of operator (&) and dereference operator (*) 
    work as opposites: address-of gets the address of an object, 
    and dereference gets the object at an address.
    */
    int* ptr{ &x }; // ptr holds the address of x
    cout << *ptr << endl;
    return 0;
}

//int;  int; a normal int
//int&; int&; an lvalue reference to an int value
//int*; int*; a pointer to an int value (holds the address of an integer value)