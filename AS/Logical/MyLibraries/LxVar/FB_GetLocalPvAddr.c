/*!
	* @file        FB_GetLocalPvAddr.c
	* @brief       ���ô˺��������뵱ǰģ��ľֲ���������������ģ����������ͨ��srtOut�õ������ĵ�ַ��Ϣ����֧������Logger��¼��Ϣ
				   ͬ��ģ��ͬ������ִֻ��һ�Ρ�
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
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <string.h>
	#include <sys_lib.h>
#ifdef __cplusplus
	};
#endif

void FB_GetLocalPvAddr(struct FB_GetLocalPvAddr* inst)
{
	//��֤�˺������ڱ����������ظ�ʹ�á�
	if (memcmp((char *)inst->sPvName,(char *)inst->sPvNameTmp,sizeof(inst->sPvName)) != 0)
	{
		memcpy((char *)inst->sPvNameTmp,(char *)inst->sPvName,sizeof(inst->sPvName));
		inst->udCheckCallCount = 0;
	}
	
	if (inst->udCheckCallCount < 1)
	{
			memset((char *)inst->strOut,0,sizeof(inst->strOut));
			inst->udCheckCallCount++;
			//��ȡ����������
			FB_GetModuleName(&inst->FB_GetModuleNameY);
		
			//��ȡ��ַ��Ϣ�Լ�����
			memcpy((char *)inst->FB_GetPvInfoY.sAppModuleName,(char *)inst->FB_GetModuleNameY.strOut,sizeof(inst->FB_GetModuleNameY.strOut));
			memcpy((char *)inst->FB_GetPvInfoY.sName,(char *)inst->sPvName,sizeof(inst->sPvName));
			FB_GetPvInfo(&inst->FB_GetPvInfoY);
	
			//���UDINT���͵ĵ�ַ��Ϣ
			inst->udAddr = inst->FB_GetPvInfoY.udPvAddr;
			
			//�����ַ���ƴ��
			inst->FB_Udint2StrY.udInput = inst->FB_GetPvInfoY.udPvAddr;
			FB_Udint2Str(&inst->FB_Udint2StrY);
			strcat((char *)inst->strOut,(char *)inst->FB_GetPvInfoY.sPvName);
			strcat((char *)inst->strOut,(char *)" | Addr:");
			if (inst->udAddr == 0)//�ж��Ƿ��ȡ�ı���������
			{
				strcat((char *)inst->strOut,(char *)"PvNotExist");	
			}else
			{
				strcat((char *)inst->strOut,(char *)inst->FB_Udint2StrY.strOut);	
			}
		
			//�ж��Ƿ���ҪдLogger��Ϣ
			if (inst->bWriteLogEnableFlag ==  1 && inst->udCheckCallCount <= 1)
			{
				VarWarnLogWrite(7200,(UDINT)inst->strOut);
			}
	}
}
