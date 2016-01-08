/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoveableObject.cpp
 * Author: brian
 * 
 * Created on January 6, 2016, 6:13 PM
 */
#include "App.h"
#include "MoveableObject.h"

MoveableObject::MoveableObject( ) {
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;
    
    mCollider.x = x;
    mCollider.y = y;

    xVel = 0;
    yVel = 0;

    direction = 0.0;

    spriteName = "";
}

MoveableObject::MoveableObject( const MoveableObject& orig ) {
}

MoveableObject::~MoveableObject( ) {
}

void MoveableObject::move( ) {
    //Move the dot left or right
    x += xVel;
    mCollider.x = x;

    //If the dot went too far to the left or right
    if ( (x < 0) || (x + getHeight() > SCREEN_WIDTH) ) {
        //move back
        x -= xVel;
        mCollider.x = x;
    }

    //Move the dot up or down
    y += yVel;
    mCollider.y = y;

    //If the dot went too far up or down
    if ( (y < 0) || (y + getWidth() > SCREEN_HEIGHT) ) {
        //move back
        y -= yVel;
        mCollider.y = y;
    }

    //std::cout << "x: " << x << ", y: " << y << std::endl;
}

int MoveableObject::getHeight() {
    return height;
}

int MoveableObject:: getWidth() {
    return width;
}

void MoveableObject::setHeight(int _height) {
    height = _height;
    
    mCollider.h = height;
}

void MoveableObject::setWidth(int _width) {
    width = _width;
    mCollider.w = width;
}

SDL_Rect MoveableObject::getCollider() {
    return mCollider;
}

bool MoveableObject::checkCollision( SDL_Rect targetRect ) {
    SDL_Rect result;
    SDL_bool val;
    std::cout << "\ncheckCollision1: " << val << " " 
            << mCollider.x << " " << mCollider.y << " " 
            << mCollider.h << " " << mCollider.w 
            << std::endl;
    
    std::cout << "checkCollision2: " << val << " " 
            << targetRect.x << " " << targetRect.y << " " 
            << targetRect.h << " " << targetRect.w 
            << std::endl;
    
    val = SDL_IntersectRect( &mCollider, &targetRect, &result );
    
    std::cout << "checkCollision3: " << val << " " 
            << result.x << " " << result.y << " " 
            << result.h << " " << result.w 
            << std::endl;
    
    return 0;
}