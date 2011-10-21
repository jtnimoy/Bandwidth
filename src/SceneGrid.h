//
//  SceneGrid.h
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
