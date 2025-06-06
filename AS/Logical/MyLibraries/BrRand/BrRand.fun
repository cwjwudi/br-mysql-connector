
FUNCTION RandomBase : DINT (*�������������*)
END_FUNCTION

FUNCTION RandRange : DINT (*�������Χ����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : DINT;
		max : DINT;
	END_VAR
END_FUNCTION

FUNCTION RandBOOL : BOOL (*���BOOL�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandUSINT : USINT (*���USINT�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandSINT : SINT (*���SINT�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandUINT : UINT (*���UINT�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandINT : INT (*���INT�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandUDINT : UDINT (*���UDINT�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandDINT : DINT (*���DINT�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandREAL : REAL (*���REAL�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandLREAL : LREAL (*���LREAL�����*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandRangeUnsigned : UDINT (*�趨��Χ�����޷������������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : UDINT;
		max : UDINT;
	END_VAR
END_FUNCTION

FUNCTION RandRangeSigned : DINT (*�趨��Χ�����з������������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : DINT;
		max : DINT;
	END_VAR
END_FUNCTION

FUNCTION RandRangeReal : REAL (*�趨��Χ�����������������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : REAL;
		max : REAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_RandString (*��������ַ���*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pString : {REDUND_UNREPLICABLE} UDINT; (*[Optional]��������ַ�����ַ*)
		uStrLen : {REDUND_UNREPLICABLE} UDINT; (*[Optional]�趨����������ַ������ȣ���Ϊ0�����pString*)
	END_VAR
	VAR_OUTPUT
		sStrOut : {REDUND_UNREPLICABLE} STRING[8]; (*Ĭ�����8���ֽڵ�����ַ���*)
	END_VAR
END_FUNCTION_BLOCK
