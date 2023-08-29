#include "ExplosionEntity.h"

ExplosionEntity::ExplosionEntity(Image* image, Sound* sound, int x, int y) :
    SceneNode(ENTITY_EXPLOSION, x, y,
              image->getFrameWidth(), image->getFrameHeight())
{
    sprite.setImage(image);

    if(sound != NULL)
        sound->play();

    frame = -1;
}

ExplosionEntity::~ExplosionEntity()
{

}

void ExplosionEntity::update()
{
    frame++;

    if(frame >= NUM_FRAMES)
    {
        remove();
    }

    sprite.setFrame(frame);
    sprite.update();
}

void ExplosionEntity::draw(Rectangle* view, Graphics* g)
{
    sprite.draw(getX() - view->getX(), getY() - view->getY(), g);
}
