#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define MAX_BULLETS 1000
#define FONT_PATH   "assets/arcadeclassic/ARCADECLASSIC.ttf"

const int SCREEN_WIDTH = 1225;
const int SCREEN_HEIGHT = 700;

const int GRAVITY = 1;
const int JUMP_FORCE = -20;
const int CHARACTER_SPEED = 5;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;




// Load an image and return an SDL_Texture
SDL_Texture* load_texture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Draw a texture at the specified location
void draw_texture(SDL_Texture* texture,SDL_Rect rect ) {
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// Check if two rectangles intersect
int intersect_rects(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w < b.x || a.x > b.x + b.w || a.y + a.h < b.y || a.y > b.y + b.h) {
        return 0;
    }
    return 1;
}



int Level2() {



    // Initialize SDL2 and create a window and renderer
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) ;
        IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );

    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *jump = NULL;
    Mix_Chunk *kill = NULL;
    Mix_Chunk *lost = NULL;
    Mix_Chunk *win = NULL;
    //Load music
       gMusic = Mix_LoadMUS( "assets/m1.wav" );
       if( gMusic == NULL )
       {
           printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       //Load sound effects
       jump = Mix_LoadWAV( "assets/jump.wav" );
       if( jump == NULL )
       {
           printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );

       }

       kill = Mix_LoadWAV( "assets/enemy_killed.wav" );
       if( kill == NULL )
       {
           printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       lost = Mix_LoadWAV( "assets/lost.wav" );
       if( lost == NULL )
       {
           printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       win = Mix_LoadWAV( "assets/lvl_win.wav" );
       if( win == NULL )
       {
           printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }


    window = SDL_CreateWindow("mole Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/pacifico/Pacifico.ttf", 40);

    // Create a surface for the text
    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game over! Hit any key to replay", textColor);

    // Convert the surface to a texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Get the dimensions of the texture
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Set the position of the text
    SDL_Rect textRect = { (SCREEN_HEIGHT - textHeight ) / 2, (SCREEN_WIDTH - textWidth) / 2, textWidth, textHeight };


    // Render the texture to the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);


    // Load background, character, and obstacle images
    SDL_Texture* background_texture = load_texture("assets/back2.png");
    SDL_Texture* character_texture = load_texture("assets/guy.png");
    SDL_Texture* enemy_texture = load_texture("assets/flame4.png");

    SDL_Texture* obstacle_texture= load_texture("assets/obstt.png");
    SDL_Texture* opened_door_texture= load_texture("assets/open1.png");
    SDL_Texture* closed_door_texture= load_texture("assets/close1.png");


 // int channel;

    // Set the initial position and state of the character

        // Load background music and sound effect
    Mix_Music* bg_music = Mix_LoadMUS("assets/m1.mp3");
     //Mix_Chunk* diedsong = Mix_LoadWAV("assets/died.wav");
     //Mix_Chunk* jump = Mix_LoadWAV("assets/jump.wav");



    // Play background music on loop

    // Run the game loop
    int character_x = 100;
    int character_y = -100;
    int character_vy = 0;
    int is_jumping = 0;
    int is_dead = 0;
    int is_enemy2_dead=0;
    int is_enemy1_dead=0;


    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    // Set the position of the obstacle
    int enemy_x = 100;
    int enemy_y = 100;
    int enemy2_x = 0;
    int enemy2_y = 0;
    int enemy2_vy = 0;

    int enemy_vy=0;

    int quit = 0;
    while (!quit) {
        // Handle events


        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && !is_jumping && !is_dead) {
                    // Start jumping
                    Mix_PlayChannel( -1, jump, 0 );


                    character_vy = JUMP_FORCE;
                    enemy_vy=JUMP_FORCE;
                    enemy2_vy=JUMP_FORCE;

                    is_jumping = 1;
                }
            }
        }


        // Update the character position and velocity
        character_y += character_vy;
        enemy_y+=enemy_vy;
        enemy2_y+=enemy2_vy;
        enemy_vy+=GRAVITY;
        enemy2_vy+=GRAVITY;
        character_vy += GRAVITY;

        // Check if the character hits the ground
        if (character_y >= SCREEN_HEIGHT - 100) {
            character_y = SCREEN_HEIGHT - 100;
            enemy2_y = SCREEN_HEIGHT - 100;

            character_vy = 0;
            is_jumping = 0;
            enemy2_vy=0;
        }
        if (enemy_y >= SCREEN_HEIGHT - 440) {
            enemy_y = SCREEN_HEIGHT - 440;

            enemy_vy=0;
            is_jumping = 0;
        }

        // Move the character left or right
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && !is_dead) {
            if (!(character_x<0)){
                character_x -= CHARACTER_SPEED;
                enemy_x -= CHARACTER_SPEED;
                enemy2_x -= CHARACTER_SPEED;


            }

        }else if (state[SDL_SCANCODE_RIGHT] && !is_dead) {
            if (character_x<SCREEN_WIDTH){
                character_x += CHARACTER_SPEED;
                enemy_x += CHARACTER_SPEED;
                enemy2_x += CHARACTER_SPEED;



            }
        }

        // Check if the character or the enemy  hits the obstacle
        SDL_Rect character_rect = { character_x, character_y, 10, 10 };
        SDL_Rect enemy2_rect = { enemy2_x, enemy2_y, 32, 32 };
        SDL_Rect enemy1_rect = { enemy_x, enemy_y, 32, 32 };


        SDL_Rect obstacle_rect= {SCREEN_WIDTH/2,SCREEN_HEIGHT-120 ,50,50};
        SDL_Rect obstacle_rect1= {(SCREEN_WIDTH/2) +50,SCREEN_HEIGHT-458 ,50,50};

        if (intersect_rects(character_rect, obstacle_rect)) {
            Mix_PlayChannel( -1, lost, 0 );

            is_dead = 1;




        }

        if (intersect_rects(enemy2_rect, obstacle_rect)|| intersect_rects(enemy2_rect, obstacle_rect1)) {
            Mix_PlayChannel( -1, kill, 0 );

            is_enemy2_dead = 1;



     }

        if (intersect_rects(enemy1_rect, obstacle_rect)|| intersect_rects(enemy1_rect, obstacle_rect1)) {
            Mix_PlayChannel( -1, kill, 0 );

            is_enemy1_dead = 1;



     }


        // Clear the screen and draw the background and character
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect = { 0, 0, 0, 0 };

        draw_texture(background_texture, rect);
        draw_texture(obstacle_texture,obstacle_rect);
        draw_texture(obstacle_texture,obstacle_rect1);

        draw_texture(character_texture,  character_rect);
        SDL_RenderPresent(renderer);



        SDL_Rect rect1 = { SCREEN_WIDTH-95, SCREEN_HEIGHT - 172,100,100 };


            if(!is_enemy2_dead ){

                draw_texture(enemy_texture,enemy2_rect);

                draw_texture(closed_door_texture,rect1);


            }
            if(!is_enemy1_dead ){

                draw_texture(enemy_texture,enemy1_rect);

                draw_texture(closed_door_texture,rect1);


            }





         if(is_enemy2_dead && is_enemy1_dead ){
            draw_texture(opened_door_texture,rect1);
            enemy_y=1;
            enemy_x=1;

            if (intersect_rects(character_rect, rect1)){
                SDL_Surface* textSurface4 = TTF_RenderText_Solid(font, "YOU WIN !!!!!!!!!!!!!!!!!!!", textColor);
                SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface4);
                SDL_QueryTexture(textTexture1, NULL, NULL, &textWidth, &textHeight);
                SDL_RenderCopy(renderer, textTexture1, NULL, &textRect);
                SDL_RenderPresent(renderer);
                quit = 1;
                Mix_PlayChannel( -1, win, 0 );

                SDL_Delay(3000);
                return 1;



            }


        }

        if ( !quit ){
            draw_texture(character_texture,  character_rect);
        }

        // Draw the obstacle if the character is not dead


        // Update the screen
        SDL_RenderPresent(renderer);

        // Wait for a short time
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( gMusic, -1 );
        }
        //If music is being played

        SDL_Delay(10);




        while (is_dead) {
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_RenderPresent(renderer);
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_KEYDOWN){
                    is_dead=0;
                    character_x = 100;
                     enemy_x=100;
                     enemy_y = SCREEN_HEIGHT - 100;
                     character_y = SCREEN_HEIGHT - 100;
                     enemy_x = 100;
                      enemy_y = 100;
                      enemy2_x = 0;
                      enemy2_y = 0;
                      is_enemy1_dead=0;
                      is_enemy2_dead=0;


                     enemy_vy=0;
                     character_vy = 0;
                     is_jumping = 0;

                    // Set the position of the obstacle

                }

                SDL_Delay(50);

            }
            SDL_Delay(50);
        }
    }

    // Clean up and exit
    Mix_FreeMusic(bg_music);
    //Free the sound effects
    Mix_FreeChunk( jump );
    Mix_FreeChunk( kill );
    Mix_FreeChunk( lost );
    Mix_FreeChunk( win );
    jump = NULL;
    kill = NULL;
    lost = NULL;
    win = NULL;
    Mix_FreeMusic( gMusic );


    Mix_CloseAudio();
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    return 0;


}





int Level1() {



    // Initialize SDL2 and create a window and renderer
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) ;
        IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );

    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *jump = NULL;
    Mix_Chunk *kill = NULL;
    Mix_Chunk *lost = NULL;
    Mix_Chunk *win = NULL;
    //Load music
       gMusic = Mix_LoadMUS( "assets/m1.wav" );
       if( gMusic == NULL )
       {
           printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       //Load sound effects
       jump = Mix_LoadWAV( "assets/jump.wav" );
       if( jump == NULL )
       {
           printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );

       }

       kill = Mix_LoadWAV( "assets/enemy_killed.wav" );
       if( kill == NULL )
       {
           printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       lost = Mix_LoadWAV( "assets/lost.wav" );
       if( lost == NULL )
       {
           printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       win = Mix_LoadWAV( "assets/lvl_win.wav" );
       if( win == NULL )
       {
           printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }


    window = SDL_CreateWindow("mole Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/pacifico/Pacifico.ttf", 40);

    // Create a surface for the text
    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game over! Hit any key to replay", textColor);

    // Convert the surface to a texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Get the dimensions of the texture
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Set the position of the text
    SDL_Rect textRect = { (SCREEN_HEIGHT - textHeight ) / 2, (SCREEN_WIDTH - textWidth) / 2, textWidth, textHeight };


    // Render the texture to the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);


    // Load background, character, and obstacle images
    SDL_Texture* background_texture = load_texture("assets/background7.png");
    SDL_Texture* character_texture = load_texture("assets/guy.png");
    SDL_Texture* enemy_texture = load_texture("assets/flame4.png");

    SDL_Texture* obstacle_texture= load_texture("assets/obstt.png");
    SDL_Texture* opened_door_texture= load_texture("assets/open1.png");
    SDL_Texture* closed_door_texture= load_texture("assets/close1.png");


 // int channel;

    // Set the initial position and state of the character

        // Load background music and sound effect
    Mix_Music* bg_music = Mix_LoadMUS("assets/m1.mp3");
     //Mix_Chunk* diedsong = Mix_LoadWAV("assets/died.wav");
     //Mix_Chunk* jump = Mix_LoadWAV("assets/jump.wav");



    // Play background music on loop

    // Run the game loop
    int character_x = 100;
    int character_y = -100;
    int character_vy = 0;
    int is_jumping = 0;
    int is_dead = 0;
    int is_enemy2_dead=0;

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    // Set the position of the obstacle
    int enemy_x = 100;
    int enemy_y = 100;
    int enemy2_x = 0;
    int enemy2_y = 0;
    int enemy2_vy = 0;

    int enemy_vy=0;

    int quit = 0;
    while (!quit) {
        // Handle events



        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && !is_jumping && !is_dead) {
                    // Start jumping
                    Mix_PlayChannel( -1, jump, 0 );


                    character_vy = JUMP_FORCE;
                    enemy_vy=JUMP_FORCE;
                    enemy2_vy=JUMP_FORCE;

                    is_jumping = 1;
                }
            }
        }


        // Update the character position and velocity
        character_y += character_vy;
        enemy_y+=enemy_vy;
        enemy2_y+=enemy2_vy;
        enemy_vy+=GRAVITY;
        enemy2_vy+=GRAVITY;
        character_vy += GRAVITY;

        // Check if the character hits the ground
        if (character_y >= SCREEN_HEIGHT - 100) {
            character_y = SCREEN_HEIGHT - 100;
            enemy2_y = SCREEN_HEIGHT - 100;

            character_vy = 0;
            is_jumping = 0;
            enemy2_vy=0;
        }
        if (enemy_y >= SCREEN_HEIGHT - 440) {
            enemy_y = SCREEN_HEIGHT - 440;

            enemy_vy=0;
            is_jumping = 0;
        }

        // Move the character left or right
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && !is_dead) {
            if (!(character_x<0)){
                character_x -= CHARACTER_SPEED;
                enemy_x -= CHARACTER_SPEED;
                enemy2_x -= CHARACTER_SPEED;


            }

        }else if (state[SDL_SCANCODE_RIGHT] && !is_dead) {
            if (character_x<SCREEN_WIDTH){
                character_x += CHARACTER_SPEED;
                enemy_x += CHARACTER_SPEED;
                enemy2_x += CHARACTER_SPEED;



            }
        }

        // Check if the character or the enemy  hits the obstacle
        SDL_Rect character_rect = { character_x, character_y, 10, 10 };
        SDL_Rect enemy2_rect = { enemy2_x, enemy2_y, 32, 32 };

        SDL_Rect obstacle_rect= {SCREEN_WIDTH/2,SCREEN_HEIGHT-120 ,50,50};

        if (intersect_rects(character_rect, obstacle_rect)) {
            Mix_PlayChannel( -1, lost, 0 );

            is_dead = 1;




        }

        if (intersect_rects(enemy2_rect, obstacle_rect)) {
            Mix_PlayChannel( -1, kill, 0 );

            is_enemy2_dead = 1;



     }


        // Clear the screen and draw the background and character
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect = { 0, 0, 0, 0 };

        draw_texture(background_texture, rect);
        draw_texture(obstacle_texture,obstacle_rect);
        draw_texture(character_texture,  character_rect);
        SDL_RenderPresent(renderer);




        SDL_Rect rect1 = { SCREEN_WIDTH-95, SCREEN_HEIGHT - 172,100,100 };


           if(!is_enemy2_dead ){

                draw_texture(enemy_texture,enemy2_rect);

                draw_texture(closed_door_texture,rect1);

            }





         if(is_enemy2_dead){
            draw_texture(opened_door_texture,rect1);
            enemy_y=1;
            enemy_x=1;

            if (intersect_rects(character_rect, rect1)){
                SDL_Surface* textSurface4 = TTF_RenderText_Solid(font, "YOU WIN !!!!!!!!!!!!!!!!!!!", textColor);
                SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface4);
                SDL_QueryTexture(textTexture1, NULL, NULL, &textWidth, &textHeight);
                SDL_RenderCopy(renderer, textTexture1, NULL, &textRect);
                SDL_RenderPresent(renderer);
                quit = 1;
                Mix_PlayChannel( -1, win, 0 );

                SDL_Delay(3000);
                return 1;


            }


        }

        if ( !quit ){
            draw_texture(character_texture,  character_rect);
        }

        // Draw the obstacle if the character is not dead


        // Update the screen
        SDL_RenderPresent(renderer);

        // Wait for a short time
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( gMusic, -1 );
        }
        //If music is being played

        SDL_Delay(10);




        while (is_dead) {
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_RenderPresent(renderer);
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_KEYDOWN){
                    is_dead=0;
                    character_x = 100;
                     enemy2_x=0;
                     enemy_y = SCREEN_HEIGHT - 100;
                     character_y = SCREEN_HEIGHT - 100;
                     enemy_vy=0;
                     character_vy = 0;
                     is_enemy2_dead=0;
                     is_jumping = 0;

                    // Set the position of the obstacle

                }

                SDL_Delay(50);

            }
            SDL_Delay(50);
        }
    }

    // Clean up and exit
    Mix_FreeMusic(bg_music);
    //Free the sound effects
    Mix_FreeChunk( jump );
    Mix_FreeChunk( kill );
    Mix_FreeChunk( lost );
    Mix_FreeChunk( win );
    jump = NULL;
    kill = NULL;
    lost = NULL;
    win = NULL;
    Mix_FreeMusic( gMusic );


    Mix_CloseAudio();
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    return 0;

}



int Level3() {



    // Initialize SDL2 and create a window and renderer
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) ;
        IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );

    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *jump = NULL;
    Mix_Chunk *kill = NULL;
    Mix_Chunk *lost = NULL;
    Mix_Chunk *win = NULL;
    //Load music
       gMusic = Mix_LoadMUS( "assets/m1.wav" );
       if( gMusic == NULL )
       {
           printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       //Load sound effects
       jump = Mix_LoadWAV( "assets/jump.wav" );
       if( jump == NULL )
       {
           printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );

       }

       kill = Mix_LoadWAV( "assets/enemy_killed.wav" );
       if( kill == NULL )
       {
           printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       lost = Mix_LoadWAV( "assets/lost.wav" );
       if( lost == NULL )
       {
           printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       win = Mix_LoadWAV( "assets/lvl_win.wav" );
       if( win == NULL )
       {
           printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }


    window = SDL_CreateWindow("mole Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/pacifico/Pacifico.ttf", 40);

    // Create a surface for the text
    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game  over ! Hit  any  key  to  replay", textColor);

    // Convert the surface to a texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Get the dimensions of the texture
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Set the position of the text
    SDL_Rect textRect = { (SCREEN_HEIGHT - textHeight ) / 2, (SCREEN_WIDTH - textWidth) / 2, textWidth, textHeight };


    // Render the texture to the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);


    // Load background, character, and obstacle images
    SDL_Texture* background_texture = load_texture("assets/background7.png");
    SDL_Texture* character_texture = load_texture("assets/guy.png");
    SDL_Texture* enemy_texture = load_texture("assets/flame4.png");
    SDL_Texture* spike = load_texture("assets/spikee.png");


    SDL_Texture* opened_door_texture= load_texture("assets/open1.png");
    SDL_Texture* closed_door_texture= load_texture("assets/close1.png");


 // int channel;

    // Set the initial position and state of the character

        // Load background music and sound effect
    Mix_Music* bg_music = Mix_LoadMUS("assets/m1.mp3");
     //Mix_Chunk* diedsong = Mix_LoadWAV("assets/died.wav");
     //Mix_Chunk* jump = Mix_LoadWAV("assets/jump.wav");



    // Play background music on loop

    // Run the game loop
    int character_x = 0;
    int spike_x=SCREEN_WIDTH-300;;
    int spike_x_direction=-2;
    int spike2_x=SCREEN_WIDTH-400;;
    int spike2_x_direction=-2;
    int spike3_x=SCREEN_WIDTH-500;;
    int spike3_x_direction=-2;
    int character_y = -100;
    int character_vy = 0;
    int is_jumping = 0;
    int is_dead = 0;
    int is_enemy2_dead=0;

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    // Set the position of the obstacle
    int enemy_x = 75;
    int enemy_y = 100;
    int enemy2_x = 75;
    int enemy2_y = 0;
    int enemy2_vy = 0;

    int enemy_vy=0;

    int quit = 0;
    while (!quit) {
        // Handle events
        SDL_Rect spike_rect = { spike_x, SCREEN_HEIGHT - 110,50,50 };
        SDL_Rect spike2_rect = { spike2_x, SCREEN_HEIGHT - 110,50,50 };

        SDL_Rect spike3_rect = { spike3_x, SCREEN_HEIGHT - 110,50,50 };



        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && !is_jumping && !is_dead) {
                    // Start jumping
                    Mix_PlayChannel( -1, jump, 0 );


                    character_vy = JUMP_FORCE;
                    enemy_vy=JUMP_FORCE;
                    enemy2_vy=JUMP_FORCE;

                    is_jumping = 1;
                }
            }
        }
        spike_x+=spike_x_direction;
        spike2_x+=spike2_x_direction;

        spike3_x+=spike3_x_direction;

        if(spike_x==SCREEN_WIDTH-200|| spike_x==75){
            spike_x_direction*=-1;

        }
        if(spike2_x==SCREEN_WIDTH-200|| spike2_x==75){
            spike2_x_direction*=-1;

        }
        if(spike3_x==SCREEN_WIDTH-200|| spike3_x==75){
            spike3_x_direction*=-1;

        }


        // Update the character position and velocity
        character_y += character_vy;
        enemy_y+=enemy_vy;
        enemy2_y+=enemy2_vy;
        enemy_vy+=GRAVITY;
        enemy2_vy+=GRAVITY;
        character_vy += GRAVITY;

        // Check if the character hits the ground
        if (character_y >= SCREEN_HEIGHT - 100) {
            character_y = SCREEN_HEIGHT - 100;
            enemy2_y = SCREEN_HEIGHT - 100;

            character_vy = 0;
            is_jumping = 0;
            enemy2_vy=0;
        }
        if (enemy_y >= SCREEN_HEIGHT - 440) {
            enemy_y = SCREEN_HEIGHT - 440;

            enemy_vy=0;
            is_jumping = 0;
        }

        // Move the character left or right
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && !is_dead) {
            if (!(character_x<0)){
                character_x -= CHARACTER_SPEED;
                enemy_x -= CHARACTER_SPEED;
                enemy2_x -= CHARACTER_SPEED;


            }

        }else if (state[SDL_SCANCODE_RIGHT] && !is_dead) {
            if (character_x<SCREEN_WIDTH){
                character_x += CHARACTER_SPEED;
                if(!is_enemy2_dead){
                    enemy2_x += CHARACTER_SPEED;

                }



            }
        }

        // Check if the character or the enemy  hits the obstacle
        SDL_Rect character_rect = { character_x, character_y, 10, 10 };
        SDL_Rect enemy2_rect = { enemy2_x, enemy2_y, 32, 32 };


        if (intersect_rects(character_rect, spike_rect)|| intersect_rects(character_rect, spike2_rect) || intersect_rects(character_rect, spike3_rect)) {
            Mix_PlayChannel( -1, lost, 0 );

            is_dead = 1;




        }


        if (intersect_rects(enemy2_rect, spike_rect)|| intersect_rects(enemy2_rect, spike2_rect) || intersect_rects(enemy2_rect, spike3_rect)) {
            Mix_PlayChannel( -1, kill, 0 );

            is_enemy2_dead = 1;
            enemy2_x=0;

        }




        // Clear the screen and draw the background and character
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect = { 0, 0, 0, 0 };






        draw_texture(background_texture, rect);
        draw_texture(character_texture,  character_rect);
        draw_texture(spike,spike_rect);
        draw_texture(spike,spike2_rect);

        draw_texture(spike,spike3_rect);


        SDL_RenderPresent(renderer);




        SDL_Rect rect1 = { SCREEN_WIDTH-95, SCREEN_HEIGHT - 172,100,100 };


           if(!is_enemy2_dead ){

                draw_texture(enemy_texture,enemy2_rect);

                draw_texture(closed_door_texture,rect1);

            }





         if(is_enemy2_dead){
            draw_texture(opened_door_texture,rect1);
            enemy_y=1;
            enemy_x=1;

            if (intersect_rects(character_rect, rect1)){
                SDL_Surface* textSurface4 = TTF_RenderText_Solid(font, "YOU  WON  CONGRATS !!!!!!!!!!", textColor);
                SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface4);
                SDL_QueryTexture(textTexture1, NULL, NULL, &textWidth, &textHeight);
                SDL_RenderCopy(renderer, textTexture1, NULL, &textRect);
                SDL_RenderPresent(renderer);
                quit = 1;
                Mix_PlayChannel( -1, win, 0 );

                SDL_Delay(3000);
                return 1;


            }


        }

        if ( !quit ){
            draw_texture(character_texture,  character_rect);
        }

        // Draw the obstacle if the character is not dead


        // Update the screen
        SDL_RenderPresent(renderer);

        // Wait for a short time
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( gMusic, -1 );
        }
        //If music is being played

        SDL_Delay(10);




        while (is_dead) {
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_RenderPresent(renderer);
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_KEYDOWN){
                    is_dead=0;
                    character_x = 0;
                    enemy2_x=75;
                     enemy_y = SCREEN_HEIGHT - 100;
                     character_y = SCREEN_HEIGHT - 100;
                     enemy_vy=0;
                     character_vy = 0;
                     is_enemy2_dead=0;
                     is_jumping = 0;

                      spike_x=SCREEN_WIDTH-200;;
                      spike_x_direction=-2;
                      spike2_x=SCREEN_WIDTH-300;;
                      spike2_x_direction=-2;
                      spike3_x=SCREEN_WIDTH-400;;
                      spike3_x_direction=-2;

                    // Set the position of the obstacle

                }

                SDL_Delay(50);

            }
            SDL_Delay(50);
        }
    }

    // Clean up and exit
    Mix_FreeMusic(bg_music);
    //Free the sound effects
    Mix_FreeChunk( jump );
    Mix_FreeChunk( kill );
    Mix_FreeChunk( lost );
    Mix_FreeChunk( win );
    jump = NULL;
    kill = NULL;
    lost = NULL;
    win = NULL;
    Mix_FreeMusic( gMusic );


    Mix_CloseAudio();
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    return 0;

}


int menu() {



    // Initialize SDL2 and create a window and renderer
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) ;
        IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );

    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *jump = NULL;
    Mix_Chunk *kill = NULL;
    Mix_Chunk *lost = NULL;
    Mix_Chunk *win = NULL;
    //Load music
       gMusic = Mix_LoadMUS( "assets/m1.wav" );
       if( gMusic == NULL )
       {
           printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       //Load sound effects
       jump = Mix_LoadWAV( "assets/jump.wav" );
       if( jump == NULL )
       {
           printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );

       }

       kill = Mix_LoadWAV( "assets/enemy_killed.wav" );
       if( kill == NULL )
       {
           printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       lost = Mix_LoadWAV( "assets/lost.wav" );
       if( lost == NULL )
       {
           printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       win = Mix_LoadWAV( "assets/lvl_win.wav" );
       if( win == NULL )
       {
           printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }


    window = SDL_CreateWindow("mole Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/pacifico/Pacifico.ttf", 40);

    // Create a surface for the text
    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game  over ! Hit  any  key  to  replay", textColor);

    // Convert the surface to a texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Get the dimensions of the texture
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Set the position of the text
    SDL_Rect textRect = { (SCREEN_HEIGHT - textHeight ) / 2, (SCREEN_WIDTH - textWidth) / 2, textWidth, textHeight };


    // Render the texture to the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);


    // Load background, character, and obstacle images
    int i=0;
    int max=3;
    char arr[3][30] = {"assets/menuplay.png","assets/menu.png","assets/menuplay.png"};
    SDL_Texture* background_texture = load_texture(arr[0]);
    SDL_Texture* character_texture = load_texture("assets/guy.png");
    SDL_Texture* enemy_texture = load_texture("assets/flame4.png");



 // int channel;

    // Set the initial position and state of the character

        // Load background music and sound effect
    Mix_Music* bg_music = Mix_LoadMUS("assets/m1.mp3");
     //Mix_Chunk* diedsong = Mix_LoadWAV("assets/died.wav");
     //Mix_Chunk* jump = Mix_LoadWAV("assets/jump.wav");



    // Play background music on loop

    // Run the game loop

    int is_jumping = 0;
    int is_dead = 0;

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    // Set the position of the obstacle



    int quit = 0;
    while (!quit) {
        // Handle events




        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && !is_jumping && !is_dead) {
                    // Start jumping
                    Mix_PlayChannel( -1, jump, 0 );
                    i++;
                    if (i>max-1){
                        return 1;
                    }
                    background_texture = load_texture(arr[i]);



                }
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect = { 0, 0, 0, 0 };






        draw_texture(background_texture, rect);



        SDL_RenderPresent(renderer);

    }

    // Clean up and exit
    Mix_FreeMusic(bg_music);
    //Free the sound effects
    Mix_FreeChunk( jump );
    Mix_FreeChunk( kill );
    Mix_FreeChunk( lost );
    Mix_FreeChunk( win );
    jump = NULL;
    kill = NULL;
    lost = NULL;
    win = NULL;
    Mix_FreeMusic( gMusic );


    Mix_CloseAudio();
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    return 0;
}
int endgame() {



    // Initialize SDL2 and create a window and renderer
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) ;
        IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );

    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *jump = NULL;
    Mix_Chunk *kill = NULL;
    Mix_Chunk *lost = NULL;
    Mix_Chunk *win = NULL;
    //Load music
       gMusic = Mix_LoadMUS( "assets/m1.wav" );
       if( gMusic == NULL )
       {
           printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       //Load sound effects
       jump = Mix_LoadWAV( "assets/jump.wav" );
       if( jump == NULL )
       {
           printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );

       }

       kill = Mix_LoadWAV( "assets/enemy_killed.wav" );
       if( kill == NULL )
       {
           printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       lost = Mix_LoadWAV( "assets/lost.wav" );
       if( lost == NULL )
       {
           printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }

       win = Mix_LoadWAV( "assets/lvl_win.wav" );
       if( win == NULL )
       {
           printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       }


    window = SDL_CreateWindow("mole Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/pacifico/Pacifico.ttf", 40);

    // Create a surface for the text
    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game  over ! Hit  any  key  to  replay", textColor);

    // Convert the surface to a texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Get the dimensions of the texture
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Set the position of the text
    SDL_Rect textRect = { (SCREEN_HEIGHT - textHeight ) / 2, (SCREEN_WIDTH - textWidth) / 2, textWidth, textHeight };


    // Render the texture to the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);


    //ici el end game background fi blaset em menuplay
    SDL_Texture* background_texture = load_texture("assets/menuplay.png");
    SDL_Texture* character_texture = load_texture("assets/guy.png");
    SDL_Texture* enemy_texture = load_texture("assets/flame4.png");



 // int channel;

    // Set the initial position and state of the character

        // Load background music and sound effect
    Mix_Music* bg_music = Mix_LoadMUS("assets/m1.mp3");
     //Mix_Chunk* diedsong = Mix_LoadWAV("assets/died.wav");
     //Mix_Chunk* jump = Mix_LoadWAV("assets/jump.wav");



    // Play background music on loop

    // Run the game loop

    int is_jumping = 0;
    int is_dead = 0;

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    // Set the position of the obstacle



    int quit = 0;
    while (!quit) {
        // Handle events




        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && !is_jumping && !is_dead) {
                    // Start jumping





                }
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect = { 0, 0, 0, 0 };






        draw_texture(background_texture, rect);



        SDL_RenderPresent(renderer);
        SDL_Delay(5000);

    }

    // Clean up and exit
    Mix_FreeMusic(bg_music);
    //Free the sound effects
    Mix_FreeChunk( jump );
    Mix_FreeChunk( kill );
    Mix_FreeChunk( lost );
    Mix_FreeChunk( win );
    jump = NULL;
    kill = NULL;
    lost = NULL;
    win = NULL;
    Mix_FreeMusic( gMusic );


    Mix_CloseAudio();
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    return 0;
}



int main(int argc, char* argv[]) {

    (void) argc;
    (void) argv;
    menu();
    Level1();
    Level2();
    Level3();
    endgame();




    return 0;
}













