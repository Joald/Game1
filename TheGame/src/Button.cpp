#include "Game_Header.hpp"
void Button::translateTo(point t)
{

    point middle(t.x+xsize/2,t.y+ysize*8/10);
    pos=middle;
    if(clickAreaAligned)
        clickArea.translateTo(t);

    lcorner=t;
    t=lcorner;
    sprite.setPosition(pointToVector(t));//pos.x-xsize/2,pos.y-ysize*8/10
    t.add(padding);
    text.setPosition(pointToVector(t));
}
Button::Button()
{

}

Button::Button(GameClass&gra,point corner, const std::string&nstring,const std::string&ntexture,point screenSize)
{
    clickAreaAligned=false;
    created=true;
    created=gra.loadTextureFromFile(*this,ntexture);
    text.setString(nstring);
    characterSize=doubleToInt(screenSize.y)/30;
    text.setCharacterSize(characterSize);
    text.setColor(sf::Color::Black);/*
    point tsize(text.getLocalBounds().width
                - text.getLocalBounds().left,
                text.getLocalBounds().height
                - text.getLocalBounds().top);*/
    padding.change(screenSize.x/40,screenSize.y/40);
    int textwidth=0.55*characterSize*text.getString().getSize();
    point spritesize1(padding.x*2+textwidth,padding.y*2+characterSize);
    totalSize.change(xsize,ysize);
    scaleSpriteToSize(spritesize1,sprite,totalSize);
    xsize=spritesize1.x;
    ysize=spritesize1.y;
    alignClickArea();
    lcorner=corner;
    translateTo(lcorner);
}


bool Button::loadFontFromFile(std::string a)
{
    bool g;
    g=font.loadFromFile("resources/fonts/"+a/*.c_str()*/+".ttf");
    text.setFont(font);
    return g;
}

void Button::changeText(std::string nstring)
{
    clickAreaAligned=false;
    text.setString(nstring);/*
    point tsize(text.getLocalBounds().width
                - text.getLocalBounds().left,
                text.getLocalBounds().height
                - text.getLocalBounds().top);*/
    int textwidth=0.55*characterSize*text.getString().getSize();
    point spritesize1(sq(padding.x)/20+textwidth,sq(padding.y)/20+characterSize);
    totalSize.change(xsize,ysize);
    scaleSpriteToSize(spritesize1,sprite,totalSize);
    xsize=spritesize1.x;
    ysize=spritesize1.y;
    alignClickArea();
    translateTo(lcorner);
}
