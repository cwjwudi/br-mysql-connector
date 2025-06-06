/*!
	* @file      FB_ShowLocalPvAddrData.c
	* @brief     调用此函数，可观察当前任务下局部变量地址附近的内存分布情况
	* @date      创建于：2021.03.12；最后修改日期：2021.03.12
	* @version   V 1.00.1
	* @author    YuanZhiyi
	* @copyright B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.12    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/


#include <bur/plctypes.h>
#include <string.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

void FB_ShowLocalPvAddrData(struct FB_ShowLocalPvAddrData* inst)
{
	//保证此函数可在被连续调用重复使用。
	if (memcmp((char *)inst->sName,(char *)inst->sNameTmp,sizeof(inst->sName)) != 0)
	{
		memcpy((char *)inst->sNameTmp,(char *)inst->sName,sizeof(inst->sName));
		inst->udCheckCallCount = 0;
	}
	
	if (inst->udCheckCallCount < 1)
	{
		memset((char *)inst->usArrData,0,sizeof(inst->usArrData));
		memcpy((char *)inst->FB_GetLocalPvAddrStrY.sPvName,(char *)inst->sName,sizeof(inst->sName));
		FB_GetLocalPvAddr(&inst->FB_GetLocalPvAddrStrY);
		if (inst->FB_GetLocalPvAddrStrY.udAddr != 0)
		{
			memcpy((char *)inst->usArrData,(char *)inst->FB_GetLocalPvAddrStrY.udAddr,sizeof(inst->usArrData));
		}		
		inst->udAddr = inst->FB_GetLocalPvAddrStrY.udAddr;
	}
}
