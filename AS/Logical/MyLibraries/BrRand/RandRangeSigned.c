/*!
* @file        BrRand/RandRangeSigned.c
* @brief       调用此函数，可实现指定范围的有符号整型数据随机生成
* @date        创建于：2018.01.16；最后修改日期：2021.02.07
* @version     V1.00.1
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.07    V1.00.1   YuanZhiyi
 *         (new)     初步实现
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     使用案例: PV := RandRangeSigned(-10,10);
 ******************************************************************************
*/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "BrRand.h"
#ifdef __cplusplus
	};
#endif

DINT RandRangeSigned(DINT min, DINT max)
{
    return RandRange(min,max);
}
