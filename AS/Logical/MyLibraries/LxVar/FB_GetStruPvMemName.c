/*!
	* @file        FB_GetStruPvMemName.c
	* @brief       ֧�־ֲ��Լ�ȫ�ֵı����г�������ĳ�Ա������
	* @date        �����ڣ�2019.08.13������޸����ڣ�2019.08.13
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2019.08.13    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
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
	//��֤�˺������ڱ����������ظ�ʹ�á�
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
    
    //���������Ǳ���ȫ��
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
					inst->uiStatus = 0;//���Ϊ�ձ����������Ϊ��Ա�б���г������
				}
                if (inst->uiStatus == 14713)
                {
                    inst->uiStatus = 0;//ERR_PV_NODETAIL,���ʵ���һ��ʵ�ʱ����������ǽṹ���Լ����顣
                }
				return;
			}
			inst->uiMemNum = inst->uiIndex + 1;
		}
	}
}
