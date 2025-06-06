
TYPE
	GetPvInfoUser_typ : 	STRUCT 
		udPvAddr : UDINT;
		sDataType : STRING[19];
		udLenth : UDINT;
		sModuleName : STRING[21];
		sName : STRING[65];
	END_STRUCT;
	DataJointUser_typ : 	STRUCT 
		sCurrentName : STRING[65];
		sCurrentModName : STRING[21];
		udCurrentOffset : UDINT;
		udDataIndex : UDINT;
		udBufferMaxLen : UDINT;
		pBuffer : UDINT;
		pSrcPvInfo : UDINT;
		udSrcPvInfoNum : UDINT;
		status : UINT;
		sErrLogMessage : STRING[160];
	END_STRUCT;
	DataSeperateUser_typ : 	STRUCT 
		sCurrentName : STRING[65];
		sCurrentModName : STRING[21];
		udCurrentOffset : UDINT;
		udDataIndex : UDINT;
		udBufferMaxLen : UDINT;
		pBuffer : UDINT;
		pSrcPvInfo : UDINT;
		udSrcPvInfoNum : UDINT;
		status : UINT;
		sErrLogMessage : STRING[160];
	END_STRUCT;
	JudgeSrcPvInfoNumUser_typ : 	STRUCT 
		pPvArrInstance : UDINT;
		udPvArrInstanceLen : UDINT;
		udSrcNum : UDINT;
		status : UINT;
	END_STRUCT;
	LxData_Tmp_Value_typ : 	STRUCT 
		bBOOL : BOOL;
		iSINT : SINT;
		iINT : INT;
		iDINT : DINT;
		uUSINT : USINT;
		uUINT : UINT;
		uUDINT : UDINT;
		rREAL : REAL;
		tDATA_AND_TIME : DATE_AND_TIME;
		tTIME : TIME;
		tDATE : DATE;
		rLREAL : LREAL;
	END_STRUCT;
END_TYPE
