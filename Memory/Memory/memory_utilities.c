#define _CRT_SECURE_NO_WARNINGS

#include "memory_utilities.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>	// Important for malloc, etc
#include <time.h>

/**************************************************************************************************
Function flushes input stream.
Parameters:
void.
Returns:
void.
*/
void flush_stdin() {
	int flush_dummy;
	while ((flush_dummy = getchar()) != '\n' && flush_dummy != EOF);
}

/**************************************************************************************************
Function askes user to type in size of playground.
Parameters:
int *size - pointer size of array.
Returns:
void.
*/
void get_size(int *psize) {
	printf("Wie gross soll das quadratische Spiel werden? \n");
	do {
		printf("Geben Sie eine gerade Zahl ein [2 - 10]: ");
		scanf(" %d", psize);
		flush_stdin();
	} while (*psize < 2 || *psize > 10 || *psize % 2 == 1);
}

/**************************************************************************************************
Function returns pointer to allocated memory.
Parameters:
int size - size of array.
Returns:
karte_t **pplayground.
*/
karte_t **allocate_memory(int size) {

	karte_t **pplayground = (karte_t**)malloc(size * sizeof(karte_t*));

	if (pplayground != NULL) {

		for (int i = 0; i < size; i++) {
			pplayground[i] = (karte_t*)malloc(size * sizeof(karte_t));

			if (pplayground[i] == NULL) {
				for (int k = i - 1; k >= 0; k--) {
					free(pplayground[k]);
				}
				free(pplayground);
				pplayground = NULL;
			}
		}
	}
	return pplayground;
}

/**************************************************************************************************
Function initializes playground.
Parameters:
karte_t **pplayground
int size
Returns:
void.
*/
void init_playground(karte_t **pplayground, int size) {

	char id = 65;
	int counter = 0;

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			//printf(" %c", id);

			pplayground[row][col].id = id;
			pplayground[row][col].flag = 0;

			counter++;
			if (counter % 2 == 0) id++;	// Increase ASCII every second iteration
		}
	}

	srand((unsigned int)time(NULL));

	int rand_row;
	int rand_col;
	char temp;

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			rand_col = rand() % size;
			rand_row = rand() % size;

			//printf("[%d][%d] %c -> ",row, col, pplayground[row][col].id);

			temp = pplayground[row][col].id;
			pplayground[row][col].id = pplayground[rand_row][rand_col].id;
			pplayground[rand_row][rand_col].id = temp;

		}
	}
}

/**************************************************************************************************
Function prints playground to console.
Parameters:
karte_t **pplayground
int size
Returns:
void.
*/
void show_playground(karte_t **pplayground, int size) {

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			printf("%c ", pplayground[row][col].id);

		}
		printf("\n");
	}
}
/**************************************************************************************************
Function prints playground to console.
Parameters:
karte_t **pplayground
int size
Returns:
void.
*/
void print_playground(karte_t **pplayground, int size, int found) {
	printf("MEMORY:\t%d Paare gefunden!\n\n", found);

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			if (pplayground[row][col].flag == 1) printf("%c ", pplayground[row][col].id);
			else printf("# ");
		}
		printf("\n");
	}
}

/**************************************************************************************************
Function clears memory.
Parameters:
karte_t **pplayground
int size
Returns:
void.
*/
void free_all(karte_t **pplayground, int size) {
	for (int i = 0; i < size; i++) {
		free(pplayground[i]); // rows
	}
	free(pplayground);	//Column
}

karte_t **load_playground(int *psize) {

	karte_t **pplayground_tmp;
	FILE *in = fopen("spielstand.dat", "rb");	// Create stream

	if (in == NULL) {
		printf("Datei konnte nicht geoeffnet werden!\n");
		return NULL;
	}
	else {
		fread(psize, sizeof(int), 1, in);
		//printf("Read Size: %d\n", *psize);	// [DEBUG]

		pplayground_tmp = allocate_memory(*psize);	// allocate memory for playground (does not work as void!)

		for (int row = 0; row < *psize; row++) {		// save karte-structs to allocated memory
			for (int col = 0; col < *psize; col++) {
				fread(&(pplayground_tmp[row][col]), sizeof(karte_t), 1, in);
			}
		}

	}

	fclose(in);	// close file

	for (int row = 0; row < *psize; row++) {
		for (int col = 0; col < *psize; col++) {
			printf("%c(%d) ", pplayground_tmp[row][col].id, pplayground_tmp[row][col].flag);
		}
		printf("\n");
	}

	

	return pplayground_tmp;
}

void save_playground(karte_t **pplayground, int size) {	// BUG?

	FILE *out = fopen("spielstand.dat", "wb"); // Create stream

	if (out == NULL) {
		printf("Datei konnte nicht geoeffent werden!\n");
	}
	else {
		fwrite(&size, sizeof(int), 1, out);
		//printf("Ausgabe: %d\n", size);	// DEBUG

		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				fwrite(&(pplayground[row][col]), sizeof(karte_t), 1, out);
			}
		}

	}

	fclose(out);

}