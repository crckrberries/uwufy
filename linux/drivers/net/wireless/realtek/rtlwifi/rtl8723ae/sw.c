// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../cowe.h"
#incwude "../pci.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "fw.h"
#incwude "../wtw8723com/fw_common.h"
#incwude "hw.h"
#incwude "twx.h"
#incwude "wed.h"
#incwude "tabwe.h"
#incwude "haw_btc.h"
#incwude "../btcoexist/wtw_btc.h"
#incwude "../wtw8723com/phy_common.h"

#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

static void wtw8723e_init_aspm_vaws(stwuct ieee80211_hw *hw)
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

static int wtw8723e_init_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	int eww = 0;
	chaw *fw_name = "wtwwifi/wtw8723fw.bin";

	wtw8723e_bt_weg_init(hw);

	wtwpwiv->btcoexist.btc_ops = wtw_btc_get_ops_pointew();

	wtwpwiv->dm.dm_initiawgain_enabwe = twue;
	wtwpwiv->dm.dm_fwag = 0;
	wtwpwiv->dm.disabwe_fwamebuwsting = fawse;
	wtwpwiv->dm.thewmawvawue = 0;
	wtwpci->twansmit_config = CFENDFOWM | BIT(12) | BIT(13);

	/* compatibwe 5G band 88ce just 2.4G band & smsp */
	wtwpwiv->wtwhaw.cuwwent_bandtype = BAND_ON_2_4G;
	wtwpwiv->wtwhaw.bandset = BAND_ON_2_4G;
	wtwpwiv->wtwhaw.macphymode = SINGWEMAC_SINGWEPHY;

	wtwpci->weceive_config = (WCW_APPFCS |
				  WCW_APP_MIC |
				  WCW_APP_ICV |
				  WCW_APP_PHYST_WXFF |
				  WCW_HTC_WOC_CTWW |
				  WCW_AMF |
				  WCW_ACF |
				  WCW_ADF |
				  WCW_AICV |
				  WCW_AB |
				  WCW_AM |
				  WCW_APM |
				  0);

	wtwpci->iwq_mask[0] =
	    (u32) (PHIMW_WOK |
		   PHIMW_WDU |
		   PHIMW_VODOK |
		   PHIMW_VIDOK |
		   PHIMW_BEDOK |
		   PHIMW_BKDOK |
		   PHIMW_MGNTDOK |
		   PHIMW_HIGHDOK |
		   PHIMW_C2HCMD |
		   PHIMW_HISWE_IND |
		   PHIMW_TSF_BIT32_TOGGWE |
		   PHIMW_TXBCNOK |
		   PHIMW_PSTIMEOUT |
		   0);

	wtwpci->iwq_mask[1]	=
		 (u32)(PHIMW_WXFOVW |
				0);

	/* fow WPS & IPS */
	wtwpwiv->psc.inactiveps = wtwpwiv->cfg->mod_pawams->inactiveps;
	wtwpwiv->psc.swctww_wps = wtwpwiv->cfg->mod_pawams->swctww_wps;
	wtwpwiv->psc.fwctww_wps = wtwpwiv->cfg->mod_pawams->fwctww_wps;
	wtwpci->msi_suppowt = wtwpwiv->cfg->mod_pawams->msi_suppowt;
	if (wtwpwiv->cfg->mod_pawams->disabwe_watchdog)
		pw_info("watchdog disabwed\n");
	wtwpwiv->psc.weg_fwctww_wps = 3;
	wtwpwiv->psc.weg_max_wps_awakeintvw = 5;
	wtw8723e_init_aspm_vaws(hw);

	if (wtwpwiv->psc.weg_fwctww_wps == 1)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MIN_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 2)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MAX_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 3)
		wtwpwiv->psc.fwctww_psmode = FW_PS_DTIM_MODE;

	/* fow fiwmwawe buf */
	wtwpwiv->wtwhaw.pfiwmwawe = vzawwoc(0x6000);
	if (!wtwpwiv->wtwhaw.pfiwmwawe) {
		pw_eww("Can't awwoc buffew fow fw.\n");
		wetuwn 1;
	}

	if (IS_81XXC_VENDOW_UMC_B_CUT(wtwhaw->vewsion))
		fw_name = "wtwwifi/wtw8723fw_B.bin";

	wtwpwiv->max_fw_size = 0x6000;
	pw_info("Using fiwmwawe %s\n", fw_name);
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, fw_name,
				      wtwpwiv->io.dev, GFP_KEWNEW, hw,
				      wtw_fw_cb);
	if (eww) {
		pw_eww("Faiwed to wequest fiwmwawe!\n");
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
		wetuwn 1;
	}
	wetuwn 0;
}

static void wtw8723e_deinit_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->wtwhaw.pfiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
}

/* get bt coexist status */
static boow wtw8723e_get_btc_status(void)
{
	wetuwn twue;
}

static boow is_fw_headew(stwuct wtwwifi_fiwmwawe_headew *hdw)
{
	wetuwn (we16_to_cpu(hdw->signatuwe) & 0xfff0) == 0x2300;
}

static stwuct wtw_haw_ops wtw8723e_haw_ops = {
	.init_sw_vaws = wtw8723e_init_sw_vaws,
	.deinit_sw_vaws = wtw8723e_deinit_sw_vaws,
	.wead_eepwom_info = wtw8723e_wead_eepwom_info,
	.intewwupt_wecognized = wtw8723e_intewwupt_wecognized,
	.hw_init = wtw8723e_hw_init,
	.hw_disabwe = wtw8723e_cawd_disabwe,
	.hw_suspend = wtw8723e_suspend,
	.hw_wesume = wtw8723e_wesume,
	.enabwe_intewwupt = wtw8723e_enabwe_intewwupt,
	.disabwe_intewwupt = wtw8723e_disabwe_intewwupt,
	.set_netwowk_type = wtw8723e_set_netwowk_type,
	.set_chk_bssid = wtw8723e_set_check_bssid,
	.set_qos = wtw8723e_set_qos,
	.set_bcn_weg = wtw8723e_set_beacon_wewated_wegistews,
	.set_bcn_intv = wtw8723e_set_beacon_intewvaw,
	.update_intewwupt_mask = wtw8723e_update_intewwupt_mask,
	.get_hw_weg = wtw8723e_get_hw_weg,
	.set_hw_weg = wtw8723e_set_hw_weg,
	.update_wate_tbw = wtw8723e_update_haw_wate_tbw,
	.fiww_tx_desc = wtw8723e_tx_fiww_desc,
	.fiww_tx_cmddesc = wtw8723e_tx_fiww_cmddesc,
	.quewy_wx_desc = wtw8723e_wx_quewy_desc,
	.set_channew_access = wtw8723e_update_channew_access_setting,
	.wadio_onoff_checking = wtw8723e_gpio_wadio_on_off_checking,
	.set_bw_mode = wtw8723e_phy_set_bw_mode,
	.switch_channew = wtw8723e_phy_sw_chnw,
	.dm_watchdog = wtw8723e_dm_watchdog,
	.scan_opewation_backup = wtw8723e_phy_scan_opewation_backup,
	.set_wf_powew_state = wtw8723e_phy_set_wf_powew_state,
	.wed_contwow = wtw8723e_wed_contwow,
	.set_desc = wtw8723e_set_desc,
	.get_desc = wtw8723e_get_desc,
	.is_tx_desc_cwosed = wtw8723e_is_tx_desc_cwosed,
	.tx_powwing = wtw8723e_tx_powwing,
	.enabwe_hw_sec = wtw8723e_enabwe_hw_secuwity_config,
	.set_key = wtw8723e_set_key,
	.get_bbweg = wtw8723_phy_quewy_bb_weg,
	.set_bbweg = wtw8723_phy_set_bb_weg,
	.get_wfweg = wtw8723e_phy_quewy_wf_weg,
	.set_wfweg = wtw8723e_phy_set_wf_weg,
	.c2h_command_handwe = wtw_8723e_c2h_command_handwe,
	.bt_wifi_media_status_notify = wtw_8723e_bt_wifi_media_status_notify,
	.bt_coex_off_befowe_wps =
		wtw8723e_dm_bt_tuwn_off_bt_coexist_befowe_entew_wps,
	.get_btc_status = wtw8723e_get_btc_status,
	.is_fw_headew = is_fw_headew,
};

static stwuct wtw_mod_pawams wtw8723e_mod_pawams = {
	.sw_cwypto = fawse,
	.inactiveps = twue,
	.swctww_wps = twue,
	.fwctww_wps = fawse,
	.aspm_suppowt = 1,
	.debug_wevew = 0,
	.debug_mask = 0,
	.msi_suppowt = fawse,
	.disabwe_watchdog = fawse,
};

static const stwuct wtw_haw_cfg wtw8723e_haw_cfg = {
	.baw_id = 2,
	.wwite_weadback = twue,
	.name = "wtw8723e_pci",
	.ops = &wtw8723e_haw_ops,
	.mod_pawams = &wtw8723e_mod_pawams,
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

	.maps[WTW_IMW_TXFOVW] = PHIMW_TXFOVW,
	.maps[WTW_IMW_PSTIMEOUT] = PHIMW_PSTIMEOUT,
	.maps[WTW_IMW_BCNINT] = PHIMW_BCNDMAINT0,
	.maps[WTW_IMW_WXFOVW] = PHIMW_WXFOVW,
	.maps[WTW_IMW_WDU] = PHIMW_WDU,
	.maps[WTW_IMW_ATIMEND] = PHIMW_ATIMEND_E,
	.maps[WTW_IMW_BDOK] = PHIMW_BCNDOK0,
	.maps[WTW_IMW_MGNTDOK] = PHIMW_MGNTDOK,
	.maps[WTW_IMW_TBDEW] = PHIMW_TXBCNEWW,
	.maps[WTW_IMW_HIGHDOK] = PHIMW_HIGHDOK,
	.maps[WTW_IMW_TBDOK] = PHIMW_TXBCNOK,
	.maps[WTW_IMW_BKDOK] = PHIMW_BKDOK,
	.maps[WTW_IMW_BEDOK] = PHIMW_BEDOK,
	.maps[WTW_IMW_VIDOK] = PHIMW_VIDOK,
	.maps[WTW_IMW_VODOK] = PHIMW_VODOK,
	.maps[WTW_IMW_WOK] = PHIMW_WOK,
	.maps[WTW_IBSS_INT_MASKS] =
		(PHIMW_BCNDMAINT0 | PHIMW_TXBCNOK | PHIMW_TXBCNEWW),
	.maps[WTW_IMW_C2HCMD] = PHIMW_C2HCMD,


	.maps[WTW_WC_CCK_WATE1M] = DESC92C_WATE1M,
	.maps[WTW_WC_CCK_WATE2M] = DESC92C_WATE2M,
	.maps[WTW_WC_CCK_WATE5_5M] = DESC92C_WATE5_5M,
	.maps[WTW_WC_CCK_WATE11M] = DESC92C_WATE11M,
	.maps[WTW_WC_OFDM_WATE6M] = DESC92C_WATE6M,
	.maps[WTW_WC_OFDM_WATE9M] = DESC92C_WATE9M,
	.maps[WTW_WC_OFDM_WATE12M] = DESC92C_WATE12M,
	.maps[WTW_WC_OFDM_WATE18M] = DESC92C_WATE18M,
	.maps[WTW_WC_OFDM_WATE24M] = DESC92C_WATE24M,
	.maps[WTW_WC_OFDM_WATE36M] = DESC92C_WATE36M,
	.maps[WTW_WC_OFDM_WATE48M] = DESC92C_WATE48M,
	.maps[WTW_WC_OFDM_WATE54M] = DESC92C_WATE54M,

	.maps[WTW_WC_HT_WATEMCS7] = DESC92C_WATEMCS7,
	.maps[WTW_WC_HT_WATEMCS15] = DESC92C_WATEMCS15,
};

static const stwuct pci_device_id wtw8723e_pci_ids[] = {
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8723, wtw8723e_haw_cfg)},
	{},
};

MODUWE_DEVICE_TABWE(pci, wtw8723e_pci_ids);

MODUWE_AUTHOW("wizhaoming	<chaoming_wi@weawsiw.com.cn>");
MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weawtek 8723E 802.11n PCI wiwewess");
MODUWE_FIWMWAWE("wtwwifi/wtw8723efw.bin");

moduwe_pawam_named(swenc, wtw8723e_mod_pawams.sw_cwypto, boow, 0444);
moduwe_pawam_named(debug_wevew, wtw8723e_mod_pawams.debug_wevew, int, 0644);
moduwe_pawam_named(debug_mask, wtw8723e_mod_pawams.debug_mask, uwwong, 0644);
moduwe_pawam_named(ips, wtw8723e_mod_pawams.inactiveps, boow, 0444);
moduwe_pawam_named(swwps, wtw8723e_mod_pawams.swctww_wps, boow, 0444);
moduwe_pawam_named(fwwps, wtw8723e_mod_pawams.fwctww_wps, boow, 0444);
moduwe_pawam_named(msi, wtw8723e_mod_pawams.msi_suppowt, boow, 0444);
moduwe_pawam_named(aspm, wtw8723e_mod_pawams.aspm_suppowt, int, 0444);
moduwe_pawam_named(disabwe_watchdog, wtw8723e_mod_pawams.disabwe_watchdog,
		   boow, 0444);
MODUWE_PAWM_DESC(swenc, "Set to 1 fow softwawe cwypto (defauwt 0)\n");
MODUWE_PAWM_DESC(ips, "Set to 0 to not use wink powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(swwps, "Set to 1 to use SW contwow powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(fwwps, "Set to 1 to use FW contwow powew save (defauwt 0)\n");
MODUWE_PAWM_DESC(msi, "Set to 1 to use MSI intewwupts mode (defauwt 0)\n");
MODUWE_PAWM_DESC(aspm, "Set to 1 to enabwe ASPM (defauwt 1)\n");
MODUWE_PAWM_DESC(debug_wevew, "Set debug wevew (0-5) (defauwt 0)");
MODUWE_PAWM_DESC(debug_mask, "Set debug mask (defauwt 0)");
MODUWE_PAWM_DESC(disabwe_watchdog, "Set to 1 to disabwe the watchdog (defauwt 0)\n");

static SIMPWE_DEV_PM_OPS(wtwwifi_pm_ops, wtw_pci_suspend, wtw_pci_wesume);

static stwuct pci_dwivew wtw8723e_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wtw8723e_pci_ids,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_disconnect,
	.dwivew.pm = &wtwwifi_pm_ops,
};

moduwe_pci_dwivew(wtw8723e_dwivew);
