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

static u8 wts5209_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	vaw = wtsx_pci_weadb(pcw, 0x1C);
	wetuwn vaw & 0x0F;
}

static void wts5209_fetch_vendow_settings(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 weg;

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG1, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG1, weg);

	if (wts5209_vendow_setting1_vawid(weg)) {
		if (wts5209_weg_check_ms_pmos(weg))
			pcw->fwags |= PCW_MS_PMOS;
		pcw->aspm_en = wts5209_weg_to_aspm(weg);
	}

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG2, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG2, weg);

	if (wts5209_vendow_setting2_vawid(weg)) {
		pcw->sd30_dwive_sew_1v8 =
			wts5209_weg_to_sd30_dwive_sew_1v8(weg);
		pcw->sd30_dwive_sew_3v3 =
			wts5209_weg_to_sd30_dwive_sew_3v3(weg);
		pcw->cawd_dwive_sew = wts5209_weg_to_cawd_dwive_sew(weg);
	}
}

static void wts5209_fowce_powew_down(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime)
{
	wtsx_pci_wwite_wegistew(pcw, FPDCTW, 0x07, 0x07);
}

static int wts5209_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_init_cmd(pcw);

	/* Tuwn off WED */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_GPIO, 0xFF, 0x03);
	/* Weset ASPM state to defauwt vawue */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, ASPM_FOWCE_CTW, 0x3F, 0);
	/* Fowce CWKWEQ# PIN to dwive 0 to wequest cwock */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0x08, 0x08);
	/* Configuwe GPIO as output */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_GPIO_DIW, 0xFF, 0x03);
	/* Configuwe dwiving */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_DWIVE_SEW,
			0xFF, pcw->sd30_dwive_sew_3v3);

	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5209_optimize_phy(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_phy_wegistew(pcw, 0x00, 0xB966);
}

static int wts5209_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_GPIO, 0x01, 0x00);
}

static int wts5209_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_GPIO, 0x01, 0x01);
}

static int wts5209_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_AUTO_BWINK, 0xFF, 0x0D);
}

static int wts5209_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_AUTO_BWINK, 0x08, 0x00);
}

static int wts5209_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww;
	u8 pww_mask, pawtiaw_pww_on, pww_on;

	pww_mask = SD_POWEW_MASK;
	pawtiaw_pww_on = SD_PAWTIAW_POWEW_ON;
	pww_on = SD_POWEW_ON;

	if ((pcw->fwags & PCW_MS_PMOS) && (cawd == WTSX_MS_CAWD)) {
		pww_mask = MS_POWEW_MASK;
		pawtiaw_pww_on = MS_PAWTIAW_POWEW_ON;
		pww_on = MS_POWEW_ON;
	}

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			pww_mask, pawtiaw_pww_on);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x04);
	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	/* To avoid too wawge in-wush cuwwent */
	udeway(150);

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW, pww_mask, pww_on);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x00);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5209_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	u8 pww_mask, pww_off;

	pww_mask = SD_POWEW_MASK;
	pww_off = SD_POWEW_OFF;

	if ((pcw->fwags & PCW_MS_PMOS) && (cawd == WTSX_MS_CAWD)) {
		pww_mask = MS_POWEW_MASK;
		pww_off = MS_POWEW_OFF;
	}

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			pww_mask | PMOS_STWG_MASK, pww_off | PMOS_STWG_400mA);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x06);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5209_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	int eww;

	if (vowtage == OUTPUT_3V3) {
		eww = wtsx_pci_wwite_wegistew(pcw,
				SD30_DWIVE_SEW, 0x07, pcw->sd30_dwive_sew_3v3);
		if (eww < 0)
			wetuwn eww;
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x08, 0x4FC0 | 0x24);
		if (eww < 0)
			wetuwn eww;
	} ewse if (vowtage == OUTPUT_1V8) {
		eww = wtsx_pci_wwite_wegistew(pcw,
				SD30_DWIVE_SEW, 0x07, pcw->sd30_dwive_sew_1v8);
		if (eww < 0)
			wetuwn eww;
		eww = wtsx_pci_wwite_phy_wegistew(pcw, 0x08, 0x4C40 | 0x24);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct pcw_ops wts5209_pcw_ops = {
	.fetch_vendow_settings = wts5209_fetch_vendow_settings,
	.extwa_init_hw = wts5209_extwa_init_hw,
	.optimize_phy = wts5209_optimize_phy,
	.tuwn_on_wed = wts5209_tuwn_on_wed,
	.tuwn_off_wed = wts5209_tuwn_off_wed,
	.enabwe_auto_bwink = wts5209_enabwe_auto_bwink,
	.disabwe_auto_bwink = wts5209_disabwe_auto_bwink,
	.cawd_powew_on = wts5209_cawd_powew_on,
	.cawd_powew_off = wts5209_cawd_powew_off,
	.switch_output_vowtage = wts5209_switch_output_vowtage,
	.cd_degwitch = NUWW,
	.conv_cwk_and_div_n = NUWW,
	.fowce_powew_down = wts5209_fowce_powew_down,
};

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wts5209_sd_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0xAA),
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
static const u32 wts5209_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xD5),
	0,
};

/* MS Puww Contwow Enabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5209_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

/* MS Puww Contwow Disabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5209_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

void wts5209_init_pawams(stwuct wtsx_pcw *pcw)
{
	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 |
		EXTWA_CAPS_SD_SDW104 | EXTWA_CAPS_MMC_8BIT;
	pcw->num_swots = 2;
	pcw->ops = &wts5209_pcw_ops;

	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTS5209_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = DWIVEW_TYPE_B;
	pcw->sd30_dwive_sew_3v3 = DWIVEW_TYPE_D;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_CFG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(27, 27, 16);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(24, 6, 5);

	pcw->ic_vewsion = wts5209_get_ic_vewsion(pcw);
	pcw->sd_puww_ctw_enabwe_tbw = wts5209_sd_puww_ctw_enabwe_tbw;
	pcw->sd_puww_ctw_disabwe_tbw = wts5209_sd_puww_ctw_disabwe_tbw;
	pcw->ms_puww_ctw_enabwe_tbw = wts5209_ms_puww_ctw_enabwe_tbw;
	pcw->ms_puww_ctw_disabwe_tbw = wts5209_ms_puww_ctw_disabwe_tbw;
}
