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

#ifndef PLAYER_H
#define PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

    class Player {
    public:
        // TODO: these need to be passed in/set somewhere

        const int JOYSTICK_DEAD_ZONE = 8000;
        const int DOT_WIDTH = 80;
        const int DOT_HEIGHT = 80;
        static const int SCREEN_WIDTH = 1024;
        static const int SCREEN_HEIGHT = 768;

        // the offsets
        int x;
        int y;

        //The velocity of the dot
        int xVel;
        int yVel;

        double direction;


    public:
        Player();
        ~Player();

        void handle_input(SDL_GameController *controller);

        //Moves the dot
        void move();


    };



#ifdef __cplusplus
}
#endif

#endif /* PLAYER_H */

