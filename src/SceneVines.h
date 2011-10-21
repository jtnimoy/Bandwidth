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