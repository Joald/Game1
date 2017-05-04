#include "Game_Header.hpp"
ClickableEntity::ClickableEntity()
{

}
ClickableEntity::ClickableEntity(Rectangle rec,point p)
{
    translateTo(p);
}
void ClickableEntity::translateTo(point t)
{
    pos=t;
    point alignment(t.x-xsize/2,t.y-ysize/2);
    if(clickAreaAligned)
        clickArea.translateTo(alignment);
    lcorner=alignment;
    sprite.setPosition(pointToVector(alignment));//pos.x-xsize/2,pos.y-ysize*8/10
    /*
    lcorner=t;
    t=lcorner;
    sprite.setPosition(pointToVector(t));//pos.x-xsize/2,pos.y-ysize*8/10*/
}

void ClickableEntity::alignClickArea()
{
    std::vector<point> a;
    ///point buffer(lcorner);

    a.push_back(point(lcorner));
    ///buffer.changex(lcorner.x+xsize);
    a.push_back(point (lcorner.x+xsize,lcorner.y));
    ///buffer.changey(lcorner.y+ysize);
    a.push_back(point (lcorner.x+xsize,lcorner.y+ysize));
    ///buffer.changex(lcorner.x);
    a.push_back(point (lcorner.x,lcorner.y+ysize));
    clickArea.makeshape(4,a);
    clickAreaAligned=true;
}
/*
bool ClickableEntity::loadTextureFromFile(std::string filename)
{
    bool a=texture->loadFromFile("resources/images/"+filename+".png");
    xsize=texture->getSize().x;
    ysize=texture->getSize().y;
    sprite.setTexture(*texture);
    pos=point(lcorner.x+xsize,lcorner.y+ysize);
    alignClickArea();
    return a;
}*/
bool ClickableEntity::setTexture(sf::Texture*source)
{
    this->texture=source;
    this->sprite.setTexture(*texture);
    this->xsize=this->texture->getSize().x;
    this->ysize=this->texture->getSize().y;
    pos=point(lcorner.x+xsize,lcorner.y+ysize);
    alignClickArea();
    return clickAreaAligned;
}

void ClickableEntity::scaleToSize(point nsize)
{
    scaleSpriteToSize(nsize,sprite,point(xsize,ysize));
    xsize=nsize.x;
    ysize=nsize.y;
    pos=point(lcorner.x+xsize,lcorner.y+ysize);
    alignClickArea();
}
