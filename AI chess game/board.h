#pragma once
#include"human.h"
#include"AI.h"
#include"chess.h"
class board
{
public:
	board(human* man, AI* ai, chess* chess);
	void play();//��ʼ�Ծ�

private:
	human* man;
	AI* ai;
	chess* Chess;
};