/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NPC.h"

#include <iostream>


static int doOnce = 1;

NPC::NPC( ) {
    std::cout << "NPC created" << std::endl;
    
    // TODO: make a setX/Y func
    mPosX = 0;
    mPosY = 0;
    
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    
    mSpriteName = "attacker2";    
}

NPC::~NPC( ) {
    std::cout << "NPC destroyed" << std::endl;
}