#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entity_list.c"
#include <stdbool.h>

bool closeProgram;

void getUserInput(char* buff, size_t size, char* prompt){
	//printf("\n--- WAITING FOR USER INPUT ---\n");
	printf("%s\n", prompt);
	while(fgets(buff, size, stdin) == NULL){
		printf("Error reading user input. Try again.\n");
	}
	buff[strcspn(buff,"\n")] = 0;
	return ;
}

void getCharacterStats(char name[], int* hp, int* ac, int* initiative){
	getUserInput(name, MAX_NAME_SIZE, "Enter character's name: ");
	char buff[4];
	getUserInput(buff, sizeof(buff), "Enter character's hp: ");
	*hp=atoi(buff);
	getUserInput(buff, sizeof(buff), "Enter character's ac: ");
	*ac=atoi(buff);
	getUserInput(buff, sizeof(buff), "Enter character's initiative: ");
	*initiative=atoi(buff);
	return;
}

void addCharacter(struct linkedList* l){
	char name[MAX_NAME_SIZE];
	int hp, ac, initiative;
	getCharacterStats(name, &hp, &ac, &initiative);

	struct entity* entity =
	createEntity(name, hp, ac, initiative);

	struct node* node =
	createNode(entity);

	insertNode(l, node);
	return;
}


void inputParser(char* input, struct linkedList* l){
	printf("echo: %s\n",input);
	switch (input[0]){
		case 'a':
			addCharacter(l);
			break;
		case 'p':
			printLinkedList(l);
			break;
		case 'e':
			printf("Exiting program\n");
			closeProgram = true;
			break;
		default:
			printf("default case\n");
			break;
	}
}

int main(){
	closeProgram = false;
	struct linkedList* list = initLinkedList();
	char buff[50];
	while(!closeProgram){
		getUserInput(
			buff,
			sizeof(buff),
			"(a)dd character\n(p)rint list\n(e)xit\n"
		);
		inputParser(buff, list);
	}
	cleanupLinkedList(list);
	return 0;
}
