#include "bmptools.h"

unsigned char* readBmp(char *bmpName){
    
    FILE *fp = fopen(bmpName, "rb");//二进制读方式打开指定的图像文件
    if (fp == 0)
        return 0;

    //跳过位图文件头结构BITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);

    //定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
    BITMAPINFOHEADER head;
    int bmpWidth;//图像的宽
    int bmpHeight;//图像的高
    RGBQUAD *pColorTable;//颜色表指针
    int biBitCount;//图像类型，每像素位数

    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp); //获取图像宽、高、每像素所占位数等信息
    bmpWidth = head.biWidth;
    bmpHeight = head.biHeight;
    biBitCount = head.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）

    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256

    if (biBitCount == 8)
    {
        //申请颜色表所需要的空间，读颜色表进内存
        pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);
    }

    //申请位图数据所需要的空间，读位图数据进内存
    unsigned char *pBmpBuf;//读入图像数据的指针
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
    fclose(fp);//关闭文件
    return pBmpBuf;//返回数据指针
}

int  readBmp(char *bmpName, tagBitMap* BitMapData){
    FILE *fp = fopen(bmpName, "rb");
    if (fp == 0)
    {
        printf("打开失败！/n");
        return 0;
    }
    //跳过位图文件头结构BITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);
    //定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
    BITMAPINFOHEADER head;
    //获取图像宽、高、每像素所占位数等信息
    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
    BitMapData->bmpWidth = head.biWidth;
    BitMapData->bmpHeight = head.biHeight;
    BitMapData->biBitCount = head.biBitCount;
    //定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
    //灰度图像有颜色表，且颜色表表项为256
    int lineByte = (BitMapData->bmpWidth * BitMapData->biBitCount / 8 + 3) / 4 * 4;
    if (BitMapData->biBitCount == 8)
    {
        //申请颜色表所需要的空间，读颜色表进内存
        BitMapData->pColorTable = new RGBQUAD[256];
        fread(BitMapData->pColorTable, sizeof(RGBQUAD), 256, fp);
    }
    //申请位图数据所需要的空间，读位图数据进内存
    BitMapData->pBmpBuf = new unsigned char[lineByte * BitMapData->bmpHeight];
    fread(BitMapData->pBmpBuf, 1, lineByte * BitMapData->bmpHeight, fp);
    //关闭文件
    fclose(fp);
    return 1;
}

int adjustBmp(unsigned char* pBmpBuf, unsigned char* pImage, int rows, int cols){
    //pImage = (unsigned char*)malloc(sizeof(unsigned char) * (rows * cols));
    for (int y = 0; y < rows; y++){
        for (int x = 0; x < cols; x++){
            unsigned char t;
            t = *(pBmpBuf + cols * (rows - 1 - y) + x);
            *(pImage + cols * y + x) = t;
        }
    }
    return 1;
}