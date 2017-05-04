#include "Game_Header.hpp"
Player::Player()
{
    hp=100;
    speed=5;
    translateTo(point(1920,900));
    Item Neohelmet,kinderSurprise,ThorArmor,SerpentGaunt;
    Neohelmet.loadItemFromFile("Neohelmet");
    kinderSurprise.loadItemFromFile("Kinder Surprise");
    ThorArmor.loadItemFromFile("Thor's Armor");
    playerInv.push_back(Neohelmet);
    playerInv.push_back(kinderSurprise);
    playerInv.push_back(ThorArmor);
}
Player::Player(double nx, double ny, int nhp,double nspeed)
{
    this->hp = nhp;
    this->speed = nspeed;
    point newloc(nx,ny);
    translateTo(newloc);
}
void Player::translateTo(point t)
{
    pos=t;
    point alignment(t.x-xsize/2,t.y-ysize*8/10);

    lcorner=alignment;


    sprite.setPosition(pointToVector(alignment));//pos.x-xsize/2,pos.y-ysize*8/10
}

void Player::start(double nx, double ny, int nhp,double nspeed)
{
    this->hp = nhp;
    this->speed = nspeed;
    point newloc(nx,ny);
    translateTo(newloc);
}
