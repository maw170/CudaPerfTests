/////////////////////////
//testCudaMultiCpy.cpp
//~Matthew Wade
//6/8/15
/////////////////////////
//Short program quickly tests the time diffrence between copying
//multiple values in a single array versus copying those values
//individually.  The results from this test will determine whether
//or not I will end up using an object(struct) of arrays or an 
//array of objects(structs).
/////////////////////////
//RESULT:
//TIME 1 = 343.766
//TIME 2 = 0.2000
#include <stdio.h>
#include <cuda.h>
#include <time.h>
#include <iostream>

using namespace std;

/////////////////////////
int main(){
	
	int col1 [10000];
	int col2 [10000];
	int col3 [10000];
	int arr [10000][3];

	for (int i = 0; i<10000; i++){
		col1[i] = 10;
		col2[i] = 12;
		col3[i] = 42;
		for (int j = 0; j<3; j++)
			arr[i][j] = i+j;
		printf("%d %d %d %d\n", col1[i], col2[i], col3[i], arr[i][2]);
	}

	size_t size1 = sizeof(int) * 10000;
	size_t size2 = sizeof(int) * 10000 * 3;

	int *pcol1, *pcol2, *pcol3, *parr;

	clock_t start;
	double duration;


	printf("START ALLOCATION\n");
	start = clock();
	cudaMalloc(&pcol1, size1);
	cudaMalloc(&pcol2, size1);
	cudaMalloc(&pcol3, size1);
	cudaMemcpy(pcol1, &col1, size1, cudaMemcpyHostToDevice);
	cudaMemcpy(pcol2, &col2, size1, cudaMemcpyHostToDevice);
	cudaMemcpy(pcol3, &col3, size1, cudaMemcpyHostToDevice);
	duration = (clock() - start)/(double) CLOCKS_PER_SEC * 1000;

	printf("TIME 1: %f\n", duration);

	start = clock();
	cudaMalloc(&parr, size2);
	cudaMemcpy(parr, &arr, size2, cudaMemcpyHostToDevice);
	duration = (clock() - start)/(double) CLOCKS_PER_SEC * 1000;

	printf("TIME 2: %f\n", duration);
	return 0;
}
