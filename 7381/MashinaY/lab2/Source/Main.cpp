#include <stdio.h>
#include "L_func.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

using namespace h_list;

typedef struct list{
	char atom;
	struct list* next;
}list;

void push(list** tail_ref, list** head, char new_data) 
{ 
    list* new_node = (list*) malloc(sizeof(list)); 
    new_node->atom = new_data; 
    new_node->next = NULL; 

    if ((*tail_ref)==NULL){
		(*tail_ref) = new_node;
		(*head) = (*tail_ref);
		return;
	}
    (*tail_ref)->next = new_node;
    (*tail_ref)= (*tail_ref)->next;

} 

int count_atoms(lisp L, list** head, list** tl, int count, int* offsetindex){

	count = 0;
	if (isNull(L))
		return 0;
	printf("\nProcessing: ");
	write_lisp(L);
	if(isAtom(L)){
		count++;
		
		push(tl, head, getAtom(L));

		printf("\n%*s'%c'!\n", (*offsetindex)*4, "Found atom: ", (*tl)->atom);

		(*offsetindex)++;
		return count;
	}
	
	printf("\n%*s\n",(*offsetindex)*4,"Didn't find an atom");
	(*offsetindex)++;
    
	count+=count_atoms(L->node.pair.hd, head, tl, count, offsetindex)+count_atoms(L->node.pair.tl, head, tl, count, offsetindex);

	return count;
}

int main(){
	lisp L;
	read_lisp(L);
	if(isNull(L)){
		printf("Empty list.\n");
		return 0;
	}
	int count = 0, offsetindex=0;

	list* l = NULL;
	list* head = l;

	count = count_atoms(L, &head, &l, count, &offsetindex);
	char s[3]="s ";
	if (count==1) {
		s[0]=' '; s[1]='\0';
	}
	printf("\n%d atom%sfound:\n",count, s);
	int n = 1;
	while (head!=NULL){
		printf("%d. atom %c\n", n, head->atom);
		head=head->next;
		n++;
	}

	destroy(L);
	putchar('\n');
	return 0;
}
