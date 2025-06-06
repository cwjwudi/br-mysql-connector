/*!
	* @file       FB_GetPvInfo.c
	* @brief      ���ô˺������ɻ���κα����ĵ�ַ���������͡����ݳ��ȵ���Ϣ��
	* @date       �����ڣ�2018.02.19������޸����ڣ�2021.06.03
	* @version    V 1.00.5
	* @author     YuanZhiyi
	* @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2018.02.19    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
 *     2021.03.05    V1.00.2   YuanZhiyi
 *         (fix)     ���������_LOCALд���������ڲ���AS�б����쳣���⡣
 *     2021.03.15    V1.00.3   YuanZhiyi
 *         (fix)     ����uiDimension��������ΪVAR_OUTPUT,�������˲��������ݳ��ȡ�
 *     2021.03.16    V1.00.4   YuanZhiyi
 *         (new)     ����sCompleteName����������������ֱ�ӻ�ȡ��ַ��
 *     2021.06.03    V1.00.5   YuanZhiyi
 *         (fix)     ����������Ϊö�����ͻ�ṹ��ʱ���޷���õ�ַ�����
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
	//ע�����	�����в�����ת��һ�����������ڼ������������
	//STEP 0: ��ʼ�� 
	
	memcpy((char *)inst->sDelimiter, (char *)":",1);
	
	memset((char *)&inst->udPvAddr, 0, 4);
	memset((char *)inst->sDataType, 0, 19);
	memset((char *)&inst->udLenth, 0, 4);
	memset((char *)&inst->udData_typ, 0, 4);
	memset((char *)&inst->udData_len, 0, 4);
	memset((char *)&inst->uiDimension, 0, 1);

	//STEP 1: �ж����������Ƿ�����
	memset((char *)inst->sPvName, 0, sizeof(inst->sPvName)); //��ջ���
    if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) { //�ж��Ƿ�����sCompleteName:ʹ��sCompleteName
        memcpy((char *)inst->sPvName, (char *)inst->sCompleteName,sizeof(inst->sCompleteName));
        memset((char *)inst->sAppModuleName,0,sizeof(inst->sAppModuleName));
        memset((char *)inst->sName,0,sizeof(inst->sName));
    }else { //ʹ��sAppModuleName��sName
	    if (memcmp((char *)inst->sAppModuleName,(char *)"",1) == 0){
		    strcat((char *)inst->sPvName,(char *)inst->sName); 
	    }else{
		    strcat((char *)inst->sPvName,(char *)inst->sAppModuleName);
		    strcat((char *)inst->sPvName,(char *)inst->sDelimiter);
		    strcat((char *)inst->sPvName,(char *)inst->sName); 
	    }
    }
	//STEP 2: ����PV_ninfo���ж��������ͣ��Ƿ񷵻ش�������
	inst->status = PV_ninfo((char *)inst->sPvName, (UDINT *)&inst->udData_typ, (UDINT *)&inst->udData_len, (UINT *)&inst->uiDimension);
	//����һ��䴦���꣬��inst->sPvName��ֵ�ᱻ��գ�����������²���
	memset((char *)inst->sPvName, 0, sizeof(inst->sPvName)); //��ջ���
    if (memcmp((char *)inst->sCompleteName,(char *)"",1) != 0) { //�ж��Ƿ�����sCompleteName:ʹ��sCompleteName
        memcpy((char *)inst->sPvName, (char *)inst->sCompleteName,sizeof(inst->sCompleteName));
    }else { //������ ������ �ֿ�����   
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
				inst->status = 7001;//��ȡ�ı���Ϊö������
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
				inst->status = 7001;//��ȡ�ı���Ϊö������
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
	//STEP3 : ���涼ͨ���������PV_xgetadr����ȡ��ַ����
	if (inst->status == 0 || inst->status == 7001){
		inst->status = PV_xgetadr(inst->sPvName, &inst->udPvAddr, &inst->udLenth);
	}
}
