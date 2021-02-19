
#include <ac_int.h>
#include <iostream>
#include <cstdlib>
#include <ctime>



static const int N = 10;
static const int M = 10;
static const int RUNS = 10;


typedef ac_int<8,false> pxl;

using std::endl;
	
class MeanFilter{
private:
	pxl p1, p2, p3, p4, p5;
public:
	MeanFilter(){};

				/* OLD CODE */

//void mean_filter(pxl img[N][M], pxl out[N][M])
//{
//	pxl p1, p2, p3, p4, p5;
//	pxl p = 0;
//	
//	ROW: for(int i=0;i<N;++i)
//	{
//
//		COL: for(int j=0;j<M;++j)
//		{
//			p1 = (j > 1)? img[i][j-2]: p;
//			p2 = (j > 0)? img[i][j-1]: p;
//			p3 = img[i][j];
//			p4 = (j < M-1)? img[i][j+1]: p ;
//			p5 = (j < M-2)? img[i][j+2]: p ;
//			out[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
//		}
//	}	
//}

void mean_filter(pxl img[N][M], pxl out[N][M])
{
	pxl p1, p2, p3, p4, p5;
		
	ROW: for(int i=0;i<N;++i)
	{
		p1 = 0;
		p2 = 0;
		p3 = img[i][0];
		p4 = img[i][1];
		p5 = img[i][2];
		out[i][0] = (p1 + p2 + p3 + p4 + p5) / 5;
		
		p2 = img[i][0];
		p3 = img[i][1];
		p4 = img[i][2];
		p5 = img[i][3];
		out[i][1] = (p1 + p2 + p3 + p4 + p5) / 5;
		
		COL: for(int j=2;j<M-2;++j)
		{
			p1 = img[i][j-2];
			p2 = img[i][j-1];
			p3 = img[i][j];
			p4 = img[i][j+1];
			p5 = img[i][j+2];
			out[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
		}
		
		p5 = 0;
		
		p1 = img[i][M-4];
		p2 = img[i][M-3];
		p3 = img[i][M-2];
		p4 = img[i][M-1];
		out[i][M-2] = (p1 + p2 + p3 + p4 + p5) / 5;
		
		p4 = 0;
		p1 = img[i][M-3];
		p2 = img[i][M-2];
		p3 = img[i][M-1];
		out[i][M-1] = (p1 + p2 + p3 + p4 + p5) / 5;
	}	
}

};


int main(){
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
	
  return 0;
}

