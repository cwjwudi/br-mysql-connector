
#include <bur/plctypes.h>
#include "deque.h"
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

_LOCAL Deque sqlDeque1;
_LOCAL DequeElement sqlElement1;

void _INIT ProgramInit(void)
{
	InsInter = &gMySQLInserter._Internal;
	InsSts = &gMySQLInserter.Status;
	InsExtCom = &gMySQLInserter.ExternalCom;
	InsCmd = &gMySQLInserter.Command;
	InsCfg = &gMySQLInserter.Config;
}

void _CYCLIC ProgramCyclic(void)
{
	if (0 == InsCmd->Enable) {
		return;
	}
	
	if (1 == InsCmd->Reset && 0 == oldReset ) {
		step = 0;
	}
	
	switch(step) {
		case 0:
			// 初始化Deque
			initDeque(&sqlDeque1);
			memset(tempStr, 0, sizeof(tempStr));
			step = 1;
			break;
		case 1:
			// 等待任务
			if(sqlDeque1.size > 0) {
				popDeque(&sqlDeque1, &sqlElement1);
				memcpy(InsExtCom->StrCmd[INTERFACE_IDX], sqlElement1.strBuffer, CMD_STR_SIZE);
				oldCounter = InsExtCom->Counter[INTERFACE_IDX];
				step = 2;
			}
			break;
		case 2:
			// 处理任务
			ton_0.IN = 1;
			ton_0.PT = 2000; // 2000ms
			// 超时未回复处理
			if (ton_0.Q) {
				ton_0.IN = 0;
				if (memcmp(InsExtCom->StrCmd[INTERFACE_IDX], tempStr, sizeof(tempStr)) != 0) {
					memcpy(sqlElement1.strBuffer, InsExtCom->StrCmd[INTERFACE_IDX], CMD_STR_SIZE);
					pushDeque(&sqlDeque1, &sqlElement1);
					step = 1;
				} else {
					step = 11;
				}

			}
			
			if (InsExtCom->Counter[INTERFACE_IDX] != oldCounter) {
				// 任务处理完成
				ton_0.IN = 0;
				step = 1;
			} 
			break;
		case 3:
			// 任务完成，返回空闲
			step = 1;
			break;

		case 11:
			// 处理错误
			// 这里可以添加错误处理逻辑
			InsSts->Task[u8idx].Err = 1;
			strcpy(InsSts->Task[u8idx].ErrMsg, "Fault Error: Can not execute create cmd.");
			break;
		default:
			step = 0;
			break;
	}
	
	// 循环检查，如果数据变化，就把数据压入Deque
	for(u8idx = 0; u8idx < TASK_SIZE; u8idx++) {
		if(memcmp(oldTaskCmdStr[u8idx], InsInter->TaskCmdStr[u8idx], CMD_STR_SIZE) != 0) {
			memcpy(oldTaskCmdStr[u8idx], InsInter->TaskCmdStr[u8idx], CMD_STR_SIZE);
			
			memset(sqlElement1.strBuffer, 0, CMD_STR_SIZE);
			memcpy(sqlElement1.strBuffer, InsInter->TaskCmdStr[u8idx], CMD_STR_SIZE);
			
			pushDeque(&sqlDeque1, &sqlElement1);
		}
	}
	
	

	
	// connect status
	ton_con.IN = 1;
	ton_con.PT = InsCfg->LostTimeMs;
	
	if (ton_con.Q) {
		ton_con.IN = 0;
		if (InsExtCom->HeartBeat[INTERFACE_IDX] != oldHeartBeat) {
			InsSts->Connected = 1;
		}else {
			InsSts->Connected = 0;
		}
		oldHeartBeat = InsExtCom->HeartBeat[INTERFACE_IDX];
	}
	
	InsSts->BufferNum[INTERFACE_IDX] = sqlDeque1.size;
	
	oldReset = InsCmd->Reset;
	
	// FB CALL
	TON(&ton_0);
	TON(&ton_con);

}

void _EXIT ProgramExit(void)
{

}

