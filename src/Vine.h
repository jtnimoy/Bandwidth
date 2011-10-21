/*
 *  Vine.h
 *  emptyExample
 *

// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//
 *
 */

#ifndef VINE_H
#define VINE_H

#include "ofMain.h"
#include "Box2D/Box2D.h"
#include "MColor.h"

class Vine{
public:
	Vine(float x,float len,MColor color_,float radius_);
	b2Body *ball;
	b2Body *pivot;
	b2RopeJoint *joint;
	MColor color;
	float radius;
	void hit();
	int hitCounter;
	MColor getColor();
	void step();
};

#endif
