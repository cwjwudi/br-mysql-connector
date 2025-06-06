/*!
	* @file       LxVar/ReturnPvAddr.c
	* @brief      调用此函数，可获得变量地址信息，如果找不到，则进入SERV。
	* @date       创建于：2021.03.18；最后修改日期：2021.03.18
	* @version    V 1.00.1
	* @author     YuanZhiyi
	* @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.18    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/
/*! USE CASE

    .Var文件中申明变量为Reference变量
    *************************************
    VAR
    	Test0 : REFERENCE TO UDINT;
    END_VAR
    *************************************
    
    在.st代码中通过以下写法实现访问任意变量
    *************************************
    Test0 ACCESS ReturnPvAddr(ADR('gTest0'));
    *************************************

    如果变量找不到，则PLC进入SERV，并在Logger中记录找不到的变量名

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
