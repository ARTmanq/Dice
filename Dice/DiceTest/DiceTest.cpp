// DiceTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest\gtest.h"
#include "C:\Users\dns\Documents\Visual Studio 2013\Projects\Dice\Dice\Dice.h"
#include <fstream>
#include <string>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(Dice_Constructor, All_Constructors)
{
	Dice a;
	EXPECT_EQ(0, a.getN());
	Dice b(3);
	EXPECT_EQ(3, b.getN());
	EXPECT_NEAR(3, b.getDice(1), 4);
	unsigned int arr[5];
	arr[0] = 1;
	arr[1] = 10;
	arr[2] = 2;
	arr[3] = 3;
	arr[4] = -1;
	Dice c(5, arr);
	EXPECT_EQ(3, c.getN());
	EXPECT_EQ(2, c.getDice(1));
	Dice d(b);
	EXPECT_EQ(3, d.getN());
	EXPECT_NEAR(3, d.getDice(1), 4);
	cout << a;
	cout << b;
	cout << c;
	cout << d;
}

TEST(Operators, Assignment)
{
	unsigned int arr[3] = { 1, 2, 3 }, arr2[4] = { 4, 5, 6, 4 };
	Dice a(3, arr);
	cout << a;
	Dice b(4, arr2);
	cout << b;
	a = b;
	EXPECT_EQ(4, a.getN());
	EXPECT_EQ(5, a.getDice(1));
}

TEST(Operators, PlusEq)
{
	unsigned int arr[5] = { 5, 4, 3, 2, 1 }, arr2[3] = { 1, 3, 5 };
	Dice a(5, arr);
	cout << a;
	EXPECT_ANY_THROW(a += 10);
	a += 3;
	EXPECT_EQ(6, a.getN());
	EXPECT_EQ(3, a.getDice(5));
	cout << a;
	Dice b(3, arr2);
	cout << b;
	a += b;
	EXPECT_EQ(9, a.getN());
	EXPECT_EQ(3, a.getDice(7));
	cout << a;
}

TEST(Operators, MinusEq)
{
	unsigned int arr[7] = { 1, 2, 3, 4, 6, 3, 4 }, arr2[6] = { 2, 6, 5, 2, 1, 4 }, arr3[3] = { 3, 2, 2 };
	Dice a(7, arr);
	cout << a;
	a -= 100;
	EXPECT_EQ(0, a.getN());
	cout << a;
	Dice b(6, arr2);
	cout << b;
	b -= 4;
	EXPECT_EQ(5, b.getN());
	EXPECT_EQ(4, b.getDice(4));
	EXPECT_ANY_THROW(b -= 10);
	cout << b;
	Dice c(3, arr3);
	cout << c;
	b -= c;
	EXPECT_EQ(3, b.getN());
	EXPECT_EQ(4, b.getDice(0));
	cout << b;
}

TEST(Operators, Index)
{
	unsigned int arr[9] = { 1, 3, 3, 6, 4, 2, 2, 5, 6 };
	Dice a(9, arr);
	cout << a;
	EXPECT_EQ(3, a[2]);
	a[2] = 6;
	EXPECT_EQ(6, a[2]);
	EXPECT_ANY_THROW(a[20]);
	cout << a;
}

TEST(Functions, Rollthedice)
{
	Dice a(10);
	a.RollTheDice();
	EXPECT_EQ(10, a.getN());
	EXPECT_NEAR(3, a.getDice(5), 3);
}

TEST(Functions, Coincidence)
{
	unsigned int arr[4] = { 5, 3, 6, 3 }, arr2[5] = { 1, 2, 3, 4, 5 };
	Dice a(10);
	cout << a;
	EXPECT_EQ(1, a.coincidence());
	Dice b(4, arr);
	cout << b;
	EXPECT_EQ(1, b.coincidence());
	Dice c(5, arr2);
	EXPECT_EQ(0, c.coincidence());
	cout << c;
}

TEST(Functions, Sum)
{
	unsigned int arr[15] = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 3, 2, 2, 4 };
	Dice a(15, arr);
	cout << a;
	EXPECT_EQ(47, a.sum());
}

TEST(Functions, Output)
{
	ofstream out1("test1.txt");
	unsigned int arr[6] = { 1, 2, 3, 4, 5, 6 };
	string right = "|   |  *|  *|* *|* *|* *\n| * |   | * |   | * |* *\n|   |*  |*  |* *|* *|* *\n\n";
	char check[77], buf;
	bool f = true;
	unsigned int i, m, j, CheckSize, l;
	Dice a(6, arr);
	out1 << a;
	out1.close();
	ifstream in1("test1.txt");
	m = right.size();
	in1.ignore();
	CheckSize = 25;
	l = 0;
	for (j = 0; j < 3; j++){
		in1.getline(check, CheckSize);
		for (i = 0; i < CheckSize - 1; i++){
			if (right[l + i] != check[i]){
				f = false;
				break;
			}
		}
		l += CheckSize;
	}
	in1.close();
	EXPECT_EQ(true, f);
}