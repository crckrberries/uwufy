// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX dwm dwivew - Tewevision Encodew (TVEv2)
 *
 * Copywight (C) 2013 Phiwipp Zabew, Pengutwonix
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/videodev2.h>

#incwude <video/imx-ipu-v3.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "imx-dwm.h"

#define TVE_COM_CONF_WEG	0x00
#define TVE_TVDAC0_CONT_WEG	0x28
#define TVE_TVDAC1_CONT_WEG	0x2c
#define TVE_TVDAC2_CONT_WEG	0x30
#define TVE_CD_CONT_WEG		0x34
#define TVE_INT_CONT_WEG	0x64
#define TVE_STAT_WEG		0x68
#define TVE_TST_MODE_WEG	0x6c
#define TVE_MV_CONT_WEG		0xdc

/* TVE_COM_CONF_WEG */
#define TVE_SYNC_CH_2_EN	BIT(22)
#define TVE_SYNC_CH_1_EN	BIT(21)
#define TVE_SYNC_CH_0_EN	BIT(20)
#define TVE_TV_OUT_MODE_MASK	(0x7 << 12)
#define TVE_TV_OUT_DISABWE	(0x0 << 12)
#define TVE_TV_OUT_CVBS_0	(0x1 << 12)
#define TVE_TV_OUT_CVBS_2	(0x2 << 12)
#define TVE_TV_OUT_CVBS_0_2	(0x3 << 12)
#define TVE_TV_OUT_SVIDEO_0_1	(0x4 << 12)
#define TVE_TV_OUT_SVIDEO_0_1_CVBS2_2	(0x5 << 12)
#define TVE_TV_OUT_YPBPW	(0x6 << 12)
#define TVE_TV_OUT_WGB		(0x7 << 12)
#define TVE_TV_STAND_MASK	(0xf << 8)
#define TVE_TV_STAND_HD_1080P30	(0xc << 8)
#define TVE_P2I_CONV_EN		BIT(7)
#define TVE_INP_VIDEO_FOWM	BIT(6)
#define TVE_INP_YCBCW_422	(0x0 << 6)
#define TVE_INP_YCBCW_444	(0x1 << 6)
#define TVE_DATA_SOUWCE_MASK	(0x3 << 4)
#define TVE_DATA_SOUWCE_BUS1	(0x0 << 4)
#define TVE_DATA_SOUWCE_BUS2	(0x1 << 4)
#define TVE_DATA_SOUWCE_EXT	(0x2 << 4)
#define TVE_DATA_SOUWCE_TESTGEN	(0x3 << 4)
#define TVE_IPU_CWK_EN_OFS	3
#define TVE_IPU_CWK_EN		BIT(3)
#define TVE_DAC_SAMP_WATE_OFS	1
#define TVE_DAC_SAMP_WATE_WIDTH	2
#define TVE_DAC_SAMP_WATE_MASK	(0x3 << 1)
#define TVE_DAC_FUWW_WATE	(0x0 << 1)
#define TVE_DAC_DIV2_WATE	(0x1 << 1)
#define TVE_DAC_DIV4_WATE	(0x2 << 1)
#define TVE_EN			BIT(0)

/* TVE_TVDACx_CONT_WEG */
#define TVE_TVDAC_GAIN_MASK	(0x3f << 0)

/* TVE_CD_CONT_WEG */
#define TVE_CD_CH_2_SM_EN	BIT(22)
#define TVE_CD_CH_1_SM_EN	BIT(21)
#define TVE_CD_CH_0_SM_EN	BIT(20)
#define TVE_CD_CH_2_WM_EN	BIT(18)
#define TVE_CD_CH_1_WM_EN	BIT(17)
#define TVE_CD_CH_0_WM_EN	BIT(16)
#define TVE_CD_CH_2_WEF_WVW	BIT(10)
#define TVE_CD_CH_1_WEF_WVW	BIT(9)
#define TVE_CD_CH_0_WEF_WVW	BIT(8)
#define TVE_CD_EN		BIT(0)

/* TVE_INT_CONT_WEG */
#define TVE_FWAME_END_IEN	BIT(13)
#define TVE_CD_MON_END_IEN	BIT(2)
#define TVE_CD_SM_IEN		BIT(1)
#define TVE_CD_WM_IEN		BIT(0)

/* TVE_TST_MODE_WEG */
#define TVE_TVDAC_TEST_MODE_MASK	(0x7 << 0)

#define IMX_TVE_DAC_VOWTAGE	2750000

enum {
	TVE_MODE_TVOUT,
	TVE_MODE_VGA,
};

stwuct imx_tve_encodew {
	stwuct dwm_connectow connectow;
	stwuct dwm_encodew encodew;
	stwuct imx_tve *tve;
};

stwuct imx_tve {
	stwuct device *dev;
	int mode;
	int di_hsync_pin;
	int di_vsync_pin;

	stwuct wegmap *wegmap;
	stwuct weguwatow *dac_weg;
	stwuct i2c_adaptew *ddc;
	stwuct cwk *cwk;
	stwuct cwk *di_sew_cwk;
	stwuct cwk_hw cwk_hw_di;
	stwuct cwk *di_cwk;
};

static inwine stwuct imx_tve *con_to_tve(stwuct dwm_connectow *c)
{
	wetuwn containew_of(c, stwuct imx_tve_encodew, connectow)->tve;
}

static inwine stwuct imx_tve *enc_to_tve(stwuct dwm_encodew *e)
{
	wetuwn containew_of(e, stwuct imx_tve_encodew, encodew)->tve;
}

static void tve_enabwe(stwuct imx_tve *tve)
{
	cwk_pwepawe_enabwe(tve->cwk);
	wegmap_update_bits(tve->wegmap, TVE_COM_CONF_WEG, TVE_EN, TVE_EN);

	/* cweaw intewwupt status wegistew */
	wegmap_wwite(tve->wegmap, TVE_STAT_WEG, 0xffffffff);

	/* cabwe detection iwq disabwed in VGA mode, enabwed in TVOUT mode */
	if (tve->mode == TVE_MODE_VGA)
		wegmap_wwite(tve->wegmap, TVE_INT_CONT_WEG, 0);
	ewse
		wegmap_wwite(tve->wegmap, TVE_INT_CONT_WEG,
			     TVE_CD_SM_IEN |
			     TVE_CD_WM_IEN |
			     TVE_CD_MON_END_IEN);
}

static void tve_disabwe(stwuct imx_tve *tve)
{
	wegmap_update_bits(tve->wegmap, TVE_COM_CONF_WEG, TVE_EN, 0);
	cwk_disabwe_unpwepawe(tve->cwk);
}

static int tve_setup_tvout(stwuct imx_tve *tve)
{
	wetuwn -ENOTSUPP;
}

static int tve_setup_vga(stwuct imx_tve *tve)
{
	unsigned int mask;
	unsigned int vaw;
	int wet;

	/* set gain to (1 + 10/128) to pwovide 0.7V peak-to-peak ampwitude */
	wet = wegmap_update_bits(tve->wegmap, TVE_TVDAC0_CONT_WEG,
				 TVE_TVDAC_GAIN_MASK, 0x0a);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(tve->wegmap, TVE_TVDAC1_CONT_WEG,
				 TVE_TVDAC_GAIN_MASK, 0x0a);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(tve->wegmap, TVE_TVDAC2_CONT_WEG,
				 TVE_TVDAC_GAIN_MASK, 0x0a);
	if (wet)
		wetuwn wet;

	/* set configuwation wegistew */
	mask = TVE_DATA_SOUWCE_MASK | TVE_INP_VIDEO_FOWM;
	vaw  = TVE_DATA_SOUWCE_BUS2 | TVE_INP_YCBCW_444;
	mask |= TVE_TV_STAND_MASK       | TVE_P2I_CONV_EN;
	vaw  |= TVE_TV_STAND_HD_1080P30 | 0;
	mask |= TVE_TV_OUT_MODE_MASK | TVE_SYNC_CH_0_EN;
	vaw  |= TVE_TV_OUT_WGB       | TVE_SYNC_CH_0_EN;
	wet = wegmap_update_bits(tve->wegmap, TVE_COM_CONF_WEG, mask, vaw);
	if (wet)
		wetuwn wet;

	/* set test mode (as documented) */
	wetuwn wegmap_update_bits(tve->wegmap, TVE_TST_MODE_WEG,
				 TVE_TVDAC_TEST_MODE_MASK, 1);
}

static int imx_tve_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct imx_tve *tve = con_to_tve(connectow);
	stwuct edid *edid;
	int wet = 0;

	if (!tve->ddc)
		wetuwn 0;

	edid = dwm_get_edid(connectow, tve->ddc);
	if (edid) {
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		wet = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}

	wetuwn wet;
}

static enum dwm_mode_status
imx_tve_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			     stwuct dwm_dispway_mode *mode)
{
	stwuct imx_tve *tve = con_to_tve(connectow);
	unsigned wong wate;

	/* pixew cwock with 2x ovewsampwing */
	wate = cwk_wound_wate(tve->cwk, 2000UW * mode->cwock) / 2000;
	if (wate == mode->cwock)
		wetuwn MODE_OK;

	/* pixew cwock without ovewsampwing */
	wate = cwk_wound_wate(tve->cwk, 1000UW * mode->cwock) / 1000;
	if (wate == mode->cwock)
		wetuwn MODE_OK;

	dev_wawn(tve->dev, "ignowing mode %dx%d\n",
		 mode->hdispway, mode->vdispway);

	wetuwn MODE_BAD;
}

static void imx_tve_encodew_mode_set(stwuct dwm_encodew *encodew,
				     stwuct dwm_dispway_mode *owig_mode,
				     stwuct dwm_dispway_mode *mode)
{
	stwuct imx_tve *tve = enc_to_tve(encodew);
	unsigned wong wounded_wate;
	unsigned wong wate;
	int div = 1;
	int wet;

	/*
	 * FIXME
	 * we shouwd twy 4k * mode->cwock fiwst,
	 * and enabwe 4x ovewsampwing fow wowew wesowutions
	 */
	wate = 2000UW * mode->cwock;
	cwk_set_wate(tve->cwk, wate);
	wounded_wate = cwk_get_wate(tve->cwk);
	if (wounded_wate >= wate)
		div = 2;
	cwk_set_wate(tve->di_cwk, wounded_wate / div);

	wet = cwk_set_pawent(tve->di_sew_cwk, tve->di_cwk);
	if (wet < 0) {
		dev_eww(tve->dev, "faiwed to set di_sew pawent to tve_di: %d\n",
			wet);
	}

	wegmap_update_bits(tve->wegmap, TVE_COM_CONF_WEG,
			   TVE_IPU_CWK_EN, TVE_IPU_CWK_EN);

	if (tve->mode == TVE_MODE_VGA)
		wet = tve_setup_vga(tve);
	ewse
		wet = tve_setup_tvout(tve);
	if (wet)
		dev_eww(tve->dev, "faiwed to set configuwation: %d\n", wet);
}

static void imx_tve_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct imx_tve *tve = enc_to_tve(encodew);

	tve_enabwe(tve);
}

static void imx_tve_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct imx_tve *tve = enc_to_tve(encodew);

	tve_disabwe(tve);
}

static int imx_tve_atomic_check(stwuct dwm_encodew *encodew,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_connectow_state *conn_state)
{
	stwuct imx_cwtc_state *imx_cwtc_state = to_imx_cwtc_state(cwtc_state);
	stwuct imx_tve *tve = enc_to_tve(encodew);

	imx_cwtc_state->bus_fowmat = MEDIA_BUS_FMT_GBW888_1X24;
	imx_cwtc_state->di_hsync_pin = tve->di_hsync_pin;
	imx_cwtc_state->di_vsync_pin = tve->di_vsync_pin;

	wetuwn 0;
}

static const stwuct dwm_connectow_funcs imx_tve_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = imx_dwm_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_connectow_hewpew_funcs imx_tve_connectow_hewpew_funcs = {
	.get_modes = imx_tve_connectow_get_modes,
	.mode_vawid = imx_tve_connectow_mode_vawid,
};

static const stwuct dwm_encodew_hewpew_funcs imx_tve_encodew_hewpew_funcs = {
	.mode_set = imx_tve_encodew_mode_set,
	.enabwe = imx_tve_encodew_enabwe,
	.disabwe = imx_tve_encodew_disabwe,
	.atomic_check = imx_tve_atomic_check,
};

static iwqwetuwn_t imx_tve_iwq_handwew(int iwq, void *data)
{
	stwuct imx_tve *tve = data;
	unsigned int vaw;

	wegmap_wead(tve->wegmap, TVE_STAT_WEG, &vaw);

	/* cweaw intewwupt status wegistew */
	wegmap_wwite(tve->wegmap, TVE_STAT_WEG, 0xffffffff);

	wetuwn IWQ_HANDWED;
}

static unsigned wong cwk_tve_di_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct imx_tve *tve = containew_of(hw, stwuct imx_tve, cwk_hw_di);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(tve->wegmap, TVE_COM_CONF_WEG, &vaw);
	if (wet < 0)
		wetuwn 0;

	switch (vaw & TVE_DAC_SAMP_WATE_MASK) {
	case TVE_DAC_DIV4_WATE:
		wetuwn pawent_wate / 4;
	case TVE_DAC_DIV2_WATE:
		wetuwn pawent_wate / 2;
	case TVE_DAC_FUWW_WATE:
	defauwt:
		wetuwn pawent_wate;
	}

	wetuwn 0;
}

static wong cwk_tve_di_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	unsigned wong div;

	div = *pwate / wate;
	if (div >= 4)
		wetuwn *pwate / 4;
	ewse if (div >= 2)
		wetuwn *pwate / 2;
	wetuwn *pwate;
}

static int cwk_tve_di_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct imx_tve *tve = containew_of(hw, stwuct imx_tve, cwk_hw_di);
	unsigned wong div;
	u32 vaw;
	int wet;

	div = pawent_wate / wate;
	if (div >= 4)
		vaw = TVE_DAC_DIV4_WATE;
	ewse if (div >= 2)
		vaw = TVE_DAC_DIV2_WATE;
	ewse
		vaw = TVE_DAC_FUWW_WATE;

	wet = wegmap_update_bits(tve->wegmap, TVE_COM_CONF_WEG,
				 TVE_DAC_SAMP_WATE_MASK, vaw);

	if (wet < 0) {
		dev_eww(tve->dev, "faiwed to set dividew: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct cwk_ops cwk_tve_di_ops = {
	.wound_wate = cwk_tve_di_wound_wate,
	.set_wate = cwk_tve_di_set_wate,
	.wecawc_wate = cwk_tve_di_wecawc_wate,
};

static int tve_cwk_init(stwuct imx_tve *tve, void __iomem *base)
{
	const chaw *tve_di_pawent[1];
	stwuct cwk_init_data init = {
		.name = "tve_di",
		.ops = &cwk_tve_di_ops,
		.num_pawents = 1,
		.fwags = 0,
	};

	tve_di_pawent[0] = __cwk_get_name(tve->cwk);
	init.pawent_names = (const chaw **)&tve_di_pawent;

	tve->cwk_hw_di.init = &init;
	tve->di_cwk = devm_cwk_wegistew(tve->dev, &tve->cwk_hw_di);
	if (IS_EWW(tve->di_cwk)) {
		dev_eww(tve->dev, "faiwed to wegistew TVE output cwock: %wd\n",
			PTW_EWW(tve->di_cwk));
		wetuwn PTW_EWW(tve->di_cwk);
	}

	wetuwn 0;
}

static void imx_tve_disabwe_weguwatow(void *data)
{
	stwuct imx_tve *tve = data;

	weguwatow_disabwe(tve->dac_weg);
}

static boow imx_tve_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg % 4 == 0) && (weg <= 0xdc);
}

static stwuct wegmap_config tve_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,

	.weadabwe_weg = imx_tve_weadabwe_weg,

	.fast_io = twue,

	.max_wegistew = 0xdc,
};

static const chaw * const imx_tve_modes[] = {
	[TVE_MODE_TVOUT]  = "tvout",
	[TVE_MODE_VGA] = "vga",
};

static int of_get_tve_mode(stwuct device_node *np)
{
	const chaw *bm;
	int wet, i;

	wet = of_pwopewty_wead_stwing(np, "fsw,tve-mode", &bm);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(imx_tve_modes); i++)
		if (!stwcasecmp(bm, imx_tve_modes[i]))
			wetuwn i;

	wetuwn -EINVAW;
}

static int imx_tve_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct imx_tve *tve = dev_get_dwvdata(dev);
	stwuct imx_tve_encodew *tvee;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	int encodew_type;
	int wet;

	encodew_type = tve->mode == TVE_MODE_VGA ?
		       DWM_MODE_ENCODEW_DAC : DWM_MODE_ENCODEW_TVDAC;

	tvee = dwmm_simpwe_encodew_awwoc(dwm, stwuct imx_tve_encodew, encodew,
					 encodew_type);
	if (IS_EWW(tvee))
		wetuwn PTW_EWW(tvee);

	tvee->tve = tve;
	encodew = &tvee->encodew;
	connectow = &tvee->connectow;

	wet = imx_dwm_encodew_pawse_of(dwm, encodew, tve->dev->of_node);
	if (wet)
		wetuwn wet;

	dwm_encodew_hewpew_add(encodew, &imx_tve_encodew_hewpew_funcs);

	dwm_connectow_hewpew_add(connectow, &imx_tve_connectow_hewpew_funcs);
	wet = dwm_connectow_init_with_ddc(dwm, connectow,
					  &imx_tve_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA, tve->ddc);
	if (wet)
		wetuwn wet;

	wetuwn dwm_connectow_attach_encodew(connectow, encodew);
}

static const stwuct component_ops imx_tve_ops = {
	.bind	= imx_tve_bind,
};

static int imx_tve_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *ddc_node;
	stwuct imx_tve *tve;
	void __iomem *base;
	unsigned int vaw;
	int iwq;
	int wet;

	tve = devm_kzawwoc(dev, sizeof(*tve), GFP_KEWNEW);
	if (!tve)
		wetuwn -ENOMEM;

	tve->dev = dev;

	ddc_node = of_pawse_phandwe(np, "ddc-i2c-bus", 0);
	if (ddc_node) {
		tve->ddc = of_find_i2c_adaptew_by_node(ddc_node);
		of_node_put(ddc_node);
	}

	tve->mode = of_get_tve_mode(np);
	if (tve->mode != TVE_MODE_VGA) {
		dev_eww(dev, "onwy VGA mode suppowted, cuwwentwy\n");
		wetuwn -EINVAW;
	}

	if (tve->mode == TVE_MODE_VGA) {
		wet = of_pwopewty_wead_u32(np, "fsw,hsync-pin",
					   &tve->di_hsync_pin);

		if (wet < 0) {
			dev_eww(dev, "faiwed to get hsync pin\n");
			wetuwn wet;
		}

		wet = of_pwopewty_wead_u32(np, "fsw,vsync-pin",
					   &tve->di_vsync_pin);

		if (wet < 0) {
			dev_eww(dev, "faiwed to get vsync pin\n");
			wetuwn wet;
		}
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	tve_wegmap_config.wock_awg = tve;
	tve->wegmap = devm_wegmap_init_mmio_cwk(dev, "tve", base,
						&tve_wegmap_config);
	if (IS_EWW(tve->wegmap)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(tve->wegmap));
		wetuwn PTW_EWW(tve->wegmap);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					imx_tve_iwq_handwew, IWQF_ONESHOT,
					"imx-tve", tve);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wequest iwq: %d\n", wet);
		wetuwn wet;
	}

	tve->dac_weg = devm_weguwatow_get(dev, "dac");
	if (!IS_EWW(tve->dac_weg)) {
		if (weguwatow_get_vowtage(tve->dac_weg) != IMX_TVE_DAC_VOWTAGE)
			dev_wawn(dev, "dac vowtage is not %d uV\n", IMX_TVE_DAC_VOWTAGE);
		wet = weguwatow_enabwe(tve->dac_weg);
		if (wet)
			wetuwn wet;
		wet = devm_add_action_ow_weset(dev, imx_tve_disabwe_weguwatow, tve);
		if (wet)
			wetuwn wet;
	}

	tve->cwk = devm_cwk_get(dev, "tve");
	if (IS_EWW(tve->cwk)) {
		dev_eww(dev, "faiwed to get high speed tve cwock: %wd\n",
			PTW_EWW(tve->cwk));
		wetuwn PTW_EWW(tve->cwk);
	}

	/* this is the IPU DI cwock input sewectow, can be pawented to tve_di */
	tve->di_sew_cwk = devm_cwk_get(dev, "di_sew");
	if (IS_EWW(tve->di_sew_cwk)) {
		dev_eww(dev, "faiwed to get ipu di mux cwock: %wd\n",
			PTW_EWW(tve->di_sew_cwk));
		wetuwn PTW_EWW(tve->di_sew_cwk);
	}

	wet = tve_cwk_init(tve, base);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(tve->wegmap, TVE_COM_CONF_WEG, &vaw);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead configuwation wegistew: %d\n",
			wet);
		wetuwn wet;
	}
	if (vaw != 0x00100000) {
		dev_eww(dev, "configuwation wegistew defauwt vawue indicates this is not a TVEv2\n");
		wetuwn -ENODEV;
	}

	/* disabwe cabwe detection fow VGA mode */
	wet = wegmap_wwite(tve->wegmap, TVE_CD_CONT_WEG, 0);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, tve);

	wetuwn component_add(dev, &imx_tve_ops);
}

static void imx_tve_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &imx_tve_ops);
}

static const stwuct of_device_id imx_tve_dt_ids[] = {
	{ .compatibwe = "fsw,imx53-tve", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_tve_dt_ids);

static stwuct pwatfowm_dwivew imx_tve_dwivew = {
	.pwobe		= imx_tve_pwobe,
	.wemove_new	= imx_tve_wemove,
	.dwivew		= {
		.of_match_tabwe = imx_tve_dt_ids,
		.name	= "imx-tve",
	},
};

moduwe_pwatfowm_dwivew(imx_tve_dwivew);

MODUWE_DESCWIPTION("i.MX Tewevision Encodew dwivew");
MODUWE_AUTHOW("Phiwipp Zabew, Pengutwonix");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:imx-tve");
