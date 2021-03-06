// avl-tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <crtdbg.h>

#include "avl_tree.h"

using namespace std;

struct test_s
{
	int a, b, c;
};


void test_avl()
{
	AVLTree<int, test_s> tree;
	size_t count = 0;

	for (int i = 0; i < 100; i += 2)
	{
		count++;
		tree[i] = test_s{ i,i * i, i * i * i };
	}

	_ASSERT(tree.size() == count);

	for (int i = 0; i < 100; i += 2)
	{
		if (tree[i].a == i && tree[i].b == i * i && tree[i].c == i * i * i)
		{
			cout << "Verify value by key OK:" << i << endl;
		}
	}

	for (int i = 1; i < 100; i += 2)
	{
		count++;
		if (tree[i].a == 0 && tree[i].b == 0 && tree[i].c == 0)
		{
			cout << "Verify uninserted value by key OK:" << i << endl;
		}
	}

	_ASSERT(tree.size() == count);

	for (int i = 0; i < 100; i += 2)
	{
		tree.remove(i);

		if (tree[i].a == 0 && tree[i].b == 0 && tree[i].c == 0)
		{
			cout << "Verify removed value by key OK:" << i << endl;
		}
	}

	for (int i = 0; i < 100; i += 2)
	{
		tree[i] = test_s{ i,i * i, i * i * i };
	}

	tree.clear();

	_ASSERT(tree.size() == 0);


	for (int i = 0; i < 100; i += 2)
	{
		tree[i] = test_s{ i,i * i, i * i * i };
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	test_avl();

	return 0;
}