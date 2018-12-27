#include "userInterface.h"
#include <stdio.h>

XError::XError()
{
	printf("HELLO.\n");
}

XError::~XError()
{
	printf("BYE.\n");
}

void XError::ErrorFun(int *p)
{
	printf("%d.\n", *p);
	p[10] = 22;  // crash position
	int debug = 0;
}
