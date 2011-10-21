
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//

#include "SceneVines.h"
#include "testApp.h"


SceneVines *SceneVines::instance = NULL;

//---------------------------------------------------

void SceneVines::setup(){
    instance = this;
	world = new b2World(b2Vec2(0,10),true);
    
    
	float W = ofGetScreenWidth();
	float H = ofGetScreenHeight();
    
    generateVines();
    
	//ground
	b2BodyDef *bodyDef2 = new b2BodyDef();
	bodyDef2->position.Set(ofGetWidth()/2,ofGetHeight());
	bodyDef2->angle = 0.01;
	groundBody = world->CreateBody(bodyDef2);
    
	// Define the ground box shape.
	b2PolygonShape groundBox;
    
	// The extents are the half-widths of the box.
	groundBox.SetAsBox(ofGetWidth(), 10.0f);
    
	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
    
	ofSetFrameRate(60);
	ofEnableSmoothing();
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    
	
	const GLubyte * version = glGetString(GL_VERSION);
	int major, minor;
	sscanf((const char*)version, "%i.%i",&major, &minor);
	
	if(major > 1 || (major==1 && minor>=3)){
		ofEnableAlphaBlending();
	}
	
	
    
	draggingVine = NULL;
	snd0.loadSound(testApp::instance->dataPath+"vines.wav");
	snd0.setVolume(0.75);
	snd0.setMultiPlay(true);
    
    
	contactListener = new VinesContactListener();
	world->SetContactListener(contactListener);
	
}

//---------------------------------------------------

void SceneVines::update(){
    for(int i=0;i<60;i++){
		world->Step(1/120.0,4,2);
	}
    
	if(draggingVine!=NULL){
		draggingMouseJoint->SetTarget(b2Vec2(testApp::instance->mouseX,testApp::instance->mouseY));
	}
    
	vector<Vine*>::iterator it = vines.begin();
	for(;it!=vines.end();it++){
		(*it)->step();
	}
    
	while(oscIn.hasWaitingMessages()){
		ofxOscMessage m;
		oscIn.getNextMessage(&m);
		int frame = m.getArgAsInt32(0);
		float speed = m.getArgAsFloat(1);
        
        
		vines[(int)(ofRandomuf()*(vines.size()-1))]->ball->ApplyForceToCenter(b2Vec2(0,speed * -1000000000.0));
	}

}

//---------------------------------------------------

void SceneVines::draw(float sceneAlpha){
    for(int i=0;i<vines.size();i++){
		Vine *v = vines[i];
		b2Vec2 pos1 = v->ball->GetPosition();
		b2Vec2 pos2 = v->pivot->GetPosition();
		MColor clr = v->getColor();
		ofSetColor(clr.red()*255.0,clr.green()*255.0,clr.blue()*255.0, (128 + max(0,128 - v->hitCounter)) * sceneAlpha);
        
		float rad = ofDist(pos1.x,pos1.y,pos2.x,pos2.y);
		float theta = atan2(pos1.y-pos2.y,pos1.x-pos2.x);
		rad-=v->radius;
		float nx = pos2.x + rad * cos(theta);
		float ny = pos2.y + rad * sin(theta);
		ofLine(nx,ny,pos2.x,pos2.y);
		ofCircle(pos1.x,pos1.y,v->radius);
	}
    
	if(draggingVine!=NULL){
		ofSetColor(255,255,255,128 * sceneAlpha);
		ofNoFill();
		ofCircle(testApp::instance->mouseX,testApp::instance->mouseY,draggingVine->radius);
		ofFill();
		b2Vec2 p = draggingVine->ball->GetPosition();
		float rad = ofDist(testApp::instance->mouseX,testApp::instance->mouseY,p.x,p.y);
		if(rad > draggingVine->radius){
			float theta = atan2(testApp::instance->mouseY - p.y,testApp::instance->mouseX - p.x);
			rad -=draggingVine->radius;
			float nx = p.x + rad * cos(theta);
			float ny = p.y + rad * sin(theta);
			ofLine(p.x,p.y,nx,ny);
		}
	}
    
}

//---------------------------------------------------

void SceneVines::keyPressed(int key){
    
    if(key=='g'){
		b2Vec2 g = world->GetGravity();
		if(g.y==-10){
			world->SetGravity(b2Vec2(0,10));
		}else{
			world->SetGravity(b2Vec2(0,-10));
			
		}
	}
	

}

//---------------------------------------------------

void SceneVines::mouseMoved(int x,int y){
    
}

//---------------------------------------------------

void SceneVines::mousePressed(int x,int y,int button){
    if(draggingVine==NULL){
		for(int i=0;i<vines.size();i++){
			b2Vec2 p = vines[i]->ball->GetPosition();
			float radius = ofDist(p.x,p.y,x,y);
			if(radius < vines[i]->radius){
				b2MouseJointDef *mouseJointDef = new b2MouseJointDef();
				mouseJointDef->bodyA = groundBody;
				mouseJointDef->bodyB = vines[i]->ball;
				mouseJointDef->dampingRatio = 1.0f;
				mouseJointDef->frequencyHz = 1.0f;
				mouseJointDef->target = vines[i]->ball->GetPosition();
				mouseJointDef->maxForce = 100000000.0f;
				draggingMouseJoint = (b2MouseJoint*)world->CreateJoint(mouseJointDef);
				draggingVine = vines[i];
				break;
			}
		}
	}

}

//---------------------------------------------------

void SceneVines::mouseReleased(int x,int y,int button){
    if(draggingVine != NULL){
        
        //slingshot
		b2Vec2 p = draggingVine->ball->GetPosition();
		float rad = ofDist(testApp::instance->mouseX,testApp::instance->mouseY,p.x,p.y);
		if(rad > draggingVine->radius){
			float scaler = 2000000.0f * draggingVine->radius;
			draggingVine->ball->ApplyForceToCenter(b2Vec2((p.x - testApp::instance->mouseX)*scaler,(p.y - testApp::instance->mouseY)*scaler));
		}
        
		draggingVine = NULL;
        
		world->DestroyJoint(draggingMouseJoint);
        
	}

}

//--------------------------------------------------

Vine* SceneVines::findVineByBody(b2Body*ball){
	vector<Vine*>::iterator it = vines.begin();
	for(;it!=vines.end();it++){
		if(ball==(*it)->ball){
			return (*it);
		}
	}
	return NULL;
}

//--------------------------------------------------


void SceneVines::reset(){
    for(int i=0;i<vines.size();i++){
        world->DestroyBody(vines[i]->ball);
        delete vines[i];
    }
    vines.clear();
    generateVines();
}

//---------------------------------------------------


void SceneVines::generateVines(){
    
    int W = ofGetScreenWidth();
    int H = ofGetScreenHeight();
    
 	for(int i=0;i<50;i++){
		MColor c(i/10.0,1.0,1.0,"HSB");
		vines.push_back(new Vine((cos(i*0.2)*W/200.0) * 50.0 +W/2,H * 0.25 + i*10,c,30+i*0.3));
	}
   
}

