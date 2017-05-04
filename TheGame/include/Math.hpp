#pragma once

double sq(double);
class point
{
public:
    point(double,double);
    point(const point&);
    double x,y;
    double angle(point,point);
    const double distance(const point&) const;
    bool isInSquare(point,point);
    void change(double,double);
    void changex(double);
    void changey(double);
    bool operator!= (const point& );
    void operator= (const point&);
    //point& operator+= (const point&);
    void add(point);
    point operator+ (const point&);
    point& operator-= (const point&);
    point operator- (const point&);
    //point operator/(const point&,int);
    point();
};
point getMidPoint(point,point);
point fractionOfDistance(point, point,int);
sf::Vector2f pointToVector(point);
sf::Vector2i pointToVectori(point);
point vectorToPoint(sf::Vector2f);
point vectoriToPoint(sf::Vector2i);
point vectoruToPoint(sf::Vector2u);
int doubleToInt(double);
void scaleSpriteToSize(point,sf::Sprite&,point);
point intersection(point,point,point,point);
double angleBetweenSegments(point,point,point,point);
bool areClose(double,double);
