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
    x = 0;
    y = 0;
    //xVel = 0;
    //yVel = 0;
    direction = 0.0;

    // do once
    xVel = BULLET_RATE * cos(direction);
    yVel = BULLET_RATE * sin(direction);
}

Bullet::Bullet(int _x, int _y, double _direction) {
    x = _x;
    y = _y;

    direction = (int)_direction;

    xVel = BULLET_RATE * cos(direction * M_PI / 180);
    yVel = BULLET_RATE * sin(direction * M_PI / 180);
    
//    if ( direction < 0 ) {
//        yVel = -yVel;
//    }
    
     std::cout << "Bullet(): x = " << x 
             << ", y = " << y
             << ", direction = " << direction
             << ", xVel = " << xVel
             << ", yVel = " << yVel
             << std::endl;
     
}

Bullet::~Bullet() {
    std::cout << "~Bullet()" << std::endl;
}

bool Bullet::move() {
    bool isAlive = true;
    x += xVel;
    y += yVel;

    //std::cout << "Bullet::move::x = " << x << ", y = " << y << std::endl;


    //    switch (int(direction)) {
    //        case 0:
    //            x += RATE;
    //            break;
    //
    //        case 45:
    //            x += RATE / 2;
    //            y += RATE / 2;
    //            break;
    //
    //        case 90:
    //            y += RATE;
    //            break;
    //
    //        case 135:
    //            x -= RATE / 2;
    //            y += RATE / 2;
    //            break;
    //
    //        case 180:
    //            x -= RATE;
    //            break;
    //
    //        case -45:
    //            x += RATE / 2;
    //            y -= RATE / 2;
    //            break;
    //
    //        case -90:
    //            y -= RATE;
    //            break;
    //
    //        case -135:
    //            x -= RATE / 2;
    //            y -= RATE / 2;
    //            break;
    //}

    // hits a wall
    if ((x <= 0) || (x >= SCREEN_WIDTH)) {
        isAlive = false;
    } else if ((y <= 0) || (y >= SCREEN_HEIGHT)) {
        isAlive = false;
    }

    return isAlive;

} // move

