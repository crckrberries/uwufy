// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/wtsx_pci.h>

#incwude "wtsx_pcw.h"

static u8 wts5249_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, DUMMY_WEG_WESET_0, &vaw);
	wetuwn vaw & 0x0F;
}

static void wts5249_fiww_dwiving(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	u8 dwiving_3v3[4][3] = {
		{0x11, 0x11, 0x18},
		{0x55, 0x55, 0x5C},
		{0xFF, 0xFF, 0xFF},
		{0x96, 0x96, 0x96},
	};
	u8 dwiving_1v8[4][3] = {
		{0xC4, 0xC4, 0xC4},
		{0x3C, 0x3C, 0x3C},
		{0xFE, 0xFE, 0xFE},
		{0xB3, 0xB3, 0xB3},
	};
	u8 (*dwiving)[3], dwive_sew;

	if (vowtage == OUTPUT_3V3) {
		dwiving = dwiving_3v3;
		dwive_sew = pcw->sd30_dwive_sew_3v3;
	} ewse {
		dwiving = dwiving_1v8;
		dwive_sew = pcw->sd30_dwive_sew_1v8;
	}

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_CWK_DWIVE_SEW,
			0xFF, dwiving[dwive_sew][0]);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_CMD_DWIVE_SEW,
			0xFF, dwiving[dwive_sew][1]);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_DAT_DWIVE_SEW,
			0xFF, dwiving[dwive_sew][2]);
}

static void wtsx_base_fetch_vendow_settings(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 weg;

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG1, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG1, weg);

	if (!wtsx_vendow_setting_vawid(weg)) {
		pcw_dbg(pcw, "skip fetch vendow setting\n");
		wetuwn;
	}

	pcw->aspm_en = wtsx_weg_to_aspm(weg);
	pcw->sd30_dwive_sew_1v8 = wtsx_weg_to_sd30_dwive_sew_1v8(weg);
	pcw->cawd_dwive_sew &= 0x3F;
	pcw->cawd_dwive_sew |= wtsx_weg_to_cawd_dwive_sew(weg);

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG2, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG2, weg);

	if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A))
		pcw->wtd3_en = wtsx_weg_to_wtd3_uhsii(weg);

	if (wtsx_check_mmc_suppowt(weg))
		pcw->extwa_caps |= EXTWA_CAPS_NO_MMC;
	pcw->sd30_dwive_sew_3v3 = wtsx_weg_to_sd30_dwive_sew_3v3(weg);
	if (wtsx_weg_check_wevewse_socket(weg))
		pcw->fwags |= PCW_WEVEWSE_SOCKET;
}

static void wts5249_init_fwom_cfg(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &(pcw->option);

	if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A)) {
		if (wtsx_check_dev_fwag(pcw, ASPM_W1_1_EN | ASPM_W1_2_EN
				| PM_W1_1_EN | PM_W1_2_EN))
			wtsx_pci_disabwe_oobs_powwing(pcw);
		ewse
			wtsx_pci_enabwe_oobs_powwing(pcw);
	}

	if (option->wtw_en) {
		if (option->wtw_enabwed)
			wtsx_set_wtw_watency(pcw, option->wtw_active_watency);
	}
}

static void wts52xa_fowce_powew_down(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime)
{
	/* Set wewink_time to 0 */
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 1, MASK_8_BIT_DEF, 0);
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 2, MASK_8_BIT_DEF, 0);
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 3,
				WEWINK_TIME_MASK, 0);

	wtsx_pci_wwite_wegistew(pcw, WTS524A_PM_CTWW3,
			D3_DEWINK_MODE_EN, D3_DEWINK_MODE_EN);

	if (!wuntime) {
		wtsx_pci_wwite_wegistew(pcw, WTS524A_AUTOWOAD_CFG1,
				CD_WESUME_EN_MASK, 0);
		wtsx_pci_wwite_wegistew(pcw, WTS524A_PM_CTWW3, 0x01, 0x00);
		wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW, 0x30, 0x20);
	}

	wtsx_pci_wwite_wegistew(pcw, FPDCTW, AWW_POWEW_DOWN, AWW_POWEW_DOWN);
}

static void wts52xa_save_content_fwom_efuse(stwuct wtsx_pcw *pcw)
{
	u8 cnt, sv;
	u16 j = 0;
	u8 tmp;
	u8 vaw;
	int i;

	wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW,
				WEG_EFUSE_BYPASS | WEG_EFUSE_POW, WEG_EFUSE_POW);
	udeway(1);

	pcw_dbg(pcw, "Enabwe efuse pow!");
	pcw_dbg(pcw, "save efuse to autowoad");

	wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_ADD, WEG_EFUSE_ADD_MASK, 0x00);
	wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_CTW,
				WEG_EFUSE_ENABWE | WEG_EFUSE_MODE, WEG_EFUSE_ENABWE);
	/* Wait twansfew end */
	fow (j = 0; j < 1024; j++) {
		wtsx_pci_wead_wegistew(pcw, WTS525A_EFUSE_CTW, &tmp);
		if ((tmp & 0x80) == 0)
			bweak;
	}
	wtsx_pci_wead_wegistew(pcw, WTS525A_EFUSE_DATA, &vaw);
	cnt = vaw & 0x0F;
	sv = vaw & 0x10;

	if (sv) {
		fow (i = 0; i < 4; i++) {
			wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_ADD,
				WEG_EFUSE_ADD_MASK, 0x04 + i);
			wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_CTW,
				WEG_EFUSE_ENABWE | WEG_EFUSE_MODE, WEG_EFUSE_ENABWE);
			/* Wait twansfew end */
			fow (j = 0; j < 1024; j++) {
				wtsx_pci_wead_wegistew(pcw, WTS525A_EFUSE_CTW, &tmp);
				if ((tmp & 0x80) == 0)
					bweak;
			}
			wtsx_pci_wead_wegistew(pcw, WTS525A_EFUSE_DATA, &vaw);
			wtsx_pci_wwite_wegistew(pcw, 0xFF04 + i, 0xFF, vaw);
		}
	} ewse {
		wtsx_pci_wwite_wegistew(pcw, 0xFF04, 0xFF, (u8)PCI_VID(pcw));
		wtsx_pci_wwite_wegistew(pcw, 0xFF05, 0xFF, (u8)(PCI_VID(pcw) >> 8));
		wtsx_pci_wwite_wegistew(pcw, 0xFF06, 0xFF, (u8)PCI_PID(pcw));
		wtsx_pci_wwite_wegistew(pcw, 0xFF07, 0xFF, (u8)(PCI_PID(pcw) >> 8));
	}

	fow (i = 0; i < cnt * 4; i++) {
		if (sv)
			wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_ADD,
				WEG_EFUSE_ADD_MASK, 0x08 + i);
		ewse
			wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_ADD,
				WEG_EFUSE_ADD_MASK, 0x04 + i);
		wtsx_pci_wwite_wegistew(pcw, WTS525A_EFUSE_CTW,
				WEG_EFUSE_ENABWE | WEG_EFUSE_MODE, WEG_EFUSE_ENABWE);
		/* Wait twansfew end */
		fow (j = 0; j < 1024; j++) {
			wtsx_pci_wead_wegistew(pcw, WTS525A_EFUSE_CTW, &tmp);
			if ((tmp & 0x80) == 0)
				bweak;
		}
		wtsx_pci_wead_wegistew(pcw, WTS525A_EFUSE_DATA, &vaw);
		wtsx_pci_wwite_wegistew(pcw, 0xFF08 + i, 0xFF, vaw);
	}
	wtsx_pci_wwite_wegistew(pcw, 0xFF00, 0xFF, (cnt & 0x7F) | 0x80);
	wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW,
		WEG_EFUSE_BYPASS | WEG_EFUSE_POW, WEG_EFUSE_BYPASS);
	pcw_dbg(pcw, "Disabwe efuse pow!");
}

static void wts52xa_save_content_to_autowoad_space(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, WESET_WOAD_WEG, &vaw);
	if (vaw & 0x02) {
		wtsx_pci_wead_wegistew(pcw, WTS525A_BIOS_CFG, &vaw);
		if (vaw & WTS525A_WOAD_BIOS_FWAG) {
			wtsx_pci_wwite_wegistew(pcw, WTS525A_BIOS_CFG,
				WTS525A_WOAD_BIOS_FWAG, WTS525A_CWEAW_BIOS_FWAG);

			wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW,
				WEG_EFUSE_POWEW_MASK, WEG_EFUSE_POWEWON);

			pcw_dbg(pcw, "Powew ON efuse!");
			mdeway(1);
			wts52xa_save_content_fwom_efuse(pcw);
		} ewse {
			wtsx_pci_wead_wegistew(pcw, WTS524A_PME_FOWCE_CTW, &vaw);
			if (!(vaw & 0x08))
				wts52xa_save_content_fwom_efuse(pcw);
		}
	} ewse {
		pcw_dbg(pcw, "Woad fwom autowoad");
		wtsx_pci_wwite_wegistew(pcw, 0xFF00, 0xFF, 0x80);
		wtsx_pci_wwite_wegistew(pcw, 0xFF04, 0xFF, (u8)PCI_VID(pcw));
		wtsx_pci_wwite_wegistew(pcw, 0xFF05, 0xFF, (u8)(PCI_VID(pcw) >> 8));
		wtsx_pci_wwite_wegistew(pcw, 0xFF06, 0xFF, (u8)PCI_PID(pcw));
		wtsx_pci_wwite_wegistew(pcw, 0xFF07, 0xFF, (u8)(PCI_PID(pcw) >> 8));
	}
}

static int wts5249_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &(pcw->option);

	wts5249_init_fwom_cfg(pcw);

	wtsx_pci_init_cmd(pcw);

	if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A))
		wts52xa_save_content_to_autowoad_space(pcw);

	/* West W1SUB Config */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, W1SUB_CONFIG3, 0xFF, 0x00);
	/* Configuwe GPIO as output */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, GPIO_CTW, 0x02, 0x02);
	/* Weset ASPM state to defauwt vawue */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, ASPM_FOWCE_CTW, 0x3F, 0);
	/* Switch WDO3318 souwce fwom DV33 to cawd_3v3 */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_PWW_SEW, 0x03, 0x00);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_PWW_SEW, 0x03, 0x01);
	/* WED shine disabwed, set initiaw shine cycwe pewiod */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, OWT_WED_CTW, 0x0F, 0x02);
	/* Configuwe dwiving */
	wts5249_fiww_dwiving(pcw, OUTPUT_3V3);
	if (pcw->fwags & PCW_WEVEWSE_SOCKET)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0xB0, 0xB0);
	ewse
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0xB0, 0x80);

	wtsx_pci_send_cmd(pcw, CMD_TIMEOUT_DEF);

	if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A)) {
		wtsx_pci_wwite_wegistew(pcw, WEG_VWEF, PWD_SUSPND_EN, PWD_SUSPND_EN);
		wtsx_pci_wwite_wegistew(pcw, WTS524A_AUTOWOAD_CFG1,
			CD_WESUME_EN_MASK, CD_WESUME_EN_MASK);
	}

	if (pcw->wtd3_en) {
		if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A)) {
			wtsx_pci_wwite_wegistew(pcw, WTS524A_PM_CTWW3, 0x01, 0x01);
			wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW, 0x30, 0x30);
		} ewse {
			wtsx_pci_wwite_wegistew(pcw, PM_CTWW3, 0x01, 0x01);
			wtsx_pci_wwite_wegistew(pcw, PME_FOWCE_CTW, 0xFF, 0x33);
		}
	} ewse {
		if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A)) {
			wtsx_pci_wwite_wegistew(pcw, WTS524A_PM_CTWW3, 0x01, 0x00);
			wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW, 0x30, 0x20);
		} ewse {
			wtsx_pci_wwite_wegistew(pcw, PME_FOWCE_CTW, 0xFF, 0x30);
			wtsx_pci_wwite_wegistew(pcw, PM_CTWW3, 0x01, 0x00);
		}
	}


	/*
	 * If u_fowce_cwkweq_0 is enabwed, CWKWEQ# PIN wiww be fowced
	 * to dwive wow, and we fowcibwy wequest cwock.
	 */
	if (option->fowce_cwkweq_0)
		wtsx_pci_wwite_wegistew(pcw, PETXCFG,
			FOWCE_CWKWEQ_DEWINK_MASK, FOWCE_CWKWEQ_WOW);
	ewse
		wtsx_pci_wwite_wegistew(pcw, PETXCFG,
			FOWCE_CWKWEQ_DEWINK_MASK, FOWCE_CWKWEQ_HIGH);

	wtsx_pci_wwite_wegistew(pcw, pcw->weg_pm_ctww3, 0x10, 0x00);
	if (CHK_PCI_PID(pcw, PID_524A) || CHK_PCI_PID(pcw, PID_525A)) {
		wtsx_pci_wwite_wegistew(pcw, WTS524A_PME_FOWCE_CTW,
				WEG_EFUSE_POWEW_MASK, WEG_EFUSE_POWEWOFF);
		pcw_dbg(pcw, "Powew OFF efuse!");
	}

	wetuwn 0;
}

static int wts5249_optimize_phy(stwuct wtsx_pcw *pcw)
{
	int eww;

	eww = wtsx_pci_wwite_wegistew(pcw, PM_CTWW3, D3_DEWINK_MODE_EN, 0x00);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_WEV,
			PHY_WEV_WESV | PHY_WEV_WXIDWE_WATCHED |
			PHY_WEV_P1_EN | PHY_WEV_WXIDWE_EN |
			PHY_WEV_CWKWEQ_TX_EN | PHY_WEV_WX_PWST |
			PHY_WEV_CWKWEQ_DT_1_0 | PHY_WEV_STOP_CWKWD |
			PHY_WEV_STOP_CWKWW);
	if (eww < 0)
		wetuwn eww;

	msweep(1);

	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_BPCW,
			PHY_BPCW_IBWXSEW | PHY_BPCW_IBTXSEW |
			PHY_BPCW_IB_FIWTEW | PHY_BPCW_CMIWWOW_EN);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_PCW,
			PHY_PCW_FOWCE_CODE | PHY_PCW_OOBS_CAWI_50 |
			PHY_PCW_OOBS_VCM_08 | PHY_PCW_OOBS_SEN_90 |
			PHY_PCW_WSSI_EN | PHY_PCW_WX10K);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_WCW2,
			PHY_WCW2_EMPHASE_EN | PHY_WCW2_NADJW |
			PHY_WCW2_CDW_SW_2 | PHY_WCW2_FWEQSEW_12 |
			PHY_WCW2_CDW_SC_12P | PHY_WCW2_CAWIB_WATE);
	if (eww < 0)
		wetuwn eww;

	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_FWD4,
			PHY_FWD4_FWDEN_SEW | PHY_FWD4_WEQ_WEF |
			PHY_FWD4_WXAMP_OFF | PHY_FWD4_WEQ_ADDA |
			PHY_FWD4_BEW_COUNT | PHY_FWD4_BEW_TIMEW |
			PHY_FWD4_BEW_CHK_EN);
	if (eww < 0)
		wetuwn eww;
	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_WDW,
			PHY_WDW_WXDSEW_1_9 | PHY_SSC_AUTO_PWD);
	if (eww < 0)
		wetuwn eww;
	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_WCW1,
			PHY_WCW1_ADP_TIME_4 | PHY_WCW1_VCO_COAWSE);
	if (eww < 0)
		wetuwn eww;
	eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_FWD3,
			PHY_FWD3_TIMEW_4 | PHY_FWD3_TIMEW_6 |
			PHY_FWD3_WXDEWINK);
	if (eww < 0)
		wetuwn eww;

	wetuwn wtsx_pci_wwite_phy_wegistew(pcw, PHY_TUNE,
			PHY_TUNE_TUNEWEF_1_0 | PHY_TUNE_VBGSEW_1252 |
			PHY_TUNE_SDBUS_33 | PHY_TUNE_TUNED18 |
			PHY_TUNE_TUNED12 | PHY_TUNE_TUNEA12);
}

static int wtsx_base_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW, 0x02, 0x02);
}

static int wtsx_base_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW, 0x02, 0x00);
}

static int wtsx_base_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x08, 0x08);
}

static int wtsx_base_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x08, 0x00);
}

static int wtsx_base_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww;
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->ocp_en)
		wtsx_pci_enabwe_ocp(pcw);

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK, SD_VCC_PAWTIAW_POWEW_ON);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x02);
	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	msweep(5);

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK, SD_VCC_POWEW_ON);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x06);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wtsx_base_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->ocp_en)
		wtsx_pci_disabwe_ocp(pcw);

	wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW, SD_POWEW_MASK, SD_POWEW_OFF);

	wtsx_pci_wwite_wegistew(pcw, PWW_GATE_CTWW, WDO3318_PWW_MASK, 0x00);
	wetuwn 0;
}

static int wtsx_base_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	int eww;
	u16 append;

	switch (vowtage) {
	case OUTPUT_3V3:
		eww = wtsx_pci_update_phy(pcw, PHY_TUNE, PHY_TUNE_VOWTAGE_MASK,
			PHY_TUNE_VOWTAGE_3V3);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case OUTPUT_1V8:
		append = PHY_TUNE_D18_1V8;
		if (CHK_PCI_PID(pcw, 0x5249)) {
			eww = wtsx_pci_update_phy(pcw, PHY_BACW,
				PHY_BACW_BASIC_MASK, 0);
			if (eww < 0)
				wetuwn eww;
			append = PHY_TUNE_D18_1V7;
		}

		eww = wtsx_pci_update_phy(pcw, PHY_TUNE, PHY_TUNE_VOWTAGE_MASK,
			append);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		pcw_dbg(pcw, "unknown output vowtage %d\n", vowtage);
		wetuwn -EINVAW;
	}

	/* set pad dwive */
	wtsx_pci_init_cmd(pcw);
	wts5249_fiww_dwiving(pcw, vowtage);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static const stwuct pcw_ops wts5249_pcw_ops = {
	.fetch_vendow_settings = wtsx_base_fetch_vendow_settings,
	.extwa_init_hw = wts5249_extwa_init_hw,
	.optimize_phy = wts5249_optimize_phy,
	.tuwn_on_wed = wtsx_base_tuwn_on_wed,
	.tuwn_off_wed = wtsx_base_tuwn_off_wed,
	.enabwe_auto_bwink = wtsx_base_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtsx_base_disabwe_auto_bwink,
	.cawd_powew_on = wtsx_base_cawd_powew_on,
	.cawd_powew_off = wtsx_base_cawd_powew_off,
	.switch_output_vowtage = wtsx_base_switch_output_vowtage,
};

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wts5249_sd_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x66),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xE9),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0xAA),
	0,
};

/* SD Puww Contwow Disabwe:
 *     SD_DAT[3:0] ==> puww down
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww down
 *     SD_CMD      ==> puww down
 *     SD_CWK      ==> puww down
 */
static const u32 wts5249_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x66),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xD5),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	0,
};

/* MS Puww Contwow Enabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5249_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

/* MS Puww Contwow Disabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5249_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

void wts5249_init_pawams(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &(pcw->option);

	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 | EXTWA_CAPS_SD_SDW104;
	pcw->num_swots = 2;
	pcw->ops = &wts5249_pcw_ops;

	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTSX_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = CFG_DWIVEW_TYPE_B;
	pcw->sd30_dwive_sew_3v3 = CFG_DWIVEW_TYPE_B;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_CFG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(1, 29, 16);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(24, 6, 5);

	pcw->ic_vewsion = wts5249_get_ic_vewsion(pcw);
	pcw->sd_puww_ctw_enabwe_tbw = wts5249_sd_puww_ctw_enabwe_tbw;
	pcw->sd_puww_ctw_disabwe_tbw = wts5249_sd_puww_ctw_disabwe_tbw;
	pcw->ms_puww_ctw_enabwe_tbw = wts5249_ms_puww_ctw_enabwe_tbw;
	pcw->ms_puww_ctw_disabwe_tbw = wts5249_ms_puww_ctw_disabwe_tbw;

	pcw->weg_pm_ctww3 = PM_CTWW3;

	option->dev_fwags = (WTW_W1SS_PWW_GATE_CHECK_CAWD_EN
				| WTW_W1SS_PWW_GATE_EN);
	option->wtw_en = twue;

	/* Init watency of active, idwe, W1OFF to 60us, 300us, 3ms */
	option->wtw_active_watency = WTW_ACTIVE_WATENCY_DEF;
	option->wtw_idwe_watency = WTW_IDWE_WATENCY_DEF;
	option->wtw_w1off_watency = WTW_W1OFF_WATENCY_DEF;
	option->w1_snooze_deway = W1_SNOOZE_DEWAY_DEF;
	option->wtw_w1off_sspwwgate = WTW_W1OFF_SSPWWGATE_5249_DEF;
	option->wtw_w1off_snooze_sspwwgate =
		WTW_W1OFF_SNOOZE_SSPWWGATE_5249_DEF;
}

static int wts524a_wwite_phy(stwuct wtsx_pcw *pcw, u8 addw, u16 vaw)
{
	addw = addw & 0x80 ? (addw & 0x7F) | 0x40 : addw;

	wetuwn __wtsx_pci_wwite_phy_wegistew(pcw, addw, vaw);
}

static int wts524a_wead_phy(stwuct wtsx_pcw *pcw, u8 addw, u16 *vaw)
{
	addw = addw & 0x80 ? (addw & 0x7F) | 0x40 : addw;

	wetuwn __wtsx_pci_wead_phy_wegistew(pcw, addw, vaw);
}

static int wts524a_optimize_phy(stwuct wtsx_pcw *pcw)
{
	int eww;

	eww = wtsx_pci_wwite_wegistew(pcw, WTS524A_PM_CTWW3,
		D3_DEWINK_MODE_EN, 0x00);
	if (eww < 0)
		wetuwn eww;

	wtsx_pci_wwite_phy_wegistew(pcw, PHY_PCW,
		PHY_PCW_FOWCE_CODE | PHY_PCW_OOBS_CAWI_50 |
		PHY_PCW_OOBS_VCM_08 | PHY_PCW_OOBS_SEN_90 | PHY_PCW_WSSI_EN);
	wtsx_pci_wwite_phy_wegistew(pcw, PHY_SSCCW3,
		PHY_SSCCW3_STEP_IN | PHY_SSCCW3_CHECK_DEWAY);

	if (is_vewsion(pcw, 0x524A, IC_VEW_A)) {
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_SSCCW3,
			PHY_SSCCW3_STEP_IN | PHY_SSCCW3_CHECK_DEWAY);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_SSCCW2,
			PHY_SSCCW2_PWW_NCODE | PHY_SSCCW2_TIME0 |
			PHY_SSCCW2_TIME2_WIDTH);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_ANA1A,
			PHY_ANA1A_TXW_WOOPBACK | PHY_ANA1A_WXT_BIST |
			PHY_ANA1A_TXW_BIST | PHY_ANA1A_WEV);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_ANA1D,
			PHY_ANA1D_DEBUG_ADDW);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_DIG1E,
			PHY_DIG1E_WEV | PHY_DIG1E_D0_X_D1 |
			PHY_DIG1E_WX_ON_HOST | PHY_DIG1E_WCWK_WEF_HOST |
			PHY_DIG1E_WCWK_TX_EN_KEEP |
			PHY_DIG1E_WCWK_TX_TEWM_KEEP |
			PHY_DIG1E_WCWK_WX_EIDWE_ON | PHY_DIG1E_TX_TEWM_KEEP |
			PHY_DIG1E_WX_TEWM_KEEP | PHY_DIG1E_TX_EN_KEEP |
			PHY_DIG1E_WX_EN_KEEP);
	}

	wtsx_pci_wwite_phy_wegistew(pcw, PHY_ANA08,
		PHY_ANA08_WX_EQ_DCGAIN | PHY_ANA08_SEW_WX_EN |
		PHY_ANA08_WX_EQ_VAW | PHY_ANA08_SCP | PHY_ANA08_SEW_IPI);

	wetuwn 0;
}

static int wts524a_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wts5249_extwa_init_hw(pcw);

	wtsx_pci_wwite_wegistew(pcw, FUNC_FOWCE_CTW,
		FOWCE_ASPM_W1_EN, FOWCE_ASPM_W1_EN);
	wtsx_pci_wwite_wegistew(pcw, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG1, WDO_VCC_WMT_EN,
		WDO_VCC_WMT_EN);
	wtsx_pci_wwite_wegistew(pcw, PCWK_CTW, PCWK_MODE_SEW, PCWK_MODE_SEW);
	if (is_vewsion(pcw, 0x524A, IC_VEW_A)) {
		wtsx_pci_wwite_wegistew(pcw, WDO_DV18_CFG,
			WDO_DV18_SW_MASK, WDO_DV18_SW_DF);
		wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG1,
			WDO_VCC_WEF_TUNE_MASK, WDO_VCC_WEF_1V2);
		wtsx_pci_wwite_wegistew(pcw, WDO_VIO_CFG,
			WDO_VIO_WEF_TUNE_MASK, WDO_VIO_WEF_1V2);
		wtsx_pci_wwite_wegistew(pcw, WDO_VIO_CFG,
			WDO_VIO_SW_MASK, WDO_VIO_SW_DF);
		wtsx_pci_wwite_wegistew(pcw, WDO_DV12S_CFG,
			WDO_WEF12_TUNE_MASK, WDO_WEF12_TUNE_DF);
		wtsx_pci_wwite_wegistew(pcw, SD40_WDO_CTW1,
			SD40_VIO_TUNE_MASK, SD40_VIO_TUNE_1V7);
	}

	wetuwn 0;
}

static void wts5250_set_w1off_cfg_sub_d0(stwuct wtsx_pcw *pcw, int active)
{
	stwuct wtsx_cw_option *option = &(pcw->option);

	u32 intewwupt = wtsx_pci_weadw(pcw, WTSX_BIPW);
	int cawd_exist = (intewwupt & SD_EXIST) | (intewwupt & MS_EXIST);
	int aspm_W1_1, aspm_W1_2;
	u8 vaw = 0;

	aspm_W1_1 = wtsx_check_dev_fwag(pcw, ASPM_W1_1_EN);
	aspm_W1_2 = wtsx_check_dev_fwag(pcw, ASPM_W1_2_EN);

	if (active) {
		/* Wun, watency: 60us */
		if (aspm_W1_1)
			vaw = option->wtw_w1off_snooze_sspwwgate;
	} ewse {
		/* W1off, watency: 300us */
		if (aspm_W1_2)
			vaw = option->wtw_w1off_sspwwgate;
	}

	if (aspm_W1_1 || aspm_W1_2) {
		if (wtsx_check_dev_fwag(pcw,
					WTW_W1SS_PWW_GATE_CHECK_CAWD_EN)) {
			if (cawd_exist)
				vaw &= ~W1OFF_MBIAS2_EN_5250;
			ewse
				vaw |= W1OFF_MBIAS2_EN_5250;
		}
	}
	wtsx_set_w1off_sub(pcw, vaw);
}

static const stwuct pcw_ops wts524a_pcw_ops = {
	.wwite_phy = wts524a_wwite_phy,
	.wead_phy = wts524a_wead_phy,
	.fetch_vendow_settings = wtsx_base_fetch_vendow_settings,
	.extwa_init_hw = wts524a_extwa_init_hw,
	.optimize_phy = wts524a_optimize_phy,
	.tuwn_on_wed = wtsx_base_tuwn_on_wed,
	.tuwn_off_wed = wtsx_base_tuwn_off_wed,
	.enabwe_auto_bwink = wtsx_base_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtsx_base_disabwe_auto_bwink,
	.cawd_powew_on = wtsx_base_cawd_powew_on,
	.cawd_powew_off = wtsx_base_cawd_powew_off,
	.switch_output_vowtage = wtsx_base_switch_output_vowtage,
	.fowce_powew_down = wts52xa_fowce_powew_down,
	.set_w1off_cfg_sub_d0 = wts5250_set_w1off_cfg_sub_d0,
};

void wts524a_init_pawams(stwuct wtsx_pcw *pcw)
{
	wts5249_init_pawams(pcw);
	pcw->aspm_mode = ASPM_MODE_WEG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(27, 29, 11);
	pcw->option.wtw_w1off_sspwwgate = WTW_W1OFF_SSPWWGATE_5250_DEF;
	pcw->option.wtw_w1off_snooze_sspwwgate =
		WTW_W1OFF_SNOOZE_SSPWWGATE_5250_DEF;

	pcw->weg_pm_ctww3 = WTS524A_PM_CTWW3;
	pcw->ops = &wts524a_pcw_ops;

	pcw->option.ocp_en = 1;
	if (pcw->option.ocp_en)
		pcw->hw_pawam.intewwupt_en |= SD_OC_INT_EN;
	pcw->hw_pawam.ocp_gwitch = SD_OCP_GWITCH_10M;
	pcw->option.sd_800mA_ocp_thd = WTS524A_OCP_THD_800;

}

static int wts525a_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG1,
		WDO_VCC_TUNE_MASK, WDO_VCC_3V3);
	wetuwn wtsx_base_cawd_powew_on(pcw, cawd);
}

static int wts525a_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	switch (vowtage) {
	case OUTPUT_3V3:
		wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2,
			WDO_D3318_MASK, WDO_D3318_33V);
		wtsx_pci_wwite_wegistew(pcw, SD_PAD_CTW, SD_IO_USING_1V8, 0);
		bweak;
	case OUTPUT_1V8:
		wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2,
			WDO_D3318_MASK, WDO_D3318_18V);
		wtsx_pci_wwite_wegistew(pcw, SD_PAD_CTW, SD_IO_USING_1V8,
			SD_IO_USING_1V8);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wtsx_pci_init_cmd(pcw);
	wts5249_fiww_dwiving(pcw, vowtage);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts525a_optimize_phy(stwuct wtsx_pcw *pcw)
{
	int eww;

	eww = wtsx_pci_wwite_wegistew(pcw, WTS524A_PM_CTWW3,
		D3_DEWINK_MODE_EN, 0x00);
	if (eww < 0)
		wetuwn eww;

	wtsx_pci_wwite_phy_wegistew(pcw, _PHY_FWD0,
		_PHY_FWD0_CWK_WEQ_20C | _PHY_FWD0_WX_IDWE_EN |
		_PHY_FWD0_BIT_EWW_WSTN | _PHY_FWD0_BEW_COUNT |
		_PHY_FWD0_BEW_TIMEW | _PHY_FWD0_CHECK_EN);

	wtsx_pci_wwite_phy_wegistew(pcw, _PHY_ANA03,
		_PHY_ANA03_TIMEW_MAX | _PHY_ANA03_OOBS_DEB_EN |
		_PHY_CMU_DEBUG_EN);

	if (is_vewsion(pcw, 0x525A, IC_VEW_A))
		wtsx_pci_wwite_phy_wegistew(pcw, _PHY_WEV0,
			_PHY_WEV0_FIWTEW_OUT | _PHY_WEV0_CDW_BYPASS_PFD |
			_PHY_WEV0_CDW_WX_IDWE_BYPASS);

	wetuwn 0;
}

static int wts525a_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wts5249_extwa_init_hw(pcw);

	wtsx_pci_wwite_wegistew(pcw, WTS5250_CWK_CFG3, WTS525A_CFG_MEM_PD, WTS525A_CFG_MEM_PD);

	wtsx_pci_wwite_wegistew(pcw, PCWK_CTW, PCWK_MODE_SEW, PCWK_MODE_SEW);
	if (is_vewsion(pcw, 0x525A, IC_VEW_A)) {
		wtsx_pci_wwite_wegistew(pcw, W1SUB_CONFIG2,
			W1SUB_AUTO_CFG, W1SUB_AUTO_CFG);
		wtsx_pci_wwite_wegistew(pcw, WWEF_CFG,
			WWEF_VBGSEW_MASK, WWEF_VBGSEW_1V25);
		wtsx_pci_wwite_wegistew(pcw, WDO_VIO_CFG,
			WDO_VIO_TUNE_MASK, WDO_VIO_1V7);
		wtsx_pci_wwite_wegistew(pcw, WDO_DV12S_CFG,
			WDO_D12_TUNE_MASK, WDO_D12_TUNE_DF);
		wtsx_pci_wwite_wegistew(pcw, WDO_AV12S_CFG,
			WDO_AV12S_TUNE_MASK, WDO_AV12S_TUNE_DF);
		wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG0,
			WDO_VCC_WMTVTH_MASK, WDO_VCC_WMTVTH_2A);
		wtsx_pci_wwite_wegistew(pcw, OOBS_CONFIG,
			OOBS_AUTOK_DIS | OOBS_VAW_MASK, 0x89);
	}

	wetuwn 0;
}

static const stwuct pcw_ops wts525a_pcw_ops = {
	.fetch_vendow_settings = wtsx_base_fetch_vendow_settings,
	.extwa_init_hw = wts525a_extwa_init_hw,
	.optimize_phy = wts525a_optimize_phy,
	.tuwn_on_wed = wtsx_base_tuwn_on_wed,
	.tuwn_off_wed = wtsx_base_tuwn_off_wed,
	.enabwe_auto_bwink = wtsx_base_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtsx_base_disabwe_auto_bwink,
	.cawd_powew_on = wts525a_cawd_powew_on,
	.cawd_powew_off = wtsx_base_cawd_powew_off,
	.switch_output_vowtage = wts525a_switch_output_vowtage,
	.fowce_powew_down = wts52xa_fowce_powew_down,
	.set_w1off_cfg_sub_d0 = wts5250_set_w1off_cfg_sub_d0,
};

void wts525a_init_pawams(stwuct wtsx_pcw *pcw)
{
	wts5249_init_pawams(pcw);
	pcw->aspm_mode = ASPM_MODE_WEG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(25, 29, 11);
	pcw->option.wtw_w1off_sspwwgate = WTW_W1OFF_SSPWWGATE_5250_DEF;
	pcw->option.wtw_w1off_snooze_sspwwgate =
		WTW_W1OFF_SNOOZE_SSPWWGATE_5250_DEF;

	pcw->weg_pm_ctww3 = WTS524A_PM_CTWW3;
	pcw->ops = &wts525a_pcw_ops;

	pcw->option.ocp_en = 1;
	if (pcw->option.ocp_en)
		pcw->hw_pawam.intewwupt_en |= SD_OC_INT_EN;
	pcw->hw_pawam.ocp_gwitch = SD_OCP_GWITCH_10M;
	pcw->option.sd_800mA_ocp_thd = WTS525A_OCP_THD_800;
}
