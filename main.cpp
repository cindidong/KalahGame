//
//  main.cpp
//  project3
//
//  Created by Cindi Dong on 5/11/19.
//  Copyright © 2019 Cindi Dong. All rights reserved.
//

#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
           b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
           b.beansInPlay(SOUTH) == 3);
    
    Side es;
    int eh;
    
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
           b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
           b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
    
    assert(es == NORTH);
    assert(eh == 3);
    assert(b.beans(SOUTH, 3) == 0);
    assert(b.beans(NORTH, 3) == 3);
    assert(b.beans(SOUTH, POT) == 3);
    assert(b.beansInPlay(SOUTH) == 1);
    assert(b.beansInPlay(NORTH) == 7);
    
    Board b1(3, 7);
    b1.sow(SOUTH, 3, es, eh);
    assert(b1.beans(SOUTH, POT) == 1); ///check if there is one bean in south's pot
    assert(b1.beans(SOUTH, 3) == 1);  ///checks to see if there is 1 bean in spot 3 on the south side
    assert(es == SOUTH);
    assert(eh == 3);
    
    Board b2(6, 2);
    b2.sow(SOUTH, 1, es, eh);
    assert(b2.beans(SOUTH, 1) == 0);
    assert(b2.beans(SOUTH, 2) == 3);
    assert(b2.beans(SOUTH, 3) == 3);
    assert(b2.beans(SOUTH, 4) == 2);
    
    Board b3(2, 1);
    b3.sow(SOUTH, 1, es, eh);
    assert(b3.beans(SOUTH, 1) == 0);
    assert(b3.beans(SOUTH, 2) == 2);
    assert(b3.beans(SOUTH, POT) == 0);
    assert(es == SOUTH);
    assert(eh == 2);
    
    ///check a case that ends in a pot
    Board b4 (2, 1);
    b4.sow(SOUTH, 2, es, eh);
    assert(b4.beans(SOUTH, 2)== 0);
    assert(b4.beans(SOUTH, POT) == 1);
    assert(es == SOUTH);
    assert(eh == 0);
    
    ///now check the north cases
    Board b5 (3, 3);
    b5.sow(NORTH, 1, es, eh);
    assert(es == SOUTH);
    assert(eh == 2);
    assert(b5.beans(NORTH, 500000000) == -1);
    
    Board b6(3, 2);
    assert(b6.holes() == 3  &&  b6.totalBeans() == 12  &&
           b6.beans(NORTH, POT) == 0  &&  b6.beansInPlay(NORTH) == 6);
    b6.setBeans(NORTH, 1, 1);
    b6.moveToPot(NORTH, 2, NORTH);
    assert(b6.totalBeans() == 11  &&  b6.beans(NORTH, 1) == 1  &&
           b6.beans(NORTH, 2) == 0  &&  b6.beans(NORTH, POT) == 2  &&
           b6.beansInPlay(NORTH) == 3);
    
    
    ///test case: Try inserting beans into a hole that does not exist
    Board b7(1, 0);
    assert(b7.setBeans(NORTH, 2, 3) == false);
    ///now, using the same board, see if this algorithm works for a the smallest board
    b7.setBeans(NORTH, 1, 10);
    assert(b7.beans(NORTH, 1) == 10);
    assert(b7.beans(NORTH, POT) == 0);
    assert(b7.beans(SOUTH, 1) == 0);
    assert(b7.beans(SOUTH, POT) == 0);
    b7.sow(NORTH, 1, es, eh);
    assert(b7.beans(SOUTH, POT) == 0);
    assert(b7.beans(NORTH, POT) == 4);
    
    
    Board b8(2, 5);
    b8.sow(NORTH, 1, es, eh);
    assert(b8.beans(NORTH, POT) == 1);
    assert(b8.beans(SOUTH, POT) == 0);
    assert(b8.beans(NORTH, 1) == 1);
    
    
    Board b9(2, 5);
    b9.sow(SOUTH, 1, es, eh);
    assert(b9.beans(SOUTH, POT) == 1);
    assert(b9.beans(SOUTH, 1) == 1);
    assert(b9.beans(SOUTH, 2) == 6);
    assert(b9.beans(NORTH, 2) == 6);
    assert(b9.beans(NORTH, 1) == 6);
    assert(b9.beans(NORTH, POT) == 0);
    
    ///try a really small case on the south side
    Board b10(1, 5);
    b10.sow(SOUTH, 1, es, eh);
    assert(b10.beans(NORTH, POT) == 0);
    assert(b10.beans(NORTH, 1) == 7);
    assert(b10.beans(SOUTH, POT) == 2);
    assert(b10.beans(SOUTH, 1) == 1);
    
    ///now check a case in which we start at an edge case
    Board b11 (5, 3);
    ///this is what the board should look like at the beginning
    ///     3   3   3   3   3
    /// 0                       0
    ///     3   3   3   3   3
    for (int i = 1; i < 6; i ++)
    {
        assert(b11.beans(NORTH, i) == 3);
        assert(b11.beans(SOUTH, i) == 3);
    }
    ///and both the pots should be 0
    assert(b11.beans(NORTH, POT) == 0);
    assert(b11.beans(SOUTH, POT) == 0);
    
    b11.sow(SOUTH, 5, es, eh);
    ///at the end
    ///     3   3   3   4   4
    /// 0                       1
    ///     3   3   3   3   0
    for (int i = 1; i < 4; i ++)
    {
        assert(b11.beans(NORTH, i) == 3);
        assert(b11.beans(SOUTH, i) == 3);
    }
    assert(b11.beans(SOUTH, 4) == 3);
    assert(b11.beans(SOUTH, 5) == 0);
    assert(b11.beans(NORTH, 5) == 4);
    assert(b11.beans(NORTH, 4) == 4);
    assert(es == NORTH && eh == 4);
    
    ///now check something in the middle, that might end in a hole
    ///use the same (updated) board as above, and sow at position 3
    b11.sow(SOUTH, 3, es, eh);
    ///new board
    ///     3   3   3   4   4
    /// 0                       2
    ///     3   3   0   4   1
    for (int i = 1; i < 3; i ++)
    {
        assert(b11.beans(NORTH, i) == 3);
        assert(b11.beans(SOUTH, i) == 3);
    }
    assert(b11.beans(SOUTH, 3) == 0);
    assert(b11.beans(SOUTH, 4) == 4);
    assert(b11.beans(SOUTH, 5) == 1);
    assert(b11.beans(NORTH, 3) == 3);
    assert(b11.beans(NORTH, 4) == 4);
    assert(b11.beans(NORTH, 5) == 4);
    ///now check the end
    assert(es == SOUTH && eh == 0);
    ///and check the pots
    assert(b11.beans(NORTH, POT) == 0);
    assert(b11.beans(SOUTH, POT) == 2);
    
    ///now check the middle and it does not end in a hole
    b11.sow(SOUTH, 2, es, eh);
    ///new board
    ///     3   3   3   4   4
    /// 0                       2
    ///     3   0   1   5   2
    assert(es == SOUTH && eh == 5);
    assert(b11.beans(SOUTH, 1) == 3);
    assert(b11.beans(SOUTH, 2) == 0);
    assert(b11.beans(SOUTH, 3) == 1);
    assert(b11.beans(SOUTH, 4) == 5);
    assert(b11.beans(SOUTH, 5) == 2);
    assert(b11.beans(NORTH, 1) == 3);
    assert(b11.beans(NORTH, 2) == 3);
    assert(b11.beans(NORTH, 3) == 3);
    assert(b11.beans(NORTH, 4) == 4);
    assert(b11.beans(NORTH, 5) == 4);
    assert(b11.beans(NORTH, POT) == 0);
    assert(b11.beans(SOUTH, POT) == 2);
    
    ///try a smaller test case starting on the north side
    Board b12(1, 10);
    ///original board:
    ///     10
    /// 0        0
    ///     10
    assert(b12.beans(NORTH, 0) == 0);
    assert(b12.beans(NORTH, 1) == 10);
    assert(b12.beans(SOUTH, 0) == 0);
    assert(b12.beans(SOUTH, 1) == 10);
    ///sow on the north
    b12.sow(NORTH, 1, es, eh);
    ///updated board:
    ///     3
    /// 4        0
    ///     13
    assert(b12.beans(NORTH, 0) == 4);
    assert(b12.beans(NORTH, 1) == 3);
    assert(b12.beans(SOUTH, 0) == 0);
    assert(b12.beans(SOUTH, 1) == 13);
    assert(es == NORTH && eh == 0);
    
    ///try the same thing on the south side
    Board b13(1, 10);
    assert(b13.beans(NORTH, 0) == 0);
    assert(b13.beans(NORTH, 1) == 10);
    assert(b13.beans(SOUTH, 0) == 0);
    assert(b13.beans(SOUTH, 1) == 10);
    b13.sow(SOUTH, 1, es, eh);
    assert(b13.beans(SOUTH, 0) == 4);
    assert(b13.beans(SOUTH, 1) == 3);
    assert(b13.beans(NORTH, 0) == 0);
    assert(b13.beans(NORTH, 1) == 13);
    
    ///now try a more complicated case for starting in the north
    Board b14(2, 7);
    assert(b14.beans(NORTH, 0) == 0);
    assert(b14.beans(NORTH, 1) == 7);
    assert(b14.beans(NORTH, 2) == 7);
    assert(b14.beans(SOUTH, 0) == 0);
    assert(b14.beans(SOUTH, 1) == 7);
    assert(b14.beans(SOUTH, 2) == 7);
    b14.sow(NORTH, 1, es, eh);
    ///updated board:
    ///     1    8
    /// 2             0
    ///     9    8
    assert(b14.beans(NORTH, 0) == 2);
    assert(b14.beans(NORTH, 1) == 1);
    assert(b14.beans(NORTH, 2) == 8);
    assert(b14.beans(SOUTH, 0) == 0);
    assert(b14.beans(SOUTH, 1) == 9);
    assert(b14.beans(SOUTH, 2) == 8);
    assert(es == SOUTH && eh == 1);
    ///now sow the furthest one
    ///updated board:
    ///     3    1
    cout<<"passed all tests"<<endl;
}
