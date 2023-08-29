#include "GameEndingState.h"

bool GameEndingState::init(GameState* r, Input* i)
{
    runState = r;
    input = i;

    if(!mainMenuButtonImage.load("graphics/menus/ending/main_menu.bmp"))
        return false;

    if(!backgroundImage.load("graphics/menus/ending/blue_wins.bmp"))
        return false;

    mainMenuButton.setPos(BUTTON_X, BUTTON_Y);
    mainMenuButton.setImage(&mainMenuButtonImage);

    return true;
}

void GameEndingState::free()
{
    mainMenuButtonImage.free();
    backgroundImage.free();
}

void GameEndingState::update()
{
    mainMenuButton.update(input);

    if(mainMenuButton.fired())
    {
        runState->free();
        getManager()->popState();
        getManager()->popState();
    }
}

void GameEndingState::draw(Graphics* g)
{
    backgroundImage.draw(0,0,g);
    mainMenuButton.draw(g);
}

