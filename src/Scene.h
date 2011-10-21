//
//  Scene.h
//

// a superclass for the different scenes


// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
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
