//////////////////////
//testCudaObj.cpp
//~Matthew Wade
//5/8/16
//////////////////////
//This code tests to see how CUDA handles objects.  Hopefully Cuda has
//access to all data within the object.  This program will involve
//test to see how CUDA handles simple objects, arrays of objects,
//and objects containing arrays.
//////////////////////
#include <cuda.h>
#include <iostream>
#include <stdio.h>
#include <vector>
//////////////////////
//Classes
class myArr
{
	public:
	int val[10][10];
	
	__device__ __host__ myArr()
	{
		for(int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				val[i][j] = i + j;
	}

	__device__ __host__ void getVal(int i, int j)
	{
		printf("VAL: %d\n", val[i][j]);
	}
};

/////////////////////////
//Kernel
__global__ void myKern(myClass *d_in){
	
	printf("INPUT: %d\n", d_in[0].val);
	d_in[0].Add();
	printf("RESULT: %f\n", d_in[0].result);	
	
	d_in[0].val = 4;
}

//////////////////////////
int main(){
	myClass Test(2, 3.4);
	myClass *pTest;
	
	size_t size = sizeof(myClass);
	cudaMalloc(&pTest, size);
	cudaMemcpy(pTest, &Test, size, cudaMemcpyHostToDevice);
	
	myKern<<<1,1>>>(pTest);

	cudaMemcpy(&Test, pTest, size, cudaMemcpyDeviceToHost);
	printf("VAL: %d\n", Test.val);

	return 0;
}
