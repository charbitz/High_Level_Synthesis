
/*	This file implements a CSD (Canonical Signed Digit) representation of a signed number num to it's unsigned components x_p and x_n. */

/*	The variable num has W bits and for this algorithm we need the components x_p and x_n to have W+1 bits . */

/*	The components are declared with the value 0. */

/*	The algorithm which describes the CSD */

//
//
//


/*	The variable cnt counts the consequtive 1s. With the below implementation cnt starts at value 1 and increases as we find 2 consecutive 1s. */



/* This version was created to correct csd_overlap_combs_with_num_updated.cpp file. */

/*	It takes into account the MSB-check in order not to check for next bit (out of bounds). */

/* The thought is to check at the begining if num(i)==1 and then to check if i is the position of MSB (W-1) */

#include <iostream>
#include<ac_int.h>
#include<ac_fixed.h>
#include<ac_channel.h>

using std::endl;

static const int W = 18;
typedef ac_int<W,true> s_int;			//sint stand for signed int
//	x_p and x_n need to have 1 bit more in order to compute correctly the cases,
// 	which num is in a form like 11XXX..X , where X is a 1 or a 0 :
typedef ac_int<W+1,false> un_int;		//un_int stands for unsigned int		


//	trial for running the function without template application :
void csd_encode(s_int &num, un_int &x_p, un_int &x_n)
{
//	Trial for run with overlapping combinations :
	
//	cnt will be the counter for the consequtively 1s :
	int cnt = 1;
//	rdy_ovrlp_comb is a flag to know if there is an overlapp in the future :
	int rdy_ovrlp_comb = 0;
	ac_int<W,false> num_upd = num;
//	UA DIAGRPHEI 
	for(int k=0;k<W;k++)
	{
//		num_upd.set_slc(k,num.) // ayto den xreiaazetai tora epeidh to theto sthnarxh num_upd = num
		std::cout<<"delete me after that ___num("<<k<<") :"<<num.slc<1>(k)<<endl;
		std::cout<<"delete me after that ___num_upd("<<k<<") :"<<num_upd.slc<1>(k)<<endl;
	}
//	UA DIAGRPHEI
 
	for(int i=0;i<W;i++)
	{
		std::cout<<"i = "<<i<<endl;
//		check here if there was an alert for an overalapping combination, if there was, start checking from the previous bit , not the current :
		if(rdy_ovrlp_comb == 1)
		{
			std::cout<<"overlapping comb situation here!!!"<<endl;
			i = i - 1;
			rdy_ovrlp_comb = 0;
		}
		
		if(num_upd.slc<1>(i) == 1)																				//new code check for num_upd
		{
			if(i == W-1)
			{
//				Now we are at the MSB, so no need to check for consecutive 1s :
				std::cout<<"LAST BIT (W-1) is an 1 !!! "<<endl;
				
				if(cnt>1)
				{
//					helper 1-bit words in order to fill in the components x_p and x_n : 
					ac_int<1,0> hlpr_xn;
					ac_int<1,0> hlpr_xp;
					
					for(int j=i-cnt+1;j<i+2;j++)
					{
						std::cout<<"  j = "<<j<<endl;
						
						hlpr_xn = 0;
						hlpr_xp = 0;
//						At the LSB we need to put a 0 to x_n:
						if(j == i-cnt+1)
						{
							std::cout<<"first bit so let's put a 1 to x_n!"<<endl;
							hlpr_xn = 1;
						}
//						At the MSB (W-1) we need to put an 1 to x_p:
						else if(j==i+1)								
						{
							hlpr_xp = 1;							
//							x_p.set_slc(j,hlpr.slc<1>(0));
//							num_upd.set_slc(j,num.slc<1>(0));										//new code for update the num_upd variable
//							hlpr = 0;							
						}
						
						x_p.set_slc(j,hlpr_xp.slc<1>(0));
						x_n.set_slc(j,hlpr_xn.slc<1>(0));
//						num_upd.set_slc(j,hlpr_xp.slc<1>(0));								  		//new code for update the num_upd variable_ TRY THAT HERE
					}
					cnt = 1;
//					* * * After that combination we don't have to check for an overlapping situation because there will be no 1 after the MSB! * * *
				}
				else
				{
//					copy single 1 found for x_p or invert it for x_n :
//					ac_int<1,false> hlprxp = 1;
//					ac_int<1,false> hlprxn = 0;
					ac_int<1,false> hlpr_single = 1;
//					x_p.set_slc(i,hlpr2.slc<1>(0));		//new code for x_p assign (15/12)

//					copy the single 1 for x_p:
					std::cout<<"Found single 1 so copy it to 0 for x_p"<<endl;
					x_p.set_slc(i,hlpr_single.slc<1>(0));

					hlpr_single = 0;
//					convert the single 1 into a 0 for x_n:
					std::cout<<"Found single 1 so convert it to 0 for x_n"<<endl;
					x_n.set_slc(i,hlpr_single.slc<1>(0));
				}	
			}
			else
			{
//				Now we check all the other bits apart from MSB : 
				if(num_upd.slc<1>(i)==num_upd.slc<1>(i+1))														//new code check for num_upd
				{
					std::cout<<"		2 consequtively 1s found!"<<endl;
					cnt += 1;
				}
				else
				{
					if(cnt>1)
					{	
//						helper 1-bit words in order to fill in the components x_p and x_n : 
						ac_int<1,0> hlpr_x_p;
						ac_int<1,0> hlpr_x_n;
						
						for(int jj=i-cnt+1;jj<i+2;jj++)
						{
							std::cout<<"  jj = "<<jj<<endl;
//							x_p.set_slc(jj,~num_upd.slc<1>(jj));												//new code check for num_upd
//							num_upd.set_slc(jj,~num.slc<1>(jj));
							hlpr_x_p = 0;
							hlpr_x_n = 0;
							
//							Check for the LSB of the area to transform :
							if(jj == i-cnt+1)
							{
								std::cout<<"LSB so let's put a 1 to x_n!"<<endl;
								hlpr_x_n = 1;
							}
//							Check for the MSB of the area to transform :
							else if(jj == i+1)
							{
								std::cout<<"MSB so let's put a 1 to x_p!"<<endl;
								hlpr_x_p = 1;
							}
							x_p.set_slc(jj,hlpr_x_p.slc<1>(0));
							x_n.set_slc(jj,hlpr_x_n.slc<1>(0));
/*that was correct*/		num_upd.set_slc(jj,hlpr_x_p.slc<1>(0));
///*lets try that*/			num_upd.set_slc(jj,num.slc<1>(jj));	  //mpa lathos
						}
						cnt = 1;
						
//						check here if there is an overlapping combination, have to check in the x_p variable, because num is not updated :

						if( num_upd.slc<1>(i+2)==1)													//new code for update the num_upd variable
						{
							std::cout<<"~ ~ ~ we WILL have an overlapp ~ ~ ~"<<endl;
							rdy_ovrlp_comb = 1;
						}		
					}
					else
					{
						ac_int<1,false> hlpr2 = 1;
						x_p.set_slc(i,hlpr2.slc<1>(0));		//new code for x_p assign (15/12)
						hlpr2 = 0;
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
	
	std::cout<<"inside csd:		num_upd ::: "<<endl;
	for(int k=0;k<W;k++)
	{
		std::cout<<"num_upd("<<k<<"): "<<num_upd.slc<1>(k)<<endl;
	}
		
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
//	num = 819;   // W = 10

//	num = 19;    //	W = 5
//	num = 13;	 // W = 5
//	num = 6;	 // W = 5
//	num = 26;    // W = 5
//	num = -6;
//	num = 43; 	 // W = 7
//	num = 62; 	 // W = 8
//	num = 150; 	 // W = 9

	num = 171;	 // W = 8
	
	num = 219051;// W = 18
	x_p = x_n = 0;
	
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
