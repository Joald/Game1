#include "Game_Header.hpp"
Clickable::Clickable(Rectangle newshape)
{
    clickArea=newshape;
}
Clickable::Clickable()
{

}
void Clickable::setClickArea(Rectangle newshape)
{
    clickArea=newshape;
}
bool Clickable::isClicked(point clickpoint, void(*func)(GameClass&),GameClass&gra)const
{
    Rectangle testshape=clickArea;
    point a[4];
    for(int i=0;i<4;++i)
    {
        a[i]=testshape.vertices[i];
    }
    if(clickArea.contains(clickpoint))
    {
        ///*GameClass::*/callMemberFn(gra,func);
        (*func)(gra);
        return true;
    }
    return false;
}

bool Clickable::isClicked(point clickpoint, GameClass&gra)const
{ // a function just to check if something is clicked
    if(clickArea.contains(clickpoint)){
        return true;
    }

    return false;
}

void Clickable::translateTo(point t)
{
    clickArea.translateTo(t);
}
