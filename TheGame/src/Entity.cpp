#include "Game_Header.hpp"

Entity::Entity(point t)
{
    pos=t;
    point alignment(t.x-xsize/2,t.y-ysize/2);
    lcorner=alignment;
    sprite.setPosition(pointToVector(alignment));
}
Entity::Entity()
{

}
Entity::~Entity()
{
    //dtor
}

bool Entity::setTexture(sf::Texture*source)
{
    this->texture=source;
    this->sprite.setTexture(*texture);
    this->xsize=this->texture->getSize().x;
    this->ysize=this->texture->getSize().y;
    pos=point(lcorner.x+xsize,lcorner.y+ysize);
    return 1;
}/*
bool Entity::loadTextureFromFile(std::string filename)///obsolete, do not use
{
    bool a=texture->loadFromFile("resources/images/"+filename+".png");
    xsize=texture->getSize().x;
    ysize=texture->getSize().y;
    sprite.setTexture(*texture);
    pos=point(lcorner.x+xsize,lcorner.y+ysize);
    return a;
}*/
void Entity::translateTo(point t)
{
    pos=t;
    point alignment(t.x-xsize/2,t.y-ysize/2);
    lcorner=alignment;
    sprite.setPosition(pointToVector(alignment));
}
void Entity::scaleToSize(point nsize)
{
    scaleSpriteToSize(nsize,sprite,point(xsize,ysize));
    xsize=nsize.x;
    ysize=nsize.y;
    pos=point(lcorner.x+xsize,lcorner.y+ysize);
}
