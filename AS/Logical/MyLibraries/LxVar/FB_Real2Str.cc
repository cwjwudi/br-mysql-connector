/*!
	* @file        FB_Real2Str.cc
	* @brief       带有小数点限制的REAL数据转换
	* @date        创建于：2019.11.12；最后修改日期：2019.11.13
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2019.11.12    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/


#include <bur/plctypes.h>
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

unsigned long bur_heap_size=0xFFF;

void FB_Real2Str(struct FB_Real2Str* inst)
{
	memset((void *)&inst->strOut,0,sizeof(inst->strOut));
    
	if (inst->digital == 0)
	{
	  sprintf((char *)&inst->strOut,"%.0f", inst->rNum);
	}
	if (inst->digital == 1)
	{
		sprintf((char *)&inst->strOut,"%.1f", inst->rNum);
	}
	if (inst->digital == 2)
	{
		sprintf((char *)&inst->strOut,"%.2f", inst->rNum);
	}
	if (inst->digital == 3)
	{
		sprintf((char *)&inst->strOut,"%.3f", inst->rNum);
	}
	if (inst->digital >= 4)
	{
		sprintf((char *)&inst->strOut,"%.4f", inst->rNum);
	}
	
}
