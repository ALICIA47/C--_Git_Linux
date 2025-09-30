#pragma once
#include<graphics.h>//easyx��ͷ�ļ�
#include"stdlib.h"
#include<vector>


struct Chessplace {
	int row;
	int col;

	Chessplace(int r = 0, int c = 0) :row(r), col(c) {};//ʹ�ò���r��c���г�ʼ������
};

typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1,
}chess_kind_t;//�������



class chess
{
public:
	chess(int gradeSize, int margin_x, int margin_y,float chessSize);//���캯��


	void init();//��ʼ��
	bool clickboard(int x, int y, Chessplace* place);//�Ƿ���Ч���
	void downchess(Chessplace* place, chess_kind_t kind);//�����λ������
	int getchesstype(Chessplace* place);
	int getchessdata(int row, int col);
	int getBoardsize();//��֪���̴�С
	bool whethergameend();//�ж��Ƿ�������
private:
	IMAGE BlackchessImg;//����
	IMAGE WhitechessImg;//����

	int gradeSize;//���̴�С
	int margin_x;//����x��Ե����
	int margin_y;//����y��Ե����
	float chessSize;//���Ӵ�С�����̷����С��
	std::vector<std::vector<int>> mapdata;//�洢��ǰ��������λ��0�հ�1����-1����

	bool playerFlag;//true�������ӣ�false��������

	void updataGameMap(Chessplace* place);//�洢��������

	bool checkWin();//�����Ϸ��Ӯ

	Chessplace lplace;//������ӵ�
};