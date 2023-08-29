#ifndef CHECKPOINTENTITY_H
#define CHECKPOINTENTITY_H

#include "Core/Graphics.h"
#include "Core/SceneNode.h"
#include "EntityDef.h"
#include "PlayerEntity.h"

class CheckpointEntity : public SceneNode
{
private:
    Image* image;
    bool triggered;
public:
    CheckpointEntity(Image* i, int x, int y);
    ~CheckpointEntity();
    void update();
    void draw(Rectangle* view, Graphics* g);
};

#endif
