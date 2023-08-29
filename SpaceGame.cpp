#include "SpaceGame.h"

bool SpaceGame::init()
{
    if(!initSystem("Tankz", SCREEN_WIDTH, SCREEN_HEIGHT, true))
    {
        return false;
    }

    if(!mainMenuState.init(getInput(), getAudio(), this, &runState))
    {
        return false;
    }

    setFPS(60);

    stateManager.addState(&mainMenuState);

    return true;
}

void SpaceGame::free()
{
    mainMenuState.free();
    freeSystem();
}

void SpaceGame::update()
{
    stateManager.update();
}

void SpaceGame::draw(Graphics* g)
{
    stateManager.draw(g);
}
