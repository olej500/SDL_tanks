#include "CheckpointEntity.h"

CheckpointEntity::CheckpointEntity(Image* i, int x, int y)
    : SceneNode(ENTITY_CHECKPOINT, x, y, 1, 1)
{
    image = i;
    triggered = false;
}

CheckpointEntity::~CheckpointEntity()
{

}

void CheckpointEntity::update()
{
    std::list<SceneNode*> *nodes = getScene()->getNodes();

    for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
    {
        if((*it)->getID() == ENTITY_PLAYER)
        {
            PlayerEntity* player = (PlayerEntity*)(*it);

            if(player->getX2() > getX())
            {
                if(player->getSpawnX() < getX())
                {
                    player->setSpawn(getX(), getY());
                    triggered = true;
                }
            }
        }
    }
}

void CheckpointEntity::draw(Rectangle* view, Graphics* g)
{
    if(triggered)
    {
        image->draw(getX() - view->getX()+100, getY() - view->getY(), g);
    }
    else
    {
        g->drawRect(getX()-view->getX(), 0, 2, view->getHeight(), 0, 255, 0);
    }
}
