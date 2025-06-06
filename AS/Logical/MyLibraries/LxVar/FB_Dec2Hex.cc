/*!
	* @file        FB_Dec2Hex.cc
	* @brief       ���ô˺������ɽ���������ת��Ϊʮ�������ַ���
	* @date        �����ڣ�2021.02.19������޸����ڣ�2021.02.19
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.19    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
 ******************************************************************************
*/

#include <bur/plctypes.h>
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

void FB_Dec2Hex(struct FB_Dec2Hex* inst)
{
    memset((void *)&inst->sHex,0,sizeof(inst->sHex));

    sprintf((char *)&inst->sHex,"%x", inst->iDec);

}
