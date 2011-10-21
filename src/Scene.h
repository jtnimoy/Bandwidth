//
//  Scene.h
//

// a superclass for the different scenes

//  Created by Josh Nimoy on 10/19/11.
//  Copyright 2011 Josh Nimoy. All rights reserved.
//


#ifndef Scene_h
#define Scene_h


class Scene{
public:
    virtual void setup();
    virtual void update();
    virtual void draw(float alpha);
    virtual void keyPressed(int key);
    virtual void mouseMoved(int x,int y);
    virtual void mouseDragged(int x,int y,int button);
    virtual void mousePressed(int x,int y,int button);
    virtual void mouseReleased(int x,int y,int button);
    virtual void reset();
};

#endif
