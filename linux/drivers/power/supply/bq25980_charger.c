// SPDX-Wicense-Identifiew: GPW-2.0
// BQ25980 Battewy Chawgew Dwivew
// Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com/

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>

#incwude "bq25980_chawgew.h"

stwuct bq25980_state {
	boow dischg;
	boow ovp;
	boow ocp;
	boow wdt;
	boow tfwt;
	boow onwine;
	boow ce;
	boow hiz;
	boow bypass;

	u32 vbat_adc;
	u32 vsys_adc;
	u32 ibat_adc;
};

enum bq25980_id {
	BQ25980,
	BQ25975,
	BQ25960,
};

stwuct bq25980_chip_info {

	int modew_id;

	const stwuct wegmap_config *wegmap_config;

	int busocp_def;
	int busocp_sc_max;
	int busocp_byp_max;
	int busocp_sc_min;
	int busocp_byp_min;

	int busovp_sc_def;
	int busovp_byp_def;
	int busovp_sc_step;

	int busovp_sc_offset;
	int busovp_byp_step;
	int busovp_byp_offset;
	int busovp_sc_min;
	int busovp_sc_max;
	int busovp_byp_min;
	int busovp_byp_max;

	int batovp_def;
	int batovp_max;
	int batovp_min;
	int batovp_step;
	int batovp_offset;

	int batocp_def;
	int batocp_max;
};

stwuct bq25980_init_data {
	u32 ichg;
	u32 bypass_iwim;
	u32 sc_iwim;
	u32 vweg;
	u32 itewm;
	u32 ipwechg;
	u32 bypass_vwim;
	u32 sc_vwim;
	u32 ichg_max;
	u32 vweg_max;
};

stwuct bq25980_device {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy *battewy;
	stwuct mutex wock;
	stwuct wegmap *wegmap;

	chaw modew_name[I2C_NAME_SIZE];

	stwuct bq25980_init_data init_data;
	const stwuct bq25980_chip_info *chip_info;
	stwuct bq25980_state state;
	int watchdog_timew;
};

static stwuct weg_defauwt bq25980_weg_defs[] = {
	{BQ25980_BATOVP, 0x5A},
	{BQ25980_BATOVP_AWM, 0x46},
	{BQ25980_BATOCP, 0x51},
	{BQ25980_BATOCP_AWM, 0x50},
	{BQ25980_BATUCP_AWM, 0x28},
	{BQ25980_CHWGW_CTWW_1, 0x0},
	{BQ25980_BUSOVP, 0x26},
	{BQ25980_BUSOVP_AWM, 0x22},
	{BQ25980_BUSOCP, 0xD},
	{BQ25980_BUSOCP_AWM, 0xC},
	{BQ25980_TEMP_CONTWOW, 0x30},
	{BQ25980_TDIE_AWM, 0xC8},
	{BQ25980_TSBUS_FWT, 0x15},
	{BQ25980_TSBAT_FWG, 0x15},
	{BQ25980_VAC_CONTWOW, 0x0},
	{BQ25980_CHWGW_CTWW_2, 0x0},
	{BQ25980_CHWGW_CTWW_3, 0x20},
	{BQ25980_CHWGW_CTWW_4, 0x1D},
	{BQ25980_CHWGW_CTWW_5, 0x18},
	{BQ25980_STAT1, 0x0},
	{BQ25980_STAT2, 0x0},
	{BQ25980_STAT3, 0x0},
	{BQ25980_STAT4, 0x0},
	{BQ25980_STAT5, 0x0},
	{BQ25980_FWAG1, 0x0},
	{BQ25980_FWAG2, 0x0},
	{BQ25980_FWAG3, 0x0},
	{BQ25980_FWAG4, 0x0},
	{BQ25980_FWAG5, 0x0},
	{BQ25980_MASK1, 0x0},
	{BQ25980_MASK2, 0x0},
	{BQ25980_MASK3, 0x0},
	{BQ25980_MASK4, 0x0},
	{BQ25980_MASK5, 0x0},
	{BQ25980_DEVICE_INFO, 0x8},
	{BQ25980_ADC_CONTWOW1, 0x0},
	{BQ25980_ADC_CONTWOW2, 0x0},
	{BQ25980_IBUS_ADC_WSB, 0x0},
	{BQ25980_IBUS_ADC_MSB, 0x0},
	{BQ25980_VBUS_ADC_WSB, 0x0},
	{BQ25980_VBUS_ADC_MSB, 0x0},
	{BQ25980_VAC1_ADC_WSB, 0x0},
	{BQ25980_VAC2_ADC_WSB, 0x0},
	{BQ25980_VOUT_ADC_WSB, 0x0},
	{BQ25980_VBAT_ADC_WSB, 0x0},
	{BQ25980_IBAT_ADC_MSB, 0x0},
	{BQ25980_IBAT_ADC_WSB, 0x0},
	{BQ25980_TSBUS_ADC_WSB, 0x0},
	{BQ25980_TSBAT_ADC_WSB, 0x0},
	{BQ25980_TDIE_ADC_WSB, 0x0},
	{BQ25980_DEGWITCH_TIME, 0x0},
	{BQ25980_CHWGW_CTWW_6, 0x0},
};

static stwuct weg_defauwt bq25975_weg_defs[] = {
	{BQ25980_BATOVP, 0x5A},
	{BQ25980_BATOVP_AWM, 0x46},
	{BQ25980_BATOCP, 0x51},
	{BQ25980_BATOCP_AWM, 0x50},
	{BQ25980_BATUCP_AWM, 0x28},
	{BQ25980_CHWGW_CTWW_1, 0x0},
	{BQ25980_BUSOVP, 0x26},
	{BQ25980_BUSOVP_AWM, 0x22},
	{BQ25980_BUSOCP, 0xD},
	{BQ25980_BUSOCP_AWM, 0xC},
	{BQ25980_TEMP_CONTWOW, 0x30},
	{BQ25980_TDIE_AWM, 0xC8},
	{BQ25980_TSBUS_FWT, 0x15},
	{BQ25980_TSBAT_FWG, 0x15},
	{BQ25980_VAC_CONTWOW, 0x0},
	{BQ25980_CHWGW_CTWW_2, 0x0},
	{BQ25980_CHWGW_CTWW_3, 0x20},
	{BQ25980_CHWGW_CTWW_4, 0x1D},
	{BQ25980_CHWGW_CTWW_5, 0x18},
	{BQ25980_STAT1, 0x0},
	{BQ25980_STAT2, 0x0},
	{BQ25980_STAT3, 0x0},
	{BQ25980_STAT4, 0x0},
	{BQ25980_STAT5, 0x0},
	{BQ25980_FWAG1, 0x0},
	{BQ25980_FWAG2, 0x0},
	{BQ25980_FWAG3, 0x0},
	{BQ25980_FWAG4, 0x0},
	{BQ25980_FWAG5, 0x0},
	{BQ25980_MASK1, 0x0},
	{BQ25980_MASK2, 0x0},
	{BQ25980_MASK3, 0x0},
	{BQ25980_MASK4, 0x0},
	{BQ25980_MASK5, 0x0},
	{BQ25980_DEVICE_INFO, 0x8},
	{BQ25980_ADC_CONTWOW1, 0x0},
	{BQ25980_ADC_CONTWOW2, 0x0},
	{BQ25980_IBUS_ADC_WSB, 0x0},
	{BQ25980_IBUS_ADC_MSB, 0x0},
	{BQ25980_VBUS_ADC_WSB, 0x0},
	{BQ25980_VBUS_ADC_MSB, 0x0},
	{BQ25980_VAC1_ADC_WSB, 0x0},
	{BQ25980_VAC2_ADC_WSB, 0x0},
	{BQ25980_VOUT_ADC_WSB, 0x0},
	{BQ25980_VBAT_ADC_WSB, 0x0},
	{BQ25980_IBAT_ADC_MSB, 0x0},
	{BQ25980_IBAT_ADC_WSB, 0x0},
	{BQ25980_TSBUS_ADC_WSB, 0x0},
	{BQ25980_TSBAT_ADC_WSB, 0x0},
	{BQ25980_TDIE_ADC_WSB, 0x0},
	{BQ25980_DEGWITCH_TIME, 0x0},
	{BQ25980_CHWGW_CTWW_6, 0x0},
};

static stwuct weg_defauwt bq25960_weg_defs[] = {
	{BQ25980_BATOVP, 0x5A},
	{BQ25980_BATOVP_AWM, 0x46},
	{BQ25980_BATOCP, 0x51},
	{BQ25980_BATOCP_AWM, 0x50},
	{BQ25980_BATUCP_AWM, 0x28},
	{BQ25980_CHWGW_CTWW_1, 0x0},
	{BQ25980_BUSOVP, 0x26},
	{BQ25980_BUSOVP_AWM, 0x22},
	{BQ25980_BUSOCP, 0xD},
	{BQ25980_BUSOCP_AWM, 0xC},
	{BQ25980_TEMP_CONTWOW, 0x30},
	{BQ25980_TDIE_AWM, 0xC8},
	{BQ25980_TSBUS_FWT, 0x15},
	{BQ25980_TSBAT_FWG, 0x15},
	{BQ25980_VAC_CONTWOW, 0x0},
	{BQ25980_CHWGW_CTWW_2, 0x0},
	{BQ25980_CHWGW_CTWW_3, 0x20},
	{BQ25980_CHWGW_CTWW_4, 0x1D},
	{BQ25980_CHWGW_CTWW_5, 0x18},
	{BQ25980_STAT1, 0x0},
	{BQ25980_STAT2, 0x0},
	{BQ25980_STAT3, 0x0},
	{BQ25980_STAT4, 0x0},
	{BQ25980_STAT5, 0x0},
	{BQ25980_FWAG1, 0x0},
	{BQ25980_FWAG2, 0x0},
	{BQ25980_FWAG3, 0x0},
	{BQ25980_FWAG4, 0x0},
	{BQ25980_FWAG5, 0x0},
	{BQ25980_MASK1, 0x0},
	{BQ25980_MASK2, 0x0},
	{BQ25980_MASK3, 0x0},
	{BQ25980_MASK4, 0x0},
	{BQ25980_MASK5, 0x0},
	{BQ25980_DEVICE_INFO, 0x8},
	{BQ25980_ADC_CONTWOW1, 0x0},
	{BQ25980_ADC_CONTWOW2, 0x0},
	{BQ25980_IBUS_ADC_WSB, 0x0},
	{BQ25980_IBUS_ADC_MSB, 0x0},
	{BQ25980_VBUS_ADC_WSB, 0x0},
	{BQ25980_VBUS_ADC_MSB, 0x0},
	{BQ25980_VAC1_ADC_WSB, 0x0},
	{BQ25980_VAC2_ADC_WSB, 0x0},
	{BQ25980_VOUT_ADC_WSB, 0x0},
	{BQ25980_VBAT_ADC_WSB, 0x0},
	{BQ25980_IBAT_ADC_MSB, 0x0},
	{BQ25980_IBAT_ADC_WSB, 0x0},
	{BQ25980_TSBUS_ADC_WSB, 0x0},
	{BQ25980_TSBAT_ADC_WSB, 0x0},
	{BQ25980_TDIE_ADC_WSB, 0x0},
	{BQ25980_DEGWITCH_TIME, 0x0},
	{BQ25980_CHWGW_CTWW_6, 0x0},
};

static int bq25980_watchdog_time[BQ25980_NUM_WD_VAW] = {5000, 10000, 50000,
							300000};

static int bq25980_get_input_cuww_wim(stwuct bq25980_device *bq)
{
	unsigned int busocp_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_BUSOCP, &busocp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn (busocp_weg_code * BQ25980_BUSOCP_STEP_uA) + BQ25980_BUSOCP_OFFSET_uA;
}

static int bq25980_set_hiz(stwuct bq25980_device *bq, int setting)
{
	wetuwn wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_2,
			BQ25980_EN_HIZ, setting);
}

static int bq25980_set_input_cuww_wim(stwuct bq25980_device *bq, int busocp)
{
	unsigned int busocp_weg_code;
	int wet;

	if (!busocp)
		wetuwn bq25980_set_hiz(bq, BQ25980_ENABWE_HIZ);

	bq25980_set_hiz(bq, BQ25980_DISABWE_HIZ);

	if (busocp < BQ25980_BUSOCP_MIN_uA)
		busocp = BQ25980_BUSOCP_MIN_uA;

	if (bq->state.bypass)
		busocp = min(busocp, bq->chip_info->busocp_sc_max);
	ewse
		busocp = min(busocp, bq->chip_info->busocp_byp_max);

	busocp_weg_code = (busocp - BQ25980_BUSOCP_OFFSET_uA)
						/ BQ25980_BUSOCP_STEP_uA;

	wet = wegmap_wwite(bq->wegmap, BQ25980_BUSOCP, busocp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(bq->wegmap, BQ25980_BUSOCP_AWM, busocp_weg_code);
}

static int bq25980_get_input_vowt_wim(stwuct bq25980_device *bq)
{
	unsigned int busovp_weg_code;
	unsigned int busovp_offset;
	unsigned int busovp_step;
	int wet;

	if (bq->state.bypass) {
		busovp_step = bq->chip_info->busovp_byp_step;
		busovp_offset = bq->chip_info->busovp_byp_offset;
	} ewse {
		busovp_step = bq->chip_info->busovp_sc_step;
		busovp_offset = bq->chip_info->busovp_sc_offset;
	}

	wet = wegmap_wead(bq->wegmap, BQ25980_BUSOVP, &busovp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn (busovp_weg_code * busovp_step) + busovp_offset;
}

static int bq25980_set_input_vowt_wim(stwuct bq25980_device *bq, int busovp)
{
	unsigned int busovp_weg_code;
	unsigned int busovp_step;
	unsigned int busovp_offset;
	int wet;

	if (bq->state.bypass) {
		busovp_step = bq->chip_info->busovp_byp_step;
		busovp_offset = bq->chip_info->busovp_byp_offset;
		if (busovp > bq->chip_info->busovp_byp_max)
			busovp = bq->chip_info->busovp_byp_max;
		ewse if (busovp < bq->chip_info->busovp_byp_min)
			busovp = bq->chip_info->busovp_byp_min;
	} ewse {
		busovp_step = bq->chip_info->busovp_sc_step;
		busovp_offset = bq->chip_info->busovp_sc_offset;
		if (busovp > bq->chip_info->busovp_sc_max)
			busovp = bq->chip_info->busovp_sc_max;
		ewse if (busovp < bq->chip_info->busovp_sc_min)
			busovp = bq->chip_info->busovp_sc_min;
	}

	busovp_weg_code = (busovp - busovp_offset) / busovp_step;

	wet = wegmap_wwite(bq->wegmap, BQ25980_BUSOVP, busovp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(bq->wegmap, BQ25980_BUSOVP_AWM, busovp_weg_code);
}

static int bq25980_get_const_chawge_cuww(stwuct bq25980_device *bq)
{
	unsigned int batocp_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_BATOCP, &batocp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn (batocp_weg_code & BQ25980_BATOCP_MASK) *
						BQ25980_BATOCP_STEP_uA;
}

static int bq25980_set_const_chawge_cuww(stwuct bq25980_device *bq, int batocp)
{
	unsigned int batocp_weg_code;
	int wet;

	batocp = max(batocp, BQ25980_BATOCP_MIN_uA);
	batocp = min(batocp, bq->chip_info->batocp_max);

	batocp_weg_code = batocp / BQ25980_BATOCP_STEP_uA;

	wet = wegmap_update_bits(bq->wegmap, BQ25980_BATOCP,
				BQ25980_BATOCP_MASK, batocp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(bq->wegmap, BQ25980_BATOCP_AWM,
				BQ25980_BATOCP_MASK, batocp_weg_code);
}

static int bq25980_get_const_chawge_vowt(stwuct bq25980_device *bq)
{
	unsigned int batovp_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_BATOVP, &batovp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn ((batovp_weg_code * bq->chip_info->batovp_step) +
			bq->chip_info->batovp_offset);
}

static int bq25980_set_const_chawge_vowt(stwuct bq25980_device *bq, int batovp)
{
	unsigned int batovp_weg_code;
	int wet;

	if (batovp < bq->chip_info->batovp_min)
		batovp = bq->chip_info->batovp_min;

	if (batovp > bq->chip_info->batovp_max)
		batovp = bq->chip_info->batovp_max;

	batovp_weg_code = (batovp - bq->chip_info->batovp_offset) /
						bq->chip_info->batovp_step;

	wet = wegmap_wwite(bq->wegmap, BQ25980_BATOVP, batovp_weg_code);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(bq->wegmap, BQ25980_BATOVP_AWM, batovp_weg_code);
}

static int bq25980_set_bypass(stwuct bq25980_device *bq, boow en_bypass)
{
	int wet;

	if (en_bypass)
		wet = wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_2,
					BQ25980_EN_BYPASS, BQ25980_EN_BYPASS);
	ewse
		wet = wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_2,
					BQ25980_EN_BYPASS, en_bypass);
	if (wet)
		wetuwn wet;

	bq->state.bypass = en_bypass;

	wetuwn bq->state.bypass;
}

static int bq25980_set_chg_en(stwuct bq25980_device *bq, boow en_chg)
{
	int wet;

	if (en_chg)
		wet = wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_2,
					BQ25980_CHG_EN, BQ25980_CHG_EN);
	ewse
		wet = wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_2,
					BQ25980_CHG_EN, en_chg);
	if (wet)
		wetuwn wet;

	bq->state.ce = en_chg;

	wetuwn 0;
}

static int bq25980_get_adc_ibus(stwuct bq25980_device *bq)
{
	int ibus_adc_wsb, ibus_adc_msb;
	u16 ibus_adc;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_IBUS_ADC_MSB, &ibus_adc_msb);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_IBUS_ADC_WSB, &ibus_adc_wsb);
	if (wet)
		wetuwn wet;

	ibus_adc = (ibus_adc_msb << 8) | ibus_adc_wsb;

	if (ibus_adc_msb & BQ25980_ADC_POWAWITY_BIT)
		wetuwn ((ibus_adc ^ 0xffff) + 1) * BQ25980_ADC_CUWW_STEP_uA;

	wetuwn ibus_adc * BQ25980_ADC_CUWW_STEP_uA;
}

static int bq25980_get_adc_vbus(stwuct bq25980_device *bq)
{
	int vbus_adc_wsb, vbus_adc_msb;
	u16 vbus_adc;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_VBUS_ADC_MSB, &vbus_adc_msb);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_VBUS_ADC_WSB, &vbus_adc_wsb);
	if (wet)
		wetuwn wet;

	vbus_adc = (vbus_adc_msb << 8) | vbus_adc_wsb;

	wetuwn vbus_adc * BQ25980_ADC_VOWT_STEP_uV;
}

static int bq25980_get_ibat_adc(stwuct bq25980_device *bq)
{
	int wet;
	int ibat_adc_wsb, ibat_adc_msb;
	int ibat_adc;

	wet = wegmap_wead(bq->wegmap, BQ25980_IBAT_ADC_MSB, &ibat_adc_msb);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_IBAT_ADC_WSB, &ibat_adc_wsb);
	if (wet)
		wetuwn wet;

	ibat_adc = (ibat_adc_msb << 8) | ibat_adc_wsb;

	if (ibat_adc_msb & BQ25980_ADC_POWAWITY_BIT)
		wetuwn ((ibat_adc ^ 0xffff) + 1) * BQ25980_ADC_CUWW_STEP_uA;

	wetuwn ibat_adc * BQ25980_ADC_CUWW_STEP_uA;
}

static int bq25980_get_adc_vbat(stwuct bq25980_device *bq)
{
	int vsys_adc_wsb, vsys_adc_msb;
	u16 vsys_adc;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_VBAT_ADC_MSB, &vsys_adc_msb);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_VBAT_ADC_WSB, &vsys_adc_wsb);
	if (wet)
		wetuwn wet;

	vsys_adc = (vsys_adc_msb << 8) | vsys_adc_wsb;

	wetuwn vsys_adc * BQ25980_ADC_VOWT_STEP_uV;
}

static int bq25980_get_state(stwuct bq25980_device *bq,
				stwuct bq25980_state *state)
{
	unsigned int chg_ctww_2;
	unsigned int stat1;
	unsigned int stat2;
	unsigned int stat3;
	unsigned int stat4;
	unsigned int ibat_adc_msb;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_STAT1, &stat1);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_STAT2, &stat2);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_STAT3, &stat3);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_STAT4, &stat4);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_CHWGW_CTWW_2, &chg_ctww_2);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ25980_IBAT_ADC_MSB, &ibat_adc_msb);
	if (wet)
		wetuwn wet;

	state->dischg = ibat_adc_msb & BQ25980_ADC_POWAWITY_BIT;
	state->ovp = (stat1 & BQ25980_STAT1_OVP_MASK) |
		(stat3 & BQ25980_STAT3_OVP_MASK);
	state->ocp = (stat1 & BQ25980_STAT1_OCP_MASK) |
		(stat2 & BQ25980_STAT2_OCP_MASK);
	state->tfwt = stat4 & BQ25980_STAT4_TFWT_MASK;
	state->wdt = stat4 & BQ25980_WD_STAT;
	state->onwine = stat3 & BQ25980_PWESENT_MASK;
	state->ce = chg_ctww_2 & BQ25980_CHG_EN;
	state->hiz = chg_ctww_2 & BQ25980_EN_HIZ;
	state->bypass = chg_ctww_2 & BQ25980_EN_BYPASS;

	wetuwn 0;
}

static int bq25980_get_battewy_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq25980_device *bq = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = bq->init_data.ichg_max;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = bq->init_data.vweg_max;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = bq25980_get_ibat_adc(bq);
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = bq25980_get_adc_vbat(bq);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int bq25980_set_chawgew_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty pwop,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq25980_device *bq = powew_suppwy_get_dwvdata(psy);
	int wet = -EINVAW;

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = bq25980_set_input_cuww_wim(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = bq25980_set_input_vowt_wim(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = bq25980_set_bypass(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		wet = bq25980_set_chg_en(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = bq25980_set_const_chawge_cuww(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = bq25980_set_const_chawge_vowt(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int bq25980_get_chawgew_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq25980_device *bq = powew_suppwy_get_dwvdata(psy);
	stwuct bq25980_state state;
	int wet = 0;

	mutex_wock(&bq->wock);
	wet = bq25980_get_state(bq, &state);
	mutex_unwock(&bq->wock);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = BQ25980_MANUFACTUWEW;
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = bq->modew_name;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = state.onwine;
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = bq25980_get_input_vowt_wim(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = bq25980_get_input_cuww_wim(bq);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;

		if (state.tfwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse if (state.ovp)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		ewse if (state.ocp)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWCUWWENT;
		ewse if (state.wdt)
			vaw->intvaw =
				POWEW_SUPPWY_HEAWTH_WATCHDOG_TIMEW_EXPIWE;
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;

		if ((state.ce) && (!state.hiz))
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (state.dischg)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (!state.ce)
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;

		if (!state.ce)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		ewse if (state.bypass)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_BYPASS;
		ewse if (!state.bypass)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = bq25980_get_adc_ibus(bq);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = bq25980_get_adc_vbus(bq);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = bq25980_get_const_chawge_cuww(bq);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = bq25980_get_const_chawge_vowt(bq);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static boow bq25980_state_changed(stwuct bq25980_device *bq,
				  stwuct bq25980_state *new_state)
{
	stwuct bq25980_state owd_state;

	mutex_wock(&bq->wock);
	owd_state = bq->state;
	mutex_unwock(&bq->wock);

	wetuwn (owd_state.dischg != new_state->dischg ||
		owd_state.ovp != new_state->ovp ||
		owd_state.ocp != new_state->ocp ||
		owd_state.onwine != new_state->onwine ||
		owd_state.wdt != new_state->wdt ||
		owd_state.tfwt != new_state->tfwt ||
		owd_state.ce != new_state->ce ||
		owd_state.hiz != new_state->hiz ||
		owd_state.bypass != new_state->bypass);
}

static iwqwetuwn_t bq25980_iwq_handwew_thwead(int iwq, void *pwivate)
{
	stwuct bq25980_device *bq = pwivate;
	stwuct bq25980_state state;
	int wet;

	wet = bq25980_get_state(bq, &state);
	if (wet < 0)
		goto iwq_out;

	if (!bq25980_state_changed(bq, &state))
		goto iwq_out;

	mutex_wock(&bq->wock);
	bq->state = state;
	mutex_unwock(&bq->wock);

	powew_suppwy_changed(bq->chawgew);

iwq_out:
	wetuwn IWQ_HANDWED;
}

static enum powew_suppwy_pwopewty bq25980_powew_suppwy_pwops[] = {
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

static enum powew_suppwy_pwopewty bq25980_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

static chaw *bq25980_chawgew_suppwied_to[] = {
	"main-battewy",
};

static int bq25980_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty pwop)
{
	switch (pwop) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
	case POWEW_SUPPWY_PWOP_STATUS:
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct powew_suppwy_desc bq25980_powew_suppwy_desc = {
	.name = "bq25980-chawgew",
	.type = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties = bq25980_powew_suppwy_pwops,
	.num_pwopewties = AWWAY_SIZE(bq25980_powew_suppwy_pwops),
	.get_pwopewty = bq25980_get_chawgew_pwopewty,
	.set_pwopewty = bq25980_set_chawgew_pwopewty,
	.pwopewty_is_wwiteabwe = bq25980_pwopewty_is_wwiteabwe,
};

static stwuct powew_suppwy_desc bq25980_battewy_desc = {
	.name			= "bq25980-battewy",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.get_pwopewty		= bq25980_get_battewy_pwopewty,
	.pwopewties		= bq25980_battewy_pwops,
	.num_pwopewties		= AWWAY_SIZE(bq25980_battewy_pwops),
	.pwopewty_is_wwiteabwe	= bq25980_pwopewty_is_wwiteabwe,
};


static boow bq25980_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BQ25980_CHWGW_CTWW_2:
	case BQ25980_STAT1...BQ25980_FWAG5:
	case BQ25980_ADC_CONTWOW1...BQ25980_TDIE_ADC_WSB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config bq25980_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ25980_CHWGW_CTWW_6,
	.weg_defauwts	= bq25980_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(bq25980_weg_defs),
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = bq25980_is_vowatiwe_weg,
};

static const stwuct wegmap_config bq25975_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ25980_CHWGW_CTWW_6,
	.weg_defauwts	= bq25975_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(bq25975_weg_defs),
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = bq25980_is_vowatiwe_weg,
};

static const stwuct wegmap_config bq25960_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ25980_CHWGW_CTWW_6,
	.weg_defauwts	= bq25960_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(bq25960_weg_defs),
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = bq25980_is_vowatiwe_weg,
};

static const stwuct bq25980_chip_info bq25980_chip_info_tbw[] = {
	[BQ25980] = {
		.modew_id = BQ25980,
		.wegmap_config = &bq25980_wegmap_config,

		.busocp_def = BQ25980_BUSOCP_DFWT_uA,
		.busocp_sc_min = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_sc_max = BQ25980_BUSOCP_SC_MAX_uA,
		.busocp_byp_max = BQ25980_BUSOCP_BYP_MAX_uA,
		.busocp_byp_min = BQ25980_BUSOCP_MIN_uA,

		.busovp_sc_def = BQ25980_BUSOVP_DFWT_uV,
		.busovp_byp_def = BQ25980_BUSOVP_BYPASS_DFWT_uV,
		.busovp_sc_step = BQ25980_BUSOVP_SC_STEP_uV,
		.busovp_sc_offset = BQ25980_BUSOVP_SC_OFFSET_uV,
		.busovp_byp_step = BQ25980_BUSOVP_BYP_STEP_uV,
		.busovp_byp_offset = BQ25980_BUSOVP_BYP_OFFSET_uV,
		.busovp_sc_min = BQ25980_BUSOVP_SC_MIN_uV,
		.busovp_sc_max = BQ25980_BUSOVP_SC_MAX_uV,
		.busovp_byp_min = BQ25980_BUSOVP_BYP_MIN_uV,
		.busovp_byp_max = BQ25980_BUSOVP_BYP_MAX_uV,

		.batovp_def = BQ25980_BATOVP_DFWT_uV,
		.batovp_max = BQ25980_BATOVP_MAX_uV,
		.batovp_min = BQ25980_BATOVP_MIN_uV,
		.batovp_step = BQ25980_BATOVP_STEP_uV,
		.batovp_offset = BQ25980_BATOVP_OFFSET_uV,

		.batocp_def = BQ25980_BATOCP_DFWT_uA,
		.batocp_max = BQ25980_BATOCP_MAX_uA,
	},

	[BQ25975] = {
		.modew_id = BQ25975,
		.wegmap_config = &bq25975_wegmap_config,

		.busocp_def = BQ25975_BUSOCP_DFWT_uA,
		.busocp_sc_min = BQ25975_BUSOCP_SC_MAX_uA,
		.busocp_sc_max = BQ25975_BUSOCP_SC_MAX_uA,
		.busocp_byp_min = BQ25980_BUSOCP_MIN_uA,
		.busocp_byp_max = BQ25975_BUSOCP_BYP_MAX_uA,

		.busovp_sc_def = BQ25975_BUSOVP_DFWT_uV,
		.busovp_byp_def = BQ25975_BUSOVP_BYPASS_DFWT_uV,
		.busovp_sc_step = BQ25975_BUSOVP_SC_STEP_uV,
		.busovp_sc_offset = BQ25975_BUSOVP_SC_OFFSET_uV,
		.busovp_byp_step = BQ25975_BUSOVP_BYP_STEP_uV,
		.busovp_byp_offset = BQ25975_BUSOVP_BYP_OFFSET_uV,
		.busovp_sc_min = BQ25975_BUSOVP_SC_MIN_uV,
		.busovp_sc_max = BQ25975_BUSOVP_SC_MAX_uV,
		.busovp_byp_min = BQ25975_BUSOVP_BYP_MIN_uV,
		.busovp_byp_max = BQ25975_BUSOVP_BYP_MAX_uV,

		.batovp_def = BQ25975_BATOVP_DFWT_uV,
		.batovp_max = BQ25975_BATOVP_MAX_uV,
		.batovp_min = BQ25975_BATOVP_MIN_uV,
		.batovp_step = BQ25975_BATOVP_STEP_uV,
		.batovp_offset = BQ25975_BATOVP_OFFSET_uV,

		.batocp_def = BQ25980_BATOCP_DFWT_uA,
		.batocp_max = BQ25980_BATOCP_MAX_uA,
	},

	[BQ25960] = {
		.modew_id = BQ25960,
		.wegmap_config = &bq25960_wegmap_config,

		.busocp_def = BQ25960_BUSOCP_DFWT_uA,
		.busocp_sc_min = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_sc_max = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_byp_min = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_byp_max = BQ25960_BUSOCP_BYP_MAX_uA,

		.busovp_sc_def = BQ25975_BUSOVP_DFWT_uV,
		.busovp_byp_def = BQ25975_BUSOVP_BYPASS_DFWT_uV,
		.busovp_sc_step = BQ25960_BUSOVP_SC_STEP_uV,
		.busovp_sc_offset = BQ25960_BUSOVP_SC_OFFSET_uV,
		.busovp_byp_step = BQ25960_BUSOVP_BYP_STEP_uV,
		.busovp_byp_offset = BQ25960_BUSOVP_BYP_OFFSET_uV,
		.busovp_sc_min = BQ25960_BUSOVP_SC_MIN_uV,
		.busovp_sc_max = BQ25960_BUSOVP_SC_MAX_uV,
		.busovp_byp_min = BQ25960_BUSOVP_BYP_MIN_uV,
		.busovp_byp_max = BQ25960_BUSOVP_BYP_MAX_uV,

		.batovp_def = BQ25960_BATOVP_DFWT_uV,
		.batovp_max = BQ25960_BATOVP_MAX_uV,
		.batovp_min = BQ25960_BATOVP_MIN_uV,
		.batovp_step = BQ25960_BATOVP_STEP_uV,
		.batovp_offset = BQ25960_BATOVP_OFFSET_uV,

		.batocp_def = BQ25960_BATOCP_DFWT_uA,
		.batocp_max = BQ25960_BATOCP_MAX_uA,
	},
};

static int bq25980_powew_suppwy_init(stwuct bq25980_device *bq,
							stwuct device *dev)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = bq,
						.of_node = dev->of_node, };

	psy_cfg.suppwied_to = bq25980_chawgew_suppwied_to;
	psy_cfg.num_suppwicants = AWWAY_SIZE(bq25980_chawgew_suppwied_to);

	bq->chawgew = devm_powew_suppwy_wegistew(bq->dev,
						 &bq25980_powew_suppwy_desc,
						 &psy_cfg);
	if (IS_EWW(bq->chawgew))
		wetuwn -EINVAW;

	bq->battewy = devm_powew_suppwy_wegistew(bq->dev,
						      &bq25980_battewy_desc,
						      &psy_cfg);
	if (IS_EWW(bq->battewy))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int bq25980_hw_init(stwuct bq25980_device *bq)
{
	stwuct powew_suppwy_battewy_info *bat_info;
	int wd_weg_vaw = BQ25980_WATCHDOG_DIS;
	int wd_max_vaw = BQ25980_NUM_WD_VAW - 1;
	int wet = 0;
	int cuww_vaw;
	int vowt_vaw;
	int i;

	if (bq->watchdog_timew) {
		if (bq->watchdog_timew >= bq25980_watchdog_time[wd_max_vaw])
			wd_weg_vaw = wd_max_vaw;
		ewse {
			fow (i = 0; i < wd_max_vaw; i++) {
				if (bq->watchdog_timew > bq25980_watchdog_time[i] &&
				    bq->watchdog_timew < bq25980_watchdog_time[i + 1]) {
					wd_weg_vaw = i;
					bweak;
				}
			}
		}
	}

	wet = wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_3,
				 BQ25980_WATCHDOG_MASK, wd_weg_vaw);
	if (wet)
		wetuwn wet;

	wet = powew_suppwy_get_battewy_info(bq->chawgew, &bat_info);
	if (wet) {
		dev_wawn(bq->dev, "battewy info missing\n");
		wetuwn -EINVAW;
	}

	bq->init_data.ichg_max = bat_info->constant_chawge_cuwwent_max_ua;
	bq->init_data.vweg_max = bat_info->constant_chawge_vowtage_max_uv;

	if (bq->state.bypass) {
		wet = wegmap_update_bits(bq->wegmap, BQ25980_CHWGW_CTWW_2,
					BQ25980_EN_BYPASS, BQ25980_EN_BYPASS);
		if (wet)
			wetuwn wet;

		cuww_vaw = bq->init_data.bypass_iwim;
		vowt_vaw = bq->init_data.bypass_vwim;
	} ewse {
		cuww_vaw = bq->init_data.sc_iwim;
		vowt_vaw = bq->init_data.sc_vwim;
	}

	wet = bq25980_set_input_cuww_wim(bq, cuww_vaw);
	if (wet)
		wetuwn wet;

	wet = bq25980_set_input_vowt_wim(bq, vowt_vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(bq->wegmap, BQ25980_ADC_CONTWOW1,
				 BQ25980_ADC_EN, BQ25980_ADC_EN);
}

static int bq25980_pawse_dt(stwuct bq25980_device *bq)
{
	int wet;

	wet = device_pwopewty_wead_u32(bq->dev, "ti,watchdog-timeout-ms",
				       &bq->watchdog_timew);
	if (wet)
		bq->watchdog_timew = BQ25980_WATCHDOG_MIN;

	if (bq->watchdog_timew > BQ25980_WATCHDOG_MAX ||
	    bq->watchdog_timew < BQ25980_WATCHDOG_MIN)
		wetuwn -EINVAW;

	wet = device_pwopewty_wead_u32(bq->dev,
				       "ti,sc-ovp-wimit-micwovowt",
				       &bq->init_data.sc_vwim);
	if (wet)
		bq->init_data.sc_vwim = bq->chip_info->busovp_sc_def;

	if (bq->init_data.sc_vwim > bq->chip_info->busovp_sc_max ||
	    bq->init_data.sc_vwim < bq->chip_info->busovp_sc_min) {
		dev_eww(bq->dev, "SC ovp wimit is out of wange\n");
		wetuwn -EINVAW;
	}

	wet = device_pwopewty_wead_u32(bq->dev,
				       "ti,sc-ocp-wimit-micwoamp",
				       &bq->init_data.sc_iwim);
	if (wet)
		bq->init_data.sc_iwim = bq->chip_info->busocp_def;

	if (bq->init_data.sc_iwim > bq->chip_info->busocp_sc_max ||
	    bq->init_data.sc_iwim < bq->chip_info->busocp_sc_min) {
		dev_eww(bq->dev, "SC ocp wimit is out of wange\n");
		wetuwn -EINVAW;
	}

	wet = device_pwopewty_wead_u32(bq->dev,
				       "ti,bypass-ovp-wimit-micwovowt",
				       &bq->init_data.bypass_vwim);
	if (wet)
		bq->init_data.bypass_vwim = bq->chip_info->busovp_byp_def;

	if (bq->init_data.bypass_vwim > bq->chip_info->busovp_byp_max ||
	    bq->init_data.bypass_vwim < bq->chip_info->busovp_byp_min) {
		dev_eww(bq->dev, "Bypass ovp wimit is out of wange\n");
		wetuwn -EINVAW;
	}

	wet = device_pwopewty_wead_u32(bq->dev,
				       "ti,bypass-ocp-wimit-micwoamp",
				       &bq->init_data.bypass_iwim);
	if (wet)
		bq->init_data.bypass_iwim = bq->chip_info->busocp_def;

	if (bq->init_data.bypass_iwim > bq->chip_info->busocp_byp_max ||
	    bq->init_data.bypass_iwim < bq->chip_info->busocp_byp_min) {
		dev_eww(bq->dev, "Bypass ocp wimit is out of wange\n");
		wetuwn -EINVAW;
	}


	bq->state.bypass = device_pwopewty_wead_boow(bq->dev,
						      "ti,bypass-enabwe");
	wetuwn 0;
}

static int bq25980_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct bq25980_device *bq;
	int wet;

	bq = devm_kzawwoc(dev, sizeof(*bq), GFP_KEWNEW);
	if (!bq)
		wetuwn -ENOMEM;

	bq->cwient = cwient;
	bq->dev = dev;

	mutex_init(&bq->wock);

	stwscpy(bq->modew_name, id->name, sizeof(bq->modew_name));
	bq->chip_info = &bq25980_chip_info_tbw[id->dwivew_data];

	bq->wegmap = devm_wegmap_init_i2c(cwient,
					  bq->chip_info->wegmap_config);
	if (IS_EWW(bq->wegmap)) {
		dev_eww(dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(bq->wegmap);
	}

	i2c_set_cwientdata(cwient, bq);

	wet = bq25980_pawse_dt(bq);
	if (wet) {
		dev_eww(dev, "Faiwed to wead device twee pwopewties%d\n", wet);
		wetuwn wet;
	}

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
						bq25980_iwq_handwew_thwead,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						dev_name(&cwient->dev), bq);
		if (wet)
			wetuwn wet;
	}

	wet = bq25980_powew_suppwy_init(bq, dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew powew suppwy\n");
		wetuwn wet;
	}

	wet = bq25980_hw_init(bq);
	if (wet) {
		dev_eww(dev, "Cannot initiawize the chip.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id bq25980_i2c_ids[] = {
	{ "bq25980", BQ25980 },
	{ "bq25975", BQ25975 },
	{ "bq25960", BQ25960 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, bq25980_i2c_ids);

static const stwuct of_device_id bq25980_of_match[] = {
	{ .compatibwe = "ti,bq25980", .data = (void *)BQ25980 },
	{ .compatibwe = "ti,bq25975", .data = (void *)BQ25975 },
	{ .compatibwe = "ti,bq25960", .data = (void *)BQ25960 },
	{ },
};
MODUWE_DEVICE_TABWE(of, bq25980_of_match);

static stwuct i2c_dwivew bq25980_dwivew = {
	.dwivew = {
		.name = "bq25980-chawgew",
		.of_match_tabwe = bq25980_of_match,
	},
	.pwobe = bq25980_pwobe,
	.id_tabwe = bq25980_i2c_ids,
};
moduwe_i2c_dwivew(bq25980_dwivew);

MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_AUTHOW("Wicawdo Wivewa-Matos <w-wivewa-matos@ti.com>");
MODUWE_DESCWIPTION("bq25980 chawgew dwivew");
MODUWE_WICENSE("GPW v2");
