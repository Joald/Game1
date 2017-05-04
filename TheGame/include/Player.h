#pragma once
#include "Game_Header.hpp"

class Player:public Entity///don't make Player a ClickableEntity without overloading translateTo(point)
{
    public:
        int hp;
        int attack;
        int defense;
        int persuasion;
        int money;
        std::vector<Item> playerInv;
        double speed;
        Player();
        Player(double, double, int,double);
        void translateTo(point);
        void start(double, double, int,double);
    protected:
    private:
};


