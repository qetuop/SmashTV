/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bullet.h
 * Author: brian
 *
 * Created on January 2, 2016, 7:33 PM
 */

#ifndef BULLET_H
#define BULLET_H



class Bullet {
    
public:
    // the offsets
    int x;
    int y;

    // The velocity of the bullet
    int xVel;
    int yVel;

    double direction;

public:
    Bullet();
    Bullet(int _x, int _y, double _direction );
    ~Bullet();
    
    bool move();
};

#endif /* BULLET_H */

