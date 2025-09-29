#include "GAME.h"
#include<stdlib.h>
#include<vector>
#include<conio.h>
#include<time.h>
#include"BLOCK.h"
#include<mmsystem.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")

const int Speed_Slow = 500;//ms
const int Speed_Fast = 50;//ms

GAME::GAME(int rows, int coles, int left, int top, int blocksize)
    : curblock(nullptr), delay(0), nextblock(nullptr), update(false)
{
    rounds = rows;
    lines = coles;
    leftmargin = left;
    topmargin = top;
    this->blocksize = blocksize;

    for (int i = 0; i < rounds; i++) {
        std::vector<int>maprow;
        for (int j = 0; j < lines; j++) {
            maprow.push_back(0);
        }

        mapdata.push_back(maprow);
    }//��ʼ����ͼ
}

void GAME::init()
{
	delay = Speed_Slow;//ˢ����

	//�����������
	srand(time(NULL));

	//������Ϸ����
	initgraph(938,896);

	//���ر���ͼƬ
	loadimage(&imgbackground, "res/bg2.png");

	//��ʼ����Ϸ�е�����

	for (int i = 0; i < rounds;i++) {
		for (int j = 0; j < lines; j++) {
			mapdata[i][j] = 0;
		}
	}
	//score = 0;
}

//2025/2/12ʵ����Ϸ��ѭ��

void GAME::play()
{
	init();

	nextblock = new BLOCK;
	if (!curblock) {
		curblock = nextblock;
	}
	nextblock = new BLOCK;


	int timer = 0;//��ʱ��

	while (1)//��ѭ�� 
	{
		//�����û�����
		KeyEvent();

		timer += getDelay();//����ˢ�¼��
		if (timer > delay) {
			timer = 0;
			//�����½�
			drop();
			//�ж���Ⱦʱ��
			update = true;
		}//������Ⱦ�Ĵ���
		if (update) {
			update = false;

			//��Ⱦ����
			
			updateWindow();

			//������Ϸ����
			//����
			clearline();
		}
	}
}

void GAME::KeyEvent()
{
	unsigned char ch;//0~255
	bool rotateflag = false;
	int dx = 0;
	while(_kbhit()) {
		ch=_getch();
		//��������᷵�������ַ�����Ϊ224/72����Ϊ224/80����Ϊ224/75����Ϊ224/77��
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				rotateflag = true;
				break;
			case 80:
				delay = Speed_Fast;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;	
			}
		}
	}
	if (rotateflag) {
		rotate();
		update = true;
	}

	if (dx != 0) {
		bakblock = *curblock;
		curblock->moveLeftRight(dx);

		if (!curblock->blockInmap(mapdata)) {
			*curblock = bakblock;
		}
		update = true;
	}
	//update = true;//�û������������ж���Ⱦ��
}

void GAME::updateWindow()
{
	putimage(0, 0, &imgbackground);

	IMAGE** imgs = BLOCK::getImages();//ѡȡ�ö�Ӧ�ķ�������

	//����
	//BLOCK block;
	//block.draw(263,133);

	BeginBatchDraw();

	//�̶�����ײ��ķ���
	for (int i = 0; i < rounds; i++){
		for (int j = 0; j < lines; j++) {
			if (mapdata[i][j] == 0)continue;

			int x = j * blocksize + leftmargin;
			int y = i * blocksize + topmargin;
			int imgIndex = mapdata[i][j];
			
			putimage(x, y, imgs[mapdata[i][j]-1]);
		}
	}


	//ʵ��ʵ��
	curblock->draw(263,133);
	nextblock->draw(689,133);

	drawscore();


	EndBatchDraw();
}

void GAME::drop()
{
	bakblock = *curblock;
	curblock->drop();

	if (!curblock->blockInmap(mapdata)) {
		bakblock.solidify(mapdata);
		delete curblock;//�ͷ��ڴ�
		if (!curblock) {
			curblock = nextblock;//Ԥ�淽��������
		}
		nextblock = new BLOCK;//�µ�Ԥ�淽��
	}
	delay = Speed_Slow;
}

void GAME::clearline()
{
	int scoreline = 0;
	int k = rounds - 1;//�洢��������
	for (int i = rounds - 1; i >= 0; i--) {
		//���i���Ƿ�����
		int count = 0;
		for (int j = 0; j < lines; j++) {
			if (mapdata[i][j]) {
				count++;
			}
			mapdata[k][j] = mapdata[i][j];//һ��ɨ��һ�ߴ洢
		}
		if (count < lines) {//������
			k--;
		}
		else {
			scoreline++;
		}
	}
	if (scoreline > 0) {
		//�������е÷�
		int addscore[4] = { 10,30,60,80 };
		score += addscore[scoreline - 1];

		mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
		update = true;
	}
}

void GAME::rotate()
{
	if (curblock->getblockType() == 7)return;
	bakblock = *curblock;
	curblock->rotate();
	if (!curblock->blockInmap(mapdata)) {
		*curblock = bakblock;
	}
}

void GAME::drawscore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);

	outtextxy(670, 727, scoreText);
}

//�״η���0������������һ�ε��ü������ms
int GAME::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime=GetTickCount();

	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}

}