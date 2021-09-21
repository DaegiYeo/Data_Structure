//201727531 여대기 자료구조 두번째 과제입니다.

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
using namespace std;
class Polynomial;
class Term
{
	friend Polynomial;
private:
	float coef;
	int exp;
};
class Polynomial {
public:
	Polynomial();
	//construct the polynomial p(x) = 0;
	Polynomial Add(Polynomial b);
	Polynomial Sub(Polynomial b);
	//return the sum of the polynomials *this and b
	Polynomial Mult(Polynomial b);
	//return the product of the polynomials *this and b
	float Eval(float f);
	//evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();

	friend ostream& operator <<(ostream& os, Polynomial& b);
	friend istream& operator >>(istream& in, Polynomial& b);
	Polynomial operator+(Polynomial& b);
	Polynomial operator-(Polynomial& b);
	Polynomial operator*(Polynomial& b);

private:
	static Term* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};
ostream& operator<<(ostream& os, Polynomial& p) //다항식 출력을 위한 연산자 오버로딩
{
	p.Display();
	return os;
}
istream& operator>>(istream& is, Polynomial& p) // 다항식 입력을 위한 연산자 오버로딩
{
	p.GetData();
	return is;
}
Polynomial Polynomial :: operator+(Polynomial& p) // 다항식 덧셈을 위한 연산자 오버로딩
{
	return Add(p);
}
Polynomial Polynomial :: operator-(Polynomial& p) // 다항식 뺄셈을 위한 연산자 오버로딩
{
	return Sub(p);
}
Polynomial Polynomial :: operator*(Polynomial& p) // 다항식 곱셈을 위한 연산자 오버로딩
{
	return Mult(p);
}
Polynomial::Polynomial()
{
	start = -1;
	finish = -1;
	terms = 0;
}
int Polynomial::Display() {
	int aPos = start;
	for (; aPos <= finish; aPos++) {
		if (termArray[aPos].coef != 0) { // 다항식의 계수가 0이아닌 항만 출력하도록 수정하였습니다.
			cout << termArray[aPos].coef << "x^" << termArray[aPos].exp;
			if ((aPos - finish) != 0)
				cout << " + ";
		}
		
	}
	cout << "\n";
	return 0;
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + free, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
}
int Polynomial::GetData() {
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree Of Polynomial:";
	cin >> degree;
	start = free;
	for (i = degree; i > 0; i--) {
		cout << "Enter coefficient of x^" << i << ":";
		cin >> coef;
		cout << "Enter exponent of x^" << i << ":";
		cin >> expo;
		NewTerm(coef, expo);
	}
	finish = free - 1;
	terms = finish - start + 1;
	return 0;
}
Polynomial Polynomial::Add(Polynomial b)
{
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free;
	while ((aPos <= finish) && (bPos <= b.finish))
		if ((termArray[aPos].exp == b.termArray[bPos].exp))
		{
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp))
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	for (; aPos < finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.finish; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1;
	return c;
}
Polynomial Polynomial::Sub(Polynomial b)
{
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free;
	while ((aPos <= finish) && (bPos <= b.finish))
		if ((termArray[aPos].exp == b.termArray[bPos].exp))
		{
			float t = termArray[aPos].coef - b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp))
		{
			c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	for (; aPos < finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.finish; bPos++)
		c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1;
	return c;
}
Polynomial Polynomial::Mult(Polynomial b)
{
	{
		Polynomial c;
		int aPos = start;
		c.start = free;

		for (; aPos <= finish; aPos++) {
			Polynomial temp;
			
			for (int bPos = b.start; bPos <= b.finish; bPos++)
			{
				float newCoef = termArray[aPos].coef * b.termArray[bPos].coef;  // 계수는 곱
				int newExp = termArray[aPos].exp + b.termArray[bPos].exp;		// 지수는 더해서 새로운 항에
				c.NewTerm(newCoef, newExp);
				c.finish = free - 1;
			}	
		}
		for (int cPos1 = c.start; cPos1 <= c.finish; cPos1++) // 지수가 중복될 때 계수를 합쳐주는 for문
		{
			for (int cPos2 = cPos1+1; cPos2 <= c.finish; cPos2++)
			{
				if ((termArray[cPos1].exp == termArray[cPos2].exp))
				{
					termArray[cPos1].coef =+ termArray[cPos1].coef + termArray[cPos2].coef;
					termArray[cPos2].coef = 0;					
				}
			}
		}
		
		return c;
	}
}
float Polynomial::Eval(float f)
{
	int Pos = start;
	float result = 0;
	for (; Pos <= finish; Pos++) 
	{
		float expSum = 1; 
		for (int i = 0; i < termArray[Pos].exp; i++) // f의 termArray[Pos].exp 승
		{
			expSum *= f;

		}
		result += termArray[Pos].coef * expSum; //result 에 항에 f를 대입한 값을 더해줌
		cout << result<<endl;
	}
	return result;
}

int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

int main(void) {
	int choice;
	Polynomial P1, P2, P3, P4;
	cout << "Instruction:- \nExample:-\nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x) = 5x ^ 3 + 0x ^ 2 + 3x ^ 1 + 0x ^ 0 \n";
	cout << "Enter Polynomial1:-" << endl;
	//P1.GetData();
	cin >> P1;
	cout << "Enter Polynomial2:-" << endl;
	//P2.GetData();
	cin >> P2;
	cout << "Enter Polynomial3:-" << endl;
	cin >> P3;
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Substraction\n3: Multiplication\n0: Exit" << endl;
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1:";
			//P1.Display();
			cout << P1;
			cout << "Polynomial2:";
			//P2.Display();
			cout << P2;
			cout << "Polynomial3:";
			cout << P3;
			P3 = P1 + P2;
			//P3 = P1.Add(P2);
			P4 = P1 + P2 + P3;
			//P4 = P1+P2+P3;
			//P3.Display();
			cout << P4;
			cout << "---------------------------------------- \n";
			break;
		case 2:
			cout << "\n------------- Substraction -------------\n";
			cout << "Polynomial1:";
			//P1.Display();
			cout << P1;
			cout << "Polynomial2:";
			//P2.Display();
			cout << P2;
			//P3.Substract(P1, P2); 학생 구현 실습 대상
			P4 = P1 - P2;
			cout << P4;
			cout << "---------------------------------------- \n";
			break;
		case 3:
			cout << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1:";
			//P1.Display();
			cout << P1;
			cout << "Polynomial2:";
			//P2.Display();
			cout << P2;
			//P3.Multiply(P1, P2);
			P4 = P1 * P2;
			cout << P4;
			cout << "---------------------------------------- \n";
			break;
		case 4: //P2.Eval(5); 학생 구현 실습 대상
			{float Eval = P2.Eval(5);
			cout << Eval;
			}
			break;
		case 0:
			cout << "Good Bye...!!!" << endl;
			exit(0);
		}
	}
	system("pause");
	return 0;
}

