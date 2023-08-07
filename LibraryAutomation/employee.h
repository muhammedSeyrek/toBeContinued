#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "book.h"

typedef struct Person{
	char name[40];
	char department[40];
	char email[100];
	int age;
	char tel[12];
	int state;
	Book *loan;
	struct Person *next;
}Person;

void printEmployees(Person *person);

void inactive(Person **head, char *name, char *email);

void processEmployee(Person **person);


#endif

