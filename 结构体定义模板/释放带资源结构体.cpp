/*
 * �����ͷŴ���Դ�Ľṹ��
*/
#include "stdio.h"
#include "Struct.h"
#include <vector>
using namespace std;

template <typename T>
void freeVectorPoint(vector<T*> vVector)
{
	if (!vVector.empty())
	{
		for (size_t i = 0; i < vVector.size(); i++)
		{
			if (vVector.at(i) != NULL)
			{
				delete  vVector.at(i);
				vVector.at(i) = NULL;
			}
		}
	}
}

void main()
{
	ImageBuffer* image = new ImageBuffer;
	image->pBuf = new unsigned char[4];
	vector<ImageBuffer*> vImage;
	vImage.push_back(image);
	vImage.push_back(image);
	//����Դ�Ľṹ��ָ��ѹ��vector��,�������������ͷ�
	for (size_t i = 0; i < vImage.size(); i++)
	{
		delete vImage.at(i);
		vImage.at(i) = NULL;
	}
	vImage.clear();
}