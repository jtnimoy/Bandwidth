//
//  SceneRipple.h
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
