#include "SpaceGame.h"

int main(int argc, char *argv[])
{
    SpaceGame game;

    if(!game.init())
    {
        game.free();
        return 0;
    }

    game.run();

    return 0;
}
