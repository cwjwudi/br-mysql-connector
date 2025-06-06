/*!
* @file        BrRand/RandomBase.c
* @brief       ���ô˺�����ʵ��DINT���͵����������
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
 *     
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

int rand();

signed long RandomBase(void)
{
    signed long i = 0;
    if ( rand()  > 1073741823 ) {
        i =  rand(); 
    }else { 
        i = -1 * rand();
    }
    return i;
}


