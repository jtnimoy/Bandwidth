/*
 *  contactListener.cpp
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/8/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
 *
 */

#include "ContactListener.h"
#include "SceneBumpers.h"
#include "BumperBodyData.h"
#include "ofMain.h"

ContactListener::ContactListener():b2ContactListener(){
}

void ContactListener::BeginContact(b2Contact *contact){
	if(contacts.find(contact)!=contacts.end()){
		if(!contacts[contact]){
			contacts[contact]=true;
			playSound(contact);
		}
	}else{
		contacts[contact]=true;
		playSound(contact);
	}
}


void ContactListener::EndContact(b2Contact *contact){
	contacts[contact] = false;
}

void ContactListener::playSound(b2Contact *contact){

	//grace period
	//if(ofGetFrameNum() < 100){
	//	return;
	//}

	b2Fixture *f0 = contact->GetFixtureA();
	b2Fixture *f1 = contact->GetFixtureB();

	b2Body *b0 = f0->GetBody();
	b2Body *b1 = f1->GetBody();

    BumperBodyData* u0 = (BumperBodyData*)b0->GetUserData();
    BumperBodyData* u1 = (BumperBodyData*)b1->GetUserData();
    
	b2Vec2 vel0 = b0->GetLinearVelocity();
	b2Vec2 vel1 = b1->GetLinearVelocity();

	float d = ofDist(vel0.x,vel0.y,vel1.x,vel1.y);
	float thresh = 5;

    //hit strength has to be high enough, and one of them must be an obstacle.
	if(d > thresh &&   ( (u0->type==BumperBodyData::TYPE_OBSTACLE && u1->type==BumperBodyData::TYPE_BALL)
                      || (u1->type==BumperBodyData::TYPE_OBSTACLE && u0->type==BumperBodyData::TYPE_BALL) )){
		//average the densities
        b2Vec2 pos;
        if(u0->type==BumperBodyData::TYPE_OBSTACLE){
            pos = b0->GetPosition();
        }else{
            pos = b1->GetPosition();
        }
		SceneBumpers::instance->snd0.setSpeed( SceneBumpers::instance->welltempered[(int)((pos.x / ofGetScreenWidth()) * 8)] );
		SceneBumpers::instance->snd0.play();
        
        if(u0->type==BumperBodyData::TYPE_OBSTACLE){
            u0->lastHitFrame = ofGetFrameNum();
            u0->hitCount++;
        }else{
            u1->lastHitFrame = ofGetFrameNum();
            u1->hitCount++;
        }
	}
    
    if(u0->type==BumperBodyData::TYPE_GROUND){
        SceneBumpers::instance->removeBall(b1);
    }
    
    if(u1->type==BumperBodyData::TYPE_GROUND){
        SceneBumpers::instance->removeBall(b0);
    }
    
}
