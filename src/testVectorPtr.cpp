/////////////////////////
//testVectorPtr.cpp
//~Matthew Wade
//6/5/15
////////////////////////
//This is a short program to test and see if data
//within a vector an be modified by generating pointer
//to vector's memory array and performing operations
//on that array.  Ideally changes in the memory array
//should be reflected in the vector.  If this is true
//it will be possible to pass memory array of a 
//vector to a CUDA kernel and allow opertations to be
//performed on that array while maintaining structure of
//vector.
////////////////////////
#include <vector>
#include <stdio.h>
#include <time.h>

using namespace std;

////////////////////////
//Prototypes
void Unwrap (vector< vector<int> >& wrapped, vector<int>& unwrapped, int rows, int cols);
void Wrap (vector<int>& unwrapped, vector< vector<int> >& wrapped, int rows, int cols);
////////////////////////
//Main program

int main(){
	//Declare timer
	clock_t start;
	double duration;

	//Declare sizes
	int rows = 10000;
	int cols = 100;
	int tmp;
	//Declare vector and fill with 0s
	vector < vector<int> > myWrapVec (rows, vector<int>(cols));
	vector <int> myVec (rows * cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j<cols; j++)
			myWrapVec[i][j] = (i+j);
	
	//Start timer and call unwrap
	start = clock();
	Unwrap(myWrapVec, myVec, rows, cols);	

	//Print test value
	tmp = myVec[0];
	printf("TEST 1: %d\n", tmp);


	//Initialize array and set it equal to vector location
	int* myArr = myVec.data();
	myArr[0] = 99;

	//print test value
	tmp = myVec[0];
	printf("TEST 2: %d\n", tmp);
	
	//Convert back to 2D and write test 3
	Wrap(myVec, myWrapVec, rows, cols);
	tmp = myWrapVec[0][0];
	printf("TEST 3: %d\n", tmp);

	//End timer and print result
	duration = (clock() - start)/(double) CLOCKS_PER_SEC * 1000;
	printf("TIME: %fms\n", duration);

	return 0;
}

////////////////////
//Functions
void Unwrap (vector< vector<int> >& wrapped, vector<int>& unwrapped, int rows, int cols){
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			unwrapped[i*cols + j] = wrapped[i][j];
}

void Wrap (vector<int>& unwrapped, vector< vector<int> >& wrapped, int rows, int cols){
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			wrapped[i][j] = unwrapped[i*cols + j];
}

