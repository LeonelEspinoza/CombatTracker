#include <stdlib.h>
#include <stdio.h>

typedef struct entity {
	char* name;
	int hp;
	int ac;
	int initiative;
} entity;

typedef struct linkedNode {
	void* data;
	struct linkedNode* next;
	struct linkedNode* prev;
} node;

node* createNode(void* data){
	node* node = NULL;
	node = (node*) malloc(sizeof(node));

	if(!node){
		printf("Memory allocation failed\n");
		return 1;
	}

	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void setNext(node* self, node* next){
	self->next = next;
}

void setPrev(node* self, node* prev){
	self->prev = prev;
}

node* getNext(node* self){
	return self->next;
}

node* getPrev(node* self){
	return self->prev;
}

void* getData(node* self){
	return self->data;
}

void main(){
	entity p1 = {"player1", 10, 12, 05}; 
	entity p2 = {"player2", 13, 10, 15}; 
	entity p3 = {"player3", 12, 11, 25}; 
	entity p4 = {"player4", 10, 15, 08}; 
	return;
}
