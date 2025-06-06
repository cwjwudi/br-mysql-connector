/*!
* @file        JudgeSrcPvInfoNum.c 
* @brief       �ж�GetPvInfoUser����ṹ��Ч����
* @date        �����ڣ�2018.02.19������޸����ڣ�2021.06.03
* @version     V1.00.2
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2018.02.19    V1.00.1   YuanZhiyi
 *         (new)     ����ʵ��
 *     2021.06.03    V1.00.2   YuanZhiyi
 *         (new)     ����ע��
 ******************************************************************************
*/


#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <string.h>
#ifdef __cplusplus
	};
#endif

#ifndef _LOCAL
#define _LOCAL
#endif
	
#define DATA_TYP GetPvInfoUser_typ
 
DATA_TYP *pStruPvInfo;

unsigned short JudgeSrcPvInfoNum(struct JudgeSrcPvInfoNumUser_typ* DataIn)
{
	//STEP 0:�жϵ�ǰ�������Ϣ�Ƿ���Ч
	if (DataIn->pPvArrInstance == 0) {
		DataIn->status = 7008;
		return 7008;//7008��JudgeSrcPvInfoNumY������ĵ�ַΪ��
	}
	if (DataIn->udPvArrInstanceLen == 0) {
		DataIn->status = 7009;
		return 7009;//7009: JudgeSrcPvInfoNumY�������������ռ�ռ�Ϊ��
	}
	//STEP 1:����Forѭ������ɨ���жϴ���������������Ƿ��㹻
	for (DataIn->udSrcNum = 0; DataIn->udSrcNum < DataIn->udPvArrInstanceLen; DataIn->udSrcNum++) {
		pStruPvInfo = (DATA_TYP *)(DataIn->pPvArrInstance + DataIn->udSrcNum * sizeof(DATA_TYP));
		if (memcmp((char *)pStruPvInfo->sName,(char *)"",1) == 0) {
			DataIn->status = 0;
			return 0;
		}
	}
	DataIn->status = 0;
	return 0;
}
