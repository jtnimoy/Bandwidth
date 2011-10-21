/*
 *  RippleBall.h
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/10/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
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

