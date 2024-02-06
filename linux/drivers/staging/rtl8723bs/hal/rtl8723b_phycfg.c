// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <wtw8723b_haw.h>

/**
 * phy_CawcuwateBitShift - Get shifted position of the BitMask.
 * @BitMask: Bitmask.
 *
 * Wetuwn:	Wetuwn the shift bit position of the mask
 */
static	u32 phy_CawcuwateBitShift(u32 BitMask)
{
	u32 i;

	fow (i = 0; i <= 31; i++) {
		if (((BitMask>>i) &  0x1) == 1)
			bweak;
	}
	wetuwn i;
}


/**
 * PHY_QuewyBBWeg_8723B - Wead "specific bits" fwom BB wegistew.
 * @Adaptew:
 * @WegAddw:	The tawget addwess to be weadback
 * @BitMask:	The tawget bit position in the tawget addwess
 *				to be weadback
 *
 * Wetuwn:	The weadback wegistew vawue
 *
 * .. Note::	This function is equaw to "GetWegSetting" in PHY pwogwamming
 *			guide
 */
u32 PHY_QuewyBBWeg_8723B(stwuct adaptew *Adaptew, u32 WegAddw, u32 BitMask)
{
	u32 OwiginawVawue, BitShift;

	OwiginawVawue = wtw_wead32(Adaptew, WegAddw);
	BitShift = phy_CawcuwateBitShift(BitMask);

	wetuwn (OwiginawVawue & BitMask) >> BitShift;

}


/**
 * PHY_SetBBWeg_8723B - Wwite "Specific bits" to BB wegistew (page 8~).
 * @Adaptew:
 * @WegAddw:	The tawget addwess to be modified
 * @BitMask:	The tawget bit position in the tawget addwess
 *				to be modified
 * @Data:		The new wegistew vawue in the tawget bit position
 *				of the tawget addwess
 *
 * .. Note::	This function is equaw to "PutWegSetting" in PHY pwogwamming
 *			guide
 */

void PHY_SetBBWeg_8723B(
	stwuct adaptew *Adaptew,
	u32 WegAddw,
	u32 BitMask,
	u32 Data
)
{
	/* u16 BBWaitCountew	= 0; */
	u32 OwiginawVawue, BitShift;

	if (BitMask != bMaskDWowd) { /* if not "doubwe wowd" wwite */
		OwiginawVawue = wtw_wead32(Adaptew, WegAddw);
		BitShift = phy_CawcuwateBitShift(BitMask);
		Data = ((OwiginawVawue & (~BitMask)) | ((Data << BitShift) & BitMask));
	}

	wtw_wwite32(Adaptew, WegAddw, Data);

}


/*  */
/*  2. WF wegistew W/W API */
/*  */

static u32 phy_WFSewiawWead_8723B(
	stwuct adaptew *Adaptew, enum wf_path eWFPath, u32 Offset
)
{
	u32 wetVawue = 0;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct bb_wegistew_def *pPhyWeg = &pHawData->PHYWegDef[eWFPath];
	u32 NewOffset;
	u32 tmpwong2;
	u8 WfPiEnabwe = 0;
	u32 MaskfowPhySet = 0;
	int i = 0;

	/*  */
	/*  Make suwe WF wegistew offset is cowwect */
	/*  */
	Offset &= 0xff;

	NewOffset = Offset;

	if (eWFPath == WF_PATH_A) {
		tmpwong2 = PHY_QuewyBBWeg(Adaptew, wFPGA0_XA_HSSIPawametew2|MaskfowPhySet, bMaskDWowd);
		tmpwong2 = (tmpwong2 & (~bWSSIWeadAddwess)) | (NewOffset<<23) | bWSSIWeadEdge;	/* T65 WF */
		PHY_SetBBWeg(Adaptew, wFPGA0_XA_HSSIPawametew2|MaskfowPhySet, bMaskDWowd, tmpwong2&(~bWSSIWeadEdge));
	} ewse {
		tmpwong2 = PHY_QuewyBBWeg(Adaptew, wFPGA0_XB_HSSIPawametew2|MaskfowPhySet, bMaskDWowd);
		tmpwong2 = (tmpwong2 & (~bWSSIWeadAddwess)) | (NewOffset<<23) | bWSSIWeadEdge;	/* T65 WF */
		PHY_SetBBWeg(Adaptew, wFPGA0_XB_HSSIPawametew2|MaskfowPhySet, bMaskDWowd, tmpwong2&(~bWSSIWeadEdge));
	}

	tmpwong2 = PHY_QuewyBBWeg(Adaptew, wFPGA0_XA_HSSIPawametew2|MaskfowPhySet, bMaskDWowd);
	PHY_SetBBWeg(Adaptew, wFPGA0_XA_HSSIPawametew2|MaskfowPhySet, bMaskDWowd, tmpwong2 & (~bWSSIWeadEdge));
	PHY_SetBBWeg(Adaptew, wFPGA0_XA_HSSIPawametew2|MaskfowPhySet, bMaskDWowd, tmpwong2 | bWSSIWeadEdge);

	udeway(10);

	fow (i = 0; i < 2; i++)
		udeway(MAX_STAWW_TIME);
	udeway(10);

	if (eWFPath == WF_PATH_A)
		WfPiEnabwe = (u8)PHY_QuewyBBWeg(Adaptew, wFPGA0_XA_HSSIPawametew1|MaskfowPhySet, BIT8);
	ewse if (eWFPath == WF_PATH_B)
		WfPiEnabwe = (u8)PHY_QuewyBBWeg(Adaptew, wFPGA0_XB_HSSIPawametew1|MaskfowPhySet, BIT8);

	if (WfPiEnabwe) {
		/*  Wead fwom BBweg8b8, 12 bits fow 8190, 20bits fow T65 WF */
		wetVawue = PHY_QuewyBBWeg(Adaptew, pPhyWeg->wfWSSIWeadBackPi|MaskfowPhySet, bWSSIWeadBackData);
	} ewse {
		/* Wead fwom BBweg8a0, 12 bits fow 8190, 20 bits fow T65 WF */
		wetVawue = PHY_QuewyBBWeg(Adaptew, pPhyWeg->wfWSSIWeadBack|MaskfowPhySet, bWSSIWeadBackData);
	}
	wetuwn wetVawue;

}

/**
 * phy_WFSewiawWwite_8723B - Wwite data to WF wegistew (page 8~).
 * @Adaptew:
 * @eWFPath:	Wadio path of A/B/C/D
 * @Offset:	The tawget addwess to be wead
 * @Data:	The new wegistew Data in the tawget bit position
 *			of the tawget to be wead
 *
 * .. Note::	Thewe awe thwee types of sewiaw opewations:
 *		1. Softwawe sewiaw wwite
 *		2. Hawdwawe WSSI-Wow Speed Sewiaw Intewface
 *		3. Hawdwawe HSSI-High speed
 *		sewiaw wwite. Dwivew need to impwement (1) and (2).
 *		This function is equaw to the combination of WF_WeadWeg() and  WFWSSIWead()
 *
 * .. Note::		  Fow WF8256 onwy
 *		 The totaw count of WTW8256(Zebwa4) wegistew is awound 36 bit it onwy empwoys
 *		 4-bit WF addwess. WTW8256 uses "wegistew mode contwow bit" (Weg00[12], Weg00[10])
 *		 to access wegistew addwess biggew than 0xf. See "Appendix-4 in PHY Configuwation
 *		 pwogwamming guide" fow mowe detaiws.
 *		 Thus, we define a sub-finction fow WTW8526 wegistew addwess convewsion
 *	       ===========================================================
 *		 Wegistew Mode		WegCTW[1]		WegCTW[0]		Note
 *							(Weg00[12])		(Weg00[10])
 *	       ===========================================================
 *		 Weg_Mode0				0				x			Weg 0 ~15(0x0 ~ 0xf)
 *	       ------------------------------------------------------------------
 *		 Weg_Mode1				1				0			Weg 16 ~30(0x1 ~ 0xf)
 *	       ------------------------------------------------------------------
 *		 Weg_Mode2				1				1			Weg 31 ~ 45(0x1 ~ 0xf)
 *	       ------------------------------------------------------------------
 *
 *2008/09/02	MH	Add 92S WF definition
 *
 *
 *
 */
static void phy_WFSewiawWwite_8723B(
	stwuct adaptew *Adaptew,
	enum wf_path eWFPath,
	u32 Offset,
	u32 Data
)
{
	u32 DataAndAddw = 0;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct bb_wegistew_def *pPhyWeg = &pHawData->PHYWegDef[eWFPath];
	u32 NewOffset;

	Offset &= 0xff;

	/*  */
	/*  Switch page fow 8256 WF IC */
	/*  */
	NewOffset = Offset;

	/*  */
	/*  Put wwite addw in [5:0]  and wwite data in [31:16] */
	/*  */
	DataAndAddw = ((NewOffset<<20) | (Data&0x000fffff)) & 0x0fffffff;	/*  T65 WF */
	/*  */
	/*  Wwite Opewation */
	/*  */
	PHY_SetBBWeg(Adaptew, pPhyWeg->wf3wiweOffset, bMaskDWowd, DataAndAddw);
}


/**
 * PHY_QuewyWFWeg_8723B - Quewy "Specific bits" to WF wegistew (page 8~).
 * @Adaptew:
 * @eWFPath:	Wadio path of A/B/C/D
 * @WegAddw:	The tawget addwess to be wead
 * @BitMask:	The tawget bit position in the tawget addwess
 *				to be wead
 *
 * Wetuwn:	Weadback vawue
 *
 * .. Note::	This function is equaw to "GetWFWegSetting" in PHY
 *			pwogwamming guide
 */
u32 PHY_QuewyWFWeg_8723B(
	stwuct adaptew *Adaptew,
	u8 eWFPath,
	u32 WegAddw,
	u32 BitMask
)
{
	u32 Owiginaw_Vawue, BitShift;

	Owiginaw_Vawue = phy_WFSewiawWead_8723B(Adaptew, eWFPath, WegAddw);
	BitShift =  phy_CawcuwateBitShift(BitMask);

	wetuwn (Owiginaw_Vawue & BitMask) >> BitShift;
}

/**
 * PHY_SetWFWeg_8723B - Wwite "Specific bits" to WF wegistew (page 8~).
 * @Adaptew:
 * @eWFPath:	Wadio path of A/B/C/D
 * @WegAddw:	The tawget addwess to be modified
 * @BitMask:	The tawget bit position in the tawget addwess
 *				to be modified
 * @Data:	The new wegistew Data in the tawget bit position
 *								of the tawget addwess
 *
 * .. Note::	This function is equaw to "PutWFWegSetting" in PHY
 *			pwogwamming guide.
 */
void PHY_SetWFWeg_8723B(
	stwuct adaptew *Adaptew,
	u8 eWFPath,
	u32 WegAddw,
	u32 BitMask,
	u32 Data
)
{
	u32 Owiginaw_Vawue, BitShift;

	/*  WF data is 12 bits onwy */
	if (BitMask != bWFWegOffsetMask) {
		Owiginaw_Vawue = phy_WFSewiawWead_8723B(Adaptew, eWFPath, WegAddw);
		BitShift =  phy_CawcuwateBitShift(BitMask);
		Data = ((Owiginaw_Vawue & (~BitMask)) | (Data<<BitShift));
	}

	phy_WFSewiawWwite_8723B(Adaptew, eWFPath, WegAddw, Data);
}


/*  */
/*  3. Initiaw MAC/BB/WF config by weading MAC/BB/WF txt. */
/*  */


/*-----------------------------------------------------------------------------
 * PHY_MACConfig8192C - Config MAC by headew fiwe ow pawametew fiwe.
 *
 * Wevised Histowy:
 *  When		Who		Wemawk
 *  08/12/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------
 */
s32 PHY_MACConfig8723B(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(Adaptew);

	ODM_WeadAndConfig_MP_8723B_MAC_WEG(&pHawData->odmpwiv);
	wetuwn _SUCCESS;
}

/**
 * phy_InitBBWFWegistewDefinition - Initiawize Wegistew definition offset fow
 *									Wadio Path A/B/C/D
 * @Adaptew:
 *
 * .. Note::		The initiawization vawue is constant and it shouwd nevew be changes
 */
static void phy_InitBBWFWegistewDefinition(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data		*pHawData = GET_HAW_DATA(Adaptew);

	/*  WF Intewface Sowwtwawe Contwow */
	pHawData->PHYWegDef[WF_PATH_A].wfintfs = wFPGA0_XAB_WFIntewfaceSW; /*  16 WSBs if wead 32-bit fwom 0x870 */
	pHawData->PHYWegDef[WF_PATH_B].wfintfs = wFPGA0_XAB_WFIntewfaceSW; /*  16 MSBs if wead 32-bit fwom 0x870 (16-bit fow 0x872) */

	/*  WF Intewface Output (and Enabwe) */
	pHawData->PHYWegDef[WF_PATH_A].wfintfo = wFPGA0_XA_WFIntewfaceOE; /*  16 WSBs if wead 32-bit fwom 0x860 */
	pHawData->PHYWegDef[WF_PATH_B].wfintfo = wFPGA0_XB_WFIntewfaceOE; /*  16 WSBs if wead 32-bit fwom 0x864 */

	/*  WF Intewface (Output and)  Enabwe */
	pHawData->PHYWegDef[WF_PATH_A].wfintfe = wFPGA0_XA_WFIntewfaceOE; /*  16 MSBs if wead 32-bit fwom 0x860 (16-bit fow 0x862) */
	pHawData->PHYWegDef[WF_PATH_B].wfintfe = wFPGA0_XB_WFIntewfaceOE; /*  16 MSBs if wead 32-bit fwom 0x864 (16-bit fow 0x866) */

	pHawData->PHYWegDef[WF_PATH_A].wf3wiweOffset = wFPGA0_XA_WSSIPawametew; /* WSSI Pawametew */
	pHawData->PHYWegDef[WF_PATH_B].wf3wiweOffset = wFPGA0_XB_WSSIPawametew;

	pHawData->PHYWegDef[WF_PATH_A].wfHSSIPawa2 = wFPGA0_XA_HSSIPawametew2;  /* wiwe contwow pawametew2 */
	pHawData->PHYWegDef[WF_PATH_B].wfHSSIPawa2 = wFPGA0_XB_HSSIPawametew2;  /* wiwe contwow pawametew2 */

	/*  Twansceivew Weadback WSSI/HSPI mode */
	pHawData->PHYWegDef[WF_PATH_A].wfWSSIWeadBack = wFPGA0_XA_WSSIWeadBack;
	pHawData->PHYWegDef[WF_PATH_B].wfWSSIWeadBack = wFPGA0_XB_WSSIWeadBack;
	pHawData->PHYWegDef[WF_PATH_A].wfWSSIWeadBackPi = TwansceivewA_HSPI_Weadback;
	pHawData->PHYWegDef[WF_PATH_B].wfWSSIWeadBackPi = TwansceivewB_HSPI_Weadback;

}

static int phy_BB8723b_Config_PawaFiwe(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	/*  Wead Tx Powew Wimit Fiwe */
	PHY_InitTxPowewWimit(Adaptew);
	if (
		Adaptew->wegistwypwiv.WegEnabweTxPowewWimit == 1 ||
		(Adaptew->wegistwypwiv.WegEnabweTxPowewWimit == 2 && pHawData->EEPWOMWeguwatowy == 1)
	) {
		ODM_ConfigWFWithHeadewFiwe(&pHawData->odmpwiv,
					   CONFIG_WF_TXPWW_WMT, 0);
	}

	/*  */
	/*  1. Wead PHY_WEG.TXT BB INIT!! */
	/*  */
	ODM_ConfigBBWithHeadewFiwe(&pHawData->odmpwiv, CONFIG_BB_PHY_WEG);

	/*  If EEPWOM ow EFUSE autowoad OK, We must config by PHY_WEG_PG.txt */
	PHY_InitTxPowewByWate(Adaptew);
	if (
		Adaptew->wegistwypwiv.WegEnabweTxPowewByWate == 1 ||
		(Adaptew->wegistwypwiv.WegEnabweTxPowewByWate == 2 && pHawData->EEPWOMWeguwatowy != 2)
	) {
		ODM_ConfigBBWithHeadewFiwe(&pHawData->odmpwiv,
					   CONFIG_BB_PHY_WEG_PG);

		if (pHawData->odmpwiv.PhyWegPgVawueType == PHY_WEG_PG_EXACT_VAWUE)
			PHY_TxPowewByWateConfiguwation(Adaptew);

		if (
			Adaptew->wegistwypwiv.WegEnabweTxPowewWimit == 1 ||
			(Adaptew->wegistwypwiv.WegEnabweTxPowewWimit == 2 && pHawData->EEPWOMWeguwatowy == 1)
		)
			PHY_ConvewtTxPowewWimitToPowewIndex(Adaptew);
	}

	/*  */
	/*  2. Wead BB AGC tabwe Initiawization */
	/*  */
	ODM_ConfigBBWithHeadewFiwe(&pHawData->odmpwiv, CONFIG_BB_AGC_TAB);

	wetuwn _SUCCESS;
}


int PHY_BBConfig8723B(stwuct adaptew *Adaptew)
{
	int	wtStatus = _SUCCESS;
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(Adaptew);
	u32 WegVaw;
	u8 CwystawCap;

	phy_InitBBWFWegistewDefinition(Adaptew);

	/*  Enabwe BB and WF */
	WegVaw = wtw_wead16(Adaptew, WEG_SYS_FUNC_EN);
	wtw_wwite16(Adaptew, WEG_SYS_FUNC_EN, (u16)(WegVaw|BIT13|BIT0|BIT1));

	wtw_wwite32(Adaptew, 0x948, 0x280);	/*  Othews use Antenna S1 */

	wtw_wwite8(Adaptew, WEG_WF_CTWW, WF_EN|WF_WSTB|WF_SDMWSTB);

	msweep(1);

	PHY_SetWFWeg(Adaptew, WF_PATH_A, 0x1, 0xfffff, 0x780);

	wtw_wwite8(Adaptew, WEG_SYS_FUNC_EN, FEN_PPWW|FEN_PCIEA|FEN_DIO_PCIE|FEN_BB_GWB_WSTn|FEN_BBWSTB);

	wtw_wwite8(Adaptew, WEG_AFE_XTAW_CTWW+1, 0x80);

	/*  */
	/*  Config BB and AGC */
	/*  */
	wtStatus = phy_BB8723b_Config_PawaFiwe(Adaptew);

	/*  0x2C[23:18] = 0x2C[17:12] = CwystawCap */
	CwystawCap = pHawData->CwystawCap & 0x3F;
	PHY_SetBBWeg(Adaptew, WEG_MAC_PHY_CTWW, 0xFFF000, (CwystawCap | (CwystawCap << 6)));

	wetuwn wtStatus;
}

static void phy_WCK_8723B(stwuct adaptew *Adaptew)
{
	PHY_SetWFWeg(Adaptew, WF_PATH_A, 0xB0, bWFWegOffsetMask, 0xDFBE0);
	PHY_SetWFWeg(Adaptew, WF_PATH_A, WF_CHNWBW, bWFWegOffsetMask, 0x8C01);
	mdeway(200);
	PHY_SetWFWeg(Adaptew, WF_PATH_A, 0xB0, bWFWegOffsetMask, 0xDFFE0);
}

int PHY_WFConfig8723B(stwuct adaptew *Adaptew)
{
	int wtStatus = _SUCCESS;

	/*  */
	/*  WF config */
	/*  */
	wtStatus = PHY_WF6052_Config8723B(Adaptew);

	phy_WCK_8723B(Adaptew);

	wetuwn wtStatus;
}

/**************************************************************************************************************
 *   Descwiption:
 *       The wow-wevew intewface to set TxAGC , cawwed by both MP and Nowmaw Dwivew.
 *
 *                                                                                    <20120830, Kowdan>
 **************************************************************************************************************/

void PHY_SetTxPowewIndex(
	stwuct adaptew *Adaptew,
	u32 PowewIndex,
	u8 WFPath,
	u8 Wate
)
{
	if (WFPath == WF_PATH_A || WFPath == WF_PATH_B) {
		switch (Wate) {
		case MGN_1M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_CCK1_Mcs32, bMaskByte1, PowewIndex);
			bweak;
		case MGN_2M:
			PHY_SetBBWeg(Adaptew, wTxAGC_B_CCK11_A_CCK2_11, bMaskByte1, PowewIndex);
			bweak;
		case MGN_5_5M:
			PHY_SetBBWeg(Adaptew, wTxAGC_B_CCK11_A_CCK2_11, bMaskByte2, PowewIndex);
			bweak;
		case MGN_11M:
			PHY_SetBBWeg(Adaptew, wTxAGC_B_CCK11_A_CCK2_11, bMaskByte3, PowewIndex);
			bweak;

		case MGN_6M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate18_06, bMaskByte0, PowewIndex);
			bweak;
		case MGN_9M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate18_06, bMaskByte1, PowewIndex);
			bweak;
		case MGN_12M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate18_06, bMaskByte2, PowewIndex);
			bweak;
		case MGN_18M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate18_06, bMaskByte3, PowewIndex);
			bweak;

		case MGN_24M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate54_24, bMaskByte0, PowewIndex);
			bweak;
		case MGN_36M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate54_24, bMaskByte1, PowewIndex);
			bweak;
		case MGN_48M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate54_24, bMaskByte2, PowewIndex);
			bweak;
		case MGN_54M:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Wate54_24, bMaskByte3, PowewIndex);
			bweak;

		case MGN_MCS0:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs03_Mcs00, bMaskByte0, PowewIndex);
			bweak;
		case MGN_MCS1:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs03_Mcs00, bMaskByte1, PowewIndex);
			bweak;
		case MGN_MCS2:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs03_Mcs00, bMaskByte2, PowewIndex);
			bweak;
		case MGN_MCS3:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs03_Mcs00, bMaskByte3, PowewIndex);
			bweak;

		case MGN_MCS4:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs07_Mcs04, bMaskByte0, PowewIndex);
			bweak;
		case MGN_MCS5:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs07_Mcs04, bMaskByte1, PowewIndex);
			bweak;
		case MGN_MCS6:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs07_Mcs04, bMaskByte2, PowewIndex);
			bweak;
		case MGN_MCS7:
			PHY_SetBBWeg(Adaptew, wTxAGC_A_Mcs07_Mcs04, bMaskByte3, PowewIndex);
			bweak;

		defauwt:
			bweak;
		}
	}
}

u8 PHY_GetTxPowewIndex(
	stwuct adaptew *padaptew,
	u8 WFPath,
	u8 Wate,
	enum channew_width BandWidth,
	u8 Channew
)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);
	s8 txPowew = 0, powewDiffByWate = 0, wimit = 0;

	txPowew = (s8) PHY_GetTxPowewIndexBase(padaptew, WFPath, Wate, BandWidth, Channew);
	powewDiffByWate = PHY_GetTxPowewByWate(padaptew, WF_PATH_A, Wate);

	wimit = phy_get_tx_pww_wmt(
		padaptew,
		padaptew->wegistwypwiv.WegPwwTbwSew,
		pHawData->CuwwentChannewBW,
		WFPath,
		Wate,
		pHawData->CuwwentChannew
	);

	powewDiffByWate = powewDiffByWate > wimit ? wimit : powewDiffByWate;
	txPowew += powewDiffByWate;

	txPowew += PHY_GetTxPowewTwackingOffset(padaptew, WFPath, Wate);

	if (txPowew > MAX_POWEW_INDEX)
		txPowew = MAX_POWEW_INDEX;

	wetuwn (u8) txPowew;
}

void PHY_SetTxPowewWevew8723B(stwuct adaptew *Adaptew, u8 Channew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;
	stwuct fat_t *pDM_FatTabwe = &pDM_Odm->DM_FatTabwe;
	u8 WFPath = WF_PATH_A;

	if (pHawData->AntDivCfg) {/*  antenna divewsity Enabwe */
		WFPath = ((pDM_FatTabwe->WxIdweAnt == MAIN_ANT) ? WF_PATH_A : WF_PATH_B);
	} ewse { /*  antenna divewsity disabwe */
		WFPath = pHawData->ant_path;
	}

	PHY_SetTxPowewWevewByPath(Adaptew, Channew, WFPath);
}

void PHY_GetTxPowewWevew8723B(stwuct adaptew *Adaptew, s32 *powewwevew)
{
}

static void phy_SetWegBW_8723B(
	stwuct adaptew *Adaptew, enum channew_width CuwwentBW
)
{
	u16 WegWfMod_BW, u2tmp = 0;
	WegWfMod_BW = wtw_wead16(Adaptew, WEG_TWXPTCW_CTW_8723B);

	switch (CuwwentBW) {
	case CHANNEW_WIDTH_20:
		wtw_wwite16(Adaptew, WEG_TWXPTCW_CTW_8723B, (WegWfMod_BW & 0xFE7F)); /*  BIT 7 = 0, BIT 8 = 0 */
		bweak;

	case CHANNEW_WIDTH_40:
		u2tmp = WegWfMod_BW | BIT7;
		wtw_wwite16(Adaptew, WEG_TWXPTCW_CTW_8723B, (u2tmp & 0xFEFF)); /*  BIT 7 = 1, BIT 8 = 0 */
		bweak;

	defauwt:
		bweak;
	}
}

static u8 phy_GetSecondawyChnw_8723B(stwuct adaptew *Adaptew)
{
	u8 SCSettingOf40 = 0, SCSettingOf20 = 0;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	if (pHawData->CuwwentChannewBW == CHANNEW_WIDTH_40) {
		if (pHawData->nCuw40MhzPwimeSC == HAW_PWIME_CHNW_OFFSET_UPPEW)
			SCSettingOf20 = HT_DATA_SC_20_UPPEW_OF_40MHZ;
		ewse if (pHawData->nCuw40MhzPwimeSC == HAW_PWIME_CHNW_OFFSET_WOWEW)
			SCSettingOf20 = HT_DATA_SC_20_WOWEW_OF_40MHZ;
	}

	wetuwn  (SCSettingOf40 << 4) | SCSettingOf20;
}

static void phy_PostSetBwMode8723B(stwuct adaptew *Adaptew)
{
	u8 SubChnwNum = 0;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);


	/* 3 Set Weg668 Weg440 BW */
	phy_SetWegBW_8723B(Adaptew, pHawData->CuwwentChannewBW);

	/* 3 Set Weg483 */
	SubChnwNum = phy_GetSecondawyChnw_8723B(Adaptew);
	wtw_wwite8(Adaptew, WEG_DATA_SC_8723B, SubChnwNum);

	/* 3 */
	/* 3<2>Set PHY wewated wegistew */
	/* 3 */
	switch (pHawData->CuwwentChannewBW) {
	/* 20 MHz channew*/
	case CHANNEW_WIDTH_20:
		PHY_SetBBWeg(Adaptew, wFPGA0_WFMOD, bWFMOD, 0x0);

		PHY_SetBBWeg(Adaptew, wFPGA1_WFMOD, bWFMOD, 0x0);

		PHY_SetBBWeg(Adaptew, wOFDM0_TxPseudoNoiseWgt, (BIT31|BIT30), 0x0);
		bweak;

	/* 40 MHz channew*/
	case CHANNEW_WIDTH_40:
		PHY_SetBBWeg(Adaptew, wFPGA0_WFMOD, bWFMOD, 0x1);

		PHY_SetBBWeg(Adaptew, wFPGA1_WFMOD, bWFMOD, 0x1);

		/*  Set Contwow channew to uppew ow wowew. These settings awe wequiwed onwy fow 40MHz */
		PHY_SetBBWeg(Adaptew, wCCK0_System, bCCKSideBand, (pHawData->nCuw40MhzPwimeSC>>1));

		PHY_SetBBWeg(Adaptew, wOFDM1_WSTF, 0xC00, pHawData->nCuw40MhzPwimeSC);

		PHY_SetBBWeg(Adaptew, 0x818, (BIT26|BIT27), (pHawData->nCuw40MhzPwimeSC == HAW_PWIME_CHNW_OFFSET_WOWEW) ? 2 : 1);
		bweak;
	defauwt:
		bweak;
	}

	/* 3<3>Set WF wewated wegistew */
	PHY_WF6052SetBandwidth8723B(Adaptew, pHawData->CuwwentChannewBW);
}

static void phy_SwChnw8723B(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);
	u8 channewToSW = pHawData->CuwwentChannew;

	if (pHawData->wf_chip == WF_PSEUDO_11N)
		wetuwn;
	pHawData->WfWegChnwVaw[0] = ((pHawData->WfWegChnwVaw[0] & 0xfffff00) | channewToSW);
	PHY_SetWFWeg(padaptew, WF_PATH_A, WF_CHNWBW, 0x3FF, pHawData->WfWegChnwVaw[0]);
	PHY_SetWFWeg(padaptew, WF_PATH_B, WF_CHNWBW, 0x3FF, pHawData->WfWegChnwVaw[0]);
}

static void phy_SwChnwAndSetBwMode8723B(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	if (Adaptew->bDwivewStopped || Adaptew->bSuwpwiseWemoved)
		wetuwn;

	if (pHawData->bSwChnw) {
		phy_SwChnw8723B(Adaptew);
		pHawData->bSwChnw = fawse;
	}

	if (pHawData->bSetChnwBW) {
		phy_PostSetBwMode8723B(Adaptew);
		pHawData->bSetChnwBW = fawse;
	}

	PHY_SetTxPowewWevew8723B(Adaptew, pHawData->CuwwentChannew);
}

static void PHY_HandweSwChnwAndSetBW8723B(
	stwuct adaptew *Adaptew,
	boow bSwitchChannew,
	boow bSetBandWidth,
	u8 ChannewNum,
	enum channew_width ChnwWidth,
	enum extchnw_offset ExtChnwOffsetOf40MHz,
	enum extchnw_offset ExtChnwOffsetOf80MHz,
	u8 CentewFwequencyIndex1
)
{
	/* static boow		bInitiawzed = fawse; */
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	u8 tmpChannew = pHawData->CuwwentChannew;
	enum channew_width tmpBW = pHawData->CuwwentChannewBW;
	u8 tmpnCuw40MhzPwimeSC = pHawData->nCuw40MhzPwimeSC;
	u8 tmpnCuw80MhzPwimeSC = pHawData->nCuw80MhzPwimeSC;
	u8 tmpCentewFwequencyIndex1 = pHawData->CuwwentCentewFwequencyIndex1;

	/* check is swchnw ow setbw */
	if (!bSwitchChannew && !bSetBandWidth)
		wetuwn;

	/* skip change fow channew ow bandwidth is the same */
	if (bSwitchChannew) {
		{
			if (HAW_IsWegawChannew(Adaptew, ChannewNum))
				pHawData->bSwChnw = twue;
		}
	}

	if (bSetBandWidth)
		pHawData->bSetChnwBW = twue;

	if (!pHawData->bSetChnwBW && !pHawData->bSwChnw)
		wetuwn;


	if (pHawData->bSwChnw) {
		pHawData->CuwwentChannew = ChannewNum;
		pHawData->CuwwentCentewFwequencyIndex1 = ChannewNum;
	}


	if (pHawData->bSetChnwBW) {
		pHawData->CuwwentChannewBW = ChnwWidth;
		pHawData->nCuw40MhzPwimeSC = ExtChnwOffsetOf40MHz;
		pHawData->nCuw80MhzPwimeSC = ExtChnwOffsetOf80MHz;
		pHawData->CuwwentCentewFwequencyIndex1 = CentewFwequencyIndex1;
	}

	/* Switch wowkitem ow set timew to do switch channew ow setbandwidth opewation */
	if ((!Adaptew->bDwivewStopped) && (!Adaptew->bSuwpwiseWemoved)) {
		phy_SwChnwAndSetBwMode8723B(Adaptew);
	} ewse {
		if (pHawData->bSwChnw) {
			pHawData->CuwwentChannew = tmpChannew;
			pHawData->CuwwentCentewFwequencyIndex1 = tmpChannew;
		}

		if (pHawData->bSetChnwBW) {
			pHawData->CuwwentChannewBW = tmpBW;
			pHawData->nCuw40MhzPwimeSC = tmpnCuw40MhzPwimeSC;
			pHawData->nCuw80MhzPwimeSC = tmpnCuw80MhzPwimeSC;
			pHawData->CuwwentCentewFwequencyIndex1 = tmpCentewFwequencyIndex1;
		}
	}
}

void PHY_SetBWMode8723B(
	stwuct adaptew *Adaptew,
	enum channew_width Bandwidth, /*  20M ow 40M */
	unsigned chaw Offset /*  Uppew, Wowew, ow Don't cawe */
)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	PHY_HandweSwChnwAndSetBW8723B(Adaptew, fawse, twue, pHawData->CuwwentChannew, Bandwidth, Offset, Offset, pHawData->CuwwentChannew);
}

/*  Caww aftew initiawization */
void PHY_SwChnw8723B(stwuct adaptew *Adaptew, u8 channew)
{
	PHY_HandweSwChnwAndSetBW8723B(Adaptew, twue, fawse, channew, 0, 0, 0, channew);
}

void PHY_SetSwChnwBWMode8723B(
	stwuct adaptew *Adaptew,
	u8 channew,
	enum channew_width Bandwidth,
	u8 Offset40,
	u8 Offset80
)
{
	PHY_HandweSwChnwAndSetBW8723B(Adaptew, twue, twue, channew, Bandwidth, Offset40, Offset80, channew);
}
