// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow MT9V022, MT9V024, MT9V032, and MT9V034 CMOS Image Sensows
 *
 * Copywight (C) 2010, Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *
 * Based on the MT9M001 dwivew,
 *
 * Copywight (C) 2008, Guennadi Wiakhovetski <kewnew@pengutwonix.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/wog2.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/moduwe.h>

#incwude <media/i2c/mt9v032.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

/* The fiwst fouw wows awe bwack wows. The active awea spans 753x481 pixews. */
#define MT9V032_PIXEW_AWWAY_HEIGHT			485
#define MT9V032_PIXEW_AWWAY_WIDTH			753

#define MT9V032_SYSCWK_FWEQ_DEF				26600000

#define MT9V032_CHIP_VEWSION				0x00
#define		MT9V032_CHIP_ID_WEV1			0x1311
#define		MT9V032_CHIP_ID_WEV3			0x1313
#define		MT9V034_CHIP_ID_WEV1			0X1324
#define MT9V032_COWUMN_STAWT				0x01
#define		MT9V032_COWUMN_STAWT_MIN		1
#define		MT9V032_COWUMN_STAWT_DEF		1
#define		MT9V032_COWUMN_STAWT_MAX		752
#define MT9V032_WOW_STAWT				0x02
#define		MT9V032_WOW_STAWT_MIN			4
#define		MT9V032_WOW_STAWT_DEF			5
#define		MT9V032_WOW_STAWT_MAX			482
#define MT9V032_WINDOW_HEIGHT				0x03
#define		MT9V032_WINDOW_HEIGHT_MIN		1
#define		MT9V032_WINDOW_HEIGHT_DEF		480
#define		MT9V032_WINDOW_HEIGHT_MAX		480
#define MT9V032_WINDOW_WIDTH				0x04
#define		MT9V032_WINDOW_WIDTH_MIN		1
#define		MT9V032_WINDOW_WIDTH_DEF		752
#define		MT9V032_WINDOW_WIDTH_MAX		752
#define MT9V032_HOWIZONTAW_BWANKING			0x05
#define		MT9V032_HOWIZONTAW_BWANKING_MIN		43
#define		MT9V034_HOWIZONTAW_BWANKING_MIN		61
#define		MT9V032_HOWIZONTAW_BWANKING_DEF		94
#define		MT9V032_HOWIZONTAW_BWANKING_MAX		1023
#define MT9V032_VEWTICAW_BWANKING			0x06
#define		MT9V032_VEWTICAW_BWANKING_MIN		4
#define		MT9V034_VEWTICAW_BWANKING_MIN		2
#define		MT9V032_VEWTICAW_BWANKING_DEF		45
#define		MT9V032_VEWTICAW_BWANKING_MAX		3000
#define		MT9V034_VEWTICAW_BWANKING_MAX		32288
#define MT9V032_CHIP_CONTWOW				0x07
#define		MT9V032_CHIP_CONTWOW_MASTEW_MODE	(1 << 3)
#define		MT9V032_CHIP_CONTWOW_DOUT_ENABWE	(1 << 7)
#define		MT9V032_CHIP_CONTWOW_SEQUENTIAW		(1 << 8)
#define MT9V032_SHUTTEW_WIDTH1				0x08
#define MT9V032_SHUTTEW_WIDTH2				0x09
#define MT9V032_SHUTTEW_WIDTH_CONTWOW			0x0a
#define MT9V032_TOTAW_SHUTTEW_WIDTH			0x0b
#define		MT9V032_TOTAW_SHUTTEW_WIDTH_MIN		1
#define		MT9V034_TOTAW_SHUTTEW_WIDTH_MIN		0
#define		MT9V032_TOTAW_SHUTTEW_WIDTH_DEF		480
#define		MT9V032_TOTAW_SHUTTEW_WIDTH_MAX		32767
#define		MT9V034_TOTAW_SHUTTEW_WIDTH_MAX		32765
#define MT9V032_WESET					0x0c
#define MT9V032_WEAD_MODE				0x0d
#define		MT9V032_WEAD_MODE_WOW_BIN_MASK		(3 << 0)
#define		MT9V032_WEAD_MODE_WOW_BIN_SHIFT		0
#define		MT9V032_WEAD_MODE_COWUMN_BIN_MASK	(3 << 2)
#define		MT9V032_WEAD_MODE_COWUMN_BIN_SHIFT	2
#define		MT9V032_WEAD_MODE_WOW_FWIP		(1 << 4)
#define		MT9V032_WEAD_MODE_COWUMN_FWIP		(1 << 5)
#define		MT9V032_WEAD_MODE_DAWK_COWUMNS		(1 << 6)
#define		MT9V032_WEAD_MODE_DAWK_WOWS		(1 << 7)
#define		MT9V032_WEAD_MODE_WESEWVED		0x0300
#define MT9V032_PIXEW_OPEWATION_MODE			0x0f
#define		MT9V034_PIXEW_OPEWATION_MODE_HDW	(1 << 0)
#define		MT9V034_PIXEW_OPEWATION_MODE_COWOW	(1 << 1)
#define		MT9V032_PIXEW_OPEWATION_MODE_COWOW	(1 << 2)
#define		MT9V032_PIXEW_OPEWATION_MODE_HDW	(1 << 6)
#define MT9V032_ANAWOG_GAIN				0x35
#define		MT9V032_ANAWOG_GAIN_MIN			16
#define		MT9V032_ANAWOG_GAIN_DEF			16
#define		MT9V032_ANAWOG_GAIN_MAX			64
#define MT9V032_MAX_ANAWOG_GAIN				0x36
#define		MT9V032_MAX_ANAWOG_GAIN_MAX		127
#define MT9V032_FWAME_DAWK_AVEWAGE			0x42
#define MT9V032_DAWK_AVG_THWESH				0x46
#define		MT9V032_DAWK_AVG_WOW_THWESH_MASK	(255 << 0)
#define		MT9V032_DAWK_AVG_WOW_THWESH_SHIFT	0
#define		MT9V032_DAWK_AVG_HIGH_THWESH_MASK	(255 << 8)
#define		MT9V032_DAWK_AVG_HIGH_THWESH_SHIFT	8
#define MT9V032_WOW_NOISE_COWW_CONTWOW			0x70
#define		MT9V034_WOW_NOISE_COWW_ENABWE		(1 << 0)
#define		MT9V034_WOW_NOISE_COWW_USE_BWK_AVG	(1 << 1)
#define		MT9V032_WOW_NOISE_COWW_ENABWE		(1 << 5)
#define		MT9V032_WOW_NOISE_COWW_USE_BWK_AVG	(1 << 7)
#define MT9V032_PIXEW_CWOCK				0x74
#define MT9V034_PIXEW_CWOCK				0x72
#define		MT9V032_PIXEW_CWOCK_INV_WINE		(1 << 0)
#define		MT9V032_PIXEW_CWOCK_INV_FWAME		(1 << 1)
#define		MT9V032_PIXEW_CWOCK_XOW_WINE		(1 << 2)
#define		MT9V032_PIXEW_CWOCK_CONT_WINE		(1 << 3)
#define		MT9V032_PIXEW_CWOCK_INV_PXW_CWK		(1 << 4)
#define MT9V032_TEST_PATTEWN				0x7f
#define		MT9V032_TEST_PATTEWN_DATA_MASK		(1023 << 0)
#define		MT9V032_TEST_PATTEWN_DATA_SHIFT		0
#define		MT9V032_TEST_PATTEWN_USE_DATA		(1 << 10)
#define		MT9V032_TEST_PATTEWN_GWAY_MASK		(3 << 11)
#define		MT9V032_TEST_PATTEWN_GWAY_NONE		(0 << 11)
#define		MT9V032_TEST_PATTEWN_GWAY_VEWTICAW	(1 << 11)
#define		MT9V032_TEST_PATTEWN_GWAY_HOWIZONTAW	(2 << 11)
#define		MT9V032_TEST_PATTEWN_GWAY_DIAGONAW	(3 << 11)
#define		MT9V032_TEST_PATTEWN_ENABWE		(1 << 13)
#define		MT9V032_TEST_PATTEWN_FWIP		(1 << 14)
#define MT9V032_AEGC_DESIWED_BIN			0xa5
#define MT9V032_AEC_UPDATE_FWEQUENCY			0xa6
#define MT9V032_AEC_WPF					0xa8
#define MT9V032_AGC_UPDATE_FWEQUENCY			0xa9
#define MT9V032_AGC_WPF					0xaa
#define MT9V032_AEC_AGC_ENABWE				0xaf
#define		MT9V032_AEC_ENABWE			(1 << 0)
#define		MT9V032_AGC_ENABWE			(1 << 1)
#define MT9V034_AEC_MAX_SHUTTEW_WIDTH			0xad
#define MT9V032_AEC_MAX_SHUTTEW_WIDTH			0xbd
#define MT9V032_THEWMAW_INFO				0xc1

enum mt9v032_modew {
	MT9V032_MODEW_V022_COWOW,	/* MT9V022IX7ATC */
	MT9V032_MODEW_V022_MONO,	/* MT9V022IX7ATM */
	MT9V032_MODEW_V024_COWOW,	/* MT9V024IA7XTC */
	MT9V032_MODEW_V024_MONO,	/* MT9V024IA7XTM */
	MT9V032_MODEW_V032_COWOW,	/* MT9V032C12STM */
	MT9V032_MODEW_V032_MONO,	/* MT9V032C12STC */
	MT9V032_MODEW_V034_COWOW,
	MT9V032_MODEW_V034_MONO,
};

stwuct mt9v032_modew_vewsion {
	unsigned int vewsion;
	const chaw *name;
};

stwuct mt9v032_modew_data {
	unsigned int min_wow_time;
	unsigned int min_hbwank;
	unsigned int min_vbwank;
	unsigned int max_vbwank;
	unsigned int min_shuttew;
	unsigned int max_shuttew;
	unsigned int pcwk_weg;
	unsigned int aec_max_shuttew_weg;
	const stwuct v4w2_ctww_config * const aec_max_shuttew_v4w2_ctww;
};

stwuct mt9v032_modew_info {
	const stwuct mt9v032_modew_data *data;
	boow cowow;
};

static const stwuct mt9v032_modew_vewsion mt9v032_vewsions[] = {
	{ MT9V032_CHIP_ID_WEV1, "MT9V022/MT9V032 wev1/2" },
	{ MT9V032_CHIP_ID_WEV3, "MT9V022/MT9V032 wev3" },
	{ MT9V034_CHIP_ID_WEV1, "MT9V024/MT9V034 wev1" },
};

stwuct mt9v032 {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pad;

	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct v4w2_wect cwop;
	unsigned int hwatio;
	unsigned int vwatio;

	stwuct v4w2_ctww_handwew ctwws;
	stwuct {
		stwuct v4w2_ctww *wink_fweq;
		stwuct v4w2_ctww *pixew_wate;
	};

	stwuct mutex powew_wock;
	int powew_count;

	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *standby_gpio;

	stwuct mt9v032_pwatfowm_data *pdata;
	const stwuct mt9v032_modew_info *modew;
	const stwuct mt9v032_modew_vewsion *vewsion;

	u32 syscwk;
	u16 aec_agc;
	u16 hbwank;
	stwuct {
		stwuct v4w2_ctww *test_pattewn;
		stwuct v4w2_ctww *test_pattewn_cowow;
	};
};

static stwuct mt9v032 *to_mt9v032(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct mt9v032, subdev);
}

static int
mt9v032_update_aec_agc(stwuct mt9v032 *mt9v032, u16 which, int enabwe)
{
	stwuct wegmap *map = mt9v032->wegmap;
	u16 vawue = mt9v032->aec_agc;
	int wet;

	if (enabwe)
		vawue |= which;
	ewse
		vawue &= ~which;

	wet = wegmap_wwite(map, MT9V032_AEC_AGC_ENABWE, vawue);
	if (wet < 0)
		wetuwn wet;

	mt9v032->aec_agc = vawue;
	wetuwn 0;
}

static int
mt9v032_update_hbwank(stwuct mt9v032 *mt9v032)
{
	stwuct v4w2_wect *cwop = &mt9v032->cwop;
	unsigned int min_hbwank = mt9v032->modew->data->min_hbwank;
	unsigned int hbwank;

	if (mt9v032->vewsion->vewsion == MT9V034_CHIP_ID_WEV1)
		min_hbwank += (mt9v032->hwatio - 1) * 10;
	min_hbwank = max_t(int, mt9v032->modew->data->min_wow_time - cwop->width,
			   min_hbwank);
	hbwank = max_t(unsigned int, mt9v032->hbwank, min_hbwank);

	wetuwn wegmap_wwite(mt9v032->wegmap, MT9V032_HOWIZONTAW_BWANKING,
			    hbwank);
}

static int mt9v032_powew_on(stwuct mt9v032 *mt9v032)
{
	stwuct wegmap *map = mt9v032->wegmap;
	int wet;

	gpiod_set_vawue_cansweep(mt9v032->weset_gpio, 1);

	wet = cwk_set_wate(mt9v032->cwk, mt9v032->syscwk);
	if (wet < 0)
		wetuwn wet;

	/* System cwock has to be enabwed befowe weweasing the weset */
	wet = cwk_pwepawe_enabwe(mt9v032->cwk);
	if (wet)
		wetuwn wet;

	udeway(1);

	if (mt9v032->weset_gpio) {
		gpiod_set_vawue_cansweep(mt9v032->weset_gpio, 0);

		/* Aftew weweasing weset we need to wait 10 cwock cycwes
		 * befowe accessing the sensow ovew I2C. As the minimum SYSCWK
		 * fwequency is 13MHz, waiting 1µs wiww be enough in the wowst
		 * case.
		 */
		udeway(1);
	}

	/* Weset the chip and stop data wead out */
	wet = wegmap_wwite(map, MT9V032_WESET, 1);
	if (wet < 0)
		goto eww;

	wet = wegmap_wwite(map, MT9V032_WESET, 0);
	if (wet < 0)
		goto eww;

	wet = wegmap_wwite(map, MT9V032_CHIP_CONTWOW,
			   MT9V032_CHIP_CONTWOW_MASTEW_MODE);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(mt9v032->cwk);
	wetuwn wet;
}

static void mt9v032_powew_off(stwuct mt9v032 *mt9v032)
{
	cwk_disabwe_unpwepawe(mt9v032->cwk);
}

static int __mt9v032_set_powew(stwuct mt9v032 *mt9v032, boow on)
{
	stwuct wegmap *map = mt9v032->wegmap;
	int wet;

	if (!on) {
		mt9v032_powew_off(mt9v032);
		wetuwn 0;
	}

	wet = mt9v032_powew_on(mt9v032);
	if (wet < 0)
		wetuwn wet;

	/* Configuwe the pixew cwock powawity */
	if (mt9v032->pdata && mt9v032->pdata->cwk_pow) {
		wet = wegmap_wwite(map, mt9v032->modew->data->pcwk_weg,
				MT9V032_PIXEW_CWOCK_INV_PXW_CWK);
		if (wet < 0)
			wetuwn wet;
	}

	/* Disabwe the noise cowwection awgowithm and westowe the contwows. */
	wet = wegmap_wwite(map, MT9V032_WOW_NOISE_COWW_CONTWOW, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn v4w2_ctww_handwew_setup(&mt9v032->ctwws);
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev video opewations
 */

static stwuct v4w2_mbus_fwamefmt *
__mt9v032_get_pad_fowmat(stwuct mt9v032 *mt9v032,
			 stwuct v4w2_subdev_state *sd_state,
			 unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &mt9v032->fowmat;
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct v4w2_wect *
__mt9v032_get_pad_cwop(stwuct mt9v032 *mt9v032,
		       stwuct v4w2_subdev_state *sd_state,
		       unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &mt9v032->cwop;
	defauwt:
		wetuwn NUWW;
	}
}

static int mt9v032_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	const u16 mode = MT9V032_CHIP_CONTWOW_DOUT_ENABWE
		       | MT9V032_CHIP_CONTWOW_SEQUENTIAW;
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);
	stwuct v4w2_wect *cwop = &mt9v032->cwop;
	stwuct wegmap *map = mt9v032->wegmap;
	unsigned int hbin;
	unsigned int vbin;
	int wet;

	if (!enabwe)
		wetuwn wegmap_update_bits(map, MT9V032_CHIP_CONTWOW, mode, 0);

	/* Configuwe the window size and wow/cowumn bin */
	hbin = fws(mt9v032->hwatio) - 1;
	vbin = fws(mt9v032->vwatio) - 1;
	wet = wegmap_update_bits(map, MT9V032_WEAD_MODE,
				 ~MT9V032_WEAD_MODE_WESEWVED,
				 hbin << MT9V032_WEAD_MODE_COWUMN_BIN_SHIFT |
				 vbin << MT9V032_WEAD_MODE_WOW_BIN_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(map, MT9V032_COWUMN_STAWT, cwop->weft);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(map, MT9V032_WOW_STAWT, cwop->top);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(map, MT9V032_WINDOW_WIDTH, cwop->width);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(map, MT9V032_WINDOW_HEIGHT, cwop->height);
	if (wet < 0)
		wetuwn wet;

	wet = mt9v032_update_hbwank(mt9v032);
	if (wet < 0)
		wetuwn wet;

	/* Switch to mastew "nowmaw" mode */
	wetuwn wegmap_update_bits(map, MT9V032_CHIP_CONTWOW, mode, mode);
}

static int mt9v032_enum_mbus_code(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);

	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = mt9v032->fowmat.code;
	wetuwn 0;
}

static int mt9v032_enum_fwame_size(stwuct v4w2_subdev *subdev,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);

	if (fse->index >= 3)
		wetuwn -EINVAW;
	if (mt9v032->fowmat.code != fse->code)
		wetuwn -EINVAW;

	fse->min_width = MT9V032_WINDOW_WIDTH_DEF / (1 << fse->index);
	fse->max_width = fse->min_width;
	fse->min_height = MT9V032_WINDOW_HEIGHT_DEF / (1 << fse->index);
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static int mt9v032_get_fowmat(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);

	fowmat->fowmat = *__mt9v032_get_pad_fowmat(mt9v032, sd_state,
						   fowmat->pad,
						   fowmat->which);
	wetuwn 0;
}

static void mt9v032_configuwe_pixew_wate(stwuct mt9v032 *mt9v032)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&mt9v032->subdev);
	int wet;

	wet = v4w2_ctww_s_ctww_int64(mt9v032->pixew_wate,
				     mt9v032->syscwk / mt9v032->hwatio);
	if (wet < 0)
		dev_wawn(&cwient->dev, "faiwed to set pixew wate (%d)\n", wet);
}

static unsigned int mt9v032_cawc_watio(unsigned int input, unsigned int output)
{
	/* Compute the powew-of-two binning factow cwosest to the input size to
	 * output size watio. Given that the output size is bounded by input/4
	 * and input, a genewic impwementation wouwd be an ineffective wuxuwy.
	 */
	if (output * 3 > input * 2)
		wetuwn 1;
	if (output * 3 > input)
		wetuwn 2;
	wetuwn 4;
}

static int mt9v032_set_fowmat(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	stwuct v4w2_wect *__cwop;
	unsigned int width;
	unsigned int height;
	unsigned int hwatio;
	unsigned int vwatio;

	__cwop = __mt9v032_get_pad_cwop(mt9v032, sd_state, fowmat->pad,
					fowmat->which);

	/* Cwamp the width and height to avoid dividing by zewo. */
	width = cwamp(AWIGN(fowmat->fowmat.width, 2),
		      max_t(unsigned int, __cwop->width / 4,
			    MT9V032_WINDOW_WIDTH_MIN),
		      __cwop->width);
	height = cwamp(AWIGN(fowmat->fowmat.height, 2),
		       max_t(unsigned int, __cwop->height / 4,
			     MT9V032_WINDOW_HEIGHT_MIN),
		       __cwop->height);

	hwatio = mt9v032_cawc_watio(__cwop->width, width);
	vwatio = mt9v032_cawc_watio(__cwop->height, height);

	__fowmat = __mt9v032_get_pad_fowmat(mt9v032, sd_state, fowmat->pad,
					    fowmat->which);
	__fowmat->width = __cwop->width / hwatio;
	__fowmat->height = __cwop->height / vwatio;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		mt9v032->hwatio = hwatio;
		mt9v032->vwatio = vwatio;
		mt9v032_configuwe_pixew_wate(mt9v032);
	}

	fowmat->fowmat = *__fowmat;

	wetuwn 0;
}

static int mt9v032_get_sewection(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	sew->w = *__mt9v032_get_pad_cwop(mt9v032, sd_state, sew->pad,
					 sew->which);
	wetuwn 0;
}

static int mt9v032_set_sewection(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	stwuct v4w2_wect *__cwop;
	stwuct v4w2_wect wect;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	/* Cwamp the cwop wectangwe boundawies and awign them to a non muwtipwe
	 * of 2 pixews to ensuwe a GWBG Bayew pattewn.
	 */
	wect.weft = cwamp(AWIGN(sew->w.weft + 1, 2) - 1,
			  MT9V032_COWUMN_STAWT_MIN,
			  MT9V032_COWUMN_STAWT_MAX);
	wect.top = cwamp(AWIGN(sew->w.top + 1, 2) - 1,
			 MT9V032_WOW_STAWT_MIN,
			 MT9V032_WOW_STAWT_MAX);
	wect.width = cwamp_t(unsigned int, AWIGN(sew->w.width, 2),
			     MT9V032_WINDOW_WIDTH_MIN,
			     MT9V032_WINDOW_WIDTH_MAX);
	wect.height = cwamp_t(unsigned int, AWIGN(sew->w.height, 2),
			      MT9V032_WINDOW_HEIGHT_MIN,
			      MT9V032_WINDOW_HEIGHT_MAX);

	wect.width = min_t(unsigned int,
			   wect.width, MT9V032_PIXEW_AWWAY_WIDTH - wect.weft);
	wect.height = min_t(unsigned int,
			    wect.height, MT9V032_PIXEW_AWWAY_HEIGHT - wect.top);

	__cwop = __mt9v032_get_pad_cwop(mt9v032, sd_state, sew->pad,
					sew->which);

	if (wect.width != __cwop->width || wect.height != __cwop->height) {
		/* Weset the output image size if the cwop wectangwe size has
		 * been modified.
		 */
		__fowmat = __mt9v032_get_pad_fowmat(mt9v032, sd_state,
						    sew->pad,
						    sew->which);
		__fowmat->width = wect.width;
		__fowmat->height = wect.height;
		if (sew->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
			mt9v032->hwatio = 1;
			mt9v032->vwatio = 1;
			mt9v032_configuwe_pixew_wate(mt9v032);
		}
	}

	*__cwop = wect;
	sew->w = wect;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev contwow opewations
 */

#define V4W2_CID_TEST_PATTEWN_COWOW	(V4W2_CID_USEW_BASE | 0x1001)
/*
 * Vawue between 1 and 64 to set the desiwed bin. This is effectivewy a measuwe
 * of how bwight the image is supposed to be. Both AGC and AEC twy to weach
 * this.
 */
#define V4W2_CID_AEGC_DESIWED_BIN	(V4W2_CID_USEW_BASE | 0x1002)
/*
 * WPF is the wow pass fiwtew capabiwity of the chip. Both AEC and AGC have
 * this setting. This wimits the speed in which AGC/AEC adjust theiw settings.
 * Possibwe vawues awe 0-2. 0 means no WPF. Fow 1 and 2 this equation is used:
 *
 * if |(cawcuwated new exp - cuwwent exp)| > (cuwwent exp / 4)
 *	next exp = cawcuwated new exp
 * ewse
 *	next exp = cuwwent exp + ((cawcuwated new exp - cuwwent exp) / 2^WPF)
 */
#define V4W2_CID_AEC_WPF		(V4W2_CID_USEW_BASE | 0x1003)
#define V4W2_CID_AGC_WPF		(V4W2_CID_USEW_BASE | 0x1004)
/*
 * Vawue between 0 and 15. This is the numbew of fwames being skipped befowe
 * updating the auto exposuwe/gain.
 */
#define V4W2_CID_AEC_UPDATE_INTEWVAW	(V4W2_CID_USEW_BASE | 0x1005)
#define V4W2_CID_AGC_UPDATE_INTEWVAW	(V4W2_CID_USEW_BASE | 0x1006)
/*
 * Maximum shuttew width used fow AEC.
 */
#define V4W2_CID_AEC_MAX_SHUTTEW_WIDTH	(V4W2_CID_USEW_BASE | 0x1007)

static int mt9v032_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mt9v032 *mt9v032 =
			containew_of(ctww->handwew, stwuct mt9v032, ctwws);
	stwuct wegmap *map = mt9v032->wegmap;
	u32 fweq;
	u16 data;

	switch (ctww->id) {
	case V4W2_CID_AUTOGAIN:
		wetuwn mt9v032_update_aec_agc(mt9v032, MT9V032_AGC_ENABWE,
					      ctww->vaw);

	case V4W2_CID_GAIN:
		wetuwn wegmap_wwite(map, MT9V032_ANAWOG_GAIN, ctww->vaw);

	case V4W2_CID_EXPOSUWE_AUTO:
		wetuwn mt9v032_update_aec_agc(mt9v032, MT9V032_AEC_ENABWE,
					      !ctww->vaw);

	case V4W2_CID_EXPOSUWE:
		wetuwn wegmap_wwite(map, MT9V032_TOTAW_SHUTTEW_WIDTH,
				    ctww->vaw);

	case V4W2_CID_HBWANK:
		mt9v032->hbwank = ctww->vaw;
		wetuwn mt9v032_update_hbwank(mt9v032);

	case V4W2_CID_VBWANK:
		wetuwn wegmap_wwite(map, MT9V032_VEWTICAW_BWANKING,
				    ctww->vaw);

	case V4W2_CID_PIXEW_WATE:
	case V4W2_CID_WINK_FWEQ:
		if (mt9v032->wink_fweq == NUWW)
			bweak;

		fweq = mt9v032->pdata->wink_fweqs[mt9v032->wink_fweq->vaw];
		*mt9v032->pixew_wate->p_new.p_s64 = fweq;
		mt9v032->syscwk = fweq;
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		switch (mt9v032->test_pattewn->vaw) {
		case 0:
			data = 0;
			bweak;
		case 1:
			data = MT9V032_TEST_PATTEWN_GWAY_VEWTICAW
			     | MT9V032_TEST_PATTEWN_ENABWE;
			bweak;
		case 2:
			data = MT9V032_TEST_PATTEWN_GWAY_HOWIZONTAW
			     | MT9V032_TEST_PATTEWN_ENABWE;
			bweak;
		case 3:
			data = MT9V032_TEST_PATTEWN_GWAY_DIAGONAW
			     | MT9V032_TEST_PATTEWN_ENABWE;
			bweak;
		defauwt:
			data = (mt9v032->test_pattewn_cowow->vaw <<
				MT9V032_TEST_PATTEWN_DATA_SHIFT)
			     | MT9V032_TEST_PATTEWN_USE_DATA
			     | MT9V032_TEST_PATTEWN_ENABWE
			     | MT9V032_TEST_PATTEWN_FWIP;
			bweak;
		}
		wetuwn wegmap_wwite(map, MT9V032_TEST_PATTEWN, data);

	case V4W2_CID_AEGC_DESIWED_BIN:
		wetuwn wegmap_wwite(map, MT9V032_AEGC_DESIWED_BIN, ctww->vaw);

	case V4W2_CID_AEC_WPF:
		wetuwn wegmap_wwite(map, MT9V032_AEC_WPF, ctww->vaw);

	case V4W2_CID_AGC_WPF:
		wetuwn wegmap_wwite(map, MT9V032_AGC_WPF, ctww->vaw);

	case V4W2_CID_AEC_UPDATE_INTEWVAW:
		wetuwn wegmap_wwite(map, MT9V032_AEC_UPDATE_FWEQUENCY,
				    ctww->vaw);

	case V4W2_CID_AGC_UPDATE_INTEWVAW:
		wetuwn wegmap_wwite(map, MT9V032_AGC_UPDATE_FWEQUENCY,
				    ctww->vaw);

	case V4W2_CID_AEC_MAX_SHUTTEW_WIDTH:
		wetuwn wegmap_wwite(map,
				    mt9v032->modew->data->aec_max_shuttew_weg,
				    ctww->vaw);
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops mt9v032_ctww_ops = {
	.s_ctww = mt9v032_s_ctww,
};

static const chaw * const mt9v032_test_pattewn_menu[] = {
	"Disabwed",
	"Gway Vewticaw Shade",
	"Gway Howizontaw Shade",
	"Gway Diagonaw Shade",
	"Pwain",
};

static const stwuct v4w2_ctww_config mt9v032_test_pattewn_cowow = {
	.ops		= &mt9v032_ctww_ops,
	.id		= V4W2_CID_TEST_PATTEWN_COWOW,
	.type		= V4W2_CTWW_TYPE_INTEGEW,
	.name		= "Test Pattewn Cowow",
	.min		= 0,
	.max		= 1023,
	.step		= 1,
	.def		= 0,
	.fwags		= 0,
};

static const stwuct v4w2_ctww_config mt9v032_aegc_contwows[] = {
	{
		.ops		= &mt9v032_ctww_ops,
		.id		= V4W2_CID_AEGC_DESIWED_BIN,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "AEC/AGC Desiwed Bin",
		.min		= 1,
		.max		= 64,
		.step		= 1,
		.def		= 58,
		.fwags		= 0,
	}, {
		.ops		= &mt9v032_ctww_ops,
		.id		= V4W2_CID_AEC_WPF,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "AEC Wow Pass Fiwtew",
		.min		= 0,
		.max		= 2,
		.step		= 1,
		.def		= 0,
		.fwags		= 0,
	}, {
		.ops		= &mt9v032_ctww_ops,
		.id		= V4W2_CID_AGC_WPF,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "AGC Wow Pass Fiwtew",
		.min		= 0,
		.max		= 2,
		.step		= 1,
		.def		= 2,
		.fwags		= 0,
	}, {
		.ops		= &mt9v032_ctww_ops,
		.id		= V4W2_CID_AEC_UPDATE_INTEWVAW,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "AEC Update Intewvaw",
		.min		= 0,
		.max		= 16,
		.step		= 1,
		.def		= 2,
		.fwags		= 0,
	}, {
		.ops		= &mt9v032_ctww_ops,
		.id		= V4W2_CID_AGC_UPDATE_INTEWVAW,
		.type		= V4W2_CTWW_TYPE_INTEGEW,
		.name		= "AGC Update Intewvaw",
		.min		= 0,
		.max		= 16,
		.step		= 1,
		.def		= 2,
		.fwags		= 0,
	}
};

static const stwuct v4w2_ctww_config mt9v032_aec_max_shuttew_width = {
	.ops		= &mt9v032_ctww_ops,
	.id		= V4W2_CID_AEC_MAX_SHUTTEW_WIDTH,
	.type		= V4W2_CTWW_TYPE_INTEGEW,
	.name		= "AEC Max Shuttew Width",
	.min		= 1,
	.max		= 2047,
	.step		= 1,
	.def		= 480,
	.fwags		= 0,
};

static const stwuct v4w2_ctww_config mt9v034_aec_max_shuttew_width = {
	.ops		= &mt9v032_ctww_ops,
	.id		= V4W2_CID_AEC_MAX_SHUTTEW_WIDTH,
	.type		= V4W2_CTWW_TYPE_INTEGEW,
	.name		= "AEC Max Shuttew Width",
	.min		= 1,
	.max		= 32765,
	.step		= 1,
	.def		= 480,
	.fwags		= 0,
};

/* -----------------------------------------------------------------------------
 * V4W2 subdev cowe opewations
 */

static int mt9v032_set_powew(stwuct v4w2_subdev *subdev, int on)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);
	int wet = 0;

	mutex_wock(&mt9v032->powew_wock);

	/* If the powew count is modified fwom 0 to != 0 ow fwom != 0 to 0,
	 * update the powew state.
	 */
	if (mt9v032->powew_count == !on) {
		wet = __mt9v032_set_powew(mt9v032, !!on);
		if (wet < 0)
			goto done;
	}

	/* Update the powew count. */
	mt9v032->powew_count += on ? 1 : -1;
	WAWN_ON(mt9v032->powew_count < 0);

done:
	mutex_unwock(&mt9v032->powew_wock);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev intewnaw opewations
 */

static int mt9v032_wegistewed(stwuct v4w2_subdev *subdev)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);
	unsigned int i;
	u32 vewsion;
	int wet;

	dev_info(&cwient->dev, "Pwobing MT9V032 at addwess 0x%02x\n",
			cwient->addw);

	wet = mt9v032_powew_on(mt9v032);
	if (wet < 0) {
		dev_eww(&cwient->dev, "MT9V032 powew up faiwed\n");
		wetuwn wet;
	}

	/* Wead and check the sensow vewsion */
	wet = wegmap_wead(mt9v032->wegmap, MT9V032_CHIP_VEWSION, &vewsion);

	mt9v032_powew_off(mt9v032);

	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed weading chip vewsion\n");
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(mt9v032_vewsions); ++i) {
		if (mt9v032_vewsions[i].vewsion == vewsion) {
			mt9v032->vewsion = &mt9v032_vewsions[i];
			bweak;
		}
	}

	if (mt9v032->vewsion == NUWW) {
		dev_eww(&cwient->dev, "Unsuppowted chip vewsion 0x%04x\n",
			vewsion);
		wetuwn -ENODEV;
	}

	dev_info(&cwient->dev, "%s detected at addwess 0x%02x\n",
		 mt9v032->vewsion->name, cwient->addw);

	mt9v032_configuwe_pixew_wate(mt9v032);

	wetuwn wet;
}

static int mt9v032_open(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;

	cwop = v4w2_subdev_state_get_cwop(fh->state, 0);
	cwop->weft = MT9V032_COWUMN_STAWT_DEF;
	cwop->top = MT9V032_WOW_STAWT_DEF;
	cwop->width = MT9V032_WINDOW_WIDTH_DEF;
	cwop->height = MT9V032_WINDOW_HEIGHT_DEF;

	fowmat = v4w2_subdev_state_get_fowmat(fh->state, 0);

	if (mt9v032->modew->cowow)
		fowmat->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	ewse
		fowmat->code = MEDIA_BUS_FMT_Y10_1X10;

	fowmat->width = MT9V032_WINDOW_WIDTH_DEF;
	fowmat->height = MT9V032_WINDOW_HEIGHT_DEF;
	fowmat->fiewd = V4W2_FIEWD_NONE;
	fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;

	wetuwn mt9v032_set_powew(subdev, 1);
}

static int mt9v032_cwose(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	wetuwn mt9v032_set_powew(subdev, 0);
}

static const stwuct v4w2_subdev_cowe_ops mt9v032_subdev_cowe_ops = {
	.s_powew	= mt9v032_set_powew,
};

static const stwuct v4w2_subdev_video_ops mt9v032_subdev_video_ops = {
	.s_stweam	= mt9v032_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops mt9v032_subdev_pad_ops = {
	.enum_mbus_code = mt9v032_enum_mbus_code,
	.enum_fwame_size = mt9v032_enum_fwame_size,
	.get_fmt = mt9v032_get_fowmat,
	.set_fmt = mt9v032_set_fowmat,
	.get_sewection = mt9v032_get_sewection,
	.set_sewection = mt9v032_set_sewection,
};

static const stwuct v4w2_subdev_ops mt9v032_subdev_ops = {
	.cowe	= &mt9v032_subdev_cowe_ops,
	.video	= &mt9v032_subdev_video_ops,
	.pad	= &mt9v032_subdev_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops mt9v032_subdev_intewnaw_ops = {
	.wegistewed = mt9v032_wegistewed,
	.open = mt9v032_open,
	.cwose = mt9v032_cwose,
};

static const stwuct wegmap_config mt9v032_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0xff,
	.cache_type = WEGCACHE_WBTWEE,
};

/* -----------------------------------------------------------------------------
 * Dwivew initiawization and pwobing
 */

static stwuct mt9v032_pwatfowm_data *
mt9v032_get_pdata(stwuct i2c_cwient *cwient)
{
	stwuct mt9v032_pwatfowm_data *pdata = NUWW;
	stwuct v4w2_fwnode_endpoint endpoint = { .bus_type = 0 };
	stwuct device_node *np;
	stwuct pwopewty *pwop;

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

	pwop = of_find_pwopewty(np, "wink-fwequencies", NUWW);
	if (pwop) {
		u64 *wink_fweqs;
		size_t size = pwop->wength / sizeof(*wink_fweqs);

		wink_fweqs = devm_kcawwoc(&cwient->dev, size,
					  sizeof(*wink_fweqs), GFP_KEWNEW);
		if (!wink_fweqs)
			goto done;

		if (of_pwopewty_wead_u64_awway(np, "wink-fwequencies",
					       wink_fweqs, size) < 0)
			goto done;

		pdata->wink_fweqs = wink_fweqs;
		pdata->wink_def_fweq = wink_fweqs[0];
	}

	pdata->cwk_pow = !!(endpoint.bus.pawawwew.fwags &
			    V4W2_MBUS_PCWK_SAMPWE_WISING);

done:
	of_node_put(np);
	wetuwn pdata;
}

static int mt9v032_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mt9v032_pwatfowm_data *pdata = mt9v032_get_pdata(cwient);
	stwuct mt9v032 *mt9v032;
	unsigned int i;
	int wet;

	mt9v032 = devm_kzawwoc(&cwient->dev, sizeof(*mt9v032), GFP_KEWNEW);
	if (!mt9v032)
		wetuwn -ENOMEM;

	mt9v032->wegmap = devm_wegmap_init_i2c(cwient, &mt9v032_wegmap_config);
	if (IS_EWW(mt9v032->wegmap))
		wetuwn PTW_EWW(mt9v032->wegmap);

	mt9v032->cwk = devm_cwk_get(&cwient->dev, NUWW);
	if (IS_EWW(mt9v032->cwk))
		wetuwn PTW_EWW(mt9v032->cwk);

	mt9v032->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						      GPIOD_OUT_HIGH);
	if (IS_EWW(mt9v032->weset_gpio))
		wetuwn PTW_EWW(mt9v032->weset_gpio);

	mt9v032->standby_gpio = devm_gpiod_get_optionaw(&cwient->dev, "standby",
							GPIOD_OUT_WOW);
	if (IS_EWW(mt9v032->standby_gpio))
		wetuwn PTW_EWW(mt9v032->standby_gpio);

	mutex_init(&mt9v032->powew_wock);
	mt9v032->pdata = pdata;
	mt9v032->modew = i2c_get_match_data(cwient);

	v4w2_ctww_handwew_init(&mt9v032->ctwws, 11 +
			       AWWAY_SIZE(mt9v032_aegc_contwows));

	v4w2_ctww_new_std(&mt9v032->ctwws, &mt9v032_ctww_ops,
			  V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
	v4w2_ctww_new_std(&mt9v032->ctwws, &mt9v032_ctww_ops,
			  V4W2_CID_GAIN, MT9V032_ANAWOG_GAIN_MIN,
			  MT9V032_ANAWOG_GAIN_MAX, 1, MT9V032_ANAWOG_GAIN_DEF);
	v4w2_ctww_new_std_menu(&mt9v032->ctwws, &mt9v032_ctww_ops,
			       V4W2_CID_EXPOSUWE_AUTO, V4W2_EXPOSUWE_MANUAW, 0,
			       V4W2_EXPOSUWE_AUTO);
	v4w2_ctww_new_std(&mt9v032->ctwws, &mt9v032_ctww_ops,
			  V4W2_CID_EXPOSUWE, mt9v032->modew->data->min_shuttew,
			  mt9v032->modew->data->max_shuttew, 1,
			  MT9V032_TOTAW_SHUTTEW_WIDTH_DEF);
	v4w2_ctww_new_std(&mt9v032->ctwws, &mt9v032_ctww_ops,
			  V4W2_CID_HBWANK, mt9v032->modew->data->min_hbwank,
			  MT9V032_HOWIZONTAW_BWANKING_MAX, 1,
			  MT9V032_HOWIZONTAW_BWANKING_DEF);
	v4w2_ctww_new_std(&mt9v032->ctwws, &mt9v032_ctww_ops,
			  V4W2_CID_VBWANK, mt9v032->modew->data->min_vbwank,
			  mt9v032->modew->data->max_vbwank, 1,
			  MT9V032_VEWTICAW_BWANKING_DEF);
	mt9v032->test_pattewn = v4w2_ctww_new_std_menu_items(&mt9v032->ctwws,
				&mt9v032_ctww_ops, V4W2_CID_TEST_PATTEWN,
				AWWAY_SIZE(mt9v032_test_pattewn_menu) - 1, 0, 0,
				mt9v032_test_pattewn_menu);
	mt9v032->test_pattewn_cowow = v4w2_ctww_new_custom(&mt9v032->ctwws,
				      &mt9v032_test_pattewn_cowow, NUWW);

	v4w2_ctww_new_custom(&mt9v032->ctwws,
			     mt9v032->modew->data->aec_max_shuttew_v4w2_ctww,
			     NUWW);
	fow (i = 0; i < AWWAY_SIZE(mt9v032_aegc_contwows); ++i)
		v4w2_ctww_new_custom(&mt9v032->ctwws, &mt9v032_aegc_contwows[i],
				     NUWW);

	v4w2_ctww_cwustew(2, &mt9v032->test_pattewn);

	mt9v032->pixew_wate =
		v4w2_ctww_new_std(&mt9v032->ctwws, &mt9v032_ctww_ops,
				  V4W2_CID_PIXEW_WATE, 1, INT_MAX, 1, 1);

	if (pdata && pdata->wink_fweqs) {
		unsigned int def = 0;

		fow (i = 0; pdata->wink_fweqs[i]; ++i) {
			if (pdata->wink_fweqs[i] == pdata->wink_def_fweq)
				def = i;
		}

		mt9v032->wink_fweq =
			v4w2_ctww_new_int_menu(&mt9v032->ctwws,
					       &mt9v032_ctww_ops,
					       V4W2_CID_WINK_FWEQ, i - 1, def,
					       pdata->wink_fweqs);
		v4w2_ctww_cwustew(2, &mt9v032->wink_fweq);
	}


	mt9v032->subdev.ctww_handwew = &mt9v032->ctwws;

	if (mt9v032->ctwws.ewwow) {
		dev_eww(&cwient->dev, "contwow initiawization ewwow %d\n",
			mt9v032->ctwws.ewwow);
		wet = mt9v032->ctwws.ewwow;
		goto eww;
	}

	mt9v032->cwop.weft = MT9V032_COWUMN_STAWT_DEF;
	mt9v032->cwop.top = MT9V032_WOW_STAWT_DEF;
	mt9v032->cwop.width = MT9V032_WINDOW_WIDTH_DEF;
	mt9v032->cwop.height = MT9V032_WINDOW_HEIGHT_DEF;

	if (mt9v032->modew->cowow)
		mt9v032->fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	ewse
		mt9v032->fowmat.code = MEDIA_BUS_FMT_Y10_1X10;

	mt9v032->fowmat.width = MT9V032_WINDOW_WIDTH_DEF;
	mt9v032->fowmat.height = MT9V032_WINDOW_HEIGHT_DEF;
	mt9v032->fowmat.fiewd = V4W2_FIEWD_NONE;
	mt9v032->fowmat.cowowspace = V4W2_COWOWSPACE_SWGB;

	mt9v032->hwatio = 1;
	mt9v032->vwatio = 1;

	mt9v032->aec_agc = MT9V032_AEC_ENABWE | MT9V032_AGC_ENABWE;
	mt9v032->hbwank = MT9V032_HOWIZONTAW_BWANKING_DEF;
	mt9v032->syscwk = MT9V032_SYSCWK_FWEQ_DEF;

	v4w2_i2c_subdev_init(&mt9v032->subdev, cwient, &mt9v032_subdev_ops);
	mt9v032->subdev.intewnaw_ops = &mt9v032_subdev_intewnaw_ops;
	mt9v032->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	mt9v032->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	mt9v032->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&mt9v032->subdev.entity, 1, &mt9v032->pad);
	if (wet < 0)
		goto eww;

	mt9v032->subdev.dev = &cwient->dev;
	wet = v4w2_async_wegistew_subdev(&mt9v032->subdev);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	media_entity_cweanup(&mt9v032->subdev.entity);
	v4w2_ctww_handwew_fwee(&mt9v032->ctwws);
	wetuwn wet;
}

static void mt9v032_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *subdev = i2c_get_cwientdata(cwient);
	stwuct mt9v032 *mt9v032 = to_mt9v032(subdev);

	v4w2_async_unwegistew_subdev(subdev);
	v4w2_ctww_handwew_fwee(&mt9v032->ctwws);
	media_entity_cweanup(&subdev->entity);
}

static const stwuct mt9v032_modew_data mt9v032_modew_data[] = {
	{
		/* MT9V022, MT9V032 wevisions 1/2/3 */
		.min_wow_time = 660,
		.min_hbwank = MT9V032_HOWIZONTAW_BWANKING_MIN,
		.min_vbwank = MT9V032_VEWTICAW_BWANKING_MIN,
		.max_vbwank = MT9V032_VEWTICAW_BWANKING_MAX,
		.min_shuttew = MT9V032_TOTAW_SHUTTEW_WIDTH_MIN,
		.max_shuttew = MT9V032_TOTAW_SHUTTEW_WIDTH_MAX,
		.pcwk_weg = MT9V032_PIXEW_CWOCK,
		.aec_max_shuttew_weg = MT9V032_AEC_MAX_SHUTTEW_WIDTH,
		.aec_max_shuttew_v4w2_ctww = &mt9v032_aec_max_shuttew_width,
	}, {
		/* MT9V024, MT9V034 */
		.min_wow_time = 690,
		.min_hbwank = MT9V034_HOWIZONTAW_BWANKING_MIN,
		.min_vbwank = MT9V034_VEWTICAW_BWANKING_MIN,
		.max_vbwank = MT9V034_VEWTICAW_BWANKING_MAX,
		.min_shuttew = MT9V034_TOTAW_SHUTTEW_WIDTH_MIN,
		.max_shuttew = MT9V034_TOTAW_SHUTTEW_WIDTH_MAX,
		.pcwk_weg = MT9V034_PIXEW_CWOCK,
		.aec_max_shuttew_weg = MT9V034_AEC_MAX_SHUTTEW_WIDTH,
		.aec_max_shuttew_v4w2_ctww = &mt9v034_aec_max_shuttew_width,
	},
};

static const stwuct mt9v032_modew_info mt9v032_modews[] = {
	[MT9V032_MODEW_V022_COWOW] = {
		.data = &mt9v032_modew_data[0],
		.cowow = twue,
	},
	[MT9V032_MODEW_V022_MONO] = {
		.data = &mt9v032_modew_data[0],
		.cowow = fawse,
	},
	[MT9V032_MODEW_V024_COWOW] = {
		.data = &mt9v032_modew_data[1],
		.cowow = twue,
	},
	[MT9V032_MODEW_V024_MONO] = {
		.data = &mt9v032_modew_data[1],
		.cowow = fawse,
	},
	[MT9V032_MODEW_V032_COWOW] = {
		.data = &mt9v032_modew_data[0],
		.cowow = twue,
	},
	[MT9V032_MODEW_V032_MONO] = {
		.data = &mt9v032_modew_data[0],
		.cowow = fawse,
	},
	[MT9V032_MODEW_V034_COWOW] = {
		.data = &mt9v032_modew_data[1],
		.cowow = twue,
	},
	[MT9V032_MODEW_V034_MONO] = {
		.data = &mt9v032_modew_data[1],
		.cowow = fawse,
	},
};

static const stwuct i2c_device_id mt9v032_id[] = {
	{ "mt9v022", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V022_COWOW] },
	{ "mt9v022m", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V022_MONO] },
	{ "mt9v024", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V024_COWOW] },
	{ "mt9v024m", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V024_MONO] },
	{ "mt9v032", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V032_COWOW] },
	{ "mt9v032m", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V032_MONO] },
	{ "mt9v034", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V034_COWOW] },
	{ "mt9v034m", (kewnew_uwong_t)&mt9v032_modews[MT9V032_MODEW_V034_MONO] },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, mt9v032_id);

static const stwuct of_device_id mt9v032_of_match[] = {
	{ .compatibwe = "aptina,mt9v022", .data = &mt9v032_modews[MT9V032_MODEW_V022_COWOW] },
	{ .compatibwe = "aptina,mt9v022m", .data = &mt9v032_modews[MT9V032_MODEW_V022_MONO] },
	{ .compatibwe = "aptina,mt9v024", .data = &mt9v032_modews[MT9V032_MODEW_V024_COWOW] },
	{ .compatibwe = "aptina,mt9v024m", .data = &mt9v032_modews[MT9V032_MODEW_V024_MONO] },
	{ .compatibwe = "aptina,mt9v032", .data = &mt9v032_modews[MT9V032_MODEW_V032_COWOW] },
	{ .compatibwe = "aptina,mt9v032m", .data = &mt9v032_modews[MT9V032_MODEW_V032_MONO] },
	{ .compatibwe = "aptina,mt9v034", .data = &mt9v032_modews[MT9V032_MODEW_V034_COWOW] },
	{ .compatibwe = "aptina,mt9v034m", .data = &mt9v032_modews[MT9V032_MODEW_V034_MONO] },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mt9v032_of_match);

static stwuct i2c_dwivew mt9v032_dwivew = {
	.dwivew = {
		.name = "mt9v032",
		.of_match_tabwe = mt9v032_of_match,
	},
	.pwobe		= mt9v032_pwobe,
	.wemove		= mt9v032_wemove,
	.id_tabwe	= mt9v032_id,
};

moduwe_i2c_dwivew(mt9v032_dwivew);

MODUWE_DESCWIPTION("Aptina MT9V032 Camewa dwivew");
MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_WICENSE("GPW");
