/*
 *  VinesContactListener.h
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

