#ifndef ENTITY_LIST_H
#define ENTITY_LIST_H

#include <stdlib.h>
#include <stdio.h>

/*
* Entity structure
	* Name string
	* Health
	* Armor Class
	* Initiative
*/
struct entity {
	char* name;
	int hp;
	int ac;
	int initiative;
};

/*
* Entity Initializer
	* Allocates memory for object
	* Sets object's attributes with arguments values
*/
struct entity* createEntity(char* name, int hp, int ac, int initiative){
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

/*
* Entity cleanup
	* Free allocated memory
	* Nullifies attributes
*/
void cleanupEntity(struct entity* entity){
	entity->name = NULL;
	entity->hp = 0;
	entity->ac = 0;
	entity->initiative = 0;
	free(entity);
	return;
}

void printEntity(struct entity* self){
	printf(
		"%s:\n	Health: %d\n	AC: %d\n	Initiative: %d\n",
		self->name, self->hp, self->ac, self->initiative
	);
	return;
}

/*
* Node structure
	* Entity pointer
	* Next Node pointer
	* Previous Node pointer
*/
struct node {
	struct entity* entity;
	struct node* next;
	struct node* prev;
};

/*
* Node initializer
	* Allocates memory for object
	* Set entity pointer with argument value
*/
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

/*
* Node cleanup
	* Make sure neighbors nodes are pointing eachother
	* Free allocated memory for self and entity child
	* Nullifies attributes
*/
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
	self->entity = NULL;
	self->prev = NULL;
	self->next = NULL;
	free(self);
	return;
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

/*
* Get entity child initiative
	* Auxiliar getter for entity child
*/
int getNodeInitiative(struct node* self){
	struct entity* entity = self->entity;
	return entity->initiative;
}

void printNode(struct node* self){
	printEntity(self->entity);
	return;
}
	
/*
* Linked list structure
	* Sorts its members by initiative decreasing order
	* Head: pointer first node in list
	* Current: pointer to current node
	* Size: number of linked nodes
	* round: current loop number
*/
struct linkedList {
	struct node* head;
	struct node* current;
	int size;
	int round;
};

/*
* Linked List Initializer
	* Allocates memory for object
	* Set size and round attributes to zero
*/
struct linkedList* initLinkedList(){
	struct linkedList* self = NULL;
	self = (struct linkedList*) malloc(sizeof(struct linkedList));
	if(!self){
		printf("Memory allocation failed\n");
		return NULL;
	}
	self->head = NULL;
	self->current = NULL;
	self->size = 0;
	self->round = 0;
}

/*
* Recursive Node cleanup
	* Calls itself on next node
	* Calls Node ceanup function on head.
*/
void cleanupLinkedTail(struct node* head){
	if (head->next != NULL){
		cleanupLinkedTail(head->next);
	}
	cleanupNode(head);
	return;
}

/*
* Linked List cleanup
	* calls recursive cleanup
	* Nullifies object's attributes
	* Frees allocated mamory
*/
void cleanupLinkedList(struct linkedList* self){
	if (self->head != NULL){
		cleanupLinkedTail(self->head);
	}
	self->head = NULL;
	self->current = NULL;
	self->size = 0;
	self->round = 0;
	free(self);
	return;
}

/*
* Recursive insert auxiliar
	* inserts new node sorted by initiative
*/
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

/*
* Insert ONE new node
	* If list is empty inserts its first Node
	* Else inserts node sorted by initiative
	* updates head if new node is first
	* updates list's size
*/
void insertNode(struct linkedList* self, struct node* node){
	if (self->head == NULL){
		self->head = node;
		self->current = node;
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

/*
* Deletes Current Node
	* if current is NULL do nothing
	* if next is NULL current points to head
	* calls node cleanup for current node
	* updates size
*/
void deleteCurrentNode(struct linkedList* self){
	struct node* cur = self->current;
	if (cur == NULL){
		return;
	}

	if (cur->next != NULL){
		self->current = cur->next;
	}else{
		self->current = self->head;
	}

	cleanupNode(cur);
	self->size -= 1;
	return;
}

/*
* Update current forward
	* updates current pointer to next node
	* if current is last, increase round and point to first
*/
void moveForward(struct linkedList* self){
	struct node* cur = self->current;
	if (cur->next == NULL){
		self->current = self->head;
		self->round += 1;
		return;
	}
	self->current = cur->next;
	return;
}

/*
* Update current backwards
	* updates current pointer to previous node
	* if current is first, decrease round and point to last
*/
void moveBack(struct linkedList* self){
	struct node* cur = self->current;
	if (cur->prev == NULL && cur == self->head){
		struct node* tmp = self->head;
		while(tmp->next != NULL){
			tmp=tmp->next;
		}
		self->current = tmp;
		self->round -= 1;
		return;
	}

	self->current = cur->prev;
	return;
}

/*
* Auxiliar recursive print
	* prints node number and entity attributes
*/
void printRecursive(struct node* head, int i){
	printf("\nNode #%d\n",i);
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
	printf("\nRound #%d | Size: %d\n", list->round, list->size);
	printRecursive(head,1);
	return;
}

#endif

