/*!
	* @file        FB_GetPvEntireName.c
	* @brief       ���ô˺������ɻ�ñ������������ƣ�������ʣ�����Դ
	* @date        �����ڣ�2021.03.15������޸����ڣ�2021.03.16
	* @version     V 1.00.1
	* @author      YuanZhiyi
	* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.16    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
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
    //�ж��Ƿ�������б仯 ���������������Ϊ����Դ
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
    
    //�ж�����������Ƿ��б仯��
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
    
    if (inst->bInTraversal == 0) { //�����б仯ʱ��ȡ��Ϣ,�˴�Ĭ��Ϊ��һ�ζԱ������б���
        //��ȡ��������Ϣ
        if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) {
            memcpy((char *)inst->FB_GetPvInfo_0.sCompleteName,(char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        }else {
            memcpy((char *)inst->FB_GetPvInfo_0.sAppModuleName,(char *)inst->sModuleName,sizeof(inst->sModuleName));
            memcpy((char *)inst->FB_GetPvInfo_0.sName,(char *)inst->sName,sizeof(inst->sName));
        }
        inst->uTotalNumber = 0;
        inst->uCurrentIndex = 0;     
        FB_GetPvInfo(&inst->FB_GetPvInfo_0); //�쳣����ж�
        if ((inst->FB_GetPvInfo_0.status != 0) && (inst->FB_GetPvInfo_0.status != 7001)) {
            inst->uStatus = inst->FB_GetPvInfo_0.status;
            return;
        }else { //ƴ�������ж�
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
        //���ڱ���������
    } else if (inst->uCurrentIndex != 0 && inst->uTotalNumber != 0 && inst->bInTraversal == 1) {
        if ((inst->FB_GetPvInfo_0.uDataType == 0) || (inst->FB_GetPvInfo_0.uDataType == 15)) { //�Խṹ��Ϣ�Ĵ���
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
        }else { //�������������ݽ��д���
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
