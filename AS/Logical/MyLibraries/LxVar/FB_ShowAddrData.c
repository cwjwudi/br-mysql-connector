/*!
	* @file      FB_ShowAddrData.c
	* @brief     调用此函数，可观察地址附近的内存分布情况
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

void FB_ShowAddrData(struct FB_ShowAddrData* inst)
{
    //保证此函数可在被连续调用重复使用。
    if ((inst->pWatchAddr != inst->pWatchAddrTmp) || (inst->iOffset != inst->iOffsetTmp))
    {
        inst->pWatchAddrTmp = inst->pWatchAddr;
        inst->iOffsetTmp    = inst->iOffset;
    
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
        
        inst->udCurrentAddr = inst->pWatchAddr + inst->iOffset;

        if (inst->pWatchAddr != 0 && (inst->udCurrentAddr > SHOW_LOCAL_PV_ADDR_SIZE))
        {
            memcpy((char *)inst->auData,(char *)inst->udCurrentAddr,sizeof(inst->auData));
            memcpy((char *)inst->sData,(char *)inst->udCurrentAddr,sizeof(inst->sData));
            memcpy((char *)inst->auDataBefore,(char *)inst->udCurrentAddr - SHOW_LOCAL_PV_ADDR_SIZE - 1,sizeof(inst->auDataBefore));
            memcpy((char *)inst->sDataBefore,(char *)inst->udCurrentAddr - SHOW_LOCAL_PV_ADDR_SIZE - 1,sizeof(inst->sDataBefore));
        }else
        {
            inst->uStatus = 1;//访问得到的地址为0
        }     
    }
}
