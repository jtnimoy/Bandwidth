//
//  SceneGalaxy.h
//  BANDWIDTH
//

// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//
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
