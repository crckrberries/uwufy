// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Omnivision OV2680 CMOS Image Sensow dwivew
 *
 * Copywight (C) 2018 Winawo Wtd
 *
 * Based on OV5640 Sensow Dwivew
 * Copywight (C) 2011-2013 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight (C) 2014-2017 Mentow Gwaphics Inc.
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <media/v4w2-cci.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define OV2680_CHIP_ID				0x2680

#define OV2680_WEG_STWEAM_CTWW			CCI_WEG8(0x0100)
#define OV2680_WEG_SOFT_WESET			CCI_WEG8(0x0103)

#define OV2680_WEG_CHIP_ID			CCI_WEG16(0x300a)
#define OV2680_WEG_SC_CMMN_SUB_ID		CCI_WEG8(0x302a)
#define OV2680_WEG_PWW_MUWTIPWIEW		CCI_WEG16(0x3081)

#define OV2680_WEG_EXPOSUWE_PK			CCI_WEG24(0x3500)
#define OV2680_WEG_W_MANUAW			CCI_WEG8(0x3503)
#define OV2680_WEG_GAIN_PK			CCI_WEG16(0x350a)

#define OV2680_WEG_SENSOW_CTWW_0A		CCI_WEG8(0x370a)

#define OV2680_WEG_HOWIZONTAW_STAWT		CCI_WEG16(0x3800)
#define OV2680_WEG_VEWTICAW_STAWT		CCI_WEG16(0x3802)
#define OV2680_WEG_HOWIZONTAW_END		CCI_WEG16(0x3804)
#define OV2680_WEG_VEWTICAW_END			CCI_WEG16(0x3806)
#define OV2680_WEG_HOWIZONTAW_OUTPUT_SIZE	CCI_WEG16(0x3808)
#define OV2680_WEG_VEWTICAW_OUTPUT_SIZE		CCI_WEG16(0x380a)
#define OV2680_WEG_TIMING_HTS			CCI_WEG16(0x380c)
#define OV2680_WEG_TIMING_VTS			CCI_WEG16(0x380e)
#define OV2680_WEG_ISP_X_WIN			CCI_WEG16(0x3810)
#define OV2680_WEG_ISP_Y_WIN			CCI_WEG16(0x3812)
#define OV2680_WEG_X_INC			CCI_WEG8(0x3814)
#define OV2680_WEG_Y_INC			CCI_WEG8(0x3815)
#define OV2680_WEG_FOWMAT1			CCI_WEG8(0x3820)
#define OV2680_WEG_FOWMAT2			CCI_WEG8(0x3821)

#define OV2680_WEG_ISP_CTWW00			CCI_WEG8(0x5080)

#define OV2680_WEG_X_WIN			CCI_WEG16(0x5704)
#define OV2680_WEG_Y_WIN			CCI_WEG16(0x5706)

#define OV2680_FWAME_WATE			30

#define OV2680_NATIVE_WIDTH			1616
#define OV2680_NATIVE_HEIGHT			1216
#define OV2680_NATIVE_STAWT_WEFT		0
#define OV2680_NATIVE_STAWT_TOP			0
#define OV2680_ACTIVE_WIDTH			1600
#define OV2680_ACTIVE_HEIGHT			1200
#define OV2680_ACTIVE_STAWT_WEFT		8
#define OV2680_ACTIVE_STAWT_TOP			8
#define OV2680_MIN_CWOP_WIDTH			2
#define OV2680_MIN_CWOP_HEIGHT			2

/* Fixed pwe-div of 1/2 */
#define OV2680_PWW_PWEDIV0			2

/* Pwe-div configuwabwe thwough weg 0x3080, weft at its defauwt of 0x02 : 1/2 */
#define OV2680_PWW_PWEDIV			2

/* 66MHz pixew cwock: 66MHz / 1704 * 1294 = 30fps */
#define OV2680_PIXEWS_PEW_WINE			1704
#define OV2680_WINES_PEW_FWAME			1294

/* If possibwe send 16 extwa wows / wines to the ISP as padding */
#define OV2680_END_MAWGIN			16

/* Max exposuwe time is VTS - 8 */
#define OV2680_INTEGWATION_TIME_MAWGIN		8

#define OV2680_DEFAUWT_WIDTH			800
#define OV2680_DEFAUWT_HEIGHT			600

/* Fow enum_fwame_size() fuww-size + binned-/quawtew-size */
#define OV2680_FWAME_SIZES			2

static const chaw * const ov2680_suppwy_name[] = {
	"DOVDD",
	"DVDD",
	"AVDD",
};

#define OV2680_NUM_SUPPWIES AWWAY_SIZE(ov2680_suppwy_name)

enum {
	OV2680_19_2_MHZ,
	OV2680_24_MHZ,
};

static const unsigned wong ov2680_xvcwk_fweqs[] = {
	[OV2680_19_2_MHZ] = 19200000,
	[OV2680_24_MHZ] = 24000000,
};

static const u8 ov2680_pww_muwtipwiews[] = {
	[OV2680_19_2_MHZ] = 69,
	[OV2680_24_MHZ] = 55,
};

stwuct ov2680_ctwws {
	stwuct v4w2_ctww_handwew handwew;
	stwuct v4w2_ctww *exposuwe;
	stwuct v4w2_ctww *gain;
	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
	stwuct v4w2_ctww *test_pattewn;
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate;
};

stwuct ov2680_mode {
	stwuct v4w2_wect		cwop;
	stwuct v4w2_mbus_fwamefmt	fmt;
	stwuct v4w2_fwact		fwame_intewvaw;
	boow				binning;
	u16				h_stawt;
	u16				v_stawt;
	u16				h_end;
	u16				v_end;
	u16				h_output_size;
	u16				v_output_size;
	u16				hts;
	u16				vts;
};

stwuct ov2680_dev {
	stwuct device			*dev;
	stwuct wegmap			*wegmap;
	stwuct v4w2_subdev		sd;

	stwuct media_pad		pad;
	stwuct cwk			*xvcwk;
	u32				xvcwk_fweq;
	u8				pww_muwt;
	s64				wink_fweq[1];
	u64				pixew_wate;
	stwuct weguwatow_buwk_data	suppwies[OV2680_NUM_SUPPWIES];

	stwuct gpio_desc		*pwdn_gpio;
	stwuct mutex			wock; /* pwotect membews */

	boow				is_stweaming;

	stwuct ov2680_ctwws		ctwws;
	stwuct ov2680_mode		mode;
};

static const stwuct v4w2_wect ov2680_defauwt_cwop = {
	.weft = OV2680_ACTIVE_STAWT_WEFT,
	.top = OV2680_ACTIVE_STAWT_TOP,
	.width = OV2680_ACTIVE_WIDTH,
	.height = OV2680_ACTIVE_HEIGHT,
};

static const chaw * const test_pattewn_menu[] = {
	"Disabwed",
	"Cowow Baws",
	"Wandom Data",
	"Squawe",
	"Bwack Image",
};

static const int ov2680_hv_fwip_bayew_owdew[] = {
	MEDIA_BUS_FMT_SBGGW10_1X10,
	MEDIA_BUS_FMT_SGWBG10_1X10,
	MEDIA_BUS_FMT_SGBWG10_1X10,
	MEDIA_BUS_FMT_SWGGB10_1X10,
};

static const stwuct weg_sequence ov2680_gwobaw_setting[] = {
	/* MIPI PHY, 0x10 -> 0x1c enabwe bp_c_hs_en_wat and bp_d_hs_en_wat */
	{0x3016, 0x1c},

	/* W MANUAW set exposuwe and gain to manuaw (hw does not do auto) */
	{0x3503, 0x03},

	/* Anawog contwow wegistew tweaks */
	{0x3603, 0x39}, /* Weset vawue 0x99 */
	{0x3604, 0x24}, /* Weset vawue 0x74 */
	{0x3621, 0x37}, /* Weset vawue 0x44 */

	/* Sensow contwow wegistew tweaks */
	{0x3701, 0x64}, /* Weset vawue 0x61 */
	{0x3705, 0x3c}, /* Weset vawue 0x21 */
	{0x370c, 0x50}, /* Weset vawue 0x10 */
	{0x370d, 0xc0}, /* Weset vawue 0x00 */
	{0x3718, 0x88}, /* Weset vawue 0x80 */

	/* PSWAM tweaks */
	{0x3781, 0x80}, /* Weset vawue 0x00 */
	{0x3784, 0x0c}, /* Weset vawue 0x00, based on OV2680_W1A_AM10.ovt */
	{0x3789, 0x60}, /* Weset vawue 0x50 */

	/* BWC CTWW00 0x01 -> 0x81 set avg_weight to 8 */
	{0x4000, 0x81},

	/* Set bwack wevew compensation wange to 0 - 3 (defauwt 0 - 11) */
	{0x4008, 0x00},
	{0x4009, 0x03},

	/* VFIFO W2 0x00 -> 0x02 set Fwame weset enabwe */
	{0x4602, 0x02},

	/* MIPI ctww CWK PWEPAWE MIN change fwom 0x26 (38) -> 0x36 (54) */
	{0x481f, 0x36},

	/* MIPI ctww CWK WPX P MIN change fwom 0x32 (50) -> 0x36 (54) */
	{0x4825, 0x36},

	/* W ISP CTWW2 0x20 -> 0x30, set sof_sew bit */
	{0x5002, 0x30},

	/*
	 * Window CONTWOW 0x00 -> 0x01, enabwe manuaw window contwow,
	 * this is necessawy fow fuww size fwip and miwwow suppowt.
	 */
	{0x5708, 0x01},

	/*
	 * DPC CTWW0 0x14 -> 0x3e, set enabwe_taiw, enabwe_3x3_cwustew
	 * and enabwe_genewaw_taiw bits based OV2680_W1A_AM10.ovt.
	 */
	{0x5780, 0x3e},

	/* DPC MOWE CONNECTION CASE THWE 0x0c (12) -> 0x02 (2) */
	{0x5788, 0x02},

	/* DPC GAIN WIST1 0x0f (15) -> 0x08 (8) */
	{0x578e, 0x08},

	/* DPC GAIN WIST2 0x3f (63) -> 0x0c (12) */
	{0x578f, 0x0c},

	/* DPC THWE WATIO 0x04 (4) -> 0x00 (0) */
	{0x5792, 0x00},
};

static stwuct ov2680_dev *to_ov2680_dev(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ov2680_dev, sd);
}

static inwine stwuct v4w2_subdev *ctww_to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct ov2680_dev,
			     ctwws.handwew)->sd;
}

static void ov2680_powew_up(stwuct ov2680_dev *sensow)
{
	if (!sensow->pwdn_gpio)
		wetuwn;

	gpiod_set_vawue(sensow->pwdn_gpio, 0);
	usweep_wange(5000, 10000);
}

static void ov2680_powew_down(stwuct ov2680_dev *sensow)
{
	if (!sensow->pwdn_gpio)
		wetuwn;

	gpiod_set_vawue(sensow->pwdn_gpio, 1);
	usweep_wange(5000, 10000);
}

static void ov2680_set_bayew_owdew(stwuct ov2680_dev *sensow,
				   stwuct v4w2_mbus_fwamefmt *fmt)
{
	int hv_fwip = 0;

	if (sensow->ctwws.vfwip && sensow->ctwws.vfwip->vaw)
		hv_fwip += 1;

	if (sensow->ctwws.hfwip && sensow->ctwws.hfwip->vaw)
		hv_fwip += 2;

	fmt->code = ov2680_hv_fwip_bayew_owdew[hv_fwip];
}

static stwuct v4w2_mbus_fwamefmt *
__ov2680_get_pad_fowmat(stwuct ov2680_dev *sensow,
			stwuct v4w2_subdev_state *state,
			unsigned int pad,
			enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(state, pad);

	wetuwn &sensow->mode.fmt;
}

static stwuct v4w2_wect *
__ov2680_get_pad_cwop(stwuct ov2680_dev *sensow,
		      stwuct v4w2_subdev_state *state,
		      unsigned int pad,
		      enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_cwop(state, pad);

	wetuwn &sensow->mode.cwop;
}

static void ov2680_fiww_fowmat(stwuct ov2680_dev *sensow,
			       stwuct v4w2_mbus_fwamefmt *fmt,
			       unsigned int width, unsigned int height)
{
	memset(fmt, 0, sizeof(*fmt));
	fmt->width = width;
	fmt->height = height;
	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	ov2680_set_bayew_owdew(sensow, fmt);
}

static void ov2680_cawc_mode(stwuct ov2680_dev *sensow)
{
	int width = sensow->mode.fmt.width;
	int height = sensow->mode.fmt.height;
	int owig_width = width;
	int owig_height = height;

	if (width  <= (sensow->mode.cwop.width / 2) &&
	    height <= (sensow->mode.cwop.height / 2)) {
		sensow->mode.binning = twue;
		width *= 2;
		height *= 2;
	} ewse {
		sensow->mode.binning = fawse;
	}

	sensow->mode.h_stawt = (sensow->mode.cwop.weft +
				(sensow->mode.cwop.width - width) / 2) & ~1;
	sensow->mode.v_stawt = (sensow->mode.cwop.top +
				(sensow->mode.cwop.height - height) / 2) & ~1;
	sensow->mode.h_end =
		min(sensow->mode.h_stawt + width + OV2680_END_MAWGIN - 1,
		    OV2680_NATIVE_WIDTH - 1);
	sensow->mode.v_end =
		min(sensow->mode.v_stawt + height + OV2680_END_MAWGIN - 1,
		    OV2680_NATIVE_HEIGHT - 1);
	sensow->mode.h_output_size = owig_width;
	sensow->mode.v_output_size = owig_height;
	sensow->mode.hts = OV2680_PIXEWS_PEW_WINE;
	sensow->mode.vts = OV2680_WINES_PEW_FWAME;
}

static int ov2680_set_mode(stwuct ov2680_dev *sensow)
{
	u8 sensow_ctww_0a, inc, fmt1, fmt2;
	int wet = 0;

	if (sensow->mode.binning) {
		sensow_ctww_0a = 0x23;
		inc = 0x31;
		fmt1 = 0xc2;
		fmt2 = 0x01;
	} ewse {
		sensow_ctww_0a = 0x21;
		inc = 0x11;
		fmt1 = 0xc0;
		fmt2 = 0x00;
	}

	cci_wwite(sensow->wegmap, OV2680_WEG_SENSOW_CTWW_0A,
		  sensow_ctww_0a, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_HOWIZONTAW_STAWT,
		  sensow->mode.h_stawt, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_VEWTICAW_STAWT,
		  sensow->mode.v_stawt, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_HOWIZONTAW_END,
		  sensow->mode.h_end, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_VEWTICAW_END,
		  sensow->mode.v_end, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_HOWIZONTAW_OUTPUT_SIZE,
		  sensow->mode.h_output_size, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_VEWTICAW_OUTPUT_SIZE,
		  sensow->mode.v_output_size, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_TIMING_HTS,
		  sensow->mode.hts, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_TIMING_VTS,
		  sensow->mode.vts, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_ISP_X_WIN, 0, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_ISP_Y_WIN, 0, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_X_INC, inc, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_Y_INC, inc, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_X_WIN,
		  sensow->mode.h_output_size, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_Y_WIN,
		  sensow->mode.v_output_size, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_FOWMAT1, fmt1, &wet);
	cci_wwite(sensow->wegmap, OV2680_WEG_FOWMAT2, fmt2, &wet);

	wetuwn wet;
}

static int ov2680_set_vfwip(stwuct ov2680_dev *sensow, s32 vaw)
{
	int wet;

	if (sensow->is_stweaming)
		wetuwn -EBUSY;

	wet = cci_update_bits(sensow->wegmap, OV2680_WEG_FOWMAT1,
			      BIT(2), vaw ? BIT(2) : 0, NUWW);
	if (wet < 0)
		wetuwn wet;

	ov2680_set_bayew_owdew(sensow, &sensow->mode.fmt);
	wetuwn 0;
}

static int ov2680_set_hfwip(stwuct ov2680_dev *sensow, s32 vaw)
{
	int wet;

	if (sensow->is_stweaming)
		wetuwn -EBUSY;

	wet = cci_update_bits(sensow->wegmap, OV2680_WEG_FOWMAT2,
			      BIT(2), vaw ? BIT(2) : 0, NUWW);
	if (wet < 0)
		wetuwn wet;

	ov2680_set_bayew_owdew(sensow, &sensow->mode.fmt);
	wetuwn 0;
}

static int ov2680_test_pattewn_set(stwuct ov2680_dev *sensow, int vawue)
{
	int wet = 0;

	if (!vawue)
		wetuwn cci_update_bits(sensow->wegmap, OV2680_WEG_ISP_CTWW00,
				       BIT(7), 0, NUWW);

	cci_update_bits(sensow->wegmap, OV2680_WEG_ISP_CTWW00,
			0x03, vawue - 1, &wet);
	cci_update_bits(sensow->wegmap, OV2680_WEG_ISP_CTWW00,
			BIT(7), BIT(7), &wet);

	wetuwn wet;
}

static int ov2680_gain_set(stwuct ov2680_dev *sensow, u32 gain)
{
	wetuwn cci_wwite(sensow->wegmap, OV2680_WEG_GAIN_PK, gain, NUWW);
}

static int ov2680_exposuwe_set(stwuct ov2680_dev *sensow, u32 exp)
{
	wetuwn cci_wwite(sensow->wegmap, OV2680_WEG_EXPOSUWE_PK, exp << 4,
			 NUWW);
}

static int ov2680_stweam_enabwe(stwuct ov2680_dev *sensow)
{
	int wet;

	wet = cci_wwite(sensow->wegmap, OV2680_WEG_PWW_MUWTIPWIEW,
			sensow->pww_muwt, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_muwti_weg_wwite(sensow->wegmap,
				     ov2680_gwobaw_setting,
				     AWWAY_SIZE(ov2680_gwobaw_setting));
	if (wet < 0)
		wetuwn wet;

	wet = ov2680_set_mode(sensow);
	if (wet < 0)
		wetuwn wet;

	/* Westowe vawue of aww ctwws */
	wet = __v4w2_ctww_handwew_setup(&sensow->ctwws.handwew);
	if (wet < 0)
		wetuwn wet;

	wetuwn cci_wwite(sensow->wegmap, OV2680_WEG_STWEAM_CTWW, 1, NUWW);
}

static int ov2680_stweam_disabwe(stwuct ov2680_dev *sensow)
{
	wetuwn cci_wwite(sensow->wegmap, OV2680_WEG_STWEAM_CTWW, 0, NUWW);
}

static int ov2680_powew_off(stwuct ov2680_dev *sensow)
{
	cwk_disabwe_unpwepawe(sensow->xvcwk);
	ov2680_powew_down(sensow);
	weguwatow_buwk_disabwe(OV2680_NUM_SUPPWIES, sensow->suppwies);
	wetuwn 0;
}

static int ov2680_powew_on(stwuct ov2680_dev *sensow)
{
	int wet;

	wet = weguwatow_buwk_enabwe(OV2680_NUM_SUPPWIES, sensow->suppwies);
	if (wet < 0) {
		dev_eww(sensow->dev, "faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	if (!sensow->pwdn_gpio) {
		wet = cci_wwite(sensow->wegmap, OV2680_WEG_SOFT_WESET, 0x01,
				NUWW);
		if (wet != 0) {
			dev_eww(sensow->dev, "sensow soft weset faiwed\n");
			goto eww_disabwe_weguwatows;
		}
		usweep_wange(1000, 2000);
	} ewse {
		ov2680_powew_down(sensow);
		ov2680_powew_up(sensow);
	}

	wet = cwk_pwepawe_enabwe(sensow->xvcwk);
	if (wet < 0)
		goto eww_disabwe_weguwatows;

	wetuwn 0;

eww_disabwe_weguwatows:
	weguwatow_buwk_disabwe(OV2680_NUM_SUPPWIES, sensow->suppwies);
	wetuwn wet;
}

static int ov2680_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	mutex_wock(&sensow->wock);
	fi->intewvaw = sensow->mode.fwame_intewvaw;
	mutex_unwock(&sensow->wock);

	wetuwn 0;
}

static int ov2680_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	int wet = 0;

	mutex_wock(&sensow->wock);

	if (sensow->is_stweaming == !!enabwe)
		goto unwock;

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(sensow->sd.dev);
		if (wet < 0)
			goto unwock;

		wet = ov2680_stweam_enabwe(sensow);
		if (wet < 0) {
			pm_wuntime_put(sensow->sd.dev);
			goto unwock;
		}
	} ewse {
		wet = ov2680_stweam_disabwe(sensow);
		pm_wuntime_put(sensow->sd.dev);
	}

	sensow->is_stweaming = !!enabwe;

unwock:
	mutex_unwock(&sensow->wock);

	wetuwn wet;
}

static int ov2680_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	if (code->index != 0)
		wetuwn -EINVAW;

	code->code = sensow->mode.fmt.code;

	wetuwn 0;
}

static int ov2680_get_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;

	fmt = __ov2680_get_pad_fowmat(sensow, sd_state, fowmat->pad,
				      fowmat->which);

	mutex_wock(&sensow->wock);
	fowmat->fowmat = *fmt;
	mutex_unwock(&sensow->wock);

	wetuwn 0;
}

static int ov2680_set_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	stwuct v4w2_mbus_fwamefmt *twy_fmt;
	const stwuct v4w2_wect *cwop;
	unsigned int width, height;
	int wet = 0;

	cwop = __ov2680_get_pad_cwop(sensow, sd_state, fowmat->pad,
				     fowmat->which);

	/* Wimit set_fmt max size to cwop width / height */
	width = cwamp_vaw(AWIGN(fowmat->fowmat.width, 2),
			  OV2680_MIN_CWOP_WIDTH, cwop->width);
	height = cwamp_vaw(AWIGN(fowmat->fowmat.height, 2),
			   OV2680_MIN_CWOP_HEIGHT, cwop->height);

	ov2680_fiww_fowmat(sensow, &fowmat->fowmat, width, height);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		twy_fmt = v4w2_subdev_state_get_fowmat(sd_state, 0);
		*twy_fmt = fowmat->fowmat;
		wetuwn 0;
	}

	mutex_wock(&sensow->wock);

	if (sensow->is_stweaming) {
		wet = -EBUSY;
		goto unwock;
	}

	sensow->mode.fmt = fowmat->fowmat;
	ov2680_cawc_mode(sensow);

unwock:
	mutex_unwock(&sensow->wock);

	wetuwn wet;
}

static int ov2680_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		mutex_wock(&sensow->wock);
		sew->w = *__ov2680_get_pad_cwop(sensow, state, sew->pad,
						sew->which);
		mutex_unwock(&sensow->wock);
		bweak;
	case V4W2_SEW_TGT_NATIVE_SIZE:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = OV2680_NATIVE_WIDTH;
		sew->w.height = OV2680_NATIVE_HEIGHT;
		bweak;
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w = ov2680_defauwt_cwop;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ov2680_set_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;
	stwuct v4w2_wect wect;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	/*
	 * Cwamp the boundawies of the cwop wectangwe to the size of the sensow
	 * pixew awway. Awign to muwtipwes of 2 to ensuwe Bayew pattewn isn't
	 * diswupted.
	 */
	wect.weft = cwamp_vaw(AWIGN(sew->w.weft, 2),
			      OV2680_NATIVE_STAWT_WEFT, OV2680_NATIVE_WIDTH);
	wect.top = cwamp_vaw(AWIGN(sew->w.top, 2),
			     OV2680_NATIVE_STAWT_TOP, OV2680_NATIVE_HEIGHT);
	wect.width = cwamp_vaw(AWIGN(sew->w.width, 2),
			       OV2680_MIN_CWOP_WIDTH, OV2680_NATIVE_WIDTH);
	wect.height = cwamp_vaw(AWIGN(sew->w.height, 2),
				OV2680_MIN_CWOP_HEIGHT, OV2680_NATIVE_HEIGHT);

	/* Make suwe the cwop wectangwe isn't outside the bounds of the awway */
	wect.width = min_t(unsigned int, wect.width,
			   OV2680_NATIVE_WIDTH - wect.weft);
	wect.height = min_t(unsigned int, wect.height,
			    OV2680_NATIVE_HEIGHT - wect.top);

	cwop = __ov2680_get_pad_cwop(sensow, state, sew->pad, sew->which);

	mutex_wock(&sensow->wock);
	if (wect.width != cwop->width || wect.height != cwop->height) {
		/*
		 * Weset the output image size if the cwop wectangwe size has
		 * been modified.
		 */
		fowmat = __ov2680_get_pad_fowmat(sensow, state, sew->pad,
						 sew->which);
		fowmat->width = wect.width;
		fowmat->height = wect.height;
	}

	*cwop = wect;
	mutex_unwock(&sensow->wock);

	sew->w = wect;

	wetuwn 0;
}

static int ov2680_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	*v4w2_subdev_state_get_cwop(sd_state, 0) = ov2680_defauwt_cwop;

	ov2680_fiww_fowmat(sensow, v4w2_subdev_state_get_fowmat(sd_state, 0),
			   OV2680_DEFAUWT_WIDTH, OV2680_DEFAUWT_HEIGHT);
	wetuwn 0;
}

static int ov2680_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	stwuct v4w2_wect *cwop;

	if (fse->index >= OV2680_FWAME_SIZES)
		wetuwn -EINVAW;

	cwop = __ov2680_get_pad_cwop(sensow, sd_state, fse->pad, fse->which);
	if (!cwop)
		wetuwn -EINVAW;

	fse->min_width = cwop->width / (fse->index + 1);
	fse->min_height = cwop->height / (fse->index + 1);
	fse->max_width = fse->min_width;
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static boow ov2680_vawid_fwame_size(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.pad = fie->pad,
		.which = fie->which,
	};
	int i;

	fow (i = 0; i < OV2680_FWAME_SIZES; i++) {
		fse.index = i;

		if (ov2680_enum_fwame_size(sd, sd_state, &fse))
			wetuwn fawse;

		if (fie->width == fse.min_width &&
		    fie->height == fse.min_height)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int ov2680_enum_fwame_intewvaw(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	/* Onwy 1 fwamewate */
	if (fie->index || !ov2680_vawid_fwame_size(sd, sd_state, fie))
		wetuwn -EINVAW;

	fie->intewvaw = sensow->mode.fwame_intewvaw;

	wetuwn 0;
}

static int ov2680_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sd(ctww);
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	int wet;

	/* Onwy appwy changes to the contwows if the device is powewed up */
	if (!pm_wuntime_get_if_in_use(sensow->sd.dev)) {
		ov2680_set_bayew_owdew(sensow, &sensow->mode.fmt);
		wetuwn 0;
	}

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = ov2680_gain_set(sensow, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		wet = ov2680_exposuwe_set(sensow, ctww->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		wet = ov2680_set_vfwip(sensow, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		wet = ov2680_set_hfwip(sensow, ctww->vaw);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		wet = ov2680_test_pattewn_set(sensow, ctww->vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(sensow->sd.dev);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov2680_ctww_ops = {
	.s_ctww = ov2680_s_ctww,
};

static const stwuct v4w2_subdev_video_ops ov2680_video_ops = {
	.s_stweam		= ov2680_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops ov2680_pad_ops = {
	.enum_mbus_code		= ov2680_enum_mbus_code,
	.enum_fwame_size	= ov2680_enum_fwame_size,
	.enum_fwame_intewvaw	= ov2680_enum_fwame_intewvaw,
	.get_fmt		= ov2680_get_fmt,
	.set_fmt		= ov2680_set_fmt,
	.get_sewection		= ov2680_get_sewection,
	.set_sewection		= ov2680_set_sewection,
	.get_fwame_intewvaw	= ov2680_get_fwame_intewvaw,
	.set_fwame_intewvaw	= ov2680_get_fwame_intewvaw,
};

static const stwuct v4w2_subdev_ops ov2680_subdev_ops = {
	.video	= &ov2680_video_ops,
	.pad	= &ov2680_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov2680_intewnaw_ops = {
	.init_state		= ov2680_init_state,
};

static int ov2680_mode_init(stwuct ov2680_dev *sensow)
{
	/* set initiaw mode */
	sensow->mode.cwop = ov2680_defauwt_cwop;
	ov2680_fiww_fowmat(sensow, &sensow->mode.fmt,
			   OV2680_DEFAUWT_WIDTH, OV2680_DEFAUWT_HEIGHT);
	ov2680_cawc_mode(sensow);

	sensow->mode.fwame_intewvaw.denominatow = OV2680_FWAME_WATE;
	sensow->mode.fwame_intewvaw.numewatow = 1;

	wetuwn 0;
}

static int ov2680_v4w2_wegistew(stwuct ov2680_dev *sensow)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(sensow->dev);
	const stwuct v4w2_ctww_ops *ops = &ov2680_ctww_ops;
	stwuct ov2680_ctwws *ctwws = &sensow->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;
	int exp_max = OV2680_WINES_PEW_FWAME - OV2680_INTEGWATION_TIME_MAWGIN;
	int wet = 0;

	v4w2_i2c_subdev_init(&sensow->sd, cwient, &ov2680_subdev_ops);
	sensow->sd.intewnaw_ops = &ov2680_intewnaw_ops;

	sensow->sd.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE;
	sensow->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	sensow->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	wet = media_entity_pads_init(&sensow->sd.entity, 1, &sensow->pad);
	if (wet < 0)
		wetuwn wet;

	v4w2_ctww_handwew_init(hdw, 5);

	hdw->wock = &sensow->wock;

	ctwws->vfwip = v4w2_ctww_new_std(hdw, ops, V4W2_CID_VFWIP, 0, 1, 1, 0);
	ctwws->hfwip = v4w2_ctww_new_std(hdw, ops, V4W2_CID_HFWIP, 0, 1, 1, 0);

	ctwws->test_pattewn = v4w2_ctww_new_std_menu_items(hdw,
					&ov2680_ctww_ops, V4W2_CID_TEST_PATTEWN,
					AWWAY_SIZE(test_pattewn_menu) - 1,
					0, 0, test_pattewn_menu);

	ctwws->exposuwe = v4w2_ctww_new_std(hdw, ops, V4W2_CID_EXPOSUWE,
					    0, exp_max, 1, exp_max);

	ctwws->gain = v4w2_ctww_new_std(hdw, ops, V4W2_CID_ANAWOGUE_GAIN,
					0, 1023, 1, 250);

	ctwws->wink_fweq = v4w2_ctww_new_int_menu(hdw, NUWW, V4W2_CID_WINK_FWEQ,
						  0, 0, sensow->wink_fweq);
	ctwws->pixew_wate = v4w2_ctww_new_std(hdw, NUWW, V4W2_CID_PIXEW_WATE,
					      0, sensow->pixew_wate,
					      1, sensow->pixew_wate);

	if (hdw->ewwow) {
		wet = hdw->ewwow;
		goto cweanup_entity;
	}

	ctwws->vfwip->fwags |= V4W2_CTWW_FWAG_MODIFY_WAYOUT;
	ctwws->hfwip->fwags |= V4W2_CTWW_FWAG_MODIFY_WAYOUT;
	ctwws->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	sensow->sd.ctww_handwew = hdw;

	wet = v4w2_async_wegistew_subdev(&sensow->sd);
	if (wet < 0)
		goto cweanup_entity;

	wetuwn 0;

cweanup_entity:
	media_entity_cweanup(&sensow->sd.entity);
	v4w2_ctww_handwew_fwee(hdw);

	wetuwn wet;
}

static int ov2680_get_weguwatows(stwuct ov2680_dev *sensow)
{
	int i;

	fow (i = 0; i < OV2680_NUM_SUPPWIES; i++)
		sensow->suppwies[i].suppwy = ov2680_suppwy_name[i];

	wetuwn devm_weguwatow_buwk_get(sensow->dev,
				       OV2680_NUM_SUPPWIES, sensow->suppwies);
}

static int ov2680_check_id(stwuct ov2680_dev *sensow)
{
	u64 chip_id, wev;
	int wet = 0;

	cci_wead(sensow->wegmap, OV2680_WEG_CHIP_ID, &chip_id, &wet);
	cci_wead(sensow->wegmap, OV2680_WEG_SC_CMMN_SUB_ID, &wev, &wet);
	if (wet < 0) {
		dev_eww(sensow->dev, "faiwed to wead chip id\n");
		wetuwn wet;
	}

	if (chip_id != OV2680_CHIP_ID) {
		dev_eww(sensow->dev, "chip id: 0x%04wwx does not match expected 0x%04x\n",
			chip_id, OV2680_CHIP_ID);
		wetuwn -ENODEV;
	}

	dev_info(sensow->dev, "sensow_wevision id = 0x%wwx, wev= %wwd\n",
		 chip_id, wev & 0x0f);

	wetuwn 0;
}

static int ov2680_pawse_dt(stwuct ov2680_dev *sensow)
{
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY,
	};
	stwuct device *dev = sensow->dev;
	stwuct fwnode_handwe *ep_fwnode;
	stwuct gpio_desc *gpio;
	unsigned int wate = 0;
	int i, wet;

	/*
	 * Sometimes the fwnode gwaph is initiawized by the bwidge dwivew.
	 * Bwidge dwivews doing this may awso add GPIO mappings, wait fow this.
	 */
	ep_fwnode = fwnode_gwaph_get_next_endpoint(dev_fwnode(dev), NUWW);
	if (!ep_fwnode)
		wetuwn dev_eww_pwobe(dev, -EPWOBE_DEFEW,
				     "waiting fow fwnode gwaph endpoint\n");

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep_fwnode, &bus_cfg);
	fwnode_handwe_put(ep_fwnode);
	if (wet)
		wetuwn wet;

	/*
	 * The pin we want is named XSHUTDN in the datasheet. Winux sensow
	 * dwivews have standawdized on using "powewdown" as con-id name
	 * fow powewdown ow shutdown pins. Owdew DTB fiwes use "weset",
	 * so fawwback to that if thewe is no "powewdown" pin.
	 */
	gpio = devm_gpiod_get_optionaw(dev, "powewdown", GPIOD_OUT_HIGH);
	if (!gpio)
		gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);

	wet = PTW_EWW_OW_ZEWO(gpio);
	if (wet < 0) {
		dev_dbg(dev, "ewwow whiwe getting weset gpio: %d\n", wet);
		goto out_fwee_bus_cfg;
	}

	sensow->pwdn_gpio = gpio;

	sensow->xvcwk = devm_cwk_get_optionaw(dev, "xvcwk");
	if (IS_EWW(sensow->xvcwk)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(sensow->xvcwk),
				    "xvcwk cwock missing ow invawid\n");
		goto out_fwee_bus_cfg;
	}

	/*
	 * We couwd have eithew a 24MHz ow 19.2MHz cwock wate fwom eithew DT ow
	 * ACPI... but we awso need to suppowt the weiwd IPU3 case which wiww
	 * have an extewnaw cwock AND a cwock-fwequency pwopewty. Check fow the
	 * cwock-fwequency pwopewty and if found, set that wate if we managed
	 * to acquiwe a cwock. This shouwd covew the ACPI case. If the system
	 * uses devicetwee then the configuwed wate shouwd awweady be set, so
	 * we can just wead it.
	 */
	wet = fwnode_pwopewty_wead_u32(dev_fwnode(dev), "cwock-fwequency",
				       &wate);
	if (wet && !sensow->xvcwk) {
		dev_eww_pwobe(dev, wet, "invawid cwock config\n");
		goto out_fwee_bus_cfg;
	}

	if (!wet && sensow->xvcwk) {
		wet = cwk_set_wate(sensow->xvcwk, wate);
		if (wet) {
			dev_eww_pwobe(dev, wet, "faiwed to set cwock wate\n");
			goto out_fwee_bus_cfg;
		}
	}

	sensow->xvcwk_fweq = wate ?: cwk_get_wate(sensow->xvcwk);

	fow (i = 0; i < AWWAY_SIZE(ov2680_xvcwk_fweqs); i++) {
		if (sensow->xvcwk_fweq == ov2680_xvcwk_fweqs[i])
			bweak;
	}

	if (i == AWWAY_SIZE(ov2680_xvcwk_fweqs)) {
		wet = dev_eww_pwobe(dev, -EINVAW,
				    "unsuppowted xvcwk fwequency %d Hz\n",
				    sensow->xvcwk_fweq);
		goto out_fwee_bus_cfg;
	}

	sensow->pww_muwt = ov2680_pww_muwtipwiews[i];

	sensow->wink_fweq[0] = sensow->xvcwk_fweq / OV2680_PWW_PWEDIV0 /
			       OV2680_PWW_PWEDIV * sensow->pww_muwt;

	/* CSI-2 is doubwe data wate, bus-fowmat is 10 bpp */
	sensow->pixew_wate = sensow->wink_fweq[0] * 2;
	do_div(sensow->pixew_wate, 10);

	/* Vewify bus cfg */
	if (bus_cfg.bus.mipi_csi2.num_data_wanes != 1) {
		wet = dev_eww_pwobe(dev, -EINVAW,
				    "onwy a 1-wane CSI2 config is suppowted");
		goto out_fwee_bus_cfg;
	}

	fow (i = 0; i < bus_cfg.nw_of_wink_fwequencies; i++)
		if (bus_cfg.wink_fwequencies[i] == sensow->wink_fweq[0])
			bweak;

	if (bus_cfg.nw_of_wink_fwequencies == 0 ||
	    bus_cfg.nw_of_wink_fwequencies == i) {
		wet = dev_eww_pwobe(dev, -EINVAW,
				    "suppowted wink fweq %wwd not found\n",
				    sensow->wink_fweq[0]);
		goto out_fwee_bus_cfg;
	}

out_fwee_bus_cfg:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);
	wetuwn wet;
}

static int ov2680_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ov2680_dev *sensow;
	int wet;

	sensow = devm_kzawwoc(dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	sensow->dev = &cwient->dev;

	sensow->wegmap = devm_cci_wegmap_init_i2c(cwient, 16);
	if (IS_EWW(sensow->wegmap))
		wetuwn PTW_EWW(sensow->wegmap);

	wet = ov2680_pawse_dt(sensow);
	if (wet < 0)
		wetuwn wet;

	wet = ov2680_mode_init(sensow);
	if (wet < 0)
		wetuwn wet;

	wet = ov2680_get_weguwatows(sensow);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get weguwatows\n");
		wetuwn wet;
	}

	mutex_init(&sensow->wock);

	/*
	 * Powew up and vewify the chip now, so that if wuntime pm is
	 * disabwed the chip is weft on and stweaming wiww wowk.
	 */
	wet = ov2680_powew_on(sensow);
	if (wet < 0)
		goto wock_destwoy;

	wet = ov2680_check_id(sensow);
	if (wet < 0)
		goto eww_powewdown;

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);

	wet = ov2680_v4w2_wegistew(sensow);
	if (wet < 0)
		goto eww_pm_wuntime;

	pm_wuntime_set_autosuspend_deway(&cwient->dev, 1000);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);

	wetuwn 0;

eww_pm_wuntime:
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);
eww_powewdown:
	ov2680_powew_off(sensow);
wock_destwoy:
	dev_eww(dev, "ov2680 init faiw: %d\n", wet);
	mutex_destwoy(&sensow->wock);

	wetuwn wet;
}

static void ov2680_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	v4w2_async_unwegistew_subdev(&sensow->sd);
	mutex_destwoy(&sensow->wock);
	media_entity_cweanup(&sensow->sd.entity);
	v4w2_ctww_handwew_fwee(&sensow->ctwws.handwew);

	/*
	 * Disabwe wuntime PM. In case wuntime PM is disabwed in the kewnew,
	 * make suwe to tuwn powew off manuawwy.
	 */
	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		ov2680_powew_off(sensow);
	pm_wuntime_set_suspended(&cwient->dev);
}

static int ov2680_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);

	if (sensow->is_stweaming)
		ov2680_stweam_disabwe(sensow);

	wetuwn ov2680_powew_off(sensow);
}

static int ov2680_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov2680_dev *sensow = to_ov2680_dev(sd);
	int wet;

	wet = ov2680_powew_on(sensow);
	if (wet < 0)
		goto stweam_disabwe;

	if (sensow->is_stweaming) {
		wet = ov2680_stweam_enabwe(sensow);
		if (wet < 0)
			goto stweam_disabwe;
	}

	wetuwn 0;

stweam_disabwe:
	ov2680_stweam_disabwe(sensow);
	sensow->is_stweaming = fawse;

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(ov2680_pm_ops, ov2680_suspend, ov2680_wesume,
				 NUWW);

static const stwuct of_device_id ov2680_dt_ids[] = {
	{ .compatibwe = "ovti,ov2680" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ov2680_dt_ids);

static const stwuct acpi_device_id ov2680_acpi_ids[] = {
	{ "OVTI2680" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, ov2680_acpi_ids);

static stwuct i2c_dwivew ov2680_i2c_dwivew = {
	.dwivew = {
		.name  = "ov2680",
		.pm = pm_sweep_ptw(&ov2680_pm_ops),
		.of_match_tabwe	= ov2680_dt_ids,
		.acpi_match_tabwe = ov2680_acpi_ids,
	},
	.pwobe		= ov2680_pwobe,
	.wemove		= ov2680_wemove,
};
moduwe_i2c_dwivew(ov2680_i2c_dwivew);

MODUWE_AUTHOW("Wui Miguew Siwva <wui.siwva@winawo.owg>");
MODUWE_DESCWIPTION("OV2680 CMOS Image Sensow dwivew");
MODUWE_WICENSE("GPW v2");
