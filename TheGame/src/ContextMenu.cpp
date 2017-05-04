#include "Game_Header.hpp"

ContextMenu::ContextMenu(){
    this->isOn = false; // default value
}

ContextMenu::ContextMenu(GameClass&gra,std::vector<NPC>::iterator source){
    this->isOn = false;
    this->currentInterlocutor = source;

    // setting textures to all clickable option fields
    loadedTextures=0;
    loadedTextures+=gra.loadTextureFromFile(Attack,"dialogueWindowAttack");
    loadedTextures+=gra.loadTextureFromFile(Examine,"dialogueWindowExamine");
    loadedTextures+=gra.loadTextureFromFile(Trade,"dialogueWindowTrade");
    loadedTextures+=gra.loadTextureFromFile(Speak,"dialogueWindowSpeak");
    loadedTextures+=gra.loadTextureFromFile(Steal,"dialogueWindowSteal");
    loadedTextures+=gra.loadTextureFromFile(Close,"dialogueWindowClose");

    // declarations that make life easier
    double x = source->xsize/2;
    double y = source->ysize/2;
    double xField = Attack.xsize/2; // half of fields size
    double yField = Attack.ysize/2;

    // getting all the clickable option fields in position
    point examinePos;
    examinePos.x = source->pos.x-x-10;
    examinePos.y = source->pos.y;
    Examine.translateTo(examinePos);

    point stealPos;
    stealPos.x = source->pos.x+x+10;
    stealPos.y = source->pos.y;
    Steal.translateTo(stealPos);

    point closePos;
    closePos.x = source->pos.x+x+10;
    closePos.y = Steal.pos.y+yField+10;
    Close.translateTo(closePos);

    point speakPos;
    speakPos.x = source->pos.x;
    speakPos.y = source->pos.y-y-10;
    Speak.translateTo(speakPos);

    point attackPos;
    attackPos.x = Speak.pos.x-xField-10;
    attackPos.y = Speak.pos.y;
    Attack.translateTo(attackPos);

    point tradePos;
    tradePos.x = Speak.pos.x+xField+10;
    tradePos.y = Speak.pos.y;
    Trade.translateTo(tradePos);
}

// all the code is the same as in the constructor
void ContextMenu::SetClickableEntity(GameClass&gra, std::vector<NPC>::iterator source){
    this->isOn = true;
    this->currentInterlocutor = source;

    // setting textures to all clickable option fields
    loadedTextures=0;
    loadedTextures+=gra.loadTextureFromFile(Attack,"dialogueWindowAttack");
    loadedTextures+=gra.loadTextureFromFile(Examine,"dialogueWindowExamine");
    loadedTextures+=gra.loadTextureFromFile(Trade,"dialogueWindowTrade");
    loadedTextures+=gra.loadTextureFromFile(Speak,"dialogueWindowSpeak");
    loadedTextures+=gra.loadTextureFromFile(Steal,"dialogueWindowSteal");
    loadedTextures+=gra.loadTextureFromFile(Close,"dialogueWindowClose");

    // declarations that make life easier
    double x = source->xsize/2;
    double y = source->ysize/2;
    double xField = Attack.xsize/2; // half of fields size
    double yField = Attack.ysize/2;

    // getting all the clickable option fields in position
    point examinePos;
    examinePos.x = source->pos.x-x-xField-10;
    examinePos.y = source->pos.y;
    Examine.translateTo(examinePos);

    point stealPos;
    stealPos.x = source->pos.x+x+xField+10;
    stealPos.y = source->pos.y;
    Steal.translateTo(stealPos);

    point closePos;
    closePos.x = source->pos.x+x+xField+10;
    closePos.y = Steal.pos.y+(2*yField)+10;
    Close.translateTo(closePos);

    point speakPos;
    speakPos.x = source->pos.x;
    speakPos.y = source->pos.y-y-yField-10;
    Speak.translateTo(speakPos);

    point attackPos;
    attackPos.x = Speak.pos.x-(2*xField)-10;
    attackPos.y = Speak.pos.y;
    Attack.translateTo(attackPos);

    point tradePos;
    tradePos.x = Speak.pos.x+(2*xField)+10;
    tradePos.y = Speak.pos.y;
    Trade.translateTo(tradePos);

}

