/*!
	* @file       LxVar/ReturnPvAddr.c
	* @brief      ���ô˺������ɻ�ñ�����ַ��Ϣ������Ҳ����������SERV��
	* @date       �����ڣ�2021.03.18������޸����ڣ�2021.03.18
	* @version    V 1.00.1
	* @author     YuanZhiyi
	* @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.18    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
 ******************************************************************************
*/
/*! USE CASE

    .Var�ļ�����������ΪReference����
    *************************************
    VAR
    	Test0 : REFERENCE TO UDINT;
    END_VAR
    *************************************
    
    ��.st������ͨ������д��ʵ�ַ����������
    *************************************
    Test0 ACCESS ReturnPvAddr(ADR('gTest0'));
    *************************************

    ��������Ҳ�������PLC����SERV������Logger�м�¼�Ҳ����ı�����

 */

#include <bur/plctypes.h>
#include <sys_lib.h>
#include <string.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

unsigned long ReturnPvAddr(unsigned long psVarName)
{
    UDINT uPvAddr;
    UDINT uLength;
    STRING sErrorMsg[160];
    
    PV_xgetadr((char *)psVarName, (UDINT *)&uPvAddr, (UDINT *)&uLength);
    
    if (uPvAddr == 0) {
        memset((char *)sErrorMsg,0,sizeof(sErrorMsg));
        Strcpys((UDINT)sErrorMsg,sizeof(sErrorMsg),(UDINT)psVarName);
        Strcats((UDINT)sErrorMsg,sizeof(sErrorMsg),(UDINT)" Not Found");
        VarServLogWrite(55520,(UDINT)sErrorMsg);
    }
    return uPvAddr; 
}
