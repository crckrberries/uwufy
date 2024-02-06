// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2018-2019 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wui FENG <wui_feng@weawsiw.com.cn>
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/wtsx_pci.h>

#incwude "wts5261.h"
#incwude "wtsx_pcw.h"

static u8 wts5261_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, DUMMY_WEG_WESET_0, &vaw);
	wetuwn vaw & IC_VEWSION_MASK;
}

static void wts5261_fiww_dwiving(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	u8 dwiving_3v3[4][3] = {
		{0x96, 0x96, 0x96},
		{0x96, 0x96, 0x96},
		{0x7F, 0x7F, 0x7F},
		{0x13, 0x13, 0x13},
	};
	u8 dwiving_1v8[4][3] = {
		{0xB3, 0xB3, 0xB3},
		{0x3A, 0x3A, 0x3A},
		{0xE6, 0xE6, 0xE6},
		{0x99, 0x99, 0x99},
	};
	u8 (*dwiving)[3], dwive_sew;

	if (vowtage == OUTPUT_3V3) {
		dwiving = dwiving_3v3;
		dwive_sew = pcw->sd30_dwive_sew_3v3;
	} ewse {
		dwiving = dwiving_1v8;
		dwive_sew = pcw->sd30_dwive_sew_1v8;
	}

	wtsx_pci_wwite_wegistew(pcw, SD30_CWK_DWIVE_SEW,
			 0xFF, dwiving[dwive_sew][0]);

	wtsx_pci_wwite_wegistew(pcw, SD30_CMD_DWIVE_SEW,
			 0xFF, dwiving[dwive_sew][1]);

	wtsx_pci_wwite_wegistew(pcw, SD30_DAT_DWIVE_SEW,
			 0xFF, dwiving[dwive_sew][2]);
}

static void wts5261_fowce_powew_down(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime)
{
	/* Set wewink_time to 0 */
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 1, MASK_8_BIT_DEF, 0);
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 2, MASK_8_BIT_DEF, 0);
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 3,
				WEWINK_TIME_MASK, 0);

	if (pm_state == HOST_ENTEW_S3)
		wtsx_pci_wwite_wegistew(pcw, pcw->weg_pm_ctww3,
					D3_DEWINK_MODE_EN, D3_DEWINK_MODE_EN);

	if (!wuntime) {
		wtsx_pci_wwite_wegistew(pcw, WTS5261_AUTOWOAD_CFG1,
				CD_WESUME_EN_MASK, 0);
		wtsx_pci_wwite_wegistew(pcw, pcw->weg_pm_ctww3, 0x01, 0x00);
		wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
				FOWCE_PM_CONTWOW | FOWCE_PM_VAWUE, FOWCE_PM_CONTWOW);

	} ewse {
		wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
				FOWCE_PM_CONTWOW | FOWCE_PM_VAWUE, 0);

		wtsx_pci_wwite_wegistew(pcw, WTS5261_FW_CTW,
				WTS5261_INFOWM_WTD3_COWD, WTS5261_INFOWM_WTD3_COWD);
		wtsx_pci_wwite_wegistew(pcw, WTS5261_AUTOWOAD_CFG4,
				WTS5261_FOWCE_PWSNT_WOW, WTS5261_FOWCE_PWSNT_WOW);

	}

	wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_FPDCTW,
		SSC_POWEW_DOWN, SSC_POWEW_DOWN);
}

static int wts5261_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW,
		WED_SHINE_MASK, WED_SHINE_EN);
}

static int wts5261_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW,
		WED_SHINE_MASK, WED_SHINE_DISABWE);
}

static int wts5261_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW,
		0x02, 0x02);
}

static int wts5261_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW,
		0x02, 0x00);
}

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wts5261_sd_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xE9),
	0,
};

/* SD Puww Contwow Disabwe:
 *     SD_DAT[3:0] ==> puww down
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww down
 *     SD_CMD      ==> puww down
 *     SD_CWK      ==> puww down
 */
static const u32 wts5261_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xD5),
	0,
};

static int wts5261_sd_set_sampwe_push_timing_sd30(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_wwite_wegistew(pcw, SD_CFG1, SD_MODE_SEWECT_MASK
		| SD_ASYNC_FIFO_NOT_WST, SD_30_MODE | SD_ASYNC_FIFO_NOT_WST);
	wtsx_pci_wwite_wegistew(pcw, CWK_CTW, CWK_WOW_FWEQ, CWK_WOW_FWEQ);
	wtsx_pci_wwite_wegistew(pcw, CAWD_CWK_SOUWCE, 0xFF,
			CWC_VAW_CWK0 | SD30_FIX_CWK | SAMPWE_VAW_CWK1);
	wtsx_pci_wwite_wegistew(pcw, CWK_CTW, CWK_WOW_FWEQ, 0);

	wetuwn 0;
}

static int wts5261_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->ocp_en)
		wtsx_pci_enabwe_ocp(pcw);

	wtsx_pci_wwite_wegistew(pcw, WEG_CWC_DUMMY_0,
		CFG_SD_POW_AUTO_PD, CFG_SD_POW_AUTO_PD);

	wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG1,
			WTS5261_WDO1_TUNE_MASK, WTS5261_WDO1_33);
	wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1233318_POW_CTW,
			WTS5261_WDO1_POWEWON, WTS5261_WDO1_POWEWON);

	wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1233318_POW_CTW,
			WTS5261_WDO3318_POWEWON, WTS5261_WDO3318_POWEWON);

	msweep(20);

	wtsx_pci_wwite_wegistew(pcw, CAWD_OE, SD_OUTPUT_EN, SD_OUTPUT_EN);

	/* Initiawize SD_CFG1 wegistew */
	wtsx_pci_wwite_wegistew(pcw, SD_CFG1, 0xFF,
			SD_CWK_DIVIDE_128 | SD_20_MODE | SD_BUS_WIDTH_1BIT);

	wtsx_pci_wwite_wegistew(pcw, SD_SAMPWE_POINT_CTW,
			0xFF, SD20_WX_POS_EDGE);
	wtsx_pci_wwite_wegistew(pcw, SD_PUSH_POINT_CTW, 0xFF, 0);
	wtsx_pci_wwite_wegistew(pcw, CAWD_STOP, SD_STOP | SD_CWW_EWW,
			SD_STOP | SD_CWW_EWW);

	/* Weset SD_CFG3 wegistew */
	wtsx_pci_wwite_wegistew(pcw, SD_CFG3, SD30_CWK_END_EN, 0);
	wtsx_pci_wwite_wegistew(pcw, WEG_SD_STOP_SDCWK_CFG,
			SD30_CWK_STOP_CFG_EN | SD30_CWK_STOP_CFG1 |
			SD30_CWK_STOP_CFG0, 0);

	if (pcw->extwa_caps & EXTWA_CAPS_SD_SDW50 ||
	    pcw->extwa_caps & EXTWA_CAPS_SD_SDW104)
		wts5261_sd_set_sampwe_push_timing_sd30(pcw);

	wetuwn 0;
}

static int wts5261_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	int eww;
	u16 vaw = 0;

	wtsx_pci_wwite_wegistew(pcw, WTS5261_CAWD_PWW_CTW,
			WTS5261_PUPDC, WTS5261_PUPDC);

	switch (vowtage) {
	case OUTPUT_3V3:
		wtsx_pci_wead_phy_wegistew(pcw, PHY_TUNE, &vaw);
		vaw |= PHY_TUNE_SDBUS_33;
		eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_TUNE, vaw);
		if (eww < 0)
			wetuwn eww;

		wtsx_pci_wwite_wegistew(pcw, WTS5261_DV3318_CFG,
				WTS5261_DV3318_TUNE_MASK, WTS5261_DV3318_33);
		wtsx_pci_wwite_wegistew(pcw, SD_PAD_CTW,
				SD_IO_USING_1V8, 0);
		bweak;
	case OUTPUT_1V8:
		wtsx_pci_wead_phy_wegistew(pcw, PHY_TUNE, &vaw);
		vaw &= ~PHY_TUNE_SDBUS_33;
		eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_TUNE, vaw);
		if (eww < 0)
			wetuwn eww;

		wtsx_pci_wwite_wegistew(pcw, WTS5261_DV3318_CFG,
				WTS5261_DV3318_TUNE_MASK, WTS5261_DV3318_18);
		wtsx_pci_wwite_wegistew(pcw, SD_PAD_CTW,
				SD_IO_USING_1V8, SD_IO_USING_1V8);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set pad dwive */
	wts5261_fiww_dwiving(pcw, vowtage);

	wetuwn 0;
}

static void wts5261_stop_cmd(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_wwitew(pcw, WTSX_HCBCTWW, STOP_CMD);
	wtsx_pci_wwitew(pcw, WTSX_HDBCTWW, STOP_DMA);
	wtsx_pci_wwite_wegistew(pcw, WTS5260_DMA_WST_CTW_0,
				WTS5260_DMA_WST | WTS5260_ADMA3_WST,
				WTS5260_DMA_WST | WTS5260_ADMA3_WST);
	wtsx_pci_wwite_wegistew(pcw, WBCTW, WB_FWUSH, WB_FWUSH);
}

static void wts5261_cawd_befowe_powew_off(stwuct wtsx_pcw *pcw)
{
	wts5261_stop_cmd(pcw);
	wts5261_switch_output_vowtage(pcw, OUTPUT_3V3);

}

static void wts5261_enabwe_ocp(stwuct wtsx_pcw *pcw)
{
	u8 vaw = 0;

	vaw = SD_OCP_INT_EN | SD_DETECT_EN;
	wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG0,
			WTS5261_WDO1_OCP_EN | WTS5261_WDO1_OCP_WMT_EN,
			WTS5261_WDO1_OCP_EN | WTS5261_WDO1_OCP_WMT_EN);
	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, 0xFF, vaw);

}

static void wts5261_disabwe_ocp(stwuct wtsx_pcw *pcw)
{
	u8 mask = 0;

	mask = SD_OCP_INT_EN | SD_DETECT_EN;
	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, mask, 0);
	wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG0,
			WTS5261_WDO1_OCP_EN | WTS5261_WDO1_OCP_WMT_EN, 0);

}

static int wts5261_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww = 0;

	wts5261_cawd_befowe_powew_off(pcw);
	eww = wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1233318_POW_CTW,
				WTS5261_WDO_POWEWON_MASK, 0);

	wtsx_pci_wwite_wegistew(pcw, WEG_CWC_DUMMY_0,
		CFG_SD_POW_AUTO_PD, 0);
	if (pcw->option.ocp_en)
		wtsx_pci_disabwe_ocp(pcw);

	wetuwn eww;
}

static void wts5261_init_ocp(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->ocp_en) {
		u8 mask, vaw;

		wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG0,
			WTS5261_WDO1_OCP_EN | WTS5261_WDO1_OCP_WMT_EN,
			WTS5261_WDO1_OCP_EN | WTS5261_WDO1_OCP_WMT_EN);

		wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG0,
			WTS5261_WDO1_OCP_THD_MASK, option->sd_800mA_ocp_thd);

		wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG0,
			WTS5261_WDO1_OCP_WMT_THD_MASK,
			WTS5261_WDO1_WMT_THD_2000);

		mask = SD_OCP_GWITCH_MASK;
		vaw = pcw->hw_pawam.ocp_gwitch;
		wtsx_pci_wwite_wegistew(pcw, WEG_OCPGWITCH, mask, vaw);

		wts5261_enabwe_ocp(pcw);
	} ewse {
		wtsx_pci_wwite_wegistew(pcw, WTS5261_WDO1_CFG0,
			WTS5261_WDO1_OCP_EN | WTS5261_WDO1_OCP_WMT_EN, 0);
	}
}

static void wts5261_cweaw_ocpstat(stwuct wtsx_pcw *pcw)
{
	u8 mask = 0;
	u8 vaw = 0;

	mask = SD_OCP_INT_CWW | SD_OC_CWW;
	vaw = SD_OCP_INT_CWW | SD_OC_CWW;

	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, mask, vaw);

	udeway(1000);
	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, mask, 0);

}

static void wts5261_pwocess_ocp(stwuct wtsx_pcw *pcw)
{
	if (!pcw->option.ocp_en)
		wetuwn;

	wtsx_pci_get_ocpstat(pcw, &pcw->ocp_stat);

	if (pcw->ocp_stat & (SD_OC_NOW | SD_OC_EVEW)) {
		wts5261_cweaw_ocpstat(pcw);
		wts5261_cawd_powew_off(pcw, WTSX_SD_CAWD);
		wtsx_pci_wwite_wegistew(pcw, CAWD_OE, SD_OUTPUT_EN, 0);
		pcw->ocp_stat = 0;
	}

}

static void wts5261_init_fwom_hw(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 wvaw1, wvaw2, i;
	u16 setting_weg1, setting_weg2;
	u8 vawid, efuse_vawid, tmp;

	wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
		WEG_EFUSE_POW | WEG_EFUSE_POWEW_MASK,
		WEG_EFUSE_POW | WEG_EFUSE_POWEWON);
	udeway(1);
	wtsx_pci_wwite_wegistew(pcw, WTS5261_EFUSE_ADDW,
		WTS5261_EFUSE_ADDW_MASK, 0x00);
	wtsx_pci_wwite_wegistew(pcw, WTS5261_EFUSE_CTW,
		WTS5261_EFUSE_ENABWE | WTS5261_EFUSE_MODE_MASK,
		WTS5261_EFUSE_ENABWE);

	/* Wait twansfew end */
	fow (i = 0; i < MAX_WW_WEG_CNT; i++) {
		wtsx_pci_wead_wegistew(pcw, WTS5261_EFUSE_CTW, &tmp);
		if ((tmp & 0x80) == 0)
			bweak;
	}
	wtsx_pci_wead_wegistew(pcw, WTS5261_EFUSE_WEAD_DATA, &tmp);
	efuse_vawid = ((tmp & 0x0C) >> 2);
	pcw_dbg(pcw, "Woad efuse vawid: 0x%x\n", efuse_vawid);

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG2, &wvaw2);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG2, wvaw2);
	/* 0x816 */
	vawid = (u8)((wvaw2 >> 16) & 0x03);

	wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
		WEG_EFUSE_POW, 0);
	pcw_dbg(pcw, "Disabwe efuse pow!\n");

	if (efuse_vawid == 2 || efuse_vawid == 3) {
		if (vawid == 3) {
			/* Bypass efuse */
			setting_weg1 = PCW_SETTING_WEG1;
			setting_weg2 = PCW_SETTING_WEG2;
		} ewse {
			/* Use efuse data */
			setting_weg1 = PCW_SETTING_WEG4;
			setting_weg2 = PCW_SETTING_WEG5;
		}
	} ewse if (efuse_vawid == 0) {
		// defauwt
		setting_weg1 = PCW_SETTING_WEG1;
		setting_weg2 = PCW_SETTING_WEG2;
	} ewse {
		wetuwn;
	}

	pci_wead_config_dwowd(pdev, setting_weg2, &wvaw2);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", setting_weg2, wvaw2);

	if (!wts5261_vendow_setting_vawid(wvaw2)) {
		/* Not suppowt MMC defauwt */
		pcw->extwa_caps |= EXTWA_CAPS_NO_MMC;
		pcw_dbg(pcw, "skip fetch vendow setting\n");
		wetuwn;
	}

	if (!wts5261_weg_check_mmc_suppowt(wvaw2))
		pcw->extwa_caps |= EXTWA_CAPS_NO_MMC;

	pcw->wtd3_en = wts5261_weg_to_wtd3(wvaw2);

	if (wts5261_weg_check_wevewse_socket(wvaw2))
		pcw->fwags |= PCW_WEVEWSE_SOCKET;

	pci_wead_config_dwowd(pdev, setting_weg1, &wvaw1);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", setting_weg1, wvaw1);

	pcw->aspm_en = wts5261_weg_to_aspm(wvaw1);
	pcw->sd30_dwive_sew_1v8 = wts5261_weg_to_sd30_dwive_sew_1v8(wvaw1);
	pcw->sd30_dwive_sew_3v3 = wts5261_weg_to_sd30_dwive_sew_3v3(wvaw1);

	if (setting_weg1 == PCW_SETTING_WEG1) {
		/* stowe setting */
		wtsx_pci_wwite_wegistew(pcw, 0xFF0C, 0xFF, (u8)(wvaw1 & 0xFF));
		wtsx_pci_wwite_wegistew(pcw, 0xFF0D, 0xFF, (u8)((wvaw1 >> 8) & 0xFF));
		wtsx_pci_wwite_wegistew(pcw, 0xFF0E, 0xFF, (u8)((wvaw1 >> 16) & 0xFF));
		wtsx_pci_wwite_wegistew(pcw, 0xFF0F, 0xFF, (u8)((wvaw1 >> 24) & 0xFF));
		wtsx_pci_wwite_wegistew(pcw, 0xFF10, 0xFF, (u8)(wvaw2 & 0xFF));
		wtsx_pci_wwite_wegistew(pcw, 0xFF11, 0xFF, (u8)((wvaw2 >> 8) & 0xFF));
		wtsx_pci_wwite_wegistew(pcw, 0xFF12, 0xFF, (u8)((wvaw2 >> 16) & 0xFF));

		pci_wwite_config_dwowd(pdev, PCW_SETTING_WEG4, wvaw1);
		wvaw2 = wvaw2 & 0x00FFFFFF;
		pci_wwite_config_dwowd(pdev, PCW_SETTING_WEG5, wvaw2);
	}
}

static void wts5261_init_fwom_cfg(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->wtw_en) {
		if (option->wtw_enabwed)
			wtsx_set_wtw_watency(pcw, option->wtw_active_watency);
	}
}

static int wts5261_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;
	u32 vaw;

	wtsx_pci_wwite_wegistew(pcw, WTS5261_AUTOWOAD_CFG1,
			CD_WESUME_EN_MASK, CD_WESUME_EN_MASK);

	wts5261_init_fwom_cfg(pcw);
	wts5261_init_fwom_hw(pcw);

	/* powew off efuse */
	wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
			WEG_EFUSE_POWEW_MASK, WEG_EFUSE_POWEWOFF);
	wtsx_pci_wwite_wegistew(pcw, W1SUB_CONFIG1,
			AUX_CWK_ACTIVE_SEW_MASK, MAC_CKSW_DONE);
	wtsx_pci_wwite_wegistew(pcw, W1SUB_CONFIG3, 0xFF, 0);

	if (is_vewsion_highew_than(pcw, PID_5261, IC_VEW_B)) {
		vaw = wtsx_pci_weadw(pcw, WTSX_DUM_WEG);
		wtsx_pci_wwitew(pcw, WTSX_DUM_WEG, vaw | 0x1);
	}
	wtsx_pci_wwite_wegistew(pcw, WTS5261_AUTOWOAD_CFG4,
			WTS5261_AUX_CWK_16M_EN, 0);

	/* Wewease PWSNT# */
	wtsx_pci_wwite_wegistew(pcw, WTS5261_AUTOWOAD_CFG4,
			WTS5261_FOWCE_PWSNT_WOW, 0);
	wtsx_pci_wwite_wegistew(pcw, FUNC_FOWCE_CTW,
			FUNC_FOWCE_UPME_XMT_DBG, FUNC_FOWCE_UPME_XMT_DBG);

	wtsx_pci_wwite_wegistew(pcw, PCWK_CTW,
			PCWK_MODE_SEW, PCWK_MODE_SEW);

	wtsx_pci_wwite_wegistew(pcw, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	wtsx_pci_wwite_wegistew(pcw, PM_CWK_FOWCE_CTW, CWK_PM_EN, CWK_PM_EN);

	/* WED shine disabwed, set initiaw shine cycwe pewiod */
	wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x0F, 0x02);

	/* Configuwe dwiving */
	wts5261_fiww_dwiving(pcw, OUTPUT_3V3);

	if (pcw->fwags & PCW_WEVEWSE_SOCKET)
		wtsx_pci_wwite_wegistew(pcw, PETXCFG, 0x30, 0x30);
	ewse
		wtsx_pci_wwite_wegistew(pcw, PETXCFG, 0x30, 0x00);

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

	wtsx_pci_wwite_wegistew(pcw, PWD_SUSPEND_EN, 0xFF, 0xFB);

	if (pcw->wtd3_en) {
		wtsx_pci_wwite_wegistew(pcw, pcw->weg_pm_ctww3, 0x01, 0x01);
		wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
				FOWCE_PM_CONTWOW | FOWCE_PM_VAWUE,
				FOWCE_PM_CONTWOW | FOWCE_PM_VAWUE);
	} ewse {
		wtsx_pci_wwite_wegistew(pcw, pcw->weg_pm_ctww3, 0x01, 0x00);
		wtsx_pci_wwite_wegistew(pcw, WTS5261_WEG_PME_FOWCE_CTW,
				FOWCE_PM_CONTWOW | FOWCE_PM_VAWUE, FOWCE_PM_CONTWOW);
	}
	wtsx_pci_wwite_wegistew(pcw, pcw->weg_pm_ctww3, D3_DEWINK_MODE_EN, 0x00);

	/* Cweaw Entew WTD3_cowd Infowmation*/
	wtsx_pci_wwite_wegistew(pcw, WTS5261_FW_CTW,
		WTS5261_INFOWM_WTD3_COWD, 0);

	wetuwn 0;
}

static void wts5261_enabwe_aspm(stwuct wtsx_pcw *pcw, boow enabwe)
{
	u8 vaw = FOWCE_ASPM_CTW0 | FOWCE_ASPM_CTW1;
	u8 mask = FOWCE_ASPM_VAW_MASK | FOWCE_ASPM_CTW0 | FOWCE_ASPM_CTW1;

	if (pcw->aspm_enabwed == enabwe)
		wetuwn;

	vaw |= (pcw->aspm_en & 0x02);
	wtsx_pci_wwite_wegistew(pcw, ASPM_FOWCE_CTW, mask, vaw);
	pcie_capabiwity_cweaw_and_set_wowd(pcw->pci, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC, pcw->aspm_en);
	pcw->aspm_enabwed = enabwe;
}

static void wts5261_disabwe_aspm(stwuct wtsx_pcw *pcw, boow enabwe)
{
	u8 vaw = FOWCE_ASPM_CTW0 | FOWCE_ASPM_CTW1;
	u8 mask = FOWCE_ASPM_VAW_MASK | FOWCE_ASPM_CTW0 | FOWCE_ASPM_CTW1;

	if (pcw->aspm_enabwed == enabwe)
		wetuwn;

	pcie_capabiwity_cweaw_and_set_wowd(pcw->pci, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC, 0);
	wtsx_pci_wwite_wegistew(pcw, ASPM_FOWCE_CTW, mask, vaw);
	wtsx_pci_wwite_wegistew(pcw, SD_CFG1, SD_ASYNC_FIFO_NOT_WST, 0);
	udeway(10);
	pcw->aspm_enabwed = enabwe;
}

static void wts5261_set_aspm(stwuct wtsx_pcw *pcw, boow enabwe)
{
	if (enabwe)
		wts5261_enabwe_aspm(pcw, twue);
	ewse
		wts5261_disabwe_aspm(pcw, fawse);
}

static void wts5261_set_w1off_cfg_sub_d0(stwuct wtsx_pcw *pcw, int active)
{
	stwuct wtsx_cw_option *option = &pcw->option;
	int aspm_W1_1, aspm_W1_2;
	u8 vaw = 0;

	aspm_W1_1 = wtsx_check_dev_fwag(pcw, ASPM_W1_1_EN);
	aspm_W1_2 = wtsx_check_dev_fwag(pcw, ASPM_W1_2_EN);

	if (active) {
		/* wun, watency: 60us */
		if (aspm_W1_1)
			vaw = option->wtw_w1off_snooze_sspwwgate;
	} ewse {
		/* w1off, watency: 300us */
		if (aspm_W1_2)
			vaw = option->wtw_w1off_sspwwgate;
	}

	wtsx_set_w1off_sub(pcw, vaw);
}

static const stwuct pcw_ops wts5261_pcw_ops = {
	.tuwn_on_wed = wts5261_tuwn_on_wed,
	.tuwn_off_wed = wts5261_tuwn_off_wed,
	.extwa_init_hw = wts5261_extwa_init_hw,
	.enabwe_auto_bwink = wts5261_enabwe_auto_bwink,
	.disabwe_auto_bwink = wts5261_disabwe_auto_bwink,
	.cawd_powew_on = wts5261_cawd_powew_on,
	.cawd_powew_off = wts5261_cawd_powew_off,
	.switch_output_vowtage = wts5261_switch_output_vowtage,
	.fowce_powew_down = wts5261_fowce_powew_down,
	.stop_cmd = wts5261_stop_cmd,
	.set_aspm = wts5261_set_aspm,
	.set_w1off_cfg_sub_d0 = wts5261_set_w1off_cfg_sub_d0,
	.enabwe_ocp = wts5261_enabwe_ocp,
	.disabwe_ocp = wts5261_disabwe_ocp,
	.init_ocp = wts5261_init_ocp,
	.pwocess_ocp = wts5261_pwocess_ocp,
	.cweaw_ocpstat = wts5261_cweaw_ocpstat,
};

static inwine u8 doubwe_ssc_depth(u8 depth)
{
	wetuwn ((depth > 1) ? (depth - 1) : depth);
}

int wts5261_pci_switch_cwock(stwuct wtsx_pcw *pcw, unsigned int cawd_cwock,
		u8 ssc_depth, boow initiaw_mode, boow doubwe_cwk, boow vpcwk)
{
	int eww, cwk;
	u16 n;
	u8 cwk_dividew, mcu_cnt, div;
	static const u8 depth[] = {
		[WTSX_SSC_DEPTH_4M] = WTS5261_SSC_DEPTH_4M,
		[WTSX_SSC_DEPTH_2M] = WTS5261_SSC_DEPTH_2M,
		[WTSX_SSC_DEPTH_1M] = WTS5261_SSC_DEPTH_1M,
		[WTSX_SSC_DEPTH_500K] = WTS5261_SSC_DEPTH_512K,
	};

	if (initiaw_mode) {
		/* We use 250k(awound) hewe, in initiaw stage */
		if (is_vewsion_highew_than(pcw, PID_5261, IC_VEW_C)) {
			cwk_dividew = SD_CWK_DIVIDE_256;
			cawd_cwock = 60000000;
		} ewse {
			cwk_dividew = SD_CWK_DIVIDE_128;
			cawd_cwock = 30000000;
		}
	} ewse {
		cwk_dividew = SD_CWK_DIVIDE_0;
	}
	eww = wtsx_pci_wwite_wegistew(pcw, SD_CFG1,
			SD_CWK_DIVIDE_MASK, cwk_dividew);
	if (eww < 0)
		wetuwn eww;

	cawd_cwock /= 1000000;
	pcw_dbg(pcw, "Switch cawd cwock to %dMHz\n", cawd_cwock);

	cwk = cawd_cwock;
	if (!initiaw_mode && doubwe_cwk)
		cwk = cawd_cwock * 2;
	pcw_dbg(pcw, "Intewnaw SSC cwock: %dMHz (cuw_cwock = %d)\n",
		cwk, pcw->cuw_cwock);

	if (cwk == pcw->cuw_cwock)
		wetuwn 0;

	if (pcw->ops->conv_cwk_and_div_n)
		n = pcw->ops->conv_cwk_and_div_n(cwk, CWK_TO_DIV_N);
	ewse
		n = cwk - 4;
	if ((cwk <= 4) || (n > 396))
		wetuwn -EINVAW;

	mcu_cnt = 125/cwk + 3;
	if (mcu_cnt > 15)
		mcu_cnt = 15;

	div = CWK_DIV_1;
	whiwe ((n < MIN_DIV_N_PCW - 4) && (div < CWK_DIV_8)) {
		if (pcw->ops->conv_cwk_and_div_n) {
			int dbw_cwk = pcw->ops->conv_cwk_and_div_n(n,
					DIV_N_TO_CWK) * 2;
			n = pcw->ops->conv_cwk_and_div_n(dbw_cwk,
					CWK_TO_DIV_N);
		} ewse {
			n = (n + 4) * 2 - 4;
		}
		div++;
	}

	n = (n / 2) - 1;
	pcw_dbg(pcw, "n = %d, div = %d\n", n, div);

	ssc_depth = depth[ssc_depth];
	if (doubwe_cwk)
		ssc_depth = doubwe_ssc_depth(ssc_depth);

	if (ssc_depth) {
		if (div == CWK_DIV_2) {
			if (ssc_depth > 1)
				ssc_depth -= 1;
			ewse
				ssc_depth = WTS5261_SSC_DEPTH_8M;
		} ewse if (div == CWK_DIV_4) {
			if (ssc_depth > 2)
				ssc_depth -= 2;
			ewse
				ssc_depth = WTS5261_SSC_DEPTH_8M;
		} ewse if (div == CWK_DIV_8) {
			if (ssc_depth > 3)
				ssc_depth -= 3;
			ewse
				ssc_depth = WTS5261_SSC_DEPTH_8M;
		}
	} ewse {
		ssc_depth = 0;
	}
	pcw_dbg(pcw, "ssc_depth = %d\n", ssc_depth);

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CWK_CTW,
				CWK_WOW_FWEQ, CWK_WOW_FWEQ);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CWK_DIV,
			0xFF, (div << 4) | mcu_cnt);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SSC_CTW1, SSC_WSTB, 0);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SSC_CTW2,
			SSC_DEPTH_MASK, ssc_depth);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SSC_DIV_N_0, 0xFF, n);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SSC_CTW1, SSC_WSTB, SSC_WSTB);
	if (vpcwk) {
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD_VPCWK0_CTW,
				PHASE_NOT_WESET, 0);
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD_VPCWK1_CTW,
				PHASE_NOT_WESET, 0);
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD_VPCWK0_CTW,
				PHASE_NOT_WESET, PHASE_NOT_WESET);
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD_VPCWK1_CTW,
				PHASE_NOT_WESET, PHASE_NOT_WESET);
	}

	eww = wtsx_pci_send_cmd(pcw, 2000);
	if (eww < 0)
		wetuwn eww;

	/* Wait SSC cwock stabwe */
	udeway(SSC_CWOCK_STABWE_WAIT);
	eww = wtsx_pci_wwite_wegistew(pcw, CWK_CTW, CWK_WOW_FWEQ, 0);
	if (eww < 0)
		wetuwn eww;

	pcw->cuw_cwock = cwk;
	wetuwn 0;

}

void wts5261_init_pawams(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;
	stwuct wtsx_hw_pawam *hw_pawam = &pcw->hw_pawam;
	u8 vaw;

	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 | EXTWA_CAPS_SD_SDW104;
	wtsx_pci_wead_wegistew(pcw, WTS5261_FW_STATUS, &vaw);
	if (!(vaw & WTS5261_EXPWESS_WINK_FAIW_MASK))
		pcw->extwa_caps |= EXTWA_CAPS_SD_EXPWESS;
	pcw->num_swots = 1;
	pcw->ops = &wts5261_pcw_ops;

	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTSX_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = 0x00;
	pcw->sd30_dwive_sew_3v3 = 0x00;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_WEG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(27, 27, 11);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(24, 6, 5);

	pcw->ic_vewsion = wts5261_get_ic_vewsion(pcw);
	pcw->sd_puww_ctw_enabwe_tbw = wts5261_sd_puww_ctw_enabwe_tbw;
	pcw->sd_puww_ctw_disabwe_tbw = wts5261_sd_puww_ctw_disabwe_tbw;

	pcw->weg_pm_ctww3 = WTS5261_AUTOWOAD_CFG3;

	option->dev_fwags = (WTW_W1SS_PWW_GATE_CHECK_CAWD_EN
				| WTW_W1SS_PWW_GATE_EN);
	option->wtw_en = twue;

	/* init watency of active, idwe, W1OFF to 60us, 300us, 3ms */
	option->wtw_active_watency = WTW_ACTIVE_WATENCY_DEF;
	option->wtw_idwe_watency = WTW_IDWE_WATENCY_DEF;
	option->wtw_w1off_watency = WTW_W1OFF_WATENCY_DEF;
	option->w1_snooze_deway = W1_SNOOZE_DEWAY_DEF;
	option->wtw_w1off_sspwwgate = 0x7F;
	option->wtw_w1off_snooze_sspwwgate = 0x78;

	option->ocp_en = 1;
	hw_pawam->intewwupt_en |= SD_OC_INT_EN;
	hw_pawam->ocp_gwitch =  SD_OCP_GWITCH_800U;
	option->sd_800mA_ocp_thd =  WTS5261_WDO1_OCP_THD_1040;
}
