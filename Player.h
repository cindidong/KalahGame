//
//  Player.hpp
//  project3
//
//  Created by Cindi Dong on 5/12/19.
//  Copyright © 2019 Cindi Dong. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Board.h"
#include <iostream>
#include <string>
using namespace std;

class Player
{
public:
    Player(std::string name);
    //Create a Player with the indicated name.
    std::string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be
    //computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing
    //side s and had to make a move given board b, the function returns the move the player would choose. If no move is
    //possible, return −1.
    virtual ~Player() {};
    //Since this class is designed as a base class, it should have a virtual destructor.
private:
    std::string m_name;
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    //Create a Player with the indicated name.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be
    //computer players.
    virtual int chooseMove(const Board& b, Side s) const;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing
    //side s and had to make a move given board b, the function returns the move the player would choose. If no move is
    //possible, return −1.
    
};

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    //Create a Player with the indicated name.
    virtual int chooseMove(const Board& b, Side s) const;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing
    //side s and had to make a move given board b, the function returns the move the player would choose. If no move is
    //possible, return −1.
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name);
    //Create a Player with the indicated name.
    virtual int chooseMove(const Board& b, Side s) const;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing
    //side s and had to make a move given board b, the function returns the move the player would choose. If no move is
    //possible, return −1.
private:
    int evaluate(const Board& temp, Side s, int maxDepth) const;
    int smartPlayerHelper(Board temp, Side s, int& bestHole, int depth, int maxDepth) const;
};

#endif /* Player_h */
