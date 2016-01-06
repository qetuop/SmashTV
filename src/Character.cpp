/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Character.h"
#include "App.h"
#include <iostream>

#include <vector>

static int doOnce = 1;

Character::Character( ) {
    std::cout << "Character created" << std::endl;
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;

    xVel = 0;
    yVel = 0;

    firing = false;
    
    direction = 0.0;
    
    spriteName = "";
}

Character::~Character( ) {
    std::cout << "Character destroyed" << std::endl;
}

void Character::move( ) {
    //Move the dot left or right
    x += xVel;

    //If the dot went too far to the left or right
    if ( (x < 0) || (x + PLAYER_WIDTH > SCREEN_WIDTH) ) {
        //move back
        x -= xVel;
    }

    //Move the dot up or down
    y += yVel;

    //If the dot went too far up or down
    if ( (y < 0) || (y + PLAYER_HEIGHT > SCREEN_HEIGHT) ) {
        //move back
        y -= yVel;
    }

    //std::cout << "x: " << x << ", y: " << y << std::endl;
}

void Character::fireBullet( ) {


    //std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
    auto bullet = std::make_shared<Bullet>(x + PLAYER_WIDTH / 2, y + PLAYER_HEIGHT / 2, direction);

    // TODO: set these to be the point of the pointer
    //    bullet.get()->x = x;
    //    bullet.get()->y = y;
    //    bullet.get()->direction = direction;

    mBullets.push_back(bullet);
    
    //App::GetInstance()->shoot();
}

void Character::updateBullets( ) {

    for ( auto bulletItr = mBullets.begin(); bulletItr != mBullets.end(); ) {
        if ( bulletItr->get()->move() == false ) {
            bulletItr = mBullets.erase(bulletItr);
        } else {
            ++bulletItr;
        }
    }
}