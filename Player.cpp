//
//  Player.cpp
//  project3
//
//  Created by Cindi Dong on 5/12/19.
//  Copyright © 2019 Cindi Dong. All rights reserved.
//

#include "Player.h"

Player::Player(std::string name)
//Create a Player with the indicated name.
{
    m_name = name;
}
std::string Player::name() const
//Return the name of the player.
{
    return (m_name);
}
bool Player::isInteractive() const
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be
//computer players.
{
    return false;
}
HumanPlayer::HumanPlayer(std::string name) : Player(name) {}
//Create a Player with the indicated name.

bool HumanPlayer::isInteractive() const
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be
//computer players.
{
    return true;
}
int HumanPlayer::chooseMove(const Board& b, Side s) const
//Every concrete class derived from this class must implement this function so that if the player were to be playing
//side s and had to make a move given board b, the function returns the move the player would choose. If no move is
//possible, return −1.
{
    if (b.beansInPlay(s) == 0)
        return (-1);
    int hole = 0;
    cout<<"Select a hole, "<<name()<<": ";
    cin>>hole;
    //while(b.beans(s, hole) == -1)
    while (hole > b.holes() || hole < 0)
    {
        cout<<"The hole number must be from 1 to "<<b.holes()<<"."<<endl;
        cout<<"Select a hole, "<<name()<<": ";
        cin>>hole;
    }
    while (b.beans(s, hole) < 1)
    {
        cout<<"There are no beans in that hole."<<endl;
        cout<<"Select a hole, "<<name()<<": ";
        cin>>hole;
    }
    return (hole);
}

BadPlayer::BadPlayer(std::string name) : Player(name) {}
//Create a Player with the indicated name.

int BadPlayer::chooseMove(const Board& b, Side s) const
//Every concrete class derived from this class must implement this function so that if the player were to be playing
//side s and had to make a move given board b, the function returns the move the player would choose. If no move is
//possible, return −1.
{
    //picks the first hole with beans in it
    for (int i = 1; i < b.holes() + 1; i++)
    {
        if (b.beans(s, i) > 0)
            return i;
    }
    return (-1);
}

SmartPlayer::SmartPlayer(std::string name) : Player(name) {}
//Create a Player with the indicated name.

int SmartPlayer::chooseMove(const Board& b, Side s) const
//Every concrete class derived from this class must implement this function so that if the player were to be playing
//side s and had to make a move given board b, the function returns the move the player would choose. If no move is
//possible, return −1.
{
    int maxDepth = 4;
    int bestHole = -1;
    if (b.beansInPlay(s) == 0)
        return (-1);
    smartPlayerHelper(b, s, bestHole, 0, maxDepth);
    return (bestHole);
}

//evaluates my heuristic
int SmartPlayer::evaluate(const Board& temp, Side s, int maxDepth) const
{
    int difference;
    if (s == NORTH)
        difference = temp.beans(NORTH, 0)-temp.beans(SOUTH, 0);
    else
        difference = temp.beans(SOUTH, 0)-temp.beans(NORTH, 0);
    if (maxDepth%2 != 0)
        difference = -difference;
    return (difference);
}

//helper function for the recursion
int SmartPlayer::smartPlayerHelper(Board b, Side s, int& bestHole, int depth, int maxDepth) const
{
    Side endSide;
    int endHole;
    int bestScore;
    //initializing bestScore
    if (depth%2 == 0)
        bestScore = -9999999;
    else
        bestScore = 99999999;
    //base case for winning condition
    if (b.beansInPlay(s) == 0)
    {
        if (s == NORTH) {
            bestScore = b.beans(NORTH, 0) - (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0));
            //checks if the smart player is north or south. if it is south, the sign is negative
            if (depth%2 != 0)
                bestScore = -bestScore;
        }
        if (s == SOUTH) {
            bestScore = b.beans(SOUTH, 0) - (b.beansInPlay(NORTH) + b.beans(NORTH, 0));
            //checks if the smart player is north or south. if it is north, the sign is negative
            if (depth%2 != 0)
                bestScore = -bestScore;
        }
        //if bestScore is postive, current side has won. set to postitive infinity
        if (bestScore > 0)
            bestScore = 9999999;
        //if bestScore is negative, other side has won. set to negative infinity
        else
            bestScore = -9999999;
        return bestScore;
    }
    //base case for maxDepth
    if (depth >= maxDepth)
        return evaluate(b, s, maxDepth);
    for (int i = 1; i <= b.holes(); i++)
    {
        //check if hole is empty (invalid move)
        if (b.beans(s, i) > 0)
        {
            Board temp(b);
            temp.sow(s, i, endSide, endHole);
            int score = smartPlayerHelper(temp, s, bestHole, depth+1, maxDepth);
            //checks if current side is smart player
            if (depth%2 == 0)
            {
                if (score >= bestScore)
                {
                    bestScore = score;
                    bestHole = i;
                }
            }
            //checks if current side is not smart player
            else
            {
                if (score <= bestScore)
                {
                    bestScore = score;
                    bestHole = i;
                }
            }
        }
    }
    return bestScore;
}
