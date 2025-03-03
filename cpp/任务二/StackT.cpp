//没有做选做的功能

#include<iostream>
#include<vector>//应该可以用吧（）
using namespace std;

template<typename T>  

class Stack{
    private:
        int length;
        vector<T>stack;
    public;
        Stack()
        {
            this->length = 0;
            this->stack = vector<T>(0);
        }
        Stack(const Stack& other)
        {
            this->length = other.length;
            for(int i = 0;i < other.length;i++)
            {
                this->stack.push_back(other.stack[i])
            }
        }
        firend int size()
        {
            return this->length;
        }
        void push(T value)
        {
            this->stack.push_back(T);
            this->length += 1;
        }
        void pop()
        {
            if(this->length > 0)
                this->stack.pop_back();
            else
                throw -1;
        }
        T top()
        {
            if(this->length == 0)
                throw -1;
            return this->stack.back();
        }
        bool isEmpty()
        {
            if(this->length == 0)
                return true;
            else 
                return false;
        }
};
