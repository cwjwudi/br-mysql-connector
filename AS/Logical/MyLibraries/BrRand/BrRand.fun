
FUNCTION RandomBase : DINT (*随机数基础函数*)
END_FUNCTION

FUNCTION RandRange : DINT (*随机数范围函数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : DINT;
		max : DINT;
	END_VAR
END_FUNCTION

FUNCTION RandBOOL : BOOL (*输出BOOL随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandUSINT : USINT (*输出USINT随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandSINT : SINT (*输出SINT随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandUINT : UINT (*输出UINT随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandINT : INT (*输出INT随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandUDINT : UDINT (*输出UDINT随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandDINT : DINT (*输出DINT随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandREAL : REAL (*输出REAL随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandLREAL : LREAL (*输出LREAL随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
END_FUNCTION

FUNCTION RandRangeUnsigned : UDINT (*设定范围产生无符号整型随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : UDINT;
		max : UDINT;
	END_VAR
END_FUNCTION

FUNCTION RandRangeSigned : DINT (*设定范围产生有符号整型随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : DINT;
		max : DINT;
	END_VAR
END_FUNCTION

FUNCTION RandRangeReal : REAL (*设定范围产生浮点类型随机数*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		min : REAL;
		max : REAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_RandString (*生成随机字符串*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pString : {REDUND_UNREPLICABLE} UDINT; (*[Optional]生成随机字符串地址*)
		uStrLen : {REDUND_UNREPLICABLE} UDINT; (*[Optional]设定的生成随机字符串长度，若为0则充满pString*)
	END_VAR
	VAR_OUTPUT
		sStrOut : {REDUND_UNREPLICABLE} STRING[8]; (*默认输出8个字节的随机字符串*)
	END_VAR
END_FUNCTION_BLOCK
