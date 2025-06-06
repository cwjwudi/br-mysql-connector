/*!
* @file         LxVar/VarServLogWrite.c
  * @brief      ���ô˺�������������루UINT���ͣ��������ַ�����Ϣ��������Looger�е�System������Logger��¼,PLC��ֱ�ӽ���SERV��
  * @date       �����ڣ�2021.03.18������޸����ڣ�2021.03.18
  * @version    V1.00.1
  * @author     YuanZhiyi
  * @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.18    V1.00.1   YuanZhiyi
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
