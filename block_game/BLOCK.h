#pragma once
#include<stdlib.h>
#include<vector>
#include<graphics.h>//easyXͼ�ο�

struct Point {
	int row;
	int col;
};//ȷ���������λ��




class BLOCK
{
public:
	BLOCK();//���캯����С�����λ��

	void drop();
	void moveLeftRight(int offset);
	void draw(int leftMargin,int topMargin);//��������
	void rotate();//��ת����
	void solidify(std::vector<std::vector<int>>& mapdata);
	int getblockType();
	BLOCK& operator=(const BLOCK& other);
	bool blockInmap(const std::vector<std::vector<int>>&mapdata);
	static IMAGE** getImages();

private:
	int blockType;//��������
	Point singleBlock[4];
	IMAGE *img;

	static IMAGE* imgs[7];
	static int size;//�����С
};