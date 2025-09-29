#pragma once
#include<graphics.h>//easyXͼ�ο�
#include"BLOCK.h"
#include<vector>
#include<stdlib.h>

class GAME
{
public:
	GAME(int rows, int coles, int left, int top, int blocksize);//���캯��������Ϸ�����С
	void init();//��ʼ����Ϸ����,
	void play();//��Ϸ��ʼ
private:
	void KeyEvent();
	void updateWindow();//��Ⱦ
	void drop();
	void clearline();
	void rotate();//��ת����
	void drawscore();//��¼����

	int getDelay();//���ؾ�����һ�ε��øú���������೤ʱ��
private:
	int delay;
	bool update;//�ж��Ƿ����

	//-1����û���κη���
	//��Ӧ���ִ�����Ӧ���෽��
	std::vector<std::vector<int>> mapdata;

	int rounds;
	int lines;
	int leftmargin;
	int topmargin;
	int blocksize;
	IMAGE imgbackground;

	BLOCK* curblock;
	BLOCK* nextblock;//Ԥ�淽��
	BLOCK bakblock;//������һ���Ϸ�λ��

	int score;
};