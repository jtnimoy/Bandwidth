
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//

#include "testApp.h"
#include "MColor.h"
#include <fstream.h>
#include <iostream.h>
using namespace std;


testApp *testApp::instance;//singleton
//--------------------------------------------------------------
void testApp::setup(){
	instance = this;
    
    
    
    
    
#if defined (TARGET_OSX)
    ifstream yamlInfile("../Resources/settings.yml");
    ofDisableDataPath();
#else
    ifstream yamlInfile("data/settings.yml");
#endif

    YAML::Parser yamlParser(yamlInfile);    
    yamlParser.GetNextDocument(yamlDoc);

    yamlDoc["osc port"] >> osc_port;
    cout << "osc port discovered: " << osc_port << endl;
     
    yamlDoc["help text"] >> helpText;
    
	oscIn.setup(osc_port);
    const GLubyte * version = glGetString(GL_VERSION);
	int major, minor;
	sscanf((const char*)version, "%i.%i",&major, &minor);
    if(major > 1 || (major==1 && minor>=3)){
		ofEnableAlphaBlending();
	}
	
	ofEnableSmoothing();
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	ofSetFrameRate(60);
	ofHideCursor();
    
    for(int i=0;i<6;i++){
        buttonAlpha[i] = 0;
        sceneAlphas[i] = 0.0f;
    }
    
    yamlDoc["default scene"] >> buttonActive;
    yamlDoc["hide help"] >> hideHelp;
    yamlDoc["scene fade speed"] >> sceneFadeSpeed;
    yamlDoc["show scene switcher"] >> showSceneSwitcher;

    yamlDoc["window fullscreen"] >> doFullScreen;

    int windowW,windowH;
    yamlDoc["window shape"]["width"] >> windowW;
    yamlDoc["window shape"]["height"] >> windowH;
    ofSetWindowShape(windowW, windowH);
    
    int windowX,windowY;
    yamlDoc["window shape"]["left"] >> windowX;
    yamlDoc["window shape"]["top"] >> windowY;
    ofSetWindowPosition(windowX,windowY);
    

    if(doFullScreen){
        ofToggleFullscreen();   
    }
    
    if(hideHelp){
        helpAlpha = 0.0f;
    }else{
        helpAlpha = 255.0f;
    }
    
    yamlDoc["scene dimmed alpha"] >> dimmedAlpha;
 
    
    scenes[0] = new SceneVines();
    scenes[1] = new SceneGrid();
    scenes[2] = new SceneGalaxy();
    scenes[3] = new SceneRipple();
    scenes[4] = new SceneLines();
    scenes[5] = new SceneBumpers();
 

    dataPath = "";
#if defined (TARGET_OSX)
    dataPath = "../Resources/";
#endif
    
    
    font.loadFont(dataPath+"raleway_thin.otf",18);

    
    for(int i=0;i<6;i++){
        switch(i){
            case 0:
                buttonImages[i].loadImage(dataPath+"icon_vines.png");
                break;
            case 1:
                buttonImages[i].loadImage(dataPath+"icon_grid.png");
                break;
                
            case 2:
                buttonImages[i].loadImage(dataPath+"icon_galaxy.png");
                break;
                
            case 3:
                buttonImages[i].loadImage(dataPath+"icon_ripple.png");
                break;
                
            case 4:
                buttonImages[i].loadImage(dataPath+"icon_lines.png");
                break;
                
            default:
                buttonImages[i].loadImage(dataPath+"icon_bumpers.png");
                break;

        }
        scenes[i]->setup();
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    for(int i=0;i<6;i++){
        scenes[i]->update();
    }


    for(int i=0;i<6;i++){
        buttonAlpha[i] = fmax(buttonAlpha[i]-8,0);
    }
    
    if(hideHelp){
        helpAlpha = fmax(0.0, helpAlpha - 2.0f);
        
    }
    
    for(int i=0;i<6;i++){
        
        if(buttonActive==i){
            sceneAlphas[i] += (1.0 - sceneAlphas[i]) * sceneFadeSpeed;
        }else{
            sceneAlphas[i] += (dimmedAlpha - sceneAlphas[i]) * sceneFadeSpeed;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0,0);
    
    for(int i=0;i<6;i++){
        scenes[i]->draw(sceneAlphas[i]);
    }
    
    
    //buttons
    
    if(showSceneSwitcher){
        
        ofNoFill();
        for(int i=0;i<6;i++){
            if(buttonActive==i){
                ofSetColor(255,255,255);
            }else{
                ofSetColor(90,90,90);
            }
            ofCircle(BUTTONRAD + i*(BUTTONRAD*2 + BUTTONMARGIN),ofGetHeight()-BUTTONRAD,BUTTONRAD);
        }
        ofFill();
                
        for(int i=0;i<6;i++){
            if(buttonActive==i){
                ofSetColor(255,255,255,buttonAlpha[i]);
            }else{
                ofSetColor(90,90,90,buttonAlpha[i]);
            }
            ofCircle(BUTTONRAD + i*(BUTTONRAD*2 + BUTTONMARGIN),ofGetHeight()-BUTTONRAD,BUTTONRAD);

            
            if(buttonActive==i){
                ofSetColor(255,255,255,255);
            }else{
                ofSetColor(90,90,90,255);
            }
            buttonImages[i].draw(i*(BUTTONRAD*2 + BUTTONMARGIN),ofGetHeight()-BUTTONRAD*2);

        }
    }
    
    //dark overlay
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0,0,0,helpAlpha);
    ofSetRectMode(OF_RECTMODE_CORNER);
	ofRect(0,0,ofGetScreenWidth(),ofGetScreenHeight());
    
    //text
    ofSetColor(128,255,255,helpAlpha);
    font.drawString(helpText,100,100);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='f'){
		ofToggleFullscreen();
	}
	
	if(key=='m'){
        ofShowCursor();
	}
    
    if(key=='1'){
        
        buttonAlpha[0] = 255;
        if(buttonActive == 0){
            scenes[0]->reset();
        }else{
            buttonActive = 0;
        }
    }

    if(key=='2'){
        
        buttonAlpha[1] = 255;
        if(buttonActive == 1){
            scenes[1]->reset();
        }else{
            buttonActive = 1;
        }
    }

    if(key=='3'){
        
        buttonAlpha[2] = 255;
        if(buttonActive == 2){
            scenes[2]->reset();
        }else{
            buttonActive = 2;
        }
    }

    if(key=='4'){
        
        buttonAlpha[3] = 255;
        if(buttonActive == 3){
            scenes[3]->reset();
        }else{
            buttonActive = 3;
        }
    }

    if(key=='5'){
        
        buttonAlpha[4] = 255;
        if(buttonActive == 4){
            scenes[4]->reset();
        }else{
            buttonActive = 4;
        }
    }

    if(key=='6'){
        
        buttonAlpha[5] = 255;
        if(buttonActive == 5){
            scenes[5]->reset();
        }else{
            buttonActive = 5;
        }
    }

    
    scenes[buttonActive]->keyPressed(key);
    
    hideHelp = true;
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    ofShowCursor();

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    scenes[buttonActive]->mouseDragged(x,y,button);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    int mx = mouseX;
    int my = mouseY;
    
    if(      ofDist(BUTTONRAD,
		    ofGetHeight()-BUTTONRAD,mx,my) < BUTTONRAD && showSceneSwitcher){
		buttonAlpha[0] = 255;
        if(buttonActive == 0){
            scenes[0]->reset();
        }else{
            buttonActive = 0;
        }
    }else if(ofDist(BUTTONRAD +    (BUTTONRAD*2+BUTTONMARGIN),
		    ofGetHeight()-BUTTONRAD,mx,my) < BUTTONRAD && showSceneSwitcher){
		buttonAlpha[1] = 255;
        if(buttonActive == 1){
            scenes[1]->reset();   
        }else{
            buttonActive = 1;
        }
    }else if(ofDist(BUTTONRAD + 2 *(BUTTONRAD*2+BUTTONMARGIN),
		    ofGetHeight()-BUTTONRAD,mx,my) < BUTTONRAD && showSceneSwitcher){
		buttonAlpha[2] = 255;
        if(buttonActive == 2){
            scenes[2]->reset();   
        }else{
            buttonActive = 2;
        }
    }else if(ofDist(BUTTONRAD + 3 *(BUTTONRAD*2+BUTTONMARGIN),
		    ofGetHeight()-BUTTONRAD,mx,my) < BUTTONRAD && showSceneSwitcher){
		buttonAlpha[3] = 255;
        if(buttonActive == 3){
            scenes[3]->reset();   
        }else{
            buttonActive = 3;
        }
    }else if(ofDist(BUTTONRAD + 4 *(BUTTONRAD*2+BUTTONMARGIN),
		    ofGetHeight()-BUTTONRAD,mx,my) < BUTTONRAD && showSceneSwitcher){
		buttonAlpha[4] = 255;
        if(buttonActive == 4){
            scenes[4]->reset();   
        }else{
            buttonActive = 4;
        }
    }else if(ofDist(BUTTONRAD + 5 *(BUTTONRAD*2+BUTTONMARGIN),
		    ofGetHeight()-BUTTONRAD,mx,my) < BUTTONRAD && showSceneSwitcher){
		buttonAlpha[5] = 255;
        if(buttonActive == 5){
            scenes[5]->reset();   
        }else{
            buttonActive = 5;
        }
    }else{
            scenes[buttonActive]->mousePressed(x,y,button);
    }
    
    hideHelp = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    scenes[buttonActive]->mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
//--------------------------------------------------------------
