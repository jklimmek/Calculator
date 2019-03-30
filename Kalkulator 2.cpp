#include "stos.h"
#include "dstos.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

#define DOT '.'

double GetNum();
char getOper();
void SkipSpaces();
int isOper( char c );
int isDigit( char c );
int prior( char cOper );
double Eval( char oper, double arg1, double arg2 );
double Calc();

int main()
{
	cout << Calc();

	return 0;
}

double GetNum(){
	char c;
	double res = 0;
	int flag = 0;

	SkipSpaces();

	if (( c = getchar()) == '-' ) {
		flag = 1;
		SkipSpaces();
	}
	else res = res * 10 + ( c - '0' );

	while ( isDigit( c = getchar() ))
		res = res * 10 + ( c - '0' );

	if ( c == DOT ){
		double coef = -0.1;

		while ( isDigit( c = getchar() )){
			res += coef * ( c - '0' );
			coef /= 10;
		}
	}  
	ungetc( c, stdin );
	if ( flag ) res = -res;
	return res;
	//	return (flag) ? -res : res;
}

char getOper(){
	SkipSpaces();
	return getchar();
}

void SkipSpaces(){
	char c;
	while (( c = getchar()) == ' ' );
	ungetc( c, stdin );
}

int isOper( char c ){
	switch ( c ){
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;
	}
	return 0;
}

int isDigit( char c ){

	return ( c >= '0' ) && ( c <= '9' );
}

int prior( char cOper ){
	switch ( cOper ){

	case '(': return 1;
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^': return 4;
	}
	return 0;
}

double Eval( char oper, double arg1, double arg2 ){
	switch ( oper ){
	case '+': return ( arg1 + arg2 );
	case '-': return ( arg1 - arg2 );
	case '*': return ( arg1 * arg2 );
	case '/':	
		if ( fabs( arg2 ) >= 1e-14 ) 
			return arg1 / arg2;
		perror("ERROR: dzielenie przez 0\n");
		break;
	case '^': return pow( arg1, arg2 );
	}
	return 0;
}

double Calc(){

	char c;

	double temp1;
	double temp2;

	Stack* pStack = InitStack();
	dStack* dpStack = dInitStack();

	SkipSpaces();

	while (( c = getchar()) == '(' ) {
		push(c, &pStack);
		SkipSpaces();
	}
	ungetc(c, stdin);

	dpush( GetNum(), &dpStack );

	while ( isOper( c = getOper() )){
		if ( c == ')' ){
			while (( c = pop ( &pStack )) != '(' ){
				temp2 = dpop( &dpStack );
				dpush( Eval( c, dpop(&dpStack), temp2 ), &dpStack );
			}
		}
		else{
			while ( prior( c ) <= prior( top( pStack )) ){
				temp2 = dpop( &dpStack );
				dpush( Eval( pop( &pStack ), dpop(&dpStack), temp2 ), &dpStack );
			}

			SkipSpaces();
			push( c, &pStack );	
			while ( ( c = getchar() ) == '(' )
				push( c, &pStack );
			ungetc( c, stdin );
			dpush( GetNum(), &dpStack );
		}
	}

	while (!isEmpty(pStack)){
		temp2 = dpop(&dpStack);
		temp1 = Eval(pop(&pStack), dpop(&dpStack), temp2);
		dpush(temp1, &dpStack);	
	}
	temp1 = dtop(dpStack);

	RemoveStack(&pStack);
	dRemoveStack(&dpStack);

	return temp1;
}