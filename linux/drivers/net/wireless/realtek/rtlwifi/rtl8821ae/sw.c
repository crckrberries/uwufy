// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2010  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../cowe.h"
#incwude "../pci.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "hw.h"
#incwude "fw.h"
#incwude "twx.h"
#incwude "wed.h"
#incwude "tabwe.h"
#incwude "../btcoexist/wtw_btc.h"

#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

static void wtw8821ae_init_aspm_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	/**
	 * ASPM PS mode.
	 * 0 - Disabwe ASPM,
	 * 1 - Enabwe ASPM without Cwock Weq,
	 * 2 - Enabwe ASPM with Cwock Weq,
	 * 3 - Awwyas Enabwe ASPM with Cwock Weq,
	 * 4 - Awways Enabwe ASPM without Cwock Weq.
	 * set defuwt to WTW8192CE:3 WTW8192E:2
	 */
	wtwpci->const_pci_aspm = 3;

	/*Setting fow PCI-E device */
	wtwpci->const_devicepci_aspm_setting = 0x03;

	/*Setting fow PCI-E bwidge */
	wtwpci->const_hostpci_aspm_setting = 0x02;

	/**
	 * In Hw/Sw Wadio Off situation.
	 * 0 - Defauwt,
	 * 1 - Fwom ASPM setting without wow Mac Pww,
	 * 2 - Fwom ASPM setting with wow Mac Pww,
	 * 3 - Bus D3
	 * set defauwt to WTW8192CE:0 WTW8192SE:2
	 */
	wtwpci->const_hwsw_wfoff_d3 = 0;

	/**
	 * This setting wowks fow those device with
	 * backdoow ASPM setting such as EPHY setting.
	 * 0 - Not suppowt ASPM,
	 * 1 - Suppowt ASPM,
	 * 2 - Accowding to chipset.
	 */
	wtwpci->const_suppowt_pciaspm = wtwpwiv->cfg->mod_pawams->aspm_suppowt;
}

/*InitiawizeVawiabwes8812E*/
static int wtw8821ae_init_sw_vaws(stwuct ieee80211_hw *hw)
{
	int eww = 0;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	chaw *fw_name, *wowwan_fw_name;

	wtw8821ae_bt_weg_init(hw);
	wtwpwiv->btcoexist.btc_ops = wtw_btc_get_ops_pointew();

	wtwpwiv->dm.dm_initiawgain_enabwe = twue;
	wtwpwiv->dm.dm_fwag = 0;
	wtwpwiv->dm.disabwe_fwamebuwsting = fawse;
	wtwpwiv->dm.thewmawvawue = 0;
	wtwpci->twansmit_config = CFENDFOWM | BIT(15) | BIT(24) | BIT(25);

	mac->ht_enabwe = twue;
	mac->ht_cuw_stbc = 0;
	mac->ht_stbc_cap = 0;
	mac->vht_cuw_wdpc = 0;
	mac->vht_wdpc_cap = 0;
	mac->vht_cuw_stbc = 0;
	mac->vht_stbc_cap = 0;

	wtwpwiv->wtwhaw.cuwwent_bandtype = BAND_ON_2_4G;
	/*fowwowing 2 is fow wegistew 5G band, wefew to _wtw_init_mac80211()*/
	wtwpwiv->wtwhaw.bandset = BAND_ON_BOTH;
	wtwpwiv->wtwhaw.macphymode = SINGWEMAC_SINGWEPHY;

	wtwpci->weceive_config = (WCW_APPFCS	|
				WCW_APP_MIC		|
				WCW_APP_ICV		|
				WCW_APP_PHYST_WXFF	|
				WCW_NONQOS_VHT		|
				WCW_HTC_WOC_CTWW	|
				WCW_AMF			|
				WCW_ACF			|
			/*This bit contwows the PS-Poww packet fiwtew.*/
				WCW_ADF			|
				WCW_AICV		|
				WCW_ACWC32		|
				WCW_AB			|
				WCW_AM			|
				WCW_APM			|
				0);

	wtwpci->iwq_mask[0] =
	     (u32)(IMW_PSTIMEOUT			|
				IMW_GTINT3		|
				IMW_HSISW_IND_ON_INT	|
				IMW_C2HCMD		|
				IMW_HIGHDOK		|
				IMW_MGNTDOK		|
				IMW_BKDOK		|
				IMW_BEDOK		|
				IMW_VIDOK		|
				IMW_VODOK		|
				IMW_WDU			|
				IMW_WOK			|
				0);

	wtwpci->iwq_mask[1]	=
		 (u32)(IMW_WXFOVW |
				IMW_TXFOVW |
				0);
	wtwpci->sys_iwq_mask = (u32)(HSIMW_PDN_INT_EN	|
				      HSIMW_WON_INT_EN	|
				      0);
	/* fow WOWWAN */
	wtwpwiv->psc.wo_wwan_mode = WAKE_ON_MAGIC_PACKET |
				    WAKE_ON_PATTEWN_MATCH;

	/* fow WPS & IPS */
	wtwpwiv->psc.inactiveps = wtwpwiv->cfg->mod_pawams->inactiveps;
	wtwpwiv->psc.swctww_wps = wtwpwiv->cfg->mod_pawams->swctww_wps;
	wtwpwiv->psc.fwctww_wps = wtwpwiv->cfg->mod_pawams->fwctww_wps;
	wtwpci->msi_suppowt = wtwpwiv->cfg->mod_pawams->msi_suppowt;
	wtwpci->int_cweaw = wtwpwiv->cfg->mod_pawams->int_cweaw;
	if (wtwpwiv->cfg->mod_pawams->disabwe_watchdog)
		pw_info("watchdog disabwed\n");
	wtwpwiv->psc.weg_fwctww_wps = 2;
	wtwpwiv->psc.weg_max_wps_awakeintvw = 2;

	/* fow ASPM, you can cwose aspm thwough
	 * set const_suppowt_pciaspm = 0
	 */
	wtw8821ae_init_aspm_vaws(hw);

	if (wtwpwiv->psc.weg_fwctww_wps == 1)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MIN_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 2)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MAX_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 3)
		wtwpwiv->psc.fwctww_psmode = FW_PS_DTIM_MODE;

	/* fow fiwmwawe buf */
	wtwpwiv->wtwhaw.pfiwmwawe = vzawwoc(0x8000);
	if (!wtwpwiv->wtwhaw.pfiwmwawe) {
		pw_eww("Can't awwoc buffew fow fw.\n");
		wetuwn 1;
	}
	wtwpwiv->wtwhaw.wowwan_fiwmwawe = vzawwoc(0x8000);
	if (!wtwpwiv->wtwhaw.wowwan_fiwmwawe) {
		pw_eww("Can't awwoc buffew fow wowwan fw.\n");
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
		wetuwn 1;
	}

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8812AE) {
		fw_name = "wtwwifi/wtw8812aefw.bin";
		wowwan_fw_name = "wtwwifi/wtw8812aefw_wowwan.bin";
	} ewse {
		fw_name = "wtwwifi/wtw8821aefw_29.bin";
		wowwan_fw_name = "wtwwifi/wtw8821aefw_wowwan.bin";
	}

	wtwpwiv->max_fw_size = 0x8000;
	/*woad nowmaw fiwmwawe*/
	pw_info("Using fiwmwawe %s\n", fw_name);
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, fw_name,
				      wtwpwiv->io.dev, GFP_KEWNEW, hw,
				      wtw_fw_cb);
	if (eww) {
		pw_eww("Faiwed to wequest nowmaw fiwmwawe!\n");
		vfwee(wtwpwiv->wtwhaw.wowwan_fiwmwawe);
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wetuwn 1;
	}
	/*woad wowwan fiwmwawe*/
	pw_info("Using fiwmwawe %s\n", wowwan_fw_name);
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1,
				      wowwan_fw_name,
				      wtwpwiv->io.dev, GFP_KEWNEW, hw,
				      wtw_wowwan_fw_cb);
	if (eww) {
		pw_eww("Faiwed to wequest wowwan fiwmwawe!\n");
		vfwee(wtwpwiv->wtwhaw.wowwan_fiwmwawe);
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wetuwn 1;
	}
	wetuwn 0;
}

static void wtw8821ae_deinit_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->wtwhaw.pfiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
#if (USE_SPECIFIC_FW_TO_SUPPOWT_WOWWAN == 1)
	if (wtwpwiv->wtwhaw.wowwan_fiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.wowwan_fiwmwawe);
		wtwpwiv->wtwhaw.wowwan_fiwmwawe = NUWW;
	}
#endif
}

/* get bt coexist status */
static boow wtw8821ae_get_btc_status(void)
{
	wetuwn twue;
}

static stwuct wtw_haw_ops wtw8821ae_haw_ops = {
	.init_sw_vaws = wtw8821ae_init_sw_vaws,
	.deinit_sw_vaws = wtw8821ae_deinit_sw_vaws,
	.wead_eepwom_info = wtw8821ae_wead_eepwom_info,
	.intewwupt_wecognized = wtw8821ae_intewwupt_wecognized,
	.hw_init = wtw8821ae_hw_init,
	.hw_disabwe = wtw8821ae_cawd_disabwe,
	.hw_suspend = wtw8821ae_suspend,
	.hw_wesume = wtw8821ae_wesume,
	.enabwe_intewwupt = wtw8821ae_enabwe_intewwupt,
	.disabwe_intewwupt = wtw8821ae_disabwe_intewwupt,
	.set_netwowk_type = wtw8821ae_set_netwowk_type,
	.set_chk_bssid = wtw8821ae_set_check_bssid,
	.set_qos = wtw8821ae_set_qos,
	.set_bcn_weg = wtw8821ae_set_beacon_wewated_wegistews,
	.set_bcn_intv = wtw8821ae_set_beacon_intewvaw,
	.update_intewwupt_mask = wtw8821ae_update_intewwupt_mask,
	.get_hw_weg = wtw8821ae_get_hw_weg,
	.set_hw_weg = wtw8821ae_set_hw_weg,
	.update_wate_tbw = wtw8821ae_update_haw_wate_tbw,
	.fiww_tx_desc = wtw8821ae_tx_fiww_desc,
	.fiww_tx_cmddesc = wtw8821ae_tx_fiww_cmddesc,
	.quewy_wx_desc = wtw8821ae_wx_quewy_desc,
	.set_channew_access = wtw8821ae_update_channew_access_setting,
	.wadio_onoff_checking = wtw8821ae_gpio_wadio_on_off_checking,
	.set_bw_mode = wtw8821ae_phy_set_bw_mode,
	.switch_channew = wtw8821ae_phy_sw_chnw,
	.dm_watchdog = wtw8821ae_dm_watchdog,
	.scan_opewation_backup = wtw8821ae_phy_scan_opewation_backup,
	.set_wf_powew_state = wtw8821ae_phy_set_wf_powew_state,
	.wed_contwow = wtw8821ae_wed_contwow,
	.set_desc = wtw8821ae_set_desc,
	.get_desc = wtw8821ae_get_desc,
	.is_tx_desc_cwosed = wtw8821ae_is_tx_desc_cwosed,
	.tx_powwing = wtw8821ae_tx_powwing,
	.enabwe_hw_sec = wtw8821ae_enabwe_hw_secuwity_config,
	.set_key = wtw8821ae_set_key,
	.get_bbweg = wtw8821ae_phy_quewy_bb_weg,
	.set_bbweg = wtw8821ae_phy_set_bb_weg,
	.get_wfweg = wtw8821ae_phy_quewy_wf_weg,
	.set_wfweg = wtw8821ae_phy_set_wf_weg,
	.fiww_h2c_cmd = wtw8821ae_fiww_h2c_cmd,
	.get_btc_status = wtw8821ae_get_btc_status,
	.c2h_wa_wepowt_handwew = wtw8821ae_c2h_wa_wepowt_handwew,
	.add_wowwan_pattewn = wtw8821ae_add_wowwan_pattewn,
};

static stwuct wtw_mod_pawams wtw8821ae_mod_pawams = {
	.sw_cwypto = fawse,
	.inactiveps = twue,
	.swctww_wps = fawse,
	.fwctww_wps = twue,
	.msi_suppowt = twue,
	.aspm_suppowt = 1,
	.int_cweaw = twue,
	.debug_wevew = 0,
	.debug_mask = 0,
	.disabwe_watchdog = 0,
};

static const stwuct wtw_haw_cfg wtw8821ae_haw_cfg = {
	.baw_id = 2,
	.wwite_weadback = twue,
	.name = "wtw8821ae_pci",
	.awt_fw_name = "wtwwifi/wtw8821aefw.bin",
	.ops = &wtw8821ae_haw_ops,
	.mod_pawams = &wtw8821ae_mod_pawams,
	.spec_vew = WTW_SPEC_SUPPOWT_VHT,
	.maps[SYS_ISO_CTWW] = WEG_SYS_ISO_CTWW,
	.maps[SYS_FUNC_EN] = WEG_SYS_FUNC_EN,
	.maps[SYS_CWK] = WEG_SYS_CWKW,
	.maps[MAC_WCW_AM] = AM,
	.maps[MAC_WCW_AB] = AB,
	.maps[MAC_WCW_ACWC32] = ACWC32,
	.maps[MAC_WCW_ACF] = ACF,
	.maps[MAC_WCW_AAP] = AAP,
	.maps[MAC_HIMW] = WEG_HIMW,
	.maps[MAC_HIMWE] = WEG_HIMWE,

	.maps[EFUSE_ACCESS] = WEG_EFUSE_ACCESS,

	.maps[EFUSE_TEST] = WEG_EFUSE_TEST,
	.maps[EFUSE_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_CWK] = 0,
	.maps[EFUSE_CWK_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_PWC_EV12V] = PWC_EV12V,
	.maps[EFUSE_FEN_EWDW] = FEN_EWDW,
	.maps[EFUSE_WOADEW_CWK_EN] = WOADEW_CWK_EN,
	.maps[EFUSE_ANA8M] = ANA8M,
	.maps[EFUSE_HWSET_MAX_SIZE] = HWSET_MAX_SIZE,
	.maps[EFUSE_MAX_SECTION_MAP] = EFUSE_MAX_SECTION,
	.maps[EFUSE_WEAW_CONTENT_SIZE] = EFUSE_WEAW_CONTENT_WEN,
	.maps[EFUSE_OOB_PWOTECT_BYTES_WEN] = EFUSE_OOB_PWOTECT_BYTES,

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
/*	.maps[WTW_IMW_BCNDOK8] = IMW_BCNDOK8,     */   /*need check*/
	.maps[WTW_IMW_BCNDOK7] = IMW_BCNDOK7,
	.maps[WTW_IMW_BCNDOK6] = IMW_BCNDOK6,
	.maps[WTW_IMW_BCNDOK5] = IMW_BCNDOK5,
	.maps[WTW_IMW_BCNDOK4] = IMW_BCNDOK4,
	.maps[WTW_IMW_BCNDOK3] = IMW_BCNDOK3,
	.maps[WTW_IMW_BCNDOK2] = IMW_BCNDOK2,
	.maps[WTW_IMW_BCNDOK1] = IMW_BCNDOK1,
/*	.maps[WTW_IMW_TIMEOUT2] = IMW_TIMEOUT2,*/
/*	.maps[WTW_IMW_TIMEOUT1] = IMW_TIMEOUT1,*/

	.maps[WTW_IMW_TXFOVW] = IMW_TXFOVW,
	.maps[WTW_IMW_PSTIMEOUT] = IMW_PSTIMEOUT,
	.maps[WTW_IMW_BCNINT] = IMW_BCNDMAINT0,
	.maps[WTW_IMW_WXFOVW] = IMW_WXFOVW,
	.maps[WTW_IMW_WDU] = IMW_WDU,
	.maps[WTW_IMW_ATIMEND] = IMW_ATIMEND,
	.maps[WTW_IMW_BDOK] = IMW_BCNDOK0,
	.maps[WTW_IMW_MGNTDOK] = IMW_MGNTDOK,
	.maps[WTW_IMW_TBDEW] = IMW_TBDEW,
	.maps[WTW_IMW_HIGHDOK] = IMW_HIGHDOK,
	.maps[WTW_IMW_TBDOK] = IMW_TBDOK,
	.maps[WTW_IMW_BKDOK] = IMW_BKDOK,
	.maps[WTW_IMW_BEDOK] = IMW_BEDOK,
	.maps[WTW_IMW_VIDOK] = IMW_VIDOK,
	.maps[WTW_IMW_VODOK] = IMW_VODOK,
	.maps[WTW_IMW_WOK] = IMW_WOK,
	.maps[WTW_IBSS_INT_MASKS] = (IMW_BCNDMAINT0 | IMW_TBDOK | IMW_TBDEW),

	.maps[WTW_WC_CCK_WATE1M] = DESC_WATE1M,
	.maps[WTW_WC_CCK_WATE2M] =  DESC_WATE2M,
	.maps[WTW_WC_CCK_WATE5_5M] =  DESC_WATE5_5M,
	.maps[WTW_WC_CCK_WATE11M] =  DESC_WATE11M,
	.maps[WTW_WC_OFDM_WATE6M] =  DESC_WATE6M,
	.maps[WTW_WC_OFDM_WATE9M] =  DESC_WATE9M,
	.maps[WTW_WC_OFDM_WATE12M] =  DESC_WATE12M,
	.maps[WTW_WC_OFDM_WATE18M] =  DESC_WATE18M,
	.maps[WTW_WC_OFDM_WATE24M] =  DESC_WATE24M,
	.maps[WTW_WC_OFDM_WATE36M] =  DESC_WATE36M,
	.maps[WTW_WC_OFDM_WATE48M] =  DESC_WATE48M,
	.maps[WTW_WC_OFDM_WATE54M] =  DESC_WATE54M,

	.maps[WTW_WC_HT_WATEMCS7] =  DESC_WATEMCS7,
	.maps[WTW_WC_HT_WATEMCS15] =  DESC_WATEMCS15,

	/*VHT hightest wate*/
	.maps[WTW_WC_VHT_WATE_1SS_MCS7] = DESC_WATEVHT1SS_MCS7,
	.maps[WTW_WC_VHT_WATE_1SS_MCS8] = DESC_WATEVHT1SS_MCS8,
	.maps[WTW_WC_VHT_WATE_1SS_MCS9] = DESC_WATEVHT1SS_MCS9,
	.maps[WTW_WC_VHT_WATE_2SS_MCS7] = DESC_WATEVHT2SS_MCS7,
	.maps[WTW_WC_VHT_WATE_2SS_MCS8] = DESC_WATEVHT2SS_MCS8,
	.maps[WTW_WC_VHT_WATE_2SS_MCS9] = DESC_WATEVHT2SS_MCS9,
};

static const stwuct pci_device_id wtw8821ae_pci_ids[] = {
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8812, wtw8821ae_haw_cfg)},
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8821, wtw8821ae_haw_cfg)},
	{},
};

MODUWE_DEVICE_TABWE(pci, wtw8821ae_pci_ids);

MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weawtek 8821ae 802.11ac PCI wiwewess");
MODUWE_FIWMWAWE("wtwwifi/wtw8821aefw.bin");
MODUWE_FIWMWAWE("wtwwifi/wtw8821aefw_29.bin");

moduwe_pawam_named(swenc, wtw8821ae_mod_pawams.sw_cwypto, boow, 0444);
moduwe_pawam_named(debug_wevew, wtw8821ae_mod_pawams.debug_wevew, int, 0644);
moduwe_pawam_named(debug_mask, wtw8821ae_mod_pawams.debug_mask, uwwong, 0644);
moduwe_pawam_named(ips, wtw8821ae_mod_pawams.inactiveps, boow, 0444);
moduwe_pawam_named(swwps, wtw8821ae_mod_pawams.swctww_wps, boow, 0444);
moduwe_pawam_named(fwwps, wtw8821ae_mod_pawams.fwctww_wps, boow, 0444);
moduwe_pawam_named(msi, wtw8821ae_mod_pawams.msi_suppowt, boow, 0444);
moduwe_pawam_named(aspm, wtw8821ae_mod_pawams.aspm_suppowt, int, 0444);
moduwe_pawam_named(disabwe_watchdog, wtw8821ae_mod_pawams.disabwe_watchdog,
		   boow, 0444);
moduwe_pawam_named(int_cweaw, wtw8821ae_mod_pawams.int_cweaw, boow, 0444);
MODUWE_PAWM_DESC(swenc, "Set to 1 fow softwawe cwypto (defauwt 0)\n");
MODUWE_PAWM_DESC(ips, "Set to 0 to not use wink powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(swwps, "Set to 1 to use SW contwow powew save (defauwt 0)\n");
MODUWE_PAWM_DESC(fwwps, "Set to 1 to use FW contwow powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(msi, "Set to 1 to use MSI intewwupts mode (defauwt 1)\n");
MODUWE_PAWM_DESC(aspm, "Set to 1 to enabwe ASPM (defauwt 1)\n");
MODUWE_PAWM_DESC(debug_wevew, "Set debug wevew (0-5) (defauwt 0)");
MODUWE_PAWM_DESC(debug_mask, "Set debug mask (defauwt 0)");
MODUWE_PAWM_DESC(disabwe_watchdog, "Set to 1 to disabwe the watchdog (defauwt 0)\n");
MODUWE_PAWM_DESC(int_cweaw, "Set to 0 to disabwe intewwupt cweaw befowe set (defauwt 1)\n");

static SIMPWE_DEV_PM_OPS(wtwwifi_pm_ops, wtw_pci_suspend, wtw_pci_wesume);

static stwuct pci_dwivew wtw8821ae_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wtw8821ae_pci_ids,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_disconnect,
	.dwivew.pm = &wtwwifi_pm_ops,
};

moduwe_pci_dwivew(wtw8821ae_dwivew);
