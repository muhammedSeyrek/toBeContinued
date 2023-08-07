#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relevant.h"

int check(Link *iter, int array[], int index){
	
	if(!strcmp(NULL, iter -> name))
		
	
}


void processLink(Link **head, char *text, int number){
	int index = 0, temp = number;
	Link *iter = *head;
	while(!temp){
		temp /= 10;
		index++;
	}
	int array[index];
	for(int i = index; i > -1; i--){
		array[i] = number % 10;
		number /= 10;
	}
	if(check(*iter, array, 0)){
		//eger onaydan gecerse yazicak.	
	}
	else{
		printf("There is NULL!...\n");
	}
}
