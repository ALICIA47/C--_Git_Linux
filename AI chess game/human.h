#pragma once
#include"chess.h"
class human
{
public:
	void init(chess*chess);
	void go();

private:
	chess *Chess;
};

