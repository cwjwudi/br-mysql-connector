/*!
	* @file       FB_GetPvInfo.c
	* @brief      调用此函数，可获得任何变量的地址、数据类型、数据长度等信息。
	* @date       创建于：2018.02.19；最后修改日期：2021.06.03
	* @version    V 1.00.5
	* @author     YuanZhiyi
	* @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2018.02.19    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 *     2021.03.05    V1.00.2   YuanZhiyi
 *         (fix)     调整代码的_LOCAL写法，避免在部分AS中编译异常问题。
 *     2021.03.15    V1.00.3   YuanZhiyi
 *         (fix)     调整uiDimension变量方向为VAR_OUTPUT,并修正此参数的数据长度。
 *     2021.03.16    V1.00.4   YuanZhiyi
 *         (new)     增加sCompleteName，满足后续输出内容直接获取地址。
 *     2021.06.03    V1.00.5   YuanZhiyi
 *         (fix)     修正当数据为枚举类型或结构体时，无法获得地址的设计
 ******************************************************************************
*/


#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <sys_lib.h>
	#include <string.h>
#ifdef __cplusplus
	};
#endif

void FB_GetPvInfo(struct FB_GetPvInfo* inst)
{
	//注意事项：	不进行步骤跳转，一个任务周期内即完成所有任务
	//STEP 0: 初始化 
	
	memcpy((char *)inst->sDelimiter, (char *)":",1);
	
	memset((char *)&inst->udPvAddr, 0, 4);
	memset((char *)inst->sDataType, 0, 19);
	memset((char *)&inst->udLenth, 0, 4);
	memset((char *)&inst->udData_typ, 0, 4);
	memset((char *)&inst->udData_len, 0, 4);
	memset((char *)&inst->uiDimension, 0, 1);

	//STEP 1: 判断输入数据是否正常
	memset((char *)inst->sPvName, 0, sizeof(inst->sPvName)); //清空缓存
    if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) { //判断是否启用sCompleteName:使用sCompleteName
        memcpy((char *)inst->sPvName, (char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        memset((char *)inst->sAppModuleName,0,sizeof(inst->sAppModuleName));
        memset((char *)inst->sName,0,sizeof(inst->sName));
    }else { //使用sAppModuleName与sName
	    if (memcmp((char *)inst->sAppModuleName,(char *)"",1) == 0){
		    strcat((char *)inst->sPvName,(char *)inst->sName); 
	    }else{
		    strcat((char *)inst->sPvName,(char *)inst->sAppModuleName);
		    strcat((char *)inst->sPvName,(char *)inst->sDelimiter);
		    strcat((char *)inst->sPvName,(char *)inst->sName); 
	    }
    }
	//STEP 2: 进行PV_ninfo，判断数据类型，是否返回错误数据
	inst->status = PV_ninfo((char *)inst->sPvName, (UDINT *)&inst->udData_typ, (UDINT *)&inst->udData_len, (UINT *)&inst->uiDimension);
	//因上一语句处理完，则inst->sPvName的值会被清空，因而做了以下操作
	memset((char *)inst->sPvName, 0, sizeof(inst->sPvName)); //清空缓存
    if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) { //判断是否启用sCompleteName:使用sCompleteName
        memcpy((char *)inst->sPvName, (char *)inst->sCompleteName,sizeof(inst->sCompleteName));
    }else { //任务名 变量名 分开输入   
        if (memcmp((char *)inst->sAppModuleName,(char *)"",1) == 0){
            strcat((char *)inst->sPvName,(char *)inst->sName); 
        }else{
            strcat((char *)inst->sPvName,(char *)inst->sAppModuleName);
            memcpy((char *)inst->sDelimiter, (char *)":",1);
            strcat((char *)inst->sPvName,(char *)inst->sDelimiter);
            strcat((char *)inst->sPvName,(char *)inst->sName); 
        }
    }
	if (inst->status == 0){
    inst->uDataType = inst->udData_typ; 
		switch (inst->udData_typ){
			case 0:
				strcat((char *)inst->sDataType,(char *)"Derived data types");
				inst->status = 7001;//读取的变量为枚举类型
				break;
			case 1:
				strcat((char *)inst->sDataType,(char *)"BOOL");
				break;
			case 2:
				strcat((char *)inst->sDataType,(char *)"SINT");
				break;
			case 3:
				strcat((char *)inst->sDataType,(char *)"INT");
				break;
			case 4:
				strcat((char *)inst->sDataType,(char *)"DINT");
				break;
			case 5:
				strcat((char *)inst->sDataType,(char *)"USINT");
				break;
			case 6:
				strcat((char *)inst->sDataType,(char *)"UINT");
				break;
			case 7:
				strcat((char *)inst->sDataType,(char *)"UDINT");
				break;
			case 8:
				strcat((char *)inst->sDataType,(char *)"REAL");
				break;
			case 9:
				strcat((char *)inst->sDataType,(char *)"STRING");
				break;
			case 10:
				strcat((char *)inst->sDataType,(char *)"ULINT");
				break;
			case 11:
				strcat((char *)inst->sDataType,(char *)"DATE_AND_TIME");
				break;
			case 12:
				strcat((char *)inst->sDataType,(char *)"TIME");
				break;
			case 13:
				strcat((char *)inst->sDataType,(char *)"DATE");
				break;
			case 14:
				strcat((char *)inst->sDataType,(char *)"LREAL");
				break;
			case 15:
				strcat((char *)inst->sDataType,(char *)"Derived data types");
				inst->status = 7001;//读取的变量为枚举类型
				break;
			case 16:
				strcat((char *)inst->sDataType,(char *)"TIME_OF_DAY");
				break;
			case 17:
				strcat((char *)inst->sDataType,(char *)"BYTE");
				break;
			case 18:
				strcat((char *)inst->sDataType,(char *)"WORD");
				break;
			case 19:
				strcat((char *)inst->sDataType,(char *)"DWORD");
				break;
			case 20:
				strcat((char *)inst->sDataType,(char *)"LWORD");
				break;
			case 21:
				strcat((char *)inst->sDataType,(char *)"WSTRING");
				break;
			case 23:
				strcat((char *)inst->sDataType,(char *)"LINT");
				break;
			default:
				break;
		}
	}
	//STEP3 : 上面都通过，则进行PV_xgetadr，获取地址数据
	if (inst->status == 0 || inst->status == 7001){
		inst->status = PV_xgetadr(inst->sPvName, &inst->udPvAddr, &inst->udLenth);
	}
}
