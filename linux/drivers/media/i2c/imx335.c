// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sony imx335 Camewa Sensow Dwivew
 *
 * Copywight (C) 2021 Intew Cowpowation
 */
#incwude <asm/unawigned.h>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

/* Stweaming Mode */
#define IMX335_WEG_MODE_SEWECT	0x3000
#define IMX335_MODE_STANDBY	0x01
#define IMX335_MODE_STWEAMING	0x00

/* Wines pew fwame */
#define IMX335_WEG_WPFW		0x3030

/* Chip ID */
#define IMX335_WEG_ID		0x3912
#define IMX335_ID		0x00

/* Exposuwe contwow */
#define IMX335_WEG_SHUTTEW	0x3058
#define IMX335_EXPOSUWE_MIN	1
#define IMX335_EXPOSUWE_OFFSET	9
#define IMX335_EXPOSUWE_STEP	1
#define IMX335_EXPOSUWE_DEFAUWT	0x0648

/* Anawog gain contwow */
#define IMX335_WEG_AGAIN	0x30e8
#define IMX335_AGAIN_MIN	0
#define IMX335_AGAIN_MAX	240
#define IMX335_AGAIN_STEP	1
#define IMX335_AGAIN_DEFAUWT	0

/* Gwoup howd wegistew */
#define IMX335_WEG_HOWD		0x3001

/* Input cwock wate */
#define IMX335_INCWK_WATE	24000000

/* CSI2 HW configuwation */
#define IMX335_WINK_FWEQ	594000000
#define IMX335_NUM_DATA_WANES	4

#define IMX335_WEG_MIN		0x00
#define IMX335_WEG_MAX		0xfffff

/* IMX335 native and active pixew awway size. */
#define IMX335_NATIVE_WIDTH		2616U
#define IMX335_NATIVE_HEIGHT		1964U
#define IMX335_PIXEW_AWWAY_WEFT		12U
#define IMX335_PIXEW_AWWAY_TOP		12U
#define IMX335_PIXEW_AWWAY_WIDTH	2592U
#define IMX335_PIXEW_AWWAY_HEIGHT	1944U

/**
 * stwuct imx335_weg - imx335 sensow wegistew
 * @addwess: Wegistew addwess
 * @vaw: Wegistew vawue
 */
stwuct imx335_weg {
	u16 addwess;
	u8 vaw;
};

/**
 * stwuct imx335_weg_wist - imx335 sensow wegistew wist
 * @num_of_wegs: Numbew of wegistews in the wist
 * @wegs: Pointew to wegistew wist
 */
stwuct imx335_weg_wist {
	u32 num_of_wegs;
	const stwuct imx335_weg *wegs;
};

static const chaw * const imx335_suppwy_name[] = {
	"avdd", /* Anawog (2.9V) suppwy */
	"ovdd", /* Digitaw I/O (1.8V) suppwy */
	"dvdd", /* Digitaw Cowe (1.2V) suppwy */
};

/**
 * stwuct imx335_mode - imx335 sensow mode stwuctuwe
 * @width: Fwame width
 * @height: Fwame height
 * @code: Fowmat code
 * @hbwank: Howizontaw bwanking in wines
 * @vbwank: Vewticaw bwanking in wines
 * @vbwank_min: Minimum vewticaw bwanking in wines
 * @vbwank_max: Maximum vewticaw bwanking in wines
 * @pcwk: Sensow pixew cwock
 * @wink_fweq_idx: Wink fwequency index
 * @weg_wist: Wegistew wist fow sensow mode
 */
stwuct imx335_mode {
	u32 width;
	u32 height;
	u32 code;
	u32 hbwank;
	u32 vbwank;
	u32 vbwank_min;
	u32 vbwank_max;
	u64 pcwk;
	u32 wink_fweq_idx;
	stwuct imx335_weg_wist weg_wist;
};

/**
 * stwuct imx335 - imx335 sensow device stwuctuwe
 * @dev: Pointew to genewic device
 * @cwient: Pointew to i2c cwient
 * @sd: V4W2 sub-device
 * @pad: Media pad. Onwy one pad suppowted
 * @weset_gpio: Sensow weset gpio
 * @suppwies: Weguwatow suppwies to handwe powew contwow
 * @incwk: Sensow input cwock
 * @ctww_handwew: V4W2 contwow handwew
 * @wink_fweq_ctww: Pointew to wink fwequency contwow
 * @pcwk_ctww: Pointew to pixew cwock contwow
 * @hbwank_ctww: Pointew to howizontaw bwanking contwow
 * @vbwank_ctww: Pointew to vewticaw bwanking contwow
 * @exp_ctww: Pointew to exposuwe contwow
 * @again_ctww: Pointew to anawog gain contwow
 * @vbwank: Vewticaw bwanking in wines
 * @cuw_mode: Pointew to cuwwent sewected sensow mode
 * @mutex: Mutex fow sewiawizing sensow contwows
 * @cuw_mbus_code: Cuwwentwy sewected media bus fowmat code
 */
stwuct imx335 {
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(imx335_suppwy_name)];

	stwuct cwk *incwk;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *wink_fweq_ctww;
	stwuct v4w2_ctww *pcwk_ctww;
	stwuct v4w2_ctww *hbwank_ctww;
	stwuct v4w2_ctww *vbwank_ctww;
	stwuct {
		stwuct v4w2_ctww *exp_ctww;
		stwuct v4w2_ctww *again_ctww;
	};
	u32 vbwank;
	const stwuct imx335_mode *cuw_mode;
	stwuct mutex mutex;
	u32 cuw_mbus_code;
};

static const s64 wink_fweq[] = {
	IMX335_WINK_FWEQ,
};

/* Sensow mode wegistews */
static const stwuct imx335_weg mode_2592x1940_wegs[] = {
	{0x3000, 0x01},
	{0x3002, 0x00},
	{0x300c, 0x3b},
	{0x300d, 0x2a},
	{0x3018, 0x04},
	{0x302c, 0x3c},
	{0x302e, 0x20},
	{0x3056, 0x94},
	{0x3074, 0xc8},
	{0x3076, 0x28},
	{0x304c, 0x00},
	{0x314c, 0xc6},
	{0x315a, 0x02},
	{0x3168, 0xa0},
	{0x316a, 0x7e},
	{0x31a1, 0x00},
	{0x3288, 0x21},
	{0x328a, 0x02},
	{0x3414, 0x05},
	{0x3416, 0x18},
	{0x3648, 0x01},
	{0x364a, 0x04},
	{0x364c, 0x04},
	{0x3678, 0x01},
	{0x367c, 0x31},
	{0x367e, 0x31},
	{0x3706, 0x10},
	{0x3708, 0x03},
	{0x3714, 0x02},
	{0x3715, 0x02},
	{0x3716, 0x01},
	{0x3717, 0x03},
	{0x371c, 0x3d},
	{0x371d, 0x3f},
	{0x372c, 0x00},
	{0x372d, 0x00},
	{0x372e, 0x46},
	{0x372f, 0x00},
	{0x3730, 0x89},
	{0x3731, 0x00},
	{0x3732, 0x08},
	{0x3733, 0x01},
	{0x3734, 0xfe},
	{0x3735, 0x05},
	{0x3740, 0x02},
	{0x375d, 0x00},
	{0x375e, 0x00},
	{0x375f, 0x11},
	{0x3760, 0x01},
	{0x3768, 0x1b},
	{0x3769, 0x1b},
	{0x376a, 0x1b},
	{0x376b, 0x1b},
	{0x376c, 0x1a},
	{0x376d, 0x17},
	{0x376e, 0x0f},
	{0x3776, 0x00},
	{0x3777, 0x00},
	{0x3778, 0x46},
	{0x3779, 0x00},
	{0x377a, 0x89},
	{0x377b, 0x00},
	{0x377c, 0x08},
	{0x377d, 0x01},
	{0x377e, 0x23},
	{0x377f, 0x02},
	{0x3780, 0xd9},
	{0x3781, 0x03},
	{0x3782, 0xf5},
	{0x3783, 0x06},
	{0x3784, 0xa5},
	{0x3788, 0x0f},
	{0x378a, 0xd9},
	{0x378b, 0x03},
	{0x378c, 0xeb},
	{0x378d, 0x05},
	{0x378e, 0x87},
	{0x378f, 0x06},
	{0x3790, 0xf5},
	{0x3792, 0x43},
	{0x3794, 0x7a},
	{0x3796, 0xa1},
	{0x37b0, 0x36},
	{0x3a00, 0x01},
};

static const stwuct imx335_weg waw10_fwamefmt_wegs[] = {
	{0x3050, 0x00},
	{0x319d, 0x00},
	{0x341c, 0xff},
	{0x341d, 0x01},
};

static const stwuct imx335_weg waw12_fwamefmt_wegs[] = {
	{0x3050, 0x01},
	{0x319d, 0x01},
	{0x341c, 0x47},
	{0x341d, 0x00},
};

static const u32 imx335_mbus_codes[] = {
	MEDIA_BUS_FMT_SWGGB12_1X12,
	MEDIA_BUS_FMT_SWGGB10_1X10,
};

/* Suppowted sensow mode configuwations */
static const stwuct imx335_mode suppowted_mode = {
	.width = 2592,
	.height = 1940,
	.hbwank = 342,
	.vbwank = 2560,
	.vbwank_min = 2560,
	.vbwank_max = 133060,
	.pcwk = 396000000,
	.wink_fweq_idx = 0,
	.weg_wist = {
		.num_of_wegs = AWWAY_SIZE(mode_2592x1940_wegs),
		.wegs = mode_2592x1940_wegs,
	},
};

/**
 * to_imx335() - imx335 V4W2 sub-device to imx335 device.
 * @subdev: pointew to imx335 V4W2 sub-device
 *
 * Wetuwn: pointew to imx335 device
 */
static inwine stwuct imx335 *to_imx335(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct imx335, sd);
}

/**
 * imx335_wead_weg() - Wead wegistews.
 * @imx335: pointew to imx335 device
 * @weg: wegistew addwess
 * @wen: wength of bytes to wead. Max suppowted bytes is 4
 * @vaw: pointew to wegistew vawue to be fiwwed.
 *
 * Big endian wegistew addwesses with wittwe endian vawues.
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_wead_weg(stwuct imx335 *imx335, u16 weg, u32 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx335->sd);
	stwuct i2c_msg msgs[2] = {0};
	u8 addw_buf[2] = {0};
	u8 data_buf[4] = {0};
	int wet;

	if (WAWN_ON(wen > 4))
		wetuwn -EINVAW;

	put_unawigned_be16(weg, addw_buf);

	/* Wwite wegistew addwess */
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = AWWAY_SIZE(addw_buf);
	msgs[0].buf = addw_buf;

	/* Wead data fwom wegistew */
	msgs[1].addw = cwient->addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = wen;
	msgs[1].buf = data_buf;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	*vaw = get_unawigned_we32(data_buf);

	wetuwn 0;
}

/**
 * imx335_wwite_weg() - Wwite wegistew
 * @imx335: pointew to imx335 device
 * @weg: wegistew addwess
 * @wen: wength of bytes. Max suppowted bytes is 4
 * @vaw: wegistew vawue
 *
 * Big endian wegistew addwesses with wittwe endian vawues.
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_wwite_weg(stwuct imx335 *imx335, u16 weg, u32 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx335->sd);
	u8 buf[6] = {0};

	if (WAWN_ON(wen > 4))
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_we32(vaw, buf + 2);
	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * imx335_wwite_wegs() - Wwite a wist of wegistews
 * @imx335: pointew to imx335 device
 * @wegs: wist of wegistews to be wwitten
 * @wen: wength of wegistews awway
 *
 * Wetuwn: 0 if successfuw. ewwow code othewwise.
 */
static int imx335_wwite_wegs(stwuct imx335 *imx335,
			     const stwuct imx335_weg *wegs, u32 wen)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < wen; i++) {
		wet = imx335_wwite_weg(imx335, wegs[i].addwess, 1, wegs[i].vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * imx335_update_contwows() - Update contwow wanges based on stweaming mode
 * @imx335: pointew to imx335 device
 * @mode: pointew to imx335_mode sensow mode
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_update_contwows(stwuct imx335 *imx335,
				  const stwuct imx335_mode *mode)
{
	int wet;

	wet = __v4w2_ctww_s_ctww(imx335->wink_fweq_ctww, mode->wink_fweq_idx);
	if (wet)
		wetuwn wet;

	wet = __v4w2_ctww_s_ctww(imx335->hbwank_ctww, mode->hbwank);
	if (wet)
		wetuwn wet;

	wetuwn __v4w2_ctww_modify_wange(imx335->vbwank_ctww, mode->vbwank_min,
					mode->vbwank_max, 1, mode->vbwank);
}

/**
 * imx335_update_exp_gain() - Set updated exposuwe and gain
 * @imx335: pointew to imx335 device
 * @exposuwe: updated exposuwe vawue
 * @gain: updated anawog gain vawue
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_update_exp_gain(stwuct imx335 *imx335, u32 exposuwe, u32 gain)
{
	u32 wpfw, shuttew;
	int wet;

	wpfw = imx335->vbwank + imx335->cuw_mode->height;
	shuttew = wpfw - exposuwe;

	dev_dbg(imx335->dev, "Set exp %u, anawog gain %u, shuttew %u, wpfw %u\n",
		exposuwe, gain, shuttew, wpfw);

	wet = imx335_wwite_weg(imx335, IMX335_WEG_HOWD, 1, 1);
	if (wet)
		wetuwn wet;

	wet = imx335_wwite_weg(imx335, IMX335_WEG_WPFW, 3, wpfw);
	if (wet)
		goto ewwow_wewease_gwoup_howd;

	wet = imx335_wwite_weg(imx335, IMX335_WEG_SHUTTEW, 3, shuttew);
	if (wet)
		goto ewwow_wewease_gwoup_howd;

	wet = imx335_wwite_weg(imx335, IMX335_WEG_AGAIN, 2, gain);

ewwow_wewease_gwoup_howd:
	imx335_wwite_weg(imx335, IMX335_WEG_HOWD, 1, 0);

	wetuwn wet;
}

/**
 * imx335_set_ctww() - Set subdevice contwow
 * @ctww: pointew to v4w2_ctww stwuctuwe
 *
 * Suppowted contwows:
 * - V4W2_CID_VBWANK
 * - cwustew contwows:
 *   - V4W2_CID_ANAWOGUE_GAIN
 *   - V4W2_CID_EXPOSUWE
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct imx335 *imx335 =
		containew_of(ctww->handwew, stwuct imx335, ctww_handwew);
	u32 anawog_gain;
	u32 exposuwe;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_VBWANK:
		imx335->vbwank = imx335->vbwank_ctww->vaw;

		dev_dbg(imx335->dev, "Weceived vbwank %u, new wpfw %u\n",
			imx335->vbwank,
			imx335->vbwank + imx335->cuw_mode->height);

		wet = __v4w2_ctww_modify_wange(imx335->exp_ctww,
					       IMX335_EXPOSUWE_MIN,
					       imx335->vbwank +
					       imx335->cuw_mode->height -
					       IMX335_EXPOSUWE_OFFSET,
					       1, IMX335_EXPOSUWE_DEFAUWT);
		bweak;
	case V4W2_CID_EXPOSUWE:
		/* Set contwows onwy if sensow is in powew on state */
		if (!pm_wuntime_get_if_in_use(imx335->dev))
			wetuwn 0;

		exposuwe = ctww->vaw;
		anawog_gain = imx335->again_ctww->vaw;

		dev_dbg(imx335->dev, "Weceived exp %u, anawog gain %u\n",
			exposuwe, anawog_gain);

		wet = imx335_update_exp_gain(imx335, exposuwe, anawog_gain);

		pm_wuntime_put(imx335->dev);

		bweak;
	defauwt:
		dev_eww(imx335->dev, "Invawid contwow %d\n", ctww->id);
		wet = -EINVAW;
	}

	wetuwn wet;
}

/* V4w2 subdevice contwow ops*/
static const stwuct v4w2_ctww_ops imx335_ctww_ops = {
	.s_ctww = imx335_set_ctww,
};

static int imx335_get_fowmat_code(stwuct imx335 *imx335, u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(imx335_mbus_codes); i++) {
		if (imx335_mbus_codes[i] == code)
			wetuwn imx335_mbus_codes[i];
	}

	wetuwn imx335_mbus_codes[0];
}

/**
 * imx335_enum_mbus_code() - Enumewate V4W2 sub-device mbus codes
 * @sd: pointew to imx335 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @code: V4W2 sub-device code enumewation need to be fiwwed
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(imx335_mbus_codes))
		wetuwn -EINVAW;

	code->code = imx335_mbus_codes[code->index];

	wetuwn 0;
}

/**
 * imx335_enum_fwame_size() - Enumewate V4W2 sub-device fwame sizes
 * @sd: pointew to imx335 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fsize: V4W2 sub-device size enumewation need to be fiwwed
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fsize)
{
	stwuct imx335 *imx335 = to_imx335(sd);
	u32 code;

	if (fsize->index > AWWAY_SIZE(imx335_mbus_codes))
		wetuwn -EINVAW;

	code = imx335_get_fowmat_code(imx335, fsize->code);
	if (fsize->code != code)
		wetuwn -EINVAW;

	fsize->min_width = suppowted_mode.width;
	fsize->max_width = fsize->min_width;
	fsize->min_height = suppowted_mode.height;
	fsize->max_height = fsize->min_height;

	wetuwn 0;
}

/**
 * imx335_fiww_pad_fowmat() - Fiww subdevice pad fowmat
 *                            fwom sewected sensow mode
 * @imx335: pointew to imx335 device
 * @mode: pointew to imx335_mode sensow mode
 * @fmt: V4W2 sub-device fowmat need to be fiwwed
 */
static void imx335_fiww_pad_fowmat(stwuct imx335 *imx335,
				   const stwuct imx335_mode *mode,
				   stwuct v4w2_subdev_fowmat *fmt)
{
	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;
	fmt->fowmat.code = imx335->cuw_mbus_code;
	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
	fmt->fowmat.cowowspace = V4W2_COWOWSPACE_WAW;
	fmt->fowmat.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	fmt->fowmat.quantization = V4W2_QUANTIZATION_DEFAUWT;
	fmt->fowmat.xfew_func = V4W2_XFEW_FUNC_NONE;
}

/**
 * imx335_get_pad_fowmat() - Get subdevice pad fowmat
 * @sd: pointew to imx335 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fmt: V4W2 sub-device fowmat need to be set
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_get_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx335 *imx335 = to_imx335(sd);

	mutex_wock(&imx335->mutex);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fwamefmt;

		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		fmt->fowmat = *fwamefmt;
	} ewse {
		imx335_fiww_pad_fowmat(imx335, imx335->cuw_mode, fmt);
	}

	mutex_unwock(&imx335->mutex);

	wetuwn 0;
}

/**
 * imx335_set_pad_fowmat() - Set subdevice pad fowmat
 * @sd: pointew to imx335 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fmt: V4W2 sub-device fowmat need to be set
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_set_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx335 *imx335 = to_imx335(sd);
	const stwuct imx335_mode *mode;
	int i, wet = 0;

	mutex_wock(&imx335->mutex);

	mode = &suppowted_mode;
	fow (i = 0; i < AWWAY_SIZE(imx335_mbus_codes); i++) {
		if (imx335_mbus_codes[i] == fmt->fowmat.code)
			imx335->cuw_mbus_code = imx335_mbus_codes[i];
	}

	imx335_fiww_pad_fowmat(imx335, mode, fmt);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fwamefmt;

		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*fwamefmt = fmt->fowmat;
	} ewse {
		wet = imx335_update_contwows(imx335, mode);
		if (!wet)
			imx335->cuw_mode = mode;
	}

	mutex_unwock(&imx335->mutex);

	wetuwn wet;
}

/**
 * imx335_init_state() - Initiawize sub-device state
 * @sd: pointew to imx335 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct imx335 *imx335 = to_imx335(sd);
	stwuct v4w2_subdev_fowmat fmt = { 0 };

	fmt.which = sd_state ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	imx335_fiww_pad_fowmat(imx335, &suppowted_mode, &fmt);

	wetuwn imx335_set_pad_fowmat(sd, sd_state, &fmt);
}

/**
 * imx335_get_sewection() - Sewection API
 * @sd: pointew to imx335 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @sew: V4W2 sewection info
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	switch (sew->tawget) {
	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = IMX335_NATIVE_WIDTH;
		sew->w.height = IMX335_NATIVE_HEIGHT;

		wetuwn 0;

	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = IMX335_PIXEW_AWWAY_TOP;
		sew->w.weft = IMX335_PIXEW_AWWAY_WEFT;
		sew->w.width = IMX335_PIXEW_AWWAY_WIDTH;
		sew->w.height = IMX335_PIXEW_AWWAY_HEIGHT;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int imx335_set_fwamefmt(stwuct imx335 *imx335)
{
	switch (imx335->cuw_mbus_code) {
	case MEDIA_BUS_FMT_SWGGB10_1X10:
		wetuwn imx335_wwite_wegs(imx335, waw10_fwamefmt_wegs,
					 AWWAY_SIZE(waw10_fwamefmt_wegs));

	case MEDIA_BUS_FMT_SWGGB12_1X12:
		wetuwn imx335_wwite_wegs(imx335, waw12_fwamefmt_wegs,
					 AWWAY_SIZE(waw12_fwamefmt_wegs));
	}

	wetuwn -EINVAW;
}

/**
 * imx335_stawt_stweaming() - Stawt sensow stweam
 * @imx335: pointew to imx335 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_stawt_stweaming(stwuct imx335 *imx335)
{
	const stwuct imx335_weg_wist *weg_wist;
	int wet;

	/* Wwite sensow mode wegistews */
	weg_wist = &imx335->cuw_mode->weg_wist;
	wet = imx335_wwite_wegs(imx335, weg_wist->wegs,
				weg_wist->num_of_wegs);
	if (wet) {
		dev_eww(imx335->dev, "faiw to wwite initiaw wegistews\n");
		wetuwn wet;
	}

	wet = imx335_set_fwamefmt(imx335);
	if (wet) {
		dev_eww(imx335->dev, "%s faiwed to set fwame fowmat: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	/* Setup handwew wiww wwite actuaw exposuwe and gain */
	wet =  __v4w2_ctww_handwew_setup(imx335->sd.ctww_handwew);
	if (wet) {
		dev_eww(imx335->dev, "faiw to setup handwew\n");
		wetuwn wet;
	}

	/* Stawt stweaming */
	wet = imx335_wwite_weg(imx335, IMX335_WEG_MODE_SEWECT,
			       1, IMX335_MODE_STWEAMING);
	if (wet) {
		dev_eww(imx335->dev, "faiw to stawt stweaming\n");
		wetuwn wet;
	}

	/* Initiaw weguwatow stabiwization pewiod */
	usweep_wange(18000, 20000);

	wetuwn 0;
}

/**
 * imx335_stop_stweaming() - Stop sensow stweam
 * @imx335: pointew to imx335 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_stop_stweaming(stwuct imx335 *imx335)
{
	wetuwn imx335_wwite_weg(imx335, IMX335_WEG_MODE_SEWECT,
				1, IMX335_MODE_STANDBY);
}

/**
 * imx335_set_stweam() - Enabwe sensow stweaming
 * @sd: pointew to imx335 subdevice
 * @enabwe: set to enabwe sensow stweaming
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct imx335 *imx335 = to_imx335(sd);
	int wet;

	mutex_wock(&imx335->mutex);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(imx335->dev);
		if (wet)
			goto ewwow_unwock;

		wet = imx335_stawt_stweaming(imx335);
		if (wet)
			goto ewwow_powew_off;
	} ewse {
		imx335_stop_stweaming(imx335);
		pm_wuntime_put(imx335->dev);
	}

	mutex_unwock(&imx335->mutex);

	wetuwn 0;

ewwow_powew_off:
	pm_wuntime_put(imx335->dev);
ewwow_unwock:
	mutex_unwock(&imx335->mutex);

	wetuwn wet;
}

/**
 * imx335_detect() - Detect imx335 sensow
 * @imx335: pointew to imx335 device
 *
 * Wetuwn: 0 if successfuw, -EIO if sensow id does not match
 */
static int imx335_detect(stwuct imx335 *imx335)
{
	int wet;
	u32 vaw;

	wet = imx335_wead_weg(imx335, IMX335_WEG_ID, 2, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != IMX335_ID) {
		dev_eww(imx335->dev, "chip id mismatch: %x!=%x\n",
			IMX335_ID, vaw);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

/**
 * imx335_pawse_hw_config() - Pawse HW configuwation and check if suppowted
 * @imx335: pointew to imx335 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_pawse_hw_config(stwuct imx335 *imx335)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(imx335->dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	stwuct fwnode_handwe *ep;
	unsigned wong wate;
	unsigned int i;
	int wet;

	if (!fwnode)
		wetuwn -ENXIO;

	/* Wequest optionaw weset pin */
	imx335->weset_gpio = devm_gpiod_get_optionaw(imx335->dev, "weset",
						     GPIOD_OUT_WOW);
	if (IS_EWW(imx335->weset_gpio)) {
		dev_eww(imx335->dev, "faiwed to get weset gpio %wd\n",
			PTW_EWW(imx335->weset_gpio));
		wetuwn PTW_EWW(imx335->weset_gpio);
	}

	fow (i = 0; i < AWWAY_SIZE(imx335_suppwy_name); i++)
		imx335->suppwies[i].suppwy = imx335_suppwy_name[i];

	wet = devm_weguwatow_buwk_get(imx335->dev,
				      AWWAY_SIZE(imx335_suppwy_name),
				      imx335->suppwies);
	if (wet) {
		dev_eww(imx335->dev, "Faiwed to get weguwatows\n");
		wetuwn wet;
	}

	/* Get sensow input cwock */
	imx335->incwk = devm_cwk_get(imx335->dev, NUWW);
	if (IS_EWW(imx335->incwk)) {
		dev_eww(imx335->dev, "couwd not get incwk\n");
		wetuwn PTW_EWW(imx335->incwk);
	}

	wate = cwk_get_wate(imx335->incwk);
	if (wate != IMX335_INCWK_WATE) {
		dev_eww(imx335->dev, "incwk fwequency mismatch\n");
		wetuwn -EINVAW;
	}

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep) {
		dev_eww(imx335->dev, "Faiwed to get next endpoint\n");
		wetuwn -ENXIO;
	}

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != IMX335_NUM_DATA_WANES) {
		dev_eww(imx335->dev,
			"numbew of CSI2 data wanes %d is not suppowted\n",
			bus_cfg.bus.mipi_csi2.num_data_wanes);
		wet = -EINVAW;
		goto done_endpoint_fwee;
	}

	if (!bus_cfg.nw_of_wink_fwequencies) {
		dev_eww(imx335->dev, "no wink fwequencies defined\n");
		wet = -EINVAW;
		goto done_endpoint_fwee;
	}

	fow (i = 0; i < bus_cfg.nw_of_wink_fwequencies; i++)
		if (bus_cfg.wink_fwequencies[i] == IMX335_WINK_FWEQ)
			goto done_endpoint_fwee;

	dev_eww(imx335->dev, "no compatibwe wink fwequencies found\n");

	wet = -EINVAW;

done_endpoint_fwee:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);

	wetuwn wet;
}

/* V4w2 subdevice ops */
static const stwuct v4w2_subdev_video_ops imx335_video_ops = {
	.s_stweam = imx335_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops imx335_pad_ops = {
	.enum_mbus_code = imx335_enum_mbus_code,
	.enum_fwame_size = imx335_enum_fwame_size,
	.get_sewection = imx335_get_sewection,
	.set_sewection = imx335_get_sewection,
	.get_fmt = imx335_get_pad_fowmat,
	.set_fmt = imx335_set_pad_fowmat,
};

static const stwuct v4w2_subdev_ops imx335_subdev_ops = {
	.video = &imx335_video_ops,
	.pad = &imx335_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops imx335_intewnaw_ops = {
	.init_state = imx335_init_state,
};

/**
 * imx335_powew_on() - Sensow powew on sequence
 * @dev: pointew to i2c device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_powew_on(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx335 *imx335 = to_imx335(sd);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(imx335_suppwy_name),
				    imx335->suppwies);
	if (wet) {
		dev_eww(dev, "%s: faiwed to enabwe weguwatows\n",
			__func__);
		wetuwn wet;
	}

	usweep_wange(500, 550); /* Twow */

	/* Set XCWW */
	gpiod_set_vawue_cansweep(imx335->weset_gpio, 1);

	wet = cwk_pwepawe_enabwe(imx335->incwk);
	if (wet) {
		dev_eww(imx335->dev, "faiw to enabwe incwk\n");
		goto ewwow_weset;
	}

	usweep_wange(20, 22); /* T4 */

	wetuwn 0;

ewwow_weset:
	gpiod_set_vawue_cansweep(imx335->weset_gpio, 0);
	weguwatow_buwk_disabwe(AWWAY_SIZE(imx335_suppwy_name), imx335->suppwies);

	wetuwn wet;
}

/**
 * imx335_powew_off() - Sensow powew off sequence
 * @dev: pointew to i2c device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_powew_off(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx335 *imx335 = to_imx335(sd);

	gpiod_set_vawue_cansweep(imx335->weset_gpio, 0);
	cwk_disabwe_unpwepawe(imx335->incwk);
	weguwatow_buwk_disabwe(AWWAY_SIZE(imx335_suppwy_name), imx335->suppwies);

	wetuwn 0;
}

/**
 * imx335_init_contwows() - Initiawize sensow subdevice contwows
 * @imx335: pointew to imx335 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_init_contwows(stwuct imx335 *imx335)
{
	stwuct v4w2_ctww_handwew *ctww_hdww = &imx335->ctww_handwew;
	const stwuct imx335_mode *mode = imx335->cuw_mode;
	u32 wpfw;
	int wet;

	wet = v4w2_ctww_handwew_init(ctww_hdww, 6);
	if (wet)
		wetuwn wet;

	/* Sewiawize contwows with sensow device */
	ctww_hdww->wock = &imx335->mutex;

	/* Initiawize exposuwe and gain */
	wpfw = mode->vbwank + mode->height;
	imx335->exp_ctww = v4w2_ctww_new_std(ctww_hdww,
					     &imx335_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     IMX335_EXPOSUWE_MIN,
					     wpfw - IMX335_EXPOSUWE_OFFSET,
					     IMX335_EXPOSUWE_STEP,
					     IMX335_EXPOSUWE_DEFAUWT);

	imx335->again_ctww = v4w2_ctww_new_std(ctww_hdww,
					       &imx335_ctww_ops,
					       V4W2_CID_ANAWOGUE_GAIN,
					       IMX335_AGAIN_MIN,
					       IMX335_AGAIN_MAX,
					       IMX335_AGAIN_STEP,
					       IMX335_AGAIN_DEFAUWT);

	v4w2_ctww_cwustew(2, &imx335->exp_ctww);

	imx335->vbwank_ctww = v4w2_ctww_new_std(ctww_hdww,
						&imx335_ctww_ops,
						V4W2_CID_VBWANK,
						mode->vbwank_min,
						mode->vbwank_max,
						1, mode->vbwank);

	/* Wead onwy contwows */
	imx335->pcwk_ctww = v4w2_ctww_new_std(ctww_hdww,
					      &imx335_ctww_ops,
					      V4W2_CID_PIXEW_WATE,
					      mode->pcwk, mode->pcwk,
					      1, mode->pcwk);

	imx335->wink_fweq_ctww = v4w2_ctww_new_int_menu(ctww_hdww,
							&imx335_ctww_ops,
							V4W2_CID_WINK_FWEQ,
							AWWAY_SIZE(wink_fweq) -
							1,
							mode->wink_fweq_idx,
							wink_fweq);
	if (imx335->wink_fweq_ctww)
		imx335->wink_fweq_ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	imx335->hbwank_ctww = v4w2_ctww_new_std(ctww_hdww,
						&imx335_ctww_ops,
						V4W2_CID_HBWANK,
						mode->hbwank,
						mode->hbwank,
						1, mode->hbwank);
	if (imx335->hbwank_ctww)
		imx335->hbwank_ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	if (ctww_hdww->ewwow) {
		dev_eww(imx335->dev, "contwow init faiwed: %d\n",
			ctww_hdww->ewwow);
		v4w2_ctww_handwew_fwee(ctww_hdww);
		wetuwn ctww_hdww->ewwow;
	}

	imx335->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
}

/**
 * imx335_pwobe() - I2C cwient device binding
 * @cwient: pointew to i2c cwient device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx335_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct imx335 *imx335;
	int wet;

	imx335 = devm_kzawwoc(&cwient->dev, sizeof(*imx335), GFP_KEWNEW);
	if (!imx335)
		wetuwn -ENOMEM;

	imx335->dev = &cwient->dev;

	/* Initiawize subdev */
	v4w2_i2c_subdev_init(&imx335->sd, cwient, &imx335_subdev_ops);
	imx335->sd.intewnaw_ops = &imx335_intewnaw_ops;

	wet = imx335_pawse_hw_config(imx335);
	if (wet) {
		dev_eww(imx335->dev, "HW configuwation is not suppowted\n");
		wetuwn wet;
	}

	mutex_init(&imx335->mutex);

	wet = imx335_powew_on(imx335->dev);
	if (wet) {
		dev_eww(imx335->dev, "faiwed to powew-on the sensow\n");
		goto ewwow_mutex_destwoy;
	}

	/* Check moduwe identity */
	wet = imx335_detect(imx335);
	if (wet) {
		dev_eww(imx335->dev, "faiwed to find sensow: %d\n", wet);
		goto ewwow_powew_off;
	}

	/* Set defauwt mode to max wesowution */
	imx335->cuw_mode = &suppowted_mode;
	imx335->cuw_mbus_code = imx335_mbus_codes[0];
	imx335->vbwank = imx335->cuw_mode->vbwank;

	wet = imx335_init_contwows(imx335);
	if (wet) {
		dev_eww(imx335->dev, "faiwed to init contwows: %d\n", wet);
		goto ewwow_powew_off;
	}

	/* Initiawize subdev */
	imx335->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	imx335->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	/* Initiawize souwce pad */
	imx335->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&imx335->sd.entity, 1, &imx335->pad);
	if (wet) {
		dev_eww(imx335->dev, "faiwed to init entity pads: %d\n", wet);
		goto ewwow_handwew_fwee;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&imx335->sd);
	if (wet < 0) {
		dev_eww(imx335->dev,
			"faiwed to wegistew async subdev: %d\n", wet);
		goto ewwow_media_entity;
	}

	pm_wuntime_set_active(imx335->dev);
	pm_wuntime_enabwe(imx335->dev);
	pm_wuntime_idwe(imx335->dev);

	wetuwn 0;

ewwow_media_entity:
	media_entity_cweanup(&imx335->sd.entity);
ewwow_handwew_fwee:
	v4w2_ctww_handwew_fwee(imx335->sd.ctww_handwew);
ewwow_powew_off:
	imx335_powew_off(imx335->dev);
ewwow_mutex_destwoy:
	mutex_destwoy(&imx335->mutex);

	wetuwn wet;
}

/**
 * imx335_wemove() - I2C cwient device unbinding
 * @cwient: pointew to I2C cwient device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static void imx335_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx335 *imx335 = to_imx335(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		imx335_powew_off(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	mutex_destwoy(&imx335->mutex);
}

static const stwuct dev_pm_ops imx335_pm_ops = {
	SET_WUNTIME_PM_OPS(imx335_powew_off, imx335_powew_on, NUWW)
};

static const stwuct of_device_id imx335_of_match[] = {
	{ .compatibwe = "sony,imx335" },
	{ }
};

MODUWE_DEVICE_TABWE(of, imx335_of_match);

static stwuct i2c_dwivew imx335_dwivew = {
	.pwobe = imx335_pwobe,
	.wemove = imx335_wemove,
	.dwivew = {
		.name = "imx335",
		.pm = &imx335_pm_ops,
		.of_match_tabwe = imx335_of_match,
	},
};

moduwe_i2c_dwivew(imx335_dwivew);

MODUWE_DESCWIPTION("Sony imx335 sensow dwivew");
MODUWE_WICENSE("GPW");
