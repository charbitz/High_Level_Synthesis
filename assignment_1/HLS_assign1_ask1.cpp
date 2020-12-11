#include <iostream>
#include <stdlib.h> // it's for rand()
#include <time.h>   // it's for seeding the srand() 

//	Constant variable declration :
static const int RUNS = 10;

//	Datatypes definition :
typedef unsigned int uint;
typedef unsigned short int usint; 

//	Function which counts the sum of bits equal to 1 :
usint sum_of_ones (uint N)
{
	
	usint cnt;
	while (N != 0)
	{
		if(N%2 != 0)
		{
			cnt++;
		}
		
		N = N / 2 ;
	}
	return cnt;
}
 
int main()
{
//	using srand to change randomly the seed of rand() at any execution time
	srand(time(NULL));

//	Variable declration :	
	uint num;
	usint count;
	
//	Loop to run 10 tests :
	for(int k=0;k<RUNS;k++)
	{
		std::cout << "Trial " << k << "\n";
		num = rand() % 4294967296 ;
		count = sum_of_ones(num);
		std :: cout<<"Number :  "<<num<<"\n"<<"Count of 1s:  "<<count<<"\n\n";
	}
		
	return 0; 
}
