/*
 *  VinesContactListener.h
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/8/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
 *
 */

#ifndef VINESCONTACTLISTENER_H
#define VINESCONTACTLISTENER_H

#include "ofMain.h"
#include "Box2D/Box2D.h"
#include <map>

using namespace std;

class VinesContactListener : public b2ContactListener{
public:
	VinesContactListener();
	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	map<b2Contact*,bool>contacts;
	void playSound(b2Contact *contact);
};

#endif

