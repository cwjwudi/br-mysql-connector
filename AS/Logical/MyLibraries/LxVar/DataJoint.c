/*!
	* @file       DataJoint.c
	* @brief      根据地址信息，实现数据拼接
	* @date       创建于：2018.02.19；最后修改日期：2018.02.19
	* @version    V 1.00.1
	* @author     YuanZhiyi
	* @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2018.02.19    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <string.h>
#ifdef __cplusplus
	};
#endif

GetPvInfoUser_typ *pStruPvInfo; 

unsigned short DataJoint(struct DataJointUser_typ* DataIn)
{
	//一个任务周期就需要全部完成所有任务
	//STEP 0 清空|初始化
	memset((char *)DataIn->sCurrentName,0,sizeof(DataIn->sCurrentName));
	memset((char *)DataIn->sCurrentModName,0,sizeof(DataIn->sCurrentModName));
	memset((char *)DataIn->sErrLogMessage,0,sizeof(DataIn->sErrLogMessage));
	DataIn->udCurrentOffset = 0;
	DataIn->udDataIndex = 0;
	//STEP 1 检查输入的指针是否正常
	if (DataIn->pBuffer == 0 || DataIn->pSrcPvInfo == 0){
		DataIn->status = 7002;
		return 7002; //7002:DataJoint接收的指针为NULL
	}
	//STEP 2 进入循环进行处理
	for (DataIn->udDataIndex = 0; DataIn->udDataIndex < DataIn->udSrcPvInfoNum; DataIn->udDataIndex++){
		//STEP 2.1 进行数据准备 记录当前信息
		pStruPvInfo = (GetPvInfoUser_typ *)(DataIn->pSrcPvInfo + DataIn->udDataIndex * sizeof(GetPvInfoUser_typ));
		memcpy((char *)DataIn->sCurrentName,(char *)pStruPvInfo->sName,sizeof(pStruPvInfo->sName));
		memcpy((char *)DataIn->sCurrentModName,(char *)pStruPvInfo->sModuleName,sizeof(pStruPvInfo->sModuleName));
		//STEP 2.2 检测pStruPvInfo的信息是否完整。
		if (pStruPvInfo->udPvAddr == 0 || pStruPvInfo->udLenth == 0){
			//STEP 2.2.1 当数据异常时，则将卡主的地方变量传递至sErrLogMessage，便于找到错误点。
			strcpy((char *)DataIn->sErrLogMessage,(char *)"DataJointY::PV NOT FOUND:");//sErrLogMessage总长度不能超过160字节。
			strcat((char *)DataIn->sErrLogMessage,(char *)pStruPvInfo->sName);
			DataIn->status = 7003;
			return 7003;//7003:传入DataJoint的SrcPvInfo数据丢失，即传入的数据为错误的。
		}
		//STEP 2.3 进行Buffer边界判断，是否超界。
		if (DataIn->udCurrentOffset + pStruPvInfo->udLenth > DataIn->udBufferMaxLen ){
			DataIn->status = 7004;
			return 7004;//7004:DataJoint拼接数据流超出设定的Buffer。
		}
		//STEP 2.4 进行数据复制，存储信息
		memcpy((char *)(DataIn->pBuffer + DataIn->udCurrentOffset),(char *)pStruPvInfo->udPvAddr,(UDINT)pStruPvInfo->udLenth);
		DataIn->udCurrentOffset += pStruPvInfo->udLenth;	
		//break;		 
	}
	DataIn->status = 0;
    return 0;
}
