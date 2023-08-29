#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "Core/GameState.h"
#include "Core/Image.h"
#include "Core/Input.h"

class CreditsState : public GameState
{
private:
    Image backgroundImage;
    Input* input;
public:
    bool init(Input* i);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
