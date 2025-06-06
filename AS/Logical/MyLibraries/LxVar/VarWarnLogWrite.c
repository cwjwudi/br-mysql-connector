/*!
* @file        VarWarnLogWrite.c
 * @brief      调用此函数，输入故障码（UINT类型），输入字符串信息，即可在Looger中的System中生成Logger记录。
 * @date       创建于：2019.08.13；最后修改日期：2020.11.04
 * @version    V1.00.1
 * @author     YuanZhiyi
 * @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2020.11.04    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
#include "LxVar.h"
#include <sys_lib.h>
#ifdef __cplusplus
	};
#endif

unsigned short VarWarnLogWrite(UINT uNum,UDINT psErrorInfo)
{
    if (psErrorInfo == 0)
    {
        ERRxwarning(uNum, 0, (char *)"VarLogWrite Input psErrorInfo is NULL");
    }else
    {
        ERRxwarning(uNum, 0, (char *)psErrorInfo);	
    }
    return 0;
}
