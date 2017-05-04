#include "Game_Header.hpp"
bool cmpNPC(NPC lhs,NPC rhs) ///this is a function used to make it
{           /// so that NPCs are displayed in the correct
            /// order, and also clicked
    return (lhs.pos.y<rhs.pos.y);
}
Level::Level(int nw,int nh)
{
    width=nw;
    height=nh;
}
Level::Level()
{

}
bool Level::importFromFile(std::string fileName,GameClass&gra)
{
    std::ifstream inputStream;
    fileName+=".lvl";
    inputStream.open(fileName.c_str());
    if(!inputStream.is_open())
        return false;
    std::getline(inputStream,this->name);
    point sizeMult;
    inputStream>>sizeMult.x>>sizeMult.y;
    point siz(gra.screenSize.x*sizeMult.x,gra.screenSize.y*sizeMult.y);
    width=siz.x+0.5;
    height=siz.y+0.5;
    int n;
    inputStream>>n;
    std::vector<point> a;
    int x1,x2,y1,y2;
    for(int i=0;i<n;++i)
    {
        inputStream>>x1>>x2>>y1>>y2;
        a.push_back( point(width*x1/x2,  height*y1/y2));
    }
    inputStream>>x1>>x2>>y1>>y2;
    playerEntryPoint.change(width*x1/x2,  height*y1/y2);
    border.makeshape(n,a);
    int npcnum;
    inputStream>>npcnum;
    std::string npcname;
    point lookout;
    for(int i=0;i<npcnum;++i)
    {
        inputStream>>npcname;
        inputStream>>x1>>x2>>y1>>y2;
        lookout.change(width*x1/x2,  height*y1/y2);
        NPC placeholder(lookout);
        placeholder.loadNPCFromFile(npcname);
        gra.loadTextureFromFile(placeholder,npcname);
        placeholder.translateTo(lookout);
        moblist.push_back(placeholder);
    }
    std::sort(moblist.begin(),moblist.end(),cmpNPC);
    int cluttercount=0;
    inputStream>>cluttercount;
    for(int i=0;i<cluttercount;++i)
    {
        int currclutcter=0;
        inputStream>>currclutcter;
        std::vector<point>ax;
        for(int j=0;j<currclutcter;++j)
        {
            inputStream>>x1>>x2>>y1>>y2;
            ax.push_back(point(width*x1/x2,  height*y1/y2));
        }
        Shape xa;
        xa.makeshape(currclutcter,ax);
        clutter.push_back(xa);
    }
    return 1;
}

bool Level::blocks(point source)
{
    if(!border.contains(source))
        return 0;
    for(auto i=clutter.begin();i!=clutter.end();++i)
    {
        if((*i).contains(source))
            return 0;
    }
    return 1;
}

point Level::getSafeMoveLocation(point start,point fin)
{
    point null(-1000,-1000);
    point eval=intersection(start,fin,border.vertices[0],border.vertices[border.nr-1]);
    /*double ang=angleBetweenSegments(start,fin,border.vertices[0],border.vertices[border.nr-1])
    if(ang==0 or ang==acos(1))
        return fin;*/
    if(eval!=null)
    {
        return eval;
    }
    for(int i=0;i<border.nr-1;++i)
    {
        eval=intersection(start,fin,border.vertices[i],border.vertices[i+1]);

        if(eval!=null)
        {
            return eval;
        }
    }
    for(auto it=clutter.begin();it!=clutter.end();++it)
    {
        for(int i=0;i<it->nr;++i)
        {
            eval=intersection(start,fin,it->vertices[i],it->vertices[i+1]);
            if(eval!=null)
            {
                return eval;
            }
        }
    }

    return start;
}
