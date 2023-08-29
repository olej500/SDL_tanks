#ifndef RUNSTATE_H
#define RUNSTATE_H

#include "Core/Audio.h"
#include "Core/GameState.h"
#include "Core/Map.h"
#include "Core/Music.h"
#include "Core/Rectangle.h"
#include "Core/Scene.h"

#include "EntityFactory.h"
#include "GameEndingState.h"
#include "GameOverState.h"
#include "Level.h"
#include "Player.h"
#include "Player2.h"
#include "PauseState.h"

class PauseState;

class RunState : public GameState
{
private:
    Image background1;

    Audio* audio;
    Input* input;
    Music song;

    EntityFactory factory;
    GameOverState gameOverState;
    GameEndingState gameEndingState;
    Level level;
    Player player;
    Player2 player2;
    PauseState pauseState;
    Rectangle camera;

    bool loadFiles();
    void freeFiles();
    void drawBackground(Graphics* g);
    bool initLevel();
public:
    bool init(Input* i, Audio* a, int width, int height);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
