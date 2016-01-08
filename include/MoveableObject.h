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
    int height;
    int width;
    
    // TODO: make a setX/Y func
    // TODO: change to mPosX;
    // the offsets
    int x;
    int y;

    // The velocity
    int xVel;
    int yVel;

    // facing
    double direction;

    std::string spriteName;

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

