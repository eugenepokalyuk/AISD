#pragma once
#include<iostream>
#include <conio.h>
#include <string>
#include <conio.h>
#include <math.h>
#include "BSTTree.h"
#include "RBTree.h"
using namespace std;

namespace TestEffect
{
	void test_rand(int n);
	void test_sort(int n);
	typedef unsigned long long INT_64;
	INT_64 lrand() { return rand() << 16 | rand(); }
}
void main()
{
	RBTree<int, int> tree;
	RBTree<int, int>::Iterator it = RBTree<int, int>::Iterator(&tree);
	setlocale(LC_ALL,"RUS");
	while(true) 
	{
		cout<< endl << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl << endl;
		cout<<"1. �������� ������"<<endl;
		cout<<"2. ������� ������"<<endl;
		cout<<"3. �������� �� �������"<<endl;
		cout<<"4. ����� ������� � �������� ������"<<endl;
		cout<<"5. ���������� ������ � �������� ������"<<endl;		
		cout<<"6. �������� ������ � �������� ������"<<endl;
		cout<<"7. ����� ������� ������"<<endl;
		cout<<"8. �� ������ ����"<<endl;
		cout<<"9. �� ��������� ����"<<endl;
		cout<<"10. �������� ��������� ���������"<<endl;
		cout<<"11. �������� �������� ��������"<<endl;
		cout<<"12. ������ �������� �� ������� ���������"<<endl;
		cout<<"13. ���������"<<endl;
		cout<<"14. ����������"<<endl;
		cout<<"15. ���� ���������� ������"<<endl;
		cout<<"16. ���� ������������ ������"<<endl;
		cout<< endl << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl << endl;

		int t;
		int value, key;
		cin >> t;
		switch(t) 
		{
		case 1:
			tree.ShowTree();
			break;
		case 2:
			tree.Clear();
			break;
		case 3:
			cout<<tree.IsEmpty()<<endl;
			break;
		case 4:
			cout<<"������� ����: "<<endl;
			cin >> key;
			try 
			{
				cout << tree.Search(key) << endl;
			}
			catch(...) { cout<<"����������"<<endl; }
			break;
		case 5:
			cout<<"������� ��������: "<<endl;
			cin>>value;
			cout<<"������� ����: "<<endl;
			cin>>key;
			cout<<tree.Insert(value, key)<<endl;			
			break;
		case 6:
			cout<<"������� ����: "<<endl;
			cin>>key;
			cout<<tree.Delete(key)<<endl;			
			break;
		case 7:
			cout<<"������� ������ ������: "<<tree.GetSize()<<endl;
			break;
		case 8:
			it.begin();
			break;
		case 9:
			it.end();
			break;
		case 10:
			cout<< "�� ���������: "<<it.is_off() << endl;
			break;
		case 11:
			try 
			{
				cout<<"������� �������: "<< *it <<endl;
			}
			catch (...)
			{
				cout<<"����������"<<endl;
			}
			break;
		case 12:
			cout<<"������� ��������: "<<endl;
			cin>>value;
			try 
			{
				*it = value;
			}
			catch(...) 
			{
				cout<<"����������"<<endl;
			}
			break;
		case 13:
			it.next();
			break;	
		case 14:
			it.prev();
			break;
		case 15:
			int n;
			cout << "������� ������ ������:" << endl;
			cin >> n;
			TestEffect::test_rand(n);
			break;
		case 16:
			int n2;
			cout << "������� ������ ������:" << endl;
			cin >> n2;
			TestEffect::test_sort(n2);
			break;	
		case 17:
		
			break;
		case 18:
		
			break;
		case 20:
			
			break;
		}
	}
}

void TestEffect::test_rand(int n)
{
	RBTree<int, INT_64> tree;
	Tree<int, INT_64> BSTtree;
	INT_64* m = new INT_64[n];
	for (int i = 0; i < n; i++)
	{
		m[i] = lrand();
		tree.Insert(1, m[i]);
		BSTtree.Insert(1, m[i]);
	}
	tree.getCountNodesView();

	cout << "������ ������ ��: " << tree.GetSize() << endl;
	cout<<endl;
	double I = 0;
	double D = 0;
	double S = 0;
	double Ib=0;
	double Db=0;
	double Sb=0;

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
			try {
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

	cout << "������ RB-������ �����: " << tree.GetSize() << endl;
	cout << "1.002*log2(n)=" << 1.002*(log((double)n) / log((double)2)) << endl;
	cout << "�������: " << I / (n / 2) << endl;
	cout << "��������: " << D / (n / 2) << endl;
	cout << "�����: " << S / (n / 2) << endl;
	cout<< endl;
	cout << "������ BST-������ �����: " << BSTtree.GetSize() << endl;
	cout << "1.39*log2(n)=" << 1.39*(log((double)n) / log((double)2)) << endl;
	cout << "�������: " << Ib / (n / 2) << endl;
	cout << "��������: " << Db / (n / 2) << endl;
	cout << "�����: " << Sb / (n / 2) << endl;

	delete[] m;
}

void TestEffect::test_sort(int n)
{
	RBTree<int, INT_64> tree;
	Tree<int, INT_64> BSTtree;

	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++) 
	{
		m[i] = i * 1000;
		tree.Insert(1, m[i]);
		BSTtree.Insert(1, m[i]);
	}
	tree.getCountNodesView();
	BSTtree.getCountNodesView();
	cout << "������ ������ ��: " << tree.GetSize() << endl;
	cout<<endl;
	double I = 0;
	double D = 0;
	double S = 0;
	double Ib=0;
	double Db=0;
	double Sb=0;

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
			try {
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
	cout << "������ RB-������ �����: " << tree.GetSize() << endl;
	cout << "1.002*log2(n)=" << 1.002*(log((double)n) / log((double)2)) << endl;
	cout << "�������: " << I / (n / 2) << endl;
	cout << "��������: " << D / (n / 2) << endl;
	cout << "�����: " << S / (n / 2) << endl;
	cout<<endl;
	cout << "������ BST-������ �����: " << BSTtree.GetSize() << endl;
	cout << "n/2=" << n / 2 << endl;
	cout << "�������: " << Ib / (n / 2) << endl;
	cout << "��������: " << Db / (n / 2) << endl;
	cout << "�����: " << Sb / (n / 2) << endl;
	delete[] m;
}

