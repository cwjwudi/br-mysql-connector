
{REDUND_ERROR} FUNCTION_BLOCK FB_GetPvInfo (*ͨ��������+����������õ�ַ���������͡����ݳ�����Ϣ*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sAppModuleName : STRING[20]; (*������:��ע�ⳬ��10���ַ����Զ���д����Cpu.sw����ϢΪ׼*)
		sName : STRING[65]; (*������*)
		sCompleteName : STRING[107]; (*(��ѡ)�ɴ��������������������ơ�����˱�����ֵ����sModuleName��sName�������á�*)
	END_VAR
	VAR_OUTPUT
		udPvAddr : {REDUND_UNREPLICABLE} UDINT; (*������ַ*)
		sDataType : {REDUND_UNREPLICABLE} STRING[18]; (*�ַ������͵���������*)
		udLenth : {REDUND_UNREPLICABLE} UDINT; (*����ʵ��ռ�ó���*)
		sPvName : STRING[107]; (*�ڲ�ƴ�ӵı�����*)
		uDataType : UDINT; (*�������͵ı�������*)
		status : UINT; (*����״̬��Ϣ��0��Ϊ����*)
		uiDimension : UINT;
	END_VAR
	VAR
		udData_typ : UDINT;
		udData_len : UDINT;
		sDelimiter : STRING[2];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION GetPvOutside : UINT (*��������Ϣ��ȡ��������ⲿ���ݽṹ��*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		dataIn : GetPvInfoUser_typ;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION DataJoint : UINT (*���ݵ�ַ������ƴ��*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		DataIn : DataJointUser_typ;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION DataSeparate : UINT (*���ݵ�ַ�����ݲ��*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		DataIn : DataSeperateUser_typ;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION JudgeSrcPvInfoNum : UINT (*�ж�GetPvInfoUser����ṹ��Ч����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		DataIn : JudgeSrcPvInfoNumUser_typ;
	END_VAR
END_FUNCTION

FUNCTION_BLOCK FB_GetModuleName (*��ȡ���ô˹��ܿ��������*)
	VAR_OUTPUT
		strOut : STRING[20];
	END_VAR
	VAR
		udCheckCallCount : UDINT := 0;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FB_GetLocalPvAddr (*��ȡ�ֲ�������ַ��Ϣ���������ַ�����Ϣ������logger*)
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

FUNCTION_BLOCK FB_GetPvAddrStr (*��ȡ������ַ��Ϣ���������ַ�����Ϣ������logger*)
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

{REDUND_ERROR} FUNCTION_BLOCK FB_GetStruPvMemName (*֧�־ֲ��Լ�ȫ�ֵı����г�������ĳ�Ա������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		LocalFlag : BOOL;
		sModuleName : STRING[20];
		sName : {REDUND_UNREPLICABLE} STRING[NAME_STR_SIZE];
		sCompleteName : STRING[107]; (*(��ѡ)�ɴ��������������������ơ�����˱�����ֵ����sModuleName��sName�������á�*)
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

{REDUND_ERROR} FUNCTION_BLOCK FB_ShowLocalPvAddrData (*��ʾ�ֲ������ĵ�ַ��Χ���ڴ����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
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

{REDUND_ERROR} FUNCTION_BLOCK FB_ShowAddrData (*�����ַ����ʾ��ַǰ��һ�οռ���ڴ�ֲ�*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pWatchAddr : UDINT; (*�۲����ݷֲ��ĵ�ַ����*)
		bContinuousWatch : BOOL; (*�����������������������*)
		iOffset : DINT; (*��Ӧ������ַ������ƫ�ƣ����ڲ鿴����*)
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

{REDUND_ERROR} FUNCTION_BLOCK FB_ShowPvAddrData (*��ʾ�����ĵ�ַǰ��Χ��ʵ������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sModuleName : {REDUND_UNREPLICABLE} STRING[20];
		sName : {REDUND_UNREPLICABLE} STRING[NAME_STR_SIZE];
		bContinuousWatch : BOOL; (*�����������������������*)
		iOffset : DINT; (*��Ӧ������ַ������ƫ�ƣ����ڲ鿴����*)
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

{REDUND_ERROR} FUNCTION Strcats : UDINT (*����strlcatʵ�ֵĻ��������������strcat*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pDest : UDINT;
		udDestsz : UDINT;
		pSrc : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Strcpys : UDINT (*����strlcpyʵ�ֵĻ��������������strcpy*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pDest : UDINT;
		udDestsz : UDINT;
		pSrc : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Strlens : UDINT (*������󳤶����Ƶ��ַ�������ͳ�ƺ���*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pStr : UDINT;
		udMaxSize : UDINT;
	END_VAR
END_FUNCTION

FUNCTION_BLOCK FB_Udint2Str (*��UDINT��������ת��ΪSTRING*)
	VAR_INPUT
		udInput : UDINT;
	END_VAR
	VAR_OUTPUT
		strOut : STRING[14];
		uiLen : UINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Real2Str (*����С�������Ƶ�REAL����ת��*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		rNum : REAL;
		digital : {REDUND_UNREPLICABLE} USINT := 2;
	END_VAR
	VAR_OUTPUT
		strOut : {REDUND_UNREPLICABLE} STRING[32];
		uiLen : UINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_LReal2Str (*����С�������Ƶ�LREAL����ת��*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		rNum : {REDUND_UNREPLICABLE} LREAL;
		digital : {REDUND_UNREPLICABLE} USINT := 2;
	END_VAR
	VAR_OUTPUT
		strOut : {REDUND_UNREPLICABLE} STRING[32];
		uiLen : {REDUND_UNREPLICABLE} UINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION VarWarnLogWrite : UINT (*��System��дLogger����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		uNum : UINT;
		psErrorInfo : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Dec2Hex (*ʮ��������ת��Ϊʮ�������ַ�������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		iDec : {REDUND_UNREPLICABLE} DINT;
	END_VAR
	VAR_OUTPUT
		sHex : {REDUND_UNREPLICABLE} STRING[20];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Hex2Dec (*ʮ�������ַ�������ת��Ϊʮ��������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sHex : {REDUND_UNREPLICABLE} STRING[20];
	END_VAR
	VAR_OUTPUT
		iDec : DINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_GetPvEntireName (*����������ж��Ƿ�Ϊ�����������ͣ�������ǣ��򷵻���һ����Ϣ*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		sModuleName : STRING[20]; (*������:��ע�ⳬ��10���ַ����Զ���д����Cpu.sw����ϢΪ׼*)
		sName : STRING[65]; (*������*)
		sCompleteName : STRING[107]; (*(��ѡ)�ɴ��������������������ơ�����˱�����ֵ����sModuleName��sName�������á�*)
	END_VAR
	VAR_OUTPUT
		uStatus : UINT;
		sEntirePvName : STRING[107];
		uCurrentIndex : UDINT;
		uTotalNumber : UDINT;
		bInTraversal : BOOL; (*��־λ�����ڱ�������/�ṹ��ĳ�Ա*)
		bEnd : BOOL; (*����������ǽṹ��������飬�����ٵݹ��ȡ���������*)
	END_VAR
	VAR
		sModuleNameTmp : STRING[20]; (*������:��ע�ⳬ��10���ַ����Զ���д����Cpu.sw����ϢΪ׼*)
		sNameTmp : STRING[65]; (*������*)
		FB_GetPvInfo_0 : FB_GetPvInfo;
		FB_GetStruPvMemName_0 : FB_GetStruPvMemName;
		FB_Udint2Str_0 : FB_Udint2Str;
		sCompleteNameTmp : STRING[107];
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION VarServLogWrite : BOOL (*��System��дLogger������PLC����SERV*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		uErrorNum : UINT;
		psErrorInfo : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION ReturnPvAddr : UDINT (*�ɻ�ñ�����ַ��Ϣ������Ҳ����������SERV*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		psVarName : UDINT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION_BLOCK FB_ContinualStrcat (*�ɾ��б�����,��������strcat�����ĺ���,���⸺�ع���*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		psDestStr : {REDUND_UNREPLICABLE} UDINT;
		uDestMaxSize : {REDUND_UNREPLICABLE} UDINT; (*[ ��ѡ ] �������룬�򲻽��а�ȫ���*)
		psSrcStr : {REDUND_UNREPLICABLE} UDINT;
		uSrcMaxSize : {REDUND_UNREPLICABLE} UDINT; (*[ ��ѡ ] �������룬�򲻽��а�ȫ���*)
		bInitial : BOOL; (*��ΪTRUE����uOffset��0����һ�ε��ô˹��ܿ��ʱ����ʹ��*)
		uDestStrOffset : UDINT; (*[ ��ѡ ] Ŀ���ַ�����ĳһƫ������ʼ�����ַ�����ӣ���Ӱ�칦�ܣ������ڽ���strcat����*)
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
