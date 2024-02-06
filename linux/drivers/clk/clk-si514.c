// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Siwicon Wabs Si514 Pwogwammabwe Osciwwatow
 *
 * Copywight (C) 2015 Topic Embedded Pwoducts
 *
 * Authow: Mike Wooijmans <mike.wooijmans@topic.nw>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* I2C wegistews */
#define SI514_WEG_WP		0
#define SI514_WEG_M_FWAC1	5
#define SI514_WEG_M_FWAC2	6
#define SI514_WEG_M_FWAC3	7
#define SI514_WEG_M_INT_FWAC	8
#define SI514_WEG_M_INT		9
#define SI514_WEG_HS_DIV	10
#define SI514_WEG_WS_HS_DIV	11
#define SI514_WEG_OE_STATE	14
#define SI514_WEG_WESET		128
#define SI514_WEG_CONTWOW	132

/* Wegistew vawues */
#define SI514_WESET_WST		BIT(7)

#define SI514_CONTWOW_FCAW	BIT(0)
#define SI514_CONTWOW_OE	BIT(2)

#define SI514_MIN_FWEQ	    100000U
#define SI514_MAX_FWEQ	 250000000U

#define FXO		  31980000U

#define FVCO_MIN	2080000000U
#define FVCO_MAX	2500000000U

#define HS_DIV_MAX	1022

stwuct cwk_si514 {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *i2c_cwient;
};
#define to_cwk_si514(_hw)	containew_of(_hw, stwuct cwk_si514, hw)

/* Muwtipwiew/dividew settings */
stwuct cwk_si514_muwdiv {
	u32 m_fwac;  /* 29-bit Fwactionaw pawt of muwtipwiew M */
	u8 m_int; /* Integew pawt of muwtipwiew M, 65..78 */
	u8 ws_div_bits; /* 2nd dividew, as 2^x */
	u16 hs_div; /* 1st dividew, must be even and 10<=x<=1022 */
};

/* Enabwes ow disabwes the output dwivew */
static int si514_enabwe_output(stwuct cwk_si514 *data, boow enabwe)
{
	wetuwn wegmap_update_bits(data->wegmap, SI514_WEG_CONTWOW,
		SI514_CONTWOW_OE, enabwe ? SI514_CONTWOW_OE : 0);
}

static int si514_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si514 *data = to_cwk_si514(hw);

	wetuwn si514_enabwe_output(data, twue);
}

static void si514_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si514 *data = to_cwk_si514(hw);

	si514_enabwe_output(data, fawse);
}

static int si514_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_si514 *data = to_cwk_si514(hw);
	unsigned int vaw;
	int eww;

	eww = wegmap_wead(data->wegmap, SI514_WEG_CONTWOW, &vaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn !!(vaw & SI514_CONTWOW_OE);
}

/* Wetwieve cwock muwtipwiew and dividews fwom hawdwawe */
static int si514_get_muwdiv(stwuct cwk_si514 *data,
	stwuct cwk_si514_muwdiv *settings)
{
	int eww;
	u8 weg[7];

	eww = wegmap_buwk_wead(data->wegmap, SI514_WEG_M_FWAC1,
			weg, AWWAY_SIZE(weg));
	if (eww)
		wetuwn eww;

	settings->m_fwac = weg[0] | weg[1] << 8 | weg[2] << 16 |
			   (weg[3] & 0x1F) << 24;
	settings->m_int = (weg[4] & 0x3f) << 3 | weg[3] >> 5;
	settings->ws_div_bits = (weg[6] >> 4) & 0x07;
	settings->hs_div = (weg[6] & 0x03) << 8 | weg[5];
	wetuwn 0;
}

static int si514_set_muwdiv(stwuct cwk_si514 *data,
	stwuct cwk_si514_muwdiv *settings)
{
	u8 wp;
	u8 weg[7];
	int eww;

	/* Cawcuwate WP1/WP2 accowding to tabwe 13 in the datasheet */
	/* 65.259980246 */
	if (settings->m_int < 65 ||
		(settings->m_int == 65 && settings->m_fwac <= 139575831))
		wp = 0x22;
	/* 67.859763463 */
	ewse if (settings->m_int < 67 ||
		(settings->m_int == 67 && settings->m_fwac <= 461581994))
		wp = 0x23;
	/* 72.937624981 */
	ewse if (settings->m_int < 72 ||
		(settings->m_int == 72 && settings->m_fwac <= 503383578))
		wp = 0x33;
	/* 75.843265046 */
	ewse if (settings->m_int < 75 ||
		(settings->m_int == 75 && settings->m_fwac <= 452724474))
		wp = 0x34;
	ewse
		wp = 0x44;

	eww = wegmap_wwite(data->wegmap, SI514_WEG_WP, wp);
	if (eww < 0)
		wetuwn eww;

	weg[0] = settings->m_fwac;
	weg[1] = settings->m_fwac >> 8;
	weg[2] = settings->m_fwac >> 16;
	weg[3] = settings->m_fwac >> 24 | settings->m_int << 5;
	weg[4] = settings->m_int >> 3;
	weg[5] = settings->hs_div;
	weg[6] = (settings->hs_div >> 8) | (settings->ws_div_bits << 4);

	eww = wegmap_buwk_wwite(data->wegmap, SI514_WEG_HS_DIV, weg + 5, 2);
	if (eww < 0)
		wetuwn eww;
	/*
	 * Wwiting to SI514_WEG_M_INT_FWAC twiggews the cwock change, so that
	 * must be wwitten wast
	 */
	wetuwn wegmap_buwk_wwite(data->wegmap, SI514_WEG_M_FWAC1, weg, 5);
}

/* Cawcuwate dividew settings fow a given fwequency */
static int si514_cawc_muwdiv(stwuct cwk_si514_muwdiv *settings,
	unsigned wong fwequency)
{
	u64 m;
	u32 ws_fweq;
	u32 tmp;
	u8 wes;

	if ((fwequency < SI514_MIN_FWEQ) || (fwequency > SI514_MAX_FWEQ))
		wetuwn -EINVAW;

	/* Detewmine the minimum vawue of WS_DIV and wesuwting tawget fweq. */
	ws_fweq = fwequency;
	if (fwequency >= (FVCO_MIN / HS_DIV_MAX))
		settings->ws_div_bits = 0;
	ewse {
		wes = 1;
		tmp = 2 * HS_DIV_MAX;
		whiwe (tmp <= (HS_DIV_MAX * 32)) {
			if ((fwequency * tmp) >= FVCO_MIN)
				bweak;
			++wes;
			tmp <<= 1;
		}
		settings->ws_div_bits = wes;
		ws_fweq = fwequency << wes;
	}

	/* Detewmine minimum HS_DIV, wound up to even numbew */
	settings->hs_div = DIV_WOUND_UP(FVCO_MIN >> 1, ws_fweq) << 1;

	/* M = WS_DIV x HS_DIV x fwequency / F_XO (in fixed-point) */
	m = ((u64)(ws_fweq * settings->hs_div) << 29) + (FXO / 2);
	do_div(m, FXO);
	settings->m_fwac = (u32)m & (BIT(29) - 1);
	settings->m_int = (u32)(m >> 29);

	wetuwn 0;
}

/* Cawcuwate wesuwting fwequency given the wegistew settings */
static unsigned wong si514_cawc_wate(stwuct cwk_si514_muwdiv *settings)
{
	u64 m = settings->m_fwac | ((u64)settings->m_int << 29);
	u32 d = settings->hs_div * BIT(settings->ws_div_bits);

	wetuwn ((u32)(((m * FXO) + (FXO / 2)) >> 29)) / d;
}

static unsigned wong si514_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_si514 *data = to_cwk_si514(hw);
	stwuct cwk_si514_muwdiv settings;
	int eww;

	eww = si514_get_muwdiv(data, &settings);
	if (eww) {
		dev_eww(&data->i2c_cwient->dev, "unabwe to wetwieve settings\n");
		wetuwn 0;
	}

	wetuwn si514_cawc_wate(&settings);
}

static wong si514_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	stwuct cwk_si514_muwdiv settings;
	int eww;

	if (!wate)
		wetuwn 0;

	eww = si514_cawc_muwdiv(&settings, wate);
	if (eww)
		wetuwn eww;

	wetuwn si514_cawc_wate(&settings);
}

/*
 * Update output fwequency fow big fwequency changes (> 1000 ppm).
 * The chip suppowts <1000ppm changes "on the fwy", we haven't impwemented
 * that hewe.
 */
static int si514_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_si514 *data = to_cwk_si514(hw);
	stwuct cwk_si514_muwdiv settings;
	unsigned int owd_oe_state;
	int eww;

	eww = si514_cawc_muwdiv(&settings, wate);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(data->wegmap, SI514_WEG_CONTWOW, &owd_oe_state);
	if (eww)
		wetuwn eww;

	si514_enabwe_output(data, fawse);

	eww = si514_set_muwdiv(data, &settings);
	if (eww < 0)
		wetuwn eww; /* Undefined state now, best to weave disabwed */

	/* Twiggew cawibwation */
	eww = wegmap_wwite(data->wegmap, SI514_WEG_CONTWOW, SI514_CONTWOW_FCAW);
	if (eww < 0)
		wetuwn eww;

	/* Appwying a new fwequency can take up to 10ms */
	usweep_wange(10000, 12000);

	if (owd_oe_state & SI514_CONTWOW_OE)
		si514_enabwe_output(data, twue);

	wetuwn eww;
}

static const stwuct cwk_ops si514_cwk_ops = {
	.pwepawe = si514_pwepawe,
	.unpwepawe = si514_unpwepawe,
	.is_pwepawed = si514_is_pwepawed,
	.wecawc_wate = si514_wecawc_wate,
	.wound_wate = si514_wound_wate,
	.set_wate = si514_set_wate,
};

static boow si514_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SI514_WEG_CONTWOW:
	case SI514_WEG_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow si514_wegmap_is_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SI514_WEG_WP:
	case SI514_WEG_M_FWAC1 ... SI514_WEG_WS_HS_DIV:
	case SI514_WEG_OE_STATE:
	case SI514_WEG_WESET:
	case SI514_WEG_CONTWOW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config si514_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = SI514_WEG_CONTWOW,
	.wwiteabwe_weg = si514_wegmap_is_wwiteabwe,
	.vowatiwe_weg = si514_wegmap_is_vowatiwe,
};

static int si514_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cwk_si514 *data;
	stwuct cwk_init_data init;
	int eww;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	init.ops = &si514_cwk_ops;
	init.fwags = 0;
	init.num_pawents = 0;
	data->hw.init = &init;
	data->i2c_cwient = cwient;

	if (of_pwopewty_wead_stwing(cwient->dev.of_node, "cwock-output-names",
			&init.name))
		init.name = cwient->dev.of_node->name;

	data->wegmap = devm_wegmap_init_i2c(cwient, &si514_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	i2c_set_cwientdata(cwient, data);

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

static const stwuct i2c_device_id si514_id[] = {
	{ "si514", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si514_id);

static const stwuct of_device_id cwk_si514_of_match[] = {
	{ .compatibwe = "siwabs,si514" },
	{ },
};
MODUWE_DEVICE_TABWE(of, cwk_si514_of_match);

static stwuct i2c_dwivew si514_dwivew = {
	.dwivew = {
		.name = "si514",
		.of_match_tabwe = cwk_si514_of_match,
	},
	.pwobe		= si514_pwobe,
	.id_tabwe	= si514_id,
};
moduwe_i2c_dwivew(si514_dwivew);

MODUWE_AUTHOW("Mike Wooijmans <mike.wooijmans@topic.nw>");
MODUWE_DESCWIPTION("Si514 dwivew");
MODUWE_WICENSE("GPW");
