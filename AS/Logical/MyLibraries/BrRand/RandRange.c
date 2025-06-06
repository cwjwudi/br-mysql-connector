/*!
* @file        BrRand/RandRange.c
* @brief       ���ô˺�������ʵ���������Χ����
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
                                                                  
DINT RandRange(DINT min, DINT max)
{
	if (min > max) {
		return 0;
	} else if ((min == 0) && (max == 0)) {
		return RandomBase();
	} else if(min == max){
		return min;
    }else {
        // Note -  This will bias the randomness slightly, but probably not anything to be concerned about if you're not doing something particularly sensitive.
        return rand() % (max + 1 - min) + min;
    }
}

