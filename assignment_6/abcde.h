#ifndef ABCDE_H
#define ABCDE_H

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <ac_int.h>

#include "mc_scverify.h"

static const int N = 10000;
static const int RUNS = 10;

typedef ac_int<8,false> num;
typedef ac_int<16,true> num_A;

using std::endl;

#pragma hls_design top
class ABCDE{
	private:
	public:
		ABCDE(){};
		

#pragma hls_design interface
void CCS_BLOCK (abcde)(num_A A[N], num B[N], num C[N], num D[N], num E[N])
{
	for (int i=0; i < N; i++)
	{
		A[i] = (B[i]*C[i] ) - ( D[i]*E[i]);
	}
}

	
};

#endif

