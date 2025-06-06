/*!
* @file        BrRand/RandRangeReal.c
* @brief       ���ô˺�������ʵ��ָ����Χ���з��������������
* @date        �����ڣ�2018.01.16 ����޸����ڣ�2021.09.23
* @version     V 1.00.2
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2018.01.16    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
 *     2021.09.23    V1.00.2   YuanZhiyi
 *         (fix)     ������min��max��ֵΪ0~1��Χ����ֵʱ�����������쳣�����⡣
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     ʹ�ð���: RandRangeReal(0.8,1);
 *     ע������: ����REAL�������ݷ�ΧΪ(-2147483,2147483)
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
