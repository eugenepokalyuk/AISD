
// standard includes
#include <iostream>
#include <cmath>

// local includes
#include "rbtree.h"
#include "test.h"

using namespace std; // cout, endl

TestEffect::INT_64 TestEffect::lrand()
{
    return std::rand() << 16 | rand();
}

void TestEffect::test_rand(int n)
{
    RBTree<int, INT_64> tree;
    Tree<int, INT_64> BSTtree;
    INT_64 *m = new INT_64[n];
    for (int i = 0; i < n; i++)
    {
        m[i] = lrand();
        tree.Insert(1, m[i]);
        BSTtree.Insert(1, m[i]);
    }
    tree.getCountNodesView();

    cout << "Размер дерева до: " << tree.GetSize() << endl;
    cout << endl;
    double I = 0;
    double D = 0;
    double S = 0;
    double Ib = 0;
    double Db = 0;
    double Sb = 0;

    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)
        {
            tree.Delete(lrand());
            BSTtree.Delete(lrand());
            D += tree.getCountNodesView();
            Db += BSTtree.getCountNodesView();
            tree.Insert(1, m[rand() % n]);
            BSTtree.Insert(1, m[rand() % n]);
            I += tree.getCountNodesView();
            Ib += BSTtree.getCountNodesView();
            try
            {
                tree.Search(lrand());
                BSTtree.Search(lrand());
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
            catch (...)
            {
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
        }
        else
        {
            int ind = rand() % n;
            tree.Delete(m[ind]);
            BSTtree.Delete(m[ind]);
            D += tree.getCountNodesView();
            Db += BSTtree.getCountNodesView();
            INT_64 key = lrand();
            tree.Insert(1, key);
            BSTtree.Insert(1, key);
            I += tree.getCountNodesView();
            Ib += BSTtree.getCountNodesView();
            m[ind] = key;
            try
            {
                tree.Search(m[rand() % n]);
                BSTtree.Search(m[rand() % n]);
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
            catch (...)
            {
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
        }

    cout << "Размер RB-дерева после: " << tree.GetSize() << endl;
    cout << "1.002*log2(n)=" << 1.002 * (log((double)n) / log((double)2)) << endl;
    cout << "Вставка: " << I / (n / 2) << endl;
    cout << "Удаление: " << D / (n / 2) << endl;
    cout << "Поиск: " << S / (n / 2) << endl;
    cout << endl;
    cout << "Размер BST-дерева после: " << BSTtree.GetSize() << endl;
    cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log((double)2)) << endl;
    cout << "Вставка: " << Ib / (n / 2) << endl;
    cout << "Удаление: " << Db / (n / 2) << endl;
    cout << "Поиск: " << Sb / (n / 2) << endl;

    delete[] m;
}

void TestEffect::test_sort(int n)
{
    RBTree<int, INT_64> tree;
    Tree<int, INT_64> BSTtree;

    INT_64 *m = new INT_64[n];

    for (int i = 0; i < n; i++)
    {
        m[i] = i * 1000;
        tree.Insert(1, m[i]);
        BSTtree.Insert(1, m[i]);
    }
    tree.getCountNodesView();
    BSTtree.getCountNodesView();
    cout << "Размер дерева до: " << tree.GetSize() << endl;
    cout << endl;
    double I = 0;
    double D = 0;
    double S = 0;
    double Ib = 0;
    double Db = 0;
    double Sb = 0;

    for (int i = 0; i < n / 2; i++)
    {
        if (i % 10 == 0)
        {
            int k = lrand() % (1000 * n);
            k = k + !(k % 2);
            tree.Delete(k);
            BSTtree.Delete(k);
            D += tree.getCountNodesView();
            Db += BSTtree.getCountNodesView();
            tree.Insert(1, m[rand() % n]);
            BSTtree.Insert(1, m[rand() % n]);
            I += tree.getCountNodesView();
            Ib += BSTtree.getCountNodesView();
            k = lrand() % (1000 * n);
            k = k + !(k % 2);
            try
            {
                tree.Search(k);
                BSTtree.Search(k);
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
            catch (...)
            {
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
        }
        else
        {
            int ind = rand() % n;
            try
            {
                tree.Search(m[rand() % n]);
                BSTtree.Search(m[rand() % n]);
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
            catch (...)
            {
                S += tree.getCountNodesView();
                Sb += BSTtree.getCountNodesView();
            }
            tree.Delete(m[ind]);
            BSTtree.Delete(m[ind]);
            D += tree.getCountNodesView();
            Db += BSTtree.getCountNodesView();
            int k = lrand() % (1000 * n);
            k = k + k % 2;
            tree.Insert(1, k);
            BSTtree.Insert(1, k);
            I += tree.getCountNodesView();
            Ib += BSTtree.getCountNodesView();
            m[ind] = k;
        }
    }
    cout << "Размер RB-дерева после: " << tree.GetSize() << endl;
    cout << "1.002*log2(n)=" << 1.002 * (log((double)n) / log((double)2)) << endl;
    cout << "Вставка: " << I / (n / 2) << endl;
    cout << "Удаление: " << D / (n / 2) << endl;
    cout << "Поиск: " << S / (n / 2) << endl;
    cout << endl;
    cout << "Размер BST-дерева после: " << BSTtree.GetSize() << endl;
    cout << "n/2=" << n / 2 << endl;
    cout << "Вставка: " << Ib / (n / 2) << endl;
    cout << "Удаление: " << Db / (n / 2) << endl;
    cout << "Поиск: " << Sb / (n / 2) << endl;
    delete[] m;
}
