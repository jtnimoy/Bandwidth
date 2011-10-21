//
//  Ball.h
//  emptyExample
//
//  Created by Josh Nimoy on 10/16/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#ifndef BumperBodyData_h
#define BumperBodyData_h

class BumperBodyData{
  
public:
    BumperBodyData(int type_);
    int birthFrame;    
    int type;
    static int TYPE_OBSTACLE;
    static int TYPE_BALL;
    static int TYPE_GROUND;
    int lastHitFrame;
    int hitCount;
};

#endif
