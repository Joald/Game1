#pragma once
#include "Game_Header.hpp"
class Shape
{
    public:
        Shape(int,std::vector<point>);
        Shape();
        virtual ~Shape();
        int nr;
        point shapeSize;
        std::vector<point> vertices;
        virtual bool contains(point);
        Shape operator= (const Shape&);
        void makeshape(int,std::vector<point>);
        void translateBy(point);
        virtual void translateTo(const point&);
    protected:
    private:
};

class Rectangle : public Shape
{
public:
    Rectangle(std::vector<point>);
    Rectangle();
    //Rectangle(sf::FloatRect);
    bool contains(point)const;
    bool success;
    void translateTo(const point&);
};
