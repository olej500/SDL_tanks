#include "PauseState.h"

bool PauseState::init(GameState* r, Input* i)
{
    runState = r;
    input = i;

    if(!continueButtonImage.load("graphics/menus/pause/continue.bmp"))
        return false;

    if(!exitButtonImage.load("graphics/menus/pause/exit.bmp"))
        return false;

    if(!overlayImage.load("graphics/menus/pause/game_paused.bmp"))
        return false;

    continueButton.setPos(BUTTON_X, BUTTON_Y);
    exitButton.setPos(BUTTON_X, BUTTON_Y+BUTTON_SPACING);

    continueButton.setImage(&continueButtonImage);
    exitButton.setImage(&exitButtonImage);

    return true;
}

void PauseState::free()
{
    continueButtonImage.free();
    exitButtonImage.free();
    overlayImage.free();
}

void PauseState::update()
{
    continueButton.update(input);
    exitButton.update(input);

    if(continueButton.fired())
    {
        getManager()->popState();
    }

    if(exitButton.fired())
    {
        runState->free();
        getManager()->popState();
        getManager()->popState();
    }
}

void PauseState::draw(Graphics* g)
{
    runState->draw(g);
    overlayImage.draw(0,0,g);
    continueButton.draw(g);
    exitButton.draw(g);
}
