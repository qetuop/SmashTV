/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NPC.h"
#include "App.h"
#include <iostream>

#include <vector>

static int doOnce = 1;

NPC::NPC( ) {
    std::cout << "NPC created" << std::endl;
    
    x = 0;
    y = 0;
    
    spriteName = "attacker2";
    
    std::cout << "direction " << direction << std::endl;
    
}

NPC::~NPC( ) {
    std::cout << "NPC destroyed" << std::endl;
}


void NPC::move( ) {
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
