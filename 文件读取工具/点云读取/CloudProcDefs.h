/*=============================================================================

                Copyright (c) 2018 XTCLOUDPROC, XTOP
                            Unpublished

=============================================================================*/
#pragma once
#ifndef _max_element_num_
#define _max_element_num_      100
#endif

#include <vector>
using namespace std;

namespace TDCLD
{
	// 二维点
	struct TDPT2D
	{
		double dX;    // X坐标
		double dY;    // Y坐标
		TDPT2D()
		{
			dX = 0;
			dY = 0;
		}
	};

	// 三维点
	struct TDPT3D
	{
		double dX;    // X坐标
		double dY;    // Y坐标
		double dZ;    // Z坐标
		TDPT3D()
		{
			dX = 0;
			dY = 0;
			dZ = 0;
		}
	};

	// 三维点云定义
	struct TDNODE3D
	{
		__int64 iId;
		TDPT3D  Pt;                                    // 空间坐标
		TDPT3D  PtNormal;                              // 法向量
		RGBQUAD dwColor;                               // 颜色
		TDPT2D  PtImgPixel;                            // 二维像素点坐标
		int     iMainElement;                          // 所属主测头，点所在测头
		int     iRelateEleIndex[_max_element_num_];    // 点的所有相关测头（包含主测头）
		TDNODE3D()
		{
			iId = 0;
			iMainElement = -1;
			for (int i = 0; i < _max_element_num_; i++)
			{
				iRelateEleIndex[i] = -1;
			}
		}
	};

	// 面片顶点定义
	struct TDVERTEX3D
	{
		int                iIndex;                                // 自身索引号
		double			   dX;                                    // X坐标
		double			   dY;                                    // Y坐标
		double			   dZ;                                    // Z坐标
		//TDPT3D           VertexPt;                              // 顶点坐标
		TDPT3D             NormalVt;                              // 法向量
		int                iMainElement;                          // 所属测头
		int                iRelateEleIndex[_max_element_num_];    // 所有相关测头（包含主测头）
		RGBQUAD            dwColor;
		//long lColor      r || g || b || a//颜色
		double             dPixel[2];

		TDVERTEX3D()
		{
			iIndex = -1;
			dX = 0;
			dY = 0;
			dZ = 0;
			iMainElement = -1;
			for (int i = 0; i < _max_element_num_; i++)
			{
				iRelateEleIndex[i] = -1;
			}
			dPixel[0] = 0;
			dPixel[1] = 0;
		}
	
	};

	// 二维图像点定义
	struct TDPIXEL2D
	{
		int  iIndex; //自身索引号
		bool bDeleted; //删除
		double dX; //X坐标
		double dY; //Y坐标
		TDPIXEL2D()
		{
			iIndex = -1;
			bDeleted = false;
			dX = 0;
			dY = 0;
		}
	};

	//边的定义
	struct TDEDGE
	{
		int         iId;                    //每条边对应的起点的索引:
		int         iFaceId;                //三角形ID
		bool        bMark;                  //被标记
		TDEDGE*     pTwins;                 //相邻边
		TDEDGE*     pNext;                  //下一条边	

		TDEDGE()
		{
			iId = -1;
			iFaceId = -1;
			bMark = false;
			pTwins = 0;
			pNext = 0;
		}

		bool Isbundary()
		{
			if (pTwins == NULL && !bMark)
				return true;
			return false;
		}

	};

	//三角面片定义
	struct TDTRIANGLE3D
	{
		__int64                         iId;
		int                             iIndex[3];                          //三个点的索引号
		int                             iPixelIndex[3];                     //三个点的图像索引号
		int                             iMainElement;
		int                             iRelateEleIndex[_max_element_num_]; //所有相关测头（包含主测头）
		TDPT3D                          NormalVt;                           //法向量
		TDEDGE *                        pEdge[3];                           //面片的三条边
		TDTRIANGLE3D()
		{
			iId = -1;
			for (int i = 0; i < 3; i++)
			{
				iIndex[i] = -1;
				iPixelIndex[i] =-1;
				pEdge[i] = 0;
			}
			iMainElement = -1;
			for (int i = 0; i < _max_element_num_; i++)
			{
				iRelateEleIndex[i] = -1;
			}
		}
	};

	//三角面片集合定义
	struct TDSURFACE
	{
		int             iId;
		__int64         iVertexTotalNum;   //顶点总个数
		__int64         iPixelTotalNum;    //像素总个数
		__int64         iTriangleTotalNum; //三角面片总个数

		TDVERTEX3D      * p3Vertex;   // 顶点
		TDPIXEL2D       * p2Pixel;    // 像素
		TDTRIANGLE3D    * p3Triangle; // 三角面片
		
		RGBQUAD         dwColor;     //色彩
		int             iRelateEleIndex[_max_element_num_];//所有相关测头（包含主测头）
		int             iFrameWidth;  //贴图宽度
		int             iFrameHeight; //贴图高度

		TDSURFACE()
		{
			iId = -1;
			iVertexTotalNum = 0;
			iPixelTotalNum = 0;
			iTriangleTotalNum = 0;
			p3Vertex = 0;
			p2Pixel = 0;
			p3Triangle = 0;
			for (int i = 0; i < _max_element_num_; i++)
			{
				iRelateEleIndex[i] = -1;
			}
			iFrameWidth = 0;
			iFrameHeight = 0;
		}

		~TDSURFACE()
		{
			if (p3Vertex)
			{
				delete[]p3Vertex;
				p3Vertex = 0;
			}

			if (p2Pixel)
			{
				delete[]p2Pixel;
				p2Pixel = 0;
			}

			if (p3Triangle)
			{
				delete[]p3Triangle;
				p3Triangle = 0;
			}
		}

	};

	//外参数
	struct TDEOPARAM
	{
		double d2Rot[3][3];
		double dTrans[3];

		TDEOPARAM(void)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					d2Rot[i][j] = i == j ? 1 : 0;
				}
				dTrans[i] = 0;
			}
		}
	};
	
	//测头参数定义
	struct TDCAMERAELEMENT
	{
		int                  id;
		bool                 bColorCamera;  //是否为彩色相机
		unsigned int         uiFrameWidth;  //相机宽度
		unsigned int         uiFrameHeight; //相机高度
		unsigned int         uiWidthoffset; //宽度偏移
		unsigned int         uiHeightoffset;//高度偏移
		int                  iIntParaModel; //相机内参数模型,0是十参数，1 是双F
		double		         dSelfParam[10];//相机内参数
		TDEOPARAM            Eo;            //相机外参数

		TDCAMERAELEMENT()
		{
			id = -1;
			bColorCamera = false;
			uiFrameWidth = 1920;
			uiFrameHeight = 1200;
			iIntParaModel = 0;
			uiWidthoffset = 0;
			uiHeightoffset = 0;
			memset(dSelfParam, 0, sizeof(double) * 10);
		}
	};
	
	//点对应的边的索引
	struct TDPT2EDGE
	{
		int   isize;
		TDEDGE* addr[40];

		TDPT2EDGE()
		{
			isize = 0;
			for (int i = 0; i < 40; i++)
			{
				addr[i] = 0;
			}
		}

		TDPT2EDGE(const TDPT2EDGE& Other)
		{
			isize = Other.isize;
			memcpy(addr, Other.addr, 40 * sizeof(TDEDGE*));
		}

		TDPT2EDGE& operator = (const TDPT2EDGE& Other)
		{
			isize = Other.isize;
			memcpy(addr, Other.addr, 40 * sizeof(TDEDGE*));
			return (*this);
		}

		int bundaryNum()
		{
			int inum = 0;
			for (int i = 0; i < isize; i++)
			{
				if (addr[i]->Isbundary())
					inum++;
			}
			return inum;
		}

		TDEDGE * getbundary()
		{
			for (int i = 0; i < isize; i++)
			{
				if (addr[i]->Isbundary())
					return addr[i];
			}
			return 0;
		}

		TDEDGE * getEdge(int inextid)
		{
			for (int i = 0; i < isize; i++)
			{
				if (addr[i]->pNext->iId == inextid)
					return addr[i];
			}
			return 0;
		}

	};

	//网格数据结构
	struct  TDMESH
	{
		///数据
		TDNODE3D *               pNode;                                 //原始点集
		__int64                  iNode_size;                            //原始点个数
		bool                     bHasColor;                             //法向
		bool                     bHasNormal;                            //颜色
		TDEOPARAM                Eo;                                    //外参数

		///面片集合		   	     
		TDSURFACE                Facets;                                //三角面片
		__int64                  iFacets_size;                          //三角面片数

		///面片拓扑关系
		TDEDGE*                  pEdge;                                 //边集
		__int64                  iEdge_size;                            //边的个数
		TDPT2EDGE*               pPtoedge;                              //点对应的边的索引

		///二维图像点	         
		TDPIXEL2D*               PPixelPt;                               //图像像素点
		__int64                  iPixels_size;                           //像素点数

		///点云处理参数      
		int                      iId;                                     //点云id
		bool                     bReflection;                             //是否贴图
		RGBQUAD                  dwColor;                                 //点云颜色
		TDPT3D                   dCenter;                                 //点云中心
		double                   dAverageSpacing;                         //平均点距
		int                      iRelateEleIndex[_max_element_num_];      //点云生成源ID

		//测量头列表
		std::vector<TDCAMERAELEMENT>  vCamlist;
		int                           iFramewidth;                        //贴图的大小4096
		int                           iFrameheight;                       //贴图的大小4096
		std::vector<unsigned char *>  vpColorbufferList;                  //彩色图像列表
		std::vector<unsigned char *>  vpGreybufferList;                   //灰度图像列表

		TDMESH()
		{
			pNode = 0;
			iNode_size = 0;
			bHasColor = false;
			bHasNormal = false;
			iFacets_size = 0;
			pEdge = 0;
			iEdge_size = 0;
			pPtoedge = 0;
			PPixelPt = 0;
			iPixels_size = 0;

			iId = -1;
			bReflection = false;
			dAverageSpacing = 0;
			for (int i = 0; i < _max_element_num_; i++)
			{
				iRelateEleIndex[i] = -1;
			}

			iFrameheight = 0;
			iFramewidth = 0;
		}

		~TDMESH()
		{
			if (pNode)
			{
				delete[]pNode;
				pNode = 0;
			}
			iNode_size = 0;

			if (PPixelPt)
			{
				delete[]PPixelPt;
				PPixelPt = 0;
				iPixels_size = 0;
			}
			
			if (NULL != pEdge)
			{
				delete[]pEdge;
				pEdge = 0;
				iEdge_size = 0;
			}
			
			if (NULL != pPtoedge)
			{
				delete[]pPtoedge;
				pPtoedge = 0;
			}

			vCamlist.clear();

			for (int i = 0; i < (int)vpColorbufferList.size(); i++)
			{
				if (vpColorbufferList[i])
				{
					delete[]vpColorbufferList[i];
					vpColorbufferList[i] = NULL;
				}

			}
			vpColorbufferList.clear();

			for (int i = 0; i < (int)vpGreybufferList.size(); i++)
			{
				if (vpGreybufferList[i])
				{
					delete[]vpGreybufferList[i];
					vpGreybufferList[i] = NULL;
				}
			}
			vpGreybufferList.clear();

		}

		int  FindCamerabyId(int iid)
		{
			int ncamera = (int)vCamlist.size();
			for (int i = 0; i < ncamera; i++)
			{
				if (vCamlist[i].id == iid)
					return i;
			}
			return -1;
		}
	};

	struct TDMESHLIST
	{
		std::vector<TDMESH *>  m_vCloudList;
		~TDMESHLIST()
		{
			int iCloudNum = (int)m_vCloudList.size();
			for (int i = 0; i < iCloudNum;i++)
			{
				if (m_vCloudList[i]!=NULL)
				{
					delete m_vCloudList[i];
					m_vCloudList[i] = NULL;
				}
			}
			m_vCloudList.clear();
		}
	};
}