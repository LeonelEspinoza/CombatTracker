#ifndef ENTITY_H
#define ENTITY_H
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

#endif
