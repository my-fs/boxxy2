class Player {
    public: 
        Player(RenderWindow *window, Entity *p_entity) // defrencing entity
        :entity(p_entity)
        {
            onRight = false;
            onLeft = false;
            onUp = false;
            onDown = false;
            facing = false;

            //test
           // b2Body* body;
           // {
           //     // Falling box
           //     b2BodyDef bodyDef;
           //     bodyDef.type = b2_dynamicBody;
           //     bodyDef.position.Set(-4.0f, 12.0f);
           //     //bodyDef.angle = 3.1415f / 3.0;
           //     body = world.CreateBody(&bodyDef);
           //     b2PolygonShape dynamicBox;
           //     dynamicBox.SetAsBox(0.5, 0.5);
           //     b2FixtureDef fixtureDef;
           //     fixtureDef.shape = &dynamicBox;
           //     fixtureDef.density = 1.0f;
           //     fixtureDef.friction = 0.8f;
           //     fixtureDef.restitution = 0.5f;
           //     body->CreateFixture(&fixtureDef);
           // }
           // b2Vec2 bodypos = body->GetPosition();
            //std::cout << p_entity->getPos().x << std::endl; // entity info
        }
        int slower;
        void Update(uint64_t *tick){
            if(*tick%16==0) {
                slower++;
            }
            //std::cout << *tick << " " << onUp << std::endl;
            if(onUp){
                entity->setPos(Vector2f(0,entity->getPos().y-1));
            }
            if(onDown){
                entity->setPos(Vector2f(0,entity->getPos().y+1));
            }
            if(onRight){
                facing = true;
                //b2Vec2 v = body->GetLinearVelocity();
                //v.x = -2;
                //body->SetLinearVelocity( v );
            }
            if(onLeft){
                facing = false;
            }
            if(onUp||onDown||onRight||onLeft){
                idle = true;
            } else {
                idle = false;
            }
        }
        bool onRight;
        bool onLeft;
        bool onUp;
        bool onDown;
        bool facing;
        bool idle;
    private:
        Entity *entity;
        RenderWindow *window;
};
