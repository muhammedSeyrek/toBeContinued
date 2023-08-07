#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "employee.h"
#include "book.h"
#include "reader.h"

int totalPerson = 0, totalBook = 0;

//Eksiklikler
//Sonradan book islemleride bozuldu niyeyse.
//reader kaydi tutumuyor.
//Bunlar halledilirse kucuk bir revizyon ile program halledilir.

Person *createNode(char *name, char *department, char *email, int age, char *tel, int state, char *bookName, char *authorName){
	Person *person = (Person *) malloc(sizeof(Person));
    strcpy(person -> name, name);
    strcpy(person -> department, department);
    strcpy(person -> email, email);
    person -> age = age;
    strcpy(person -> tel, tel);
    person -> state = state;
    if(strcmp("Reader", department) == 0)
        if(strlen(bookName) > 0 && strlen(authorName) > 0){
        	strcpy(person -> loan -> name, bookName);
        	strcpy(person -> loan -> author, authorName); 
		}
        else
            person -> loan = NULL;
	else
        person -> loan = NULL;
    person -> next = NULL;
    return person;
}

void insertNode(Person **head, Person *person){
	if(*head == NULL)
		*head = person;
	else{
		Person *iter = *head;
		while(iter -> next != NULL)
			iter = iter -> next;
		iter -> next = person;
	}
}

int check(Person *head, char *name, char *email){
	Person *iter = head;
	while(iter != NULL){
		if((strcmp(iter -> name, name) == 0) && (strcmp(iter -> email, email) == 0)){
			if(strcmp("Manager", iter -> department) == 0 || strcmp("Manager Asistant", iter -> department) == 0){
				return 1;	
			}
			else if(strcmp("Employee", iter -> department) == 0){
				return 2;	
			}
			else if(strcmp("Reader", iter -> department) == 0){
				return 3;	
			}
		}
		iter = iter -> next;
	}
	return 0;
}


void freeList(Person *persons, Book *books){
	Person *iterPerson = persons;
	while(iterPerson != NULL){
		Person *temp = iterPerson;
		iterPerson = iterPerson -> next;
		free(temp);
	}	
	
	Book *iterBook = books;
	while(iterBook != NULL){
		Book *temp = iterBook;
		iterBook = iterBook -> next;
		free(temp);
	}
}

void saveToFile(Person *persons, char *personList, Book *books, char *bookList){
	FILE *tempPerson = fopen(personList, "w");
	FILE *tempBook = fopen(bookList, "w");
	if(tempPerson == NULL || tempBook == NULL)
		printf("File open error!!!\n");
	Person *iterPerson = persons;
	while(iterPerson != NULL){
		char bookName[100] = "";
		if(iterPerson -> loan != NULL){
			fprintf(tempPerson, "%s-%s-%s-%d-%s-%d-%s-%s\n", iterPerson -> name, iterPerson -> department, 
			iterPerson -> email, iterPerson -> age, iterPerson -> tel, 
			iterPerson -> state, iterPerson -> loan -> name, iterPerson -> loan -> author);
		}
		else{
			fprintf(tempPerson, "%s-%s-%s-%d-%s-%d\n", iterPerson -> name, iterPerson -> department,
            iterPerson -> email, iterPerson -> age, iterPerson -> tel, iterPerson -> state);
		}
		iterPerson = iterPerson -> next;
		totalPerson++; 
	}
	fclose(tempPerson);
	Book *iterBook = books;
	while(iterBook != NULL){
		fprintf(tempBook, "%s-%s-%d-%d\n", iterBook -> name, iterBook -> author, 
		iterBook -> count, iterBook -> state);
		iterBook = iterBook -> next;
		totalBook += iterBook -> count;
	}
	fclose(tempBook);
}


int main(void){
	FILE *file = fopen("Person.txt", "r");
	FILE *bookFile = fopen("Book.txt", "r");
	Person *head = NULL;
	Book *book = NULL;
	char line[200];
	while(fgets(line, sizeof(line), file) != NULL && " "){
		char *name = strtok(line, "-");
		if(name != NULL){
			char *department = strtok(NULL, "-");
            char *email = strtok(NULL, "-");
            int age = atoi(strtok(NULL, "-"));
            char *tel = strtok(NULL, "-");
            int state = atoi(strtok(NULL, "-"));
            char *nameBook = strtok(NULL, "-");
            char *authorName = strtok(NULL, "-");
            insertNode(&head, createNode(name, department, email, age, tel, state, nameBook, authorName));
		}
	}
	while(fgets(line, sizeof(line), bookFile) != NULL){
		char *name = strtok(line, "-");
		if(name != NULL){
			char *author = strtok(NULL, "-");
			int count = atoi(strtok(NULL, "-"));
			insertBook(&book, createBook(name, author, count));
		}
	}
	int choice;
	printf("1 - Login\n2 - Sign Up\n");
	scanf("%d", &choice);
	char name[40], email[100], tel[12];
	int age;
	if(choice == 1){
		printf("Name and Surname please = ");
	    fscanf(stdin, " %[^\n]s", name);
	    printf("Email = ");
	    fscanf(stdin, " %[^\n]s", email);
	    int select = check(head, name, email);
	    printf("%d\n", select);
	    switch(select){
	    	case 1:
	    		printf("Manager %s you have process...\n", name);
	    		printf("1 - Employee process\n2 - Book process\n3 - Reader process\n");
	    		Person *temp = head;
	    		while(temp != NULL){
	    			printf("%s ", temp -> department);
	    			temp = temp -> next;
				}
	    		scanf("%d", &choice);
	    		if(choice == 1)
	    			processEmployee(&head);
				if(choice == 2)
					processBook(&book);
				if(choice == 3)
					processReader(&head, &book, name, email);
	    		break;
	    	case 2:
	    		printf("Employee %s you have process...\n", name);
	    		printf("1 - Book process\n2 - Reader process\n");
	    		scanf("%d", &choice);
	    		if(choice == 1)
	    			processBook(&book);
	    		if(choice == 2)
	    			processReader(&head, &book, name, email);
	    		break;
	    	case 3:
	    		printf("Reader %s you have process...\n", name);
	    		processReader(&head, &book, name, email);
	    		//Kayit sil yada guncelle
	    		//Book islemler
	    		break;
	    	default:
	    		printf("Wrong process!!!");
	    		break;
		}
	}
	else if(choice == 2){
		Book *temp;
		printf("Please enter name = ");
		fscanf(stdin, " %[^\n]s", name);
		printf("Please enter email = ");
		fscanf(stdin, " %[^\n]s", email);
		printf("Please enter tel = ");
		fscanf(stdin, " %[^\n]s", tel);
		printf("Please enter your age = ");
		scanf("%d", &age);
		int exists = check(head, name, email);
		if(!exists)
			insertNode(&head, createNode(name, "Reader", email, age, tel, 1, " ", " "));	
		else 
			printf("This person is non-exist");
	}
	//Bu aradaki kod program ctrl + c vb. sekilde kapanirsa dosyayi kapatir bu sayede icindeki
	//dosyalar silinmez.
	void fcloseFile(void){
		fclose(file);
		fclose(bookFile);
	}
	atexit(fclose);
	getchar();
	//Bu modulun bitisi.
	
	saveToFile(head, "Person.txt", book, "Book.txt");
	freeList(head, book); //Bellegi serbest birakiyoruz.
	return 0;
}
