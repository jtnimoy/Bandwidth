//
//  SceneRipple.h
//  BANDWIDTH
//
//  Created by Josh Nimoy on 10/20/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#ifndef BANDWIDTH_SceneRipple_h
#define BANDWIDTH_SceneRipple_h

#include "RippleBall.h"
#include "Scene.h"
#include "ofxOsc.h"

class SceneRipple:public Scene{
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
    
    vector<RippleBall*>balls;
	ofSoundPlayer snd0;
    
	float buttonAlpha;
    
    int deathCount;
    
    void colorTotem(int index,float alpha);
    float welltempered[128];
    int ticks;
    static SceneRipple *instance;

};

#endif
