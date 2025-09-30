#include"AI.h"
#include"chess.h"
#include"human.h"
#include"board.h"
#include<iostream>


int main(void) {
	human man;
	AI ai;
	//chess Chess;
	chess Chess(13,44,43,67.3);
	board mainboard(&man,&ai,&Chess);//������Ϸ


	mainboard.play();//����
	
	return 0;
}