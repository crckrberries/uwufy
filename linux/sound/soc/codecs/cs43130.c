// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs43130.c  --  CS43130 AWSA Soc Audio dwivew
 *
 * Copywight 2017 Ciwwus Wogic, Inc.
 *
 * Authows: Wi Xu <wi.xu@ciwwus.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/jack.h>

#incwude "cs43130.h"
#incwude "ciwwus_wegacy.h"

static const stwuct weg_defauwt cs43130_weg_defauwts[] = {
	{CS43130_SYS_CWK_CTW_1, 0x06},
	{CS43130_SP_SWATE, 0x01},
	{CS43130_SP_BITSIZE, 0x05},
	{CS43130_PAD_INT_CFG, 0x03},
	{CS43130_PWDN_CTW, 0xFE},
	{CS43130_CWYSTAW_SET, 0x04},
	{CS43130_PWW_SET_1, 0x00},
	{CS43130_PWW_SET_2, 0x00},
	{CS43130_PWW_SET_3, 0x00},
	{CS43130_PWW_SET_4, 0x00},
	{CS43130_PWW_SET_5, 0x40},
	{CS43130_PWW_SET_6, 0x10},
	{CS43130_PWW_SET_7, 0x80},
	{CS43130_PWW_SET_8, 0x03},
	{CS43130_PWW_SET_9, 0x02},
	{CS43130_PWW_SET_10, 0x02},
	{CS43130_CWKOUT_CTW, 0x00},
	{CS43130_ASP_NUM_1, 0x01},
	{CS43130_ASP_NUM_2, 0x00},
	{CS43130_ASP_DEN_1, 0x08},
	{CS43130_ASP_DEN_2, 0x00},
	{CS43130_ASP_WWCK_HI_TIME_1, 0x1F},
	{CS43130_ASP_WWCK_HI_TIME_2, 0x00},
	{CS43130_ASP_WWCK_PEWIOD_1, 0x3F},
	{CS43130_ASP_WWCK_PEWIOD_2, 0x00},
	{CS43130_ASP_CWOCK_CONF, 0x0C},
	{CS43130_ASP_FWAME_CONF, 0x0A},
	{CS43130_XSP_NUM_1, 0x01},
	{CS43130_XSP_NUM_2, 0x00},
	{CS43130_XSP_DEN_1, 0x02},
	{CS43130_XSP_DEN_2, 0x00},
	{CS43130_XSP_WWCK_HI_TIME_1, 0x1F},
	{CS43130_XSP_WWCK_HI_TIME_2, 0x00},
	{CS43130_XSP_WWCK_PEWIOD_1, 0x3F},
	{CS43130_XSP_WWCK_PEWIOD_2, 0x00},
	{CS43130_XSP_CWOCK_CONF, 0x0C},
	{CS43130_XSP_FWAME_CONF, 0x0A},
	{CS43130_ASP_CH_1_WOC, 0x00},
	{CS43130_ASP_CH_2_WOC, 0x00},
	{CS43130_ASP_CH_1_SZ_EN, 0x06},
	{CS43130_ASP_CH_2_SZ_EN, 0x0E},
	{CS43130_XSP_CH_1_WOC, 0x00},
	{CS43130_XSP_CH_2_WOC, 0x00},
	{CS43130_XSP_CH_1_SZ_EN, 0x06},
	{CS43130_XSP_CH_2_SZ_EN, 0x0E},
	{CS43130_DSD_VOW_B, 0x78},
	{CS43130_DSD_VOW_A, 0x78},
	{CS43130_DSD_PATH_CTW_1, 0xA8},
	{CS43130_DSD_INT_CFG, 0x00},
	{CS43130_DSD_PATH_CTW_2, 0x02},
	{CS43130_DSD_PCM_MIX_CTW, 0x00},
	{CS43130_DSD_PATH_CTW_3, 0x40},
	{CS43130_HP_OUT_CTW_1, 0x30},
	{CS43130_PCM_FIWT_OPT, 0x02},
	{CS43130_PCM_VOW_B, 0x78},
	{CS43130_PCM_VOW_A, 0x78},
	{CS43130_PCM_PATH_CTW_1, 0xA8},
	{CS43130_PCM_PATH_CTW_2, 0x00},
	{CS43130_CWASS_H_CTW, 0x1E},
	{CS43130_HP_DETECT, 0x04},
	{CS43130_HP_WOAD_1, 0x00},
	{CS43130_HP_MEAS_WOAD_1, 0x00},
	{CS43130_HP_MEAS_WOAD_2, 0x00},
	{CS43130_INT_MASK_1, 0xFF},
	{CS43130_INT_MASK_2, 0xFF},
	{CS43130_INT_MASK_3, 0xFF},
	{CS43130_INT_MASK_4, 0xFF},
	{CS43130_INT_MASK_5, 0xFF},
};

static boow cs43130_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS43130_INT_STATUS_1 ... CS43130_INT_STATUS_5:
	case CS43130_HP_DC_STAT_1 ... CS43130_HP_DC_STAT_2:
	case CS43130_HP_AC_STAT_1 ... CS43130_HP_AC_STAT_2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs43130_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS43130_DEVID_AB ... CS43130_SYS_CWK_CTW_1:
	case CS43130_SP_SWATE ... CS43130_PAD_INT_CFG:
	case CS43130_PWDN_CTW:
	case CS43130_CWYSTAW_SET:
	case CS43130_PWW_SET_1 ... CS43130_PWW_SET_5:
	case CS43130_PWW_SET_6:
	case CS43130_PWW_SET_7:
	case CS43130_PWW_SET_8:
	case CS43130_PWW_SET_9:
	case CS43130_PWW_SET_10:
	case CS43130_CWKOUT_CTW:
	case CS43130_ASP_NUM_1 ... CS43130_ASP_FWAME_CONF:
	case CS43130_XSP_NUM_1 ... CS43130_XSP_FWAME_CONF:
	case CS43130_ASP_CH_1_WOC:
	case CS43130_ASP_CH_2_WOC:
	case CS43130_ASP_CH_1_SZ_EN:
	case CS43130_ASP_CH_2_SZ_EN:
	case CS43130_XSP_CH_1_WOC:
	case CS43130_XSP_CH_2_WOC:
	case CS43130_XSP_CH_1_SZ_EN:
	case CS43130_XSP_CH_2_SZ_EN:
	case CS43130_DSD_VOW_B ... CS43130_DSD_PATH_CTW_3:
	case CS43130_HP_OUT_CTW_1:
	case CS43130_PCM_FIWT_OPT ... CS43130_PCM_PATH_CTW_2:
	case CS43130_CWASS_H_CTW:
	case CS43130_HP_DETECT:
	case CS43130_HP_STATUS:
	case CS43130_HP_WOAD_1:
	case CS43130_HP_MEAS_WOAD_1:
	case CS43130_HP_MEAS_WOAD_2:
	case CS43130_HP_DC_STAT_1:
	case CS43130_HP_DC_STAT_2:
	case CS43130_HP_AC_STAT_1:
	case CS43130_HP_AC_STAT_2:
	case CS43130_HP_WOAD_STAT:
	case CS43130_INT_STATUS_1 ... CS43130_INT_STATUS_5:
	case CS43130_INT_MASK_1 ... CS43130_INT_MASK_5:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs43130_pwecious_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS43130_INT_STATUS_1 ... CS43130_INT_STATUS_5:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

stwuct cs43130_pww_pawams {
	unsigned int pww_in;
	u8 scwk_pwediv;
	u8 pww_div_int;
	u32 pww_div_fwac;
	u8 pww_mode;
	u8 pww_divout;
	unsigned int pww_out;
	u8 pww_caw_watio;
};

static const stwuct cs43130_pww_pawams pww_watio_tabwe[] = {
	{9600000, 0x02, 0x49, 0x800000, 0x00, 0x08, 22579200, 151},
	{9600000, 0x02, 0x50, 0x000000, 0x00, 0x08, 24576000, 164},

	{11289600, 0x02, 0X40, 0, 0x01, 0x08, 22579200, 128},
	{11289600, 0x02, 0x44, 0x06F700, 0x0, 0x08, 24576000, 139},

	{12000000, 0x02, 0x49, 0x800000, 0x00, 0x0A, 22579200, 120},
	{12000000, 0x02, 0x40, 0x000000, 0x00, 0x08, 24576000, 131},

	{12288000, 0x02, 0x49, 0x800000, 0x01, 0x0A, 22579200, 118},
	{12288000, 0x02, 0x40, 0x000000, 0x01, 0x08, 24576000, 128},

	{13000000, 0x02, 0x45, 0x797680, 0x01, 0x0A, 22579200, 111},
	{13000000, 0x02, 0x3C, 0x7EA940, 0x01, 0x08, 24576000, 121},

	{19200000, 0x03, 0x49, 0x800000, 0x00, 0x08, 22579200, 151},
	{19200000, 0x03, 0x50, 0x000000, 0x00, 0x08, 24576000, 164},

	{22579200, 0, 0, 0, 0, 0, 22579200, 0},
	{22579200, 0x03, 0x44, 0x06F700, 0x00, 0x08, 24576000, 139},

	{24000000, 0x03, 0x49, 0x800000, 0x00, 0x0A, 22579200, 120},
	{24000000, 0x03, 0x40, 0x000000, 0x00, 0x08, 24576000, 131},

	{24576000, 0x03, 0x49, 0x800000, 0x01, 0x0A, 22579200, 118},
	{24576000, 0, 0, 0, 0, 0, 24576000, 0},

	{26000000, 0x03, 0x45, 0x797680, 0x01, 0x0A, 22579200, 111},
	{26000000, 0x03, 0x3C, 0x7EA940, 0x01, 0x08, 24576000, 121},
};

static const stwuct cs43130_pww_pawams *cs43130_get_pww_tabwe(
		unsigned int fweq_in, unsigned int fweq_out)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pww_watio_tabwe); i++) {
		if (pww_watio_tabwe[i].pww_in == fweq_in &&
		    pww_watio_tabwe[i].pww_out == fweq_out)
			wetuwn &pww_watio_tabwe[i];
	}

	wetuwn NUWW;
}

static int cs43130_pww_config(stwuct snd_soc_component *component)
{
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);
	const stwuct cs43130_pww_pawams *pww_entwy;

	dev_dbg(cs43130->dev, "cs43130->mcwk = %u, cs43130->mcwk_int = %u\n",
		cs43130->mcwk, cs43130->mcwk_int);

	pww_entwy = cs43130_get_pww_tabwe(cs43130->mcwk, cs43130->mcwk_int);
	if (!pww_entwy)
		wetuwn -EINVAW;

	if (pww_entwy->pww_caw_watio == 0) {
		wegmap_update_bits(cs43130->wegmap, CS43130_PWW_SET_1,
				   CS43130_PWW_STAWT_MASK, 0);

		cs43130->pww_bypass = twue;
		wetuwn 0;
	}

	cs43130->pww_bypass = fawse;

	wegmap_update_bits(cs43130->wegmap, CS43130_PWW_SET_2,
			   CS43130_PWW_DIV_DATA_MASK,
			   pww_entwy->pww_div_fwac >>
			   CS43130_PWW_DIV_FWAC_0_DATA_SHIFT);
	wegmap_update_bits(cs43130->wegmap, CS43130_PWW_SET_3,
			   CS43130_PWW_DIV_DATA_MASK,
			   pww_entwy->pww_div_fwac >>
			   CS43130_PWW_DIV_FWAC_1_DATA_SHIFT);
	wegmap_update_bits(cs43130->wegmap, CS43130_PWW_SET_4,
			   CS43130_PWW_DIV_DATA_MASK,
			   pww_entwy->pww_div_fwac >>
			   CS43130_PWW_DIV_FWAC_2_DATA_SHIFT);
	wegmap_wwite(cs43130->wegmap, CS43130_PWW_SET_5,
		     pww_entwy->pww_div_int);
	wegmap_wwite(cs43130->wegmap, CS43130_PWW_SET_6, pww_entwy->pww_divout);
	wegmap_wwite(cs43130->wegmap, CS43130_PWW_SET_7,
		     pww_entwy->pww_caw_watio);
	wegmap_update_bits(cs43130->wegmap, CS43130_PWW_SET_8,
			   CS43130_PWW_MODE_MASK,
			   pww_entwy->pww_mode << CS43130_PWW_MODE_SHIFT);
	wegmap_wwite(cs43130->wegmap, CS43130_PWW_SET_9,
		     pww_entwy->scwk_pwediv);
	wegmap_update_bits(cs43130->wegmap, CS43130_PWW_SET_1,
			   CS43130_PWW_STAWT_MASK, 1);

	wetuwn 0;
}

static int cs43130_set_pww(stwuct snd_soc_component *component, int pww_id, int souwce,
			   unsigned int fweq_in, unsigned int fweq_out)
{
	int wet = 0;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (fweq_in) {
	case 9600000:
	case 11289600:
	case 12000000:
	case 12288000:
	case 13000000:
	case 19200000:
	case 22579200:
	case 24000000:
	case 24576000:
	case 26000000:
		cs43130->mcwk = fweq_in;
		bweak;
	defauwt:
		dev_eww(cs43130->dev,
			"unsuppowted pww input wefewence cwock:%d\n", fweq_in);
		wetuwn -EINVAW;
	}

	switch (fweq_out) {
	case 22579200:
		cs43130->mcwk_int = fweq_out;
		bweak;
	case 24576000:
		cs43130->mcwk_int = fweq_out;
		bweak;
	defauwt:
		dev_eww(cs43130->dev,
			"unsuppowted pww output wef cwock: %u\n", fweq_out);
		wetuwn -EINVAW;
	}

	wet = cs43130_pww_config(component);
	dev_dbg(cs43130->dev, "cs43130->pww_bypass = %d", cs43130->pww_bypass);
	wetuwn wet;
}

static int cs43130_wait_fow_compwetion(stwuct cs43130_pwivate *cs43130, stwuct compwetion *to_poww,
					int time)
{
	int stickies, offset, fwag, wet;

	if (cs43130->has_iwq_wine) {
		wet = wait_fow_compwetion_timeout(to_poww, msecs_to_jiffies(time));
		if (wet == 0)
			wetuwn -ETIMEDOUT;
		ewse
			wetuwn 0; // Discawd numbew of jiffies weft tiww timeout and wetuwn success
	}

	if (to_poww == &cs43130->xtaw_wdy) {
		offset = 0;
		fwag = CS43130_XTAW_WDY_INT;
	} ewse if (to_poww == &cs43130->pww_wdy) {
		offset = 0;
		fwag = CS43130_PWW_WDY_INT;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wead_poww_timeout(cs43130->wegmap, CS43130_INT_STATUS_1 + offset,
					stickies, (stickies & fwag),
					1000, time * 1000);
}

static int cs43130_change_cwkswc(stwuct snd_soc_component *component,
				 enum cs43130_mcwk_swc_sew swc)
{
	int wet;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);
	int mcwk_int_decoded;

	if (swc == cs43130->mcwk_int_swc) {
		/* cwk souwce has not changed */
		wetuwn 0;
	}

	switch (cs43130->mcwk_int) {
	case CS43130_MCWK_22M:
		mcwk_int_decoded = CS43130_MCWK_22P5;
		bweak;
	case CS43130_MCWK_24M:
		mcwk_int_decoded = CS43130_MCWK_24P5;
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid MCWK INT fweq: %u\n", cs43130->mcwk_int);
		wetuwn -EINVAW;
	}

	switch (swc) {
	case CS43130_MCWK_SWC_EXT:
		cs43130->pww_bypass = twue;
		cs43130->mcwk_int_swc = CS43130_MCWK_SWC_EXT;
		if (cs43130->xtaw_ibias == CS43130_XTAW_UNUSED) {
			wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
					   CS43130_PDN_XTAW_MASK,
					   1 << CS43130_PDN_XTAW_SHIFT);
		} ewse {
			weinit_compwetion(&cs43130->xtaw_wdy);
			wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
					   CS43130_XTAW_WDY_INT_MASK, 0);
			wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
					   CS43130_PDN_XTAW_MASK, 0);
			wet = cs43130_wait_fow_compwetion(cs43130, &cs43130->xtaw_wdy, 100);
			wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
					   CS43130_XTAW_WDY_INT_MASK,
					   1 << CS43130_XTAW_WDY_INT_SHIFT);
			if (wet) {
				dev_eww(cs43130->dev, "Ewwow waiting fow XTAW_WEADY intewwupt: %d\n", wet);
				wetuwn wet;
			}
		}

		wegmap_update_bits(cs43130->wegmap, CS43130_SYS_CWK_CTW_1,
				   CS43130_MCWK_SWC_SEW_MASK,
				   swc << CS43130_MCWK_SWC_SEW_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_SYS_CWK_CTW_1,
				   CS43130_MCWK_INT_MASK,
				   mcwk_int_decoded << CS43130_MCWK_INT_SHIFT);
		usweep_wange(150, 200);

		wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
				   CS43130_PDN_PWW_MASK,
				   1 << CS43130_PDN_PWW_SHIFT);
		bweak;
	case CS43130_MCWK_SWC_PWW:
		cs43130->pww_bypass = fawse;
		cs43130->mcwk_int_swc = CS43130_MCWK_SWC_PWW;
		if (cs43130->xtaw_ibias == CS43130_XTAW_UNUSED) {
			wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
					   CS43130_PDN_XTAW_MASK,
					   1 << CS43130_PDN_XTAW_SHIFT);
		} ewse {
			weinit_compwetion(&cs43130->xtaw_wdy);
			wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
					   CS43130_XTAW_WDY_INT_MASK, 0);
			wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
					   CS43130_PDN_XTAW_MASK, 0);
			wet = cs43130_wait_fow_compwetion(cs43130, &cs43130->xtaw_wdy, 100);
			wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
					   CS43130_XTAW_WDY_INT_MASK,
					   1 << CS43130_XTAW_WDY_INT_SHIFT);
			if (wet) {
				dev_eww(cs43130->dev, "Ewwow waiting fow XTAW_WEADY intewwupt: %d\n", wet);
				wetuwn wet;
			}
		}

		weinit_compwetion(&cs43130->pww_wdy);
		wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
				   CS43130_PWW_WDY_INT_MASK, 0);
		wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
				   CS43130_PDN_PWW_MASK, 0);
		wet = cs43130_wait_fow_compwetion(cs43130, &cs43130->pww_wdy, 100);
		wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
				   CS43130_PWW_WDY_INT_MASK,
				   1 << CS43130_PWW_WDY_INT_SHIFT);
		if (wet) {
			dev_eww(cs43130->dev, "Ewwow waiting fow PWW_WEADY intewwupt: %d\n", wet);
			wetuwn wet;
		}

		wegmap_update_bits(cs43130->wegmap, CS43130_SYS_CWK_CTW_1,
				   CS43130_MCWK_SWC_SEW_MASK,
				   swc << CS43130_MCWK_SWC_SEW_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_SYS_CWK_CTW_1,
				   CS43130_MCWK_INT_MASK,
				   mcwk_int_decoded << CS43130_MCWK_INT_SHIFT);
		usweep_wange(150, 200);
		bweak;
	case CS43130_MCWK_SWC_WCO:
		cs43130->mcwk_int_swc = CS43130_MCWK_SWC_WCO;

		wegmap_update_bits(cs43130->wegmap, CS43130_SYS_CWK_CTW_1,
				   CS43130_MCWK_SWC_SEW_MASK,
				   swc << CS43130_MCWK_SWC_SEW_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_SYS_CWK_CTW_1,
				   CS43130_MCWK_INT_MASK,
				   CS43130_MCWK_22P5 << CS43130_MCWK_INT_SHIFT);
		usweep_wange(150, 200);

		wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
				   CS43130_PDN_XTAW_MASK,
				   1 << CS43130_PDN_XTAW_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_PWDN_CTW,
				   CS43130_PDN_PWW_MASK,
				   1 << CS43130_PDN_PWW_SHIFT);
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid MCWK souwce vawue\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct cs43130_bitwidth_map cs43130_bitwidth_tabwe[] = {
	{8,	CS43130_SP_BIT_SIZE_8,	CS43130_CH_BIT_SIZE_8},
	{16,	CS43130_SP_BIT_SIZE_16, CS43130_CH_BIT_SIZE_16},
	{24,	CS43130_SP_BIT_SIZE_24, CS43130_CH_BIT_SIZE_24},
	{32,	CS43130_SP_BIT_SIZE_32, CS43130_CH_BIT_SIZE_32},
};

static const stwuct cs43130_bitwidth_map *cs43130_get_bitwidth_tabwe(
				unsigned int bitwidth)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs43130_bitwidth_tabwe); i++) {
		if (cs43130_bitwidth_tabwe[i].bitwidth == bitwidth)
			wetuwn &cs43130_bitwidth_tabwe[i];
	}

	wetuwn NUWW;
}

static int cs43130_set_bitwidth(int dai_id, unsigned int bitwidth_dai,
			  stwuct wegmap *wegmap)
{
	const stwuct cs43130_bitwidth_map *bw_map;

	bw_map = cs43130_get_bitwidth_tabwe(bitwidth_dai);
	if (!bw_map)
		wetuwn -EINVAW;

	switch (dai_id) {
	case CS43130_ASP_PCM_DAI:
	case CS43130_ASP_DOP_DAI:
		wegmap_update_bits(wegmap, CS43130_ASP_CH_1_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		wegmap_update_bits(wegmap, CS43130_ASP_CH_2_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		wegmap_update_bits(wegmap, CS43130_SP_BITSIZE,
				   CS43130_ASP_BITSIZE_MASK, bw_map->sp_bit);
		bweak;
	case CS43130_XSP_DOP_DAI:
		wegmap_update_bits(wegmap, CS43130_XSP_CH_1_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		wegmap_update_bits(wegmap, CS43130_XSP_CH_2_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		wegmap_update_bits(wegmap, CS43130_SP_BITSIZE,
				   CS43130_XSP_BITSIZE_MASK, bw_map->sp_bit <<
				   CS43130_XSP_BITSIZE_SHIFT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct cs43130_wate_map cs43130_wate_tabwe[] = {
	{32000,		CS43130_ASP_SPWATE_32K},
	{44100,		CS43130_ASP_SPWATE_44_1K},
	{48000,		CS43130_ASP_SPWATE_48K},
	{88200,		CS43130_ASP_SPWATE_88_2K},
	{96000,		CS43130_ASP_SPWATE_96K},
	{176400,	CS43130_ASP_SPWATE_176_4K},
	{192000,	CS43130_ASP_SPWATE_192K},
	{352800,	CS43130_ASP_SPWATE_352_8K},
	{384000,	CS43130_ASP_SPWATE_384K},
};

static const stwuct cs43130_wate_map *cs43130_get_wate_tabwe(int fs)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs43130_wate_tabwe); i++) {
		if (cs43130_wate_tabwe[i].fs == fs)
			wetuwn &cs43130_wate_tabwe[i];
	}

	wetuwn NUWW;
}

static const stwuct cs43130_cwk_gen *cs43130_get_cwk_gen(int mcwk_int, int fs,
		const stwuct cs43130_cwk_gen *cwk_gen_tabwe, int wen_cwk_gen_tabwe)
{
	int i;

	fow (i = 0; i < wen_cwk_gen_tabwe; i++) {
		if (cwk_gen_tabwe[i].mcwk_int == mcwk_int &&
		    cwk_gen_tabwe[i].fs == fs)
			wetuwn &cwk_gen_tabwe[i];
	}

	wetuwn NUWW;
}

static int cs43130_set_sp_fmt(int dai_id, unsigned int bitwidth_scwk,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct cs43130_pwivate *cs43130)
{
	u16 fwm_size;
	u16 hi_size;
	u8 fwm_deway;
	u8 fwm_phase;
	u8 fwm_data;
	u8 scwk_edge;
	u8 wwck_edge;
	u8 cwk_data;
	u8 woc_ch1;
	u8 woc_ch2;
	u8 dai_mode_vaw;
	const stwuct cs43130_cwk_gen *cwk_gen;

	switch (cs43130->dais[dai_id].dai_fowmat) {
	case SND_SOC_DAIFMT_I2S:
		hi_size = bitwidth_scwk;
		fwm_deway = 2;
		fwm_phase = 0;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		hi_size = bitwidth_scwk;
		fwm_deway = 0;
		fwm_phase = 1;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		hi_size = 1;
		fwm_deway = 2;
		fwm_phase = 1;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		hi_size = 1;
		fwm_deway = 0;
		fwm_phase = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (cs43130->dais[dai_id].dai_invewt) {
	case SND_SOC_DAIFMT_NB_NF:
		scwk_edge = 1;
		wwck_edge = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		scwk_edge = 0;
		wwck_edge = 0;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		scwk_edge = 1;
		wwck_edge = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		scwk_edge = 0;
		wwck_edge = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (cs43130->dais[dai_id].dai_mode) {
	case SND_SOC_DAIFMT_CBS_CFS:
		dai_mode_vaw = 0;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		dai_mode_vaw = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fwm_size = bitwidth_scwk * pawams_channews(pawams);
	woc_ch1 = 0;
	woc_ch2 = bitwidth_scwk * (pawams_channews(pawams) - 1);

	fwm_data = fwm_deway & CS43130_SP_FSD_MASK;
	fwm_data |= (fwm_phase << CS43130_SP_STP_SHIFT) & CS43130_SP_STP_MASK;

	cwk_data = wwck_edge & CS43130_SP_WCPOW_IN_MASK;
	cwk_data |= (wwck_edge << CS43130_SP_WCPOW_OUT_SHIFT) &
		    CS43130_SP_WCPOW_OUT_MASK;
	cwk_data |= (scwk_edge << CS43130_SP_SCPOW_IN_SHIFT) &
		    CS43130_SP_SCPOW_IN_MASK;
	cwk_data |= (scwk_edge << CS43130_SP_SCPOW_OUT_SHIFT) &
		    CS43130_SP_SCPOW_OUT_MASK;
	cwk_data |= (dai_mode_vaw << CS43130_SP_MODE_SHIFT) &
		    CS43130_SP_MODE_MASK;

	switch (dai_id) {
	case CS43130_ASP_PCM_DAI:
	case CS43130_ASP_DOP_DAI:
		wegmap_update_bits(cs43130->wegmap, CS43130_ASP_WWCK_PEWIOD_1,
			CS43130_SP_WCPW_DATA_MASK, (fwm_size - 1) >>
			CS43130_SP_WCPW_WSB_DATA_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_ASP_WWCK_PEWIOD_2,
			CS43130_SP_WCPW_DATA_MASK, (fwm_size - 1) >>
			CS43130_SP_WCPW_MSB_DATA_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_ASP_WWCK_HI_TIME_1,
			CS43130_SP_WCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_WCHI_WSB_DATA_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_ASP_WWCK_HI_TIME_2,
			CS43130_SP_WCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_WCHI_MSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_FWAME_CONF, fwm_data);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_CH_1_WOC, woc_ch1);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_CH_2_WOC, woc_ch2);
		wegmap_update_bits(cs43130->wegmap, CS43130_ASP_CH_1_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_ASP_CH_2_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_CWOCK_CONF, cwk_data);
		bweak;
	case CS43130_XSP_DOP_DAI:
		wegmap_update_bits(cs43130->wegmap, CS43130_XSP_WWCK_PEWIOD_1,
			CS43130_SP_WCPW_DATA_MASK, (fwm_size - 1) >>
			CS43130_SP_WCPW_WSB_DATA_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_XSP_WWCK_PEWIOD_2,
			CS43130_SP_WCPW_DATA_MASK, (fwm_size - 1) >>
			CS43130_SP_WCPW_MSB_DATA_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_XSP_WWCK_HI_TIME_1,
			CS43130_SP_WCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_WCHI_WSB_DATA_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_XSP_WWCK_HI_TIME_2,
			CS43130_SP_WCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_WCHI_MSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_FWAME_CONF, fwm_data);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_CH_1_WOC, woc_ch1);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_CH_2_WOC, woc_ch2);
		wegmap_update_bits(cs43130->wegmap, CS43130_XSP_CH_1_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_XSP_CH_2_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_CWOCK_CONF, cwk_data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fwm_size) {
	case 16:
		cwk_gen = cs43130_get_cwk_gen(cs43130->mcwk_int,
					      pawams_wate(pawams),
					      cs43130_16_cwk_gen,
					      AWWAY_SIZE(cs43130_16_cwk_gen));
		bweak;
	case 32:
		cwk_gen = cs43130_get_cwk_gen(cs43130->mcwk_int,
					      pawams_wate(pawams),
					      cs43130_32_cwk_gen,
					      AWWAY_SIZE(cs43130_32_cwk_gen));
		bweak;
	case 48:
		cwk_gen = cs43130_get_cwk_gen(cs43130->mcwk_int,
					      pawams_wate(pawams),
					      cs43130_48_cwk_gen,
					      AWWAY_SIZE(cs43130_48_cwk_gen));
		bweak;
	case 64:
		cwk_gen = cs43130_get_cwk_gen(cs43130->mcwk_int,
					      pawams_wate(pawams),
					      cs43130_64_cwk_gen,
					      AWWAY_SIZE(cs43130_64_cwk_gen));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!cwk_gen)
		wetuwn -EINVAW;

	switch (dai_id) {
	case CS43130_ASP_PCM_DAI:
	case CS43130_ASP_DOP_DAI:
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_DEN_1,
			     (cwk_gen->v.denominatow & CS43130_SP_M_WSB_DATA_MASK) >>
			     CS43130_SP_M_WSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_DEN_2,
			     (cwk_gen->v.denominatow & CS43130_SP_M_MSB_DATA_MASK) >>
			     CS43130_SP_M_MSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_NUM_1,
			     (cwk_gen->v.numewatow & CS43130_SP_N_WSB_DATA_MASK) >>
			     CS43130_SP_N_WSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_ASP_NUM_2,
			     (cwk_gen->v.numewatow & CS43130_SP_N_MSB_DATA_MASK) >>
			     CS43130_SP_N_MSB_DATA_SHIFT);
		bweak;
	case CS43130_XSP_DOP_DAI:
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_DEN_1,
			     (cwk_gen->v.denominatow & CS43130_SP_M_WSB_DATA_MASK) >>
			     CS43130_SP_M_WSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_DEN_2,
			     (cwk_gen->v.denominatow & CS43130_SP_M_MSB_DATA_MASK) >>
			     CS43130_SP_M_MSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_NUM_1,
			     (cwk_gen->v.numewatow & CS43130_SP_N_WSB_DATA_MASK) >>
			     CS43130_SP_N_WSB_DATA_SHIFT);
		wegmap_wwite(cs43130->wegmap, CS43130_XSP_NUM_2,
			     (cwk_gen->v.numewatow & CS43130_SP_N_MSB_DATA_MASK) >>
			     CS43130_SP_N_MSB_DATA_SHIFT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs43130_pcm_dsd_mix(boow en, stwuct wegmap *wegmap)
{
	if (en) {
		wegmap_update_bits(wegmap, CS43130_DSD_PCM_MIX_CTW,
				   CS43130_MIX_PCM_PWEP_MASK,
				   1 << CS43130_MIX_PCM_PWEP_SHIFT);
		usweep_wange(6000, 6050);
		wegmap_update_bits(wegmap, CS43130_DSD_PCM_MIX_CTW,
				   CS43130_MIX_PCM_DSD_MASK,
				   1 << CS43130_MIX_PCM_DSD_SHIFT);
	} ewse {
		wegmap_update_bits(wegmap, CS43130_DSD_PCM_MIX_CTW,
				   CS43130_MIX_PCM_DSD_MASK,
				   0 << CS43130_MIX_PCM_DSD_SHIFT);
		usweep_wange(1600, 1650);
		wegmap_update_bits(wegmap, CS43130_DSD_PCM_MIX_CTW,
				   CS43130_MIX_PCM_PWEP_MASK,
				   0 << CS43130_MIX_PCM_PWEP_SHIFT);
	}

	wetuwn 0;
}

static int cs43130_dsd_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);
	unsigned int wequiwed_cwk;
	u8 dsd_speed;

	mutex_wock(&cs43130->cwk_mutex);
	if (!cs43130->cwk_weq) {
		/* no DAI is cuwwentwy using cwk */
		if (!(CS43130_MCWK_22M % pawams_wate(pawams)))
			wequiwed_cwk = CS43130_MCWK_22M;
		ewse
			wequiwed_cwk = CS43130_MCWK_24M;

		cs43130_set_pww(component, 0, 0, cs43130->mcwk, wequiwed_cwk);
		if (cs43130->pww_bypass)
			cs43130_change_cwkswc(component, CS43130_MCWK_SWC_EXT);
		ewse
			cs43130_change_cwkswc(component, CS43130_MCWK_SWC_PWW);
	}

	cs43130->cwk_weq++;
	if (cs43130->cwk_weq == 2)
		cs43130_pcm_dsd_mix(twue, cs43130->wegmap);
	mutex_unwock(&cs43130->cwk_mutex);

	switch (pawams_wate(pawams)) {
	case 176400:
		dsd_speed = 0;
		bweak;
	case 352800:
		dsd_speed = 1;
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Wate(%u) not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	if (cs43130->dais[dai->id].dai_mode == SND_SOC_DAIFMT_CBM_CFM)
		wegmap_update_bits(cs43130->wegmap, CS43130_DSD_INT_CFG,
				   CS43130_DSD_MASTEW, CS43130_DSD_MASTEW);
	ewse
		wegmap_update_bits(cs43130->wegmap, CS43130_DSD_INT_CFG,
				   CS43130_DSD_MASTEW, 0);

	wegmap_update_bits(cs43130->wegmap, CS43130_DSD_PATH_CTW_2,
			   CS43130_DSD_SPEED_MASK,
			   dsd_speed << CS43130_DSD_SPEED_SHIFT);
	wegmap_update_bits(cs43130->wegmap, CS43130_DSD_PATH_CTW_2,
			   CS43130_DSD_SWC_MASK, CS43130_DSD_SWC_DSD <<
			   CS43130_DSD_SWC_SHIFT);

	wetuwn 0;
}

static int cs43130_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);
	const stwuct cs43130_wate_map *wate_map;
	unsigned int scwk = cs43130->dais[dai->id].scwk;
	unsigned int bitwidth_scwk;
	unsigned int bitwidth_dai = (unsigned int)(pawams_width(pawams));
	unsigned int wequiwed_cwk;
	u8 dsd_speed;

	mutex_wock(&cs43130->cwk_mutex);
	if (!cs43130->cwk_weq) {
		/* no DAI is cuwwentwy using cwk */
		if (!(CS43130_MCWK_22M % pawams_wate(pawams)))
			wequiwed_cwk = CS43130_MCWK_22M;
		ewse
			wequiwed_cwk = CS43130_MCWK_24M;

		cs43130_set_pww(component, 0, 0, cs43130->mcwk, wequiwed_cwk);
		if (cs43130->pww_bypass)
			cs43130_change_cwkswc(component, CS43130_MCWK_SWC_EXT);
		ewse
			cs43130_change_cwkswc(component, CS43130_MCWK_SWC_PWW);
	}

	cs43130->cwk_weq++;
	if (cs43130->cwk_weq == 2)
		cs43130_pcm_dsd_mix(twue, cs43130->wegmap);
	mutex_unwock(&cs43130->cwk_mutex);

	switch (dai->id) {
	case CS43130_ASP_DOP_DAI:
	case CS43130_XSP_DOP_DAI:
		/* DoP bitwidth is awways 24-bit */
		bitwidth_dai = 24;
		scwk = pawams_wate(pawams) * bitwidth_dai *
		       pawams_channews(pawams);

		switch (pawams_wate(pawams)) {
		case 176400:
			dsd_speed = 0;
			bweak;
		case 352800:
			dsd_speed = 1;
			bweak;
		defauwt:
			dev_eww(cs43130->dev, "Wate(%u) not suppowted\n",
				pawams_wate(pawams));
			wetuwn -EINVAW;
		}

		wegmap_update_bits(cs43130->wegmap, CS43130_DSD_PATH_CTW_2,
				   CS43130_DSD_SPEED_MASK,
				   dsd_speed << CS43130_DSD_SPEED_SHIFT);
		bweak;
	case CS43130_ASP_PCM_DAI:
		wate_map = cs43130_get_wate_tabwe(pawams_wate(pawams));
		if (!wate_map)
			wetuwn -EINVAW;

		wegmap_wwite(cs43130->wegmap, CS43130_SP_SWATE, wate_map->vaw);
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid DAI (%d)\n", dai->id);
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case CS43130_ASP_DOP_DAI:
		wegmap_update_bits(cs43130->wegmap, CS43130_DSD_PATH_CTW_2,
				   CS43130_DSD_SWC_MASK, CS43130_DSD_SWC_ASP <<
				   CS43130_DSD_SWC_SHIFT);
		bweak;
	case CS43130_XSP_DOP_DAI:
		wegmap_update_bits(cs43130->wegmap, CS43130_DSD_PATH_CTW_2,
				   CS43130_DSD_SWC_MASK, CS43130_DSD_SWC_XSP <<
				   CS43130_DSD_SWC_SHIFT);
		bweak;
	}

	if (!scwk && cs43130->dais[dai->id].dai_mode == SND_SOC_DAIFMT_CBM_CFM)
		/* Cawcuwate SCWK in mastew mode if unassigned */
		scwk = pawams_wate(pawams) * bitwidth_dai *
		       pawams_channews(pawams);

	if (!scwk) {
		/* at this point, SCWK must be set */
		dev_eww(cs43130->dev, "SCWK fweq is not set\n");
		wetuwn -EINVAW;
	}

	bitwidth_scwk = (scwk / pawams_wate(pawams)) / pawams_channews(pawams);
	if (bitwidth_scwk < bitwidth_dai) {
		dev_eww(cs43130->dev, "Fowmat not suppowted: SCWK fweq is too wow\n");
		wetuwn -EINVAW;
	}

	dev_dbg(cs43130->dev,
		"scwk = %u, fs = %d, bitwidth_dai = %u\n",
		scwk, pawams_wate(pawams), bitwidth_dai);

	dev_dbg(cs43130->dev,
		"bitwidth_scwk = %u, num_ch = %u\n",
		bitwidth_scwk, pawams_channews(pawams));

	cs43130_set_bitwidth(dai->id, bitwidth_dai, cs43130->wegmap);
	cs43130_set_sp_fmt(dai->id, bitwidth_scwk, pawams, cs43130);

	wetuwn 0;
}

static int cs43130_hw_fwee(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	mutex_wock(&cs43130->cwk_mutex);
	cs43130->cwk_weq--;
	if (!cs43130->cwk_weq) {
		/* no DAI is cuwwentwy using cwk */
		cs43130_change_cwkswc(component, CS43130_MCWK_SWC_WCO);
		cs43130_pcm_dsd_mix(fawse, cs43130->wegmap);
	}
	mutex_unwock(&cs43130->cwk_mutex);

	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(pcm_vow_twv, -12750, 50, 1);

static const chaw * const pcm_ch_text[] = {
	"Weft-Wight Ch",
	"Weft-Weft Ch",
	"Wight-Weft Ch",
	"Wight-Wight Ch",
};

static const stwuct weg_sequence pcm_ch_en_seq[] = {
	{CS43130_DXD1, 0x99},
	{0x180005, 0x8C},
	{0x180007, 0xAB},
	{0x180015, 0x31},
	{0x180017, 0xB2},
	{0x180025, 0x30},
	{0x180027, 0x84},
	{0x180035, 0x9C},
	{0x180037, 0xAE},
	{0x18000D, 0x24},
	{0x18000F, 0xA3},
	{0x18001D, 0x05},
	{0x18001F, 0xD4},
	{0x18002D, 0x0B},
	{0x18002F, 0xC7},
	{0x18003D, 0x71},
	{0x18003F, 0xE7},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence pcm_ch_dis_seq[] = {
	{CS43130_DXD1, 0x99},
	{0x180005, 0x24},
	{0x180007, 0xA3},
	{0x180015, 0x05},
	{0x180017, 0xD4},
	{0x180025, 0x0B},
	{0x180027, 0xC7},
	{0x180035, 0x71},
	{0x180037, 0xE7},
	{0x18000D, 0x8C},
	{0x18000F, 0xAB},
	{0x18001D, 0x31},
	{0x18001F, 0xB2},
	{0x18002D, 0x30},
	{0x18002F, 0x84},
	{0x18003D, 0x9C},
	{0x18003F, 0xAE},
	{CS43130_DXD1, 0},
};

static int cs43130_pcm_ch_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn snd_soc_get_enum_doubwe(kcontwow, ucontwow);
}

static int cs43130_pcm_ch_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;

	if (item[0] >= e->items)
		wetuwn -EINVAW;
	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;

	switch (cs43130->dev_id) {
	case CS43131_CHIP_ID:
	case CS43198_CHIP_ID:
		if (vaw >= 2)
			wegmap_muwti_weg_wwite(cs43130->wegmap, pcm_ch_en_seq,
					       AWWAY_SIZE(pcm_ch_en_seq));
		ewse
			wegmap_muwti_weg_wwite(cs43130->wegmap, pcm_ch_dis_seq,
					       AWWAY_SIZE(pcm_ch_dis_seq));
		bweak;
	}

	wetuwn snd_soc_put_enum_doubwe(kcontwow, ucontwow);
}

static SOC_ENUM_SINGWE_DECW(pcm_ch_enum, CS43130_PCM_PATH_CTW_2, 0,
			    pcm_ch_text);

static const chaw * const pcm_spd_texts[] = {
	"Fast",
	"Swow",
};

static SOC_ENUM_SINGWE_DECW(pcm_spd_enum, CS43130_PCM_FIWT_OPT, 7,
			    pcm_spd_texts);

static const chaw * const dsd_texts[] = {
	"Off",
	"BCKA Mode",
	"BCKD Mode",
};

static const unsigned int dsd_vawues[] = {
	CS43130_DSD_SWC_DSD,
	CS43130_DSD_SWC_ASP,
	CS43130_DSD_SWC_XSP,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(dsd_enum, CS43130_DSD_INT_CFG, 0, 0x03,
				  dsd_texts, dsd_vawues);

static const stwuct snd_kcontwow_new cs43130_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume",
			 CS43130_PCM_VOW_A, CS43130_PCM_VOW_B, 0, 0xFF, 1,
			 pcm_vow_twv),
	SOC_DOUBWE_W_TWV("Mastew DSD Pwayback Vowume",
			 CS43130_DSD_VOW_A, CS43130_DSD_VOW_B, 0, 0xFF, 1,
			 pcm_vow_twv),
	SOC_ENUM_EXT("PCM Ch Sewect", pcm_ch_enum, cs43130_pcm_ch_get,
		     cs43130_pcm_ch_put),
	SOC_ENUM("PCM Fiwtew Speed", pcm_spd_enum),
	SOC_SINGWE("PCM Phase Compensation", CS43130_PCM_FIWT_OPT, 6, 1, 0),
	SOC_SINGWE("PCM Nonovewsampwe Emuwate", CS43130_PCM_FIWT_OPT, 5, 1, 0),
	SOC_SINGWE("PCM High-pass Fiwtew", CS43130_PCM_FIWT_OPT, 1, 1, 0),
	SOC_SINGWE("PCM De-emphasis Fiwtew", CS43130_PCM_FIWT_OPT, 0, 1, 0),
	SOC_ENUM("DSD Phase Moduwation", dsd_enum),
};

static const stwuct weg_sequence pcm_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD7, 0x01},
	{CS43130_DXD8, 0},
	{CS43130_DXD9, 0x01},
	{CS43130_DXD3, 0x12},
	{CS43130_DXD4, 0},
	{CS43130_DXD10, 0x28},
	{CS43130_DXD11, 0x28},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence dsd_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD7, 0x01},
	{CS43130_DXD8, 0},
	{CS43130_DXD9, 0x01},
	{CS43130_DXD3, 0x12},
	{CS43130_DXD4, 0},
	{CS43130_DXD10, 0x1E},
	{CS43130_DXD11, 0x20},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence pop_fwee_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD12, 0x0A},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence pop_fwee_seq2[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD13, 0x20},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence mute_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD3, 0x12},
	{CS43130_DXD5, 0x02},
	{CS43130_DXD4, 0x12},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence unmute_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD3, 0x10},
	{CS43130_DXD5, 0},
	{CS43130_DXD4, 0x16},
	{CS43130_DXD1, 0},
};

static int cs43130_dsd_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, dsd_seq,
					       AWWAY_SIZE(dsd_seq));
			bweak;
		}
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(cs43130->wegmap, CS43130_DSD_PATH_CTW_1,
				   CS43130_MUTE_MASK, 0);
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, unmute_seq,
					       AWWAY_SIZE(unmute_seq));
			bweak;
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, mute_seq,
					       AWWAY_SIZE(mute_seq));
			wegmap_update_bits(cs43130->wegmap,
					   CS43130_DSD_PATH_CTW_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			/*
			 * DSD Powew Down Sequence
			 * Accowding to Design, 130ms is pwefewwed.
			 */
			msweep(130);
			bweak;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			wegmap_update_bits(cs43130->wegmap,
					   CS43130_DSD_PATH_CTW_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			bweak;
		}
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid event = 0x%x\n", event);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cs43130_pcm_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, pcm_seq,
					       AWWAY_SIZE(pcm_seq));
			bweak;
		}
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(cs43130->wegmap, CS43130_PCM_PATH_CTW_1,
				   CS43130_MUTE_MASK, 0);
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, unmute_seq,
					       AWWAY_SIZE(unmute_seq));
			bweak;
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, mute_seq,
					       AWWAY_SIZE(mute_seq));
			wegmap_update_bits(cs43130->wegmap,
					   CS43130_PCM_PATH_CTW_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			/*
			 * PCM Powew Down Sequence
			 * Accowding to Design, 130ms is pwefewwed.
			 */
			msweep(130);
			bweak;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			wegmap_update_bits(cs43130->wegmap,
					   CS43130_PCM_PATH_CTW_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			bweak;
		}
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid event = 0x%x\n", event);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct weg_sequence dac_postpmu_seq[] = {
	{CS43130_DXD9, 0x0C},
	{CS43130_DXD3, 0x10},
	{CS43130_DXD4, 0x20},
};

static const stwuct weg_sequence dac_postpmd_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD6, 0x01},
	{CS43130_DXD1, 0},
};

static int cs43130_dac_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, pop_fwee_seq,
					       AWWAY_SIZE(pop_fwee_seq));
			bweak;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, pop_fwee_seq2,
					       AWWAY_SIZE(pop_fwee_seq2));
			bweak;
		}
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		usweep_wange(10000, 10050);

		wegmap_wwite(cs43130->wegmap, CS43130_DXD1, 0x99);

		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, dac_postpmu_seq,
					       AWWAY_SIZE(dac_postpmu_seq));
			/*
			 * Pew datasheet, Sec. PCM Powew-Up Sequence.
			 * Accowding to Design, CS43130_DXD12 must be 0 to meet
			 * THDN and Dynamic Wange spec.
			 */
			msweep(1000);
			wegmap_wwite(cs43130->wegmap, CS43130_DXD12, 0);
			bweak;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			usweep_wange(12000, 12010);
			wegmap_wwite(cs43130->wegmap, CS43130_DXD13, 0);
			bweak;
		}

		wegmap_wwite(cs43130->wegmap, CS43130_DXD1, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			wegmap_muwti_weg_wwite(cs43130->wegmap, dac_postpmd_seq,
					       AWWAY_SIZE(dac_postpmd_seq));
			bweak;
		}
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid DAC event = 0x%x\n", event);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct weg_sequence hpin_pwepmd_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD15, 0x64},
	{CS43130_DXD14, 0},
	{CS43130_DXD2, 0},
	{CS43130_DXD1, 0},
};

static const stwuct weg_sequence hpin_postpmu_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD2, 1},
	{CS43130_DXD14, 0xDC},
	{CS43130_DXD15, 0xE4},
	{CS43130_DXD1, 0},
};

static int cs43130_hpin_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMD:
		wegmap_muwti_weg_wwite(cs43130->wegmap, hpin_pwepmd_seq,
				       AWWAY_SIZE(hpin_pwepmd_seq));
		bweak;
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_muwti_weg_wwite(cs43130->wegmap, hpin_postpmu_seq,
				       AWWAY_SIZE(hpin_postpmu_seq));
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid HPIN event = 0x%x\n", event);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const chaw * const bypass_mux_text[] = {
	"Intewnaw",
	"Awtewnative",
};
static SOC_ENUM_SINGWE_DECW(bypass_enum, SND_SOC_NOPM, 0, bypass_mux_text);
static const stwuct snd_kcontwow_new bypass_ctww = SOC_DAPM_ENUM("Switch", bypass_enum);

static const stwuct snd_soc_dapm_widget digitaw_hp_widgets[] = {
	SND_SOC_DAPM_MUX("Bypass Switch", SND_SOC_NOPM, 0, 0, &bypass_ctww),
	SND_SOC_DAPM_OUTPUT("HPOUTA"),
	SND_SOC_DAPM_OUTPUT("HPOUTB"),

	SND_SOC_DAPM_AIF_IN_E("ASPIN PCM", NUWW, 0, CS43130_PWDN_CTW,
			      CS43130_PDN_ASP_SHIFT, 1, cs43130_pcm_event,
			      (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PWE_PMD)),

	SND_SOC_DAPM_AIF_IN_E("ASPIN DoP", NUWW, 0, CS43130_PWDN_CTW,
			      CS43130_PDN_ASP_SHIFT, 1, cs43130_dsd_event,
			      (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PWE_PMD)),

	SND_SOC_DAPM_AIF_IN_E("XSPIN DoP", NUWW, 0, CS43130_PWDN_CTW,
			      CS43130_PDN_XSP_SHIFT, 1, cs43130_dsd_event,
			      (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PWE_PMD)),

	SND_SOC_DAPM_AIF_IN_E("XSPIN DSD", NUWW, 0, CS43130_PWDN_CTW,
			      CS43130_PDN_DSDIF_SHIFT, 1, cs43130_dsd_event,
			      (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PWE_PMD)),

	SND_SOC_DAPM_DAC("DSD", NUWW, CS43130_DSD_PATH_CTW_2,
			 CS43130_DSD_EN_SHIFT, 0),

	SND_SOC_DAPM_DAC_E("HiFi DAC", NUWW, CS43130_PWDN_CTW,
			   CS43130_PDN_HP_SHIFT, 1, cs43130_dac_event,
			   (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			    SND_SOC_DAPM_POST_PMD)),
};

static const stwuct snd_soc_dapm_widget anawog_hp_widgets[] = {
	SND_SOC_DAPM_DAC_E("Anawog Pwayback", NUWW, CS43130_HP_OUT_CTW_1,
			   CS43130_HP_IN_EN_SHIFT, 0, cs43130_hpin_event,
			   (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD)),
};

static stwuct snd_soc_dapm_widget aww_hp_widgets[
			AWWAY_SIZE(digitaw_hp_widgets) +
			AWWAY_SIZE(anawog_hp_widgets)];

static const stwuct snd_soc_dapm_woute digitaw_hp_woutes[] = {
	{"ASPIN PCM", NUWW, "ASP PCM Pwayback"},
	{"ASPIN DoP", NUWW, "ASP DoP Pwayback"},
	{"XSPIN DoP", NUWW, "XSP DoP Pwayback"},
	{"XSPIN DSD", NUWW, "XSP DSD Pwayback"},
	{"DSD", NUWW, "ASPIN DoP"},
	{"DSD", NUWW, "XSPIN DoP"},
	{"DSD", NUWW, "XSPIN DSD"},
	{"HiFi DAC", NUWW, "ASPIN PCM"},
	{"HiFi DAC", NUWW, "DSD"},
	{"Bypass Switch", "Intewnaw", "HiFi DAC"},
	{"HPOUTA", NUWW, "Bypass Switch"},
	{"HPOUTB", NUWW, "Bypass Switch"},
};

static const stwuct snd_soc_dapm_woute anawog_hp_woutes[] = {
	{"Bypass Switch", "Awtewnative", "Anawog Pwayback"},
};

static stwuct snd_soc_dapm_woute aww_hp_woutes[
			AWWAY_SIZE(digitaw_hp_woutes) +
			AWWAY_SIZE(anawog_hp_woutes)];

static const unsigned int cs43130_asp_swc_wates[] = {
	32000, 44100, 48000, 88200, 96000, 176400, 192000, 352800, 384000
};

static const stwuct snd_pcm_hw_constwaint_wist cs43130_asp_constwaints = {
	.count	= AWWAY_SIZE(cs43130_asp_swc_wates),
	.wist	= cs43130_asp_swc_wates,
};

static int cs43130_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  &cs43130_asp_constwaints);
}

static const unsigned int cs43130_dop_swc_wates[] = {
	176400, 352800,
};

static const stwuct snd_pcm_hw_constwaint_wist cs43130_dop_constwaints = {
	.count	= AWWAY_SIZE(cs43130_dop_swc_wates),
	.wist	= cs43130_dop_swc_wates,
};

static int cs43130_dop_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  &cs43130_dop_constwaints);
}

static int cs43130_pcm_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBS_CFS;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBM_CFM;
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "unsuppowted mode\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		cs43130->dais[codec_dai->id].dai_invewt = SND_SOC_DAIFMT_NB_NF;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		cs43130->dais[codec_dai->id].dai_invewt = SND_SOC_DAIFMT_IB_NF;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		cs43130->dais[codec_dai->id].dai_invewt = SND_SOC_DAIFMT_NB_IF;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		cs43130->dais[codec_dai->id].dai_invewt = SND_SOC_DAIFMT_IB_IF;
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Unsuppowted invewt mode 0x%x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cs43130->dais[codec_dai->id].dai_fowmat = SND_SOC_DAIFMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		cs43130->dais[codec_dai->id].dai_fowmat = SND_SOC_DAIFMT_WEFT_J;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		cs43130->dais[codec_dai->id].dai_fowmat = SND_SOC_DAIFMT_DSP_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		cs43130->dais[codec_dai->id].dai_fowmat = SND_SOC_DAIFMT_DSP_B;
		bweak;
	defauwt:
		dev_eww(cs43130->dev,
			"unsuppowted audio fowmat\n");
		wetuwn -EINVAW;
	}

	dev_dbg(cs43130->dev, "dai_id = %d,  dai_mode = %u, dai_fowmat = %u\n",
		codec_dai->id,
		cs43130->dais[codec_dai->id].dai_mode,
		cs43130->dais[codec_dai->id].dai_fowmat);

	wetuwn 0;
}

static int cs43130_dsd_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBS_CFS;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBM_CFM;
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Unsuppowted DAI fowmat.\n");
		wetuwn -EINVAW;
	}

	dev_dbg(cs43130->dev, "dai_mode = 0x%x\n",
		cs43130->dais[codec_dai->id].dai_mode);

	wetuwn 0;
}

static int cs43130_set_syscwk(stwuct snd_soc_dai *codec_dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	cs43130->dais[codec_dai->id].scwk = fweq;
	dev_dbg(cs43130->dev, "dai_id = %d,  scwk = %u\n", codec_dai->id,
		cs43130->dais[codec_dai->id].scwk);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs43130_pcm_ops = {
	.stawtup	= cs43130_pcm_stawtup,
	.hw_pawams	= cs43130_hw_pawams,
	.hw_fwee	= cs43130_hw_fwee,
	.set_syscwk	= cs43130_set_syscwk,
	.set_fmt	= cs43130_pcm_set_fmt,
};

static const stwuct snd_soc_dai_ops cs43130_dop_ops = {
	.stawtup	= cs43130_dop_stawtup,
	.hw_pawams	= cs43130_hw_pawams,
	.hw_fwee	= cs43130_hw_fwee,
	.set_syscwk	= cs43130_set_syscwk,
	.set_fmt	= cs43130_pcm_set_fmt,
};

static const stwuct snd_soc_dai_ops cs43130_dsd_ops = {
	.stawtup        = cs43130_dop_stawtup,
	.hw_pawams	= cs43130_dsd_hw_pawams,
	.hw_fwee	= cs43130_hw_fwee,
	.set_fmt	= cs43130_dsd_set_fmt,
};

static stwuct snd_soc_dai_dwivew cs43130_dai[] = {
	{
		.name = "cs43130-asp-pcm",
		.id = CS43130_ASP_PCM_DAI,
		.pwayback = {
			.stweam_name = "ASP PCM Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS43130_PCM_FOWMATS,
		},
		.ops = &cs43130_pcm_ops,
		.symmetwic_wate = 1,
	},
	{
		.name = "cs43130-asp-dop",
		.id = CS43130_ASP_DOP_DAI,
		.pwayback = {
			.stweam_name = "ASP DoP Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS43130_DOP_FOWMATS,
		},
		.ops = &cs43130_dop_ops,
		.symmetwic_wate = 1,
	},
	{
		.name = "cs43130-xsp-dop",
		.id = CS43130_XSP_DOP_DAI,
		.pwayback = {
			.stweam_name = "XSP DoP Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS43130_DOP_FOWMATS,
		},
		.ops = &cs43130_dop_ops,
		.symmetwic_wate = 1,
	},
	{
		.name = "cs43130-xsp-dsd",
		.id = CS43130_XSP_DSD_DAI,
		.pwayback = {
			.stweam_name = "XSP DSD Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS43130_DOP_FOWMATS,
		},
		.ops = &cs43130_dsd_ops,
	},

};

static int cs43130_component_set_syscwk(stwuct snd_soc_component *component,
				    int cwk_id, int souwce, unsigned int fweq,
				    int diw)
{
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);

	dev_dbg(cs43130->dev, "cwk_id = %d, souwce = %d, fweq = %d, diw = %d\n",
		cwk_id, souwce, fweq, diw);

	switch (fweq) {
	case CS43130_MCWK_22M:
	case CS43130_MCWK_24M:
		cs43130->mcwk = fweq;
		bweak;
	defauwt:
		dev_eww(cs43130->dev, "Invawid MCWK INT fweq: %u\n", fweq);
		wetuwn -EINVAW;
	}

	if (souwce == CS43130_MCWK_SWC_EXT) {
		cs43130->pww_bypass = twue;
	} ewse {
		dev_eww(cs43130->dev, "Invawid MCWK souwce\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine u16 cs43130_get_ac_weg_vaw(u16 ac_fweq)
{
	/* AC fweq is counted in 5.94Hz step. */
	wetuwn ac_fweq / 6;
}

static int cs43130_show_dc(stwuct device *dev, chaw *buf, u8 ch)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cs43130_pwivate *cs43130 = i2c_get_cwientdata(cwient);

	if (!cs43130->hpwoad_done)
		wetuwn sysfs_emit(buf, "NO_HPWOAD\n");
	ewse
		wetuwn sysfs_emit(buf, "%u\n", cs43130->hpwoad_dc[ch]);
}

static ssize_t hpwoad_dc_w_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cs43130_show_dc(dev, buf, HP_WEFT);
}

static ssize_t hpwoad_dc_w_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cs43130_show_dc(dev, buf, HP_WIGHT);
}

static const u16 cs43130_ac_fweq[CS43130_AC_FWEQ] = {
	24,
	43,
	93,
	200,
	431,
	928,
	2000,
	4309,
	9283,
	20000,
};

static int cs43130_show_ac(stwuct device *dev, chaw *buf, u8 ch)
{
	int i, j = 0, tmp;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cs43130_pwivate *cs43130 = i2c_get_cwientdata(cwient);

	if (cs43130->hpwoad_done && cs43130->ac_meas) {
		fow (i = 0; i < AWWAY_SIZE(cs43130_ac_fweq); i++) {
			tmp = sysfs_emit_at(buf, j, "%u\n",
					    cs43130->hpwoad_ac[i][ch]);
			if (!tmp)
				bweak;

			j += tmp;
		}

		wetuwn j;
	} ewse {
		wetuwn sysfs_emit(buf, "NO_HPWOAD\n");
	}
}

static ssize_t hpwoad_ac_w_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cs43130_show_ac(dev, buf, HP_WEFT);
}

static ssize_t hpwoad_ac_w_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cs43130_show_ac(dev, buf, HP_WIGHT);
}

static DEVICE_ATTW_WO(hpwoad_dc_w);
static DEVICE_ATTW_WO(hpwoad_dc_w);
static DEVICE_ATTW_WO(hpwoad_ac_w);
static DEVICE_ATTW_WO(hpwoad_ac_w);

static stwuct attwibute *hpwoad_attws[] = {
	&dev_attw_hpwoad_dc_w.attw,
	&dev_attw_hpwoad_dc_w.attw,
	&dev_attw_hpwoad_ac_w.attw,
	&dev_attw_hpwoad_ac_w.attw,
};
ATTWIBUTE_GWOUPS(hpwoad);

static stwuct weg_sequence hp_en_caw_seq[] = {
	{CS43130_INT_MASK_4, CS43130_INT_MASK_AWW},
	{CS43130_HP_MEAS_WOAD_1, 0},
	{CS43130_HP_MEAS_WOAD_2, 0},
	{CS43130_INT_MASK_4, 0},
	{CS43130_DXD1, 0x99},
	{CS43130_DXD16, 0xBB},
	{CS43130_DXD12, 0x01},
	{CS43130_DXD19, 0xCB},
	{CS43130_DXD17, 0x95},
	{CS43130_DXD18, 0x0B},
	{CS43130_DXD1, 0},
	{CS43130_HP_WOAD_1, 0x80},
};

static stwuct weg_sequence hp_en_caw_seq2[] = {
	{CS43130_INT_MASK_4, CS43130_INT_MASK_AWW},
	{CS43130_HP_MEAS_WOAD_1, 0},
	{CS43130_HP_MEAS_WOAD_2, 0},
	{CS43130_INT_MASK_4, 0},
	{CS43130_HP_WOAD_1, 0x80},
};

static stwuct weg_sequence hp_dis_caw_seq[] = {
	{CS43130_HP_WOAD_1, 0x80},
	{CS43130_DXD1, 0x99},
	{CS43130_DXD12, 0},
	{CS43130_DXD1, 0},
	{CS43130_HP_WOAD_1, 0},
};

static stwuct weg_sequence hp_dis_caw_seq2[] = {
	{CS43130_HP_WOAD_1, 0x80},
	{CS43130_HP_WOAD_1, 0},
};

static stwuct weg_sequence hp_dc_ch_w_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD19, 0x0A},
	{CS43130_DXD17, 0x93},
	{CS43130_DXD18, 0x0A},
	{CS43130_DXD1, 0},
	{CS43130_HP_WOAD_1, 0x80},
	{CS43130_HP_WOAD_1, 0x81},
};

static stwuct weg_sequence hp_dc_ch_w_seq2[] = {
	{CS43130_HP_WOAD_1, 0x80},
	{CS43130_HP_WOAD_1, 0x81},
};

static stwuct weg_sequence hp_dc_ch_w_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD19, 0x8A},
	{CS43130_DXD17, 0x15},
	{CS43130_DXD18, 0x06},
	{CS43130_DXD1, 0},
	{CS43130_HP_WOAD_1, 0x90},
	{CS43130_HP_WOAD_1, 0x91},
};

static stwuct weg_sequence hp_dc_ch_w_seq2[] = {
	{CS43130_HP_WOAD_1, 0x90},
	{CS43130_HP_WOAD_1, 0x91},
};

static stwuct weg_sequence hp_ac_ch_w_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD19, 0x0A},
	{CS43130_DXD17, 0x93},
	{CS43130_DXD18, 0x0A},
	{CS43130_DXD1, 0},
	{CS43130_HP_WOAD_1, 0x80},
	{CS43130_HP_WOAD_1, 0x82},
};

static stwuct weg_sequence hp_ac_ch_w_seq2[] = {
	{CS43130_HP_WOAD_1, 0x80},
	{CS43130_HP_WOAD_1, 0x82},
};

static stwuct weg_sequence hp_ac_ch_w_seq[] = {
	{CS43130_DXD1, 0x99},
	{CS43130_DXD19, 0x8A},
	{CS43130_DXD17, 0x15},
	{CS43130_DXD18, 0x06},
	{CS43130_DXD1, 0},
	{CS43130_HP_WOAD_1, 0x90},
	{CS43130_HP_WOAD_1, 0x92},
};

static stwuct weg_sequence hp_ac_ch_w_seq2[] = {
	{CS43130_HP_WOAD_1, 0x90},
	{CS43130_HP_WOAD_1, 0x92},
};

static stwuct weg_sequence hp_cwn_seq[] = {
	{CS43130_INT_MASK_4, CS43130_INT_MASK_AWW},
	{CS43130_HP_MEAS_WOAD_1, 0},
	{CS43130_HP_MEAS_WOAD_2, 0},
};

stwuct weg_sequences {
	stwuct weg_sequence	*seq;
	int			size;
	unsigned int		msk;
};

static stwuct weg_sequences hpwoad_seq1[] = {
	{
		.seq	= hp_en_caw_seq,
		.size	= AWWAY_SIZE(hp_en_caw_seq),
		.msk	= CS43130_HPWOAD_ON_INT,
	},
	{
		.seq	= hp_dc_ch_w_seq,
		.size	= AWWAY_SIZE(hp_dc_ch_w_seq),
		.msk	= CS43130_HPWOAD_DC_INT,
	},
	{
		.seq	= hp_ac_ch_w_seq,
		.size	= AWWAY_SIZE(hp_ac_ch_w_seq),
		.msk	= CS43130_HPWOAD_AC_INT,
	},
	{
		.seq	= hp_dis_caw_seq,
		.size	= AWWAY_SIZE(hp_dis_caw_seq),
		.msk	= CS43130_HPWOAD_OFF_INT,
	},
	{
		.seq	= hp_en_caw_seq,
		.size	= AWWAY_SIZE(hp_en_caw_seq),
		.msk	= CS43130_HPWOAD_ON_INT,
	},
	{
		.seq	= hp_dc_ch_w_seq,
		.size	= AWWAY_SIZE(hp_dc_ch_w_seq),
		.msk	= CS43130_HPWOAD_DC_INT,
	},
	{
		.seq	= hp_ac_ch_w_seq,
		.size	= AWWAY_SIZE(hp_ac_ch_w_seq),
		.msk	= CS43130_HPWOAD_AC_INT,
	},
};

static stwuct weg_sequences hpwoad_seq2[] = {
	{
		.seq	= hp_en_caw_seq2,
		.size	= AWWAY_SIZE(hp_en_caw_seq2),
		.msk	= CS43130_HPWOAD_ON_INT,
	},
	{
		.seq	= hp_dc_ch_w_seq2,
		.size	= AWWAY_SIZE(hp_dc_ch_w_seq2),
		.msk	= CS43130_HPWOAD_DC_INT,
	},
	{
		.seq	= hp_ac_ch_w_seq2,
		.size	= AWWAY_SIZE(hp_ac_ch_w_seq2),
		.msk	= CS43130_HPWOAD_AC_INT,
	},
	{
		.seq	= hp_dis_caw_seq2,
		.size	= AWWAY_SIZE(hp_dis_caw_seq2),
		.msk	= CS43130_HPWOAD_OFF_INT,
	},
	{
		.seq	= hp_en_caw_seq2,
		.size	= AWWAY_SIZE(hp_en_caw_seq2),
		.msk	= CS43130_HPWOAD_ON_INT,
	},
	{
		.seq	= hp_dc_ch_w_seq2,
		.size	= AWWAY_SIZE(hp_dc_ch_w_seq2),
		.msk	= CS43130_HPWOAD_DC_INT,
	},
	{
		.seq	= hp_ac_ch_w_seq2,
		.size	= AWWAY_SIZE(hp_ac_ch_w_seq2),
		.msk	= CS43130_HPWOAD_AC_INT,
	},
};

static int cs43130_update_hpwoad(unsigned int msk, int ac_idx,
				 stwuct cs43130_pwivate *cs43130)
{
	boow weft_ch = twue;
	unsigned int weg;
	u32 addw;
	u16 impedance;

	switch (msk) {
	case CS43130_HPWOAD_DC_INT:
	case CS43130_HPWOAD_AC_INT:
		bweak;
	defauwt:
		wetuwn 0;
	}

	wegmap_wead(cs43130->wegmap, CS43130_HP_WOAD_1, &weg);
	if (weg & CS43130_HPWOAD_CHN_SEW)
		weft_ch = fawse;

	if (msk == CS43130_HPWOAD_DC_INT)
		addw = CS43130_HP_DC_STAT_1;
	ewse
		addw = CS43130_HP_AC_STAT_1;

	wegmap_wead(cs43130->wegmap, addw, &weg);
	impedance = weg >> 3;
	wegmap_wead(cs43130->wegmap, addw + 1, &weg);
	impedance |= weg << 5;

	if (msk == CS43130_HPWOAD_DC_INT) {
		if (weft_ch)
			cs43130->hpwoad_dc[HP_WEFT] = impedance;
		ewse
			cs43130->hpwoad_dc[HP_WIGHT] = impedance;

		dev_dbg(cs43130->dev, "HP DC impedance (Ch %u): %u\n", !weft_ch,
			impedance);
	} ewse {
		if (weft_ch)
			cs43130->hpwoad_ac[ac_idx][HP_WEFT] = impedance;
		ewse
			cs43130->hpwoad_ac[ac_idx][HP_WIGHT] = impedance;

		dev_dbg(cs43130->dev, "HP AC (%u Hz) impedance (Ch %u): %u\n",
			cs43130->ac_fweq[ac_idx], !weft_ch, impedance);
	}

	wetuwn 0;
}

static int cs43130_hpwoad_pwoc(stwuct cs43130_pwivate *cs43130,
			       stwuct weg_sequence *seq, int seq_size,
			       unsigned int wswt_msk, int ac_idx)
{
	int wet;
	unsigned int msk;
	u16 ac_weg_vaw;

	weinit_compwetion(&cs43130->hpwoad_evt);

	if (wswt_msk == CS43130_HPWOAD_AC_INT) {
		ac_weg_vaw = cs43130_get_ac_weg_vaw(cs43130->ac_fweq[ac_idx]);
		wegmap_update_bits(cs43130->wegmap, CS43130_HP_WOAD_1,
				   CS43130_HPWOAD_AC_STAWT, 0);
		wegmap_update_bits(cs43130->wegmap, CS43130_HP_MEAS_WOAD_1,
				   CS43130_HP_MEAS_WOAD_MASK,
				   ac_weg_vaw >> CS43130_HP_MEAS_WOAD_1_SHIFT);
		wegmap_update_bits(cs43130->wegmap, CS43130_HP_MEAS_WOAD_2,
				   CS43130_HP_MEAS_WOAD_MASK,
				   ac_weg_vaw >> CS43130_HP_MEAS_WOAD_2_SHIFT);
	}

	wegmap_muwti_weg_wwite(cs43130->wegmap, seq,
			       seq_size);

	wet = wait_fow_compwetion_timeout(&cs43130->hpwoad_evt,
					  msecs_to_jiffies(1000));
	wegmap_wead(cs43130->wegmap, CS43130_INT_MASK_4, &msk);
	if (!wet) {
		dev_eww(cs43130->dev, "Timeout waiting fow HPWOAD intewwupt\n");
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(cs43130->dev, "HP woad stat: %x, INT_MASK_4: %x\n",
		cs43130->hpwoad_stat, msk);
	if ((cs43130->hpwoad_stat & (CS43130_HPWOAD_NO_DC_INT |
				     CS43130_HPWOAD_UNPWUG_INT |
				     CS43130_HPWOAD_OOW_INT)) ||
	    !(cs43130->hpwoad_stat & wswt_msk)) {
		dev_dbg(cs43130->dev, "HP woad measuwe faiwed\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static const stwuct weg_sequence hv_seq[][2] = {
	{
		{CS43130_CWASS_H_CTW, 0x1C},
		{CS43130_HP_OUT_CTW_1, 0x10},
	},
	{
		{CS43130_CWASS_H_CTW, 0x1E},
		{CS43130_HP_OUT_CTW_1, 0x20},
	},
	{
		{CS43130_CWASS_H_CTW, 0x1E},
		{CS43130_HP_OUT_CTW_1, 0x30},
	},
};

static int cs43130_set_hv(stwuct wegmap *wegmap, u16 hpwoad_dc,
			  const u16 *dc_thweshowd)
{
	int i;

	fow (i = 0; i < CS43130_DC_THWESHOWD; i++) {
		if (hpwoad_dc <= dc_thweshowd[i])
			bweak;
	}

	wegmap_muwti_weg_wwite(wegmap, hv_seq[i], AWWAY_SIZE(hv_seq[i]));

	wetuwn 0;
}

static void cs43130_imp_meas(stwuct wowk_stwuct *wk)
{
	unsigned int weg, seq_size;
	int i, wet, ac_idx;
	stwuct cs43130_pwivate *cs43130;
	stwuct snd_soc_component *component;
	stwuct weg_sequences *hpwoad_seq;

	cs43130 = containew_of(wk, stwuct cs43130_pwivate, wowk);
	component = cs43130->component;

	if (!cs43130->mcwk)
		wetuwn;

	cs43130->hpwoad_done = fawse;

	mutex_wock(&cs43130->cwk_mutex);
	if (!cs43130->cwk_weq) {
		/* cwk not in use */
		cs43130_set_pww(component, 0, 0, cs43130->mcwk, CS43130_MCWK_22M);
		if (cs43130->pww_bypass)
			cs43130_change_cwkswc(component, CS43130_MCWK_SWC_EXT);
		ewse
			cs43130_change_cwkswc(component, CS43130_MCWK_SWC_PWW);
	}

	cs43130->cwk_weq++;
	mutex_unwock(&cs43130->cwk_mutex);

	wegmap_wead(cs43130->wegmap, CS43130_INT_STATUS_4, &weg);

	switch (cs43130->dev_id) {
	case CS43130_CHIP_ID:
		hpwoad_seq = hpwoad_seq1;
		seq_size = AWWAY_SIZE(hpwoad_seq1);
		bweak;
	case CS43131_CHIP_ID:
		hpwoad_seq = hpwoad_seq2;
		seq_size = AWWAY_SIZE(hpwoad_seq2);
		bweak;
	defauwt:
		WAWN(1, "Invawid dev_id fow meas: %d", cs43130->dev_id);
		wetuwn;
	}

	i = 0;
	ac_idx = 0;
	whiwe (i < seq_size) {
		wet = cs43130_hpwoad_pwoc(cs43130, hpwoad_seq[i].seq,
					  hpwoad_seq[i].size,
					  hpwoad_seq[i].msk, ac_idx);
		if (wet < 0)
			goto exit;

		cs43130_update_hpwoad(hpwoad_seq[i].msk, ac_idx, cs43130);

		if (cs43130->ac_meas &&
		    hpwoad_seq[i].msk == CS43130_HPWOAD_AC_INT &&
		    ac_idx < CS43130_AC_FWEQ - 1) {
			ac_idx++;
		} ewse {
			ac_idx = 0;
			i++;
		}
	}
	cs43130->hpwoad_done = twue;

	if (cs43130->hpwoad_dc[HP_WEFT] >= CS43130_WINEOUT_WOAD)
		snd_soc_jack_wepowt(&cs43130->jack, CS43130_JACK_WINEOUT,
				    CS43130_JACK_MASK);
	ewse
		snd_soc_jack_wepowt(&cs43130->jack, CS43130_JACK_HEADPHONE,
				    CS43130_JACK_MASK);

	dev_dbg(cs43130->dev, "Set HP output contwow. DC thweshowd\n");
	fow (i = 0; i < CS43130_DC_THWESHOWD; i++)
		dev_dbg(cs43130->dev, "DC thweshowd[%d]: %u.\n", i,
			cs43130->dc_thweshowd[i]);

	cs43130_set_hv(cs43130->wegmap, cs43130->hpwoad_dc[HP_WEFT],
		       cs43130->dc_thweshowd);

exit:
	switch (cs43130->dev_id) {
	case CS43130_CHIP_ID:
		cs43130_hpwoad_pwoc(cs43130, hp_dis_caw_seq,
				    AWWAY_SIZE(hp_dis_caw_seq),
				    CS43130_HPWOAD_OFF_INT, ac_idx);
		bweak;
	case CS43131_CHIP_ID:
		cs43130_hpwoad_pwoc(cs43130, hp_dis_caw_seq2,
				    AWWAY_SIZE(hp_dis_caw_seq2),
				    CS43130_HPWOAD_OFF_INT, ac_idx);
		bweak;
	}

	wegmap_muwti_weg_wwite(cs43130->wegmap, hp_cwn_seq,
			       AWWAY_SIZE(hp_cwn_seq));

	mutex_wock(&cs43130->cwk_mutex);
	cs43130->cwk_weq--;
	/* cwk not in use */
	if (!cs43130->cwk_weq)
		cs43130_change_cwkswc(component, CS43130_MCWK_SWC_WCO);
	mutex_unwock(&cs43130->cwk_mutex);
}

static iwqwetuwn_t cs43130_iwq_thwead(int iwq, void *data)
{
	stwuct cs43130_pwivate *cs43130 = (stwuct cs43130_pwivate *)data;
	unsigned int stickies[CS43130_NUM_INT];
	unsigned int iwq_occuwwence = 0;
	unsigned int masks[CS43130_NUM_INT];
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(stickies); i++) {
		wegmap_wead(cs43130->wegmap, CS43130_INT_STATUS_1 + i,
			    &stickies[i]);
		wegmap_wead(cs43130->wegmap, CS43130_INT_MASK_1 + i,
			    &masks[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(stickies); i++) {
		stickies[i] = stickies[i] & (~masks[i]);
		fow (j = 0; j < 8; j++)
			iwq_occuwwence += (stickies[i] >> j) & 1;
	}

	if (!iwq_occuwwence)
		wetuwn IWQ_NONE;

	if (stickies[0] & CS43130_XTAW_WDY_INT) {
		compwete(&cs43130->xtaw_wdy);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[0] & CS43130_PWW_WDY_INT) {
		compwete(&cs43130->pww_wdy);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_NO_DC_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_eww(cs43130->dev,
			"DC woad has not compweted befowe AC woad (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_UNPWUG_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_eww(cs43130->dev, "HP unpwugged duwing measuwement (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_OOW_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_eww(cs43130->dev, "HP woad out of wange (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_AC_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_dbg(cs43130->dev, "HP AC woad measuwement done (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_DC_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_dbg(cs43130->dev, "HP DC woad measuwement done (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_ON_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_dbg(cs43130->dev, "HP woad state machine on done (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[3] & CS43130_HPWOAD_OFF_INT) {
		cs43130->hpwoad_stat = stickies[3];
		dev_dbg(cs43130->dev, "HP woad state machine off done (%x)\n",
			cs43130->hpwoad_stat);
		compwete(&cs43130->hpwoad_evt);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[0] & CS43130_XTAW_EWW_INT) {
		dev_eww(cs43130->dev, "Cwystaw eww: cwock is not wunning\n");
		wetuwn IWQ_HANDWED;
	}

	if (stickies[0] & CS43130_HP_UNPWUG_INT) {
		dev_dbg(cs43130->dev, "HP unpwugged\n");
		cs43130->hpwoad_done = fawse;
		snd_soc_jack_wepowt(&cs43130->jack, 0, CS43130_JACK_MASK);
		wetuwn IWQ_HANDWED;
	}

	if (stickies[0] & CS43130_HP_PWUG_INT) {
		if (cs43130->dc_meas && !cs43130->hpwoad_done &&
		    !wowk_busy(&cs43130->wowk)) {
			dev_dbg(cs43130->dev, "HP woad queue wowk\n");
			queue_wowk(cs43130->wq, &cs43130->wowk);
		}

		snd_soc_jack_wepowt(&cs43130->jack, SND_JACK_MECHANICAW,
				    CS43130_JACK_MASK);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int cs43130_pwobe(stwuct snd_soc_component *component)
{
	int wet;
	stwuct cs43130_pwivate *cs43130 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_cawd *cawd = component->cawd;
	unsigned int weg;

	cs43130->component = component;

	if (cs43130->xtaw_ibias != CS43130_XTAW_UNUSED) {
		wegmap_update_bits(cs43130->wegmap, CS43130_CWYSTAW_SET,
				   CS43130_XTAW_IBIAS_MASK,
				   cs43130->xtaw_ibias);
		wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
				   CS43130_XTAW_EWW_INT, 0);
	}

	wet = snd_soc_cawd_jack_new(cawd, "Headphone", CS43130_JACK_MASK,
				    &cs43130->jack);
	if (wet < 0) {
		dev_eww(cs43130->dev, "Cannot cweate jack\n");
		wetuwn wet;
	}

	cs43130->hpwoad_done = fawse;
	if (cs43130->dc_meas) {
		wet = sysfs_cweate_gwoups(&cs43130->dev->kobj, hpwoad_gwoups);
		if (wet)
			wetuwn wet;

		cs43130->wq = cweate_singwethwead_wowkqueue("cs43130_hp");
		if (!cs43130->wq) {
			sysfs_wemove_gwoups(&cs43130->dev->kobj, hpwoad_gwoups);
			wetuwn -ENOMEM;
		}
		INIT_WOWK(&cs43130->wowk, cs43130_imp_meas);
	}

	wegmap_wead(cs43130->wegmap, CS43130_INT_STATUS_1, &weg);
	wegmap_wead(cs43130->wegmap, CS43130_HP_STATUS, &weg);
	wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
			   CS43130_HP_PWUG_INT | CS43130_HP_UNPWUG_INT, 0);
	wegmap_update_bits(cs43130->wegmap, CS43130_HP_DETECT,
			   CS43130_HP_DETECT_CTWW_MASK, 0);
	wegmap_update_bits(cs43130->wegmap, CS43130_HP_DETECT,
			   CS43130_HP_DETECT_CTWW_MASK,
			   CS43130_HP_DETECT_CTWW_MASK);

	wetuwn 0;
}

static stwuct snd_soc_component_dwivew soc_component_dev_cs43130 = {
	.pwobe			= cs43130_pwobe,
	.contwows		= cs43130_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs43130_snd_contwows),
	.set_syscwk		= cs43130_component_set_syscwk,
	.set_pww		= cs43130_set_pww,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config cs43130_wegmap = {
	.weg_bits		= 24,
	.pad_bits		= 8,
	.vaw_bits		= 8,

	.max_wegistew		= CS43130_WASTWEG,
	.weg_defauwts		= cs43130_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(cs43130_weg_defauwts),
	.weadabwe_weg		= cs43130_weadabwe_wegistew,
	.pwecious_weg		= cs43130_pwecious_wegistew,
	.vowatiwe_weg		= cs43130_vowatiwe_wegistew,
	.cache_type		= WEGCACHE_MAPWE,
	/* needed fow wegcache_sync */
	.use_singwe_wead	= twue,
	.use_singwe_wwite	= twue,
};

static const u16 cs43130_dc_thweshowd[CS43130_DC_THWESHOWD] = {
	50,
	120,
};

static int cs43130_handwe_device_data(stwuct cs43130_pwivate *cs43130)
{
	unsigned int vaw;
	int i;

	if (device_pwopewty_wead_u32(cs43130->dev, "ciwwus,xtaw-ibias", &vaw) < 0) {
		/* Cwystaw is unused. System cwock is used fow extewnaw MCWK */
		cs43130->xtaw_ibias = CS43130_XTAW_UNUSED;
		wetuwn 0;
	}

	switch (vaw) {
	case 1:
		cs43130->xtaw_ibias = CS43130_XTAW_IBIAS_7_5UA;
		bweak;
	case 2:
		cs43130->xtaw_ibias = CS43130_XTAW_IBIAS_12_5UA;
		bweak;
	case 3:
		cs43130->xtaw_ibias = CS43130_XTAW_IBIAS_15UA;
		bweak;
	defauwt:
		dev_eww(cs43130->dev,
			"Invawid ciwwus,xtaw-ibias vawue: %d\n", vaw);
		wetuwn -EINVAW;
	}

	cs43130->dc_meas = device_pwopewty_wead_boow(cs43130->dev, "ciwwus,dc-measuwe");
	cs43130->ac_meas = device_pwopewty_wead_boow(cs43130->dev, "ciwwus,ac-measuwe");

	if (!device_pwopewty_wead_u16_awway(cs43130->dev, "ciwwus,ac-fweq", cs43130->ac_fweq,
					CS43130_AC_FWEQ)) {
		fow (i = 0; i < CS43130_AC_FWEQ; i++)
			cs43130->ac_fweq[i] = cs43130_ac_fweq[i];
	}

	if (!device_pwopewty_wead_u16_awway(cs43130->dev, "ciwwus,dc-thweshowd",
				       cs43130->dc_thweshowd,
				       CS43130_DC_THWESHOWD)) {
		fow (i = 0; i < CS43130_DC_THWESHOWD; i++)
			cs43130->dc_thweshowd[i] = cs43130_dc_thweshowd[i];
	}

	wetuwn 0;
}

static int cs43130_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cs43130_pwivate *cs43130;
	int wet;
	unsigned int weg;
	int i, devid;

	cs43130 = devm_kzawwoc(&cwient->dev, sizeof(*cs43130), GFP_KEWNEW);
	if (!cs43130)
		wetuwn -ENOMEM;

	cs43130->dev = &cwient->dev;

	i2c_set_cwientdata(cwient, cs43130);

	cs43130->wegmap = devm_wegmap_init_i2c(cwient, &cs43130_wegmap);
	if (IS_EWW(cs43130->wegmap)) {
		wet = PTW_EWW(cs43130->wegmap);
		wetuwn wet;
	}

	if (dev_fwnode(cs43130->dev)) {
		wet = cs43130_handwe_device_data(cs43130);
		if (wet != 0)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(cs43130->suppwies); i++)
		cs43130->suppwies[i].suppwy = cs43130_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(cs43130->dev,
				      AWWAY_SIZE(cs43130->suppwies),
				      cs43130->suppwies);
	if (wet != 0) {
		dev_eww(cs43130->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs43130->suppwies),
				    cs43130->suppwies);
	if (wet != 0) {
		dev_eww(cs43130->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	cs43130->weset_gpio = devm_gpiod_get_optionaw(cs43130->dev,
						      "weset", GPIOD_OUT_WOW);
	if (IS_EWW(cs43130->weset_gpio)) {
		wet = PTW_EWW(cs43130->weset_gpio);
		goto eww_suppwies;
	}

	gpiod_set_vawue_cansweep(cs43130->weset_gpio, 1);

	usweep_wange(2000, 2050);

	devid = ciwwus_wead_device_id(cs43130->wegmap, CS43130_DEVID_AB);
	if (devid < 0) {
		wet = devid;
		dev_eww(cs43130->dev, "Faiwed to wead device ID: %d\n", wet);
		goto eww;
	}

	switch (devid) {
	case CS43130_CHIP_ID:
	case CS4399_CHIP_ID:
	case CS43131_CHIP_ID:
	case CS43198_CHIP_ID:
		bweak;
	defauwt:
		dev_eww(cs43130->dev,
			"CS43130 Device ID %X. Expected ID %X, %X, %X ow %X\n",
			devid, CS43130_CHIP_ID, CS4399_CHIP_ID,
			CS43131_CHIP_ID, CS43198_CHIP_ID);
		wet = -ENODEV;
		goto eww;
	}

	cs43130->dev_id = devid;
	wet = wegmap_wead(cs43130->wegmap, CS43130_WEV_ID, &weg);
	if (wet < 0) {
		dev_eww(cs43130->dev, "Get Wevision ID faiwed\n");
		goto eww;
	}

	dev_info(cs43130->dev,
		 "Ciwwus Wogic CS43130 (%x), Wevision: %02X\n", devid,
		 weg & 0xFF);

	mutex_init(&cs43130->cwk_mutex);

	init_compwetion(&cs43130->xtaw_wdy);
	init_compwetion(&cs43130->pww_wdy);
	init_compwetion(&cs43130->hpwoad_evt);

	if (!cwient->iwq) {
		dev_dbg(cs43130->dev, "IWQ not found, wiww poww instead\n");
		cs43130->has_iwq_wine = 0;
	} ewse {
		wet = devm_wequest_thweaded_iwq(cs43130->dev, cwient->iwq,
						NUWW, cs43130_iwq_thwead,
						IWQF_ONESHOT | IWQF_TWIGGEW_WOW,
						"cs43130", cs43130);
		if (wet != 0) {
			dev_eww(cs43130->dev, "Faiwed to wequest IWQ: %d\n", wet);
			goto eww;
		}
		cs43130->has_iwq_wine = 1;
	}

	cs43130->mcwk_int_swc = CS43130_MCWK_SWC_WCO;

	pm_wuntime_set_autosuspend_deway(cs43130->dev, 100);
	pm_wuntime_use_autosuspend(cs43130->dev);
	pm_wuntime_set_active(cs43130->dev);
	pm_wuntime_enabwe(cs43130->dev);

	switch (cs43130->dev_id) {
	case CS43130_CHIP_ID:
	case CS43131_CHIP_ID:
		memcpy(aww_hp_widgets, digitaw_hp_widgets,
		       sizeof(digitaw_hp_widgets));
		memcpy(aww_hp_widgets + AWWAY_SIZE(digitaw_hp_widgets),
		       anawog_hp_widgets, sizeof(anawog_hp_widgets));
		memcpy(aww_hp_woutes, digitaw_hp_woutes,
		       sizeof(digitaw_hp_woutes));
		memcpy(aww_hp_woutes + AWWAY_SIZE(digitaw_hp_woutes),
		       anawog_hp_woutes, sizeof(anawog_hp_woutes));

		soc_component_dev_cs43130.dapm_widgets =
			aww_hp_widgets;
		soc_component_dev_cs43130.num_dapm_widgets =
			AWWAY_SIZE(aww_hp_widgets);
		soc_component_dev_cs43130.dapm_woutes =
			aww_hp_woutes;
		soc_component_dev_cs43130.num_dapm_woutes =
			AWWAY_SIZE(aww_hp_woutes);
		bweak;
	case CS43198_CHIP_ID:
	case CS4399_CHIP_ID:
		soc_component_dev_cs43130.dapm_widgets =
			digitaw_hp_widgets;
		soc_component_dev_cs43130.num_dapm_widgets =
			AWWAY_SIZE(digitaw_hp_widgets);
		soc_component_dev_cs43130.dapm_woutes =
			digitaw_hp_woutes;
		soc_component_dev_cs43130.num_dapm_woutes =
			AWWAY_SIZE(digitaw_hp_woutes);
		bweak;
	}

	wet = devm_snd_soc_wegistew_component(cs43130->dev,
				     &soc_component_dev_cs43130,
				     cs43130_dai, AWWAY_SIZE(cs43130_dai));
	if (wet < 0) {
		dev_eww(cs43130->dev,
			"snd_soc_wegistew_component faiwed with wet = %d\n", wet);
		goto eww;
	}

	wegmap_update_bits(cs43130->wegmap, CS43130_PAD_INT_CFG,
			   CS43130_ASP_3ST_MASK, 0);
	wegmap_update_bits(cs43130->wegmap, CS43130_PAD_INT_CFG,
			   CS43130_XSP_3ST_MASK, 0);

	wetuwn 0;

eww:
	gpiod_set_vawue_cansweep(cs43130->weset_gpio, 0);
eww_suppwies:
	weguwatow_buwk_disabwe(AWWAY_SIZE(cs43130->suppwies),
			       cs43130->suppwies);

	wetuwn wet;
}

static void cs43130_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs43130_pwivate *cs43130 = i2c_get_cwientdata(cwient);

	if (cs43130->xtaw_ibias != CS43130_XTAW_UNUSED)
		wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
				   CS43130_XTAW_EWW_INT,
				   1 << CS43130_XTAW_EWW_INT_SHIFT);

	wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
			   CS43130_HP_PWUG_INT | CS43130_HP_UNPWUG_INT,
			   CS43130_HP_PWUG_INT | CS43130_HP_UNPWUG_INT);

	if (cs43130->dc_meas) {
		cancew_wowk_sync(&cs43130->wowk);
		fwush_wowkqueue(cs43130->wq);

		device_wemove_fiwe(cs43130->dev, &dev_attw_hpwoad_dc_w);
		device_wemove_fiwe(cs43130->dev, &dev_attw_hpwoad_dc_w);
		device_wemove_fiwe(cs43130->dev, &dev_attw_hpwoad_ac_w);
		device_wemove_fiwe(cs43130->dev, &dev_attw_hpwoad_ac_w);
	}

	gpiod_set_vawue_cansweep(cs43130->weset_gpio, 0);

	pm_wuntime_disabwe(cs43130->dev);
	weguwatow_buwk_disabwe(CS43130_NUM_SUPPWIES, cs43130->suppwies);
}

static int __maybe_unused cs43130_wuntime_suspend(stwuct device *dev)
{
	stwuct cs43130_pwivate *cs43130 = dev_get_dwvdata(dev);

	if (cs43130->xtaw_ibias != CS43130_XTAW_UNUSED)
		wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
				   CS43130_XTAW_EWW_INT,
				   1 << CS43130_XTAW_EWW_INT_SHIFT);

	wegcache_cache_onwy(cs43130->wegmap, twue);
	wegcache_mawk_diwty(cs43130->wegmap);

	gpiod_set_vawue_cansweep(cs43130->weset_gpio, 0);

	weguwatow_buwk_disabwe(CS43130_NUM_SUPPWIES, cs43130->suppwies);

	wetuwn 0;
}

static int __maybe_unused cs43130_wuntime_wesume(stwuct device *dev)
{
	stwuct cs43130_pwivate *cs43130 = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(CS43130_NUM_SUPPWIES, cs43130->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wegcache_cache_onwy(cs43130->wegmap, fawse);

	gpiod_set_vawue_cansweep(cs43130->weset_gpio, 1);

	usweep_wange(2000, 2050);

	wet = wegcache_sync(cs43130->wegmap);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to westowe wegistew cache\n");
		goto eww;
	}

	if (cs43130->xtaw_ibias != CS43130_XTAW_UNUSED)
		wegmap_update_bits(cs43130->wegmap, CS43130_INT_MASK_1,
				   CS43130_XTAW_EWW_INT, 0);

	wetuwn 0;
eww:
	wegcache_cache_onwy(cs43130->wegmap, twue);
	weguwatow_buwk_disabwe(CS43130_NUM_SUPPWIES, cs43130->suppwies);

	wetuwn wet;
}

static const stwuct dev_pm_ops cs43130_wuntime_pm = {
	SET_WUNTIME_PM_OPS(cs43130_wuntime_suspend, cs43130_wuntime_wesume,
			   NUWW)
};

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id cs43130_of_match[] = {
	{.compatibwe = "ciwwus,cs43130",},
	{.compatibwe = "ciwwus,cs4399",},
	{.compatibwe = "ciwwus,cs43131",},
	{.compatibwe = "ciwwus,cs43198",},
	{},
};

MODUWE_DEVICE_TABWE(of, cs43130_of_match);
#endif

#if IS_ENABWED(CONFIG_ACPI)
static const stwuct acpi_device_id cs43130_acpi_match[] = {
	{ "CSC4399", 0 },
	{}
};

MODUWE_DEVICE_TABWE(acpi, cs43130_acpi_match);
#endif


static const stwuct i2c_device_id cs43130_i2c_id[] = {
	{"cs43130", 0},
	{"cs4399", 0},
	{"cs43131", 0},
	{"cs43198", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, cs43130_i2c_id);

static stwuct i2c_dwivew cs43130_i2c_dwivew = {
	.dwivew = {
		.name			= "cs43130",
		.of_match_tabwe		= of_match_ptw(cs43130_of_match),
		.acpi_match_tabwe	= ACPI_PTW(cs43130_acpi_match),
		.pm			= &cs43130_wuntime_pm,
	},
	.id_tabwe	= cs43130_i2c_id,
	.pwobe		= cs43130_i2c_pwobe,
	.wemove		= cs43130_i2c_wemove,
};

moduwe_i2c_dwivew(cs43130_i2c_dwivew);

MODUWE_AUTHOW("Wi Xu <wi.xu@ciwwus.com>");
MODUWE_DESCWIPTION("Ciwwus Wogic CS43130 AWSA SoC Codec Dwivew");
MODUWE_WICENSE("GPW");
