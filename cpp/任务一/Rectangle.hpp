#ifndef Rectangle.hpp
#define Rectangle.hpp

#include<iostream>

class RecTangle {
    private:
        double width,height;
    public:
        RecTangle(double width,double heiht);//构造
        RecTangle(const RecTangle &other);//拷贝构造
        RecTangle operator=(const RecTangle &other);//重载运算符
        double area();//计算面积
        void resize(double scale);//缩放
        friend bool isSquare(RecTangle& obj);//友元函数
        ~RecTangle();//析构函数
};

#endif