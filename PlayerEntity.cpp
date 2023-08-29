#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(Image* image, Map* m, Rectangle* c, int x, int y, EntityFactory* f) :
    MapNode(ENTITY_PLAYER, x - ENTITY_WIDTH/2,
            y - ENTITY_HEIGHT/2,
            ENTITY_WIDTH, ENTITY_HEIGHT, true, m)
{
    sprite.setImage(image);

    camera = c;
    factory = f;
    xVel = yVel = 0;
    gunCooldown = 0;
    frame_change = 0;
    health = 100;
    upShoot = false;
    downShoot = true;
    rightShoot = false;
    leftShoot = false;
}

PlayerEntity::~PlayerEntity()
{

}

void PlayerEntity::moveUp()
{
    move(0, yVel);
    yVel-=ACCEL;
}

void PlayerEntity::moveDown()
{
    move(0, yVel);
    yVel+=ACCEL;
}

void PlayerEntity::moveLeft()
{
    move(xVel, 0);
    xVel-=ACCEL;
}

void PlayerEntity::moveRight()
{
    move(xVel, 0);
    xVel+=ACCEL;
}

void PlayerEntity::respawn()
{
    setX(startX);
    setY(startY);
    xVel = 0;
    yVel = 0;
    sprite.setFrame(1);
    health = 100;
}

void PlayerEntity::setSpawn(int x, int y)
{
    startX = x;
    startY = y;
}

int PlayerEntity::getSpawnX()
{
    return startX;
}

void PlayerEntity::update()
{
    if(health <= 0)
        return;

    gunCooldown--;

    frame_change--;

    if(frame_change < 0)
        frame_change = FRAME_CHANGE_TIME;

    if(xVel > MAX_VEL)
        xVel = MAX_VEL;

    if(xVel < -MAX_VEL)
        xVel = -MAX_VEL;

    if(yVel > MAX_VEL)
        yVel = MAX_VEL;

    if(yVel < -MAX_VEL)
        yVel = -MAX_VEL;

    if(yVel > 0)
    {
        yVel--;
        if(frame_change < FRAME_CHANGE_TIME/3)
            sprite.setFrame(8);
        else if(frame_change < FRAME_CHANGE_TIME*2/3)
            sprite.setFrame(7);
        else
            sprite.setFrame(6);
        upShoot = true;
        downShoot = false;
        leftShoot = false;
        rightShoot = false;
    }

    if(yVel < 0)
    {
        yVel++;
        if(frame_change < FRAME_CHANGE_TIME/3)
            sprite.setFrame(2);
        else if(frame_change < FRAME_CHANGE_TIME*2/3)
            sprite.setFrame(1);
        else
            sprite.setFrame(0);
        upShoot = false;
        downShoot = true;
        leftShoot = false;
        rightShoot = false;
    }

    if(xVel > 0)
    {
        xVel--;
        if(frame_change < FRAME_CHANGE_TIME/3)
            sprite.setFrame(5);
        else if(frame_change < FRAME_CHANGE_TIME*2/3)
            sprite.setFrame(4);
        else
            sprite.setFrame(3);
        upShoot = false;
        downShoot = false;
        leftShoot = false;
        rightShoot = true;
    }

    if(xVel < 0)
    {
        xVel++;
        if(frame_change < FRAME_CHANGE_TIME/3)
            sprite.setFrame(11);
        else if(frame_change < FRAME_CHANGE_TIME*2/3)
            sprite.setFrame(10);
        else
            sprite.setFrame(9);
        upShoot = false;
        downShoot = false;
        leftShoot = true;
        rightShoot = false;
    }

    sprite.update();

    //setY(getY() + yVel);
    //setX(getX() + xVel);

    if(getY() <= camera->getY())
        setY(camera->getY());

    if(getX() <= camera->getX())
        setX(camera->getX());

    if(getY2() >= camera->getY2())
        setY2(camera->getY2());

    if(getX2() >= camera->getX2())
        setX2(camera->getX2());

    if(overlapsMap())
    {
        getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));

        for(int i = 0; i < 10; i++)
            getScene()->addNode(factory->makeEntity(ENTITY_SILENT_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));

        //health = 0;
    }

    if(health < 30)
        getScene()->addNode(factory->makeEntity(ENTITY_SMALL_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));
}

void PlayerEntity::damage(int d)
{
    health -= d;

    if(health < 0)
        health = 0;

    for(int i = 0; i < 5; i++)
        getScene()->addNode(factory->makeEntity(ENTITY_SMALL_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));
}

int PlayerEntity::getHealth()
{
    return health;
}

void PlayerEntity::shoot()
{
    if(gunCooldown <= 0)
    {
        if(rightShoot)
            getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET_RIGHT, getX2(), getCenterY()));
        if(leftShoot)
            getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET_LEFT, getX(), getCenterY()));
        if(upShoot)
            getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET_UP, getCenterX(), getY2()));
        if(downShoot)
            getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET_DOWN, getCenterX(), getY()));

        gunCooldown = GUN_COOLDOWN_TIME;
    }
}

void PlayerEntity::draw(Rectangle* view, Graphics* g)
{
    if(health <= 0)
        return;

    sprite.draw(getCenterX() - sprite.getWidth()/2 - view->getX(), getCenterY() - sprite.getHeight()/2 - view->getY(), g);
}
