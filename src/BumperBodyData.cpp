//
//  Ball.cpp
//  emptyExample
//
//  Created by Josh Nimoy on 10/16/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#include <iostream>
#include "ofMain.h"
#include "BumperBodyData.h"

int BumperBodyData::TYPE_OBSTACLE = 1;
int BumperBodyData::TYPE_BALL = 2;
int BumperBodyData::TYPE_GROUND = 3;


BumperBodyData::BumperBodyData(int type_){
    type = type_;
    lastHitFrame = birthFrame = ofGetFrameNum();
    hitCount = 0;
}
