//implementing a general tree in C
//General tree=is a data structure that can have any number of children for each node
#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node **children; //array of pointers to children
    int childCount;//number of children
}Node;

Node* createNode(int data){//function to create a new node
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=data;
    newNode->children=NULL;
    newNode->childCount=0;
    return newNode;
}

//function to add a child to a node
void addChild(Node* parent,Node* child){
    parent->childCount++;
    parent->children=(Node**)realloc(parent->children,parent->childCount*sizeof(Node*));
    parent->children[parent->childCount-1]=child;
}

//function to print the tree(pre-order traversal)
void printTree(Node* root,int level){
    if(root==NULL) return;
    for(int i=0; i<level; i++) printf(" ");
    printf("%d\n",root->data);
    for(int i=0; i<root->childCount; i++){
        printTree(root->children[i],level+1);
    }
}
void freeTree(Node* root) {
    if (!root) return;
    for (int i = 0; i < root->childCount; i++) {
        freeTree(root->children[i]);
    }
    free(root->children); // eliberăm vectorul de pointeri la copii
    free(root);           // eliberăm nodul propriu-zis
}

void deleteNode(Node* parent,int target)
{
    if(!parent || parent->childCount==0) return;

    for(int i=0; i<parent->childCount; i++){
        if(parent->children[i]->data==target){
            freeTree(parent->children[i]);

            for(int j=i; j<parent->childCount-1; j++){
                parent->children[j]=parent->children[j+1];
            }
            parent->childCount--;
            parent->children=(Node**)realloc(parent->children,parent->childCount*sizeof(Node*));
            printf("Nodul %d a fost sters\n",target);
            return;
        }else{
            deleteNode(parent->children[i],target);
        }
    }
}
//functie de cautare
Node* searchNode(Node* root,int valoare){
    if(root==NULL) return NULL;

    if(root->data==valoare)
    return root;

    for(int i=0; i<root->childCount; i++)
    {
        Node* rezultat=searchNode(root->children[i],valoare);
        if(rezultat!=NULL)
            return rezultat;
    }
    return NULL;
}

int height(Node* root)
{
    if(root==NULL)
        return 0;
    int maxHeight=0;
    for(int i=0; i<root->childCount; i++){
        int childHeight=height(root->children[i]);
        if(childHeight>maxHeight)
        maxHeight=childHeight;
    }
    return maxHeight+1;//+1 pentru nodul curent
}

Node* cautaParinte(Node* root,int val){
    if(root==NULL) return NULL;

    for(int i=0; i<root->childCount; i++){
        if(root->children[i]->data==val){
            return root;
        }
        Node* found=cautaParinte(root->children[i],val);
        if(found!=NULL)
            return found;
    }

    return NULL;
}
int main()
{
    Node* root=createNode(1);
    Node* child1=createNode(2);
    Node* child2=createNode(3);
    addChild(root,child1);
    addChild(root,child2);
    addChild(child1,createNode(4));
    addChild(child1,createNode(5));
    addChild(child2,createNode(6));

    printf("General Tree:\n");
    printTree(root,0);

    printf("Stergem nodul cu valoarea 4");
    deleteNode(root,4);
    printTree(root,0);

    int valoareCautata=5;
    Node* gasit=searchNode(root,valoareCautata);

    if(gasit!=NULL)
        printf("Nodul cu valoarea %d a fost gasit.\n",valoareCautata);
    else
        printf("Nodul cu valoarea %d nu a fost gasit.\n",valoareCautata);
    
    printf("Inaltimea arborelui este:%d\n",height(root));

    Node* parinte=cautaParinte(root,valoareCautata);
    if(parinte!=NULL)
        printf("Parintele nodului %d este: %d",valoareCautata,parinte->data);
    else
        printf("Nodul %d nu are parinte\n",valoareCautata);

    return 0;
}
