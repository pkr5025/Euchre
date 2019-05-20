#ifndef PACK_H
#define PACK_H
/* Pack.h
 *
 * Represents a pack of playing cards
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2013-09-06
 */


#include "Card.h"

const int PACK_SIZE = 24;

struct Pack {
  Card cards[PACK_SIZE];
  Card *next; //next card to be dealt
};

//REQUIRES pack_filename file contains a well-formed Euchre pack
//MODIFIES pack_ptr, stdout
//EFFECTS  Initializes Pack pointed to by pack_ptr by reading from pack_filename
//  if file IO fails, prints an error message and calls exit(EXIT_FAILURE).
void Pack_init(Pack *pack_ptr, const char* pack_filename);

//REQUIRES pack_ptr points to an initialized Pack
//  cards remain in the Pack
//MODIFIES pack_ptr
//EFFECTS  Returns the next card in the pack and increments the next pointer
Card Pack_deal_one(Pack *pack_ptr);

//REQUIRES pack_ptr points to an initialized Pack
//MODIFIES pack_ptr
//EFFECTS  Resets next pointer to first card in the Pack
void Pack_reset(Pack *pack_ptr);

//REQUIRES pack_ptr points to an initialized Pack
//MODIFIES pack_ptr
//EFFECTS  Shuffles the Pack and resets the next pointer.  See the project spec
//  for a description of the shuffling procedure
void Pack_shuffle(Pack *pack_ptr);

#endif
