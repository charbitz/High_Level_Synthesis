#include <iostream>
#include <ac_int.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>

using std::endl;

static const int C = 4;

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
					static Card card;
					static ac_int<5,false> sum = 0;
					static Card incr = 0;
					static Card ace1 = 0;
					
					card = in_card.read();
					
					if (card>0 && card<11)
					{
						
					
						std::cout<<"in class, new card : "<<card<<endl;
						incr += 1;
						std::cout<<"in class, incr : "<<incr<<endl;
						
						if (card == 1)
						{
//							std::cout<<"in class, We have an Ace : "<<card<<endl;
							sum += 11;
							std::cout<<"so sum with Ace , sum : "<<sum<<endl;
						}
						else
						{
							sum += card;
							std::cout<<"in class, current sum : "<<sum<<endl;
						}
						
						if ( (sum > 21) && (card != 1) )
						{
							std::cout<<"YOU LOST ! "<<endl;
							end_round = 1;
							win = 0;
						}
						else
						{
							if(sum == 21)
							{
								std::cout<<"YOU WON 21!!!"<<endl;
								end_round = 1;
								win = 1;
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
							}
							
							if ( (incr == 5) && (sum <21) )
							{
								std::cout<<"YOU WON with 5 cards !!! "<<incr<<endl;
								end_round = 1;
								win = 1;
							}	
						}
					}
					else 
					{
						std::cout<<"NON-VALID CARD ! Where did you find that ???"<<endl;
					}
					
				}
			}
		}			
};



int main()
{
	ac_channel<Card> in_card;
	bool end_round;
	bool win;
	
	BlackJack bljck;
	
	Card random_val;		// we need 4 bits, so range : [0...15]
	
	random_val = 2;
	in_card.write(random_val);
	bljck.run(in_card, end_round, win);
	
	random_val = 2;
	in_card.write(random_val);
	bljck.run(in_card, end_round, win);
	
	random_val = 3;
	in_card.write(random_val);
	bljck.run(in_card, end_round, win);
	
	random_val = 2;
	in_card.write(random_val);
	bljck.run(in_card, end_round, win);
	
	random_val = 2;
	in_card.write(random_val);
	bljck.run(in_card, end_round, win);
	
	return 0;
}
