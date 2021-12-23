//
// Fall 2021 COSE213 Assignment 1
//
// Test Case made by Minseong Bae
//

#include "polynomial.h"
#include <iostream>

int main()
{
	Polynomial f, g, a, b;

	std::cout << "1. CreateTerm Test (1)" << std::endl;

	f.CreateTerm(-3, 0);
	f.CreateTerm(-4, 3);
	f.CreateTerm(2.3, 2);
	
	std::cout << "Terms of f : " << f.Terms() << std::endl; //3
	std::cout << "f = ";
	f.Print(); //f = -4x^3+2.3x^2-3
	
	g.CreateTerm(3, 4);
	g.CreateTerm(-4, 3);
	g.CreateTerm(5, 2);
	g.CreateTerm(-4, 0);

	std::cout << "Terms of g : " << g.Terms() << std::endl; //4
	std::cout << "g = ";
	g.Print(); //g = 3x^4-4x^3+5x^2-4
	
	g.CreateTerm(2, 5); //new term : 2x^5
	g.CreateTerm(0, 3); //deleting x^3
	g.CreateTerm(2, -2); //need to ignore : exp<0
	g.CreateTerm(0, 1); //also need to ignore : new exp but coef is 0
	g.CreateTerm(0, 0); //delete x^0
	g.CreateTerm(1, 2); //change coef : 5 -> 1
	
	std::cout << "g (creating a new term) = ";
	g.Print(); //g = 2x^5 + 3x^4 + x^2
	std::cout << "Terms of new g : " << g.Terms() << std::endl; //3

	std::cout << "2. CreateTerm Test (2) : stress test of capacity" << std::endl;

	for(int i=0;i<10;i++){
		a.CreateTerm(1, i);
	}

	std::cout << "a = ";
	a.Print();
	std::cout << "Term / Capacity of a : " << a.Terms() << " " << a.Capacity() << std::endl;

	a.CreateTerm(1, 10);

	std::cout << "a = ";
	a.Print();
	std::cout << "Term / Capacity of new a : " << a.Terms() << " " << a.Capacity() << std::endl;

	for(int i=0;i<1000;i++){
		b.CreateTerm(i+1, i);
	}

	std::cout << "b = ";
	b.Print();
	std::cout << "Term / Capacity of b : " << b.Terms() << " " << b.Capacity() << std::endl;

	std::cout << "3. copy constructor test" << std::endl;

	std::cout << "3-1) normal copy" << std::endl;

	std::cout << "h (created from f) = ";
	Polynomial h = f;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "3-2) empty copy" << std::endl;

	Polynomial e;
	Polynomial k = e;
	std::cout << "k = ";
	k.Print();
	std::cout << "Term / Capacity of k : " << k.Terms() << " " << k.Capacity() << std::endl;

	std::cout << "4. assignment operator test" << std::endl;

	std::cout << "4-1) normal assignment" << std::endl;

	std::cout << "h (assigned from g) = ";
	h = g;	
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "4-2) empty assignment" << std::endl;

	Polynomial e2;
	e2 = e;

	std::cout << "e2 = ";
	e2.Print();
	std::cout << "Term / Capacity of e2 : " << e2.Terms() << " " << e2.Capacity() << std::endl;

	std::cout << "5. Add test" << std::endl;

	std::cout << "5-1) assignment add (add 4x^3 to g for test temporarily)" << std::endl;
	g.CreateTerm(4, 3);
	std::cout << "f = ";
	f.Print();
	std::cout << "g = ";
	g.Print();
	std::cout << "f + g = ";
	h = f + g;	
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;
	g.CreateTerm(0, 3);

	std::cout << "f + g + g = ";
	h = h + g;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "5-2) copy add" << std::endl;
	std::cout << "(copy) f + g = ";
	Polynomial t1 = f + g;
	t1.Print();
	std::cout << "Term / Capacity of t1 : " << t1.Terms() << " " << t1.Capacity() << std::endl;

	std::cout << "5-3) add empty + polynomial" << std::endl;

	std::cout << "e + f = ";
	h = e + f;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "f + e = ";
	h = f + e;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "5-4) add empty + empty" << std::endl;
	std::cout << "e + e2 = ";
	h = e + e2;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "5-5) add capacity test" << std::endl;

	Polynomial a2;

	for(int i=11;i<22;i++){
		a2.CreateTerm(1, i);
	}

	std::cout << "a + a2 = ";
	h = a + a2;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "a + a2 + a = ";
	h = a + a2 + a;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "6. Subtract test(add -4x^3 to g for test temporarily)" << std::endl;

	std::cout << "6-1) assignment subtract" << std::endl;
	g.CreateTerm(-4, 3);
	std::cout << "f = ";
	f.Print();
	std::cout << "g = ";
	g.Print();
	std::cout << "f - g = ";
	h = f - g;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;
	g.CreateTerm(0, 3);

	std::cout << "f - g - g = ";
	h = h - g;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "6-2) copy subtract" << std::endl;
	std::cout << "(copy) f - g = ";
	Polynomial t2 = f - g;
	t2.Print();
	std::cout << "Term / Capacity of t2 : " << t2.Terms() << " " << t2.Capacity() << std::endl;

	std::cout << "6-3) subtract empty and polynomial" << std::endl;

	std::cout << "e - f = ";
	h = e - f;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;
	std::cout << "f - e = ";
	h = f - e;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "6-4) empty - empty" << std::endl;
	std::cout << "e - e2 = ";
	h = e - e2;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "6-5) subtract capacity test" << std::endl;

	std::cout << "a - a2 = ";
	h = a - a2;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "a - a2 - a2 = ";
	h = a - a2 - a2;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "7. Multiply test" << std::endl;

	std::cout << "7-1) assignment multiply" << std::endl;

	std::cout << "f * g = ";
	h = f * g;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "f * g * g = ";
	h = h * g;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "7-2) copy multiply" << std::endl;

	std::cout << "(copy) f * g = ";
	Polynomial t3 = f * g;
	t3.Print();
	std::cout << "Term / Capacity of t3 : " << t3.Terms() << " " << t3.Capacity() << std::endl;

	std::cout << "7-3) multiply empty and polynomial" << std::endl;

	std::cout << "e * f = ";
	h = e * f;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;
	std::cout << "f * e = ";
	h = f * e;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "7-4) empty * empty" << std::endl;
	std::cout << "e * e2 = ";
	h = e * e2;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "7-5) multiply capacity test" << std::endl;

	std::cout << "a * a = ";
	h = a * a;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "a * a * a = ";
	h = a * a * a;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "**Complex Operation Test**" << std::endl;

	std::cout << "f + g - a = ";
	h = f + g - a;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "f + a * a = ";

	h = f + a * a;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "f * g - a = ";

	h = f * g - a;
	h.Print();
	std::cout << "Term / Capacity of h : " << h.Terms() << " " << h.Capacity() << std::endl;

	std::cout << "8. Equal test" << std::endl;

	if(f == g)
		std::cout << "f and g are same" << std::endl;
	else
		std::cout << "f and g are different" << std::endl;

	h = f;
	if (f == h)
		std::cout << "f and h are same" << std::endl;
	else
		std::cout << "f and h are different" << std::endl;

	Polynomial a3 = a;
	a3.CreateTerm(-1, 0);

	if (a == a3)
		std::cout << "a and a3 are same" << std::endl;
	else
		std::cout << "a and a3 are different" << std::endl;

	if(e == e2)
		std::cout << "e and e2 are same" << std::endl;
	else
		std::cout << "e and e2 are different" << std::endl;

	if (e == f)
		std::cout << "e and f are same" << std::endl;
	else
		std::cout << "e and f are different" << std::endl;

	std::cout << "9. Eval test" << std::endl;
	std::cout << "f(3.5) is " << f.Eval(3.5) << std::endl;
	std::cout << "e(3.5) is " << e.Eval(3.5) << std::endl;

	std::cout << "10. Derivative test" << std::endl;

	std::cout << "10-1) normal" << std::endl;
	Polynomial i = f.Derivative(); 
	std::cout << "Derivative of f = ";
	i.Print();

	std::cout << "10-2) only x^1" << std::endl;
	Polynomial t4;
	t4.CreateTerm(4, 1);

	Polynomial i2 = t4.Derivative();

	std::cout << "Derivative of i2(4x^1) = ";
	i2.Print();

	std::cout << "10-3) only const" << std::endl;
	Polynomial t5;
	t5.CreateTerm(5, 0);

	Polynomial i4 = t5.Derivative();

	std::cout << "Derivative of i4(const : 5) = ";
	i4.Print();

	std::cout << "10-4) empty" << std::endl;

	Polynomial i3 = e.Derivative();
	std::cout << "Derivative of e = ";
	i3.Print();

	return 0;

}
