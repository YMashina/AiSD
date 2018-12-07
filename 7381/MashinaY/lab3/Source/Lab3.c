#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#define STACK_SIZE 100
enum err {err1 = 1, err2, err3, err4};

void error(enum err er, char* str){

	switch (er){
		case 1: printf("\nSequence: %s\nOdd symbols in input\n", str);
		case 2: printf("\nSequence: %s\nx1 and x2 don't match\n", str);
		case 3: printf("\nSequence: %s\nCan't pop from empty stack.\n", str);
		default: printf("\nNo errors besides the listed ones.\n");
	}
}

struct Stack 
{ 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
struct Stack* createStack(unsigned capacity) //create a stack of a certain capacity
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
int isFull(struct Stack* stack) 
{   return stack->top == stack->capacity - 1; } 
  
int isEmpty(struct Stack* stack) 
{   return stack->top == -1;  } 
   
void push(struct Stack* stack, int item) // increases top by 1
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    printf("%c pushed to stack\n", item); 
} 

int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)){ 
      printf("Cannot pop from an empty stack.\n");
        return 0; 
      }
    return stack->array[stack->top--]; 
} 
char peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) {
      printf("Cannot peek an empty stack.\n");
       return 0; 
    }
       
    return stack->array[stack->top]; 
} 

int nooddsymbols(char a){
  if (a!='A'&&a!='B'&&a!='C'&&a!='D'&&a!='\n'&&a!=EOF){
      return 0;
    }
    return 1;
}

int check(struct Stack* , char * , int*, int, int*);
  
int abcd(struct Stack* stack, char * str, int* i, int* er){
	char a;
  	while ((a=getchar())==' ')
  		;
  	if (a==EOF||a=='\n'){ //sequence as A C A is allowed
      if(*i==0){
      printf("Empty sequence\n");
      return 0;}
      if(*i==1){
      printf("Correct\n");
      exit(0);}
    }
    printf("Processing: %c\n", a);
  	if (!nooddsymbols(a)){
  		str[*i]=a;
    	str[(*i)+1]='\0';
    	(*i)++;
  		error(1, str);
      *er = 0;
  		return 0;
  	}
  	if (a=='C'){
  		str[*i]=' ';
  		str[(*i)+1]='C';
  		str[(*i)+2]=' ';
    	str[(*i)+3]='\0';
    	(*i)+=3;
  		if (check(stack, str, i, 0, er))
  		return 1;
    return 0;
  	}
  	str[*i]=a;
    str[(*i)+1]='\0';
    (*i)++;
    push(stack, a);
    printf("on top of stack:%c\n", peek(stack));
    if(!abcd(stack, str, i, er))
      return 0;

    return *er;
}

int check(struct Stack* stack, char * str, int* i, int dflag, int* er){ //checking if x1 matches x2
	char a;
	while ((a=getchar())==' ')
  		;
    if (!nooddsymbols(a)){
      str[*i]=a;
      str[(*i)+1]='\0';
      (*i)++;
      error(1, str);
      *er = 0;
      return 0;
    }
  	printf("on top of stack :%c\n", peek(stack));
    printf("Processing: %c\n", a);
  	if (a==peek(stack)&& a !='D'){ // checking for the ultimate D separator
  		str[*i]=a;
  		str[(*i)+1]='\0';
    	(*i)++;
    	if (!isEmpty(stack))
  			pop(stack);
  		
  		else {
  			error(3,str); 
        *er = 0;     
  			return 0;
  		}

  	}
  	else 
  		if (a !='D'){
  			str[*i]=a;
  			str[(*i)+1]='\0';
    		(*i)++;
  			error(2, str);
        *er = 0;  
  			return 0;
  	}

  	if (a=='D'){
      dflag = 1;
  		str[*i]=' ';
  		str[(*i)+1]='D';
  		str[(*i)+2]=' ';
  		str[(*i)+3]='\0';
    	(*i)+=3;
  		if (isEmpty(stack)&&dflag){
  			abcd(stack, str, i, er);
  		}
  		else {
  			error(2, str);
        *er = 0;
  			return 0;
  		}
  	}
    if (!isEmpty(stack)) 
      if (check(stack, str, i, dflag, er))
        return 1;

      return 1;
}

int main() 
{ 

    struct Stack* stack = createStack(STACK_SIZE); 
    char a;

    char str[100]; int e = 1;
    int i = 0, noerror = abcd(stack, str, &i, &e);
  	
  	if (noerror)
  		printf("\nCorrect\n");
  	else printf("\nNot correct\n");
    return 0; 
} 
