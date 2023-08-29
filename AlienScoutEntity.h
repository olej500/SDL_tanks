#ifndef ALIENSCOUTENTITY_H
#define ALIENSCOUTENTITY_H

#include <math.h>

#include "Core/Image.h"
#include "Core/SceneNode.h"

#include "EntityDef.h"
#include "EntityFactory.h"

#define PI 3.14159265

class EntityFactory;

class AlienScoutEntity : public SceneNode
{
private:
    static const int ENTITY_SPEED = 3;
    static const int ENTITY_WIDTH = 100;
    static const int ENTITY_HEIGHT = 100;
    static const int NUM_FRAMES = 7;
    EntityFactory* factory;
    Image* image;
    Rectangle* camera;

    bool active;
    int startY;
    int health;
    float cycle;
public:
    AlienScoutEntity(Image* i, Rectangle* c, EntityFactory* f, int x, int y);
    ~AlienScoutEntity();
    void update();
    void draw(Rectangle* view, Graphics* g);
    void damage(int d);
};

#endif
