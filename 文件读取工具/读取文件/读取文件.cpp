#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    FILE* pFile = NULL;
    char str[50];
    int num;
    pFile = fopen("1.txt", "rt");
    if(pFile==NULL) { cerr<<"error!"<<endl; exit(-1); }
    while(!feof(pFile)) {
        int res = fscanf(pFile, "%s", str);
        //防止最后一行读两遍
        if(res == -1) { break; }
        if(strcmp(str,"v")==0) {
            fscanf(pFile, "%d", &num);
            printf("%d\n", num);
        }

    }
    fclose(pFile);

    return 0;
}