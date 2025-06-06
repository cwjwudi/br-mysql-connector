/*!
* @file        BrRand/RandBOOL.c
* @brief       ���ô˺�������ʵ��BOOL���������������
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
 *     ʹ�ð���: PV := RandBOOL();
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

extern int rand();

plcbit RandBOOL(void)
{
	if (RandomBase() > 0) {
		return 1;
	} else {
		return 0;
	}
}
