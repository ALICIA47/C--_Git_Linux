#include "board.h"
#include"human.h"
#include"AI.h"
#include"chess.h"

board::board(human* man, AI* ai, chess* Chess)
{
	this->man = man;
	this->ai = ai;
	this->Chess = Chess;

	man->init(Chess);
	ai->init(Chess);
}

void board::play()
{
	Chess->init();
	while (1) {
		man->go();//������
		if (Chess->whethergameend()) {
			Chess->init();
			continue;
		}


		ai->go();
		if (Chess->whethergameend()) {
			Chess->init();
			continue;
		}	
	}
}