#pragma once
#include<iostream>
#include <stack>
using namespace std;

#define BLACK false 
#define RED true

template <class Td, class Tk>
class Tree
{
protected:
	enum Side { LEFT, RIGHT }; //сторона узла
	extern class Node;
	Node *root;	//указатель на корень
	int size; //размер дерева
	int cnt; //Кол-во пройденных узлов (для тестирования)
	class Node
	{
	public:
		Tk key; //ключ объекта
		Td data; //значение объекта в элементе
		Node *left; // указатель на левого сына
		Node *right; //указатель на правого сына
		Node *parent; 
		int n; //кол-во элементов в поддереве
		bool color; 

		Node(Td d, Tk k) //конструктор с параметрами
		{ 
			key = k;
			data = d;
			left = right = parent= NULL;
			n=1;
			color=RED;
		}
		Node() //без параметров
		{
			key=NULL;
			data=NULL;
			left=right= parent= NULL;
			n=1;
			color=RED;
		}
	};

public:
	class Iterator
	{
		Tree *tree;
		Node *cur;
	public:
		Iterator(Tree<Td, Tk> *thistree);
		void begin();
		void end();
		void next();
		void prev();
		bool is_off();
		Td& operator *();
	};

public: 
	Tree(); //конструктор
	Tree(const Tree<Td, Tk> &anotherTree); //Конструктор копирования
	virtual ~Tree(); //деструктор
	bool Insert(Td obj, Tk key); //включение нового элемента с заданным ключом
	bool Delete(Tk key); //удаление элемента с заданным ключом	
	Td Search(Tk key); //поиск элемента с заданным ключом
	void ShowTree(); //вывод дерева на экран
	int GetSize(); //опрос размера дерева
	bool IsEmpty(); //проверка дерева на пустоту
	void t_L_R_Traversal(); //обход по дереву префиксный
	void Clear(); //очистка дерева
	Tk SelectK(int k); //поиск k-го ключа в дереве 
	int getCountNodesView(); //подсчет узлов 

protected:
	void Show(Node *r, int level); //вспомогательный метод для вывода дерева
	void t_L_R(Node *r); //обход узлов t->L->R (префиксный)
	void CopyTree(Node* r);	//Вспомогательная функция для копирования дерева	
	Node* Predecessor(Node *t); //поиск предыдущего по ключу узла
	Node* Max(Node *x); //узел с максимальным ключом
	Node* RParent(Node *t, Node *x);
	Node* Successor(Node *t); //поиск следующего по ключу узла
	Node* Min(Node *t); //узел с минимальным ключом
	Node* LParent(Node *t, Node *x);
	Node* BSTSelectK(Node *t, int k); // поиск по номеру 
};

template <class Td, class Tk>
Tree<Td, Tk>::Tree()
{
	root=NULL;
	size=0;
	cnt = 0;
}

template <class Td, class Tk>
Tree<Td, Tk>::Tree(const Tree<Td, Tk> &anotherTree)
{
	root = NULL;
	size = 0;
	CopyTree(anotherTree.root);
}

template <class Td, class Tk>
Tree<Td, Tk>::~Tree()
{
	Clear();
}

template <class Tk, class Td>
void Tree<Tk, Td>::Clear() 
{
	if (IsEmpty())
		return;
	stack<Node*> s1, s2;
	Node* t;
	s1.push(root);
	while (!s1.empty())
	{
		t = s1.top();
		s1.pop();
		s2.push(t);
		if (t->left!= NULL)
			s1.push(t->left);
		if (t->right!= NULL)
			s1.push(t->right);
		while (!s2.empty())
		{
			t = s2.top();
			s2.pop();
			delete t;
			size--;
		}
	}
	root = NULL;
	size = 0;
}

template <class Tk, class Td>
void Tree<Tk, Td>::CopyTree(typename Tree<Tk, Td>::Node* r)
{
	if (r == NULL)
		return;
	Insert(r->key, r->data);
	CopyTree(r->left);
	CopyTree(r->right);
}

template <class Td, class Tk> 
bool Tree<Td, Tk>::Insert(Td val, Tk key) 
{
	if (root == NULL) 
	{ 
		root = new Node(val, key); 
		size++; 
		return true; 
	} 

	Node *t = root, *pred = NULL; 
	while (t!= NULL) 
	{ 
		pred = t;  
		if (key == t->key)
		{
			t=root;
			while (t->key!= key) 
			{ 
				pred = t;  
				if (key<t->key) {t->n=t->n-1; t = t->left;} 
				else {t->n=t->n-1;t = t->right;}
			} 
			return false; //если ключи совпадают 
		}
		cnt++;
		if (key<t->key) {t->n=t->n+1; t = t->left;} 
		else {t->n=t->n+1; t = t->right; }
	} 

	if (key<pred->key) 
		pred->left = new Node(val, key); 
	else 
		pred->right = new Node(val, key); 

	size++;  
	cnt++;
	return true; 	
}

template <class Td, class Tk>
void Tree<Td,Tk>::Show(Node *r, int level)//вспомогательная функция для вывода структуры
{
	if(r == NULL)
		return;
	Show(r->right, level+1);
	for(int i = 0; i <= 3*level; i++)
		cout << " ";
	cout << r->key;
	(r->color==BLACK)? cout<<"B":cout<<"R"<< endl;
	Show(r->left, level+1);
}

template<class Td, class Tk>
bool Tree<Td, Tk>::Delete(Tk key)
{	

	cnt=0;
	Node *t = root, *pred = NULL, *x = NULL, *t0 = NULL;
	while (t!= NULL && t->key!= key) 
	{
		cnt++;
		pred = t;
		if (key < t->key) {t->n=t->n-1; t = t->left;}
		else {t->n=t->n-1; t = t->right;}
	}
	cnt++;
	if (t == NULL) //если ключи совпадают - откатиться назад
	{ 
		t=root;
		while (t!= NULL && t->key!= key) 
		{
			pred = t;
			if (key < t->key) {t->n=t->n+1; t = t->left;}
			else {t->n=t->n+1; t = t->right;}
		}
		return false;
	}
	if (t->left!= NULL && t->right!= NULL)
	{
		t0 = t;
		pred = t;
		t->n=t->n-1;
		t = t->right;
		while (t->left!= NULL) 
		{
			cnt++;
			pred = t;
			t->n=t->n-1;
			t = t->left;
		}	
		cnt++;
		x = t->right;
	}
	else 
	{
		t0 = NULL;
		if (t->left == NULL && t->right == NULL) x = NULL;	//Лист
		else if (t->left == NULL) {if (t->left!=NULL) x->n=x->n-1; x = t->right;}	
		else if (t->right == NULL) {if (t->right!=NULL) x->n=x->n-1; x = t->left;}
	}

	if (pred == NULL) root = x;
	else 
	{
		if (t->key<pred->key) pred->left = x;
		else pred->right = x;
	}

	if (t0 != NULL) 
	{
		t0->key = t->key;
		t0->data = t->data;
	}
	delete t;
	size--;
	return true;	
}

template<class Td, class Tk>
void Tree<Td, Tk>::ShowTree() //вывод структуры дерева на экран
{
	if(root == NULL)
	{
		return;
	}
	Show(root,0);
}

template<class Td, class Tk>
int Tree<Td, Tk>::GetSize()
{
	return size;
}

template<class Td, class Tk>
bool Tree<Td, Tk>::IsEmpty()
{
	return (size==0);
}

template<class Td, class Tk>
Td Tree<Td, Tk>::Search(Tk key)
{
	//cnt=0;
	Node *t = root;
	while(t!= NULL && t->key!=key)
	{
		if (key < t->key) t=t->left;
		else t=t->right;
		cnt++;
	}
	if (t == NULL) throw -1;
	else return t->data;
}

template<class Td, class Tk>
void Tree<Td, Tk>::t_L_R(Node *r)
{
	if(r==NULL) return;
	cout<<r->key<<" ";
	t_L_R(r->left);
	t_L_R(r->right);
}

template<class Td, class Tk>
void Tree<Td, Tk>::t_L_R_Traversal()
{
	t_L_R(root);	
}

template<class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::Predecessor(typename Tree<Td, Tk>::Node *x)
{
	if (x == NULL) return NULL;
	if (x->left != NULL)
		return Max(x->left);
	else return RParent(root, x);
}

template<class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::Max(typename Tree<Td, Tk>::Node *t)
{
	if (t==NULL) return NULL;
	while (t->right!= NULL)
	{
		t=t->right;
	}
	return t;
}

template <class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::RParent(typename Tree<Td, Tk>::Node *t, typename Tree<Td, Tk>::Node *x) 
{
	if (t == x) return NULL;
	if (x->key>t->key) {
		Node *rp = RParent(t->right, x);
		if (rp != NULL) return rp;
		else return t;
	}
	else return RParent(t->left, x);
}

template <class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::Successor(typename Tree<Td, Tk>::Node *x) 
{
	if (x == NULL) return NULL;
	//cnt++;
	if (x->right != NULL) return Min(x->right);	
	else return LParent(root, x);
}

template <class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::Min(typename Tree<Td, Tk>::Node *t) 
{
	if (t == NULL) return NULL;
	while (t->left != NULL) {t = t->left; cnt++;}
	return t;
}

template <class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::LParent(typename Tree<Td, Tk>::Node *t, typename Tree<Td, Tk>::Node *x) 
{
	if (t == x) return NULL;
	cnt++;
	if (x->key<t->key) 
	{
		cnt++;
		Node *lp = LParent(t->left, x);
		if (lp != NULL) return lp;
		else return t;
	}
	else return LParent(t->right, x);
}

template <class Td, class Tk>
typename Tree<Td, Tk>::Node* Tree<Td, Tk>::BSTSelectK(typename Tree<Td, Tk>::Node *t, int k) 
{
	int m;
	if (t==NULL) return t;
	if (t->left==NULL)	{ m=0; }
		else m=t->left->n;
	
	if (m > k)
		return BSTSelectK(t->left, k);
	if (m < k)
		return BSTSelectK(t->right, k-m-1);
	return t;
}

template <class Td, class Tk>
Tk Tree<Td, Tk>::SelectK(int k)
{
	Node *t = BSTSelectK(root, k);
	if(t==NULL) throw -1;
		return t->key;
}

template <class Td, class Tk>
Tree<Td, Tk>::Iterator::Iterator(Tree<Td, Tk> *thistree) 
{
	tree = thistree;
	cur = NULL;
}

template <class Td, class Tk>
void Tree<Td, Tk>::Iterator::begin()
{
	cur = tree->root;
	while (cur!= NULL && cur->left!= NULL) 
		cur = cur->left;
}

template <class Td, class Tk>
void Tree<Td, Tk>::Iterator::end()
{
	cur = tree->root;
	while (cur!= NULL && cur->right!= NULL) 
		cur = cur->right;
}

template <class Td, class Tk>
bool Tree<Td, Tk>::Iterator::is_off()
{
	return (cur==NULL);
}

template <class Td, class Tk>
Td& Tree<Td, Tk>::Iterator::operator *() 
{
	if (is_off()) 
		throw -1;
	return cur->data;
}

template <class Td, class Tk>
void Tree<Td, Tk>::Iterator::next()
{
	cur = tree->Successor(cur);
}

template <class Td, class Tk>
void Tree<Td, Tk>::Iterator::prev()
{
	cur = tree->Predecessor(cur);
}

template <class Td, class Tk>
int Tree<Td, Tk>::getCountNodesView() 
{
	int temp = cnt;
	cnt = 0;
	return temp;
}
