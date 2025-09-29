#include "BLOCK.h"
#include"GAME.h"
#include<stdlib.h>
#include<vector>



//2025/2/13

IMAGE* BLOCK::imgs[7] = { NULL, };
int BLOCK::size = 36;

BLOCK::BLOCK() 
{
	if (imgs[0] == NULL) {
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");//ͼƬ�����ڴ�

		SetWorkingImage(&imgTmp);
		//�ָ�ͼƬ
		for (int i = 0; i < 7; i++) {
			imgs[i] = new IMAGE;//�����ڴ�
			getimage(imgs[i],i*36,0,size,size);//�ָ������ͼƬ���и�xλ�ã��и�yλ�ã���ͼƬ���ȣ���ͼƬ�߶ȣ�
		}
		SetWorkingImage();//�ָ�������

	}

	int block[7][4] = {
	/*  01
		23
		45
		67*/
		1,3,5,7,//����
		2,4,5,7,//z��1��
		3,5,4,6,//z��2��
		3,5,4,7,//t��
		2,3,5,7,//l��
		3,5,7,6,//j��
		2,3,4,5,//������
	};

	//�������һ�ַ���
	blockType= rand() % 7+1;

	//��ʼ��λ����Ϣ
	int randomplace = rand() % 9;
	for (int i = 0; i < 4; i++) {
		
		int value = block[blockType-1][i];
		singleBlock[i].row = value / 2;
		singleBlock[i].col = value % 2;
	}

	img = imgs[blockType-1];//ָ������ͼƬ
}



//2025/2/16
void BLOCK::drop()
{
	for (auto &BLOCK:singleBlock) {
		BLOCK.row++;
	}
}

void BLOCK::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++) {
		singleBlock[i].col += offset;
	}
}



//2025/2/14
void BLOCK::draw(int leftMargin, int topMargin)
{
	for (int i = 0; i < 4; i++) {
		if (singleBlock[i].col < 0 || singleBlock[i].row < 0)continue;
		int x = leftMargin + singleBlock[i].col * size;
		int y = topMargin + singleBlock[i].row * size;

		if (img != nullptr) {
			putimage(x, y, img);
		}
		
	}
}

void BLOCK::rotate()
{
	Point p = singleBlock[1];//����ת����
	for (int i = 0; i < 4; i++) {
		Point tmp = singleBlock[i];
		singleBlock[i].col = p.col - tmp.row + p.row;//����ת���ĵ���ת��ʽ
		singleBlock[i].row = p.row + tmp.col - p.col;
	}
}

void BLOCK::solidify(std::vector<std::vector<int>>& mapdata)
{
	for (int i = 0; i < 4; i++) {
		//���ñ�ǹ̻�
		mapdata[singleBlock[i].row][singleBlock[i].col] = blockType;
	}
}

int BLOCK::getblockType()
{
	return blockType;
}

IMAGE** BLOCK::getImages()
{
	return imgs;
}

BLOCK& BLOCK::operator=(const BLOCK& other)
{
	if (this == &other) return *this;

	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) {
		this->singleBlock[i] = other.singleBlock[i];
	}

	return *this;// TODO: �ڴ˴����� return ���
}

bool BLOCK::blockInmap(const std::vector<std::vector<int>>& mapdata)
{
	int rows = mapdata.size();
	int cols = mapdata[0].size();
	for (int i = 0; i < 4; i++) {
		if (singleBlock[i].col < 0 || singleBlock[i].col >= cols ||
			singleBlock[i].row < 0 || singleBlock[i].row >= rows ||
			mapdata[singleBlock[i].row][singleBlock[i].col]) {
			return false;
		}//��������ܳ���ͼ��Ե���������������ص���Ϊ�Ƿ�
	}
	return true;
}