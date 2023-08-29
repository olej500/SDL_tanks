#ifndef PLAYER2_H
#define PLAYER2_H

#include "Core/Graphics.h"
#include "Core/Input.h"
#include "PlayerEntity.h"
#include "Level.h"

class Player2
{
private:
    static const int LIFEBAR_WIDTH = 300;
    static const int LIFEBAR_HEIGHT = 30;
    static const int LIFEBAR_X = 970;
    static const int LIFEBAR_Y = 680;
    static const int LIVES_PANEL_X = 970;
    static const int LIVES_PANEL_Y = 620;
    static const int LIVES_SPACING = 115;

    Image lifeCounterImage;
    PlayerEntity* entity;
    Rectangle* camera;
    int deathDelay;
    int lives;
    bool up;
    bool down;
    bool left;
    bool right;
public:
    bool init();
    void free();

    void setEntity(PlayerEntity* n);
    void setCamera(Rectangle* r);
    void update(Input* i, Level* l);
    void draw(Graphics* g);
    void scroll(int x);
    int getLives();
};

#endif
