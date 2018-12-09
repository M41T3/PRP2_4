/*
PRP2-2 Aufgabe 4.1
Name: Malte Müller, Fabian Liebold
Date: 09.12.2018
*/

#include <stdio.h>

//Prototypes:
void get_size(int *size);


int main(void) {
	int size;	// size of playground
	get_size(&size);

	printf("[DEBUG] SIZE: %d\n", size);

	system("PAUSE");
	return 0;
}

void get_size(int *size){
	printf("Wie gross soll das quadratische Spiel werden? \n");
	do {
		printf("Geben Sie eine gerade Zahl ein [2 - 10]: ");
		scanf_s(" %d",size);
	} while (*size < 2 || *size > 10 || *size%2 == 1);
}