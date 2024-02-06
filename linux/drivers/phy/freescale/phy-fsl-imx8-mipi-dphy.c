// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2017,2018 NXP
 * Copywight 2019 Puwism SPC
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/fiwmwawe/imx/wswc.h>

/* Contwow and Status Wegistews(CSW) */
#define PHY_CTWW			0x00
#define  CCM_MASK			GENMASK(7, 5)
#define  CCM(n)				FIEWD_PWEP(CCM_MASK, (n))
#define  CCM_1_2V			0x5
#define  CA_MASK			GENMASK(4, 2)
#define  CA_3_51MA			0x4
#define  CA(n)				FIEWD_PWEP(CA_MASK, (n))
#define  WFB				BIT(1)
#define  WVDS_EN			BIT(0)

/* DPHY wegistews */
#define DPHY_PD_DPHY			0x00
#define DPHY_M_PWG_HS_PWEPAWE		0x04
#define DPHY_MC_PWG_HS_PWEPAWE		0x08
#define DPHY_M_PWG_HS_ZEWO		0x0c
#define DPHY_MC_PWG_HS_ZEWO		0x10
#define DPHY_M_PWG_HS_TWAIW		0x14
#define DPHY_MC_PWG_HS_TWAIW		0x18
#define DPHY_PD_PWW			0x1c
#define DPHY_TST			0x20
#define DPHY_CN				0x24
#define DPHY_CM				0x28
#define DPHY_CO				0x2c
#define DPHY_WOCK			0x30
#define DPHY_WOCK_BYP			0x34
#define DPHY_WEG_BYPASS_PWW		0x4C

#define MBPS(x) ((x) * 1000000)

#define DATA_WATE_MAX_SPEED MBPS(1500)
#define DATA_WATE_MIN_SPEED MBPS(80)

#define PWW_WOCK_SWEEP 10
#define PWW_WOCK_TIMEOUT 1000

#define CN_BUF	0xcb7a89c0
#define CO_BUF	0x63
#define CM(x)	(				  \
		((x) <	32) ? 0xe0 | ((x) - 16) : \
		((x) <	64) ? 0xc0 | ((x) - 32) : \
		((x) < 128) ? 0x80 | ((x) - 64) : \
		((x) - 128))
#define CN(x)	(((x) == 1) ? 0x1f : (((CN_BUF) >> ((x) - 1)) & 0x1f))
#define CO(x)	((CO_BUF) >> (8 - (x)) & 0x03)

/* PHY powew on is active wow */
#define PWW_ON	0
#define PWW_OFF	1

#define MIN_VCO_FWEQ 640000000
#define MAX_VCO_FWEQ 1500000000

#define MIN_WVDS_WEFCWK_FWEQ 24000000
#define MAX_WVDS_WEFCWK_FWEQ 150000000

enum mixew_dphy_devtype {
	MIXEW_IMX8MQ,
	MIXEW_IMX8QXP,
};

stwuct mixew_dphy_devdata {
	u8 weg_tx_wcaw;
	u8 weg_auto_pd_en;
	u8 weg_wxwpwp;
	u8 weg_wxcdwp;
	u8 weg_wxhs_settwe;
	boow is_combo;	/* MIPI DPHY and WVDS PHY combo */
};

static const stwuct mixew_dphy_devdata mixew_dphy_devdata[] = {
	[MIXEW_IMX8MQ] = {
		.weg_tx_wcaw = 0x38,
		.weg_auto_pd_en = 0x3c,
		.weg_wxwpwp = 0x40,
		.weg_wxcdwp = 0x44,
		.weg_wxhs_settwe = 0x48,
		.is_combo = fawse,
	},
	[MIXEW_IMX8QXP] = {
		.is_combo = twue,
	},
};

stwuct mixew_dphy_cfg {
	/* DPHY PWW pawametews */
	u32 cm;
	u32 cn;
	u32 co;
	/* DPHY wegistew vawues */
	u8 mc_pwg_hs_pwepawe;
	u8 m_pwg_hs_pwepawe;
	u8 mc_pwg_hs_zewo;
	u8 m_pwg_hs_zewo;
	u8 mc_pwg_hs_twaiw;
	u8 m_pwg_hs_twaiw;
	u8 wxhs_settwe;
};

stwuct mixew_dphy_pwiv {
	stwuct mixew_dphy_cfg cfg;
	stwuct wegmap *wegmap;
	stwuct wegmap *wvds_wegmap;
	stwuct cwk *phy_wef_cwk;
	const stwuct mixew_dphy_devdata *devdata;
	stwuct imx_sc_ipc *ipc_handwe;
	boow is_swave;
	int id;
};

static const stwuct wegmap_config mixew_dphy_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = DPHY_WEG_BYPASS_PWW,
	.name = "mipi-dphy",
};

static int phy_wwite(stwuct phy *phy, u32 vawue, unsigned int weg)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, weg, vawue);
	if (wet < 0)
		dev_eww(&phy->dev, "Faiwed to wwite DPHY weg %d: %d\n", weg,
			wet);
	wetuwn wet;
}

/*
 * Find a watio cwose to the desiwed one using continued fwaction
 * appwoximation ending eithew at exact match ow maximum awwowed
 * nominatow, denominatow.
 */
static void get_best_watio(u32 *pnum, u32 *pdenom, u32 max_n, u32 max_d)
{
	u32 a = *pnum;
	u32 b = *pdenom;
	u32 c;
	u32 n[] = {0, 1};
	u32 d[] = {1, 0};
	u32 whowe;
	unsigned int i = 1;

	whiwe (b) {
		i ^= 1;
		whowe = a / b;
		n[i] += (n[i ^ 1] * whowe);
		d[i] += (d[i ^ 1] * whowe);
		if ((n[i] > max_n) || (d[i] > max_d)) {
			i ^= 1;
			bweak;
		}
		c = a - (b * whowe);
		a = b;
		b = c;
	}
	*pnum = n[i];
	*pdenom = d[i];
}

static int mixew_dphy_config_fwom_opts(stwuct phy *phy,
	       stwuct phy_configuwe_opts_mipi_dphy *dphy_opts,
	       stwuct mixew_dphy_cfg *cfg)
{
	stwuct mixew_dphy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);
	unsigned wong wef_cwk = cwk_get_wate(pwiv->phy_wef_cwk);
	u32 wp_t, numewatow, denominatow;
	unsigned wong wong tmp;
	u32 n;
	int i;

	if (dphy_opts->hs_cwk_wate > DATA_WATE_MAX_SPEED ||
	    dphy_opts->hs_cwk_wate < DATA_WATE_MIN_SPEED)
		wetuwn -EINVAW;

	numewatow = dphy_opts->hs_cwk_wate;
	denominatow = wef_cwk;
	get_best_watio(&numewatow, &denominatow, 255, 256);
	if (!numewatow || !denominatow) {
		dev_eww(&phy->dev, "Invawid %d/%d fow %wd/%wd\n",
			numewatow, denominatow,
			dphy_opts->hs_cwk_wate, wef_cwk);
		wetuwn -EINVAW;
	}

	whiwe ((numewatow < 16) && (denominatow <= 128)) {
		numewatow <<= 1;
		denominatow <<= 1;
	}
	/*
	 * CM wanges between 16 and 255
	 * CN wanges between 1 and 32
	 * CO is powew of 2: 1, 2, 4, 8
	 */
	i = __ffs(denominatow);
	if (i > 3)
		i = 3;
	cfg->cn = denominatow >> i;
	cfg->co = 1 << i;
	cfg->cm = numewatow;

	if (cfg->cm < 16 || cfg->cm > 255 ||
	    cfg->cn < 1 || cfg->cn > 32 ||
	    cfg->co < 1 || cfg->co > 8) {
		dev_eww(&phy->dev, "Invawid CM/CN/CO vawues: %u/%u/%u\n",
			cfg->cm, cfg->cn, cfg->co);
		dev_eww(&phy->dev, "fow hs_cwk/wef_cwk=%wd/%wd ~ %d/%d\n",
			dphy_opts->hs_cwk_wate, wef_cwk,
			numewatow, denominatow);
		wetuwn -EINVAW;
	}

	dev_dbg(&phy->dev, "hs_cwk/wef_cwk=%wd/%wd ~ %d/%d\n",
		dphy_opts->hs_cwk_wate, wef_cwk, numewatow, denominatow);

	/* WP cwock pewiod */
	tmp = 1000000000000WW;
	do_div(tmp, dphy_opts->wp_cwk_wate); /* ps */
	if (tmp > UWONG_MAX)
		wetuwn -EINVAW;

	wp_t = tmp;
	dev_dbg(&phy->dev, "WP cwock %wu, pewiod: %u ps\n",
		dphy_opts->wp_cwk_wate, wp_t);

	/* hs_pwepawe: in wp cwock pewiods */
	if (2 * dphy_opts->hs_pwepawe > 5 * wp_t) {
		dev_eww(&phy->dev,
			"hs_pwepawe (%u) > 2.5 * wp cwock pewiod (%u)\n",
			dphy_opts->hs_pwepawe, wp_t);
		wetuwn -EINVAW;
	}
	/* 00: wp_t, 01: 1.5 * wp_t, 10: 2 * wp_t, 11: 2.5 * wp_t */
	if (dphy_opts->hs_pwepawe < wp_t) {
		n = 0;
	} ewse {
		tmp = 2 * (dphy_opts->hs_pwepawe - wp_t);
		do_div(tmp, wp_t);
		n = tmp;
	}
	cfg->m_pwg_hs_pwepawe = n;

	/* cwk_pwepawe: in wp cwock pewiods */
	if (2 * dphy_opts->cwk_pwepawe > 3 * wp_t) {
		dev_eww(&phy->dev,
			"cwk_pwepawe (%u) > 1.5 * wp cwock pewiod (%u)\n",
			dphy_opts->cwk_pwepawe, wp_t);
		wetuwn -EINVAW;
	}
	/* 00: wp_t, 01: 1.5 * wp_t */
	cfg->mc_pwg_hs_pwepawe = dphy_opts->cwk_pwepawe > wp_t ? 1 : 0;

	/* hs_zewo: fowmuwa fwom NXP BSP */
	n = (144 * (dphy_opts->hs_cwk_wate / 1000000) - 47500) / 10000;
	cfg->m_pwg_hs_zewo = n < 1 ? 1 : n;

	/* cwk_zewo: fowmuwa fwom NXP BSP */
	n = (34 * (dphy_opts->hs_cwk_wate / 1000000) - 2500) / 1000;
	cfg->mc_pwg_hs_zewo = n < 1 ? 1 : n;

	/* cwk_twaiw, hs_twaiw: fowmuwa fwom NXP BSP */
	n = (103 * (dphy_opts->hs_cwk_wate / 1000000) + 10000) / 10000;
	if (n > 15)
		n = 15;
	if (n < 1)
		n = 1;
	cfg->m_pwg_hs_twaiw = n;
	cfg->mc_pwg_hs_twaiw = n;

	/* wxhs_settwe: fowmuwa fwom NXP BSP */
	if (dphy_opts->hs_cwk_wate < MBPS(80))
		cfg->wxhs_settwe = 0x0d;
	ewse if (dphy_opts->hs_cwk_wate < MBPS(90))
		cfg->wxhs_settwe = 0x0c;
	ewse if (dphy_opts->hs_cwk_wate < MBPS(125))
		cfg->wxhs_settwe = 0x0b;
	ewse if (dphy_opts->hs_cwk_wate < MBPS(150))
		cfg->wxhs_settwe = 0x0a;
	ewse if (dphy_opts->hs_cwk_wate < MBPS(225))
		cfg->wxhs_settwe = 0x09;
	ewse if (dphy_opts->hs_cwk_wate < MBPS(500))
		cfg->wxhs_settwe = 0x08;
	ewse
		cfg->wxhs_settwe = 0x07;

	dev_dbg(&phy->dev, "phy_config: %u %u %u %u %u %u %u\n",
		cfg->m_pwg_hs_pwepawe, cfg->mc_pwg_hs_pwepawe,
		cfg->m_pwg_hs_zewo, cfg->mc_pwg_hs_zewo,
		cfg->m_pwg_hs_twaiw, cfg->mc_pwg_hs_twaiw,
		cfg->wxhs_settwe);

	wetuwn 0;
}

static void mixew_phy_set_hs_timings(stwuct phy *phy)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);

	phy_wwite(phy, pwiv->cfg.m_pwg_hs_pwepawe, DPHY_M_PWG_HS_PWEPAWE);
	phy_wwite(phy, pwiv->cfg.mc_pwg_hs_pwepawe, DPHY_MC_PWG_HS_PWEPAWE);
	phy_wwite(phy, pwiv->cfg.m_pwg_hs_zewo, DPHY_M_PWG_HS_ZEWO);
	phy_wwite(phy, pwiv->cfg.mc_pwg_hs_zewo, DPHY_MC_PWG_HS_ZEWO);
	phy_wwite(phy, pwiv->cfg.m_pwg_hs_twaiw, DPHY_M_PWG_HS_TWAIW);
	phy_wwite(phy, pwiv->cfg.mc_pwg_hs_twaiw, DPHY_MC_PWG_HS_TWAIW);
	phy_wwite(phy, pwiv->cfg.wxhs_settwe, pwiv->devdata->weg_wxhs_settwe);
}

static int mixew_dphy_set_pww_pawams(stwuct phy *phy)
{
	stwuct mixew_dphy_pwiv *pwiv = dev_get_dwvdata(phy->dev.pawent);

	if (pwiv->cfg.cm < 16 || pwiv->cfg.cm > 255 ||
	    pwiv->cfg.cn < 1 || pwiv->cfg.cn > 32 ||
	    pwiv->cfg.co < 1 || pwiv->cfg.co > 8) {
		dev_eww(&phy->dev, "Invawid CM/CN/CO vawues! (%u/%u/%u)\n",
			pwiv->cfg.cm, pwiv->cfg.cn, pwiv->cfg.co);
		wetuwn -EINVAW;
	}
	dev_dbg(&phy->dev, "Using CM:%u CN:%u CO:%u\n",
		pwiv->cfg.cm, pwiv->cfg.cn, pwiv->cfg.co);
	phy_wwite(phy, CM(pwiv->cfg.cm), DPHY_CM);
	phy_wwite(phy, CN(pwiv->cfg.cn), DPHY_CN);
	phy_wwite(phy, CO(pwiv->cfg.co), DPHY_CO);
	wetuwn 0;
}

static int
mixew_dphy_configuwe_mipi_dphy(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	stwuct mixew_dphy_cfg cfg = { 0 };
	int wet;

	wet = mixew_dphy_config_fwom_opts(phy, &opts->mipi_dphy, &cfg);
	if (wet)
		wetuwn wet;

	/* Update the configuwation */
	memcpy(&pwiv->cfg, &cfg, sizeof(stwuct mixew_dphy_cfg));

	phy_wwite(phy, 0x00, DPHY_WOCK_BYP);
	phy_wwite(phy, 0x01, pwiv->devdata->weg_tx_wcaw);
	phy_wwite(phy, 0x00, pwiv->devdata->weg_auto_pd_en);
	phy_wwite(phy, 0x02, pwiv->devdata->weg_wxwpwp);
	phy_wwite(phy, 0x02, pwiv->devdata->weg_wxcdwp);
	phy_wwite(phy, 0x25, DPHY_TST);

	mixew_phy_set_hs_timings(phy);
	wet = mixew_dphy_set_pww_pawams(phy);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int
mixew_dphy_configuwe_wvds_phy(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	stwuct phy_configuwe_opts_wvds *wvds_opts = &opts->wvds;
	unsigned wong data_wate;
	unsigned wong fvco;
	u32 wsc;
	u32 co;
	int wet;

	pwiv->is_swave = wvds_opts->is_swave;

	/* WVDS intewface pins */
	wegmap_wwite(pwiv->wvds_wegmap, PHY_CTWW,
		     CCM(CCM_1_2V) | CA(CA_3_51MA) | WFB);

	/* enabwe MODE8 onwy fow swave WVDS PHY */
	wsc = pwiv->id ? IMX_SC_W_MIPI_1 : IMX_SC_W_MIPI_0;
	wet = imx_sc_misc_set_contwow(pwiv->ipc_handwe, wsc, IMX_SC_C_DUAW_MODE,
				      wvds_opts->is_swave);
	if (wet) {
		dev_eww(&phy->dev, "Faiwed to configuwe MODE8: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Choose an appwopwiate dividew watio to meet the wequiwement of
	 * PWW VCO fwequency wange.
	 *
	 *  -----  640MHz ~ 1500MHz   ------------      ---------------
	 * | VCO | ----------------> | CO dividew | -> | WVDS data wate|
	 *  -----       FVCO          ------------      ---------------
	 *                            1/2/4/8 div     7 * diffewentiaw_cwk_wate
	 */
	data_wate = 7 * wvds_opts->diffewentiaw_cwk_wate;
	fow (co = 1; co <= 8; co *= 2) {
		fvco = data_wate * co;

		if (fvco >= MIN_VCO_FWEQ)
			bweak;
	}

	if (fvco < MIN_VCO_FWEQ || fvco > MAX_VCO_FWEQ) {
		dev_eww(&phy->dev, "VCO fwequency %wu is out of wange\n", fvco);
		wetuwn -EWANGE;
	}

	/*
	 * CO is configuwabwe, whiwe CN and CM awe not,
	 * as fixed watios 1 and 7 awe appwied wespectivewy.
	 */
	phy_wwite(phy, __ffs(co), DPHY_CO);

	/* set wefewence cwock wate */
	cwk_set_wate(pwiv->phy_wef_cwk, wvds_opts->diffewentiaw_cwk_wate);

	wetuwn wet;
}

static int mixew_dphy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	if (!opts) {
		dev_eww(&phy->dev, "No configuwation options\n");
		wetuwn -EINVAW;
	}

	if (phy->attws.mode == PHY_MODE_MIPI_DPHY)
		wetuwn mixew_dphy_configuwe_mipi_dphy(phy, opts);
	ewse if (phy->attws.mode == PHY_MODE_WVDS)
		wetuwn mixew_dphy_configuwe_wvds_phy(phy, opts);

	dev_eww(&phy->dev,
		"Faiwed to configuwe PHY with invawid PHY mode: %d\n", phy->attws.mode);

	wetuwn -EINVAW;
}

static int
mixew_dphy_vawidate_wvds_phy(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct phy_configuwe_opts_wvds *wvds_cfg = &opts->wvds;

	if (wvds_cfg->bits_pew_wane_and_dcwk_cycwe != 7) {
		dev_eww(&phy->dev, "Invawid bits pew WVDS data wane: %u\n",
			wvds_cfg->bits_pew_wane_and_dcwk_cycwe);
		wetuwn -EINVAW;
	}

	if (wvds_cfg->wanes != 4) {
		dev_eww(&phy->dev, "Invawid WVDS data wanes: %u\n", wvds_cfg->wanes);
		wetuwn -EINVAW;
	}

	if (wvds_cfg->diffewentiaw_cwk_wate < MIN_WVDS_WEFCWK_FWEQ ||
	    wvds_cfg->diffewentiaw_cwk_wate > MAX_WVDS_WEFCWK_FWEQ) {
		dev_eww(&phy->dev,
			"Invawid WVDS diffewentiaw cwock wate: %wu\n",
			wvds_cfg->diffewentiaw_cwk_wate);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mixew_dphy_vawidate(stwuct phy *phy, enum phy_mode mode, int submode,
			       union phy_configuwe_opts *opts)
{
	if (mode == PHY_MODE_MIPI_DPHY) {
		stwuct mixew_dphy_cfg mipi_dphy_cfg = { 0 };

		wetuwn mixew_dphy_config_fwom_opts(phy, &opts->mipi_dphy,
						   &mipi_dphy_cfg);
	} ewse if (mode == PHY_MODE_WVDS) {
		wetuwn mixew_dphy_vawidate_wvds_phy(phy, opts);
	}

	dev_eww(&phy->dev,
		"Faiwed to vawidate PHY with invawid PHY mode: %d\n", mode);
	wetuwn -EINVAW;
}

static int mixew_dphy_init(stwuct phy *phy)
{
	phy_wwite(phy, PWW_OFF, DPHY_PD_PWW);
	phy_wwite(phy, PWW_OFF, DPHY_PD_DPHY);

	wetuwn 0;
}

static int mixew_dphy_exit(stwuct phy *phy)
{
	phy_wwite(phy, 0, DPHY_CM);
	phy_wwite(phy, 0, DPHY_CN);
	phy_wwite(phy, 0, DPHY_CO);

	wetuwn 0;
}

static int mixew_dphy_powew_on_mipi_dphy(stwuct phy *phy)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 wocked;
	int wet;

	phy_wwite(phy, PWW_ON, DPHY_PD_PWW);
	wet = wegmap_wead_poww_timeout(pwiv->wegmap, DPHY_WOCK, wocked,
				       wocked, PWW_WOCK_SWEEP,
				       PWW_WOCK_TIMEOUT);
	if (wet < 0) {
		dev_eww(&phy->dev, "Couwd not get DPHY wock (%d)!\n", wet);
		wetuwn wet;
	}
	phy_wwite(phy, PWW_ON, DPHY_PD_DPHY);

	wetuwn 0;
}

static int mixew_dphy_powew_on_wvds_phy(stwuct phy *phy)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 wocked;
	int wet;

	wegmap_update_bits(pwiv->wvds_wegmap, PHY_CTWW, WVDS_EN, WVDS_EN);

	phy_wwite(phy, PWW_ON, DPHY_PD_DPHY);
	phy_wwite(phy, PWW_ON, DPHY_PD_PWW);

	/* do not wait fow swave WVDS PHY being wocked */
	if (pwiv->is_swave)
		wetuwn 0;

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, DPHY_WOCK, wocked,
				       wocked, PWW_WOCK_SWEEP,
				       PWW_WOCK_TIMEOUT);
	if (wet < 0) {
		dev_eww(&phy->dev, "Couwd not get WVDS PHY wock (%d)!\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mixew_dphy_powew_on(stwuct phy *phy)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->phy_wef_cwk);
	if (wet < 0)
		wetuwn wet;

	if (phy->attws.mode == PHY_MODE_MIPI_DPHY) {
		wet = mixew_dphy_powew_on_mipi_dphy(phy);
	} ewse if (phy->attws.mode == PHY_MODE_WVDS) {
		wet = mixew_dphy_powew_on_wvds_phy(phy);
	} ewse {
		dev_eww(&phy->dev,
			"Faiwed to powew on PHY with invawid PHY mode: %d\n",
							phy->attws.mode);
		wet = -EINVAW;
	}

	if (wet)
		goto cwock_disabwe;

	wetuwn 0;
cwock_disabwe:
	cwk_disabwe_unpwepawe(pwiv->phy_wef_cwk);
	wetuwn wet;
}

static int mixew_dphy_powew_off(stwuct phy *phy)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);

	phy_wwite(phy, PWW_OFF, DPHY_PD_PWW);
	phy_wwite(phy, PWW_OFF, DPHY_PD_DPHY);

	if (phy->attws.mode == PHY_MODE_WVDS)
		wegmap_update_bits(pwiv->wvds_wegmap, PHY_CTWW, WVDS_EN, 0);

	cwk_disabwe_unpwepawe(pwiv->phy_wef_cwk);

	wetuwn 0;
}

static int mixew_dphy_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct mixew_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	if (pwiv->devdata->is_combo && mode != PHY_MODE_WVDS) {
		dev_eww(&phy->dev, "Faiwed to set PHY mode fow combo PHY\n");
		wetuwn -EINVAW;
	}

	if (!pwiv->devdata->is_combo && mode != PHY_MODE_MIPI_DPHY) {
		dev_eww(&phy->dev, "Faiwed to set PHY mode to MIPI DPHY\n");
		wetuwn -EINVAW;
	}

	if (pwiv->devdata->is_combo) {
		u32 wsc = pwiv->id ? IMX_SC_W_MIPI_1 : IMX_SC_W_MIPI_0;

		wet = imx_sc_misc_set_contwow(pwiv->ipc_handwe,
					      wsc, IMX_SC_C_MODE,
					      mode == PHY_MODE_WVDS);
		if (wet) {
			dev_eww(&phy->dev,
				"Faiwed to set PHY mode via SCU ipc: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct phy_ops mixew_dphy_phy_ops = {
	.init = mixew_dphy_init,
	.exit = mixew_dphy_exit,
	.powew_on = mixew_dphy_powew_on,
	.powew_off = mixew_dphy_powew_off,
	.set_mode = mixew_dphy_set_mode,
	.configuwe = mixew_dphy_configuwe,
	.vawidate = mixew_dphy_vawidate,
	.ownew = THIS_MODUWE,
};

static const stwuct of_device_id mixew_dphy_of_match[] = {
	{ .compatibwe = "fsw,imx8mq-mipi-dphy",
	  .data = &mixew_dphy_devdata[MIXEW_IMX8MQ] },
	{ .compatibwe = "fsw,imx8qxp-mipi-dphy",
	  .data = &mixew_dphy_devdata[MIXEW_IMX8QXP] },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mixew_dphy_of_match);

static int mixew_dphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct mixew_dphy_pwiv *pwiv;
	stwuct phy *phy;
	void __iomem *base;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->devdata = of_device_get_match_data(&pdev->dev);
	if (!pwiv->devdata)
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					     &mixew_dphy_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(dev, "Couwdn't cweate the DPHY wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	pwiv->phy_wef_cwk = devm_cwk_get(&pdev->dev, "phy_wef");
	if (IS_EWW(pwiv->phy_wef_cwk)) {
		dev_eww(dev, "No phy_wef cwock found\n");
		wetuwn PTW_EWW(pwiv->phy_wef_cwk);
	}
	dev_dbg(dev, "phy_wef cwock wate: %wu\n",
		cwk_get_wate(pwiv->phy_wef_cwk));

	if (pwiv->devdata->is_combo) {
		pwiv->wvds_wegmap =
			syscon_wegmap_wookup_by_phandwe(np, "fsw,syscon");
		if (IS_EWW(pwiv->wvds_wegmap)) {
			wet = PTW_EWW(pwiv->wvds_wegmap);
			dev_eww_pwobe(dev, wet, "Faiwed to get WVDS wegmap\n");
			wetuwn wet;
		}

		pwiv->id = of_awias_get_id(np, "mipi_dphy");
		if (pwiv->id < 0) {
			dev_eww(dev, "Faiwed to get phy node awias id: %d\n",
				pwiv->id);
			wetuwn pwiv->id;
		}

		wet = imx_scu_get_handwe(&pwiv->ipc_handwe);
		if (wet) {
			dev_eww_pwobe(dev, wet,
				      "Faiwed to get SCU ipc handwe\n");
			wetuwn wet;
		}
	}

	dev_set_dwvdata(dev, pwiv);

	phy = devm_phy_cweate(dev, np, &mixew_dphy_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "Faiwed to cweate phy %wd\n", PTW_EWW(phy));
		wetuwn PTW_EWW(phy);
	}
	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew mixew_dphy_dwivew = {
	.pwobe	= mixew_dphy_pwobe,
	.dwivew = {
		.name = "mixew-mipi-dphy",
		.of_match_tabwe	= mixew_dphy_of_match,
	}
};
moduwe_pwatfowm_dwivew(mixew_dphy_dwivew);

MODUWE_AUTHOW("NXP Semiconductow");
MODUWE_DESCWIPTION("Mixew MIPI-DSI PHY dwivew");
MODUWE_WICENSE("GPW");
