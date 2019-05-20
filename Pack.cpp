// pkleinr Philip Klein-Rodick
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "Pack.h"
#include <string>
#include <cstdlib>
using namespace std;

void Pack_init(Pack *pack_ptr, const char* pack_filename){
	ifstream filestream;
	filestream.open(pack_filename);
	if (! filestream.is_open()){
		cout<<"Error opening "<<pack_filename<<endl;
		exit(EXIT_FAILURE);
	}
	string word1, word2, word3;
	int i=0;
	while (filestream >> word1 >> word2 >> word3){
		Card_init(&(pack_ptr -> cards[i]), word1.c_str(), word3.c_str());
		i++;
	}
	pack_ptr -> next = &(pack_ptr -> cards[0]);
	filestream.close();
}

Card Pack_deal_one(Pack *pack_ptr){
	(pack_ptr -> next) ++;
	return *((pack_ptr -> next) -1);
}

void Pack_reset(Pack *pack_ptr){
	(*pack_ptr).next = & (pack_ptr -> cards[0]);
}

void Pack_shuffle(Pack *pack_ptr){
	Card temp[3] = {pack_ptr -> cards[0], pack_ptr -> cards[1], pack_ptr -> cards[2]};
	int x=0;
	while (x<21){
		pack_ptr -> cards[x] = pack_ptr -> cards[x+3];
		x++;
	}
	x=0;
	while (x<3){
		pack_ptr -> cards[PACK_SIZE-(3-x)] = temp[x];
		x++;
	}
	(*pack_ptr).next = & (pack_ptr -> cards[0]);

}
