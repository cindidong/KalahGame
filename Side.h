//
//  Side.h
//  project3
//
//  Created by Cindi Dong on 5/14/19.
//  Copyright © 2019 Cindi Dong. All rights reserved.
//

#ifndef Side_h
#define Side_h

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

#endif /* Side_h */
