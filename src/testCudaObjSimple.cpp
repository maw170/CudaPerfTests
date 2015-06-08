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
class myClass
{
	public:
	int val;
	float flo;
	float result;

	__device__ __host__ myClass()
	{
		val = 1;
		flo = 1.5;
	}
	__device__ __host__ myClass(int a, float b)
	{
		val = a;
		flo = b;
	}

	__device__ __host__ void Add()
	{
		result = (float) val + flo;
	}

	__device__ __host__ ~myClass(){};

};

/////////////////////////
//Kernel
__global__ void myKern(myClass *d_in){
	
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	
	printf("INPUT: %d\n", d_in[tid].val);
	d_in[tid].Add();
	printf("RESULT: %f\n", d_in[tid].result);	
	
	d_in[tid].val = 4 + tid;
}

//////////////////////////
int main(){
	myClass Test[4];
	myClass *pTest;
	
	size_t size = 4 * sizeof(myClass);
	cudaMalloc(&pTest, size);
	cudaMemcpy(pTest, &Test[0], size, cudaMemcpyHostToDevice);
	
	myKern<<<1,4>>>(pTest);

	cudaMemcpy(&Test[0], pTest, size, cudaMemcpyDeviceToHost);
	printf("VAL: %d\n", Test[3].val);

	return 0;
}
