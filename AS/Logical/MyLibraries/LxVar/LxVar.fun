
{REDUND_ERROR} FUNCTION_BLOCK FB_GetPvInfo (*通过任务名+变量名，获得地址、数据类型、数据长度信息*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sAppModuleName : STRING[20]; (*任务名:需注意超过10个字符会自动缩写。以Cpu.sw中信息为准*)
		sName : STRING[65]; (*变量名*)
		sCompleteName : STRING[107]; (*(可选)可带任务名的完整变量名称。如果此变量有值，则sModuleName与sName不起作用。*)
	END_VAR
	VAR_OUTPUT
		udPvAddr : {REDUND_UNREPLICABLE} UDINT; (*变量地址*)
		sDataType : {REDUND_UNREPLICABLE} STRING[18]; (*字符串类型的数据类型*)
		udLenth : {REDUND_UNREPLICABLE} UDINT; (*变量实际占用长度*)
		sPvName : STRING[107]; (*内部拼接的变量名*)
		uDataType : UDINT; (*数据类型的变量类型*)
		status : UINT; (*返回状态信息，0则为正常*)
		uiDimension : UINT;
	END_VAR
	VAR
		udData_typ : UDINT;
		udData_len : UDINT;
		sDelimiter : STRING[2];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION GetPvOutside : UINT (*将变量信息获取并输出至外部数据结构中*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		dataIn : GetPvInfoUser_typ;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION DataJoint : UINT (*根据地址，数据拼接*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		DataIn : DataJointUser_typ;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION DataSeparate : UINT (*根据地址，数据拆分*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		DataIn : DataSeperateUser_typ;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION JudgeSrcPvInfoNum : UINT (*判断GetPvInfoUser数组结构有效长度*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		DataIn : JudgeSrcPvInfoNumUser_typ;
	END_VAR
END_FUNCTION

FUNCTION_BLOCK FB_GetModuleName (*获取调用此功能块的任务名*)
	VAR_OUTPUT
		strOut : STRING[20];
	END_VAR
	VAR
		udCheckCallCount : UDINT := 0;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FB_GetLocalPvAddr (*获取局部变量地址信息，可生成字符串信息并生成logger*)
	VAR_INPUT
		bWriteLogEnableFlag : BOOL := FALSE;
		sPvName : STRING[65];
	END_VAR
	VAR_OUTPUT
		udAddr : UDINT;
		strOut : STRING[130];
	END_VAR
	VAR
		udCheckCallCount : UDINT;
		FB_GetPvInfoY : FB_GetPvInfo;
		FB_GetModuleNameY : FB_GetModuleName;
		FB_Udint2StrY : FB_Udint2Str;
		sPvNameTmp : STRING[65];
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FB_GetPvAddrStr (*获取变量地址信息，可生成字符串信息并生成logger*)
	VAR_INPUT
		bWriteLogEnableFlag : BOOL := FALSE;
		sModuleName : STRING[20];
		sPvName : STRING[65];
	END_VAR
	VAR_OUTPUT
		udAddr : UDINT;
		strOut : STRING[130];
		uStatus : UINT;
	END_VAR
	VAR
		udCheckCallCount : UDINT;
		FB_GetPvInfoY : FB_GetPvInfo;
		FB_Udint2StrY : FB_Udint2Str;
		sPvNameTmp : STRING[65];
		sModuleNameTmp : STRING[20];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_GetStruPvMemName (*支持局部以及全局的变量列出其包含的成员变量名*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		LocalFlag : BOOL;
		sModuleName : STRING[20];
		sName : {REDUND_UNREPLICABLE} STRING[NAME_STR_SIZE];
		sCompleteName : STRING[107]; (*(可选)可带任务名的完整变量名称。如果此变量有值，则sModuleName与sName不起作用。*)
	END_VAR
	VAR_OUTPUT
		sArrMemName : ARRAY[0..GET_STRU_PV_NAME_SIZE] OF STRING[MODULE_PV_NAME_STR_SIZE];
		uiMemNum : UINT;
		uiStatus : UINT;
	END_VAR
	VAR
		uiIndex : UINT;
		sPvName : STRING[MODULE_PV_NAME_STR_SIZE];
		udCheckCallCount : UDINT;
		sModulePvName : USINT;
		sModuleNameTmp : STRING[20];
		sNameTmp : STRING[NAME_STR_SIZE];
		FB_GetModuleNameY : FB_GetModuleName;
		sCompleteNameTmp : STRING[107];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_ShowLocalPvAddrData (*显示局部变量的地址范围内内存分配*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sName : {REDUND_UNREPLICABLE} STRING[NAME_STR_SIZE];
	END_VAR
	VAR_OUTPUT
		usArrData : {REDUND_UNREPLICABLE} ARRAY[0..SHOW_LOCAL_PV_ADDR_SIZE] OF USINT;
		udAddr : UDINT;
	END_VAR
	VAR
		sNameTmp : STRING[NAME_STR_SIZE];
		FB_GetLocalPvAddrStrY : FB_GetLocalPvAddr;
		udCheckCallCount : UDINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_ShowAddrData (*输入地址，显示地址前后一段空间的内存分布*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pWatchAddr : UDINT; (*观察数据分布的地址输入*)
		bContinuousWatch : BOOL; (*如果开启，则连续更新数据*)
		iOffset : DINT; (*对应变量地址的数据偏移，便于查看数据*)
	END_VAR
	VAR_OUTPUT
		udCurrentAddr : {REDUND_UNREPLICABLE} UDINT;
		auData : {REDUND_UNREPLICABLE} ARRAY[0..SHOW_LOCAL_PV_ADDR_SIZE] OF USINT;
		sData : STRING[SHOW_LOCAL_PV_ADDR_SIZE];
		auDataBefore : ARRAY[0..SHOW_LOCAL_PV_ADDR_SIZE] OF USINT;
		sDataBefore : STRING[SHOW_LOCAL_PV_ADDR_SIZE];
		uStatus : UINT;
	END_VAR
	VAR
		udCheckCallCount : {REDUND_UNREPLICABLE} UDINT;
		pWatchAddrTmp : UDINT;
		iOffsetTmp : DINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_ShowPvAddrData (*显示变量的地址前后范围的实际数据*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sModuleName : {REDUND_UNREPLICABLE} STRING[20];
		sName : {REDUND_UNREPLICABLE} STRING[NAME_STR_SIZE];
		bContinuousWatch : BOOL; (*如果开启，则连续更新数据*)
		iOffset : DINT; (*对应变量地址的数据偏移，便于查看数据*)
	END_VAR
	VAR_OUTPUT
		auData : {REDUND_UNREPLICABLE} ARRAY[0..SHOW_LOCAL_PV_ADDR_SIZE] OF USINT;
		udAddr : {REDUND_UNREPLICABLE} UDINT;
		uStatus : UINT;
		sData : STRING[SHOW_LOCAL_PV_ADDR_SIZE];
		auDataBefore : ARRAY[0..SHOW_LOCAL_PV_ADDR_SIZE] OF USINT;
		sDataBefore : STRING[SHOW_LOCAL_PV_ADDR_SIZE];
	END_VAR
	VAR
		sModuleNameTmp : STRING[20];
		sNameTmp : {REDUND_UNREPLICABLE} STRING[NAME_STR_SIZE];
		FB_GetPvAddrStr_0 : {REDUND_UNREPLICABLE} FB_GetPvAddrStr;
		udCheckCallCount : {REDUND_UNREPLICABLE} UDINT;
		iOffsetTmp : DINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION Strcats : UDINT (*基于strlcat实现的缓冲区溢出保护的strcat*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pDest : UDINT;
		udDestsz : UDINT;
		pSrc : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Strcpys : UDINT (*基于strlcpy实现的缓冲区溢出保护的strcpy*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pDest : UDINT;
		udDestsz : UDINT;
		pSrc : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Strlens : UDINT (*带有最大长度限制的字符串长度统计函数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pStr : UDINT;
		udMaxSize : UDINT;
	END_VAR
END_FUNCTION

FUNCTION_BLOCK FB_Udint2Str (*将UDINT类型数据转换为STRING*)
	VAR_INPUT
		udInput : UDINT;
	END_VAR
	VAR_OUTPUT
		strOut : STRING[14];
		uiLen : UINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Real2Str (*带有小数点限制的REAL数据转换*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		rNum : REAL;
		digital : {REDUND_UNREPLICABLE} USINT := 2;
	END_VAR
	VAR_OUTPUT
		strOut : {REDUND_UNREPLICABLE} STRING[32];
		uiLen : UINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_LReal2Str (*带有小数点限制的LREAL数据转换*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		rNum : {REDUND_UNREPLICABLE} LREAL;
		digital : {REDUND_UNREPLICABLE} USINT := 2;
	END_VAR
	VAR_OUTPUT
		strOut : {REDUND_UNREPLICABLE} STRING[32];
		uiLen : {REDUND_UNREPLICABLE} UINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION VarWarnLogWrite : UINT (*在System中写Logger函数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		uNum : UINT;
		psErrorInfo : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Dec2Hex (*十进制数据转换为十六进制字符串数据*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		iDec : {REDUND_UNREPLICABLE} DINT;
	END_VAR
	VAR_OUTPUT
		sHex : {REDUND_UNREPLICABLE} STRING[20];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Hex2Dec (*十六进制字符串数据转换为十进制数据*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sHex : {REDUND_UNREPLICABLE} STRING[20];
	END_VAR
	VAR_OUTPUT
		iDec : DINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_GetPvEntireName (*输入变量，判断是否为基本数据类型，如果不是，则返回下一级信息*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sModuleName : STRING[20]; (*任务名:需注意超过10个字符会自动缩写。以Cpu.sw中信息为准*)
		sName : STRING[65]; (*变量名*)
		sCompleteName : STRING[107]; (*(可选)可带任务名的完整变量名称。如果此变量有值，则sModuleName与sName不起作用。*)
	END_VAR
	VAR_OUTPUT
		uStatus : UINT;
		sEntirePvName : STRING[107];
		uCurrentIndex : UDINT;
		uTotalNumber : UDINT;
		bInTraversal : BOOL; (*标志位：正在遍历数组/结构体的成员*)
		bEnd : BOOL; (*代表变量不是结构体或者数组，无需再递归获取其变量名。*)
	END_VAR
	VAR
		sModuleNameTmp : STRING[20]; (*任务名:需注意超过10个字符会自动缩写。以Cpu.sw中信息为准*)
		sNameTmp : STRING[65]; (*变量名*)
		FB_GetPvInfo_0 : FB_GetPvInfo;
		FB_GetStruPvMemName_0 : FB_GetStruPvMemName;
		FB_Udint2Str_0 : FB_Udint2Str;
		sCompleteNameTmp : STRING[107];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION VarServLogWrite : BOOL (*在System中写Logger函数，PLC进入SERV*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		uErrorNum : UINT;
		psErrorInfo : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION ReturnPvAddr : UDINT (*可获得变量地址信息，如果找不到，则进入SERV*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		psVarName : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION_BLOCK FB_ContinualStrcat (*可具有保护的,用于连续strcat操作的函数,避免负载过高*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		psDestStr : {REDUND_UNREPLICABLE} UDINT;
		uDestMaxSize : {REDUND_UNREPLICABLE} UDINT; (*[ 可选 ] 若不输入，则不进行安全检查*)
		psSrcStr : {REDUND_UNREPLICABLE} UDINT;
		uSrcMaxSize : {REDUND_UNREPLICABLE} UDINT; (*[ 可选 ] 若不输入，则不进行安全检查*)
		bInitial : BOOL; (*若为TRUE，则uOffset归0，第一次调用此功能块的时候需使用*)
		uDestStrOffset : UDINT; (*[ 可选 ] 目标字符串的某一偏移量开始进行字符串添加，不影响功能，可用于降低strcat负载*)
	END_VAR
	VAR_OUTPUT
		uStrSize : UDINT;
		uStatus : {REDUND_UNREPLICABLE} UINT;
	END_VAR
	VAR
		uOffset : {REDUND_UNREPLICABLE} UDINT;
		uSrcActualLenth : UDINT;
		uDestInitialLenth : UDINT;
	END_VAR
END_FUNCTION_BLOCK
