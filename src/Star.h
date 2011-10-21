/*
 *  Star.h
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
