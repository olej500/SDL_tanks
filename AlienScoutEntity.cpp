#include "AlienScoutEntity.h"

AlienScoutEntity::AlienScoutEntity(Image* i, Rectangle* c, EntityFactory* f, int x, int y) :
    SceneNode(ENTITY_ENEMY, x-ENTITY_WIDTH/2, y-ENTITY_HEIGHT/2, ENTITY_WIDTH, ENTITY_HEIGHT)
{
    image = i;
    camera = c;
    factory = f;
    cycle = 0;
    startY = y;
    active = false;
    health = 10;
}

AlienScoutEntity::~AlienScoutEntity()
{

}

void AlienScoutEntity::update()
{
    if(health <= 0)
    {
        remove();
        return;
    }

    if(active)
    {
        cycle+=PI/20;
        if(cycle > 2*PI)
            cycle = 0;

        setY(startY + sin(cycle)*ENTITY_HEIGHT);
        setX(getX()-ENTITY_SPEED);

        if(!overlaps(*camera))
            remove();

        std::list<SceneNode*>* nodes = getScene()->getNodes();

        for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_PLAYER && overlaps(**it))
            {
                PlayerEntity* player = (PlayerEntity*)(*it);

                player->damage(5);
                getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getCenterX(), getCenterY()));
                remove();
            }
        }
    }
    else
    {
        if(overlaps(*camera))
            active = true;
    }
}

void AlienScoutEntity::draw(Rectangle* view, Graphics* g)
{
    if(active)
    {
        if(image != NULL)
        {
            int frame = NUM_FRAMES/2 + sin(cycle)*NUM_FRAMES/2;
            image->draw(getCenterX() - getWidth()/2 - view->getX(), getCenterY() - getHeight()/2 - view->getY(), frame, g);
        }
    }
}

void AlienScoutEntity::damage(int d)
{
    health -= d;
}

