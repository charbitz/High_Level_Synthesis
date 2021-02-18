#ifndef MEAN_FILTER_NEW_H
#define MEAN_FILTER_NEW_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ac_int.h>

#include "mc_scverify.h"

static const int N = 200;
static const int M = 250;
static const int RUNS = 10;
static const int n = 8;

typedef ac_int<n,false> pxl;

using std::endl;

#pragma hls_design top
class MeanFilter{
	private:
		pxl p1, p2, p3, p4, p5, p;
		pxl temp[M];
	public:
		MeanFilter()
		{
			p = 0;
		};

#pragma hls_design interface
void CCS_BLOCK(mean_filter)(pxl img[N][M], pxl out[N][M])
{

	ROW: for(int i=0;i<N;++i)
	{
		BUF_INIT: for(int k=0;k<M;++k)
		{
			temp[k] = img[i][k];
		}
		
		COL: for(int j=0;j<M;++j)
		{
			p1 = (j > 1)? temp[j-2]: p;
			p2 = (j > 0)? temp[j-1]: p;
			p3 = temp[j];
			p4 = (j < M-1)? temp[j+1]: p ;
			p5 = (j < M-2)? temp[j+2]: p ;
			out[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
		}
	}	
}

};

#endif
