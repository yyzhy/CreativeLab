/*
读取位图文件
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
    //读入图像数据的指针
    unsigned char *pBmpBuf;
    //图像的宽
    int bmpWidth;
    //图像的高
    int bmpHeight;
    //颜色表指针
    RGBQUAD *pColorTable;
    //图像类型，每像素位数
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