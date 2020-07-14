#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_NAME "test.dat"
#define uint32_t u_int32_t

int  arg_test(int argc, char **argv);
void conversion_test();
void load_data(int **int_array, uint32_t *array_size);
int  find_nth(int *int_array, uint32_t array_size, int n);
void print_array(uint32_t size, int *arr);

int main(int argc, char **argv)
{
    int valid = arg_test(argc, argv);
    // Test function for atoi
    conversion_test();
    
    int nth = -3;
 
    if(valid) {
        int *int_array = NULL;
        uint32_t array_size = 0;
        load_data(&int_array, &array_size);

        // This function prints the content of the array - debugging tool
        print_array(array_size, int_array);

        // Insert your code here (1)
	// easy way to take string to int type
        int n = strtol(argv[1], NULL, 10);
	// n is 0 if something other than int was given
	// .
	// ------------------------

        nth = find_nth(int_array, array_size, n);
        if(nth >= 0) {
            printf("---- Answer ----\n");
            printf("The nth value is %d\n", int_array[nth]);
            printf("--------\n");
        } else if(nth == -1) {
            printf("---- Answer ----\n");
            printf("n is too large!\n");
            printf("--------\n");
        } else if(nth == -2) {
            printf("---- Answer ----\n");
            printf("Some error!\n");
            printf("--------\n");
        } else {
            // Do nothing
        }
    } else {
        // Do nothing
    }
    
    return 0;
}



int arg_test(int argc, char **argv)
{
    int return_val = 0;
    if(argc < 2) {
        fprintf(stderr, "Error: no input entered\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else if(argc > 2) {
        fprintf(stderr, "Error: too many inputs\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else {
        return_val = 1;
    }
    return return_val;
}

void conversion_test()
{
    printf("---- ATOI Sample Usage ----\n");
    char *num_str = "101";
    int num = atoi(num_str);
    printf("The number is %d\n", num);
    printf("--------\n\n");
}

void load_data(int **int_array, uint32_t *array_size)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    int tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        cnt++;
    }
    fclose(fp);

    int *tmp_array = (int*) malloc(sizeof(int) * cnt);
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }
    cnt = 0;
    tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        tmp_array[cnt] = tmp;
        cnt++;
    }
    fclose(fp);
    
    *int_array = tmp_array;
    *array_size = cnt;
}

// Given n as input, find the nth largest value
// in the list of integers loaded from the file.
// If n is larger than the number of integers,
// return -1.
// Return -2 for any other errors.
// NOTE 1:
// The file used for grading will be different from
// the file given with the homework - it will have
// different number of integers and different integer
// values
int find_nth(int *int_array, uint32_t array_size, int n)
{
    // Insert your code here (2)
    if(n > array_size){
	return -1;
    }
    else if(n == 0){
	return -2;
    }
    // Im going to copy then sort the array then find the nth element

    // copy
    int i, j, max_index, temp;
    int *copy = malloc(sizeof(int)*array_size);
    for(i = 0; i < array_size; i++){
	copy[i] = int_array[i];	
    }
    for(i = 0; i < array_size -1; i++){
	max_index = i;
	for(j = i + 1; j < array_size; j++){
	    if(copy[j] > copy[max_index]){
		max_index = j;
	    }
	    else if(copy[j] == copy[max_index]){
		copy[j] = -2;
	    }
	}
	temp = copy[max_index];
	copy[max_index] = copy[i];
	copy[i] = temp;
    }

    // now i have a sorted array in copy so i find the value of the nth largest
    int nth_largest_ele = copy[n-1];
    if(nth_largest_ele == -2){
	return -2;
    }
    free(copy);
    
    for(i = 0; i < array_size; i++){
	if(int_array[i] == nth_largest_ele){
	    return i;
	}
    }
    // ------------------------

}

void print_array(uint32_t size, int *arr)
{
   printf("---- Print Array ----\n");
    printf("This file has %d elements\n", size);
    printf("#\tValue\n");
    for(int i = 0; i < size; i++) {
        printf("%d\t%d\n", i, arr[i]);
    }
   printf("--------\n\n");
}

