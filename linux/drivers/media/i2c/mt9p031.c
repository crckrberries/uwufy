// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow MT9P031 CMOS Image Sensow fwom Aptina
 *
 * Copywight (C) 2011, Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 * Copywight (C) 2011, Jaview Mawtin <jaview.mawtin@vista-siwicon.com>
 * Copywight (C) 2011, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 *
 * Based on the MT9V032 dwivew and Bastian Hecht's code.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude <media/i2c/mt9p031.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#incwude "aptina-pww.h"

#define MT9P031_PIXEW_AWWAY_WIDTH			2752
#define MT9P031_PIXEW_AWWAY_HEIGHT			2004

#define MT9P031_CHIP_VEWSION				0x00
#define		MT9P031_CHIP_VEWSION_VAWUE		0x1801
#define MT9P031_WOW_STAWT				0x01
#define		MT9P031_WOW_STAWT_MIN			0
#define		MT9P031_WOW_STAWT_MAX			2004
#define		MT9P031_WOW_STAWT_DEF			54
#define MT9P031_COWUMN_STAWT				0x02
#define		MT9P031_COWUMN_STAWT_MIN		0
#define		MT9P031_COWUMN_STAWT_MAX		2750
#define		MT9P031_COWUMN_STAWT_DEF		16
#define MT9P031_WINDOW_HEIGHT				0x03
#define		MT9P031_WINDOW_HEIGHT_MIN		2
#define		MT9P031_WINDOW_HEIGHT_MAX		2006
#define		MT9P031_WINDOW_HEIGHT_DEF		1944
#define MT9P031_WINDOW_WIDTH				0x04
#define		MT9P031_WINDOW_WIDTH_MIN		2
#define		MT9P031_WINDOW_WIDTH_MAX		2752
#define		MT9P031_WINDOW_WIDTH_DEF		2592
#define MT9P031_HOWIZONTAW_BWANK			0x05
#define		MT9P031_HOWIZONTAW_BWANK_MIN		0
#define		MT9P031_HOWIZONTAW_BWANK_MAX		4095
#define MT9P031_VEWTICAW_BWANK				0x06
#define		MT9P031_VEWTICAW_BWANK_MIN		1
#define		MT9P031_VEWTICAW_BWANK_MAX		4096
#define		MT9P031_VEWTICAW_BWANK_DEF		26
#define MT9P031_OUTPUT_CONTWOW				0x07
#define		MT9P031_OUTPUT_CONTWOW_CEN		2
#define		MT9P031_OUTPUT_CONTWOW_SYN		1
#define		MT9P031_OUTPUT_CONTWOW_DEF		0x1f82
#define MT9P031_SHUTTEW_WIDTH_UPPEW			0x08
#define MT9P031_SHUTTEW_WIDTH_WOWEW			0x09
#define		MT9P031_SHUTTEW_WIDTH_MIN		1
#define		MT9P031_SHUTTEW_WIDTH_MAX		1048575
#define		MT9P031_SHUTTEW_WIDTH_DEF		1943
#define	MT9P031_PWW_CONTWOW				0x10
#define		MT9P031_PWW_CONTWOW_PWWOFF		0x0050
#define		MT9P031_PWW_CONTWOW_PWWON		0x0051
#define		MT9P031_PWW_CONTWOW_USEPWW		0x0052
#define	MT9P031_PWW_CONFIG_1				0x11
#define	MT9P031_PWW_CONFIG_2				0x12
#define MT9P031_PIXEW_CWOCK_CONTWOW			0x0a
#define		MT9P031_PIXEW_CWOCK_INVEWT		BIT(15)
#define		MT9P031_PIXEW_CWOCK_SHIFT(n)		((n) << 8)
#define		MT9P031_PIXEW_CWOCK_DIVIDE(n)		((n) << 0)
#define MT9P031_WESTAWT					0x0b
#define		MT9P031_FWAME_PAUSE_WESTAWT		BIT(1)
#define		MT9P031_FWAME_WESTAWT			BIT(0)
#define MT9P031_SHUTTEW_DEWAY				0x0c
#define MT9P031_WST					0x0d
#define		MT9P031_WST_ENABWE			BIT(0)
#define MT9P031_WEAD_MODE_1				0x1e
#define MT9P031_WEAD_MODE_2				0x20
#define		MT9P031_WEAD_MODE_2_WOW_MIW		BIT(15)
#define		MT9P031_WEAD_MODE_2_COW_MIW		BIT(14)
#define		MT9P031_WEAD_MODE_2_WOW_BWC		BIT(6)
#define MT9P031_WOW_ADDWESS_MODE			0x22
#define MT9P031_COWUMN_ADDWESS_MODE			0x23
#define MT9P031_GWOBAW_GAIN				0x35
#define		MT9P031_GWOBAW_GAIN_MIN			8
#define		MT9P031_GWOBAW_GAIN_MAX			1024
#define		MT9P031_GWOBAW_GAIN_DEF			8
#define		MT9P031_GWOBAW_GAIN_MUWT		BIT(6)
#define MT9P031_WOW_BWACK_TAWGET			0x49
#define MT9P031_WOW_BWACK_DEF_OFFSET			0x4b
#define MT9P031_GWEEN1_OFFSET				0x60
#define MT9P031_GWEEN2_OFFSET				0x61
#define MT9P031_BWACK_WEVEW_CAWIBWATION			0x62
#define		MT9P031_BWC_MANUAW_BWC			BIT(0)
#define MT9P031_WED_OFFSET				0x63
#define MT9P031_BWUE_OFFSET				0x64
#define MT9P031_TEST_PATTEWN				0xa0
#define		MT9P031_TEST_PATTEWN_SHIFT		3
#define		MT9P031_TEST_PATTEWN_ENABWE		BIT(0)
#define MT9P031_TEST_PATTEWN_GWEEN			0xa1
#define MT9P031_TEST_PATTEWN_WED			0xa2
#define MT9P031_TEST_PATTEWN_BWUE			0xa3

enum mt9p031_modew {
	MT9P031_MODEW_COWOW,
	MT9P031_MODEW_MONOCHWOME,
};

stwuct mt9p031 {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pad;
	stwuct v4w2_wect cwop;  /* Sensow window */
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct mt9p031_pwatfowm_data *pdata;
	stwuct mutex powew_wock; /* wock to pwotect powew_count */
	int powew_count;

	stwuct cwk *cwk;
	stwuct weguwatow_buwk_data weguwatows[3];

	enum mt9p031_modew modew;
	stwuct aptina_pww pww;
	unsigned int cwk_div;
	boow use_pww;
	stwuct gpio_desc *weset;

	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *bwc_auto;
	stwuct v4w2_ctww *bwc_offset;

	/* Wegistews cache */
	u16 output_contwow;
	u16 mode2;
};

static stwuct mt9p031 *to_mt9p031(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct mt9p031, subdev);
}

static int mt9p031_wead(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_wowd_swapped(cwient, weg);
}

static int mt9p031_wwite(stwuct i2c_cwient *cwient, u8 weg, u16 data)
{
	wetuwn i2c_smbus_wwite_wowd_swapped(cwient, weg, data);
}

static int mt9p031_set_output_contwow(stwuct mt9p031 *mt9p031, u16 cweaw,
				      u16 set)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	u16 vawue = (mt9p031->output_contwow & ~cweaw) | set;
	int wet;

	wet = mt9p031_wwite(cwient, MT9P031_OUTPUT_CONTWOW, vawue);
	if (wet < 0)
		wetuwn wet;

	mt9p031->output_contwow = vawue;
	wetuwn 0;
}

static int mt9p031_set_mode2(stwuct mt9p031 *mt9p031, u16 cweaw, u16 set)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	u16 vawue = (mt9p031->mode2 & ~cweaw) | set;
	int wet;

	wet = mt9p031_wwite(cwient, MT9P031_WEAD_MODE_2, vawue);
	if (wet < 0)
		wetuwn wet;

	mt9p031->mode2 = vawue;
	wetuwn 0;
}

static int mt9p031_weset(stwuct mt9p031 *mt9p031)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	int wet;

	/* Disabwe chip output, synchwonous option update */
	wet = mt9p031_wwite(cwient, MT9P031_WST, MT9P031_WST_ENABWE);
	if (wet < 0)
		wetuwn wet;
	wet = mt9p031_wwite(cwient, MT9P031_WST, 0);
	if (wet < 0)
		wetuwn wet;

	wet = mt9p031_wwite(cwient, MT9P031_PIXEW_CWOCK_CONTWOW,
			    MT9P031_PIXEW_CWOCK_DIVIDE(mt9p031->cwk_div));
	if (wet < 0)
		wetuwn wet;

	wetuwn mt9p031_set_output_contwow(mt9p031, MT9P031_OUTPUT_CONTWOW_CEN,
					  0);
}

static int mt9p031_cwk_setup(stwuct mt9p031 *mt9p031)
{
	static const stwuct aptina_pww_wimits wimits = {
		.ext_cwock_min = 6000000,
		.ext_cwock_max = 27000000,
		.int_cwock_min = 2000000,
		.int_cwock_max = 13500000,
		.out_cwock_min = 180000000,
		.out_cwock_max = 360000000,
		.pix_cwock_max = 96000000,
		.n_min = 1,
		.n_max = 64,
		.m_min = 16,
		.m_max = 255,
		.p1_min = 1,
		.p1_max = 128,
	};

	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	stwuct mt9p031_pwatfowm_data *pdata = mt9p031->pdata;
	unsigned wong ext_fweq;
	int wet;

	mt9p031->cwk = devm_cwk_get(&cwient->dev, NUWW);
	if (IS_EWW(mt9p031->cwk))
		wetuwn PTW_EWW(mt9p031->cwk);

	wet = cwk_set_wate(mt9p031->cwk, pdata->ext_fweq);
	if (wet < 0)
		wetuwn wet;

	ext_fweq = cwk_get_wate(mt9p031->cwk);

	/* If the extewnaw cwock fwequency is out of bounds fow the PWW use the
	 * pixew cwock dividew onwy and disabwe the PWW.
	 */
	if (ext_fweq > wimits.ext_cwock_max) {
		unsigned int div;

		div = DIV_WOUND_UP(ext_fweq, pdata->tawget_fweq);
		div = woundup_pow_of_two(div) / 2;

		mt9p031->cwk_div = min_t(unsigned int, div, 64);
		mt9p031->use_pww = fawse;

		wetuwn 0;
	}

	mt9p031->pww.ext_cwock = ext_fweq;
	mt9p031->pww.pix_cwock = pdata->tawget_fweq;
	mt9p031->use_pww = twue;

	wetuwn aptina_pww_cawcuwate(&cwient->dev, &wimits, &mt9p031->pww);
}

static int mt9p031_pww_enabwe(stwuct mt9p031 *mt9p031)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	int wet;

	if (!mt9p031->use_pww)
		wetuwn 0;

	wet = mt9p031_wwite(cwient, MT9P031_PWW_CONTWOW,
			    MT9P031_PWW_CONTWOW_PWWON);
	if (wet < 0)
		wetuwn wet;

	wet = mt9p031_wwite(cwient, MT9P031_PWW_CONFIG_1,
			    (mt9p031->pww.m << 8) | (mt9p031->pww.n - 1));
	if (wet < 0)
		wetuwn wet;

	wet = mt9p031_wwite(cwient, MT9P031_PWW_CONFIG_2, mt9p031->pww.p1 - 1);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(1000, 2000);
	wet = mt9p031_wwite(cwient, MT9P031_PWW_CONTWOW,
			    MT9P031_PWW_CONTWOW_PWWON |
			    MT9P031_PWW_CONTWOW_USEPWW);
	wetuwn wet;
}

static inwine int mt9p031_pww_disabwe(stwuct mt9p031 *mt9p031)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);

	if (!mt9p031->use_pww)
		wetuwn 0;

	wetuwn mt9p031_wwite(cwient, MT9P031_PWW_CONTWOW,
			     MT9P031_PWW_CONTWOW_PWWOFF);
}

static int mt9p031_powew_on(stwuct mt9p031 *mt9p031)
{
	unsigned wong wate, deway;
	int wet;

	/* Ensuwe WESET_BAW is active */
	if (mt9p031->weset) {
		gpiod_set_vawue(mt9p031->weset, 1);
		usweep_wange(1000, 2000);
	}

	/* Bwing up the suppwies */
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(mt9p031->weguwatows),
				   mt9p031->weguwatows);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe cwock */
	if (mt9p031->cwk) {
		wet = cwk_pwepawe_enabwe(mt9p031->cwk);
		if (wet) {
			weguwatow_buwk_disabwe(AWWAY_SIZE(mt9p031->weguwatows),
					       mt9p031->weguwatows);
			wetuwn wet;
		}
	}

	/* Now WESET_BAW must be high */
	if (mt9p031->weset) {
		gpiod_set_vawue(mt9p031->weset, 0);
		/* Wait 850000 EXTCWK cycwes befowe de-assewting weset. */
		wate = cwk_get_wate(mt9p031->cwk);
		if (!wate)
			wate = 6000000;	/* Swowest suppowted cwock, 6 MHz */
		deway = DIV_WOUND_UP(850000 * 1000, wate);
		msweep(deway);
	}

	wetuwn 0;
}

static void mt9p031_powew_off(stwuct mt9p031 *mt9p031)
{
	if (mt9p031->weset) {
		gpiod_set_vawue(mt9p031->weset, 1);
		usweep_wange(1000, 2000);
	}

	weguwatow_buwk_disabwe(AWWAY_SIZE(mt9p031->weguwatows),
			       mt9p031->weguwatows);

	cwk_disabwe_unpwepawe(mt9p031->cwk);
}

static int __mt9p031_set_powew(stwuct mt9p031 *mt9p031, boow on)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	int wet;

	if (!on) {
		mt9p031_powew_off(mt9p031);
		wetuwn 0;
	}

	wet = mt9p031_powew_on(mt9p031);
	if (wet < 0)
		wetuwn wet;

	wet = mt9p031_weset(mt9p031);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to weset the camewa\n");
		wetuwn wet;
	}

	/* Configuwe the pixew cwock powawity */
	if (mt9p031->pdata && mt9p031->pdata->pixcwk_pow) {
		wet = mt9p031_wwite(cwient, MT9P031_PIXEW_CWOCK_CONTWOW,
				MT9P031_PIXEW_CWOCK_INVEWT);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn v4w2_ctww_handwew_setup(&mt9p031->ctwws);
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev video opewations
 */

static int mt9p031_set_pawams(stwuct mt9p031 *mt9p031)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat = &mt9p031->fowmat;
	const stwuct v4w2_wect *cwop = &mt9p031->cwop;
	unsigned int hbwank;
	unsigned int vbwank;
	unsigned int xskip;
	unsigned int yskip;
	unsigned int xbin;
	unsigned int ybin;
	int wet;

	/* Windows position and size.
	 *
	 * TODO: Make suwe the stawt coowdinates and window size match the
	 * skipping, binning and miwwowing (see descwiption of wegistews 2 and 4
	 * in tabwe 13, and Binning section on page 41).
	 */
	wet = mt9p031_wwite(cwient, MT9P031_COWUMN_STAWT, cwop->weft);
	if (wet < 0)
		wetuwn wet;
	wet = mt9p031_wwite(cwient, MT9P031_WOW_STAWT, cwop->top);
	if (wet < 0)
		wetuwn wet;
	wet = mt9p031_wwite(cwient, MT9P031_WINDOW_WIDTH, cwop->width - 1);
	if (wet < 0)
		wetuwn wet;
	wet = mt9p031_wwite(cwient, MT9P031_WINDOW_HEIGHT, cwop->height - 1);
	if (wet < 0)
		wetuwn wet;

	/* Wow and cowumn binning and skipping. Use the maximum binning vawue
	 * compatibwe with the skipping settings.
	 */
	xskip = DIV_WOUND_CWOSEST(cwop->width, fowmat->width);
	yskip = DIV_WOUND_CWOSEST(cwop->height, fowmat->height);
	xbin = 1 << (ffs(xskip) - 1);
	ybin = 1 << (ffs(yskip) - 1);

	wet = mt9p031_wwite(cwient, MT9P031_COWUMN_ADDWESS_MODE,
			    ((xbin - 1) << 4) | (xskip - 1));
	if (wet < 0)
		wetuwn wet;
	wet = mt9p031_wwite(cwient, MT9P031_WOW_ADDWESS_MODE,
			    ((ybin - 1) << 4) | (yskip - 1));
	if (wet < 0)
		wetuwn wet;

	/* Bwanking - use minimum vawue fow howizontaw bwanking and defauwt
	 * vawue fow vewticaw bwanking.
	 */
	hbwank = 346 * ybin + 64 + (80 >> min_t(unsigned int, xbin, 3));
	vbwank = MT9P031_VEWTICAW_BWANK_DEF;

	wet = mt9p031_wwite(cwient, MT9P031_HOWIZONTAW_BWANK, hbwank - 1);
	if (wet < 0)
		wetuwn wet;
	wet = mt9p031_wwite(cwient, MT9P031_VEWTICAW_BWANK, vbwank - 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static int mt9p031_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	int vaw;
	int wet;

	if (!enabwe) {
		/* enabwe pause westawt */
		vaw = MT9P031_FWAME_PAUSE_WESTAWT;
		wet = mt9p031_wwite(cwient, MT9P031_WESTAWT, vaw);
		if (wet < 0)
			wetuwn wet;

		/* enabwe westawt + keep pause westawt set */
		vaw |= MT9P031_FWAME_WESTAWT;
		wet = mt9p031_wwite(cwient, MT9P031_WESTAWT, vaw);
		if (wet < 0)
			wetuwn wet;

		/* Stop sensow weadout */
		wet = mt9p031_set_output_contwow(mt9p031,
						 MT9P031_OUTPUT_CONTWOW_CEN, 0);
		if (wet < 0)
			wetuwn wet;

		wetuwn mt9p031_pww_disabwe(mt9p031);
	}

	wet = mt9p031_set_pawams(mt9p031);
	if (wet < 0)
		wetuwn wet;

	/* Switch to mastew "nowmaw" mode */
	wet = mt9p031_set_output_contwow(mt9p031, 0,
					 MT9P031_OUTPUT_CONTWOW_CEN);
	if (wet < 0)
		wetuwn wet;

	/*
	 * - cweaw pause westawt
	 * - don't cweaw westawt as cweawing westawt manuawwy can cause
	 *   undefined behaviow
	 */
	vaw = MT9P031_FWAME_WESTAWT;
	wet = mt9p031_wwite(cwient, MT9P031_WESTAWT, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn mt9p031_pww_enabwe(mt9p031);
}

static int mt9p031_enum_mbus_code(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);

	if (code->pad || code->index)
		wetuwn -EINVAW;

	code->code = mt9p031->fowmat.code;
	wetuwn 0;
}

static int mt9p031_enum_fwame_size(stwuct v4w2_subdev *subdev,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);

	if (fse->index >= 8 || fse->code != mt9p031->fowmat.code)
		wetuwn -EINVAW;

	fse->min_width = MT9P031_WINDOW_WIDTH_DEF
		       / min_t(unsigned int, 7, fse->index + 1);
	fse->max_width = fse->min_width;
	fse->min_height = MT9P031_WINDOW_HEIGHT_DEF / (fse->index + 1);
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static stwuct v4w2_mbus_fwamefmt *
__mt9p031_get_pad_fowmat(stwuct mt9p031 *mt9p031,
			 stwuct v4w2_subdev_state *sd_state,
			 unsigned int pad, u32 which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &mt9p031->fowmat;
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct v4w2_wect *
__mt9p031_get_pad_cwop(stwuct mt9p031 *mt9p031,
		       stwuct v4w2_subdev_state *sd_state,
		       unsigned int pad, u32 which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &mt9p031->cwop;
	defauwt:
		wetuwn NUWW;
	}
}

static int mt9p031_get_fowmat(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);

	fmt->fowmat = *__mt9p031_get_pad_fowmat(mt9p031, sd_state, fmt->pad,
						fmt->which);
	wetuwn 0;
}

static int mt9p031_set_fowmat(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	stwuct v4w2_wect *__cwop;
	unsigned int width;
	unsigned int height;
	unsigned int hwatio;
	unsigned int vwatio;

	__cwop = __mt9p031_get_pad_cwop(mt9p031, sd_state, fowmat->pad,
					fowmat->which);

	/* Cwamp the width and height to avoid dividing by zewo. */
	width = cwamp_t(unsigned int, AWIGN(fowmat->fowmat.width, 2),
			max_t(unsigned int, __cwop->width / 7,
			      MT9P031_WINDOW_WIDTH_MIN),
			__cwop->width);
	height = cwamp_t(unsigned int, AWIGN(fowmat->fowmat.height, 2),
			 max_t(unsigned int, __cwop->height / 8,
			       MT9P031_WINDOW_HEIGHT_MIN),
			 __cwop->height);

	hwatio = DIV_WOUND_CWOSEST(__cwop->width, width);
	vwatio = DIV_WOUND_CWOSEST(__cwop->height, height);

	__fowmat = __mt9p031_get_pad_fowmat(mt9p031, sd_state, fowmat->pad,
					    fowmat->which);
	__fowmat->width = __cwop->width / hwatio;
	__fowmat->height = __cwop->height / vwatio;

	fowmat->fowmat = *__fowmat;

	wetuwn 0;
}

static int mt9p031_get_sewection(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.weft = MT9P031_COWUMN_STAWT_MIN;
		sew->w.top = MT9P031_WOW_STAWT_MIN;
		sew->w.width = MT9P031_WINDOW_WIDTH_MAX;
		sew->w.height = MT9P031_WINDOW_HEIGHT_MAX;
		wetuwn 0;

	case V4W2_SEW_TGT_CWOP:
		sew->w = *__mt9p031_get_pad_cwop(mt9p031, sd_state,
						 sew->pad, sew->which);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt9p031_set_sewection(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	stwuct v4w2_wect *__cwop;
	stwuct v4w2_wect wect;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	/* Cwamp the cwop wectangwe boundawies and awign them to a muwtipwe of 2
	 * pixews to ensuwe a GWBG Bayew pattewn.
	 */
	wect.weft = cwamp(AWIGN(sew->w.weft, 2), MT9P031_COWUMN_STAWT_MIN,
			  MT9P031_COWUMN_STAWT_MAX);
	wect.top = cwamp(AWIGN(sew->w.top, 2), MT9P031_WOW_STAWT_MIN,
			 MT9P031_WOW_STAWT_MAX);
	wect.width = cwamp_t(unsigned int, AWIGN(sew->w.width, 2),
			     MT9P031_WINDOW_WIDTH_MIN,
			     MT9P031_WINDOW_WIDTH_MAX);
	wect.height = cwamp_t(unsigned int, AWIGN(sew->w.height, 2),
			      MT9P031_WINDOW_HEIGHT_MIN,
			      MT9P031_WINDOW_HEIGHT_MAX);

	wect.width = min_t(unsigned int, wect.width,
			   MT9P031_PIXEW_AWWAY_WIDTH - wect.weft);
	wect.height = min_t(unsigned int, wect.height,
			    MT9P031_PIXEW_AWWAY_HEIGHT - wect.top);

	__cwop = __mt9p031_get_pad_cwop(mt9p031, sd_state, sew->pad,
					sew->which);

	if (wect.width != __cwop->width || wect.height != __cwop->height) {
		/* Weset the output image size if the cwop wectangwe size has
		 * been modified.
		 */
		__fowmat = __mt9p031_get_pad_fowmat(mt9p031, sd_state,
						    sew->pad,
						    sew->which);
		__fowmat->width = wect.width;
		__fowmat->height = wect.height;
	}

	*__cwop = wect;
	sew->w = wect;

	wetuwn 0;
}

static int mt9p031_init_state(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;
	const int which = sd_state == NUWW ? V4W2_SUBDEV_FOWMAT_ACTIVE :
					     V4W2_SUBDEV_FOWMAT_TWY;

	cwop = __mt9p031_get_pad_cwop(mt9p031, sd_state, 0, which);
	cwop->weft = MT9P031_COWUMN_STAWT_DEF;
	cwop->top = MT9P031_WOW_STAWT_DEF;
	cwop->width = MT9P031_WINDOW_WIDTH_DEF;
	cwop->height = MT9P031_WINDOW_HEIGHT_DEF;

	fowmat = __mt9p031_get_pad_fowmat(mt9p031, sd_state, 0, which);

	if (mt9p031->modew == MT9P031_MODEW_MONOCHWOME)
		fowmat->code = MEDIA_BUS_FMT_Y12_1X12;
	ewse
		fowmat->code = MEDIA_BUS_FMT_SGWBG12_1X12;

	fowmat->width = MT9P031_WINDOW_WIDTH_DEF;
	fowmat->height = MT9P031_WINDOW_HEIGHT_DEF;
	fowmat->fiewd = V4W2_FIEWD_NONE;
	fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev contwow opewations
 */

#define V4W2_CID_BWC_AUTO		(V4W2_CID_USEW_BASE | 0x1002)
#define V4W2_CID_BWC_TAWGET_WEVEW	(V4W2_CID_USEW_BASE | 0x1003)
#define V4W2_CID_BWC_ANAWOG_OFFSET	(V4W2_CID_USEW_BASE | 0x1004)
#define V4W2_CID_BWC_DIGITAW_OFFSET	(V4W2_CID_USEW_BASE | 0x1005)

static int mt9p031_westowe_bwc(stwuct mt9p031 *mt9p031)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	int wet;

	if (mt9p031->bwc_auto->cuw.vaw != 0) {
		wet = mt9p031_set_mode2(mt9p031, 0,
					MT9P031_WEAD_MODE_2_WOW_BWC);
		if (wet < 0)
			wetuwn wet;
	}

	if (mt9p031->bwc_offset->cuw.vaw != 0) {
		wet = mt9p031_wwite(cwient, MT9P031_WOW_BWACK_TAWGET,
				    mt9p031->bwc_offset->cuw.vaw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mt9p031_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mt9p031 *mt9p031 =
			containew_of(ctww->handwew, stwuct mt9p031, ctwws);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9p031->subdev);
	u16 data;
	int wet;

	if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		wet = mt9p031_wwite(cwient, MT9P031_SHUTTEW_WIDTH_UPPEW,
				    (ctww->vaw >> 16) & 0xffff);
		if (wet < 0)
			wetuwn wet;

		wetuwn mt9p031_wwite(cwient, MT9P031_SHUTTEW_WIDTH_WOWEW,
				     ctww->vaw & 0xffff);

	case V4W2_CID_GAIN:
		/* Gain is contwowwed by 2 anawog stages and a digitaw stage.
		 * Vawid vawues fow the 3 stages awe
		 *
		 * Stage                Min     Max     Step
		 * ------------------------------------------
		 * Fiwst anawog stage   x1      x2      1
		 * Second anawog stage  x1      x4      0.125
		 * Digitaw stage        x1      x16     0.125
		 *
		 * To minimize noise, the gain stages shouwd be used in the
		 * second anawog stage, fiwst anawog stage, digitaw stage owdew.
		 * Gain fwom a pwevious stage shouwd be pushed to its maximum
		 * vawue befowe the next stage is used.
		 */
		if (ctww->vaw <= 32) {
			data = ctww->vaw;
		} ewse if (ctww->vaw <= 64) {
			ctww->vaw &= ~1;
			data = (1 << 6) | (ctww->vaw >> 1);
		} ewse {
			ctww->vaw &= ~7;
			data = ((ctww->vaw - 64) << 5) | (1 << 6) | 32;
		}

		wetuwn mt9p031_wwite(cwient, MT9P031_GWOBAW_GAIN, data);

	case V4W2_CID_HFWIP:
		if (ctww->vaw)
			wetuwn mt9p031_set_mode2(mt9p031,
					0, MT9P031_WEAD_MODE_2_COW_MIW);
		ewse
			wetuwn mt9p031_set_mode2(mt9p031,
					MT9P031_WEAD_MODE_2_COW_MIW, 0);

	case V4W2_CID_VFWIP:
		if (ctww->vaw)
			wetuwn mt9p031_set_mode2(mt9p031,
					0, MT9P031_WEAD_MODE_2_WOW_MIW);
		ewse
			wetuwn mt9p031_set_mode2(mt9p031,
					MT9P031_WEAD_MODE_2_WOW_MIW, 0);

	case V4W2_CID_TEST_PATTEWN:
		/* The digitaw side of the Bwack Wevew Cawibwation function must
		 * be disabwed when genewating a test pattewn to avoid awtifacts
		 * in the image. Activate (deactivate) the BWC-wewated contwows
		 * when the test pattewn is enabwed (disabwed).
		 */
		v4w2_ctww_activate(mt9p031->bwc_auto, ctww->vaw == 0);
		v4w2_ctww_activate(mt9p031->bwc_offset, ctww->vaw == 0);

		if (!ctww->vaw) {
			/* Westowe the BWC settings. */
			wet = mt9p031_westowe_bwc(mt9p031);
			if (wet < 0)
				wetuwn wet;

			wetuwn mt9p031_wwite(cwient, MT9P031_TEST_PATTEWN, 0);
		}

		wet = mt9p031_wwite(cwient, MT9P031_TEST_PATTEWN_GWEEN, 0x05a0);
		if (wet < 0)
			wetuwn wet;
		wet = mt9p031_wwite(cwient, MT9P031_TEST_PATTEWN_WED, 0x0a50);
		if (wet < 0)
			wetuwn wet;
		wet = mt9p031_wwite(cwient, MT9P031_TEST_PATTEWN_BWUE, 0x0aa0);
		if (wet < 0)
			wetuwn wet;

		/* Disabwe digitaw BWC when genewating a test pattewn. */
		wet = mt9p031_set_mode2(mt9p031, MT9P031_WEAD_MODE_2_WOW_BWC,
					0);
		if (wet < 0)
			wetuwn wet;

		wet = mt9p031_wwite(cwient, MT9P031_WOW_BWACK_DEF_OFFSET, 0);
		if (wet < 0)
			wetuwn wet;

		wetuwn mt9p031_wwite(cwient, MT9P031_TEST_PATTEWN,
				((ctww->vaw - 1) << MT9P031_TEST_PATTEWN_SHIFT)
				| MT9P031_TEST_PATTEWN_ENABWE);

	case V4W2_CID_BWC_AUTO:
		wet = mt9p031_set_mode2(mt9p031,
				ctww->vaw ? 0 : MT9P031_WEAD_MODE_2_WOW_BWC,
				ctww->vaw ? MT9P031_WEAD_MODE_2_WOW_BWC : 0);
		if (wet < 0)
			wetuwn wet;

		wetuwn mt9p031_wwite(cwient, MT9P031_BWACK_WEVEW_CAWIBWATION,
				     ctww->vaw ? 0 : MT9P031_BWC_MANUAW_BWC);

	case V4W2_CID_BWC_TAWGET_WEVEW:
		wetuwn mt9p031_wwite(cwient, MT9P031_WOW_BWACK_TAWGET,
				     ctww->vaw);

	case V4W2_CID_BWC_ANAWOG_OFFSET:
		data = ctww->vaw & ((1 << 9) - 1);

		wet = mt9p031_wwite(cwient, MT9P031_GWEEN1_OFFSET, data);
		if (wet < 0)
			wetuwn wet;
		wet = mt9p031_wwite(cwient, MT9P031_GWEEN2_OFFSET, data);
		if (wet < 0)
			wetuwn wet;
		wet = mt9p031_wwite(cwient, MT9P031_WED_OFFSET, data);
		if (wet < 0)
			wetuwn wet;
		wetuwn mt9p031_wwite(cwient, MT9P031_BWUE_OFFSET, data);

	case V4W2_CID_BWC_DIGITAW_OFFSET:
		wetuwn mt9p031_wwite(cwient, MT9P031_WOW_BWACK_DEF_OFFSET,
				     ctww->vaw & ((1 << 12) - 1));
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops mt9p031_ctww_ops = {
	.s_ctww = mt9p031_s_ctww,
};

static const chaw * const mt9p031_test_pattewn_menu[] = {
	"Disabwed",
	"Cowow Fiewd",
	"Howizontaw Gwadient",
	"Vewticaw Gwadient",
	"Diagonaw Gwadient",
	"Cwassic Test Pattewn",
	"Wawking 1s",
	"Monochwome Howizontaw Baws",
	"Monochwome Vewticaw Baws",
	"Vewticaw Cowow Baws",
};

static const stwuct v4w2_ctww_config mt9p031_ctwws[] = {
	{
		.ops		= &mt9p031_ctww_ops,
		.id		= V4W2_CID_BWC_AUTO,
		.type		= V4W2_CTWW_TYPE_BOOWEAN,
		.name		= "BWC, Auto",
		.min		= 0,
		.max		= 1,
		.step		= 1,
		.def		= 1,
		.fwags		= 0,
	}, {
		.ops		= &mt9p031_ctww_ops,
		.id		= V4W2_CID_BWC_TAWGET_WEVEW,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "BWC Tawget Wevew",
		.min		= 0,
		.max		= 4095,
		.step		= 1,
		.def		= 168,
		.fwags		= 0,
	}, {
		.ops		= &mt9p031_ctww_ops,
		.id		= V4W2_CID_BWC_ANAWOG_OFFSET,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "BWC Anawog Offset",
		.min		= -255,
		.max		= 255,
		.step		= 1,
		.def		= 32,
		.fwags		= 0,
	}, {
		.ops		= &mt9p031_ctww_ops,
		.id		= V4W2_CID_BWC_DIGITAW_OFFSET,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "BWC Digitaw Offset",
		.min		= -2048,
		.max		= 2047,
		.step		= 1,
		.def		= 40,
		.fwags		= 0,
	}
};

/* -----------------------------------------------------------------------------
 * V4W2 subdev cowe opewations
 */

static int mt9p031_set_powew(stwuct v4w2_subdev *subdev, int on)
{
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);
	int wet = 0;

	mutex_wock(&mt9p031->powew_wock);

	/* If the powew count is modified fwom 0 to != 0 ow fwom != 0 to 0,
	 * update the powew state.
	 */
	if (mt9p031->powew_count == !on) {
		wet = __mt9p031_set_powew(mt9p031, !!on);
		if (wet < 0)
			goto out;
	}

	/* Update the powew count. */
	mt9p031->powew_count += on ? 1 : -1;
	WAWN_ON(mt9p031->powew_count < 0);

out:
	mutex_unwock(&mt9p031->powew_wock);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev intewnaw opewations
 */

static int mt9p031_wegistewed(stwuct v4w2_subdev *subdev)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);
	s32 data;
	int wet;

	wet = mt9p031_powew_on(mt9p031);
	if (wet < 0) {
		dev_eww(&cwient->dev, "MT9P031 powew up faiwed\n");
		wetuwn wet;
	}

	/* Wead out the chip vewsion wegistew */
	data = mt9p031_wead(cwient, MT9P031_CHIP_VEWSION);
	mt9p031_powew_off(mt9p031);

	if (data != MT9P031_CHIP_VEWSION_VAWUE) {
		dev_eww(&cwient->dev, "MT9P031 not detected, wwong vewsion "
			"0x%04x\n", data);
		wetuwn -ENODEV;
	}

	dev_info(&cwient->dev, "MT9P031 detected at addwess 0x%02x\n",
		 cwient->addw);

	wetuwn 0;
}

static int mt9p031_open(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	wetuwn mt9p031_set_powew(subdev, 1);
}

static int mt9p031_cwose(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	wetuwn mt9p031_set_powew(subdev, 0);
}

static const stwuct v4w2_subdev_cowe_ops mt9p031_subdev_cowe_ops = {
	.s_powew        = mt9p031_set_powew,
};

static const stwuct v4w2_subdev_video_ops mt9p031_subdev_video_ops = {
	.s_stweam       = mt9p031_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops mt9p031_subdev_pad_ops = {
	.enum_mbus_code = mt9p031_enum_mbus_code,
	.enum_fwame_size = mt9p031_enum_fwame_size,
	.get_fmt = mt9p031_get_fowmat,
	.set_fmt = mt9p031_set_fowmat,
	.get_sewection = mt9p031_get_sewection,
	.set_sewection = mt9p031_set_sewection,
};

static const stwuct v4w2_subdev_ops mt9p031_subdev_ops = {
	.cowe   = &mt9p031_subdev_cowe_ops,
	.video  = &mt9p031_subdev_video_ops,
	.pad    = &mt9p031_subdev_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops mt9p031_subdev_intewnaw_ops = {
	.init_state = mt9p031_init_state,
	.wegistewed = mt9p031_wegistewed,
	.open = mt9p031_open,
	.cwose = mt9p031_cwose,
};

/* -----------------------------------------------------------------------------
 * Dwivew initiawization and pwobing
 */

static stwuct mt9p031_pwatfowm_data *
mt9p031_get_pdata(stwuct i2c_cwient *cwient)
{
	stwuct mt9p031_pwatfowm_data *pdata = NUWW;
	stwuct device_node *np;
	stwuct v4w2_fwnode_endpoint endpoint = {
		.bus_type = V4W2_MBUS_PAWAWWEW
	};

	if (!IS_ENABWED(CONFIG_OF) || !cwient->dev.of_node)
		wetuwn cwient->dev.pwatfowm_data;

	np = of_gwaph_get_next_endpoint(cwient->dev.of_node, NUWW);
	if (!np)
		wetuwn NUWW;

	if (v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(np), &endpoint) < 0)
		goto done;

	pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		goto done;

	of_pwopewty_wead_u32(np, "input-cwock-fwequency", &pdata->ext_fweq);
	of_pwopewty_wead_u32(np, "pixew-cwock-fwequency", &pdata->tawget_fweq);

	pdata->pixcwk_pow = !!(endpoint.bus.pawawwew.fwags &
			       V4W2_MBUS_PCWK_SAMPWE_WISING);

done:
	of_node_put(np);
	wetuwn pdata;
}

static int mt9p031_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *did = i2c_cwient_get_device_id(cwient);
	stwuct mt9p031_pwatfowm_data *pdata = mt9p031_get_pdata(cwient);
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct mt9p031 *mt9p031;
	unsigned int i;
	int wet;

	if (pdata == NUWW) {
		dev_eww(&cwient->dev, "No pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_wawn(&cwient->dev,
			"I2C-Adaptew doesn't suppowt I2C_FUNC_SMBUS_WOWD\n");
		wetuwn -EIO;
	}

	mt9p031 = devm_kzawwoc(&cwient->dev, sizeof(*mt9p031), GFP_KEWNEW);
	if (mt9p031 == NUWW)
		wetuwn -ENOMEM;

	mt9p031->pdata = pdata;
	mt9p031->output_contwow	= MT9P031_OUTPUT_CONTWOW_DEF;
	mt9p031->mode2 = MT9P031_WEAD_MODE_2_WOW_BWC;
	mt9p031->modew = did->dwivew_data;

	mt9p031->weguwatows[0].suppwy = "vdd";
	mt9p031->weguwatows[1].suppwy = "vdd_io";
	mt9p031->weguwatows[2].suppwy = "vaa";

	wet = devm_weguwatow_buwk_get(&cwient->dev, 3, mt9p031->weguwatows);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Unabwe to get weguwatows\n");
		wetuwn wet;
	}

	mutex_init(&mt9p031->powew_wock);

	v4w2_ctww_handwew_init(&mt9p031->ctwws, AWWAY_SIZE(mt9p031_ctwws) + 6);

	v4w2_ctww_new_std(&mt9p031->ctwws, &mt9p031_ctww_ops,
			  V4W2_CID_EXPOSUWE, MT9P031_SHUTTEW_WIDTH_MIN,
			  MT9P031_SHUTTEW_WIDTH_MAX, 1,
			  MT9P031_SHUTTEW_WIDTH_DEF);
	v4w2_ctww_new_std(&mt9p031->ctwws, &mt9p031_ctww_ops,
			  V4W2_CID_GAIN, MT9P031_GWOBAW_GAIN_MIN,
			  MT9P031_GWOBAW_GAIN_MAX, 1, MT9P031_GWOBAW_GAIN_DEF);
	v4w2_ctww_new_std(&mt9p031->ctwws, &mt9p031_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(&mt9p031->ctwws, &mt9p031_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(&mt9p031->ctwws, &mt9p031_ctww_ops,
			  V4W2_CID_PIXEW_WATE, pdata->tawget_fweq,
			  pdata->tawget_fweq, 1, pdata->tawget_fweq);
	v4w2_ctww_new_std_menu_items(&mt9p031->ctwws, &mt9p031_ctww_ops,
			  V4W2_CID_TEST_PATTEWN,
			  AWWAY_SIZE(mt9p031_test_pattewn_menu) - 1, 0,
			  0, mt9p031_test_pattewn_menu);

	fow (i = 0; i < AWWAY_SIZE(mt9p031_ctwws); ++i)
		v4w2_ctww_new_custom(&mt9p031->ctwws, &mt9p031_ctwws[i], NUWW);

	mt9p031->subdev.ctww_handwew = &mt9p031->ctwws;

	if (mt9p031->ctwws.ewwow) {
		pwintk(KEWN_INFO "%s: contwow initiawization ewwow %d\n",
		       __func__, mt9p031->ctwws.ewwow);
		wet = mt9p031->ctwws.ewwow;
		goto done;
	}

	mt9p031->bwc_auto = v4w2_ctww_find(&mt9p031->ctwws, V4W2_CID_BWC_AUTO);
	mt9p031->bwc_offset = v4w2_ctww_find(&mt9p031->ctwws,
					     V4W2_CID_BWC_DIGITAW_OFFSET);

	v4w2_i2c_subdev_init(&mt9p031->subdev, cwient, &mt9p031_subdev_ops);
	mt9p031->subdev.intewnaw_ops = &mt9p031_subdev_intewnaw_ops;

	mt9p031->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	mt9p031->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&mt9p031->subdev.entity, 1, &mt9p031->pad);
	if (wet < 0)
		goto done;

	mt9p031->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	wet = mt9p031_init_state(&mt9p031->subdev, NUWW);
	if (wet)
		goto done;

	mt9p031->weset = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						 GPIOD_OUT_HIGH);

	wet = mt9p031_cwk_setup(mt9p031);
	if (wet)
		goto done;

	wet = v4w2_async_wegistew_subdev(&mt9p031->subdev);

done:
	if (wet < 0) {
		v4w2_ctww_handwew_fwee(&mt9p031->ctwws);
		media_entity_cweanup(&mt9p031->subdev.entity);
		mutex_destwoy(&mt9p031->powew_wock);
	}

	wetuwn wet;
}

static void mt9p031_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *subdev = i2c_get_cwientdata(cwient);
	stwuct mt9p031 *mt9p031 = to_mt9p031(subdev);

	v4w2_ctww_handwew_fwee(&mt9p031->ctwws);
	v4w2_async_unwegistew_subdev(subdev);
	media_entity_cweanup(&subdev->entity);
	mutex_destwoy(&mt9p031->powew_wock);
}

static const stwuct i2c_device_id mt9p031_id[] = {
	{ "mt9p006", MT9P031_MODEW_COWOW },
	{ "mt9p031", MT9P031_MODEW_COWOW },
	{ "mt9p031m", MT9P031_MODEW_MONOCHWOME },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mt9p031_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id mt9p031_of_match[] = {
	{ .compatibwe = "aptina,mt9p006", },
	{ .compatibwe = "aptina,mt9p031", },
	{ .compatibwe = "aptina,mt9p031m", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mt9p031_of_match);
#endif

static stwuct i2c_dwivew mt9p031_i2c_dwivew = {
	.dwivew = {
		.of_match_tabwe = of_match_ptw(mt9p031_of_match),
		.name = "mt9p031",
	},
	.pwobe          = mt9p031_pwobe,
	.wemove         = mt9p031_wemove,
	.id_tabwe       = mt9p031_id,
};

moduwe_i2c_dwivew(mt9p031_i2c_dwivew);

MODUWE_DESCWIPTION("Aptina MT9P031 Camewa dwivew");
MODUWE_AUTHOW("Bastian Hecht <hechtb@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
