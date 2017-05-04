#include "Game_Header.hpp"

Shape::Shape()
{
    //ctor
}
Shape::Shape(int a,std::vector<point> b)
{
    makeshape(a,b);
}
void Shape::makeshape(int a,std::vector<point> b)
{
    nr=a;
    vertices=b;
    vertices.push_back(*vertices.begin());
    const int beyond=1000000000;
    double maxx=-beyond,minx=beyond,maxy=-beyond,miny=beyond;
    for(int i=0;i<nr;++i)
    {
        maxx = vertices[i].x > maxx ? vertices[i].x : maxx;
        maxy = vertices[i].y > maxy ? vertices[i].y : maxy;
        minx = vertices[i].x < minx ? vertices[i].x : minx;
        miny = vertices[i].y < miny ? vertices[i].y : miny;
    }
    point newsize(maxx-minx,maxy-miny);
    shapeSize=newsize;
}
Shape::~Shape()
{
    //dtor
}
Shape Shape::operator=(const Shape&other)
{
    vertices=other.vertices;
    nr=other.nr;
    return *this;
}
void Shape::translateBy(point change)
{
    for(int i = 0; i < nr; ++i)
    {
        vertices[i].add(change);
    }
}
int isLeft( point P0, point P1, point P2 )
{
    return ( (P1.x - P0.x) * (P2.y - P0.y)
            - (P2.x -  P0.x) * (P1.y - P0.y) );
}
bool Shape::contains(point checked)
{
    ///new improved algorithm, courtesy of http://geomalgorithms.com/a03-_inclusion.html
    ///old one provided for reference
    point P=checked;
    int    wn = 0;    // the  winding number counter

    // loop through all edges of the polygon
    for (int i=0; i<nr; i++) {   // edge from vertices[i] to  vertices[i+1]
        if (vertices[i].y <= P.y) {          // start y <= P.y
            if (vertices[i+1].y  > P.y)      // an upward crossing
                 if (isLeft( vertices[i], vertices[i+1], P) > 0)  // P left of  edge
                     ++wn;            // have  a valid up intersect
        }
        else {                        // start y > P.y (no test needed)
            if (vertices[i+1].y  <= P.y)     // a downward crossing
                 if (isLeft( vertices[i], vertices[i+1], P) < 0)  // P right of  edge
                     --wn;            // have  a valid down intersect
        }
    }
    return wn!=0;



    /**const int beyond=1000000000;
    double maxx=-beyond,minx=beyond,maxy=-beyond,miny=beyond;
    for(int i=0;i<nr;++i)
    {
        maxx = vertices[i].x > maxx ? vertices[i].x : maxx;
        maxy = vertices[i].y > maxy ? vertices[i].y : maxy;
        minx = vertices[i].x < minx ? vertices[i].x : minx;
        miny = vertices[i].y < miny ? vertices[i].y : miny;
    }
    point mins(minx,miny);
    point maxs(maxx,maxy);
    if(!checked.isInSquare(mins,maxs))
        return false;


    int i, j;
    int nvert=nr;
    double testx=checked.x;
    double testy=checked.y;

    bool c = 0;
    for (i=0, j = nvert-1; i < nvert; j = i++)
    {
        if(((vertices[i].y>testy) != (vertices[j].y>testy)) && (testx < (vertices[j].x-vertices[i].x) * (testy-vertices[i].y) / (vertices[j].y-vertices[i].y) + vertices[i].x) )
            c=!c;
    }
      return c;*/
    /**
Arguments

nvert: Number of vertices in the polygon. Whether to repeat the first vertex at the end has been discussed in the article referred above.
vertx, verty: Arrays containing the x- and y-coordinates of the polygon's vertices.
testx, testy: X- and y-coordinate of the test point.    */
}

void Shape::translateTo(const point&newpoint)
{
    /*std::vector<point>ts;
    point zer(0,0);
    ts.push_back(zer);*/
    for(int i=1;i<nr;++i)
    {
        point smth(vertices[i]);
        smth-=vertices[0];
        vertices[i]=newpoint;
        vertices[i].add(smth);
    }
    vertices[0]=newpoint;
}
Rectangle::Rectangle()
{
    nr=4;
    point a(0,0);
    for(int i=0;i<4;++i)
    {
        vertices.push_back(a);
    }
    success=false;
}
Rectangle::Rectangle(std::vector<point>source)
{
    nr=4;
    if(source.size()==4)
    {
        vertices=source;
        success=true;
    }
    else
    {
        point a(0,0);
        for(int i=0;i<4;++i)
        {
            vertices.push_back(a);
        }
        success=false;
    }
}
//Rectangle::Rectangle(sf::FloatRect from);
bool Rectangle::contains(point checked)const
{
    const int beyond=1000000000;
    double minx=beyond,miny=beyond,maxx=-beyond,maxy=-beyond;
    for(int i=0;i<nr;++i)
    {
        maxx = vertices[i].x > maxx ? vertices[i].x : maxx;
        maxy = vertices[i].y > maxy ? vertices[i].y : maxy;
        minx = vertices[i].x < minx ? vertices[i].x : minx;
        miny = vertices[i].y < miny ? vertices[i].y : miny;
    }
    point mins(minx,miny);
    point maxs(maxx,maxy);
    if(checked.isInSquare(mins,maxs))
        return true;
    else
        return false;
}
void Rectangle::translateTo(const point&newpoint )
{
    vertices[0]=newpoint;
    vertices[1]=point(newpoint.x+shapeSize.x,newpoint.y);
    vertices[2]=point(newpoint.x+shapeSize.x,newpoint.y+shapeSize.y);
    vertices[3]=point(newpoint.x,newpoint.y+shapeSize.y);


}
