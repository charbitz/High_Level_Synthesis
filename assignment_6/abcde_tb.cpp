#include <iostream>
#include <cstdlib>
#include <ctime>

#include "abcde.h"

//static const int N = 10000;
//static const int RUNS = 10;

typedef ac_int<8,false> num;
typedef ac_int<16,true> num_A;

using std::endl;

CCS_MAIN(int argc, char* argv[])
{
	num_A A[N];
	num B[N];
	num C[N];
	num D[N];
	num E[N];
	
//  reseed RNG :
//  	std::srand(std::time(NULL));
		
	ABCDE ob;
//	testbench :
	for(int k=0;k<RUNS;k++)
	{
		std :: cout << "~ ~ ~ ~ ~ Trial " << k << " ~ ~ ~ ~ ~" << endl << endl;
		
//		initial declaration of matrices B,C,D,E with random numbers [0-255] :
 		for (int i=0;i<N;i++) 
		{
	        B[i] = std :: rand() % 255;
			C[i] = std :: rand() % 255;
			D[i] = std :: rand() % 255;
			E[i] = std :: rand() % 255;
		}
		
//		printing matrices B,C,D,E :
			
		std :: cout << "matrix B :\t";
		for (int i=0;i<N;i++)
		{
			std :: cout << B[i] << "\t";
		}
		std :: cout << endl << endl;
		
		std :: cout << "matrix C :\t";
		for (int i=0;i<N;i++)
		{
			std :: cout << C[i] << "\t";
		}
		std :: cout << endl << endl;
		
		std :: cout << "matrix D :\t";
		for (int i=0;i<N;i++)
		{
			std :: cout << D[i] << "\t";
		}
		std :: cout << endl << endl;
		
		std :: cout << "matrix E :\t";
		for (int i=0;i<N;i++)
		{
			std :: cout << E[i] << "\t";
		}
		std :: cout << endl << endl;
		
//		call abcde :
		ob.abcde(A, B, C, D, E);
		
		std :: cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
		
//		printing matrix A :
		std :: cout << "matrix A :\t";
		for (int i=0;i<N;i++)
		{
			std :: cout << A[i] << "\t";
		}
		std :: cout << endl << endl << endl;
	}
	
	CCS_RETURN(0);
}
