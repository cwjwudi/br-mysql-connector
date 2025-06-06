/*!
	* @file        FB_GetStruPvMemName.c
	* @brief       支持局部以及全局的变量列出其包含的成员变量名
	* @date        创建于：2019.08.13；最后修改日期：2019.08.13
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2019.08.13    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/


#include <bur/plctypes.h>
#include <string.h>
#include <sys_lib.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

void FB_GetStruPvMemName(struct FB_GetStruPvMemName* inst)
{
	//保证此函数可在被连续调用重复使用。
	if ((memcmp((char *)inst->sName,(char *)inst->sNameTmp,sizeof(inst->sName)) != 0) || 
		 (memcmp((char *)inst->sModuleName,(char *)inst->sModuleNameTmp,sizeof(inst->sModuleName)) != 0))
	{
		memcpy((char *)inst->sNameTmp,(char *)inst->sName,sizeof(inst->sName));
		if (inst->LocalFlag == 0)
		{
	 		memcpy((char *)inst->sModuleNameTmp,(char *)inst->sModuleName,sizeof(inst->sModuleName));
		}else
		{
			FB_GetModuleName(&inst->FB_GetModuleNameY);
			memcpy((char *)inst->sModuleName,(char *)inst->FB_GetModuleNameY.strOut,sizeof(inst->sModuleName));
			memcpy((char *)inst->sModuleNameTmp,(char *)inst->sModuleName,sizeof(inst->sModuleName));
		}
		
        memset((char *)inst->sCompleteName,0,sizeof(inst->sCompleteName));
        memset((char *)inst->sCompleteNameTmp,0,sizeof(inst->sCompleteNameTmp));
		memset((char *)inst->sPvName,0,sizeof(inst->sPvName));
		Strcats((UDINT)inst->sPvName,sizeof(inst->sPvName),(UDINT)inst->sModuleName);
		Strcats((UDINT)inst->sPvName,sizeof(inst->sPvName),(UDINT)":");
		Strcats((UDINT)inst->sPvName,sizeof(inst->sPvName),(UDINT)inst->sName);
		
		inst->udCheckCallCount = 0;
		inst->uiMemNum = 0;
		inst->uiStatus = 0;
	}
    
    //如果输入的是变量全名
    if (memcmp((char *)inst->sCompleteName,(char *)inst->sCompleteNameTmp,sizeof(inst->sCompleteNameTmp)) != 0) {
        memcpy((char *)inst->sCompleteNameTmp,(char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        
        memset((char *)inst->sName,0,sizeof(inst->sName));
        memset((char *)inst->sNameTmp,0,sizeof(inst->sNameTmp));
        memset((char *)inst->sModuleName,0,sizeof(inst->sModuleName));
        memset((char *)inst->sModuleNameTmp,0,sizeof(inst->sModuleNameTmp));
        
        memcpy((char *)inst->sPvName,(char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        
        inst->udCheckCallCount = 0;
        inst->uiMemNum = 0;
        inst->uiStatus = 0;
    }
    
    
	if (inst->udCheckCallCount < 1)
	{
		inst->udCheckCallCount++;
		memset(inst->sArrMemName,0,sizeof(inst->sArrMemName));
		for (inst->uiIndex = 0; inst->uiIndex < GET_STRU_PV_NAME_SIZE; inst->uiIndex ++)
		{
			inst->uiStatus = PV_item((char *)inst->sPvName, (UINT)inst->uiIndex, (char *)inst->sArrMemName[inst->uiIndex]);
			if (inst->uiStatus != 0)
			{
				if (inst->uiStatus == 14704)
				{
					inst->uiStatus = 0;//如果为空变量，则可认为成员列表的列出已完成
				}
                if (inst->uiStatus == 14713)
                {
                    inst->uiStatus = 0;//ERR_PV_NODETAIL,访问的是一个实际变量，并非是结构体以及数组。
                }
				return;
			}
			inst->uiMemNum = inst->uiIndex + 1;
		}
	}
}
