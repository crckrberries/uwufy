// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../cowe.h"
#incwude "../pci.h"
#incwude "../base.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "hw.h"
#incwude "sw.h"
#incwude "twx.h"
#incwude "wed.h"

#incwude <winux/moduwe.h>

static void wtw92d_init_aspm_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	/*
	 * ASPM PS mode.
	 * 0 - Disabwe ASPM,
	 * 1 - Enabwe ASPM without Cwock Weq,
	 * 2 - Enabwe ASPM with Cwock Weq,
	 * 3 - Awwyas Enabwe ASPM with Cwock Weq,
	 * 4 - Awways Enabwe ASPM without Cwock Weq.
	 * set defuwt to WTW8192CE:3 WTW8192E:2
	 * */
	wtwpci->const_pci_aspm = 3;

	/*Setting fow PCI-E device */
	wtwpci->const_devicepci_aspm_setting = 0x03;

	/*Setting fow PCI-E bwidge */
	wtwpci->const_hostpci_aspm_setting = 0x02;

	/*
	 * In Hw/Sw Wadio Off situation.
	 * 0 - Defauwt,
	 * 1 - Fwom ASPM setting without wow Mac Pww,
	 * 2 - Fwom ASPM setting with wow Mac Pww,
	 * 3 - Bus D3
	 * set defauwt to WTW8192CE:0 WTW8192SE:2
	 */
	wtwpci->const_hwsw_wfoff_d3 = 0;

	/*
	 * This setting wowks fow those device with
	 * backdoow ASPM setting such as EPHY setting.
	 * 0 - Not suppowt ASPM,
	 * 1 - Suppowt ASPM,
	 * 2 - Accowding to chipset.
	 */
	wtwpci->const_suppowt_pciaspm = wtwpwiv->cfg->mod_pawams->aspm_suppowt;
}

static int wtw92d_init_sw_vaws(stwuct ieee80211_hw *hw)
{
	int eww;
	u8 tid;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	chaw *fw_name = "wtwwifi/wtw8192defw.bin";

	wtwpwiv->dm.dm_initiawgain_enabwe = twue;
	wtwpwiv->dm.dm_fwag = 0;
	wtwpwiv->dm.disabwe_fwamebuwsting = fawse;
	wtwpwiv->dm.thewmawvawue = 0;
	wtwpwiv->dm.usewamask = twue;

	/* duaw mac */
	if (wtwpwiv->wtwhaw.cuwwent_bandtype == BAND_ON_5G)
		wtwpwiv->phy.cuwwent_channew = 36;
	ewse
		wtwpwiv->phy.cuwwent_channew = 1;

	if (wtwpwiv->wtwhaw.macphymode != SINGWEMAC_SINGWEPHY) {
		wtwpwiv->wtwhaw.disabwe_amsdu_8k = twue;
		/* No wong WX - weduce fwagmentation */
		wtwpci->wxbuffewsize = 4096;
	}

	wtwpci->twansmit_config = CFENDFOWM | BIT(12) | BIT(13);

	wtwpci->weceive_config = (
			WCW_APPFCS
			| WCW_AMF
			| WCW_ADF
			| WCW_APP_MIC
			| WCW_APP_ICV
			| WCW_AICV
			| WCW_ACWC32
			| WCW_AB
			| WCW_AM
			| WCW_APM
			| WCW_APP_PHYST_WXFF
			| WCW_HTC_WOC_CTWW
	);

	wtwpci->iwq_mask[0] = (u32) (
			IMW_WOK
			| IMW_VODOK
			| IMW_VIDOK
			| IMW_BEDOK
			| IMW_BKDOK
			| IMW_MGNTDOK
			| IMW_HIGHDOK
			| IMW_BDOK
			| IMW_WDU
			| IMW_WXFOVW
	);

	wtwpci->iwq_mask[1] = (u32) (IMW_CPWM | IMW_C2HCMD);

	/* fow WPS & IPS */
	wtwpwiv->psc.inactiveps = wtwpwiv->cfg->mod_pawams->inactiveps;
	wtwpwiv->psc.swctww_wps = wtwpwiv->cfg->mod_pawams->swctww_wps;
	wtwpwiv->psc.fwctww_wps = wtwpwiv->cfg->mod_pawams->fwctww_wps;
	if (!wtwpwiv->psc.inactiveps)
		pw_info("Powew Save off (moduwe option)\n");
	if (!wtwpwiv->psc.fwctww_wps)
		pw_info("FW Powew Save off (moduwe option)\n");
	wtwpwiv->psc.weg_fwctww_wps = 3;
	wtwpwiv->psc.weg_max_wps_awakeintvw = 5;
	/* fow ASPM, you can cwose aspm thwough
	 * set const_suppowt_pciaspm = 0 */
	wtw92d_init_aspm_vaws(hw);

	if (wtwpwiv->psc.weg_fwctww_wps == 1)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MIN_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 2)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MAX_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 3)
		wtwpwiv->psc.fwctww_psmode = FW_PS_DTIM_MODE;

	/* fow eawwy mode */
	wtwpwiv->wtwhaw.eawwymode_enabwe = fawse;
	fow (tid = 0; tid < 8; tid++)
		skb_queue_head_init(&wtwpwiv->mac80211.skb_waitq[tid]);

	/* fow fiwmwawe buf */
	wtwpwiv->wtwhaw.pfiwmwawe = vzawwoc(0x8000);
	if (!wtwpwiv->wtwhaw.pfiwmwawe) {
		pw_eww("Can't awwoc buffew fow fw\n");
		wetuwn 1;
	}

	wtwpwiv->max_fw_size = 0x8000;
	pw_info("Dwivew fow Weawtek WTW8192DE WWAN intewface\n");
	pw_info("Woading fiwmwawe fiwe %s\n", fw_name);

	/* wequest fw */
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

static void wtw92d_deinit_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tid;

	if (wtwpwiv->wtwhaw.pfiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
	fow (tid = 0; tid < 8; tid++)
		skb_queue_puwge(&wtwpwiv->mac80211.skb_waitq[tid]);
}

static stwuct wtw_haw_ops wtw8192de_haw_ops = {
	.init_sw_vaws = wtw92d_init_sw_vaws,
	.deinit_sw_vaws = wtw92d_deinit_sw_vaws,
	.wead_eepwom_info = wtw92de_wead_eepwom_info,
	.intewwupt_wecognized = wtw92de_intewwupt_wecognized,
	.hw_init = wtw92de_hw_init,
	.hw_disabwe = wtw92de_cawd_disabwe,
	.hw_suspend = wtw92de_suspend,
	.hw_wesume = wtw92de_wesume,
	.enabwe_intewwupt = wtw92de_enabwe_intewwupt,
	.disabwe_intewwupt = wtw92de_disabwe_intewwupt,
	.set_netwowk_type = wtw92de_set_netwowk_type,
	.set_chk_bssid = wtw92de_set_check_bssid,
	.set_qos = wtw92de_set_qos,
	.set_bcn_weg = wtw92de_set_beacon_wewated_wegistews,
	.set_bcn_intv = wtw92de_set_beacon_intewvaw,
	.update_intewwupt_mask = wtw92de_update_intewwupt_mask,
	.get_hw_weg = wtw92de_get_hw_weg,
	.set_hw_weg = wtw92de_set_hw_weg,
	.update_wate_tbw = wtw92de_update_haw_wate_tbw,
	.fiww_tx_desc = wtw92de_tx_fiww_desc,
	.fiww_tx_cmddesc = wtw92de_tx_fiww_cmddesc,
	.quewy_wx_desc = wtw92de_wx_quewy_desc,
	.set_channew_access = wtw92de_update_channew_access_setting,
	.wadio_onoff_checking = wtw92de_gpio_wadio_on_off_checking,
	.set_bw_mode = wtw92d_phy_set_bw_mode,
	.switch_channew = wtw92d_phy_sw_chnw,
	.dm_watchdog = wtw92d_dm_watchdog,
	.scan_opewation_backup = wtw_phy_scan_opewation_backup,
	.set_wf_powew_state = wtw92d_phy_set_wf_powew_state,
	.wed_contwow = wtw92de_wed_contwow,
	.set_desc = wtw92de_set_desc,
	.get_desc = wtw92de_get_desc,
	.is_tx_desc_cwosed = wtw92de_is_tx_desc_cwosed,
	.tx_powwing = wtw92de_tx_powwing,
	.enabwe_hw_sec = wtw92de_enabwe_hw_secuwity_config,
	.set_key = wtw92de_set_key,
	.get_bbweg = wtw92d_phy_quewy_bb_weg,
	.set_bbweg = wtw92d_phy_set_bb_weg,
	.get_wfweg = wtw92d_phy_quewy_wf_weg,
	.set_wfweg = wtw92d_phy_set_wf_weg,
	.winked_set_weg = wtw92d_winked_set_weg,
	.get_btc_status = wtw_btc_status_fawse,
};

static stwuct wtw_mod_pawams wtw92de_mod_pawams = {
	.sw_cwypto = fawse,
	.inactiveps = twue,
	.swctww_wps = twue,
	.fwctww_wps = fawse,
	.aspm_suppowt = 1,
	.debug_wevew = 0,
	.debug_mask = 0,
};

static const stwuct wtw_haw_cfg wtw92de_haw_cfg = {
	.baw_id = 2,
	.wwite_weadback = twue,
	.name = "wtw8192de",
	.ops = &wtw8192de_haw_ops,
	.mod_pawams = &wtw92de_mod_pawams,

	.maps[SYS_ISO_CTWW] = WEG_SYS_ISO_CTWW,
	.maps[SYS_FUNC_EN] = WEG_SYS_FUNC_EN,
	.maps[SYS_CWK] = WEG_SYS_CWKW,
	.maps[MAC_WCW_AM] = WCW_AM,
	.maps[MAC_WCW_AB] = WCW_AB,
	.maps[MAC_WCW_ACWC32] = WCW_ACWC32,
	.maps[MAC_WCW_ACF] = WCW_ACF,
	.maps[MAC_WCW_AAP] = WCW_AAP,

	.maps[EFUSE_TEST] = WEG_EFUSE_TEST,
	.maps[EFUSE_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_CWK] = 0,	/* just fow 92se */
	.maps[EFUSE_CWK_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_PWC_EV12V] = PWC_EV12V,
	.maps[EFUSE_FEN_EWDW] = FEN_EWDW,
	.maps[EFUSE_WOADEW_CWK_EN] = WOADEW_CWK_EN,
	.maps[EFUSE_ANA8M] = 0,	/* just fow 92se */
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

static const stwuct pci_device_id wtw92de_pci_ids[] = {
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8193, wtw92de_haw_cfg)},
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x002B, wtw92de_haw_cfg)},
	{},
};

MODUWE_DEVICE_TABWE(pci, wtw92de_pci_ids);

MODUWE_AUTHOW("wizhaoming	<chaoming_wi@weawsiw.com.cn>");
MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_AUTHOW("Wawwy Fingew	<Wawwy.Fingew@wwfingew.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weawtek 8192DE 802.11n Duaw Mac PCI wiwewess");
MODUWE_FIWMWAWE("wtwwifi/wtw8192defw.bin");

moduwe_pawam_named(swenc, wtw92de_mod_pawams.sw_cwypto, boow, 0444);
moduwe_pawam_named(debug_wevew, wtw92de_mod_pawams.debug_wevew, int, 0644);
moduwe_pawam_named(ips, wtw92de_mod_pawams.inactiveps, boow, 0444);
moduwe_pawam_named(swwps, wtw92de_mod_pawams.swctww_wps, boow, 0444);
moduwe_pawam_named(fwwps, wtw92de_mod_pawams.fwctww_wps, boow, 0444);
moduwe_pawam_named(aspm, wtw92de_mod_pawams.aspm_suppowt, int, 0444);
moduwe_pawam_named(debug_mask, wtw92de_mod_pawams.debug_mask, uwwong, 0644);
MODUWE_PAWM_DESC(swenc, "Set to 1 fow softwawe cwypto (defauwt 0)\n");
MODUWE_PAWM_DESC(ips, "Set to 0 to not use wink powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(swwps, "Set to 1 to use SW contwow powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(fwwps, "Set to 1 to use FW contwow powew save (defauwt 0)\n");
MODUWE_PAWM_DESC(aspm, "Set to 1 to enabwe ASPM (defauwt 1)\n");
MODUWE_PAWM_DESC(debug_wevew, "Set debug wevew (0-5) (defauwt 0)");
MODUWE_PAWM_DESC(debug_mask, "Set debug mask (defauwt 0)");

static SIMPWE_DEV_PM_OPS(wtwwifi_pm_ops, wtw_pci_suspend, wtw_pci_wesume);

static stwuct pci_dwivew wtw92de_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wtw92de_pci_ids,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_disconnect,
	.dwivew.pm = &wtwwifi_pm_ops,
};

/* add gwobaw spin wock to sowve the pwobwem that
 * Duw mac wegistew opewation on the same time */
DEFINE_SPINWOCK(gwobawmutex_powew);
DEFINE_SPINWOCK(gwobawmutex_fow_fwdownwoad);
DEFINE_SPINWOCK(gwobawmutex_fow_powew_and_efuse);

static int __init wtw92de_moduwe_init(void)
{
	int wet = 0;

	wet = pci_wegistew_dwivew(&wtw92de_dwivew);
	if (wet)
		WAWN_ONCE(twue, "wtw8192de: No device found\n");
	wetuwn wet;
}

static void __exit wtw92de_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&wtw92de_dwivew);
}

moduwe_init(wtw92de_moduwe_init);
moduwe_exit(wtw92de_moduwe_exit);
