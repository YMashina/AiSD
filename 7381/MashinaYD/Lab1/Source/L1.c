/*
13. Построить синтаксический анализатор для понятия скобки. 
скобки::=А | скобка скобки 
скобка::= ( B скобки )
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

int check (char a){
	if (a!=')'&&a!='B'&&a!=' '&&a!='('&&a!='A') {
		return 1;
		}
	return 0;
	}

enum err {err1 = 1, err2, err3, err4};

void error(enum err er, char str[MAX]){
	switch (er){
		case 1: printf("\nSequence: %s: Odd symbols in input\n",str);
		case 2: printf("\nSequence: %s: Missing ')'\n",str);
		case 3: printf("\nSequence: %s: Missing 'B'\n",str);
		case 4: printf("\nSequence: %s: Missing '('\n",str);
		case 5: printf("\nSequence: %s: Extra symbols\n",str);
		default: printf("\nNo other errors\n");
	}
}

int bracket(int offsetindex, char* str, int* chindex);

int brackets(int offsetindex, char* str, int* chindex) {
	printf("%*s\n", 8+offsetindex*4,"BRACKETS");
	offsetindex++;
	char a;
	while (isspace(a=getchar())) //ignoring spaces
		;
	if(a=='\n'||a==EOF){
		ungetc(a,stdin);
		return 0;
	}
	printf("-processing '%c'-\n", a);
	if(strlen(str)+1==MAX){
		printf("More than 100 characters\n");
		return 0;
	}
	if (check(a)) {
	error(1,str);
	return 0;
	}
	if (a=='A'){
		str[*chindex]=a;
		(*chindex)++;
		str[*chindex]='\0';
		return 1;
	} 
	else 
	{
		ungetc(a,stdin);
		if (bracket(offsetindex, str, chindex)){
			if(brackets(offsetindex, str, chindex)){
				return 1;
			}
		}
	}
	return 0;
}
		
int bracket(int offsetindex, char* str, int* chindex){
	printf("%*s\n", 7+offsetindex*4,"BRACKET");
	char a;
	while (isspace(a=getchar()))
		;
	if(a=='\n'||a==EOF){
		ungetc(a,stdin);
		return 0;
	} 
	printf("-processing '%c'-\n", a);
	if (check(a)) {
	error(1,str);
	return 0;
	}
	if(strlen(str)+1==MAX){
		printf("MAX characters reached\n");
		return 0;
	}
	
	if(a=='('){
		str[*chindex]=a;
		(*chindex)++;
		str[*chindex]='\0';
		while (isspace(a=getchar()))
			;
		if(a=='\n'||a==EOF){
			ungetc(a,stdin);
			return 0;
		} 
		printf("-processing '%c'-\n", a);
		if (check(a)) {
		error(1,str);
		return 0;
		}
		if(a=='B'){
		str[*chindex]=a;
		(*chindex)++;
		str[*chindex]='\0';
			if(brackets(offsetindex, str, chindex)){
				while (isspace(a=getchar()))
					;
				if(a=='\n'||a==EOF){
					ungetc(a,stdin);
					return 0;
				} 
				printf("-processing '%c'-\n", a);
				if(a==')'){
					str[*chindex]=a;
					(*chindex)++;
					str[*chindex]='\0';
					return 1;
				}
				else {
					error(2,str);
					return 0;
				}
			}
			
		}
		else {
			error(3,str);
			return 0;
		}
	}
	else {
		error(4,str);
		return 0;
	}
	return 0;
}

int main(){
	char a;
	a=getchar();
	if (a== EOF||a=='\n'){
		printf("Input empty\n");
		return 0;
	}
	else ungetc(a,stdin);
	char* str=(char*)malloc(MAX*sizeof(char));
	str[0]='\0';
	int chindex=0;
	if(brackets(0, str, &chindex)){
		if ((a=getchar())=='\n'||a==EOF){
			printf("\nBrackets\n");
		}
		else {
			error(5,str);
			printf("a='%c'\n", a);
			printf("\nNot brackets\n");
		}
	}
	return 0;
}
