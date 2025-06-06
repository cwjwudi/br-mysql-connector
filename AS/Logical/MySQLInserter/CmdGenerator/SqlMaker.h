#ifndef SQLMAKER_H
#define SQLMAKER_H

#include <bur/plctypes.h>
#include <string.h>
#include <LxVar.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void MakeInsertSql(STRING* sqlBuffer, UDINT bufferSize, TaskSetting_typ* taskSetting, TaskStatus_typ* taskStatus);
void MakeCreateTableSql(STRING* sqlBuffer, UDINT bufferSize, TaskSetting_typ* taskSetting);
UDINT CreateMySQLDateTimeStamp(STRING *pOutputString);


#endif // SQLMAKER_H