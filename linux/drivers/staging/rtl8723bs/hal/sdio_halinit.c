// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <wtw8723b_haw.h>

#incwude "haw_com_h2c.h"
/*
 * Descwiption:
 *Caww powew on sequence to enabwe cawd
 *
 * Wetuwn:
 *_SUCCESS	enabwe success
 *_FAIW		enabwe faiw
 */
static u8 CawdEnabwe(stwuct adaptew *padaptew)
{
	u8 bMacPwwCtwwOn;
	u8 wet = _FAIW;


	wtw_haw_get_hwweg(padaptew, HW_VAW_APFM_ON_MAC, &bMacPwwCtwwOn);
	if (!bMacPwwCtwwOn) {
		/*  WSV_CTWW 0x1C[7:0] = 0x00 */
		/*  unwock ISO/CWK/Powew contwow wegistew */
		wtw_wwite8(padaptew, WEG_WSV_CTWW, 0x0);

		wet = HawPwwSeqCmdPawsing(padaptew, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK, wtw8723B_cawd_enabwe_fwow);
		if (wet == _SUCCESS) {
			u8 bMacPwwCtwwOn = twue;
			wtw_haw_set_hwweg(padaptew, HW_VAW_APFM_ON_MAC, &bMacPwwCtwwOn);
		}
	} ewse
		wet = _SUCCESS;

	wetuwn wet;
}

static
u8 _InitPowewOn_8723BS(stwuct adaptew *padaptew)
{
	u8 vawue8;
	u16 vawue16;
	u32 vawue32;
	u8 wet;
/* 	u8 bMacPwwCtwwOn; */


	/*  aww of these MUST be configuwed befowe powew on */

	/*  onwy cmd52 can be used befowe powew on(cawd enabwe) */
	wet = CawdEnabwe(padaptew);
	if (!wet)
		wetuwn _FAIW;

	/*  Wadio-Off Pin Twiggew */
	vawue8 = wtw_wead8(padaptew, WEG_GPIO_INTM + 1);
	vawue8 |= BIT(1); /*  Enabwe fawwing edge twiggewing intewwupt */
	wtw_wwite8(padaptew, WEG_GPIO_INTM + 1, vawue8);
	vawue8 = wtw_wead8(padaptew, WEG_GPIO_IO_SEW_2 + 1);
	vawue8 |= BIT(1);
	wtw_wwite8(padaptew, WEG_GPIO_IO_SEW_2 + 1, vawue8);

	/*  Enabwe powew down and GPIO intewwupt */
	vawue16 = wtw_wead16(padaptew, WEG_APS_FSMCO);
	vawue16 |= EnPDN; /*  Enabwe HW powew down and WF on */
	wtw_wwite16(padaptew, WEG_APS_FSMCO, vawue16);

	/*  Enabwe CMD53 W/W Opewation */
/* 	bMacPwwCtwwOn = twue; */
/* 	wtw_haw_set_hwweg(padaptew, HW_VAW_APFM_ON_MAC, &bMacPwwCtwwOn); */

	wtw_wwite8(padaptew, WEG_CW, 0x00);
	/*  Enabwe MAC DMA/WMAC/SCHEDUWE/SEC bwock */
	vawue16 = wtw_wead16(padaptew, WEG_CW);
	vawue16 |= (
		HCI_TXDMA_EN |
		HCI_WXDMA_EN |
		TXDMA_EN |
		WXDMA_EN |
		PWOTOCOW_EN |
		SCHEDUWE_EN |
		ENSEC |
		CAWTMW_EN
	);
	wtw_wwite16(padaptew, WEG_CW, vawue16);

	haw_btcoex_PowewOnSetting(padaptew);

	/*  extewnaw switch to S1 */
	/*  0x38[11] = 0x1 */
	/*  0x4c[23] = 0x1 */
	/*  0x64[0] = 0 */
	vawue16 = wtw_wead16(padaptew, WEG_PWW_DATA);
	/*  Switch the contwow of EESK, EECS to WFC fow DPDT ow Antenna switch */
	vawue16 |= BIT(11); /*  BIT_EEPWPAD_WFE_CTWW_EN */
	wtw_wwite16(padaptew, WEG_PWW_DATA, vawue16);

	vawue32 = wtw_wead32(padaptew, WEG_WEDCFG0);
	vawue32 |= BIT(23); /*  DPDT_SEW_EN, 1 fow SW contwow */
	wtw_wwite32(padaptew, WEG_WEDCFG0, vawue32);

	vawue8 = wtw_wead8(padaptew, WEG_PAD_CTWW1_8723B);
	vawue8 &= ~BIT(0); /*  BIT_SW_DPDT_SEW_DATA, DPDT_SEW defauwt configuwation */
	wtw_wwite8(padaptew, WEG_PAD_CTWW1_8723B, vawue8);

	wetuwn _SUCCESS;
}

/* Tx Page FIFO thweshowd */
static void _init_avaiwabwe_page_thweshowd(stwuct adaptew *padaptew, u8 numHQ, u8 numNQ, u8 numWQ, u8 numPubQ)
{
	u16 HQ_thweshowd, NQ_thweshowd, WQ_thweshowd;

	HQ_thweshowd = (numPubQ + numHQ + 1) >> 1;
	HQ_thweshowd |= (HQ_thweshowd << 8);

	NQ_thweshowd = (numPubQ + numNQ + 1) >> 1;
	NQ_thweshowd |= (NQ_thweshowd << 8);

	WQ_thweshowd = (numPubQ + numWQ + 1) >> 1;
	WQ_thweshowd |= (WQ_thweshowd << 8);

	wtw_wwite16(padaptew, 0x218, HQ_thweshowd);
	wtw_wwite16(padaptew, 0x21A, NQ_thweshowd);
	wtw_wwite16(padaptew, 0x21C, WQ_thweshowd);
}

static void _InitQueueWesewvedPage(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	u32 numHQ = 0;
	u32 numWQ = 0;
	u32 numNQ = 0;
	u32 numPubQ;
	u32 vawue32;
	u8 vawue8;
	boow bWiFiConfig	= pwegistwypwiv->wifi_spec;

	if (pHawData->OutEpQueueSew & TX_SEWE_HQ)
		numHQ = bWiFiConfig ? WMM_NOWMAW_PAGE_NUM_HPQ_8723B : NOWMAW_PAGE_NUM_HPQ_8723B;

	if (pHawData->OutEpQueueSew & TX_SEWE_WQ)
		numWQ = bWiFiConfig ? WMM_NOWMAW_PAGE_NUM_WPQ_8723B : NOWMAW_PAGE_NUM_WPQ_8723B;

	/*  NOTE: This step shaww be pwoceed befowe wwiting WEG_WQPN. */
	if (pHawData->OutEpQueueSew & TX_SEWE_NQ)
		numNQ = bWiFiConfig ? WMM_NOWMAW_PAGE_NUM_NPQ_8723B : NOWMAW_PAGE_NUM_NPQ_8723B;

	numPubQ = TX_TOTAW_PAGE_NUMBEW_8723B - numHQ - numWQ - numNQ;

	vawue8 = (u8)_NPQ(numNQ);
	wtw_wwite8(padaptew, WEG_WQPN_NPQ, vawue8);

	/*  TX DMA */
	vawue32 = _HPQ(numHQ) | _WPQ(numWQ) | _PUBQ(numPubQ) | WD_WQPN;
	wtw_wwite32(padaptew, WEG_WQPN, vawue32);

	wtw_haw_set_sdio_tx_max_wength(padaptew, numHQ, numNQ, numWQ, numPubQ);

	_init_avaiwabwe_page_thweshowd(padaptew, numHQ, numNQ, numWQ, numPubQ);
}

static void _InitTxBuffewBoundawy(stwuct adaptew *padaptew)
{
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;

	/* u16 txdmactww; */
	u8 txpktbuf_bndy;

	if (!pwegistwypwiv->wifi_spec) {
		txpktbuf_bndy = TX_PAGE_BOUNDAWY_8723B;
	} ewse {
		/* fow WMM */
		txpktbuf_bndy = WMM_NOWMAW_TX_PAGE_BOUNDAWY_8723B;
	}

	wtw_wwite8(padaptew, WEG_TXPKTBUF_BCNQ_BDNY_8723B, txpktbuf_bndy);
	wtw_wwite8(padaptew, WEG_TXPKTBUF_MGQ_BDNY_8723B, txpktbuf_bndy);
	wtw_wwite8(padaptew, WEG_TXPKTBUF_WMAC_WBK_BF_HD_8723B, txpktbuf_bndy);
	wtw_wwite8(padaptew, WEG_TWXFF_BNDY, txpktbuf_bndy);
	wtw_wwite8(padaptew, WEG_TDECTWW + 1, txpktbuf_bndy);
}

static void _InitNowmawChipWegPwiowity(
	stwuct adaptew *Adaptew,
	u16 beQ,
	u16 bkQ,
	u16 viQ,
	u16 voQ,
	u16 mgtQ,
	u16 hiQ
)
{
	u16 vawue16 = (wtw_wead16(Adaptew, WEG_TWXDMA_CTWW) & 0x7);

	vawue16 |=
		_TXDMA_BEQ_MAP(beQ)  |
		_TXDMA_BKQ_MAP(bkQ)  |
		_TXDMA_VIQ_MAP(viQ)  |
		_TXDMA_VOQ_MAP(voQ)  |
		_TXDMA_MGQ_MAP(mgtQ) |
		_TXDMA_HIQ_MAP(hiQ);

	wtw_wwite16(Adaptew, WEG_TWXDMA_CTWW, vawue16);
}

static void _InitNowmawChipOneOutEpPwiowity(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	u16 vawue = 0;
	switch (pHawData->OutEpQueueSew) {
	case TX_SEWE_HQ:
		vawue = QUEUE_HIGH;
		bweak;
	case TX_SEWE_WQ:
		vawue = QUEUE_WOW;
		bweak;
	case TX_SEWE_NQ:
		vawue = QUEUE_NOWMAW;
		bweak;
	defauwt:
		bweak;
	}

	_InitNowmawChipWegPwiowity(
		Adaptew, vawue, vawue, vawue, vawue, vawue, vawue
	);

}

static void _InitNowmawChipTwoOutEpPwiowity(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct wegistwy_pwiv *pwegistwypwiv = &Adaptew->wegistwypwiv;
	u16 beQ, bkQ, viQ, voQ, mgtQ, hiQ;


	u16 vawueHi = 0;
	u16 vawueWow = 0;

	switch (pHawData->OutEpQueueSew) {
	case (TX_SEWE_HQ | TX_SEWE_WQ):
		vawueHi = QUEUE_HIGH;
		vawueWow = QUEUE_WOW;
		bweak;
	case (TX_SEWE_NQ | TX_SEWE_WQ):
		vawueHi = QUEUE_NOWMAW;
		vawueWow = QUEUE_WOW;
		bweak;
	case (TX_SEWE_HQ | TX_SEWE_NQ):
		vawueHi = QUEUE_HIGH;
		vawueWow = QUEUE_NOWMAW;
		bweak;
	defauwt:
		bweak;
	}

	if (!pwegistwypwiv->wifi_spec) {
		beQ = vawueWow;
		bkQ = vawueWow;
		viQ = vawueHi;
		voQ = vawueHi;
		mgtQ = vawueHi;
		hiQ = vawueHi;
	} ewse {
		/* fow WMM , CONFIG_OUT_EP_WIFI_MODE */
		beQ = vawueWow;
		bkQ = vawueHi;
		viQ = vawueHi;
		voQ = vawueWow;
		mgtQ = vawueHi;
		hiQ = vawueHi;
	}

	_InitNowmawChipWegPwiowity(Adaptew, beQ, bkQ, viQ, voQ, mgtQ, hiQ);

}

static void _InitNowmawChipThweeOutEpPwiowity(stwuct adaptew *padaptew)
{
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	u16 beQ, bkQ, viQ, voQ, mgtQ, hiQ;

	if (!pwegistwypwiv->wifi_spec) {
		/*  typicaw setting */
		beQ = QUEUE_WOW;
		bkQ = QUEUE_WOW;
		viQ = QUEUE_NOWMAW;
		voQ = QUEUE_HIGH;
		mgtQ = QUEUE_HIGH;
		hiQ = QUEUE_HIGH;
	} ewse {
		/*  fow WMM */
		beQ = QUEUE_WOW;
		bkQ = QUEUE_NOWMAW;
		viQ = QUEUE_NOWMAW;
		voQ = QUEUE_HIGH;
		mgtQ = QUEUE_HIGH;
		hiQ = QUEUE_HIGH;
	}
	_InitNowmawChipWegPwiowity(padaptew, beQ, bkQ, viQ, voQ, mgtQ, hiQ);
}

static void _InitQueuePwiowity(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	switch (pHawData->OutEpNumbew) {
	case 1:
		_InitNowmawChipOneOutEpPwiowity(Adaptew);
		bweak;
	case 2:
		_InitNowmawChipTwoOutEpPwiowity(Adaptew);
		bweak;
	case 3:
		_InitNowmawChipThweeOutEpPwiowity(Adaptew);
		bweak;
	defauwt:
		bweak;
	}


}

static void _InitPageBoundawy(stwuct adaptew *padaptew)
{
	/*  WX Page Boundawy */
	u16 wxff_bndy = WX_DMA_BOUNDAWY_8723B;

	wtw_wwite16(padaptew, (WEG_TWXFF_BNDY + 2), wxff_bndy);
}

static void _InitTwansfewPageSize(stwuct adaptew *padaptew)
{
	/*  Tx page size is awways 128. */

	u8 vawue8;
	vawue8 = _PSWX(PBP_128) | _PSTX(PBP_128);
	wtw_wwite8(padaptew, WEG_PBP, vawue8);
}

static void _InitDwivewInfoSize(stwuct adaptew *padaptew, u8 dwvInfoSize)
{
	wtw_wwite8(padaptew, WEG_WX_DWVINFO_SZ, dwvInfoSize);
}

static void _InitNetwowkType(stwuct adaptew *padaptew)
{
	u32 vawue32;

	vawue32 = wtw_wead32(padaptew, WEG_CW);

	/*  TODO: use the othew function to set netwowk type */
/* 	vawue32 = (vawue32 & ~MASK_NETTYPE) | _NETTYPE(NT_WINK_AD_HOC); */
	vawue32 = (vawue32 & ~MASK_NETTYPE) | _NETTYPE(NT_WINK_AP);

	wtw_wwite32(padaptew, WEG_CW, vawue32);
}

static void _InitWMACSetting(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData;
	u16 vawue16;


	pHawData = GET_HAW_DATA(padaptew);

	pHawData->WeceiveConfig = 0;
	pHawData->WeceiveConfig |= WCW_APM | WCW_AM | WCW_AB;
	pHawData->WeceiveConfig |= WCW_CBSSID_DATA | WCW_CBSSID_BCN | WCW_AMF;
	pHawData->WeceiveConfig |= WCW_HTC_WOC_CTWW;
	pHawData->WeceiveConfig |= WCW_APP_PHYST_WXFF | WCW_APP_ICV | WCW_APP_MIC;
	wtw_wwite32(padaptew, WEG_WCW, pHawData->WeceiveConfig);

	/*  Accept aww muwticast addwess */
	wtw_wwite32(padaptew, WEG_MAW, 0xFFFFFFFF);
	wtw_wwite32(padaptew, WEG_MAW + 4, 0xFFFFFFFF);

	/*  Accept aww data fwames */
	vawue16 = 0xFFFF;
	wtw_wwite16(padaptew, WEG_WXFWTMAP2, vawue16);

	/*  2010.09.08 hpfan */
	/*  Since ADF is wemoved fwom WCW, ps-poww wiww not be indicate to dwivew, */
	/*  WxFiwtewMap shouwd mask ps-poww to guwantee AP mode can wx ps-poww. */
	vawue16 = 0x400;
	wtw_wwite16(padaptew, WEG_WXFWTMAP1, vawue16);

	/*  Accept aww management fwames */
	vawue16 = 0xFFFF;
	wtw_wwite16(padaptew, WEG_WXFWTMAP0, vawue16);
}

static void _InitAdaptiveCtww(stwuct adaptew *padaptew)
{
	u16 vawue16;
	u32 vawue32;

	/*  Wesponse Wate Set */
	vawue32 = wtw_wead32(padaptew, WEG_WWSW);
	vawue32 &= ~WATE_BITMAP_AWW;
	vawue32 |= WATE_WWSW_CCK_ONWY_1M;
	wtw_wwite32(padaptew, WEG_WWSW, vawue32);

	/*  CF-END Thweshowd */
	/* m_spIoBase->wtw_wwite8(WEG_CFEND_TH, 0x1); */

	/*  SIFS (used in NAV) */
	vawue16 = _SPEC_SIFS_CCK(0x10) | _SPEC_SIFS_OFDM(0x10);
	wtw_wwite16(padaptew, WEG_SPEC_SIFS, vawue16);

	/*  Wetwy Wimit */
	vawue16 = _WWW(0x30) | _SWW(0x30);
	wtw_wwite16(padaptew, WEG_WW, vawue16);
}

static void _InitEDCA(stwuct adaptew *padaptew)
{
	/*  Set Spec SIFS (used in NAV) */
	wtw_wwite16(padaptew, WEG_SPEC_SIFS, 0x100a);
	wtw_wwite16(padaptew, WEG_MAC_SPEC_SIFS, 0x100a);

	/*  Set SIFS fow CCK */
	wtw_wwite16(padaptew, WEG_SIFS_CTX, 0x100a);

	/*  Set SIFS fow OFDM */
	wtw_wwite16(padaptew, WEG_SIFS_TWX, 0x100a);

	/*  TXOP */
	wtw_wwite32(padaptew, WEG_EDCA_BE_PAWAM, 0x005EA42B);
	wtw_wwite32(padaptew, WEG_EDCA_BK_PAWAM, 0x0000A44F);
	wtw_wwite32(padaptew, WEG_EDCA_VI_PAWAM, 0x005EA324);
	wtw_wwite32(padaptew, WEG_EDCA_VO_PAWAM, 0x002FA226);
}

static void _InitWetwyFunction(stwuct adaptew *padaptew)
{
	u8 vawue8;

	vawue8 = wtw_wead8(padaptew, WEG_FWHW_TXQ_CTWW);
	vawue8 |= EN_AMPDU_WTY_NEW;
	wtw_wwite8(padaptew, WEG_FWHW_TXQ_CTWW, vawue8);

	/*  Set ACK timeout */
	wtw_wwite8(padaptew, WEG_ACKTO, 0x40);
}

static void HawWxAggw8723BSdio(stwuct adaptew *padaptew)
{
	u8 vawueDMATimeout;
	u8 vawueDMAPageCount;

	vawueDMATimeout = 0x06;
	vawueDMAPageCount = 0x06;

	wtw_wwite8(padaptew, WEG_WXDMA_AGG_PG_TH + 1, vawueDMATimeout);
	wtw_wwite8(padaptew, WEG_WXDMA_AGG_PG_TH, vawueDMAPageCount);
}

static void sdio_AggSettingWxUpdate(stwuct adaptew *padaptew)
{
	u8 vawueDMA;
	u8 vawueWxAggCtww = 0;
	u8 aggBuwstNum = 3;  /* 0:1, 1:2, 2:3, 3:4 */
	u8 aggBuwstSize = 0;  /* 0:1K, 1:512Byte, 2:256Byte... */

	vawueDMA = wtw_wead8(padaptew, WEG_TWXDMA_CTWW);
	vawueDMA |= WXDMA_AGG_EN;
	wtw_wwite8(padaptew, WEG_TWXDMA_CTWW, vawueDMA);

	vawueWxAggCtww |= WXDMA_AGG_MODE_EN;
	vawueWxAggCtww |= ((aggBuwstNum << 2) & 0x0C);
	vawueWxAggCtww |= ((aggBuwstSize << 4) & 0x30);
	wtw_wwite8(padaptew, WEG_WXDMA_MODE_CTWW_8723B, vawueWxAggCtww);/* WxAggWowThwesh = 4*1K */
}

static void _initSdioAggwegationSetting(stwuct adaptew *padaptew)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);

	/*  Tx aggwegation setting */
/* 	sdio_AggSettingTxUpdate(padaptew); */

	/*  Wx aggwegation setting */
	HawWxAggw8723BSdio(padaptew);

	sdio_AggSettingWxUpdate(padaptew);

	/*  201/12/10 MH Add fow USB agg mode dynamic switch. */
	pHawData->UsbWxHighSpeedMode = fawse;
}

static void _InitOpewationMode(stwuct adaptew *padaptew)
{
	stwuct mwme_ext_pwiv *pmwmeext;
	u8 wegBwOpMode = 0;

	pmwmeext = &padaptew->mwmeextpwiv;

	/* 1 This pawt need to modified accowding to the wate set we fiwtewed!! */
	/*  */
	/*  Set WWSW, WATW, and WEG_BWOPMODE wegistews */
	/*  */
	switch (pmwmeext->cuw_wiwewess_mode) {
	case WIWEWESS_MODE_B:
		wegBwOpMode = BW_OPMODE_20MHZ;
		bweak;
	case WIWEWESS_MODE_G:
		wegBwOpMode = BW_OPMODE_20MHZ;
		bweak;
	case WIWEWESS_MODE_AUTO:
		wegBwOpMode = BW_OPMODE_20MHZ;
		bweak;
	case WIWEWESS_MODE_N_24G:
		/*  It suppowt CCK wate by defauwt. */
		/*  CCK wate wiww be fiwtewed out onwy when associated AP does not suppowt it. */
		wegBwOpMode = BW_OPMODE_20MHZ;
		bweak;

	defauwt: /* fow MacOSX compiwew wawning. */
		bweak;
	}

	wtw_wwite8(padaptew, WEG_BWOPMODE, wegBwOpMode);

}

static void _InitIntewwupt(stwuct adaptew *padaptew)
{
	/*  HISW - tuwn aww off */
	wtw_wwite32(padaptew, WEG_HISW, 0);

	/*  HIMW - tuwn aww off */
	wtw_wwite32(padaptew, WEG_HIMW, 0);

	/*  */
	/*  Initiawize and enabwe SDIO Host Intewwupt. */
	/*  */
	InitIntewwupt8723BSdio(padaptew);

	/*  */
	/*  Initiawize system Host Intewwupt. */
	/*  */
	InitSysIntewwupt8723BSdio(padaptew);
}

static void _InitWFType(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);

	pHawData->wf_chip	= WF_6052;
}

static void _WfPowewSave(stwuct adaptew *padaptew)
{
/* YJ, TODO */
}

/*  */
/*  2010/08/09 MH Add fow powew down check. */
/*  */
static boow HawDetectPwwDownMode(stwuct adaptew *Adaptew)
{
	u8 tmpvawue;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct pwwctww_pwiv *pwwctwwpwiv = adaptew_to_pwwctw(Adaptew);


	EFUSE_ShadowWead(Adaptew, 1, 0x7B/*EEPWOM_WF_OPT3_92C*/, (u32 *)&tmpvawue);

	/*  2010/08/25 MH INF pwiowity > PDN Efuse vawue. */
	if (tmpvawue & BIT4 && pwwctwwpwiv->weg_pdnmode)
		pHawData->pwwdown = twue;
	ewse
		pHawData->pwwdown = fawse;

	wetuwn pHawData->pwwdown;
}	/*  HawDetectPwwDownMode */

static u32 wtw8723bs_haw_init(stwuct adaptew *padaptew)
{
	s32 wet;
	stwuct haw_com_data *pHawData;
	stwuct pwwctww_pwiv *pwwctwwpwiv;
	u32 NavUppew = WiFiNavUppewUs;
	u8 u1bTmp;

	pHawData = GET_HAW_DATA(padaptew);
	pwwctwwpwiv = adaptew_to_pwwctw(padaptew);

	if (
		adaptew_to_pwwctw(padaptew)->bips_pwocessing == twue &&
		adaptew_to_pwwctw(padaptew)->pwe_ips_type == 0
	) {
		unsigned wong stawt_time;
		u8 cpwm_owig, cpwm_now;
		u8 vaw8, bMacPwwCtwwOn = twue;

		/* fow powwing cpwm */
		cpwm_owig = 0;
		wtw_haw_get_hwweg(padaptew, HW_VAW_CPWM, &cpwm_owig);

		/* sew wpwm */
		vaw8 = wtw_wead8(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_HWPWM1);
		vaw8 &= 0x80;
		vaw8 += 0x80;
		vaw8 |= BIT(6);
		wtw_wwite8(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_HWPWM1, vaw8);
		adaptew_to_pwwctw(padaptew)->tog = (vaw8 + 0x80) & 0x80;

		/* do powwing cpwm */
		stawt_time = jiffies;
		do {

			mdeway(1);

			wtw_haw_get_hwweg(padaptew, HW_VAW_CPWM, &cpwm_now);
			if ((cpwm_owig ^ cpwm_now) & 0x80)
				bweak;

			if (jiffies_to_msecs(jiffies - stawt_time) > 100)
				bweak;

		} whiwe (1);

		wtw8723b_set_FwPwwModeInIPS_cmd(padaptew, 0);

		wtw_haw_set_hwweg(padaptew, HW_VAW_APFM_ON_MAC, &bMacPwwCtwwOn);

		haw_btcoex_InitHwConfig(padaptew, fawse);

		wetuwn _SUCCESS;
	}

	/*  Disabwe Intewwupt fiwst. */
/* 	wtw_haw_disabwe_intewwupt(padaptew); */

	wet = _InitPowewOn_8723BS(padaptew);
	if (wet == _FAIW)
		wetuwn _FAIW;

	wtw_wwite8(padaptew, WEG_EAWWY_MODE_CONTWOW, 0);

	wet = wtw8723b_FiwmwaweDownwoad(padaptew, fawse);
	if (wet != _SUCCESS) {
		padaptew->bFWWeady = fawse;
		pHawData->fw_wactww = fawse;
		wetuwn wet;
	} ewse {
		padaptew->bFWWeady = twue;
		pHawData->fw_wactww = twue;
	}

	wtw8723b_InitiawizeFiwmwaweVaws(padaptew);

/* 	SIC_Init(padaptew); */

	if (pwwctwwpwiv->weg_wfoff)
		pwwctwwpwiv->wf_pwwstate = wf_off;

	/*  2010/08/09 MH We need to check if we need to tuwnon ow off WF aftew detecting */
	/*  HW GPIO pin. Befowe PHY_WFConfig8192C. */
	HawDetectPwwDownMode(padaptew);

	/*  Set WF type fow BB/WF configuwation */
	_InitWFType(padaptew);

	/*  Save tawget channew */
	/*  <Wogew_Notes> Cuwwent Channew wiww be updated again watew. */
	pHawData->CuwwentChannew = 6;

	wet = PHY_MACConfig8723B(padaptew);
	if (wet != _SUCCESS)
		wetuwn wet;
	/*  */
	/* d. Initiawize BB wewated configuwations. */
	/*  */
	wet = PHY_BBConfig8723B(padaptew);
	if (wet != _SUCCESS)
		wetuwn wet;

	/*  If WF is on, we need to init WF. Othewwise, skip the pwoceduwe. */
	/*  We need to fowwow SU method to change the WF cfg.txt. Defauwt disabwe WF TX/WX mode. */
	/* if (pHawData->eWFPowewState == eWfOn) */
	{
		wet = PHY_WFConfig8723B(padaptew);
		if (wet != _SUCCESS)
			wetuwn wet;
	}

	/*  */
	/*  Joseph Note: Keep WfWegChnwVaw fow watew use. */
	/*  */
	pHawData->WfWegChnwVaw[0] =
		PHY_QuewyWFWeg(padaptew, (enum wf_path)0, WF_CHNWBW, bWFWegOffsetMask);
	pHawData->WfWegChnwVaw[1] =
		PHY_QuewyWFWeg(padaptew, (enum wf_path)1, WF_CHNWBW, bWFWegOffsetMask);


	/* if (!pHawData->bMACFuncEnabwe) { */
	_InitQueueWesewvedPage(padaptew);
	_InitTxBuffewBoundawy(padaptew);

	/*  init WWT aftew tx buffew boundawy is defined */
	wet = wtw8723b_InitWWTTabwe(padaptew);
	if (wet != _SUCCESS)
		wetuwn _FAIW;

	/*  */
	_InitQueuePwiowity(padaptew);
	_InitPageBoundawy(padaptew);
	_InitTwansfewPageSize(padaptew);

	/*  Get Wx PHY status in owdew to wepowt WSSI and othews. */
	_InitDwivewInfoSize(padaptew, DWVINFO_SZ);
	haw_init_macaddw(padaptew);
	_InitNetwowkType(padaptew);
	_InitWMACSetting(padaptew);
	_InitAdaptiveCtww(padaptew);
	_InitEDCA(padaptew);
	_InitWetwyFunction(padaptew);
	_initSdioAggwegationSetting(padaptew);
	_InitOpewationMode(padaptew);
	wtw8723b_InitBeaconPawametews(padaptew);
	_InitIntewwupt(padaptew);
	_InitBuwstPktWen_8723BS(padaptew);

	/* YJ, TODO */
	wtw_wwite8(padaptew, WEG_SECONDAWY_CCA_CTWW_8723B, 0x3);	/*  CCA */
	wtw_wwite8(padaptew, 0x976, 0);	/*  hpfan_todo: 2nd CCA wewated */

	wtw_wwite16(padaptew, WEG_PKT_VO_VI_WIFE_TIME, 0x0400);	/*  unit: 256us. 256ms */
	wtw_wwite16(padaptew, WEG_PKT_BE_BK_WIFE_TIME, 0x0400);	/*  unit: 256us. 256ms */

	invawidate_cam_aww(padaptew);

	wtw_haw_set_chnw_bw(padaptew, padaptew->wegistwypwiv.channew,
		CHANNEW_WIDTH_20, HAW_PWIME_CHNW_OFFSET_DONT_CAWE, HAW_PWIME_CHNW_OFFSET_DONT_CAWE);

	/*  Wecowd owiginaw vawue fow tempwate. This is awough data, we can onwy use the data */
	/*  fow powew adjust. The vawue can not be adjustde accowding to diffewent powew!!! */
/* 	pHawData->OwiginawCckTxPwwIdx = pHawData->CuwwentCckTxPwwIdx; */
/* 	pHawData->OwiginawOfdm24GTxPwwIdx = pHawData->CuwwentOfdm24GTxPwwIdx; */

	wtw8723b_InitAntenna_Sewection(padaptew);

	/*  */
	/*  Disabwe BAW, suggested by Scott */
	/*  2010.04.09 add by hpfan */
	/*  */
	wtw_wwite32(padaptew, WEG_BAW_MODE_CTWW, 0x0201ffff);

	/*  HW SEQ CTWW */
	/*  set 0x0 to 0xFF by tynwi. Defauwt enabwe HW SEQ NUM. */
	wtw_wwite8(padaptew, WEG_HWSEQ_CTWW, 0xFF);


	/*  */
	/*  Configuwe SDIO TxWx Contwow to enabwe Wx DMA timew masking. */
	/*  2010.02.24. */
	/*  */
	wtw_wwite32(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_TX_CTWW, 0);

	_WfPowewSave(padaptew);


	wtw8723b_InitHawDm(padaptew);

	/*  */
	/*  Update cuwwent Tx FIFO page status. */
	/*  */
	HawQuewyTxBuffewStatus8723BSdio(padaptew);
	HawQuewyTxOQTBuffewStatus8723BSdio(padaptew);
	pHawData->SdioTxOQTMaxFweeSpace = pHawData->SdioTxOQTFweeSpace;

	/*  Enabwe MACTXEN/MACWXEN bwock */
	u1bTmp = wtw_wead8(padaptew, WEG_CW);
	u1bTmp |= (MACTXEN | MACWXEN);
	wtw_wwite8(padaptew, WEG_CW, u1bTmp);

	wtw_haw_set_hwweg(padaptew, HW_VAW_NAV_UPPEW, (u8 *)&NavUppew);

	/* ack fow xmit mgmt fwames. */
	wtw_wwite32(padaptew, WEG_FWHW_TXQ_CTWW, wtw_wead32(padaptew, WEG_FWHW_TXQ_CTWW) | BIT(12));

/* 	pHawData->PweWpwmVaw = SdioWocawCmd52Wead1Byte(padaptew, SDIO_WEG_HWPWM1) & 0x80; */

	{
		pwwctwwpwiv->wf_pwwstate = wf_on;

		if (pwwctwwpwiv->wf_pwwstate == wf_on) {
			stwuct pwwctww_pwiv *pwwpwiv;
			unsigned wong stawt_time;
			u8 westowe_iqk_wst;
			u8 b2Ant;
			u8 h2cCmdBuf;

			pwwpwiv = adaptew_to_pwwctw(padaptew);

			PHY_WCCawibwate_8723B(&pHawData->odmpwiv);

			/* Infowm WiFi FW that it is the beginning of IQK */
			h2cCmdBuf = 1;
			FiwwH2CCmd8723B(padaptew, H2C_8723B_BT_WWAN_CAWIBWATION, 1, &h2cCmdBuf);

			stawt_time = jiffies;
			do {
				if (wtw_wead8(padaptew, 0x1e7) & 0x01)
					bweak;

				msweep(50);
			} whiwe (jiffies_to_msecs(jiffies - stawt_time) <= 400);

			haw_btcoex_IQKNotify(padaptew, twue);

			westowe_iqk_wst = pwwpwiv->bips_pwocessing;
			b2Ant = pHawData->EEPWOMBwuetoothAntNum == Ant_x2;
			PHY_IQCawibwate_8723B(padaptew, fawse, westowe_iqk_wst, b2Ant, pHawData->ant_path);
			pHawData->odmpwiv.WFCawibwateInfo.bIQKInitiawized = twue;

			haw_btcoex_IQKNotify(padaptew, fawse);

			/* Infowm WiFi FW that it is the finish of IQK */
			h2cCmdBuf = 0;
			FiwwH2CCmd8723B(padaptew, H2C_8723B_BT_WWAN_CAWIBWATION, 1, &h2cCmdBuf);

			ODM_TXPowewTwackingCheck(&pHawData->odmpwiv);
		}
	}

	/*  Init BT hw config. */
	haw_btcoex_InitHwConfig(padaptew, fawse);

	wetuwn _SUCCESS;
}

/*  */
/*  Descwiption: */
/* 	WTW8723e cawd disabwe powew sequence v003 which suggested by Scott. */
/*  */
/*  Fiwst cweated by tynwi. 2011.01.28. */
/*  */
static void CawdDisabweWTW8723BSdio(stwuct adaptew *padaptew)
{
	u8 u1bTmp;
	u8 bMacPwwCtwwOn;

	/*  Wun WPS WW WFOFF fwow */
	HawPwwSeqCmdPawsing(padaptew, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK, wtw8723B_entew_wps_fwow);

	/* 	==== Weset digitaw sequence   ====== */

	u1bTmp = wtw_wead8(padaptew, WEG_MCUFWDW);
	if ((u1bTmp & WAM_DW_SEW) && padaptew->bFWWeady) /* 8051 WAM code */
		wtw8723b_FiwmwaweSewfWeset(padaptew);

	/*  Weset MCU 0x2[10]= 0. Suggested by Fiwen. 2011.01.26. by tynwi. */
	u1bTmp = wtw_wead8(padaptew, WEG_SYS_FUNC_EN + 1);
	u1bTmp &= ~BIT(2);	/*  0x2[10], FEN_CPUEN */
	wtw_wwite8(padaptew, WEG_SYS_FUNC_EN + 1, u1bTmp);

	/*  MCUFWDW 0x80[1:0]= 0 */
	/*  weset MCU weady status */
	wtw_wwite8(padaptew, WEG_MCUFWDW, 0);

	/*  Weset MCU IO Wwappew, added by Wogew, 2011.08.30 */
	u1bTmp = wtw_wead8(padaptew, WEG_WSV_CTWW + 1);
	u1bTmp &= ~BIT(0);
	wtw_wwite8(padaptew, WEG_WSV_CTWW + 1, u1bTmp);
	u1bTmp = wtw_wead8(padaptew, WEG_WSV_CTWW + 1);
	u1bTmp |= BIT(0);
	wtw_wwite8(padaptew, WEG_WSV_CTWW+1, u1bTmp);

	/* 	==== Weset digitaw sequence end ====== */

	bMacPwwCtwwOn = fawse;	/*  Disabwe CMD53 W/W */
	wtw_haw_set_hwweg(padaptew, HW_VAW_APFM_ON_MAC, &bMacPwwCtwwOn);
	HawPwwSeqCmdPawsing(padaptew, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK, wtw8723B_cawd_disabwe_fwow);
}

static u32 wtw8723bs_haw_deinit(stwuct adaptew *padaptew)
{
	stwuct dvobj_pwiv *psdpwiv = padaptew->dvobj;
	stwuct debug_pwiv *pdbgpwiv = &psdpwiv->dwv_dbg;

	if (padaptew->hw_init_compweted) {
		if (adaptew_to_pwwctw(padaptew)->bips_pwocessing) {
			if (padaptew->netif_up) {
				int cnt = 0;
				u8 vaw8 = 0;

				wtw8723b_set_FwPwwModeInIPS_cmd(padaptew, 0x3);
				/* poww 0x1cc to make suwe H2C command awweady finished by FW; MAC_0x1cc = 0 means H2C done by FW. */
				do {
					vaw8 = wtw_wead8(padaptew, WEG_HMETFW);
					cnt++;
					mdeway(10);
				} whiwe (cnt < 100 && (vaw8 != 0));
				/* H2C done, entew 32k */
				if (vaw8 == 0) {
					/* sew wpwm to entew 32k */
					vaw8 = wtw_wead8(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_HWPWM1);
					vaw8 += 0x80;
					vaw8 |= BIT(0);
					wtw_wwite8(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_HWPWM1, vaw8);
					adaptew_to_pwwctw(padaptew)->tog = (vaw8 + 0x80) & 0x80;
					cnt = vaw8 = 0;
					do {
						vaw8 = wtw_wead8(padaptew, WEG_CW);
						cnt++;
						mdeway(10);
					} whiwe (cnt < 100 && (vaw8 != 0xEA));
				}

				adaptew_to_pwwctw(padaptew)->pwe_ips_type = 0;

			} ewse {
				pdbgpwiv->dbg_cawddisabwe_cnt++;
				CawdDisabweWTW8723BSdio(padaptew);

				adaptew_to_pwwctw(padaptew)->pwe_ips_type = 1;
			}

		} ewse {
			pdbgpwiv->dbg_cawddisabwe_cnt++;
			CawdDisabweWTW8723BSdio(padaptew);
		}
	} ewse
		pdbgpwiv->dbg_deinit_faiw_cnt++;

	wetuwn _SUCCESS;
}

static u32 wtw8723bs_iniwp_init(stwuct adaptew *padaptew)
{
	wetuwn _SUCCESS;
}

static u32 wtw8723bs_iniwp_deinit(stwuct adaptew *padaptew)
{
	wetuwn _SUCCESS;
}

static void wtw8723bs_init_defauwt_vawue(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData;


	pHawData = GET_HAW_DATA(padaptew);

	wtw8723b_init_defauwt_vawue(padaptew);

	/*  intewface wewated vawiabwe */
	pHawData->SdioWxFIFOCnt = 0;
}

static void wtw8723bs_intewface_configuwe(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);
	stwuct dvobj_pwiv *pdvobjpwiv = adaptew_to_dvobj(padaptew);
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	boow bWiFiConfig = pwegistwypwiv->wifi_spec;


	pdvobjpwiv->WtOutPipe[0] = WWAN_TX_HIQ_DEVICE_ID;
	pdvobjpwiv->WtOutPipe[1] = WWAN_TX_MIQ_DEVICE_ID;
	pdvobjpwiv->WtOutPipe[2] = WWAN_TX_WOQ_DEVICE_ID;

	if (bWiFiConfig)
		pHawData->OutEpNumbew = 2;
	ewse
		pHawData->OutEpNumbew = SDIO_MAX_TX_QUEUE;

	switch (pHawData->OutEpNumbew) {
	case 3:
		pHawData->OutEpQueueSew = TX_SEWE_HQ | TX_SEWE_WQ | TX_SEWE_NQ;
		bweak;
	case 2:
		pHawData->OutEpQueueSew = TX_SEWE_HQ | TX_SEWE_NQ;
		bweak;
	case 1:
		pHawData->OutEpQueueSew = TX_SEWE_HQ;
		bweak;
	defauwt:
		bweak;
	}

	Haw_MappingOutPipe(padaptew, pHawData->OutEpNumbew);
}

/*  */
/* 	Descwiption: */
/* 		We shouwd set Efuse ceww sewection to WiFi ceww in defauwt. */
/*  */
/* 	Assumption: */
/* 		PASSIVE_WEVEW */
/*  */
/* 	Added by Wogew, 2010.11.23. */
/*  */
static void _EfuseCewwSew(stwuct adaptew *padaptew)
{
	u32 vawue32;

	vawue32 = wtw_wead32(padaptew, EFUSE_TEST);
	vawue32 = (vawue32 & ~EFUSE_SEW_MASK) | EFUSE_SEW(EFUSE_WIFI_SEW_0);
	wtw_wwite32(padaptew, EFUSE_TEST, vawue32);
}

static void _WeadWFType(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	pHawData->wf_chip = WF_6052;
}


static void Haw_EfusePawseMACAddw_8723BS(
	stwuct adaptew *padaptew, u8 *hwinfo, boow AutoWoadFaiw
)
{
	u16 i;
	u8 sMacAddw[6] = {0x00, 0xE0, 0x4C, 0xb7, 0x23, 0x00};
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);

	if (AutoWoadFaiw) {
/* 		sMacAddw[5] = (u8)GetWandomNumbew(1, 254); */
		fow (i = 0; i < 6; i++)
			pEEPWOM->mac_addw[i] = sMacAddw[i];
	} ewse {
		/* Wead Pewmanent MAC addwess */
		memcpy(pEEPWOM->mac_addw, &hwinfo[EEPWOM_MAC_ADDW_8723BS], ETH_AWEN);
	}
}

static void Haw_EfusePawseBoawdType_8723BS(
	stwuct adaptew *padaptew, u8 *hwinfo, boow AutoWoadFaiw
)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);

	if (!AutoWoadFaiw) {
		pHawData->BoawdType = (hwinfo[EEPWOM_WF_BOAWD_OPTION_8723B] & 0xE0) >> 5;
		if (pHawData->BoawdType == 0xFF)
			pHawData->BoawdType = (EEPWOM_DEFAUWT_BOAWD_OPTION & 0xE0) >> 5;
	} ewse
		pHawData->BoawdType = 0;
}

static void _WeadEfuseInfo8723BS(stwuct adaptew *padaptew)
{
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);
	u8 *hwinfo = NUWW;

	/*  */
	/*  This pawt wead and pawse the eepwom/efuse content */
	/*  */

	hwinfo = pEEPWOM->efuse_eepwom_data;

	Haw_InitPGData(padaptew, hwinfo);

	Haw_EfusePawseIDCode(padaptew, hwinfo);
	Haw_EfusePawseEEPWOMVew_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);

	Haw_EfusePawseMACAddw_8723BS(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);

	Haw_EfusePawseTxPowewInfo_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseBoawdType_8723BS(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);

	/*  */
	/*  Wead Bwuetooth co-exist and initiawize */
	/*  */
	Haw_EfusePawsePackageType_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseBTCoexistInfo_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseChnwPwan_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseXtaw_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseThewmawMetew_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseAntennaDivewsity_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
	Haw_EfusePawseCustomewID_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);

	Haw_EfusePawseVowtage_8723B(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);

	Haw_WeadWFGainOffset(padaptew, hwinfo, pEEPWOM->bautowoad_faiw_fwag);
}

static void _WeadPWOMContent(stwuct adaptew *padaptew)
{
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);
	u8 	eeVawue;

	eeVawue = wtw_wead8(padaptew, WEG_9346CW);
	/*  To check system boot sewection. */
	pEEPWOM->EepwomOwEfuse = (eeVawue & BOOT_FWOM_EEPWOM) ? twue : fawse;
	pEEPWOM->bautowoad_faiw_fwag = (eeVawue & EEPWOM_EN) ? fawse : twue;

/* 	pHawData->EEType = IS_BOOT_FWOM_EEPWOM(Adaptew) ? EEPWOM_93C46 : EEPWOM_BOOT_EFUSE; */

	_WeadEfuseInfo8723BS(padaptew);
}

static void _InitOthewVawiabwe(stwuct adaptew *Adaptew)
{
}

/*  */
/* 	Descwiption: */
/* 		Wead HW adaptew infowmation by E-Fuse ow EEPWOM accowding CW9346 wepowted. */
/*  */
/* 	Assumption: */
/* 		PASSIVE_WEVEW (SDIO intewface) */
/*  */
/*  */
static s32 _WeadAdaptewInfo8723BS(stwuct adaptew *padaptew)
{
	u8 vaw8;

	/*  befowe access eFuse, make suwe cawd enabwe has been cawwed */
	if (!padaptew->hw_init_compweted)
		_InitPowewOn_8723BS(padaptew);


	vaw8 = wtw_wead8(padaptew, 0x4e);
	vaw8 |= BIT(6);
	wtw_wwite8(padaptew, 0x4e, vaw8);

	_EfuseCewwSew(padaptew);
	_WeadWFType(padaptew);
	_WeadPWOMContent(padaptew);
	_InitOthewVawiabwe(padaptew);

	if (!padaptew->hw_init_compweted) {
		wtw_wwite8(padaptew, 0x67, 0x00); /*  fow BT, Switch Ant contwow to BT */
		CawdDisabweWTW8723BSdio(padaptew);/* fow the powew consumption issue,  wifi ko moduwe is woaded duwing booting, but wifi GUI is off */
	}

	wetuwn _SUCCESS;
}

static void WeadAdaptewInfo8723BS(stwuct adaptew *padaptew)
{
	/*  Wead EEPWOM size befowe caww any EEPWOM function */
	padaptew->EepwomAddwessSize = GetEEPWOMSize8723B(padaptew);

	_WeadAdaptewInfo8723BS(padaptew);
}

/*
 * If vawiabwe not handwed hewe,
 * some vawiabwes wiww be pwocessed in SetHwWeg8723B()
 */
static void SetHwWeg8723BS(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw)
{
	u8 vaw8;

	switch (vawiabwe) {
	case HW_VAW_SET_WPWM:
		/*  wpwm vawue onwy use BIT0(cwock bit) , BIT6(Ack bit), and BIT7(Toggwe bit) */
		/*  BIT0 vawue - 1: 32k, 0:40MHz. */
		/*  BIT6 vawue - 1: wepowt cpwm vawue aftew success set, 0:do not wepowt. */
		/*  BIT7 vawue - Toggwe bit change. */
		{
			vaw8 = *vaw;
			vaw8 &= 0xC1;
			wtw_wwite8(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_HWPWM1, vaw8);
		}
		bweak;
	case HW_VAW_SET_WEQ_FW_PS:
		{
			u8 weq_fw_ps = 0;
			weq_fw_ps = wtw_wead8(padaptew, 0x8f);
			weq_fw_ps |= 0x10;
			wtw_wwite8(padaptew, 0x8f, weq_fw_ps);
		}
		bweak;
	case HW_VAW_WXDMA_AGG_PG_TH:
		vaw8 = *vaw;
		bweak;

	case HW_VAW_DM_IN_WPS:
		wtw8723b_haw_dm_in_wps(padaptew);
		bweak;
	defauwt:
		SetHwWeg8723B(padaptew, vawiabwe, vaw);
		bweak;
	}
}

/*
 * If vawiabwe not handwed hewe,
 * some vawiabwes wiww be pwocessed in GetHwWeg8723B()
 */
static void GetHwWeg8723BS(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw)
{
	switch (vawiabwe) {
	case HW_VAW_CPWM:
		*vaw = wtw_wead8(padaptew, SDIO_WOCAW_BASE | SDIO_WEG_HCPWM1_8723B);
		bweak;

	case HW_VAW_FW_PS_STATE:
		{
			/* 3. wead dwowd 0x88               dwivew wead fw ps state */
			*((u16 *)vaw) = wtw_wead16(padaptew, 0x88);
		}
		bweak;
	defauwt:
		GetHwWeg8723B(padaptew, vawiabwe, vaw);
		bweak;
	}
}

static void SetHwWegWithBuf8723B(stwuct adaptew *padaptew, u8 vawiabwe, u8 *pbuf, int wen)
{
	switch (vawiabwe) {
	case HW_VAW_C2H_HANDWE:
		C2HPacketHandwew_8723B(padaptew, pbuf, wen);
		bweak;
	defauwt:
		bweak;
	}
}

/*  */
/* 	Descwiption: */
/* 		Quewy setting of specified vawiabwe. */
/*  */
static u8 GetHawDefVaw8723BSDIO(
	stwuct adaptew *Adaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue
)
{
	u8 	bWesuwt = _SUCCESS;

	switch (eVawiabwe) {
	case HAW_DEF_IS_SUPPOWT_ANT_DIV:
		bweak;
	case HAW_DEF_CUWWENT_ANTENNA:
		bweak;
	case HW_VAW_MAX_WX_AMPDU_FACTOW:
		/*  Stanwey@BB.SD3 suggests 16K can get stabwe pewfowmance */
		/*  coding by Wucas@20130730 */
		*(u32 *)pVawue = IEEE80211_HT_MAX_AMPDU_16K;
		bweak;
	defauwt:
		bWesuwt = GetHawDefVaw8723B(Adaptew, eVawiabwe, pVawue);
		bweak;
	}

	wetuwn bWesuwt;
}

/*  */
/* 	Descwiption: */
/* 		Change defauwt setting of specified vawiabwe. */
/*  */
static u8 SetHawDefVaw8723BSDIO(stwuct adaptew *Adaptew,
				enum haw_def_vawiabwe eVawiabwe, void *pVawue)
{
	wetuwn SetHawDefVaw8723B(Adaptew, eVawiabwe, pVawue);
}

void wtw8723bs_set_haw_ops(stwuct adaptew *padaptew)
{
	stwuct haw_ops *pHawFunc = &padaptew->HawFunc;

	wtw8723b_set_haw_ops(pHawFunc);

	pHawFunc->haw_init = &wtw8723bs_haw_init;
	pHawFunc->haw_deinit = &wtw8723bs_haw_deinit;

	pHawFunc->iniwp_init = &wtw8723bs_iniwp_init;
	pHawFunc->iniwp_deinit = &wtw8723bs_iniwp_deinit;

	pHawFunc->init_xmit_pwiv = &wtw8723bs_init_xmit_pwiv;
	pHawFunc->fwee_xmit_pwiv = &wtw8723bs_fwee_xmit_pwiv;

	pHawFunc->init_wecv_pwiv = &wtw8723bs_init_wecv_pwiv;
	pHawFunc->fwee_wecv_pwiv = &wtw8723bs_fwee_wecv_pwiv;

	pHawFunc->init_defauwt_vawue = &wtw8723bs_init_defauwt_vawue;
	pHawFunc->intf_chip_configuwe = &wtw8723bs_intewface_configuwe;
	pHawFunc->wead_adaptew_info = &WeadAdaptewInfo8723BS;

	pHawFunc->enabwe_intewwupt = &EnabweIntewwupt8723BSdio;
	pHawFunc->disabwe_intewwupt = &DisabweIntewwupt8723BSdio;
	pHawFunc->check_ips_status = &CheckIPSStatus;
	pHawFunc->SetHwWegHandwew = &SetHwWeg8723BS;
	pHawFunc->GetHwWegHandwew = &GetHwWeg8723BS;
	pHawFunc->SetHwWegHandwewWithBuf = &SetHwWegWithBuf8723B;
	pHawFunc->GetHawDefVawHandwew = &GetHawDefVaw8723BSDIO;
	pHawFunc->SetHawDefVawHandwew = &SetHawDefVaw8723BSDIO;

	pHawFunc->haw_xmit = &wtw8723bs_haw_xmit;
	pHawFunc->mgnt_xmit = &wtw8723bs_mgnt_xmit;
	pHawFunc->haw_xmitfwame_enqueue = &wtw8723bs_haw_xmitfwame_enqueue;
}
