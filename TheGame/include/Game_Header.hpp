#pragma once
#include <bits/stdc++.h>///temporarily, currently cmath, fstream,vector,map,climits,algorithm needed
#include <SFML/Graphics.hpp>///order of including depends on which class depends on which. If a class depends on nothing, it goes first.
#define callMemberFn(object,ptrToMember)  ((object).*(ptrToMember))

/// moved from NPC class to ensure that all classes that need it, recognize the behaviourType type
enum behaviourType{///passives don't fight unless provoked, aggros fight within a radius (TBA), friendlies fight alongside you within a radius (TBA)
    passive,aggresive,friendly,
};
enum contentsType {
    nuul, player, enemy, frend, thing
};


enum itemType{
    boots,gloves,ring,armor,consumable,helmet,unsignd,
};
enum statType{
    health,attack,defense,persuasion,money
};
typedef int statVal ;
const statVal bignumber=(INT_MAX%1000000000)+6;

#include "Math.hpp"
#include "Shape.hpp"
#include "Clickable.hpp"
#include "Entity.h"
#include "ClickableEntity.hpp"
#include "ContextMenu.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "Stat.hpp"
#include "Item.hpp"
#include "Inventory.hpp"
#include "NPC.hpp"
#include "Level.hpp"
#include "Player.h"
#include "Fight.h"
#include "GameClass.hpp"

