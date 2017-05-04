#include "Game_Header.hpp"
bool point::isInSquare(point c1,point c2)
{
    bool a = ( (x>c1.x and x<c2.x) or (x>c2.x and x<c1.x) ) and ( (y>c1.y and y<c2.y ) or (y>c2.y and y<c1.y));
    /*goto randomcode;
    randomcode:*/
    return a;
}
double sq(double x)
{
    return x*x;
}
const double point::distance( const point&p)const
{
    return sqrt(sq(x-p.x)+sq(y-p.y));
}
double point::angle(point p2,point p3)///p1 to jest this point
{
    //double PI=3.1415926535;
    double r=(2*this->distance(p2)*this->distance(p3));
    r=r?r:-1;
    return acos((sq(this->distance(p2))+sq(this->distance(p3))-sq(p2.distance(p3)))/r )/* *180/PI*/;
}
point::point(double nx,double ny)
{
    x=nx;
    y=ny;
}
point::point(const point& a)
{
    *this=a;
}
void point::change(double nx,double ny)
{
    x=nx;
    y=ny;
}
void point::changex(double nx)
{
    x=nx;
}
void point::changey(double ny)
{
    y=ny;
}
point::point()
{
    x=y=0;
}
void point::operator= (const point&param)
{
    x=param.x;
    y=param.y;
}
bool point::operator!= (const point& param)
{
    return this->x!=param.x or this->y!=param.y;
}/*
point& point::operator+=(const point&param)
{
    double a=x;
    double b=y;
    a+=param.x;
    b+=param.y;
    point(a,b);
    this->x+=param.x;
    this->y+=param.y;
    return *this;
}*/
void point::add(point addendum)
{
    x+=addendum.x;
    y+=addendum.y;
}
point point::operator+( const point&rpoint)
{
    add(rpoint);
    return *this;
}
point& point::operator-=(const point&param)
{
    this->x-=param.x;
    this->y-=param.y;
    return *this;
}/*
point point::operator/(const point &lpoint,int factor)
{
    point ofNoReturn(lpoint.x/factor,lpoint.y/factor)
    return ofNoReturn;
}*/
point point::operator-( const point&rpoint)
{
    point a=*this;
    a-=rpoint;
    return a;
}
sf::Vector2f pointToVector(point source)
{
    sf::Vector2f returning;
    returning.x=source.x;
    returning.y=source.y;

    return returning;
}
sf::Vector2i pointToVectori(point source)
{
    sf::Vector2i returning;
    int a,b;
    a=source.x+0.5;
    b=source.y+0.5;
    returning.x=(int)a;
    returning.y=(int)b;

    return returning;
}
point vectoriToPoint(sf::Vector2i source)
{
    point returning(source.x,source.y);
    return returning;
}
point vectoruToPoint(sf::Vector2u source)
{
    point returning(source.x,source.y);
    return returning;
}
point vectorToPoint(sf::Vector2f source)
{
    point returning(source.x,source.y);
    return returning;
}
point getMidPoint(point a,point b)
{
    point c(a.x/2+b.x/2,a.y/2+b.y/2);
    return c;
}
point fractionOfDistance(point a,point b,int fraction)
{
    if(fraction==0)
        return a;
    point c(a.x+(b.x-a.x)/fraction,a.y+(b.y-a.y)/fraction);
    return c;
}
int doubleToInt(double a)
{
    a+=0.5;
    return (int)a;
}

void scaleSpriteToSize(point nsize,sf::Sprite&target,point oldsize)
{
    target.setScale(1.f,1.f);
    point newscale(nsize.x/oldsize.x,nsize.y/oldsize.y);
    target.scale(pointToVector(newscale));
}

double angleBetweenSegments(point a,point b,point c,point d)
{
    int x1=doubleToInt(a.x),x2=doubleToInt(b.x),x3=doubleToInt(c.x),x4=doubleToInt(d.x);
    int y1=doubleToInt(a.y),y2=doubleToInt(b.y),y3=doubleToInt(c.y),y4=doubleToInt(d.y);
    return std::acos(((x2-x1)*(x4-x3)+(y2-y1)*(y4-y3))/sqrt(sq(x2-x1)+sq(y2-y1))*sqrt(sq(x4-x3)+sq(y4-y3)));
}
bool areClose(double a,double b)
{
    int dif=fabs(a-b);
    return dif<0.001;
}
point intersection(point a,point b,point c,point d)///adapted from http://www.ahristov.com/tutorial/geometry-games/intersection-segments.html
{
    int x1=doubleToInt(a.x),x2=doubleToInt(b.x),x3=doubleToInt(c.x),x4=doubleToInt(d.x);
    int y1=doubleToInt(a.y),y2=doubleToInt(b.y),y3=doubleToInt(c.y),y4=doubleToInt(d.y);
    point null(-1000,-1000);


    int e = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    if (e == 0) return null;

    int xi = ((x3-x4)*(x1*y2-y1*x2)-(x1-x2)*(x3*y4-y3*x4))/e;
    int yi = ((y3-y4)*(x1*y2-y1*x2)-(y1-y2)*(x3*y4-y3*x4))/e;

    if (xi < std::min(x1,x2) || xi > std::max(x1,x2)) return null;
    if (yi < std::min(y1,y2) || yi > std::max(y1,y2)) return null;
    if (xi < std::min(x3,x4) || xi > std::max(x3,x4)) return null;
    if (yi < std::min(y3,y4) || yi > std::max(y3,y4)) return null;
    point p(xi,yi);
    double ang=angleBetweenSegments(a,b,c,d);
    if(areClose(ang,0) or areClose(ang,acos(1)))
        return b;
    return p;
}
