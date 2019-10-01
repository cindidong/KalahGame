//
//  Game.cpp
//  project3
//
//  Created by Cindi Dong on 5/12/19.
//  Copyright © 2019 Cindi Dong. All rights reserved.
//

#include "Game.h"

Game::Game(const Board& b, Player* south, Player* north) : m_board(b), southPlayer(south), northPlayer(north)
//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side
//always moves first.
{
    currentSide = SOUTH;
    isGameOver = false;
}
void Game::display() const
//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable
//representation of the state of the board.
{
    cout<<"   "<<northPlayer->name()<<endl;
    cout<<"  ";
    for (int i = 1; i < m_board.holes()+1; i++)
        cout<<m_board.beans(NORTH, i)<<" ";
    cout<<endl;
    cout<<m_board.beans(NORTH, 0)<<"          "<<m_board.beans(SOUTH, 0)<<endl;
    cout<<"  ";
    for (int i = 1; i < m_board.holes()+1; i++)
        cout<<m_board.beans(SOUTH, i)<<" ";
    cout<<endl;
    cout<<"   "<<southPlayer->name()<<endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else.
//Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If
//hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
{
    if (m_board.beansInPlay(NORTH) != 0 || m_board.beansInPlay(SOUTH) != 0)
    {
        over = false;
    }
    else
    {
        over = true;
        if (m_board.beans(NORTH, 0) == m_board.beans(SOUTH, 0))
            hasWinner = false;
        else
        {
            hasWinner = true;
            if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0))
                winner = NORTH;
            if (m_board.beans(NORTH, 0) < m_board.beans(SOUTH, 0))
                winner = SOUTH;
        }
    }
}
bool Game::move()
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it
//becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and
//takes any additional turns required or completes a capture. If the player gets an additional turn, you should
//display the board so someone looking at the screen can follow what's happening.
{
    Side endSide;
    int endHole = 0;
    if (currentSide == NORTH)
    {
        int hole = northPlayer->chooseMove(m_board, currentSide);
        cout<<northPlayer->name()<<" picked hole "<<hole<<endl;
        m_board.sow(currentSide, hole, endSide, endHole);
        //checks if player lands in their pot
        while (endHole == 0 && endSide == NORTH)
        {
            if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0)
                break;
            display();
            int hole = northPlayer->chooseMove(m_board, NORTH);
            cout<<northPlayer->name()<<" picked hole "<<hole<<endl;
            m_board.sow(NORTH, hole, endSide, endHole);
        }
        //checks for a capture
        if (endSide == NORTH && m_board.beans(endSide, endHole) == 1 && endHole != 0)
        {
            if (m_board.beans(SOUTH, endHole) > 0)
            {
                cout<<"Capture!"<<endl;
                m_board.moveToPot(SOUTH, endHole, NORTH);
                m_board.moveToPot(NORTH, endHole, NORTH);
            }
        }
        currentSide = SOUTH;
    }
    
    else if (currentSide == SOUTH)
    {
        int hole = southPlayer->chooseMove(m_board, currentSide);
        cout<<southPlayer->name()<<" picked hole "<<hole<<endl;
        m_board.sow(currentSide, hole, endSide, endHole);
        //checks if player lands on a pot
        while (endHole == 0 && endSide == SOUTH)
        {
            if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0)
                break;
            display();
            int hole = southPlayer->chooseMove(m_board, SOUTH);
            cout<<southPlayer->name()<<" picked hole "<<hole<<endl;
            m_board.sow(SOUTH, hole, endSide, endHole);
        }
        //checks for a capture
        if (endSide == SOUTH && m_board.beans(endSide, endHole) == 1 && endHole != 0)
        {
            if (m_board.beans(NORTH, endHole) > 0)
            {
                cout<<"Capture!"<<endl;
                m_board.moveToPot(NORTH, endHole, SOUTH);
                m_board.moveToPot(SOUTH, endHole, SOUTH);
            }
        }
        currentSide = NORTH;
    }
    //checks ending conditions
    if (m_board.beansInPlay(NORTH) == 0)
    {
        cout<<"Sweeping "<<southPlayer->name()<<"'s beans"<<endl;
        for (int i = 1; i < m_board.holes()+1; i++)
        {
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
        display();
        return (false);
    }
    else if (m_board.beansInPlay(SOUTH) == 0)
    {
        cout<<"Sweeping "<<northPlayer->name()<<"'s beans"<<endl;
        for (int i = 1; i < m_board.holes()+1; i++)
        {
            m_board.moveToPot(NORTH, i, NORTH);
        }
        display();
        return (false);
    }
    return (true);
}

void Game::play()
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the
//screen can follow what's happening. If neither player is interactive, then to keep the display from quickly
//scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to
//continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce
//the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board
//between this function and the move function. (Note: If when this function is called, South has no beans in play,
//so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus
//over.)
{
    int count = 0;
    //checks for ending conditions
    if (m_board.beansInPlay(SOUTH) == 0)
    {
        display();
        for (int i = 1; i < m_board.holes()+1; i++)
        {
            m_board.moveToPot(NORTH, i, NORTH);
        }
        isGameOver = true;
    }
    else if (m_board.beansInPlay(NORTH) == 0)
    {
        display();
        for (int i = 1; i < m_board.holes()+1; i++)
        {
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
        isGameOver = true;
    }
    //handles the case for two computer players
    else if (northPlayer->isInteractive() == false && southPlayer->isInteractive() == false)
    {
        while (isGameOver == false)
        {
            count++;
            display();
            bool flag = move();
            if (flag == false)
            {
                isGameOver = true;
            }
            if (count >= 3)
            {
                cout<<"Press enter to continue ";
                cin.get();
                count = 0;
            }
        }
    }
    //handles the case for 1 human player
    else
    {
        while (isGameOver == false)
        {
            display();
            bool flag = move();
            if (flag == false)
            {
                isGameOver = true;
            }
        }
    }
    //sets winner
    bool over = false;
    bool hasWinner = true;
    Side winner = NORTH;
    if (isGameOver == true)
    {
        status(over, hasWinner, winner);
        if (winner == NORTH)
        {
            cout<<"The winner is "<<northPlayer->name()<<endl;
        }
        if (winner == SOUTH)
        {
            cout<<"The winner is "<<southPlayer->name()<<endl;
        }
    }
}

int Game::beans(Side s, int hole) const
//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid.
//This function exists so that we and you can more easily test your program.
{
    if (hole > m_board.holes() || hole < 0)
        return (-1);
    return(m_board.beans(s, hole));
}
