#pragma once

#ifdef TESTDLL_EXPORTS 
	#define _XError_DLL_ _declspec(dllexport) 
#else 
	#define _XError_DLL_ _declspec(dllimport) 
#endif 

class _XError_DLL_ XError
{
public:
	XError(void);
	~XError(void);
public: 
	void ErrorFun(int *p);
};