#pragma once
#include "Game_Header.hpp"

class ClickableEntity : public Entity, public Clickable
{
public:
    ClickableEntity();
    ClickableEntity(Rectangle,point);
    virtual void translateTo(point t);
    bool clickAreaAligned;
    void alignClickArea();
    //bool loadTextureFromFile(std::string);
    bool setTexture(sf::Texture*);
    void scaleToSize(point);
};
