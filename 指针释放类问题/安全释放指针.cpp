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
