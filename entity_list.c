#ifndef ENTITY_LIST_H
#define ENTITY_LIST_H

#include <stdlib.h>
#include <stdio.h>

struct entity {
	char* name;
	int hp;
	int ac;
	int initiative;
};

struct entity* createEntity(char name[], int hp, int ac, int initiative){
	struct entity* entity = NULL;
	entity = (struct entity*) malloc(sizeof(struct entity));
	if(!entity){
		perror("Memory allocation for entity failed\n");
		return NULL;
	}
	entity->name = name;
	entity->hp = hp;
	entity->ac = ac;
	entity->initiative = initiative;
	return entity;
}

void cleanupEntity(struct entity* entity){
	free(entity);
	return;
}

struct node {
	struct entity* entity;
	struct node* next;
	struct node* prev;
};

struct node* createNode(struct entity* entity){
	struct node* node = NULL;
	node = (struct node *) malloc(sizeof(struct node));
	if(!node){
		perror("Memory allocation for node failed\n");
		return NULL;
	}
	node->entity = entity;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void cleanupNode(struct node* self){
	struct node* next = self->next;
	struct node* prev = self->prev;
	if(next != NULL){
		next->prev = prev;
	}
	if(prev != NULL){
		prev->next = next;
	}
	cleanupEntity(self->entity);
	free(self);
	return;
}

void setNext(struct node* self, struct node* next){
	self->next = next;
}

void setPrev(struct node* self, struct node* prev){
	self->prev = prev;
}

struct node* getNext(struct node* self){
	return self->next;
}

struct node* getPrev(struct node* self){
	return self->prev;
}

struct entity* getEntity(struct node* self){
	return self->entity;
}

int getNodeInitiative(struct node* self){
	struct entity* entity = self->entity;
	return entity->initiative;
}

void printNode(struct node* self){
	struct entity* entity = self->entity;
	printf("Name: %s, HP: %d, AC: %d, Initiative: %d\n", entity->name, entity->hp, entity->ac, entity->initiative);
	return;
}
	
struct linkedList {
	struct node* head;
	int size;
};

struct linkedList* initLinkedList(){
	struct linkedList* self = NULL;
	self = (struct linkedList*) malloc(sizeof(struct linkedList));
	if(!self){
		printf("Memory allocation failed\n");
		return NULL;
	}
	self->head = NULL;
	self->size = 0;
}

void cleanupLinkedTail(struct node* head){
	if (head->next != NULL){
		cleanupLinkedTail(head->next);
	}
	cleanupNode(head);
	return;
}

void cleanupLinkedList(struct linkedList* self){
	if (self->head != NULL){
		cleanupLinkedTail(self->head);
	}
	free(self);
	return;
}


void insertRecursive(struct node* head, struct node* node){
	if (getNodeInitiative(head) < getNodeInitiative(node)){
		if (head->prev != NULL){
			struct node* prev = head->prev;
			node->prev = prev;
			prev->next = node;
		}
		node->next = head;
		head->prev = node;
		return;
	}
	if (head->next != NULL){
		insertRecursive(head->next,node);
		return;
	}
	head->next = node;
	node->prev = head;
	return;
}

void insertNode(struct linkedList* self, struct node* node){
	if (self->head == NULL){
		self->head = node;
	} else {
		insertRecursive(self->head,node);
	}

	struct node* head = self->head;
	if(head->prev != NULL){
		self->head = head->prev;
	}

	self->size +=1;
	return;
}

void printRecursive(struct node* head, int i){
	printf("Node #%d : ",i);
	if(head->entity == NULL){
		printf("Node without entity\n");
	} else {
		printNode(head);
	}
	if (!head->next) {
		printf("end of list\n");
		return;
	}
	printRecursive(head->next,i+1);
	return;
}

void printLinkedList(struct linkedList* list){
	struct node* head = list->head;
	printRecursive(head,1);
	return;
}

#endif

