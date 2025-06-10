
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
		DataSize : USINT; (*VARCHAR��Ҫ���ã�DATETIME�Ƽ�����*)
		Digital : USINT; (*��FLOAT��Ч��
����С����λ��*)
		ManualTime : BOOL; (*��DATETIME��Ч:
0���Զ�����TimeStamp
1���ⲿ����TimeStamp*)
		MissingCheck : BOOL; (*��INT��Ч:(�������ݣ��ⲿ�������)
0���ر�
1��������Ĭ������1�����ڼ���Ƿ�©д*)
		AutoIncrement : BOOL; (*mysql����AUTO_INCREMENT*)
		NotNull : BOOL; (*mysql����NOT NULL*)
		PrimaryKey : BOOL; (*mysql����PRIMARY KEY*)
		Millisec : BOOL; (*�������Ƿ����ڼ�¼ms*)
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
		TrigMode : USINT; (*0���ⲿ�����ش���
1�����ղ���ʱ���Զ�����*)
		IntervalTimeMs : UINT; (*�������ʱ��ms����ò�Ҫ<1000�������1000��������*)
		DbName : STRING[SQL_NAME_STR_SIZE];
		TableName : STRING[SQL_NAME_STR_SIZE];
		CacheSize : USINT; (*�����С�����úϲ�����*)
		WritePrimaryKey : USINT; (*�Ƿ�д������*)
		DataSetting : ARRAY[0..DATA_SIZE_MINUS_ONE]OF DataSetting_typ;
	END_STRUCT;
END_TYPE
