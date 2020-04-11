#pragma once
#include<iostream>
#include <stack>
#include "BSTTree.h"
using namespace std;

template <class Td, class Tk>
class RBTree : virtual public Tree < Td, Tk >
{ 
	static bool red(Node* node) 
	{
		return node ? (node->color == RED) : false;
	}

	static Node* leftOf(Node* node) 
	{
		return node ? node->left : NULL;
	}

	static Node* rightOf(Node* node) 
	{
		return node ? node->right : NULL;
	}

	static Node* parentOf(Node* node) 
	{
		return node ? node->parent : NULL;
	}

	static void setColor(Node* node, bool color) {
		if (node) node->color = color;
	}
public:
	RBTree():Tree() {} //конструктор
	RBTree(const Tree<Td, Tk> &anotherTree): Tree(anotherTree){} //Конструктор копирования
	virtual ~RBTree(); //деструктор
	bool Insert(Td obj, Tk key); //включение нового элемента с заданным ключом
	bool Delete(Tk key); //удаление элемента с заданным ключом	
protected:
	Node* Rotate(Node* p, Side side);
	bool Insert(Node*& node, Tk key, Td value, Side sw);
	void Fixup(Node *x);

};

template <class Td, class Tk>
RBTree<Td, Tk>::~RBTree()
{
	Clear();
}

template <class Td, class Tk>
typename Tree<Td, Tk>::Node* RBTree<Td, Tk>::Rotate(Node* p, Side side) 
{
	if (!p) return NULL;
	if (side == LEFT) 
	{
		Node* r = p->right;
		p->right = r->left;
		if (r->left) r->left->parent = p;
		r->parent = p->parent;
		if (!p->parent) 
		{
			root = r;
		} 
		else if (p->parent->left == p) 
		{
			p->parent->left = r;
		} 
		else 
		{
			p->parent->right = r;
		}
		r->left = p;
		p->parent = r;
		return r;
	} 
	else 
	{
		Node* l = p->left;
		p->left = l->right;
		if (l->right) l->right->parent = p;
		l->parent = p->parent;
		if (!p->parent) 
		{
			root = l;
		} 
		else if (p->parent->right == p) 
		{
			p->parent->right = l;
		} 
		else 
		{
			p->parent->left = l;
		}
		l->right = p;
		p->parent = l;
		return l;
	}
}

template <class Td, class Tk>
bool RBTree<Td, Tk>::Insert(Node*& node, Tk key, Td value, Side sw) 
{		
		cnt++;
		if (!node) 
		{
			node = new Node(value, key);
			cnt++;
			return true;
		}
		if (red(node->left) && red(node->right)) 
		{
			node->color = RED;
			node->left->color = BLACK;
			node->right->color = BLACK;
		}
		bool success;
		if (node->key == key) 
		{
			return false;
		} 
		else if (key < node->key) 
		{
			success = Insert(node->left, key, value, LEFT);
			node->left->parent = node;
			if (red(node) && red(node->left) && (sw == RIGHT)) 
			{
				node = Rotate(node, RIGHT);
			}
			if (red(node->left) && red(node->left->left)) 
			{
				node = Rotate(node, RIGHT);
				node->color = BLACK;
				node->right->color = RED;
			}
		} 
		else 
		{
			success = Insert(node->right, key, value, RIGHT);
			node->right->parent = node;
			if (red(node) && red(node->right) && (sw == LEFT)) 
			{
				node = Rotate(node, LEFT);
			}
			if (red(node->right) && red(node->right->right)) 
			{
				node = Rotate(node, LEFT);
				node->color = BLACK;
				node->left->color = RED;
			}
		}
		return success;
	}

template <class Td, class Tk>
bool RBTree<Td, Tk>::Insert(Td value, Tk key) 
{
	cnt = 0;
	bool success = Insert(root, key, value, LEFT);
	if (!success) return false;
	root->color = BLACK;
	size++;
	return true;
}

template <class Td, class Tk>
bool RBTree<Td, Tk>::Delete(Tk key) 
{
	cnt = 0;
	Node *t = root, *x = NULL;
	while (t!= NULL && t->key!= key) 
	{
		if (key < t->key) t = t->left;
		else t = t->right;
		cnt++;
	}	
	if (t == NULL)	return false;
	cnt++;
	if(t->left && t->right)
	{
		x=Successor(t);
		t->key=x->key;
		t->data=t->data;
		t=x;
	}
	 Node* replacement = (t->left ? t->left : t->right);

        if (replacement) 
		{
			t->key=replacement->key;
			t->data=replacement->data;
			t->left = t->right = NULL;
			t = replacement;
        } 
		else if (!t->parent) 
		{
            root = NULL;
        } 
		else 
		{
            if (t->color == BLACK)
                Fixup(t);

            if (t->parent) 
			{
                if (t == t->parent->left)
                    t->parent->left = NULL;
                else if (t == t->parent->right)
                    t->parent->right = NULL;
                t->parent = NULL;
            }
        }
		delete t;
		size--;
		return true;
}

template <class Td, class Tk>
void RBTree<Td, Tk>::Fixup(Node* x) 
{
		while (x != root && red(x) == BLACK) 
		{
            if (x == leftOf(parentOf(x))) 
			{
                Node* sib = rightOf(parentOf(x));

                if (red(sib) == RED) {
                    setColor(sib, BLACK);
                    setColor(parentOf(x), RED);
                    Rotate(parentOf(x), LEFT);
                    sib = rightOf(parentOf(x));
                }

                if (!red(leftOf(sib)) && !red(rightOf(sib))) {
                    setColor(sib, RED);
                    x = parentOf(x);
                } else {
                    if (red(rightOf(sib)) == BLACK) {
                        setColor(leftOf(sib), BLACK);
                        setColor(sib, RED);
                        Rotate(sib, RIGHT);
                        sib = rightOf(parentOf(x));
                    }
                    setColor(sib, red(parentOf(x))); //цвет sib  становится цветом отца x
                    setColor(parentOf(x), BLACK);
                    setColor(rightOf(sib), BLACK);
                    Rotate(parentOf(x), LEFT);
                    x = root;
                }
            } else { // симметрично
                Node* sib = leftOf(parentOf(x));

                if (red(sib) == RED) {
                    setColor(sib, BLACK);
                    setColor(parentOf(x), RED);
                    Rotate(parentOf(x), RIGHT);
                    sib = leftOf(parentOf(x));
                }

                if (red(rightOf(sib)) == BLACK &&
                    red(leftOf(sib)) == BLACK) {
                    setColor(sib, RED);
                    x = parentOf(x);
                } else {
                    if (red(leftOf(sib)) == BLACK) {
                        setColor(rightOf(sib), BLACK);
                        setColor(sib, RED);
                        Rotate(sib, LEFT);
                        sib = leftOf(parentOf(x));
                    }
                    setColor(sib, red(parentOf(x)));
                    setColor(parentOf(x), BLACK);
                    setColor(leftOf(sib), BLACK);
                    Rotate(parentOf(x), RIGHT);
                    x = root;
                }
            }
        }

        setColor(x, BLACK);
}

