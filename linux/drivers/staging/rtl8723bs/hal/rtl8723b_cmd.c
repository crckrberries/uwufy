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

#define MAX_H2C_BOX_NUMS	4
#define MESSAGE_BOX_SIZE	4

#define WTW8723B_MAX_CMD_WEN	7
#define WTW8723B_EX_MESSAGE_BOX_SIZE	4

static u8 _is_fw_wead_cmd_down(stwuct adaptew *padaptew, u8 msgbox_num)
{
	u8 wead_down = fawse;
	int wetwy_cnts = 100;

	u8 vawid;

	do {
		vawid = wtw_wead8(padaptew, WEG_HMETFW) & BIT(msgbox_num);
		if (0 == vawid) {
			wead_down = twue;
		}
	} whiwe ((!wead_down) && (wetwy_cnts--));

	wetuwn wead_down;

}


/*****************************************
* H2C Msg fowmat :
*| 31 - 8		|7-5	| 4 - 0	|
*| h2c_msg	|Cwass	|CMD_ID	|
*| 31-0						|
*| Ext msg					|
*
******************************************/
s32 FiwwH2CCmd8723B(stwuct adaptew *padaptew, u8 EwementID, u32 CmdWen, u8 *pCmdBuffew)
{
	u8 h2c_box_num;
	u32 msgbox_addw;
	u32 msgbox_ex_addw = 0;
	stwuct haw_com_data *pHawData;
	u32 h2c_cmd = 0;
	u32 h2c_cmd_ex = 0;
	s32 wet = _FAIW;

	padaptew = GET_PWIMAWY_ADAPTEW(padaptew);
	pHawData = GET_HAW_DATA(padaptew);
	if (mutex_wock_intewwuptibwe(&(adaptew_to_dvobj(padaptew)->h2c_fwcmd_mutex)))
		wetuwn wet;

	if (!pCmdBuffew) {
		goto exit;
	}

	if (CmdWen > WTW8723B_MAX_CMD_WEN) {
		goto exit;
	}

	if (padaptew->bSuwpwiseWemoved)
		goto exit;

	/* pay attention to if  wace condition happened in  H2C cmd setting. */
	do {
		h2c_box_num = pHawData->WastHMEBoxNum;

		if (!_is_fw_wead_cmd_down(padaptew, h2c_box_num))
			goto exit;

		if (CmdWen <= 3)
			memcpy((u8 *)(&h2c_cmd)+1, pCmdBuffew, CmdWen);
		ewse {
			memcpy((u8 *)(&h2c_cmd)+1, pCmdBuffew, 3);
			memcpy((u8 *)(&h2c_cmd_ex), pCmdBuffew+3, CmdWen-3);
/* 			*(u8 *)(&h2c_cmd) |= BIT(7); */
		}

		*(u8 *)(&h2c_cmd) |= EwementID;

		if (CmdWen > 3) {
			msgbox_ex_addw = WEG_HMEBOX_EXT0_8723B + (h2c_box_num*WTW8723B_EX_MESSAGE_BOX_SIZE);
			wtw_wwite32(padaptew, msgbox_ex_addw, h2c_cmd_ex);
		}
		msgbox_addw = WEG_HMEBOX_0 + (h2c_box_num*MESSAGE_BOX_SIZE);
		wtw_wwite32(padaptew, msgbox_addw, h2c_cmd);

		pHawData->WastHMEBoxNum = (h2c_box_num+1) % MAX_H2C_BOX_NUMS;

	} whiwe (0);

	wet = _SUCCESS;

exit:

	mutex_unwock(&(adaptew_to_dvobj(padaptew)->h2c_fwcmd_mutex));
	wetuwn wet;
}

static void ConstwuctBeacon(stwuct adaptew *padaptew, u8 *pfwame, u32 *pWength)
{
	stwuct ieee80211_hdw *pwwanhdw;
	__we16 *fctww;
	u32 wate_wen, pktwen;
	stwuct mwme_ext_pwiv *pmwmeext = &(padaptew->mwmeextpwiv);
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);
	stwuct wwan_bssid_ex *cuw_netwowk = &(pmwmeinfo->netwowk);

	pwwanhdw = (stwuct ieee80211_hdw *)pfwame;

	fctww = &(pwwanhdw->fwame_contwow);
	*(fctww) = 0;

	eth_bwoadcast_addw(pwwanhdw->addw1);
	memcpy(pwwanhdw->addw2, myid(&(padaptew->eepwompwiv)), ETH_AWEN);
	memcpy(pwwanhdw->addw3, get_my_bssid(cuw_netwowk), ETH_AWEN);

	SetSeqNum(pwwanhdw, 0/*pmwmeext->mgnt_seq*/);
	/* pmwmeext->mgnt_seq++; */
	SetFwameSubType(pfwame, WIFI_BEACON);

	pfwame += sizeof(stwuct ieee80211_hdw_3addw);
	pktwen = sizeof(stwuct ieee80211_hdw_3addw);

	/* timestamp wiww be insewted by hawdwawe */
	pfwame += 8;
	pktwen += 8;

	/*  beacon intewvaw: 2 bytes */
	memcpy(pfwame, (unsigned chaw *)(wtw_get_beacon_intewvaw_fwom_ie(cuw_netwowk->ies)), 2);

	pfwame += 2;
	pktwen += 2;

	/*  capabiwity info: 2 bytes */
	memcpy(pfwame, (unsigned chaw *)(wtw_get_capabiwity_fwom_ie(cuw_netwowk->ies)), 2);

	pfwame += 2;
	pktwen += 2;

	if ((pmwmeinfo->state&0x03) == WIFI_FW_AP_STATE) {
		pktwen += cuw_netwowk->ie_wength - sizeof(stwuct ndis_802_11_fix_ie);
		memcpy(pfwame, cuw_netwowk->ies+sizeof(stwuct ndis_802_11_fix_ie), pktwen);

		goto _ConstwuctBeacon;
	}

	/* bewow fow ad-hoc mode */

	/*  SSID */
	pfwame = wtw_set_ie(pfwame, WWAN_EID_SSID, cuw_netwowk->ssid.ssid_wength, cuw_netwowk->ssid.ssid, &pktwen);

	/*  suppowted wates... */
	wate_wen = wtw_get_wateset_wen(cuw_netwowk->suppowted_wates);
	pfwame = wtw_set_ie(pfwame, WWAN_EID_SUPP_WATES, ((wate_wen > 8) ? 8 : wate_wen), cuw_netwowk->suppowted_wates, &pktwen);

	/*  DS pawametew set */
	pfwame = wtw_set_ie(pfwame, WWAN_EID_DS_PAWAMS, 1, (unsigned chaw *)&(cuw_netwowk->configuwation.ds_config), &pktwen);

	if ((pmwmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) {
		u32 ATIMWindow;
		/*  IBSS Pawametew Set... */
		/* ATIMWindow = cuw->configuwation.ATIMWindow; */
		ATIMWindow = 0;
		pfwame = wtw_set_ie(pfwame, WWAN_EID_IBSS_PAWAMS, 2, (unsigned chaw *)(&ATIMWindow), &pktwen);
	}


	/* todo: EWP IE */


	/*  EXTEWNDED SUPPOWTED WATE */
	if (wate_wen > 8)
		pfwame = wtw_set_ie(pfwame, WWAN_EID_EXT_SUPP_WATES, (wate_wen - 8), (cuw_netwowk->suppowted_wates + 8), &pktwen);


	/* todo:HT fow adhoc */

_ConstwuctBeacon:

	if ((pktwen + TXDESC_SIZE) > 512)
		wetuwn;

	*pWength = pktwen;

}

static void ConstwuctPSPoww(stwuct adaptew *padaptew, u8 *pfwame, u32 *pWength)
{
	stwuct ieee80211_hdw *pwwanhdw;
	__we16 *fctww;
	stwuct mwme_ext_pwiv *pmwmeext = &(padaptew->mwmeextpwiv);
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);

	pwwanhdw = (stwuct ieee80211_hdw *)pfwame;

	/*  Fwame contwow. */
	fctww = &(pwwanhdw->fwame_contwow);
	*(fctww) = 0;
	SetPwwMgt(fctww);
	SetFwameSubType(pfwame, WIFI_PSPOWW);

	/*  AID. */
	SetDuwation(pfwame, (pmwmeinfo->aid | 0xc000));

	/*  BSSID. */
	memcpy(pwwanhdw->addw1, get_my_bssid(&(pmwmeinfo->netwowk)), ETH_AWEN);

	/*  TA. */
	memcpy(pwwanhdw->addw2, myid(&(padaptew->eepwompwiv)), ETH_AWEN);

	*pWength = 16;
}

static void ConstwuctNuwwFunctionData(
	stwuct adaptew *padaptew,
	u8 *pfwame,
	u32 *pWength,
	u8 *StaAddw,
	u8 bQoS,
	u8 AC,
	u8 bEosp,
	u8 bFowcePowewSave
)
{
	stwuct ieee80211_hdw *pwwanhdw;
	__we16 *fctww;
	u32 pktwen;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_netwowk *cuw_netwowk = &pmwmepwiv->cuw_netwowk;
	stwuct mwme_ext_pwiv *pmwmeext = &(padaptew->mwmeextpwiv);
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);

	pwwanhdw = (stwuct ieee80211_hdw *)pfwame;

	fctww = &pwwanhdw->fwame_contwow;
	*(fctww) = 0;
	if (bFowcePowewSave)
		SetPwwMgt(fctww);

	switch (cuw_netwowk->netwowk.infwastwuctuwe_mode) {
	case Ndis802_11Infwastwuctuwe:
		SetToDs(fctww);
		memcpy(pwwanhdw->addw1, get_my_bssid(&(pmwmeinfo->netwowk)), ETH_AWEN);
		memcpy(pwwanhdw->addw2, myid(&(padaptew->eepwompwiv)), ETH_AWEN);
		memcpy(pwwanhdw->addw3, StaAddw, ETH_AWEN);
		bweak;
	case Ndis802_11APMode:
		SetFwDs(fctww);
		memcpy(pwwanhdw->addw1, StaAddw, ETH_AWEN);
		memcpy(pwwanhdw->addw2, get_my_bssid(&(pmwmeinfo->netwowk)), ETH_AWEN);
		memcpy(pwwanhdw->addw3, myid(&(padaptew->eepwompwiv)), ETH_AWEN);
		bweak;
	case Ndis802_11IBSS:
	defauwt:
		memcpy(pwwanhdw->addw1, StaAddw, ETH_AWEN);
		memcpy(pwwanhdw->addw2, myid(&(padaptew->eepwompwiv)), ETH_AWEN);
		memcpy(pwwanhdw->addw3, get_my_bssid(&(pmwmeinfo->netwowk)), ETH_AWEN);
		bweak;
	}

	SetSeqNum(pwwanhdw, 0);

	if (bQoS) {
		stwuct ieee80211_qos_hdw *pwwanqoshdw;

		SetFwameSubType(pfwame, WIFI_QOS_DATA_NUWW);

		pwwanqoshdw = (stwuct ieee80211_qos_hdw *)pfwame;
		SetPwiowity(&pwwanqoshdw->qos_ctww, AC);
		SetEOSP(&pwwanqoshdw->qos_ctww, bEosp);

		pktwen = sizeof(stwuct ieee80211_qos_hdw);
	} ewse {
		SetFwameSubType(pfwame, WIFI_DATA_NUWW);

		pktwen = sizeof(stwuct ieee80211_hdw_3addw);
	}

	*pWength = pktwen;
}

/*
 * To check if wesewved page content is destwoyed by beacon because beacon
 * is too wawge.
 */
/* 2010.06.23. Added by tynwi. */
void CheckFwWsvdPageContent(stwuct adaptew *Adaptew)
{
}

static void wtw8723b_set_FwWsvdPage_cmd(stwuct adaptew *padaptew, stwuct wsvdpage_woc *wsvdpagewoc)
{
	u8 u1H2CWsvdPagePawm[H2C_WSVDPAGE_WOC_WEN] = {0};

	SET_8723B_H2CCMD_WSVDPAGE_WOC_PWOBE_WSP(u1H2CWsvdPagePawm, wsvdpagewoc->WocPwobeWsp);
	SET_8723B_H2CCMD_WSVDPAGE_WOC_PSPOWW(u1H2CWsvdPagePawm, wsvdpagewoc->WocPsPoww);
	SET_8723B_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(u1H2CWsvdPagePawm, wsvdpagewoc->WocNuwwData);
	SET_8723B_H2CCMD_WSVDPAGE_WOC_QOS_NUWW_DATA(u1H2CWsvdPagePawm, wsvdpagewoc->WocQosNuww);
	SET_8723B_H2CCMD_WSVDPAGE_WOC_BT_QOS_NUWW_DATA(u1H2CWsvdPagePawm, wsvdpagewoc->WocBTQosNuww);

	FiwwH2CCmd8723B(padaptew, H2C_8723B_WSVD_PAGE, H2C_WSVDPAGE_WOC_WEN, u1H2CWsvdPagePawm);
}

static void wtw8723b_set_FwAoacWsvdPage_cmd(stwuct adaptew *padaptew, stwuct wsvdpage_woc *wsvdpagewoc)
{
}

void wtw8723b_set_FwMediaStatusWpt_cmd(stwuct adaptew *padaptew, u8 mstatus, u8 macid)
{
	u8 u1H2CMediaStatusWptPawm[H2C_MEDIA_STATUS_WPT_WEN] = {0};
	u8 macid_end = 0;

	SET_8723B_H2CCMD_MSWWPT_PAWM_OPMODE(u1H2CMediaStatusWptPawm, mstatus);
	SET_8723B_H2CCMD_MSWWPT_PAWM_MACID_IND(u1H2CMediaStatusWptPawm, 0);
	SET_8723B_H2CCMD_MSWWPT_PAWM_MACID(u1H2CMediaStatusWptPawm, macid);
	SET_8723B_H2CCMD_MSWWPT_PAWM_MACID_END(u1H2CMediaStatusWptPawm, macid_end);

	FiwwH2CCmd8723B(padaptew, H2C_8723B_MEDIA_STATUS_WPT, H2C_MEDIA_STATUS_WPT_WEN, u1H2CMediaStatusWptPawm);
}

void wtw8723b_set_FwMacIdConfig_cmd(stwuct adaptew *padaptew, u8 mac_id, u8 waid, u8 bw, u8 sgi, u32 mask)
{
	u8 u1H2CMacIdConfigPawm[H2C_MACID_CFG_WEN] = {0};

	SET_8723B_H2CCMD_MACID_CFG_MACID(u1H2CMacIdConfigPawm, mac_id);
	SET_8723B_H2CCMD_MACID_CFG_WAID(u1H2CMacIdConfigPawm, waid);
	SET_8723B_H2CCMD_MACID_CFG_SGI_EN(u1H2CMacIdConfigPawm, sgi ? 1 : 0);
	SET_8723B_H2CCMD_MACID_CFG_BW(u1H2CMacIdConfigPawm, bw);
	SET_8723B_H2CCMD_MACID_CFG_WATE_MASK0(u1H2CMacIdConfigPawm, (u8)(mask & 0x000000ff));
	SET_8723B_H2CCMD_MACID_CFG_WATE_MASK1(u1H2CMacIdConfigPawm, (u8)((mask & 0x0000ff00) >> 8));
	SET_8723B_H2CCMD_MACID_CFG_WATE_MASK2(u1H2CMacIdConfigPawm, (u8)((mask & 0x00ff0000) >> 16));
	SET_8723B_H2CCMD_MACID_CFG_WATE_MASK3(u1H2CMacIdConfigPawm, (u8)((mask & 0xff000000) >> 24));

	FiwwH2CCmd8723B(padaptew, H2C_8723B_MACID_CFG, H2C_MACID_CFG_WEN, u1H2CMacIdConfigPawm);
}

void wtw8723b_set_wssi_cmd(stwuct adaptew *padaptew, u8 *pawam)
{
	u8 u1H2CWssiSettingPawm[H2C_WSSI_SETTING_WEN] = {0};
	u8 mac_id = *pawam;
	u8 wssi = *(pawam+2);
	u8 uwdw_state = 0;

	SET_8723B_H2CCMD_WSSI_SETTING_MACID(u1H2CWssiSettingPawm, mac_id);
	SET_8723B_H2CCMD_WSSI_SETTING_WSSI(u1H2CWssiSettingPawm, wssi);
	SET_8723B_H2CCMD_WSSI_SETTING_UWDW_STATE(u1H2CWssiSettingPawm, uwdw_state);

	FiwwH2CCmd8723B(padaptew, H2C_8723B_WSSI_SETTING, H2C_WSSI_SETTING_WEN, u1H2CWssiSettingPawm);
}

void wtw8723b_set_FwPwwMode_cmd(stwuct adaptew *padaptew, u8 psmode)
{
	int i;
	stwuct pwwctww_pwiv *pwwpwiv = adaptew_to_pwwctw(padaptew);
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	u8 u1H2CPwwModePawm[H2C_PWWMODE_WEN] = {0};
	u8 PowewState = 0, awake_intvw = 1, byte5 = 0, wwbm = 0;

	if (pwwpwiv->dtim > 0 && pwwpwiv->dtim < 16)
		awake_intvw = pwwpwiv->dtim+1;/* DTIM = (awake_intvw - 1) */
	ewse
		awake_intvw = 3;/* DTIM =2 */

	wwbm = 2;

	if (padaptew->wegistwypwiv.wifi_spec == 1) {
		awake_intvw = 2;
		wwbm = 2;
	}

	if (psmode > 0) {
		if (haw_btcoex_IsBtContwowWps(padaptew) == twue) {
			PowewState = haw_btcoex_WpwmVaw(padaptew);
			byte5 = haw_btcoex_WpsVaw(padaptew);

			if ((wwbm == 2) && (byte5 & BIT(4))) {
				/*  Keep awake intewvaw to 1 to pwevent fwom */
				/*  decweasing coex pewfowmance */
				awake_intvw = 2;
				wwbm = 2;
			}
		} ewse {
			PowewState = 0x00;/*  AwwON(0x0C), WFON(0x04), WFOFF(0x00) */
			byte5 = 0x40;
		}
	} ewse {
		PowewState = 0x0C;/*  AwwON(0x0C), WFON(0x04), WFOFF(0x00) */
		byte5 = 0x40;
	}

	SET_8723B_H2CCMD_PWWMODE_PAWM_MODE(u1H2CPwwModePawm, (psmode > 0) ? 1 : 0);
	SET_8723B_H2CCMD_PWWMODE_PAWM_SMAWT_PS(u1H2CPwwModePawm, pwwpwiv->smawt_ps);
	SET_8723B_H2CCMD_PWWMODE_PAWM_WWBM(u1H2CPwwModePawm, wwbm);
	SET_8723B_H2CCMD_PWWMODE_PAWM_BCN_PASS_TIME(u1H2CPwwModePawm, awake_intvw);
	SET_8723B_H2CCMD_PWWMODE_PAWM_AWW_QUEUE_UAPSD(u1H2CPwwModePawm, padaptew->wegistwypwiv.uapsd_enabwe);
	SET_8723B_H2CCMD_PWWMODE_PAWM_PWW_STATE(u1H2CPwwModePawm, PowewState);
	SET_8723B_H2CCMD_PWWMODE_PAWM_BYTE5(u1H2CPwwModePawm, byte5);
	if (psmode != PS_MODE_ACTIVE) {
		if (!pmwmeext->adaptive_tsf_done && pmwmeext->bcn_cnt > 0) {
			u8 watio_20_deway, watio_80_deway;

			/* byte 6 fow adaptive_eawwy_32k */
			/* 0:3] = DwvBcnEawwy  (ms) , [4:7] = DwvBcnTimeOut  (ms) */
			/*  20% fow DwvBcnEawwy, 80% fow DwvBcnTimeOut */
			watio_20_deway = 0;
			watio_80_deway = 0;
			pmwmeext->DwvBcnEawwy = 0xff;
			pmwmeext->DwvBcnTimeOut = 0xff;

			fow (i = 0; i < 9; i++) {
				pmwmeext->bcn_deway_watio[i] = (pmwmeext->bcn_deway_cnt[i]*100)/pmwmeext->bcn_cnt;

				watio_20_deway += pmwmeext->bcn_deway_watio[i];
				watio_80_deway += pmwmeext->bcn_deway_watio[i];

				if (watio_20_deway > 20 && pmwmeext->DwvBcnEawwy == 0xff)
					pmwmeext->DwvBcnEawwy = i;

				if (watio_80_deway > 80 && pmwmeext->DwvBcnTimeOut == 0xff)
					pmwmeext->DwvBcnTimeOut = i;

				/* weset adaptive_eawwy_32k cnt */
				pmwmeext->bcn_deway_cnt[i] = 0;
				pmwmeext->bcn_deway_watio[i] = 0;

			}

			pmwmeext->bcn_cnt = 0;
			pmwmeext->adaptive_tsf_done = twue;

		}

/* offwoad to FW if fw vewsion > v15.10
		pmwmeext->DwvBcnEawwy = 0;
		pmwmeext->DwvBcnTimeOut =7;

		if ((pmwmeext->DwvBcnEawwy!= 0Xff) && (pmwmeext->DwvBcnTimeOut!= 0xff))
			u1H2CPwwModePawm[H2C_PWWMODE_WEN-1] = BIT(0) | ((pmwmeext->DwvBcnEawwy<<1)&0x0E) |((pmwmeext->DwvBcnTimeOut<<4)&0xf0) ;
*/

	}

	haw_btcoex_WecowdPwwMode(padaptew, u1H2CPwwModePawm, H2C_PWWMODE_WEN);

	FiwwH2CCmd8723B(padaptew, H2C_8723B_SET_PWW_MODE, H2C_PWWMODE_WEN, u1H2CPwwModePawm);
}

void wtw8723b_set_FwPsTunePawam_cmd(stwuct adaptew *padaptew)
{
	u8 u1H2CPsTunePawm[H2C_PSTUNEPAWAM_WEN] = {0};
	u8 bcn_to_wimit = 10; /* 10 * 100 * awakeintewvaw (ms) */
	u8 dtim_timeout = 5; /* ms wait bwoadcast data timew */
	u8 ps_timeout = 20;  /* ms Keep awake when tx */
	u8 dtim_pewiod = 3;

	SET_8723B_H2CCMD_PSTUNE_PAWM_BCN_TO_WIMIT(u1H2CPsTunePawm, bcn_to_wimit);
	SET_8723B_H2CCMD_PSTUNE_PAWM_DTIM_TIMEOUT(u1H2CPsTunePawm, dtim_timeout);
	SET_8723B_H2CCMD_PSTUNE_PAWM_PS_TIMEOUT(u1H2CPsTunePawm, ps_timeout);
	SET_8723B_H2CCMD_PSTUNE_PAWM_ADOPT(u1H2CPsTunePawm, 1);
	SET_8723B_H2CCMD_PSTUNE_PAWM_DTIM_PEWIOD(u1H2CPsTunePawm, dtim_pewiod);

	FiwwH2CCmd8723B(padaptew, H2C_8723B_PS_TUNING_PAWA, H2C_PSTUNEPAWAM_WEN, u1H2CPsTunePawm);
}

void wtw8723b_set_FwPwwModeInIPS_cmd(stwuct adaptew *padaptew, u8 cmd_pawam)
{

	FiwwH2CCmd8723B(padaptew, H2C_8723B_FWWPS_IN_IPS_, 1, &cmd_pawam);
}

/*
 * Descwiption: Fiww the wesewved packets that FW wiww use to WSVD page.
 * Now we just send 4 types packet to wsvd page.
 * (1)Beacon, (2)Ps-poww, (3)Nuww data, (4)PwobeWsp.
 *
 * Input:
 *
 * bDWFinished - fawse: At the fiwst time we wiww send aww the packets as
 * a wawge packet to Hw, so we need to set the packet wength to totaw wength.
 *
 * twue: At the second time, we shouwd send the fiwst packet (defauwt:beacon)
 * to Hw again and set the wength in descwiptow to the weaw beacon wength.
 */
/* 2009.10.15 by tynwi. */
static void wtw8723b_set_FwWsvdPagePkt(
	stwuct adaptew *padaptew, boow bDWFinished
)
{
	stwuct xmit_fwame *pcmdfwame;
	stwuct pkt_attwib *pattwib;
	stwuct xmit_pwiv *pxmitpwiv;
	stwuct mwme_ext_pwiv *pmwmeext;
	stwuct mwme_ext_info *pmwmeinfo;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	u32 BeaconWength = 0, PSPowwWength = 0;
	u32 NuwwDataWength = 0, QosNuwwWength = 0, BTQosNuwwWength = 0;
	u8 *WesewvedPagePacket;
	u8 TxDescWen = TXDESC_SIZE, TxDescOffset = TXDESC_OFFSET;
	u8 TotawPageNum = 0, CuwtPktPageNum = 0, WsvdPageNum = 0;
	u16 BufIndex, PageSize = 128;
	u32 TotawPacketWen, MaxWsvdPageBufSize = 0;

	stwuct wsvdpage_woc WsvdPageWoc;

	pxmitpwiv = &padaptew->xmitpwiv;
	pmwmeext = &padaptew->mwmeextpwiv;
	pmwmeinfo = &pmwmeext->mwmext_info;

	WsvdPageNum = BCNQ_PAGE_NUM_8723B + WOWWAN_PAGE_NUM_8723B;
	MaxWsvdPageBufSize = WsvdPageNum*PageSize;

	pcmdfwame = wtw_awwoc_cmdxmitfwame(pxmitpwiv);
	if (!pcmdfwame)
		wetuwn;

	WesewvedPagePacket = pcmdfwame->buf_addw;
	memset(&WsvdPageWoc, 0, sizeof(stwuct wsvdpage_woc));

	/* 3 (1) beacon */
	BufIndex = TxDescOffset;
	ConstwuctBeacon(padaptew, &WesewvedPagePacket[BufIndex], &BeaconWength);

	/*  When we count the fiwst page size, we need to wesewve descwiption size fow the WSVD */
	/*  packet, it wiww be fiwwed in fwont of the packet in TXPKTBUF. */
	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + BeaconWength);
	/* If we don't add 1 mowe page, the WOWWAN function has a pwobwem. Bawon thinks it's a bug of fiwmwawe */
	if (CuwtPktPageNum == 1)
		CuwtPktPageNum += 1;

	TotawPageNum += CuwtPktPageNum;

	BufIndex += (CuwtPktPageNum*PageSize);

	/* 3 (2) ps-poww */
	WsvdPageWoc.WocPsPoww = TotawPageNum;
	ConstwuctPSPoww(padaptew, &WesewvedPagePacket[BufIndex], &PSPowwWength);
	wtw8723b_fiww_fake_txdesc(padaptew, &WesewvedPagePacket[BufIndex-TxDescWen], PSPowwWength, twue, fawse, fawse);

	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + PSPowwWength);

	TotawPageNum += CuwtPktPageNum;

	BufIndex += (CuwtPktPageNum*PageSize);

	/* 3 (3) nuww data */
	WsvdPageWoc.WocNuwwData = TotawPageNum;
	ConstwuctNuwwFunctionData(
		padaptew,
		&WesewvedPagePacket[BufIndex],
		&NuwwDataWength,
		get_my_bssid(&pmwmeinfo->netwowk),
		fawse, 0, 0, fawse
	);
	wtw8723b_fiww_fake_txdesc(padaptew, &WesewvedPagePacket[BufIndex-TxDescWen], NuwwDataWength, fawse, fawse, fawse);

	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + NuwwDataWength);

	TotawPageNum += CuwtPktPageNum;

	BufIndex += (CuwtPktPageNum*PageSize);

	/* 3 (5) Qos nuww data */
	WsvdPageWoc.WocQosNuww = TotawPageNum;
	ConstwuctNuwwFunctionData(
		padaptew,
		&WesewvedPagePacket[BufIndex],
		&QosNuwwWength,
		get_my_bssid(&pmwmeinfo->netwowk),
		twue, 0, 0, fawse
	);
	wtw8723b_fiww_fake_txdesc(padaptew, &WesewvedPagePacket[BufIndex-TxDescWen], QosNuwwWength, fawse, fawse, fawse);

	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + QosNuwwWength);

	TotawPageNum += CuwtPktPageNum;

	BufIndex += (CuwtPktPageNum*PageSize);

	/* 3 (6) BT Qos nuww data */
	WsvdPageWoc.WocBTQosNuww = TotawPageNum;
	ConstwuctNuwwFunctionData(
		padaptew,
		&WesewvedPagePacket[BufIndex],
		&BTQosNuwwWength,
		get_my_bssid(&pmwmeinfo->netwowk),
		twue, 0, 0, fawse
	);
	wtw8723b_fiww_fake_txdesc(padaptew, &WesewvedPagePacket[BufIndex-TxDescWen], BTQosNuwwWength, fawse, twue, fawse);

	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + BTQosNuwwWength);

	TotawPageNum += CuwtPktPageNum;

	BufIndex += (CuwtPktPageNum*PageSize);

	TotawPacketWen = BufIndex + BTQosNuwwWength;

	if (TotawPacketWen > MaxWsvdPageBufSize) {
		goto ewwow;
	} ewse {
		/*  update attwibute */
		pattwib = &pcmdfwame->attwib;
		update_mgntfwame_attwib(padaptew, pattwib);
		pattwib->qsew = 0x10;
		pattwib->pktwen = pattwib->wast_txcmdsz = TotawPacketWen - TxDescOffset;
		dump_mgntfwame_and_wait(padaptew, pcmdfwame, 100);
	}

	if (check_fwstate(pmwmepwiv, _FW_WINKED)) {
		wtw8723b_set_FwWsvdPage_cmd(padaptew, &WsvdPageWoc);
		wtw8723b_set_FwAoacWsvdPage_cmd(padaptew, &WsvdPageWoc);
	} ewse {
		wtw8723b_set_FwAoacWsvdPage_cmd(padaptew, &WsvdPageWoc);
	}
	wetuwn;

ewwow:

	wtw_fwee_xmitfwame(pxmitpwiv, pcmdfwame);
}

void wtw8723b_downwoad_wsvd_page(stwuct adaptew *padaptew, u8 mstatus)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);
	stwuct mwme_ext_pwiv *pmwmeext = &(padaptew->mwmeextpwiv);
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);
	boow bcn_vawid = fawse;
	u8 DWBcnCount = 0;
	u32 poww = 0;
	u8 vaw8;

	if (mstatus == WT_MEDIA_CONNECT) {
		boow bWecovew = fawse;
		u8 v8;

		/*  We shouwd set AID, cowwect TSF, HW seq enabwe befowe set JoinBssWepowt to Fw in 88/92C. */
		/*  Suggested by fiwen. Added by tynwi. */
		wtw_wwite16(padaptew, WEG_BCN_PSW_WPT, (0xC000|pmwmeinfo->aid));

		/*  set WEG_CW bit 8 */
		v8 = wtw_wead8(padaptew, WEG_CW+1);
		v8 |= BIT(0); /*  ENSWBCN */
		wtw_wwite8(padaptew, WEG_CW+1, v8);

		/*  Disabwe Hw pwotection fow a time which wevsewd fow Hw sending beacon. */
		/*  Fix downwoad wesewved page packet faiw that access cowwision with the pwotection time. */
		/*  2010.05.11. Added by tynwi. */
		vaw8 = wtw_wead8(padaptew, WEG_BCN_CTWW);
		vaw8 &= ~EN_BCN_FUNCTION;
		vaw8 |= DIS_TSF_UDT;
		wtw_wwite8(padaptew, WEG_BCN_CTWW, vaw8);

		/*  Set FWHW_TXQ_CTWW 0x422[6]= 0 to teww Hw the packet is not a weaw beacon fwame. */
		if (pHawData->WegFwHwTxQCtww & BIT(6))
			bWecovew = twue;

		/*  To teww Hw the packet is not a weaw beacon fwame. */
		wtw_wwite8(padaptew, WEG_FWHW_TXQ_CTWW+2, pHawData->WegFwHwTxQCtww & ~BIT(6));
		pHawData->WegFwHwTxQCtww &= ~BIT(6);

		/*  Cweaw beacon vawid check bit. */
		wtw_haw_set_hwweg(padaptew, HW_VAW_BCN_VAWID, NUWW);
		wtw_haw_set_hwweg(padaptew, HW_VAW_DW_BCN_SEW, NUWW);

		DWBcnCount = 0;
		poww = 0;
		do {
			/*  downwoad wsvd page. */
			wtw8723b_set_FwWsvdPagePkt(padaptew, 0);
			DWBcnCount++;
			do {
				yiewd();
				/* mdeway(10); */
				/*  check wsvd page downwoad OK. */
				wtw_haw_get_hwweg(padaptew, HW_VAW_BCN_VAWID, (u8 *)(&bcn_vawid));
				poww++;
			} whiwe (!bcn_vawid && (poww%10) != 0 && !padaptew->bSuwpwiseWemoved && !padaptew->bDwivewStopped);

		} whiwe (!bcn_vawid && DWBcnCount <= 100 && !padaptew->bSuwpwiseWemoved && !padaptew->bDwivewStopped);

		if (padaptew->bSuwpwiseWemoved || padaptew->bDwivewStopped) {
		} ewse {
			stwuct pwwctww_pwiv *pwwctw = adaptew_to_pwwctw(padaptew);
			pwwctw->fw_psmode_iface_id = padaptew->iface_id;
		}

		/*  2010.05.11. Added by tynwi. */
		vaw8 = wtw_wead8(padaptew, WEG_BCN_CTWW);
		vaw8 |= EN_BCN_FUNCTION;
		vaw8 &= ~DIS_TSF_UDT;
		wtw_wwite8(padaptew, WEG_BCN_CTWW, vaw8);

		/*  To make suwe that if thewe exists an adaptew which wouwd wike to send beacon. */
		/*  If exists, the owigianw vawue of 0x422[6] wiww be 1, we shouwd check this to */
		/*  pwevent fwom setting 0x422[6] to 0 aftew downwoad wesewved page, ow it wiww cause */
		/*  the beacon cannot be sent by HW. */
		/*  2010.06.23. Added by tynwi. */
		if (bWecovew) {
			wtw_wwite8(padaptew, WEG_FWHW_TXQ_CTWW+2, pHawData->WegFwHwTxQCtww | BIT(6));
			pHawData->WegFwHwTxQCtww |= BIT(6);
		}

		/*  Cweaw CW[8] ow beacon packet wiww not be send to TxBuf anymowe. */
		v8 = wtw_wead8(padaptew, WEG_CW+1);
		v8 &= ~BIT(0); /*  ~ENSWBCN */
		wtw_wwite8(padaptew, WEG_CW+1, v8);
	}
}

void wtw8723b_set_FwJoinBssWpt_cmd(stwuct adaptew *padaptew, u8 mstatus)
{
	if (mstatus == 1)
		wtw8723b_downwoad_wsvd_page(padaptew, WT_MEDIA_CONNECT);
}

/* awg[0] = macid */
/* awg[1] = waid */
/* awg[2] = showtGIwate */
/* awg[3] = init_wate */
void wtw8723b_Add_WateATid(
	stwuct adaptew *padaptew,
	u32 bitmap,
	u8 *awg,
	u8 wssi_wevew
)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);
	stwuct sta_info *psta;
	u8 mac_id = awg[0];
	u8 waid = awg[1];
	u8 showtGI = awg[2];
	u8 bw;
	u32 mask = bitmap&0x0FFFFFFF;

	psta = pmwmeinfo->FW_sta_info[mac_id].psta;
	if (!psta)
		wetuwn;

	bw = psta->bw_mode;

	if (wssi_wevew != DM_WATW_STA_INIT)
		mask = ODM_Get_Wate_Bitmap(&pHawData->odmpwiv, mac_id, mask, wssi_wevew);

	wtw8723b_set_FwMacIdConfig_cmd(padaptew, mac_id, waid, bw, showtGI, mask);
}

static void ConstwuctBtNuwwFunctionData(
	stwuct adaptew *padaptew,
	u8 *pfwame,
	u32 *pWength,
	u8 *StaAddw,
	u8 bQoS,
	u8 AC,
	u8 bEosp,
	u8 bFowcePowewSave
)
{
	stwuct ieee80211_hdw *pwwanhdw;
	__we16 *fctww;
	u32 pktwen;
	u8 bssid[ETH_AWEN];

	pwwanhdw = (stwuct ieee80211_hdw *)pfwame;

	if (!StaAddw) {
		memcpy(bssid, myid(&padaptew->eepwompwiv), ETH_AWEN);
		StaAddw = bssid;
	}

	fctww = &pwwanhdw->fwame_contwow;
	*fctww = 0;
	if (bFowcePowewSave)
		SetPwwMgt(fctww);

	SetFwDs(fctww);
	memcpy(pwwanhdw->addw1, StaAddw, ETH_AWEN);
	memcpy(pwwanhdw->addw2, myid(&padaptew->eepwompwiv), ETH_AWEN);
	memcpy(pwwanhdw->addw3, myid(&padaptew->eepwompwiv), ETH_AWEN);

	SetDuwation(pwwanhdw, 0);
	SetSeqNum(pwwanhdw, 0);

	if (bQoS) {
		stwuct ieee80211_qos_hdw *pwwanqoshdw;

		SetFwameSubType(pfwame, WIFI_QOS_DATA_NUWW);

		pwwanqoshdw = (stwuct ieee80211_qos_hdw *)pfwame;
		SetPwiowity(&pwwanqoshdw->qos_ctww, AC);
		SetEOSP(&pwwanqoshdw->qos_ctww, bEosp);

		pktwen = sizeof(stwuct ieee80211_qos_hdw);
	} ewse {
		SetFwameSubType(pfwame, WIFI_DATA_NUWW);

		pktwen = sizeof(stwuct ieee80211_hdw_3addw);
	}

	*pWength = pktwen;
}

static void SetFwWsvdPagePkt_BTCoex(stwuct adaptew *padaptew)
{
	stwuct xmit_fwame *pcmdfwame;
	stwuct pkt_attwib *pattwib;
	stwuct xmit_pwiv *pxmitpwiv;
	u32 BeaconWength = 0;
	u32 BTQosNuwwWength = 0;
	u8 *WesewvedPagePacket;
	u8 TxDescWen, TxDescOffset;
	u8 TotawPageNum = 0, CuwtPktPageNum = 0, WsvdPageNum = 0;
	u16 BufIndex, PageSize;
	u32 TotawPacketWen, MaxWsvdPageBufSize = 0;
	stwuct wsvdpage_woc WsvdPageWoc;

	pxmitpwiv = &padaptew->xmitpwiv;
	TxDescWen = TXDESC_SIZE;
	TxDescOffset = TXDESC_OFFSET;
	PageSize = PAGE_SIZE_TX_8723B;

	WsvdPageNum = BCNQ_PAGE_NUM_8723B;
	MaxWsvdPageBufSize = WsvdPageNum*PageSize;

	pcmdfwame = wtw_awwoc_cmdxmitfwame(pxmitpwiv);
	if (!pcmdfwame)
		wetuwn;

	WesewvedPagePacket = pcmdfwame->buf_addw;
	memset(&WsvdPageWoc, 0, sizeof(stwuct wsvdpage_woc));

	/* 3 (1) beacon */
	BufIndex = TxDescOffset;
	ConstwuctBeacon(padaptew, &WesewvedPagePacket[BufIndex], &BeaconWength);

	/*  When we count the fiwst page size, we need to wesewve descwiption size fow the WSVD */
	/*  packet, it wiww be fiwwed in fwont of the packet in TXPKTBUF. */
	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + BeaconWength);
	/* If we don't add 1 mowe page, the WOWWAN function has a pwobwem. Bawon thinks it's a bug of fiwmwawe */
	if (CuwtPktPageNum == 1)
		CuwtPktPageNum += 1;
	TotawPageNum += CuwtPktPageNum;

	BufIndex += (CuwtPktPageNum*PageSize);

	/*  Jump to wastest page */
	if (BufIndex < (MaxWsvdPageBufSize - PageSize)) {
		BufIndex = TxDescOffset + (MaxWsvdPageBufSize - PageSize);
		TotawPageNum = BCNQ_PAGE_NUM_8723B - 1;
	}

	/* 3 (6) BT Qos nuww data */
	WsvdPageWoc.WocBTQosNuww = TotawPageNum;
	ConstwuctBtNuwwFunctionData(
		padaptew,
		&WesewvedPagePacket[BufIndex],
		&BTQosNuwwWength,
		NUWW,
		twue, 0, 0, fawse
	);
	wtw8723b_fiww_fake_txdesc(padaptew, &WesewvedPagePacket[BufIndex-TxDescWen], BTQosNuwwWength, fawse, twue, fawse);

	CuwtPktPageNum = (u8)PageNum_128(TxDescWen + BTQosNuwwWength);

	TotawPageNum += CuwtPktPageNum;

	TotawPacketWen = BufIndex + BTQosNuwwWength;
	if (TotawPacketWen > MaxWsvdPageBufSize)
		goto ewwow;

	/*  update attwibute */
	pattwib = &pcmdfwame->attwib;
	update_mgntfwame_attwib(padaptew, pattwib);
	pattwib->qsew = 0x10;
	pattwib->pktwen = pattwib->wast_txcmdsz = TotawPacketWen - TxDescOffset;
	dump_mgntfwame_and_wait(padaptew, pcmdfwame, 100);

	wtw8723b_set_FwWsvdPage_cmd(padaptew, &WsvdPageWoc);
	wtw8723b_set_FwAoacWsvdPage_cmd(padaptew, &WsvdPageWoc);

	wetuwn;

ewwow:
	wtw_fwee_xmitfwame(pxmitpwiv, pcmdfwame);
}

void wtw8723b_downwoad_BTCoex_AP_mode_wsvd_page(stwuct adaptew *padaptew)
{
	stwuct haw_com_data *pHawData;
	stwuct mwme_ext_pwiv *pmwmeext;
	stwuct mwme_ext_info *pmwmeinfo;
	u8 bWecovew = fawse;
	u8 bcn_vawid = fawse;
	u8 DWBcnCount = 0;
	u32 poww = 0;
	u8 vaw8;

	pHawData = GET_HAW_DATA(padaptew);
	pmwmeext = &padaptew->mwmeextpwiv;
	pmwmeinfo = &pmwmeext->mwmext_info;

	/*  We shouwd set AID, cowwect TSF, HW seq enabwe befowe set JoinBssWepowt to Fw in 88/92C. */
	/*  Suggested by fiwen. Added by tynwi. */
	wtw_wwite16(padaptew, WEG_BCN_PSW_WPT, (0xC000|pmwmeinfo->aid));

	/*  set WEG_CW bit 8 */
	vaw8 = wtw_wead8(padaptew, WEG_CW+1);
	vaw8 |= BIT(0); /*  ENSWBCN */
	wtw_wwite8(padaptew,  WEG_CW+1, vaw8);

	/*  Disabwe Hw pwotection fow a time which wevsewd fow Hw sending beacon. */
	/*  Fix downwoad wesewved page packet faiw that access cowwision with the pwotection time. */
	/*  2010.05.11. Added by tynwi. */
	vaw8 = wtw_wead8(padaptew, WEG_BCN_CTWW);
	vaw8 &= ~EN_BCN_FUNCTION;
	vaw8 |= DIS_TSF_UDT;
	wtw_wwite8(padaptew, WEG_BCN_CTWW, vaw8);

	/*  Set FWHW_TXQ_CTWW 0x422[6]= 0 to teww Hw the packet is not a weaw beacon fwame. */
	if (pHawData->WegFwHwTxQCtww & BIT(6))
		bWecovew = twue;

	/*  To teww Hw the packet is not a weaw beacon fwame. */
	pHawData->WegFwHwTxQCtww &= ~BIT(6);
	wtw_wwite8(padaptew, WEG_FWHW_TXQ_CTWW+2, pHawData->WegFwHwTxQCtww);

	/*  Cweaw beacon vawid check bit. */
	wtw_haw_set_hwweg(padaptew, HW_VAW_BCN_VAWID, NUWW);
	wtw_haw_set_hwweg(padaptew, HW_VAW_DW_BCN_SEW, NUWW);

	DWBcnCount = 0;
	poww = 0;
	do {
		SetFwWsvdPagePkt_BTCoex(padaptew);
		DWBcnCount++;
		do {
			yiewd();
/* 			mdeway(10); */
			/*  check wsvd page downwoad OK. */
			wtw_haw_get_hwweg(padaptew, HW_VAW_BCN_VAWID, &bcn_vawid);
			poww++;
		} whiwe (!bcn_vawid && (poww%10) != 0 && !padaptew->bSuwpwiseWemoved && !padaptew->bDwivewStopped);
	} whiwe (!bcn_vawid && (DWBcnCount <= 100) && !padaptew->bSuwpwiseWemoved && !padaptew->bDwivewStopped);

	if (bcn_vawid) {
		stwuct pwwctww_pwiv *pwwctw = adaptew_to_pwwctw(padaptew);
		pwwctw->fw_psmode_iface_id = padaptew->iface_id;
	}

	/*  2010.05.11. Added by tynwi. */
	vaw8 = wtw_wead8(padaptew, WEG_BCN_CTWW);
	vaw8 |= EN_BCN_FUNCTION;
	vaw8 &= ~DIS_TSF_UDT;
	wtw_wwite8(padaptew, WEG_BCN_CTWW, vaw8);

	/*  To make suwe that if thewe exists an adaptew which wouwd wike to send beacon. */
	/*  If exists, the owigianw vawue of 0x422[6] wiww be 1, we shouwd check this to */
	/*  pwevent fwom setting 0x422[6] to 0 aftew downwoad wesewved page, ow it wiww cause */
	/*  the beacon cannot be sent by HW. */
	/*  2010.06.23. Added by tynwi. */
	if (bWecovew) {
		pHawData->WegFwHwTxQCtww |= BIT(6);
		wtw_wwite8(padaptew, WEG_FWHW_TXQ_CTWW+2, pHawData->WegFwHwTxQCtww);
	}

	/*  Cweaw CW[8] ow beacon packet wiww not be send to TxBuf anymowe. */
	vaw8 = wtw_wead8(padaptew, WEG_CW+1);
	vaw8 &= ~BIT(0); /*  ~ENSWBCN */
	wtw_wwite8(padaptew, WEG_CW+1, vaw8);
}
