/*
 *  Vine.h
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/7/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
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