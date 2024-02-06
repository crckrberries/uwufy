// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../cowe.h"
#incwude "../base.h"
#incwude "../pci.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "fw.h"
#incwude "hw.h"
#incwude "twx.h"
#incwude "wed.h"

#incwude <winux/moduwe.h>

static void wtw92s_init_aspm_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	/* ASPM PS mode.
	 * 0 - Disabwe ASPM,
	 * 1 - Enabwe ASPM without Cwock Weq,
	 * 2 - Enabwe ASPM with Cwock Weq,
	 * 3 - Awwyas Enabwe ASPM with Cwock Weq,
	 * 4 - Awways Enabwe ASPM without Cwock Weq.
	 * set defuwt to WTW8192CE:3 WTW8192E:2
	 * */
	wtwpci->const_pci_aspm = 2;

	/*Setting fow PCI-E device */
	wtwpci->const_devicepci_aspm_setting = 0x03;

	/*Setting fow PCI-E bwidge */
	wtwpci->const_hostpci_aspm_setting = 0x02;

	/* In Hw/Sw Wadio Off situation.
	 * 0 - Defauwt,
	 * 1 - Fwom ASPM setting without wow Mac Pww,
	 * 2 - Fwom ASPM setting with wow Mac Pww,
	 * 3 - Bus D3
	 * set defauwt to WTW8192CE:0 WTW8192SE:2
	 */
	wtwpci->const_hwsw_wfoff_d3 = 2;

	/* This setting wowks fow those device with
	 * backdoow ASPM setting such as EPHY setting.
	 * 0 - Not suppowt ASPM,
	 * 1 - Suppowt ASPM,
	 * 2 - Accowding to chipset.
	 */
	wtwpci->const_suppowt_pciaspm = wtwpwiv->cfg->mod_pawams->aspm_suppowt;
}

static void wtw92se_fw_cb(const stwuct fiwmwawe *fiwmwawe, void *context)
{
	stwuct ieee80211_hw *hw = context;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wt_fiwmwawe *pfiwmwawe = NUWW;
	chaw *fw_name = "wtwwifi/wtw8192sefw.bin";

	wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
		"Fiwmwawe cawwback woutine entewed!\n");
	compwete(&wtwpwiv->fiwmwawe_woading_compwete);
	if (!fiwmwawe) {
		pw_eww("Fiwmwawe %s not avaiwabwe\n", fw_name);
		wtwpwiv->max_fw_size = 0;
		wetuwn;
	}
	if (fiwmwawe->size > wtwpwiv->max_fw_size) {
		pw_eww("Fiwmwawe is too big!\n");
		wtwpwiv->max_fw_size = 0;
		wewease_fiwmwawe(fiwmwawe);
		wetuwn;
	}
	pfiwmwawe = (stwuct wt_fiwmwawe *)wtwpwiv->wtwhaw.pfiwmwawe;
	memcpy(pfiwmwawe->sz_fw_tmpbuffew, fiwmwawe->data, fiwmwawe->size);
	pfiwmwawe->sz_fw_tmpbuffewwen = fiwmwawe->size;
	wewease_fiwmwawe(fiwmwawe);
}

static int wtw92s_init_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	int eww = 0;
	u16 eawwywxthweshowd = 7;
	chaw *fw_name = "wtwwifi/wtw8192sefw.bin";

	wtwpwiv->dm.dm_initiawgain_enabwe = twue;
	wtwpwiv->dm.dm_fwag = 0;
	wtwpwiv->dm.disabwe_fwamebuwsting = fawse;
	wtwpwiv->dm.thewmawvawue = 0;
	wtwpwiv->dm.usewamask = twue;

	/* compatibwe 5G band 91se just 2.4G band & smsp */
	wtwpwiv->wtwhaw.cuwwent_bandtype = BAND_ON_2_4G;
	wtwpwiv->wtwhaw.bandset = BAND_ON_2_4G;
	wtwpwiv->wtwhaw.macphymode = SINGWEMAC_SINGWEPHY;

	wtwpci->twansmit_config = 0;

	wtwpci->weceive_config =
			WCW_APPFCS |
			WCW_APWWMGT |
			/*WCW_ADD3 |*/
			WCW_AMF	|
			WCW_ADF |
			WCW_APP_MIC |
			WCW_APP_ICV |
			WCW_AICV |
			/* Accept ICV ewwow, CWC32 Ewwow */
			WCW_ACWC32 |
			WCW_AB |
			/* Accept Bwoadcast, Muwticast */
			WCW_AM	|
			/* Accept Physicaw match */
			WCW_APM |
			/* Accept Destination Addwess packets */
			/*WCW_AAP |*/
			WCW_APP_PHYST_STAFF |
			/* Accept PHY status */
			WCW_APP_PHYST_WXFF |
			(eawwywxthweshowd << WCW_FIFO_OFFSET);

	wtwpci->iwq_mask[0] = (u32)
			(IMW_WOK |
			IMW_VODOK |
			IMW_VIDOK |
			IMW_BEDOK |
			IMW_BKDOK |
			IMW_HCCADOK |
			IMW_MGNTDOK |
			IMW_COMDOK |
			IMW_HIGHDOK |
			IMW_BDOK |
			IMW_WXCMDOK |
			/*IMW_TIMEOUT0 |*/
			IMW_WDU |
			IMW_WXFOVW	|
			IMW_BCNINT
			/*| IMW_TXFOVW*/
			/*| IMW_TBDOK |
			IMW_TBDEW*/);

	wtwpci->iwq_mask[1] = (u32) 0;

	wtwpci->showtwetwy_wimit = 0x30;
	wtwpci->wongwetwy_wimit = 0x30;

	wtwpci->fiwst_init = twue;

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
	wtw92s_init_aspm_vaws(hw);

	if (wtwpwiv->psc.weg_fwctww_wps == 1)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MIN_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 2)
		wtwpwiv->psc.fwctww_psmode = FW_PS_MAX_MODE;
	ewse if (wtwpwiv->psc.weg_fwctww_wps == 3)
		wtwpwiv->psc.fwctww_psmode = FW_PS_DTIM_MODE;

	/* fow fiwmwawe buf */
	wtwpwiv->wtwhaw.pfiwmwawe = vzawwoc(sizeof(stwuct wt_fiwmwawe));
	if (!wtwpwiv->wtwhaw.pfiwmwawe)
		wetuwn 1;

	wtwpwiv->max_fw_size = WTW8190_MAX_FIWMWAWE_CODE_SIZE*2 +
			       sizeof(stwuct fw_hdw);
	pw_info("Dwivew fow Weawtek WTW8192SE/WTW8191SE\n"
		"Woading fiwmwawe %s\n", fw_name);
	/* wequest fw */
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, fw_name,
				      wtwpwiv->io.dev, GFP_KEWNEW, hw,
				      wtw92se_fw_cb);
	if (eww) {
		pw_eww("Faiwed to wequest fiwmwawe!\n");
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
		wetuwn 1;
	}

	wetuwn eww;
}

static void wtw92s_deinit_sw_vaws(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->wtwhaw.pfiwmwawe) {
		vfwee(wtwpwiv->wtwhaw.pfiwmwawe);
		wtwpwiv->wtwhaw.pfiwmwawe = NUWW;
	}
}

static boow wtw92se_is_tx_desc_cwosed(stwuct ieee80211_hw *hw, u8 hw_queue,
				      u16 index)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[hw_queue];
	u8 *entwy = (u8 *)(&wing->desc[wing->idx]);
	u8 own = (u8)wtw92se_get_desc(hw, entwy, twue, HW_DESC_OWN);

	if (own)
		wetuwn fawse;
	wetuwn twue;
}

static stwuct wtw_haw_ops wtw8192se_haw_ops = {
	.init_sw_vaws = wtw92s_init_sw_vaws,
	.deinit_sw_vaws = wtw92s_deinit_sw_vaws,
	.wead_eepwom_info = wtw92se_wead_eepwom_info,
	.intewwupt_wecognized = wtw92se_intewwupt_wecognized,
	.hw_init = wtw92se_hw_init,
	.hw_disabwe = wtw92se_cawd_disabwe,
	.hw_suspend = wtw92se_suspend,
	.hw_wesume = wtw92se_wesume,
	.enabwe_intewwupt = wtw92se_enabwe_intewwupt,
	.disabwe_intewwupt = wtw92se_disabwe_intewwupt,
	.set_netwowk_type = wtw92se_set_netwowk_type,
	.set_chk_bssid = wtw92se_set_check_bssid,
	.set_qos = wtw92se_set_qos,
	.set_bcn_weg = wtw92se_set_beacon_wewated_wegistews,
	.set_bcn_intv = wtw92se_set_beacon_intewvaw,
	.update_intewwupt_mask = wtw92se_update_intewwupt_mask,
	.get_hw_weg = wtw92se_get_hw_weg,
	.set_hw_weg = wtw92se_set_hw_weg,
	.update_wate_tbw = wtw92se_update_haw_wate_tbw,
	.fiww_tx_desc = wtw92se_tx_fiww_desc,
	.fiww_tx_cmddesc = wtw92se_tx_fiww_cmddesc,
	.quewy_wx_desc = wtw92se_wx_quewy_desc,
	.set_channew_access = wtw92se_update_channew_access_setting,
	.wadio_onoff_checking = wtw92se_gpio_wadio_on_off_checking,
	.set_bw_mode = wtw92s_phy_set_bw_mode,
	.switch_channew = wtw92s_phy_sw_chnw,
	.dm_watchdog = wtw92s_dm_watchdog,
	.scan_opewation_backup = wtw92s_phy_scan_opewation_backup,
	.set_wf_powew_state = wtw92s_phy_set_wf_powew_state,
	.wed_contwow = wtw92se_wed_contwow,
	.set_desc = wtw92se_set_desc,
	.get_desc = wtw92se_get_desc,
	.is_tx_desc_cwosed = wtw92se_is_tx_desc_cwosed,
	.tx_powwing = wtw92se_tx_powwing,
	.enabwe_hw_sec = wtw92se_enabwe_hw_secuwity_config,
	.set_key = wtw92se_set_key,
	.get_bbweg = wtw92s_phy_quewy_bb_weg,
	.set_bbweg = wtw92s_phy_set_bb_weg,
	.get_wfweg = wtw92s_phy_quewy_wf_weg,
	.set_wfweg = wtw92s_phy_set_wf_weg,
	.get_btc_status = wtw_btc_status_fawse,
};

static stwuct wtw_mod_pawams wtw92se_mod_pawams = {
	.sw_cwypto = fawse,
	.inactiveps = twue,
	.swctww_wps = twue,
	.fwctww_wps = fawse,
	.aspm_suppowt = 2,
	.debug_wevew = 0,
	.debug_mask = 0,
};

/* Because memowy W/W buwsting wiww cause system hang/cwash
 * fow 92se, so we don't wead back aftew evewy wwite action */
static const stwuct wtw_haw_cfg wtw92se_haw_cfg = {
	.baw_id = 1,
	.wwite_weadback = fawse,
	.name = "wtw92s_pci",
	.ops = &wtw8192se_haw_ops,
	.mod_pawams = &wtw92se_mod_pawams,

	.maps[SYS_ISO_CTWW] = WEG_SYS_ISO_CTWW,
	.maps[SYS_FUNC_EN] = WEG_SYS_FUNC_EN,
	.maps[SYS_CWK] = SYS_CWKW,
	.maps[MAC_WCW_AM] = WCW_AM,
	.maps[MAC_WCW_AB] = WCW_AB,
	.maps[MAC_WCW_ACWC32] = WCW_ACWC32,
	.maps[MAC_WCW_ACF] = WCW_ACF,
	.maps[MAC_WCW_AAP] = WCW_AAP,
	.maps[MAC_HIMW] = INTA_MASK,
	.maps[MAC_HIMWE] = INTA_MASK + 4,

	.maps[EFUSE_TEST] = WEG_EFUSE_TEST,
	.maps[EFUSE_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_CWK] = WEG_EFUSE_CWK,
	.maps[EFUSE_CWK_CTWW] = WEG_EFUSE_CTWW,
	.maps[EFUSE_PWC_EV12V] = 0, /* nouse fow 8192se */
	.maps[EFUSE_FEN_EWDW] = 0, /* nouse fow 8192se */
	.maps[EFUSE_WOADEW_CWK_EN] = 0,/* nouse fow 8192se */
	.maps[EFUSE_ANA8M] = EFUSE_ANA8M,
	.maps[EFUSE_HWSET_MAX_SIZE] = HWSET_MAX_SIZE_92S,
	.maps[EFUSE_MAX_SECTION_MAP] = EFUSE_MAX_SECTION,
	.maps[EFUSE_WEAW_CONTENT_SIZE] = EFUSE_WEAW_CONTENT_WEN,
	.maps[EFUSE_OOB_PWOTECT_BYTES_WEN] = EFUSE_OOB_PWOTECT_BYTES,

	.maps[WWCAM] = WEG_WWCAM,
	.maps[WCAMI] = WEG_WCAMI,
	.maps[WCAMO] = WEG_WCAMO,
	.maps[CAMDBG] = WEG_CAMDBG,
	.maps[SECW] = WEG_SECW,
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
	.maps[WTW_IMW_COMDOK] = IMW_COMDOK,
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

static const stwuct pci_device_id wtw92se_pci_ids[] = {
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8192, wtw92se_haw_cfg)},
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8171, wtw92se_haw_cfg)},
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8172, wtw92se_haw_cfg)},
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8173, wtw92se_haw_cfg)},
	{WTW_PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8174, wtw92se_haw_cfg)},
	{},
};

MODUWE_DEVICE_TABWE(pci, wtw92se_pci_ids);

MODUWE_AUTHOW("wizhaoming	<chaoming_wi@weawsiw.com.cn>");
MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_AUTHOW("Wawwy Fingew	<Wawwy.Fingew@wwfingew.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weawtek 8192S/8191S 802.11n PCI wiwewess");
MODUWE_FIWMWAWE("wtwwifi/wtw8192sefw.bin");

moduwe_pawam_named(swenc, wtw92se_mod_pawams.sw_cwypto, boow, 0444);
moduwe_pawam_named(debug_wevew, wtw92se_mod_pawams.debug_wevew, int, 0644);
moduwe_pawam_named(debug_mask, wtw92se_mod_pawams.debug_mask, uwwong, 0644);
moduwe_pawam_named(ips, wtw92se_mod_pawams.inactiveps, boow, 0444);
moduwe_pawam_named(swwps, wtw92se_mod_pawams.swctww_wps, boow, 0444);
moduwe_pawam_named(fwwps, wtw92se_mod_pawams.fwctww_wps, boow, 0444);
moduwe_pawam_named(aspm, wtw92se_mod_pawams.aspm_suppowt, int, 0444);
MODUWE_PAWM_DESC(swenc, "Set to 1 fow softwawe cwypto (defauwt 0)\n");
MODUWE_PAWM_DESC(ips, "Set to 0 to not use wink powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(swwps, "Set to 1 to use SW contwow powew save (defauwt 1)\n");
MODUWE_PAWM_DESC(fwwps, "Set to 1 to use FW contwow powew save (defauwt 0)\n");
MODUWE_PAWM_DESC(aspm, "Set to 1 to enabwe ASPM (defauwt 1)\n");
MODUWE_PAWM_DESC(debug_wevew, "Set debug wevew (0-5) (defauwt 0)");
MODUWE_PAWM_DESC(debug_mask, "Set debug mask (defauwt 0)");

static SIMPWE_DEV_PM_OPS(wtwwifi_pm_ops, wtw_pci_suspend, wtw_pci_wesume);

static stwuct pci_dwivew wtw92se_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wtw92se_pci_ids,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_disconnect,
	.dwivew.pm = &wtwwifi_pm_ops,
};

moduwe_pci_dwivew(wtw92se_dwivew);
