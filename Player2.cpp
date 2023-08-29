#include "Player2.h"

bool Player2::init()
{
    entity = NULL;
    camera = NULL;
    deathDelay = 0;
    lives = 3;
    up, down, left, right = false;

    if(!lifeCounterImage.load("graphics/sprites/tank_icon_out_small.bmp"))
    {
        return false;
    }

    return true;
}

void Player2::free()
{
    lifeCounterImage.free();
}

void Player2::setEntity(PlayerEntity* n)
{
    entity = n;
}

void Player2::setCamera(Rectangle* r)
{
    camera = r;
}

void Player2::update(Input* i, Level* l)
{
    if(entity != NULL)
    {
        if(i->keyHit(SDLK_w))
        {
            up = true;
            down = false;
            left = false;
            right = false;
        }

        if(i->keyHit(SDLK_s))
        {
            down = true;
            up = false;
            left = false;
            right = false;
        }

        if(i->keyHit(SDLK_a))
        {
            left = true;
            down = false;
            up = false;
            right = false;
        }

        if(i->keyHit(SDLK_d))
        {
            right = true;
            down = false;
            left = false;
            up = false;
        }

        if(i->keyUp(SDLK_w))
        {
            up = false;
            if(i->keyDown(SDLK_s))
                down = true;
            if(i->keyDown(SDLK_a))
                left = true;
            if(i->keyDown(SDLK_d))
                right = true;
        }

        if(i->keyUp(SDLK_s))
        {
            down = false;
            if(i->keyDown(SDLK_w))
                up = true;
            if(i->keyDown(SDLK_a))
                left = true;
            if(i->keyDown(SDLK_d))
                right = true;
        }

        if(i->keyUp(SDLK_a))
        {
            left = false;
            if(i->keyDown(SDLK_s))
                down = true;
            if(i->keyDown(SDLK_w))
                up = true;
            if(i->keyDown(SDLK_d))
                right = true;
        }

        if(i->keyUp(SDLK_d))
        {
            right = false;
            if(i->keyDown(SDLK_s))
                down = true;
            if(i->keyDown(SDLK_a))
                left = true;
            if(i->keyDown(SDLK_w))
                up = true;
        }

        if(i->keyDown(SDLK_w) && up)// && (!i->keyDown(SDLK_DOWN)) && (!i->keyDown(SDLK_LEFT)) && (!i->keyDown(SDLK_RIGHT)))
        {
            entity->moveUp();
        }

        if(i->keyDown(SDLK_s) && down)// && (!i->keyDown(SDLK_UP)) && (!i->keyDown(SDLK_LEFT)) && (!i->keyDown(SDLK_RIGHT)))
        {
            entity->moveDown();
        }

        if(i->keyDown(SDLK_a) && left)// && (!i->keyDown(SDLK_RIGHT)) && (!i->keyDown(SDLK_UP)) && (!i->keyDown(SDLK_DOWN)))
        {
            entity->moveLeft();
        }

        if(i->keyDown(SDLK_d) && right)// && (!i->keyDown(SDLK_LEFT)) && (!i->keyDown(SDLK_UP)) && (!i->keyDown(SDLK_DOWN)))
        {
            entity->moveRight();
        }

        if(i->keyDown(SDLK_LCTRL))
        {
            entity->shoot();
        }

        if(entity->getHealth() <= 0)
        {
            if(deathDelay == 0)
            {
                lives--;
            }

            deathDelay++;

            if(deathDelay >= 60)
            {
                deathDelay = 0;
                entity->setSpawn(1175, 525);
                entity->respawn();
                //camera->setCenterX(entity->getSpawnX());
                //l->reset();
            }
        }
    }
}

void Player2::draw(Graphics* g)
{
    int barWidth = entity->getHealth()*3;

    for(int i = 0; i < barWidth; i++)
    {
        int colorMod = ((float)i/LIFEBAR_WIDTH)*255;
        g->drawRect(LIFEBAR_X+i, LIFEBAR_Y, 1, LIFEBAR_HEIGHT, 255, colorMod, 0);
    }

    g->drawRect(LIFEBAR_X-1,LIFEBAR_Y-1,LIFEBAR_WIDTH+2, LIFEBAR_HEIGHT+2, 255, 255, 255);

    for(int i = 0; i < lives; i++)
    {
        lifeCounterImage.draw(LIVES_PANEL_X+LIVES_SPACING*i, LIVES_PANEL_Y, g);
    }
}

void Player2::scroll(int x)
{
    if(entity != NULL)
    {
        entity->setX(entity->getX() + x);
    }
}

int Player2::getLives()
{
    return lives;
}
