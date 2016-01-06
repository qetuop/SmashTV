/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: brian
 *
 * Created on January 1, 2016, 5:54 PM
 */
#include <SDL2/SDL.h>

#include <memory>
#include <list>

#include "Bullet.h"
#include "Character.h"

#ifndef PLAYER_H
#define PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

    class Player : public Character {
    public:

    public:
        Player();
        ~Player();

        void handle_input(SDL_GameController *controller);

        // Moves the dot
        void move();
    };



#ifdef __cplusplus
}
#endif

#endif /* PLAYER_H */

