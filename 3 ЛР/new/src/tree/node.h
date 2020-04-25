#pragma once

// local includes
#include "color.h"

template<typename Tk, typename Td>
class Node
{
public:
    Tk key;     //ключ объекта
    Td data;    //значение объекта в элементе
    Node *left;  // указатель на левого сына
    Node *right; //указатель на правого сына
    Node *parent;
    int n; //кол-во элементов в поддереве
    colors color;

    Node();
    Node(Td d, Tk k);
};

#include "node.cpp"
