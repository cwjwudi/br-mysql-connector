/*!
	* @file      FB_ContinualStrcat.c
	* @brief     可具有保护的,用于连续strcat操作的函数,避免负载过高
	* @date      创建于：2021.06.03；
	* @author    YuanZhiyi
	* @copyright B&R
*/
/*! History
 *****************************************************************************
 *     2021.06.03    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 *     2021.06.09    V1.00.2   YuanZhiyi
 *         (new)     增加uStrSize，整体字符串长度输出接口
 *     2022.10.31    V1.00.3   YuanZhiyi
 *         (new)     增加可选的uDestStrOffset，从目标字符串的某一偏移量开始进行字符串添加
 ******************************************************************************
*/
/*! Attention
 *****************************************************************************
    inst->uSrcMaxSize与inst->uDestMaxSize均为可选项，若不输入，则不进行安全检查
    此函数的目的为替换strcat函数，避免当字符串较大时，Strcat在找Dest的地址消耗过多资源
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

void FB_ContinualStrcat(struct FB_ContinualStrcat* inst)
{
    if (inst->bInitial == 1) {
        inst->uOffset = 0;
        inst->bInitial = 0;
        if (inst->uDestMaxSize == 0) {
            /*----------在没有输入uDestMaxSize的情况下的执行方式---------------*/
            inst->uOffset = strlen((char *)inst->psDestStr + inst->uDestStrOffset) + inst->uDestStrOffset;
        }
        else {
            inst->uOffset = Strlens(inst->psDestStr + inst->uDestStrOffset,inst->uDestMaxSize) + inst->uDestStrOffset;
        }  
    }
    
    if (inst->psSrcStr == 0 || inst->psDestStr == 0) {
        inst->uStatus = 7210; //输入地址为NULL
    }
    else {
        if (inst->uSrcMaxSize == 0) {
            /*----------在没有输入uSrcMax的情况下的执行方式---------------*/
            inst->uSrcActualLenth = strlen((char *)inst->psSrcStr);
        }
        else {
            inst->uSrcActualLenth = Strlens(inst->psSrcStr,inst->uSrcMaxSize);
        }
        
        /*-----------------进行目标地址边界检查，若没有输入uDestMaxSize，则不判断---------------*/
        if (inst->uOffset + inst->uSrcActualLenth > inst->uDestMaxSize && inst->uDestMaxSize != 0) {
            inst->uStatus = 7211; //超出目标地址最大长度。
        }
        else {
            memcpy((char *)(inst->psDestStr + inst->uOffset),(char *)inst->psSrcStr,inst->uSrcActualLenth);
            inst->uOffset = inst->uOffset + inst->uSrcActualLenth;
        }
    }
    
    /*----------------- 输出字符串整体长度---------------*/
    inst->uStrSize = inst->uOffset;
}
