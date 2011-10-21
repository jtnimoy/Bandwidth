/*
 *  VinesContactListener.cpp
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

#include "VinesContactListener.h"
#include "testApp.h"
#include "SceneVines.h"

VinesContactListener::VinesContactListener():b2ContactListener(){
}

void VinesContactListener::BeginContact(b2Contact *contact){
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


void VinesContactListener::EndContact(b2Contact *contact){
	contacts[contact] = false;
}

void VinesContactListener::playSound(b2Contact *contact){

	//grace period
	if(ofGetFrameNum() < 100){
		return;
	}

	b2Fixture *f0 = contact->GetFixtureA();
	b2Fixture *f1 = contact->GetFixtureB();

	b2Body *b0 = f0->GetBody();
	b2Body *b1 = f1->GetBody();

	b2Vec2 vel0 = b0->GetLinearVelocity();
	b2Vec2 vel1 = b1->GetLinearVelocity();

	float d = ofDist(vel0.x,vel0.y,vel1.x,vel1.y);
	float thresh = 5;

	if(d > thresh){
		//average the densities
		float radius = 4.5 - powf((f0->GetDensity() + f1->GetDensity()) * 0.01,6.0) * 10.0;
		SceneVines::instance->snd0.setSpeed(radius);
		SceneVines::instance->snd0.play();

		Vine*v0 = SceneVines::instance->findVineByBody(b0);
		Vine*v1 = SceneVines::instance->findVineByBody(b1);

		if(v0!=NULL){
			v0->hit();
		}
		if(v1!=NULL){
			v1->hit();
		}

	}
}
