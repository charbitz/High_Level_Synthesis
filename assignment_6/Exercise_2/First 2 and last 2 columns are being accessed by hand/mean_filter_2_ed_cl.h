#ifndef MEAN_FILTER_2_ED_CL_H
#define MEAN_FILTER_2_ED_CL_H


#include <ac_int.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "mc_scverify.h"

static const int N = 10;
static const int M = 10;
//static const int RUNS = 10;


typedef ac_int<8,false> pxl;

using std::endl;

#pragma hls_design top	
class MeanFilter{
private:
	pxl p1, p2, p3, p4, p5;
public:
	MeanFilter(){};

#pragma hls_design interface
void CCS_BLOCK(mean_filter)(pxl img[N][M], pxl out[N][M])
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

#endif
