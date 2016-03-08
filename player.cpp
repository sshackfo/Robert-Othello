#include "player.h"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <climits>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;
    game = new Board(); // makes a game board
    myside = side;         // remembers the player's side
    if(myside == WHITE)
        theirside = BLACK;
    else
        theirside = WHITE;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete game;       // destroys the board object you've created
}

void Player::setBoard(Board *b){
    game = b;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    if(testingMinimax == true)
    {
        game->doMove(opponentsMove, theirside);       
        // Uses Minimax to play game
        //make treenode corresponding to initial board
        treeNode *root = new treeNode(game, myside, theirside);
        //for each possible move of mine, make a board        
        // as a child to the initial board
        int max = INT_MIN;
        Move *winner = NULL;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j< 8 ; j++)
            {
                Move m(i,j);

                if(game->checkMove(&m, myside))
                {
                    // make new board copy of game
                    // do move on that board
                    Move *muv = new Move(i, j);
                    Board *copy = game->copy();
                    copy->doMove(muv, myside);
                    // Make new treenode and append to tree
                    treeNode *t = new treeNode(copy, myside, theirside);
                    root->addchild(*t);

                    std::vector<treeNode> children;
                    children.push_back(*t);
                    int minscore = INT_MAX;
                    for(int k = 0; k < 8; k++)
                    {
                        for(int l = 0; l < 8; l++)
                        {
                            Move h(k,l);
                            if(copy->checkMove(&h, theirside))
                            {
                                // make new board copy of game
                                // do move on that board
                                Move *theirmuv = new Move(k, l);
                               Board *theircopy = t->data->copy();
                                theircopy->doMove(theirmuv, theirside);
                                treeNode *th = new treeNode(theircopy, myside, theirside);
                                t->addchild(*th);
                                if(th->score < minscore)
                                {
                                    minscore = th->score;
                                }
                            }
                        }
                    }
                    //sets t's score to the minimum of it's children's scores
                    t->score = minscore;
                    if(t -> score > max)
                    {
                        max = t-> score;
                        winner = muv;
                    }
                }
            }
        } 
        game->doMove(winner, myside);
        return winner;
    }
    else
    {
       // update board to represent opponent's move
        game->doMove(opponentsMove, theirside);
        // now see if have any legal moves left (if not return null)
        if(!game->hasMoves(myside))
        {
            return NULL;
        }
        // Maximum score for a given move. Initialized to lowest possible score
        int maxscore = -10;
        // Sets default move to a terrible move. We know at least one move is 
        // Possible so if this isn't the best move the move will be changed
        Move *muv = new Move(1, 1);

        // Iterate through moves, comparing move score to max score. Saves best
        // current move.
        
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                Move m(i,j);
                if(game->checkMove(&m, myside))
                {
                    int score = scoreboard[i][j];
                    if (score > maxscore)
                    {
                        maxscore = score;
                        muv->setX(i);
                        muv->setY(j);
                    }
                }
            }
        }
        game-> doMove(muv, myside);
        return muv; 
    }
        
}
