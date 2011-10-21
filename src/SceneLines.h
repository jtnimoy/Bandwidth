//
//  SceneLines.h
//  BANDWIDTH
//
//  Created by Josh Nimoy on 10/20/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#ifndef BANDWIDTH_SceneLines_h
#define BANDWIDTH_SceneLines_h

#include <vector>
#include "Line.h"
#include "Scene.h"

class SceneLines:public Scene{
public:
    void setup();
    void update();
    void draw(float alpha);
    void keyPressed(int key);
    void mouseMoved(int x,int y);
    void mouseDragged(int x,int y,int button);
    void mousePressed(int x,int y,int button);
    void mouseReleased(int x,int y,int button);
    void reset();
    std::vector<Line*>lines;
	static SceneLines* instance;
	ofSoundPlayer snd0;
    
	float buttonAlpha;
    
    int deathCount;
    
    float welltempered[128];
    int ticks;

};

#endif
