//Justin Gamboa
//Dr. Neslisah Torosdagli
//COP3502C Spring 2024
//Theater Loyalty Program

#include <stdio.h>
#include <stdlib.h>

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

int main(){
    return 0;
}