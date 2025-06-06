/*!
	* @file        FB_GetPvAddrStr.c
	* @brief       调用此函数，可输入全局变量，可输入指定模块的局部变量，通过srtOut得到完整的地址信息，并支持生成Logger记录信息
				   同名模块同名变量只执行一次。
	* @date        创建于：2019.08.13；最后修改日期：2019.08.13
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2019.08.13    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/


#include <bur/plctypes.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <string.h>
	#include <sys_lib.h>
#ifdef __cplusplus
	};
#endif

void FB_GetPvAddrStr(struct FB_GetPvAddrStr* inst)
{
	//保证此函数可在被连续调用重复使用。
	if ((memcmp((char *)inst->sPvName,(char *)inst->sPvNameTmp,sizeof(inst->sPvName)) != 0) ||  
		(memcmp((char *)inst->sModuleName,(char *)inst->sModuleNameTmp,sizeof(inst->sModuleName)) != 0))
	{
		memcpy((char *)inst->sPvNameTmp,(char *)inst->sPvName,sizeof(inst->sPvName));
		memcpy((char *)inst->sModuleNameTmp,(char *)inst->sModuleName,sizeof(inst->sModuleName));
		inst->udCheckCallCount = 0;
	}
	
	if (inst->udCheckCallCount < 1)
	{
			memset((char *)inst->strOut,0,sizeof(inst->strOut));
			inst->udCheckCallCount++;
		
			//获取地址信息以及其他
			memcpy((char *)inst->FB_GetPvInfoY.sAppModuleName,(char *)inst->sModuleName,sizeof(inst->sModuleName));
			memcpy((char *)inst->FB_GetPvInfoY.sName,(char *)inst->sPvName,sizeof(inst->sPvName));
			FB_GetPvInfo(&inst->FB_GetPvInfoY);
      inst->uStatus = inst->FB_GetPvInfoY.status;
	
			//输出UDINT类型的地址信息
			inst->udAddr = inst->FB_GetPvInfoY.udPvAddr;
			
			//进行字符串拼接
			inst->FB_Udint2StrY.udInput = inst->FB_GetPvInfoY.udPvAddr;
			FB_Udint2Str(&inst->FB_Udint2StrY);
			strcat((char *)inst->strOut,(char *)inst->FB_GetPvInfoY.sPvName);
			strcat((char *)inst->strOut,(char *)" | Addr:");
			if (inst->udAddr == 0)//判断是否读取的变量不存在
			{
				strcat((char *)inst->strOut,(char *)" PvNotFound");	
			}else
			{
				strcat((char *)inst->strOut,(char *)inst->FB_Udint2StrY.strOut);	
			}
			//判断是否需要写Logger信息
			if (inst->bWriteLogEnableFlag ==  1 && inst->udCheckCallCount <= 1)
			{
				//WarnLogWriteY(7201,(UDINT)inst->strOut);
			}
	}	
}
