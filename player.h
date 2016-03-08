#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <stdlib.h> 
#include <vector>
#include "common.h"
#include "board.h"
using namespace std;


static int scoreboard[8][8] = 
{{10, -3, 3, 3, 3, 3, -3, 10},\
{-3, -10, 0, 0, 0, 0, -10, -3},\
{3, 0, 0, 0, 0, 0, 0, 3},\
{3, 0, 0, 0, 0, 0, 0, 3},\
{3, 0, 0, 0, 0, 0, 0, 3},\
{3, 0, 0, 0, 0, 0, 0, 3},\
{-3, -10, 0, 0, 0, 0, -10, -3},\
{10, -3, 3, 3, 3, 3, -3, 10}};

struct treeNode{
	Board *data;
	std::vector<treeNode> children;
	int score;

	treeNode(Board *b, Side myside, Side theirside)
	{
		data = b;
		score = b->count(myside) - b->count(theirside);
	}
	void addchild(treeNode c)
	{
		children.push_back(c);
	}

};
class Player {
private:
	Board *game;
	Side theirside;
	Side myside;
public:
    Player(Side side);
    ~Player();
    void setBoard(Board *b);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
