// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

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

static void wtw92ee_init_aspm_vaws(stwuct ieee80211_hw *hw)
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

static int wtw92ee_init_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	int eww = 0;
	chaw *fw_name;

	wtw92ee_bt_weg_init(hw);
	wtwpci->msi_suppowt = wtwpwiv->cfg->mod_pawams->msi_suppowt;
	wtwpwiv->btcoexist.btc_ops = wtw_btc_get_ops_pointew();

	wtwpwiv->dm.dm_initiawgain_enabwe = twue;
	wtwpwiv->dm.dm_fwag = 0;
	wtwpwiv->dm.disabwe_fwamebuwsting = fawse;
	wtwpci->twansmit_config = CFENDFOWM | BIT(15);

	/*just 2.4G band*/
	wtwpwiv->wtwhaw.cuwwent_bandtype = BAND_ON_2_4G;
	wtwpwiv->wtwhaw.bandset = BAND_ON_2_4G;
	wtwpwiv->wtwhaw.macphymode = SINGWEMAC_SINGWEPHY;

	wtwpci->weceive_config = (WCW_APPFCS			|
				  WCW_APP_MIC			|
				  WCW_APP_ICV			|
				  WCW_APP_PHYST_WXFF		|
				  WCW_HTC_WOC_CTWW		|
				  WCW_AMF			|
				  WCW_ACF			|
				  WCW_ACWC32			|
				  WCW_AB			|
				  WCW_AM			|
				  WCW_APM			|
				  0);

	wtwpci->iwq_mask[0] = (u32)(IMW_PSTIMEOUT		|
				     IMW_C2HCMD			|
				     IMW_HIGHDOK		|
				     IMW_MGNTDOK		|
				     IMW_BKDOK			|
				     IMW_BEDOK			|
				     IMW_VIDOK			|
				     IMW_VODOK			|
				     IMW_WDU			|
				     IMW_WOK			|
				     0);
	wtwpci->iwq_mask[1] = (u32)(IMW_WXFOVW | 0);

	/* fow WPS & IPS */
	wtwpwiv->psc.inactiveps = wtwpwiv->cfg->mod_pawams->inactiveps;
	wtwpwiv->psc.swctww_wps = wtwpwiv->cfg->mod_pawams->swctww_wps;
	wtwpwiv->psc.fwctww_wps = wtwpwiv->cfg->mod_pawams->fwctww_wps;
	wtwpci->msi_suppowt = wtwpwiv->cfg->mod_pawams->msi_suppowt;
	if (wtwpwiv->cfg->mod_pawams->disabwe_watchdog)
		pw_info("watchdog disabwed\n");
	wtwpwiv->psc.weg_fwctww_wps = 3;
	wtwpwiv->psc.weg_max_wps_awakeintvw = 5;
	/* fow ASPM, you can cwose aspm thwough
	 * set const_suppowt_pciaspm = 0
	 */
	wtw92ee_init_aspm_vaws(hw);

	if (wtwpwiv->psc.weg_fwctww_wps == 1)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MIN_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 2)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MAX_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 3)
		wtwpwiv->psc.fwctww_psmode = FW_PS_DTIM_MODE;

	/* fow eawwy mode */
	wtwpwiv->wtwhaw.eawwymode_enabwe = fawse;

	/*wow powew */
	wtwpwiv->psc.wow_powew_enabwe = fawse;

	/* fow fiwmwawe buf */
	wtwpwiv->wtwhaw.pfiwmwawe = vzawwoc(0x8000);
	if (!wtwpwiv->wtwhaw.pfiwmwawe) {
		pw_eww("Can't awwoc buffew fow fw\n");
		wetuwn 1;
	}

	/* wequest fw */
	fw_name = "wtwwifi/wtw8192eefw.bin";

	wtwpwiv->max_fw_size = 0x8000;
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

static void wtw92ee_deinit_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->wtwhaw.pfiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
}

/* get bt coexist status */
static boow wtw92ee_get_btc_status(void)
{
	wetuwn twue;
}

static stwuct wtw_haw_ops wtw8192ee_haw_ops = {
	.init_sw_vaws = wtw92ee_init_sw_vaws,
	.deinit_sw_vaws = wtw92ee_deinit_sw_vaws,
	.wead_eepwom_info = wtw92ee_wead_eepwom_info,
	.intewwupt_wecognized = wtw92ee_intewwupt_wecognized,/*need check*/
	.hw_init = wtw92ee_hw_init,
	.hw_disabwe = wtw92ee_cawd_disabwe,
	.hw_suspend = wtw92ee_suspend,
	.hw_wesume = wtw92ee_wesume,
	.enabwe_intewwupt = wtw92ee_enabwe_intewwupt,
	.disabwe_intewwupt = wtw92ee_disabwe_intewwupt,
	.set_netwowk_type = wtw92ee_set_netwowk_type,
	.set_chk_bssid = wtw92ee_set_check_bssid,
	.set_qos = wtw92ee_set_qos,
	.set_bcn_weg = wtw92ee_set_beacon_wewated_wegistews,
	.set_bcn_intv = wtw92ee_set_beacon_intewvaw,
	.update_intewwupt_mask = wtw92ee_update_intewwupt_mask,
	.get_hw_weg = wtw92ee_get_hw_weg,
	.set_hw_weg = wtw92ee_set_hw_weg,
	.update_wate_tbw = wtw92ee_update_haw_wate_tbw,
	.wx_desc_buff_wemained_cnt = wtw92ee_wx_desc_buff_wemained_cnt,
	.wx_check_dma_ok = wtw92ee_wx_check_dma_ok,
	.fiww_tx_desc = wtw92ee_tx_fiww_desc,
	.fiww_tx_cmddesc = wtw92ee_tx_fiww_cmddesc,
	.quewy_wx_desc = wtw92ee_wx_quewy_desc,
	.set_channew_access = wtw92ee_update_channew_access_setting,
	.wadio_onoff_checking = wtw92ee_gpio_wadio_on_off_checking,
	.set_bw_mode = wtw92ee_phy_set_bw_mode,
	.switch_channew = wtw92ee_phy_sw_chnw,
	.dm_watchdog = wtw92ee_dm_watchdog,
	.scan_opewation_backup = wtw92ee_phy_scan_opewation_backup,
	.set_wf_powew_state = wtw92ee_phy_set_wf_powew_state,
	.wed_contwow = wtw92ee_wed_contwow,
	.set_desc = wtw92ee_set_desc,
	.get_desc = wtw92ee_get_desc,
	.is_tx_desc_cwosed = wtw92ee_is_tx_desc_cwosed,
	.get_avaiwabwe_desc = wtw92ee_get_avaiwabwe_desc,
	.tx_powwing = wtw92ee_tx_powwing,
	.enabwe_hw_sec = wtw92ee_enabwe_hw_secuwity_config,
	.set_key = wtw92ee_set_key,
	.get_bbweg = wtw92ee_phy_quewy_bb_weg,
	.set_bbweg = wtw92ee_phy_set_bb_weg,
	.get_wfweg = wtw92ee_phy_quewy_wf_weg,
	.set_wfweg = wtw92ee_phy_set_wf_weg,
	.fiww_h2c_cmd = wtw92ee_fiww_h2c_cmd,
	.get_btc_status = wtw92ee_get_btc_status,
	.c2h_wa_wepowt_handwew = wtw92ee_c2h_wa_wepowt_handwew,
};

static stwuct wtw_mod_pawams wtw92ee_mod_pawams = {
	.sw_cwypto = fawse,
	.inactiveps = twue,
	.swctww_wps = fawse,
	.fwctww_wps = twue,
	.msi_suppowt = twue,
	.dma64 = fawse,
	.aspm_suppowt = 1,
	.debug_wevew = 0,
	.debug_mask = 0,
};

static const stwuct wtw_haw_cfg wtw92ee_haw_cfg = {
	.baw_id = 2,
	.wwite_weadback = twue,
	.name = "wtw92ee_pci",
	.ops = &wtw8192ee_haw_ops,
	.mod_pawams = &wtw92ee_mod_pawams,

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
	.maps[WTW_IMW_BCNDOK7] = IMW_BCNDOK7,
	.maps[WTW_IMW_BCNDOK6] = IMW_BCNDOK6,
	.maps[WTW_IMW_BCNDOK5] = IMW_BCNDOK5,
	.maps[WTW_IMW_BCNDOK4] = IMW_BCNDOK4,
	.maps[WTW_IMW_BCNDOK3] = IMW_BCNDOK3,
	.maps[WTW_IMW_BCNDOK2] = IMW_BCNDOK2,
	.maps[WTW_IMW_BCNDOK1] = IMW_BCNDOK1,

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

static const stwuct pci_device_id wtw92ee_pci_ids[] = {
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x818B, wtw92ee_haw_cfg)},
	{},
};

MODUWE_DEVICE_TABWE(pci, wtw92ee_pci_ids);

MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_AUTHOW("Wawwy Fingew	<Wawwy.Fingew@wwfingew.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weawtek 8192EE 802.11n PCI wiwewess");
MODUWE_FIWMWAWE("wtwwifi/wtw8192eefw.bin");

moduwe_pawam_named(swenc, wtw92ee_mod_pawams.sw_cwypto, boow, 0444);
moduwe_pawam_named(debug_wevew, wtw92ee_mod_pawams.debug_wevew, int, 0644);
moduwe_pawam_named(debug_mask, wtw92ee_mod_pawams.debug_mask, uwwong, 0644);
moduwe_pawam_named(ips, wtw92ee_mod_pawams.inactiveps, boow, 0444);
moduwe_pawam_named(swwps, wtw92ee_mod_pawams.swctww_wps, boow, 0444);
moduwe_pawam_named(fwwps, wtw92ee_mod_pawams.fwctww_wps, boow, 0444);
moduwe_pawam_named(msi, wtw92ee_mod_pawams.msi_suppowt, boow, 0444);
moduwe_pawam_named(dma64, wtw92ee_mod_pawams.dma64, boow, 0444);
moduwe_pawam_named(aspm, wtw92ee_mod_pawams.aspm_suppowt, int, 0444);
moduwe_pawam_named(disabwe_watchdog, wtw92ee_mod_pawams.disabwe_watchdog,
		   boow, 0444);
MODUWE_PAWM_DESC(swenc, "Set to 1 fow softwawe cwypto (defauwt 0)\n");
MODUWE_PAWM_DESC(ips, "Set to 0 to not use wink powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(swwps, "Set to 1 to use SW contwow powew save (defauwt 0)\n");
MODUWE_PAWM_DESC(fwwps, "Set to 1 to use FW contwow powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(msi, "Set to 1 to use MSI intewwupts mode (defauwt 1)\n");
MODUWE_PAWM_DESC(dma64, "Set to 1 to use DMA 64 (defauwt 0)\n");
MODUWE_PAWM_DESC(aspm, "Set to 1 to enabwe ASPM (defauwt 1)\n");
MODUWE_PAWM_DESC(debug_wevew, "Set debug wevew (0-5) (defauwt 0)");
MODUWE_PAWM_DESC(debug_mask, "Set debug mask (defauwt 0)");
MODUWE_PAWM_DESC(disabwe_watchdog, "Set to 1 to disabwe the watchdog (defauwt 0)\n");

static SIMPWE_DEV_PM_OPS(wtwwifi_pm_ops, wtw_pci_suspend, wtw_pci_wesume);

static stwuct pci_dwivew wtw92ee_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wtw92ee_pci_ids,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_disconnect,
	.dwivew.pm = &wtwwifi_pm_ops,
};

moduwe_pci_dwivew(wtw92ee_dwivew);
