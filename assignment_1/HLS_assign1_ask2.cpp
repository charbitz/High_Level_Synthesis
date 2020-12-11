#include <iostream>
#include <math.h>	//pow()
#include <stdlib.h> // it's for rand()
#include <time.h>   // it's for seeding the srand() 

static const int RUNS = 10;

typedef unsigned int uint ;

uint checksum (uint N)
{
	uint ch_sum;
	uint digits;
	
//	array to store my decimal digits of number N :
	uint arr_dec_dig[10] = {0,0,0,0,0,0,0,0,0,0};
	
	if(N<=9) 
	{
		digits = 1;
	}
	else if(9<N && N<=99)
	{	
		digits = 2;
	}
	else if(99<N && N<=999)
	{
		digits = 3;
	}
	else if(999<N && N<=9999)
	{
		digits = 4;
	}
	else if(9999<N && N<=99999)
	{
		digits = 5;
	}
	else if(99999<N && N<=999999)
	{
		digits = 6;
	}
	else if(999999<N && N<=9999999)
	{
		digits = 7;
	}
	else if(9999999<N && N<=99999999)
	{
		digits = 8; 
	}
	else if(99999999<N && N<=999999999)
	{
		digits = 9;
	}
	else
	{
		digits = 10;
	}
	
//	std :: cout<<"Digits :"<<digits<<"\n";
	
	for(int i=1 ; i<digits + 1 ; i++)
	{
		arr_dec_dig[digits-i] = N / (pow(10 , digits-i));
		N = N - arr_dec_dig[digits-i] * pow(10 , digits-i);
	}
	
	
	ch_sum = 0;
	
	
	for (int i =0;i<digits;i++)
	{
//		for even arr_dec_dig cells :
		if(i%2==0)
		{
			ch_sum = ch_sum + arr_dec_dig[i];
		}
		else 
//		for odd arr_dec_dig cells :
		{
//			for 1 digit mult (2* )
			if (2*arr_dec_dig[i]<=9)
			{
				ch_sum = ch_sum + 2 * arr_dec_dig[i];
			}
			else
//			for 2 digits mult (2* )
			{
				ch_sum = ch_sum + (2*arr_dec_dig[i] / 10) + 2*arr_dec_dig[i] - (2*arr_dec_dig[i] / 10) * 10;
			}	
		}
	}
	
	return ch_sum ;

}

 
int main()
{
	srand(time(NULL));
	
	uint ch_s;
	uint random_num;
	
//	Loop to run 10 tests :
	for(int i=0;i<RUNS;i++)
	{
		std::cout << "Trial " << i << "\n";
		random_num=rand() % 4294967296 ;
		ch_s = checksum(random_num);
		std :: cout<<"Number :  "<<random_num<<"\n"<<"Checksum :  "<<ch_s<<"\n\n";	
	}
		
	return 0;	
}
