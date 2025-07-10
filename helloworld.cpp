#include <iostream>
using namespace std;


void doubleInputNumber() {
    std::cout << "Print function\n";
    std::cout << "Enter an integer: ";
    int num;
	std::cin >> num;
	int doublenum = num * 2; // define a new variable and initialize it with num * 2
	std::cout << "Double that number is: " << doublenum << '\n'; // then print the value of that variable here
}

void assignments() {
	int var1 { 55 };
	std::cout << var1;
}

int main()
{
	//doubleInputNumber();
	assignments();
	return 0;
}

/*Important*/
//  clang++ -std=c++11 helloworld.cpp -o helloworld

/*

type of an object must be known at compile-time, and that type can not be changed without recompiling the program. 

avoid defining multiple variables of the same type in a single statement
int a, b; // correct

// correct and recommended (easier to read)
int a;
double b;

*/