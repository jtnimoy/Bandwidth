//
//  SceneLines.cpp
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

#include "SceneLines.h"
#include "testApp.h"

SceneLines *SceneLines::instance = NULL;

//---------------------------------------------------

void SceneLines::setup(){
    instance = this;
	
	const GLubyte * version = glGetString(GL_VERSION);
	int major, minor;
	sscanf((const char*)version, "%i.%i",&major, &minor);
    
	if(major > 1 || (major==1 && minor>=3)){
		ofEnableAlphaBlending();
	}
	
    
	//ofEnableSmoothing();
	//ofSetFrameRate(60);
	//ofHideCursor();
	//ofToggleFullscreen();
	snd0.loadSound(testApp::instance->dataPath+"lines.wav");
    snd0.setMultiPlay(true);
    
	buttonAlpha = 0;
    
    deathCount = 0;
    
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
    
    ticks = 0;
}

//---------------------------------------------------

void SceneLines::update(){
    
    std::vector<JTLine*>::iterator it;
    
    for(it=lines.begin();it!=lines.end();it++){
		(*it)->step();
	}
    
    //kill dead ones
	bool foundOne = true;
	while(foundOne){
		foundOne = false;
		for(it=lines.begin();it!=lines.end();it++){
			//advance through dead ones
			if(it != lines.end()){
                
				if((*it)->death != -1 ){
					delete (*it);
					it = lines.erase(it);
					foundOne = true;
                    deathCount++;
					if(it==lines.end()){
						break;
					}
				}
			}
		}
        
	}
    
    
    while(testApp::instance->oscIn.hasWaitingMessages()){
		ofxOscMessage m;
		testApp::instance->oscIn.getNextMessage(&m);
		int frame = m.getArgAsInt32(0);
		float speed = m.getArgAsFloat(1);
        
        if(ofRandomuf()>0.8){
            lines.push_back( new JTLine(ofRandomuf() * ofGetScreenWidth() , ofRandomuf() * ofGetScreenHeight() ) );
        }
        
        
	}
    
    
    
    ticks++;
}

//---------------------------------------------------

void SceneLines::draw(float alpha){
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    std::vector<JTLine*>::iterator it;
    for(it=lines.begin();it!=lines.end();it++){
        (*it)->draw(alpha);
    }
    
}

//---------------------------------------------------

void SceneLines::keyPressed(int key){
    
}

//---------------------------------------------------

void SceneLines::mouseMoved(int x,int y){
    
}

//---------------------------------------------------

void SceneLines::mouseDragged(int x,int y,int button){
    if(lines.size() > 0){
        JTLine *thisLine = lines.back();
        thisLine->dest_x2 = x;//(x - thisLine->x2) * 0.1;
        thisLine->dest_y2 = y;//(y - thisLine->y2) * 0.1;
    }

}

//---------------------------------------------------

void SceneLines::mousePressed(int x,int y,int button){
    JTLine*thisLine = new JTLine(x,y);
    lines.push_back(thisLine);

}

//---------------------------------------------------

void SceneLines::mouseReleased(int x,int y,int button){
    
}

//---------------------------------------------------

void SceneLines::reset(){
    buttonAlpha = 255;
    
    for(int i=0;i<lines.size();i++){
        delete lines[i];
    }
    lines.clear();

}



