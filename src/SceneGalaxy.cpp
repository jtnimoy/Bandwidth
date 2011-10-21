//
//  SceneGalaxy.cpp
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

#include "SceneGalaxy.h"
#include "testApp.h"

SceneGalaxy *SceneGalaxy::instance = NULL;
//---------------------------------------------------

void SceneGalaxy::setup(){
    instance = this;
    for(int i=0;i<4;i++){
        char fname[64];
        sprintf(fname,"galaxy%i.mp3",i);
        snd[i].loadSound(testApp::instance->dataPath+fname);
        snd[i].setMultiPlay(true);
    }
    
	int lowW = ofGetScreenWidth() / RESOLUTION_RATIO;
	int lowH = ofGetScreenHeight() / RESOLUTION_RATIO;
	
    Star::screenLowWidth = lowW;
    Star::screenLowHeight = lowH;
    
	loresScreen.allocate(lowW, lowH + 1, OF_IMAGE_COLOR);
	pixels = loresScreen.getPixels();
    
	blankLoresScreen();
	
	//for(int i=0;i<100;i++){
	//	points.push_back(ofVec2f( (lowW / 100.0 ) * i , lowH / 2 ));
	//}
	mouseIsDown = false;

	

}

//---------------------------------------------------

void SceneGalaxy::update(){
    
    vector<Star*>::iterator it;
    
	bool foundOne = true;
	while(foundOne){
		foundOne = false;
		for(it=stars.begin();it!=stars.end();it++){
			//advance through dead ones
			if(it != stars.end()){
				if((*it)->strength<=0){
                    delete (*it);
					it = stars.erase(it);
					foundOne = true;
					if(it==stars.end()){
						break;
					}
				}
			}
		}
	}
    
	for(int i=0;i<stars.size();i++){
		stars[i]->step();
	}
	
	blankLoresScreen();
    
    
	ofVec2f loresMouse = screen2lores(ofVec2f(testApp::instance->mouseX,testApp::instance->mouseY));
	int loresW = ofGetScreenWidth() / RESOLUTION_RATIO;
	for(it=stars.begin();it!=stars.end();it++){
        
		for(int y=0; y < ofGetScreenHeight() / RESOLUTION_RATIO; y++ ){
			for(int x= 0; x < loresW; x++ ){
				int pxpos = (y*loresW+x)*3;
				
				float dist =  ofDist((*it)->pos.x, (*it)->pos.y, x, y) * RESOLUTION_RATIO;
				//float rad =  (cos((ofGetFrameNum())*0.01 + i*10)+1.0)*0.1 + 0.001;
				
				int v = fmax(0,1.0 - dist * (*it)->getRadius()) * 0xAA * (*it)->strength;
                
				pixels[ pxpos+0 ] = min(pixels[ pxpos+0 ]+(int)round(v * (*it)->color.red()   ) , 0xFF );
				pixels[ pxpos+1 ] = min(pixels[ pxpos+1 ]+(int)round(v * (*it)->color.green() ) , 0xFF );
				pixels[ pxpos+2 ] = min(pixels[ pxpos+2 ]+(int)round(v * (*it)->color.blue()  ) , 0xFF );
				
			}		
		}
	}
	
	loresScreen.update();
    
    
    while(oscIn.hasWaitingMessages()){
		ofxOscMessage m;
		oscIn.getNextMessage(&m);
		int frame = m.getArgAsInt32(0);
		float speed = m.getArgAsFloat(1);
        
        if(ofRandomuf()>0.8)stars.push_back(new Star(ofVec2f( (int)(ofRandomuf()*Star::screenLowWidth),(int)(ofRandomuf()*Star::screenLowHeight) )));
        
	}

}

//---------------------------------------------------

void SceneGalaxy::draw(float alpha){
    
	ofBackground(0,0,0);
    ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(255,255,255,alpha*255);
	ofPushMatrix();
	ofScale(RESOLUTION_RATIO,RESOLUTION_RATIO , 1);
	loresScreen.draw(0,0);
	ofPopMatrix();

}

//---------------------------------------------------

void SceneGalaxy::keyPressed(int key){
    
}

//---------------------------------------------------

void SceneGalaxy::mouseMoved(int x,int y){
    
}

//---------------------------------------------------

void SceneGalaxy::mouseDragged(int x,int y,int button){
    if(stars.size()>0){
		stars.back()->pos = screen2lores( ofVec2f(x,y) );
	}

}

//---------------------------------------------------

void SceneGalaxy::mousePressed(int x,int y,int button){
    stars.push_back(new Star(screen2lores(ofVec2f(x,y))) );
}

//---------------------------------------------------

void SceneGalaxy::mouseReleased(int x,int y,int button){
    
}

//---------------------------------------------------

void SceneGalaxy::reset(){
    for(int i=0;i<stars.size();i++){            
        delete stars[i];
    }
    stars.clear();
    ofSoundStopAll();

}


//--------------------------------------------------------------
ofVec2f SceneGalaxy::screen2lores(ofVec2f in){
	ofVec2f out;
	out.x = in.x / RESOLUTION_RATIO;
	out.y = in.y / RESOLUTION_RATIO;
	return out;
}

//--------------------------------------------------------------

void SceneGalaxy::blankLoresScreen(){
	int loresW = ofGetScreenWidth() / RESOLUTION_RATIO;
	for(int y=0; y < ofGetScreenHeight() / RESOLUTION_RATIO; y++ ){
		for(int x= 0; x < loresW; x++ ){
			int pos = (y*loresW+x)*3;
			pixels[pos+0] = 0;
			pixels[pos+1] = 0;
			pixels[pos+2] = 0;
		}
	}
    
}


