#include "MainMenuState.h"

bool MainMenuState::init(Input* i, Audio* a, Game* g, RunState* r)
{
    audio = a;
    input = i;
    game = g;
    runState = r;

    if(!background.load("graphics/menus/main/tank_wars.bmp"))
    {
        return false;
    }

    if(!startButtonImage.load("graphics/menus/main/start_game.bmp"))
    {
        return false;
    }

    if(!exitButtonImage.load("graphics/menus/main/exit.bmp"))
    {
        return false;
    }

    if(!song.load("audio/music/menu.mp3"))
    {
        return false;
    }

    startButton.setImage(&startButtonImage);
    exitButton.setImage(&exitButtonImage);

    startButton.setPos(BUTTON_X, BUTTON_Y);
    exitButton.setPos(BUTTON_X, BUTTON_Y+BUTTON_SPACING);

    screenWidth = game->getGraphics()->getWidth();
    screenHeight = game->getGraphics()->getHeight();

    return true;
}

void MainMenuState::free()
{
    audio->stopMusic();
    song.free();
    startButtonImage.free();
    exitButtonImage.free();
    background.free();
}

void MainMenuState::update()
{
    startButton.update(input);
    exitButton.update(input);

    if(!audio->musicPlaying())
    {
        song.play(-1);
    }

    if(startButton.fired())
    {
        if(!runState->init(input, audio, screenWidth, screenHeight))
        {
            runState->free();
            game->end();
        }

        getManager()->addState(runState);
    }

    if(exitButton.fired())
    {
        game->end();
    }
}

void MainMenuState::draw(Graphics* g)
{
    background.draw(0,0,g);
    startButton.draw(g);
    exitButton.draw(g);
}
