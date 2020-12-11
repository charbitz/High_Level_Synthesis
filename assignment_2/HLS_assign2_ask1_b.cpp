#include <iostream>
#include<ac_fixed.h>

using std::endl;

int main()
{
	ac_fixed <5,2,false> f; 	//unsigned  XX.XXX bounds:[0...3.875]
	ac_fixed <5,4,true> g; 		//signed 	XXXX.X bounds:[-8...7.5]

//  max_f * max_g = 3.875 * 7.5 = 29.0625 so,

//  we need 5 bits to represent 29 in unsigned form,  
//  plus 1 more bit to declare the sign (for signed representation) so :
//  eventually we need 6 bits before the decimal point. 

//  After the decimal point : in order to represent 0.625 , we need 4 bits,
//	so h needs to have 6 bits before the decimal point and 4 bits after it, so:

	ac_fixed<10,6, true> h;
	
//  Test of correct representation of min value of the product:
	std::cout<<"min h :"<<endl;
	f = 0;
	g = -8;
	h = f * g;
	std::cout<<"fmin = "<<f<<"\t"<<"gmin = "<<g<<endl;
	std::cout<<"hmin = "<<h<<endl<<endl;
	
//	Test of correct representation of max value of the product:
	std::cout<<"max h : "<<endl;
	f = 3.875;
	g = 7.5;
	h = f * g;
	
	std::cout<<"fmax = "<<f<<"\t"<<"gmax = "<<g<<endl;
	std::cout<<"hmax = "<<h<<endl;

//	So we can easily check that 
//	if h is in the form of ac_fixed<10,6,true> , we can represent the max value of f*g.
	return 0;
}
