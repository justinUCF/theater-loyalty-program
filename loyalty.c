//Justin Gamboa
//Dr. Neslisah Torosdagli
//COP3502C Spring 2024
//Theater Loyalty Program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19

typedef struct customer {
    char name[MAXLEN+1];
    int points;
} customer;

typedef struct treenode {
    customer* cPtr;
    int size;
    struct treenode* left;
    struct treenode* right;
} treenode;

typedef struct BST{
    treenode* root;
    int numOfNodes;
} BST;

customer* initCustomer(char* name, int points);                         //Initialize Customer structure
treenode* initTreeNode(customer* cPtr);                                 //Initialize Tree Node structure
BST*      initBST();                                                    //Initialize Binary Search Tree structure
BST*      insert(BST* binarySearchTree, treenode* node);                //Calls insert algorithm
treenode* insertHelper(treenode* root, treenode* node);                 //Enacts insert algorithm
treenode* search(BST* binarySearchTree, char name[], int operation);    //Search for name and return 
treenode* searchNodeHelper(treenode* root, char name[]);                //Enacts search algorithm for node
treenode* searchParentHelper(treenode* root, char name[]);              //Enacts search algorithem for parent
treenode* findSmallest(treenode* root);                                //Finds smallest node
treenode* delete(BST* binarySearchTree, char name[]);                   //Deletes node in tree

int main(){
    BST* binarySearchTree = initBST();
    insert(binarySearchTree, initTreeNode(initCustomer("Jaocb", 76)));
    insert(binarySearchTree, initTreeNode(initCustomer("Charlie", 98)));
    insert(binarySearchTree, initTreeNode(initCustomer("Zaocb", 45)));

    char name[] = "A";
    treenode* node = search(binarySearchTree, name, 1);
    if(node == NULL){
        printf("Node doesnt exist");
        return 0;
    }
    printf("%s--%d--%d\n", node->cPtr->name, node->cPtr->points, node->size);
    return 0;
}

//Initialize Customer
customer* initCustomer(char name[], int points){
    customer* c = (customer*)malloc(sizeof(customer));
    if(c == NULL) return c;
    strncpy(c->name, name, sizeof(c->name));
    c->points = points;
    return c;
}

//Initialize Tree node
treenode* initTreeNode(customer* cPtr){
    treenode* node = (treenode*)malloc(sizeof(treenode));
    if(node == NULL) return node;
    node->cPtr = cPtr;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//Initialize Binary Search Tree
BST* initBST(){
    BST* binarySearchTree = (BST*)malloc(sizeof(BST));
    if(binarySearchTree != NULL){
        binarySearchTree->root = NULL;
        binarySearchTree->numOfNodes = 0;
    }
    return binarySearchTree;
}

//Insert function implementation
BST* insert(BST* binarySearchTree, treenode* node){
    if(binarySearchTree != NULL && node != NULL){
        binarySearchTree->root = insertHelper(binarySearchTree->root, node);
        binarySearchTree->numOfNodes++;
    }
    return binarySearchTree;
}

treenode* insertHelper(treenode* root, treenode* node){
    if(node == NULL){
        return root;
    }
    if(root == NULL){
        return node;
    }
    if(root->cPtr->name[0] >= node->cPtr->name[0]){
        root->left = insertHelper(root->left, node);
        root->size++;
    }
    else{
        root->right = insertHelper(root->right, node);
        root->size++;
    }
    return root;
}
//Search function implementation
treenode* search(BST* binarySearchTree, char name[], int operation){
    if(binarySearchTree == NULL){
        return NULL;
    }
    switch (operation) {
    case 0:
        return searchNodeHelper(binarySearchTree->root, name);
        break;
    case 1:
        return searchParentHelper(binarySearchTree->root, name);
        break;
    default:
        return NULL;
    }
}

treenode* searchNodeHelper(treenode* root, char name[]){
    if(root == NULL || strcmp(root->cPtr->name, name) == 0){
        return root;
    }
    else if(root->cPtr->name[0] > name[0]){
        return searchNodeHelper(root->left, name);
    }
    else{
        return searchNodeHelper(root->right, name);
    }
}

treenode* searchParentHelper(treenode* root, char name[]){
    if(root == NULL || strcmp(root->left->cPtr->name, name) == 0 || strcmp(root->right->cPtr->name, name) == 0){
        return root;
    }
    else if(root->cPtr->name[0] > name[0]){
        return searchParentHelper(root->left, name);
    }
    else{
        return searchParentHelper(root->right, name);
    }
}

treenode* findSmallest(treenode* root){
    if(root == NULL || root->left == NULL){
        return root;
    }
    else{
        return findSmallest(root->left);
    }
}

//Delete function implementation
treenode* delete(BST* binarySearchTree, char name[]){
    if(binarySearchTree == NULL){
        return NULL;
    }
    treenode* toDelete = search(binarySearchTree, name, 0);
    if(toDelete == NULL) return NULL;
    treenode* parent = search(binarySearchTree, name, 1);

    if(toDelete->left == NULL && toDelete->right == NULL){
        if(parent->left == toDelete){
            parent->left = NULL;
            return toDelete;
        }
        else{
            parent->right = NULL;
            return toDelete;
        }
    }

    if((toDelete->left == NULL && toDelete->right != NULL)){
        if(parent->left == toDelete){
            parent->left = toDelete->right;
            return toDelete;
        }
        else{
            parent->right = toDelete->right;
            return toDelete;
        }
    }
    if((toDelete->right == NULL && toDelete->left != NULL)){
        if(parent->left == toDelete){
            parent->left = toDelete->left;
            return toDelete;
        }
        else{
            parent->right = toDelete->left;
            return toDelete;
        }
    }
    
}