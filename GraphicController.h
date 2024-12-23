#pragma once
#include<vector>
#include<iostream>

using namespace std;
struct node
{
	int x;
	int y;
	int data;
	node(){}
	node(int _x, int _y, int _data) : x(_x), y(_y), data(_data) {}
};

class GraphicController
{
public:
	GraphicController();
	void drawBoard(vector<node> v);
};

