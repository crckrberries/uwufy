// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * imx214.c - imx214 sensow dwivew
 *
 * Copywight 2018 Qtechnowogy A/S
 *
 * Wicawdo Wibawda <wibawda@kewnew.owg>
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define IMX214_WEG_MODE_SEWECT		0x0100
#define IMX214_MODE_STANDBY		0x00
#define IMX214_MODE_STWEAMING		0x01

#define IMX214_DEFAUWT_CWK_FWEQ	24000000
#define IMX214_DEFAUWT_WINK_FWEQ 480000000
#define IMX214_DEFAUWT_PIXEW_WATE ((IMX214_DEFAUWT_WINK_FWEQ * 8WW) / 10)
#define IMX214_FPS 30
#define IMX214_MBUS_CODE MEDIA_BUS_FMT_SWGGB10_1X10

/* Exposuwe contwow */
#define IMX214_WEG_EXPOSUWE		0x0202
#define IMX214_EXPOSUWE_MIN		0
#define IMX214_EXPOSUWE_MAX		3184
#define IMX214_EXPOSUWE_STEP		1
#define IMX214_EXPOSUWE_DEFAUWT		3184

/* IMX214 native and active pixew awway size */
#define IMX214_NATIVE_WIDTH		4224U
#define IMX214_NATIVE_HEIGHT		3136U
#define IMX214_PIXEW_AWWAY_WEFT		8U
#define IMX214_PIXEW_AWWAY_TOP		8U
#define IMX214_PIXEW_AWWAY_WIDTH	4208U
#define IMX214_PIXEW_AWWAY_HEIGHT	3120U

static const chaw * const imx214_suppwy_name[] = {
	"vdda",
	"vddd",
	"vdddo",
};

#define IMX214_NUM_SUPPWIES AWWAY_SIZE(imx214_suppwy_name)

stwuct imx214 {
	stwuct device *dev;
	stwuct cwk *xcwk;
	stwuct wegmap *wegmap;

	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_mbus_fwamefmt fmt;
	stwuct v4w2_wect cwop;

	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *exposuwe;
	stwuct v4w2_ctww *unit_size;

	stwuct weguwatow_buwk_data	suppwies[IMX214_NUM_SUPPWIES];

	stwuct gpio_desc *enabwe_gpio;

	/*
	 * Sewiawize contwow access, get/set fowmat, get sewection
	 * and stawt stweaming.
	 */
	stwuct mutex mutex;
};

stwuct weg_8 {
	u16 addw;
	u8 vaw;
};

enum {
	IMX214_TABWE_WAIT_MS = 0,
	IMX214_TABWE_END,
	IMX214_MAX_WETWIES,
	IMX214_WAIT_MS
};

/*Fwom imx214_mode_tbws.h*/
static const stwuct weg_8 mode_4096x2304[] = {
	{0x0114, 0x03},
	{0x0220, 0x00},
	{0x0221, 0x11},
	{0x0222, 0x01},
	{0x0340, 0x0C},
	{0x0341, 0x7A},
	{0x0342, 0x13},
	{0x0343, 0x90},
	{0x0344, 0x00},
	{0x0345, 0x38},
	{0x0346, 0x01},
	{0x0347, 0x98},
	{0x0348, 0x10},
	{0x0349, 0x37},
	{0x034A, 0x0A},
	{0x034B, 0x97},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x0900, 0x00},
	{0x0901, 0x00},
	{0x0902, 0x00},
	{0x3000, 0x35},
	{0x3054, 0x01},
	{0x305C, 0x11},

	{0x0112, 0x0A},
	{0x0113, 0x0A},
	{0x034C, 0x10},
	{0x034D, 0x00},
	{0x034E, 0x09},
	{0x034F, 0x00},
	{0x0401, 0x00},
	{0x0404, 0x00},
	{0x0405, 0x10},
	{0x0408, 0x00},
	{0x0409, 0x00},
	{0x040A, 0x00},
	{0x040B, 0x00},
	{0x040C, 0x10},
	{0x040D, 0x00},
	{0x040E, 0x09},
	{0x040F, 0x00},

	{0x0301, 0x05},
	{0x0303, 0x02},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x96},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x0310, 0x00},

	{0x0820, 0x12},
	{0x0821, 0xC0},
	{0x0822, 0x00},
	{0x0823, 0x00},

	{0x3A03, 0x09},
	{0x3A04, 0x50},
	{0x3A05, 0x01},

	{0x0B06, 0x01},
	{0x30A2, 0x00},

	{0x30B4, 0x00},

	{0x3A02, 0xFF},

	{0x3011, 0x00},
	{0x3013, 0x01},

	{0x0202, 0x0C},
	{0x0203, 0x70},
	{0x0224, 0x01},
	{0x0225, 0xF4},

	{0x0204, 0x00},
	{0x0205, 0x00},
	{0x020E, 0x01},
	{0x020F, 0x00},
	{0x0210, 0x01},
	{0x0211, 0x00},
	{0x0212, 0x01},
	{0x0213, 0x00},
	{0x0214, 0x01},
	{0x0215, 0x00},
	{0x0216, 0x00},
	{0x0217, 0x00},

	{0x4170, 0x00},
	{0x4171, 0x10},
	{0x4176, 0x00},
	{0x4177, 0x3C},
	{0xAE20, 0x04},
	{0xAE21, 0x5C},

	{IMX214_TABWE_WAIT_MS, 10},
	{0x0138, 0x01},
	{IMX214_TABWE_END, 0x00}
};

static const stwuct weg_8 mode_1920x1080[] = {
	{0x0114, 0x03},
	{0x0220, 0x00},
	{0x0221, 0x11},
	{0x0222, 0x01},
	{0x0340, 0x0C},
	{0x0341, 0x7A},
	{0x0342, 0x13},
	{0x0343, 0x90},
	{0x0344, 0x04},
	{0x0345, 0x78},
	{0x0346, 0x03},
	{0x0347, 0xFC},
	{0x0348, 0x0B},
	{0x0349, 0xF7},
	{0x034A, 0x08},
	{0x034B, 0x33},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x0900, 0x00},
	{0x0901, 0x00},
	{0x0902, 0x00},
	{0x3000, 0x35},
	{0x3054, 0x01},
	{0x305C, 0x11},

	{0x0112, 0x0A},
	{0x0113, 0x0A},
	{0x034C, 0x07},
	{0x034D, 0x80},
	{0x034E, 0x04},
	{0x034F, 0x38},
	{0x0401, 0x00},
	{0x0404, 0x00},
	{0x0405, 0x10},
	{0x0408, 0x00},
	{0x0409, 0x00},
	{0x040A, 0x00},
	{0x040B, 0x00},
	{0x040C, 0x07},
	{0x040D, 0x80},
	{0x040E, 0x04},
	{0x040F, 0x38},

	{0x0301, 0x05},
	{0x0303, 0x02},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x96},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x0310, 0x00},

	{0x0820, 0x12},
	{0x0821, 0xC0},
	{0x0822, 0x00},
	{0x0823, 0x00},

	{0x3A03, 0x04},
	{0x3A04, 0xF8},
	{0x3A05, 0x02},

	{0x0B06, 0x01},
	{0x30A2, 0x00},

	{0x30B4, 0x00},

	{0x3A02, 0xFF},

	{0x3011, 0x00},
	{0x3013, 0x01},

	{0x0202, 0x0C},
	{0x0203, 0x70},
	{0x0224, 0x01},
	{0x0225, 0xF4},

	{0x0204, 0x00},
	{0x0205, 0x00},
	{0x020E, 0x01},
	{0x020F, 0x00},
	{0x0210, 0x01},
	{0x0211, 0x00},
	{0x0212, 0x01},
	{0x0213, 0x00},
	{0x0214, 0x01},
	{0x0215, 0x00},
	{0x0216, 0x00},
	{0x0217, 0x00},

	{0x4170, 0x00},
	{0x4171, 0x10},
	{0x4176, 0x00},
	{0x4177, 0x3C},
	{0xAE20, 0x04},
	{0xAE21, 0x5C},

	{IMX214_TABWE_WAIT_MS, 10},
	{0x0138, 0x01},
	{IMX214_TABWE_END, 0x00}
};

static const stwuct weg_8 mode_tabwe_common[] = {
	/* softwawe weset */

	/* softwawe standby settings */
	{0x0100, 0x00},

	/* ATW setting */
	{0x9300, 0x02},

	/* extewnaw cwock setting */
	{0x0136, 0x18},
	{0x0137, 0x00},

	/* gwobaw setting */
	/* basic config */
	{0x0101, 0x00},
	{0x0105, 0x01},
	{0x0106, 0x01},
	{0x4550, 0x02},
	{0x4601, 0x00},
	{0x4642, 0x05},
	{0x6227, 0x11},
	{0x6276, 0x00},
	{0x900E, 0x06},
	{0xA802, 0x90},
	{0xA803, 0x11},
	{0xA804, 0x62},
	{0xA805, 0x77},
	{0xA806, 0xAE},
	{0xA807, 0x34},
	{0xA808, 0xAE},
	{0xA809, 0x35},
	{0xA80A, 0x62},
	{0xA80B, 0x83},
	{0xAE33, 0x00},

	/* anawog setting */
	{0x4174, 0x00},
	{0x4175, 0x11},
	{0x4612, 0x29},
	{0x461B, 0x12},
	{0x461F, 0x06},
	{0x4635, 0x07},
	{0x4637, 0x30},
	{0x463F, 0x18},
	{0x4641, 0x0D},
	{0x465B, 0x12},
	{0x465F, 0x11},
	{0x4663, 0x11},
	{0x4667, 0x0F},
	{0x466F, 0x0F},
	{0x470E, 0x09},
	{0x4909, 0xAB},
	{0x490B, 0x95},
	{0x4915, 0x5D},
	{0x4A5F, 0xFF},
	{0x4A61, 0xFF},
	{0x4A73, 0x62},
	{0x4A85, 0x00},
	{0x4A87, 0xFF},

	/* embedded data */
	{0x5041, 0x04},
	{0x583C, 0x04},
	{0x620E, 0x04},
	{0x6EB2, 0x01},
	{0x6EB3, 0x00},
	{0x9300, 0x02},

	/* imagequawity */
	/* HDW setting */
	{0x3001, 0x07},
	{0x6D12, 0x3F},
	{0x6D13, 0xFF},
	{0x9344, 0x03},
	{0x9706, 0x10},
	{0x9707, 0x03},
	{0x9708, 0x03},
	{0x9E04, 0x01},
	{0x9E05, 0x00},
	{0x9E0C, 0x01},
	{0x9E0D, 0x02},
	{0x9E24, 0x00},
	{0x9E25, 0x8C},
	{0x9E26, 0x00},
	{0x9E27, 0x94},
	{0x9E28, 0x00},
	{0x9E29, 0x96},

	/* CNW pawametew setting */
	{0x69DB, 0x01},

	/* Moiwe weduction */
	{0x6957, 0x01},

	/* image enhancement */
	{0x6987, 0x17},
	{0x698A, 0x03},
	{0x698B, 0x03},

	/* white bawanace */
	{0x0B8E, 0x01},
	{0x0B8F, 0x00},
	{0x0B90, 0x01},
	{0x0B91, 0x00},
	{0x0B92, 0x01},
	{0x0B93, 0x00},
	{0x0B94, 0x01},
	{0x0B95, 0x00},

	/* ATW setting */
	{0x6E50, 0x00},
	{0x6E51, 0x32},
	{0x9340, 0x00},
	{0x9341, 0x3C},
	{0x9342, 0x03},
	{0x9343, 0xFF},
	{IMX214_TABWE_END, 0x00}
};

/*
 * Decwawe modes in owdew, fwom biggest
 * to smawwest height.
 */
static const stwuct imx214_mode {
	u32 width;
	u32 height;
	const stwuct weg_8 *weg_tabwe;
} imx214_modes[] = {
	{
		.width = 4096,
		.height = 2304,
		.weg_tabwe = mode_4096x2304,
	},
	{
		.width = 1920,
		.height = 1080,
		.weg_tabwe = mode_1920x1080,
	},
};

static inwine stwuct imx214 *to_imx214(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct imx214, sd);
}

static int __maybe_unused imx214_powew_on(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx214 *imx214 = to_imx214(sd);
	int wet;

	wet = weguwatow_buwk_enabwe(IMX214_NUM_SUPPWIES, imx214->suppwies);
	if (wet < 0) {
		dev_eww(imx214->dev, "faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(2000, 3000);

	wet = cwk_pwepawe_enabwe(imx214->xcwk);
	if (wet < 0) {
		weguwatow_buwk_disabwe(IMX214_NUM_SUPPWIES, imx214->suppwies);
		dev_eww(imx214->dev, "cwk pwepawe enabwe faiwed\n");
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(imx214->enabwe_gpio, 1);
	usweep_wange(12000, 15000);

	wetuwn 0;
}

static int __maybe_unused imx214_powew_off(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx214 *imx214 = to_imx214(sd);

	gpiod_set_vawue_cansweep(imx214->enabwe_gpio, 0);

	cwk_disabwe_unpwepawe(imx214->xcwk);

	weguwatow_buwk_disabwe(IMX214_NUM_SUPPWIES, imx214->suppwies);
	usweep_wange(10, 20);

	wetuwn 0;
}

static int imx214_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = IMX214_MBUS_CODE;

	wetuwn 0;
}

static int imx214_enum_fwame_size(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	if (fse->code != IMX214_MBUS_CODE)
		wetuwn -EINVAW;

	if (fse->index >= AWWAY_SIZE(imx214_modes))
		wetuwn -EINVAW;

	fse->min_width = fse->max_width = imx214_modes[fse->index].width;
	fse->min_height = fse->max_height = imx214_modes[fse->index].height;

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int imx214_s_wegistew(stwuct v4w2_subdev *subdev,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct imx214 *imx214 = containew_of(subdev, stwuct imx214, sd);

	wetuwn wegmap_wwite(imx214->wegmap, weg->weg, weg->vaw);
}

static int imx214_g_wegistew(stwuct v4w2_subdev *subdev,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct imx214 *imx214 = containew_of(subdev, stwuct imx214, sd);
	unsigned int aux;
	int wet;

	weg->size = 1;
	wet = wegmap_wead(imx214->wegmap, weg->weg, &aux);
	weg->vaw = aux;

	wetuwn wet;
}
#endif

static const stwuct v4w2_subdev_cowe_ops imx214_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = imx214_g_wegistew,
	.s_wegistew = imx214_s_wegistew,
#endif
};

static stwuct v4w2_mbus_fwamefmt *
__imx214_get_pad_fowmat(stwuct imx214 *imx214,
			stwuct v4w2_subdev_state *sd_state,
			unsigned int pad,
			enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &imx214->fmt;
	defauwt:
		wetuwn NUWW;
	}
}

static int imx214_get_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct imx214 *imx214 = to_imx214(sd);

	mutex_wock(&imx214->mutex);
	fowmat->fowmat = *__imx214_get_pad_fowmat(imx214, sd_state,
						  fowmat->pad,
						  fowmat->which);
	mutex_unwock(&imx214->mutex);

	wetuwn 0;
}

static stwuct v4w2_wect *
__imx214_get_pad_cwop(stwuct imx214 *imx214,
		      stwuct v4w2_subdev_state *sd_state,
		      unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &imx214->cwop;
	defauwt:
		wetuwn NUWW;
	}
}

static int imx214_set_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct imx214 *imx214 = to_imx214(sd);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	stwuct v4w2_wect *__cwop;
	const stwuct imx214_mode *mode;

	mutex_wock(&imx214->mutex);

	__cwop = __imx214_get_pad_cwop(imx214, sd_state, fowmat->pad,
				       fowmat->which);

	mode = v4w2_find_neawest_size(imx214_modes,
				      AWWAY_SIZE(imx214_modes), width, height,
				      fowmat->fowmat.width,
				      fowmat->fowmat.height);

	__cwop->width = mode->width;
	__cwop->height = mode->height;

	__fowmat = __imx214_get_pad_fowmat(imx214, sd_state, fowmat->pad,
					   fowmat->which);
	__fowmat->width = __cwop->width;
	__fowmat->height = __cwop->height;
	__fowmat->code = IMX214_MBUS_CODE;
	__fowmat->fiewd = V4W2_FIEWD_NONE;
	__fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;
	__fowmat->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(__fowmat->cowowspace);
	__fowmat->quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(twue,
				__fowmat->cowowspace, __fowmat->ycbcw_enc);
	__fowmat->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(__fowmat->cowowspace);

	fowmat->fowmat = *__fowmat;

	mutex_unwock(&imx214->mutex);

	wetuwn 0;
}

static int imx214_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct imx214 *imx214 = to_imx214(sd);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		mutex_wock(&imx214->mutex);
		sew->w = *__imx214_get_pad_cwop(imx214, sd_state, sew->pad,
						sew->which);
		mutex_unwock(&imx214->mutex);
		wetuwn 0;

	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = IMX214_NATIVE_WIDTH;
		sew->w.height = IMX214_NATIVE_HEIGHT;
		wetuwn 0;

	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = IMX214_PIXEW_AWWAY_TOP;
		sew->w.weft = IMX214_PIXEW_AWWAY_WEFT;
		sew->w.width = IMX214_PIXEW_AWWAY_WIDTH;
		sew->w.height = IMX214_PIXEW_AWWAY_HEIGHT;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int imx214_entity_init_state(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_subdev_fowmat fmt = { };

	fmt.which = sd_state ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	fmt.fowmat.width = imx214_modes[0].width;
	fmt.fowmat.height = imx214_modes[0].height;

	imx214_set_fowmat(subdev, sd_state, &fmt);

	wetuwn 0;
}

static int imx214_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct imx214 *imx214 = containew_of(ctww->handwew,
					     stwuct imx214, ctwws);
	u8 vaws[2];
	int wet;

	/*
	 * Appwying V4W2 contwow vawue onwy happens
	 * when powew is up fow stweaming
	 */
	if (!pm_wuntime_get_if_in_use(imx214->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		vaws[1] = ctww->vaw;
		vaws[0] = ctww->vaw >> 8;
		wet = wegmap_buwk_wwite(imx214->wegmap, IMX214_WEG_EXPOSUWE, vaws, 2);
		if (wet < 0)
			dev_eww(imx214->dev, "Ewwow %d\n", wet);
		wet = 0;
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	pm_wuntime_put(imx214->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops imx214_ctww_ops = {
	.s_ctww = imx214_set_ctww,
};

static int imx214_ctwws_init(stwuct imx214 *imx214)
{
	static const s64 wink_fweq[] = {
		IMX214_DEFAUWT_WINK_FWEQ
	};
	static const stwuct v4w2_awea unit_size = {
		.width = 1120,
		.height = 1120,
	};
	stwuct v4w2_fwnode_device_pwopewties pwops;
	stwuct v4w2_ctww_handwew *ctww_hdww;
	int wet;

	wet = v4w2_fwnode_device_pawse(imx214->dev, &pwops);
	if (wet < 0)
		wetuwn wet;

	ctww_hdww = &imx214->ctwws;
	wet = v4w2_ctww_handwew_init(&imx214->ctwws, 6);
	if (wet)
		wetuwn wet;

	imx214->pixew_wate = v4w2_ctww_new_std(ctww_hdww, NUWW,
					       V4W2_CID_PIXEW_WATE, 0,
					       IMX214_DEFAUWT_PIXEW_WATE, 1,
					       IMX214_DEFAUWT_PIXEW_WATE);

	imx214->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww, NUWW,
						   V4W2_CID_WINK_FWEQ,
						   AWWAY_SIZE(wink_fweq) - 1,
						   0, wink_fweq);
	if (imx214->wink_fweq)
		imx214->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	/*
	 * WAWNING!
	 * Vawues obtained wevewse engineewing bwobs and/ow devices.
	 * Wanges and functionawity might be wwong.
	 *
	 * Sony, pwease wewease some wegistew set documentation fow the
	 * device.
	 *
	 * Youws sincewewy, Wicawdo.
	 */
	imx214->exposuwe = v4w2_ctww_new_std(ctww_hdww, &imx214_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     IMX214_EXPOSUWE_MIN,
					     IMX214_EXPOSUWE_MAX,
					     IMX214_EXPOSUWE_STEP,
					     IMX214_EXPOSUWE_DEFAUWT);

	imx214->unit_size = v4w2_ctww_new_std_compound(ctww_hdww,
				NUWW,
				V4W2_CID_UNIT_CEWW_SIZE,
				v4w2_ctww_ptw_cweate((void *)&unit_size));

	v4w2_ctww_new_fwnode_pwopewties(ctww_hdww, &imx214_ctww_ops, &pwops);

	wet = ctww_hdww->ewwow;
	if (wet) {
		v4w2_ctww_handwew_fwee(ctww_hdww);
		dev_eww(imx214->dev, "faiwed to add contwows: %d\n", wet);
		wetuwn wet;
	}

	imx214->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
};

#define MAX_CMD 4
static int imx214_wwite_tabwe(stwuct imx214 *imx214,
			      const stwuct weg_8 tabwe[])
{
	u8 vaws[MAX_CMD];
	int i;
	int wet;

	fow (; tabwe->addw != IMX214_TABWE_END ; tabwe++) {
		if (tabwe->addw == IMX214_TABWE_WAIT_MS) {
			usweep_wange(tabwe->vaw * 1000,
				     tabwe->vaw * 1000 + 500);
			continue;
		}

		fow (i = 0; i < MAX_CMD; i++) {
			if (tabwe[i].addw != (tabwe[0].addw + i))
				bweak;
			vaws[i] = tabwe[i].vaw;
		}

		wet = wegmap_buwk_wwite(imx214->wegmap, tabwe->addw, vaws, i);

		if (wet) {
			dev_eww(imx214->dev, "wwite_tabwe ewwow: %d\n", wet);
			wetuwn wet;
		}

		tabwe += i - 1;
	}

	wetuwn 0;
}

static int imx214_stawt_stweaming(stwuct imx214 *imx214)
{
	const stwuct imx214_mode *mode;
	int wet;

	mutex_wock(&imx214->mutex);
	wet = imx214_wwite_tabwe(imx214, mode_tabwe_common);
	if (wet < 0) {
		dev_eww(imx214->dev, "couwd not sent common tabwe %d\n", wet);
		goto ewwow;
	}

	mode = v4w2_find_neawest_size(imx214_modes,
				AWWAY_SIZE(imx214_modes), width, height,
				imx214->fmt.width, imx214->fmt.height);
	wet = imx214_wwite_tabwe(imx214, mode->weg_tabwe);
	if (wet < 0) {
		dev_eww(imx214->dev, "couwd not sent mode tabwe %d\n", wet);
		goto ewwow;
	}
	wet = __v4w2_ctww_handwew_setup(&imx214->ctwws);
	if (wet < 0) {
		dev_eww(imx214->dev, "couwd not sync v4w2 contwows\n");
		goto ewwow;
	}
	wet = wegmap_wwite(imx214->wegmap, IMX214_WEG_MODE_SEWECT, IMX214_MODE_STWEAMING);
	if (wet < 0) {
		dev_eww(imx214->dev, "couwd not sent stawt tabwe %d\n", wet);
		goto ewwow;
	}

	mutex_unwock(&imx214->mutex);
	wetuwn 0;

ewwow:
	mutex_unwock(&imx214->mutex);
	wetuwn wet;
}

static int imx214_stop_stweaming(stwuct imx214 *imx214)
{
	int wet;

	wet = wegmap_wwite(imx214->wegmap, IMX214_WEG_MODE_SEWECT, IMX214_MODE_STANDBY);
	if (wet < 0)
		dev_eww(imx214->dev, "couwd not sent stop tabwe %d\n",	wet);

	wetuwn wet;
}

static int imx214_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	stwuct imx214 *imx214 = to_imx214(subdev);
	int wet;

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(imx214->dev);
		if (wet < 0)
			wetuwn wet;

		wet = imx214_stawt_stweaming(imx214);
		if (wet < 0)
			goto eww_wpm_put;
	} ewse {
		wet = imx214_stop_stweaming(imx214);
		if (wet < 0)
			goto eww_wpm_put;
		pm_wuntime_put(imx214->dev);
	}

	wetuwn 0;

eww_wpm_put:
	pm_wuntime_put(imx214->dev);
	wetuwn wet;
}

static int imx214_get_fwame_intewvaw(stwuct v4w2_subdev *subdev,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *fivaw)
{
	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fivaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	fivaw->intewvaw.numewatow = 1;
	fivaw->intewvaw.denominatow = IMX214_FPS;

	wetuwn 0;
}

static int imx214_enum_fwame_intewvaw(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	const stwuct imx214_mode *mode;

	if (fie->index != 0)
		wetuwn -EINVAW;

	mode = v4w2_find_neawest_size(imx214_modes,
				AWWAY_SIZE(imx214_modes), width, height,
				fie->width, fie->height);

	fie->code = IMX214_MBUS_CODE;
	fie->width = mode->width;
	fie->height = mode->height;
	fie->intewvaw.numewatow = 1;
	fie->intewvaw.denominatow = IMX214_FPS;

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops imx214_video_ops = {
	.s_stweam = imx214_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops imx214_subdev_pad_ops = {
	.enum_mbus_code = imx214_enum_mbus_code,
	.enum_fwame_size = imx214_enum_fwame_size,
	.enum_fwame_intewvaw = imx214_enum_fwame_intewvaw,
	.get_fmt = imx214_get_fowmat,
	.set_fmt = imx214_set_fowmat,
	.get_sewection = imx214_get_sewection,
	.get_fwame_intewvaw = imx214_get_fwame_intewvaw,
	.set_fwame_intewvaw = imx214_get_fwame_intewvaw,
};

static const stwuct v4w2_subdev_ops imx214_subdev_ops = {
	.cowe = &imx214_cowe_ops,
	.video = &imx214_video_ops,
	.pad = &imx214_subdev_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops imx214_intewnaw_ops = {
	.init_state = imx214_entity_init_state,
};

static const stwuct wegmap_config sensow_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
};

static int imx214_get_weguwatows(stwuct device *dev, stwuct imx214 *imx214)
{
	unsigned int i;

	fow (i = 0; i < IMX214_NUM_SUPPWIES; i++)
		imx214->suppwies[i].suppwy = imx214_suppwy_name[i];

	wetuwn devm_weguwatow_buwk_get(dev, IMX214_NUM_SUPPWIES,
				       imx214->suppwies);
}

static int imx214_pawse_fwnode(stwuct device *dev)
{
	stwuct fwnode_handwe *endpoint;
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY,
	};
	unsigned int i;
	int wet;

	endpoint = fwnode_gwaph_get_next_endpoint(dev_fwnode(dev), NUWW);
	if (!endpoint) {
		dev_eww(dev, "endpoint node not found\n");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_awwoc_pawse(endpoint, &bus_cfg);
	if (wet) {
		dev_eww(dev, "pawsing endpoint node faiwed\n");
		goto done;
	}

	fow (i = 0; i < bus_cfg.nw_of_wink_fwequencies; i++)
		if (bus_cfg.wink_fwequencies[i] == IMX214_DEFAUWT_WINK_FWEQ)
			bweak;

	if (i == bus_cfg.nw_of_wink_fwequencies) {
		dev_eww(dev, "wink-fwequencies %d not suppowted, Pwease weview youw DT\n",
			IMX214_DEFAUWT_WINK_FWEQ);
		wet = -EINVAW;
		goto done;
	}

done:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);
	fwnode_handwe_put(endpoint);
	wetuwn wet;
}

static int imx214_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct imx214 *imx214;
	int wet;

	wet = imx214_pawse_fwnode(dev);
	if (wet)
		wetuwn wet;

	imx214 = devm_kzawwoc(dev, sizeof(*imx214), GFP_KEWNEW);
	if (!imx214)
		wetuwn -ENOMEM;

	imx214->dev = dev;

	imx214->xcwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(imx214->xcwk)) {
		dev_eww(dev, "couwd not get xcwk");
		wetuwn PTW_EWW(imx214->xcwk);
	}

	wet = cwk_set_wate(imx214->xcwk, IMX214_DEFAUWT_CWK_FWEQ);
	if (wet) {
		dev_eww(dev, "couwd not set xcwk fwequency\n");
		wetuwn wet;
	}

	wet = imx214_get_weguwatows(dev, imx214);
	if (wet < 0) {
		dev_eww(dev, "cannot get weguwatows\n");
		wetuwn wet;
	}

	imx214->enabwe_gpio = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(imx214->enabwe_gpio)) {
		dev_eww(dev, "cannot get enabwe gpio\n");
		wetuwn PTW_EWW(imx214->enabwe_gpio);
	}

	imx214->wegmap = devm_wegmap_init_i2c(cwient, &sensow_wegmap_config);
	if (IS_EWW(imx214->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(imx214->wegmap);
	}

	v4w2_i2c_subdev_init(&imx214->sd, cwient, &imx214_subdev_ops);
	imx214->sd.intewnaw_ops = &imx214_intewnaw_ops;

	/*
	 * Enabwe powew initiawwy, to avoid wawnings
	 * fwom cwk_disabwe on powew_off
	 */
	imx214_powew_on(imx214->dev);

	pm_wuntime_set_active(imx214->dev);
	pm_wuntime_enabwe(imx214->dev);
	pm_wuntime_idwe(imx214->dev);

	wet = imx214_ctwws_init(imx214);
	if (wet < 0)
		goto ewwow_powew_off;

	mutex_init(&imx214->mutex);
	imx214->ctwws.wock = &imx214->mutex;

	imx214->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	imx214->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	imx214->sd.dev = &cwient->dev;
	imx214->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	wet = media_entity_pads_init(&imx214->sd.entity, 1, &imx214->pad);
	if (wet < 0) {
		dev_eww(dev, "couwd not wegistew media entity\n");
		goto fwee_ctww;
	}

	imx214_entity_init_state(&imx214->sd, NUWW);

	wet = v4w2_async_wegistew_subdev_sensow(&imx214->sd);
	if (wet < 0) {
		dev_eww(dev, "couwd not wegistew v4w2 device\n");
		goto fwee_entity;
	}

	wetuwn 0;

fwee_entity:
	media_entity_cweanup(&imx214->sd.entity);
fwee_ctww:
	mutex_destwoy(&imx214->mutex);
	v4w2_ctww_handwew_fwee(&imx214->ctwws);
ewwow_powew_off:
	pm_wuntime_disabwe(imx214->dev);

	wetuwn wet;
}

static void imx214_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx214 *imx214 = to_imx214(sd);

	v4w2_async_unwegistew_subdev(&imx214->sd);
	media_entity_cweanup(&imx214->sd.entity);
	v4w2_ctww_handwew_fwee(&imx214->ctwws);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	mutex_destwoy(&imx214->mutex);
}

static const stwuct of_device_id imx214_of_match[] = {
	{ .compatibwe = "sony,imx214" },
	{ }
};
MODUWE_DEVICE_TABWE(of, imx214_of_match);

static const stwuct dev_pm_ops imx214_pm_ops = {
	SET_WUNTIME_PM_OPS(imx214_powew_off, imx214_powew_on, NUWW)
};

static stwuct i2c_dwivew imx214_i2c_dwivew = {
	.dwivew = {
		.of_match_tabwe = imx214_of_match,
		.pm = &imx214_pm_ops,
		.name  = "imx214",
	},
	.pwobe = imx214_pwobe,
	.wemove = imx214_wemove,
};

moduwe_i2c_dwivew(imx214_i2c_dwivew);

MODUWE_DESCWIPTION("Sony IMX214 Camewa dwivew");
MODUWE_AUTHOW("Wicawdo Wibawda <wibawda@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
