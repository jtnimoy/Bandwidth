
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//

#ifndef SCENE_VINES_H
#define SCENE_VINES_H


#include "Scene.h"
#include "Box2D/Box2D.h"
#include "Vine.h"
#include "VinesContactLIstener.h"
#include "ofxOsc.h"
#include <vector>
using namespace std;


class SceneVines:public Scene{
public:
    
    void setup();
    void update();
    void draw(float sceneAlpha);
    void keyPressed(int key);
    void mouseMoved(int x,int y);
    void mousePressed(int x,int y,int button);
    void mouseReleased(int x,int y,int button);
    void reset();
    b2World *world;
	vector<Vine*>vines;
	Vine *draggingVine;
	b2MouseJoint *draggingMouseJoint;
	b2Body *groundBody;
	
	ofSoundPlayer  snd0;
	VinesContactListener *contactListener;
	Vine*findVineByBody(b2Body*ball);
	
	ofxOscReceiver oscIn; 
    static SceneVines *instance;
    void generateVines();
};

#endif
