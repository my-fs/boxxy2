#include "Math.hpp"

class Entity {
    public:
        Entity(Vector2f p_pos, int w, int h, SDL_Texture* p_tex)
        :pos(p_pos), tex(p_tex) { //memeber init list, looks weird cuz it looks like a function buts is bascially setting those variables to the param values
            currentFrame.x = 0;
            currentFrame.y = 0;
            currentFrame.w = w;
            currentFrame.h = h;
        }
        
        Vector2f& getPos() {
            return pos;
        }
        
        void setPos(Vector2f p_pos) {
           pos = p_pos;
        };
        
        SDL_Texture* getTex() {
            return tex;
        }

        SDL_Rect getCurrentFrame() {
            return currentFrame;
        }

    private:
        Vector2f pos;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};
