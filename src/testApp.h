
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//


#pragma once

#include "ofMain.h"
#include "Scene.h"
#include "SceneVines.h"
#include "SceneGrid.h"
#include "SceneGalaxy.h"
#include "SceneRipple.h"
#include "SceneLines.h"
#include "SceneBumpers.h"
#include "yaml-cpp/yaml.h"

#define BLOCKSIZE 30
#define BUTTONRAD 32
#define BUTTONMARGIN 10
#define RESOLUTION_RATIO 32.0f


class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

    static testApp*instance;//singleton

    float buttonAlpha[6];
    int buttonActive;
    
    Scene *scenes[6];
    float sceneAlphas[6];
    bool hideHelp;
    float helpAlpha;
    ofTrueTypeFont font;
    YAML::Node yamlDoc;
    int osc_port;
    ofxOscReceiver oscIn;
    string helpText;
    float dimmedAlpha;
    float sceneFadeSpeed;
    bool showSceneSwitcher;
    bool doFullScreen;
    ofImage buttonImages[6];
    string dataPath;
};
