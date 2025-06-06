/*!
	* @file       DataJoint.c
	* @brief      ���ݵ�ַ��Ϣ��ʵ������ƴ��
	* @date       �����ڣ�2018.02.19������޸����ڣ�2018.02.19
	* @version    V 1.00.1
	* @author     YuanZhiyi
	* @copyright  B&R
*/
/*! History
 *****************************************************************************
 *     2018.02.19    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
 ******************************************************************************
*/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <string.h>
#ifdef __cplusplus
	};
#endif

GetPvInfoUser_typ *pStruPvInfo; 

unsigned short DataJoint(struct DataJointUser_typ* DataIn)
{
	//һ���������ھ���Ҫȫ�������������
	//STEP 0 ���|��ʼ��
	memset((char *)DataIn->sCurrentName,0,sizeof(DataIn->sCurrentName));
	memset((char *)DataIn->sCurrentModName,0,sizeof(DataIn->sCurrentModName));
	memset((char *)DataIn->sErrLogMessage,0,sizeof(DataIn->sErrLogMessage));
	DataIn->udCurrentOffset = 0;
	DataIn->udDataIndex = 0;
	//STEP 1 ��������ָ���Ƿ�����
	if (DataIn->pBuffer == 0 || DataIn->pSrcPvInfo == 0){
		DataIn->status = 7002;
		return 7002; //7002:DataJoint���յ�ָ��ΪNULL
	}
	//STEP 2 ����ѭ�����д���
	for (DataIn->udDataIndex = 0; DataIn->udDataIndex < DataIn->udSrcPvInfoNum; DataIn->udDataIndex++){
		//STEP 2.1 ��������׼�� ��¼��ǰ��Ϣ
		pStruPvInfo = (GetPvInfoUser_typ *)(DataIn->pSrcPvInfo + DataIn->udDataIndex * sizeof(GetPvInfoUser_typ));
		memcpy((char *)DataIn->sCurrentName,(char *)pStruPvInfo->sName,sizeof(pStruPvInfo->sName));
		memcpy((char *)DataIn->sCurrentModName,(char *)pStruPvInfo->sModuleName,sizeof(pStruPvInfo->sModuleName));
		//STEP 2.2 ���pStruPvInfo����Ϣ�Ƿ�������
		if (pStruPvInfo->udPvAddr == 0 || pStruPvInfo->udLenth == 0){
			//STEP 2.2.1 �������쳣ʱ���򽫿����ĵط�����������sErrLogMessage�������ҵ�����㡣
			strcpy((char *)DataIn->sErrLogMessage,(char *)"DataJointY::PV NOT FOUND:");//sErrLogMessage�ܳ��Ȳ��ܳ���160�ֽڡ�
			strcat((char *)DataIn->sErrLogMessage,(char *)pStruPvInfo->sName);
			DataIn->status = 7003;
			return 7003;//7003:����DataJoint��SrcPvInfo���ݶ�ʧ�������������Ϊ����ġ�
		}
		//STEP 2.3 ����Buffer�߽��жϣ��Ƿ񳬽硣
		if (DataIn->udCurrentOffset + pStruPvInfo->udLenth > DataIn->udBufferMaxLen ){
			DataIn->status = 7004;
			return 7004;//7004:DataJointƴ�������������趨��Buffer��
		}
		//STEP 2.4 �������ݸ��ƣ��洢��Ϣ
		memcpy((char *)(DataIn->pBuffer + DataIn->udCurrentOffset),(char *)pStruPvInfo->udPvAddr,(UDINT)pStruPvInfo->udLenth);
		DataIn->udCurrentOffset += pStruPvInfo->udLenth;	
		//break;		 
	}
	DataIn->status = 0;
    return 0;
}
