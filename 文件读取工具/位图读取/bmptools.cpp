#include "bmptools.h"

unsigned char* readBmp(char *bmpName){
    
    FILE *fp = fopen(bmpName, "rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
    if (fp == 0)
        return 0;

    //����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);

    //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
    BITMAPINFOHEADER head;
    int bmpWidth;//ͼ��Ŀ�
    int bmpHeight;//ͼ��ĸ�
    RGBQUAD *pColorTable;//��ɫ��ָ��
    int biBitCount;//ͼ�����ͣ�ÿ����λ��

    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp); //��ȡͼ����ߡ�ÿ������ռλ������Ϣ
    bmpWidth = head.biWidth;
    bmpHeight = head.biHeight;
    biBitCount = head.biBitCount;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����

    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256

    if (biBitCount == 8)
    {
        //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
        pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);
    }

    //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
    unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
    fclose(fp);//�ر��ļ�
    return pBmpBuf;//��������ָ��
}

int  readBmp(char *bmpName, tagBitMap* BitMapData){
    FILE *fp = fopen(bmpName, "rb");
    if (fp == 0)
    {
        printf("��ʧ�ܣ�/n");
        return 0;
    }
    //����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);
    //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
    BITMAPINFOHEADER head;
    //��ȡͼ����ߡ�ÿ������ռλ������Ϣ
    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
    BitMapData->bmpWidth = head.biWidth;
    BitMapData->bmpHeight = head.biHeight;
    BitMapData->biBitCount = head.biBitCount;
    //�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
    //�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
    int lineByte = (BitMapData->bmpWidth * BitMapData->biBitCount / 8 + 3) / 4 * 4;
    if (BitMapData->biBitCount == 8)
    {
        //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
        BitMapData->pColorTable = new RGBQUAD[256];
        fread(BitMapData->pColorTable, sizeof(RGBQUAD), 256, fp);
    }
    //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
    BitMapData->pBmpBuf = new unsigned char[lineByte * BitMapData->bmpHeight];
    fread(BitMapData->pBmpBuf, 1, lineByte * BitMapData->bmpHeight, fp);
    //�ر��ļ�
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