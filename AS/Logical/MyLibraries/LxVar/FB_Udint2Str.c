/*!
	* @file        FB_Udint2Str.c
	* @brief       ���ô˺�������ͨ��srtOut�õ�UDINT��������ת��Ϊ�ַ�������Ϣ�����ܵõ��ַ�����ʵ�ʳ��ȡ�
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
	#include <AsBrStr.h>
    #include <string.h>
#ifdef __cplusplus
	};
#endif

void FB_Udint2Str(struct FB_Udint2Str* inst)
{	
	memset((UDINT *)inst->strOut,0,sizeof(inst->strOut));
	if (inst->udInput > 2147483647LL && inst->udInput < 3000000000LL )
	{
		inst->uiLen = brsitoa((DINT)(inst->udInput - 1000000000LL), (UDINT)&inst->strOut);
		memcpy((UDINT *)inst->strOut,(UDINT *)"2",1);
	}else if (inst->udInput >= 3000000000LL && inst->udInput < 4000000000LL )
	{
		inst->uiLen = brsitoa((DINT)(inst->udInput - 2000000000LL), (UDINT) inst->strOut);
		memcpy((UDINT *)inst->strOut,(UDINT *)"3",1);
	}else if (inst->udInput >= 4000000000LL)
	{
		inst->uiLen = brsitoa((DINT)(inst->udInput - 3000000000LL), (UDINT) inst->strOut);
		memcpy((UDINT *)inst->strOut,(UDINT *)"4",1);
	}else{
		inst->uiLen = brsitoa((DINT)(inst->udInput), (UDINT) inst->strOut);
	}
}
