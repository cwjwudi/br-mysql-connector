/*!
	* @file      FB_ShowLocalPvAddrData.c
	* @brief     ���ô˺������ɹ۲쵱ǰ�����¾ֲ�������ַ�������ڴ�ֲ����
	* @date      �����ڣ�2021.03.12������޸����ڣ�2021.03.12
	* @version   V 1.00.1
	* @author    YuanZhiyi
	* @copyright B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.12    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
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
	//��֤�˺������ڱ����������ظ�ʹ�á�
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
