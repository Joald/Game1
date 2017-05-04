#pragma once
#include "Game_Header.hpp"
class GameClass
{
    ///random crap and variables here (if you want to make a global, this is the place)
    std::string gamename;
    point screenMovementTarget;
    sf::RectangleShape shade;
public:
    point screenSize;
    Entity levelbg;
    std::map<std::string,sf::Texture>textureLibrary;
    std::vector<Item> playerInv;///OLA - To raczej powinno byc wrzucone w klase gracza
    sf::Color FadeInColor;
    sf::View view;
    sf::RenderWindow window;
    void execute();///this is the function where everything takes place
    void draw(const Entity&);
    void draw(const Button&);
    void draw(const ContextMenu&);
    bool loadTextureFromFile(Entity&,std::string);
    void FadeIn();
    void drawAll();
    void update(double);
    void FadeOut();
    void drawInventory(std::vector<Item>);
    void Inventory();
    bool guardFade;
    Fight battle;
    void handleScreenMovement();
    Level currentLevel;
    GameClass();
    Player player;
    ContextMenu contextMenu;
    bool freeze;
    bool vSyncEnabled;
    void toggleVerticalSync();
    bool setLevel(std::string);
};

void endGame(GameClass&);
