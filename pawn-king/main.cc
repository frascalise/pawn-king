#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>

/* Screen Dimension */
constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

/* Prototypes */
bool init();        // Initializes SDL and creates a window
bool loadMedia();   // Loads media resources (images, sounds, etc.)
void close();       // Frees media resources and closes SDL

/* Global Variables */
SDL_Window* gWindow{nullptr};         // Window on the screen
SDL_Surface* gScreenSurface{nullptr}; // Surface in the window with content
SDL_Surface* gHelloWorld{nullptr};    // The image we will load and show on the screen

/** MARK: Init()
 * Check if I can initialize SDL, then
 * check if I can create a window, then
 * create the surface of the window
 */
bool init() {
    bool isInitialized{true};

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL error: %s\n", SDL_GetError());
        isInitialized = false;
    } else {
        if(gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0); gWindow == nullptr) {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            isInitialized = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return isInitialized;
}

/** MARK: loadMedia()
 * Load the file and put it into gHelloWorld,
 * then check if it's null
 */
bool loadMedia() {
    bool isLoaded{true};
    std::string imagePath{"file.bmp"};

    if(gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr) {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
        isLoaded = false;
    }

    return isLoaded;
}

/** MARK: close()
 * Destroy all the surfaces and the window, then
 * quit the SDL subsystems
 */
void close() {
    SDL_DestroySurface(gHelloWorld);
    SDL_DestroySurface(gScreenSurface);
    SDL_DestroyWindow(gWindow);
    
    gHelloWorld = nullptr;
    gScreenSurface = nullptr;
    gWindow = nullptr;

    SDL_Quit();
}

/** MARK: main()
 * 1) Initialize SDL
 * 2) Load media
 * 3) Close
 * 
 * If media is loaded correctly then start the SDL loop.
 * You can quit if the quit event is triggered,
 * otherwise load the image and render it in the surface.
 * 
 * The SDL_Event is created and set to 0.
 */
int main(int argc, char* args[]) {
    int exitCode{0};

    if(init() == false) {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    } else {
        if(loadMedia() == false) {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        } else {
            bool quit{false};

            SDL_Event e;
            SDL_zero(e);
            
            while(quit == false) {
                
                // Get event loop
                while(SDL_PollEvent(&e) == true) {
                    // Check if event is a quit event
                    if(e.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }
                }

                //Fill the surface with a color (RGB)
                SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 120, 255, 255));
            
                //Render image on screen
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            } 
        }
    }
    
    close();

    return exitCode;
}
