/*!
	* @file       GetPvOutside.c
	* @brief      将变量信息获取并输出至外部数据结构中
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

FB_GetPvInfo_typ GetPvInfoY_0;                   
                                        
unsigned short GetPvOutside(struct GetPvInfoUser_typ* dataIn)
{
	
	//是否增加dataIn的数据校验？
	//如果数据不正常，应该会在编译时就报错。但需要确认数据是否正常
	memcpy((char *)&GetPvInfoY_0.sAppModuleName,(char *)dataIn->sModuleName,sizeof(dataIn->sModuleName));
	memcpy((char *)GetPvInfoY_0.sName,(char *)dataIn->sName,sizeof(dataIn->sName));
	FB_GetPvInfo(&GetPvInfoY_0);
	if(GetPvInfoY_0.status == 0){
		memcpy((char *)dataIn->sDataType,(char *)GetPvInfoY_0.sDataType,19);
		dataIn->udLenth = GetPvInfoY_0.udLenth;
		dataIn->udPvAddr = GetPvInfoY_0.udPvAddr;
	}else{
		memset((char *)dataIn->sDataType,0,19);
		dataIn->udLenth = 0;
		dataIn->udPvAddr = 0;	
	}
	return GetPvInfoY_0.status;
}
