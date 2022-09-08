#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void print_error_message();
void matrix_print(int **, const int, const  int);
void matrix_print_ull(unsigned long long **, const int, const int);
int **matrix_alloc(const int,const int);
unsigned long long**matrix_alloc_ull(const int, const int);
void init_random(int **, const int, const int);
int *row_vector(int **, const int);
int *col_vector(int **, const int, const int);
unsigned long long inner_product(int *,int*, const int);
unsigned long long**matrix_mult(int **,int **, int, int, int);

int main(int argc, char *argv[]){
	if(argc != 4){
		print_error_message();
		exit(1);
	}
	else if( atoi(*(argv+1))<1 || atoi(*(argv+2))<1 || atoi(*(argv+3))<1){
		print_error_message();
		exit(1);
	}
		
	int i;

	const int a = atoi(*(argv+1));
	const int b = atoi(*(argv+2));
	const int c = atoi(*(argv+3));

	int **M = matrix_alloc(a,b);
	int **N = matrix_alloc(b,c);

	srand(time(NULL));

	init_random(M,a,b);
	printf("\nmatrix M: \n");
	matrix_print(M,a,b);
	
	init_random(N,b,c);
	printf("\nmatrix N: \n");
	matrix_print(N,b,c);

	unsigned long long**L = matrix_mult(M, N,a, b, c);	
	
	printf("\nmatrix L = M*N: \n");
	matrix_print_ull(L,a,c);

	free(M);
	free(N);
	free(L);
	
	return 0;
}

void print_error_message(){
		printf("ARGUMENT ERROR!\n");
		printf("argument description:\n");
		printf("[exe_file_name] [first_matrix_row_numbers(>0)] [first_matrix_column_numbers(>0)] [second_matrix_column_numbers(>0)]\n");
}
	
int **matrix_alloc(const int r, const int c){
	int **M = (int **)malloc(r*sizeof(int *));
	int i;
	for(i=0; i<r; ++i){
		*(M+i) = (int *)malloc(c*sizeof(int));
	}
	return M;
}

unsigned long long **matrix_alloc_ull(const int r, const int c){
	unsigned long long**L = (unsigned long long**)malloc(r*sizeof(unsigned long long*));
	int i;
	for(i=0; i<r; ++i) *(L+i) = (unsigned long long*)malloc(c*sizeof(unsigned long long));
	return L;
}


void matrix_print(int **M, const int r, const int c){
	int i,j;
	printf("address: %p\n",M);
	printf("elements: \n");
	for(i=0; i<r; ++i){
		for(j=0; j<c; ++j){
			printf("%-11d",*(*(M+i)+j));
		}
		printf("\n");
	}
}

void matrix_print_ull(unsigned long long**M, const int r, const c){
	int i,j;
	printf("address: %p\n",M);
	printf("elements: \n");
	for(i=0; i<r; ++i){
		for(j=0; j<c; ++j){
			printf("%-21llu",*(*(M+i)+j));
		}
		printf("\n");
	}
}

void init_random(int **M, const int r, const int c){
	int i, j;
	for(i=0; i<r; ++i){
		for(j=0; j<c; ++j){
			*(*(M+i)+j) = (int)(rand()%10000+1);
		}
	}
}

int *row_vector(int **M, const int r_ind){
	return *(M+r_ind);
}

int *col_vector(int **M, const int c_ind, const int row_num){
	int i;
	int *c_vec = (int *)malloc(row_num*sizeof(int));
	for(i=0; i<row_num; ++i){
		*(c_vec+i) = *(*(M+i)+c_ind);
	}
	return c_vec;
}

unsigned long long inner_product(int *v1, int *v2, const int size){
	unsigned long long e1, e2, result = 0;
	int i;
	for(i = 0; i< size; ++i){
		e1 = *(v1+i);
		e2 = *(v2+i);
		result += e1*e2;
	}
	return result;
}

unsigned long long**matrix_mult(int **M, int **N, const int a, const int b, const int c){
	int *r_vec, *c_vec;
	int i,j;
	unsigned long long **L = matrix_alloc_ull(a,c);
	for(i=0; i<a; ++i){
		r_vec = row_vector(M,i);
		for(j=0; j<c; ++j){
			c_vec = col_vector(N,j,b);
			*(*(L+i)+j) = inner_product(r_vec,c_vec,b);
			free(c_vec);
		}
	}
	return L;
}
