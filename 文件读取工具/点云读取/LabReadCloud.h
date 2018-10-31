/**************************************************//**
* 读文件取点云数据
* 按照TDNODE3D定义的三维点云数据格式
* LabCloudProcDefs.h 直接引用已有的结构体定义
* zhouye
* 2018.08.11
******************************************************/
#pragma  once



/**
 * @Method labReadCloud
 * @brief 
 * @param char * filename  点云数据文件名
 * @param vector<TDNODE3D> vCloudPoint  返回读取的点云数据
 * Returns int
*/
int labReadCloud(char *filename, void *pointCloud);
int labReadCloudNoColor(char *filename, void *pointCloud);
int labWriteCloud(char *filename, void *pointCloud);