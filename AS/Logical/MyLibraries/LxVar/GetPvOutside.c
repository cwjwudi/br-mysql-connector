/*!
	* @file       GetPvOutside.c
	* @brief      ��������Ϣ��ȡ��������ⲿ���ݽṹ��
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

FB_GetPvInfo_typ GetPvInfoY_0;                   
                                        
unsigned short GetPvOutside(struct GetPvInfoUser_typ* dataIn)
{
	
	//�Ƿ�����dataIn������У�飿
	//������ݲ�������Ӧ�û��ڱ���ʱ�ͱ�������Ҫȷ�������Ƿ�����
	memcpy((char *)&GetPvInfoY_0.sAppModuleName,(char *)dataIn->sModuleName,sizeof(dataIn->sModuleName));
	memcpy((char *)GetPvInfoY_0.sName,(char *)dataIn->sName,sizeof(dataIn->sName));
	FB_GetPvInfo(&GetPvInfoY_0);
	if(GetPvInfoY_0.status == 0){
		memcpy((char *)dataIn->sDataType,(char *)GetPvInfoY_0.sDataType,19);
		dataIn->udLenth = GetPvInfoY_0.udLenth;
		dataIn->udPvAddr = GetPvInfoY_0.udPvAddr;
	}else{
		memset((char *)dataIn->sDataType,0,19);
		dataIn->udLenth = 0;
		dataIn->udPvAddr = 0;	
	}
	return GetPvInfoY_0.status;
}
