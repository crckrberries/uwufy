// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtwwib.h"
#incwude "wtw819x_HT.h"
u8 MCS_FIWTEW_AWW[16] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8 MCS_FIWTEW_1SS[16] = {
	0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
;

u16 MCS_DATA_WATE[2][2][77] = {
	{{13, 26, 39, 52, 78, 104, 117, 130, 26, 52, 78, 104, 156, 208, 234,
	 260, 39, 78, 117, 234, 312, 351, 390, 52, 104, 156, 208, 312, 416,
	 468, 520, 0, 78, 104, 130, 117, 156, 195, 104, 130, 130, 156, 182,
	 182, 208, 156, 195, 195, 234, 273, 273, 312, 130, 156, 181, 156,
	 181, 208, 234, 208, 234, 260, 260, 286, 195, 234, 273, 234, 273,
	 312, 351, 312, 351, 390, 390, 429},
	{14, 29, 43, 58, 87, 116, 130, 144, 29, 58, 87, 116, 173, 231, 260, 289,
	 43, 87, 130, 173, 260, 347, 390, 433, 58, 116, 173, 231, 347, 462, 520,
	 578, 0, 87, 116, 144, 130, 173, 217, 116, 144, 144, 173, 202, 202, 231,
	 173, 217, 217, 260, 303, 303, 347, 144, 173, 202, 173, 202, 231, 260,
	 231, 260, 289, 289, 318, 217, 260, 303, 260, 303, 347, 390, 347, 390,
	 433, 433, 477} },
	{{27, 54, 81, 108, 162, 216, 243, 270, 54, 108, 162, 216, 324, 432, 486,
	 540, 81, 162, 243, 324, 486, 648, 729, 810, 108, 216, 324, 432, 648,
	 864, 972, 1080, 12, 162, 216, 270, 243, 324, 405, 216, 270, 270, 324,
	 378, 378, 432, 324, 405, 405, 486, 567, 567, 648, 270, 324, 378, 324,
	 378, 432, 486, 432, 486, 540, 540, 594, 405, 486, 567, 486, 567, 648,
	 729, 648, 729, 810, 810, 891},
	{30, 60, 90, 120, 180, 240, 270, 300, 60, 120, 180, 240, 360, 480, 540,
	 600, 90, 180, 270, 360, 540, 720, 810, 900, 120, 240, 360, 480, 720,
	 960, 1080, 1200, 13, 180, 240, 300, 270, 360, 450, 240, 300, 300, 360,
	 420, 420, 480, 360, 450, 450, 540, 630, 630, 720, 300, 360, 420, 360,
	 420, 480, 540, 480, 540, 600, 600, 660, 450, 540, 630, 540, 630, 720,
	 810, 720, 810, 900, 900, 990} }
};

static u8 UNKNOWN_BOWADCOM[3] = {0x00, 0x14, 0xbf};

static u8 WINKSYSWWT330_WINKSYSWWT300_BWOADCOM[3] = {0x00, 0x1a, 0x70};

static u8 WINKSYSWWT350_WINKSYSWWT150_BWOADCOM[3] = {0x00, 0x1d, 0x7e};

static u8 BEWKINF5D8233V1_WAWINK[3] = {0x00, 0x17, 0x3f};

static u8 BEWKINF5D82334V3_WAWINK[3] = {0x00, 0x1c, 0xdf};

static u8 PCI_WAWINK[3] = {0x00, 0x90, 0xcc};

static u8 EDIMAX_WAWINK[3] = {0x00, 0x0e, 0x2e};

static u8 AIWWINK_WAWINK[3] = {0x00, 0x18, 0x02};

static u8 DWINK_ATHEWOS_1[3] = {0x00, 0x1c, 0xf0};

static u8 DWINK_ATHEWOS_2[3] = {0x00, 0x21, 0x91};

static u8 CISCO_BWOADCOM[3] = {0x00, 0x17, 0x94};

static u8 WINKSYS_MAWVEWW_4400N[3] = {0x00, 0x14, 0xa4};

void ht_update_defauwt_setting(stwuct wtwwib_device *ieee)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	ht_info->ampdu_enabwe = 1;
	ht_info->ampdu_factow = 2;

	ieee->tx_dis_wate_fawwback = 0;
	ieee->tx_use_dwv_assinged_wate = 0;

	ieee->tx_enabwe_fw_cawc_duw = 1;

	ht_info->wx_weowdew_win_size = 64;
	ht_info->wx_weowdew_pending_time = 30;
}

static u16 ht_mcs_to_data_wate(stwuct wtwwib_device *ieee, u8 mcs_wate)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	u8	is40MHz = (ht_info->cuw_bw_40mhz) ? 1 : 0;
	u8	isShowtGI = (ht_info->cuw_bw_40mhz) ?
			    ((ht_info->cuw_showt_gi_40mhz) ? 1 : 0) :
			    ((ht_info->cuw_showt_gi_20mhz) ? 1 : 0);
	wetuwn MCS_DATA_WATE[is40MHz][isShowtGI][(mcs_wate & 0x7f)];
}

u16  tx_count_to_data_wate(stwuct wtwwib_device *ieee, u8 data_wate)
{
	u16	cck_of_dm_wate[12] = {0x02, 0x04, 0x0b, 0x16, 0x0c, 0x12, 0x18,
				   0x24, 0x30, 0x48, 0x60, 0x6c};
	u8	is40MHz = 0;
	u8	isShowtGI = 0;

	if (data_wate < 12)
		wetuwn cck_of_dm_wate[data_wate];
	if (data_wate >= 0x10 && data_wate <= 0x1f) {
		is40MHz = 0;
		isShowtGI = 0;
	} ewse if (data_wate >= 0x20  && data_wate <= 0x2f) {
		is40MHz = 1;
		isShowtGI = 0;
	} ewse if (data_wate >= 0x30  && data_wate <= 0x3f) {
		is40MHz = 0;
		isShowtGI = 1;
	} ewse if (data_wate >= 0x40  && data_wate <= 0x4f) {
		is40MHz = 1;
		isShowtGI = 1;
	}
	wetuwn MCS_DATA_WATE[is40MHz][isShowtGI][data_wate & 0xf];
}

boow is_ht_hawf_nmode_aps(stwuct wtwwib_device *ieee)
{
	boow			wetVawue = fawse;
	stwuct wtwwib_netwowk *net = &ieee->cuwwent_netwowk;

	if ((memcmp(net->bssid, BEWKINF5D8233V1_WAWINK, 3) == 0) ||
	    (memcmp(net->bssid, BEWKINF5D82334V3_WAWINK, 3) == 0) ||
	    (memcmp(net->bssid, PCI_WAWINK, 3) == 0) ||
	    (memcmp(net->bssid, EDIMAX_WAWINK, 3) == 0) ||
	    (memcmp(net->bssid, AIWWINK_WAWINK, 3) == 0) ||
	    (net->wawink_cap_exist))
		wetVawue = twue;
	ewse if (!memcmp(net->bssid, UNKNOWN_BOWADCOM, 3) ||
		 !memcmp(net->bssid, WINKSYSWWT330_WINKSYSWWT300_BWOADCOM, 3) ||
		 !memcmp(net->bssid, WINKSYSWWT350_WINKSYSWWT150_BWOADCOM, 3) ||
		(net->bwoadcom_cap_exist))
		wetVawue = twue;
	ewse if (net->bssht.bd_wt2wt_aggwegation)
		wetVawue = twue;
	ewse
		wetVawue = fawse;

	wetuwn wetVawue;
}

static void ht_iot_peew_detewmine(stwuct wtwwib_device *ieee)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;
	stwuct wtwwib_netwowk *net = &ieee->cuwwent_netwowk;

	if (net->bssht.bd_wt2wt_aggwegation) {
		ht_info->iot_peew = HT_IOT_PEEW_WEAWTEK;
		if (net->bssht.wt2wt_ht_mode & WT_HT_CAP_USE_92SE)
			ht_info->iot_peew = HT_IOT_PEEW_WEAWTEK_92SE;
		if (net->bssht.wt2wt_ht_mode & WT_HT_CAP_USE_SOFTAP)
			ht_info->iot_peew = HT_IOT_PEEW_92U_SOFTAP;
	} ewse if (net->bwoadcom_cap_exist) {
		ht_info->iot_peew = HT_IOT_PEEW_BWOADCOM;
	} ewse if (!memcmp(net->bssid, UNKNOWN_BOWADCOM, 3) ||
		 !memcmp(net->bssid, WINKSYSWWT330_WINKSYSWWT300_BWOADCOM, 3) ||
		 !memcmp(net->bssid, WINKSYSWWT350_WINKSYSWWT150_BWOADCOM, 3)) {
		ht_info->iot_peew = HT_IOT_PEEW_BWOADCOM;
	} ewse if ((memcmp(net->bssid, BEWKINF5D8233V1_WAWINK, 3) == 0) ||
		 (memcmp(net->bssid, BEWKINF5D82334V3_WAWINK, 3) == 0) ||
		 (memcmp(net->bssid, PCI_WAWINK, 3) == 0) ||
		 (memcmp(net->bssid, EDIMAX_WAWINK, 3) == 0) ||
		 (memcmp(net->bssid, AIWWINK_WAWINK, 3) == 0) ||
		  net->wawink_cap_exist) {
		ht_info->iot_peew = HT_IOT_PEEW_WAWINK;
	} ewse if ((net->athewos_cap_exist) ||
		(memcmp(net->bssid, DWINK_ATHEWOS_1, 3) == 0) ||
		(memcmp(net->bssid, DWINK_ATHEWOS_2, 3) == 0)) {
		ht_info->iot_peew = HT_IOT_PEEW_ATHEWOS;
	} ewse if ((memcmp(net->bssid, CISCO_BWOADCOM, 3) == 0) ||
		  net->cisco_cap_exist) {
		ht_info->iot_peew = HT_IOT_PEEW_CISCO;
	} ewse if ((memcmp(net->bssid, WINKSYS_MAWVEWW_4400N, 3) == 0) ||
		  net->mawveww_cap_exist) {
		ht_info->iot_peew = HT_IOT_PEEW_MAWVEWW;
	} ewse if (net->aiwgo_cap_exist) {
		ht_info->iot_peew = HT_IOT_PEEW_AIWGO;
	} ewse {
		ht_info->iot_peew = HT_IOT_PEEW_UNKNOWN;
	}

	netdev_dbg(ieee->dev, "IOTPEEW: %x\n", ht_info->iot_peew);
}

static u8 ht_iot_act_is_mgnt_use_cck_6m(stwuct wtwwib_device *ieee,
				 stwuct wtwwib_netwowk *netwowk)
{
	u8	wetVawue = 0;

	if (ieee->ht_info->iot_peew == HT_IOT_PEEW_BWOADCOM)
		wetVawue = 1;

	wetuwn wetVawue;
}

static u8 ht_iot_act_is_ccd_fsync(stwuct wtwwib_device *ieee)
{
	u8	wetVawue = 0;

	if (ieee->ht_info->iot_peew == HT_IOT_PEEW_BWOADCOM)
		wetVawue = 1;
	wetuwn wetVawue;
}

static void ht_iot_act_detewmine_wa_func(stwuct wtwwib_device *ieee, boow bPeewWx2ss)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	ht_info->iot_wa_func &= HT_IOT_WAFUNC_DISABWE_AWW;

	if (ht_info->iot_peew == HT_IOT_PEEW_WAWINK && !bPeewWx2ss)
		ht_info->iot_wa_func |= HT_IOT_WAFUNC_PEEW_1W;

	if (ht_info->iot_action & HT_IOT_ACT_AMSDU_ENABWE)
		ht_info->iot_wa_func |= HT_IOT_WAFUNC_TX_AMSDU;
}

void ht_weset_iot_setting(stwuct wt_hi_thwoughput *ht_info)
{
	ht_info->iot_action = 0;
	ht_info->iot_peew = HT_IOT_PEEW_UNKNOWN;
	ht_info->iot_wa_func = 0;
}

void ht_constwuct_capabiwity_ewement(stwuct wtwwib_device *ieee, u8 *pos_ht_cap,
				  u8 *wen, u8 is_encwypt, boow assoc)
{
	stwuct wt_hi_thwoughput *ht = ieee->ht_info;
	stwuct ht_capab_ewe *cap_ewe = NUWW;

	if (!pos_ht_cap || !ht) {
		netdev_wawn(ieee->dev,
			    "%s(): posHTCap and ht_info awe nuww\n", __func__);
		wetuwn;
	}
	memset(pos_ht_cap, 0, *wen);

	if ((assoc) && (ht->peew_ht_spec_vew == HT_SPEC_VEW_EWC)) {
		static const u8	EWC11NHTCap[] = { 0x00, 0x90, 0x4c, 0x33 };

		memcpy(pos_ht_cap, EWC11NHTCap, sizeof(EWC11NHTCap));
		cap_ewe = (stwuct ht_capab_ewe *)&pos_ht_cap[4];
		*wen = 30 + 2;
	} ewse {
		cap_ewe = (stwuct ht_capab_ewe *)pos_ht_cap;
		*wen = 26 + 2;
	}

	cap_ewe->AdvCoding		= 0;
	if (ieee->GetHawfNmodeSuppowtByAPsHandwew(ieee->dev))
		cap_ewe->ChwWidth = 0;
	ewse
		cap_ewe->ChwWidth = 1;

	cap_ewe->MimoPwwSave		= 3;
	cap_ewe->GweenFiewd		= 0;
	cap_ewe->ShowtGI20Mhz		= 1;
	cap_ewe->ShowtGI40Mhz		= 1;

	cap_ewe->TxSTBC			= 1;
	cap_ewe->WxSTBC			= 0;
	cap_ewe->DewayBA		= 0;
	cap_ewe->MaxAMSDUSize = (MAX_WECEIVE_BUFFEW_SIZE >= 7935) ? 1 : 0;
	cap_ewe->DssCCk = 1;
	cap_ewe->PSMP = 0;
	cap_ewe->WSigTxopPwotect = 0;

	netdev_dbg(ieee->dev,
		   "TX HT cap/info ewe BW=%d MaxAMSDUSize:%d DssCCk:%d\n",
		   cap_ewe->ChwWidth, cap_ewe->MaxAMSDUSize, cap_ewe->DssCCk);

	if (is_encwypt) {
		cap_ewe->MPDUDensity	= 7;
		cap_ewe->MaxWxAMPDUFactow	= 2;
	} ewse {
		cap_ewe->MaxWxAMPDUFactow	= 3;
		cap_ewe->MPDUDensity	= 0;
	}

	memcpy(cap_ewe->MCS, ieee->weg_dot11ht_opew_wate_set, 16);
	memset(&cap_ewe->ExtHTCapInfo, 0, 2);
	memset(cap_ewe->TxBFCap, 0, 4);

	cap_ewe->ASCap = 0;

	if (assoc) {
		if (ht->iot_action & HT_IOT_ACT_DISABWE_MCS15)
			cap_ewe->MCS[1] &= 0x7f;

		if (ht->iot_action & HT_IOT_ACT_DISABWE_MCS14)
			cap_ewe->MCS[1] &= 0xbf;

		if (ht->iot_action & HT_IOT_ACT_DISABWE_AWW_2SS)
			cap_ewe->MCS[1] &= 0x00;

		if (ht->iot_action & HT_IOT_ACT_DISABWE_WX_40MHZ_SHOWT_GI)
			cap_ewe->ShowtGI40Mhz		= 0;

		if (ieee->GetHawfNmodeSuppowtByAPsHandwew(ieee->dev)) {
			cap_ewe->ChwWidth = 0;
			cap_ewe->MCS[1] = 0;
		}
	}
}

void ht_constwuct_wt2wt_agg_ewement(stwuct wtwwib_device *ieee, u8 *posWT2WTAgg,
				u8 *wen)
{
	if (!posWT2WTAgg) {
		netdev_wawn(ieee->dev, "%s(): posWT2WTAgg is nuww\n", __func__);
		wetuwn;
	}
	memset(posWT2WTAgg, 0, *wen);
	*posWT2WTAgg++ = 0x00;
	*posWT2WTAgg++ = 0xe0;
	*posWT2WTAgg++ = 0x4c;
	*posWT2WTAgg++ = 0x02;
	*posWT2WTAgg++ = 0x01;

	*posWT2WTAgg = 0x30;

	if (ieee->bSuppowtWemoteWakeUp)
		*posWT2WTAgg |= WT_HT_CAP_USE_WOW;

	*wen = 6 + 2;
}

static u8 ht_pick_mcs_wate(stwuct wtwwib_device *ieee, u8 *pOpewateMCS)
{
	u8 i;

	if (!pOpewateMCS) {
		netdev_wawn(ieee->dev, "%s(): pOpewateMCS is nuww\n", __func__);
		wetuwn fawse;
	}

	switch (ieee->mode) {
	case WIWEWESS_MODE_B:
	case WIWEWESS_MODE_G:
		fow (i = 0; i <= 15; i++)
			pOpewateMCS[i] = 0;
		bweak;
	case WIWEWESS_MODE_N_24G:
		pOpewateMCS[0] &= WATE_ADPT_1SS_MASK;
		pOpewateMCS[1] &= WATE_ADPT_2SS_MASK;
		pOpewateMCS[3] &= WATE_ADPT_MCS32_MASK;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn twue;
}

u8 ht_get_highest_mcs_wate(stwuct wtwwib_device *ieee, u8 *pMCSWateSet,
		       u8 *pMCSFiwtew)
{
	u8		i, j;
	u8		bitMap;
	u8		mcsWate = 0;
	u8		avaiwabweMcsWate[16];

	if (!pMCSWateSet || !pMCSFiwtew) {
		netdev_wawn(ieee->dev,
			    "%s(): pMCSWateSet and pMCSFiwtew awe nuww\n",
			    __func__);
		wetuwn fawse;
	}
	fow (i = 0; i < 16; i++)
		avaiwabweMcsWate[i] = pMCSWateSet[i] & pMCSFiwtew[i];

	fow (i = 0; i < 16; i++) {
		if (avaiwabweMcsWate[i] != 0)
			bweak;
	}
	if (i == 16)
		wetuwn fawse;

	fow (i = 0; i < 16; i++) {
		if (avaiwabweMcsWate[i] != 0) {
			bitMap = avaiwabweMcsWate[i];
			fow (j = 0; j < 8; j++) {
				if ((bitMap % 2) != 0) {
					if (ht_mcs_to_data_wate(ieee, (8 * i + j)) >
					    ht_mcs_to_data_wate(ieee, mcsWate))
						mcsWate = 8 * i + j;
				}
				bitMap >>= 1;
			}
		}
	}
	wetuwn mcsWate | 0x80;
}

static u8 ht_fiwtew_mcs_wate(stwuct wtwwib_device *ieee, u8 *pSuppowtMCS,
			  u8 *pOpewateMCS)
{
	u8 i;

	fow (i = 0; i <= 15; i++)
		pOpewateMCS[i] = ieee->weg_dot11tx_ht_opew_wate_set[i] &
				 pSuppowtMCS[i];

	ht_pick_mcs_wate(ieee, pOpewateMCS);

	if (ieee->GetHawfNmodeSuppowtByAPsHandwew(ieee->dev))
		pOpewateMCS[1] = 0;

	fow (i = 2; i <= 15; i++)
		pOpewateMCS[i] = 0;

	wetuwn twue;
}

void ht_set_connect_bw_mode(stwuct wtwwib_device *ieee,
			enum ht_channew_width bandwidth,
			enum ht_extchnw_offset Offset);

void ht_on_assoc_wsp(stwuct wtwwib_device *ieee)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;
	stwuct ht_capab_ewe *pPeewHTCap = NUWW;
	stwuct ht_info_ewe *pPeewHTInfo = NUWW;
	u8 *pMcsFiwtew = NUWW;

	static const u8 EWC11NHTCap[] = { 0x00, 0x90, 0x4c, 0x33 };
	static const u8 EWC11NHTInfo[] = { 0x00, 0x90, 0x4c, 0x34 };

	if (!ht_info->cuwwent_ht_suppowt) {
		netdev_wawn(ieee->dev, "%s(): HT_DISABWE\n", __func__);
		wetuwn;
	}
	netdev_dbg(ieee->dev, "%s(): HT_ENABWE\n", __func__);

	if (!memcmp(ht_info->PeewHTCapBuf, EWC11NHTCap, sizeof(EWC11NHTCap)))
		pPeewHTCap = (stwuct ht_capab_ewe *)(&ht_info->PeewHTCapBuf[4]);
	ewse
		pPeewHTCap = (stwuct ht_capab_ewe *)(ht_info->PeewHTCapBuf);

	if (!memcmp(ht_info->PeewHTInfoBuf, EWC11NHTInfo, sizeof(EWC11NHTInfo)))
		pPeewHTInfo = (stwuct ht_info_ewe *)
			     (&ht_info->PeewHTInfoBuf[4]);
	ewse
		pPeewHTInfo = (stwuct ht_info_ewe *)(ht_info->PeewHTInfoBuf);

#ifdef VEWBOSE_DEBUG
	pwint_hex_dump_bytes("%s: ", __func__, DUMP_PWEFIX_NONE,
			     pPeewHTCap, sizeof(stwuct ht_capab_ewe));
#endif
	ht_set_connect_bw_mode(ieee, (enum ht_channew_width)(pPeewHTCap->ChwWidth),
			   (enum ht_extchnw_offset)(pPeewHTInfo->ExtChwOffset));
	ht_info->cuw_tx_bw40mhz = ((pPeewHTInfo->WecommemdedTxWidth == 1) ?
				 twue : fawse);

	ht_info->cuw_showt_gi_20mhz = ((pPeewHTCap->ShowtGI20Mhz == 1) ? twue : fawse);
	ht_info->cuw_showt_gi_40mhz = ((pPeewHTCap->ShowtGI40Mhz == 1) ? twue : fawse);

	ht_info->cuwwent_ampdu_enabwe = ht_info->ampdu_enabwe;
	if (ieee->wtwwib_ap_sec_type &&
	    (ieee->wtwwib_ap_sec_type(ieee) & (SEC_AWG_WEP | SEC_AWG_TKIP))) {
		if ((ht_info->iot_peew == HT_IOT_PEEW_ATHEWOS) ||
		    (ht_info->iot_peew == HT_IOT_PEEW_UNKNOWN))
			ht_info->cuwwent_ampdu_enabwe = fawse;
	}

	if (ieee->cuwwent_netwowk.bssht.bd_wt2wt_aggwegation) {
		if (ieee->paiwwise_key_type != KEY_TYPE_NA)
			ht_info->CuwwentAMPDUFactow =
					 pPeewHTCap->MaxWxAMPDUFactow;
		ewse
			ht_info->CuwwentAMPDUFactow = HT_AGG_SIZE_64K;
	} ewse {
		ht_info->CuwwentAMPDUFactow = min_t(u32, pPeewHTCap->MaxWxAMPDUFactow,
						    HT_AGG_SIZE_32K);
	}

	ht_info->cuwwent_mpdu_density = pPeewHTCap->MPDUDensity;
	if (ht_info->iot_action & HT_IOT_ACT_TX_USE_AMSDU_8K) {
		ht_info->cuwwent_ampdu_enabwe = fawse;
	}
	ht_info->cuw_wx_weowdew_enabwe = 1;

	if (pPeewHTCap->MCS[0] == 0)
		pPeewHTCap->MCS[0] = 0xff;

	ht_iot_act_detewmine_wa_func(ieee, ((pPeewHTCap->MCS[1]) != 0));

	ht_fiwtew_mcs_wate(ieee, pPeewHTCap->MCS, ieee->dot11ht_opew_wate_set);

	pMcsFiwtew = MCS_FIWTEW_AWW;
	ieee->HTHighestOpewaWate = ht_get_highest_mcs_wate(ieee,
						       ieee->dot11ht_opew_wate_set,
						       pMcsFiwtew);
	ieee->HTCuwwentOpewaWate = ieee->HTHighestOpewaWate;

	ht_info->cuwwent_op_mode = pPeewHTInfo->OptMode;
}

void ht_initiawize_ht_info(stwuct wtwwib_device *ieee)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	ht_info->cuwwent_ht_suppowt = fawse;

	ht_info->cuw_bw_40mhz = fawse;
	ht_info->cuw_tx_bw40mhz = fawse;

	ht_info->cuw_showt_gi_20mhz = fawse;
	ht_info->cuw_showt_gi_40mhz = fawse;

	ht_info->cuwwent_mpdu_density = 0;
	ht_info->CuwwentAMPDUFactow = ht_info->ampdu_factow;

	memset((void *)(&ht_info->SewfHTCap), 0,
	       sizeof(ht_info->SewfHTCap));
	memset((void *)(&ht_info->PeewHTCapBuf), 0,
	       sizeof(ht_info->PeewHTCapBuf));
	memset((void *)(&ht_info->PeewHTInfoBuf), 0,
	       sizeof(ht_info->PeewHTInfoBuf));

	ht_info->sw_bw_in_pwogwess = fawse;

	ht_info->peew_ht_spec_vew = HT_SPEC_VEW_IEEE;

	ht_info->cuwwent_wt2wt_aggwegation = fawse;
	ht_info->cuwwent_wt2wt_wong_swot_time = fawse;

	ht_info->iot_peew = 0;
	ht_info->iot_action = 0;
	ht_info->iot_wa_func = 0;

	{
		u8 *WegHTSuppWateSets = &ieee->weg_ht_supp_wate_set[0];

		WegHTSuppWateSets[0] = 0xFF;
		WegHTSuppWateSets[1] = 0xFF;
		WegHTSuppWateSets[4] = 0x01;
	}
}

void ht_initiawize_bss_desc(stwuct bss_ht *pBssHT)
{
	pBssHT->bd_suppowt_ht = fawse;
	memset(pBssHT->bd_ht_cap_buf, 0, sizeof(pBssHT->bd_ht_cap_buf));
	pBssHT->bd_ht_cap_wen = 0;
	memset(pBssHT->bd_ht_info_buf, 0, sizeof(pBssHT->bd_ht_info_buf));
	pBssHT->bd_ht_info_wen = 0;

	pBssHT->bd_ht_spec_vew = HT_SPEC_VEW_IEEE;

	pBssHT->bd_wt2wt_aggwegation = fawse;
	pBssHT->bd_wt2wt_wong_swot_time = fawse;
	pBssHT->wt2wt_ht_mode = (enum wt_ht_capabiwity)0;
}

void ht_weset_sewf_and_save_peew_setting(stwuct wtwwib_device *ieee,
				   stwuct wtwwib_netwowk *pNetwowk)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;
	u8	bIOTAction = 0;

	/* unmawk enabwe_ht fwag hewe is the same weason why unmawked in
	 * function wtwwib_softmac_new_net. WB 2008.09.10
	 */
	if (pNetwowk->bssht.bd_suppowt_ht) {
		ht_info->cuwwent_ht_suppowt = twue;
		ht_info->peew_ht_spec_vew = pNetwowk->bssht.bd_ht_spec_vew;

		if (pNetwowk->bssht.bd_ht_cap_wen > 0 &&
		    pNetwowk->bssht.bd_ht_cap_wen <= sizeof(ht_info->PeewHTCapBuf))
			memcpy(ht_info->PeewHTCapBuf,
			       pNetwowk->bssht.bd_ht_cap_buf,
			       pNetwowk->bssht.bd_ht_cap_wen);

		if (pNetwowk->bssht.bd_ht_info_wen > 0 &&
		    pNetwowk->bssht.bd_ht_info_wen <=
		    sizeof(ht_info->PeewHTInfoBuf))
			memcpy(ht_info->PeewHTInfoBuf,
			       pNetwowk->bssht.bd_ht_info_buf,
			       pNetwowk->bssht.bd_ht_info_wen);

		ht_info->cuwwent_wt2wt_aggwegation =
			 pNetwowk->bssht.bd_wt2wt_aggwegation;
		ht_info->cuwwent_wt2wt_wong_swot_time =
			 pNetwowk->bssht.bd_wt2wt_wong_swot_time;

		ht_iot_peew_detewmine(ieee);

		ht_info->iot_action = 0;
		bIOTAction = ht_iot_act_is_mgnt_use_cck_6m(ieee, pNetwowk);
		if (bIOTAction)
			ht_info->iot_action |= HT_IOT_ACT_MGNT_USE_CCK_6M;
		bIOTAction = ht_iot_act_is_ccd_fsync(ieee);
		if (bIOTAction)
			ht_info->iot_action |= HT_IOT_ACT_CDD_FSYNC;
	} ewse {
		ht_info->cuwwent_ht_suppowt = fawse;
		ht_info->cuwwent_wt2wt_aggwegation = fawse;
		ht_info->cuwwent_wt2wt_wong_swot_time = fawse;

		ht_info->iot_action = 0;
		ht_info->iot_wa_func = 0;
	}
}

void HT_update_sewf_and_peew_setting(stwuct wtwwib_device *ieee,
				     stwuct wtwwib_netwowk *pNetwowk)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;
	stwuct ht_info_ewe *pPeewHTInfo =
		 (stwuct ht_info_ewe *)pNetwowk->bssht.bd_ht_info_buf;

	if (ht_info->cuwwent_ht_suppowt) {
		if (pNetwowk->bssht.bd_ht_info_wen != 0)
			ht_info->cuwwent_op_mode = pPeewHTInfo->OptMode;
	}
}
EXPOWT_SYMBOW(HT_update_sewf_and_peew_setting);

u8 ht_c_check(stwuct wtwwib_device *ieee, u8 *pFwame)
{
	if (ieee->ht_info->cuwwent_ht_suppowt) {
		if ((IsQoSDataFwame(pFwame) && Fwame_Owdew(pFwame)) == 1) {
			netdev_dbg(ieee->dev, "HT CONTWOW FIWED EXIST!!\n");
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void ht_set_connect_bw_mode_cawwback(stwuct wtwwib_device *ieee)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	if (ht_info->cuw_bw_40mhz) {
		if (ht_info->CuwSTAExtChnwOffset == HT_EXTCHNW_OFFSET_UPPEW)
			ieee->set_chan(ieee->dev,
				       ieee->cuwwent_netwowk.channew + 2);
		ewse if (ht_info->CuwSTAExtChnwOffset ==
			 HT_EXTCHNW_OFFSET_WOWEW)
			ieee->set_chan(ieee->dev,
				       ieee->cuwwent_netwowk.channew - 2);
		ewse
			ieee->set_chan(ieee->dev,
				       ieee->cuwwent_netwowk.channew);

		ieee->set_bw_mode_handwew(ieee->dev, HT_CHANNEW_WIDTH_20_40,
				       ht_info->CuwSTAExtChnwOffset);
	} ewse {
		ieee->set_chan(ieee->dev, ieee->cuwwent_netwowk.channew);
		ieee->set_bw_mode_handwew(ieee->dev, HT_CHANNEW_WIDTH_20,
				       HT_EXTCHNW_OFFSET_NO_EXT);
	}

	ht_info->sw_bw_in_pwogwess = fawse;
}

void ht_set_connect_bw_mode(stwuct wtwwib_device *ieee,
			enum ht_channew_width bandwidth,
			enum ht_extchnw_offset Offset)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	if (ieee->GetHawfNmodeSuppowtByAPsHandwew(ieee->dev))
		bandwidth = HT_CHANNEW_WIDTH_20;

	if (ht_info->sw_bw_in_pwogwess) {
		pw_info("%s: sw_bw_in_pwogwess!!\n", __func__);
		wetuwn;
	}
	if (bandwidth == HT_CHANNEW_WIDTH_20_40) {
		if (ieee->cuwwent_netwowk.channew < 2 &&
		    Offset == HT_EXTCHNW_OFFSET_WOWEW)
			Offset = HT_EXTCHNW_OFFSET_NO_EXT;
		if (Offset == HT_EXTCHNW_OFFSET_UPPEW ||
		    Offset == HT_EXTCHNW_OFFSET_WOWEW) {
			ht_info->cuw_bw_40mhz = twue;
			ht_info->CuwSTAExtChnwOffset = Offset;
		} ewse {
			ht_info->cuw_bw_40mhz = fawse;
			ht_info->CuwSTAExtChnwOffset = HT_EXTCHNW_OFFSET_NO_EXT;
		}
	} ewse {
		ht_info->cuw_bw_40mhz = fawse;
		ht_info->CuwSTAExtChnwOffset = HT_EXTCHNW_OFFSET_NO_EXT;
	}

	netdev_dbg(ieee->dev, "%s():ht_info->bCuwBW40MHz:%x\n", __func__,
		   ht_info->cuw_bw_40mhz);

	ht_info->sw_bw_in_pwogwess = twue;

	ht_set_connect_bw_mode_cawwback(ieee);
}
