//#include<C:/Users/HP/Desktop/HLS_demos/ac_int.h>
//#include<C:/Users/HP/Desktop/HLS_demos/ac_channel.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "mc_scverify.h"

static const int V = 5;
static const int RUNS = 10;

typedef ac_int<V,false> data_t;
typedef ac_int<1,false> sbit;

using std::endl;

#pragma hls_design top
void graph_color(data_t Adj_G[V], int temp[V])
{
	NODES:for(int i=0;i<V;i++)
	{
		int c = 1;	
		ADJ_NODES:for(int j=V-1;j>=0;j--)
		{
			if(Adj_G[i].slc<1>(j) == 1 & temp[V-j-1] == c)
			{
				c = c + 1;
			}
		}
		temp[i] = c;
	}
}



CCS_MAIN(int argc, char* argv[]) {	

	std::srand(std::time(NULL));
			
  	data_t adj_matrix[V];
	

//  helper for set_slc
  	sbit hlpr = 0;

//  random bits	
  	sbit r = 0;
  
  
	for(int w=0;w<RUNS;w++)
	{
		int temp[V]={0,0,0,0,0};
		
		std::cout<<"Trial "<<w<<endl;
		std::cout<<"r = ";
		//	first pass for declaring the elements above the diagonal :
		for(int i=0;i<V;i++)
		{
			for(int j=0;j<V;j++)
			{  
			 	if(i==V-j-1)
				{
					adj_matrix[i].set_slc(j,hlpr);	
				} 
				else if(i<V-j-1)
				{
					r = std::rand() % 2;
					std::cout<<r<<"  ";
					adj_matrix[i].set_slc(j,r);
				}
				
			}
			
		}
		std::cout<<endl<<endl;
	//	Second pass to copy the elements :
	
		for(int i=0;i<V;i++)
		{
			for(int j=0;j<V;j++)
			{ 
				if(i>V-j-1)
				{
					adj_matrix[i].set_slc(j,adj_matrix[V-j-1].slc<1>(V-i-1));	
				}
			}	
			
		}
	
	//	Print the random generated array :
		for(int d=0;d<V;d++)
		{
			for (int k=V-1;k>=0;k--)
			{
				std::cout<<adj_matrix[d].slc<1>(k)<<"\t";
			}	
			std::cout<<endl;
		}
		
		
//		Call graph_color() :
		graph_color( adj_matrix , temp);
		
		
//		Print color arrays :
		
		std::cout<<"Colors : ";
		for (int i=0;i<V;i++)
		{
			std::cout<<temp[i]<<" ";
		}
		std::cout<<endl;
		
////		had to clear the values of temp :
//		for(int v=0;v<V;v++)
//		{
//			temp[v] = 0;	
//		}
		
	}
	
  CCS_RETURN(0);
}


