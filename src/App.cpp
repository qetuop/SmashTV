//==============================================================================
#include "App.h"
#include "Log.h"
#include "Event.h"
#include "Helper.h"
#include "Player.h"
#include "Bullet.h"

App App::Instance;

//==============================================================================

App::App( ) {
}

//------------------------------------------------------------------------------

void App::OnEvent( SDL_Event* Event ) {
    Event::OnEvent(Event);
}

//------------------------------------------------------------------------------

bool App::Init( ) {
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        Log("Unable to Init SDL: %s", SDL_GetError());
        return false;
    }

    if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }

    if ( (Window = SDL_CreateWindow(
            "My SDL Game",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)
            ) == NULL ) {
        Log("Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    //    PrimarySurface = SDL_GetWindowSurface(Window);

    if ( (Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr ) {
        Log("Unable to create renderer");
        return false;
    }

    //SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

    // Initialize image loading for PNGs
    if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
        Log("Unable to init SDL_image: %s", IMG_GetError());
        return false;
    }

    // Load all of our Textures (see TextureBank class for expected folder)
    if ( TextureBank::Init() == false ) {
        Log("Unable to init TextureBank");
        return false;
    }

    //Check for joysticks
    if ( SDL_NumJoysticks() < 1 ) {
        printf("Warning: No joysticks connected!\n");
    } else {
        //Load joystick
        mJoystick = SDL_JoystickOpen(0);
        if ( mJoystick == NULL ) {
            logSDLError(std::cout, "CApp::OnInit");
        } else
            std::cout << "LOADED JOYSTICK" << std::endl;
    }


    for ( int i = 0; i < SDL_NumJoysticks(); ++i ) {
        if ( SDL_IsGameController(i) ) {
            mGameController = SDL_GameControllerOpen(i);
            if ( mGameController ) {
                cout << "Found Controller" << endl;
                std::cout << SDL_GameControllerMapping(mGameController) << std::endl;
                break;
            } else {
                logSDLError(std::cout, "CApp::OnInit");
            }
        }
    }

    // The Players
    Texture *texture = TextureBank::Get("survivor2");
    if ( texture != nullptr ) {
        mPlayerPtr = std::make_shared<Player>();
        mPlayerPtr->setWidth(texture->GetWidth());
        mPlayerPtr->setHeight((texture->GetHeight()));
    }
    

    // The baddies
    texture = TextureBank::Get("attacker2");
    if ( texture != nullptr ) {
        mNPCPtr = std::make_shared<NPC>();
        mNPCPtr->setWidth(texture->GetWidth());
        mNPCPtr->setHeight((texture->GetHeight()));
    }


    //Initialize SDL_mixer
    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    //Load sound effects
    mPew = Mix_LoadWAV("Sounds/pew.wav");
    if ( mPew == NULL ) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}
// TODO: need to move this somewhere else

void App::shoot( ) {
    Mix_PlayChannel(-1, mPew, 0);
}

//------------------------------------------------------------------------------

void App::Loop( ) {
    if ( mGameController != nullptr && SDL_GameControllerGetAttached(mGameController) ) {
        // NOTE: We have a mGameController with index ControllerIndex.

        mPlayerPtr->handle_input(mGameController);
        mPlayerPtr->move();
        mPlayerPtr->checkCollision(mNPCPtr->getCollider());

        mPlayerPtr->updateBullets();                
    }
}

//------------------------------------------------------------------------------

void App::Render( ) {
    SDL_RenderClear(Renderer);

    //std::cout << __FILE__ << " " << __LINE__ << std::endl;
    
    // TODO: need to loop through textures?
    Texture* texture = nullptr;

    // Players
    //std::string name = mPlayerPtr->getSpriteName();
    //std::cout << "name  " << name << std::endl;
    texture = TextureBank::Get(mPlayerPtr->getSpriteName());
    //std::cout << "mPlayerPtr->getSpriteName() " << mPlayerPtr->getSpriteName() << endl;
    if ( texture != nullptr ) {

        texture->render(Renderer, mPlayerPtr->mPosX, mPlayerPtr->mPosY, 
                NULL, mPlayerPtr->mDirection);
    } else {
        logSDLError(std::cout, "App::Render");
    }
        
    // NPCs
    texture = TextureBank::Get(mNPCPtr->mSpriteName);
    if ( texture != nullptr ) {

        texture->render(Renderer, mNPCPtr->mPosX, mNPCPtr->mPosY, 
                NULL, mNPCPtr->mDirection);
    } else {
        logSDLError(std::cout, "App::Render");
    }
    
    // Bullets!
    // TODO: move the texture type into the Bullet class?  Just the identifier string bulletType
    texture = TextureBank::Get("bullet");
    if ( texture != nullptr ) {
        for ( auto&& bullet : mPlayerPtr->mBullets ) {
            if ( bullet != nullptr ) {
                texture->render(Renderer, bullet->mPosX, bullet->mPosY);
            }
        }
    } else {
        logSDLError(std::cout, "App::Render");
    }


    SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------

void App::Cleanup( ) {
    
    TextureBank::Cleanup();

    if ( Renderer ) {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
    }

    if ( Window ) {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }
    
    // sounds?

    IMG_Quit();
    SDL_Quit();
}

//------------------------------------------------------------------------------

int App::Execute( int argc, char* argv[] ) {
    if ( !Init() ) return 0;

    SDL_Event Event;

    while (Running) {
        //Start the frame timer
        fps.start();


        while (SDL_PollEvent(&Event) != 0) {
            OnEvent(&Event);

            if ( Event.type == SDL_QUIT )
                Running = false;
        }

        Loop();
        Render();

        //Cap the frame rate
        if ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
        }

        //SDL_Delay(1); // Breath
    }

    Cleanup();

    return 1;
}

//==============================================================================

SDL_Renderer * App::GetRenderer( ) {
    return Renderer;
}

//==============================================================================

App * App::GetInstance( ) {
    return &App::Instance;
}

int App::GetWindowWidth( ) {
    return SCREEN_WIDTH;
}

int App::GetWindowHeight( ) {
    return SCREEN_HEIGHT;
}

//==============================================================================
