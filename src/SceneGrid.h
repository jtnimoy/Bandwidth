//
//  SceneGrid.h
//  BANDWIDTH
//
//  Created by Josh Nimoy on 10/20/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#ifndef BANDWIDTH_SceneGrid_h
#define BANDWIDTH_SceneGrid_h

#include "Scene.h"
#include <vector>
#include "ofxOsc.h"
#include "GridBall.h"

using namespace std;

class SceneGrid:public Scene{
public:

     void setup();
     void update();
     void draw(float sceneAlpha);
     void keyPressed(int key);
     void mouseMoved(int x,int y,int button);
     void mouseDragged(int x,int y,int button);
     void mousePressed(int x,int y,int button);
     void mouseReleased(int x,int y,int button);

    
    vector<GridBall*>balls;
	static SceneGrid*instance;
	ofSoundPlayer snd_preloaders[1];
    
	vector<ofxOscSender*> oscOut;
    
    void sendOscMessage(ofxOscMessage m);
    void reset();
};

#endif
