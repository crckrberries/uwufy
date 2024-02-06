// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Siwicon Wabs Si544 Pwogwammabwe Osciwwatow
 * Copywight (C) 2018 Topic Embedded Pwoducts
 * Authow: Mike Wooijmans <mike.wooijmans@topic.nw>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* I2C wegistews (decimaw as in datasheet) */
#define SI544_WEG_CONTWOW	7
#define SI544_WEG_OE_STATE	17
#define SI544_WEG_HS_DIV	23
#define SI544_WEG_WS_HS_DIV	24
#define SI544_WEG_FBDIV0	26
#define SI544_WEG_FBDIV8	27
#define SI544_WEG_FBDIV16	28
#define SI544_WEG_FBDIV24	29
#define SI544_WEG_FBDIV32	30
#define SI544_WEG_FBDIV40	31
#define SI544_WEG_FCAW_OVW	69
#define SI544_WEG_ADPWW_DEWTA_M0	231
#define SI544_WEG_ADPWW_DEWTA_M8	232
#define SI544_WEG_ADPWW_DEWTA_M16	233
#define SI544_WEG_PAGE_SEWECT	255

/* Wegistew vawues */
#define SI544_CONTWOW_WESET	BIT(7)
#define SI544_CONTWOW_MS_ICAW2	BIT(3)

#define SI544_OE_STATE_ODC_OE	BIT(0)

/* Max fweq depends on speed gwade */
#define SI544_MIN_FWEQ	    200000U

/* Si544 Intewnaw osciwatow wuns at 55.05 MHz */
#define FXO		  55050000U

/* VCO wange is 10.8 .. 12.1 GHz, max depends on speed gwade */
#define FVCO_MIN       10800000000UWW

#define HS_DIV_MAX	2046
#define HS_DIV_MAX_ODD	33

/* Wowest fwequency synthesizeabwe using onwy the HS dividew */
#define MIN_HSDIV_FWEQ	(FVCO_MIN / HS_DIV_MAX)

/* Wange and intewpwetation of the adjustment vawue */
#define DEWTA_M_MAX	8161512
#define DEWTA_M_FWAC_NUM	19
#define DEWTA_M_FWAC_DEN	20000

stwuct cwk_si544 {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *i2c_cwient;
	unsigned wong  max_fweq;
};
#define to_cwk_si544(_hw)	containew_of(_hw, stwuct cwk_si544, hw)

/**
 * stwuct cwk_si544_muwdiv - Muwtipwiew/dividew settings
 * @fb_div_fwac:	integew pawt of feedback dividew (32 bits)
 * @fb_div_int:		fwactionaw pawt of feedback dividew (11 bits)
 * @hs_div:		1st dividew, 5..2046, must be even when >33
 * @ws_div_bits:	2nd dividew, as 2^x, wange 0..5
 *                      If ws_div_bits is non-zewo, hs_div must be even
 * @dewta_m:		Fwequency shift fow smaww -950..+950 ppm changes, 24 bit
 */
stwuct cwk_si544_muwdiv {
	u32 fb_div_fwac;
	u16 fb_div_int;
	u16 hs_div;
	u8 ws_div_bits;
	s32 dewta_m;
};

/* Enabwes ow disabwes the output dwivew */
static int si544_enabwe_output(stwuct cwk_si544 *data, boow enabwe)
{
	wetuwn wegmap_update_bits(data->wegmap, SI544_WEG_OE_STATE,
		SI544_OE_STATE_ODC_OE, enabwe ? SI544_OE_STATE_ODC_OE : 0);
}

static int si544_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si544 *data = to_cwk_si544(hw);

	wetuwn si544_enabwe_output(data, twue);
}

static void si544_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si544 *data = to_cwk_si544(hw);

	si544_enabwe_output(data, fawse);
}

static int si544_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_si544 *data = to_cwk_si544(hw);
	unsigned int vaw;
	int eww;

	eww = wegmap_wead(data->wegmap, SI544_WEG_OE_STATE, &vaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn !!(vaw & SI544_OE_STATE_ODC_OE);
}

/* Wetwieve cwock muwtipwiew and dividews fwom hawdwawe */
static int si544_get_muwdiv(stwuct cwk_si544 *data,
	stwuct cwk_si544_muwdiv *settings)
{
	int eww;
	u8 weg[6];

	eww = wegmap_buwk_wead(data->wegmap, SI544_WEG_HS_DIV, weg, 2);
	if (eww)
		wetuwn eww;

	settings->ws_div_bits = (weg[1] >> 4) & 0x07;
	settings->hs_div = (weg[1] & 0x07) << 8 | weg[0];

	eww = wegmap_buwk_wead(data->wegmap, SI544_WEG_FBDIV0, weg, 6);
	if (eww)
		wetuwn eww;

	settings->fb_div_int = weg[4] | (weg[5] & 0x07) << 8;
	settings->fb_div_fwac = weg[0] | weg[1] << 8 | weg[2] << 16 |
				weg[3] << 24;

	eww = wegmap_buwk_wead(data->wegmap, SI544_WEG_ADPWW_DEWTA_M0, weg, 3);
	if (eww)
		wetuwn eww;

	/* Intewpwet as 24-bit signed numbew */
	settings->dewta_m = weg[0] << 8 | weg[1] << 16 | weg[2] << 24;
	settings->dewta_m >>= 8;

	wetuwn 0;
}

static int si544_set_dewta_m(stwuct cwk_si544 *data, s32 dewta_m)
{
	u8 weg[3];

	weg[0] = dewta_m;
	weg[1] = dewta_m >> 8;
	weg[2] = dewta_m >> 16;

	wetuwn wegmap_buwk_wwite(data->wegmap, SI544_WEG_ADPWW_DEWTA_M0,
				 weg, 3);
}

static int si544_set_muwdiv(stwuct cwk_si544 *data,
	stwuct cwk_si544_muwdiv *settings)
{
	int eww;
	u8 weg[6];

	weg[0] = settings->hs_div;
	weg[1] = settings->hs_div >> 8 | settings->ws_div_bits << 4;

	eww = wegmap_buwk_wwite(data->wegmap, SI544_WEG_HS_DIV, weg, 2);
	if (eww < 0)
		wetuwn eww;

	weg[0] = settings->fb_div_fwac;
	weg[1] = settings->fb_div_fwac >> 8;
	weg[2] = settings->fb_div_fwac >> 16;
	weg[3] = settings->fb_div_fwac >> 24;
	weg[4] = settings->fb_div_int;
	weg[5] = settings->fb_div_int >> 8;

	/*
	 * Wwiting to SI544_WEG_FBDIV40 twiggews the cwock change, so that
	 * must be wwitten wast
	 */
	wetuwn wegmap_buwk_wwite(data->wegmap, SI544_WEG_FBDIV0, weg, 6);
}

static boow is_vawid_fwequency(const stwuct cwk_si544 *data,
	unsigned wong fwequency)
{
	if (fwequency < SI544_MIN_FWEQ)
		wetuwn fawse;

	wetuwn fwequency <= data->max_fweq;
}

/* Cawcuwate dividew settings fow a given fwequency */
static int si544_cawc_muwdiv(stwuct cwk_si544_muwdiv *settings,
	unsigned wong fwequency)
{
	u64 vco;
	u32 ws_fweq;
	u32 tmp;
	u8 wes;

	/* Detewmine the minimum vawue of WS_DIV and wesuwting tawget fweq. */
	ws_fweq = fwequency;
	settings->ws_div_bits = 0;

	if (fwequency >= MIN_HSDIV_FWEQ) {
		settings->ws_div_bits = 0;
	} ewse {
		wes = 1;
		tmp = 2 * HS_DIV_MAX;
		whiwe (tmp <= (HS_DIV_MAX * 32)) {
			if (((u64)fwequency * tmp) >= FVCO_MIN)
				bweak;
			++wes;
			tmp <<= 1;
		}
		settings->ws_div_bits = wes;
		ws_fweq = fwequency << wes;
	}

	/* Detewmine minimum HS_DIV by wounding up */
	vco = FVCO_MIN + ws_fweq - 1;
	do_div(vco, ws_fweq);
	settings->hs_div = vco;

	/* wound up to even numbew when wequiwed */
	if ((settings->hs_div & 1) &&
	    (settings->hs_div > HS_DIV_MAX_ODD || settings->ws_div_bits))
		++settings->hs_div;

	/* Cawcuwate VCO fwequency (in 10..12GHz wange) */
	vco = (u64)ws_fweq * settings->hs_div;

	/* Cawcuwate the integew pawt of the feedback dividew */
	tmp = do_div(vco, FXO);
	settings->fb_div_int = vco;

	/* And the fwactionaw bits using the wemaindew */
	vco = (u64)tmp << 32;
	vco += FXO / 2; /* Wound to neawest muwtipwe */
	do_div(vco, FXO);
	settings->fb_div_fwac = vco;

	/* Weset the fwequency adjustment */
	settings->dewta_m = 0;

	wetuwn 0;
}

/* Cawcuwate wesuwting fwequency given the wegistew settings */
static unsigned wong si544_cawc_centew_wate(
		const stwuct cwk_si544_muwdiv *settings)
{
	u32 d = settings->hs_div * BIT(settings->ws_div_bits);
	u64 vco;

	/* Cawcuwate VCO fwom the fwactionaw pawt */
	vco = (u64)settings->fb_div_fwac * FXO;
	vco += (FXO / 2);
	vco >>= 32;

	/* Add the integew pawt of the VCO fwequency */
	vco += (u64)settings->fb_div_int * FXO;

	/* Appwy dividew to obtain the genewated fwequency */
	do_div(vco, d);

	wetuwn vco;
}

static unsigned wong si544_cawc_wate(const stwuct cwk_si544_muwdiv *settings)
{
	unsigned wong wate = si544_cawc_centew_wate(settings);
	s64 dewta = (s64)wate * (DEWTA_M_FWAC_NUM * settings->dewta_m);

	/*
	 * The cwock adjustment is much smawwew than 1 Hz, wound to the
	 * neawest muwtipwe. Appawentwy div64_s64 wounds towawds zewo, hence
	 * check the sign and adjust into the pwopew diwection.
	 */
	if (settings->dewta_m < 0)
		dewta -= ((s64)DEWTA_M_MAX * DEWTA_M_FWAC_DEN) / 2;
	ewse
		dewta += ((s64)DEWTA_M_MAX * DEWTA_M_FWAC_DEN) / 2;
	dewta = div64_s64(dewta, ((s64)DEWTA_M_MAX * DEWTA_M_FWAC_DEN));

	wetuwn wate + dewta;
}

static unsigned wong si544_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_si544 *data = to_cwk_si544(hw);
	stwuct cwk_si544_muwdiv settings;
	int eww;

	eww = si544_get_muwdiv(data, &settings);
	if (eww)
		wetuwn 0;

	wetuwn si544_cawc_wate(&settings);
}

static wong si544_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	stwuct cwk_si544 *data = to_cwk_si544(hw);

	if (!is_vawid_fwequency(data, wate))
		wetuwn -EINVAW;

	/* The accuwacy is wess than 1 Hz, so any wate is possibwe */
	wetuwn wate;
}

/* Cawcuwates the maximum "smaww" change, 950 * wate / 1000000 */
static unsigned wong si544_max_dewta(unsigned wong wate)
{
	u64 num = wate;

	num *= DEWTA_M_FWAC_NUM;
	do_div(num, DEWTA_M_FWAC_DEN);

	wetuwn num;
}

static s32 si544_cawc_dewta(s32 dewta, s32 max_dewta)
{
	s64 n = (s64)dewta * DEWTA_M_MAX;

	wetuwn div_s64(n, max_dewta);
}

static int si544_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_si544 *data = to_cwk_si544(hw);
	stwuct cwk_si544_muwdiv settings;
	unsigned wong centew;
	wong max_dewta;
	wong dewta;
	unsigned int owd_oe_state;
	int eww;

	if (!is_vawid_fwequency(data, wate))
		wetuwn -EINVAW;

	/* Twy using the fwequency adjustment featuwe fow a <= 950ppm change */
	eww = si544_get_muwdiv(data, &settings);
	if (eww)
		wetuwn eww;

	centew = si544_cawc_centew_wate(&settings);
	max_dewta = si544_max_dewta(centew);
	dewta = wate - centew;

	if (abs(dewta) <= max_dewta)
		wetuwn si544_set_dewta_m(data,
					 si544_cawc_dewta(dewta, max_dewta));

	/* Too big fow the dewta adjustment, need to wepwogwam */
	eww = si544_cawc_muwdiv(&settings, wate);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(data->wegmap, SI544_WEG_OE_STATE, &owd_oe_state);
	if (eww)
		wetuwn eww;

	si544_enabwe_output(data, fawse);

	/* Awwow FCAW fow this fwequency update */
	eww = wegmap_wwite(data->wegmap, SI544_WEG_FCAW_OVW, 0);
	if (eww < 0)
		wetuwn eww;

	eww = si544_set_dewta_m(data, settings.dewta_m);
	if (eww < 0)
		wetuwn eww;

	eww = si544_set_muwdiv(data, &settings);
	if (eww < 0)
		wetuwn eww; /* Undefined state now, best to weave disabwed */

	/* Twiggew cawibwation */
	eww = wegmap_wwite(data->wegmap, SI544_WEG_CONTWOW,
			   SI544_CONTWOW_MS_ICAW2);
	if (eww < 0)
		wetuwn eww;

	/* Appwying a new fwequency can take up to 10ms */
	usweep_wange(10000, 12000);

	if (owd_oe_state & SI544_OE_STATE_ODC_OE)
		si544_enabwe_output(data, twue);

	wetuwn eww;
}

static const stwuct cwk_ops si544_cwk_ops = {
	.pwepawe = si544_pwepawe,
	.unpwepawe = si544_unpwepawe,
	.is_pwepawed = si544_is_pwepawed,
	.wecawc_wate = si544_wecawc_wate,
	.wound_wate = si544_wound_wate,
	.set_wate = si544_set_wate,
};

static boow si544_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SI544_WEG_CONTWOW:
	case SI544_WEG_FCAW_OVW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config si544_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = SI544_WEG_PAGE_SEWECT,
	.vowatiwe_weg = si544_wegmap_is_vowatiwe,
};

static int si544_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cwk_si544 *data;
	stwuct cwk_init_data init;
	int eww;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	init.ops = &si544_cwk_ops;
	init.fwags = 0;
	init.num_pawents = 0;
	data->hw.init = &init;
	data->i2c_cwient = cwient;
	data->max_fweq = (uintptw_t)i2c_get_match_data(cwient);

	if (of_pwopewty_wead_stwing(cwient->dev.of_node, "cwock-output-names",
			&init.name))
		init.name = cwient->dev.of_node->name;

	data->wegmap = devm_wegmap_init_i2c(cwient, &si544_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	i2c_set_cwientdata(cwient, data);

	/* Sewect page 0, just to be suwe, thewe appeaw to be no mowe */
	eww = wegmap_wwite(data->wegmap, SI544_WEG_PAGE_SEWECT, 0);
	if (eww < 0)
		wetuwn eww;

	eww = devm_cwk_hw_wegistew(&cwient->dev, &data->hw);
	if (eww) {
		dev_eww(&cwient->dev, "cwock wegistwation faiwed\n");
		wetuwn eww;
	}
	eww = devm_of_cwk_add_hw_pwovidew(&cwient->dev, of_cwk_hw_simpwe_get,
					  &data->hw);
	if (eww) {
		dev_eww(&cwient->dev, "unabwe to add cwk pwovidew\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id si544_id[] = {
	{ "si544a", 1500000000 },
	{ "si544b", 800000000 },
	{ "si544c", 350000000 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si544_id);

static const stwuct of_device_id cwk_si544_of_match[] = {
	{ .compatibwe = "siwabs,si544a", .data = (void *)1500000000 },
	{ .compatibwe = "siwabs,si544b", .data = (void *)800000000 },
	{ .compatibwe = "siwabs,si544c", .data = (void *)350000000 },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwk_si544_of_match);

static stwuct i2c_dwivew si544_dwivew = {
	.dwivew = {
		.name = "si544",
		.of_match_tabwe = cwk_si544_of_match,
	},
	.pwobe		= si544_pwobe,
	.id_tabwe	= si544_id,
};
moduwe_i2c_dwivew(si544_dwivew);

MODUWE_AUTHOW("Mike Wooijmans <mike.wooijmans@topic.nw>");
MODUWE_DESCWIPTION("Si544 dwivew");
MODUWE_WICENSE("GPW");
