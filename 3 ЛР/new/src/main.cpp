
// standard includes
#include <iostream>
#include <string>
#include <math.h>

// local includes
#include "rbtree.h"
#include "test.h"

using namespace std; // cout, endl

int main()
{
	RBTree<int, int> tree;
	RBTree<int, int>::Iterator it = RBTree<int, int>::Iterator(&tree);

	while (true)
	{
		cout << endl
			 << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl
			 << endl;
		cout << "1. Просмотр дерева" << endl;
		cout << "2. Очистка дерева" << endl;
		cout << "3. Проверка на пустоту" << endl;
		cout << "4. Поиск объекта с заданным ключом" << endl;
		cout << "5. Добавление данных с заданным ключом" << endl;
		cout << "6. Удаление данных с заданным ключом" << endl;
		cout << "7. Опрос размера дерева" << endl;
		cout << "8. На первый узел" << endl;
		cout << "9. На последний узел" << endl;
		cout << "10. Проверка состояния итератора" << endl;
		cout << "11. Проверка значения текущего" << endl;
		cout << "12. Запись значения на позицию итератора" << endl;
		cout << "13. Следующий" << endl;
		cout << "14. Предыдущий" << endl;
		cout << "15. Тест случайного дерева" << endl;
		cout << "16. Тест вырожденного дерева" << endl;
		cout << endl
			 << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl
			 << endl;

		int t;
		int value, key;
		cin >> t;
		switch (t)
		{
		case 1:
			tree.ShowTree();
			break;
		case 2:
			tree.Clear();
			break;
		case 3:
			cout << tree.IsEmpty() << endl;
			break;
		case 4:
			cout << "Введите ключ: " << endl;
			cin >> key;
			try
			{
				cout << tree.Search(key) << endl;
			}
			catch (...)
			{
				cout << "Исключение" << endl;
			}
			break;
		case 5:
			cout << "Введите значение: " << endl;
			cin >> value;
			cout << "Введите ключ: " << endl;
			cin >> key;
			cout << tree.Insert(value, key) << endl;
			break;
		case 6:
			cout << "Введите ключ: " << endl;
			cin >> key;
			cout << tree.Delete(key) << endl;
			break;
		case 7:
			cout << "Текущий размер дерева: " << tree.GetSize() << endl;
			break;
		case 8:
			it.begin();
			break;
		case 9:
			it.end();
			break;
		case 10:
			cout << "За пределами: " << it.is_off() << endl;
			break;
		case 11:
			try
			{
				cout << "Текущий элемент: " << *it << endl;
			}
			catch (...)
			{
				cout << "Исключение" << endl;
			}
			break;
		case 12:
			cout << "Введите значение: " << endl;
			cin >> value;
			try
			{
				*it = value;
			}
			catch (...)
			{
				cout << "Исключение" << endl;
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
			cout << "Введите размер дерева:" << endl;
			cin >> n;
			TestEffect::test_rand(n);
			break;
		case 16:
			int n2;
			cout << "Введите размер дерева:" << endl;
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

    return 0;
}
