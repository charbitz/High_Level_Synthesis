#include<ac_int.h>
#include<ac_channel.h>
#include <stdlib.h> // it's for rand()
#include <time.h>   // it's for seeding the srand() 


using std::endl;

static const int W = 4;
static const int RUNS = 10;

typedef ac_int<W,false> Data_t ; 

void run_length_encode (ac_channel< Data_t >&in , ac_channel< Data_t >&out)
	{
		if (in.available(10))
		{
//			we need to represent only numbers from 0 to 10 , so 4 bits will be ok (we don't need an int cnt)
			Data_t cnt = 1;	//the existence of a number means min count = 1
			
//			array of ac_int:
			Data_t arr[10];
			
			
//			loop to store the data from the channel to the array :
			for(int i=0;i<10;i++)
			{
				arr[i] = in.read();
			}
			
//			loop to check consecutively numbers :	
			for(int j=0;j<9;j++)
			{
				if(arr[j]==arr[j+1])
				{
					cnt +=1;
				}
				else
				{
					out.write(arr[j]);
					out.write(cnt);
					cnt = 1;	
				}
			}
//			last element ( arr[9] ) must be written to the channel ;
			out.write(arr[9]);
			
//			in case arr[8] = arr[9] count_written = count of arr[8] elements ,
//			in case arr[8] != arr[9] count_written = 1 :
			out.write(cnt);
		}
	}

int main()
{
//	srand(time(NULL));
	
	ac_channel< Data_t >in;
	ac_channel< Data_t >out;
	
	int random_num[10] ;
	
//	Testbench :
	for (int i=0;i<RUNS;i++)
	{
		std::cout<<" ~ ~ ~ Trial "<<i<<" ~ ~ ~ "<<endl;
		
		std::cout<<" random_num : "<<endl;
		for(int k=0;k<10;k++)
		{
			random_num[k] = rand() % 16 ;		// in order not to wrap arround due to 4 bits limit
			std::cout<<random_num[k]<<" ";
		}
		std::cout<<endl<<endl;
		
		for(int k=0;k<10;k++)
		{
			in.write(random_num[k]);	
		}
		
		for(int k=0;k<10;k++)
		{
			run_length_encode(in,out);		
		}
		
		std::cout<<" out : "<<endl;
		do
		{
			std::cout<<out.read()<<" ";
		}
		while(out.available(1));
		std::cout<<endl<<endl<<endl<<endl;		
	}

	return 0;
}
