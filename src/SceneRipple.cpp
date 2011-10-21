//
//  SceneRipple.cpp
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

#include "SceneRipple.h"
#include "testApp.h"


SceneRipple *SceneRipple::instance = NULL;
//---------------------------------------------------

void SceneRipple::setup(){
    instance = this;
    snd0.loadSound(testApp::instance->dataPath+"ripple.wav");
    snd0.setMultiPlay(true);
    
    deathCount = 0;
    
    float counter = 1;
    int index = 0;
    int halfNotes = 0;
    while(index < 128){
        int octaveKey = (halfNotes % 12);
        if(//pentatonic scale
           octaveKey==1
           || octaveKey==3
           || octaveKey==5
           || octaveKey==8
           || octaveKey==10
           ){
            welltempered[index] = counter;
            index++;
        }
        counter *= powf(2,1/12.0);
        halfNotes++;
    }
    
    ticks = 0;

}

//---------------------------------------------------

void SceneRipple::update(){
    
    
	vector<RippleBall*>::iterator it;
    
    for(it=balls.begin();it!=balls.end();it++){
		(*it)->step();
	}
    
    
    //kill dead ones
	bool foundOne = true;
	while(foundOne){
		foundOne = false;
		for(it=balls.begin();it!=balls.end();it++){
			//advance through dead ones
			if(it != balls.end()){
                
				if((*it)->death != -1 && ((*it)->ticks - (*it)->death) > RIPPLEBALL_DEATH_DURATION ){
					delete (*it);
					it = balls.erase(it);
					foundOne = true;
                    deathCount++;
					if(it==balls.end()){
						break;
					}
				}
			}
		}
        
	}
    
    
    //find intersections
    for(it=balls.begin();it!=balls.end();it++){
        vector<RippleBall*>::iterator that;
        for( that=balls.begin(); that!=balls.end(); that++){
            
            if( (*that) != (*it) ){
                
                if( (*it)->intersectsNonConcentric(*that) ){
                    (*it)->intersections[*that] = RIPPLEBALL_INTERSECTS;
                }else{
                    (*it)->intersections[*that] = RIPPLEBALL_NOT_INTERSECTS;
                }
                
            }
            
        }
    }
    
    
    while(testApp::instance->oscIn.hasWaitingMessages()){
		ofxOscMessage m;
		testApp::instance->oscIn.getNextMessage(&m);
		int frame = m.getArgAsInt32(0);
		float speed = m.getArgAsFloat(1);
		cout << "OSC IN " << frame << ' ' << speed << endl;
        
        if(ofRandomuf()>0.5)balls.push_back( new RippleBall(ofRandomuf() * ofGetScreenWidth() , ofRandomuf() * ofGetScreenHeight() ) );
        
	}
    
    
    
    ticks++;

}

//---------------------------------------------------

void SceneRipple::draw(float sceneAlpha){
    vector<RippleBall*>::iterator it;
    
    
    for(int j=0;j<2;j++){
        if(j==0){
            //glBlendFunc(GL_ONE_MINUS_DST_COLOR,GL_ONE_MINUS_SRC_COLOR);
            ofFill();
        }else{
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            ofNoFill();
        }
        
        for(it=balls.begin();it!=balls.end();it++){
            //MColor c(PI - (*it)->y*0.005,1.0,1.0,"HSB");
            int intersectionCount = (*it)->countIntersections();
            
            float alpha = (*it)->getAlpha();
            
            if(j==0){
                
                ofSetColor( (*it)->color.red()  *255,
                           (*it)->color.green()*255,
                           (*it)->color.blue() *255 ,(alpha * (*it)->fillAlpha) * 90 * sceneAlpha );
            }else{
                
                colorTotem(intersectionCount,alpha * sceneAlpha);
                
            }
            
            if(j==1 || intersectionCount > 0){
                int steps =  ( 0.01f * (*it)->radius) + 3;
                float inc = (TWO_PI / steps);
                ofBeginShape();
                for(int i=0;i<steps+1;i++){
                    float x = (*it)->x + (*it)->radius * cos(inc*i + (*it)->rotationSpeed*ticks);
                    float y = (*it)->y + (*it)->radius * sin(inc*i + (*it)->rotationSpeed*ticks);
                    ofVertex(x,y);
                }
                ofEndShape();
            }
            
            if(j==1){
                float centroidRadius;
                if((*it)->death == -1){
                    centroidRadius = 1;
                }else{
                    centroidRadius = ((*it)->ticks - (*it)->death) * 0.1;
                }
                
                if(intersectionCount>0){
                    ofFill();
                }else{
                    ofNoFill();
                }
                ofCircle((*it)->x,(*it)->y,5+centroidRadius);
                ofNoFill();
                
            }
        }
        
    }
    
    ofNoFill();    
    if(balls.size()>1){
        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
        glBegin(GL_LINES);
        
        for(it=balls.begin();(it+1)!=balls.end();it++){
            
            int intersectionCount = (*it)->countIntersections();
            colorTotem(intersectionCount,(*it)->getAlpha() * 0.5 * sceneAlpha);
            glVertex2f((*it)->x,(*it)->y);
            
            intersectionCount = (*(it+1))->countIntersections();
            
            colorTotem(intersectionCount,(*(it+1))->getAlpha() * 0.1);
            glVertex2f((*(it+1))->x,(*(it+1))->y);
            
        }
        
        glEnd();
        glPopAttrib();
        
    }
    

}

//---------------------------------------------------

void SceneRipple::keyPressed(int key){
    
}

//---------------------------------------------------

void SceneRipple::mouseMoved(int x,int y){
    
}

//---------------------------------------------------

void SceneRipple::mouseDragged(int x,int y,int button){
    if(balls.size()>0){
        RippleBall *that = balls.back();
        that->x = x;
        that->y = y;
    }

}

//---------------------------------------------------

void SceneRipple::mousePressed(int x,int y,int button){
    RippleBall*b = new RippleBall(x,y);
    balls.push_back(b);

}

//---------------------------------------------------

void SceneRipple::mouseReleased(int x,int y,int button){
    
}

//---------------------------------------------------

void SceneRipple::reset(){
    buttonAlpha = 255;
    
    for(int i=0;i<balls.size();i++){
        delete balls[i];
    }
    balls.clear();

}
//---------------------------------------------------

void SceneRipple::colorTotem(int index,float alpha){
    
    //http://kuler.adobe.com/#themeID/1490158
    
    switch(index){
        case 0:
            ofSetColor(178,171,49,alpha * 255);
            break;
            
        case 1:
            ofSetColor(242,205,92,alpha * 255);
            break;
            
        case 2:
            ofSetColor(204,108,42,alpha * 255);
            break;
            
        case 3:
            ofSetColor(156,42,22,alpha * 255);
            break;
            
        default:
            ofSetColor(66,110,92,alpha * 255);
            break;                        
    } 
    
}


