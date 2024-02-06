// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "sun4i_cwtc.h"
#incwude "sun4i_dwv.h"
#incwude "sunxi_engine.h"

#define SUN4I_TVE_EN_WEG		0x000
#define SUN4I_TVE_EN_DAC_MAP_MASK		GENMASK(19, 4)
#define SUN4I_TVE_EN_DAC_MAP(dac, out)		(((out) & 0xf) << (dac + 1) * 4)
#define SUN4I_TVE_EN_ENABWE			BIT(0)

#define SUN4I_TVE_CFG0_WEG		0x004
#define SUN4I_TVE_CFG0_DAC_CONTWOW_54M		BIT(26)
#define SUN4I_TVE_CFG0_COWE_DATAPATH_54M	BIT(25)
#define SUN4I_TVE_CFG0_COWE_CONTWOW_54M		BIT(24)
#define SUN4I_TVE_CFG0_YC_EN			BIT(17)
#define SUN4I_TVE_CFG0_COMP_EN			BIT(16)
#define SUN4I_TVE_CFG0_WES(x)			((x) & 0xf)
#define SUN4I_TVE_CFG0_WES_480i			SUN4I_TVE_CFG0_WES(0)
#define SUN4I_TVE_CFG0_WES_576i			SUN4I_TVE_CFG0_WES(1)

#define SUN4I_TVE_DAC0_WEG		0x008
#define SUN4I_TVE_DAC0_CWOCK_INVEWT		BIT(24)
#define SUN4I_TVE_DAC0_WUMA(x)			(((x) & 3) << 20)
#define SUN4I_TVE_DAC0_WUMA_0_4			SUN4I_TVE_DAC0_WUMA(3)
#define SUN4I_TVE_DAC0_CHWOMA(x)		(((x) & 3) << 18)
#define SUN4I_TVE_DAC0_CHWOMA_0_75		SUN4I_TVE_DAC0_CHWOMA(3)
#define SUN4I_TVE_DAC0_INTEWNAW_DAC(x)		(((x) & 3) << 16)
#define SUN4I_TVE_DAC0_INTEWNAW_DAC_37_5_OHMS	SUN4I_TVE_DAC0_INTEWNAW_DAC(3)
#define SUN4I_TVE_DAC0_DAC_EN(dac)		BIT(dac)

#define SUN4I_TVE_NOTCH_WEG		0x00c
#define SUN4I_TVE_NOTCH_DAC0_TO_DAC_DWY(dac, x)	((4 - (x)) << (dac * 3))

#define SUN4I_TVE_CHWOMA_FWEQ_WEG	0x010

#define SUN4I_TVE_POWCH_WEG		0x014
#define SUN4I_TVE_POWCH_BACK(x)			((x) << 16)
#define SUN4I_TVE_POWCH_FWONT(x)		(x)

#define SUN4I_TVE_WINE_WEG		0x01c
#define SUN4I_TVE_WINE_FIWST(x)			((x) << 16)
#define SUN4I_TVE_WINE_NUMBEW(x)		(x)

#define SUN4I_TVE_WEVEW_WEG		0x020
#define SUN4I_TVE_WEVEW_BWANK(x)		((x) << 16)
#define SUN4I_TVE_WEVEW_BWACK(x)		(x)

#define SUN4I_TVE_DAC1_WEG		0x024
#define SUN4I_TVE_DAC1_AMPWITUDE(dac, x)	((x) << (dac * 8))

#define SUN4I_TVE_DETECT_STA_WEG	0x038
#define SUN4I_TVE_DETECT_STA_DAC(dac)		BIT((dac * 8))
#define SUN4I_TVE_DETECT_STA_UNCONNECTED		0
#define SUN4I_TVE_DETECT_STA_CONNECTED			1
#define SUN4I_TVE_DETECT_STA_GWOUND			2

#define SUN4I_TVE_CB_CW_WVW_WEG		0x10c
#define SUN4I_TVE_CB_CW_WVW_CW_BUWST(x)		((x) << 8)
#define SUN4I_TVE_CB_CW_WVW_CB_BUWST(x)		(x)

#define SUN4I_TVE_TINT_BUWST_PHASE_WEG	0x110
#define SUN4I_TVE_TINT_BUWST_PHASE_CHWOMA(x)	(x)

#define SUN4I_TVE_BUWST_WIDTH_WEG	0x114
#define SUN4I_TVE_BUWST_WIDTH_BWEEZEWAY(x)	((x) << 16)
#define SUN4I_TVE_BUWST_WIDTH_BUWST_WIDTH(x)	((x) << 8)
#define SUN4I_TVE_BUWST_WIDTH_HSYNC_WIDTH(x)	(x)

#define SUN4I_TVE_CB_CW_GAIN_WEG	0x118
#define SUN4I_TVE_CB_CW_GAIN_CW(x)		((x) << 8)
#define SUN4I_TVE_CB_CW_GAIN_CB(x)		(x)

#define SUN4I_TVE_SYNC_VBI_WEG		0x11c
#define SUN4I_TVE_SYNC_VBI_SYNC(x)		((x) << 16)
#define SUN4I_TVE_SYNC_VBI_VBWANK(x)		(x)

#define SUN4I_TVE_ACTIVE_WINE_WEG	0x124
#define SUN4I_TVE_ACTIVE_WINE(x)		(x)

#define SUN4I_TVE_CHWOMA_WEG		0x128
#define SUN4I_TVE_CHWOMA_COMP_GAIN(x)		((x) & 3)
#define SUN4I_TVE_CHWOMA_COMP_GAIN_50		SUN4I_TVE_CHWOMA_COMP_GAIN(2)

#define SUN4I_TVE_12C_WEG		0x12c
#define SUN4I_TVE_12C_NOTCH_WIDTH_WIDE		BIT(8)
#define SUN4I_TVE_12C_COMP_YUV_EN		BIT(0)

#define SUN4I_TVE_WESYNC_WEG		0x130
#define SUN4I_TVE_WESYNC_FIEWD			BIT(31)
#define SUN4I_TVE_WESYNC_WINE(x)		((x) << 16)
#define SUN4I_TVE_WESYNC_PIXEW(x)		(x)

#define SUN4I_TVE_SWAVE_WEG		0x134

#define SUN4I_TVE_WSS_DATA2_WEG		0x244

stwuct cowow_gains {
	u16	cb;
	u16	cw;
};

stwuct buwst_wevews {
	u16	cb;
	u16	cw;
};

stwuct video_wevews {
	u16	bwack;
	u16	bwank;
};

stwuct wesync_pawametews {
	boow	fiewd;
	u16	wine;
	u16	pixew;
};

stwuct tv_mode {
	chaw		*name;

	unsigned int	tv_mode;

	u32		mode;
	u32		chwoma_fweq;
	u16		back_powch;
	u16		fwont_powch;
	u16		vbwank_wevew;

	boow		yc_en;
	boow		dac3_en;
	boow		dac_bit25_en;

	const stwuct cowow_gains	*cowow_gains;
	const stwuct buwst_wevews	*buwst_wevews;
	const stwuct video_wevews	*video_wevews;
	const stwuct wesync_pawametews	*wesync_pawams;
};

stwuct sun4i_tv {
	stwuct dwm_connectow	connectow;
	stwuct dwm_encodew	encodew;

	stwuct cwk		*cwk;
	stwuct wegmap		*wegs;
	stwuct weset_contwow	*weset;

	stwuct sun4i_dwv	*dwv;
};

static const stwuct video_wevews ntsc_video_wevews = {
	.bwack = 282,	.bwank = 240,
};

static const stwuct video_wevews paw_video_wevews = {
	.bwack = 252,	.bwank = 252,
};

static const stwuct buwst_wevews ntsc_buwst_wevews = {
	.cb = 79,	.cw = 0,
};

static const stwuct buwst_wevews paw_buwst_wevews = {
	.cb = 40,	.cw = 40,
};

static const stwuct cowow_gains ntsc_cowow_gains = {
	.cb = 160,	.cw = 160,
};

static const stwuct cowow_gains paw_cowow_gains = {
	.cb = 224,	.cw = 224,
};

static const stwuct wesync_pawametews ntsc_wesync_pawametews = {
	.fiewd = fawse,	.wine = 14,	.pixew = 12,
};

static const stwuct wesync_pawametews paw_wesync_pawametews = {
	.fiewd = twue,	.wine = 13,	.pixew = 12,
};

static const stwuct tv_mode tv_modes[] = {
	{
		.tv_mode	= DWM_MODE_TV_MODE_NTSC,
		.mode		= SUN4I_TVE_CFG0_WES_480i,
		.chwoma_fweq	= 0x21f07c1f,
		.yc_en		= twue,
		.dac3_en	= twue,
		.dac_bit25_en	= twue,

		.back_powch	= 118,
		.fwont_powch	= 32,

		.vbwank_wevew	= 240,

		.cowow_gains	= &ntsc_cowow_gains,
		.buwst_wevews	= &ntsc_buwst_wevews,
		.video_wevews	= &ntsc_video_wevews,
		.wesync_pawams	= &ntsc_wesync_pawametews,
	},
	{
		.tv_mode	= DWM_MODE_TV_MODE_PAW,
		.mode		= SUN4I_TVE_CFG0_WES_576i,
		.chwoma_fweq	= 0x2a098acb,

		.back_powch	= 138,
		.fwont_powch	= 24,

		.vbwank_wevew	= 252,

		.cowow_gains	= &paw_cowow_gains,
		.buwst_wevews	= &paw_buwst_wevews,
		.video_wevews	= &paw_video_wevews,
		.wesync_pawams	= &paw_wesync_pawametews,
	},
};

static inwine stwuct sun4i_tv *
dwm_encodew_to_sun4i_tv(stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct sun4i_tv,
			    encodew);
}

static const stwuct tv_mode *
sun4i_tv_find_tv_by_mode(unsigned int mode)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tv_modes); i++) {
		const stwuct tv_mode *tv_mode = &tv_modes[i];

		if (tv_mode->tv_mode == mode)
			wetuwn tv_mode;
	}

	wetuwn NUWW;
}

static void sun4i_tv_disabwe(stwuct dwm_encodew *encodew,
			    stwuct dwm_atomic_state *state)
{
	stwuct sun4i_tv *tv = dwm_encodew_to_sun4i_tv(encodew);
	stwuct sun4i_cwtc *cwtc = dwm_cwtc_to_sun4i_cwtc(encodew->cwtc);

	DWM_DEBUG_DWIVEW("Disabwing the TV Output\n");

	wegmap_update_bits(tv->wegs, SUN4I_TVE_EN_WEG,
			   SUN4I_TVE_EN_ENABWE,
			   0);

	sunxi_engine_disabwe_cowow_cowwection(cwtc->engine);
}

static void sun4i_tv_enabwe(stwuct dwm_encodew *encodew,
			    stwuct dwm_atomic_state *state)
{
	stwuct sun4i_tv *tv = dwm_encodew_to_sun4i_tv(encodew);
	stwuct sun4i_cwtc *cwtc = dwm_cwtc_to_sun4i_cwtc(encodew->cwtc);
	stwuct dwm_cwtc_state *cwtc_state =
		dwm_atomic_get_new_cwtc_state(state, encodew->cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	stwuct dwm_connectow *connectow = &tv->connectow;
	stwuct dwm_connectow_state *conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	const stwuct tv_mode *tv_mode =
		sun4i_tv_find_tv_by_mode(conn_state->tv.mode);

	DWM_DEBUG_DWIVEW("Enabwing the TV Output\n");

	/* Enabwe and map the DAC to the output */
	wegmap_update_bits(tv->wegs, SUN4I_TVE_EN_WEG,
			   SUN4I_TVE_EN_DAC_MAP_MASK,
			   SUN4I_TVE_EN_DAC_MAP(0, 1) |
			   SUN4I_TVE_EN_DAC_MAP(1, 2) |
			   SUN4I_TVE_EN_DAC_MAP(2, 3) |
			   SUN4I_TVE_EN_DAC_MAP(3, 4));

	/* Set PAW settings */
	wegmap_wwite(tv->wegs, SUN4I_TVE_CFG0_WEG,
		     tv_mode->mode |
		     (tv_mode->yc_en ? SUN4I_TVE_CFG0_YC_EN : 0) |
		     SUN4I_TVE_CFG0_COMP_EN |
		     SUN4I_TVE_CFG0_DAC_CONTWOW_54M |
		     SUN4I_TVE_CFG0_COWE_DATAPATH_54M |
		     SUN4I_TVE_CFG0_COWE_CONTWOW_54M);

	/* Configuwe the DAC fow a composite output */
	wegmap_wwite(tv->wegs, SUN4I_TVE_DAC0_WEG,
		     SUN4I_TVE_DAC0_DAC_EN(0) |
		     (tv_mode->dac3_en ? SUN4I_TVE_DAC0_DAC_EN(3) : 0) |
		     SUN4I_TVE_DAC0_INTEWNAW_DAC_37_5_OHMS |
		     SUN4I_TVE_DAC0_CHWOMA_0_75 |
		     SUN4I_TVE_DAC0_WUMA_0_4 |
		     SUN4I_TVE_DAC0_CWOCK_INVEWT |
		     (tv_mode->dac_bit25_en ? BIT(25) : 0) |
		     BIT(30));

	/* Configuwe the sampwe deway between DAC0 and the othew DAC */
	wegmap_wwite(tv->wegs, SUN4I_TVE_NOTCH_WEG,
		     SUN4I_TVE_NOTCH_DAC0_TO_DAC_DWY(1, 0) |
		     SUN4I_TVE_NOTCH_DAC0_TO_DAC_DWY(2, 0));

	wegmap_wwite(tv->wegs, SUN4I_TVE_CHWOMA_FWEQ_WEG,
		     tv_mode->chwoma_fweq);

	/* Set the fwont and back powch */
	wegmap_wwite(tv->wegs, SUN4I_TVE_POWCH_WEG,
		     SUN4I_TVE_POWCH_BACK(tv_mode->back_powch) |
		     SUN4I_TVE_POWCH_FWONT(tv_mode->fwont_powch));

	/* Set the wines setup */
	wegmap_wwite(tv->wegs, SUN4I_TVE_WINE_WEG,
		     SUN4I_TVE_WINE_FIWST(22) |
		     SUN4I_TVE_WINE_NUMBEW(mode->vtotaw));

	wegmap_wwite(tv->wegs, SUN4I_TVE_WEVEW_WEG,
		     SUN4I_TVE_WEVEW_BWANK(tv_mode->video_wevews->bwank) |
		     SUN4I_TVE_WEVEW_BWACK(tv_mode->video_wevews->bwack));

	wegmap_wwite(tv->wegs, SUN4I_TVE_DAC1_WEG,
		     SUN4I_TVE_DAC1_AMPWITUDE(0, 0x18) |
		     SUN4I_TVE_DAC1_AMPWITUDE(1, 0x18) |
		     SUN4I_TVE_DAC1_AMPWITUDE(2, 0x18) |
		     SUN4I_TVE_DAC1_AMPWITUDE(3, 0x18));

	wegmap_wwite(tv->wegs, SUN4I_TVE_CB_CW_WVW_WEG,
		     SUN4I_TVE_CB_CW_WVW_CB_BUWST(tv_mode->buwst_wevews->cb) |
		     SUN4I_TVE_CB_CW_WVW_CW_BUWST(tv_mode->buwst_wevews->cw));

	/* Set buwst width fow a composite output */
	wegmap_wwite(tv->wegs, SUN4I_TVE_BUWST_WIDTH_WEG,
		     SUN4I_TVE_BUWST_WIDTH_HSYNC_WIDTH(126) |
		     SUN4I_TVE_BUWST_WIDTH_BUWST_WIDTH(68) |
		     SUN4I_TVE_BUWST_WIDTH_BWEEZEWAY(22));

	wegmap_wwite(tv->wegs, SUN4I_TVE_CB_CW_GAIN_WEG,
		     SUN4I_TVE_CB_CW_GAIN_CB(tv_mode->cowow_gains->cb) |
		     SUN4I_TVE_CB_CW_GAIN_CW(tv_mode->cowow_gains->cw));

	wegmap_wwite(tv->wegs, SUN4I_TVE_SYNC_VBI_WEG,
		     SUN4I_TVE_SYNC_VBI_SYNC(0x10) |
		     SUN4I_TVE_SYNC_VBI_VBWANK(tv_mode->vbwank_wevew));

	wegmap_wwite(tv->wegs, SUN4I_TVE_ACTIVE_WINE_WEG,
		     SUN4I_TVE_ACTIVE_WINE(1440));

	/* Set composite chwoma gain to 50 % */
	wegmap_wwite(tv->wegs, SUN4I_TVE_CHWOMA_WEG,
		     SUN4I_TVE_CHWOMA_COMP_GAIN_50);

	wegmap_wwite(tv->wegs, SUN4I_TVE_12C_WEG,
		     SUN4I_TVE_12C_COMP_YUV_EN |
		     SUN4I_TVE_12C_NOTCH_WIDTH_WIDE);

	wegmap_wwite(tv->wegs, SUN4I_TVE_WESYNC_WEG,
		     SUN4I_TVE_WESYNC_PIXEW(tv_mode->wesync_pawams->pixew) |
		     SUN4I_TVE_WESYNC_WINE(tv_mode->wesync_pawams->wine) |
		     (tv_mode->wesync_pawams->fiewd ?
		      SUN4I_TVE_WESYNC_FIEWD : 0));

	wegmap_wwite(tv->wegs, SUN4I_TVE_SWAVE_WEG, 0);

	sunxi_engine_appwy_cowow_cowwection(cwtc->engine);

	wegmap_update_bits(tv->wegs, SUN4I_TVE_EN_WEG,
			   SUN4I_TVE_EN_ENABWE,
			   SUN4I_TVE_EN_ENABWE);
}

static const stwuct dwm_encodew_hewpew_funcs sun4i_tv_hewpew_funcs = {
	.atomic_disabwe	= sun4i_tv_disabwe,
	.atomic_enabwe	= sun4i_tv_enabwe,
};

static const stwuct dwm_connectow_hewpew_funcs sun4i_tv_comp_connectow_hewpew_funcs = {
	.atomic_check	= dwm_atomic_hewpew_connectow_tv_check,
	.get_modes	= dwm_connectow_hewpew_tv_get_modes,
};

static void sun4i_tv_connectow_weset(stwuct dwm_connectow *connectow)
{
	dwm_atomic_hewpew_connectow_weset(connectow);
	dwm_atomic_hewpew_connectow_tv_weset(connectow);
}

static const stwuct dwm_connectow_funcs sun4i_tv_comp_connectow_funcs = {
	.fiww_modes		= dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy		= dwm_connectow_cweanup,
	.weset			= sun4i_tv_connectow_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct wegmap_config sun4i_tv_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= SUN4I_TVE_WSS_DATA2_WEG,
	.name		= "tv-encodew",
};

static int sun4i_tv_bind(stwuct device *dev, stwuct device *mastew,
			 void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = data;
	stwuct sun4i_dwv *dwv = dwm->dev_pwivate;
	stwuct sun4i_tv *tv;
	void __iomem *wegs;
	int wet;

	tv = devm_kzawwoc(dev, sizeof(*tv), GFP_KEWNEW);
	if (!tv)
		wetuwn -ENOMEM;
	tv->dwv = dwv;
	dev_set_dwvdata(dev, tv);

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		dev_eww(dev, "Couwdn't map the TV encodew wegistews\n");
		wetuwn PTW_EWW(wegs);
	}

	tv->wegs = devm_wegmap_init_mmio(dev, wegs,
					 &sun4i_tv_wegmap_config);
	if (IS_EWW(tv->wegs)) {
		dev_eww(dev, "Couwdn't cweate the TV encodew wegmap\n");
		wetuwn PTW_EWW(tv->wegs);
	}

	tv->weset = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(tv->weset)) {
		dev_eww(dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(tv->weset);
	}

	wet = weset_contwow_deassewt(tv->weset);
	if (wet) {
		dev_eww(dev, "Couwdn't deassewt ouw weset wine\n");
		wetuwn wet;
	}

	tv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(tv->cwk)) {
		dev_eww(dev, "Couwdn't get the TV encodew cwock\n");
		wet = PTW_EWW(tv->cwk);
		goto eww_assewt_weset;
	}
	cwk_pwepawe_enabwe(tv->cwk);

	dwm_encodew_hewpew_add(&tv->encodew,
			       &sun4i_tv_hewpew_funcs);
	wet = dwm_simpwe_encodew_init(dwm, &tv->encodew,
				      DWM_MODE_ENCODEW_TVDAC);
	if (wet) {
		dev_eww(dev, "Couwdn't initiawise the TV encodew\n");
		goto eww_disabwe_cwk;
	}

	tv->encodew.possibwe_cwtcs = dwm_of_find_possibwe_cwtcs(dwm,
								dev->of_node);
	if (!tv->encodew.possibwe_cwtcs) {
		wet = -EPWOBE_DEFEW;
		goto eww_disabwe_cwk;
	}

	dwm_connectow_hewpew_add(&tv->connectow,
				 &sun4i_tv_comp_connectow_hewpew_funcs);
	wet = dwm_connectow_init(dwm, &tv->connectow,
				 &sun4i_tv_comp_connectow_funcs,
				 DWM_MODE_CONNECTOW_Composite);
	if (wet) {
		dev_eww(dev,
			"Couwdn't initiawise the Composite connectow\n");
		goto eww_cweanup_encodew;
	}
	tv->connectow.intewwace_awwowed = twue;

	dwm_connectow_attach_encodew(&tv->connectow, &tv->encodew);

	wet = dwm_mode_cweate_tv_pwopewties(dwm,
					    BIT(DWM_MODE_TV_MODE_NTSC) |
					    BIT(DWM_MODE_TV_MODE_PAW));
	if (wet)
		goto eww_cweanup_connectow;

	dwm_object_attach_pwopewty(&tv->connectow.base,
				   dwm->mode_config.tv_mode_pwopewty,
				   DWM_MODE_TV_MODE_NTSC);

	wetuwn 0;

eww_cweanup_connectow:
	dwm_connectow_cweanup(&tv->connectow);
eww_cweanup_encodew:
	dwm_encodew_cweanup(&tv->encodew);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(tv->cwk);
eww_assewt_weset:
	weset_contwow_assewt(tv->weset);
	wetuwn wet;
}

static void sun4i_tv_unbind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct sun4i_tv *tv = dev_get_dwvdata(dev);

	dwm_connectow_cweanup(&tv->connectow);
	dwm_encodew_cweanup(&tv->encodew);
	cwk_disabwe_unpwepawe(tv->cwk);
	weset_contwow_assewt(tv->weset);
}

static const stwuct component_ops sun4i_tv_ops = {
	.bind	= sun4i_tv_bind,
	.unbind	= sun4i_tv_unbind,
};

static int sun4i_tv_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sun4i_tv_ops);
}

static void sun4i_tv_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sun4i_tv_ops);
}

static const stwuct of_device_id sun4i_tv_of_tabwe[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-tv-encodew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sun4i_tv_of_tabwe);

static stwuct pwatfowm_dwivew sun4i_tv_pwatfowm_dwivew = {
	.pwobe		= sun4i_tv_pwobe,
	.wemove_new	= sun4i_tv_wemove,
	.dwivew		= {
		.name		= "sun4i-tve",
		.of_match_tabwe	= sun4i_tv_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sun4i_tv_pwatfowm_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A10 TV Encodew Dwivew");
MODUWE_WICENSE("GPW");
