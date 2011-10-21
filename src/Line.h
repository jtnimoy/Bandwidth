/*
 *  Ball.h
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

#ifndef LINE_H
#define LINE_H

#include "ofMain.h"
#include "MColor.h"
#include <map>
using namespace std;

class Line{
public:
        Line();
	Line(int xx,int yy);
	void step();
	float x;
	float y;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;
    float ballX;
    float ballY;
    float dest_x2;
    float dest_y2;
	int death;
    int ticks;
    MColor color;
    MColor ballColor;
    
    void draw(float alpha);
    float lineWidth;
    float ballPosition;
    int ballSpeed;
    
    float slope;
    float elevation;
    
    bool pointAbove(float xx,float yy);
    map<Line*,int> sides;
    float radius;
    void sound();
    void crossed();
    int pluckCounter;
};

#endif

