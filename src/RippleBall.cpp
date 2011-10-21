/*
 *  RippleBall.cpp
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/10/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
 *
 */

#include "RippleBall.h"
#include "testApp.h"
#include "SceneRipple.h"


RippleBall::RippleBall(int xx,int yy){
	x=xx;
	y=yy;
    ticks=0;
	death = -1;
    color = MColor( ofRandomuf() * TWO_PI, 1.0, 1.0, "HSB");
    radius = 0;
    lastIntersectionCount = -1;
    rotationSpeed = (ofRandomuf()-0.5) * 0.1f;
    fillAlpha = 0;
}

float RippleBall::getAlpha(){
    if(death == -1){
        return 1.0;
    }else{
        return 1.0 - ( ticks - death )/ RIPPLEBALL_DEATH_DURATION;
    }
}

bool RippleBall::intersectsNonConcentric(RippleBall *that){
    float dist = ofDist(that->x,that->y,this->x,this->y);
    
    return (
       dist < ( that->radius + this->radius )
            && dist + that->radius > this->radius
            && dist + this->radius > that->radius
       );
}

int RippleBall::countIntersections(){
    int counter = 0;
    map<RippleBall*,int>::iterator it;
    for( it = intersections.begin();it != intersections.end() ; it ++ ){
        if(it->second==RIPPLEBALL_INTERSECTS){
            counter++;
        }
    }
    return counter;
}

void RippleBall::step(){
    
    float radSq = powf(radius,2);
    float screenW = ofGetScreenWidth();
    float screenH = ofGetScreenHeight();
    
    if(death == -1){
        if( ofDistSquared(0,0,x,y) < radSq 
           && ofDistSquared(screenW,0,x,y) < radSq 
           && ofDistSquared(screenW,screenH,x,y) < radSq 
           && ofDistSquared(0,screenH,x,y) < radSq 
           ){
            death = ticks;
        }
    }else{
        snd0.setVolume(1.0 - ((ticks-death) / RIPPLEBALL_DEATH_DURATION) );
    }

    radius = powf(ticks,3) * 0.0001;
    
    
    int intersectionCount = countIntersections();
    if(lastIntersectionCount != -1 && lastIntersectionCount != intersectionCount){
        if(intersectionCount > 0){
            float note =  (1 - y / ofGetScreenHeight() ) * 1.0f;
            cout << note << endl;
            SceneRipple::instance->snd0.setVolume(0.2f);
            SceneRipple::instance->snd0.setSpeed(SceneRipple::instance->welltempered[(int)(note * 16)] * 0.2);
            SceneRipple::instance->snd0.play();
            fillAlpha = 1.0;
        }else{
            //snd0.stop();
        }
    }
    lastIntersectionCount = intersectionCount;
    
    fillAlpha = fmax(0,fillAlpha-0.05f);
    ticks++;

}

