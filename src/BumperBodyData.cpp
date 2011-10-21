//
//  Ball.cpp
//  BANDWIDTH
//
//  Created by Josh Nimoy on 10/16/11.

// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
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
