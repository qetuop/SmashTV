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

    //If the dot went too far to the left or right
    if ( (x < 0) || (x + getHeight() > SCREEN_WIDTH) ) {
        //move back
        x -= xVel;
    }

    //Move the dot up or down
    y += yVel;

    //If the dot went too far up or down
    if ( (y < 0) || (y + getWidth() > SCREEN_HEIGHT) ) {
        //move back
        y -= yVel;
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
}

void MoveableObject::setWidth(int _width) {
    width = _width;
}