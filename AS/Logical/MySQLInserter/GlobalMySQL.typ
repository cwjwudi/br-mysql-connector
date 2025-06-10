
TYPE
	MySQLInserter_typ : 	STRUCT 
		Command : MySQLInserterCommand_typ;
		Input : MySQLInserterInput_typ;
		Status : MySQLInserterStatus_typ;
		Config : MySQLInserterConfig_typ;
		ExternalCom : MySQLInserterExternalCom_typ;
		_Internal : MySQLInserterInternal_typ;
	END_STRUCT;
	MySQLInserterCommand_typ : 	STRUCT 
		Enable : BOOL;
		Reset : BOOL;
	END_STRUCT;
	MySQLInserterInput_typ : 	STRUCT 
		TaskTrig : ARRAY[0..TASK_SIZE_MINUS_ONE]OF BOOL;
	END_STRUCT;
	MySQLInserterStatus_typ : 	STRUCT 
		BufferNum : ARRAY[0..INTERFACE_SIZE_MINUS_ONE]OF USINT;
		Connected : BOOL;
		Task : ARRAY[0..TASK_SIZE_MINUS_ONE]OF TaskStatus_typ;
	END_STRUCT;
	MySQLInserterConfig_typ : 	STRUCT 
		TaskSetting : ARRAY[0..TASK_SIZE_MINUS_ONE]OF TaskSetting_typ;
		LostTimeMs : UDINT; (*Connect lost time*)
	END_STRUCT;
	MySQLInserterInternal_typ : 	STRUCT 
		TaskCmdStr : ARRAY[0..TASK_SIZE_MINUS_ONE]OF STRING[CMD_STR_SIZE];
	END_STRUCT;
	MySQLInserterExternalCom_typ : 	STRUCT 
		StrCmd : ARRAY[0..INTERFACE_SIZE_MINUS_ONE]OF STRING[CMD_STR_SIZE];
		Counter : ARRAY[0..INTERFACE_SIZE_MINUS_ONE]OF UDINT;
		HeartBeat : ARRAY[0..INTERFACE_SIZE_MINUS_ONE]OF UDINT;
	END_STRUCT;
	DataSetting_typ : 	STRUCT 
		Name : STRING[SQL_NAME_STR_SIZE];
		Type : STRING[SQL_NAME_STR_SIZE];
		DataAddr : UDINT;
		DataSize : USINT; (*VARCHAR需要设置，DATETIME推荐设置*)
		Digital : USINT; (*仅FLOAT有效：
保留小数点位数*)
		ManualTime : BOOL; (*仅DATETIME有效:
0：自动生成TimeStamp
1：外部给出TimeStamp*)
		MissingCheck : BOOL; (*仅INT有效:(关联数据，外部请勿操作)
0：关闭
1：开启，默认自增1，用于检查是否漏写*)
		AutoIncrement : BOOL; (*mysql属性AUTO_INCREMENT*)
		NotNull : BOOL; (*mysql属性NOT NULL*)
		PrimaryKey : BOOL; (*mysql属性PRIMARY KEY*)
		Millisec : BOOL; (*该数据是否用于记录ms*)
	END_STRUCT;
	MySQLInserterTask_typ : 	STRUCT 
		Setting : TaskSetting_typ;
		Status : TaskStatus_typ;
	END_STRUCT;
	TaskStatus_typ : 	STRUCT 
		Err : USINT;
		ErrMsg : STRING[64];
		CacheCount : USINT;
	END_STRUCT;
	TaskSetting_typ : 	STRUCT 
		TrigMode : USINT; (*0：外部上升沿触发
1：按照采样时间自动触发*)
		IntervalTimeMs : UINT; (*采样间隔时间ms，最好不要<1000，最好是1000的整数倍*)
		DbName : STRING[SQL_NAME_STR_SIZE];
		TableName : STRING[SQL_NAME_STR_SIZE];
		CacheSize : USINT; (*缓存大小，设置合并插入*)
		WritePrimaryKey : USINT; (*是否写入主键*)
		DataSetting : ARRAY[0..DATA_SIZE_MINUS_ONE]OF DataSetting_typ;
	END_STRUCT;
END_TYPE
