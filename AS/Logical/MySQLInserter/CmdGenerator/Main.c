
#include <bur/plctypes.h>
#include "SqlMaker.h"
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	// Insert code here 
	InsCfg = &gMySQLInserter.Config;
	InsSts = &gMySQLInserter.Status;
	InsInter = &gMySQLInserter._Internal;
	InsInput = &gMySQLInserter.Input;
	InsCmd = &gMySQLInserter.Command;
	firstScan = 1;
}

void _CYCLIC ProgramCyclic(void)
{
	// Insert code here 
	if (0 == InsCmd->Enable) {
		return;
	}
	
	if (InsCmd->Reset) {
		firstScan = 1;
	}
	
	/* 获取线程信息 */
	RTInfo_0.enable = 1;
	RTInfo(&RTInfo_0);
	
	if (firstScan) {
		for (u8idx = 0; u8idx < TASK_SIZE ; u8idx++) {
			MakeCreateTableSql(strBuffer[u8idx], CMD_STR_SIZE, &InsCfg->TaskSetting[u8idx]);
			brsmemcpy((UDINT)InsInter->TaskCmdStr[u8idx], (UDINT)strBuffer[u8idx], CMD_STR_SIZE);
			InsSts->Task[u8idx].CacheCount = 0; // Cache清0
		}
		firstScan = 0;
		return;
	}
	
	
	for (u8idx = 0; u8idx < TASK_SIZE ; u8idx++) {
		// 定时触发模式
		if (1 == InsCfg->TaskSetting[u8idx].TrigMode) {
			if (InsCfg->TaskSetting[u8idx].IntervalTimeMs * 1000 > RTInfo_0.cycle_time && RTInfo_0.cycle_time != 0) {
				accTimeUs[u8idx] = accTimeUs[u8idx] + RTInfo_0.cycle_time;
				if (accTimeUs[u8idx] >= InsCfg->TaskSetting[u8idx].IntervalTimeMs * 1000){		
					// 计时到，采集一次数据
					MakeInsertSql(strBuffer[u8idx], CMD_STR_SIZE, &InsCfg->TaskSetting[u8idx], &InsSts->Task[u8idx]);
					accTimeUs[u8idx] = 0;
				}
			} else {
				InsSts->Task[u8idx].Err = 1;
				strcpy(InsSts->Task[u8idx].ErrMsg, "Sampling interval is less than task cycle time.");
			}
		// 手动触发模式
		}else if (0 == InsCfg->TaskSetting[u8idx].TrigMode) {
			if (1 == InsInput->TaskTrig[u8idx]) {
				InsInput->TaskTrig[u8idx] = 0;
				MakeInsertSql(strBuffer[u8idx], CMD_STR_SIZE, &InsCfg->TaskSetting[u8idx], &InsSts->Task[u8idx]);
			}
		}
		// 到达cache_size大小，自动封包
		if (0 == InsSts->Task[u8idx].CacheCount) {
			// memset((UDINT)InsInter->TaskCmdStr[u8idx], 0, CMD_STR_SIZE);
			brsmemcpy((UDINT)InsInter->TaskCmdStr[u8idx], (UDINT)strBuffer[u8idx], CMD_STR_SIZE);
		}
	}
}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}
