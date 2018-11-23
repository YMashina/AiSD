// Huffman encoding 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#define MAX_HEIGHT 70 

struct HuffNode{ 
    char data; 
    unsigned int frequency; 
    struct HuffNode *left;
    struct HuffNode * right; 
}; 

struct HuffNode* newNode(char data, unsigned int frequency) { 
    struct HuffNode* temp =(struct HuffNode*)malloc(sizeof(struct HuffNode)); 
    temp->left=temp->right=NULL; 
    temp->data=data; 
    temp->frequency=frequency; 
    return temp; 
} 
  
struct MinNode{
    unsigned int current_size;
    unsigned int capacity;
    struct HuffNode **array;
}; 

struct MinNode* createMinNode(unsigned int capacity) { 
    struct MinNode* MinNode=(struct MinNode*)malloc(sizeof(struct MinNode)); 
    MinNode->capacity = capacity;
    MinNode->current_size =0; 
    MinNode->array = (struct HuffNode**)malloc(MinNode->capacity*sizeof(struct HuffNode*)); 
    return MinNode; 
} 

void swap(struct HuffNode** a, struct HuffNode** b){ 
    struct HuffNode* t=*a; 
    *a=*b; 
    *b=t; 
} 

void MinNodeFunc(struct MinNode* MinNode, int idx){ 
    int smallest = idx; 
    int left = 2*idx+1; //index of left child on node index idx
    int right = 2*idx+2; //index of left child on node index idx (layers fillment starting from 0 at the top)
    if (left<MinNode->current_size && MinNode->array[left]->frequency < MinNode->array[smallest]->frequency) 
        smallest = left; 
    if (right < MinNode->current_size && MinNode->array[right]->frequency < MinNode->array[smallest]->frequency) 
        smallest = right; 
    if (smallest != idx) { 
        swap(&MinNode->array[smallest], &MinNode->array[idx]); 
        MinNodeFunc(MinNode, smallest); 
    } 
} 

int check(struct MinNode* MinNode){ 
    return (MinNode->current_size == 1); 
} 
int isLeaf(struct HuffNode* root){ 
    return !(root->left)&&!(root->right); 
} 

struct HuffNode* extractMin(struct MinNode* MinNode) { 
    struct HuffNode* temp = MinNode->array[0]; 
    MinNode->array[0] = MinNode->array[MinNode->current_size-1]; 
    MinNode->current_size--; 
    MinNodeFunc(MinNode, 0); 
    return temp; 
} 

void insertMinNode(struct MinNode* MinNode, struct HuffNode* HuffNode){ 
    MinNode->current_size++; 
    int i=MinNode->current_size-1; 
    while (i && HuffNode->frequency < MinNode->array[(i-1)/2]->frequency) { 
        MinNode->array[i] = MinNode->array[(i-1)/2]; 
        i=(i-1)/2; 
    } 
    MinNode->array[i] = HuffNode; 
} 

void buildMinNode(struct MinNode* MinNode) { 
    int n = MinNode->current_size-1; 
    int i; 
    for (i = (n-1)/2;i>= 0;--i) 
        MinNodeFunc(MinNode, i); 
} 

void printArr(int* arr, int n) { 
    int i; 
    for (i=0; i<n; ++i) 
        printf("%d",  arr[i]); 
    printf("\n"); 
} 

struct MinNode* CBMinNode(char *data, int* frequency, int size){ 
    struct MinNode* MinNode = createMinNode(size); 
    for (int i=0; i<size; ++i) 
        MinNode->array[i] = newNode(data[i], frequency[i]); 
    MinNode->current_size = size; 
    buildMinNode(MinNode); 
    return MinNode; 
} 

struct HuffNode* buildHuffmanTree(char *data, int *frequency, int size){ 
    struct HuffNode *left, *right, *top; 
    struct MinNode* MinNode = CBMinNode(data, frequency, size); 

    while (!check(MinNode)) {  
        left = extractMin(MinNode); 
        right = extractMin(MinNode); 
        top = newNode('$', left->frequency + right->frequency); 
        top->left = left; 
        top->right = right; 
        insertMinNode(MinNode, top); 
    } 
    return extractMin(MinNode); //what remains is the root of the tree
} 
void printCodes(struct HuffNode* root, int *arr, int top){ 
    if (root->left) { 
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
    if (root->right) { 
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
    if (isLeaf(root)) { 
        printf("%c: ", root->data); 
        printArr(arr, top); 
    } 
} 

void HuffmanEncoding(char* data, int* frequency, int size){ 
    struct HuffNode* root = buildHuffmanTree(data, frequency, size); 
    int arr[MAX_HEIGHT], top = 0; 
    printCodes(root, arr, top); 
} 

int main() { 
    char a;
    if((a=getchar())==EOF||a=='\n'){
        printf("Empty input.\n");
        return 0;
    }
    ungetc(a, stdin);
    int size = 0, N = 100, M=100;

    char* arr=(char*)calloc(M,sizeof(char));
    int* frequency=(int*)malloc(sizeof(int)*M);

    int w=0, fr=0, t=0; 
    char* tmp =(char*)calloc(30,sizeof(char));
    char* str=(char*)malloc(sizeof(char)*M);
int flag = 0;
    while ((a=getchar())!=EOF&&a!='\n'){
        if(isalpha(a)){
            arr[w]=a;
            w++; flag =1;
        }
        
        if(isdigit(a))
        {
            tmp[t]=a;
            t++;
            if(!flag){
                printf("Error: some character is absent next to the frequency assignation.\n");
                return 0;
            }
        }
        if(a==' '){
            if(!(*tmp)){
                printf("Error: some character doesn't have a frequency assignation.\n");
                return 0 ;
            }
            frequency[fr]=atoi(tmp);
            t=0; 
            tmp[t]='\0';
            fr++; 
            
            flag=0;
        }
    }

    if(fr<w){
        if(!*(tmp)){
        printf("Error: some character doesn't have a frequency assignation.\n");
        return 0 ;
    }
        frequency[fr]=atoi(tmp);
        fr++;
    }

    size=strlen(arr);
    HuffmanEncoding(arr, frequency, size); 
  
    return 0; 
} 