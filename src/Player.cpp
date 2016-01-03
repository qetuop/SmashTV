/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"
#include "App.h"
#include <iostream>

#include <vector>

static int doOnce = 1;

Player::Player( ) {
    std::cout << "Player created" << std::endl;
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;

    xVel = 0;
    yVel = 0;

    firing = false;
}

Player::~Player( ) {
    std::cout << "Player destroyed" << std::endl;
}

void Player::handle_input( SDL_GameController *controller ) {

    // DPAD
    bool Up = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
    bool Down = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    bool Left = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    bool Right = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    bool Start = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
    bool Back = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);

    bool LeftShoulder = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    bool RightShoulder = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

    bool AButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
    bool BButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
    bool XButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
    bool YButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);

    Sint16 StickLeftX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 StickLeftY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

    Sint16 StickRightX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    Sint16 StickRightY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);

    //          -90
    //     -135  |  -45
    //         \ | /
    //    180 -- + --  0
    //         / | \
    //     135   |  45
    //          90
    //direction = atan2((double) yDir, (double) xDir) * (180.0 / M_PI);

    if ( ( (StickRightX < -JOYSTICK_DEAD_ZONE) || (StickRightX > JOYSTICK_DEAD_ZONE))
      || ( (StickRightY < -JOYSTICK_DEAD_ZONE) || (StickRightY > JOYSTICK_DEAD_ZONE) ) ) {
        direction = atan2((double) StickRightY, (double) StickRightX) * (180.0 / M_PI);
        fireBullet();
    }

    //std::cout << "direction " << int(direction) << std::endl;

    //if ( doOnce ){   
    //    std::vector<int> test = {0, 45, 90, 135, 180, -135, -90, -45};
    //    for (auto b : test) {
    //        auto bullet = std::make_shared<Bullet>(x, y, b);
    //        mBullets.push_back(bullet);
    //    }
    //    doOnce = 0;
    //}

    if ( RightShoulder == 1 ) {
        fireBullet();
    }

    // ------------------
    // Player movement
    //-------------------

    // If the X axis is neutral
    if ( (StickLeftX > -JOYSTICK_DEAD_ZONE) && (StickLeftX < JOYSTICK_DEAD_ZONE) ) {
        xVel = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftX < 0 ) {
            xVel = -PLAYER_WIDTH / 8;
        } else {
            xVel = PLAYER_WIDTH / 8;
        }
    }

    // If the Y axis is neutral
    if ( (StickLeftY > -JOYSTICK_DEAD_ZONE) && (StickLeftY < JOYSTICK_DEAD_ZONE) ) {
        yVel = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftY < 0 ) {
            yVel = -PLAYER_HEIGHT / 8;
        } else {
            yVel = PLAYER_HEIGHT / 8;
        }
    }

    //std::cout << "xVel: " << xVel << ", yVel: " << yVel << ", direction: " << direction << std::endl;



} // handle_input

void Player::move( ) {
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

void Player::fireBullet( ) {


    //std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
    auto bullet = std::make_shared<Bullet>(x+PLAYER_WIDTH/2, y+PLAYER_HEIGHT/2, direction);

    // TODO: set these to be the point of the pointer
    //    bullet.get()->x = x;
    //    bullet.get()->y = y;
    //    bullet.get()->direction = direction;

    mBullets.push_back(bullet);
}

void Player::updateBullets( ) {

    for ( auto bulletItr = mBullets.begin(); bulletItr != mBullets.end(); ) {
        if ( bulletItr->get()->move() == false ) {
            bulletItr = mBullets.erase(bulletItr);
        } else {
            ++bulletItr;
        }
    }
}