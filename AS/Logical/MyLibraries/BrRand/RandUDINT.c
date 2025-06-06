/*!
* @file        BrRand/RandUDINT.c
* @brief       ���ô˺�������ʵ��UDINT���������������
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
 *     ʹ�ð���: PV := RandUDINT();
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

UDINT RandUDINT()
{
    return abs(RandRange(0,0)) * 2 + RandRange(0,1) ;
}
