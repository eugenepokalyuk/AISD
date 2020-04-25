#pragma once

// local includes
#include "tree.h"
#include "color.h"

template <typename Tk, typename Td>
class RBTree : public Tree<Tk, Td>
{
    enum Side
    {
        LEFT,
        RIGHT
    }; //сторона узла

    static colors red(Node<Tk, Td> *node);
    static Node<Tk, Td> *leftOf(Node<Tk, Td> *node);
    static Node<Tk, Td> *rightOf(Node<Tk, Td> *node);
    static Node<Tk, Td> *parentOf(Node<Tk, Td> *node);
    static void setColor(Node<Tk, Td> *node, colors color);

protected:
    Node<Tk, Td> *Rotate(Node<Tk, Td> *p, Side side);
    bool Insert(Node<Tk, Td> *&node, Tk key, Td value, Side sw);
    void Fixup(Node<Tk, Td> *x);

public:
    RBTree();                                // конструктор
    RBTree(const Tree<Tk, Td> &anotherTree); // конструктор копирования
    virtual ~RBTree();                       // деструктор
    bool Insert(Td obj, Tk key);             // включение нового элемента с заданным ключом
    bool Delete(Tk key);                     // удаление элемента с заданным ключом
};

#include "rbtree.cpp"
