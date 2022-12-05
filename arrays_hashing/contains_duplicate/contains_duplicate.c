#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
 */

bool contains_dupl(int arr[], int len) {
	int i, k, count;
	
	int *arr_copy = (int*)malloc(sizeof *arr);
	memcpy(&arr_copy, &arr, sizeof arr);

	for (i = 0; i < len; i++) {
		printf("checking: %i\n", arr_copy[i]);
		count = 0;
		for (k = 0; k < len; k++) {
			printf("currently: %i\n", arr[i]);
			if (arr_copy[i] == arr[k]) {
				count++;
				if (count == 2) {
					return true;
				}
			}
		}
	}

	return false;
}

int main (int argc, char *argv[]) {
	//int arr[] = {1, 3, 2, 4, 5, 4};	// True
	//int arr[] = {1, 2, 3, 4};			// False
	int arr[] = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};	// True
	int len;

	len = sizeof(arr) / sizeof(arr[0]);

	if (!contains_dupl(arr, len)) {
		printf("false\n");
		return 1;
	}
	printf("true\n");
	return 0;
}
