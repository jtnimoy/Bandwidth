/*
 *  Vine.cpp
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

#include "Vine.h"
#include "testApp.h"
#include "SceneVines.h"

void Vine::hit(){
	hitCounter = 0;
}

Vine::Vine(float x,float len,MColor color_,float radius_){

	color = color_;
	radius = radius_;

	//ball
	b2BodyDef *bodyDef1 = new b2BodyDef();
	bodyDef1->position.Set(x,ofGetHeight()/2);
	bodyDef1->type = b2_dynamicBody;
	bodyDef1->allowSleep = true;
	ball = SceneVines::instance->world->CreateBody(bodyDef1);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(radius,radius);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = radius;

	// Override the default friction.
	fixtureDef.friction = 100.0f;

	fixtureDef.restitution = 0.5f;

	// Add the shape to the body.
	ball->CreateFixture(&fixtureDef);



	//pivot
	b2BodyDef *bodyDef3 = new b2BodyDef();
	bodyDef3->position.Set(x,0);
	bodyDef3->type = b2_staticBody;
	bodyDef3->allowSleep = true;
	pivot = SceneVines::instance->world->CreateBody(bodyDef3);




	b2RopeJointDef *jointDef = new b2RopeJointDef();
	//jointDef->frequencyHz = 4.0f;
	//jointDef->dampingRatio = 0.1f;
	//jointDef->length = ofGetHeight() * 0.75;
	jointDef->bodyA = ball;
	jointDef->bodyB = pivot;
	jointDef->localAnchorA = b2Vec2(0,0);
	jointDef->localAnchorB = b2Vec2(0,0);
	jointDef->maxLength = len;
	joint = (b2RopeJoint*)SceneVines::instance->world->CreateJoint(jointDef);


	hitCounter = 0;
}

MColor Vine::getColor(){
	MColor c = this->color;
	float v = fmax(5 - hitCounter * 0.5,0);
	c.mixSelfTo(MColor(255,255,255), v * 0.2);
	return c;
}

void Vine::step(){
	hitCounter++;
}

