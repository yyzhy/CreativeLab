// 安全释放指针 
template<class Interface> 
inline void SafeRelease(Interface *& pInterfaceToRelease) 
{ 
    if (pInterfaceToRelease != NULL) 
    {
        pInterfaceToRelease->Release(); 
        pInterfaceToRelease = NULL; 
    } 
}


//FreePointer
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

template <typename T>
void freedoublepointer(T **point, int num)
{
	if (point != NULL)
	{
		for (int v = 0; v < num; v++)
		{
			if (point[v] != NULL)
			{
				delete point[v];
				point[v] = NULL;
			}
		}
		delete point;
		point = NULL;
	}
}

#define FREEPOINTER(pointer) if ((pointer) != NULL) { delete (pointer); (pointer) = NULL; }