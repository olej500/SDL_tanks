#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>

#include "Core/Map.h"
#include "Core/Scene.h"

#include "EntityFactory.h"
#include "BossEntity.h"

using namespace std;

class Level
{
private:
    BossEntity* boss;
    EntityFactory* factory;
    Map map;
    Scene scene;

    int spawnX;
    int spawnY;

    char filename[256];

    void parseLine(ifstream* in, EntityFactory* f);
public:
    bool load(char fn[], EntityFactory* factory);
    void free();
    void reset();

    void update();
    void draw(Rectangle* view, Graphics* g);

    BossEntity* getBoss();
    Map* getMap();
    Scene* getScene();
    int getSpawnX();
    int getSpawnY();
};

#endif
