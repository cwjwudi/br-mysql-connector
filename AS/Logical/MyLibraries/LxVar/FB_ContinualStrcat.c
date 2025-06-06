/*!
	* @file      FB_ContinualStrcat.c
	* @brief     �ɾ��б�����,��������strcat�����ĺ���,���⸺�ع���
	* @date      �����ڣ�2021.06.03��
	* @author    YuanZhiyi
	* @copyright B&R
*/
/*! History
 *****************************************************************************
 *     2021.06.03    V1.00.1   YuanZhiyi
 *         (new)     ��ʼ�汾
 *     2021.06.09    V1.00.2   YuanZhiyi
 *         (new)     ����uStrSize�������ַ�����������ӿ�
 *     2022.10.31    V1.00.3   YuanZhiyi
 *         (new)     ���ӿ�ѡ��uDestStrOffset����Ŀ���ַ�����ĳһƫ������ʼ�����ַ������
 ******************************************************************************
*/
/*! Attention
 *****************************************************************************
    inst->uSrcMaxSize��inst->uDestMaxSize��Ϊ��ѡ��������룬�򲻽��а�ȫ���
    �˺�����Ŀ��Ϊ�滻strcat���������⵱�ַ����ϴ�ʱ��Strcat����Dest�ĵ�ַ���Ĺ�����Դ
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

void FB_ContinualStrcat(struct FB_ContinualStrcat* inst)
{
    if (inst->bInitial == 1) {
        inst->uOffset = 0;
        inst->bInitial = 0;
        if (inst->uDestMaxSize == 0) {
            /*----------��û������uDestMaxSize������µ�ִ�з�ʽ---------------*/
            inst->uOffset = strlen((char *)inst->psDestStr + inst->uDestStrOffset) + inst->uDestStrOffset;
        }
        else {
            inst->uOffset = Strlens(inst->psDestStr + inst->uDestStrOffset,inst->uDestMaxSize) + inst->uDestStrOffset;
        }  
    }
    
    if (inst->psSrcStr == 0 || inst->psDestStr == 0) {
        inst->uStatus = 7210; //�����ַΪNULL
    }
    else {
        if (inst->uSrcMaxSize == 0) {
            /*----------��û������uSrcMax������µ�ִ�з�ʽ---------------*/
            inst->uSrcActualLenth = strlen((char *)inst->psSrcStr);
        }
        else {
            inst->uSrcActualLenth = Strlens(inst->psSrcStr,inst->uSrcMaxSize);
        }
        
        /*-----------------����Ŀ���ַ�߽��飬��û������uDestMaxSize�����ж�---------------*/
        if (inst->uOffset + inst->uSrcActualLenth > inst->uDestMaxSize && inst->uDestMaxSize != 0) {
            inst->uStatus = 7211; //����Ŀ���ַ��󳤶ȡ�
        }
        else {
            memcpy((char *)(inst->psDestStr + inst->uOffset),(char *)inst->psSrcStr,inst->uSrcActualLenth);
            inst->uOffset = inst->uOffset + inst->uSrcActualLenth;
        }
    }
    
    /*----------------- ����ַ������峤��---------------*/
    inst->uStrSize = inst->uOffset;
}
