#pragma once
#include "Game_Header.hpp"
class NPC;

class ContextMenu : public Entity
{
    public:
    ContextMenu();
    ContextMenu(GameClass&,std::vector<NPC>::iterator);
    void SetClickableEntity(GameClass&, std::vector<NPC>::iterator);
    // actions, which can be chosen in the context menu ("clickable option fields"):
    ClickableEntity Attack, Close, Examine, Trade, Speak, Steal;
    std::vector<NPC>::iterator currentInterlocutor; // the thing over which context menu shall be displayed
    int loadedTextures;
    bool isOn;
};
