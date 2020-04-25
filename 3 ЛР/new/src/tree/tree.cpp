
// standard includes
#include <iostream>
#include <stack>

template <typename Tk, typename Td>
Tree<Tk, Td>::Tree()
{
	root = nullptr;
	size = 0;
	cnt = 0;
}

template <typename Tk, typename Td>
Tree<Tk, Td>::Tree(const Tree &anotherTree)
{
	root = nullptr;
	size = 0;
	CopyTree(anotherTree.root);
}

template <typename Tk, typename Td>
Tree<Tk, Td>::~Tree()
{
	Clear();
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::Clear()
{
	if (IsEmpty())
		return;
	std::stack<Node<Tk, Td> *> s1, s2;
	Node<Tk, Td> *t;
	s1.push(root);
	while (!s1.empty())
	{
		t = s1.top();
		s1.pop();
		s2.push(t);
		if (t->left != nullptr)
			s1.push(t->left);
		if (t->right != nullptr)
			s1.push(t->right);
		while (!s2.empty())
		{
			t = s2.top();
			s2.pop();
			delete t;
			size--;
		}
	}
	root = nullptr;
	size = 0;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::CopyTree(Node<Tk, Td> *r)
{
	if (r == nullptr)
		return;
	Insert(r->key, r->data);
	CopyTree(r->left);
	CopyTree(r->right);
}

template <typename Tk, typename Td>
bool Tree<Tk, Td>::Insert(int val, int key)
{
	if (root == nullptr)
	{
		root = new Node<Tk, Td>(val, key);
		size++;
		return true;
	}

	Node<Tk, Td> *t = root, *pred = nullptr;
	while (t != nullptr)
	{
		pred = t;
		if (key == t->key)
		{
			t = root;
			while (t->key != key)
			{
				pred = t;
				if (key < t->key)
				{
					t->n = t->n - 1;
					t = t->left;
				}
				else
				{
					t->n = t->n - 1;
					t = t->right;
				}
			}
			return false; //если ключи совпадают
		}
		cnt++;
		if (key < t->key)
		{
			t->n = t->n + 1;
			t = t->left;
		}
		else
		{
			t->n = t->n + 1;
			t = t->right;
		}
	}

	if (key < pred->key)
		pred->left = new Node<Tk, Td>(val, key);
	else
		pred->right = new Node<Tk, Td>(val, key);

	size++;
	cnt++;
	return true;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::Show(Node<Tk, Td> *r, int level) //вспомогательная функция для вывода структуры
{
	if (r == nullptr)
		return;
	Show(r->right, level + 1);
	for (int i = 0; i <= 3 * level; i++)
		std::cout << " ";
	std::cout << r->key;
	(r->color == BLACK) ? std::cout << "B" : std::cout << "R" << std::endl;
	Show(r->left, level + 1);
}

template <typename Tk, typename Td>
bool Tree<Tk, Td>::Delete(int key)
{

	cnt = 0;
	Node<Tk, Td> *t = root, *pred = nullptr, *x = nullptr, *t0 = nullptr;
	while (t != nullptr && t->key != key)
	{
		cnt++;
		pred = t;
		if (key < t->key)
		{
			t->n = t->n - 1;
			t = t->left;
		}
		else
		{
			t->n = t->n - 1;
			t = t->right;
		}
	}
	cnt++;
	if (t == nullptr) //если ключи совпадают - откатиться назад
	{
		t = root;
		while (t != nullptr && t->key != key)
		{
			pred = t;
			if (key < t->key)
			{
				t->n = t->n + 1;
				t = t->left;
			}
			else
			{
				t->n = t->n + 1;
				t = t->right;
			}
		}
		return false;
	}
	if (t->left != nullptr && t->right != nullptr)
	{
		t0 = t;
		pred = t;
		t->n = t->n - 1;
		t = t->right;
		while (t->left != nullptr)
		{
			cnt++;
			pred = t;
			t->n = t->n - 1;
			t = t->left;
		}
		cnt++;
		x = t->right;
	}
	else
	{
		t0 = nullptr;
		if (t->left == nullptr && t->right == nullptr)
			x = nullptr; //Лист
		else if (t->left == nullptr)
		{
			if (t->left != nullptr)
				x->n = x->n - 1;
			x = t->right;
		}
		else if (t->right == nullptr)
		{
			if (t->right != nullptr)
				x->n = x->n - 1;
			x = t->left;
		}
	}

	if (pred == nullptr)
		root = x;
	else
	{
		if (t->key < pred->key)
			pred->left = x;
		else
			pred->right = x;
	}

	if (t0 != nullptr)
	{
		t0->key = t->key;
		t0->data = t->data;
	}
	delete t;
	size--;
	return true;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::ShowTree() //вывод структуры дерева на экран
{
	if (root == nullptr)
	{
		return;
	}
	Show(root, 0);
}

template <typename Tk, typename Td>
int Tree<Tk, Td>::GetSize()
{
	return size;
}

template <typename Tk, typename Td>
bool Tree<Tk, Td>::IsEmpty()
{
	return (size == 0);
}

template <typename Tk, typename Td>
int Tree<Tk, Td>::Search(int key)
{
	//cnt=0;
	Node<Tk, Td> *t = root;
	while (t != nullptr && t->key != key)
	{
		if (key < t->key)
			t = t->left;
		else
			t = t->right;
		cnt++;
	}
	if (t == nullptr)
		throw - 1;
	else
		return t->data;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::t_L_R(Node<Tk, Td> *r)
{
	if (r == nullptr)
		return;
	std::cout << r->key << " ";
	t_L_R(r->left);
	t_L_R(r->right);
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::t_L_R_Traversal()
{
	t_L_R(root);
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::Predecessor(Node<Tk, Td> *x)
{
	if (x == nullptr)
		return nullptr;
	if (x->left != nullptr)
		return Max(x->left);
	else
		return RParent(root, x);
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::Max(Node<Tk, Td> *t)
{
	if (t == nullptr)
		return nullptr;
	while (t->right != nullptr)
	{
		t = t->right;
	}
	return t;
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::RParent(Node<Tk, Td> *t, Node<Tk, Td> *x)
{
	if (t == x)
		return nullptr;
	if (x->key > t->key)
	{
		Node<Tk, Td> *rp = RParent(t->right, x);
		if (rp != nullptr)
			return rp;
		else
			return t;
	}
	else
		return RParent(t->left, x);
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::Successor(Node<Tk, Td> *x)
{
	if (x == nullptr)
		return nullptr;
	//cnt++;
	if (x->right != nullptr)
		return Min(x->right);
	else
		return LParent(root, x);
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::Min(Node<Tk, Td> *t)
{
	if (t == nullptr)
		return nullptr;
	while (t->left != nullptr)
	{
		t = t->left;
		cnt++;
	}
	return t;
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::LParent(Node<Tk, Td> *t, Node<Tk, Td> *x)
{
	if (t == x)
		return nullptr;
	cnt++;
	if (x->key < t->key)
	{
		cnt++;
		Node<Tk, Td> *lp = LParent(t->left, x);
		if (lp != nullptr)
			return lp;
		else
			return t;
	}
	else
		return LParent(t->right, x);
}

template <typename Tk, typename Td>
Node<Tk, Td> *Tree<Tk, Td>::BSTSelectK(Node<Tk, Td> *t, int k)
{
	int m;
	if (t == nullptr)
		return t;
	if (t->left == nullptr)
	{
		m = 0;
	}
	else
		m = t->left->n;

	if (m > k)
		return BSTSelectK(t->left, k);
	if (m < k)
		return BSTSelectK(t->right, k - m - 1);
	return t;
}

template <typename Tk, typename Td>
int Tree<Tk, Td>::SelectK(int k)
{
	Node<Tk, Td> *t = BSTSelectK(root, k);
	if (t == nullptr)
		throw - 1;
	return t->key;
}

template <typename Tk, typename Td>
int Tree<Tk, Td>::getCountNodesView()
{
	int temp = cnt;
	cnt = 0;
	return temp;
}
