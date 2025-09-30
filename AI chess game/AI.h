#pragma once
#include"chess.h"
#include<vector>
//��������ÿ�������ӵļ�ֵ
class AI
{
public:

	void init(chess*Chess);
	void go();
private:
	chess* Chess;
	std::vector<std::vector<int>>AIdata;

	void calculateScore();
	Chessplace think();
};