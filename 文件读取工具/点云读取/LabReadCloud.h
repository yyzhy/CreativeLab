/**************************************************//**
* ���ļ�ȡ��������
* ����TDNODE3D�������ά�������ݸ�ʽ
* LabCloudProcDefs.h ֱ���������еĽṹ�嶨��
* zhouye
* 2018.08.11
******************************************************/
#pragma  once



/**
 * @Method labReadCloud
 * @brief 
 * @param char * filename  ���������ļ���
 * @param vector<TDNODE3D> vCloudPoint  ���ض�ȡ�ĵ�������
 * Returns int
*/
int labReadCloud(char *filename, void *pointCloud);
int labReadCloudNoColor(char *filename, void *pointCloud);
int labWriteCloud(char *filename, void *pointCloud);