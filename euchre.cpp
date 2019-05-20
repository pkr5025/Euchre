#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Game.h"
using namespace std;

int main(int argc, char *argv[]){
if (argc !=8){
	cout<<"Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4"<<endl;
	exit(EXIT_FAILURE);
	}
if ((strcmp(argv[2], "shuffle") != 0) && (strcmp(argv[2], "noshuffle") != 0)){
	cout<<"Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4"<<endl;
	exit(EXIT_FAILURE);
	}
if ((atoi(argv[3])>100) || (atoi(argv[3])<1)){
	cout<<"Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4"<<endl;
	exit(EXIT_FAILURE);
	}
Game game;
const char *const player_names[] = {argv[4], argv[5], argv[6], argv[7]};
const char *pack_filename = argv[1];
bool shuffle = false;
if (strcmp(argv[2], "shuffle") == 0)
	shuffle = true;
for (int i=0; i<argc; i++){
	cout<<argv[i]<<" ";
}
cout<<endl;
Game_init(&game, pack_filename, shuffle, atoi(argv[3]), player_names );
Game_play(&game);
return EXIT_SUCCESS;
}
