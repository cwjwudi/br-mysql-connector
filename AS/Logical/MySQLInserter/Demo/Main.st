
PROGRAM _INIT
	(* Insert code here *)
	gMySQLInserter.Command.Enable := 1;
	gMySQLInserter.Config.LostTimeMs := 2000;
	
	(***********************任务0**********************************)
	gMySQLInserter.Config.TaskSetting[0].DbName := 'wn_8';
	gMySQLInserter.Config.TaskSetting[0].TableName := 'ct_data';
	gMySQLInserter.Config.TaskSetting[0].TrigMode := 1; // 定时自动触发
	gMySQLInserter.Config.TaskSetting[0].IntervalTimeMs := 1000;
	gMySQLInserter.Config.TaskSetting[0].CacheSize := 2;
	
	gMySQLInserter.Config.TaskSetting[0].DataSetting[0].DataAddr := ADR(IP1);
	gMySQLInserter.Config.TaskSetting[0].DataSetting[0].Name := 'IP1';
	gMySQLInserter.Config.TaskSetting[0].DataSetting[0].Type := 'INT';
	gMySQLInserter.Config.TaskSetting[0].DataSetting[1].DataAddr := ADR(FP1);
	gMySQLInserter.Config.TaskSetting[0].DataSetting[1].Name := 'FP1';
	gMySQLInserter.Config.TaskSetting[0].DataSetting[1].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[0].DataSetting[1].Digital := 2;
	
	(***********************任务1**********************************)
	gMySQLInserter.Config.TaskSetting[1].DbName := 'wn_8';
	gMySQLInserter.Config.TaskSetting[1].TableName := 'ct_cip';
	gMySQLInserter.Config.TaskSetting[1].TrigMode := 0; // 外部上升沿触发
	gMySQLInserter.Config.TaskSetting[1].IntervalTimeMs := 0;
	gMySQLInserter.Config.TaskSetting[1].CacheSize := 1;	
	
	gMySQLInserter.Config.TaskSetting[1].DataSetting[0].DataAddr := ADR(IP2);
	gMySQLInserter.Config.TaskSetting[1].DataSetting[0].Name := 'IP2';
	gMySQLInserter.Config.TaskSetting[1].DataSetting[0].Type := 'INT';
	gMySQLInserter.Config.TaskSetting[1].DataSetting[1].DataAddr := ADR(FP2);
	gMySQLInserter.Config.TaskSetting[1].DataSetting[1].Name := 'FP2';
	gMySQLInserter.Config.TaskSetting[1].DataSetting[1].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[1].DataSetting[1].Digital := 3;
	
	(***********************任务2**********************************)
	gMySQLInserter.Config.TaskSetting[2].DbName := 'wn_9';
	gMySQLInserter.Config.TaskSetting[2].TableName := 'ct_data';	
	gMySQLInserter.Config.TaskSetting[2].TrigMode := 1; // 定时自动触发
	gMySQLInserter.Config.TaskSetting[2].IntervalTimeMs := 1000;
	gMySQLInserter.Config.TaskSetting[2].CacheSize := 2;
	
	gMySQLInserter.Config.TaskSetting[2].DataSetting[0].DataAddr := ADR(ID);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[0].Name := 'ID';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[0].Type := 'INT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[0].PrimaryKey := TRUE;
	gMySQLInserter.Config.TaskSetting[2].DataSetting[0].AutoIncrement := TRUE;
	gMySQLInserter.Config.TaskSetting[2].DataSetting[0].NotNull := TRUE;
	
	gMySQLInserter.Config.TaskSetting[2].DataSetting[1].DataAddr := ADR(STATE);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[1].Name := 'STATE';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[1].Type := 'INT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[1].MissingCheck := 1; // 调试用。用于设定检测漏写的标志位，自增1

	gMySQLInserter.Config.TaskSetting[2].DataSetting[2].DataAddr := ADR(TimeStamp);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[2].Name := 'TimeStamp';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[2].Type := 'DATETIME';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[2].DataSize := SIZEOF(TimeStamp);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[2].ManualTime := FALSE; // 自动模式，实际用不到本地TimeStamp

	
	gMySQLInserter.Config.TaskSetting[2].DataSetting[3].DataAddr := ADR(Millsec);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[3].Name := 'Millsec';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[3].Type := 'INT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[3].Millisec := TRUE;
	// F2 ~ F15
	gMySQLInserter.Config.TaskSetting[2].DataSetting[4].DataAddr := ADR(F2);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[4].Name := 'F2';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[4].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[4].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[5].DataAddr := ADR(F3);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[5].Name := 'F3';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[5].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[5].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[6].DataAddr := ADR(F4);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[6].Name := 'F4';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[6].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[6].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[7].DataAddr := ADR(F5);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[7].Name := 'F5';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[7].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[7].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[8].DataAddr := ADR(F6);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[8].Name := 'F6';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[8].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[8].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[9].DataAddr := ADR(F7);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[9].Name := 'F7';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[9].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[9].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[10].DataAddr := ADR(F8);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[10].Name := 'F8';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[10].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[10].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[11].DataAddr := ADR(F9);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[11].Name := 'F9';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[11].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[11].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[12].DataAddr := ADR(F10);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[12].Name := 'F10';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[12].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[12].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[13].DataAddr := ADR(F11);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[13].Name := 'F11';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[13].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[13].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[14].DataAddr := ADR(F12);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[14].Name := 'F12';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[14].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[14].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[15].DataAddr := ADR(F13);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[15].Name := 'F13';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[15].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[15].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[16].DataAddr := ADR(F14);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[16].Name := 'F14';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[16].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[16].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[17].DataAddr := ADR(F15);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[17].Name := 'F15';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[17].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[17].Digital := 3;

	// FP
	gMySQLInserter.Config.TaskSetting[2].DataSetting[18].DataAddr := ADR(FP);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[18].Name := 'FP';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[18].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[18].Digital := 3;

	// AP1, BP1, AP2
	gMySQLInserter.Config.TaskSetting[2].DataSetting[19].DataAddr := ADR(AP1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[19].Name := 'AP1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[19].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[19].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[20].DataAddr := ADR(BP1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[20].Name := 'BP1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[20].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[20].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[21].DataAddr := ADR(AP2);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[21].Name := 'AP2';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[21].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[21].Digital := 3;

	// ST1 ~ ST15
	gMySQLInserter.Config.TaskSetting[2].DataSetting[22].DataAddr := ADR(ST1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[22].Name := 'ST1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[22].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[22].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[23].DataAddr := ADR(ST2);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[23].Name := 'ST2';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[23].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[23].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[24].DataAddr := ADR(ST3);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[24].Name := 'ST3';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[24].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[24].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[25].DataAddr := ADR(ST4);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[25].Name := 'ST4';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[25].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[25].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[26].DataAddr := ADR(ST5);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[26].Name := 'ST5';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[26].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[26].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[27].DataAddr := ADR(ST6);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[27].Name := 'ST6';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[27].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[27].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[28].DataAddr := ADR(ST7);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[28].Name := 'ST7';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[28].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[28].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[29].DataAddr := ADR(ST8);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[29].Name := 'ST8';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[29].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[29].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[30].DataAddr := ADR(ST9);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[30].Name := 'ST9';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[30].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[30].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[31].DataAddr := ADR(ST10);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[31].Name := 'ST10';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[31].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[31].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[32].DataAddr := ADR(ST11);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[32].Name := 'ST11';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[32].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[32].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[33].DataAddr := ADR(ST12);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[33].Name := 'ST12';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[33].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[33].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[34].DataAddr := ADR(ST13);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[34].Name := 'ST13';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[34].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[34].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[35].DataAddr := ADR(ST14);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[35].Name := 'ST14';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[35].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[35].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[36].DataAddr := ADR(ST15);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[36].Name := 'ST15';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[36].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[36].Digital := 3;

	// AIR, CP, CT, CRT, ES, FP1, FT, FF
	gMySQLInserter.Config.TaskSetting[2].DataSetting[37].DataAddr := ADR(AIR);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[37].Name := 'AIR';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[37].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[37].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[38].DataAddr := ADR(CP);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[38].Name := 'CP';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[38].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[38].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[39].DataAddr := ADR(CT);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[39].Name := 'CT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[39].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[39].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[40].DataAddr := ADR(CRT);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[40].Name := 'CRT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[40].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[40].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[41].DataAddr := ADR(ES);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[41].Name := 'ES';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[41].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[41].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[42].DataAddr := ADR(FP1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[42].Name := 'FP1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[42].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[42].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[43].DataAddr := ADR(FT);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[43].Name := 'FT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[43].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[43].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[44].DataAddr := ADR(FF);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[44].Name := 'FF';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[44].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[44].Digital := 3;

	// FC (DINT)
	gMySQLInserter.Config.TaskSetting[2].DataSetting[45].DataAddr := ADR(FC);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[45].Name := 'FC';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[45].Type := 'INT';

	// HT1 ~ HT20
	gMySQLInserter.Config.TaskSetting[2].DataSetting[46].DataAddr := ADR(HT1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[46].Name := 'HT1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[46].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[46].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[47].DataAddr := ADR(HT2);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[47].Name := 'HT2';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[47].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[47].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[48].DataAddr := ADR(HT3);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[48].Name := 'HT3';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[48].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[48].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[49].DataAddr := ADR(HT4);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[49].Name := 'HT4';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[49].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[49].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[50].DataAddr := ADR(HT5);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[50].Name := 'HT5';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[50].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[50].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[51].DataAddr := ADR(HT6);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[51].Name := 'HT6';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[51].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[51].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[52].DataAddr := ADR(HT7);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[52].Name := 'HT7';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[52].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[52].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[53].DataAddr := ADR(HT8);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[53].Name := 'HT8';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[53].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[53].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[54].DataAddr := ADR(HT9);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[54].Name := 'HT9';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[54].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[54].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[55].DataAddr := ADR(HT10);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[55].Name := 'HT10';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[55].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[55].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[56].DataAddr := ADR(HT11);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[56].Name := 'HT11';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[56].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[56].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[57].DataAddr := ADR(HT12);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[57].Name := 'HT12';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[57].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[57].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[58].DataAddr := ADR(HT13);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[58].Name := 'HT13';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[58].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[58].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[59].DataAddr := ADR(HT14);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[59].Name := 'HT14';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[59].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[59].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[60].DataAddr := ADR(HT15);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[60].Name := 'HT15';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[60].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[60].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[61].DataAddr := ADR(HT16);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[61].Name := 'HT16';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[61].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[61].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[62].DataAddr := ADR(HT17);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[62].Name := 'HT17';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[62].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[62].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[63].DataAddr := ADR(HT18);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[63].Name := 'HT18';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[63].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[63].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[64].DataAddr := ADR(HT19);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[64].Name := 'HT19';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[64].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[64].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[65].DataAddr := ADR(HT20);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[65].Name := 'HT20';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[65].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[65].Digital := 3;

	// MP, MT, MCT, MCP, EC, EST, ES1, TC, TF, TW
	gMySQLInserter.Config.TaskSetting[2].DataSetting[66].DataAddr := ADR(MP);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[66].Name := 'MP';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[66].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[66].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[67].DataAddr := ADR(MT);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[67].Name := 'MT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[67].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[67].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[68].DataAddr := ADR(MCT);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[68].Name := 'MCT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[68].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[68].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[69].DataAddr := ADR(MCP);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[69].Name := 'MCP';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[69].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[69].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[70].DataAddr := ADR(EC);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[70].Name := 'EC';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[70].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[70].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[71].DataAddr := ADR(EST);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[71].Name := 'EST';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[71].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[71].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[72].DataAddr := ADR(ES1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[72].Name := 'ES1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[72].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[72].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[73].DataAddr := ADR(TC);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[73].Name := 'TC';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[73].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[73].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[74].DataAddr := ADR(TF);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[74].Name := 'TF';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[74].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[74].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[75].DataAddr := ADR(TW);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[75].Name := 'TW';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[75].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[75].Digital := 3;
	
	gMySQLInserter.Config.TaskSetting[2].DataSetting[76].DataAddr := ADR(CV);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[76].Name := 'CV';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[76].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[76].Digital := 3;
	
	gMySQLInserter.Config.TaskSetting[2].DataSetting[77].DataAddr := ADR(VPF);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[77].Name := 'VPF';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[77].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[77].Digital := 3;
	// 添加 WT 点位
	gMySQLInserter.Config.TaskSetting[2].DataSetting[78].DataAddr := ADR(WT);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[78].Name := 'WT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[78].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[78].Digital := 3;

	gMySQLInserter.Config.TaskSetting[2].DataSetting[79].DataAddr := ADR(F1);
	gMySQLInserter.Config.TaskSetting[2].DataSetting[79].Name := 'F1';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[79].Type := 'FLOAT';
	gMySQLInserter.Config.TaskSetting[2].DataSetting[79].Digital := 3;

	
END_PROGRAM

PROGRAM _CYCLIC
	(* Insert code here *)

	
	IP1 := RandINT();
	IP2 := RandINT();

	FP1 := RandRangeReal(0, 100);
	FP2 := RandRangeReal(0, 100);

	CV := RandRangeReal(0, 100);
	VPF := RandRangeReal(0, 100);
	WT := RandRangeReal(0, 100);

	F1 := RandRangeReal(0, 100);
	F2 := RandRangeReal(0, 100);
	F3 := RandRangeReal(0, 100);
	F4 := RandRangeReal(0, 100);
	F5 := RandRangeReal(0, 100);
	F6 := RandRangeReal(0, 100);
	F7 := RandRangeReal(0, 100);
	F8 := RandRangeReal(0, 100);
	F9 := RandRangeReal(0, 100);
	F10 := RandRangeReal(0, 100);
	F11 := RandRangeReal(0, 100);
	F12 := RandRangeReal(0, 100);
	F13 := RandRangeReal(0, 100);
	F14 := RandRangeReal(0, 100);
	F15 := RandRangeReal(0, 100);

	FP := RandRangeReal(0, 100);

	AP1 := RandRangeReal(0, 100);
	BP1 := RandRangeReal(0, 100);
	AP2 := RandRangeReal(0, 100);

	ST1 := RandRangeReal(0, 100);
	ST2 := RandRangeReal(0, 100);
	ST3 := RandRangeReal(0, 100);
	ST4 := RandRangeReal(0, 100);
	ST5 := RandRangeReal(0, 100);
	ST6 := RandRangeReal(0, 100);
	ST7 := RandRangeReal(0, 100);
	ST8 := RandRangeReal(0, 100);
	ST9 := RandRangeReal(0, 100);
	ST10 := RandRangeReal(0, 100);
	ST11 := RandRangeReal(0, 100);
	ST12 := RandRangeReal(0, 100);
	ST13 := RandRangeReal(0, 100);
	ST14 := RandRangeReal(0, 100);
	ST15 := RandRangeReal(0, 100);

	AIR := RandRangeReal(0, 100);
	CP := RandRangeReal(0, 100);
	CT := RandRangeReal(0, 100);
	CRT := RandRangeReal(0, 100);
	ES := RandRangeReal(0, 100);
	FT := RandRangeReal(0, 100);
	FF := RandRangeReal(0, 100);

	FC := RandINT();

	HT1 := RandRangeReal(0, 100);
	HT2 := RandRangeReal(0, 100);
	HT3 := RandRangeReal(0, 100);
	HT4 := RandRangeReal(0, 100);
	HT5 := RandRangeReal(0, 100);
	HT6 := RandRangeReal(0, 100);
	HT7 := RandRangeReal(0, 100);
	HT8 := RandRangeReal(0, 100);
	HT9 := RandRangeReal(0, 100);
	HT10 := RandRangeReal(0, 100);
	HT11 := RandRangeReal(0, 100);
	HT12 := RandRangeReal(0, 100);
	HT13 := RandRangeReal(0, 100);
	HT14 := RandRangeReal(0, 100);
	HT15 := RandRangeReal(0, 100);
	HT16 := RandRangeReal(0, 100);
	HT17 := RandRangeReal(0, 100);
	HT18 := RandRangeReal(0, 100);
	HT19 := RandRangeReal(0, 100);
	HT20 := RandRangeReal(0, 100);

	MP := RandRangeReal(0, 100);
	MT := RandRangeReal(0, 100);
	MCT := RandRangeReal(0, 100);
	MCP := RandRangeReal(0, 100);
	EC := RandRangeReal(0, 100);
	EST := RandRangeReal(0, 100);
	ES1 := RandRangeReal(0, 100);
	TC := RandRangeReal(0, 100);
	TF := RandRangeReal(0, 100);
	TW := RandRangeReal(0, 100);

	//gMySQLInserter.Task.Setting.DataSetting[]

END_PROGRAM

PROGRAM _EXIT
	(* Insert code here *)
	 
END_PROGRAM

