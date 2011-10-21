/*
 *  contactListener.h
 *  emptyExample
 *
 *  Created by Josh Nimoy on 9/8/11.
 *  Copyright 2011 Josh Nimoy. All rights reserved.
 *
 */

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "ofMain.h"
#include "Box2D/Box2D.h"
#include <map>

using namespace std;

class ContactListener : public b2ContactListener{
public:
	ContactListener();
	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	map<b2Contact*,bool>contacts;
	void playSound(b2Contact *contact);
};

#endif

