#include <iostream>
#include <stdlib.h> // it's for rand()
#include <time.h>   // it's for seeding the srand() 

unsigned short int sum_of_ones (unsigned int N)
{
	
	unsigned short int cnt;
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

//	variable declration :	
	unsigned int num;
	unsigned short int count;
		
//	generate random unsigned integers :
	for(int i=0;i<10;i++)
	{
		num = rand() % 4294967296 ;
		count = sum_of_ones(num);
		std :: cout<<"number :"<<num<<"\t"<<"count :"<<count<<"\n";
	}
		
	return 0;
}
