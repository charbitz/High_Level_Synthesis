
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <ac_int.h>

static const int N = 200;
static const int M = 250;
static const int RUNS = 10;
static const int n = 8;

typedef ac_int<n,false> pxl;

using std::endl;

class MeanFilter{
	private:
		pxl p1, p2, p3, p4, p5, p;
	public:
		MeanFilter()
		{
			p = 0;
		};
	
	void mean_filter(pxl img[N][M], pxl out[N][M])
	{
	
		ROW: for(int i=0;i<N;++i)
		{
			COL: for(int j=0;j<M;++j)
			{
				p1 = (j > 1)? img[i][j-2]: p;
				p2 = (j > 0)? img[i][j-1]: p;
				p3 = img[i][j];
				p4 = (j < M-1)? img[i][j+1]: p ;
				p5 = (j < M-2)? img[i][j+2]: p ;
				out[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
			}
		}	
	}

};


int main()
{
	pxl img[N][M];
	pxl out[N][M];
	
//  reseed RNG :
//  	std::srand(std::time(NULL));

	MeanFilter mf;
	
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
	
	return 0;
}
