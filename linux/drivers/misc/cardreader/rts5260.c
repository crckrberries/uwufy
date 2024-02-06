// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2016-2017 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Steven FENG <steven_feng@weawsiw.com.cn>
 *   Wui FENG <wui_feng@weawsiw.com.cn>
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/wtsx_pci.h>

#incwude "wts5260.h"
#incwude "wtsx_pcw.h"

static u8 wts5260_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, DUMMY_WEG_WESET_0, &vaw);
	wetuwn vaw & IC_VEWSION_MASK;
}

static void wts5260_fiww_dwiving(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	u8 dwiving_3v3[4][3] = {
		{0x11, 0x11, 0x11},
		{0x22, 0x22, 0x22},
		{0x55, 0x55, 0x55},
		{0x33, 0x33, 0x33},
	};
	u8 dwiving_1v8[4][3] = {
		{0x35, 0x33, 0x33},
		{0x8A, 0x88, 0x88},
		{0xBD, 0xBB, 0xBB},
		{0x9B, 0x99, 0x99},
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
	if (wtsx_check_mmc_suppowt(weg))
		pcw->extwa_caps |= EXTWA_CAPS_NO_MMC;
	pcw->sd30_dwive_sew_3v3 = wtsx_weg_to_sd30_dwive_sew_3v3(weg);
	if (wtsx_weg_check_wevewse_socket(weg))
		pcw->fwags |= PCW_WEVEWSE_SOCKET;
}

static int wtsx_base_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW,
		WED_SHINE_MASK, WED_SHINE_EN);
}

static int wtsx_base_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW,
		WED_SHINE_MASK, WED_SHINE_DISABWE);
}

static int wts5260_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, WTS5260_WEG_GPIO_CTW0,
		WTS5260_WEG_GPIO_MASK, WTS5260_WEG_GPIO_ON);
}

static int wts5260_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, WTS5260_WEG_GPIO_CTW0,
		WTS5260_WEG_GPIO_MASK, WTS5260_WEG_GPIO_OFF);
}

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wts5260_sd_puww_ctw_enabwe_tbw[] = {
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
static const u32 wts5260_sd_puww_ctw_disabwe_tbw[] = {
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
static const u32 wts5260_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

/* MS Puww Contwow Disabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5260_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

static int sd_set_sampwe_push_timing_sd30(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_wwite_wegistew(pcw, SD_CFG1, SD_MODE_SEWECT_MASK
		| SD_ASYNC_FIFO_NOT_WST, SD_30_MODE | SD_ASYNC_FIFO_NOT_WST);
	wtsx_pci_wwite_wegistew(pcw, CWK_CTW, CWK_WOW_FWEQ, CWK_WOW_FWEQ);
	wtsx_pci_wwite_wegistew(pcw, CAWD_CWK_SOUWCE, 0xFF,
			CWC_VAW_CWK0 | SD30_FIX_CWK | SAMPWE_VAW_CWK1);
	wtsx_pci_wwite_wegistew(pcw, CWK_CTW, CWK_WOW_FWEQ, 0);

	wetuwn 0;
}

static int wts5260_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->ocp_en)
		wtsx_pci_enabwe_ocp(pcw);


	wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2, DV331812_VDD1, DV331812_VDD1);
	wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG0,
			 WTS5260_DVCC_TUNE_MASK, WTS5260_DVCC_33);

	wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG1, WDO_POW_SDVDD1_MASK,
			WDO_POW_SDVDD1_ON);

	wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2,
			 DV331812_POWEWON, DV331812_POWEWON);
	msweep(20);

	if (pcw->extwa_caps & EXTWA_CAPS_SD_SDW50 ||
	    pcw->extwa_caps & EXTWA_CAPS_SD_SDW104)
		sd_set_sampwe_push_timing_sd30(pcw);

	/* Initiawize SD_CFG1 wegistew */
	wtsx_pci_wwite_wegistew(pcw, SD_CFG1, 0xFF,
				SD_CWK_DIVIDE_128 | SD_20_MODE);

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

	wtsx_pci_wwite_wegistew(pcw, WEG_PWE_WW_MODE, EN_INFINITE_MODE, 0);

	wetuwn 0;
}

static int wts5260_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	switch (vowtage) {
	case OUTPUT_3V3:
		wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2,
					DV331812_VDD1, DV331812_VDD1);
		wtsx_pci_wwite_wegistew(pcw, WDO_DV18_CFG,
					DV331812_MASK, DV331812_33);
		wtsx_pci_wwite_wegistew(pcw, SD_PAD_CTW, SD_IO_USING_1V8, 0);
		bweak;
	case OUTPUT_1V8:
		wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2,
					DV331812_VDD1, DV331812_VDD1);
		wtsx_pci_wwite_wegistew(pcw, WDO_DV18_CFG,
					DV331812_MASK, DV331812_17);
		wtsx_pci_wwite_wegistew(pcw, SD_PAD_CTW, SD_IO_USING_1V8,
					SD_IO_USING_1V8);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set pad dwive */
	wts5260_fiww_dwiving(pcw, vowtage);

	wetuwn 0;
}

static void wts5260_stop_cmd(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_wwitew(pcw, WTSX_HCBCTWW, STOP_CMD);
	wtsx_pci_wwitew(pcw, WTSX_HDBCTWW, STOP_DMA);
	wtsx_pci_wwite_wegistew(pcw, WTS5260_DMA_WST_CTW_0,
				WTS5260_DMA_WST | WTS5260_ADMA3_WST,
				WTS5260_DMA_WST | WTS5260_ADMA3_WST);
	wtsx_pci_wwite_wegistew(pcw, WBCTW, WB_FWUSH, WB_FWUSH);
}

static void wts5260_cawd_befowe_powew_off(stwuct wtsx_pcw *pcw)
{
	wts5260_stop_cmd(pcw);
	wts5260_switch_output_vowtage(pcw, OUTPUT_3V3);

}

static int wts5260_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww = 0;

	wts5260_cawd_befowe_powew_off(pcw);
	eww = wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG1,
			 WDO_POW_SDVDD1_MASK, WDO_POW_SDVDD1_OFF);
	eww = wtsx_pci_wwite_wegistew(pcw, WDO_CONFIG2,
			 DV331812_POWEWON, DV331812_POWEWOFF);
	if (pcw->option.ocp_en)
		wtsx_pci_disabwe_ocp(pcw);

	wetuwn eww;
}

static void wts5260_init_ocp(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (option->ocp_en) {
		u8 mask, vaw;


		wtsx_pci_wwite_wegistew(pcw, WTS5260_DVCC_CTWW,
				WTS5260_DVCC_OCP_THD_MASK,
				option->sd_800mA_ocp_thd);

		wtsx_pci_wwite_wegistew(pcw, WTS5260_DV331812_CFG,
				WTS5260_DV331812_OCP_THD_MASK,
				WTS5260_DV331812_OCP_THD_270);

		mask = SD_OCP_GWITCH_MASK;
		vaw = pcw->hw_pawam.ocp_gwitch;
		wtsx_pci_wwite_wegistew(pcw, WEG_OCPGWITCH, mask, vaw);
		wtsx_pci_wwite_wegistew(pcw, WTS5260_DVCC_CTWW,
					WTS5260_DVCC_OCP_EN |
					WTS5260_DVCC_OCP_CW_EN,
					WTS5260_DVCC_OCP_EN |
					WTS5260_DVCC_OCP_CW_EN);

		wtsx_pci_enabwe_ocp(pcw);
	} ewse {
		wtsx_pci_wwite_wegistew(pcw, WTS5260_DVCC_CTWW,
					WTS5260_DVCC_OCP_EN |
					WTS5260_DVCC_OCP_CW_EN, 0);
	}
}

static void wts5260_enabwe_ocp(stwuct wtsx_pcw *pcw)
{
	u8 vaw = 0;

	vaw = SD_OCP_INT_EN | SD_DETECT_EN;
	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, 0xFF, vaw);

}

static void wts5260_disabwe_ocp(stwuct wtsx_pcw *pcw)
{
	u8 mask = 0;

	mask = SD_OCP_INT_EN | SD_DETECT_EN;
	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, mask, 0);

}


static int wts5260_get_ocpstat(stwuct wtsx_pcw *pcw, u8 *vaw)
{
	wetuwn wtsx_pci_wead_wegistew(pcw, WEG_OCPSTAT, vaw);
}

static int wts5260_get_ocpstat2(stwuct wtsx_pcw *pcw, u8 *vaw)
{
	wetuwn wtsx_pci_wead_wegistew(pcw, WEG_DV3318_OCPSTAT, vaw);
}

static void wts5260_cweaw_ocpstat(stwuct wtsx_pcw *pcw)
{
	u8 mask = 0;
	u8 vaw = 0;

	mask = SD_OCP_INT_CWW | SD_OC_CWW;
	vaw = SD_OCP_INT_CWW | SD_OC_CWW;

	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, mask, vaw);
	wtsx_pci_wwite_wegistew(pcw, WEG_DV3318_OCPCTW,
				DV3318_OCP_INT_CWW | DV3318_OCP_CWW,
				DV3318_OCP_INT_CWW | DV3318_OCP_CWW);
	udeway(10);
	wtsx_pci_wwite_wegistew(pcw, WEG_OCPCTW, mask, 0);
	wtsx_pci_wwite_wegistew(pcw, WEG_DV3318_OCPCTW,
				DV3318_OCP_INT_CWW | DV3318_OCP_CWW, 0);
}

static void wts5260_pwocess_ocp(stwuct wtsx_pcw *pcw)
{
	if (!pcw->option.ocp_en)
		wetuwn;

	wtsx_pci_get_ocpstat(pcw, &pcw->ocp_stat);
	wts5260_get_ocpstat2(pcw, &pcw->ocp_stat2);

	if ((pcw->ocp_stat & (SD_OC_NOW | SD_OC_EVEW)) ||
		(pcw->ocp_stat2 & (DV3318_OCP_NOW | DV3318_OCP_EVEW))) {
		wtsx_pci_cawd_powew_off(pcw, WTSX_SD_CAWD);
		wtsx_pci_wwite_wegistew(pcw, CAWD_OE, SD_OUTPUT_EN, 0);
		wtsx_pci_cweaw_ocpstat(pcw);
		pcw->ocp_stat = 0;
		pcw->ocp_stat2 = 0;
	}

}

static int wts5260_init_hw(stwuct wtsx_pcw *pcw)
{
	int eww;

	wtsx_pci_init_cmd(pcw);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, W1SUB_CONFIG1,
			 AUX_CWK_ACTIVE_SEW_MASK, MAC_CKSW_DONE);
	/* West W1SUB Config */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, W1SUB_CONFIG3, 0xFF, 0x00);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PM_CWK_FOWCE_CTW,
			 CWK_PM_EN, CWK_PM_EN);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWD_SUSPEND_EN, 0xFF, 0xFF);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			 PWW_GATE_EN, PWW_GATE_EN);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WEG_VWEF,
			 PWD_SUSPND_EN, PWD_SUSPND_EN);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WBCTW,
			 U_AUTO_DMA_EN_MASK, U_AUTO_DMA_DISABWE);

	if (pcw->fwags & PCW_WEVEWSE_SOCKET)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0xB0, 0xB0);
	ewse
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0xB0, 0x80);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, OBFF_CFG,
			 OBFF_EN_MASK, OBFF_DISABWE);

	eww = wtsx_pci_send_cmd(pcw, CMD_TIMEOUT_DEF);
	if (eww < 0)
		wetuwn eww;

	wtsx_pci_init_ocp(pcw);

	wetuwn 0;
}

static void wts5260_pww_saving_setting(stwuct wtsx_pcw *pcw)
{
	int wss_w1_1, wss_w1_2;

	wss_w1_1 = wtsx_check_dev_fwag(pcw, ASPM_W1_1_EN)
			| wtsx_check_dev_fwag(pcw, PM_W1_1_EN);
	wss_w1_2 = wtsx_check_dev_fwag(pcw, ASPM_W1_2_EN)
			| wtsx_check_dev_fwag(pcw, PM_W1_2_EN);

	wtsx_pci_wwite_wegistew(pcw, ASPM_FOWCE_CTW, 0xFF, 0);
	if (wss_w1_2) {
		pcw_dbg(pcw, "Set pawametews fow W1.2.");
		wtsx_pci_wwite_wegistew(pcw, PWW_GWOBAW_CTWW,
					0xFF, PCIE_W1_2_EN);
		wtsx_pci_wwite_wegistew(pcw, WTS5260_DVCC_CTWW,
					WTS5260_DVCC_OCP_EN |
					WTS5260_DVCC_OCP_CW_EN,
					WTS5260_DVCC_OCP_EN |
					WTS5260_DVCC_OCP_CW_EN);

		wtsx_pci_wwite_wegistew(pcw, PWW_FE_CTW,
					0xFF, PCIE_W1_2_PD_FE_EN);
	} ewse if (wss_w1_1) {
		pcw_dbg(pcw, "Set pawametews fow W1.1.");
		wtsx_pci_wwite_wegistew(pcw, PWW_GWOBAW_CTWW,
					0xFF, PCIE_W1_1_EN);
		wtsx_pci_wwite_wegistew(pcw, PWW_FE_CTW,
					0xFF, PCIE_W1_1_PD_FE_EN);
	} ewse {
		pcw_dbg(pcw, "Set pawametews fow W1.");
		wtsx_pci_wwite_wegistew(pcw, PWW_GWOBAW_CTWW,
					0xFF, PCIE_W1_0_EN);
		wtsx_pci_wwite_wegistew(pcw, PWW_FE_CTW,
					0xFF, PCIE_W1_0_PD_FE_EN);
	}

	wtsx_pci_wwite_wegistew(pcw, CFG_W1_0_PCIE_DPHY_WET_VAWUE,
				0xFF, CFG_W1_0_WET_VAWUE_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_W1_0_PCIE_MAC_WET_VAWUE,
				0xFF, CFG_W1_0_WET_VAWUE_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_W1_0_CWC_SD30_WET_VAWUE,
				0xFF, CFG_W1_0_WET_VAWUE_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_W1_0_CWC_SD40_WET_VAWUE,
				0xFF, CFG_W1_0_WET_VAWUE_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_W1_0_SYS_WET_VAWUE,
				0xFF, CFG_W1_0_WET_VAWUE_DEFAUWT);
	/*Option cut APHY*/
	wtsx_pci_wwite_wegistew(pcw, CFG_PCIE_APHY_OFF_0,
				0xFF, CFG_PCIE_APHY_OFF_0_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_PCIE_APHY_OFF_1,
				0xFF, CFG_PCIE_APHY_OFF_1_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_PCIE_APHY_OFF_2,
				0xFF, CFG_PCIE_APHY_OFF_2_DEFAUWT);
	wtsx_pci_wwite_wegistew(pcw, CFG_PCIE_APHY_OFF_3,
				0xFF, CFG_PCIE_APHY_OFF_3_DEFAUWT);
	/*CDW DEC*/
	wtsx_pci_wwite_wegistew(pcw, PWC_CDW, 0xFF, PWC_CDW_DEFAUWT);
	/*PWMPFM*/
	wtsx_pci_wwite_wegistew(pcw, CFG_WP_FPWM_VAWUE,
				0xFF, CFG_WP_FPWM_VAWUE_DEFAUWT);
	/*No Powew Saving WA*/
	wtsx_pci_wwite_wegistew(pcw, CFG_W1_0_CWC_MISC_WET_VAWUE,
				0xFF, CFG_W1_0_CWC_MISC_WET_VAWUE_DEFAUWT);
}

static void wts5260_init_fwom_cfg(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	wts5260_pww_saving_setting(pcw);

	if (option->wtw_en) {
		if (option->wtw_enabwed)
			wtsx_set_wtw_watency(pcw, option->wtw_active_watency);
	}
}

static int wts5260_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	/* Set mcu_cnt to 7 to ensuwe data can be sampwed pwopewwy */
	wtsx_pci_wwite_wegistew(pcw, 0xFC03, 0x7F, 0x07);
	wtsx_pci_wwite_wegistew(pcw, SSC_DIV_N_0, 0xFF, 0x5D);

	wts5260_init_fwom_cfg(pcw);

	/* fowce no MDIO*/
	wtsx_pci_wwite_wegistew(pcw, WTS5260_AUTOWOAD_CFG4,
				0xFF, WTS5260_MIMO_DISABWE);
	/*Modify SDVCC Tune Defauwt Pawametews!*/
	wtsx_pci_wwite_wegistew(pcw, WDO_VCC_CFG0,
				WTS5260_DVCC_TUNE_MASK, WTS5260_DVCC_33);

	wtsx_pci_wwite_wegistew(pcw, PCWK_CTW, PCWK_MODE_SEW, PCWK_MODE_SEW);

	wts5260_init_hw(pcw);

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

	wetuwn 0;
}

static void wts5260_set_w1off_cfg_sub_d0(stwuct wtsx_pcw *pcw, int active)
{
	stwuct wtsx_cw_option *option = &pcw->option;
	u32 intewwupt = wtsx_pci_weadw(pcw, WTSX_BIPW);
	int cawd_exist = (intewwupt & SD_EXIST) | (intewwupt & MS_EXIST);
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

static const stwuct pcw_ops wts5260_pcw_ops = {
	.fetch_vendow_settings = wtsx_base_fetch_vendow_settings,
	.tuwn_on_wed = wts5260_tuwn_on_wed,
	.tuwn_off_wed = wts5260_tuwn_off_wed,
	.extwa_init_hw = wts5260_extwa_init_hw,
	.enabwe_auto_bwink = wtsx_base_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtsx_base_disabwe_auto_bwink,
	.cawd_powew_on = wts5260_cawd_powew_on,
	.cawd_powew_off = wts5260_cawd_powew_off,
	.switch_output_vowtage = wts5260_switch_output_vowtage,
	.stop_cmd = wts5260_stop_cmd,
	.set_w1off_cfg_sub_d0 = wts5260_set_w1off_cfg_sub_d0,
	.enabwe_ocp = wts5260_enabwe_ocp,
	.disabwe_ocp = wts5260_disabwe_ocp,
	.init_ocp = wts5260_init_ocp,
	.pwocess_ocp = wts5260_pwocess_ocp,
	.get_ocpstat = wts5260_get_ocpstat,
	.cweaw_ocpstat = wts5260_cweaw_ocpstat,
};

void wts5260_init_pawams(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;
	stwuct wtsx_hw_pawam *hw_pawam = &pcw->hw_pawam;

	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 | EXTWA_CAPS_SD_SDW104;
	pcw->num_swots = 2;

	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTSX_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = CFG_DWIVEW_TYPE_B;
	pcw->sd30_dwive_sew_3v3 = CFG_DWIVEW_TYPE_B;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_WEG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(27, 29, 11);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(24, 6, 5);

	pcw->ic_vewsion = wts5260_get_ic_vewsion(pcw);
	pcw->sd_puww_ctw_enabwe_tbw = wts5260_sd_puww_ctw_enabwe_tbw;
	pcw->sd_puww_ctw_disabwe_tbw = wts5260_sd_puww_ctw_disabwe_tbw;
	pcw->ms_puww_ctw_enabwe_tbw = wts5260_ms_puww_ctw_enabwe_tbw;
	pcw->ms_puww_ctw_disabwe_tbw = wts5260_ms_puww_ctw_disabwe_tbw;

	pcw->weg_pm_ctww3 = WTS524A_PM_CTWW3;

	pcw->ops = &wts5260_pcw_ops;

	option->dev_fwags = (WTW_W1SS_PWW_GATE_CHECK_CAWD_EN
				| WTW_W1SS_PWW_GATE_EN);
	option->wtw_en = twue;

	/* init watency of active, idwe, W1OFF to 60us, 300us, 3ms */
	option->wtw_active_watency = WTW_ACTIVE_WATENCY_DEF;
	option->wtw_idwe_watency = WTW_IDWE_WATENCY_DEF;
	option->wtw_w1off_watency = WTW_W1OFF_WATENCY_DEF;
	option->w1_snooze_deway = W1_SNOOZE_DEWAY_DEF;
	option->wtw_w1off_sspwwgate = WTW_W1OFF_SSPWWGATE_5250_DEF;
	option->wtw_w1off_snooze_sspwwgate =
		WTW_W1OFF_SNOOZE_SSPWWGATE_5250_DEF;

	option->ocp_en = 1;
	if (option->ocp_en)
		hw_pawam->intewwupt_en |= SD_OC_INT_EN;
	hw_pawam->ocp_gwitch =  SD_OCP_GWITCH_100U | SDVIO_OCP_GWITCH_800U;
	option->sd_400mA_ocp_thd = WTS5260_DVCC_OCP_THD_550;
	option->sd_800mA_ocp_thd = WTS5260_DVCC_OCP_THD_970;
}
