/*!
* @file        BrRand/RandREAL.c
* @brief       调用此函数，可实现REAL类型数据随机生成
* @date        创建于：2018.01.16 最后修改日期：2021.02.07
* @version     V 1.00.1
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.07    V1.00.1   YuanZhiyi
 *         (new)     完成版本
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     使用案例: PV := RandREAL();
 ******************************************************************************
*/


#include <bur/plctypes.h>
#include <stdlib.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "BrRand.h"
#ifdef __cplusplus
	};
#endif

REAL RandREAL()
{
    REAL tmpValue;
    tmpValue = (float)RandomBase() * (float)RandomBase() * (float)RandomBase() / (float)RandRange(1,2147483647) * RandSINT();
    return tmpValue;
}
