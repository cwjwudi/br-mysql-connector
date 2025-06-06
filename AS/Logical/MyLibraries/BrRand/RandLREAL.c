/*!
* @file        BrRand/RandLREAL.c
* @brief       ���ô˺�������ʵ��LREAL���������������
* @date        �����ڣ�2018.01.16 ����޸����ڣ�2021.02.07
* @version     V 1.00.1
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.07    V1.00.1   YuanZhiyi
 *         (new)     ��ɰ汾
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     ʹ�ð���: PV := RandLREAL();
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

LREAL RandLREAL()
{
    LREAL tmpValue;
    tmpValue = RandREAL() * rand() * 3.14159 / RandRange(1,1000) * RandRange(0,0) * 2.19 * rand() *  RandSINT();
    if (rand() < 0) {
        tmpValue = tmpValue * -1.0;
    }
    return tmpValue;
}
