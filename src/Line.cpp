/*
 *  Line.cpp
 *  emptyExample
 *

 // This work is licensed under the Creative Commons
 // Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a
 // copy of this license, visit
 // http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
 // Creative Commons, 444 Castro Street, Suite 900, Mountain View,
 // California, 94041, USA.
 //
 *
 */

#include "Line.h"
#include "testApp.h"


Line::Line(){
  

}

//--------------------------------------------



Line::Line(int xx,int yy){
	x=xx;
	y=yy;
    x2 = ofGetScreenWidth() * ofRandomuf();
    y2 = ofGetScreenHeight() * ofRandomuf();
    dest_x2 = ofGetScreenWidth() * ofRandomuf();
    dest_y2 = ofGetScreenHeight() * ofRandomuf();
    
    ticks=0;
	death = -1;
    color = MColor( ofRandomuf() * HALF_PI + PI, 0.5, 0.5, "HSB");
    ballColor = MColor( ofRandomuf() * PI, 1.0f, 1.0f, "HSB");
    lineWidth = ofRandomuf() * 10;
    ballSpeed = ofRandomuf() * 100.0f + 200;
    ballX = ballY = 0;
    x3 = y3 = x4 = y4 = 0;
    radius = lineWidth;
    pluckCounter = 0;
}


//--------------------------------------------



void Line::step(){    
    
    x2 += (dest_x2 - x2) * 0.1;
    y2 += (dest_y2 - y2) * 0.1;

    ballPosition = ((ticks % ballSpeed) / (float)ballSpeed);
    

    
    //find sufficient extender length
    float hyp = ofDist(ofGetScreenWidth(),ofGetScreenHeight(),0,0);
    
    //get angles in both directions
    float theta1 = atan2(y-y2,x-x2);
    float theta2 = atan2(y2-y,x2-x);
    
    //define rendering segment
    x3 = x  + cos(theta2) * hyp;
    y3 = y  + sin(theta2) * hyp;
    x4 = x2 + cos(theta1) * hyp;
    y4 = y2 + sin(theta1) * hyp;
    
    //find ball position based on time
    ballX = x3 + (x4-x3) * ballPosition;
    ballY = y3 + (y4-y3) * ballPosition;

    //update math calculations
    slope = (y4 - y3) / (x4 - x3);
    elevation = y4 - slope * x4;
    
    vector<Line*>::iterator it;    
    float screenW = ofGetScreenWidth();
    float screenH = ofGetScreenHeight();
    for(it = SceneLines::instance->lines.begin(); it != SceneLines::instance->lines.end() ; it ++ ){
        if( (*it) != this){
            
            if(ballX > 0 && ballX < screenW  && ballY > 0 && ballY < screenH ){
                
                bool side = (*it)->pointAbove(ballX,ballY);
                
                if(sides[*it] == 2 ){
                    if(side){
                        sides[*it] = 3;
                        radius += 20;
                        (*it)->crossed();
                        sound();
                    }
                }else{
                    if(!side){
                        sides[*it] = 2;
                        radius += 20;
                        (*it)->crossed();
                        sound();
                    }
                }
                    
            }else{
                sides[*it] = 2;
            }
            
        }
    }
    
    pluckCounter = max(0,pluckCounter-1);
    
    radius = fmin(fmax(lineWidth, radius-5),50);
    ticks++;
}



//--------------------------------------------


void Line::draw(float alpha){
    
    //draw line
    ofNoFill();

    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    ofSetLineWidth(this->lineWidth);
    glBegin(GL_LINES);
    
    if(pluckCounter==0){
        glColor4b(
                   color.red() * 255.0,  
                   color.green() * 255.0,
                   color.blue() * 255.0,
                   128.0 * alpha );
    }else{
        glColor4f(1,1,1,alpha);
    }
    
    glVertex2f(x3,y3);
    glColor4b(0,0,0,0);
    
    glVertex2f(x4,y4);
    glEnd();
    glPopAttrib();
    
    
    //draw ball
    ofSetColor(
               ballColor.red() * 255.0,
               ballColor.green() * 255.0,
               ballColor.blue() * 255.0,
               128.0 * alpha );
    
    ofFill();
    ofSetLineWidth(1);
    ofCircle(ballX,ballY,radius);
    
}


//--------------------------------------------

bool Line::pointAbove(float xx,float yy){
    return slope * xx + elevation > yy;
}

//--------------------------------------------

void Line::sound(){
    SceneLines::instance->snd0.setSpeed(
                            SceneLines::instance->welltempered[
                                     (int)((1.0 - (ballY / ofGetScreenHeight() ) ) * 12)
                             ] * 0.5);
    SceneLines::instance->snd0.setVolume(0.1);
    SceneLines::instance->snd0.play();
   
}

//--------------------------------------------


void Line::crossed(){
    pluckCounter+=2;
}

