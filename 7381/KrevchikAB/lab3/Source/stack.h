#include <cstddef>
#include <iostream>
#include <cstring>
#define INIT_SIZE 2
#ifndef STACK_H
#define STACK_H

class Underflow{
public:
    std::string str_what;
    Underflow(std::string);
};

class Stack{
public:
    virtual void push(char ch) = 0;
    virtual char pop() = 0;
    virtual char top() = 0;
    virtual bool empty() = 0;


};

class Array_stack: public Stack{
    char *data;
    size_t size;
    size_t ontop;
public:
    Array_stack();
    ~Array_stack();
    void push(char ch);
    char pop();
    char top();
    void resize();
    bool empty();

};

#endif // STACK_H
