/*!
	* @file      Strcpys.c
	* @brief     防止内存溢出的安全型strcpy
	* @date      创建于：2021.03.12；最后修改日期：2021.03.12
	* @version   V 1.00.1
	* @author    YuanZhiyi
	* @copyright B&R
*/
/*! History
 *****************************************************************************
 *     2021.03.12    V1.00.1   YuanZhiyi
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
/* TODO: Add your comment here */
//e.g. in ST : strcpys(ADR('abc'),SIZEOF('abcXXXXXXX'),ADR('efg'),SIZEOF('efg'))
unsigned long Strcpys(unsigned long pDest, unsigned long udDestsz, unsigned long pSrc)
{
	unsigned long udStrsz = 0;
	if (pDest == 0 || udDestsz == 0 || pSrc == 0)
	{
		//WarnLogWriteY(7211,(UDINT)"strcpysY Input parameters Error");
		return 7211;//strcpysY Input parameters Error	
	}
	
	udStrsz = strlcpy((char *)pDest,(char *)pSrc,udDestsz);
	return udStrsz;
}
