/*!
* @file        BrRand/RandRangeReal.c
* @brief       调用此函数，可实现指定范围的有符号数据随机生成
* @date        创建于：2018.01.16 最后修改日期：2021.09.23
* @version     V 1.00.2
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2018.01.16    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 *     2021.09.23    V1.00.2   YuanZhiyi
 *         (fix)     修正当min，max数值为0~1范围内数值时，随机数输出异常的问题。
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     使用案例: RandRangeReal(0.8,1);
 *     注意事项: 输入REAL类型数据范围为(-2147483,2147483)
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

REAL RandRangeReal(REAL min, REAL max)
{
    DINT tmpMin;
    DINT tmpMax;
    REAL tmpValue;
    tmpMin       = (DINT)(min * 1000);
    tmpMax       = (DINT)(max * 1000);
    tmpValue     = (REAL)RandRange(tmpMin,tmpMax);
    if (tmpValue < (REAL)tmpMin) {
        tmpValue = tmpValue + 1.0;
    }else if(tmpValue > (REAL)tmpMax) {
        tmpValue = tmpValue - 1.0;
    }
    return tmpValue / 1000.0;
}
