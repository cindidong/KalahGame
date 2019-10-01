//
//  Board.cpp
//  project3
//
//  Created by Cindi Dong on 5/12/19.
//  Copyright © 2019 Cindi Dong. All rights reserved.
//

#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans
//per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it
//were 0.
{
    if (nHoles <= 0)
        m_holes = 1;
    if (nInitialBeansPerHole < 0)
        m_beans = 0;
    else
    {
        m_holes = nHoles;
        m_beans = nInitialBeansPerHole;
    }
    //array size has 2 sides and 2 pots
    arraySize = 2*m_holes+2;
    array = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
        array[i] = m_beans;
    array[0] = 0;
    array[m_holes+1] = 0;
}

Board::Board(const Board& b)
{
    m_holes = b.m_holes;
    m_beans = b.m_beans;
    arraySize = b.arraySize;
    array = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
        array[i] = b.array[i];
}

Board::~Board()
{
    delete [] array;
}

Board &Board::operator=(const Board &b)
{
    if (&b == this)
        return *this;
    delete [] array;
    m_holes = b.m_holes;
    m_beans = b.m_beans;
    arraySize = b.arraySize;
    array = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
        array[i] = b.array[i];
    return *this;
}

int Board::holes() const
//Return the number of holes on a side (not counting the pot).
{
    return (m_holes);
}

int Board::beans(Side s, int hole) const
//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
{
    if (hole > m_holes || hole < 0)
        return (-1);
    if (s == NORTH)
        return (array[hole]);
    if (s == SOUTH)
        if (hole == 0)
            return (array[m_holes+1]);
        else
            return (array[arraySize-hole]);
    else
        return (-1);
}

int Board::beansInPlay(Side s) const
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
{
    int count = 0;
    if (s == NORTH)
    {
        for (int i = 1; i < m_holes+1; i++)
            count = count + array[i];
    }
    if (s == SOUTH)
    {
        for (int i = m_holes+2; i < arraySize; i++)
            count = count + array[i];
    }
    return (count);
}

int Board::totalBeans() const
//Return the total number of beans in the game, including any in the pots.
{
    int count = 0;
    for (int i = 0; i < arraySize; i++)
        count += array[i];
    return (count);
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing
//anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown
//counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and
//endHole are set to the side and hole where the last bean was placed. (This function does not make captures or
//multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not
//be the responsibility of the Board class.)
{
    if (hole > m_holes || hole < 1)
        return (false);
    if (s == NORTH)
    {
        int beanAmount = array[hole];
        array[hole] = 0;
        int i = hole-1;
        while (beanAmount > 0)
        {
            //skips south's pot
            if (i == m_holes+1)
            {
                i--;
                continue;
            }
            array[i] += 1;
            beanAmount--;
            //resets index to the end
            if (beanAmount > 0 && i == 0)
            {
                i = arraySize-1;
                array[i] += 1;
                beanAmount--;
            }
            i--;
        }
        i++;
        if (i <= m_holes)
        {
            endSide = NORTH;
            endHole = i;
        }
        if (i >= m_holes+1)
        {
            if (i == m_holes+1)
            {
                endSide = SOUTH;
                endHole = 0;
            }
            else
            {
                endSide = SOUTH;
                endHole = arraySize-i;
            }
        }
        return (true);
    }
    if (s == SOUTH)
    {
        int beanAmount = array[arraySize-hole];
        array[arraySize-hole] = 0;
        int i = arraySize-hole;
        while (beanAmount > 0)
        {
            i--;
            //skips north's pot
            if (i == 0)
            {
                i = arraySize;
                continue;
            }
            array[i] += 1;
            beanAmount--;
        }
        if (i <= m_holes)
        {
            endSide = NORTH;
            endHole = i;
        }
        if (i >= m_holes+1)
        {
            if (i == m_holes+1)
            {
                endSide = SOUTH;
                endHole = 0;
            }
            else
            {
                endSide = SOUTH;
                endHole = arraySize-i;
            }
        }
        return (true);
    }
    else
        return (false);
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the bean
//in hole (s,hole) into the pot belonging to potOwner and return true.
{
    if (hole > m_holes || hole < 1)
        return (false);
    if (s == NORTH)
    {
        int tempBeans = array[hole];
        array[hole] = 0;
        if (potOwner == NORTH)
            array[0] = array[0] + tempBeans;
        else if (potOwner == SOUTH)
            array[m_holes+1] = array[m_holes+1] + tempBeans;
        return (true);
    }
    if (s == SOUTH)
    {
        int tempBeans = array[arraySize-hole];
        array[arraySize-hole] = 0;
        if (potOwner == NORTH)
            array[0] = array[0] + tempBeans;
        else if (potOwner == SOUTH)
            array[m_holes+1] = array[m_holes+1] + tempBeans;
        return (true);
    }
    else
        return (false);
}

bool Board::setBeans(Side s, int hole, int beans)
//If the indicated hole is invalid or beans is negative, this function returns false without changing anything.
//Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the
//third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function
//exists solely so that we and you can more easily test your program: None of your code that implements the member
//functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use
//below.)
{
    if (hole > m_holes || hole < 0)
        return (false);
    if (s == NORTH)
    {
        int tempBeans = array[hole];
        if (tempBeans < 0)
            return false;
        array[hole] = beans;
        return (true);
    }
    if (s == SOUTH)
    {
        //south's index for hole isn't 0
        if (hole == 0)
        {
            int tempBeans = array[m_holes+1];
            if (tempBeans < 0)
                return false;
            array[m_holes+1] = beans;
            return (true);
        }
        else
        {
            int tempBeans = array[arraySize-hole];
            if (tempBeans < 0)
                return false;
            array[arraySize-hole] = beans;
            return (true);
        }
    }
    else
        return (false);
}
