#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Core/Game.h"
#include "Core/GameState.h"
#include "Core/Graphics.h"
#include "Core/Image.h"
#include "Core/Input.h"
#include "Core/Music.h"

#include "Button.h"
#include "RunState.h"

class MainMenuState : public GameState
{
private:
    const static int BUTTON_X = 150;
    const static int BUTTON_Y = 400;
    const static int BUTTON_SPACING = 100;

    int screenWidth;
    int screenHeight;

    Button startButton;
    Button exitButton;
    Game* game;
    Image background;
    Image startButtonImage;
    Image exitButtonImage;
    Music song;
    Audio* audio;
    Input* input;
    RunState* runState;
public:
    bool init(Input* i, Audio* a, Game* g, RunState* r);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
