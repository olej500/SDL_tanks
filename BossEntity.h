#ifndef BOSSENTITY_H
#define BOSSENTITY_H

#include "Core/Image.h"
#include "Core/SceneNode.h"

#include "EntityDef.h"
#include "EntityFactory.h"

class EntityFactory;

class BossEntity : public SceneNode
{
private:
    static const int ENTITY_SPEED = 5;
    static const int ENTITY_WIDTH = 200;
    static const int ENTITY_HEIGHT = 300;

    static const int STATE_DYING = 0;
    static const int STATE_MOVING = 1;
    static const int STATE_ATTACKING = 2;
    static const int STATE_PANIC = 3;

    EntityFactory* factory;
    Image* image;
    Rectangle* camera;

    bool active;
    int yVel;
    int state;
    int attackCounter;

    int health;
    int panicCounter;
    int deathCounter;

    bool dead;

    void updateDying();
    void updateMoving();
    void updateAttacking();
    void updatePanic();
public:
    BossEntity(Image* i, Rectangle* c, EntityFactory* f, int x, int y);
    ~BossEntity();
    void update();
    void draw(Rectangle* view, Graphics* g);
    void damage(int d);
    int getHealth();
    bool isDead();
};

#endif

