#include "human.h"

void human::init(chess* Chess)
{
	this->Chess = Chess;
}

void human::go()
{
	MOUSEMSG msg;
	Chessplace place;

	while(1){
		msg=GetMouseMsg();//��ȡ�������Ϣ
		//�ж������Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN && Chess->clickboard(msg.x, msg.y, &place)) {//�����Ϣ
			break;
		}
	}

	Chess->downchess(&place, CHESS_BLACK);//����
}