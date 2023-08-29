#include "Button.h"

Button::Button()
{
    isFired = true;
    image = NULL;
}

Button::~Button()
{

}

void Button::setImage(Image* i)
{
    image = i;
    setWidth(i->getWidth());
    setHeight(i->getHeight());
}

void Button::update(Input* i)
{
    isFired = false;
    mouseOver = false;

    if(contains(i->getMouseX(), i->getMouseY()))
    {
        mouseOver = true;

        if(i->mouseDown(Input::MOUSE_LEFT))
        {
            isFired = true;
        }
    }
}

void Button::draw(Graphics* g)
{
    image->draw(getX(), getY(), g);

    if(mouseOver)
    {
        g->drawRect(getX()-5, getY()-5, getWidth()+10, getHeight()+10, 255, 255, 255);
        g->drawRect(getX()-4, getY()-4, getWidth()+8, getHeight()+8, 255, 255, 255);
    }
}

bool Button::fired()
{
    return isFired;
}
