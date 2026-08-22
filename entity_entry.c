#include <stdio.h>
#include <string.h>

typedef struct entity {
	char* name;
	int hp;
	int ac;
	int initiative;
} entity;

void swap(entity* a, entity* b){
	entity t = *a;
	*a = *b;
	*b = t;
}

int partition(entity arr[], int low, int high){
	int pivot = arr[high].initiative;
	int i = low-1;
	for(int j = low; j <= high-1; j++){
		if (arr[j].initiative < pivot){
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i+1], &arr[high]);
	return i+1;
}

void quickSort(entity arr[], int low, int high){
	if (low < high){
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi-1);
		quickSort(arr, pi+1, high);
	}
}

void sortGroupByInitiative(entity group[], int size){
	quickSort(group, 0, size-1);
}

int main(){
	entity ch1 = {"Wolf", 10, 10, 5};
	entity ch2 = {"Strigoi", 10, 10, 20};
	entity ch3 = {"Troll", 10, 10, 10};
	entity ch4 = {"Troll1", 10, 10, 15};
	entity ch5 = {"Troll2", 10, 10, 13};
	entity ch6 = {"Troll3", 10, 10, 18};
	entity ch7 = {"Troll4", 10, 10, 13};
	entity ch8 = {"Troll5", 10, 10, 30};
	entity ch9 = {"Troll6", 10, 10, 1};
	entity group[9] = {ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9};
	sortGroupByInitiative(group, 9);
	for(int i = 0; i < (sizeof(group) / sizeof(group[0])); i++){
		entity cha = group[i];
		printf("name: %s, HP: %d, AC: %d \n", cha.name, cha.hp, cha.ac);
	}
	return 0;
}
