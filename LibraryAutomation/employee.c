#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

void printEmployees(Person *person){
	Person *iter = person;
	while(iter != NULL){
		if(strcmp("Employee", iter -> department) == 0){
			printf("Name = %s\nDepartment = %s\n", iter -> name, iter -> department);
			printf("Email = %s\nAge = %d\nTel = %s\n", iter -> email, iter -> age, iter -> tel);
			printf("State = %d\n", iter -> state);
			printf("---------------------\n");
		}	
		iter = iter -> next;
	}
}

void inactive(Person **head, char *name, char *email){
	Person *iter = *head;
	while(iter != NULL){
		if((strcmp(iter -> name, name) == 0) && (strcmp(iter -> email, email) == 0)){
			iter -> state = 0;
			return;
		}
		iter = iter -> next;
	}
}

int checkEmployee(Person *person, char *name, char *email){
	Person *iter = person;
	while(iter != NULL){
		if(strcmp(iter -> name, name) == 0 && strcmp(iter -> email, email) == 0)
			return 0;
		iter = iter -> next;
	}
	return 1;
}

void processEmployee(Person **person){
	Book *temp;
	printf("1 - Employee List\n2 - Employee Added\n3 - Employee Del\n4 - Cikis\n");
	int choice;
	char name[40], department[40], email[100], tel[12];
	int age, state;
	scanf("%d", &choice);
	switch(choice){
		case 1:
			printEmployees(*person);
			break;
		case 2:	
			printf("Name and Surname please = ");
	    	fscanf(stdin, " %[^\n]s", name);
	    	printf("Email = ");
	    	fscanf(stdin, " %[^\n]s", department);
	    	printf("Department = ");
	    	fscanf(stdin, " %[^\n]s", email);
	    	printf("Tel = ");
	    	fscanf(stdin, "	 %[^\n]s", tel);
	    	printf("Age = ");
	    	scanf("%d", &age);
			choice = checkEmployee(*person, name, email);
			if(choice == 1)
				insertNode(person, createNode(name, department, email, age, tel, 1, temp -> name, temp -> author));
			else 
				printf("This person is available\n");
			break;
		case 3:
			printf("Name and Surname of the person to be removed = ");
			fscanf(stdin, " %[^\n]s", name);
			printf("Email of the person to be removed = ");
			fscanf(stdin, " %[^\n]s", email);
			inactive(person, name, email);
			break;
		case 4:
			//Cikis islemlerini yaptiracak bir algoritma bul..
			break;
		default:
			printf("Wrong key..\n");
			break;
	}
}
