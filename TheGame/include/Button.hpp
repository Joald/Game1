#pragma once
#include "Game_Header.hpp"
class Button : public ClickableEntity
{
public:

    Button();
    Button(GameClass&,point,/*Rectangle,*/const std::string&,const std::string&,point);
    point padding;
    point totalSize;
    int characterSize;
    bool created;
    sf::Font font;
    sf::Text text;
    void changeText(std::string);
    virtual void translateTo(point);
    bool loadFontFromFile(std::string);
};
