#include "Rectangle.hpp"
#include<iostream>

RecTangle::RecTangle(double width,double height)
{
    if(width < 0||height < 0)
        throw -1;
    this->width = width;
    this->height = height;
}

RecTangle::RecTangle(const RecTangle& other)
{
    this->height = other.height;
    this->width = other.width;
}

RecTangle::~RecTangle()
{}//没有使用new方法，任其自动销毁

RecTangle RecTangle::operator=(const RecTangle& other)
{
    this->height = other.height;
    this->width = other.width;
    return *this;
}

double RecTangle::area()
{
    if(height < 0||width < 0)
        throw -1;
    double ans = 0.0;
    ans = this->height * this->width;
    return ans;
}

void RecTangle::resize(double scale)
{
    if(this->height < 0||this->width < 0||scale <= 0)
        throw -1;
    this->height *= scale;
    this->width *= scale;
}