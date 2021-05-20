#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <box2d/box2d.h>
#include <vector>

#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "Player.hpp"

constexpr int WINDOW_WIDTH_PIXELS = 880;
constexpr int WINDOW_HEIGHT_PIXELS = 620;
constexpr int GRAVITY = 20;
constexpr float WINDOW_WIDTH = 10.0;
constexpr uint32 VELOCITY_ITERATIONS = 6;
constexpr uint32 POSITION_ITERATIONS = 2;
constexpr unsigned int PIXELS_PER_UNIT = WINDOW_WIDTH_PIXELS / WINDOW_WIDTH;

bool gameRunning = true;
//SDL_Event event; //event polling

int main() {
	//std::cout << "hi" << std::endl;

	// starting sdl
	if(SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "SDL2 failed :/ err" << SDL_GetError() << std::endl;
	}
	if(!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "SDL2 image failed err" << SDL_GetError() << std::endl;
	}

	//open window
	RenderWindow window("myGame", WINDOW_WIDTH_PIXELS, WINDOW_HEIGHT_PIXELS);	
	
	//load textures
	SDL_Texture* dogTex = window.loadTexture("res/dog.png");
	SDL_Texture* crocTex = window.loadTexture("res/croc-Sheet.png");

	//create image entity
	Entity dogEnt(Vector2f(0,0),400,10,dogTex);
	Entity crocEnt(Vector2f(16,16),16,16,crocTex); 

	Player player(&window,&crocEnt);

	b2World world(b2Vec2(0.0f, GRAVITY));	

  b2Body* groundBody;     // Ground
	//{
		b2BodyDef groundBodyDef;
		groundBodyDef.type = b2_dynamicBody;
		groundBodyDef.position.Set(-20.0, 150.0);
		groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(400, 10);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygonShape;
		fixtureDef.density = 0.0f;
		fixtureDef.restitution = 0.5f;
		fixtureDef.friction = 0.8f;
		groundBody->CreateFixture(&fixtureDef);
	//}

	b2Body* body;
	{
		// Falling box
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(WINDOW_WIDTH_PIXELS/4, 12.0f);
		bodyDef.angle = -0.2;
		body = world.CreateBody(&bodyDef);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(8,8);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.8f;
		fixtureDef.restitution = 0.5f;
		body->CreateFixture(&fixtureDef);
	}
	b2Vec2 bodypos = body->GetPosition();
	
	uint64_t loops = 0;
	uint64_t slower = 0;
	uint32 current_time, last_time;
	float step;
	last_time = SDL_GetTicks();

	while(gameRunning) {
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type)
            {
            case SDL_QUIT:
								gameRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
								{
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                		//std::cout << "key up down" << std::endl; 
										player.onUp = true;	
										break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    player.onLeft = true;
										break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
										player.onDown = true;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
										player.onRight = true;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                		//std::cout << "key up up" << std::endl; 
										player.onUp = false;
										break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    player.onLeft = false;
										break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
										player.onDown = false;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
										player.onRight = false;
                    break;
                }
                break;
            }
		}

		current_time = SDL_GetTicks();

		if(current_time != last_time) {	
			step = ((current_time - last_time) / 1000.0);
			last_time = current_time;


      world.Step(step, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
      b2Vec2 position = body->GetPosition();
			double bangle = body->GetAngle(); 

			std::cout << position.x << " " << position.y << std::endl;

			window.clear();
			
			dogEnt.setPos(Vector2f(-20,150));
			window.render(dogEnt);
			
			player.Update(&loops);
			crocEnt.setPos(Vector2f(position.x+4,position.y+4));
			window.renderSpriteFrame(crocEnt,player.idle,player.facing,player.slower%4,bangle*57.4);
			window.display();

			loops++;
		}
		

	}

	window.cleanUp();
	SDL_Quit();
	
	return 0;
}
