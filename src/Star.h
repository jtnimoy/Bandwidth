/*
 *  Star.h
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/21/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
 *
 */

#ifndef STAR_H
#define STAR_H

#include "ofMain.h"
#include "MColor.h"

class Star{
private:
	float rad;
public:
    Star();
	Star(ofVec2f p);
	void step();
	ofVec2f pos;
	int ticks;
	MColor color;
	float getRadius();
    int soundIndex;
    float strength;
    static int screenLowWidth;
    static int screenLowHeight;
    bool loaded;
    float rotation;
};

#endif