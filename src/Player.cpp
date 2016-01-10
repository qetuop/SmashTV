/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"
#include "App.h"

#include <iostream>


//static int doOnce = 1;
const int FRAME_COUNT = 20;


Player::Player( ) {
    std::cout << "Player created " << std::endl;

    frame = 0;
    mSpriteName = "survivor-move_rifle_" ;
}

Player::~Player( ) {
    std::cout << "Player destroyed" << std::endl;
}

void Player::handle_input( SDL_GameController *controller ) {
    
    // TODO: need an update() type function
    
    

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

    if ( ((StickRightX < -JOYSTICK_DEAD_ZONE) || (StickRightX > JOYSTICK_DEAD_ZONE))
            || ((StickRightY < -JOYSTICK_DEAD_ZONE) || (StickRightY > JOYSTICK_DEAD_ZONE)) ) {
        mDirection = atan2((double) StickRightY, (double) StickRightX) * (180.0 / M_PI);
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
        mVelX = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftX < 0 ) {
            mVelX = -PLAYER_WIDTH / 8;
        } else {
            mVelX = PLAYER_WIDTH / 8;
        }
    }

    // If the Y axis is neutral
    if ( (StickLeftY > -JOYSTICK_DEAD_ZONE) && (StickLeftY < JOYSTICK_DEAD_ZONE) ) {
        mVelY = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftY < 0 ) {
            mVelY = -PLAYER_HEIGHT / 8;
        } else {
            mVelY = PLAYER_HEIGHT / 8;
        }
    }

    //std::cout << "xVel: " << xVel << ", yVel: " << yVel << ", direction: " << direction << std::endl;
} // handle_input

void Player::fireBullet( ) {

    // TODO: better way to get texture size then getting it each time?
    Texture *texture = TextureBank::Get("bullet");
    if ( texture != nullptr ){
        auto bullet = std::make_shared<Bullet>(mPosX + PLAYER_WIDTH / 2, mPosY + PLAYER_HEIGHT / 2, mDirection);
        
        mBullets.push_back(bullet);
    }
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

std::string Player::getSpriteName() {
    return mSpriteName + std::to_string(frame);
}

bool Player::move() {
    MoveableObject::move();
    
    // TODO: better way
    if ( mVelX != 0 || mVelY != 0) {
        frame = ++frame % FRAME_COUNT;
    }
    
    return false;
}