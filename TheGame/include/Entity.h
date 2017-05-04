#pragma once
#include "Game_Header.hpp"
class Entity
{
    public:
        Entity(point);
        Entity();
        virtual ~Entity();
        virtual void translateTo(point);
        virtual bool setTexture(sf::Texture*);
        double xsize, ysize;//xsize and ysize should be kept even (divisible by 2)
        point pos;
        point lcorner;
        sf::Texture* texture;
        sf::Sprite sprite;
        //virtual bool loadTextureFromFile(std::string);
        virtual void scaleToSize(point);
};
