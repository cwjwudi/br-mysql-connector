/*!
* @file        BrRand/FB_RandString.c
* @brief       ���ô˺�������ʵ��ָ����Χ���ַ���������ɴ���,ͬ������
* @date        �����ڣ�2018.01.16 ����޸����ڣ�2021.02.07
* @version     V 1.00.1
* @author      YuanZhiyi
* @copyright   B&R
*/
/*! History
 *****************************************************************************
 *     2021.02.07    V1.00.1   YuanZhiyi
 *         (new)     ��ɰ汾
 ******************************************************************************
*/
/*! Descripiton
 *****************************************************************************
 *     ʹ���÷�: 
            FB_RandString_0.pString  := ADR(sString);
            FB_RandString_0.uStrLen := SIZEOF(sString);
            FB_RandString_0();
 ******************************************************************************
*/


#include <bur/plctypes.h>
#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "BrRand.h"
#ifdef __cplusplus
	};
#endif

static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";

void FB_RandString(struct FB_RandString* inst)
{
    unsigned long uMaxStrNum = 0;
    int i = 0;
    
    if (inst->uStrLen < sizeof(inst->sStrOut) - 1){
        uMaxStrNum = sizeof(inst->sStrOut) - 1;
    }else{
        uMaxStrNum = inst->uStrLen - 1;
    }
    
    for (i = 0; i < uMaxStrNum; i++){
        int uKey = rand() % (int)(sizeof(charset) - 1); 
        if (i < sizeof(inst->sStrOut) - 1) {
            if (inst->pString != 0 && inst->uStrLen != 0) {
                memcpy((char *)inst->pString + i,&charset[uKey],1);
            }
            memcpy(inst->sStrOut + i,&charset[uKey],1);
        }else{
            if (inst->pString != 0 && inst->uStrLen != 0) {
                memcpy((char *)inst->pString + i,&charset[uKey],1);
            }
        }     
    }
    memset(inst->sStrOut + sizeof(inst->sStrOut),0,1);
    if (inst->pString != 0 && inst->uStrLen != 0) {
        memset((char *)inst->pString + uMaxStrNum,0,1);
    }
}
