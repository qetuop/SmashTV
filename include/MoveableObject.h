/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoveableObject.h
 * Author: brian
 *
 * Created on January 5, 2016, 7:10 PM
 */
#include "SDL2/SDL.h"

#include <iostream>

#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H

class MoveableObject {
                            
public:
    // sprite bounding box
    int mHeight;
    int mWidth;
    
    // TODO: make a setX/Y func?

    // the offsets
    int mPosX;
    int mPosY;

    // The velocity
    int mVelX;
    int mVelY;

    // facing
    double mDirection;

    std::string mSpriteName;

    // collision box
    SDL_Rect mCollider;
    
public:
    MoveableObject();
    MoveableObject( const MoveableObject& orig );
    ~MoveableObject();
    
    void move();
    
    int getHeight();
    int getWidth();
    
    void setHeight(int _height);
    void setWidth(int _width);
    
    SDL_Rect getCollider();
    
    bool checkCollision( SDL_Rect targetRect );
    
}; // class MoveableObject

#endif /* MOVEABLEOBJECT_H */

