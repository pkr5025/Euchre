
/* Card.cpp
 *
 * Represents a single playing card
 *
 */


#include "Card.h"
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
const char *SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const int SUIT_SIZE = 4;
const char *RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six", 
                           "Seven", "Eight", "Nine", "Ten", "Jack", 
                           "Queen", "King", "Ace"};
const int RANK_SIZE = 13;


////////////////////////////////////////////////////////////////////////////////
void Suit_print(Suit suit) {
  cout << SUIT_NAMES[suit];
}

Suit Suit_next(Suit suit) {
  switch (suit) {
  case SPADES:   return CLUBS;
  case HEARTS:   return DIAMONDS;
  case CLUBS:    return SPADES;
  case DIAMONDS: return HEARTS;
  default:       assert(0); // should never get here
  }
}


////////////////////////////////////////////////////////////////////////////////
// Card

void Card_init(Card *card_ptr, Rank rank, Suit suit) {
  card_ptr->rank = rank;
  card_ptr->suit = suit;
}

void Card_print(const Card *card_ptr) {
  cout << RANK_NAMES[card_ptr->rank] << " of " << SUIT_NAMES[card_ptr->suit];
}

Suit Card_get_suit(const Card *card_ptr, Suit trump) {
  if (Card_is_left_bower(card_ptr, trump)) return trump;
  return card_ptr->suit;
}

bool Card_is_face(const Card *card_ptr) {
  return
    card_ptr->rank == JACK ||
    card_ptr->rank == QUEEN ||
    card_ptr->rank == KING ||
    card_ptr->rank == ACE;
}

bool Card_is_right_bower(const Card *card_ptr, Suit trump) {
  return card_ptr->rank == JACK && card_ptr->suit == trump; // JACK of trump suit
}

bool Card_is_left_bower(const Card *card_ptr, Suit trump) {
  return card_ptr->rank == JACK && 
    card_ptr->suit == Suit_next(trump); // JACK of trump's color
}

bool Card_is_trump(const Card *card_ptr, Suit trump) {
  return card_ptr->suit == trump ||
    Card_is_left_bower(card_ptr,trump);
}

int Card_compare(const Card *a, const Card *b) {

  // sanity check for NULL pointers
  assert(a);
  assert(b);

  // To simplify debugging and ensure that every correct solution will get the
  // same output, we’ve added an additional rule here.  In addition to being
  // ordered by rank, cards are also ordered by suit.
  return (a->suit + a->rank*SUIT_SIZE)
    -  (b->suit + b->rank*SUIT_SIZE);
}

int Card_compare_suit(const Card *a, const Card *b, Suit trump) {
	if (Card_get_suit(a, trump) == Card_get_suit(b, trump))
		return 0; 
	if (Card_get_suit(a, trump) == trump){
		if (Card_get_suit(b, trump) == trump)		
			return 0;
		else
			return 1;
	}
	else if (Card_get_suit(b, trump) == trump)
		return -1;
	if (Card_get_suit(a, trump) == DIAMONDS)
		return 1;
        else if (Card_get_suit(b, trump) == DIAMONDS)
                return -1;
	else if (Card_get_suit(a, trump) == CLUBS )
                return 1;
	else if (Card_get_suit(b, trump) == CLUBS)
		return -1;
	else if (Card_get_suit(a, trump) == HEARTS)
		return 1;
	else 
		return -1;
  assert(0);
}

void Card_init(Card *card_ptr, const char* rank, const char* suit) {
	int i=0;
	int j=0;
	while (strcmp(rank, RANK_NAMES[i]) !=0){ 
		i++;
	}
	while(strcmp(suit, SUIT_NAMES[j]) != 0){
		j++;
	}
	switch (i){
		case 0:
			card_ptr->rank = TWO;
			break;
                case 1:
                        card_ptr->rank = THREE;
                        break;
                case 2:
                        card_ptr->rank = FOUR;
                        break;
                case 3:
                        card_ptr->rank = FIVE;
                        break;
                case 4:
                        card_ptr->rank = SIX;
                        break;
                case 5:
                        card_ptr->rank = SEVEN;
                        break;
                case 6:
                        card_ptr->rank = EIGHT;
                        break;
                case 7:
                        card_ptr->rank = NINE;
                        break;
                case 8:
                        card_ptr->rank = TEN;
                        break;
                case 9:
                        card_ptr->rank = JACK;
                        break;
                case 10:
                        card_ptr->rank = QUEEN;
                        break;
                case 11:
                        card_ptr->rank = KING;
                        break;
                case 12:
                        card_ptr->rank = ACE;
                        break;
	}
	switch (j){
		case 0:
			card_ptr->suit = SPADES;
			break;
		case 1:
			card_ptr->suit = HEARTS;
			break;
		case 2:
			card_ptr->suit = CLUBS;
			break;
		case 3:
			card_ptr->suit = DIAMONDS;
			break;
	}
return;
assert(0);
}


int Card_compare(const Card *a, const Card *b, Suit trump) {
        if (((*a).suit  == (*b).suit ) && ((*a).rank == (*b).rank))
		return 0;
	if (Card_get_suit(a, trump) == trump){
		if (Card_get_suit(b,trump) == trump){
			if (Card_is_right_bower(a, trump) == true)			
				return 1;
			else if (Card_is_right_bower(b, trump) == true)
				return -1;
                        else if (Card_is_left_bower(a, trump) == true)
                                return 1;
                        else if (Card_is_left_bower(b, trump) == true)
                                return -1;

			else if ((*a).rank > (*b).rank)
				return 1;
			else
				return -1;
		}
		else
			return 1;
	}
	else  if (Card_get_suit(b,trump) == trump)
		return -1;
	else{
		if ((*a).rank > (*b).rank)
			return 1;
		else if ((*b).rank > (*a).rank)
			return -1;
		else
			return Card_compare_suit(a,b,trump);
	}
		
assert(0);
}


int Card_compare(const Card *a, const Card *b, const Card *led_card, Suit trump) {
	if (((*a).suit  == (*b).suit ) && ((*a).rank == (*b).rank))
                return 0;
	if ((Card_is_trump(a, trump) == true) || (Card_is_trump(b, trump) == true))
		return Card_compare(a, b, trump);
	if (Card_compare_suit(a, led_card, trump) == 0){
		if (Card_compare_suit(b, led_card, trump) == 0){
			if ((a->rank) > (b->rank))
				return 1;
			else
				return -1;
		}
		else
			return 1;
	}
	if (Card_compare_suit(b, led_card, trump) == 0)		
		return -1;
	return Card_compare(a, b, trump);
assert(0);
}
