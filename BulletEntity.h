#ifndef BULLETENTITY_H
#define BULLETENTITY_H

#include "Core/Image.h"
#include "Core/MapNode.h"

#include "EntityDef.h"
#include "EntityFactory.h"

class EntityFactory;

class BulletEntity : public MapNode
{
private:
    static const int ENTITY_WIDTH = 12;
    static const int ENTITY_HEIGHT = 12;
    static const int FRAME_UP = 0;
    static const int FRAME_RIGHT = 1;
    static const int FRAME_DOWN = 2;
    static const int FRAME_LEFT = 3;
    static const int SPEED = 20;
    int speedX = SPEED;
    int speedY = SPEED;
    int frameN;

    bool enemyBullet;
    EntityFactory* factory;
    Image* image;
    Rectangle* camera;
    Sound* sound;
public:
    BulletEntity(Image* i, Sound* s, Map* m, Rectangle* c, EntityFactory* f, int x, int y, bool enemy, int aim);
    ~BulletEntity();
    void update();
    void draw(Rectangle* view, Graphics* g);
};

#endif

