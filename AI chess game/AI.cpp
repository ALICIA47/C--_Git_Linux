#include "AI.h"

void AI::init(chess* Chess)
{
	this->Chess = Chess;
	int mapsize = Chess->getBoardsize();
	for (int i = 0; i < mapsize; i++) {
		std::vector<int>row;
		for (int j = 0; j < mapsize; j++) {
			row.push_back(0);
		}
		AIdata.push_back(row);
	}
}

void AI::go()
{
	Chessplace place=think();
	Sleep(1000);//����ʱ��
	Chess->downchess(&place, CHESS_WHITE);
}

void AI::calculateScore()
{
	int personNum = 0;//���������ж��ٸ���������
	int AINum = 0;//AI�����ж��ٸ���������
	int emptyNum = 0;//�÷����Ͽհ�λ�ĸ���
	
	
	//��ʼ��
	for (int i = 0; i < AIdata.size(); i++) {
		for (int j = 0; j < AIdata[i].size(); j++) {
			AIdata[i][j] = 0;
		}
	}

	int size = Chess->getBoardsize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			

			//��ÿ������м���
			if (Chess->getchessdata(row, col)) continue;
			//��λ
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					personNum = 0;
					AINum = 0;
					emptyNum = 0;//ˢ��
					if (y == 0 && x == 0)continue;
					//�����������ڸ�λ�����ӣ��ṹ��ʲô����
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&//�Ϸ�����
							Chess->getchessdata(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							Chess->getchessdata(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else { 
							break; 
						}//��������
					}
					//����
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&//�Ϸ�����
							Chess->getchessdata(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							Chess->getchessdata(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}//��������
					}
					if (personNum == 1) {//��2����
						AIdata[row][col] += 10;
					}
					else if(personNum==2){//��3����
						if (emptyNum == 1) {//��3����
							AIdata[row][col] += 30;
						}
						else if (emptyNum == 2) {//��3����
							AIdata[row][col] += 40;
						}
					}
					else if (personNum == 3) {//��4����
						if (emptyNum == 1) {//��4����
							AIdata[row][col] += 60;
						}
						else if (emptyNum == 2) {//��4����
							AIdata[row][col] += 200;
						}
					}
					else if (personNum == 4) {//����Ӯ��
						AIdata[row][col] += 20000;
					}


					//�����������ڸ�λ�����ӣ��ṹ��ʲô����
					emptyNum = 0;//ˢ��
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&//�Ϸ�����
							Chess->getchessdata(curRow, curCol) == -1) {
							AINum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							Chess->getchessdata(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else { 
							break;
						}//��������
					}
					//����
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&//�Ϸ�����
							Chess->getchessdata(curRow, curCol) == -1) {
							AINum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							Chess->getchessdata(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else { 
							break; 
						}//��������
					}
					if (AINum == 0) {//�հ��ж�
						AIdata[row][col] += 5;
					}
					else if (AINum == 1) {//��2����
						AIdata[row][col] += 10;
					}
					else if (AINum == 2) {//��3����
						if (emptyNum == 1) {//��3����
							AIdata[row][col] += 25;
						}
						else if (emptyNum == 2) {//��3����
							AIdata[row][col] += 50;
						}
					}
					else if (AINum == 3) {//��4����
						if (emptyNum == 1) {//��4����
							AIdata[row][col] += 55;
						}
						else if (emptyNum == 2) {//��4����
							AIdata[row][col] += 10000;
						}
					}
					else if (AINum >= 4) {//AIӮ��
						AIdata[row][col] += 30000;
					}
				}
			}
		}
	}
}

Chessplace AI::think()
{
	calculateScore();
	int maxScore = 0;

	std::vector<Chessplace>maxPoints;
	int size = Chess->getBoardsize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (Chess->getchessdata(row, col) == 0) {
				if (AIdata[row][col] > maxScore) {
					maxPoints.clear();
					maxScore = AIdata[row][col];
					maxPoints.push_back(Chessplace(row, col));
				}
				else if (AIdata[row][col] == maxScore) {
					maxPoints.push_back(Chessplace(row, col));
				}
			}
		}
	}
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}