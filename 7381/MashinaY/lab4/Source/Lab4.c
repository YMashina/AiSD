#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define COUNT 10 

typedef char type;

typedef struct binTree
{
	type data;
	struct binTree* sons;
	struct binTree* brothers;
	
}binTree;

binTree* newNode(type data) 
{ 
    binTree* node = (binTree*)malloc(sizeof(binTree)); 
    node->data = data; 
    node->sons = node->brothers = NULL; 
    return (node); 
} 
  
binTree* insertLevelOrder(type arr[], binTree* root, int i, int n) 
{ 
    // Base case for recursion 
    if (i < n) 
    { 
        binTree* temp = newNode(arr[i]);
        root = temp; 

        // insert left child 
        root->sons = insertLevelOrder(arr, 
                   root->sons, 2 * i + 1, n); 
  
        // insert right child 
        root->brothers = insertLevelOrder(arr, 
                  root->brothers, 2 * i + 2, n); 
    } 
    return root; 
} 

void print2DUtil(binTree *root, int space) 
{ 
// Base case 
if (root == NULL) 
return; 

// Increase distance between levels 
space += COUNT; 

// Process right child first 
print2DUtil(root->brothers, space); 

// Print current node after space 
// count 
printf("\n"); 
for (int i = COUNT; i < space; i++) 
printf(" "); 
printf("%c\n", root->data); 

// Process left child 
print2DUtil(root->sons, space); 
if(root&&root->data=='#'&&root->sons&&root->sons->data!='#'&&root->brothers&&root->brothers->data!='#'){ // no child of an empty element can be unempty.
	printf("Error: No child of an empty element can be unempty.\n");
	exit(EXIT_FAILURE);
}
return;
}

void forest(binTree** b, type* c, int i){
	if ((*b)==NULL){
		return;
	}

	if((i)==7) mkdir("forest/", 0700);
	type* c_copy=c;

	c[i] = (*b)->data;
	type backup = c[i];
	c[i+1] = '\0';


    mkdir((c), 0700);

forest(&((*b)->brothers), c_copy, i);

	c[i] = backup;
	(i)++;
	c[i] = '/';
	c[i+1] = '\0';
	(i)++;
	forest(&((*b)->sons), c, i);
	
}

int main(){
	printf("-----------------------------------------------------------\n");
	printf("Input a binary tree in level order.\nTo indicate an empty element, please use '#'.\nIn case of a non-installed 'tree' package,\nhower over the code sourse, decomment lines 132-133,\ntry again and follow terminal instructions.\nComment those lines after the termination of the program.\n");
	printf("-----------------------------------------------------------\n");
	char a;
	int q=0;
	type arr[100]; 
	if((a=getchar())==EOF||a=='\n'){
		printf("Empty input.\n");
		return 0;
	}
	ungetc(a, stdin);

	while ((a=getchar())!='\n'&&a!=EOF){
	arr[q]=a; q++;
	}
	arr[q]='\0';
	int n = strlen(arr);

	binTree* bt = insertLevelOrder(arr, bt, 0, n);

	int N=100;
	type* c =(type*)malloc(sizeof(type)*N);

	strcpy (c, "forest/");

	print2DUtil(bt,0);
	int i = strlen (c);
	
	forest(&bt, c, i);
	//char command[] ="sudo apt-get install tree"; //uncomment if tree isn't installed
	//system(command);							   //
	char command1[] ="tree ./forest";
	system(command1);
	char command2[] ="rm -r forest";
	system(command2);
	//mkdir("kill me/now", 0700);

	return  0;
	
}