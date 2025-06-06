/*!
* @file        BrRand/RandRangeSigned.c
* @brief       ���ô˺�������ʵ��ָ����Χ���з������������������
* @date        �����ڣ�2018.01.16������޸����ڣ�2021.02.07
* @version     V1.00.1
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.07    V1.00.1   YuanZhiyi
 *         (new)     ����ʵ��
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     ʹ�ð���: PV := RandRangeSigned(-10,10);
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
