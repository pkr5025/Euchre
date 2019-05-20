#include "Game.h"
#include <iostream>
using namespace std;

//******************* my own helper functions *******************

// REQUIRES game_ptr points to an initialized game, dealer is between 0 and 3 inclusive
// MODIFIES game_ptr
// EFFECTS  deals cards to each player (as indicated in the spec)
static void deal(Game *game_ptr, int dealer){
	int i=1;
	int k=1;
	Card todeal;

	// loop resets each players hand before the deal
	for (int j =0; j<4; j++){
		(game_ptr -> players[j]).hand_size =0;
	}

	// loop adds proper cards to each players hand
	for (int round = 1; round<3; round++){
		i=1;
		while (i<5){
			todeal = Pack_deal_one(&(game_ptr -> pack));
			Player_add_card(&(game_ptr -> players[(dealer+i)%4]), &todeal);	
			todeal = Pack_deal_one(&(game_ptr -> pack));
			Player_add_card(&(game_ptr -> players[(dealer+i)%4]), &todeal);	
			if (((k%2 == 1) && (k<5)) || ((k%2 == 0) && (k>=5))){  
				todeal = Pack_deal_one(&(game_ptr -> pack));
				Player_add_card(&(game_ptr -> players[(dealer+i)%4]), &todeal);	
			}
			i++;
			k++;
		}
	}
// testing code to print hand
//	for (int j=0; j<5; j++){
//		Card_print(&(game_ptr -> players[3]).hand[j]);
//		cout<<endl;
//	}
}

//REQUIRES game_ptr points to an initialized game
//MODIFIES game_ptr
//EFFECTS  determines what suit is trump, and if necessary, adds the upcard to the dealer's hand
//	   also prints messages associated with making (as indicated in the spec)
static Suit makingtrump(Game *game_ptr,int dealer, int &maker){
	Card_print((game_ptr -> pack).next);
	cout<<" turned up"<<endl;
	Make_response playerresponse;

	// round one of making
	for (int i=1; i<5; i++){
		playerresponse = Player_make_trump(&(game_ptr -> players[(dealer+i)%4]), (game_ptr->pack).next, &(game_ptr ->players[dealer]), 1);
		if (playerresponse.orderup == false){
			cout<<(game_ptr -> players[(dealer+i)%4]).name<<" passes"<<endl;
		}
		if (playerresponse.orderup == true){
			cout<<(game_ptr -> players[(dealer+i)%4]).name<<" orders up ";
			maker = (dealer+i)%4;
			Suit_print(playerresponse.trump);
			cout<<endl<<endl;
			Player_add_and_discard(&(game_ptr->players[dealer]), (game_ptr ->pack).next);
			return playerresponse.trump;
		}
	}

	// round two of making (if necessary)
	for (int i=1; i<4; i++){
                playerresponse = Player_make_trump(&(game_ptr -> players[(dealer+i)%4]), (game_ptr->pack).next, &(game_ptr ->players[dealer]), 2);
                if (playerresponse.orderup == false){
                        cout<<(game_ptr -> players[(dealer+i)%4]).name<<" passes"<<endl;
                }
                if (playerresponse.orderup == true){
			maker = (dealer+i)%4;
                        cout<<(game_ptr -> players[(dealer+i)%4]).name<<" orders up ";
                        Suit_print(playerresponse.trump);
                        cout<<endl<<endl;
			return playerresponse.trump;
                }
        }
	
	// screw the dealer (if necessary)
	cout<<(game_ptr -> players[dealer]).name<<" orders up ";
        Suit_print(playerresponse.trump);
	cout<<endl<<endl;
	maker = dealer;
	return playerresponse.trump;

}

//REQUIRES game_ptr points to an initialized game, leader is an integer between 0 and 3 inclusive
//MODIFIES game_ptr, stdout
//EFFECTS  plays a trick of euchre
static int playtrick (Game *game_ptr, Suit trump, int &leader){
	Card toplay[5];  // fifth card for comparison purposes
	Player trickwinner = game_ptr -> players[leader%4];
	int x = leader;

	toplay[0] = Player_lead_card(&(game_ptr -> players[leader%4]), trump);
	toplay[1] = Player_play_card(&(game_ptr -> players[(leader+1)%4]), &toplay[0], trump);
	toplay[2] = Player_play_card(&(game_ptr -> players[(leader+2)%4]), &toplay[0], trump);
	toplay[3] = Player_play_card(&(game_ptr -> players[(leader+3)%4]), &toplay[0], trump);
	toplay[4] = toplay[0];

	Card_print(&toplay[0]);
	cout<<" led by "<<(game_ptr->players[leader%4]).name<<endl;
	Card_print(&toplay[1]);
	cout<<" played by "<<(game_ptr->players[(leader+1)%4]).name<<endl;
	Card_print(&toplay[2]);
	cout<<" played by "<<(game_ptr->players[(leader+2)%4]).name<<endl;
	Card_print(&toplay[3]);
	cout<<" played by "<<(game_ptr->players[(leader+3)%4]).name<<endl;

	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
                        if ((Card_compare(&toplay[4], &toplay[j], &toplay[0], trump)<0) && (j>i)){
                                trickwinner = game_ptr -> players[(leader+j)%4];
				toplay[4] = toplay[j];
                                x = (leader+j)%4;
			}
		}
	}
	cout<< trickwinner.name <<" takes the trick"<<endl<<endl;
	leader = x;
	if ((x%2) == 1)
		return -1;
	else
		return 1;

}

//******************* end my own helper functions  *******************

void Game_init
(
 Game *game_ptr,
 const char *pack_filename,
 bool shuffle,
 int points_to_win,
 const char *const player_names[]
){
Pack_init(&(game_ptr->pack), pack_filename);
game_ptr->shuffle = shuffle;
game_ptr->score[0] = 0;
game_ptr->score[1] = 0;
game_ptr->points_to_win = points_to_win;

for (int i=0; i<4; i++){
	Player_init(&(game_ptr ->players[i]), player_names[i]);
	}
}

void Game_play(Game *game_ptr){
int handnumber = 0;
int dealer = 0;
int maker = 0;

// positive tricks = dealer team.  negative tricks = other team
int tricks = 0; 
int leader = 1;
Suit trump;

while (((game_ptr->score[0]) < (game_ptr->points_to_win)) && ((game_ptr->score[1]) < (game_ptr->points_to_win))){
	tricks = 0;
	leader = (dealer+1)%4;
	if (game_ptr ->shuffle == true){
		Pack_shuffle(&(game_ptr -> pack));
	}
	else
		Pack_reset(&(game_ptr -> pack));
	deal(game_ptr, dealer);
	cout<< "Hand "<< handnumber <<endl;
	cout<< (game_ptr->players[dealer]).name <<" deals"<<endl; 
	trump = makingtrump(game_ptr, dealer, maker);

	tricks += playtrick(game_ptr, trump, leader);
	tricks += playtrick(game_ptr, trump, leader);
	tricks += playtrick(game_ptr, trump, leader);
	tricks += playtrick(game_ptr, trump, leader);
	tricks += playtrick(game_ptr, trump, leader);
	
	if (tricks > 0){
		cout<<(game_ptr ->players[maker%2]).name<<" and "<<(game_ptr ->players[(maker%2)+2]).name<<" win the hand"<<endl;
		game_ptr->score[maker%2] += 1;
		if (tricks == 5){
			cout<<"march!"<<endl;
			game_ptr->score[maker%2] += 1;
		}	
	}
	else{
                cout<<(game_ptr ->players[(maker+1)%2]).name<<" and "<<(game_ptr ->players[((maker+1)%2)+2]).name<<" win the hand"<<endl;
		cout<<"euchred!"<<endl;
		game_ptr->score[(maker+1)%2] += 2;
	}
	cout<<(game_ptr ->players[0]).name<<" and "<<(game_ptr ->players[2]).name<<" have "<<game_ptr ->score[0]<<" points"<<endl;
	cout<<(game_ptr ->players[1]).name<<" and "<<(game_ptr ->players[3]).name<<" have "<<game_ptr ->score[1]<<" points"<<endl;
	cout<<endl;
	dealer = (dealer+1)%4;
	handnumber++;
//	game_ptr->score[0] += 8;  //temporarily used to end loop until score is implemented properly
	}
	if ((game_ptr->score[0]) < (game_ptr->points_to_win))
	        cout<<(game_ptr ->players[1]).name<<" and "<<(game_ptr ->players[3]).name<<" win!";
	else
                cout<<(game_ptr ->players[0]).name<<" and "<<(game_ptr ->players[2]).name<<" win!";                      
	cout<<endl<<endl;

}
