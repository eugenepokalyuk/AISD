#pragma once

// local imports
#include "node.h"

template <typename Tk, typename Td>
class Tree
{
public:
	class Iterator
	{
		Tree<Tk, Td> *tree;
		Node<Tk, Td> *cur;

	public:
		Iterator(Tree<Tk, Td> *thistree);
		void begin();
		void end();
		void next();
		void prev();
		bool is_off();
		int &operator*();
	};

	Tree();								   //конструктор
	Tree(const Tree &anotherTree); //Конструктор копирования
	virtual ~Tree();					   //деструктор
	bool Insert(int obj, int key);		   //включение нового элемента с заданным ключом
	bool Delete(int key);				   //удаление элемента с заданным ключом
	int Search(int key);					   //поиск элемента с заданным ключом
	void ShowTree();					   //вывод дерева на экран
	int GetSize();						   //опрос размера дерева
	bool IsEmpty();						   //проверка дерева на пустоту
	void t_L_R_Traversal();				   //обход по дереву префиксный
	void Clear();						   //очистка дерева
	int SelectK(int k);					   //поиск k-го ключа в дереве
	int getCountNodesView();			   //подсчет узлов

protected:
	Node<Tk, Td> *root; //указатель на корень
	int size;			//размер дерева
	int cnt;			//Кол-во пройденных узлов (для тестирования)

	void Show(Node<Tk, Td> *r, int level);		//вспомогательный метод для вывода дерева
	void t_L_R(Node<Tk, Td> *r);				//обход узлов t->L->R (префиксный)
	void CopyTree(Node<Tk, Td> *r);				//Вспомогательная функция для копирования дерева
	Node<Tk, Td> *Predecessor(Node<Tk, Td> *t); //поиск предыдущего по ключу узла
	Node<Tk, Td> *Max(Node<Tk, Td> *x);			//узел с максимальным ключом
	Node<Tk, Td> *RParent(Node<Tk, Td> *t, Node<Tk, Td> *x);
	Node<Tk, Td> *Successor(Node<Tk, Td> *t); //поиск следующего по ключу узла
	Node<Tk, Td> *Min(Node<Tk, Td> *t);		  //узел с минимальным ключом
	Node<Tk, Td> *LParent(Node<Tk, Td> *t, Node<Tk, Td> *x);
	Node<Tk, Td> *BSTSelectK(Node<Tk, Td> *t, int k); // поиск по номеру
};

#include "tree.cpp"
#include "iterator.cpp"
