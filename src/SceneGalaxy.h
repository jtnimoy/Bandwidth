//
//  SceneGalaxy.h
//  BANDWIDTH
//
//  Created by Josh Nimoy on 10/20/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#ifndef BANDWIDTH_SceneGalaxy_h
#define BANDWIDTH_SceneGalaxy_h

#include "ofxOsc.h"
#include "Star.h"
#include "Scene.h"
#include <vector>

using namespace std;


class SceneGalaxy:public Scene{
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
    
    ofSoundPlayer snd[4];
    
	//vector<ofxOscSender*> oscOut;
    
    //void sendOscMessage(ofxOscMessage m);
	
	ofImage loresScreen;
	unsigned char*pixels;
	ofVec2f screen2lores(ofVec2f in);
	vector<Star*> stars;
	void blankLoresScreen();
	bool mouseIsDown;
    static SceneGalaxy*instance;
    ofxOscReceiver oscIn; 

    
};

#endif
