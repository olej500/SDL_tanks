#include "Player.h"

bool Player::init()
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

void Player::free()
{
    lifeCounterImage.free();
}

void Player::setEntity(PlayerEntity* n)
{
    entity = n;
}

void Player::setCamera(Rectangle* r)
{
    camera = r;
}

void Player::update(Input* i, Level* l)
{
    if(entity != NULL)
    {
        if(i->keyHit(SDLK_UP))
        {
            up = true;
            down = false;
            left = false;
            right = false;
        }

        if(i->keyHit(SDLK_DOWN))
        {
            down = true;
            up = false;
            left = false;
            right = false;
        }

        if(i->keyHit(SDLK_LEFT))
        {
            left = true;
            down = false;
            up = false;
            right = false;
        }

        if(i->keyHit(SDLK_RIGHT))
        {
            right = true;
            down = false;
            left = false;
            up = false;
        }

        if(i->keyUp(SDLK_UP))
        {
            up = false;
            if(i->keyDown(SDLK_DOWN))
                down = true;
            if(i->keyDown(SDLK_LEFT))
                left = true;
            if(i->keyDown(SDLK_RIGHT))
                right = true;
        }

        if(i->keyUp(SDLK_DOWN))
        {
            down = false;
            if(i->keyDown(SDLK_UP))
                up = true;
            if(i->keyDown(SDLK_LEFT))
                left = true;
            if(i->keyDown(SDLK_RIGHT))
                right = true;
        }

        if(i->keyUp(SDLK_LEFT))
        {
            left = false;
            if(i->keyDown(SDLK_DOWN))
                down = true;
            if(i->keyDown(SDLK_UP))
                up = true;
            if(i->keyDown(SDLK_RIGHT))
                right = true;
        }

        if(i->keyUp(SDLK_RIGHT))
        {
            right = false;
            if(i->keyDown(SDLK_DOWN))
                down = true;
            if(i->keyDown(SDLK_LEFT))
                left = true;
            if(i->keyDown(SDLK_UP))
                up = true;
        }

        if(i->keyDown(SDLK_UP) && up)// && (!i->keyDown(SDLK_DOWN)) && (!i->keyDown(SDLK_LEFT)) && (!i->keyDown(SDLK_RIGHT)))
        {
            entity->moveUp();
        }

        if(i->keyDown(SDLK_DOWN) && down)// && (!i->keyDown(SDLK_UP)) && (!i->keyDown(SDLK_LEFT)) && (!i->keyDown(SDLK_RIGHT)))
        {
            entity->moveDown();
        }

        if(i->keyDown(SDLK_LEFT) && left)// && (!i->keyDown(SDLK_RIGHT)) && (!i->keyDown(SDLK_UP)) && (!i->keyDown(SDLK_DOWN)))
        {
            entity->moveLeft();
        }

        if(i->keyDown(SDLK_RIGHT) && right)// && (!i->keyDown(SDLK_LEFT)) && (!i->keyDown(SDLK_UP)) && (!i->keyDown(SDLK_DOWN)))
        {
            entity->moveRight();
        }

        if(i->keyDown(SDLK_SPACE))
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
                entity->setSpawn(50, 125);
                entity->respawn();
                //camera->setCenterX(entity->getSpawnX());
                //l->reset();
            }
        }
    }
}

void Player::draw(Graphics* g)
{
    int barWidth = entity->getHealth()*3;

    for(int i = 0; i < barWidth; i++)
    {
        int colorMod = ((float)i/LIFEBAR_WIDTH)*255;
        g->drawRect(LIFEBAR_X+i, LIFEBAR_Y, 1, LIFEBAR_HEIGHT, 0, colorMod, 255);
    }

    g->drawRect(LIFEBAR_X-1,LIFEBAR_Y-1,LIFEBAR_WIDTH+2, LIFEBAR_HEIGHT+2, 255, 255, 255);

    for(int i = 0; i < lives; i++)
    {
        lifeCounterImage.draw(LIVES_PANEL_X+LIVES_SPACING*i, LIVES_PANEL_Y, g);
    }
}

void Player::scroll(int x)
{
    if(entity != NULL)
    {
        entity->setX(entity->getX() + x);
    }
}

int Player::getLives()
{
    return lives;
}
