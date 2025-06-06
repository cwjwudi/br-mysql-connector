/*!
* @file        BrRand/RandDINT.c
* @brief       ���ô˺�������ʵ��DINT���������������
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
 *     ʹ�ð���: PV := RandDINT();
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

DINT RandDINT()
{
    DINT iTmpValue;
    iTmpValue = RandomBase();
    return iTmpValue;
}
