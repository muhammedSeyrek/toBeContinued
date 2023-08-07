#ifndef BOOK_H
#define BOOK_H

typedef struct Book{
	char name[50];
	char author[50];
	int count;
	int state;
	struct Book *next;
}Book;

Book *createBook(char *name, char *author, int count);

void insertBook(Book **book, Book *tempBook);

void printBooks(Book *book);

void processBook(Book **book);



#endif
