/*!
	* @file        FB_ShowPvAddrData.c
	* @brief       显示变量的地址前后范围的实际数据
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
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

void FB_ShowPvAddrData(struct FB_ShowPvAddrData* inst)
{
    //保证此函数可在被连续调用重复使用。
    if ((memcmp((char *)inst->sName,(char *)inst->sNameTmp,sizeof(inst->sName)) != 0) || 
       (memcmp((char *)inst->sModuleName,(char *)inst->sModuleNameTmp,sizeof(inst->sModuleName)) != 0) ||
        inst->iOffset != inst->iOffsetTmp)
    {
        memcpy((char *)inst->sNameTmp,(char *)inst->sName,sizeof(inst->sName));
        memcpy((char *)inst->sModuleNameTmp,(char *)inst->sModuleName,sizeof(inst->sModuleName));
        inst->iOffsetTmp = inst->iOffset;
    
        inst->uStatus = 0; 
        inst->udCheckCallCount = 0;
    }
	
    if (inst->udCheckCallCount < 1 || inst->bContinuousWatch == 1)
    {
        inst->udCheckCallCount = 1;
        memset((char *)inst->auData,0,sizeof(inst->auData));
        memset((char *)inst->sData,0,sizeof(inst->sData));
        memset((char *)inst->auDataBefore,0,sizeof(inst->auDataBefore));
        memset((char *)inst->sDataBefore,0,sizeof(inst->sDataBefore));
        memcpy((char *)inst->FB_GetPvAddrStr_0.sModuleName,(char *)inst->sModuleName,sizeof(inst->sModuleName));
        memcpy((char *)inst->FB_GetPvAddrStr_0.sPvName,(char *)inst->sName,sizeof(inst->sName));
        FB_GetPvAddrStr(&inst->FB_GetPvAddrStr_0);
        if (inst->FB_GetPvAddrStr_0.uStatus == 0 )
        {
            if (inst->FB_GetPvAddrStr_0.udAddr != 0 && (inst->FB_GetPvAddrStr_0.udAddr + inst->iOffset > SHOW_LOCAL_PV_ADDR_SIZE))
            {
                memcpy((char *)inst->auData,(char *)inst->FB_GetPvAddrStr_0.udAddr + inst->iOffset,sizeof(inst->auData));
                memcpy((char *)inst->sData,(char *)inst->FB_GetPvAddrStr_0.udAddr + inst->iOffset,sizeof(inst->sData));
                memcpy((char *)inst->auDataBefore,(char *)inst->FB_GetPvAddrStr_0.udAddr + inst->iOffset - SHOW_LOCAL_PV_ADDR_SIZE - 1,sizeof(inst->auDataBefore));
                memcpy((char *)inst->sDataBefore,(char *)inst->FB_GetPvAddrStr_0.udAddr + inst->iOffset - SHOW_LOCAL_PV_ADDR_SIZE - 1,sizeof(inst->sDataBefore));
            }else
            {
                inst->uStatus = 1;//访问得到的地址为0
            }
            inst->udAddr = inst->FB_GetPvAddrStr_0.udAddr;	  
        }else
        {
            inst->uStatus = inst->FB_GetPvAddrStr_0.uStatus;
        }  
    }
}
