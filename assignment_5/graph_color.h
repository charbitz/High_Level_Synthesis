#ifndef GRAPH_COLOR_H
#define GRAPH_COLOR_H

#include<C:/Users/HP/Desktop/HLS_demos/ac_int.h>
#include<C:/Users/HP/Desktop/HLS_demos/ac_channel.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <ac_int.h>

#include "mc_scverify.h"

static const int V = 5;
static const int RUNS = 10;

typedef ac_int<V,false> data_t;
typedef ac_int<1,false> sbit;

using std::endl;

#pragma hls_design top
class GraphColor {
private:
public:
  GraphColor(){};

#pragma hls_design interface
void CCS_BLOCK(graph_color)(data_t Adj_G[V], int colors[V]) {
  
  NODES:for(int i=0;i<V;i++)
	{
		int c = 1;	
		ADJ_NODES:for(int j=V-1;j>=0;j--)
		{
			if(Adj_G[i].slc<1>(j) == 1 & colors[V-j-1] == c)
			{
				c = c + 1;
			}
		}
		colors[i] = c;
	}
}

};

#endif
