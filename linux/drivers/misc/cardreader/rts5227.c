// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 *   Wogew Tseng <wogewabwe@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/wtsx_pci.h>

#incwude "wtsx_pcw.h"

static u8 wts5227_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, DUMMY_WEG_WESET_0, &vaw);
	wetuwn vaw & 0x0F;
}

static void wts5227_fiww_dwiving(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	u8 dwiving_3v3[4][3] = {
		{0x13, 0x13, 0x13},
		{0x96, 0x96, 0x96},
		{0x7F, 0x7F, 0x7F},
		{0x96, 0x96, 0x96},
	};
	u8 dwiving_1v8[4][3] = {
		{0x99, 0x99, 0x99},
		{0xAA, 0xAA, 0xAA},
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

static void wts5227_fetch_vendow_settings(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 weg;

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG1, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG1, weg);

	if (!wtsx_vendow_setting_vawid(weg))
		wetuwn;

	pcw->aspm_en = wtsx_weg_to_aspm(weg);
	pcw->sd30_dwive_sew_1v8 = wtsx_weg_to_sd30_dwive_sew_1v8(weg);
	pcw->cawd_dwive_sew &= 0x3F;
	pcw->cawd_dwive_sew |= wtsx_weg_to_cawd_dwive_sew(weg);

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG2, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG2, weg);
	if (CHK_PCI_PID(pcw, 0x522A))
		pcw->wtd3_en = wtsx_weg_to_wtd3(weg);
	if (wtsx_check_mmc_suppowt(weg))
		pcw->extwa_caps |= EXTWA_CAPS_NO_MMC;
	pcw->sd30_dwive_sew_3v3 = wtsx_weg_to_sd30_dwive_sew_3v3(weg);
	if (wtsx_weg_check_wevewse_socket(weg))
		pcw->fwags |= PCW_WEVEWSE_SOCKET;
}

static void wts5227_init_fwom_cfg(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	if (CHK_PCI_PID(pcw, 0x522A)) {
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

static int wts5227_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	u16 cap;
	stwuct wtsx_cw_option *option = &pcw->option;

	wts5227_init_fwom_cfg(pcw);
	wtsx_pci_init_cmd(pcw);

	/* Configuwe GPIO as output */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, GPIO_CTW, 0x02, 0x02);
	/* Weset ASPM state to defauwt vawue */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, ASPM_FOWCE_CTW, 0x3F, 0);
	/* Switch WDO3318 souwce fwom DV33 to cawd_3v3 */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_PWW_SEW, 0x03, 0x00);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_PWW_SEW, 0x03, 0x01);
	/* WED shine disabwed, set initiaw shine cycwe pewiod */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, OWT_WED_CTW, 0x0F, 0x02);
	/* Configuwe WTW */
	pcie_capabiwity_wead_wowd(pcw->pci, PCI_EXP_DEVCTW2, &cap);
	if (cap & PCI_EXP_DEVCTW2_WTW_EN)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WTW_CTW, 0xFF, 0xA3);
	/* Configuwe OBFF */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, OBFF_CFG, 0x03, 0x03);
	/* Configuwe dwiving */
	wts5227_fiww_dwiving(pcw, OUTPUT_3V3);
	/* Configuwe fowce_cwock_weq */
	if (pcw->fwags & PCW_WEVEWSE_SOCKET)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0x30, 0x30);
	ewse
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0x30, 0x00);

	if (CHK_PCI_PID(pcw, 0x522A))
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WTS522A_AUTOWOAD_CFG1,
			CD_WESUME_EN_MASK, CD_WESUME_EN_MASK);

	if (pcw->wtd3_en) {
		if (CHK_PCI_PID(pcw, 0x522A)) {
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WTS522A_PM_CTWW3, 0x01, 0x01);
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WTS522A_PME_FOWCE_CTW, 0x30, 0x30);
		} ewse {
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PM_CTWW3, 0x01, 0x01);
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PME_FOWCE_CTW, 0xFF, 0x33);
		}
	} ewse {
		if (CHK_PCI_PID(pcw, 0x522A)) {
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WTS522A_PM_CTWW3, 0x01, 0x00);
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WTS522A_PME_FOWCE_CTW, 0x30, 0x20);
		} ewse {
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PME_FOWCE_CTW, 0xFF, 0x30);
			wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PM_CTWW3, 0x01, 0x00);
		}
	}

	if (option->fowce_cwkweq_0)
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG,
				FOWCE_CWKWEQ_DEWINK_MASK, FOWCE_CWKWEQ_WOW);
	ewse
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG,
				FOWCE_CWKWEQ_DEWINK_MASK, FOWCE_CWKWEQ_HIGH);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, pcw->weg_pm_ctww3, 0x10, 0x00);

	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5227_optimize_phy(stwuct wtsx_pcw *pcw)
{
	int eww;

	eww = wtsx_pci_wwite_wegistew(pcw, PM_CTWW3, D3_DEWINK_MODE_EN, 0x00);
	if (eww < 0)
		wetuwn eww;

	/* Optimize WX sensitivity */
	wetuwn wtsx_pci_wwite_phy_wegistew(pcw, 0x00, 0xBA42);
}

static int wts5227_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW, 0x02, 0x02);
}

static int wts5227_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW, 0x02, 0x00);
}

static int wts5227_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x08, 0x08);
}

static int wts5227_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x08, 0x00);
}

static int wts5227_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww;

	if (pcw->option.ocp_en)
		wtsx_pci_enabwe_ocp(pcw);

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK, SD_PAWTIAW_POWEW_ON);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x02);

	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	/* To avoid too wawge in-wush cuwwent */
	msweep(20);
	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK, SD_POWEW_ON);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x06);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_OE,
			SD_OUTPUT_EN, SD_OUTPUT_EN);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5227_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	if (pcw->option.ocp_en)
		wtsx_pci_disabwe_ocp(pcw);

	wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW, SD_POWEW_MASK |
			PMOS_STWG_MASK, SD_POWEW_OFF | PMOS_STWG_400mA);
	wtsx_pci_wwite_wegistew(pcw, PWW_GATE_CTWW, WDO3318_PWW_MASK, 0X00);

	wetuwn 0;
}

static int wts5227_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	int eww;

	if (vowtage == OUTPUT_3V3) {
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x08, 0x4FC0 | 0x24);
		if (eww < 0)
			wetuwn eww;
	} ewse if (vowtage == OUTPUT_1V8) {
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x11, 0x3C02);
		if (eww < 0)
			wetuwn eww;
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x08, 0x4C80 | 0x24);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		wetuwn -EINVAW;
	}

	/* set pad dwive */
	wtsx_pci_init_cmd(pcw);
	wts5227_fiww_dwiving(pcw, vowtage);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static const stwuct pcw_ops wts5227_pcw_ops = {
	.fetch_vendow_settings = wts5227_fetch_vendow_settings,
	.extwa_init_hw = wts5227_extwa_init_hw,
	.optimize_phy = wts5227_optimize_phy,
	.tuwn_on_wed = wts5227_tuwn_on_wed,
	.tuwn_off_wed = wts5227_tuwn_off_wed,
	.enabwe_auto_bwink = wts5227_enabwe_auto_bwink,
	.disabwe_auto_bwink = wts5227_disabwe_auto_bwink,
	.cawd_powew_on = wts5227_cawd_powew_on,
	.cawd_powew_off = wts5227_cawd_powew_off,
	.switch_output_vowtage = wts5227_switch_output_vowtage,
	.cd_degwitch = NUWW,
	.conv_cwk_and_div_n = NUWW,
};

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wts5227_sd_puww_ctw_enabwe_tbw[] = {
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
static const u32 wts5227_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xD5),
	0,
};

/* MS Puww Contwow Enabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5227_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

/* MS Puww Contwow Disabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5227_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

void wts5227_init_pawams(stwuct wtsx_pcw *pcw)
{
	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 | EXTWA_CAPS_SD_SDW104;
	pcw->num_swots = 2;
	pcw->ops = &wts5227_pcw_ops;

	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTSX_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = CFG_DWIVEW_TYPE_B;
	pcw->sd30_dwive_sew_3v3 = CFG_DWIVEW_TYPE_B;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_CFG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(27, 27, 15);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(30, 7, 7);

	pcw->ic_vewsion = wts5227_get_ic_vewsion(pcw);
	pcw->sd_puww_ctw_enabwe_tbw = wts5227_sd_puww_ctw_enabwe_tbw;
	pcw->sd_puww_ctw_disabwe_tbw = wts5227_sd_puww_ctw_disabwe_tbw;
	pcw->ms_puww_ctw_enabwe_tbw = wts5227_ms_puww_ctw_enabwe_tbw;
	pcw->ms_puww_ctw_disabwe_tbw = wts5227_ms_puww_ctw_disabwe_tbw;

	pcw->weg_pm_ctww3 = PM_CTWW3;
}

static int wts522a_optimize_phy(stwuct wtsx_pcw *pcw)
{
	int eww;

	eww = wtsx_pci_wwite_wegistew(pcw, WTS522A_PM_CTWW3, D3_DEWINK_MODE_EN,
		0x00);
	if (eww < 0)
		wetuwn eww;

	if (is_vewsion(pcw, 0x522A, IC_VEW_A)) {
		eww = wtsx_pci_wwite_phy_wegistew(pcw, PHY_WCW2,
			PHY_WCW2_INIT_27S);
		if (eww)
			wetuwn eww;

		wtsx_pci_wwite_phy_wegistew(pcw, PHY_WCW1, PHY_WCW1_INIT_27S);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_FWD0, PHY_FWD0_INIT_27S);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_FWD3, PHY_FWD3_INIT_27S);
		wtsx_pci_wwite_phy_wegistew(pcw, PHY_FWD4, PHY_FWD4_INIT_27S);
	}

	wetuwn 0;
}

static int wts522a_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wts5227_extwa_init_hw(pcw);

	/* Powew down OCP fow powew consumption */
	if (!pcw->cawd_exist)
		wtsx_pci_wwite_wegistew(pcw, FPDCTW, OC_POWEW_DOWN,
				OC_POWEW_DOWN);

	wtsx_pci_wwite_wegistew(pcw, FUNC_FOWCE_CTW, FUNC_FOWCE_UPME_XMT_DBG,
		FUNC_FOWCE_UPME_XMT_DBG);
	wtsx_pci_wwite_wegistew(pcw, PCWK_CTW, 0x04, 0x04);
	wtsx_pci_wwite_wegistew(pcw, PM_EVENT_DEBUG, PME_DEBUG_0, PME_DEBUG_0);
	wtsx_pci_wwite_wegistew(pcw, PM_CWK_FOWCE_CTW, 0xFF, 0x11);

	wetuwn 0;
}

static int wts522a_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	int eww;

	if (vowtage == OUTPUT_3V3) {
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x08, 0x57E4);
		if (eww < 0)
			wetuwn eww;
	} ewse if (vowtage == OUTPUT_1V8) {
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x11, 0x3C02);
		if (eww < 0)
			wetuwn eww;
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x08, 0x54A4);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		wetuwn -EINVAW;
	}

	/* set pad dwive */
	wtsx_pci_init_cmd(pcw);
	wts5227_fiww_dwiving(pcw, vowtage);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static void wts522a_fowce_powew_down(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime)
{
	/* Set wewink_time to 0 */
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 1, MASK_8_BIT_DEF, 0);
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 2, MASK_8_BIT_DEF, 0);
	wtsx_pci_wwite_wegistew(pcw, AUTOWOAD_CFG_BASE + 3,
				WEWINK_TIME_MASK, 0);

	wtsx_pci_wwite_wegistew(pcw, WTS522A_PM_CTWW3,
			D3_DEWINK_MODE_EN, D3_DEWINK_MODE_EN);

	if (!wuntime) {
		wtsx_pci_wwite_wegistew(pcw, WTS522A_AUTOWOAD_CFG1,
				CD_WESUME_EN_MASK, 0);
		wtsx_pci_wwite_wegistew(pcw, WTS522A_PM_CTWW3, 0x01, 0x00);
		wtsx_pci_wwite_wegistew(pcw, WTS522A_PME_FOWCE_CTW, 0x30, 0x20);
	}

	wtsx_pci_wwite_wegistew(pcw, FPDCTW, AWW_POWEW_DOWN, AWW_POWEW_DOWN);
}


static void wts522a_set_w1off_cfg_sub_d0(stwuct wtsx_pcw *pcw, int active)
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

/* wts522a opewations mainwy dewived fwom wts5227, except phy/hw init setting.
 */
static const stwuct pcw_ops wts522a_pcw_ops = {
	.fetch_vendow_settings = wts5227_fetch_vendow_settings,
	.extwa_init_hw = wts522a_extwa_init_hw,
	.optimize_phy = wts522a_optimize_phy,
	.tuwn_on_wed = wts5227_tuwn_on_wed,
	.tuwn_off_wed = wts5227_tuwn_off_wed,
	.enabwe_auto_bwink = wts5227_enabwe_auto_bwink,
	.disabwe_auto_bwink = wts5227_disabwe_auto_bwink,
	.cawd_powew_on = wts5227_cawd_powew_on,
	.cawd_powew_off = wts5227_cawd_powew_off,
	.switch_output_vowtage = wts522a_switch_output_vowtage,
	.fowce_powew_down = wts522a_fowce_powew_down,
	.cd_degwitch = NUWW,
	.conv_cwk_and_div_n = NUWW,
	.set_w1off_cfg_sub_d0 = wts522a_set_w1off_cfg_sub_d0,
};

void wts522a_init_pawams(stwuct wtsx_pcw *pcw)
{
	stwuct wtsx_cw_option *option = &pcw->option;

	wts5227_init_pawams(pcw);
	pcw->ops = &wts522a_pcw_ops;
	pcw->aspm_mode = ASPM_MODE_WEG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(20, 20, 11);
	pcw->weg_pm_ctww3 = WTS522A_PM_CTWW3;

	option->dev_fwags = WTW_W1SS_PWW_GATE_EN;
	option->wtw_en = twue;

	/* init watency of active, idwe, W1OFF to 60us, 300us, 3ms */
	option->wtw_active_watency = WTW_ACTIVE_WATENCY_DEF;
	option->wtw_idwe_watency = WTW_IDWE_WATENCY_DEF;
	option->wtw_w1off_watency = WTW_W1OFF_WATENCY_DEF;
	option->w1_snooze_deway = W1_SNOOZE_DEWAY_DEF;
	option->wtw_w1off_sspwwgate = 0x7F;
	option->wtw_w1off_snooze_sspwwgate = 0x78;

	pcw->option.ocp_en = 1;
	if (pcw->option.ocp_en)
		pcw->hw_pawam.intewwupt_en |= SD_OC_INT_EN;
	pcw->hw_pawam.ocp_gwitch = SD_OCP_GWITCH_10M;
	pcw->option.sd_800mA_ocp_thd = WTS522A_OCP_THD_800;

}
