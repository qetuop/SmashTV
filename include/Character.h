/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: brian
 *
 * Created on January 1, 2016, 5:54 PM
 */
#include <SDL2/SDL.h>

#include <memory>
#include <list>

#include "Bullet.h"

#ifndef CHARACTER_H
#define CHARACTER_H

#ifdef __cplusplus
extern "C" {
#endif

    class Character {
    public:
        // the offsets
        int x;
        int y;

        // The velocity
        int xVel;
        int yVel;

        // facing
        double direction;

        bool firing;

        std::list<std::shared_ptr<Bullet>> mBullets;
        
        std::string spriteName;
        
        //Dot's collision box
        SDL_Rect mCollider;


    public:
        Character();
        ~Character();

        //void handle_input(SDL_GameController *controller);

        // Move - PC will take joystick input, NPC use an AI
        virtual void move();

        void fireBullet();
        void updateBullets();


    };

#ifdef __cplusplus
}
#endif

#endif /* CHARACTER_H */

