/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bullet.cpp
 * Author: brian
 * 
 * Created on January 2, 2016, 7:34 PM
 */

#include "Bullet.h"
#include "App.h"

#include <iostream>


Bullet::Bullet() {
    // do once
    mVelX = BULLET_RATE * cos(mDirection);
    mVelY = BULLET_RATE * sin(mDirection);
}

Bullet::Bullet(int _x, int _y, double _direction) {
    mPosX = _x;
    mPosY = _y;

    mDirection = (int)_direction;

    mVelX = BULLET_RATE * cos(mDirection * M_PI / 180);
    mVelY = BULLET_RATE * sin(mDirection * M_PI / 180);
    
//     std::cout << "Bullet(): x = " << x 
//             << ", y = " << y
//             << ", direction = " << direction
//             << ", xVel = " << xVel
//             << ", yVel = " << yVel
//             << std::endl;
     
}

Bullet::~Bullet() {
    //std::cout << "~Bullet()" << std::endl;
}

bool Bullet::move() {
    bool isAlive = true;
    mPosX += mVelX;
    mPosY += mVelY;

    //std::cout << "Bullet::move::x = " << x << ", y = " << y << std::endl;

    // hits a wall
    if ((mPosX <= 0) || (mPosX >= SCREEN_WIDTH)) {
        isAlive = false;
    } else if ((mPosY <= 0) || (mPosY >= SCREEN_HEIGHT)) {
        isAlive = false;
    }

    return isAlive;

} // move

