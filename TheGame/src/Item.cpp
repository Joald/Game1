#include "Game_Header.hpp"
Item::Item()
{
    type=unsignd;
    name="testName";
    for(int il=0;il<6;il++)
    {
        effect.push_back(0);
    }
}

void Item::addEffectToItem(int nrEfect, int valeu)
{
    effect[nrEfect]=valeu;
}

bool Item::loadItemFromFile(std::string fileName)
{
    std::ifstream inputStr;
    fileName+=".item";
   // alignClickArea();
    inputStr.open(fileName.c_str());
    if(!inputStr.is_open())
        return false;
    std::getline(inputStr,this->name);
    int typee;
    inputStr>>typee;
    switch(typee)
    {
    case 1:
        type=consumable;
        break;
    case 2:
        type=armor;
        break;
    case 3:
        type=helmet;
        break;
    case 4:
        type=boots;
        break;
    case 5:
        type=gloves;
        break;
    case 6:
        type=ring;
        break;
    default:
        type=unsignd;
        break;
    }

    int nrEfe;
    int valeu;
    while(inputStr.eof())
    {
        inputStr>>nrEfe;
        inputStr>>valeu;
        addEffectToItem(nrEfe,valeu);
    }
    return 1;
}
