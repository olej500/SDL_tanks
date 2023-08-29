#ifndef PLAYERNODE_H
#define PLAYERNODE_H

#include "Core/Rectangle.h"
#include "Core/MapNode.h"
#include "Core/Sprite.h"

#include "EntityDef.h"
#include "EntityFactory.h"

class EntityFactory;

class PlayerEntity : public MapNode
{
private:
    static const int ENTITY_WIDTH = 80;
    static const int ENTITY_HEIGHT = 80;
    static const int ACCEL = 4;
    static const int GUN_COOLDOWN_TIME = 33;
    static const int MAX_VEL = 6;
    static const int NUM_FRAMES = 12;
    static const int FRAME_CHANGE_TIME = 12;

    EntityFactory* factory;
    Sprite sprite;
    Rectangle* camera;

    int xVel;
    int yVel;
    int startX;
    int startY;
    int health;
    int gunCooldown;
    int frame_change;
    bool upShoot;
    bool downShoot;
    bool leftShoot;
    bool rightShoot;
public:
    PlayerEntity(Image* image, Map* m, Rectangle* c, int x, int y, EntityFactory* f);
    ~PlayerEntity();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void shoot();
    void respawn();
    void setSpawn(int x, int y);
    int getSpawnX();

    void damage(int d);
    int getHealth();

    void update();
    void draw(Rectangle* view, Graphics* g);
};

#endif
