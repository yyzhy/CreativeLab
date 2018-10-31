#include "stdafx.h"
#include "LabLoadData.h"
#include<iostream>
#include<fstream>
#include<stdio.h> 
#include<string>
#include "ximage.h"
using namespace std;

int LabLoadColor(int iCameraIndex, char *filename, unsigned char** ColorImage)
{
	CxImage ximage;
	CString imageName;
	imageName = filename;
	if (ximage.Load(imageName, CXIMAGE_FORMAT_BMP))
	{
		unsigned char *pcolorbuf = ximage.GetBits();
		int height = ximage.GetHeight();
		int width = ximage.GetWidth();
		//RGBQUAD color;
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				ColorImage[iCameraIndex][3 * (h * width + w)]     = pcolorbuf[3 * ((height - h - 1) * width + w)];
				ColorImage[iCameraIndex][3 * (h * width + w) + 1] = pcolorbuf[3 * ((height - h - 1) * width + w) + 1];
				ColorImage[iCameraIndex][3 * (h * width + w) + 2] = pcolorbuf[3 * ((height - h - 1) * width + w) + 2];
			}
		}
	}
	return 0;
}

int LabSaveColor(char *filename, unsigned char* ColorImage)
{
	CxImage desImg;
	CString imageName;
	imageName = filename;
	desImg.Create(640, 480, 24, CXIMAGE_FORMAT_BMP);
	unsigned char *pDesBuf = desImg.GetBits();
	for (int y = 0; y < 480; ++y)
	{
		for (int x = 0; x < 640; ++x)
		{
			pDesBuf[3 * (y * 640 + x)]     = ColorImage[3 * ((480 - y - 1) * 640 + x)];
			pDesBuf[3 * (y * 640 + x) + 1] = ColorImage[3 * ((480 - y - 1) * 640 + x) + 1];
			pDesBuf[3 * (y * 640 + x) + 2] = ColorImage[3 * ((480 - y - 1) * 640 + x) + 2];
		}
	}
	desImg.Save(imageName, CXIMAGE_SUPPORT_BMP);
	return 0;
}

int LabLoadDepth(int iCameraIndex, char *filename, float** pointCloud)
{
	int iwidth = 640;
	int iheight = 480;
	FILE *fp;
	//pointCloud[iCameraIndex] = new float[640 * 480];
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		return -1;            //文件打开失败
	}
	for (int i = 0; i < iheight; i++)
	{
		for (int j = 0; j < iwidth; j++)
		{
			fscanf_s(fp, "%f", &pointCloud[iCameraIndex][(i) * iwidth + j]);
		}
	}
	fclose(fp);
	return 0;
}

void read_C(int p, double** pCparam, string s)
{
	double a[50]{0};

	ifstream fin0(s);
	for (int i = 0; i < 50; i++)
	{
		fin0 >> a[i];
	}
	fin0.close();
	pCparam[p][0] = a[6];  //幅面宽度
	pCparam[p][1] = a[7];  //幅面高度
	for (int i_para = 0; i_para < 22; i_para++)
	{
		pCparam[p][i_para + 2] = a[14 + i_para];
	}
}

vector<string> readTxt(string filename)
{
	ifstream text;
	text.open(filename, ios::in);
	vector<string> strVec;
	while (!text.eof())
	{
		string inbuf;
		getline(text, inbuf, '\n');
		strVec.push_back(inbuf);
	}
	return strVec;
}

void read_RT(int p, double** RT, string s)
{
	vector<string> a;
	a = readTxt(s);
	vector<string> str_list;           //存放分割后的字符串
	for (int i = 0; i < 3; i++)
	{
		int comma_n = 0;
		do
		{
			string temp_s = "";
			comma_n = (int)a[i + 5].find("  ");    //20180926添加(int)
			if (-1 == comma_n)
			{
				temp_s = a[i + 5].substr(0, a[i + 5].length());
				str_list.push_back(temp_s);
				break;
			}
			temp_s = a[i + 5].substr(0, comma_n);
			a[i + 5].erase(0, comma_n + 1);
			str_list.push_back(temp_s);
		} while (true);
		for (int j = 0; j < 3; j++)
		{
			RT[p][i * 3 + j] = stod(str_list[i * 4 + j]);
		}
		RT[p][9 + i] = stod(str_list[i * 4 + 3]);
	}
}

void readRTAxis(char* filename, double *readRTAxis)
{
	FILE *fp;
	fopen_s(&fp, filename, "r");
	fscanf_s(fp, "%lf  %lf  %lf  %lf  %lf", &readRTAxis[0], &readRTAxis[1], &readRTAxis[2], &readRTAxis[3], &readRTAxis[4]);
}