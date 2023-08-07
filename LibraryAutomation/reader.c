#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"
#include "employee.h"
#include "book.h"

void loanTake(Person **person, Book **book, char *name, char *author, char *personName){
	Person *tempP = *person;
	Book *tempB = *book;
	while(tempB != NULL){
		if(strcmp(tempB -> name, name) == 0 && strcmp(tempB -> author, author) == 0){
			if(tempB -> state > 0){
				tempB -> state--;
				while(tempP != NULL){
					if(strcmp(tempP -> name, personName) == 0){
						tempP -> loan = createBook(tempB -> name, tempB -> author, 1); 
						return;
					}
					tempP = tempP -> next;
				}
			}
			else{
				printf("Counts of the book not enough!!!\n");
				return;	
			}
		}
		tempB = tempB -> next;
	}
	printf("There is no book by this name!!!\n");
}

void loanGive(Person **person, Book **book, char *personName){
	Person *iter = *person;
	Book *temp = *book;
	while(iter != NULL){
		if(strcmp(iter -> name, personName) == 0){
			Book *loanedBook = iter -> loan;
			while(temp != NULL){
				if(iter -> loan == temp){
					iter -> loan = NULL;
					temp -> state++;
					free(loanedBook);
					return;
				}
				temp = temp -> next;
			}
		}
		iter = iter -> next;
	}
}


void processReader(Person **person, Book **book, char *personName, char *personEmail){
	printf("1 - Take a book\n2 - Give a book\n3 - Update my info\n4 - Delete my registration\n5 - Reader record\n");
	int choose, age;
	char name[50], author[50], email[50], tel[12];
	Book *temp;
	scanf("%d", &choose);
	switch(choose){
		case 1:
			printBooks(*book);
			printf("Enter book info...");
			printf("Enter name = "); fscanf(stdin, " %[^\n]s", name);
			printf("Enter author = "); fscanf(stdin, " %[^\n]s", author);
			loanTake(person, book, name, author, personName);
			break;
		case 2:
			loanGive(person, book, personName);
			break;
		case 3:
			printf("1 - Tel number\n2 - gmail\n");
			scanf("%d", &choose);
			if(choose == 1)
				fscanf(stdin, " %[^\n]s", tel);
			else if(choose == 2)
				fscanf(stdin, " %[^\n]s", personEmail);
			else 
				printf("Wrong process!\n");
			break;
		case 4:
			inactive(person, name, email);
			printf("Success!\n");
			break;
		case 5:
			printf("Please enter name = ");
			fscanf(stdin, " %[^\n]s", name);
			printf("Please enter email = ");
			fscanf(stdin, " %[^\n]s", email);
			printf("Please enter tel = ");
			fscanf(stdin, " %[^\n]s", tel);
			printf("Please enter your age = ");
			scanf("%d", &age);
			insertNode(person, createNode(name, "Reader", email, age, tel, 1, temp -> name, temp -> author));
			break;
		default:
			break;
	}
}
