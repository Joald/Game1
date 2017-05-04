#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;
class point
{
public:
    double x,y;
    point() {}
    point(double nx,double ny)
    {
        x=nx;
        y=ny;
    }
};
point vectorToPoint(sf::Vector2f source)
{
    point returning(source.x,source.y);
    return returning;
}
sf::Vector2f pointToVector(point source)
{
    sf::Vector2f returning;
    returning.x=source.x;
    returning.y=source.y;

    return returning;
}
point reduce_fraction (int numerator, int denominator)
{
    for (int i = denominator * numerator; i > 1; i--)
    {
        if ((denominator % i == 0) && (numerator % i == 0))
        {
            denominator /= i;
            numerator /= i;
        }

    }
    return point(numerator,denominator);
}
int ax,ay;
void printpoint(ofstream& output, point p,bool space)
{
    output<<p.x<<' '<<p.y<<(space?' ':'\n');
}
void eport(ofstream& output, point p)
{
    if(p.x==0)
        printpoint(output,point(0,1),true);
    else
        printpoint(output,reduce_fraction(p.x,ax),true);
    if(p.y==0)
        printpoint(output,point(0,1),true);
    else
        printpoint(output,reduce_fraction(p.y,ay),false);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cout<<"Enter the name of the level\n";
    string name;
    getline(cin,name);

    cout<<"Enter the multiplier of screen size that the level will be\ntwo numbers, a and b, where level size will be \na*screensize.x and b*screensize.y\n";
    double aa,bb;
    cin>>aa>>bb;
    cout<<"Enter the number of NPCs in the level\n";
    int npccount;
    cin>>npccount;
    string npcnames[npccount];
    string a;
    getline(cin,a);
    for(int i=0; i<npccount; ++i)
    {
        cout<<"Enter the name of the "<<i+1<<". NPC.\n";
        getline(cin,npcnames[i]);
    }
    string x=name+".lvl";
    ofstream output;
    output.open(x.c_str());
    output<<name<<endl;
    sf::Sprite level;
    sf::Texture sprite;
    string spritename="resources/images/"+name+".png";
    if(!sprite.loadFromFile(spritename))
        return 0;

    ax=sprite.getSize().x,ay=sprite.getSize().y;
    while(ax*1.5>sf::VideoMode::getDesktopMode().width or ay>sf::VideoMode::getDesktopMode().height)
    {
        level.scale(0.5,0.5);
        ax/=2;
        ay/=2;
    }

    sf::RenderWindow window(sf::VideoMode(ax*1.5,ay*1.5),"lvleditor");

    level.setTexture(sprite);



    sf::Text box;
    sf::Text lb;
    sf::Text rb;
    sf::Font defaultFont;
    if (!defaultFont.loadFromFile("resources/fonts/arial.ttf"))
    {
        return 0;
    }
    box.setFont(defaultFont);
    lb.setFont(defaultFont);
    rb.setFont(defaultFont);
    box.setString("Click on subsequent angles\nuntil finished, then click\noutside the picture");
    rb.setString("Finish adding clutter");
    lb.setString("Add more clutter");
    box.setColor(sf::Color::White);
    lb.setColor(sf::Color::White);
    rb.setColor(sf::Color::White);
    box.setPosition(ax,0);
    lb.setPosition(0,ay);
    rb.setPosition(ax,ay);
    int state=0;
    vector<point>border;
    vector<point>NPCs;
    vector<vector<point> >clutter;


    int currpointcount=0;
    int curnpccount=0;
    sf::VertexArray lines(sf::Lines);
    point prevpoint,playerentrypoint;

    while(window.isOpen() and state!=10)
    {
        sf::Event event;
        point mousepos=(vectorToPoint((window.mapPixelToCoords(sf::Mouse::getPosition(window)))));
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed or (event.type==sf::Event::KeyPressed and event.key.code==sf::Keyboard::Escape))
            {
                window.close();
            }
            if(event.type==sf::Event::MouseButtonPressed)
            {
                if(state==0)
                {
                    if(mousepos.x<ax and mousepos.y<ay)
                    {
                        border.push_back(mousepos);
                        lines.append(sf::Vertex(pointToVector(mousepos),sf::Color::Blue));
                        lines.append(sf::Vertex(pointToVector(mousepos),sf::Color::Blue));
                        currpointcount++;
                        prevpoint=mousepos;
                    }
                    else
                    {
                        state=1;
                        lines.resize(lines.getVertexCount()-2);
                        box.setString("Now add clutter");
                    }

                }
                else if(state==1)
                {
                    if(mousepos.x<ax and mousepos.y>ay)
                    {
                        state=2;
                        currpointcount=0;
                        clutter.resize(clutter.size()+1);
                        box.setString("Mark the shape of the object");
                    }
                    else if(mousepos.x>ax and mousepos.y>ay)
                    {
                        if(npccount==0)
                            goto lol;
                        state=3;
                        box.setString("Now add NPCs");
                        lb.setString("Click here to add an NPC");
                        rb.setString("");
                    }
                }
                else if(state==2)
                {
                    if(mousepos.x<ax and mousepos.y<ay)
                    {
                        clutter[clutter.size()-1].push_back(mousepos);

                        lines.append(sf::Vertex(pointToVector(mousepos),sf::Color::Blue));
                        lines.append(sf::Vertex(pointToVector(mousepos),sf::Color::Blue));

                        currpointcount++;
                        prevpoint=mousepos;
                    }
                    else
                    {
                        state--;
                        lines.resize(lines.getVertexCount()-2);
                        box.setString("Now add more clutter");
                    }
                }
                else if(state==3)
                {
                    if(mousepos.x<ax and mousepos.y>ay)
                    {
                        state=4;
                        box.setString("Mark the location of the NPC");
                    }
                    else if(mousepos.x>ax and mousepos.y>ay)
                    {
                        ///print ALL NPCs here
lol:
                        state=5;
                        box.setString("Now mark the player's entry point");
                        lb.setString("");
                        rb.setString("");
                    }
                }
                else if(state==4)
                {
                    if(mousepos.x<ax and mousepos.y<ay)
                    {
                        NPCs.push_back(mousepos);
                        state=3;
                        curnpccount++;
                        if(curnpccount==npccount)
                            goto lol;
                    }
                }
                else if(state==5)
                {
                    if(mousepos.x<ax and mousepos.y<ay)
                    {
                        playerentrypoint=mousepos;
                        state=10;
                    }
                }

            }
        }
        if(lines.getVertexCount()>0 and (state==0 or state==2) and currpointcount)
            lines[lines.getVertexCount()-1].position=pointToVector(mousepos);

        window.clear();
        window.draw(level);
        window.draw(box);
        if(state==1 or state==3)
        {
            window.draw(rb);
            window.draw(lb);
        }

        window.draw(lines);

        window.display();
    }

    ///EXPORTING HERE
    output<<aa<<" "<<bb<<endl;
    output<<border.size()<<endl;
    for(unsigned int i=0; i<border.size(); ++i)
    {
        eport(output,border[i]);
    }
    eport(output,playerentrypoint);
    output<<npccount<<endl;
    for(int i=0; i<npccount; ++i)
    {
        output<<npcnames[i]<<endl;
        eport(output,NPCs[i]);
    }
    output<<clutter.size()<<endl;
    for(int i=0;i<clutter.size();++i)
    {
        output<<clutter[i].size()<<endl;
        for(auto it=clutter[i].begin();it!=clutter[i].end();++it)
        {
            eport(output,*it);
        }
    }
    /**
    cout<<"Enter the number of angles your level will have\n";
    int angleCount;
    cin>>angleCount;
    output<<angleCount<<endl;
    int xnumerator,xdenominator,ynumerator,ydenominator;
    for(int i=0;i<angleCount;++i)
    {
        cout<<"Enter the fraction of level width that is the "<<i+1<<". point's x coordinate.\n";
        cin>>xnumerator>>xdenominator;
        cout<<"Enter the fraction of level height that is the "<<i+1<<". point's y coordinate.\n";
        cin>>ynumerator>>ydenominator;
        output<<xnumerator<<" "<<xdenominator<<" "<<ynumerator<<" "<<ydenominator<<endl;
    }
    cout<<"Enter the number of solid objects the level will have\n";
    int scount;
    cin>>scount;
    for(int i=0;i<scount;++i)
    {
        cout<<"Enter the number of angles your level will have\n";
        int angleCount;
        cin>>angleCount;
        output<<angleCount<<endl;
        int xnumerator,xdenominator,ynumerator,ydenominator;
        for(int i=0;i<angleCount;++i)
        {
            cout<<"Enter the fraction of level width that is the "<<i+1<<". point's x coordinate.\n";
            cin>>xnumerator>>xdenominator;
            cout<<"Enter the fraction of level height that is the "<<i+1<<". point's y coordinate.\n";
            cin>>ynumerator>>ydenominator;
            output<<xnumerator<<" "<<xdenominator<<" "<<ynumerator<<" "<<ydenominator<<endl;
        }
    }
    cout<<"Enter the fraction of level width that is the player's entry point's x coordinate.\n";
    cin>>xnumerator>>xdenominator;
    cout<<"Enter the fraction of level height that is the player's entry point's y coordinate.\n";
    cin>>ynumerator>>ydenominator;
    output<<xnumerator<<" "<<xdenominator<<" "<<ynumerator<<" "<<ydenominator<<endl;
    cout<<"Enter the number of NPCs in the level\n";
    int npcnum;
    cin>>npcnum;
    output<<npcnum<<endl;
    string currnpcname;
    for(int i=0;i<npcnum;++i)
    {
        cout<<"Enter the name of the "<<i+1<<". NPC.\n";
        cin>>currnpcname;
        output<<currnpcname<<endl;
        cout<<"Enter the fraction of level width that is this NPC's entry point's x coordinate.\n";
        cin>>xnumerator>>xdenominator;
        cout<<"Enter the fraction of level height that is the NPC's entry point's y coordinate.\n";
        cin>>ynumerator>>ydenominator;
        output<<xnumerator<<" "<<xdenominator<<" "<<ynumerator<<" "<<ydenominator<<endl;

    }*/
    return 0;
}
