#include "Game_Header.hpp"
void doNothing() {}
bool cmpNPCs(NPC lhs,NPC rhs) ///this is a function used to make it
{           /// so that NPCs are displayed in the correct
            /// order, and also clicked
    return (lhs.pos.y<rhs.pos.y);
}

void GameClass::toggleVerticalSync()
{
    if(!vSyncEnabled){
        vSyncEnabled=true;
        window.setVerticalSyncEnabled(true);
    }
    else
    {
        vSyncEnabled=false;
        window.setVerticalSyncEnabled(false);
    }
}

GameClass::GameClass()
{
    screenSize=point(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);
    vSyncEnabled=true;
    toggleVerticalSync();
    //window.setFramerateLimit(60);
    FadeInColor.a=0;
    shade.setSize(sf::Vector2f(100*screenSize.x,10000*screenSize.y));
    gamename="TheGame";

    view.setSize(screenSize.x,screenSize.y);
    window.create(sf::VideoMode(screenSize.x, screenSize.y),gamename/*,sf::Style::Fullscreen*/);
    window.setView(view);
    guardFade=false;

    loadTextureFromFile(player,"player");
    player.start(currentLevel.playerEntryPoint.x,currentLevel.playerEntryPoint.y,100,screenSize.x/2);///Player's speed is set to this to keep it the same on different screen resolutions

    freeze = false;
}

void displayContextMenu(GameClass&gra){
    gra.contextMenu.isOn=true;
}

void endGame(GameClass&gra)
{
    gra.window.close();
}
void GameClass::draw(const Entity&source)
{
    this->window.draw(source.sprite);
}
void GameClass::draw(const Button&source)
{
    /*point textpos = vectorToPoint(source.text.getPosition());
    point spritepos = vectorToPoint(source.sprite.getPosition());*/
    window.draw(source.sprite);
    window.draw(source.text);
}

void GameClass::draw(const ContextMenu&source){
    if(!source.isOn)
        return;
    window.draw(source.Attack.sprite);
    window.draw(source.Examine.sprite);
    window.draw(source.Trade.sprite);
    window.draw(source.Speak.sprite);
    window.draw(source.Steal.sprite);
    window.draw(source.Close.sprite);
}

void GameClass::handleScreenMovement()
{
    point currentScreenPoint=vectorToPoint(window.getView().getCenter());
    //double x1=currentScreenPoint.x,y1=currentScreenPoint.y,x2=screenMovementTarget.x,y2=screenMovementTarget.y;
    view.setCenter(pointToVector(fractionOfDistance(currentScreenPoint,screenMovementTarget,10)));
    window.setView(view);
}
void GameClass::FadeIn()
{
    if(FadeInColor.a>250)
        FadeInColor.a=255;
    else
        FadeInColor.a+=4;

    shade.setFillColor(FadeInColor);

}
void GameClass::FadeOut()
{
    if(FadeInColor.a<=5)
    {
        FadeInColor.a=0;
        battle.isFighting=false;
    }
    else FadeInColor.a-=4;

    shade.setFillColor(FadeInColor);
}
void GameClass::drawAll()
{
    draw(levelbg);
    for(unsigned int i=0;i<currentLevel.moblist.size();++i)
    {
        draw(currentLevel.moblist[i]);
    }
    draw(player);
    draw(contextMenu);
    if(guardFade || battle.isFighting)
        window.draw(shade);

}
bool GameClass::loadTextureFromFile(Entity&target,std::string name)
{
    sf::Texture t;
    bool a=t.loadFromFile("resources/images/"+name+".png");
    textureLibrary.insert(std::make_pair(name,t));
    //textureLibrary.at(name);
    target.setTexture(&textureLibrary.at(name));
    return a;
}
void GameClass::drawInventory(std::vector<Item> vect)
{
    for(unsigned int i=0;i<64;i++)
    {
        ClickableEntity slot;
        point poin;
            poin.x=(screenSize.x/5)*3+((i%8)*(screenSize.x/19))-20;
            poin.y=(screenSize.y/6)+((i/8)*(screenSize.y/11))+30;
        if(i<=vect.size())
        {
            ///if(vect[i].type==helmet)
            loadTextureFromFile(slot,"armor");

        }
/*        else
        {
            slot.loadTextureFromFile("nothing");
        }*/
        point sizze;
        sizze.x=50;
        sizze.y=50;
        slot.scaleToSize(sizze);
        slot.translateTo(poin);
        draw(slot);
    }
}
void GameClass::update(double dt)
{

    point mousepos(vectorToPoint((window.mapPixelToCoords(sf::Mouse::getPosition(window)))));
    if(!freeze)
    {
        ///Player movement handling
        point playerdestination=player.pos;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerdestination.x+=player.speed*dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            playerdestination.x-=player.speed*dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            playerdestination.y-=player.speed*dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            playerdestination.y+=player.speed*dt;

        point transl(player.pos);

        if(playerdestination!=player.pos)
        {
            if(currentLevel.blocks(playerdestination))
                transl=playerdestination;
            else
            {

                while(1)
                {
                    point l=fractionOfDistance(transl,playerdestination,1000);
                    if(!currentLevel.blocks(l))
                    {
                        point h(l.x,transl.y);
                        point v(transl.x,l.y);
                        if(currentLevel.blocks(h))
                        {
                            transl=h;
                            if(!currentLevel.blocks(v) and areClose(l.x,playerdestination.x))
                            {
                                break;
                            }
                            continue;
                        }
                        if(currentLevel.blocks(v))
                        {
                            transl=v;
                            if(areClose(l.y , playerdestination.y))
                            {
                                break;
                            }
                            continue;
                        }
                        break;
                    }
                    transl=l;
                }
            }
            player.translateTo(transl);
        }
        ///PLAYER MOVEMENT AND COLLISION ENDS HERE

        ///SCREEN MOVEMENT
        screenMovementTarget=player.pos;
        for(unsigned int i=0;i<currentLevel.moblist.size();++i)
        {
            if(currentLevel.moblist[i].following and player.pos.distance(currentLevel.moblist[i].pos)>player.xsize*1.5)
            {
                point fr=fractionOfDistance(currentLevel.moblist[i].pos,player.pos,50);
                //testNPCClickarea.move(pointToVector(fr-currentLevel.moblist[i].pos));
                currentLevel.moblist[i].translateTo(fr);

            }
        }
    }
    handleScreenMovement();
    ///FIGHT!!

    if(guardFade)
    {
        freeze=true;
        FadeIn();
        if(FadeInColor.a>=255){
            battle.Fightx(screenSize,*this);
            freeze=false;
        }
    }
    if(!guardFade && FadeInColor.a<=255 && FadeInColor.a>=2)
    {
        FadeOut();
    }
}
void GameClass::Inventory()
{
    ///Ekwipunek 8x8
    Entity inventoryBg;
    if(!loadTextureFromFile(inventoryBg,"inventory"))
        return;
    point midPoint;
    inventoryBg.scaleToSize(point(screenSize.x,screenSize.y));
    midPoint=getMidPoint(point(0,0),point(screenSize.x,screenSize.y));
    inventoryBg.translateTo(midPoint);

    view.setCenter(pointToVector(midPoint));
    window.setView(view);


    ///petla eventów inventorowych
    sf::Event event;
    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::I or event.key.code == sf::Keyboard::Escape)
                {
                    return;
                }
            }
            if(event.type==sf::Event::Closed)
                window.close();
        }
        window.clear();
        draw(inventoryBg);
        //drawInventory(playerInv);
        drawInventory(player.playerInv);
        window.display();
    }
}

bool GameClass::setLevel(std::string name)
{
    if(!currentLevel.importFromFile(name,*this))
        return 0;
    loadTextureFromFile(levelbg,name);
    levelbg.scaleToSize(point(currentLevel.width,currentLevel.height));
    return 1;
}
void GameClass::execute()
{
    ///TESTLEVEL LOADING
    if(!setLevel("testlvl"))
        return;
    view.setCenter(currentLevel.width/2,currentLevel.height/2);
    window.setView(view);

    point middle(currentLevel.width/2,currentLevel.height/2);



    ///stuff for debugtext
    sf::Font defaultFont;
    if (!defaultFont.loadFromFile("resources/fonts/arial.ttf"))
    {
        return;
    }
    sf::Text debugtext;
    debugtext.setFont(defaultFont);
    debugtext.setString("debug");
    debugtext.setCharacterSize(24); // in pixels, not points!
    debugtext.setColor(sf::Color::White);
    debugtext.setStyle(sf::Text::Bold);
    debugtext.setPosition(0,0);

    ///stuff for moving the screen around
    view.setCenter(currentLevel.width/2,currentLevel.height/2);
    window.setView(view);/*
    std::vector<point> screenMovementRectangle;
    point cornerMidPoint(screenSize.x/8,screenSize.y/8);
    screenMovementRectangle.push_back(cornerMidPoint);
    cornerMidPoint.changex(screenSize.x*7/8);
    screenMovementRectangle.push_back(cornerMidPoint);
    cornerMidPoint.changey(screenSize.y*7/8);
    screenMovementRectangle.push_back(cornerMidPoint);
    cornerMidPoint.changex(screenSize.x/8);
    screenMovementRectangle.push_back(cornerMidPoint);
    Shape screenMovementShape(4,screenMovementRectangle);*/

    point start(screenSize.x/2,screenSize.y/2);

    ///player pos setting
    player.translateTo(currentLevel.playerEntryPoint);

    double totalTimeElapsed=0;
    sf::Clock timer;
    timer.restart();
    double startTime=timer.getElapsedTime().asSeconds();
    double deltaTime=timer.getElapsedTime().asSeconds();
    double accumulator=0;
    battle.isFighting=false;
    const double dt=1.f/30.f;



    ///Main LOOP========================================================================================================================================================================================================================================================================================================

    while (window.isOpen())
    {
        sf::Event event;
        point mousepos(vectorToPoint((window.mapPixelToCoords(sf::Mouse::getPosition(window)))));
        while (window.pollEvent(event))///In the event loop we keep handling EVENTS, and those happen one at a time and only once per frame. Smooth player movement is not handled here, because of http://www.sfml-dev.org/tutorials/2.3/window-events.php
        {
            if (event.type==sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::V){
                    toggleVerticalSync();
                }
                if(event.key.code == sf::Keyboard::X){
                    guardFade=true;
                }
                if(event.key.code == sf::Keyboard::I)
                {
                    Inventory();
                }
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(contextMenu.isOn)
                    {
                        /// here is the place to implement everything that will be done after clicking a field in level editor
                        if(contextMenu.Attack.isClicked(mousepos,*this)) {
                            guardFade=true;
                            contextMenu.currentInterlocutor->behaviour = aggresive;
                        }
                        freeze=false;
                        contextMenu.isOn = false;
                        break;
                    }
                    /*if(testButton.isClicked(mousepos,*endGame,*this))
                        break;*/
                    for(auto i=currentLevel.moblist.begin();i!=currentLevel.moblist.end();++i)
                    {
                        if(i->isClicked(mousepos,*displayContextMenu, *this))
                        {

                            contextMenu.SetClickableEntity(*this,i);
                            if(contextMenu.loadedTextures<6)
                                endGame(*this);
                            freeze=true;
                            break;
                        }
                    }

                }
            }
            if(event.type==sf::Event::Closed)
                window.close();
        }

        ///Event loop end===========================================


        ///Time handling
        double newtime=timer.getElapsedTime().asSeconds();
        deltaTime=newtime-startTime;
        //deltaTime=deltaTime>0.25?0.25:deltaTime;
        startTime=newtime;
        accumulator+=deltaTime;
        if(!freeze)
            totalTimeElapsed+=deltaTime;

        if(vSyncEnabled)
        {
            ///UPDATING DEBUGTEXT HERE
            std::ostringstream debugstream;
            debugstream<<player.pos.x<<", Y:"<<player.pos.y<<"\n"<<mousepos.x<<", Y:"<<mousepos.y;

            debugtext.setString(debugstream.str());
            point debugTextPos(0,0);
            accumulator+=deltaTime;
            debugtext.setPosition(window.mapPixelToCoords(pointToVectori(debugTextPos)));
            window.draw(debugtext);


            accumulator=0;
            ///UPDATING EVERYTHING (THAT IS NOT DEBUGTEXT) HERE
            update(deltaTime);
        }
        else
        {
            while(accumulator>=dt)
            {
                ///UPDATING DEBUGTEXT HERE
                std::ostringstream debugstream;
                debugstream<<player.pos.x<<", Y:"<<player.pos.y<<"\n"<<mousepos.x<<", Y:"<<mousepos.y;

                debugtext.setString(debugstream.str());
                point debugTextPos(0,0);
                debugtext.setPosition(window.mapPixelToCoords(pointToVectori(debugTextPos)));
                window.draw(debugtext);



                ///UPDATING EVERYTHING (THAT IS NOT DEBUGTEXT) HERE
                update(dt);
                accumulator-=dt;
            }
        }

        ///sorting NPCs
        std::sort(currentLevel.moblist.begin(),currentLevel.moblist.end(),cmpNPCs);

        ///drawing starts here
        window.clear();///IF NO MORE DEBUG THINGS ARE DRAWN MOVE THIS TO drawAll()

        drawAll();
        window.draw(debugtext);
        window.display();///IF NO MORE DEBUG THINGS ARE DRAWN MOVE THIS TO drawAll()
    }

}
