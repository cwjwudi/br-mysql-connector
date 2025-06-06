/*!
	* @file        FB_Udint2Str.c
	* @brief       调用此函数，可通过srtOut得到UDINT类型数据转换为字符串的信息，并能得到字符串的实际长度。
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
