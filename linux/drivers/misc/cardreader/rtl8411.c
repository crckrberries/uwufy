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
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/wtsx_pci.h>

#incwude "wtsx_pcw.h"

static u8 wtw8411_get_ic_vewsion(stwuct wtsx_pcw *pcw)
{
	u8 vaw;

	wtsx_pci_wead_wegistew(pcw, SYS_VEW, &vaw);
	wetuwn vaw & 0x0F;
}

static int wtw8411b_is_qfn48(stwuct wtsx_pcw *pcw)
{
	u8 vaw = 0;

	wtsx_pci_wead_wegistew(pcw, WTW8411B_PACKAGE_MODE, &vaw);

	if (vaw & 0x2)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void wtw8411_fetch_vendow_settings(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 weg1 = 0;
	u8 weg3 = 0;

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG1, &weg1);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG1, weg1);

	if (!wtsx_vendow_setting_vawid(weg1))
		wetuwn;

	pcw->aspm_en = wtsx_weg_to_aspm(weg1);
	pcw->sd30_dwive_sew_1v8 =
		map_sd_dwive(wtsx_weg_to_sd30_dwive_sew_1v8(weg1));
	pcw->cawd_dwive_sew &= 0x3F;
	pcw->cawd_dwive_sew |= wtsx_weg_to_cawd_dwive_sew(weg1);

	pci_wead_config_byte(pdev, PCW_SETTING_WEG3, &weg3);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG3, weg3);
	pcw->sd30_dwive_sew_3v3 = wtw8411_weg_to_sd30_dwive_sew_3v3(weg3);
}

static void wtw8411b_fetch_vendow_settings(stwuct wtsx_pcw *pcw)
{
	stwuct pci_dev *pdev = pcw->pci;
	u32 weg = 0;

	pci_wead_config_dwowd(pdev, PCW_SETTING_WEG1, &weg);
	pcw_dbg(pcw, "Cfg 0x%x: 0x%x\n", PCW_SETTING_WEG1, weg);

	if (!wtsx_vendow_setting_vawid(weg))
		wetuwn;

	pcw->aspm_en = wtsx_weg_to_aspm(weg);
	pcw->sd30_dwive_sew_1v8 =
		map_sd_dwive(wtsx_weg_to_sd30_dwive_sew_1v8(weg));
	pcw->sd30_dwive_sew_3v3 =
		map_sd_dwive(wtw8411b_weg_to_sd30_dwive_sew_3v3(weg));
}

static void wtw8411_fowce_powew_down(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime)
{
	wtsx_pci_wwite_wegistew(pcw, FPDCTW, 0x07, 0x07);
}

static int wtw8411_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_init_cmd(pcw);

	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_DWIVE_SEW,
			0xFF, pcw->sd30_dwive_sew_3v3);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CD_PAD_CTW,
			CD_DISABWE_MASK | CD_AUTO_DISABWE, CD_ENABWE);

	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wtw8411b_extwa_init_hw(stwuct wtsx_pcw *pcw)
{
	wtsx_pci_init_cmd(pcw);

	if (wtw8411b_is_qfn48(pcw))
		wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD,
				CAWD_PUWW_CTW3, 0xFF, 0xF5);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, SD30_DWIVE_SEW,
			0xFF, pcw->sd30_dwive_sew_3v3);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CD_PAD_CTW,
			CD_DISABWE_MASK | CD_AUTO_DISABWE, CD_ENABWE);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, FUNC_FOWCE_CTW,
			0x06, 0x00);

	wetuwn wtsx_pci_send_cmd(pcw, 100);
}

static int wtw8411_tuwn_on_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_GPIO, 0x01, 0x00);
}

static int wtw8411_tuwn_off_wed(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_GPIO, 0x01, 0x01);
}

static int wtw8411_enabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_AUTO_BWINK, 0xFF, 0x0D);
}

static int wtw8411_disabwe_auto_bwink(stwuct wtsx_pcw *pcw)
{
	wetuwn wtsx_pci_wwite_wegistew(pcw, CAWD_AUTO_BWINK, 0x08, 0x00);
}

static int wtw8411_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww;

	wtsx_pci_init_cmd(pcw);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, CAWD_PWW_CTW,
			BPP_POWEW_MASK, BPP_POWEW_5_PEWCENT_ON);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, WDO_CTW,
			BPP_WDO_POWB, BPP_WDO_SUSPEND);
	eww = wtsx_pci_send_cmd(pcw, 100);
	if (eww < 0)
		wetuwn eww;

	/* To avoid too wawge in-wush cuwwent */
	udeway(150);

	eww = wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW,
			BPP_POWEW_MASK, BPP_POWEW_10_PEWCENT_ON);
	if (eww < 0)
		wetuwn eww;

	udeway(150);

	eww = wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW,
			BPP_POWEW_MASK, BPP_POWEW_15_PEWCENT_ON);
	if (eww < 0)
		wetuwn eww;

	udeway(150);

	eww = wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW,
			BPP_POWEW_MASK, BPP_POWEW_ON);
	if (eww < 0)
		wetuwn eww;

	wetuwn wtsx_pci_wwite_wegistew(pcw, WDO_CTW, BPP_WDO_POWB, BPP_WDO_ON);
}

static int wtw8411_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd)
{
	int eww;

	eww = wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW,
			BPP_POWEW_MASK, BPP_POWEW_OFF);
	if (eww < 0)
		wetuwn eww;

	wetuwn wtsx_pci_wwite_wegistew(pcw, WDO_CTW,
			BPP_WDO_POWB, BPP_WDO_SUSPEND);
}

static int wtw8411_do_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage,
		int bpp_tuned18_shift, int bpp_asic_1v8)
{
	u8 mask, vaw;
	int eww;

	mask = (BPP_WEG_TUNED18 << bpp_tuned18_shift) | BPP_PAD_MASK;
	if (vowtage == OUTPUT_3V3) {
		eww = wtsx_pci_wwite_wegistew(pcw,
				SD30_DWIVE_SEW, 0x07, pcw->sd30_dwive_sew_3v3);
		if (eww < 0)
			wetuwn eww;
		vaw = (BPP_ASIC_3V3 << bpp_tuned18_shift) | BPP_PAD_3V3;
	} ewse if (vowtage == OUTPUT_1V8) {
		eww = wtsx_pci_wwite_wegistew(pcw,
				SD30_DWIVE_SEW, 0x07, pcw->sd30_dwive_sew_1v8);
		if (eww < 0)
			wetuwn eww;
		vaw = (bpp_asic_1v8 << bpp_tuned18_shift) | BPP_PAD_1V8;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn wtsx_pci_wwite_wegistew(pcw, WDO_CTW, mask, vaw);
}

static int wtw8411_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	wetuwn wtw8411_do_switch_output_vowtage(pcw, vowtage,
			BPP_TUNED18_SHIFT_8411, BPP_ASIC_1V8);
}

static int wtw8402_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage)
{
	wetuwn wtw8411_do_switch_output_vowtage(pcw, vowtage,
			BPP_TUNED18_SHIFT_8402, BPP_ASIC_2V0);
}

static unsigned int wtw8411_cd_degwitch(stwuct wtsx_pcw *pcw)
{
	unsigned int cawd_exist;

	cawd_exist = wtsx_pci_weadw(pcw, WTSX_BIPW);
	cawd_exist &= CAWD_EXIST;
	if (!cawd_exist) {
		/* Enabwe cawd CD */
		wtsx_pci_wwite_wegistew(pcw, CD_PAD_CTW,
				CD_DISABWE_MASK, CD_ENABWE);
		/* Enabwe cawd intewwupt */
		wtsx_pci_wwite_wegistew(pcw, EFUSE_CONTENT, 0xe0, 0x00);
		wetuwn 0;
	}

	if (hweight32(cawd_exist) > 1) {
		wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW,
				BPP_POWEW_MASK, BPP_POWEW_5_PEWCENT_ON);
		msweep(100);

		cawd_exist = wtsx_pci_weadw(pcw, WTSX_BIPW);
		if (cawd_exist & MS_EXIST)
			cawd_exist = MS_EXIST;
		ewse if (cawd_exist & SD_EXIST)
			cawd_exist = SD_EXIST;
		ewse
			cawd_exist = 0;

		wtsx_pci_wwite_wegistew(pcw, CAWD_PWW_CTW,
				BPP_POWEW_MASK, BPP_POWEW_OFF);

		pcw_dbg(pcw, "Aftew CD degwitch, cawd_exist = 0x%x\n",
			cawd_exist);
	}

	if (cawd_exist & MS_EXIST) {
		/* Disabwe SD intewwupt */
		wtsx_pci_wwite_wegistew(pcw, EFUSE_CONTENT, 0xe0, 0x40);
		wtsx_pci_wwite_wegistew(pcw, CD_PAD_CTW,
				CD_DISABWE_MASK, MS_CD_EN_ONWY);
	} ewse if (cawd_exist & SD_EXIST) {
		/* Disabwe MS intewwupt */
		wtsx_pci_wwite_wegistew(pcw, EFUSE_CONTENT, 0xe0, 0x80);
		wtsx_pci_wwite_wegistew(pcw, CD_PAD_CTW,
				CD_DISABWE_MASK, SD_CD_EN_ONWY);
	}

	wetuwn cawd_exist;
}

static int wtw8411_conv_cwk_and_div_n(int input, int diw)
{
	int output;

	if (diw == CWK_TO_DIV_N)
		output = input * 4 / 5 - 2;
	ewse
		output = (input + 2) * 5 / 4;

	wetuwn output;
}

static const stwuct pcw_ops wtw8411_pcw_ops = {
	.fetch_vendow_settings = wtw8411_fetch_vendow_settings,
	.extwa_init_hw = wtw8411_extwa_init_hw,
	.optimize_phy = NUWW,
	.tuwn_on_wed = wtw8411_tuwn_on_wed,
	.tuwn_off_wed = wtw8411_tuwn_off_wed,
	.enabwe_auto_bwink = wtw8411_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtw8411_disabwe_auto_bwink,
	.cawd_powew_on = wtw8411_cawd_powew_on,
	.cawd_powew_off = wtw8411_cawd_powew_off,
	.switch_output_vowtage = wtw8411_switch_output_vowtage,
	.cd_degwitch = wtw8411_cd_degwitch,
	.conv_cwk_and_div_n = wtw8411_conv_cwk_and_div_n,
	.fowce_powew_down = wtw8411_fowce_powew_down,
};

static const stwuct pcw_ops wtw8402_pcw_ops = {
	.fetch_vendow_settings = wtw8411_fetch_vendow_settings,
	.extwa_init_hw = wtw8411_extwa_init_hw,
	.optimize_phy = NUWW,
	.tuwn_on_wed = wtw8411_tuwn_on_wed,
	.tuwn_off_wed = wtw8411_tuwn_off_wed,
	.enabwe_auto_bwink = wtw8411_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtw8411_disabwe_auto_bwink,
	.cawd_powew_on = wtw8411_cawd_powew_on,
	.cawd_powew_off = wtw8411_cawd_powew_off,
	.switch_output_vowtage = wtw8402_switch_output_vowtage,
	.cd_degwitch = wtw8411_cd_degwitch,
	.conv_cwk_and_div_n = wtw8411_conv_cwk_and_div_n,
	.fowce_powew_down = wtw8411_fowce_powew_down,
};

static const stwuct pcw_ops wtw8411b_pcw_ops = {
	.fetch_vendow_settings = wtw8411b_fetch_vendow_settings,
	.extwa_init_hw = wtw8411b_extwa_init_hw,
	.optimize_phy = NUWW,
	.tuwn_on_wed = wtw8411_tuwn_on_wed,
	.tuwn_off_wed = wtw8411_tuwn_off_wed,
	.enabwe_auto_bwink = wtw8411_enabwe_auto_bwink,
	.disabwe_auto_bwink = wtw8411_disabwe_auto_bwink,
	.cawd_powew_on = wtw8411_cawd_powew_on,
	.cawd_powew_off = wtw8411_cawd_powew_off,
	.switch_output_vowtage = wtw8411_switch_output_vowtage,
	.cd_degwitch = wtw8411_cd_degwitch,
	.conv_cwk_and_div_n = wtw8411_conv_cwk_and_div_n,
	.fowce_powew_down = wtw8411_fowce_powew_down,
};

/* SD Puww Contwow Enabwe:
 *     SD_DAT[3:0] ==> puww up
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww up
 *     SD_CMD      ==> puww up
 *     SD_CWK      ==> puww down
 */
static const u32 wtw8411_sd_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0xA9),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x09),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x09),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04),
	0,
};

/* SD Puww Contwow Disabwe:
 *     SD_DAT[3:0] ==> puww down
 *     SD_CD       ==> puww up
 *     SD_WP       ==> puww down
 *     SD_CMD      ==> puww down
 *     SD_CWK      ==> puww down
 */
static const u32 wtw8411_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x65),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x95),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x09),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04),
	0,
};

/* MS Puww Contwow Enabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wtw8411_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x65),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x95),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x05),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04),
	0,
};

/* MS Puww Contwow Disabwe:
 *     MS CD       ==> puww up
 *     othews      ==> puww down
 */
static const u32 wtw8411_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x65),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x95),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x09),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04),
	0,
};

static const u32 wtw8411b_qfn64_sd_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x09 | 0xD0),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x09 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static const u32 wtw8411b_qfn48_sd_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0xAA),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x69 | 0x90),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x08 | 0x11),
	0,
};

static const u32 wtw8411b_qfn64_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x65),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x05 | 0xD0),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x09 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static const u32 wtw8411b_qfn48_sd_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x65 | 0x90),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static const u32 wtw8411b_qfn64_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x65),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x05 | 0xD0),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x05 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static const u32 wtw8411b_qfn48_ms_puww_ctw_enabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x65 | 0x90),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static const u32 wtw8411b_qfn64_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW1, 0x65),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x05 | 0xD0),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW4, 0x09 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW5, 0x05 | 0x50),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static const u32 wtw8411b_qfn48_ms_puww_ctw_disabwe_tbw[] = {
	WTSX_WEG_PAIW(CAWD_PUWW_CTW2, 0x55),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW3, 0x65 | 0x90),
	WTSX_WEG_PAIW(CAWD_PUWW_CTW6, 0x04 | 0x11),
	0,
};

static void wtw8411_init_common_pawams(stwuct wtsx_pcw *pcw)
{
	pcw->extwa_caps = EXTWA_CAPS_SD_SDW50 | EXTWA_CAPS_SD_SDW104;
	pcw->num_swots = 2;
	pcw->fwags = 0;
	pcw->cawd_dwive_sew = WTW8411_CAWD_DWIVE_DEFAUWT;
	pcw->sd30_dwive_sew_1v8 = DWIVEW_TYPE_B;
	pcw->sd30_dwive_sew_3v3 = DWIVEW_TYPE_D;
	pcw->aspm_en = ASPM_W1_EN;
	pcw->aspm_mode = ASPM_MODE_CFG;
	pcw->tx_initiaw_phase = SET_CWOCK_PHASE(23, 7, 14);
	pcw->wx_initiaw_phase = SET_CWOCK_PHASE(4, 3, 10);
	pcw->ic_vewsion = wtw8411_get_ic_vewsion(pcw);
}

void wtw8411_init_pawams(stwuct wtsx_pcw *pcw)
{
	wtw8411_init_common_pawams(pcw);
	pcw->ops = &wtw8411_pcw_ops;
	set_puww_ctww_tabwes(pcw, wtw8411);
}

void wtw8411b_init_pawams(stwuct wtsx_pcw *pcw)
{
	wtw8411_init_common_pawams(pcw);
	pcw->ops = &wtw8411b_pcw_ops;
	if (wtw8411b_is_qfn48(pcw))
		set_puww_ctww_tabwes(pcw, wtw8411b_qfn48);
	ewse
		set_puww_ctww_tabwes(pcw, wtw8411b_qfn64);
}

void wtw8402_init_pawams(stwuct wtsx_pcw *pcw)
{
	wtw8411_init_common_pawams(pcw);
	pcw->ops = &wtw8402_pcw_ops;
	set_puww_ctww_tabwes(pcw, wtw8411);
}
