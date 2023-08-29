#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H


#include "Core/Image.h"
#include "Core/Rectangle.h"
#include "Core/SceneNode.h"
#include "Core/Sound.h"

#include "EntityDef.h"

#include "AlienScoutEntity.h"
#include "BossEntity.h"
#include "BulletEntity.h"
#include "CheckpointEntity.h"
#include "ExplosionEntity.h"
#include "PlayerEntity.h"

class ExplosionEntity;
class PlayerEntity;

class EntityFactory
{
private:
    Rectangle* camera;
    Image alienScoutImage;
    Image bossImage;
    Image bulletImage;
    Image checkpointImage;
    Image explosionImage;
    Image explosionSmallImage;
    Image playerImage;
    Image playerImage2;
    Map* map;
    Sound explosionSound;
    Sound bulletSound;
public:
    EntityFactory();
    ~EntityFactory();
    bool init();
    void free();
    void setCamera(Rectangle* c);
    void setMap(Map* m);
    SceneNode* makeEntity(int e, int x, int y);
};

#endif
