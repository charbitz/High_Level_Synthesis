#include<C:/Users/HP/Desktop/HLS_demos/ac_int.h>
#include<C:/Users/HP/Desktop/HLS_demos/ac_channel.h>
#include <stdlib.h> // it's for rand()
#include <time.h>   // it's for seeding the srand() 


using std::endl;

static const int W = 4;

typedef ac_int<W,false> Data_t ; 

void run_length_encode (ac_channel< Data_t >&in , ac_channel< Data_t >&out)
	{
		if (in.available(10))
		{
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
	srand(time(NULL));
	
	ac_channel< Data_t >in;
	ac_channel< Data_t >out;
	
	int random_num ;
	
//	write values in channel via in port :
//	std::cout<<"reading from main"<<endl;
//	for(int i=0;i<3;i++)
//	{
//		in.write(2);
//		in.write(as);
//		in.write(2);
//		in.write(2);
//		in.write(3);
//		in.write(12);
//		in.write(12);
//		in.write(1);
//		in.write(1);
//		in.write(5);
//		in.write(2);
//		in.write(2);
//		in.write(2);
//		in.write(2);
//		in.write(3);
//		in.write(12);
//		in.write(12);
//		in.write(1);
//		in.write(1);
//		in.write(5);
//		run_length_encode(in,out);
//
//	}
	
	
//	generate pseudo-random numbers :

	std::cout<<"reading from main rand()!!!"<<endl;
	
	for(int k=0;k<30;k++)
	{
		random_num = rand() % 16 ;		// in order not to wrap arround due to 4 bits limit
		std::cout<<"random_num is "<<random_num<<endl;
		in.write(random_num);
		run_length_encode(in,out);	
	}

	std::cout<<"writing to main"<<endl;
	
	do
	{
		std::cout<<out.read()<<endl;
	}
	while(out.available(1));

		
//	std::cout<<"reading to main"<<endl;
//	
//	for(int j=0;j<15;j++)
//	{
//		if(out.available(1) )
//		{
//			std::cout<<out.read()<<endl;			
//		}
//	}
	
	return 0;
}
