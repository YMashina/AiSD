#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

enum err {err1 = 1, err2, err3, err4};

void error(enum err er, char* str){

	switch (er){
		case 1: printf("\nSequence: %s\nOdd symbols in input\n", str);
		case 2: printf("\nSequence: %s\nx1 and x2 don't match\n", str);
		case 3: printf("\nSequence: %s\nCan't pop from empty stack.\n", str);
		default: printf("\nNo errors besides the listed ones.\n");
	}
}

struct StackNode 
{ 
    char data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(char data) 
{ 
    struct StackNode* stackNode = 
              (struct StackNode*) malloc(sizeof(struct StackNode)); 
    stackNode->data = data; 
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode *root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, char data) 
{ 
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode; 
    printf("%c pushed to stack\n", data); 
} 
  
char pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) {
      printf("Cannot pop from an empty stack.\n");
       return 0; 
    }
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    int popped = temp->data; 
    free(temp); 
    printf("popped: %c\n", popped);
    return popped; 
} 
  
char peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) {
      printf("Cannot peek an empty stack.\n");
       return 0; 
    }
       
    return root->data; 
} 

int nooddsymbols(char a){
  if (a!='A'&&a!='B'&&a!='C'&&a!='D'&&a!='\n'&&a!=EOF){
      return 0;
    }
    return 1;
}

int check(struct StackNode* , char * , int*, int, int*);
  
int abcd(struct StackNode* root, char * str, int* i, int* er){
	char a;
  	while ((a=getchar())==' ')
  		;
  	if (a==EOF||a=='\n'){
      printf("Empty sequence\n");
      return 0;
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
  		if (check(root, str, i, 0, er))
  		return 1;
    return 0;
  	}
  	str[*i]=a;
    str[(*i)+1]='\0';
    (*i)++;
    push(&root, a);
    printf("on top of stack:%c\n", peek(root));
    if(!abcd(root, str, i, er))
      return 0;

    return *er;
}

int check(struct StackNode* root, char * str, int* i, int dflag, int* er){
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
  	printf("on top of stack :%c\n", peek(root));
    printf("Processing: %c\n", a);
  	if (a==peek(root)&& a !='D'){
  		str[*i]=a;
  		str[(*i)+1]='\0';
    	(*i)++;
    	if (!isEmpty(root))
  			pop(&root);
  		
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
  		if (isEmpty(root)&&dflag){
  			abcd(root, str, i, er);
  		}
  		else {
  			error(2, str);
        *er = 0;
  			return 0;
  		}
  	}
    if (!isEmpty(root)) 
      if (check(root, str, i, dflag, er))
        return 1;

      return 1;
}

int main() 
{ 
    struct StackNode* root = NULL; 
    char a;

    char str[100]; int e = 1;
    int i = 0, noerror = abcd(root, str, &i, &e);
  	
  	if (noerror)
  		printf("\nCorrect\n");
  	else printf("\nNot correct\n");
    return 0; 
} 