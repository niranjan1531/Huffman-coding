#include<stdio.h>
#include<stdlib.h>

int frequency[26];
  
#define MAX_TREE_HT 100 
char arr[26];
int f[26];
  
struct SNode {
    char  data;
    int size;
    struct SNode *next;
}*head=NULL;

struct MinHeapNode { 
    char data; 
    unsigned freq; 
    struct MinHeapNode *left, *right; 
}; 
  
struct MinHeap { 
  
    unsigned size; 
    unsigned capacity; 
    struct MinHeapNode** array; 
}; 
  
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
}

struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
  
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array = (struct MinHeapNode**)malloc(minHeap-> capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
void minHeapify(struct MinHeap* minHeap, int idx) 
  
{ 
  
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
  
int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) 
  
{ 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
  
void buildMinHeap(struct MinHeap* minHeap) 
  
{ 
  
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
  
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 
  
int isLeaf(struct MinHeapNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 
  
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
    int i;
    for (i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode *left, *right, *top; 
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
    while (!isSizeOne(minHeap)) { 
  
        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
  
        top = newNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    } 
  
    return extractMin(minHeap); 
} 
  
void printCodes(struct MinHeapNode* root, int arr[], int top) 
  
{ 
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
    if (isLeaf(root)) { 
  
        printf("\t%c: ", root->data); 
        printArr(arr, top);
        struct SNode* temp;
        temp=(struct SNode*)malloc(sizeof(struct SNode));
        temp->data=root->data;
        temp->size=top;
        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;

        }
        else
        {
            temp->next=head;
            head=temp;
        }

    } 
} 
  
void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode* root 
        = buildHuffmanTree(data, freq, size); 
    int arr[MAX_TREE_HT], top = 0; 
  
    printCodes(root, arr, top); 
}

int search(char c,int size)
{
    int j;
    for(j=0;j<size;j++)
    {
        if(arr[j]==c)
            return(f[j]);
    }
}

int main()
{
    int ch;
    char sf[20];
    FILE* fp;

    printf("Enter the file name :\t");
    gets(sf);
    fp = fopen(sf, "r");
    
 
    for (ch = 0; ch < 26; ch++)
        frequency[ch] = 0;
 
    while (1)
    {
        ch = fgetc(fp);
        if (ch == EOF) break; 

        if ('a' <= ch && ch <= 'z')      
            frequency[ch-'a']++;
        else if ('A' <= ch && ch <= 'Z') 
            frequency[ch-'A']++;
    }

    char a[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z'};  
    int place=0,i;

    for(i=0;i<26;i++)
    {
        if(frequency[i]!=0)
        {
            arr[place]=a[i];
            f[place]=frequency[i];
            place+=1;
        }
    }
  
    int size=0;
    for(i=0;i<26;i++)
    {
        if(frequency[i]!=0)
           size++;
    }
  
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
    printf("The Huffman codes of respective characters are as follows:\n");
    HuffmanCodes(arr, f, size); 
    struct SNode *temp=head;
    int sumh=0,sum=0;
    while(temp!=NULL)
    {
        sumh=sumh+temp->size*search(temp->data,size);
        //printf("\n%c\t%d\t%d",temp->data,temp->size,temp->size*search(temp->data,size));
        temp=temp->next;
    }
    
    for(i=0;i<size;i++)
    {
        sum=sum+f[i];
    }
    
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
    printf("\nThe actual size of file is\t%d bits\n\nThe size of file  after appling huffman encoding is\t%d bits\n",sum*8,sumh);
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
    return 0;
}