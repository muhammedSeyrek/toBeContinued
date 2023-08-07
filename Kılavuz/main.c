#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relevant.h"

//Tamamen sadece introsu olan bir program.

int main(void){	
	Link *head = NULL;
	FILE *file = fopen("Relevant.txt", "a");
	char string[100];
	int lenght = 0, number, quit = 1;
	while(quit){
		printf("Enter a words = ");
		fscanf(stdin, " %[^\n]s", string);
		while(string[lenght] != '\0')
			lenght++;
		
		char text[lenght + 1];
		strcpy(text, string);	
		
		printf("Enter, Which write location?");
		scanf("%d", &number);
		processLink(&head, text, number);
		printf("Devam Etmek icin -> 1\nCikis icin -> 0\n");
		scanf("%d", &quit);	
	}
	
	
	return 0;
}
