//
//  Ball.h
//  emptyExample
//

// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
// copy of this license, visit
// http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View,
// California, 94041, USA.
//

#ifndef BumperBodyData_h
#define BumperBodyData_h

class BumperBodyData{
  
public:
    BumperBodyData(int type_);
    int birthFrame;    
    int type;
    static int TYPE_OBSTACLE;
    static int TYPE_BALL;
    static int TYPE_GROUND;
    int lastHitFrame;
    int hitCount;
};

#endif
