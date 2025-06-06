/*!
	* @file        FB_GetModuleName.c
	* @brief       ���ô˺�������ȡ���ô˹��ܿ��������
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

void FB_GetModuleName(struct FB_GetModuleName* inst)
{	
	if (inst->udCheckCallCount <= 2)
	{
			memset((char *)inst->strOut,0,sizeof(inst->strOut));
			ST_name((UDINT)0,(char *)inst->strOut,(USINT *)0);
			inst->udCheckCallCount++;
	}
}
