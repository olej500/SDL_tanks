#include "CreditsState.h"

bool CreditsState::init(Input* i)
{
    input = i;

    if(!backgroundImage.load("graphics/menus/credits/background.bmp"))
        return false;

    return true;
}

void CreditsState::free()
{
    backgroundImage.free();
}

void CreditsState::update()
{
    if(input->keyDown(SDLK_SPACE))
    {
        free();
        getManager()->popState();
    }
}

void CreditsState::draw(Graphics* g)
{
    backgroundImage.draw(0,0,g);
}


