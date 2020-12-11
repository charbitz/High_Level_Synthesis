#include <iostream>
#include<ac_int.h>

using namespace std;

int main()
{
	
	ac_int <8,false> a,b; 	//unsigned 8 bits [0...255]
	ac_int <9,true> c,d; 	//signed 9 bits [-256...255]
	
//	max_a * max_b = 255 * 255 = 65065 so
//	a * b requires log2(65065) = 16 bits


	ac_int<16, false> e;
	std :: cout <<"Trial for product: a * b :"<<endl ;
	a = b = 0;
	for ( int i = 0 ; i<256  ; i++)
	{
		std :: cout <<"a = "<<a<<" 		b = "<<b ;
		e = a * b;
		std :: cout <<"		e = "<<e << endl;
		a += 1;	
		b += 1;
 
	}
	std :: cout <<endl ;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//	max_c * max_d = 255 * 255 = 65065 so
//	c * d requires log2(65066) + 1  = 17 bits


	ac_int<17, true> z; 
	
// 			check 0 to 255 :

	std :: cout <<"Trial for product: a * b :"<<endl ;
	c = d = 0;
	for ( int j = 0 ; j<=255  ; j++)
	{
		std :: cout <<"c = "<<c<<" 		d = "<<d ;
		z = c * d;
		std :: cout <<"		z = "<<z << endl;
		c += 1;	
		d += 1;
 
	}
	std :: cout <<endl ;
	
	
//			check -256 to 0 :

//	c = d = -256;
//	for ( int j = -256 ; j<=0  ; j++)
//	{
//		std :: cout <<"c = "<<c<<" 		d = "<<d ;
//		z = c * d;
//		std :: cout <<"		z = "<<z << endl;
//		c+=1;	
//		d+=1;
// 
//	}
	
	
//	max values : 255
//	max sum of mult : 2*255^2 =130050 so
//	log2(130051)+1 = 18 bits
	ac_int<18, true> h;
	
	
	
//	a = b = c = d = 0;
	a = b = 0;
	c = d =  256;
	
	
	for ( int i = 0 ; i<256  ; i++)
	{
		std :: cout <<"a = "<<a<<" 		b = "<<b <<"		c = "<<c<<" 		d = "<<d;
		
//		e = a * b;
//		z = c * d;
//		h = e + z ;
		
		h = a * b + c * d;
		std :: cout <<"		h = "<<h << endl;
		
		a+=1;	
		b+=1;	
		c+=1;
		d+=1;

	}
	std :: cout <<endl ;	
	
	
	return 0;
}
