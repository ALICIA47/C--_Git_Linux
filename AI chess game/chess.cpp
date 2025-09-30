#include "chess.h"
#include<graphics.h>
#include<math.h>
#include"tools.h"
#include"conio.h"
#pragma comment(lib,"winmm.lib")//��ý�岥��


chess::chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = margin_x;
    this->margin_y = margin_y;
    this->chessSize = chessSize;
    playerFlag = CHESS_BLACK;//��������

    for (int i = 0; i < gradeSize; i++) {
        std::vector<int>row;
        for (int j = 0; j < gradeSize; j++) {
            row.push_back(0);
        }
        mapdata.push_back(row);
    }
}

void chess::init()
{
    //������Ϸ����
    initgraph(897, 895); 
    //��ʾͼƬ
    loadimage(0, "res/����2.jpg");
    //���ſ�ʼ��ʾ��
    mciSendString("play res/start.wav", 0, 0, 0);

    //���غ���Ͱ������ӵ�ͼƬ��������ʵ�ʴ�С����
    loadimage(&BlackchessImg, "res/black.png",chessSize,chessSize,true);
    loadimage(&WhitechessImg, "res/white.png", chessSize, chessSize, true);

    //��������
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++) {
            mapdata[i][j] = 0;
        }
    }

    playerFlag = true;
}

bool chess::clickboard(int x, int y, Chessplace* place)//�ж�����λ��
{
    //��������
    int a = (x - margin_x) / chessSize;
    int b = (y - margin_y) / chessSize;
    int leftTopPlaceX = margin_x + chessSize *a;
    int leftTopPlaceY = margin_y + chessSize *b;

    int offset = chessSize * 0.2;//�ݴ���
    bool ret = false;
    int len = 0;
    do {
        //�ж����Ͻ�
        len = sqrt((x-leftTopPlaceX)*(x-leftTopPlaceX)
        +(y-leftTopPlaceY)*(y-leftTopPlaceY));
        if (len < offset) {
            place->row = b;
            place->col = a;
            if (mapdata[place->row][place->col] == 0) {
                ret = true;
            }
            break;
        }

        //�ж����Ͻ�
        int x2 = leftTopPlaceX + chessSize;
        int y2 = leftTopPlaceY;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset) {
            place->row = b;
            place->col = a + 1;
            if (mapdata[place->row][place->col] == 0) {
                ret = true;
            }
            break;
        }
        
        //�ж����½�
        int x3 = leftTopPlaceX;
        int y3 = leftTopPlaceY + chessSize;
        len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
        if (len < offset) {
            place->row = b+1;
            place->col = a;
            if (mapdata[place->row][place->col] == 0) {
                ret = true;
            }
            break;
        }

        //�ж����½�
        int x4 = leftTopPlaceX + chessSize;
        int y4 = leftTopPlaceY + chessSize;
        len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
        if (len < offset) {
            place->row = b+1;
            place->col = a + 1;
            if (mapdata[place->row][place->col] == 0) {
                ret = true;
            }
            break;
        }

    } while (0);
    return ret;
}

void chess::downchess(Chessplace* place, chess_kind_t kind)
{
    mciSendString("play res/down7.wav", 0, 0, 0);
    int x = margin_x + chessSize * place->col-0.5*chessSize;
    int y = margin_y + chessSize * place->row-0.5*chessSize;

    if (kind == CHESS_WHITE) {
        putimagePNG(x, y, &WhitechessImg);
    }
    else {
        putimagePNG(x, y, &BlackchessImg);
    }

    updataGameMap(place);
}

int chess::getchesstype(Chessplace* place)
{
    return mapdata[place->row][place->col];
}

int chess::getchessdata(int row, int col)
{
    return mapdata[row][col];
}

int chess::getBoardsize()
{
    return gradeSize;
}

bool chess::whethergameend()
{
    if (checkWin()) {
        Sleep(1500);
        if (playerFlag==false) {
            mciSendString("play res/����.mp3", 0, 0, 0);
            loadimage(0, "res/ʤ��.jpg");
        }
        else {
            mciSendString("play res/ʧ��.mp3", 0, 0, 0);
            loadimage(0, "res/ʧ��.jpg");
        }

        _getch();//��ͣ�������������
        return true;
    }

    return false;
}

void chess::updataGameMap(Chessplace* place)
{
    mapdata[place->row][place->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    lplace = *place;
    playerFlag = !playerFlag;//��������
}



bool chess::checkWin()
{
    // ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
    // ˮƽ����
    int row = lplace.row;
    int col = lplace.col;

    for (int i = 0; i < 5; i++)
    {
        // ����5��������ƥ��4���ӣ�20�����
        if (col - i >= 0 &&
            col - i + 4 < gradeSize &&
            mapdata[row][col - i] == mapdata[row][col - i + 1] &&
            mapdata[row][col - i] == mapdata[row][col - i + 2] &&
            mapdata[row][col - i] == mapdata[row][col - i + 3] &&
            mapdata[row][col - i] == mapdata[row][col - i + 4])
            return true;
    }

    // ��ֱ����(��������4��)
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 &&
            row - i + 4 < gradeSize &&
            mapdata[row - i][col] == mapdata[row - i + 1][col] &&
            mapdata[row - i][col] == mapdata[row - i + 2][col] &&
            mapdata[row - i][col] == mapdata[row - i + 3][col] &&
            mapdata[row - i][col] == mapdata[row - i + 4][col])
            return true;
    }

    // ��/"����
    for (int i = 0; i < 5; i++)
    {
        if (row + i < gradeSize &&
            row + i - 4 >= 0 &&
            col - i >= 0 &&
            col - i + 4 < gradeSize &&
            // ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
            mapdata[row + i][col - i] == mapdata[row + i - 1][col - i + 1] &&
            mapdata[row + i][col - i] == mapdata[row + i - 2][col - i + 2] &&
            mapdata[row + i][col - i] == mapdata[row + i - 3][col - i + 3] &&
            mapdata[row + i][col - i] == mapdata[row + i - 4][col - i + 4])
            return true;
    }

    // ��\�� ����
    for (int i = 0; i < 5; i++)
    {
        // ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
        if (row - i >= 0 &&
            row - i + 4 < gradeSize &&
            col - i >= 0 &&
            col - i + 4 < gradeSize &&
            mapdata[row - i][col - i] == mapdata[row - i + 1][col - i + 1] &&
            mapdata[row - i][col - i] == mapdata[row - i + 2][col - i + 2] &&
            mapdata[row - i][col - i] == mapdata[row - i + 3][col - i + 3] &&
            mapdata[row - i][col - i] == mapdata[row - i + 4][col - i + 4])
            return true;
    }

    return false;
}