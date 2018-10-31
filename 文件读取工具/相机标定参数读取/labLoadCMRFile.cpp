int labLoadCMRFile(const char *cCMRFileName, double pData[22])
{
	FILE *fp;
	fopen_s(&fp, cCMRFileName, "r");
	if (fp == NULL)
	{
		//文件打开失败
		return -1;
	}
	//跳过第一行数据
	fscanf_s(fp, "%*[^\n]%*c");
	//读取内参数
	//pData[0]-pData[9]
	fscanf_s(fp, "%lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf",
		     &pData[0], &pData[1], &pData[2], &pData[3], &pData[4],
		     &pData[5], &pData[6], &pData[7], &pData[8], &pData[9]);
	//读取外参数
	//pData[10], pData[11], pData[12]    平移量T
	fscanf_s(fp, "%lf  %lf  %lf", &pData[10], &pData[11], &pData[12]);
	//pData[13], pData[14], pData[15]    旋转矩阵R
	//pData[16], pData[17], pData[18]
	//pData[19], pData[20], pData[21]
	fscanf_s(fp, "%lf  %lf  %lf", &pData[13], &pData[14], &pData[15]);
	fscanf_s(fp, "%lf  %lf  %lf", &pData[16], &pData[17], &pData[18]);
	fscanf_s(fp, "%lf  %lf  %lf", &pData[19], &pData[20], &pData[21]);
	return 0;
}