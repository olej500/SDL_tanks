#include "BulletEntity.h"

BulletEntity::BulletEntity(Image* i, Sound* s, Map* m, Rectangle* c,
    EntityFactory* f, int x, int y, bool enemy, int aim)
    : MapNode(ENTITY_BULLET, x - ENTITY_WIDTH/2, y - ENTITY_HEIGHT/2,
            ENTITY_WIDTH, ENTITY_HEIGHT, true, m)
{
    image = i;
    sound = s;
    enemyBullet = enemy;
    factory = f;
    camera = c;
    s->play();
    if(aim==1)
    {
        speedX = 0;
        speedY = SPEED;
        frameN = 2;
    }
    if(aim==2)
    {
        speedX = SPEED;
        speedY = 0;
        frameN = 1;
    }
    if(aim==3)
    {
        speedX = 0;
        speedY = -SPEED;
        frameN = 0;
    }
    if(aim==4)
    {
        speedX = -SPEED;
        speedY = 0;
        frameN = 3;
    }
}

BulletEntity::~BulletEntity()
{

}

void BulletEntity::update()
{
    setX(getX()+speedX);
    setY(getY()+speedY);

    if(overlapsMap())
    {
        remove();
        getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX(), getY()));
        return;
    }

    if(!camera->overlaps(*this))
        remove();

    if(!enemyBullet)
    {
        std::list<SceneNode*>* nodes = getScene()->getNodes();

        for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_ENEMY && overlaps(**it))
            {
                AlienScoutEntity* alien = (AlienScoutEntity*)(*it);

                alien->damage(5);

                getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX(), getY()));
                remove();
            }

            if((*it)->getID() == ENTITY_BOSS && overlaps(**it))
            {
                BossEntity* boss = (BossEntity*)(*it);

                boss->damage(5);

                getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX(), getY()));
                remove();
            }
        }
    }
    else
    {
        std::list<SceneNode*>* nodes = getScene()->getNodes();

        for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_PLAYER && overlaps(**it))
            {
                PlayerEntity* player = (PlayerEntity*)(*it);

                player->damage(20);
                remove();
            }
        }
    }
}

void BulletEntity::draw(Rectangle* view, Graphics* g)
{
    int x = getCenterX() - image->getFrameWidth()/2;
    int y = getCenterY() - image->getFrameHeight()/2;
    int frame;

    frame = frameN;

    image->draw(x-view->getX(), y-view->getY(), frame, g);
}
