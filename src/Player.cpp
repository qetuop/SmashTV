/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"
#include <iostream>

Player::Player() {
    std::cout << "Player created" << std::endl;
    x = 0;
    y = 0;
}

Player::~Player() {
    std::cout << "Player destroyed" << std::endl;
}

void Player::handle_input(SDL_GameController *controller) {

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
    
    //Sint16 StickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    //Sint16 StickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
    
    std::cout << "StickX: " << StickLeftX << ", StickY: " << StickLeftY << std::endl;

    int xDir = 0;
    int yDir = 0;

    //Left of dead zone
    if (StickRightX < -JOYSTICK_DEAD_ZONE) {
        xDir = -1;
    }//Right of dead zone
    else if (StickRightX > JOYSTICK_DEAD_ZONE) {
        xDir = 1;
    } else {
        xDir = 0;
    }

    //Below of dead zone
    if (StickRightY < -JOYSTICK_DEAD_ZONE) {
        yDir = -1;
    }//Above of dead zone
    else if (StickRightY > JOYSTICK_DEAD_ZONE) {
        yDir = 1;
    } else {
        yDir = 0;
    }

    
    direction = atan2((double) yDir, (double) xDir) * (180.0 / M_PI);

    // If the X axis is neutral
    if ((StickLeftX > -JOYSTICK_DEAD_ZONE) && (StickLeftX < JOYSTICK_DEAD_ZONE)) {
        xVel = 0;
    }// Adjust the velocity
    else {        
        if (StickLeftX < 0) {
            xVel = -DOT_WIDTH / 8;
        } else {
            xVel = DOT_WIDTH / 8;
        }
    }
        
    // If the Y axis is neutral
    if ((StickLeftY > -JOYSTICK_DEAD_ZONE) && (StickLeftY < JOYSTICK_DEAD_ZONE)) {
        yVel = 0;
    } // Adjust the velocity
    else {        
        if (StickLeftY < 0) {
            yVel = -DOT_HEIGHT / 8;
        } else {
            yVel = DOT_HEIGHT / 8;
        }
    }
    
    std::cout << "xVel: " << xVel << ", yVel: " << yVel << ", direction: " << direction << std::endl;
    
} // handle_input

void Player::move() {
    //Move the dot left or right
    x += xVel;

    //If the dot went too far to the left or right
    if( ( x < 0 ) || ( x + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //move back
        x -= xVel;
    }

    //Move the dot up or down
    y += yVel;

    //If the dot went too far up or down
    if( ( y < 0 ) || ( y + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //move back
        y -= yVel;
    }
    
    std::cout << "x: " << x << ", y: " << y << std::endl;
}