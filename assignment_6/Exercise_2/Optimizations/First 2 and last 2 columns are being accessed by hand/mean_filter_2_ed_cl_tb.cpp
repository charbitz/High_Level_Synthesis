#include <iostream>
#include <cstdlib>
#include <ctime>

#include "mean_filter_2_ed_cl.h"

static const int RUNS = 10;

CCS_MAIN(int argc, char* argv[]) {
	pxl img[N][M];
	pxl out[N][M];
	
	MeanFilter mf;
	
//  reseed RNG :
//  	std::srand(std::time(NULL));
	
//	testbench :
	for(int k=0;k<RUNS;k++)
	{
		std :: cout << "~ ~ ~ ~ ~ Trial " << k << " ~ ~ ~ ~ ~" << endl << endl;
		
//		initial declaration of img with random numbers [0-255] :
 		for (int i=0;i<N;i++) 
		{
	      	for (int j=0;j<M;j++) 
			{
	        	img[i][j] = std :: rand() % 255;

	      	}
		}
		
//		printing array img :
		std :: cout << "img :" << endl << endl;
		
		for (int i=0;i<N;i++) 
		{
	      	for (int j=0;j<M;j++) 
			{
				std :: cout << img[i][j]<<"	";
				if (j == M-1)
				{
					std :: cout << endl;
				}	
			}	
		}
		
//		call mean_filter :
		mf.mean_filter(img, out);
		
		std :: cout << endl << endl;
		
	
//		printing array out :
		std :: cout << "out :" << endl << endl;
		
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				std::cout<<out[i][j]<<"	";
				if (j == M-1)
				{
					std :: cout << endl;
				}
				
			}
		}
	
		std :: cout << endl << endl;
	}
	
  CCS_RETURN(0);
}
