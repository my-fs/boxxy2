#pragma once //make sure file is only copied to main file once
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

//#include "Entity.hpp"

class RenderWindow {
    public:
        RenderWindow(const char* p_title, int p_w, int p_h)
        :window(NULL), renderer(NULL) {
            window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
            
            if(window == NULL)
            {
                std::cout << "Window failed to init err " << SDL_GetError() << std::endl;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // if GPU is present use that over CPU
        };
        
        //a SDL_Texture pointer is an address to where the image texture is loaded into memory on the GPU. If no GPU is preset it is stored on RAM
        SDL_Texture* loadTexture(const char* p_filePath) {
            SDL_Texture* texture = NULL;
            texture = IMG_LoadTexture(renderer, p_filePath);

            if(texture == NULL) {
                std::cout << "Failed to load texture err: " << SDL_GetError() << std::endl;
            }

            return texture;
        }

        void cleanUp(){
            SDL_DestroyWindow(window);
        }

        void clear(){
            SDL_RenderClear(renderer);
        }

        void render(Entity& p_entity)
        {
            // a rect is basically just a set of 4 ints
            SDL_Rect src;
            src.x = p_entity.getCurrentFrame().x; // start looking at 0,0
            src.y = p_entity.getCurrentFrame().y;
            src.w = p_entity.getCurrentFrame().w; // real size of the image, if its smaller it will crop
            src.h = p_entity.getCurrentFrame().h;

            SDL_Rect dst; // destination where to place texture
            dst.x = p_entity.getPos().x * 2;
            dst.y = p_entity.getPos().y * 2;
            dst.w = p_entity.getCurrentFrame().w * 2; // we can scale to image if we want
            dst.h = p_entity.getCurrentFrame().h * 2;
            SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
        }

        void renderSpriteFrame(Entity& p_entity,bool idle, bool facing, int p_aniFrame, double angle) {
            // a rect is basically just a set of 4 ints

            int frame = 0;
            if(idle){
                frame = p_aniFrame;
            }

            SDL_Rect src;
            src.x = p_entity.getCurrentFrame().x + (16 * frame);
            src.y = p_entity.getCurrentFrame().y;
            src.w = p_entity.getCurrentFrame().w;
            src.h = p_entity.getCurrentFrame().h;

            SDL_Rect dst; // destination where to place texture
            dst.x = p_entity.getPos().x * 2;
            dst.y = p_entity.getPos().y * 2;
            dst.w = p_entity.getCurrentFrame().w * 2; // we can scale to image if we want
            dst.h = p_entity.getCurrentFrame().h * 2;

            //double angle = 0;
            //const SDL_Point *myPoint = {p_entity.getPos().x*4,p_entity.getPos().y*4};
            SDL_RendererFlip flip;
            if(facing){
                flip = SDL_FLIP_HORIZONTAL;
            } else {
                flip = SDL_FLIP_NONE;
            }
            SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, angle, NULL, flip);
        }

        void display() {
            SDL_RenderPresent(renderer);
        }

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
