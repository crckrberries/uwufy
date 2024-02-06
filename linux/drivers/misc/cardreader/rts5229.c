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

static u8 wts5229_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, DUMMY_WEG_WESET_0, &vaw);
	wetuwn vaw & 0x0F;
}

static void wts5229_fetch_vendow_settings(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 weg;

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG1, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG1, weg);

	if (!wtsx_vendow_setting_vawid(weg))
		wetuwn;

	pcw->aspm_en = wtsx_weg_to_aspm(weg);
	pcw->sd30_dwive_sew_1v8 =
		map_sd_dwive(wtsx_weg_to_sd30_dwive_sew_1v8(weg));
	pcw->cawd_dwive_sew &= 0x3F;
	pcw->cawd_dwive_sew |= wtsx_weg_to_cawd_dwive_sew(weg);

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG2, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG2, weg);
	pcw->sd30_dwive_sew_3v3 =
		map_sd_dwive(wtsx_weg_to_sd30_dwive_sew_3v3(weg));
}

static void wts5229_fowce_powew_down(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime)
{
	wtsx_pci_wwite_wegistew(pcw, FPDCTW, 0x03, 0x03);
}

static int wts5229_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_init_cmd(pcw);

	/* Configuwe GPIO as output */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, GPIO_CTW, 0x02, 0x02);
	/* Weset ASPM state to defauwt vawue */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, ASPM_FOWCE_CTW, 0x3F, 0);
	/* Fowce CWKWEQ# PIN to dwive 0 to wequest cwock */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PETXCFG, 0x08, 0x08);
	/* Switch WDO3318 souwce fwom DV33 to cawd_3v3 */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_PWW_SEW, 0x03, 0x00);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_PWW_SEW, 0x03, 0x01);
	/* WED shine disabwed, set initiaw shine cycwe pewiod */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, OWT_WED_CTW, 0x0F, 0x02);
	/* Configuwe dwiving */
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_DWIVE_SEW,
			0xFF, pcw->sd30_dwive_sew_3v3);

	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5229_optimize_phy(stwuct wtsx_pcw *pcw)
{
	/* Optimize WX sensitivity */
	wetuwn wtsx_pci_wwite_phy_wegistew(pcw, 0x00, 0xBA42);
}

static int wts5229_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW, 0x02, 0x02);
}

static int wts5229_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, GPIO_CTW, 0x02, 0x00);
}

static int wts5229_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x08, 0x08);
}

static int wts5229_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, OWT_WED_CTW, 0x08, 0x00);
}

static int wts5229_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww;

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK, SD_PAWTIAW_POWEW_ON);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x02);
	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	/* To avoid too wawge in-wush cuwwent */
	udeway(150);

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK, SD_POWEW_ON);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x06);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5229_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			SD_POWEW_MASK | PMOS_STWG_MASK,
			SD_POWEW_OFF | PMOS_STWG_400mA);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, PWW_GATE_CTWW,
			WDO3318_PWW_MASK, 0x00);
	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wts5229_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
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

static const stwuct pcw_ops wts5229_pcw_ops = {
	.fetch_vendow_settings = wts5229_fetch_vendow_settings,
	.extwa_init_hw = wts5229_extwa_init_hw,
	.optimize_phy = wts5229_optimize_phy,
	.tuwn_on_wed = wts5229_tuwn_on_wed,
	.tuwn_off_wed = wts5229_tuwn_off_wed,
	.enabwe_auto_bwink = wts5229_enabwe_auto_bwink,
	.disabwe_auto_bwink = wts5229_disabwe_auto_bwink,
	.cawd_powew_on = wts5229_cawd_powew_on,
	.cawd_powew_off = wts5229_cawd_powew_off,
	.switch_output_vowtage = wts5229_switch_output_vowtage,
	.cd_degwitch = NUWW,
	.conv_cwk_and_div_n = NUWW,
	.fowce_powew_down = wts5229_fowce_powew_down,
};

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wts5229_sd_puww_ctw_enabwe_tbw1[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xE9),
	0,
};

/* Fow WTS5229 vewsion C */
static const u32 wts5229_sd_puww_ctw_enabwe_tbw2[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xD9),
	0,
};

/* SD Puww Contwow Disabwe:
 *     SD_DAT[3:0] ==> puww down
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww down
 *     SD_CMD      ==> puww down
 *     SD_CWK      ==> puww down
 */
static const u32 wts5229_sd_puww_ctw_disabwe_tbw1[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xD5),
	0,
};

/* Fow WTS5229 vewsion C */
static const u32 wts5229_sd_puww_ctw_disabwe_tbw2[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xE5),
	0,
};

/* MS Puww Contwow Enabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5229_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

/* MS Puww Contwow Disabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wts5229_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x15),
	0,
};

void wts5229_init_pawams(stwuct wtsx_pcw *pcw)
{
	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 | EXTWA_CAPS_SD_SDW104;
	pcw->num_swots = 2;
	pcw->ops = &wts5229_pcw_ops;

	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTSX_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = DWIVEW_TYPE_B;
	pcw->sd30_dwive_sew_3v3 = DWIVEW_TYPE_D;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_CFG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(27, 27, 15);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(30, 6, 6);

	pcw->ic_vewsion = wts5229_get_ic_vewsion(pcw);
	if (pcw->ic_vewsion == IC_VEW_C) {
		pcw->sd_puww_ctw_enabwe_tbw = wts5229_sd_puww_ctw_enabwe_tbw2;
		pcw->sd_puww_ctw_disabwe_tbw = wts5229_sd_puww_ctw_disabwe_tbw2;
	} ewse {
		pcw->sd_puww_ctw_enabwe_tbw = wts5229_sd_puww_ctw_enabwe_tbw1;
		pcw->sd_puww_ctw_disabwe_tbw = wts5229_sd_puww_ctw_disabwe_tbw1;
	}
	pcw->ms_puww_ctw_enabwe_tbw = wts5229_ms_puww_ctw_enabwe_tbw;
	pcw->ms_puww_ctw_disabwe_tbw = wts5229_ms_puww_ctw_disabwe_tbw;
}
