/*
13. Построить синтаксический анализатор для понятия скобки. 
скобки::=А | скобка скобки 
скобка::= ( B скобки )
*/

#include <stdio.h>
#include <ctype.h>

int check (char a){
	if (a!=')'&&a!='B'&&a!=' ') {
		return 1;
		}
	return 0;
	}

enum err {err1 = 1, err2, err3, err4};

void error(enum err er){
	switch (er){
		case 1: printf("\nOdd symbols in input\n");
		case 2: printf("\nMissing ')'\n");
		case 3: printf("\nMissing 'B'\n");
		case 4: printf("\nMissing '('\n");
		default: printf("\nNo other errors\n");
	}
}

int bracket(int offsetindex, char a);

int brackets(int offsetindex) {
	printf("%*s\n", 8+offsetindex*4,"BRACKETS");
	offsetindex++;
	char a;
	while (isspace(a=getchar())) //ignoring spaces
		;		     //
	if (a== EOF||a=='\n'){
		printf("Input empty\n");
		return 0;
	}
	if (a=='A') return 1;
	else if (a!=')'&&a!='B'&&a!='(') {
		error(1);
		return 0;
	}
	else 
		if (bracket(offsetindex, a))
			if(brackets(offsetindex))
				return 1;
	return 0;
}
		
int bracket(int offsetindex, char a){
	printf("%*s\n", 7+offsetindex*4,"BRACKET"); //7 - length of the word "bracket"
	if(a!='('){
		if (check(a)) {
		error(1);
		return 0;
		}
		while (isspace(a=getchar()))
			;
		if (check(a)) {
		error(1);
		return 0;
	}
	}
	
	if(a=='('){
		while (isspace(a=getchar()))
			;
		if (check(a)) {
		error(1);
		return 0;
		}
		if(a=='B'){
			if(brackets(offsetindex)){
				while (isspace(a=getchar()))
					;
				if(a==')')
					return 1;
				else {
					error(2);
					return 0;
				}
			}
			
		}
		else {
			error(3);
			return 0;
		}
	}
	else {
		error(4);
		return 0;
	}
	return 0;
}

int main(){

	if(brackets(0))
		printf("\nBrackets\n");
	else 
		printf("\nNot brackets\n");
	return 0;
}
