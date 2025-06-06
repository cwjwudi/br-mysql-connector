/*!
	* @file        FB_GetPvEntireName.c
	* @brief       调用此函数，可获得变量的完整名称，并反馈剩余的资源
	* @date        创建于：2021.03.15；最后修改日期：2021.03.16
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.16    V1.00.1   YuanZhiyi
 *         (new)     初始版本
 ******************************************************************************
*/


#include <bur/plctypes.h>
#include <string.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
#ifdef __cplusplus
	};
#endif

void FB_GetPvEntireName(struct FB_GetPvEntireName* inst)
{
    //判断是否变量名有变化 任务名与变量名作为输入源
    if ((memcmp((char *)inst->sName,(char *)inst->sNameTmp,sizeof(inst->sName)) != 0) ||  
        (memcmp((char *)inst->sModuleName,(char *)inst->sModuleNameTmp,sizeof(inst->sModuleName)) != 0)) {
        memcpy((char *)inst->sNameTmp,(char *)inst->sName,sizeof(inst->sName));
        memcpy((char *)inst->sModuleNameTmp,(char *)inst->sModuleName,sizeof(inst->sModuleName));
        
        inst->uCurrentIndex = 0;
        inst->uTotalNumber = 0;
        inst->bInTraversal = 0;
        inst->uStatus = 0;
        inst->bEnd = 0;
        memset((char *)inst->sEntirePvName,0,sizeof(inst->sEntirePvName));
        memset((char *)inst->sCompleteName,0,sizeof(inst->sCompleteName));
        memset((char *)inst->sCompleteNameTmp,0,sizeof(inst->sCompleteNameTmp));
    }
    
    //判断整体变量名是否有变化，
    if (memcmp((char *)inst->sCompleteName,(char *)inst->sCompleteNameTmp,sizeof(inst->sCompleteNameTmp)) != 0) {
	    memcpy((char *)inst->sCompleteNameTmp,(char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        
        inst->uCurrentIndex = 0;
        inst->uTotalNumber = 0;
        inst->bInTraversal = 0;
        inst->uStatus = 0;
        inst->bEnd = 0;
        memset((char *)inst->sEntirePvName,0,sizeof(inst->sEntirePvName));
        memset((char *)inst->sModuleName,0,sizeof(inst->sModuleName));
        memset((char *)inst->sModuleNameTmp,0,sizeof(inst->sModuleNameTmp));
        memset((char *)inst->sName,0,sizeof(inst->sName));
        memset((char *)inst->sNameTmp,0,sizeof(inst->sNameTmp));    
    }  
    
    if (inst->bInTraversal == 0) { //仅在有变化时读取信息,此处默认为第一次对变量进行遍历
        //读取变量名信息
        if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) {
            memcpy((char *)inst->FB_GetPvInfo_0.sCompleteName,(char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        }else {
            memcpy((char *)inst->FB_GetPvInfo_0.sAppModuleName,(char *)inst->sModuleName,sizeof(inst->sModuleName));
            memcpy((char *)inst->FB_GetPvInfo_0.sName,(char *)inst->sName,sizeof(inst->sName));
        }
        inst->uTotalNumber = 0;
        inst->uCurrentIndex = 0;     
        FB_GetPvInfo(&inst->FB_GetPvInfo_0); //异常情况判断
        if ((inst->FB_GetPvInfo_0.status != 0) && (inst->FB_GetPvInfo_0.status != 7001)) {
            inst->uStatus = inst->FB_GetPvInfo_0.status;
            return;
        }else { //拼接数据判断
            if (inst->FB_GetPvInfo_0.uDataType == 0 || inst->FB_GetPvInfo_0.uDataType == 15 ) {
                if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) {
                    memcpy((char *)inst->FB_GetStruPvMemName_0.sCompleteName,(char *)inst->sCompleteName,sizeof(inst->sCompleteName));
                }else {
                    memcpy((char *)inst->FB_GetStruPvMemName_0.sModuleName,(char *)inst->sModuleName,sizeof(inst->sModuleName));
                    memcpy((char *)inst->FB_GetStruPvMemName_0.sName,(char *)inst->sName,sizeof(inst->sName));
                }
                FB_GetStruPvMemName(&inst->FB_GetStruPvMemName_0);
                if (inst->FB_GetStruPvMemName_0.uiStatus != 0) {
                    inst->uStatus = inst->FB_GetStruPvMemName_0.uiStatus;
                    return;
                }else {
                    memcpy((char *)inst->sEntirePvName,(char *)inst->FB_GetPvInfo_0.sPvName,sizeof(inst->FB_GetPvInfo_0.sPvName));
                    Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)".");
                    Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)inst->FB_GetStruPvMemName_0.sArrMemName[inst->uCurrentIndex]);
                    inst->uTotalNumber = inst->FB_GetStruPvMemName_0.uiMemNum;
                    if (inst->uCurrentIndex < inst->uTotalNumber) {
                        inst->uCurrentIndex++;
                    }
                    if (inst->FB_GetStruPvMemName_0.uiMemNum > 1)
                    {
                        inst->uStatus = 65535;
                        inst->bInTraversal = 1;
                    }
                } 
            }else if(inst->FB_GetPvInfo_0.uiDimension > 1) {
                inst->uTotalNumber = inst->FB_GetPvInfo_0.uiDimension;
                memcpy((char *)inst->sEntirePvName,(char *)inst->FB_GetPvInfo_0.sPvName,sizeof(inst->FB_GetPvInfo_0.sPvName));
                Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)"[");
                inst->FB_Udint2Str_0.udInput = inst->uCurrentIndex;
                FB_Udint2Str(&inst->FB_Udint2Str_0);
                Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)inst->FB_Udint2Str_0.strOut);
                Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)"]");
                if (inst->uCurrentIndex < inst->uTotalNumber) {
                    inst->uCurrentIndex++;
                }        
                inst->uStatus = 65535;
                inst->bInTraversal = 1;
            }else {
                memcpy((char *)inst->sEntirePvName,(char *)inst->FB_GetPvInfo_0.sPvName,sizeof(inst->FB_GetPvInfo_0.sPvName));
                inst->bEnd = 1;
            }
        } 
        //当在遍历过程中
    } else if (inst->uCurrentIndex != 0 && inst->uTotalNumber != 0 && inst->bInTraversal == 1) {
        if ((inst->FB_GetPvInfo_0.uDataType == 0) || (inst->FB_GetPvInfo_0.uDataType == 15)) { //对结构信息的处理
            memcpy((char *)inst->sEntirePvName,(char *)inst->FB_GetPvInfo_0.sPvName,sizeof(inst->FB_GetPvInfo_0.sPvName));
            Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)".");
            Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)inst->FB_GetStruPvMemName_0.sArrMemName[inst->uCurrentIndex]);
            if (inst->uCurrentIndex < inst->uTotalNumber) {
                inst->uCurrentIndex++;
            }
            if (inst->uCurrentIndex >= inst->uTotalNumber) {
                inst->bInTraversal = 0;
                inst->uStatus = 0;
            }
        }else { //对数组类型数据进行处理
            memcpy((char *)inst->sEntirePvName,(char *)inst->FB_GetPvInfo_0.sPvName,sizeof(inst->FB_GetPvInfo_0.sPvName));
            Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)"[");
            inst->FB_Udint2Str_0.udInput = inst->uCurrentIndex;
            FB_Udint2Str(&inst->FB_Udint2Str_0);
            Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)inst->FB_Udint2Str_0.strOut);
            Strcats((UDINT)inst->sEntirePvName,sizeof(inst->sEntirePvName),(UDINT)"]");
            if (inst->uCurrentIndex < inst->uTotalNumber) {
                inst->uCurrentIndex++;
            }
            if (inst->uCurrentIndex >= inst->uTotalNumber) {
                inst->bInTraversal = 0;
                inst->uStatus = 0;
            }
        }
    }
}
