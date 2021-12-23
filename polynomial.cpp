#include "polynomial.h"
#include <iostream>
#include <math.h>

//
// Implementation
//

// Copy constructor
Polynomial::Polynomial(const Polynomial& source){

	capacity = source.capacity;
	terms = source.terms;

	termArray = new Term[capacity];

	for(int i=0;i<terms;++i){
		termArray[i].coef = source.GetTerm(i).coef;
		termArray[i].exp = source.GetTerm(i).exp;
	}

}	

// Destructor
Polynomial::~Polynomial(){

	delete[] termArray;

}


Polynomial& Polynomial::operator = (const Polynomial& source){

	if(this != &source){

		delete[] termArray;

		capacity = source.capacity;
		terms = source.terms;

		termArray = new Term[capacity];

		for(int i=0;i<terms;++i){
			termArray[i].exp = source.GetTerm(i).exp;
			termArray[i].coef = source.GetTerm(i).coef;
		}	

	}

	return *this;

}

// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source){

	Polynomial c;
	
	int l = 0, r = 0;
	int l_end = terms-1, r_end = (source.terms)-1;

	float tmp_coef;

	while((l <= l_end) && (r <= r_end)){

		if (GetTerm(l).exp == source.GetTerm(r).exp){

			tmp_coef = GetTerm(l).coef + source.GetTerm(r).coef;
			if(tmp_coef) c.CreateTerm(tmp_coef, GetTerm(l).exp);
			l++; r++;

		}

		else if (GetTerm(l).exp > source.GetTerm(r).exp){

			c.CreateTerm(GetTerm(l).coef, GetTerm(l).exp);
			l++;
		}

		else{

			c.CreateTerm(source.GetTerm(r).coef, source.GetTerm(r).exp);
			r++;

		}

	}

	for(;l<=l_end;l++){
		c.CreateTerm(GetTerm(l).coef, GetTerm(l).exp);
	}
	for(;r<=r_end;r++){
		c.CreateTerm(source.GetTerm(r).coef, source.GetTerm(r).exp);
	}
	
	return c;

}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;

	int l = 0, r = 0;
	int l_end = terms-1, r_end = (source.terms)-1;

	float tmp_coef;

	while((l <= l_end) && (r <= r_end)){

		if (GetTerm(l).exp == source.GetTerm(r).exp){

			tmp_coef = GetTerm(l).coef - source.GetTerm(r).coef;
			if(tmp_coef) c.CreateTerm(tmp_coef, GetTerm(l).exp);
			l++; r++;

		}

		else if (GetTerm(l).exp > source.GetTerm(r).exp){

			c.CreateTerm(GetTerm(l).coef, GetTerm(l).exp);
			l++;

		}

		else{

			c.CreateTerm((-1) * source.GetTerm(r).coef, source.GetTerm(r).exp);
			r++;

		}

	}

	for(;l<=l_end;l++){
		c.CreateTerm(GetTerm(l).coef, GetTerm(l).exp);
	}
	for(;r<=r_end;r++){
		c.CreateTerm((-1) * source.GetTerm(r).coef, source.GetTerm(r).exp);
	}
	
	return c;
	
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
	
	for(int i=0;i<terms;i++){
		for(int j=0;j<source.terms;j++){

			Polynomial tmp;

			tmp.CreateTerm(GetTerm(i).coef * source.GetTerm(j).coef, GetTerm(i).exp + source.GetTerm(j).exp);

			c = c + tmp;

		}
	}
	
	return c;	
}

bool Polynomial::operator == (const Polynomial& right)
{
	bool ret;
	
	if (terms!=right.terms) ret = false;

	else {

		ret = true;

		for(int i=0;i<terms;i++){
			if ((GetTerm(i).exp != right.GetTerm(i).exp) || (GetTerm(i).coef != right.GetTerm(i).coef)){
				ret = false;
				break;
			}
		}

	}
	
	return ret;

}

float Polynomial::Eval(float x)
{
	float ret = 0;
	
	for(int i=0;i<terms;i++){

		ret += GetTerm(i).coef * pow(x, GetTerm(i).exp);

	}
	
	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;

	for(int i=0;i<terms;i++){

		if ((i != terms-1) || (GetTerm(i).exp != 0)){
			c.CreateTerm(GetTerm(i).coef * GetTerm(i).exp, (GetTerm(i).exp) - 1);
		}

	}
	
	return c;	

}

void Polynomial::CreateTerm(const float coef, const int exp){
	
	if(exp < 0) return; //ignore if exp is negative

	//find there is same exp term in polynomial
	//if exists : change coef if coef != 0, remove term if coef == 0

	for(int i=0;i<terms;i++){

		if(GetTerm(i).exp < exp) break;

		else if(exp == GetTerm(i).exp){

			if(coef){
				termArray[i].coef = coef;
				return;
			}
			else{
				for(int j=i+1;j<terms;j++){
					termArray[j-1].coef = GetTerm(j).coef;
					termArray[j-1].exp = GetTerm(j).exp;
				}
				termArray[terms-1].coef = 0;
				termArray[terms-1].exp = 0;
				terms--;
				return;
			}
		}
	}

	if(!coef) return; //coef == 0 -> ignore

	//check if we need more capacity -> double capacity

	if(terms + 1 > capacity){

		Term *tmpArray = new Term[capacity];
		for(int i=0;i<terms;i++){
			tmpArray[i].coef = GetTerm(i).coef;
			tmpArray[i].exp = GetTerm(i).exp;
		}

		delete[] termArray;

		capacity *= 2;

		termArray = new Term[capacity];

		for(int i=0;i<terms;i++){
			termArray[i].coef = tmpArray[i].coef;
			termArray[i].exp = tmpArray[i].exp;
		}

		delete[] tmpArray;

	}

	//add new term

	termArray[terms].coef = coef;
	termArray[terms].exp = exp;

	terms++;

	//sort to descending order (insertion sort)

	for(int i=1;i<terms;i++){

		int e = GetTerm(i).exp;
		float c = GetTerm(i).coef;

		int j = i-1;

		while((j>=0) && (GetTerm(j).exp < e)){
			termArray[j+1].coef = GetTerm(j).coef;
			termArray[j+1].exp = GetTerm(j).exp;
			j--;
		}
		termArray[j+1].exp = e;
		termArray[j+1].coef = c;

	}

}

