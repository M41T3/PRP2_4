#pragma once

#ifndef memory_utilities
#define memory_utilities
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

#endif // !memory_utilities
