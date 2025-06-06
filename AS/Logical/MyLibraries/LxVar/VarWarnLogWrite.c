/*!
* @file        VarWarnLogWrite.c
 * @brief      ���ô˺�������������루UINT���ͣ��������ַ�����Ϣ��������Looger�е�System������Logger��¼��
 * @date       �����ڣ�2019.08.13������޸����ڣ�2020.11.04
 * @version    V1.00.1
 * @author     YuanZhiyi
 * @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2020.11.04    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
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
