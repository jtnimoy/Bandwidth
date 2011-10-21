/*
 *  RippleBall.h
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

#ifndef RIPPLEBALL_H
#define RIPPLEBALL_H

#include "ofMain.h"
#include "MColor.h"

#include <map>

#define RIPPLEBALL_INTERSECTS 3
#define RIPPLEBALL_NOT_INTERSECTS 2
#define RIPPLEBALL_DEATH_DURATION 100.0f

class RippleBall{
public:
	RippleBall(int xx,int yy);
	void step();
	float x;
	float y;
	int death;
    int ticks;
    MColor color;
    float radius;
    map<RippleBall*,int> intersections;
    int countIntersections();
    bool intersectsNonConcentric(RippleBall *that);
    float getAlpha();
    ofSoundPlayer snd0;
    int lastIntersectionCount;
    float rotationSpeed;
    float fillAlpha;
};

#endif

