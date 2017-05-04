#include "Game_Header.hpp"

void Fight::Fightx(point scrSize, GameClass&gra)
{
    leftCorner.y=scrSize.y*(-10);
    leftCorner.x=0;

    midle.x=scrSize.x/2;
    midle.y=leftCorner.y+scrSize.y/2;

    gra.view.setCenter(pointToVector(midle));
    gra.window.setView(gra.view);

    Entity textbg;
    gra.loadTextureFromFile(textbg,"battleGround");
    point fhd(1920,1080);
    scaleSpriteToSize(scrSize,textbg.sprite,fhd);
    textbg.xsize=scrSize.x;
    textbg.ysize=scrSize.y;
    textbg.translateTo(midle);

    isFighting=true;


    int radius=10000;
    std::vector < std::pair < std::pair < int,int > , int > > v;
    std::vector < int > battlemobs;
    bool visited[gra.currentLevel.moblist.size()];
    int ci=0,cj=0;
    for(auto i=gra.currentLevel.moblist.begin();i!=gra.currentLevel.moblist.end();++i)
    {
        cj=ci;
        i++;
        auto j=i;
        i--;
        for(;j!=gra.currentLevel.moblist.end();j++)
        {
            if(i->behaviour==friendly || i->behaviour==aggresive)
            {
                v.push_back(std::make_pair(std::make_pair(ci,cj),doubleToInt((*i).pos.distance(j->pos)) ) );
            }
            cj++;
        }
        ci++;
    }
    ci=0;
    for(auto i=gra.currentLevel.moblist.begin();i!=gra.currentLevel.moblist.end();++i)
    {
        if(i->behaviour==friendly || i->behaviour==aggresive)
        {
            if(gra.player.pos.distance(i->pos)<radius)
            {
                battlemobs.push_back(ci);
                visited[ci]=true;
            }
        }
        ci++;
    }
    for(unsigned int i=0;i<battlemobs.size();i++)
    {
        for(unsigned int j=0;j<v.size();j++)
        {
            auto it=gra.currentLevel.moblist.begin();
            for(int k=0;k<v[j].first.second;++k)
            {
                it++;
            }
            if(v[j].first.first==i && !visited[v[j].first.second] &&  (it->behaviour==friendly || it->behaviour==aggresive) && v[j].second<radius)
            {
                battlemobs.push_back(v[j].first.second);
                visited[v[j].first.second]=true;
            }
        }
    }

    double counter=sq(sq(battlemobs.size()));
    point tileSize,tilePos;
    tileSize.x=scrSize.x/sqrt(counter);
    tileSize.y=scrSize.y/sqrt(counter);
    Tile tile;
    doubleToInt(counter);
    std::vector < Tile > tiles;
    tilePos.y=leftCorner.y;
    tilePos.x=0;
    tile.hideOut(tileSize,tilePos);
    tiles.push_back(tile);
    for(int i=0;i<counter-1;i++)
    {
        tilePos.x+=tileSize.x;
        if(tilePos.x>=scrSize.x)
        {
            tilePos.x=leftCorner.x;
            tilePos.y+=tileSize.y;
        }
        tile.hideOut(tileSize,tilePos);
        tile.contentype=nuul;
        tiles.push_back(tile);
    }
    if(counter==0)
    {
        gra.view.setCenter(pointToVector(gra.player.pos));
        gra.window.setView(gra.view);
        gra.guardFade=false;
        gra.FadeInColor.a=255;
        return ;
    }
    ///example
    tiles[0].contentype=enemy;
    tiles[6].contentype=thing;
    tiles[9].contentype=player;
    tiles[15].contentype=frend;
    ///end

    while(isFighting and gra.window.isOpen())
    {
        sf::Event event;
        point mousepos(vectorToPoint((gra.window.mapPixelToCoords(sf::Mouse::getPosition(gra.window)))));
        while (gra.window.pollEvent(event))///In the event loop we keep handling EVENTS, and those happen one at a time and only once per frame. Smooth player movement is not handled here, because of http://www.sfml-dev.org/tutorials/2.3/window-events.php
        {
            if (event.type==sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    gra.window.close();
                }
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                gra.window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for(unsigned int i=0;i<tiles.size();i++)
                    {
                        if(tiles[i].contentype==nuul && tiles[i].isClicked(mousepos,gra))
                        {
                            for(int j=0;j<tiles.size();j++)
                            {
                                if(tiles[j].contentype==player)
                                {
                                    tiles[j].contentype=nuul;
                                }
                            }
                            tiles[i].contentype=player;
                        }
                    }
                }
            }
            if (event.key.code == sf::Keyboard::X)
            {
                gra.view.setCenter(pointToVector(gra.player.pos));
                gra.window.setView(gra.view);
                gra.guardFade=false;
                return ;
            }
            if(event.type==sf::Event::Closed) gra.window.close();
        }///Event loop end
        for(int i=0;i<tiles.size();i++)
        {
            switch(tiles[i].contentype)
            {
                case player:
                {
                    gra.loadTextureFromFile(tiles[i].cos,"player");
                    tiles[i].cos.scaleToSize(tileSize);
                    tiles[i].cos.translateTo(point(tiles[i].lcorner.x+tileSize.x/2,tiles[i].lcorner.y+tileSize.y/2));
                    break;
                }
                case nuul:
                {
                    gra.loadTextureFromFile(tiles[i].cos,"null");
                    tiles[i].cos.scaleToSize(tileSize);
                    tiles[i].cos.translateTo(point(tiles[i].lcorner.x+tileSize.x/2,tiles[i].lcorner.y+tileSize.y/2));
                    break;
                }
                case enemy:
                {
                    gra.loadTextureFromFile(tiles[i].cos,"test");
                    tiles[i].cos.scaleToSize(tileSize);
                    tiles[i].cos.translateTo(point(tiles[i].lcorner.x+tileSize.x/2,tiles[i].lcorner.y+tileSize.y/2));
                    break;
                }
                case thing:
                {
                    gra.loadTextureFromFile(tiles[i].cos,"stone");
                    tiles[i].cos.scaleToSize(tileSize);
                    tiles[i].cos.translateTo(point(tiles[i].lcorner.x+tileSize.x/2,tiles[i].lcorner.y+tileSize.y/2));
                    break;
                }
                case frend:
                {
                    gra.loadTextureFromFile(tiles[i].cos,"test5");
                    tiles[i].cos.scaleToSize(tileSize);
                    tiles[i].cos.translateTo(point(tiles[i].lcorner.x+tileSize.x/2,tiles[i].lcorner.y+tileSize.y/2));
                    break;
                }
            }

        }

        gra.window.clear();

        gra.draw(textbg);
        for(int i=0;i<tiles.size();i++)
        {
            gra.draw(tiles[i].cos);
        }
        gra.window.display();
    }
}
