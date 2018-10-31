/*
��ȡλͼ�ļ�
*/
#ifndef _BMPTOOLS_H_
#define _BMPTOOLS_H_

#include<iostream>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;

struct tagBitMap
{
    //����ͼ�����ݵ�ָ��
    unsigned char *pBmpBuf;
    //ͼ��Ŀ�
    int bmpWidth;
    //ͼ��ĸ�
    int bmpHeight;
    //��ɫ��ָ��
    RGBQUAD *pColorTable;
    //ͼ�����ͣ�ÿ����λ��
    int biBitCount;
    tagBitMap()
    {
        pBmpBuf = 0;
        bmpWidth = 0;
        pColorTable = 0;
        biBitCount = 0;
    }
};

unsigned char* readBmp(char *bmpName);
int readBmp(char *bmpName, tagBitMap* BitMapData);
int adjustBmp(unsigned char* pBmpBuf, unsigned char* pImage, int rows, int cols);
#endif