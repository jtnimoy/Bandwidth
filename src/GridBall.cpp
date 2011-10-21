/*
 *  GridBall.cpp
 *  emptyExample
 *

 // This work is licensed under the Creative Commons
 // Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
 // copy of this license, visit
 // http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
 // Creative Commons, 444 Castro Street, Suite 900, Mountain View,
 // California, 94041, USA.
 //
 *
 */

#include "GridBall.h"
#include "testApp.h"

float GridBall::speed = BLOCKSIZE;
int GridBall::delay = 24;

GridBall::GridBall(){
	x=0;
	y=0;
	dead = false;
	side = testSide();
	timer=1000;
	snd0.loadSound(testApp::instance->dataPath+"grid.wav");
	snd0.setMultiPlay(true);
	alphaTimer = 0;
}

void GridBall::beat(){
	x+=speed;
	if(x>ofGetWidth()){
		x=0;
		y+=speed;
		if(y>ofGetHeight())dead=true;
		side = testSide();
	}

	if(testSide() != side){
		timer = 0;
	}

}

void GridBall::step(){

	side = testSide();

	float sp = y*0.003+0.5;
	snd0.setSpeed(sp);
	if(timer==delay*0){
		snd0.setVolume(0.80);
		snd0.play();
		alphaTimer=0;

		ofxOscMessage m;
		m.setAddress( "/net/jtnimoy/bandwidth/tempo" );
		m.addIntArg(ofGetFrameNum());
		m.addFloatArg(sp);
		SceneGrid::instance->sendOscMessage(m);

	}else if(timer==delay*1){
		snd0.setVolume(0.60);
		snd0.play();
		alphaTimer=0;
	}else if(timer==delay*2){
		snd0.setVolume(0.40);
		snd0.play();
		alphaTimer=0;
	}else if(timer==delay*3){
		snd0.setVolume(0.20);
		snd0.play();
		alphaTimer=0;
	}else if(timer==delay*4){
		snd0.setVolume(0.10);
		snd0.play();
		alphaTimer=0;
	}

	alphaTimer++;
	timer++;
}

bool GridBall::testSide(){
	return (x < ofGetWidth()/2.0);
}
