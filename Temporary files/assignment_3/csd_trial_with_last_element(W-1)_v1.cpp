/* This was created to correct csd_trial.cpp file taking also last element of num (i = W-1) into account */

/* The thought is to check at the begining if num(i)==1 and then to check if i is the position of last element (W-1) */


#include <iostream>
#include<ac_int.h>
#include<ac_fixed.h>
#include<ac_channel.h>

using std::endl;

static const int W = 8;
typedef ac_int<W,true> s_int;			//sint stand for signed int
//	x_p and x_n need to have 1 bit more in order to compute correctly the cases,
// 	which num is in a form like 11XXX..X , where X is a 1 or a 0 :
typedef ac_int<W+1,false> un_int;		//un_int stands for unsigned int		


//	trial for running the function without template application :
void csd_encode(s_int &num, un_int &x_p, un_int &x_n)
{
//	Trial for 1-way run (without overlapping combinations) :
	
//	cnt will be the counter for the consequtively 1s :
	int cnt = 1;
	for(int i=0;i<W;i++)
	{
		std::cout<<"i = "<<i<<endl;
		
		if(num.slc<1>(i)==-1)
		{
			if(i == W-1)
			{
				if(cnt>1)
				{
					ac_int<1,0> hlpr = 0;
					for(int j=i-cnt+1;j<i+2;j++)
					{
						std::cout<<"  j = "<<j<<endl;
						
						hlpr = 0;
//						At the first element we need to put a 0 to x_n:
						if(j == i-cnt+1)
						{
							std::cout<<"first place so let's put a 1 here!"<<endl;
							hlpr = 1;
						}
//						At the last element(W-1):
						if(j==i+1)								//new code for updated x_p completion 
						{
							hlpr = 1;							//new code for updated x_p completion 
							x_p.set_slc(j,hlpr.slc<1>(0));		//new code for updated x_p completion 
							hlpr = 0;							//new code for updated x_p completion 
						}
						else									//new code for updated x_p completion 
						{
							x_p.set_slc(j,~num.slc<1>(j));
						}
						x_n.set_slc(j,hlpr.slc<1>(0));
					}
						cnt = 1;	
				}
				else
				{
					ac_int<1,false> hlpr2 = 0;
					x_n.set_slc(i,hlpr2.slc<1>(0));
				}	
			}
			else
			{
				if(num.slc<1>(i)==num.slc<1>(i+1))
				{
					std::cout<<"		2 consequtively 1s found!"<<endl;
					cnt += 1;
				}
				else
				{
					if(cnt>1)
					{	
					ac_int<1,0> hlpr3 = 0;
						for(int j=i-cnt+1;j<i+2;j++)
						{
							std::cout<<"  j = "<<j<<endl;
							x_p.set_slc(j,~num.slc<1>(j));
							hlpr3 = 0;
							if(j == i-cnt+1)
							{
								std::cout<<"first place so let's put a 1 here!"<<endl;
								hlpr3 = 1;
							}
							x_n.set_slc(j,hlpr3.slc<1>(0));
						}
						cnt = 1;	
					}
					else
					{
						ac_int<1,false> hlpr2 = 0;
						x_n.set_slc(i,hlpr2.slc<1>(0));
					}	
				}
			}
		}
	}
	std::cout<<"TESTs:"<<endl;
	std::cout<<"num :"<<num<<endl;
	std::cout<<"x_p:"<<x_p<<endl;
	std::cout<<"x_n:"<<x_n<<endl;
	std::cout<<"cnt:"<<cnt<<endl;
}

int main()
{

	s_int num;
	un_int x_p;
	un_int x_n;
	
//	num = 87;	 // W = 7
//	num = 76;	 // W = 7
//	num = 754;	 // W = 11
//	num = 483;	 // W = 11
//	num = 20083; // W = 15
//	num = 147;   // W = 9
//	num = 147;   // W = 8
//	num = 2;     // W = 5
//	num = 211;   // W = 8
//	num = 211;   // W = 9
//	num = 26;    // W = 5
//	num = 819;   // W = 10
//	num = 19;    //	W = 5
//	num = 43; 	 // W = 7
	num = 62; 	 // W = 8
	x_p = x_n = 62;
	
//	Call function to encode num into x_p and x_n :
	csd_encode(num, x_p, x_n);
	
//	Some prints in order to check input num and outputs x_p and x_n (print the bitstream of variables):
	std::cout<<"		num ::: "<<endl;
	for(int i=0;i<W;i++)
	{
		std::cout<<"num("<<i<<"): "<<num.slc<1>(i)<<endl;
	}
	
	std::cout<<"		x_p ::: "<<endl;	
	for(int i=0;i<W+1;i++)
	{
		std::cout<<"x_p("<<i<<"): "<<x_p.slc<1>(i)<<endl;
	}
	
	std::cout<<"		x_n ::: "<<endl;	
	for(int i=0;i<W+1;i++)
	{
		std::cout<<"x_n("<<i<<"): "<<x_n.slc<1>(i)<<endl;
	}

//	Some prints in order to check input num and outputs x_p and x_n (print the value of variables):
	std::cout<<"num (signed) :"<<num<<endl;
	std::cout<<"x_p :"<<x_p<<endl;
	std::cout<<"x_n :"<<x_n<<endl;	
}
