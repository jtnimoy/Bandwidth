/*
 *  GridBall.h
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/10/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
 *
 */

#ifndef BALL_H
#define BALL_H

#include "ofMain.h"



class GridBall{
public:
	GridBall();
	void step();
	void beat();
	float x;
	float y;
	static float speed;
	bool side;
	bool testSide();
	int timer;
	ofSoundPlayer snd0;
	static int delay;
	bool dead;
	int alphaTimer;
};

#endif