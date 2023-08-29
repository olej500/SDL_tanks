#ifndef BUTTON_H
#define BUTTON_H

#include "Core/Image.h"
#include "Core/Input.h"
#include "Core/Rectangle.h"

class Button : public Rectangle
{
private:
    Image* image;
    bool isFired;
    bool mouseOver;
public:
    Button();
    ~Button();
    void setImage(Image* i);
    void update(Input* i);
    void draw(Graphics* g);
    bool fired();
};

#endif
