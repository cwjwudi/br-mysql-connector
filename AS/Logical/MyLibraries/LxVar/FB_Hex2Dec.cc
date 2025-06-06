/*!
	* @file        FB_Hex2Dec.cc
	* @brief       调用此函数，可将十六进制字符串转换为整形数据
	* @date        创建于：2021.02.19；最后修改日期：2021.02.19
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.19    V1.00.1   YuanZhiyi
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

void FB_Hex2Dec(struct FB_Hex2Dec* inst)
{
    sscanf((const char *)&inst->sHex, (const char *)"%x", &inst->iDec);
    
    memset((void *)&inst->sHex,0,sizeof(inst->sHex));
}
