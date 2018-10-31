#ifndef BODYCLOUD_DEFS_H
#define BODYCLOUD_DEFS_H

#include <vector>
using namespace std;

namespace GMB_REC
{
	struct Pt2d
	{
		double dX;//坐标X
		double dY;//坐标Y
		Pt2d()
		{
			dX = 0;
			dY = 0;
		}
	};

	struct Pt3d
	{
		double dX;//坐标X
		double dY;//坐标Y
		double dZ;//坐标Z
		Pt3d()
		{
			dX = 0;
			dY = 0;
			dZ = 0;
		}
	};

	struct GlPt3d
	{
		int iId;//ID信息
		int iGroup;//分组信息
		Pt3d pt;//点坐标
		GlPt3d()
		{
			iId = -1;
			iGroup = 0;
		}
	};

	struct Pixel2d
	{
		int iId;//ID
		Pt2d pix;//图像坐标
		Pixel2d()
		{
			iId = -1;
		}
	};

	typedef Pt3d Normal3d;//法向量

	struct Vertex3d
	{
		int iId;//ID
		int iMapId;//MAP ID
		unsigned long ulColor;//颜色
		bool bDelete;//是否删除
		bool bSelect;//是否被选择	
		Pt2d pix;//图像坐标
		Pt3d pt;//坐标
		Normal3d norm;//法向量
		Vertex3d()
		{
			iId = -1;
			iMapId = -1;
			ulColor = -1;
			bDelete = false;
			bSelect = false;
			norm.dX = 1.0;
			norm.dY = 0;
			norm.dZ = 0;
		}
	};

	struct ImageBuffer
	{
		bool bValid;//是否有效
		unsigned short bit;//位深度
		int iWidth;//宽度
		int iHeight;//高度
		unsigned char* pBuf;//图像数据缓存，非对齐
		unsigned short* pDepBuf;//16位深度数据缓存
		ImageBuffer()
		{
			bValid = 0;
			bit = 8;//深度图bit为16
			iWidth = 1;
			iHeight = 1;
			pBuf = 0;
			pDepBuf = 0;
		}
		~ImageBuffer()
		{
			if (pBuf)
			{
				delete[]pBuf;
				pBuf = 0;
			}
			if (pDepBuf)
			{
				delete[]pDepBuf;
				pDepBuf = 0;
			}
		}
		void Free()//释放
		{
			if (pBuf)
			{
				delete[]pBuf;
				pBuf = 0;
			}
			if (pDepBuf)
			{
				delete[]pDepBuf;
				pDepBuf = 0;
			}
			bValid = 0;
			bit = 8;
			iWidth = 0;
			iHeight = 0;
		}
	};

	struct GmbEo  // 相机外参数定义  X = invR*(W-T)
	{
		int iStatus;//外参数状态
		int iType;//外参数类型  0：独立   1：相对
		double dRotate[3][3];//旋转矩阵
		double dTrans[3];//平移矩阵
		GmbEo()
		{
			Init();
		}
		void Init()
		{
			iStatus = 0;
			iType = 0;
			for (int p = 0; p < 3; p++)
			{
				for (int q = 0; q < 3; q++)
				{
					dRotate[p][q] = p == q ? 1 : 0;
				}
				dTrans[p] = 0;
			}
		}
	};

	struct GmbCamera//相机定义
	{
		int iId;//ID
		int iStatus;//内参状态
		int bBase;//是否基准
		int iRefCameraId;//参考相机ID
		int iFrameWidth;//幅面宽度
		int iFrameHeight;//幅面高度
		double dFocal;//焦距
		double dPixelSize;//像元尺寸
		int bAdjustInterior;//是否调整内参数
		int bFixedPrinciple;//是否固定主点偏差
		unsigned int uiInteriorParModel;//内参模型
		unsigned int uiDistortionModel;//畸变模型
		double dSelfPar[10];//内参数 10个
		double dScaleRatio;// 比例因子
		GmbEo Eo;//外参数
		GmbCamera()
		{
			iId = -1;
			iStatus = 0;
			bBase = 0;
			iRefCameraId = -1;
			iFrameWidth = 0;
			iFrameHeight = 0;
			dFocal = 12;
			dPixelSize = 3.75;
			bAdjustInterior = 1;
			bFixedPrinciple = 0;
			uiInteriorParModel = 0;
			uiDistortionModel = 0x000003FF;
			dSelfPar[0] = (dPixelSize != 0) ? (dFocal * 1000 / dPixelSize) : 0;
			dScaleRatio = 1;
			for (int i = 1; i < 10; i++)
			{
				dSelfPar[i] = 0;
			}
		}
	};

	struct PtCloud
	{
		int iId;//点云ID
		int iVertexNum;//点个数
		bool bVisible;//显示
		bool bSelect;//选择
		bool bMapValid;//对应关系是否有效
		bool bHasColor;//颜色是否有效
		bool bNoiseRemoved;//是否已经去除噪点
		bool bLock;//内存被锁定
		bool bHasNormal;//是否有法向量
		unsigned long ulColor;//默认颜色
		Vertex3d* pVertex;//定点内存指针
		GmbCamera depCamera;//深度相机
		GmbCamera iRCamera;//红外相机
		GmbCamera colCamera;//彩色相机
		ImageBuffer depBuffer;//深度数据
		ImageBuffer imgBuffer;//彩色图像数据
		PtCloud()
		{
			iId = -1;
			iVertexNum = 0;
			pVertex = 0;
			bVisible = true;
			bSelect = false;
			bMapValid = false;
			bNoiseRemoved = false;
			bHasColor = false;
			bLock = false;
			bHasNormal = false;
			ulColor = 0x0a << 16 | 0xf0 << 8 | 0x0a;
		}
		~PtCloud()
		{
			if (pVertex)
			{
				delete[]pVertex;
				pVertex = 0;
			}
		}
	};

	struct Triangle3d
	{
		int iId;//三角面片id
		bool bDelete;//是否删除
		bool bSelect;//是否选择
		int iVertexIndex[3];//对应定点索引
		int iPixelIndex[3];//点像对应贴图坐标索引
		Normal3d norm;//法向量
		Triangle3d()
		{
			iId = -1;
			bDelete = false;
			bSelect = false;
			iVertexIndex[0] = -1;
			iVertexIndex[1] = -1;
			iVertexIndex[2] = -1;
			iPixelIndex[0] = -1;
			iPixelIndex[1] = -1;
			iPixelIndex[2] = -1;
		}
	};

	struct MeshCloud
	{
		int iId;//网格id
		bool bVisible;//显示
		bool bSelect;//被选择
		bool bLock;//内存被锁定
		bool bVertexHasColor;//顶点是否着色
		bool bVertexHasMap;//顶点有点相对应
		bool bVertexHasNormal;//定点是否有法向量
		bool bTextured;//是否贴图
		int iVertexNum;//点个数
		int iTriangleNum;//面片个数	
		int iPixelNum;//像点个数
		unsigned long ulColor;//默认颜色
		Vertex3d *pVertex;//定点数据
		Triangle3d *pTriangle;//三角面片数据
		Pixel2d *pPixel;//贴图坐标,单位化[0-1]
		ImageBuffer imgBuffer;//贴图图像数据
		MeshCloud()
		{
			iId = -1;
			bVisible = true;
			bSelect = false;
			bLock = false;
			bTextured = false;
			bVertexHasColor = false;
			bVertexHasMap = false;
			bVertexHasNormal = false;
			iVertexNum = 0;
			iTriangleNum = 0;
			iPixelNum = 0;
			ulColor = 0x0a << 16 | 0xf0 << 8 | 0x0a;
			pVertex = 0;
			pTriangle = 0;
			pPixel = 0;
		}
		~MeshCloud()
		{
			if (pVertex)
			{
				delete[]pVertex;
				pVertex = 0;
			}
			if (pTriangle)
			{
				delete[]pTriangle;
				pTriangle = 0;
			}
			if (pPixel)
			{
				delete[]pPixel;
				pPixel = 0;
			}
		}
	};

	struct GmbPara
	{
		int bRemoveNormalIllegal;//删除法向量非法点
		int bRemoveOutlier;//去飞点
		int bRemoveIsolation;//去孤立点
		double dOutlierCutValue;//飞点概率阀值
		double dIsolationCutValue;//孤立度阀值
		int iReconstructQuality;//重建强度 [0-6] 默认4
		int bFilleHole;//是否补洞
		int iHoleSizeTol;//补洞大小阀值
		double dRemeshRatio;//网格重生成系数
		int bCutGround;//是否切除底面
		double dGroundOffset;//底面切除比例
		int bUseMultiProcessor;//使用多核CPU并行运算
		int iUsedCPUs;//使用的CPU线程个数
		int iTexImgWidth;//目标贴图尺寸宽度
		int iTexImgHeight;//目标贴图尺寸高度
		int bUseFieldCut;//使用景深约束切除
		int iFieldDepth[6];//每幅深度图景深切除参数  0-1，X范围， 2-3，Y范围， 4-5，深度范围， 以深度图左上角为基准
		GmbPara()
		{
			bRemoveNormalIllegal = 0;
			bRemoveOutlier = 1;
			bRemoveIsolation = 1;
			dOutlierCutValue = 0.6;
			dIsolationCutValue = 0.15;
			iReconstructQuality = 4;
			bFilleHole = 1;
			iHoleSizeTol = 500;
			dRemeshRatio = 1.0;
			bCutGround = 1;
			dGroundOffset = 20;
			bUseMultiProcessor = 1;
			iUsedCPUs = 0;
			iTexImgWidth = 2048;
			iTexImgHeight = 2048;
			bUseFieldCut = 1;
			iFieldDepth[0] = 0;
			iFieldDepth[1] = 640;
			iFieldDepth[2] = 0;
			iFieldDepth[3] = 480;
			iFieldDepth[4] = 700;
			iFieldDepth[5] = 1300;
		}
	};

	struct GmbData
	{
		GmbPara para;//计算参数
		vector<PtCloud *> vPtCloudList;//点云列表
		vector<MeshCloud *> vMeshCloudList;//网格列表
		void Clear()
		{
			int nPtCloud = (int)vPtCloudList.size();
			for (int i = 0; i < nPtCloud; i++)
			{
				if (vPtCloudList[i])
				{
					delete vPtCloudList[i];
					vPtCloudList[i] = 0;
				}
			}
			vPtCloudList.clear();

			int nMeshCloud = (int)vMeshCloudList.size();
			for (int i = 0; i < nMeshCloud; i++)
			{
				if (vMeshCloudList[i])
				{
					delete vMeshCloudList[i];
					vMeshCloudList[i] = 0;
				}
			}
			vMeshCloudList.clear();
		}
		~GmbData()
		{
			Clear();
		}
	};

	
	

}


#endif