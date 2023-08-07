#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void delBook(Book **book, char *name, char *author) {
    if (*book == NULL) 
        return; 
    Book *iter = *book;
    Book *prev = NULL;
    while (iter != NULL) {
        if (strcmp(iter -> name, name) == 0 && strcmp(iter -> author, author) == 0) {
            if (iter -> count > 1) {
                iter -> count--;
                return;
            } else {
                if (prev == NULL) {
                    *book = iter -> next; 
                } else {
                    prev -> next = iter -> next; 
                }
                free(iter); 
                return;
            }
        }
        prev = iter;
        iter = iter -> next;
    }
}

Book *createBook(char *name, char *author, int count){
	Book *newBook = (Book *) malloc(sizeof(Book));
	strcpy(newBook -> name, name);
	strcpy(newBook -> author, author);
	newBook -> count = count;
	newBook -> state = 1;
	newBook -> next = NULL;
	return newBook;
}

void insertBook(Book **book, Book *tempBook){
    if (*book == NULL)
        *book = tempBook;
    else {
        Book *iter = *book;
        while (iter != NULL) {
            if ((strcmp(iter -> name, tempBook -> name) == 0) &&
                (strcmp(iter -> author, tempBook -> author) == 0)) {
                iter -> count++;
                iter -> state = iter -> count;
                free(tempBook); // Kitap ayný listede varsa serbest býrakýyoruz.
                return;
            }
            if (iter -> next == NULL) // Bunu yapmazsan 1 tane ayni isimde kitap olunca bir kez
                break; 				//daha kitap ekliyor.
            iter = iter -> next;
        }
        iter -> next = tempBook;
    }
}

void printBooks(Book *book){
	Book *iter = book;
	while(iter != NULL){
		printf("Name = %s\nAuthor = %s\nCount = %d\nStock = %d\n", 
		iter -> name, iter -> author, iter -> count, iter -> state);
		iter = iter -> next;
	}
}

void processBook(Book **book){
	printf("1 - Book List\n2 - Book Added\n3 - Book Del\n");
	int choice;
	char name[40], author[40];
	int count;
	scanf("%d", &choice);
	switch(choice){
		case 1:
			printBooks(*book);
			break;
		case 2:
			printf("Enter book name = ");
			fscanf(stdin, " %[^\n]s", name);
	    	printf("Author name = ");
	    	fscanf(stdin, " %[^\n]s", author);	
	    	insertBook(book, createBook(name, author, 1));
			printBooks(*book);
			break;
		case 3:
			printf("Name of the book to be removed = ");
			fscanf(stdin, " %[^\n]s", name);
			printf("Name of the book's author to be removed = ");
			fscanf(stdin, " %[^\n]s", author);
			delBook(book, name, author);
			break;
		default:
			break;
	}
}
