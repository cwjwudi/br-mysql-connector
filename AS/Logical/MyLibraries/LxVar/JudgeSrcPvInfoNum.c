/*!
* @file        JudgeSrcPvInfoNum.c 
* @brief       判断GetPvInfoUser数组结构有效长度
* @date        创建于：2018.02.19；最后修改日期：2021.06.03
* @version     V1.00.2
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2018.02.19    V1.00.1   YuanZhiyi
 *         (new)     初步实现
 *     2021.06.03    V1.00.2   YuanZhiyi
 *         (new)     补充注释
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
	//STEP 0:判断当前输入的信息是否有效
	if (DataIn->pPvArrInstance == 0) {
		DataIn->status = 7008;
		return 7008;//7008：JudgeSrcPvInfoNumY被传入的地址为空
	}
	if (DataIn->udPvArrInstanceLen == 0) {
		DataIn->status = 7009;
		return 7009;//7009: JudgeSrcPvInfoNumY被传入的数据所占空间为空
	}
	//STEP 1:进行For循环处理，扫描判断此输入数组的数据是否足够
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
