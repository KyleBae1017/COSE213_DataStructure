#include "stack.h"
#include "calculator.h"
#include <iostream>

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

// stack & calculator test

int main()
{
	/*
	// Stack test
	Stack<int> s;
	
	
	s.Push(23);
	s.Push(102);
	s.Print();
	printf("--\n");
	
	s.Push(345);
	s.Push(77);
	s.Print();
	printf("--\n");
	
	s.Pop();
	s.Push(678);
	s.Push(91011);
	s.Print();
	printf("--\n");
	
	for(int i=0; i<6; i++)
	{
		try {
			s.Pop();
			std::cout << "Pop() is called" << std::endl;
		}
		catch(const char* message)
		{
			std::cout << message << std::endl;
		}		
	}

	try{
		s.Top();
		std::cout << "Top() is called" << std::endl;
	}
	catch(const char* message){
		std::cout << message << std::endl;
	}
	

	//stress test
	
	Stack<int> s2;

	for(int i=0;i<11;i++){
		s2.Push(i);
	}

	s2.Print();
	
	Stack<int> s3;

	for(int i=0;i<1000;i++){
		s3.Push(i);
	}

	s3.Print();

	*/

	// Calculator test
	
	
	char str1[] = "-10-((-2+(2+4*3))-12) + 122 * (123 + (120+888) - 300)";
	// The correct result is 101372
	double res1 = Eval(str1);
	std::cout << "Result : " << res1 << std::endl;
	
	
	char str2[] = "1.2 + 2.4 + 3.0 * 2";
	// The correct result is 9.6
	double res2 = Eval(str2);
	std::cout << "Result : " << res2 << std::endl;

	char str3[] = "(4+8+4*(8*5*(7*(6*8)+3+(6+(3+7+1*7*5*4)*3)*2*3+5)+6+7*7)*4+2+9*4+7+2*3*(7*6*1*8)+9+8)"; //1974170
	double res3 = Eval(str3);
	std::cout << "Result : " << res3 << std::endl;
	

	char str4[] = "5-2";
	double res4 = Eval(str4);
	std::cout << "Result : " << res4 << std::endl;

	return 0;

}
