/*!
	* @file      Strlens.c
	* @brief     防止内存溢出的安全型strlen
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
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "LxVar.h"
	#include <string.h>
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
unsigned long Strlens(unsigned long pStr, unsigned long udMaxSize)
{
	unsigned long udStrsz = 0;
	//检查数据入口
	if (pStr == 0 || udMaxSize ==  0)
	{
		//WarnLogWriteY(7214,(UDINT *)&"strnlenY input parameter Error");
		return 7214;//strnlenY input parameter Error;
	}
	
	//strnlen操作
	udStrsz = strnlen((char *)pStr,udMaxSize);

	return udStrsz;
}
