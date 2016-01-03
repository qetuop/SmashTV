#ifndef __APP_H__
#define __APP_H__

#include <SDL2/SDL.h>

#include "Event.h"
#include "TextureBank.h"

#include "Player.h"
#include "Timer.h"


#include <memory>

////Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
////Analog joystick dead zone
//const int JOYSTICK_DEAD_ZONE = 8000;

class App : public Event {
private:
    static App Instance;

    bool Running = true;

    SDL_Window* Window = NULL;
    SDL_Renderer* Renderer = NULL;
    //SDL_Surface* PrimarySurface = NULL;
    SDL_Joystick *mJoystick;
    SDL_GameController *mGameController;

    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;

    //The frame rate
    const int FRAMES_PER_SECOND = 10;
    //The frame rate regulator
    Timer fps;



    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000;

    Texture* TestTexture;

    std::shared_ptr<Player> mPlayerPtr;

private:
//    public:
    App();

    // Capture SDL Events
    void OnEvent(SDL_Event* Event);

    // Initialize our SDL game / app
    bool Init();

    // Logic loop
    void Loop();

    // Render loop (draw)
    void Render();

    // Free up resources
    void Cleanup();

public:
    int Execute(int argc, char* argv[]);

public:
    SDL_Renderer* GetRenderer();

public:
    static App* GetInstance();

    static int GetWindowWidth();
    static int GetWindowHeight();
};

#endif
