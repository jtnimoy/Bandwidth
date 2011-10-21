/*
 *  GridBall.h
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
