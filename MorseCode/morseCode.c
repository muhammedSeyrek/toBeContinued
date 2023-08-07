#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ekleme yapiliyor ama hedef bulma ve mors alfabesini dokmede sorun var.

typedef struct BinaryTree{
	char value;
	struct BinaryTree *left;
	struct BinaryTree *right;
}BinaryTree;

typedef struct QueueNode{
	BinaryTree *treeNode;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue{
	struct QueueNode *front;
	struct QueueNode *rear;
}Queue;



BinaryTree *createNode(char data){
	BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));
	tree -> value = data;
	tree -> left = NULL;
	tree -> right = NULL;
	return tree;
}

Queue *createQueue(){
	Queue *queue = (Queue *) malloc(sizeof(Queue));
	queue -> front = NULL;
	queue -> rear = NULL;
	return queue;
}

int isQueueEmpty(Queue *queue){
	return queue -> front == NULL;
}

void enqueue(Queue *queue, BinaryTree *treeNode){
	QueueNode *newNode = (QueueNode *) malloc(sizeof(QueueNode));
	newNode -> treeNode = treeNode;
	newNode -> next = NULL;
	if(isQueueEmpty(queue))
		queue -> front = queue -> rear = newNode;
	else{
		queue -> rear -> next = newNode;
		queue -> rear = newNode;
	}
}

BinaryTree *dequeue(Queue *queue){
	if(isQueueEmpty(queue))
		return NULL;
	QueueNode *frontNode = queue -> front;
	BinaryTree *treeNode = frontNode -> treeNode;
	if(queue -> front == queue -> rear)
		queue -> front = queue -> rear = NULL;
	else
		queue -> front = queue -> front -> next;
	free(frontNode);
	return treeNode;
}

void insertNode(BinaryTree **root, char data){
	BinaryTree *newNode = createNode(data);
	if(*root == NULL)
		*root = newNode;
	else{
		Queue *queue = createQueue();
		enqueue(queue, *root);
		while(1){
			BinaryTree *frontNode = dequeue(queue);
			if(frontNode -> left == NULL){
				frontNode -> left = newNode;
				break;
			}
			else if(frontNode -> right == NULL){
				frontNode -> right = newNode;
				break;
			}
			else{
				enqueue(queue, frontNode -> left);
				enqueue(queue, frontNode -> right);
			}
		}
		free(queue);
	}
}

void printInInsertionOrder(BinaryTree *root){
	if(root == NULL)
		return;
	Queue *queue = createQueue();
	enqueue(queue, root);
	
	while(!isQueueEmpty(queue)){
		BinaryTree *frontNode = dequeue(queue);
		printf("%c ", frontNode -> value);
		if(frontNode -> left != NULL)
			enqueue(queue, frontNode -> left);
		if(frontNode -> right != NULL)
			enqueue(queue, frontNode -> right);
	}
	free(queue);	
}

void freeBinaryTree(BinaryTree *node){
	if(node == NULL)
		return;
	freeBinaryTree(node -> left);
	freeBinaryTree(node -> right);
	free(node);
}


void findData(BinaryTree *root, char data, int depth, char *morse){
	if (root == NULL)
		return;

	if (root -> value == data) {
		morse[depth] = '\0';
		return;
	}
	
	morse[depth] = '.';
	findData(root -> left, data, morse, depth + 1);
	if (morse[depth + 1] == '\0') {
		morse[depth] = '\0';
	}

	morse[depth] = '-';
	findData(root -> right, data, morse, depth + 1);
	if (morse[depth + 1] == '\0'){
		morse[depth] = '\0';
	}
}

	
int main(){
	BinaryTree *root = NULL; 
	char quit = 'n', data;
	FILE *file = fopen("file.txt", "r");
	while(fscanf(file, " %c", &data) == 1)
		insertNode(&root, data);
	fclose(file);
	printInInsertionOrder(root);
	printf("\n\nEnter a char = ");
	scanf(" %c", &data);
	char string[100];
	findData(root, data, 0, string);
	printf("%s\n", string);
	freeBinaryTree(root);
	return 0;
}
