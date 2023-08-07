#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree{
	char value;
	struct BinaryTree *left;
	struct BinaryTree *right;	
}BinaryTree;

void add(BinaryTree **iter, char data){
	if(*iter != NULL){
		*iter = malloc(sizeof(BinaryTree));
		*iter -> value = data;
	}
	
	
	
}



int main(void){
	BinaryTree *head = malloc(sizeof(BinaryTree));
	BinaryTree *iter = head;
	char quit = 'n', data;
	int number = 4;
	printf("%4d", number);
	while(quit != 'q'){
		printf("Enter a char = ");
		printf("%c", &data);
		add(&iter, data);
		print(head, 5);
	}
	
	return 0;
}
