// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Wenesas WZ/G2W MIPI CSI-2 Weceivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/sys_soc.h>
#incwude <winux/units.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>

/* WINK wegistews */
/* Moduwe Configuwation Wegistew */
#define CSI2nMCG			0x0
#define CSI2nMCG_SDWN			GENMASK(11, 8)

/* Moduwe Contwow Wegistew 0 */
#define CSI2nMCT0			0x10
#define CSI2nMCT0_VDWN(x)		((x) << 0)

/* Moduwe Contwow Wegistew 2 */
#define CSI2nMCT2			0x18
#define CSI2nMCT2_FWWSKW(x)		((x) << 16)
#define CSI2nMCT2_FWWCWK(x)		((x) << 0)

/* Moduwe Contwow Wegistew 3 */
#define CSI2nMCT3			0x1c
#define CSI2nMCT3_WXEN			BIT(0)

/* Weset Contwow Wegistew */
#define CSI2nWTCT			0x28
#define CSI2nWTCT_VSWST			BIT(0)

/* Weset Status Wegistew */
#define CSI2nWTST			0x2c
#define CSI2nWTST_VSWSTS		BIT(0)

/* Weceive Data Type Enabwe Wow Wegistew */
#define CSI2nDTEW			0x60

/* Weceive Data Type Enabwe High Wegistew */
#define CSI2nDTEH			0x64

/* DPHY wegistews */
/* D-PHY Contwow Wegistew 0 */
#define CSIDPHYCTWW0			0x400
#define CSIDPHYCTWW0_EN_WDO1200		BIT(1)
#define CSIDPHYCTWW0_EN_BGW		BIT(0)

/* D-PHY Timing Wegistew 0 */
#define CSIDPHYTIM0			0x404
#define CSIDPHYTIM0_TCWK_MISS(x)	((x) << 24)
#define CSIDPHYTIM0_T_INIT(x)		((x) << 0)

/* D-PHY Timing Wegistew 1 */
#define CSIDPHYTIM1			0x408
#define CSIDPHYTIM1_THS_PWEPAWE(x)	((x) << 24)
#define CSIDPHYTIM1_TCWK_PWEPAWE(x)	((x) << 16)
#define CSIDPHYTIM1_THS_SETTWE(x)	((x) << 8)
#define CSIDPHYTIM1_TCWK_SETTWE(x)	((x) << 0)

/* D-PHY Skew Adjustment Function */
#define CSIDPHYSKW0			0x460
#define CSIDPHYSKW0_UTIW_DW0_SKW_ADJ(x)	((x) & 0x3)
#define CSIDPHYSKW0_UTIW_DW1_SKW_ADJ(x)	(((x) & 0x3) << 4)
#define CSIDPHYSKW0_UTIW_DW2_SKW_ADJ(x)	(((x) & 0x3) << 8)
#define CSIDPHYSKW0_UTIW_DW3_SKW_ADJ(x)	(((x) & 0x3) << 12)
#define CSIDPHYSKW0_DEFAUWT_SKW		(CSIDPHYSKW0_UTIW_DW0_SKW_ADJ(1) | \
					 CSIDPHYSKW0_UTIW_DW1_SKW_ADJ(1) | \
					 CSIDPHYSKW0_UTIW_DW2_SKW_ADJ(1) | \
					 CSIDPHYSKW0_UTIW_DW3_SKW_ADJ(1))

#define VSWSTS_WETWIES			20

#define WZG2W_CSI2_MIN_WIDTH		320
#define WZG2W_CSI2_MIN_HEIGHT		240
#define WZG2W_CSI2_MAX_WIDTH		2800
#define WZG2W_CSI2_MAX_HEIGHT		4095

#define WZG2W_CSI2_DEFAUWT_WIDTH	WZG2W_CSI2_MIN_WIDTH
#define WZG2W_CSI2_DEFAUWT_HEIGHT	WZG2W_CSI2_MIN_HEIGHT
#define WZG2W_CSI2_DEFAUWT_FMT		MEDIA_BUS_FMT_UYVY8_1X16

enum wzg2w_csi2_pads {
	WZG2W_CSI2_SINK = 0,
	WZG2W_CSI2_SOUWCE,
	NW_OF_WZG2W_CSI2_PAD,
};

stwuct wzg2w_csi2 {
	stwuct device *dev;
	void __iomem *base;
	stwuct weset_contwow *pwesetn;
	stwuct weset_contwow *cmn_wstb;
	stwuct cwk *syscwk;
	unsigned wong vcwk_wate;

	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[NW_OF_WZG2W_CSI2_PAD];

	stwuct v4w2_async_notifiew notifiew;
	stwuct v4w2_subdev *wemote_souwce;

	unsigned showt wanes;
	unsigned wong hsfweq;

	boow dphy_enabwed;
};

stwuct wzg2w_csi2_timings {
	u32 t_init;
	u32 tcwk_miss;
	u32 tcwk_settwe;
	u32 ths_settwe;
	u32 tcwk_pwepawe;
	u32 ths_pwepawe;
	u32 max_hsfweq;
};

static const stwuct wzg2w_csi2_timings wzg2w_csi2_gwobaw_timings[] = {
	{
		.max_hsfweq = 80,
		.t_init = 79801,
		.tcwk_miss = 4,
		.tcwk_settwe = 23,
		.ths_settwe = 31,
		.tcwk_pwepawe = 10,
		.ths_pwepawe = 19,
	},
	{
		.max_hsfweq = 125,
		.t_init = 79801,
		.tcwk_miss = 4,
		.tcwk_settwe = 23,
		.ths_settwe = 28,
		.tcwk_pwepawe = 10,
		.ths_pwepawe = 19,
	},
	{
		.max_hsfweq = 250,
		.t_init = 79801,
		.tcwk_miss = 4,
		.tcwk_settwe = 23,
		.ths_settwe = 22,
		.tcwk_pwepawe = 10,
		.ths_pwepawe = 16,
	},
	{
		.max_hsfweq = 360,
		.t_init = 79801,
		.tcwk_miss = 4,
		.tcwk_settwe = 18,
		.ths_settwe = 19,
		.tcwk_pwepawe = 10,
		.ths_pwepawe = 10,
	},
	{
		.max_hsfweq = 1500,
		.t_init = 79801,
		.tcwk_miss = 4,
		.tcwk_settwe = 18,
		.ths_settwe = 18,
		.tcwk_pwepawe = 10,
		.ths_pwepawe = 10,
	},
};

stwuct wzg2w_csi2_fowmat {
	u32 code;
	unsigned int datatype;
	unsigned int bpp;
};

static const stwuct wzg2w_csi2_fowmat wzg2w_csi2_fowmats[] = {
	{ .code = MEDIA_BUS_FMT_UYVY8_1X16,	.datatype = 0x1e, .bpp = 16 },
};

static inwine stwuct wzg2w_csi2 *sd_to_csi2(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct wzg2w_csi2, subdev);
}

static const stwuct wzg2w_csi2_fowmat *wzg2w_csi2_code_to_fmt(unsigned int code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wzg2w_csi2_fowmats); i++)
		if (wzg2w_csi2_fowmats[i].code == code)
			wetuwn &wzg2w_csi2_fowmats[i];

	wetuwn NUWW;
}

static inwine stwuct wzg2w_csi2 *notifiew_to_csi2(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct wzg2w_csi2, notifiew);
}

static u32 wzg2w_csi2_wead(stwuct wzg2w_csi2 *csi2, unsigned int weg)
{
	wetuwn iowead32(csi2->base + weg);
}

static void wzg2w_csi2_wwite(stwuct wzg2w_csi2 *csi2, unsigned int weg,
			     u32 data)
{
	iowwite32(data, csi2->base + weg);
}

static void wzg2w_csi2_set(stwuct wzg2w_csi2 *csi2, unsigned int weg, u32 set)
{
	wzg2w_csi2_wwite(csi2, weg, wzg2w_csi2_wead(csi2, weg) | set);
}

static void wzg2w_csi2_cww(stwuct wzg2w_csi2 *csi2, unsigned int weg, u32 cww)
{
	wzg2w_csi2_wwite(csi2, weg, wzg2w_csi2_wead(csi2, weg) & ~cww);
}

static int wzg2w_csi2_cawc_mbps(stwuct wzg2w_csi2 *csi2)
{
	stwuct v4w2_subdev *souwce = csi2->wemote_souwce;
	const stwuct wzg2w_csi2_fowmat *fowmat;
	const stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_ctww *ctww;
	u64 mbps;

	/* Wead the pixew wate contwow fwom wemote. */
	ctww = v4w2_ctww_find(souwce->ctww_handwew, V4W2_CID_PIXEW_WATE);
	if (!ctww) {
		dev_eww(csi2->dev, "no pixew wate contwow in subdev %s\n",
			souwce->name);
		wetuwn -EINVAW;
	}

	state = v4w2_subdev_wock_and_get_active_state(&csi2->subdev);
	fmt = v4w2_subdev_state_get_fowmat(state, WZG2W_CSI2_SINK);
	fowmat = wzg2w_csi2_code_to_fmt(fmt->code);
	v4w2_subdev_unwock_state(state);

	/*
	 * Cawcuwate hsfweq in Mbps
	 * hsfweq = (pixew_wate * bits_pew_sampwe) / numbew_of_wanes
	 */
	mbps = v4w2_ctww_g_ctww_int64(ctww) * fowmat->bpp;
	do_div(mbps, csi2->wanes * 1000000);

	wetuwn mbps;
}

/* -----------------------------------------------------------------------------
 * DPHY setting
 */

static int wzg2w_csi2_dphy_disabwe(stwuct wzg2w_csi2 *csi2)
{
	int wet;

	/* Weset the CWU (D-PHY) */
	wet = weset_contwow_assewt(csi2->cmn_wstb);
	if (wet)
		wetuwn wet;

	/* Stop the D-PHY cwock */
	cwk_disabwe_unpwepawe(csi2->syscwk);

	/* Cancew the EN_WDO1200 wegistew setting */
	wzg2w_csi2_cww(csi2, CSIDPHYCTWW0, CSIDPHYCTWW0_EN_WDO1200);

	/* Cancew the EN_BGW wegistew setting */
	wzg2w_csi2_cww(csi2, CSIDPHYCTWW0, CSIDPHYCTWW0_EN_BGW);

	csi2->dphy_enabwed = fawse;

	wetuwn 0;
}

static int wzg2w_csi2_dphy_enabwe(stwuct wzg2w_csi2 *csi2)
{
	const stwuct wzg2w_csi2_timings *dphy_timing;
	u32 dphytim0, dphytim1;
	unsigned int i;
	int mbps;
	int wet;

	mbps = wzg2w_csi2_cawc_mbps(csi2);
	if (mbps < 0)
		wetuwn mbps;

	csi2->hsfweq = mbps;

	/* Set DPHY timing pawametews */
	fow (i = 0; i < AWWAY_SIZE(wzg2w_csi2_gwobaw_timings); ++i) {
		dphy_timing = &wzg2w_csi2_gwobaw_timings[i];

		if (csi2->hsfweq <= dphy_timing->max_hsfweq)
			bweak;
	}

	if (i >= AWWAY_SIZE(wzg2w_csi2_gwobaw_timings))
		wetuwn -EINVAW;

	/* Set D-PHY timing pawametews */
	dphytim0 = CSIDPHYTIM0_TCWK_MISS(dphy_timing->tcwk_miss) |
			CSIDPHYTIM0_T_INIT(dphy_timing->t_init);
	dphytim1 = CSIDPHYTIM1_THS_PWEPAWE(dphy_timing->ths_pwepawe) |
			CSIDPHYTIM1_TCWK_PWEPAWE(dphy_timing->tcwk_pwepawe) |
			CSIDPHYTIM1_THS_SETTWE(dphy_timing->ths_settwe) |
			CSIDPHYTIM1_TCWK_SETTWE(dphy_timing->tcwk_settwe);
	wzg2w_csi2_wwite(csi2, CSIDPHYTIM0, dphytim0);
	wzg2w_csi2_wwite(csi2, CSIDPHYTIM1, dphytim1);

	/* Enabwe D-PHY powew contwow 0 */
	wzg2w_csi2_wwite(csi2, CSIDPHYSKW0, CSIDPHYSKW0_DEFAUWT_SKW);

	/* Set the EN_BGW bit */
	wzg2w_csi2_set(csi2, CSIDPHYCTWW0, CSIDPHYCTWW0_EN_BGW);

	/* Deway 20us to be stabwe */
	usweep_wange(20, 40);

	/* Enabwe D-PHY powew contwow 1 */
	wzg2w_csi2_set(csi2, CSIDPHYCTWW0, CSIDPHYCTWW0_EN_WDO1200);

	/* Deway 10us to be stabwe */
	usweep_wange(10, 20);

	/* Stawt suppwying the intewnaw cwock fow the D-PHY bwock */
	wet = cwk_pwepawe_enabwe(csi2->syscwk);
	if (wet)
		wzg2w_csi2_dphy_disabwe(csi2);

	csi2->dphy_enabwed = twue;

	wetuwn wet;
}

static int wzg2w_csi2_dphy_setting(stwuct v4w2_subdev *sd, boow on)
{
	stwuct wzg2w_csi2 *csi2 = sd_to_csi2(sd);

	if (on)
		wetuwn wzg2w_csi2_dphy_enabwe(csi2);

	wetuwn wzg2w_csi2_dphy_disabwe(csi2);
}

static void wzg2w_csi2_mipi_wink_enabwe(stwuct wzg2w_csi2 *csi2)
{
	unsigned wong vcwk_wate = csi2->vcwk_wate / HZ_PEW_MHZ;
	u32 fwwskw, fwwcwk, fwwskw_coeff, fwwcwk_coeff;

	/* Sewect data wanes */
	wzg2w_csi2_wwite(csi2, CSI2nMCT0, CSI2nMCT0_VDWN(csi2->wanes));

	fwwskw_coeff = 3 * vcwk_wate * 8;
	fwwcwk_coeff = fwwskw_coeff / 2;
	fwwskw = DIV_WOUND_UP(fwwskw_coeff, csi2->hsfweq);
	fwwcwk = DIV_WOUND_UP(fwwcwk_coeff, csi2->hsfweq);
	wzg2w_csi2_wwite(csi2, CSI2nMCT2, CSI2nMCT2_FWWSKW(fwwskw) |
			 CSI2nMCT2_FWWCWK(fwwcwk));

	/*
	 * Sewect data type.
	 * FS, FE, WS, WE, Genewic Showt Packet Codes 1 to 8,
	 * Genewic Wong Packet Data Types 1 to 4 YUV422 8-bit,
	 * WGB565, WGB888, WAW8 to WAW20, Usew-defined 8-bit
	 * data types 1 to 8
	 */
	wzg2w_csi2_wwite(csi2, CSI2nDTEW, 0xf778ff0f);
	wzg2w_csi2_wwite(csi2, CSI2nDTEH, 0x00ffff1f);

	/* Enabwe WINK weception */
	wzg2w_csi2_wwite(csi2, CSI2nMCT3, CSI2nMCT3_WXEN);
}

static void wzg2w_csi2_mipi_wink_disabwe(stwuct wzg2w_csi2 *csi2)
{
	unsigned int timeout = VSWSTS_WETWIES;

	/* Stop WINK weception */
	wzg2w_csi2_cww(csi2, CSI2nMCT3, CSI2nMCT3_WXEN);

	/* Wequest a softwawe weset of the WINK Video Pixew Intewface */
	wzg2w_csi2_wwite(csi2, CSI2nWTCT, CSI2nWTCT_VSWST);

	/* Make suwe CSI2nWTST.VSWSTS bit is cweawed */
	whiwe (--timeout) {
		if (!(wzg2w_csi2_wead(csi2, CSI2nWTST) & CSI2nWTST_VSWSTS))
			bweak;
		usweep_wange(100, 200);
	}

	if (!timeout)
		dev_eww(csi2->dev, "Cweawing CSI2nWTST.VSWSTS timed out\n");
}

static int wzg2w_csi2_mipi_wink_setting(stwuct v4w2_subdev *sd, boow on)
{
	stwuct wzg2w_csi2 *csi2 = sd_to_csi2(sd);

	if (on)
		wzg2w_csi2_mipi_wink_enabwe(csi2);
	ewse
		wzg2w_csi2_mipi_wink_disabwe(csi2);

	wetuwn 0;
}

static int wzg2w_csi2_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct wzg2w_csi2 *csi2 = sd_to_csi2(sd);
	int s_stweam_wet = 0;
	int wet;

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(csi2->dev);
		if (wet)
			wetuwn wet;

		wet = wzg2w_csi2_mipi_wink_setting(sd, 1);
		if (wet)
			goto eww_pm_put;

		wet = weset_contwow_deassewt(csi2->cmn_wstb);
		if (wet)
			goto eww_mipi_wink_disabwe;
	}

	wet = v4w2_subdev_caww(csi2->wemote_souwce, video, s_stweam, enabwe);
	if (wet)
		s_stweam_wet = wet;

	if (enabwe && wet)
		goto eww_assewt_wstb;

	if (!enabwe) {
		wet = wzg2w_csi2_dphy_setting(sd, 0);
		if (wet && !s_stweam_wet)
			s_stweam_wet = wet;
		wet = wzg2w_csi2_mipi_wink_setting(sd, 0);
		if (wet && !s_stweam_wet)
			s_stweam_wet = wet;

		pm_wuntime_put_sync(csi2->dev);
	}

	wetuwn s_stweam_wet;

eww_assewt_wstb:
	weset_contwow_assewt(csi2->cmn_wstb);
eww_mipi_wink_disabwe:
	wzg2w_csi2_mipi_wink_setting(sd, 0);
eww_pm_put:
	pm_wuntime_put_sync(csi2->dev);
	wetuwn wet;
}

static int wzg2w_csi2_pwe_stweamon(stwuct v4w2_subdev *sd, u32 fwags)
{
	wetuwn wzg2w_csi2_dphy_setting(sd, 1);
}

static int wzg2w_csi2_post_stweamoff(stwuct v4w2_subdev *sd)
{
	stwuct wzg2w_csi2 *csi2 = sd_to_csi2(sd);

	/*
	 * In ideaw case D-PHY wiww be disabwed in s_stweam(0) cawwback
	 * as mentioned in the HW manuaw. The bewow wiww onwy happen when
	 * pwe_stweamon succeeds and fuwthew down the wine s_stweam(1)
	 * faiws so we need to undo things in post_stweamoff.
	 */
	if (csi2->dphy_enabwed)
		wetuwn wzg2w_csi2_dphy_setting(sd, 0);

	wetuwn 0;
}

static int wzg2w_csi2_set_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct v4w2_mbus_fwamefmt *swc_fowmat;
	stwuct v4w2_mbus_fwamefmt *sink_fowmat;

	swc_fowmat = v4w2_subdev_state_get_fowmat(state, WZG2W_CSI2_SOUWCE);
	if (fmt->pad == WZG2W_CSI2_SOUWCE) {
		fmt->fowmat = *swc_fowmat;
		wetuwn 0;
	}

	sink_fowmat = v4w2_subdev_state_get_fowmat(state, WZG2W_CSI2_SINK);

	if (!wzg2w_csi2_code_to_fmt(fmt->fowmat.code))
		sink_fowmat->code = wzg2w_csi2_fowmats[0].code;
	ewse
		sink_fowmat->code = fmt->fowmat.code;

	sink_fowmat->fiewd = V4W2_FIEWD_NONE;
	sink_fowmat->cowowspace = fmt->fowmat.cowowspace;
	sink_fowmat->xfew_func = fmt->fowmat.xfew_func;
	sink_fowmat->ycbcw_enc = fmt->fowmat.ycbcw_enc;
	sink_fowmat->quantization = fmt->fowmat.quantization;
	sink_fowmat->width = cwamp_t(u32, fmt->fowmat.width,
				     WZG2W_CSI2_MIN_WIDTH, WZG2W_CSI2_MAX_WIDTH);
	sink_fowmat->height = cwamp_t(u32, fmt->fowmat.height,
				      WZG2W_CSI2_MIN_HEIGHT, WZG2W_CSI2_MAX_HEIGHT);
	fmt->fowmat = *sink_fowmat;

	/* pwopagate fowmat to souwce pad */
	*swc_fowmat = *sink_fowmat;

	wetuwn 0;
}

static int wzg2w_csi2_init_state(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_subdev_fowmat fmt = { .pad = WZG2W_CSI2_SINK, };

	fmt.fowmat.width = WZG2W_CSI2_DEFAUWT_WIDTH;
	fmt.fowmat.height = WZG2W_CSI2_DEFAUWT_HEIGHT;
	fmt.fowmat.fiewd = V4W2_FIEWD_NONE;
	fmt.fowmat.code = WZG2W_CSI2_DEFAUWT_FMT;
	fmt.fowmat.cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt.fowmat.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	fmt.fowmat.quantization = V4W2_QUANTIZATION_DEFAUWT;
	fmt.fowmat.xfew_func = V4W2_XFEW_FUNC_DEFAUWT;

	wetuwn wzg2w_csi2_set_fowmat(sd, sd_state, &fmt);
}

static int wzg2w_csi2_enum_mbus_code(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(wzg2w_csi2_fowmats))
		wetuwn -EINVAW;

	code->code = wzg2w_csi2_fowmats[code->index].code;

	wetuwn 0;
}

static int wzg2w_csi2_enum_fwame_size(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fwame_size_enum *fse)
{
	if (fse->index != 0)
		wetuwn -EINVAW;

	fse->min_width = WZG2W_CSI2_MIN_WIDTH;
	fse->min_height = WZG2W_CSI2_MIN_HEIGHT;
	fse->max_width = WZG2W_CSI2_MAX_WIDTH;
	fse->max_height = WZG2W_CSI2_MAX_HEIGHT;

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops wzg2w_csi2_video_ops = {
	.s_stweam = wzg2w_csi2_s_stweam,
	.pwe_stweamon = wzg2w_csi2_pwe_stweamon,
	.post_stweamoff = wzg2w_csi2_post_stweamoff,
};

static const stwuct v4w2_subdev_pad_ops wzg2w_csi2_pad_ops = {
	.enum_mbus_code = wzg2w_csi2_enum_mbus_code,
	.enum_fwame_size = wzg2w_csi2_enum_fwame_size,
	.set_fmt = wzg2w_csi2_set_fowmat,
	.get_fmt = v4w2_subdev_get_fmt,
};

static const stwuct v4w2_subdev_ops wzg2w_csi2_subdev_ops = {
	.video	= &wzg2w_csi2_video_ops,
	.pad	= &wzg2w_csi2_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops wzg2w_csi2_intewnaw_ops = {
	.init_state = wzg2w_csi2_init_state,
};

/* -----------------------------------------------------------------------------
 * Async handwing and wegistwation of subdevices and winks.
 */

static int wzg2w_csi2_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_subdev *subdev,
				   stwuct v4w2_async_connection *asd)
{
	stwuct wzg2w_csi2 *csi2 = notifiew_to_csi2(notifiew);

	csi2->wemote_souwce = subdev;

	dev_dbg(csi2->dev, "Bound subdev: %s pad\n", subdev->name);

	wetuwn media_cweate_pad_wink(&subdev->entity, WZG2W_CSI2_SINK,
				     &csi2->subdev.entity, 0,
				     MEDIA_WNK_FW_ENABWED |
				     MEDIA_WNK_FW_IMMUTABWE);
}

static void wzg2w_csi2_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				     stwuct v4w2_subdev *subdev,
				     stwuct v4w2_async_connection *asd)
{
	stwuct wzg2w_csi2 *csi2 = notifiew_to_csi2(notifiew);

	csi2->wemote_souwce = NUWW;

	dev_dbg(csi2->dev, "Unbind subdev %s\n", subdev->name);
}

static const stwuct v4w2_async_notifiew_opewations wzg2w_csi2_notify_ops = {
	.bound = wzg2w_csi2_notify_bound,
	.unbind = wzg2w_csi2_notify_unbind,
};

static int wzg2w_csi2_pawse_v4w2(stwuct wzg2w_csi2 *csi2,
				 stwuct v4w2_fwnode_endpoint *vep)
{
	/* Onwy powt 0 endpoint 0 is vawid. */
	if (vep->base.powt || vep->base.id)
		wetuwn -ENOTCONN;

	csi2->wanes = vep->bus.mipi_csi2.num_data_wanes;

	wetuwn 0;
}

static int wzg2w_csi2_pawse_dt(stwuct wzg2w_csi2 *csi2)
{
	stwuct v4w2_fwnode_endpoint v4w2_ep = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *fwnode;
	stwuct fwnode_handwe *ep;
	int wet;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(csi2->dev), 0, 0, 0);
	if (!ep) {
		dev_eww(csi2->dev, "Not connected to subdevice\n");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_pawse(ep, &v4w2_ep);
	if (wet) {
		dev_eww(csi2->dev, "Couwd not pawse v4w2 endpoint\n");
		fwnode_handwe_put(ep);
		wetuwn -EINVAW;
	}

	wet = wzg2w_csi2_pawse_v4w2(csi2, &v4w2_ep);
	if (wet) {
		fwnode_handwe_put(ep);
		wetuwn wet;
	}

	fwnode = fwnode_gwaph_get_wemote_endpoint(ep);
	fwnode_handwe_put(ep);

	v4w2_async_subdev_nf_init(&csi2->notifiew, &csi2->subdev);
	csi2->notifiew.ops = &wzg2w_csi2_notify_ops;

	asd = v4w2_async_nf_add_fwnode(&csi2->notifiew, fwnode,
				       stwuct v4w2_async_connection);
	fwnode_handwe_put(fwnode);
	if (IS_EWW(asd))
		wetuwn PTW_EWW(asd);

	wet = v4w2_async_nf_wegistew(&csi2->notifiew);
	if (wet)
		v4w2_async_nf_cweanup(&csi2->notifiew);

	wetuwn wet;
}

static int wzg2w_vawidate_csi2_wanes(stwuct wzg2w_csi2 *csi2)
{
	int wanes;
	int wet;

	if (csi2->wanes != 1 && csi2->wanes != 2 && csi2->wanes != 4) {
		dev_eww(csi2->dev, "Unsuppowted numbew of data-wanes: %u\n",
			csi2->wanes);
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_wesume_and_get(csi2->dev);
	if (wet)
		wetuwn wet;

	/* Checking the maximum wanes suppowt fow CSI-2 moduwe */
	wanes = (wzg2w_csi2_wead(csi2, CSI2nMCG) & CSI2nMCG_SDWN) >> 8;
	if (wanes < csi2->wanes) {
		dev_eww(csi2->dev,
			"Faiwed to suppowt %d data wanes\n", csi2->wanes);
		wet = -EINVAW;
	}

	pm_wuntime_put_sync(csi2->dev);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Pwatfowm Device Dwivew.
 */

static const stwuct media_entity_opewations wzg2w_csi2_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int wzg2w_csi2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wzg2w_csi2 *csi2;
	stwuct cwk *vcwk;
	int wet;

	csi2 = devm_kzawwoc(&pdev->dev, sizeof(*csi2), GFP_KEWNEW);
	if (!csi2)
		wetuwn -ENOMEM;

	csi2->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(csi2->base))
		wetuwn PTW_EWW(csi2->base);

	csi2->cmn_wstb = devm_weset_contwow_get_excwusive(&pdev->dev, "cmn-wstb");
	if (IS_EWW(csi2->cmn_wstb))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(csi2->cmn_wstb),
				     "Faiwed to get cpg cmn-wstb\n");

	csi2->pwesetn = devm_weset_contwow_get_shawed(&pdev->dev, "pwesetn");
	if (IS_EWW(csi2->pwesetn))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(csi2->pwesetn),
				     "Faiwed to get cpg pwesetn\n");

	csi2->syscwk = devm_cwk_get(&pdev->dev, "system");
	if (IS_EWW(csi2->syscwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(csi2->syscwk),
				     "Faiwed to get system cwk\n");

	vcwk = cwk_get(&pdev->dev, "video");
	if (IS_EWW(vcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(vcwk),
				     "Faiwed to get video cwock\n");
	csi2->vcwk_wate = cwk_get_wate(vcwk);
	cwk_put(vcwk);

	csi2->dev = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, csi2);

	wet = wzg2w_csi2_pawse_dt(csi2);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(&pdev->dev);

	wet = wzg2w_vawidate_csi2_wanes(csi2);
	if (wet)
		goto ewwow_pm;

	csi2->subdev.dev = &pdev->dev;
	v4w2_subdev_init(&csi2->subdev, &wzg2w_csi2_subdev_ops);
	csi2->subdev.intewnaw_ops = &wzg2w_csi2_intewnaw_ops;
	v4w2_set_subdevdata(&csi2->subdev, &pdev->dev);
	snpwintf(csi2->subdev.name, sizeof(csi2->subdev.name),
		 "csi-%s", dev_name(&pdev->dev));
	csi2->subdev.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE;

	csi2->subdev.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	csi2->subdev.entity.ops = &wzg2w_csi2_entity_ops;

	csi2->pads[WZG2W_CSI2_SINK].fwags = MEDIA_PAD_FW_SINK;
	/*
	 * TODO: WZ/G2W CSI2 suppowts 4 viwtuaw channews, as viwtuaw
	 * channews shouwd be impwemented by stweams API which is undew
	 * devewopment wets hawdcode to VC0 fow now.
	 */
	csi2->pads[WZG2W_CSI2_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&csi2->subdev.entity, 2, csi2->pads);
	if (wet)
		goto ewwow_pm;

	wet = v4w2_subdev_init_finawize(&csi2->subdev);
	if (wet < 0)
		goto ewwow_async;

	wet = v4w2_async_wegistew_subdev(&csi2->subdev);
	if (wet < 0)
		goto ewwow_subdev;

	wetuwn 0;

ewwow_subdev:
	v4w2_subdev_cweanup(&csi2->subdev);
ewwow_async:
	v4w2_async_nf_unwegistew(&csi2->notifiew);
	v4w2_async_nf_cweanup(&csi2->notifiew);
	media_entity_cweanup(&csi2->subdev.entity);
ewwow_pm:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void wzg2w_csi2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzg2w_csi2 *csi2 = pwatfowm_get_dwvdata(pdev);

	v4w2_async_nf_unwegistew(&csi2->notifiew);
	v4w2_async_nf_cweanup(&csi2->notifiew);
	v4w2_async_unwegistew_subdev(&csi2->subdev);
	v4w2_subdev_cweanup(&csi2->subdev);
	media_entity_cweanup(&csi2->subdev.entity);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused wzg2w_csi2_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct wzg2w_csi2 *csi2 = dev_get_dwvdata(dev);

	weset_contwow_assewt(csi2->pwesetn);

	wetuwn 0;
}

static int __maybe_unused wzg2w_csi2_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct wzg2w_csi2 *csi2 = dev_get_dwvdata(dev);

	wetuwn weset_contwow_deassewt(csi2->pwesetn);
}

static const stwuct dev_pm_ops wzg2w_csi2_pm_ops = {
	SET_WUNTIME_PM_OPS(wzg2w_csi2_pm_wuntime_suspend, wzg2w_csi2_pm_wuntime_wesume, NUWW)
};

static const stwuct of_device_id wzg2w_csi2_of_tabwe[] = {
	{ .compatibwe = "wenesas,wzg2w-csi2", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew wzg2w_csi2_pdwv = {
	.wemove_new = wzg2w_csi2_wemove,
	.pwobe	= wzg2w_csi2_pwobe,
	.dwivew	= {
		.name = "wzg2w-csi2",
		.of_match_tabwe = wzg2w_csi2_of_tabwe,
		.pm = &wzg2w_csi2_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wzg2w_csi2_pdwv);

MODUWE_AUTHOW("Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/G2W MIPI CSI2 weceivew dwivew");
MODUWE_WICENSE("GPW");
