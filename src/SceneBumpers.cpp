//
//  SceneBumpers.cpp
//  BANDWIDTH
//

// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//
//

#include "SceneBumpers.h"
#include "BumperBodyData.h"
#include "ofxOscReceiver.h"
#include "testApp.h"
#include "ofMain.h"
#include "MColor.h"

SceneBumpers *SceneBumpers::instance = NULL;
//---------------------------------------------------

void SceneBumpers::setup(){
    instance = this;
    world = new b2World(b2Vec2(0,10),true);
	float W = ofGetScreenWidth();
	float H = ofGetScreenHeight();

    
	snd0.loadSound(testApp::instance->dataPath+"bumpers.wav");
	snd0.setVolume(0.75);
	snd0.setMultiPlay(true);
    
    
    
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);
    
	
    
    float counter = 1;
    int index = 0;
    int halfNotes = 0;
    while(index < 128){
        int octaveKey = (halfNotes % 12);
        if(
           octaveKey==0
           || octaveKey==2
           || octaveKey==4
           || octaveKey==7
           || octaveKey==9
           ){
            welltempered[index] = counter;
            index++;
        }
        counter *= powf(2,1/12.0);
        halfNotes++;
    }
    
    draggingObstacle = NULL;
    newBall = false;
    dropRate = 24;

}

//---------------------------------------------------

void SceneBumpers::update(){
    for(int i=0;i<60;i++){
		world->Step(1/120.0,4,2);
	}
    
	
    if(ofGetFrameNum() % dropRate == 0 || newBall){
        
        float radius = 20;
        
        b2BodyDef *bodyDef1 = new b2BodyDef();
        bodyDef1->position.Set(ofGetScreenWidth()/2,0);
        bodyDef1->type = b2_dynamicBody;
        bodyDef1->allowSleep = true;
        balls.push_back(world->CreateBody(bodyDef1));
        
        // Define another box shape for our dynamic body.
        b2PolygonShape shape;
        
        /*
         #define CIRCLE_SEGS 4
         b2Vec2 verts[CIRCLE_SEGS];
         int steps = CIRCLE_SEGS;
         #undef CIRCLE_SEGS
         float inc = TWO_PI / steps;
         for(int i=0;i<steps;i++){
         verts[i].x = radius * cos(inc*i);
         verts[i].y = radius * sin(inc*i);
         }
         dynamicCircle.Set(verts, steps);
         */
        
        shape.SetAsBox(radius, radius, b2Vec2(0,0), 45);
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        
        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = radius;
        
        // Override the default friction.
        fixtureDef.friction = 100.0f;
        
        fixtureDef.restitution = 1.0f;
        
        // Add the shape to the body.
        balls.back()->CreateFixture(&fixtureDef);
        BumperBodyData *b = new BumperBodyData(BumperBodyData::TYPE_BALL);
        balls.back()->SetUserData((void*)b);
        
    }
    newBall = false;
    
    buttonAlpha = fmax(buttonAlpha-8,0);
    
    vector<b2Body*>::iterator it;
    for(it=balls.begin();it!=balls.end();it++){
        b2Vec2 pos = (*it)->GetPosition();
        if(pos.x < 0 || pos.x > ofGetScreenWidth() || pos.y > ofGetScreenHeight()){
            removeBall(*it);
        }
    }
    
    while(testApp::instance->oscIn.hasWaitingMessages()){
		ofxOscMessage m;
        testApp::instance->oscIn.getNextMessage(&m);
		int frame = m.getArgAsInt32(0);
		float speed = m.getArgAsFloat(1);
        
        if(ofRandomuf()>0.5){
            //newBall = true;
            createObstacle(ofGetScreenWidth() * ofRandomuf() , ofGetScreenHeight() * ofRandomuf());
        }
        
	}
    
}

//---------------------------------------------------

void SceneBumpers::draw(float sceneAlpha){
    ofSetColor(0,0,0,255-ofGetFrameNum());
	ofRect(0,0,ofGetWidth(),ofGetHeight());
    
    
    vector<b2Body*>::iterator it;
    for(it=balls.begin();it!=balls.end();it++){
        
        b2Vec2 pos = (*it)->GetPosition();
        BumperBodyData *ballData = (BumperBodyData*)(*it)->GetUserData();
        MColor c(ballData->birthFrame * 0.01, 1.0,1.0,"HSB");
        ofSetColor(c.red()*255.0,c.green()*255.0,c.blue()*255.0,sceneAlpha*255);
        ofFill();
        ofCircle(pos.x,pos.y,20);
        ofNoFill();
        ofCircle(pos.x,pos.y,20);
    }
    
    
    for(it=obstacles.begin();it!=obstacles.end();it++){
        b2Vec2 pos = (*it)->GetPosition();
        BumperBodyData *b = (BumperBodyData*)(*it)->GetUserData();
        MColor c(b->hitCount * 0.1 , 1.0,0.5,"HSB");
        ofSetColor(c.red()*255.0,c.green()*255.0,c.blue()*255.0,255 * sceneAlpha);
        ofNoFill();
        float alpha = fmax(0,1.0-((ofGetFrameNum() - b->lastHitFrame) / 10.0));
        
        ofCircle(pos.x,pos.y,30 + alpha*20);
        
        ofSetColor(255,255,255,alpha * 255.0 * sceneAlpha);
        ofFill();
        ofCircle(pos.x,pos.y,30 + alpha*20 * sceneAlpha);
    }

}

//---------------------------------------------------

void SceneBumpers::keyPressed(int key){
    if(key==OF_KEY_UP){
        dropRate++;
        cout << "droprate changed " << dropRate << endl;
    }
    
    if(key==OF_KEY_DOWN){
        dropRate--;
        cout << "droprate changed " << dropRate << endl;
    }
    
    

}

//---------------------------------------------------

void SceneBumpers::mouseMoved(int x,int y){
    
}

//---------------------------------------------------

void SceneBumpers::mouseDragged(int x,int y,int button){
    draggingObstacle->SetTransform(b2Vec2(x,y),0);
}

//---------------------------------------------------

void SceneBumpers::mousePressed(int x,int y,int button){
    vector<b2Body*>::iterator it;
    bool foundOne = false;
    for(it=obstacles.begin();it!=obstacles.end();it++){
        b2Vec2 pos = (*it)->GetPosition();
        float dist = ofDist(pos.x,pos.y,testApp::instance->mouseX,testApp::instance->mouseY);
        if(dist < 30){
            foundOne = true;
            draggingObstacle = (*it);
            break;
        }
    }
    
    if(!foundOne){
        createObstacle(x,y);
        draggingObstacle = obstacles.back();
    }

}

//---------------------------------------------------

void SceneBumpers::mouseReleased(int x,int y,int button){
       draggingObstacle = NULL;
}

//---------------------------------------------------

void SceneBumpers::reset(){
    
    for(int i=0;i<balls.size();i++){
        delete (BumperBodyData*)balls[i]->GetUserData();
        world->DestroyBody(balls[i]);
    }
    balls.clear();
    
    for(int i=0;i<obstacles.size();i++){
        delete (BumperBodyData*)obstacles[i]->GetUserData();
        world->DestroyBody(obstacles[i]);
    }
    obstacles.clear();
    
    
    ofSoundStopAll();
}

//-----------------------------------------------------


void SceneBumpers::createObstacle(int x,int y){
    float radius = 30;
    
    b2BodyDef *bodyDef1 = new b2BodyDef();
    bodyDef1->position.Set(x,y);
    bodyDef1->type = b2_staticBody;
    bodyDef1->allowSleep = true;
    obstacles.push_back(world->CreateBody(bodyDef1));
    
    // Define another box shape for our dynamic body.
    b2PolygonShape shape;
    /*
     #define CIRCLE_SEGS 4
     b2Vec2 verts[CIRCLE_SEGS];
     int steps = CIRCLE_SEGS;
     #undef CIRCLE_SEGS
     float inc = TWO_PI / steps;
     for(int i=0;i<steps;i++){
     verts[i].x = radius * cos(inc*i);
     verts[i].y = radius * sin(inc*i);
     }
     dynamicCircle.Set(verts, steps);
     */
    shape.SetAsBox(radius, radius, b2Vec2(0,0), 45);
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = radius;
    
    // Override the default friction.
    fixtureDef.friction = 100.0f;
    
    fixtureDef.restitution = 0.5f;
    
    // Add the shape to the body.
    obstacles.back()->CreateFixture(&fixtureDef);
    BumperBodyData *b = new BumperBodyData(BumperBodyData::TYPE_OBSTACLE);
    obstacles.back()->SetUserData((void*)b);
}

//------------------------------------------------------


void SceneBumpers::removeBall(b2Body*b){
    //  testApp::instance->removeBall(b1);
    vector<b2Body*>::iterator it;
    for(it=balls.begin();it!=balls.end();it++){
        if((*it)==b){
            delete (BumperBodyData*)(*it)->GetUserData();
            world->DestroyBody(*it);
            balls.erase(it);
            break;
        }
    }
}

