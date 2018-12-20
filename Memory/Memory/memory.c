/*
PRP2-2 Aufgabe 4.1
Name: Malte Müller, Fabian Liebold
Date: 09.12.2018
*/

#define _CRT_SECURE_NO_WARNINGS


#include "memory_utilities.h"
#include <string.h>	// Stringtoken
#include <stdio.h> // Input / Output
#include <stdlib.h>	// Important for malloc, etc
#include <time.h>	// Date and time

int main(void) {
	int size;	// size of playground
	int found = 0; // found pairs
	char load_flag;

	printf("******************** MEMORY ********************\n\n");

	karte_t **pplayground = NULL;
	do {

		printf("Moechten Sie einen Spielstand laden? [j/n] ");	// ask user to load playground
		scanf(" %c", &load_flag);
	
		if (load_flag == 'j') {	// load playground
		
			pplayground = load_playground(&size);
		}
		else if(load_flag == 'n'){	// randomly generate playground
			get_size(&size);
			//printf("[DEBUG] SIZE: %d\n", size);

			pplayground = allocate_memory(size);	// allocate memory for playground (does not work as void!)

			init_playground(pplayground, size);
			show_playground(pplayground, size);

		}
	} while (load_flag != 'j' && load_flag != 'n');
	

	printf("Zum Starten des Spiels ");
	system("PAUSE");

	system("cls");
	print_playground(pplayground, size, 0);

	char first_card[8];
	char second_card[8];
	char delim[2] = " ";
	int x1, y1, x2, y2;

	//flush_stdin();
	
	do {
			
		do {
			printf("Geben Sie die Koordinaten fuer die 1.Karte ein [Zeile Spalte] (-1 -1 fuer Abbruch): ");
			gets(first_card);
			
			//printf("[DEBUG] string: %s\n", first_card);

			char *token = strtok(first_card, delim);

			x1 = atoi(token);
			token = strtok(NULL, delim);
			y1 = atoi(token);
			
		} while (x1 >= size || x1 < -2 || y1 >= size || y1 < -2);

		if (x1 == -1 && y1 == -1) break;
		else if (x1 == -2 && y1 == -2) {
			save_playground(pplayground, size);
			break;
		}

		pplayground[x1][y1].flag = 1;

		print_playground(pplayground, size, found);
		
		do {
			printf("Geben Sie die Koordinaten fuer die 2.Karte ein [Zeile Spalte] (-1 -1 fuer Abbruch): ");
			gets(second_card);

			char *token2 = strtok(second_card, delim);

			x2 = atoi(token2);
			token2 = strtok(NULL, delim);
			y2 = atoi(token2);
		} while (x2 >= size || x2 < -2 || y2 >= size || y2 < -2);

		if (x2 == -1 && y2 == -1) break;
		else if (x1 == -2 && y1 == -2) {
			save_playground(pplayground, size);
			break;
		}

		pplayground[x2][y2].flag = 1;

		print_playground(pplayground, size, found);

		if (pplayground[x1][y1].id == pplayground[x2][y2].id) found++;
		else {
			pplayground[x1][y1].flag = 0;
			pplayground[x2][y2].flag = 0;
		}

		
	} while (found != (size*size) / 2);


	free_all(pplayground, size);
	system("PAUSE");
	return 0;
}
