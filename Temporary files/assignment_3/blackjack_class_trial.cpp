#include <iostream>
#include <ac_int.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>

using std::endl;

static const int C = 4;
static const int RUNS = 10;

typedef ac_int<C,false> Card;

class BlackJack
{
	private:
		Card end_round;
		Card win;
	public:
		BlackJack()
		{
			std::cout<<"An object of class BlackJack is created"<<endl;
			end_round = 0;
			win = 0;
		}
	
		void run(ac_channel<Card> &in_card, bool &end_round, bool &win)
		{
			if (in_card.available(1))
			{
				if (end_round == 0)
				{
					Card card;
					static ac_int<5,false> sum = 0;
					static Card incr = 0;
					static Card ace1 = 0;
					
					card = in_card.read();
					
					if (card>0 && card<11)
					{
						
						std::cout<<"new card : "<<card<<endl;
						incr += 1;
//						std::cout<<"in class, incr : "<<incr<<endl;
						
//						if ( (card == 1) && (incr != 1) && (incr != 2) )
						if( ( (incr == 1)||(incr == 2) ) && (card == 1) )
						{
							std::cout<<" We have an Ace : "<<card<<endl;
							sum += 11;
							std::cout<<"so sum with Ace , sum : "<<sum<<endl;
						}
						else
						{
							sum += card;
							std::cout<<"current sum : "<<sum<<endl;
						}
						
						if ( (sum > 21) && (card != 1) )
						{
							std::cout<<"YOU LOST ! "<<endl;
							end_round = 1;
							win = 0;
							incr = 0;
							sum = 0;
						}
						else
						{
							if(sum == 21)
							{
								std::cout<<"YOU WON 21!!!"<<endl;
								end_round = 1;
								win = 1;
								incr = 0;
								sum = 0;
							}
							
//							if( ( (incr == 1)||(incr == 2) ) && (card == 1) )
							if (( incr == 1 ) && (card == 1))
							{
								ace1 = 1;
								std::cout<<"First Ace, one more to go !"<<endl;
							}
							
							if ( (incr == 2) && (card == 1) && (ace1 == 1) )
							{
							
								std::cout<<"Second Ace arrived ! YOU WON 2 ACES !!!"<<endl;
								end_round = 1;
								win = 1;
								incr = 0;
								sum = 0;
							}
							
							if ( (incr == 5) && (sum <21) )
							{
								std::cout<<"YOU WON with 5 cards !!! "<<endl;
								end_round = 1;
								win = 1;
								incr = 0;
								sum = 0;
							}	
						}
					}
					else 
					{
						std::cout<<"NON-VALID CARD ! Where did you find that ???"<<endl;
					}
					
				}
				else 
				{
//					std::cout<<"incr : "<<incr<<endl;
				}
			}
		}			
};



int main()
{
	ac_channel<Card> in_card;
	bool end_round;
	bool win;
	
//	std::srand(std::time(NULL));
	
	Card random_val;		// we need 4 bits, so range : [0...15]
	
	BlackJack bljck;

//	random_val = 10;
//	in_card.write(random_val);
//	bljck.run(in_card, end_round, win);
//	
//	random_val = 10;
//	in_card.write(random_val);
//	bljck.run(in_card, end_round, win);
//	
//	random_val = 1;
//	in_card.write(random_val);
//	bljck.run(in_card, end_round, win);
//	
//	random_val = 1;
//	in_card.write(random_val);
//	bljck.run(in_card, end_round, win);
//	
//	random_val = 1;
//	in_card.write(random_val);
//	bljck.run(in_card, end_round, win);

	
	for(int i=0;i<RUNS;i++)
	{
		
		std::cout<<" ~ ~ ~ Trial "<<i<<" ~ ~ ~"<<endl<<endl;
		
		ac_channel<Card> in_card;
		
		std::cout<<"Cards : "<<endl;
		for (int j=0;j<5;j++)
		{
			random_val = rand() % 10 + 1;
			in_card.write(random_val);
			std::cout<<random_val<<" ";
//			bljck.run(in_card, end_round, win);
		}
		
		std::cout<<endl;
		
		for (int j=0;j<5;j++)
		{
			bljck.run(in_card, end_round, win);
		}
		
		std::cout<<endl<<endl;
		
		end_round = 0;
//		bljck.~BlackJack();
	}
	
	return 0;
}
