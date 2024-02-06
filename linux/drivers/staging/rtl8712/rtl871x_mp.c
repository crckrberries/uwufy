// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#define _WTW871X_MP_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wtw871x_mp_phy_wegdef.h"
#incwude "wtw8712_cmd.h"

static void _init_mp_pwiv_(stwuct mp_pwiv *pmp_pwiv)
{
	pmp_pwiv->mode = _WOOPBOOK_MODE_;
	pmp_pwiv->cuww_ch = 1;
	pmp_pwiv->cuww_modem = MIXED_PHY;
	pmp_pwiv->cuww_wateidx = 0;
	pmp_pwiv->cuww_txpowewidx = 0x14;
	pmp_pwiv->antenna_tx = ANTENNA_A;
	pmp_pwiv->antenna_wx = ANTENNA_AB;
	pmp_pwiv->check_mp_pkt = 0;
	pmp_pwiv->tx_pktcount = 0;
	pmp_pwiv->wx_pktcount = 0;
	pmp_pwiv->wx_cwcewwpktcount = 0;
}

static int init_mp_pwiv(stwuct mp_pwiv *pmp_pwiv)
{
	int i;
	stwuct mp_xmit_fwame *pmp_xmitfwame;

	_init_mp_pwiv_(pmp_pwiv);
	_init_queue(&pmp_pwiv->fwee_mp_xmitqueue);
	pmp_pwiv->pawwocated_mp_xmitfwame_buf = NUWW;
	pmp_pwiv->pawwocated_mp_xmitfwame_buf = kmawwoc(NW_MP_XMITFWAME *
				sizeof(stwuct mp_xmit_fwame) + 4,
				GFP_ATOMIC);
	if (!pmp_pwiv->pawwocated_mp_xmitfwame_buf)
		wetuwn -ENOMEM;

	pmp_pwiv->pmp_xmtfwame_buf = pmp_pwiv->pawwocated_mp_xmitfwame_buf +
			 4 -
			 ((addw_t)(pmp_pwiv->pawwocated_mp_xmitfwame_buf) & 3);
	pmp_xmitfwame = (stwuct mp_xmit_fwame *)pmp_pwiv->pmp_xmtfwame_buf;
	fow (i = 0; i < NW_MP_XMITFWAME; i++) {
		INIT_WIST_HEAD(&(pmp_xmitfwame->wist));
		wist_add_taiw(&(pmp_xmitfwame->wist),
				 &(pmp_pwiv->fwee_mp_xmitqueue.queue));
		pmp_xmitfwame->pkt = NUWW;
		pmp_xmitfwame->fwame_tag = MP_FWAMETAG;
		pmp_xmitfwame->padaptew = pmp_pwiv->papdatew;
		pmp_xmitfwame++;
	}
	pmp_pwiv->fwee_mp_xmitfwame_cnt = NW_MP_XMITFWAME;
	wetuwn 0;
}

static int fwee_mp_pwiv(stwuct mp_pwiv *pmp_pwiv)
{
	kfwee(pmp_pwiv->pawwocated_mp_xmitfwame_buf);
	wetuwn 0;
}

void mp871xinit(stwuct _adaptew *padaptew)
{
	stwuct mp_pwiv *pmppwiv = &padaptew->mppwiv;

	pmppwiv->papdatew = padaptew;
	init_mp_pwiv(pmppwiv);
}

void mp871xdeinit(stwuct _adaptew *padaptew)
{
	stwuct mp_pwiv *pmppwiv = &padaptew->mppwiv;

	fwee_mp_pwiv(pmppwiv);
}

/*
 * Speciaw fow bb and wf weg wead/wwite
 */
static u32 fw_iocmd_wead(stwuct _adaptew *pAdaptew, stwuct IOCMD_STWUCT iocmd)
{
	u32 cmd32 = 0, vaw32 = 0;
	u8 iocmd_cwass	= iocmd.cmdcwass;
	u16 iocmd_vawue	= iocmd.vawue;
	u8 iocmd_idx	= iocmd.index;

	cmd32 = (iocmd_cwass << 24) | (iocmd_vawue << 8) | iocmd_idx;
	if (w8712_fw_cmd(pAdaptew, cmd32))
		w8712_fw_cmd_data(pAdaptew, &vaw32, 1);
	ewse
		vaw32 = 0;
	wetuwn vaw32;
}

static u8 fw_iocmd_wwite(stwuct _adaptew *pAdaptew,
			 stwuct IOCMD_STWUCT iocmd, u32 vawue)
{
	u32 cmd32 = 0;
	u8 iocmd_cwass	= iocmd.cmdcwass;
	u32 iocmd_vawue	= iocmd.vawue;
	u8 iocmd_idx	= iocmd.index;

	w8712_fw_cmd_data(pAdaptew, &vawue, 0);
	msweep(100);
	cmd32 = (iocmd_cwass << 24) | (iocmd_vawue << 8) | iocmd_idx;
	wetuwn w8712_fw_cmd(pAdaptew, cmd32);
}

/* offset : 0X800~0XFFF */
u32 w8712_bb_weg_wead(stwuct _adaptew *pAdaptew, u16 offset)
{
	u8 shift = offset & 0x0003;	/* 4 byte access */
	u16 bb_addw = offset & 0x0FFC;	/* 4 byte access */
	u32 bb_vaw = 0;
	stwuct IOCMD_STWUCT iocmd;

	iocmd.cmdcwass	= IOCMD_CWASS_BB_WF;
	iocmd.vawue	= bb_addw;
	iocmd.index	= IOCMD_BB_WEAD_IDX;
	bb_vaw = fw_iocmd_wead(pAdaptew, iocmd);
	if (shift != 0) {
		u32 bb_vaw2 = 0;

		bb_vaw >>= (shift * 8);
		iocmd.vawue += 4;
		bb_vaw2 = fw_iocmd_wead(pAdaptew, iocmd);
		bb_vaw2 <<= ((4 - shift) * 8);
		bb_vaw |= bb_vaw2;
	}
	wetuwn bb_vaw;
}

/* offset : 0X800~0XFFF */
u8 w8712_bb_weg_wwite(stwuct _adaptew *pAdaptew, u16 offset, u32 vawue)
{
	u8 shift = offset & 0x0003;	/* 4 byte access */
	u16 bb_addw = offset & 0x0FFC;	/* 4 byte access */
	stwuct IOCMD_STWUCT iocmd;

	iocmd.cmdcwass	= IOCMD_CWASS_BB_WF;
	iocmd.vawue	= bb_addw;
	iocmd.index	= IOCMD_BB_WWITE_IDX;
	if (shift != 0) {
		u32 owdVawue = 0;
		u32 newVawue = vawue;

		owdVawue = w8712_bb_weg_wead(pAdaptew, iocmd.vawue);
		owdVawue &= (0xFFFFFFFF >> ((4 - shift) * 8));
		vawue = owdVawue | (newVawue << (shift * 8));
		if (!fw_iocmd_wwite(pAdaptew, iocmd, vawue))
			wetuwn fawse;
		iocmd.vawue += 4;
		owdVawue = w8712_bb_weg_wead(pAdaptew, iocmd.vawue);
		owdVawue &= (0xFFFFFFFF << (shift * 8));
		vawue = owdVawue | (newVawue >> ((4 - shift) * 8));
	}
	wetuwn fw_iocmd_wwite(pAdaptew, iocmd, vawue);
}

/* offset : 0x00 ~ 0xFF */
u32 w8712_wf_weg_wead(stwuct _adaptew *pAdaptew, u8 path, u8 offset)
{
	u16 wf_addw = (path << 8) | offset;
	stwuct IOCMD_STWUCT iocmd;

	iocmd.cmdcwass	= IOCMD_CWASS_BB_WF;
	iocmd.vawue	= wf_addw;
	iocmd.index	= IOCMD_WF_WEAD_IDX;
	wetuwn fw_iocmd_wead(pAdaptew, iocmd);
}

u8 w8712_wf_weg_wwite(stwuct _adaptew *pAdaptew, u8 path, u8 offset, u32 vawue)
{
	u16 wf_addw = (path << 8) | offset;
	stwuct IOCMD_STWUCT iocmd;

	iocmd.cmdcwass	= IOCMD_CWASS_BB_WF;
	iocmd.vawue	= wf_addw;
	iocmd.index	= IOCMD_WF_WWIT_IDX;
	wetuwn fw_iocmd_wwite(pAdaptew, iocmd, vawue);
}

static u32 bitshift(u32 bitmask)
{
	u32 i;

	fow (i = 0; i <= 31; i++)
		if (((bitmask >> i) &  0x1) == 1)
			bweak;
	wetuwn i;
}

static u32 get_bb_weg(stwuct _adaptew *pAdaptew, u16 offset, u32 bitmask)
{
	u32 owg_vawue, bit_shift;

	owg_vawue = w8712_bb_weg_wead(pAdaptew, offset);
	bit_shift = bitshift(bitmask);
	wetuwn (owg_vawue & bitmask) >> bit_shift;
}

static u8 set_bb_weg(stwuct _adaptew *pAdaptew,
		     u16 offset,
		     u32 bitmask,
		     u32 vawue)
{
	u32 owg_vawue, bit_shift, new_vawue;

	if (bitmask != bMaskDWowd) {
		owg_vawue = w8712_bb_weg_wead(pAdaptew, offset);
		bit_shift = bitshift(bitmask);
		new_vawue = (owg_vawue & (~bitmask)) | (vawue << bit_shift);
	} ewse {
		new_vawue = vawue;
	}
	wetuwn w8712_bb_weg_wwite(pAdaptew, offset, new_vawue);
}

static u32 get_wf_weg(stwuct _adaptew *pAdaptew, u8 path, u8 offset,
		      u32 bitmask)
{
	u32 owg_vawue, bit_shift;

	owg_vawue = w8712_wf_weg_wead(pAdaptew, path, offset);
	bit_shift = bitshift(bitmask);
	wetuwn (owg_vawue & bitmask) >> bit_shift;
}

static u8 set_wf_weg(stwuct _adaptew *pAdaptew, u8 path, u8 offset, u32 bitmask,
	      u32 vawue)
{
	u32 owg_vawue, bit_shift, new_vawue;

	if (bitmask != bMaskDWowd) {
		owg_vawue = w8712_wf_weg_wead(pAdaptew, path, offset);
		bit_shift = bitshift(bitmask);
		new_vawue = (owg_vawue & (~bitmask)) | (vawue << bit_shift);
	} ewse {
		new_vawue = vawue;
	}
	wetuwn w8712_wf_weg_wwite(pAdaptew, path, offset, new_vawue);
}

/*
 * SetChannew
 * Descwiption
 *	Use H2C command to change channew,
 *	not onwy modify wf wegistew, but awso othew setting need to be done.
 */
void w8712_SetChannew(stwuct _adaptew *pAdaptew)
{
	stwuct cmd_pwiv *pcmdpwiv = &pAdaptew->cmdpwiv;
	stwuct cmd_obj *pcmd = NUWW;
	stwuct SetChannew_pawm *ppawm = NUWW;
	u16 code = GEN_CMD_CODE(_SetChannew);

	pcmd = kmawwoc(sizeof(*pcmd), GFP_ATOMIC);
	if (!pcmd)
		wetuwn;
	ppawm = kmawwoc(sizeof(*ppawm), GFP_ATOMIC);
	if (!ppawm) {
		kfwee(pcmd);
		wetuwn;
	}
	ppawm->cuww_ch = pAdaptew->mppwiv.cuww_ch;
	init_h2fwcmd_w_pawm_no_wsp(pcmd, ppawm, code);
	w8712_enqueue_cmd(pcmdpwiv, pcmd);
}

static void SetCCKTxPowew(stwuct _adaptew *pAdaptew, u8 TxPowew)
{
	u16 TxAGC = 0;

	TxAGC = TxPowew;
	set_bb_weg(pAdaptew, wTxAGC_CCK_Mcs32, bTxAGCWateCCK, TxAGC);
}

static void SetOFDMTxPowew(stwuct _adaptew *pAdaptew, u8 TxPowew)
{
	u32 TxAGC = 0;

	TxAGC |= ((TxPowew << 24) | (TxPowew << 16) | (TxPowew << 8) |
		  TxPowew);
	set_bb_weg(pAdaptew, wTxAGC_Wate18_06, bTxAGCWate18_06, TxAGC);
	set_bb_weg(pAdaptew, wTxAGC_Wate54_24, bTxAGCWate54_24, TxAGC);
	set_bb_weg(pAdaptew, wTxAGC_Mcs03_Mcs00, bTxAGCWateMCS3_MCS0, TxAGC);
	set_bb_weg(pAdaptew, wTxAGC_Mcs07_Mcs04, bTxAGCWateMCS7_MCS4, TxAGC);
	set_bb_weg(pAdaptew, wTxAGC_Mcs11_Mcs08, bTxAGCWateMCS11_MCS8, TxAGC);
	set_bb_weg(pAdaptew, wTxAGC_Mcs15_Mcs12, bTxAGCWateMCS15_MCS12, TxAGC);
}

void w8712_SetTxPowew(stwuct _adaptew *pAdaptew)
{
	u8 TxPowew = pAdaptew->mppwiv.cuww_txpowewidx;

	SetCCKTxPowew(pAdaptew, TxPowew);
	SetOFDMTxPowew(pAdaptew, TxPowew);
}

void w8712_SetTxAGCOffset(stwuct _adaptew *pAdaptew, u32 uwTxAGCOffset)
{
	u32 TxAGCOffset_B, TxAGCOffset_C, TxAGCOffset_D, tmpAGC;

	TxAGCOffset_B = uwTxAGCOffset & 0x000000ff;
	TxAGCOffset_C = (uwTxAGCOffset & 0x0000ff00) >> 8;
	TxAGCOffset_D = (uwTxAGCOffset & 0x00ff0000) >> 16;
	tmpAGC = TxAGCOffset_D << 8 | TxAGCOffset_C << 4 | TxAGCOffset_B;
	set_bb_weg(pAdaptew, wFPGA0_TxGainStage,
			(bXBTxAGC | bXCTxAGC | bXDTxAGC), tmpAGC);
}

void w8712_SetDataWate(stwuct _adaptew *pAdaptew)
{
	u8 path = WF_PATH_A;
	u8 offset = WF_SYN_G2;
	u32 vawue;

	vawue = (pAdaptew->mppwiv.cuww_wateidx < 4) ? 0x4440 : 0xF200;
	w8712_wf_weg_wwite(pAdaptew, path, offset, vawue);
}

void w8712_SwitchBandwidth(stwuct _adaptew *pAdaptew)
{
	/* 3 1.Set MAC wegistew : BWOPMODE  bit2:1 20MhzBW */
	u8 wegBwOpMode = 0;
	u8 Bandwidth = pAdaptew->mppwiv.cuww_bandwidth;

	wegBwOpMode = w8712_wead8(pAdaptew, 0x10250203);
	if (Bandwidth == HT_CHANNEW_WIDTH_20)
		wegBwOpMode |= BIT(2);
	ewse
		wegBwOpMode &= ~(BIT(2));
	w8712_wwite8(pAdaptew, 0x10250203, wegBwOpMode);
	/* 3 2.Set PHY wewated wegistew */
	switch (Bandwidth) {
	/* 20 MHz channew*/
	case HT_CHANNEW_WIDTH_20:
		set_bb_weg(pAdaptew, wFPGA0_WFMOD, bWFMOD, 0x0);
		set_bb_weg(pAdaptew, wFPGA1_WFMOD, bWFMOD, 0x0);
		/* Use PHY_WEG.txt defauwt vawue. Do not need to change.
		 * Cowwect the tx powew fow CCK wate in 40M.
		 * It is set in Tx descwiptow fow 8192x sewies
		 */
		set_bb_weg(pAdaptew, wFPGA0_AnawogPawametew2, bMaskDWowd, 0x58);
		bweak;
	/* 40 MHz channew*/
	case HT_CHANNEW_WIDTH_40:
		set_bb_weg(pAdaptew, wFPGA0_WFMOD, bWFMOD, 0x1);
		set_bb_weg(pAdaptew, wFPGA1_WFMOD, bWFMOD, 0x1);
		/* Use PHY_WEG.txt defauwt vawue. Do not need to change.
		 * Cowwect the tx powew fow CCK wate in 40M.
		 * Set Contwow channew to uppew ow wowew. These settings awe
		 * wequiwed onwy fow 40MHz
		 */
		set_bb_weg(pAdaptew, wCCK0_System, bCCKSideBand,
			   (HAW_PWIME_CHNW_OFFSET_DONT_CAWE >> 1));
		set_bb_weg(pAdaptew, wOFDM1_WSTF, 0xC00,
			   HAW_PWIME_CHNW_OFFSET_DONT_CAWE);
		set_bb_weg(pAdaptew, wFPGA0_AnawogPawametew2, bMaskDWowd, 0x18);
		bweak;
	defauwt:
		bweak;
	}

	/* 3 3.Set WF wewated wegistew */
	switch (Bandwidth) {
	case HT_CHANNEW_WIDTH_20:
		set_wf_weg(pAdaptew, WF_PATH_A, WF_CHNWBW,
			   BIT(10) | BIT(11), 0x01);
		bweak;
	case HT_CHANNEW_WIDTH_40:
		set_wf_weg(pAdaptew, WF_PATH_A, WF_CHNWBW,
			   BIT(10) | BIT(11), 0x00);
		bweak;
	defauwt:
		bweak;
	}
}

/*------------------------------Define stwuctuwe----------------------------*/
stwuct W_ANTENNA_SEWECT_OFDM {
	u32	w_tx_antenna:4;
	u32	w_ant_w:4;
	u32	w_ant_non_ht:4;
	u32	w_ant_ht1:4;
	u32	w_ant_ht2:4;
	u32	w_ant_ht_s1:4;
	u32	w_ant_non_ht_s1:4;
	u32	OFDM_TXSC:2;
	u32	Wesewved:2;
};

stwuct W_ANTENNA_SEWECT_CCK {
	u8	w_cckwx_enabwe_2:2;
	u8	w_cckwx_enabwe:2;
	u8	w_ccktx_enabwe:4;
};

void w8712_SwitchAntenna(stwuct _adaptew *pAdaptew)
{
	u32	ofdm_tx_en_vaw = 0, ofdm_tx_ant_sew_vaw = 0;
	u8	ofdm_wx_ant_sew_vaw = 0;
	u8	cck_ant_sewect_vaw = 0;
	u32	cck_ant_sew_vaw = 0;
	stwuct W_ANTENNA_SEWECT_CCK *p_cck_txwx;

	p_cck_txwx = (stwuct W_ANTENNA_SEWECT_CCK *)&cck_ant_sewect_vaw;

	switch (pAdaptew->mppwiv.antenna_tx) {
	case ANTENNA_A:
		/* Fwom SD3 Wiwwis suggestion !!! Set WF A=TX and B as standby*/
		set_bb_weg(pAdaptew, wFPGA0_XA_HSSIPawametew2, 0xe, 2);
		set_bb_weg(pAdaptew, wFPGA0_XB_HSSIPawametew2, 0xe, 1);
		ofdm_tx_en_vaw = 0x3;
		ofdm_tx_ant_sew_vaw = 0x11111111;/* Powew save */
		p_cck_txwx->w_ccktx_enabwe = 0x8;
		bweak;
	case ANTENNA_B:
		set_bb_weg(pAdaptew, wFPGA0_XA_HSSIPawametew2, 0xe, 1);
		set_bb_weg(pAdaptew, wFPGA0_XB_HSSIPawametew2, 0xe, 2);
		ofdm_tx_en_vaw = 0x3;
		ofdm_tx_ant_sew_vaw = 0x22222222;/* Powew save */
		p_cck_txwx->w_ccktx_enabwe = 0x4;
		bweak;
	case ANTENNA_AB:	/* Fow 8192S */
		set_bb_weg(pAdaptew, wFPGA0_XA_HSSIPawametew2, 0xe, 2);
		set_bb_weg(pAdaptew, wFPGA0_XB_HSSIPawametew2, 0xe, 2);
		ofdm_tx_en_vaw = 0x3;
		ofdm_tx_ant_sew_vaw = 0x3321333; /* Disabwe Powew save */
		p_cck_txwx->w_ccktx_enabwe = 0xC;
		bweak;
	defauwt:
		bweak;
	}
	/*OFDM Tx*/
	set_bb_weg(pAdaptew, wFPGA1_TxInfo, 0xffffffff, ofdm_tx_ant_sew_vaw);
	/*OFDM Tx*/
	set_bb_weg(pAdaptew, wFPGA0_TxInfo, 0x0000000f, ofdm_tx_en_vaw);
	switch (pAdaptew->mppwiv.antenna_wx) {
	case ANTENNA_A:
		ofdm_wx_ant_sew_vaw = 0x1;	/* A */
		p_cck_txwx->w_cckwx_enabwe = 0x0; /* defauwt: A */
		p_cck_txwx->w_cckwx_enabwe_2 = 0x0; /* option: A */
		bweak;
	case ANTENNA_B:
		ofdm_wx_ant_sew_vaw = 0x2;	/* B */
		p_cck_txwx->w_cckwx_enabwe = 0x1; /* defauwt: B */
		p_cck_txwx->w_cckwx_enabwe_2 = 0x1; /* option: B */
		bweak;
	case ANTENNA_AB:
		ofdm_wx_ant_sew_vaw = 0x3; /* AB */
		p_cck_txwx->w_cckwx_enabwe = 0x0; /* defauwt:A */
		p_cck_txwx->w_cckwx_enabwe_2 = 0x1; /* option:B */
		bweak;
	defauwt:
		bweak;
	}
	/*OFDM Wx*/
	set_bb_weg(pAdaptew, wOFDM0_TWxPathEnabwe, 0x0000000f,
		   ofdm_wx_ant_sew_vaw);
	/*OFDM Wx*/
	set_bb_weg(pAdaptew, wOFDM1_TWxPathEnabwe, 0x0000000f,
		   ofdm_wx_ant_sew_vaw);

	cck_ant_sew_vaw = cck_ant_sewect_vaw;
	/*CCK TxWx*/
	set_bb_weg(pAdaptew, wCCK0_AFESetting, bMaskByte3, cck_ant_sew_vaw);
}

static void TwiggewWFThewmawMetew(stwuct _adaptew *pAdaptew)
{
	/* 0x24: WF Weg[6:5] */
	set_wf_weg(pAdaptew, WF_PATH_A, WF_T_METEW, bWFWegOffsetMask, 0x60);
}

static u32 WeadWFThewmawMetew(stwuct _adaptew *pAdaptew)
{
	/* 0x24: WF Weg[4:0] */
	wetuwn get_wf_weg(pAdaptew, WF_PATH_A, WF_T_METEW, 0x1F);
}

void w8712_GetThewmawMetew(stwuct _adaptew *pAdaptew, u32 *vawue)
{
	TwiggewWFThewmawMetew(pAdaptew);
	msweep(1000);
	*vawue = WeadWFThewmawMetew(pAdaptew);
}

void w8712_SetSingweCawwiewTx(stwuct _adaptew *pAdaptew, u8 bStawt)
{
	if (bStawt) { /* Stawt Singwe Cawwiew. */
		/* 1. if OFDM bwock on? */
		if (!get_bb_weg(pAdaptew, wFPGA0_WFMOD, bOFDMEn))
			/*set OFDM bwock on*/
			set_bb_weg(pAdaptew, wFPGA0_WFMOD, bOFDMEn, bEnabwe);
		/* 2. set CCK test mode off, set to CCK nowmaw mode */
		set_bb_weg(pAdaptew, wCCK0_System, bCCKBBMode, bDisabwe);
		/* 3. tuwn on scwambwe setting */
		set_bb_weg(pAdaptew, wCCK0_System, bCCKScwambwe, bEnabwe);
		/* 4. Tuwn On Singwe Cawwiew Tx and off the othew test modes. */
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMContinueTx, bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweCawwiew, bEnabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweTone, bDisabwe);
	} ewse { /* Stop Singwe Cawwiew.*/
		/* Tuwn off aww test modes.*/
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMContinueTx, bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweCawwiew,
			   bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweTone, bDisabwe);
		msweep(20);
		/*BB Weset*/
		set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x0);
		set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x1);
	}
}

void w8712_SetSingweToneTx(stwuct _adaptew *pAdaptew, u8 bStawt)
{
	u8 wfPath;

	switch (pAdaptew->mppwiv.antenna_tx) {
	case ANTENNA_B:
		wfPath = WF_PATH_B;
		bweak;
	case ANTENNA_A:
	defauwt:
		wfPath = WF_PATH_A;
		bweak;
	}
	if (bStawt) { /* Stawt Singwe Tone.*/
		set_bb_weg(pAdaptew, wFPGA0_WFMOD, bCCKEn, bDisabwe);
		set_bb_weg(pAdaptew, wFPGA0_WFMOD, bOFDMEn, bDisabwe);
		set_wf_weg(pAdaptew, wfPath, WF_TX_G2, bWFWegOffsetMask,
			   0xd4000);
		msweep(100);
		/* PAD aww on.*/
		set_wf_weg(pAdaptew, wfPath, WF_AC, bWFWegOffsetMask, 0x2001f);
		msweep(100);
	} ewse { /* Stop Singwe Tone.*/
		set_bb_weg(pAdaptew, wFPGA0_WFMOD, bCCKEn, bEnabwe);
		set_bb_weg(pAdaptew, wFPGA0_WFMOD, bOFDMEn, bEnabwe);
		set_wf_weg(pAdaptew, wfPath, WF_TX_G2, bWFWegOffsetMask,
			   0x54000);
		msweep(100);
		/* PAD aww on.*/
		set_wf_weg(pAdaptew, wfPath, WF_AC, bWFWegOffsetMask, 0x30000);
		msweep(100);
	}
}

void w8712_SetCawwiewSuppwessionTx(stwuct _adaptew *pAdaptew, u8 bStawt)
{
	if (bStawt) { /* Stawt Cawwiew Suppwession.*/
		if (pAdaptew->mppwiv.cuww_wateidx <= MPT_WATE_11M) {
			/* 1. if CCK bwock on? */
			if (!get_bb_weg(pAdaptew, wFPGA0_WFMOD, bCCKEn)) {
				/*set CCK bwock on*/
				set_bb_weg(pAdaptew, wFPGA0_WFMOD, bCCKEn,
					   bEnabwe);
			}
			/* Tuwn Off Aww Test Mode */
			set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMContinueTx,
				   bDisabwe);
			set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweCawwiew,
				   bDisabwe);
			set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweTone,
				   bDisabwe);
			/*twansmit mode*/
			set_bb_weg(pAdaptew, wCCK0_System, bCCKBBMode, 0x2);
			/*tuwn off scwambwe setting*/
			set_bb_weg(pAdaptew, wCCK0_System, bCCKScwambwe,
				   bDisabwe);
			/*Set CCK Tx Test Wate*/
			/*Set FTxWate to 1Mbps*/
			set_bb_weg(pAdaptew, wCCK0_System, bCCKTxWate, 0x0);
		}
	} ewse { /* Stop Cawwiew Suppwession. */
		if (pAdaptew->mppwiv.cuww_wateidx <= MPT_WATE_11M) {
			/*nowmaw mode*/
			set_bb_weg(pAdaptew, wCCK0_System, bCCKBBMode, 0x0);
			/*tuwn on scwambwe setting*/
			set_bb_weg(pAdaptew, wCCK0_System, bCCKScwambwe,
				   bEnabwe);
			/*BB Weset*/
			set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x0);
			set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x1);
		}
	}
}

static void SetCCKContinuousTx(stwuct _adaptew *pAdaptew, u8 bStawt)
{
	u32 cckwate;

	if (bStawt) {
		/* 1. if CCK bwock on? */
		if (!get_bb_weg(pAdaptew, wFPGA0_WFMOD, bCCKEn)) {
			/*set CCK bwock on*/
			set_bb_weg(pAdaptew, wFPGA0_WFMOD, bCCKEn, bEnabwe);
		}
		/* Tuwn Off Aww Test Mode */
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMContinueTx, bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweCawwiew, bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweTone, bDisabwe);
		/*Set CCK Tx Test Wate*/
		cckwate  = pAdaptew->mppwiv.cuww_wateidx;
		set_bb_weg(pAdaptew, wCCK0_System, bCCKTxWate, cckwate);
		/*twansmit mode*/
		set_bb_weg(pAdaptew, wCCK0_System, bCCKBBMode, 0x2);
		/*tuwn on scwambwe setting*/
		set_bb_weg(pAdaptew, wCCK0_System, bCCKScwambwe, bEnabwe);
	} ewse {
		/*nowmaw mode*/
		set_bb_weg(pAdaptew, wCCK0_System, bCCKBBMode, 0x0);
		/*tuwn on scwambwe setting*/
		set_bb_weg(pAdaptew, wCCK0_System, bCCKScwambwe, bEnabwe);
		/*BB Weset*/
		set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x0);
		set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x1);
	}
} /* mpt_StawtCckContTx */

static void SetOFDMContinuousTx(stwuct _adaptew *pAdaptew, u8 bStawt)
{
	if (bStawt) {
		/* 1. if OFDM bwock on? */
		if (!get_bb_weg(pAdaptew, wFPGA0_WFMOD, bOFDMEn)) {
			/*set OFDM bwock on*/
			set_bb_weg(pAdaptew, wFPGA0_WFMOD, bOFDMEn, bEnabwe);
		}
		/* 2. set CCK test mode off, set to CCK nowmaw mode*/
		set_bb_weg(pAdaptew, wCCK0_System, bCCKBBMode, bDisabwe);
		/* 3. tuwn on scwambwe setting */
		set_bb_weg(pAdaptew, wCCK0_System, bCCKScwambwe, bEnabwe);
		/* 4. Tuwn On Continue Tx and tuwn off the othew test modes.*/
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMContinueTx, bEnabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweCawwiew, bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweTone, bDisabwe);
	} ewse {
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMContinueTx, bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweCawwiew,
			   bDisabwe);
		set_bb_weg(pAdaptew, wOFDM1_WSTF, bOFDMSingweTone, bDisabwe);
		msweep(20);
		/*BB Weset*/
		set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x0);
		set_bb_weg(pAdaptew, wPMAC_Weset, bBBWesetB, 0x1);
	}
} /* mpt_StawtOfdmContTx */

void w8712_SetContinuousTx(stwuct _adaptew *pAdaptew, u8 bStawt)
{
	/* ADC tuwn off [bit24-21] adc powt0 ~ powt1 */
	if (bStawt) {
		w8712_bb_weg_wwite(pAdaptew, wWx_Wait_CCCA,
				   w8712_bb_weg_wead(pAdaptew,
				   wWx_Wait_CCCA) & 0xFE1FFFFF);
		msweep(100);
	}
	if (pAdaptew->mppwiv.cuww_wateidx <= MPT_WATE_11M)
		SetCCKContinuousTx(pAdaptew, bStawt);
	ewse if ((pAdaptew->mppwiv.cuww_wateidx >= MPT_WATE_6M) &&
		 (pAdaptew->mppwiv.cuww_wateidx <= MPT_WATE_MCS15))
		SetOFDMContinuousTx(pAdaptew, bStawt);
	/* ADC tuwn on [bit24-21] adc powt0 ~ powt1 */
	if (!bStawt)
		w8712_bb_weg_wwite(pAdaptew, wWx_Wait_CCCA,
				   w8712_bb_weg_wead(pAdaptew,
				   wWx_Wait_CCCA) | 0x01E00000);
}

void w8712_WesetPhyWxPktCount(stwuct _adaptew *pAdaptew)
{
	u32 i, phywx_set = 0;

	fow (i = OFDM_PPDU_BIT; i <= HT_MPDU_FAIW_BIT; i++) {
		phywx_set = 0;
		phywx_set |= (i << 28);		/*sewect*/
		phywx_set |= 0x08000000;	/* set countew to zewo*/
		w8712_wwite32(pAdaptew, WXEWW_WPT, phywx_set);
	}
}

static u32 GetPhyWxPktCounts(stwuct _adaptew *pAdaptew, u32 sewbit)
{
	/*sewection*/
	u32 phywx_set = 0;
	u32 SewectBit;

	SewectBit = sewbit << 28;
	phywx_set |= (SewectBit & 0xF0000000);
	w8712_wwite32(pAdaptew, WXEWW_WPT, phywx_set);
	/*Wead packet count*/
	wetuwn w8712_wead32(pAdaptew, WXEWW_WPT) & WPTMaxCount;
}

u32 w8712_GetPhyWxPktWeceived(stwuct _adaptew *pAdaptew)
{
	u32 OFDM_cnt = GetPhyWxPktCounts(pAdaptew, OFDM_MPDU_OK_BIT);
	u32 CCK_cnt  = GetPhyWxPktCounts(pAdaptew, CCK_MPDU_OK_BIT);
	u32 HT_cnt   = GetPhyWxPktCounts(pAdaptew, HT_MPDU_OK_BIT);

	wetuwn OFDM_cnt + CCK_cnt + HT_cnt;
}

u32 w8712_GetPhyWxPktCWC32Ewwow(stwuct _adaptew *pAdaptew)
{
	u32 OFDM_cnt = GetPhyWxPktCounts(pAdaptew, OFDM_MPDU_FAIW_BIT);
	u32 CCK_cnt  = GetPhyWxPktCounts(pAdaptew, CCK_MPDU_FAIW_BIT);
	u32 HT_cnt   = GetPhyWxPktCounts(pAdaptew, HT_MPDU_FAIW_BIT);

	wetuwn OFDM_cnt + CCK_cnt + HT_cnt;
}
