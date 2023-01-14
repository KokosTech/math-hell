#include <iostream>

#include "line.h"

using namespace std;

void vector_methods_list()
{
	cout << " c - constructor with points" << endl
		 << " s - sum of vectors" << endl
		 << " t - times_num - vector times num" << endl
		 << " i - is_colinear - are vectors colinear" << endl
		 << " l - length of vector" << endl
		 << " d - dot_product of vectors" << endl
		 << " a - area of triangle" << endl
		 << " m - multifaceted example" << endl;
}
void lines_methods_list()
{
	cout << " c - constructor with point and vector" << endl
		 << " t - two points constuct a line" << endl
		 << " a - are two lines parallel" << endl
		 << " i - is one  lines orthogonal to the other" << endl
		 << " k - \"kolinearen\"(colinear) vector to the line" << endl
		 << " o - orthogonal vector to the line" << endl
		 << " p - parallel line" << endl
		 << " l - line that is orthogonal" << endl;
}

void vector_constructor();
void vector_sum();
void vector_times();
void vector_is();
void vector_lenght();
void vector_dot();
void vector_area();
void vector_multi();

void line_constuctor(); 
void line_two_points(); 
void line_are_parallel(); 
void line_is_orthogonal(); 
void line_kolinearen(); 
void line_orthogonal(); 
void line_parallel(); 
void line_line();

int main()
{
	char object, method;
	while(true)
	{
		cout << "Input 'v' for testing vectors, 'l' for testing lines, or 'e' for exiting: ";
		cin >> object;
		if(object == 'v')
		{
			cout << "Input wanted class method (type h for list of options): ";
			cin >> method;
			switch(method)
			{
				case 'h': vector_methods_list(); break;
				case 'c': vector_constructor(); break;
				case 's': vector_sum(); break;
				case 't': vector_times(); break;
				case 'i': vector_is(); break;
				case 'l': vector_lenght(); break;
				case 'd': vector_dot(); break;
				case 'a': vector_area(); break;
				case 'm': vector_multi(); break;
				default : cout << "Invalid input, try again." << endl;
			}
		}
		else if(object == 'l')
		{
			cout << "Input wanted class method (type h for list of options): ";
			cin >> method;
			switch(method)
			{
				case 'h': lines_methods_list(); break;
				case 'c': line_constuctor(); break;
				case 't': line_two_points(); break;
				case 'a': line_are_parallel(); break; 
				case 'i': line_is_orthogonal(); break;
				case 'k': line_kolinearen(); break;
				case 'o': line_orthogonal(); break;
				case 'p': line_parallel(); break;
				case 'l': line_line(); break;
				default : cout << "Invalid input, try again." << endl;
			}
		}
		else if(object == 'e') break;
		else cout << "Invalid input, try again." << endl;
	}

	cout << "Bye" << endl;

	return 0;
}

void vector_constructor()
{
	Point p1, p2;
	cin >> p1 >> p2;
	Vector v(p1, p2);
	cout << v << endl;
}
void vector_sum()
{
	Vector v1, v2;
	cin >> v1 >> v2;
	Vector v = v1.sum(v2);
	cout << v << endl;
	cout << v2.sum(v1) << endl;
}
void vector_times()
{
	int k;
	Vector v;
	cin >> k >> v;
	Vector kv = v.times_num(k);
	cout << kv << endl;
}
void vector_is()
{
	Vector v1, v2;
	cin >> v1 >> v2;
	cout << v1.is_colinear(v2) << endl;
}
void vector_lenght()
{
	Vector v;
	cin >> v;
	cout << v.length() << endl;
}
void vector_dot()
{
	Vector v1, v2;
	cin >> v1 >> v2;
	cout << v1.dot_product(v2) << endl;
}

void vector_area()
{
	Vector v1, v2;
	cin >> v1 >> v2;
	cout << area(v1, v2) << endl;
}

void vector_multi()
{
	Vector v1, v2;
	cin >> v1 >> v2;
	Vector v3 = v1.sum(v2.times_num(-1)), // v3 = v1 - v2
	       v4 = v1.times_num(2).sum(v2); // v4 = 2*v1 + v2
	cout << v3 << endl << v4 << endl;
}

void line_constuctor()
{
	Point p;
	Vector v;
	cin >> p >> v;
	Line l(p, v);
	cout << l << endl;
}

void line_two_points()
{
	Point p1, p2;
	cin >> p1 >> p2;
	Line l(p1, p2);
	cout << l << endl;
}

void line_are_parallel()
{
	Line l1, l2;
	cin >> l1 >> l2;
	cout << l1.are_parallel(l2) << endl;
}

void line_is_orthogonal()
{
	Line l1, l2;
	cin >> l1 >> l2;
	cout << l1.is_orthogonal(l2) << endl;
}

void line_kolinearen()
{
	Line l;
	cin >> l;
	cout << l.colinear() << endl;
}

void line_orthogonal()
{
	Line l;
	cin >> l;
	cout << l.orthogonal() << endl;
}

void line_parallel()
{
	Point p;
	Line l;
	cin >> l >> p;
	cout << l.parallel(p) << endl;
} 

void line_line()
{
	Point p;
	Line l;
	cin >> l >> p;
	cout << l.orthogonal(p) << endl;
}