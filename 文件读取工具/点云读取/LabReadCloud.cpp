#include "stdafx.h"
#include "LabReadCloud.h"
using namespace TDCLD;

int labReadCloud(char *filename, void *pointCloud)
{
	vector<TDNODE3D> *ptmp = (vector<TDNODE3D> *)pointCloud;
	FILE *fp;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		return -1;    //文件打开失败
	}
	TDNODE3D tmpTdNode3d;    //把读到的数据写入结构体
	float dX, dY, dZ;
	float dNx, dNy, dNz;
	unsigned long ulColor;
	float dPixel0, dPixel1;
	int iMeasureEleID;    //对应的测头Id?
	int i = 0;
	while (!feof(fp))
	{
		int res = fscanf_s(fp, " %f %f %f %f %f %f %lu %f %f %d ",
			&dX, &dY, &dZ, &dNx, &dNy, &dNz, &ulColor,
			&dPixel0, &dPixel1, &iMeasureEleID);
		if (res == -1) { break; }
		tmpTdNode3d.iId = i;
		tmpTdNode3d.Pt.dX = dX;
		tmpTdNode3d.Pt.dY = dY;
		tmpTdNode3d.Pt.dZ = dZ;
		tmpTdNode3d.PtNormal.dX = dNx;
		tmpTdNode3d.PtNormal.dY = dNy;
		tmpTdNode3d.PtNormal.dZ = dNz;
		tmpTdNode3d.dwColor.rgbRed   = GetRValue(ulColor);
		tmpTdNode3d.dwColor.rgbGreen = GetGValue(ulColor);
		tmpTdNode3d.dwColor.rgbBlue  = GetBValue(ulColor);
		tmpTdNode3d.PtImgPixel.dX = dPixel0;
		tmpTdNode3d.PtImgPixel.dY = dPixel1;
		tmpTdNode3d.iMainElement = iMeasureEleID;
		ptmp->push_back(tmpTdNode3d);
		i++;
	}
	i = 0;
	fclose(fp);
	return 0;
}

int labReadCloudNoColor(char *filename, void *pointCloud)
{
	vector<TDNODE3D> *ptmp = (vector<TDNODE3D> *)pointCloud;
	FILE *fp;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		return -1;    //文件打开失败
	}
	TDNODE3D tmpTdNode3d;    //把读到的数据写入结构体
	float dX, dY, dZ;
	float dNx, dNy, dNz;
	int i = 0;
	while (!feof(fp))
	{
		int res = fscanf_s(fp, " %f %f %f %f %f %f",
			&dX, &dY, &dZ, &dNx, &dNy, &dNz);
		if (res == -1) { break; }
		tmpTdNode3d.iId = i;
		tmpTdNode3d.Pt.dX = dX;
		tmpTdNode3d.Pt.dY = dY;
		tmpTdNode3d.Pt.dZ = dZ;
		tmpTdNode3d.PtNormal.dX = dNx;
		tmpTdNode3d.PtNormal.dY = dNy;
		tmpTdNode3d.PtNormal.dZ = dNz;
		ptmp->push_back(tmpTdNode3d);
		i++;
	}
	i = 0;
	fclose(fp);
	return 0;
}

int labReadCloudPLY(char *filename, void *pointCloud)
{
	vector<TDNODE3D> *ptmp = (vector<TDNODE3D> *)pointCloud;
	FILE *fp;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		return -1;    //文件打开失败
	}
	TDNODE3D tmpTdNode3d;    //把读到的数据写入结构体
	float dX, dY, dZ;
	//float dNx, dNy, dNz;
	//unsigned long ulColor;
	//float dPixel0, dPixel1;
	//int iMeasureEleID;    //对应的测头Id?
	int i = 0;
	//跳过PLY文件的前7行
	for (int k = 0; k < 7; k++)
	{
		fscanf_s(fp, "%*[^\n]%*c");
	}
	while (!feof(fp))
	{
		int res = fscanf_s(fp, " %f %f %f", &dX, &dY, &dZ);
        if (res == -1) { break; }
		tmpTdNode3d.iId = i;
		tmpTdNode3d.Pt.dX = dX;
		tmpTdNode3d.Pt.dY = dY;
		tmpTdNode3d.Pt.dZ = dZ;
		tmpTdNode3d.PtNormal.dX = 0;
		tmpTdNode3d.PtNormal.dY = 0;
		tmpTdNode3d.PtNormal.dZ = 0;
		tmpTdNode3d.dwColor.rgbRed = 0;
		tmpTdNode3d.dwColor.rgbGreen = 0;
		tmpTdNode3d.dwColor.rgbBlue = 0;
		tmpTdNode3d.PtImgPixel.dX = 0;
		tmpTdNode3d.PtImgPixel.dY = 0;
		tmpTdNode3d.iMainElement = 0;
		ptmp->push_back(tmpTdNode3d);
		i++;
	}
	i = 0;
	fclose(fp);
	return 0;
}

int labWriteCloud(char *filename, void *pointCloud)
{
	vector<TDNODE3D> *ptmp = (vector<TDNODE3D> *)pointCloud;
	FILE *fp;
	fopen_s(&fp, filename, "w");
	if (fp == NULL)
	{
		return -1;    //文件打开失败
	}

	float dX, dY, dZ;
	float dNx, dNy, dNz;
	BYTE r, g, b;
	unsigned long ulColor;
	float dPixel0, dPixel1;
	int iMeasureEleID;    //对应的测头Id?
	int i = 0;
	
	for (size_t i = 0; i < ptmp->size(); i++)
	{
		dX = (float)ptmp->at(i).Pt.dX;
		dY = (float)ptmp->at(i).Pt.dY;
		dZ = (float)ptmp->at(i).Pt.dZ;
		dNx = (float)ptmp->at(i).PtNormal.dX;
		dNy = (float)ptmp->at(i).PtNormal.dY;
		dNz = (float)ptmp->at(i).PtNormal.dZ;
		r = ptmp->at(i).dwColor.rgbRed;
		g = ptmp->at(i).dwColor.rgbGreen;
		b = ptmp->at(i).dwColor.rgbBlue;
		ulColor = RGB(r,g,b);
		dPixel0 = (float)ptmp->at(i).PtImgPixel.dX;
		dPixel1 = (float)ptmp->at(i).PtImgPixel.dY;
		iMeasureEleID = ptmp->at(i).iMainElement;
		fprintf_s(fp, " %f %f %f %f %f %f %lu %f %f %d \n",
			      dX, dY, dZ, dNx, dNy, dNz, ulColor,
			      dPixel0, dPixel1, iMeasureEleID);
	}
	fclose(fp);
	return 0;
}