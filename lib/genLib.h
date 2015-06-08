/////////////////////////////
//ClassCudaLib.h
//~Matthew Wade
//6/2/15
/////////////////////////////
//General library containing classes and structs associated
//with Cuda processing.  These classes will be designed in a 
//very general manner to ensure that they can be used in a variety
//of situations.
/////////////////////////////
#include <cuda.h>
#include <vector>
//Include guards
#ifndef CLASSCUDALIB_H
#define CLASSCUDALIB_H


/////////////////////////////
//gpuAssert (aka gpuErr)
/////////////////////////////
//Function serves as an error checker when running GPU code.
//Prints out error, file, and line where it occured.
//Code was taken from "Jason R. Mick"'s anwer on stackoverflow.
//url: stackoverflow.com/questions/9676441/cudas-cudamemcpytosymbol-throwsinvalid-argument-error
/////////////////////////////
__inline__ __host__ void gpuAssert(cudaError_t code, const char* file, int line){
	//set bool to decide whether to abort or not
	bool abort = false;
		
	//print error to stderr
	if (code != cudaSuccess){
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
	}	
	
	//if already decided to abort then exit code
	if (abort) exit(code);
}
//Define function that will actually call this function
#define gpuErr(ans) {gpuAssert((ans), __FILE__, __LINE__);}

/////////////////////////////
//wrap & unwrap
/////////////////////////////
//Two short functions that wrap and unwrap vectors from 2D 
//to 1D and back again.  Results are returned in the form of
//passed variable.  This is a slight issue as this method 
//requires large amounts of memory and can take a significant
//amount of time.
/////////////////////////////
void Unwrap (vector < vector<int> >& wrapped, vector<int>& unwrapped, int rows, int cols){
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			unwrapped[i*cols + j] = wrapped [i][j];
}

void Wrap (vector<int>& unwrapped, vector <vector <int> > & wrapped. int rows, int cols){
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			wrapped[i][j] = unwrapped[i*cols + j];
}

/////////////////////////////
//GenTestArray
/////////////////////////////
//Generates massive table using nested for loops.
//Returns the massive table and nothing else.  It is
//assumed that the test function calculates totals. This 
//function is designed a test case when programming a 
//CUDA Kernel.
//NOTE: This function is not written to be fast!
//	It is written to give a simple result!
/////////////////////////////
double** GenTestArray(int rows, int cols)
{
	double** arr;
	arr = new double*[rows];
	
	for (int j = 0; j < rows; j++){
		arr[j] = new double[cols];
		for (int i = 0; i < cols; i++){
			arr[j][i] = (double)(i + j);
		}
	}
	return arr;
}

//END INCLUDE GUARDS
#endif
