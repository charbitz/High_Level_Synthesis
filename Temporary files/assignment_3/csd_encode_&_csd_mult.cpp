
/*	This file implements a CSD (Canonical Signed Digit) representation of a signed number num to it's unsigned components x_p and x_m. */

/*	The variable num has W bits and for this algorithm we need the components x_p and x_m to have W+1 bits . */

/*	The components are declared with the value 0. */

/*	The algorithm which describes the CSD */

//
//
//


/*	A combination which is mentioned at the following comments refer to the desired bit-stream of consecutive 1s followed by a 0 (looking from LSB to MSB). */


/*	The variable cnt counts the consequtive 1s. With the below implementation cnt starts at value 1 and increases as we find 2 consecutive 1s. */



/* This version was created to correct csd_overlap_combs_with_num_updated.cpp file. */

/*	It takes into account the MSB-check in order not to check for next bit (out of bounds). */

/* The thought is to check at the begining if num(i)==1 and then to check if i is the position of MSB (W-1) */

#include <iostream>
#include <ac_int.h>
#include <cstdlib>
#include <ctime>

using std::endl;

static const int W = 6;		//num of bits for num (variable which is going to be CSD encoded)

static const int RUNS = 10;

//Declaring a global variable which is the expected number of bits for the output of csd_mul function :
//const int Wout = 2*W;	//( W + pos_gr_one )

//typedef ac_int<W,true> s_int;			//s_int stands for signed int
//	x_p and x_m need to have 1 bit more in order to compute correctly the cases,
// 	which num is in a form like 11XXX..X , where X is a 1 or a 0 :
//typedef ac_int<W+1,false> un_int;		//un_int stands for unsigned int
		


// The function which converts num to it's CSD representation :
//Trial for template :
template<int W>
void csd_encode(ac_int<W,true> &num, ac_int<W+1,false> &x_p, ac_int<W+1,false> &x_m)
{
	x_p = 0;
	x_m = 0;
//	Trial for run with overlapping combinations :
	
//	cnt will be the counter of the consequtively 1s :
	int cnt = 1;
//	rdy_ovrlp_comb is a flag to know if there is an overlapp in the future :
	int rdy_ovrlp_comb = 0;
//	We need to update the num in order to be able to find overlapping combinations :
	ac_int<W,false> num_upd = num;
////	UA DIAGRPHEI 
//	for(int k=0;k<W;k++)
//	{
////		num_upd.set_slc(k,num.) // ayto den xreiaazetai tora epeidh to theto sthnarxh num_upd = num
//		std::cout << "delete me after that ___num("<<k<<") :" << num.template slc<1>(k) << endl;
//		std::cout << "delete me after that ___num_upd("<<k<<") :" << num_upd.template slc<1>(k) << endl;
//	}
////	UA DIAGRPHEI
 
	for(int i=0;i<W;i++)
	{
//		std::cout<<"i = "<<i<<endl;
//		Check here if there was an alert for an overalapping combination. 
//		If  yes, start checking from the previous bit , not the current one:
		if(rdy_ovrlp_comb == 1)
		{
//			std::cout<<"overlapping comb situation here!!!"<<endl;
			i = i - 1;
			rdy_ovrlp_comb = 0;
		}
		
		if(num_upd.template slc<1>(i) == 1)
		{
			if(i == W-1)
			{
//				Here we check MSB, so no need to check for consecutive 1s :
//				std::cout<<"LAST BIT (W-1) is an 1 !!! "<<endl;
				
//				The conditin cnt>1 means that we had at least 2 consequtive 1s(a wanted combination found), otherwise we had just found a single 1 :
				if(cnt>1)
				{
//					Helping 1-bit words in order to fill in the components x_p and x_m : 
					ac_int<1,0> hlpr_xm;
					ac_int<1,0> hlpr_xp;
					
					for(int j=i-cnt+1;j<i+2;j++)
					{
//						std::cout<<"  j = "<<j<<endl;
						
						hlpr_xm = 0;
						hlpr_xp = 0;
//						At the LSB we need to put a 0 to x_m:
						if(j == i-cnt+1)
						{
//							std::cout<<"first bit so let's put a 1 to x_m!"<<endl;
							hlpr_xm = 1;
						}
//						At the MSB (W-1) we need to put an 1 to x_p:
						else if(j==i+1)								
						{
							hlpr_xp = 1;														
						}
						x_p.set_slc(j,hlpr_xp.slc<1>(0));
						x_m.set_slc(j,hlpr_xm.slc<1>(0));
//						num_upd.set_slc(j,hlpr_xp.slc<1>(0));								  		//new code for update the num_upd variable_ TRY THAT HERE
					}
//					After updating num_upd, x_p, x_m we need to initialize our cnt back to 1, in order to count new bit-streams of 1s :
					cnt = 1;
//					* * * After that combination we don't have to check for an overlapping situation because there will be no 1 after the MSB! * * *
				}
				else
				{
//					If there was found a single 1 and not a bit-stream of consequtive 1s, then just :
//					Helping 1-bit words in order to fill in the components x_p and x_m : 
					ac_int<1,false> hlpr_single = 1;
//					x_p.set_slc(i,hlpr2.slc<1>(0));		//new code for x_p assign (15/12)

//					-copy the single 1 for x_p:
//					std::cout<<"Found single 1 so copy it for x_p"<<endl;
					x_p.set_slc(i,hlpr_single.slc<1>(0));

					hlpr_single = 0;
//					-convert the single 1 into a 0 for x_m:
//					std::cout<<"Found single 1 so convert it to 0 for x_m"<<endl;
					x_m.set_slc(i,hlpr_single.slc<1>(0));
				}	
			}
			else
			{
//				Now we check all the other bits apart from MSB : 
				if(num_upd.template slc<1>(i)==num_upd.template slc<1>(i+1))
				{
//					std::cout<<"		2 consequtively 1s found!"<<endl;
					cnt += 1;
				}
				else
				{
					if(cnt>1)
					{	
//						Helping 1-bit words in order to fill in the components x_p and x_m : 
						ac_int<1,0> hlpr_x_p;
						ac_int<1,0> hlpr_x_m;
						
						for(int jj=i-cnt+1;jj<i+2;jj++)
						{
//							std::cout<<"  jj = "<<jj<<endl;
							hlpr_x_p = 0;
							hlpr_x_m = 0;
							
//							Check for the LSB of the bit-stream of 1s :
							if(jj == i-cnt+1)
							{
//								std::cout<<"LSB so let's put a 1 to x_m!"<<endl;
								hlpr_x_m = 1;
							}
//							Check for the MSB of the bit-stream of 1s :
							else if(jj == i+1)
							{
//								std::cout<<"MSB so let's put a 1 to x_p!"<<endl;
								hlpr_x_p = 1;
							}
							x_p.set_slc(jj,hlpr_x_p.slc<1>(0));
							x_m.set_slc(jj,hlpr_x_m.slc<1>(0));
//							The algorithm scanns from LSB to MSB, so there is no need to preserve
//							also the updated x_n's 1s, because the algorithm will never check them again  
/*that was correct*/		num_upd.set_slc(jj,hlpr_x_p.slc<1>(0));
///*lets try that*/			num_upd.set_slc(jj,num.slc<1>(jj));	  //mpa lathos
						}
						cnt = 1;
						
//						Check here if there is an overlapping combination :

						if( num_upd.template slc<1>(i+2)==1)
						{
//							std::cout<<"~ ~ ~ we WILL have an overlapp ~ ~ ~"<<endl;
							rdy_ovrlp_comb = 1;
						}		
					}
					else
					{
//						If there was found a single 1 and not a bit-stream of consequtive 1s, then just :
						ac_int<1,false> hlpr2 = 1;
//						- copy the single 1s found to the x_p and 
						x_p.set_slc(i,hlpr2.slc<1>(0));	
						hlpr2 = 0;
//						- invert them to the x_m :
						x_m.set_slc(i,hlpr2.slc<1>(0));
					}	
				}
			}
		}
	}
//	std::cout<<"TESTs:"<<endl;
//	std::cout<<"num :"<<num<<endl;
//	std::cout<<"x_p:"<<x_p<<endl;
//	std::cout<<"x_m:"<<x_m<<endl;
//	std::cout<<"cnt:"<<cnt<<endl;
	
//	std::cout<<"inside csd:		num_upd ::: "<<endl;
	for(int k=0;k<W;k++)
	{
//		std::cout<<"num_upd("<<k<<"): "<<num_upd.template slc<1>(k)<<endl;
	}

}

template<int W>
ac_int<2*W,true> csd_mult(ac_int<W,true> &in, ac_int<W+1,false> &x_p, ac_int<W+1,false> &x_m)
{
	ac_int<2*W,true> out = 0;

//	We need to icrease the number of bits of variable in, in order to represent correctly the shifting value, so we have in augmented:
	ac_int<2*W,true> in_augm = in;
	
//	for(int k=0;k<W;k++)
//	{
//		if (in.slc<1>(k) != 0)
//		{
//			in_augm.set_slc(k,in.slc<1>(k));
//		}
//		
//		std::cout<<"in("<<k<<") : "<<in.slc<1>(k)<<"		";
//		std::cout<<"in_augm("<<k<<") : "<<in_augm.slc<1>(k)<<endl;	
//	}
	
	//	print the in's and in_augm's value :
//	std::cout<<"after conversion in 's value is "<<in<<endl;
//	std::cout<<"after conversion in_augm 's value is "<<in_augm<<endl<<endl;
	
//	Because x_p and x_m have W+1 bits, we need to take into account also their MSB (i = W) :
	for(int i=0;i<W+1;i++)
	{
//		std::cout<<"i = "<<i<<endl;
		if(x_p.template slc<1>(i) == 1)
		{
//			std::cout<<"found 1 at X_P"<<endl;
//			std::cout<<"out prin to shift :"<<out<<endl;
			out = out + (in_augm << i);
//			std::cout<<"sum meta to shift :"<<out<<endl;	
		}
		
		if(x_m.template slc<1>(i) == 1)
		{
//			std::cout<<"found 1 at X_M"<<endl;
//			std::cout<<"out prin to shift :"<<out<<endl;
			out = out - (in_augm << i);
//			std::cout<<"out meta to shift :"<<out<<endl;	
		}
	}
	
//	std::cout<<"out after for = "<<out<<endl;
	return out;
}

int main()
{
	ac_int<W,true> num;
	ac_int<W+1,false> x_p;
	ac_int<W+1,false> x_m;
	ac_int<W,true> in;
	ac_int<2*W,true> out;
		
	std::srand(std::time(NULL));



//	num = 23;    // W = 5
//	in = 7;
//	x_p = x_m = 0;
//		
//	Call function to encode num into x_p and x_n :
//	csd_encode(num, x_p, x_m);
	
//	Call the fuction csd_encode with template int W = 8 :
//	csd_encode<W>(num, x_p, x_m);
		
//	call csd_mult :
//	out = csd_mult(in, x_p, x_m);
//	Call the fuction csd_mult with template int W = 8 :
//	csd_mult<W>(in, x_p, x_m);	
//	std::cout<<"out = "<<out<<endl;
	


	for(int k=0;k<RUNS;k++)
	{
		std::cout << " ~ ~ ~ Trial " << k << " ~ ~ ~ \n";
//		The range of possible signed numbers of W=6 bits is : [-32...31]
		num = std::rand()%63 + (-32);
		
		std::cout<<" num :"<<num<<endl;
		std::cout<<"  ";
		for(int j=W-1;j>=0;j--)
		{
			std::cout<<num[j]<<" ";
		}
		std::cout<<endl<<endl;
		
//		call csd_encode :
		csd_encode<W>(num, x_p, x_m);
		
		std::cout<<" x_p : "<<x_p<<endl;
		for(int j=W;j>=0;j--)
		{
			std::cout<<x_p[j]<<" ";
		}
		std::cout<<endl<<endl;
		
		std::cout<<" x_m : "<<x_m<<endl;
		for(int j=W;j>=0;j--)
		{
			std::cout<<x_m[j]<<" ";
		}
		std::cout<<endl<<endl;
		
//		random number generator for variable in :
		in = std::rand()%63 + (-32);
		
		std::cout<<" in : "<<in<<endl;
		std::cout<<"  ";
		for(int j=W-1;j>=0;j--)
		{
			std::cout<<in[j]<<" ";
		}
		std::cout<<endl<<endl;
		
//		call csd_mult :
		out = csd_mult(in, x_p, x_m);
		
		std::cout<<" out : "<<out<<endl;
		for(int j=2*W-1;j>=0;j--)
		{
			std::cout<<out[j]<<" ";
		}
		std::cout<<endl<<endl<<endl<<endl<<endl<<endl;
		
				
	}
	



}
