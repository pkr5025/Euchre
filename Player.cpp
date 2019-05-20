// pkleinr Philip Klein-Rodick

#include "Player.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

void Player_init(Player *player_ptr, const char *name){
	strcpy(player_ptr -> name, name);
	player_ptr -> hand_size = 0;
}

void Player_add_card(Player *player_ptr, const Card *c){
	player_ptr -> hand[player_ptr -> hand_size] = *c;
	player_ptr -> hand_size ++;
}

Make_response Player_make_trump(const Player *player_ptr, const Card *upcard, Player *dealer, int round){
	int x=0;
	int i=0;
	Make_response response;
	response.orderup = false;
	if (round == 1){
		response.trump = upcard -> suit;
		while (i<player_ptr -> hand_size){
			if ((Card_compare_suit(&(player_ptr -> hand[i]), upcard, response.trump) ==0) && (Card_is_face(&(player_ptr -> hand[i])) == true))
				x++;
			i++;
		}
		if (x>1){
			response.orderup = true;
			return response;
		}
		else 
			return response;
	}
	else{
                response.trump = Suit_next(upcard -> suit);
                while (i<player_ptr -> hand_size){
                        if ((Card_compare_suit(&(player_ptr -> hand[i]), upcard, response.trump) ==0) && (Card_is_face(&(player_ptr -> hand[i])) == true))
                                x++;
                        i++;
                }
                if (x>0){
                        response.orderup = true;
                        return response;
                }
                else
                        return response;
       	}
}

void Player_add_and_discard(Player *player_ptr, const Card *upcard){
	Card drop = *upcard;
	int i=0;
	Card *p = & (player_ptr ->hand[0]);
	while (i<player_ptr -> hand_size){
		if (Card_compare(&(player_ptr -> hand[i]),& drop, (upcard -> suit))<0){
			drop = player_ptr -> hand[i];
			p = &(player_ptr ->hand[i]);		
		}
		i++;
	}
	if (Card_compare (&drop, upcard) == 0)
		return;
	else{
		*p = *upcard;
	}
}

Card Player_lead_card(Player *player_ptr, Suit trump){
	Card lead = player_ptr -> hand[0];
	int i=0;
	int has_trump = 1;
	Card *p = & (player_ptr ->hand[0]);
// first loop checks for non-trump
	while (i < player_ptr -> hand_size){
		if (Card_is_trump(&(player_ptr -> hand[i]),trump) == false)
			has_trump = 0;
		i++;
	}
	i=0;
// case 1: player has non-trump
	if (has_trump == 0){
	        while (Card_get_suit(&lead, trump) == trump){
                	i++;
                	lead= player_ptr -> hand[i];
                	p = &(player_ptr -> hand[i]);
        	}
		while (i< player_ptr -> hand_size){
			if (Card_is_trump(&(player_ptr -> hand[i]),trump) == false){
				if (Card_compare( &(player_ptr->hand[i]), &lead) >0){
					lead = player_ptr -> hand[i];
					p = &(player_ptr -> hand[i]);
				}
			}
			i++;
		}
	}
// case 2: player has only trump
	else{
		while (i<player_ptr -> hand_size){
                	if (Card_compare( &(player_ptr->hand[i]), &lead, trump) >0){
                                lead = player_ptr -> hand[i];
                                p = &(player_ptr -> hand[i]);
                        }   
                        i++;
		}
	}
// remove played card from hand
	i=0;
	while (p <= & (player_ptr -> hand[(player_ptr -> hand_size)-1])){
		*p = *(p+1);
		p++;
	}
	player_ptr -> hand_size --;
	return lead;
}

Card Player_play_card(Player *player_ptr, const Card *led_card, Suit trump){
	int follow_suit = 0;
	int i=0;
	Card toplay = player_ptr -> hand[0];
	Card *p = & (player_ptr -> hand[0]);
	while (i< player_ptr -> hand_size){
		if (Card_compare_suit(&(player_ptr -> hand[i]), led_card, trump) == 0)
			follow_suit = 1;
		i++;
	}
	i=0;
	if (follow_suit == 1){
		// initializes toplay to something of the suit of led card
		while (Card_compare_suit(&toplay, led_card, trump) != 0){
			toplay = player_ptr -> hand[i];
			p = &(player_ptr -> hand[i]);
			i++;
		}
		while (i< player_ptr -> hand_size){
			if (Card_compare_suit(&(player_ptr -> hand[i]), led_card, trump) == 0){
				if (Card_compare (&(player_ptr -> hand[i]), &toplay, led_card, trump)>0){
					toplay = player_ptr ->hand[i];
					p = &(player_ptr ->hand[i]);
				}
			}
			i++;
		}
	}
	else{
                while (i< player_ptr -> hand_size){
			if (Card_compare (&(player_ptr -> hand[i]), &toplay, led_card, trump)<0){
				toplay = player_ptr -> hand[i];
				p = &(player_ptr ->hand[i]);
			}
			i++;
		}
	}
	i=0;
        while (p <= & (player_ptr -> hand[(player_ptr -> hand_size) -1])){
		*p = *(p+1);
                p++;
        }
        player_ptr -> hand_size --;
        return toplay;
}
