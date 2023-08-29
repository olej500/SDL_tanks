#include "EntityFactory.h"

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{

}

bool EntityFactory::init()
{
    if(!alienScoutImage.load("graphics/sprites/alien_scout.bmp", 100, 100))
    {
        return false;
    }

    if(!bossImage.load("graphics/sprites/boss.bmp"))
    {
        return false;
    }

    if(!bulletImage.load("graphics/sprites/bullet_all.bmp", 40, 40))
    {
        return false;
    }

    if(!checkpointImage.load("graphics/sprites/checkpoint.bmp"))
    {
        return false;
    }

    if(!explosionImage.load("graphics/sprites/explosion.bmp", 50, 50))
    {
        return false;
    }

    if(!explosionSmallImage.load("graphics/sprites/explosion_small.bmp", 24, 24))
    {
        return false;
    }

    if(!playerImage.load("graphics/sprites/tank_blue.bmp", 80, 80))
    {
        return false;
    }

    if(!playerImage2.load("graphics/sprites/tank_red.bmp", 80, 80))
    {
        return false;
    }

    if(!explosionSound.load("audio/sfx/explosion.wav"))
    {
        return false;
    }

    if(!bulletSound.load("audio/sfx/tank_fire.wav"))
    {
        return false;
    }

    return true;
}

void EntityFactory::free()
{
    alienScoutImage.free();
    bossImage.free();
    bulletImage.free();
    explosionImage.free();
    explosionSmallImage.free();
    playerImage.free();
    explosionSound.free();
    bulletSound.free();
}

void EntityFactory::setCamera(Rectangle* c)
{
    camera = c;
}
void EntityFactory::setMap(Map* m)
{
    map = m;
}

SceneNode* EntityFactory::makeEntity(int e, int x, int y)
{
    switch(e)
    {
        case ENTITY_PLAYER:
            return new PlayerEntity(&playerImage, map, camera, x, y, this);
            break;
        case ENTITY_PLAYER_2:
            return new PlayerEntity(&playerImage2, map, camera, x, y, this);
            break;
        case ENTITY_EXPLOSION:
            return new ExplosionEntity(&explosionImage, &explosionSound, x, y);
            break;
        case ENTITY_SILENT_EXPLOSION:
            return new ExplosionEntity(&explosionImage, NULL, x, y);
            break;
        case ENTITY_SMALL_EXPLOSION:
            return new ExplosionEntity(&explosionSmallImage, NULL, x, y);
            break;
        case ENTITY_PLAYER_BULLET:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, false, 1);
            break;
        case ENTITY_ENEMY_BULLET:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, true, 1);
            break;
        case ENTITY_ENEMY_BULLET_UP:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, true, 1);
            break;
        case ENTITY_ENEMY_BULLET_DOWN:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, true, 3);
            break;
        case ENTITY_ENEMY_BULLET_RIGHT:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, true, 2);
            break;
        case ENTITY_ENEMY_BULLET_LEFT:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, true, 4);
            break;
        case ENTITY_ALIEN_SCOUT:
            return new AlienScoutEntity(&alienScoutImage, camera, this, x, y);
            break;
        case ENTITY_BOSS:
            return new BossEntity(&bossImage, camera, this, x, y);
            break;
        case ENTITY_CHECKPOINT:
            return new CheckpointEntity(&checkpointImage, x, y);
            break;
        default:
            return NULL;
    }
}
