#include "BossEntity.h"

BossEntity::BossEntity(Image* i, Rectangle* c, EntityFactory* f, int x, int y) :
    SceneNode(ENTITY_BOSS, x-ENTITY_WIDTH/2, y-ENTITY_HEIGHT/2, ENTITY_WIDTH, ENTITY_HEIGHT)
{
    image = i;
    camera = c;
    factory = f;

    active = false;
    dead = false;
    yVel = ENTITY_SPEED;

    state = STATE_MOVING;

    health = 500;
    deathCounter = 0;
}

BossEntity::~BossEntity()
{

}

void BossEntity::update()
{
    if(active)
    {
        if(health <= 0)
            state = STATE_DYING;

        switch(state)
        {
            case STATE_MOVING:
                updateMoving();
                break;

            case STATE_ATTACKING:
                updateAttacking();
                break;

            case STATE_PANIC:
                updatePanic();
                break;
            case STATE_DYING:
                updateDying();
                break;
        }
    }
    else
    {
        if(overlaps(*camera))
            active = true;
    }
}

void BossEntity::updateDying()
{
    deathCounter++;

    for(int i = 0; i < rand()%10; i++)
        getScene()->addNode(factory->makeEntity(ENTITY_SILENT_EXPLOSION,
                            getX() + rand()%getWidth(), getY() + rand()%getHeight()));

    setX(getX()+2);

    setX(getX()+2-rand()%4);
    setY(getY()+2-rand()%4);

    if(!overlaps(*camera))
    {
        dead = true;
    }
}

void BossEntity::updateMoving()
{
    setY(getY()+yVel);

    if(getY() < camera->getY())
    {
        yVel = ENTITY_SPEED;
    }

    if(getY2() > camera->getY2())
    {
        yVel = -ENTITY_SPEED;
    }

    if(rand()%100 == 1)
    {
        state = STATE_ATTACKING;
        attackCounter = 0;
    }

    if(health <= 200)
    {
        panicCounter = 0;
        state = STATE_PANIC;
    }
}

void BossEntity::updateAttacking()
{
    attackCounter++;

    if(attackCounter == 10)
    {
        for(int i = 0; i < getHeight(); i+= getHeight()/5)
        {
            getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET, getX(), getY()+i));
        }
    }

    if(attackCounter > 20)
    {
        setY(getY()+yVel);

        if(getY() < camera->getY())
        {
            yVel = ENTITY_SPEED;
        }

        if(getY2() > camera->getY2())
        {
            yVel = -ENTITY_SPEED;
        }
    }

    if(attackCounter == 30)
    {
        for(int i = 0; i < getHeight(); i+= getHeight()/5)
        {
            getScene()->addNode(factory->makeEntity(ENTITY_ALIEN_SCOUT, getX(), getY()+i));
        }
    }

    if(attackCounter >= 50)
    {
        for(int i = 0; i < getHeight(); i+= getHeight()/10)
        {
            getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET, getX(), getY()+i));
        }

        state = STATE_MOVING;
    }
}

void BossEntity::updatePanic()
{
    getScene()->addNode(factory->makeEntity(ENTITY_SILENT_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));

    panicCounter++;

    if(panicCounter > 100)
        panicCounter = 0;


    setY(getY()+yVel);

    if(getY() < camera->getY())
    {
        yVel = ENTITY_SPEED;
    }

    if(getY2() > camera->getY2())
    {
        yVel = -ENTITY_SPEED;
    }

    if(panicCounter %5 != 0)
        return;

    if(health < 0)
    {
        remove();
    }

    if(panicCounter > 10 && panicCounter < 30)
    {
        getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET, getX(), getY()+(rand()%getHeight())));
    }

    if(panicCounter > 30 && panicCounter < 60 && rand()%4)
    {
        getScene()->addNode(factory->makeEntity(ENTITY_ALIEN_SCOUT, getX(), getY()+(rand()%getHeight())));
    }

    if(panicCounter > 60 && panicCounter < 100 && rand()%4)
    {
        getScene()->addNode(factory->makeEntity(ENTITY_ALIEN_SCOUT, getX(), getY()+(rand()%getHeight())));
        getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET, getX(), getY()+(rand()%getHeight())));
    }
}

void BossEntity::draw(Rectangle* view, Graphics* g)
{
    if(active)
    {
        if(image != NULL)
            image->draw(getCenterX() - getWidth()/2 - view->getX(), getCenterY() - getHeight()/2 - view->getY(), g);
    }
}

void BossEntity::damage(int d)
{
    health -= d;
    if(health < 0)
        health = 0;
}

int BossEntity::getHealth()
{
    return health;
}

bool BossEntity::isDead()
{
    return dead;
}
