#include "SqlMaker.h"


void MakeInsertSql(STRING* sqlBuffer, UDINT bufferSize, TaskSetting_typ* taskSetting, TaskStatus_typ* taskStatus)
{
	// Calc data size
	if (0 == sizeof(taskSetting->DataSetting[0])) {
		return;
	}
	int dataSize = sizeof(taskSetting->DataSetting)/sizeof(taskSetting->DataSetting[0]);
	
	if (dataSize < 1) {
		return;
	}
	
	// Start building the SQL command
	if (0 == taskStatus->CacheCount) {
		memset((char*)sqlBuffer, 0, bufferSize);
		strcat((char*)sqlBuffer, "INSERT INTO ");
		strcat((char*)sqlBuffer, taskSetting->DbName);
		strcat((char*)sqlBuffer, ".");
		strcat((char*)sqlBuffer, taskSetting->TableName);
		strcat((char*)sqlBuffer, " (");
	
		// Add column names
		for (int i = 0; i < dataSize; ++i) {
			if (taskSetting->DataSetting[i].Name[0] == '\0') break;
			if (taskSetting->WritePrimaryKey == 0 && taskSetting->DataSetting[i].PrimaryKey == 1) {
				continue;
			}
			strcat((char*)sqlBuffer, taskSetting->DataSetting[i].Name);
			if (i < (dataSize - 1) && taskSetting->DataSetting[i+1].Name[0] != '\0') {
				strcat((char*)sqlBuffer, ",");
			}
		}
		strcat((char*)sqlBuffer, ") VALUES");	
	}
	
	strcat((char*)sqlBuffer, "(");
	STRING tempStr[32];
	FB_Real2Str_typ FB_Real2Str_0;
	// Add value placeholders
	for (int i = 0; i < dataSize; ++i) {
		if (taskSetting->DataSetting[i].Name[0] == '\0') break;
		if (taskSetting->WritePrimaryKey == 0 && taskSetting->DataSetting[i].PrimaryKey == 1) {
			continue;
		}
		memset((char*)tempStr, 0, sizeof(tempStr));
		// Use '%s' for string, '%d' for int, etc. Here, just use '?' as placeholder
		if (strcmp(taskSetting->DataSetting[i].Type, "FLOAT") == 0) {
			// Type is FLOAT
			if (taskSetting->DataSetting[i].Digital != 0) {
				FB_Real2Str_0.digital = taskSetting->DataSetting[i].Digital;
				FB_Real2Str_0.rNum = *(REAL*)(taskSetting->DataSetting[i].DataAddr);
				FB_Real2Str(&FB_Real2Str_0);
				strcat((char*)tempStr, FB_Real2Str_0.strOut);
			}else {
				ftoa(*(REAL*)taskSetting->DataSetting[i].DataAddr, (UDINT)tempStr);
			}
			strcat((char*)sqlBuffer, (char*)tempStr);
		}	
		else if (strcmp(taskSetting->DataSetting[i].Type, "INT") == 0) {
			// Type is INT
			if (1 == taskSetting->DataSetting[i].MissingCheck) {
				*(DINT*)taskSetting->DataSetting[i].DataAddr += 1;
			}
			itoa(*(DINT*)taskSetting->DataSetting[i].DataAddr, (UDINT)tempStr);
			strcat((char*)sqlBuffer, (char*)tempStr);
		}
		else if (strcmp(taskSetting->DataSetting[i].Type, "VARCHAR") == 0) {
			// Type is VARCHAR
			strcat((char*)sqlBuffer, (char*)taskSetting->DataSetting[i].DataAddr);
		}
		else if (strcmp(taskSetting->DataSetting[i].Type, "DATETIME") == 0) {
			// Type is DATETIME
			if (0 == taskSetting->DataSetting[i].ManualTime) {
				CreateMySQLDateTimeStamp(&tempStr);
				strcat((char*)sqlBuffer, (char*)tempStr);
			}else {
				strcat((char*)sqlBuffer, (char*)taskSetting->DataSetting[i].DataAddr);
			}	
		}
		else {
			// Default case, treat as string
		}
		
		if (i < (dataSize - 1) && taskSetting->DataSetting[i+1].Name[0] != '\0') {
			strcat((char*)sqlBuffer, ",");
		}
	}
	strcat((char*)sqlBuffer, ")");
	if (taskStatus->CacheCount < (taskSetting->CacheSize - 1) && taskSetting->CacheSize != 0) {
		taskStatus->CacheCount = taskStatus->CacheCount + 1;
		strcat((char*)sqlBuffer, ",");
	} else {
		taskStatus->CacheCount = 0;
		strcat((char*)sqlBuffer, ";");
	}
}


void MakeCreateTableSql(STRING* sqlBuffer, UDINT bufferSize, TaskSetting_typ* taskSetting)
{
	if (0 == sizeof(taskSetting->DataSetting[0])) {
		return;
	}
	int dataSize = sizeof(taskSetting->DataSetting)/sizeof(taskSetting->DataSetting[0]);
	if (dataSize < 1) {
		return;
	}

	memset((char*)sqlBuffer, 0, bufferSize);
	strcat((char*)sqlBuffer, "CREATE TABLE IF NOT EXISTS ");
	strcat((char*)sqlBuffer, taskSetting->DbName);
	strcat((char*)sqlBuffer, ".");
	strcat((char*)sqlBuffer, taskSetting->TableName);
	strcat((char*)sqlBuffer, " (");

	for (int i = 0; i < dataSize; ++i) {
		if (taskSetting->DataSetting[i].Name[0] == '\0') {
			if (0 == i) {
				memset((char*)sqlBuffer, 0, bufferSize);
				return;
			}
			break;
		}
		strcat((char*)sqlBuffer, taskSetting->DataSetting[i].Name);
		strcat((char*)sqlBuffer, " ");
		strcat((char*)sqlBuffer, taskSetting->DataSetting[i].Type);

		// VARCHAR length
		if (strcmp(taskSetting->DataSetting[i].Type, "VARCHAR") == 0 && taskSetting->DataSetting[i].DataSize > 0) {
			char lenStr[8] = {0};
			strcat((char*)sqlBuffer, "(");
			itoa(taskSetting->DataSetting[i].DataSize, (UDINT)lenStr);
			strcat((char*)sqlBuffer, lenStr);
			strcat((char*)sqlBuffer, ")");
		}

		// Auto increment
		if (taskSetting->DataSetting[i].AutoIncrement) {
			strcat((char*)sqlBuffer, " AUTO_INCREMENT");
		}

		// NOT NULL
		if (taskSetting->DataSetting[i].NotNull) {
			strcat((char*)sqlBuffer, " NOT NULL");
		}

		// PRIMARY KEY
		if (taskSetting->DataSetting[i].PrimaryKey) {
			strcat((char*)sqlBuffer, " PRIMARY KEY");
		}

		if (i < (dataSize - 1) && taskSetting->DataSetting[i+1].Name[0] != '\0') {
			strcat((char*)sqlBuffer, ",");
		}
	}
	strcat((char*)sqlBuffer, ");");
}

/**
 * @brief 此函数来自 https://github.com/kmontreal-hub/MySQL-Connector-/tree/main。
 *
 * 该函数的具体功能和用法请参考上述项目的相关文档和源代码。
 */
UDINT CreateMySQLDateTimeStamp(STRING *pOutputString)
{
	STRING tempString[10];
	RTCtime_typ	RTC;

	/* Clear output string */
	memset(pOutputString, 0, sizeof(*pOutputString));
	/* Clear temp string */
	memset(&tempString, 0, sizeof(tempString));

	/* Get time */
	RTC_gettime(&RTC);

	/* copy in single quote */
	strcpy(pOutputString, "'");
	/* copy in year */
	itoa(RTC.year, (UDINT)tempString);
	strcat(pOutputString, tempString);
	/* add dash */
	strcat(pOutputString, "-");
	/* copy in month */
	itoa(RTC.month, (UDINT)tempString);
	strcat(pOutputString, tempString);
	/* add dash */
	strcat(pOutputString, "-");
	/* copy in day */
	itoa(RTC.day, (UDINT)tempString);
	strcat(pOutputString, tempString);	

	/* add space */
	strcat(pOutputString, " ");

	/* copy in hour */
	itoa(RTC.hour, (UDINT)tempString);
	strcat(pOutputString, tempString);	
	/* add colon */
	strcat(pOutputString, ":");
	/* copy in minutes */
	itoa(RTC.minute, (UDINT)tempString);
	strcat(pOutputString, tempString);		
	/* add colon */
	strcat(pOutputString, ":");
	/* copy in seconds */
	itoa(RTC.second, (UDINT)tempString);
	strcat(pOutputString, tempString);	
	/* copy in single quote */
	strcat(pOutputString, "'");


	return((UDINT)pOutputString);
}