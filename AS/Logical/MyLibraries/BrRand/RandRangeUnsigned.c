/*!
* @file        BrRand/RandRangeUnsigned.c
* @brief       调用此函数，可实现指定范围的无符号整型数据随机生成
* @date        创建于：2018.01.16；最后修改日期：2021.05.16
* @version     V1.00.1
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.05.16    V1.00.1   YuanZhiyi
 *         (new)     更新实现
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     使用案例: PV := RandRangeUnsigned(5,200);
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

UDINT RandRangeUnsigned(UDINT min, UDINT max)
{
    if (min > 2147483647 && max > 2147483647) {
        return abs(RandRange(min - 2147483647,max - 2147483647)) + 2147483647;
    }else if (min <= 2147483647 && max > 2147483647 ) {
        if (rand() > 0 ){
            return RandRange(min,2147483647);
        }
        else{
            return RandRange(0,max - 2147483647) + 2147483647;
        }
    }else {
        return (abs(RandRange(min,max)) * 2 + RandRange(0,1)) / 2 ;
    }
}
