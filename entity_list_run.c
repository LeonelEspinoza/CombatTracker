#include "entity_list.c"

void main(){
	struct entity* p1 = createEntity("player1", 10, 12, 5);
	struct entity* p2 = createEntity("player2", 13, 10, 15);
	struct entity* p3 = createEntity("player3", 12, 11, 25);
	struct entity* p4 = createEntity("player4", 10, 15, 8);

	struct node* n1 = createNode(p1);
	struct node* n2 = createNode(p2);
	struct node* n3 = createNode(p3);
	struct node* n4 = createNode(p4);
	
	struct linkedList* l = initLinkedList();
	insertNode(l,n1);
	insertNode(l,n2);
	insertNode(l,n3);
	printLinkedList(l);
	insertNode(l,n4);
	printLinkedList(l);
	cleanupLinkedList(l);
	return;
}
