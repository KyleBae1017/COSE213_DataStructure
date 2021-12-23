#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"

Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators

int isp(char o){

	if(o == '#' || o == '(') return 4;
	else if(o == '+' || o == '-') return 3;
	else if(o == '*' || o == '/') return 2;
	else return 1; //unary -

}

int icp(char o){

	if(o == '(') return 0;
	else if(o == '_') return 1; //unary -
	else if(o == '*' || o == '/') return 2;
	else if(o == '+' || o == '-') return 3;
	else return 4;

}

//
// Modify Eval() below to evaluate the given expression
//
double Eval(char* in)
{
	double out = 0;
	
	char buf[1000]; // temp buffer
	char lastToken = '#';

	double operand;
	int i = 0, bi = 0;

	opt.Push('#');

	// 1) change to postfix notation

	char * post_expression = new char[strlen(in) * 2];
	int pi = 0;

	while(in[i] != '\0'){

		char c = in[i];

		// Operators
		if(c == '+' || c == '-' ||
		   c == '*' || c == '/' ||
		   c == '(' || c == ')'){

			if(bi > 0){

				buf[bi++] = '\0';
				
				for(int idx=0;buf[idx];idx++){
					post_expression[pi++] = buf[idx];
				}

				post_expression[pi++] = '$';

				bi = 0;
			}
			
			if(c == ')'){
				for(;opt.Top()!='(';opt.Pop()){
					post_expression[pi++] = opt.Top();
				}
				opt.Pop();
			}

			else if(c == '-'){
				
				//unary minus -> replace to '_'
				
				int f_idx = (i == 0) ? 0 : i-1; //idx of first character before - except spaces
				while(in[f_idx] == ' ' && f_idx >= 0) f_idx--;
				
				std::cout << f_idx << std::endl;

				if(f_idx < 0 || in[f_idx] == '*' || in[f_idx] == '-' || 
					in[f_idx] == '/' || in[f_idx] == '+' ||
					in[f_idx] == '(') {
					std::cout << "checked" << std::endl;
					for(;isp(opt.Top()) <= icp('_');opt.Pop()){
						post_expression[pi++] = opt.Top();
					}
					opt.Push('_'); 
				}

				else{
					for(;isp(opt.Top()) <= icp(c);opt.Pop()){
						post_expression[pi++] = opt.Top();
					}
					opt.Push(c); 
				}
			}

			else{
				for(;isp(opt.Top()) <= icp(c);opt.Pop()){
					post_expression[pi++] = opt.Top();
				}
				opt.Push(c);
			}
		}

		// Operands
		else if(c == '0' || c == '1' ||
				c == '2' || c == '3' ||
				c == '4' || c == '5' ||
				c == '6' || c == '7' ||
				c == '8' || c == '9' ||
				c == '.'){
			buf[bi++] = c;
		}
	
		i++;
		
	}
	
	// push the very last operand if exists
	if(bi > 0){
		buf[bi++] = '\0';

		for(int idx=0;buf[idx];idx++){
			post_expression[pi++] = buf[idx];
		}

		post_expression[pi++] = '$';

		bi = 0;
	}

	while(!opt.IsEmpty()){
		post_expression[pi++] = opt.Top();
		opt.Pop();
	}

	std::cout << post_expression << std::endl;

	//2. calculate with postfix notation

	bi = i = 0;

	while(post_expression[i] != lastToken){

		char token = post_expression[i];

		if(token == '_'){ //unary minus
			double tmp = opr.Top();
			opr.Pop();
			opr.Push(tmp * (-1));
		}

		else if(token == '+' || token == '-' ||
		   		token == '*' || token == '/'){ //operator

			double d1 = opr.Top();
			opr.Pop();
			double d2 = opr.Top();
			opr.Pop();
			
			if(token == '+') opr.Push(d2 + d1);
			else if(token == '*') opr.Push(d2 * d1);
			else if(token == '/') opr.Push(d2 / d1);
			else if(token == '-') opr.Push(d2 - d1);

		}

		else if(token == '$'){ //sign for numbers

			if(bi > 0){
				buf[bi++] = '\0';
				operand = atof(buf);
				opr.Push(operand);

				bi = 0;
			}

		}

		else{
			buf[bi++] = token;
		}

		i++;

	}

	out = opr.Top();
	opr.Pop();

	delete[] post_expression;

	return out;	
}

#endif
