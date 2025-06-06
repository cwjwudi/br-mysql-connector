/*!
* @file         LxVar/VarServLogWrite.c
  * @brief      调用此函数，输入故障码（UINT类型），输入字符串信息，即可在Looger中的System中生成Logger记录,PLC会直接进入SERV。
  * @date       创建于：2021.03.18；最后修改日期：2021.03.18
  * @version    V1.00.1
  * @author     YuanZhiyi
  * @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.18    V1.00.1   YuanZhiyi
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

plcbit VarServLogWrite(unsigned short uErrorNum, unsigned long psErrorInfo)
{
    if (psErrorInfo == 0)
    {
        ERRxwarning(uErrorNum, 0, (char *)"VarLogWrite Input psErrorInfo is NULL");
    }else
    {
        ERRxfatal(uErrorNum, 0, (char *)psErrorInfo);	
    }
    return 0;
}
