#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entity_list.c"

void getUserInput(char* buff, size_t size, char* prompt){
	printf("%s\n", prompt);
	while(fgets(buff, sizeof(buff), stdin) == NULL){
		printf("Error reading user input. Try again.\n");
	}
	buff[strcspn(buff,"\n")] = 0;
	return ;
}


void inputParser(char* input, struct linkedList* l){
	switch (input[0]){
		case 'a':
			printf("Case: add character\n");

			struct entity* entity =
				createEntity("name",10,10,10);

			struct node* node =
				createNode(entity);

			insertNode(l, node);
			break;
		default:
			printf("default case\n");
			break;
	}
}

void main(){
	struct linkedList* list = initLinkedList();
	char buff[50];
	int i = 0;
	while(i<3){
		getUserInput(buff, sizeof(buff), "(a)dd default character\n");
		inputParser(buff, list);
		i++;
	}
	printLinkedList(list);
	cleanupLinkedList(list);
	return ;
}
