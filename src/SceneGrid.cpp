//
//  SceneGrid.cpp
//  BANDWIDTH
//
//  Created by Josh Nimoy on 10/20/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//

#include "SceneGrid.h"
#include "ofxOsc.h"
#include "MColor.h"
#include "testApp.h"

SceneGrid *SceneGrid::instance = NULL;

void SceneGrid::sendOscMessage(ofxOscMessage m){
    for(int i=0;i<oscOut.size();i++){
        oscOut[i]->sendMessage( m );
    }
}


//--------------------------------------------------------------
void SceneGrid::setup(){
	instance = this;
	
    

	snd_preloaders[0].loadSound(testApp::instance->dataPath+"grid.wav");



    
    for(int i=0;i<testApp::instance->yamlDoc["target hosts"].size();i++){
        const YAML::Node &subnode = testApp::instance->yamlDoc["target hosts"][i];
        string host;
        subnode >> host;
        cout << "heartbeat target discovered: " << host << endl;
        ofxOscSender *osc1 = new ofxOscSender();
        osc1->setup(host,testApp::instance->osc_port);
        oscOut.push_back(osc1);
    }
    

    
}

//--------------------------------------------------------------
void SceneGrid::update(){
    
    
    
	vector<GridBall*>::iterator it;
	bool foundOne = true;
	while(foundOne){
		foundOne = false;
		for(it=balls.begin();it!=balls.end();it++){
			//advance through dead ones
			if(it != balls.end()){
				if((*it)->dead){
					delete (*it);
					it = balls.erase(it);
					foundOne = true;
					if(it==balls.end()){
						break;
					}
				}
			}
		}
	}
    
	bool beat = (ofGetFrameNum() % 16 == 0);
	for(it=balls.begin();it!=balls.end();it++){
        
		(*it)->step();
		if(beat){
			(*it)->beat();
		}
	}
    

}

//--------------------------------------------------------------
void SceneGrid::draw(float sceneAlpha){
	ofBackground(0,0,0);
	ofSetRectMode(OF_RECTMODE_CENTER);
	vector<GridBall*>::iterator it;
	for(it=balls.begin();it!=balls.end();it++){
		MColor c(PI - (*it)->y*0.005,1.0,1.0,"HSB");
		float alpha = (255 - min(255,(*it)->alphaTimer*10))+90;
		float rad = (BLOCKSIZE - min(BLOCKSIZE,(*it)->alphaTimer))+BLOCKSIZE;
		ofSetColor(c.red()*255,c.green()*255,c.blue()*255,alpha * sceneAlpha);
		ofPushMatrix();
		ofTranslate((*it)->x,(*it)->y,0);
		//ofRotateZ(ofGetFrameNum()*0.1);
		ofRect(0,0,rad,rad);
		ofPopMatrix();
	}
    
	ofSetColor(255,255,255,sceneAlpha*255);
	ofLine(ofGetWidth()/2+BLOCKSIZE/2,0,ofGetWidth()/2+BLOCKSIZE/2,ofGetHeight());
    
    
}

//--------------------------------------------------------------
void SceneGrid::keyPressed(int key){
	if(key==OF_KEY_UP){
		GridBall::delay--;
		cout << GridBall::delay << endl;
	}
    
	if(key==OF_KEY_DOWN){
		GridBall::delay++;
		cout << GridBall::delay << endl;
	}
    
    
}

//--------------------------------------------------------------

void SceneGrid::mouseMoved(int x, int y,int button ){
    ofShowCursor();
    
}
//--------------------------------------------------------------

void SceneGrid::mouseReleased(int x, int y,int button ){
    
}

//--------------------------------------------------------------
void SceneGrid::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void SceneGrid::mousePressed(int x, int y, int button){
    
		GridBall*b = new GridBall();
		b->x = x - (x % BLOCKSIZE);
		b->y = y - (y % BLOCKSIZE);
		balls.push_back(b);
}
//--------------------------------------------------------------
void SceneGrid::reset(){
    for(int i=0;i<SceneGrid::instance->balls.size();i++){
			delete SceneGrid::instance->balls[i];
		}
		SceneGrid::instance->balls.clear();
}


