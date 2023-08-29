#include "Level.h"

bool Level::load(char fn[], EntityFactory* factory)
{
    sprintf(filename, fn);

    ifstream in(filename);

    if(!in.good())
    {
        return false;
    }

    char mapFilename[128];
    char mapTilesFilename[128];

    in>>mapFilename;
    in>>mapTilesFilename;
    in>>spawnX;
    in>>spawnY;

    if(!map.load(mapFilename, mapTilesFilename))
    {
        in.close();
        return false;
    }

    factory->setMap(&map);

    boss = NULL;

    while(!in.eof())
    {
        parseLine(&in, factory);
    }

    in.close();

    return true;
}

void Level::parseLine(ifstream* in, EntityFactory* f)
{
    factory = f;

    char command[64];
    (*in)>>command;

    if(!strcmp(command, "alien_scout"))
    {
        int x;
        int y;

        (*in)>>x;
        (*in)>>y;

        scene.addNode(f->makeEntity(ENTITY_ALIEN_SCOUT, x, y));
    }

    if(!strcmp(command, "alien_boss"))
    {
        int x;
        int y;

        (*in)>>x;
        (*in)>>y;

        boss = (BossEntity*)f->makeEntity(ENTITY_BOSS, x, y);
        scene.addNode(boss);
    }

    if(!strcmp(command, "checkpoint"))
    {
        int x;
        int y;

        (*in)>>x;
        (*in)>>y;

        scene.addNode(f->makeEntity(ENTITY_CHECKPOINT, x, y));
    }
}

void Level::free()
{
    scene.removeNode(NULL);
    map.free();
}

void Level::reset()
{
    std::list<SceneNode*>* nodes = getScene()->getNodes();

    for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
    {
        if((*it)->getID() != ENTITY_PLAYER)
        {
            (*it)->remove();
        }
    }

    ifstream in(filename);

    if(!in.good())
    {
        return;
    }

    char mapFilename[128];
    char mapTilesFilename[128];

    in>>mapFilename;
    in>>mapTilesFilename;
    in>>spawnX;
    in>>spawnY;

    boss = NULL;

    while(!in.eof())
    {
        parseLine(&in, factory);
    }

    in.close();
}

void Level::update()
{
    scene.update();
}

void Level::draw(Rectangle* view, Graphics* g)
{
    map.draw(1, view->getX(), view->getY(), g);
    scene.draw(view, g);
}

BossEntity* Level::getBoss()
{
    return boss;
}

Map* Level::getMap()
{
    return &map;
}

Scene* Level::getScene()
{
    return &scene;
}

int Level::getSpawnX()
{
    return spawnX;
}

int Level::getSpawnY()
{
    return spawnY;
}
