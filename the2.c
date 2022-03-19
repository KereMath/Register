#include <stdio.h>
#include <stdlib.h>
#include "the2.h"

/* prints content of the storage */
void print_storage(int** storage, int IA_size, int* DA_sizes){
    int i, j;
    for(i=0;i<IA_size;i++){
        printf("%d -> ",i);
        for(j=0;j<(DA_sizes[i]-1);j++){
            printf("%d ",storage[i][j]);
        }
        printf("%d\n",storage[i][j]);
    }
}

/* initialize a 2D dynamic array with given sizes, allocates an array 
   to keep data array sizes in the main function */
int** initialize_storage(int IA_size, int DA_size, int** DA_sizes){
	int ** storage;
	int i,j;
	storage = malloc(IA_size * sizeof(int *));
	for (i = 0; i<IA_size; i++) {
	    storage[i] = malloc(DA_size * sizeof(int));
	    for(j =0;j<DA_size;j++){
	        storage[i][j] = 0;
	    }
	}
	*DA_sizes = malloc(IA_size * sizeof(int*));
	
	
	for (i = 0; i<IA_size; i++) {
	        DA_sizes[0][i] = DA_size;
	}	

	return storage; 
}

/* transforms given person name to name code */
int transform_name(char* name){
    char *loop_var;
    int cumulative, index;
    cumulative = 0;
    loop_var = name;
    index = 1;
    while(*loop_var) {
        cumulative += index * index * (*loop_var);
        loop_var++;
        index++;
    }
	return cumulative;
}

/* inserts given person name into storage, extends corresponding data array if it is full.
   updates data sizes array in case. */
void insert(int** storage, int IA_size, char* text, int* DA_sizes){
	int name = transform_name(text);
	int name_index = name%IA_size;
	int i,j;
	
	for(i = 0;i< DA_sizes[name_index];i++){
	    if(!storage[name_index][i]){
	        break;
	    }
	    else{ continue; }
	}
	if(i == DA_sizes[name_index]){
	    storage[name_index] = realloc(storage[name_index], (DA_sizes[name_index] << 1));
	    DA_sizes[name_index] <<= 1;
	    for(j = i+1; j< DA_sizes[name_index];j++){
	        storage[name_index][j] = 0;
	    }
	}
    storage[name_index][i] = name;
}

/* chechs if need extending the storage. initialize a new one with doubled size in case.
   allocates a new data array sizes, fills new storage, updates data array sizes and
   frees old storage and data array sizes. */
void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes){
    int i,j,sum=0,old_ia;
    int ** some_storage;
    int * some_DA;
    for(i=0;i< *IA_size; i++){
        
        sum += DA_sizes[0][i];
    }
    
    if((double)sum < (double)(DA_size*(*IA_size) * 1.5)){
        return;
    }
    
    old_ia   = (*IA_size); 
    *IA_size = ((*IA_size)<< 1);
    some_storage = *storage;
    some_DA = *DA_sizes;
	*storage = malloc((*IA_size) * sizeof(int *));
	*DA_sizes = malloc( (*IA_size) * sizeof(int ));
	
	for(i=0;i< (*IA_size); i++){
	    
	    DA_sizes[0][i] = DA_size;
	    
	    for(j = 0; j< DA_size; j++){
	        storage[0][i] = malloc(DA_size * sizeof(int));
	        storage[0][i][j] = 0;
	    }
	}
	for(i=0;i<old_ia;i++){
	    for(j = 0; j<some_DA[i];j++){
	        if(!some_storage[i][j]) continue;
	        
	        insert2(*storage,(*IA_size),some_storage[i][j],*DA_sizes);
	    }
	}
	free(some_storage);
	free(some_DA);
}

/* transfers all the content in the old storage to the new one using insert2 function. */
void fill_new_storage(int** old_storage, int old_IA_size, int* old_DA_sizes, int** new_storage, int* new_DA_sizes){
	/* write your code here */	
}

/* inserts given code name into storage, extends corresponding data array if it is full.
   updates data sizes array in case. */
void insert2(int** storage, int IA_size, int name_code, int* DA_sizes){
	/* write your code here */
	int name_index = name_code%IA_size;
	int i,j;
	
	for(i = 0;i< DA_sizes[name_index];i++){
	    if(!storage[name_index][i]){
	        break;
	    }
	    else{ continue; }
	}
	if(i == DA_sizes[name_index]){
	    storage[name_index] = realloc(storage[name_index], (DA_sizes[name_index] << 1));
	    DA_sizes[name_index] <<= 1;
	    for(j = i+1; j< DA_sizes[name_index];j++){
	        storage[name_index][j] = 0;
	    }
	}
    storage[name_index][i] = name_code;
}