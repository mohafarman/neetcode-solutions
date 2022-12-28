#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

typedef struct vector {
	void **items;
	int capacity;
	int total;
} vector;

void
vector_init(vector *v) {
	v->capacity = CAPACITY;
	v->total = 0;
	v->items = malloc(sizeof(void *) * v->capacity);
}

void
print_index(int arr[], int index) {
	/* 
	 * Using pointer arithmetics
	 */
	int i;
	int *ptr;
	ptr = arr;
	for (i = 0; i < index; i++) {
		ptr++;
	}
	printf("Index = %d : %d\n", i, *ptr);
}

void
print_vector(vector *v) {
	int i;
	for (i = 0; i < v->total; i++) {
		printf("[%d] - %d\n", i, v->items[i]);
	}
}

int
vector_get_size(vector *v) {
	return v->total;
}

int
vector_get_capacity(vector *v) {
	return v->capacity;
}

void
vector_get_info(vector *v) {
	//int is_empty = vector_is_empty(&v);
	printf("--------\nVector capacity is: %d\nVector size is %d\n", v->capacity, v->total);
	//is_empty ? printf("Vector is not empty\n") : printf("Vector is empty\n");
	printf("--------\n");
}

void
*vector_get_index(vector *v, int index) {
	if (index < 0 && index > v->total) {
		return NULL;
	}
	return v->items[index];
}

int
vector_is_empty(vector *v) {
	if (v->total) {
		return 0;
	}
	return -1;
}

// Make this function private
static void
vector_add(vector *v, void *item){
	if (v->total == v->capacity) {
		// Resize to double size and try adding again
		vector_resize(v, v->capacity * 2);
		// Recursion
		vector_add(v, item);
	}
	v->items[v->total++] = item;
}

int
vector_insert(vector *v, int index, void *item){
	// Check that index is in valid range
	int i;
	if (!v || !v->items) {
		return -1;
	}
	if (index < 0 || index > v->total) {
		return -1;
	}
	if (index == v->total) {
		vector_add(v, item);
		return 0;
	}
	// Check capacity
	if (v->total == v->capacity) {
		return 0;
	}

	// Shift all indices after $index forward
	for (i = v->total; i > index; i--) {
		v->items[i] = v->items[i-1];
	}
	// Insert the item
	v->items[index] = item;
	// Increment the total
	v->total++;
	return 0;
}

int
vector_prepend(vector *v, void *item) {
	if (!vector_insert(v, 0, item)) {
		return 0;
	}
	return -1;
}

void
*vector_pop(vector *v) {
	if (!v || !v->items) {
		return NULL;
	}

	// Store the item to be popped so it can be returned
	void *item = v->items[v->total - 1];
	v->items[v->total] = NULL;
	//free(v->items[v->total]);
	v->total--;

	if (v->total < (v->capacity * 0.25)) {
		if(!vector_resize(v, v->capacity / 2)) {
			fprintf(stdout, "Vector resized by half\n");
		} else {
			fprintf(stderr, "Vector could not be resized by half\n");
			return NULL;
		}
	}
	return item;
}

int
vector_delete_index(vector *v, int index) {
	if (!v || !v->items) {
		return -1;
	} 
	else if (index < 0 || index > v->total) {
		return -1;
	}

	int i;
	v->items[index] = NULL;
	for (i = index; i < v->total; i++) {
		v->items[i] = v->items[i+1];
	}
	v->total--;
	return 0;
}

int
vector_delete_item(vector *v, void *item) {
	int i, k, found = 0;
	if (!v || !v->items ) {
		return -1;
	}

	for (i = 0; i < v->total; i++) {
		if (item == v->items[i]) {
			found++;
			vector_delete_index(v, i);
		}
	}

	if (found) {
		return 0;
	}
	return -1;
}
int
vector_find_item(vector *v, void *item) {
	int i, k, found = 0;
	if (!v || !v->items ) {
		return -1;
	}

	for (i = 0; i < v->total; i++) {
		if (item == v->items[i]) {
			return 0;
		}
	}
	return -1;
}

int vector_resize(vector *v, int capacity) {
	int i;
	void **items = malloc(sizeof(void *) * capacity);
	memcpy(items, v->items, sizeof(void*) * capacity);
	//items = realloc(v->items, sizeof(void*) * capacity);
	if (items != NULL) {
		v->items = items;
		v->capacity = capacity;
		items = NULL;
		return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {

	vector v;
	vector_init(&v);
	int i;

	int is_empty = vector_is_empty(&v);

	printf("Vector initialized.");
	vector_get_info(&v);

	vector_add(&v, 1);
	vector_add(&v, 2);
	vector_add(&v, 3);

	is_empty = vector_is_empty(&v);

	printf("Added values to vector.");
	vector_get_info(&v);

	print_vector(&v);

	int value = 4;
	if(!vector_insert(&v, 1, value)) {
		fprintf(stdout, "Inserted value '%d' in vector\n", value);
	} else {
		fprintf(stderr, "Failed to insert value '%d'\n", value);
	}

	print_vector(&v);

	vector_get_info(&v);

	vector_prepend(&v, 8);

	print_vector(&v);

	vector_get_info(&v);

	printf("Popped item: %d\n", vector_pop(&v));

	vector_get_info(&v);
	print_vector(&v);

	if (!vector_delete_index(&v, 1)) {
		fprintf(stdout, "Deleted index '%d' in vector\n", 1);
	} else {
		fprintf(stderr, "Failed to delete index '%d'\n", 1);
	}

	vector_get_info(&v);
	print_vector(&v);

	vector_add(&v, 5);
	vector_add(&v, 5);

	int item_to_delete = 5;

	vector_get_info(&v);
	print_vector(&v);

	if (!vector_delete_item(&v, item_to_delete)) {
		fprintf(stdout, "Deleted item '%d' in vector\n", item_to_delete);
	} else {
		fprintf(stderr, "Failed to delete item '%d'\n", item_to_delete);
	}

	vector_get_info(&v);
	print_vector(&v);

	if (!vector_find_item(&v, item_to_delete)) {
		fprintf(stdout, "Found item '%d' in vector\n", item_to_delete);
	} else {
		fprintf(stderr, "Failed to find item '%d in vector'\n", item_to_delete);
	}
	

	int resize_to = 15;
	if (!vector_resize(&v, resize_to)) {
		fprintf(stdout, "Vector resized to capacity '%d'\n", resize_to);
	} else {
		fprintf(stderr, "Vector failed to resize to capacity '%d'\n", resize_to);
	}
	vector_get_info(&v);

	for (i = 6; i < 20; i++) {
		vector_add(&v, i);
	}
	printf("Added values to vector.\n");

	vector_get_info(&v);
	print_vector(&v);

	for (i = 0; i < 16; i++) {
		printf("Popped item: %d\n", vector_pop(&v));
	}

	vector_get_info(&v);
	print_vector(&v);

	return 0;
}

