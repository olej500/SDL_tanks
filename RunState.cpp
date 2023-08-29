#include "RunState.h"

bool RunState::init(Input* i, Audio* a, int width, int height)
{
    camera.set(0, 0, width, height);

    if(!loadFiles())
        return false;

    if(!gameEndingState.init(this, i))
        return false;

    if(!gameOverState.init(this,i))
        return false;

    if(!pauseState.init(this, i))
        return false;

    if(!player.init())
        return false;

    if(!player2.init())
        return false;

    if(!factory.init())
        return false;

    factory.setCamera(&camera);
    player.setCamera(&camera);

    if(!initLevel())
        return false;

    input = i;
    audio = a;

    song.play(-1);

    return true;
}

void RunState::free()
{
    audio->stopMusic();
    freeFiles();
    gameEndingState.free();
    gameOverState.free();
    level.free();
    pauseState.free();
}

bool RunState::loadFiles()
{
    if(!background1.load("graphics/backgrounds/ground.bmp"))
    {
        return false;
    }

    if(!song.load("audio/music/tanks_loop.wav"))
    {
        return false;
    }

    return true;
}

void RunState::freeFiles()
{
    background1.free();
    song.free();
}

void RunState::drawBackground(Graphics* g)
{
    background1.draw(camera.getX(), camera.getY(), g);
}

bool RunState::initLevel()
{
    if(!level.load("levels/level1.txt", &factory))
    {
        return false;
    }

    PlayerEntity* playerEntity = (PlayerEntity*)factory.makeEntity(ENTITY_PLAYER, level.getSpawnX(), level.getSpawnY());
    PlayerEntity* playerEntity2 = (PlayerEntity*)factory.makeEntity(ENTITY_PLAYER_2, level.getSpawnX() + 1150, level.getSpawnY() + 425);

    level.getScene()->addNode(playerEntity);
    player.setEntity(playerEntity);

    level.getScene()->addNode(playerEntity2);
    player2.setEntity(playerEntity2);

    return true;
}

void RunState::update()
{
    player.update(input, &level);
    player2.update(input, &level);
    level.update();

    if(input->keyHit(SDLK_ESCAPE))
    {
        getManager()->addState(&pauseState);
    }

    if(player.getLives() <= 0)
    {
        getManager()->addState(&gameOverState);
    }

    if(player2.getLives() <= 0)
    {
        getManager()->addState(&gameEndingState);
    }
}

void RunState::draw(Graphics* g)
{
    g->clear(0, 0, 0);

    drawBackground(g);
    level.draw(&camera, g);
    player.draw(g);
    player2.draw(g);
}
