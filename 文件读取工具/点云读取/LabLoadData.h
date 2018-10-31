#pragma  once


int LabLoadDepth(int iCameraIndex, char *filename, float **pointCloud);
int LabLoadColor(int iCameraIndex, char *filename, unsigned char** ColorImage);
int LabSaveColor(char *filename, unsigned char* ColorImage);

void read_C(int p, double** pCparam, string s);
void read_RT(int p, double** RT, string s);

void readRTAxis(char* filename, double *readRTAxis);