#include <stdlib.h>
#include <stdio.h>

struct entity {
	char* name;
	int hp;
	int ac;
	int initiative;
};

struct node {
	struct entity* entity;
	struct node* next;
	struct node* prev;
};

struct node* createNode(struct entity* entity){
	struct node* node = NULL;
	node = (struct node *) malloc(sizeof(struct node));
	if(!node){
		printf("Memory allocation failed\n");
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
		printf("nodo insertado entre nodos\n");
		return;
	}
	if (head->next != NULL){
		insertRecursive(head->next,node);
		return;
	}
	head->next = node;
	node->prev = head;
	printf("nodo insertado en la cola\n");
	return;
}

void insertNode(struct linkedList* self, struct node* node){
	if (self->head == NULL){
		self->head = node;
		printf("primer nodo insertado\n");
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
		struct entity* entity = head->entity;
		printf("%s\n",entity->name);
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

void main(){
	struct entity p1 = {"player1", 10, 12, 5}; 
	struct entity p2 = {"player2", 13, 10, 15}; 
	struct entity p3 = {"player3", 12, 11, 25}; 
	struct entity p4 = {"player4", 10, 15, 8}; 

	struct node* n1 = createNode(&p1);
	struct node* n2 = createNode(&p2);
	struct node* n3 = createNode(&p3);
	struct node* n4 = createNode(&p4);
	
	struct linkedList* l = initLinkedList();
	insertNode(l,n1);
	insertNode(l,n2);
	insertNode(l,n3);
	insertNode(l,n4);
	printLinkedList(l);
	cleanupLinkedList(l);
	return;
}
