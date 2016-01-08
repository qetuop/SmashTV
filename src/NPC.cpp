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
    x = 0;
    y = 0;
    
    mCollider.x = x;
    mCollider.y = y;
    
    spriteName = "attacker2";    
}

NPC::~NPC( ) {
    std::cout << "NPC destroyed" << std::endl;
}