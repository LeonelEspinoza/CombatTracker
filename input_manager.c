#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.c"
#include "entity_entry.c"

void getUserInput(char* buff, size_t size, char* prompt){
	printf("%s\n", prompt);
	while(fgets(buff, sizeof(buff), stdin) == NULL){
		printf("Error reading user input. Try again.\n");
	}
	buff[strcspn(buff,"\n")] = 0;
	return ;
}

void main(){
	char buff[50];
	int i = 0;
	while(i<3){
		getUserInput(buff, sizeof(buff), "Waiting for user Input:");
		printf("%s\n", buff);
		i++;
	}
	return ;
}
