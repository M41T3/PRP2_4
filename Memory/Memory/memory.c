/*
PRP2-2 Aufgabe 4.1
Name: Malte Müller, Fabian Liebold
Date: 09.12.2018
*/

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>	// Important for malloc, etc

typedef struct karte {
	char id;
	int flag;
} karte_t;

//Prototypes:
void get_size(int *psize);
karte_t **allocate_memory(int size);
void init_playground(karte_t **pplayground, int size);
void show_playground(karte_t **pplayground, int size);
void print_playground(karte_t **pplayground, int size, int found);
void flush_stdin();
void free_all(karte_t **pplayground, int size);
karte_t **load_playground(int *psize);
void save_playground(karte_t **pplayground, int size);

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

	char first_card[8];
	char second_card[8];
	char delim[2] = " ";
	int x1, y1, x2, y2;

	flush_stdin();
	system("cls");
	do {
			
			printf("Geben Sie die Koordinaten für die 1.Karte ein [Zeile Spalte] (-1 -1 für Abbruch): ");
			gets(first_card);
			
			printf("[DEBUG] string: %s\n", first_card);

			char *token = strtok(first_card, delim);

			x1 = atoi(token);
			token = strtok(NULL, delim);
			y1 = atoi(token);
			
			if (x1 == -1 && y1 == -1) break;
			else if (x1 == -2 && y1 == -2) {
				save_playground(pplayground, size);
				break;
			}

			pplayground[x1][y1].flag = 1;

			//printf("[DEBUG]1.  %d, %d\n", x1, y1);

			print_playground(pplayground, size, found);
		
			printf("Geben Sie die Koordinaten für die 2.Karte ein [Zeile Spalte] (-1 -1 für Abbruch): ");
			gets(second_card);

			token = strtok(second_card, delim);

			x2 = atoi(token);
			token = strtok(NULL, delim);
			y2 = atoi(token);

			if (x2 == -1 && y2 == -1) break;
			else if (x1 == -2 && y1 == -2) {
				save_playground(pplayground, size);
				break;
			}

			pplayground[x2][y2].flag = 1;

			//printf("[DEBUG]2.  %d, %d\n", x2, y2);

			print_playground(pplayground, size, found);

			if (pplayground[x1][y1].id == pplayground[x2][y2].id) found++;
			else {
				pplayground[x1][y1].flag = 0;
				pplayground[x2][y2].flag = 0;
			}

			if (found == (size*size) / 2) break;

	} while (1);


	free_all(pplayground, size);
	system("PAUSE");
	return 0;
}

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
void get_size(int *psize){
	printf("Wie gross soll das quadratische Spiel werden? \n");
	do {
		printf("Geben Sie eine gerade Zahl ein [2 - 10]: ");
		scanf(" %d",psize);
		flush_stdin();
	} while (*psize < 2 || *psize > 10 || *psize%2 == 1);
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

	for (int i = 0; i < size; i++) {
		pplayground[i] = (karte_t*)malloc(size * sizeof(karte_t));

		if (pplayground[i] == NULL) {
			for (int k = i; k >= 0; k--) {
				free(pplayground[k]);
			}
			free(pplayground);
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

	srand(time(NULL));
	
	int rand_row;
	int rand_col;
	char temp;

	//printf("\n[DEBUG] SWOAP:\n");

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			rand_col = rand() % size;
			rand_row = rand() % size;

			//printf("[%d][%d] %c -> ",row, col, pplayground[row][col].id);

			temp = pplayground[row][col].id;
			pplayground[row][col].id = pplayground[rand_row][rand_col].id;
			pplayground[rand_row][rand_col].id = temp;

			//printf("%c from [%d][%d] \n", pplayground[row][col].id, rand_row, rand_col);
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
		for (int col = 0; col < size; col++){

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
		free(pplayground[i]);
	}
	free(pplayground);
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

	// [DEBUG]:

	for (int row = 0; row < *psize; row++) {
		for (int col = 0; col < *psize; col++) {
			printf("%c(%d) ", pplayground_tmp[row][col].id, pplayground_tmp[row][col].flag);
		}
		printf("\n");
	}

	// ->|

	return pplayground_tmp;
}

void save_playground(karte_t **pplayground, int size) {	// BUG?

	FILE *out = fopen("spielstand.dat", "wb"); // Create stream

	if (out == NULL) {
		printf("Datei konnte nicht geoeffent werden!\n");
		return NULL;
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