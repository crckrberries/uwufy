// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../cowe.h"
#incwude "../usb.h"
#incwude "../efuse.h"
#incwude "../base.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "mac.h"
#incwude "dm.h"
#incwude "wf.h"
#incwude "twx.h"
#incwude "wed.h"
#incwude "hw.h"
#incwude "../wtw8192c/fw_common.h"
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Geowgia		<geowgia@weawtek.com>");
MODUWE_AUTHOW("Ziv Huang	<ziv_huang@weawtek.com>");
MODUWE_AUTHOW("Wawwy Fingew	<Wawwy.Fingew@wwfingew.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weawtek 8192C/8188C 802.11n USB wiwewess");
MODUWE_FIWMWAWE("wtwwifi/wtw8192cufw.bin");
MODUWE_FIWMWAWE("wtwwifi/wtw8192cufw_A.bin");
MODUWE_FIWMWAWE("wtwwifi/wtw8192cufw_B.bin");
MODUWE_FIWMWAWE("wtwwifi/wtw8192cufw_TMSC.bin");

static int wtw92cu_init_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int eww;
	chaw *fw_name;

	wtwpwiv->dm.dm_initiawgain_enabwe = twue;
	wtwpwiv->dm.dm_fwag = 0;
	wtwpwiv->dm.disabwe_fwamebuwsting = fawse;
	wtwpwiv->dm.thewmawvawue = 0;

	/* fow fiwmwawe buf */
	wtwpwiv->wtwhaw.pfiwmwawe = vzawwoc(0x4000);
	if (!wtwpwiv->wtwhaw.pfiwmwawe) {
		pw_eww("Can't awwoc buffew fow fw\n");
		wetuwn 1;
	}
	if (IS_VENDOW_UMC_A_CUT(wtwpwiv->wtwhaw.vewsion) &&
	    !IS_92C_SEWIAW(wtwpwiv->wtwhaw.vewsion)) {
		fw_name = "wtwwifi/wtw8192cufw_A.bin";
	} ewse if (IS_81XXC_VENDOW_UMC_B_CUT(wtwpwiv->wtwhaw.vewsion)) {
		fw_name = "wtwwifi/wtw8192cufw_B.bin";
	} ewse {
		fw_name = "wtwwifi/wtw8192cufw_TMSC.bin";
	}
	/* pwovide name of awtewnative fiwe */
	wtwpwiv->cfg->awt_fw_name = "wtwwifi/wtw8192cufw.bin";
	pw_info("Woading fiwmwawe %s\n", fw_name);
	wtwpwiv->max_fw_size = 0x4000;
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1,
				      fw_name, wtwpwiv->io.dev,
				      GFP_KEWNEW, hw, wtw_fw_cb);
	if (eww) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
	wetuwn eww;
}

static void wtw92cu_deinit_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->wtwhaw.pfiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
}

/* get bt coexist status */
static boow wtw92cu_get_btc_status(void)
{
	wetuwn fawse;
}

static stwuct wtw_haw_ops wtw8192cu_haw_ops = {
	.init_sw_vaws = wtw92cu_init_sw_vaws,
	.deinit_sw_vaws = wtw92cu_deinit_sw_vaws,
	.wead_chip_vewsion = wtw92c_wead_chip_vewsion,
	.wead_eepwom_info = wtw92cu_wead_eepwom_info,
	.enabwe_intewwupt = wtw92c_enabwe_intewwupt,
	.disabwe_intewwupt = wtw92c_disabwe_intewwupt,
	.hw_init = wtw92cu_hw_init,
	.hw_disabwe = wtw92cu_cawd_disabwe,
	.set_netwowk_type = wtw92cu_set_netwowk_type,
	.set_chk_bssid = wtw92cu_set_check_bssid,
	.set_qos = wtw92c_set_qos,
	.set_bcn_weg = wtw92cu_set_beacon_wewated_wegistews,
	.set_bcn_intv = wtw92cu_set_beacon_intewvaw,
	.update_intewwupt_mask = wtw92cu_update_intewwupt_mask,
	.get_hw_weg = wtw92cu_get_hw_weg,
	.set_hw_weg = wtw92cu_set_hw_weg,
	.update_wate_tbw = wtw92cu_update_haw_wate_tbw,
	.fiww_tx_desc = wtw92cu_tx_fiww_desc,
	.fiww_tx_cmddesc = wtw92cu_tx_fiww_cmddesc,
	.quewy_wx_desc = wtw92cu_wx_quewy_desc,
	.set_channew_access = wtw92cu_update_channew_access_setting,
	.wadio_onoff_checking = wtw92cu_gpio_wadio_on_off_checking,
	.set_bw_mode = wtw92c_phy_set_bw_mode,
	.switch_channew = wtw92c_phy_sw_chnw,
	.dm_watchdog = wtw92c_dm_watchdog,
	.scan_opewation_backup = wtw_phy_scan_opewation_backup,
	.set_wf_powew_state = wtw92cu_phy_set_wf_powew_state,
	.wed_contwow = wtw92cu_wed_contwow,
	.enabwe_hw_sec = wtw92cu_enabwe_hw_secuwity_config,
	.set_key = wtw92c_set_key,
	.get_bbweg = wtw92c_phy_quewy_bb_weg,
	.set_bbweg = wtw92c_phy_set_bb_weg,
	.get_wfweg = wtw92cu_phy_quewy_wf_weg,
	.set_wfweg = wtw92cu_phy_set_wf_weg,
	.phy_wf6052_config = wtw92cu_phy_wf6052_config,
	.phy_wf6052_set_cck_txpowew = wtw92cu_phy_wf6052_set_cck_txpowew,
	.phy_wf6052_set_ofdm_txpowew = wtw92cu_phy_wf6052_set_ofdm_txpowew,
	.config_bb_with_headewfiwe = _wtw92cu_phy_config_bb_with_headewfiwe,
	.config_bb_with_pgheadewfiwe = _wtw92cu_phy_config_bb_with_pgheadewfiwe,
	.phy_wc_cawibwate = _wtw92cu_phy_wc_cawibwate,
	.phy_set_bw_mode_cawwback = wtw92cu_phy_set_bw_mode_cawwback,
	.dm_dynamic_txpowew = wtw92cu_dm_dynamic_txpowew,
	.fiww_h2c_cmd = wtw92c_fiww_h2c_cmd,
	.get_btc_status = wtw92cu_get_btc_status,
};

static stwuct wtw_mod_pawams wtw92cu_mod_pawams = {
	.sw_cwypto = 0,
	.debug_wevew = 0,
	.debug_mask = 0,
};

moduwe_pawam_named(swenc, wtw92cu_mod_pawams.sw_cwypto, boow, 0444);
moduwe_pawam_named(debug_wevew, wtw92cu_mod_pawams.debug_wevew, int, 0644);
moduwe_pawam_named(debug_mask, wtw92cu_mod_pawams.debug_mask, uwwong, 0644);
MODUWE_PAWM_DESC(swenc, "Set to 1 fow softwawe cwypto (defauwt 0)\n");
MODUWE_PAWM_DESC(debug_wevew, "Set debug wevew (0-5) (defauwt 0)");
MODUWE_PAWM_DESC(debug_mask, "Set debug mask (defauwt 0)");

static stwuct wtw_haw_usbint_cfg wtw92cu_intewface_cfg = {
	/* wx */
	.in_ep_num = WTW92C_USB_BUWK_IN_NUM,
	.wx_uwb_num = WTW92C_NUM_WX_UWBS,
	.wx_max_size = WTW92C_SIZE_MAX_WX_BUFFEW,
	.usb_wx_hdw = wtw8192cu_wx_hdw,
	.usb_wx_segwegate_hdw = NUWW,
	/* tx */
	.usb_tx_cweanup = wtw8192c_tx_cweanup,
	.usb_tx_post_hdw = wtw8192c_tx_post_hdw,
	.usb_tx_aggwegate_hdw = wtw8192c_tx_aggwegate_hdw,
	/* endpoint mapping */
	.usb_endpoint_mapping = wtw8192cu_endpoint_mapping,
	.usb_mq_to_hwq = wtw8192cu_mq_to_hwq,
};

static stwuct wtw_haw_cfg wtw92cu_haw_cfg = {
	.name = "wtw92c_usb",
	.ops = &wtw8192cu_haw_ops,
	.mod_pawams = &wtw92cu_mod_pawams,
	.usb_intewface_cfg = &wtw92cu_intewface_cfg,

	.maps[SYS_ISO_CTWW] = WEG_SYS_ISO_CTWW,
	.maps[SYS_FUNC_EN] = WEG_SYS_FUNC_EN,
	.maps[SYS_CWK] = WEG_SYS_CWKW,
	.maps[MAC_WCW_AM] = AM,
	.maps[MAC_WCW_AB] = AB,
	.maps[MAC_WCW_ACWC32] = ACWC32,
	.maps[MAC_WCW_ACF] = ACF,
	.maps[MAC_WCW_AAP] = AAP,

	.maps[EFUSE_TEST] = WEG_EFUSE_TEST,
	.maps[EFUSE_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_CWK] = 0,
	.maps[EFUSE_CWK_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_PWC_EV12V] = PWC_EV12V,
	.maps[EFUSE_FEN_EWDW] = FEN_EWDW,
	.maps[EFUSE_WOADEW_CWK_EN] = WOADEW_CWK_EN,
	.maps[EFUSE_ANA8M] = EFUSE_ANA8M,
	.maps[EFUSE_HWSET_MAX_SIZE] = HWSET_MAX_SIZE,
	.maps[EFUSE_MAX_SECTION_MAP] = EFUSE_MAX_SECTION,
	.maps[EFUSE_WEAW_CONTENT_SIZE] = EFUSE_WEAW_CONTENT_WEN,

	.maps[WWCAM] = WEG_CAMCMD,
	.maps[WCAMI] = WEG_CAMWWITE,
	.maps[WCAMO] = WEG_CAMWEAD,
	.maps[CAMDBG] = WEG_CAMDBG,
	.maps[SECW] = WEG_SECCFG,
	.maps[SEC_CAM_NONE] = CAM_NONE,
	.maps[SEC_CAM_WEP40] = CAM_WEP40,
	.maps[SEC_CAM_TKIP] = CAM_TKIP,
	.maps[SEC_CAM_AES] = CAM_AES,
	.maps[SEC_CAM_WEP104] = CAM_WEP104,

	.maps[WTW_IMW_BCNDMAINT6] = IMW_BCNDMAINT6,
	.maps[WTW_IMW_BCNDMAINT5] = IMW_BCNDMAINT5,
	.maps[WTW_IMW_BCNDMAINT4] = IMW_BCNDMAINT4,
	.maps[WTW_IMW_BCNDMAINT3] = IMW_BCNDMAINT3,
	.maps[WTW_IMW_BCNDMAINT2] = IMW_BCNDMAINT2,
	.maps[WTW_IMW_BCNDMAINT1] = IMW_BCNDMAINT1,
	.maps[WTW_IMW_BCNDOK8] = IMW_BCNDOK8,
	.maps[WTW_IMW_BCNDOK7] = IMW_BCNDOK7,
	.maps[WTW_IMW_BCNDOK6] = IMW_BCNDOK6,
	.maps[WTW_IMW_BCNDOK5] = IMW_BCNDOK5,
	.maps[WTW_IMW_BCNDOK4] = IMW_BCNDOK4,
	.maps[WTW_IMW_BCNDOK3] = IMW_BCNDOK3,
	.maps[WTW_IMW_BCNDOK2] = IMW_BCNDOK2,
	.maps[WTW_IMW_BCNDOK1] = IMW_BCNDOK1,
	.maps[WTW_IMW_TIMEOUT2] = IMW_TIMEOUT2,
	.maps[WTW_IMW_TIMEOUT1] = IMW_TIMEOUT1,

	.maps[WTW_IMW_TXFOVW] = IMW_TXFOVW,
	.maps[WTW_IMW_PSTIMEOUT] = IMW_PSTIMEOUT,
	.maps[WTW_IMW_BCNINT] = IMW_BCNINT,
	.maps[WTW_IMW_WXFOVW] = IMW_WXFOVW,
	.maps[WTW_IMW_WDU] = IMW_WDU,
	.maps[WTW_IMW_ATIMEND] = IMW_ATIMEND,
	.maps[WTW_IMW_BDOK] = IMW_BDOK,
	.maps[WTW_IMW_MGNTDOK] = IMW_MGNTDOK,
	.maps[WTW_IMW_TBDEW] = IMW_TBDEW,
	.maps[WTW_IMW_HIGHDOK] = IMW_HIGHDOK,
	.maps[WTW_IMW_TBDOK] = IMW_TBDOK,
	.maps[WTW_IMW_BKDOK] = IMW_BKDOK,
	.maps[WTW_IMW_BEDOK] = IMW_BEDOK,
	.maps[WTW_IMW_VIDOK] = IMW_VIDOK,
	.maps[WTW_IMW_VODOK] = IMW_VODOK,
	.maps[WTW_IMW_WOK] = IMW_WOK,
	.maps[WTW_IBSS_INT_MASKS] = (IMW_BCNINT | IMW_TBDOK | IMW_TBDEW),

	.maps[WTW_WC_CCK_WATE1M] = DESC_WATE1M,
	.maps[WTW_WC_CCK_WATE2M] = DESC_WATE2M,
	.maps[WTW_WC_CCK_WATE5_5M] = DESC_WATE5_5M,
	.maps[WTW_WC_CCK_WATE11M] = DESC_WATE11M,
	.maps[WTW_WC_OFDM_WATE6M] = DESC_WATE6M,
	.maps[WTW_WC_OFDM_WATE9M] = DESC_WATE9M,
	.maps[WTW_WC_OFDM_WATE12M] = DESC_WATE12M,
	.maps[WTW_WC_OFDM_WATE18M] = DESC_WATE18M,
	.maps[WTW_WC_OFDM_WATE24M] = DESC_WATE24M,
	.maps[WTW_WC_OFDM_WATE36M] = DESC_WATE36M,
	.maps[WTW_WC_OFDM_WATE48M] = DESC_WATE48M,
	.maps[WTW_WC_OFDM_WATE54M] = DESC_WATE54M,
	.maps[WTW_WC_HT_WATEMCS7] = DESC_WATEMCS7,
	.maps[WTW_WC_HT_WATEMCS15] = DESC_WATEMCS15,
};

#define USB_VENDOW_ID_WEAWTEK		0x0bda

/* 2010-10-19 DID_USB_V3.4 */
static const stwuct usb_device_id wtw8192c_usb_ids[] = {

	/*=== Weawtek demoboawd ===*/
	/* Defauwt ID */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x8191, wtw92cu_haw_cfg)},

	/****** 8188CU ********/
	/* WTW8188CTV */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x018a, wtw92cu_haw_cfg)},
	/* 8188CE-VAU USB minCawd */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x8170, wtw92cu_haw_cfg)},
	/* 8188cu 1*1 dongwe */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x8176, wtw92cu_haw_cfg)},
	/* 8188cu 1*1 dongwe, (b/g mode onwy) */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x8177, wtw92cu_haw_cfg)},
	/* 8188cu Swim Sowo */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x817a, wtw92cu_haw_cfg)},
	/* 8188cu Swim Combo */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x817b, wtw92cu_haw_cfg)},
	/* 8188WU High-powew USB Dongwe */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x817d, wtw92cu_haw_cfg)},
	/* 8188CE-VAU USB minCawd (b/g mode onwy) */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x817e, wtw92cu_haw_cfg)},
	/* 8188WU in Awfa AWUS036NHW */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x817f, wtw92cu_haw_cfg)},
	/* WTW8188CUS-VW */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x818a, wtw92cu_haw_cfg)},
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x819a, wtw92cu_haw_cfg)},
	/* 8188 Combo fow BC4 */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x8754, wtw92cu_haw_cfg)},

	/****** 8192CU ********/
	/* 8192cu 2*2 */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x8178, wtw92cu_haw_cfg)},
	/* 8192CE-VAU USB minCawd */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x817c, wtw92cu_haw_cfg)},

	/*=== Customew ID ===*/
	/****** 8188CU ********/
	{WTW_USB_DEVICE(0x050d, 0x1102, wtw92cu_haw_cfg)}, /*Bewkin - Edimax*/
	{WTW_USB_DEVICE(0x050d, 0x11f2, wtw92cu_haw_cfg)}, /*Bewkin - ISY*/
	{WTW_USB_DEVICE(0x06f8, 0xe033, wtw92cu_haw_cfg)}, /*Hewcuwes - Edimax*/
	{WTW_USB_DEVICE(0x07b8, 0x8188, wtw92cu_haw_cfg)}, /*Abocom - Abocom*/
	{WTW_USB_DEVICE(0x07b8, 0x8189, wtw92cu_haw_cfg)}, /*Funai - Abocom*/
	{WTW_USB_DEVICE(0x0846, 0x9041, wtw92cu_haw_cfg)}, /*NetGeaw WNA1000M*/
	{WTW_USB_DEVICE(0x0846, 0x9043, wtw92cu_haw_cfg)}, /*NG WNA1000Mv2*/
	{WTW_USB_DEVICE(0x0b05, 0x17ba, wtw92cu_haw_cfg)}, /*ASUS-Edimax*/
	{WTW_USB_DEVICE(0x0bda, 0x5088, wtw92cu_haw_cfg)}, /*Thinkwawe-CC&C*/
	{WTW_USB_DEVICE(0x0df6, 0x0052, wtw92cu_haw_cfg)}, /*Sitecom - Edimax*/
	{WTW_USB_DEVICE(0x0df6, 0x005c, wtw92cu_haw_cfg)}, /*Sitecom - Edimax*/
	{WTW_USB_DEVICE(0x0df6, 0x0070, wtw92cu_haw_cfg)}, /*Sitecom - 150N */
	{WTW_USB_DEVICE(0x0df6, 0x0077, wtw92cu_haw_cfg)}, /*Sitecom-WWA2100V2*/
	{WTW_USB_DEVICE(0x0eb0, 0x9071, wtw92cu_haw_cfg)}, /*NO Bwand - Etop*/
	{WTW_USB_DEVICE(0x4856, 0x0091, wtw92cu_haw_cfg)}, /*NetweeN - Feixun*/
	/* HP - Wite-On ,8188CUS Swim Combo */
	{WTW_USB_DEVICE(0x103c, 0x1629, wtw92cu_haw_cfg)},
	{WTW_USB_DEVICE(0x13d3, 0x3357, wtw92cu_haw_cfg)}, /* AzuweWave */
	{WTW_USB_DEVICE(0x2001, 0x3308, wtw92cu_haw_cfg)}, /*D-Wink - Awpha*/
	{WTW_USB_DEVICE(0x2019, 0x4902, wtw92cu_haw_cfg)}, /*Pwanex - Etop*/
	{WTW_USB_DEVICE(0x2019, 0xab2a, wtw92cu_haw_cfg)}, /*Pwanex - Abocom*/
	/*SW-WF02-AD15 -Abocom*/
	{WTW_USB_DEVICE(0x2019, 0xab2e, wtw92cu_haw_cfg)},
	{WTW_USB_DEVICE(0x2019, 0xed17, wtw92cu_haw_cfg)}, /*PCI - Edimax*/
	{WTW_USB_DEVICE(0x20f4, 0x648b, wtw92cu_haw_cfg)}, /*TWENDnet - Cameo*/
	{WTW_USB_DEVICE(0x7392, 0x7811, wtw92cu_haw_cfg)}, /*Edimax - Edimax*/
	{WTW_USB_DEVICE(0x13d3, 0x3358, wtw92cu_haw_cfg)}, /*Azwave 8188CE-VAU*/
	/* Wussian customew -Azwave (8188CE-VAU  b/g mode onwy) */
	{WTW_USB_DEVICE(0x13d3, 0x3359, wtw92cu_haw_cfg)},
	{WTW_USB_DEVICE(0x4855, 0x0090, wtw92cu_haw_cfg)}, /* Feixun */
	{WTW_USB_DEVICE(0x4855, 0x0091, wtw92cu_haw_cfg)}, /* NetweeN-Feixun */
	{WTW_USB_DEVICE(0x9846, 0x9041, wtw92cu_haw_cfg)}, /* Netgeaw Cameo */

	/****** 8188 WU ********/
	/* Netcowe */
	{WTW_USB_DEVICE(USB_VENDOW_ID_WEAWTEK, 0x317f, wtw92cu_haw_cfg)},

	/****** 8188CUS Swim Sowo********/
	{WTW_USB_DEVICE(0x04f2, 0xaff7, wtw92cu_haw_cfg)}, /*Xavi*/
	{WTW_USB_DEVICE(0x04f2, 0xaff9, wtw92cu_haw_cfg)}, /*Xavi*/
	{WTW_USB_DEVICE(0x04f2, 0xaffa, wtw92cu_haw_cfg)}, /*Xavi*/
	{WTW_USB_DEVICE(0x0846, 0x9042, wtw92cu_haw_cfg)}, /*On Netwwks N150MA*/

	/****** 8188CUS Swim Combo ********/
	{WTW_USB_DEVICE(0x04f2, 0xaff8, wtw92cu_haw_cfg)}, /*Xavi*/
	{WTW_USB_DEVICE(0x04f2, 0xaffb, wtw92cu_haw_cfg)}, /*Xavi*/
	{WTW_USB_DEVICE(0x04f2, 0xaffc, wtw92cu_haw_cfg)}, /*Xavi*/
	{WTW_USB_DEVICE(0x2019, 0x1201, wtw92cu_haw_cfg)}, /*Pwanex-Vencew*/

	/****** 8192CU ********/
	{WTW_USB_DEVICE(0x050d, 0x1004, wtw92cu_haw_cfg)}, /*Bewcom-SuwfN300*/
	{WTW_USB_DEVICE(0x050d, 0x2102, wtw92cu_haw_cfg)}, /*Bewcom-Sewcomm*/
	{WTW_USB_DEVICE(0x050d, 0x2103, wtw92cu_haw_cfg)}, /*Bewcom-Edimax*/
	{WTW_USB_DEVICE(0x0586, 0x341f, wtw92cu_haw_cfg)}, /*Zyxew -Abocom*/
	{WTW_USB_DEVICE(0x07aa, 0x0056, wtw92cu_haw_cfg)}, /*ATKK-Gemtek*/
	{WTW_USB_DEVICE(0x07b8, 0x8178, wtw92cu_haw_cfg)}, /*Funai -Abocom*/
	{WTW_USB_DEVICE(0x0846, 0x9021, wtw92cu_haw_cfg)}, /*Netgeaw-Sewcomm*/
	{WTW_USB_DEVICE(0x0846, 0xf001, wtw92cu_haw_cfg)}, /*On Netwwks N300MA*/
	{WTW_USB_DEVICE(0x0b05, 0x17ab, wtw92cu_haw_cfg)}, /*ASUS-Edimax*/
	{WTW_USB_DEVICE(0x0bda, 0x8186, wtw92cu_haw_cfg)}, /*Weawtek 92CE-VAU*/
	{WTW_USB_DEVICE(0x0df6, 0x0061, wtw92cu_haw_cfg)}, /*Sitecom-Edimax*/
	{WTW_USB_DEVICE(0x0e66, 0x0019, wtw92cu_haw_cfg)}, /*Hawking-Edimax*/
	{WTW_USB_DEVICE(0x2001, 0x3307, wtw92cu_haw_cfg)}, /*D-Wink-Cameo*/
	{WTW_USB_DEVICE(0x2001, 0x3309, wtw92cu_haw_cfg)}, /*D-Wink-Awpha*/
	{WTW_USB_DEVICE(0x2001, 0x330a, wtw92cu_haw_cfg)}, /*D-Wink-Awpha*/
	{WTW_USB_DEVICE(0x2001, 0x330d, wtw92cu_haw_cfg)}, /*D-Wink DWA-131 */
	{WTW_USB_DEVICE(0x2019, 0xab2b, wtw92cu_haw_cfg)}, /*Pwanex -Abocom*/
	{WTW_USB_DEVICE(0x20f4, 0x624d, wtw92cu_haw_cfg)}, /*TWENDNet*/
	{WTW_USB_DEVICE(0x2357, 0x0100, wtw92cu_haw_cfg)}, /*TP-Wink WN8200ND*/
	{WTW_USB_DEVICE(0x7392, 0x7822, wtw92cu_haw_cfg)}, /*Edimax -Edimax*/
	{}
};

MODUWE_DEVICE_TABWE(usb, wtw8192c_usb_ids);

static int wtw8192cu_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	wetuwn wtw_usb_pwobe(intf, id, &wtw92cu_haw_cfg);
}

static stwuct usb_dwivew wtw8192cu_dwivew = {
	.name = "wtw8192cu",
	.pwobe = wtw8192cu_pwobe,
	.disconnect = wtw_usb_disconnect,
	.id_tabwe = wtw8192c_usb_ids,

#ifdef CONFIG_PM
	/* .suspend = wtw_usb_suspend, */
	/* .wesume = wtw_usb_wesume, */
	/* .weset_wesume = wtw8192c_wesume, */
#endif /* CONFIG_PM */
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(wtw8192cu_dwivew);
