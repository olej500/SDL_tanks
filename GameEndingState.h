#ifndef GAMEENDINGSTATE_H
#define GAMEENDINGSTATE_H

#include "Core/GameState.h"
#include "Core/Image.h"
#include "Core/Input.h"

#include "Button.h"

class GameEndingState : public GameState
{
private:
    static const int BUTTON_X = 480;
    static const int BUTTON_Y = 400;

    Image backgroundImage;
    Image mainMenuButtonImage;
    Input* input;
    Button mainMenuButton;
    GameState* runState;
public:
    bool init(GameState* r, Input* i);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif

