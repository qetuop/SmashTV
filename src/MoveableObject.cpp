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
    mPosX = SCREEN_WIDTH / 2;
    mPosY = SCREEN_HEIGHT / 2;
    
    mCollider.x = mPosX;
    mCollider.y = mPosY;

    mVelX = 0;
    mVelY = 0;

    mDirection = 0.0;

    mSpriteName = "";
}

MoveableObject::MoveableObject( const MoveableObject& orig ) {
}

MoveableObject::~MoveableObject( ) {
}

void MoveableObject::move( ) {
    //Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;

    //If the dot went too far to the left or right
    if ( (mPosX < 0) || (mPosX + getHeight() > SCREEN_WIDTH) ) {
        //move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the dot went too far up or down
    if ( (mPosY < 0) || (mPosY + getWidth() > SCREEN_HEIGHT) ) {
        //move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }

    //std::cout << "x: " << x << ", y: " << y << std::endl;
}

int MoveableObject::getHeight() {
    return mHeight;
}

int MoveableObject:: getWidth() {
    return mWidth;
}

void MoveableObject::setHeight(int _height) {
    mHeight = _height;
    
    mCollider.h = mHeight;
}

void MoveableObject::setWidth(int _width) {
    mWidth = _width;
    mCollider.w = mWidth;
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