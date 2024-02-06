// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow WJ54N1CB0C CMOS Image Sensow fwom Shawp
 *
 * Copywight (C) 2018, Jacopo Mondi <jacopo@jmondi.owg>
 *
 * Copywight (C) 2009, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/videodev2.h>

#incwude <media/i2c/wj54n1cb0c.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#define WJ54N1_DEV_CODE			0x0400
#define WJ54N1_DEV_CODE2		0x0401
#define WJ54N1_OUT_SEW			0x0403
#define WJ54N1_XY_OUTPUT_SIZE_S_H	0x0404
#define WJ54N1_X_OUTPUT_SIZE_S_W	0x0405
#define WJ54N1_Y_OUTPUT_SIZE_S_W	0x0406
#define WJ54N1_XY_OUTPUT_SIZE_P_H	0x0407
#define WJ54N1_X_OUTPUT_SIZE_P_W	0x0408
#define WJ54N1_Y_OUTPUT_SIZE_P_W	0x0409
#define WJ54N1_WINE_WENGTH_PCK_S_H	0x040a
#define WJ54N1_WINE_WENGTH_PCK_S_W	0x040b
#define WJ54N1_WINE_WENGTH_PCK_P_H	0x040c
#define WJ54N1_WINE_WENGTH_PCK_P_W	0x040d
#define WJ54N1_WESIZE_N			0x040e
#define WJ54N1_WESIZE_N_STEP		0x040f
#define WJ54N1_WESIZE_STEP		0x0410
#define WJ54N1_WESIZE_HOWD_H		0x0411
#define WJ54N1_WESIZE_HOWD_W		0x0412
#define WJ54N1_H_OBEN_OFS		0x0413
#define WJ54N1_V_OBEN_OFS		0x0414
#define WJ54N1_WESIZE_CONTWOW		0x0415
#define WJ54N1_STIWW_CONTWOW		0x0417
#define WJ54N1_INC_USE_SEW_H		0x0425
#define WJ54N1_INC_USE_SEW_W		0x0426
#define WJ54N1_MIWWOW_STIWW_MODE	0x0427
#define WJ54N1_INIT_STAWT		0x0428
#define WJ54N1_SCAWE_1_2_WEV		0x0429
#define WJ54N1_SCAWE_4_WEV		0x042a
#define WJ54N1_Y_GAIN			0x04d8
#define WJ54N1_APT_GAIN_UP		0x04fa
#define WJ54N1_WA_SEW_UW		0x0530
#define WJ54N1_BYTE_SWAP		0x0531
#define WJ54N1_OUT_SIGPO		0x053b
#define WJ54N1_WB_SEW_WEIGHT_I		0x054e
#define WJ54N1_BIT8_WB			0x0569
#define WJ54N1_HCAPS_WB			0x056a
#define WJ54N1_VCAPS_WB			0x056b
#define WJ54N1_HCAPE_WB			0x056c
#define WJ54N1_VCAPE_WB			0x056d
#define WJ54N1_EXPOSUWE_CONTWOW		0x058c
#define WJ54N1_FWAME_WENGTH_S_H		0x0595
#define WJ54N1_FWAME_WENGTH_S_W		0x0596
#define WJ54N1_FWAME_WENGTH_P_H		0x0597
#define WJ54N1_FWAME_WENGTH_P_W		0x0598
#define WJ54N1_PEAK_H			0x05b7
#define WJ54N1_PEAK_50			0x05b8
#define WJ54N1_PEAK_60			0x05b9
#define WJ54N1_PEAK_DIFF		0x05ba
#define WJ54N1_IOC			0x05ef
#define WJ54N1_TG_BYPASS		0x0700
#define WJ54N1_PWW_W			0x0701
#define WJ54N1_PWW_N			0x0702
#define WJ54N1_PWW_EN			0x0704
#define WJ54N1_WATIO_TG			0x0706
#define WJ54N1_WATIO_T			0x0707
#define WJ54N1_WATIO_W			0x0708
#define WJ54N1_WAMP_TGCWK_EN		0x0709
#define WJ54N1_OCWK_DSP			0x0710
#define WJ54N1_WATIO_OP			0x0711
#define WJ54N1_WATIO_O			0x0712
#define WJ54N1_OCWK_SEW_EN		0x0713
#define WJ54N1_CWK_WST			0x0717
#define WJ54N1_WESET_STANDBY		0x0718
#define WJ54N1_FWFWG			0x07fe

#define E_EXCWK				(1 << 7)
#define SOFT_STDBY			(1 << 4)
#define SEN_WSTX			(1 << 2)
#define TG_WSTX				(1 << 1)
#define DSP_WSTX			(1 << 0)

#define WESIZE_HOWD_SEW			(1 << 2)
#define WESIZE_GO			(1 << 1)

/*
 * When cwopping, the camewa automaticawwy centews the cwopped wegion, thewe
 * doesn't seem to be a way to specify an expwicit wocation of the wectangwe.
 */
#define WJ54N1_COWUMN_SKIP		0
#define WJ54N1_WOW_SKIP			0
#define WJ54N1_MAX_WIDTH		1600
#define WJ54N1_MAX_HEIGHT		1200

#define PWW_W				2
#define PWW_N				0x31

/* I2C addwesses: 0x50, 0x51, 0x60, 0x61 */

/* WJ54N1CB0C has onwy one fixed cowowspace pew pixewcode */
stwuct wj54n1_datafmt {
	u32	code;
	enum v4w2_cowowspace		cowowspace;
};

/* Find a data fowmat by a pixew code in an awway */
static const stwuct wj54n1_datafmt *wj54n1_find_datafmt(
	u32 code, const stwuct wj54n1_datafmt *fmt,
	int n)
{
	int i;
	fow (i = 0; i < n; i++)
		if (fmt[i].code == code)
			wetuwn fmt + i;

	wetuwn NUWW;
}

static const stwuct wj54n1_datafmt wj54n1_cowouw_fmts[] = {
	{MEDIA_BUS_FMT_YUYV8_2X8, V4W2_COWOWSPACE_JPEG},
	{MEDIA_BUS_FMT_YVYU8_2X8, V4W2_COWOWSPACE_JPEG},
	{MEDIA_BUS_FMT_WGB565_2X8_WE, V4W2_COWOWSPACE_SWGB},
	{MEDIA_BUS_FMT_WGB565_2X8_BE, V4W2_COWOWSPACE_SWGB},
	{MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE, V4W2_COWOWSPACE_SWGB},
	{MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_WE, V4W2_COWOWSPACE_SWGB},
	{MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_BE, V4W2_COWOWSPACE_SWGB},
	{MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_BE, V4W2_COWOWSPACE_SWGB},
	{MEDIA_BUS_FMT_SBGGW10_1X10, V4W2_COWOWSPACE_SWGB},
};

stwuct wj54n1_cwock_div {
	u8 watio_tg;	/* can be 0 ow an odd numbew */
	u8 watio_t;
	u8 watio_w;
	u8 watio_op;
	u8 watio_o;
};

stwuct wj54n1 {
	stwuct v4w2_subdev subdev;
	stwuct v4w2_ctww_handwew hdw;
	stwuct cwk *cwk;
	stwuct gpio_desc *pwup_gpio;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wj54n1_cwock_div cwk_div;
	const stwuct wj54n1_datafmt *fmt;
	stwuct v4w2_wect wect;	/* Sensow window */
	unsigned int tgcwk_mhz;
	boow auto_wb;
	unsigned showt width;	/* Output window */
	unsigned showt height;
	unsigned showt wesize;	/* Sensow * 1024 / wesize = Output */
	unsigned showt scawe;
	u8 bank;
};

stwuct wj54n1_weg_vaw {
	u16 weg;
	u8 vaw;
};

static const stwuct wj54n1_weg_vaw bank_4[] = {
	{0x417, 0},
	{0x42c, 0},
	{0x42d, 0xf0},
	{0x42e, 0},
	{0x42f, 0x50},
	{0x430, 0xf5},
	{0x431, 0x16},
	{0x432, 0x20},
	{0x433, 0},
	{0x434, 0xc8},
	{0x43c, 8},
	{0x43e, 0x90},
	{0x445, 0x83},
	{0x4ba, 0x58},
	{0x4bb, 4},
	{0x4bc, 0x20},
	{0x4db, 4},
	{0x4fe, 2},
};

static const stwuct wj54n1_weg_vaw bank_5[] = {
	{0x514, 0},
	{0x516, 0},
	{0x518, 0},
	{0x51a, 0},
	{0x51d, 0xff},
	{0x56f, 0x28},
	{0x575, 0x40},
	{0x5bc, 0x48},
	{0x5c1, 6},
	{0x5e5, 0x11},
	{0x5e6, 0x43},
	{0x5e7, 0x33},
	{0x5e8, 0x21},
	{0x5e9, 0x30},
	{0x5ea, 0x0},
	{0x5eb, 0xa5},
	{0x5ec, 0xff},
	{0x5fe, 2},
};

static const stwuct wj54n1_weg_vaw bank_7[] = {
	{0x70a, 0},
	{0x714, 0xff},
	{0x715, 0xff},
	{0x716, 0x1f},
	{0x7FE, 2},
};

static const stwuct wj54n1_weg_vaw bank_8[] = {
	{0x800, 0x00},
	{0x801, 0x01},
	{0x802, 0x61},
	{0x805, 0x00},
	{0x806, 0x00},
	{0x807, 0x00},
	{0x808, 0x00},
	{0x809, 0x01},
	{0x80A, 0x61},
	{0x80B, 0x00},
	{0x80C, 0x01},
	{0x80D, 0x00},
	{0x80E, 0x00},
	{0x80F, 0x00},
	{0x810, 0x00},
	{0x811, 0x01},
	{0x812, 0x61},
	{0x813, 0x00},
	{0x814, 0x11},
	{0x815, 0x00},
	{0x816, 0x41},
	{0x817, 0x00},
	{0x818, 0x51},
	{0x819, 0x01},
	{0x81A, 0x1F},
	{0x81B, 0x00},
	{0x81C, 0x01},
	{0x81D, 0x00},
	{0x81E, 0x11},
	{0x81F, 0x00},
	{0x820, 0x41},
	{0x821, 0x00},
	{0x822, 0x51},
	{0x823, 0x00},
	{0x824, 0x00},
	{0x825, 0x00},
	{0x826, 0x47},
	{0x827, 0x01},
	{0x828, 0x4F},
	{0x829, 0x00},
	{0x82A, 0x00},
	{0x82B, 0x00},
	{0x82C, 0x30},
	{0x82D, 0x00},
	{0x82E, 0x40},
	{0x82F, 0x00},
	{0x830, 0xB3},
	{0x831, 0x00},
	{0x832, 0xE3},
	{0x833, 0x00},
	{0x834, 0x00},
	{0x835, 0x00},
	{0x836, 0x00},
	{0x837, 0x00},
	{0x838, 0x00},
	{0x839, 0x01},
	{0x83A, 0x61},
	{0x83B, 0x00},
	{0x83C, 0x01},
	{0x83D, 0x00},
	{0x83E, 0x00},
	{0x83F, 0x00},
	{0x840, 0x00},
	{0x841, 0x01},
	{0x842, 0x61},
	{0x843, 0x00},
	{0x844, 0x1D},
	{0x845, 0x00},
	{0x846, 0x00},
	{0x847, 0x00},
	{0x848, 0x00},
	{0x849, 0x01},
	{0x84A, 0x1F},
	{0x84B, 0x00},
	{0x84C, 0x05},
	{0x84D, 0x00},
	{0x84E, 0x19},
	{0x84F, 0x01},
	{0x850, 0x21},
	{0x851, 0x01},
	{0x852, 0x5D},
	{0x853, 0x00},
	{0x854, 0x00},
	{0x855, 0x00},
	{0x856, 0x19},
	{0x857, 0x01},
	{0x858, 0x21},
	{0x859, 0x00},
	{0x85A, 0x00},
	{0x85B, 0x00},
	{0x85C, 0x00},
	{0x85D, 0x00},
	{0x85E, 0x00},
	{0x85F, 0x00},
	{0x860, 0xB3},
	{0x861, 0x00},
	{0x862, 0xE3},
	{0x863, 0x00},
	{0x864, 0x00},
	{0x865, 0x00},
	{0x866, 0x00},
	{0x867, 0x00},
	{0x868, 0x00},
	{0x869, 0xE2},
	{0x86A, 0x00},
	{0x86B, 0x01},
	{0x86C, 0x06},
	{0x86D, 0x00},
	{0x86E, 0x00},
	{0x86F, 0x00},
	{0x870, 0x60},
	{0x871, 0x8C},
	{0x872, 0x10},
	{0x873, 0x00},
	{0x874, 0xE0},
	{0x875, 0x00},
	{0x876, 0x27},
	{0x877, 0x01},
	{0x878, 0x00},
	{0x879, 0x00},
	{0x87A, 0x00},
	{0x87B, 0x03},
	{0x87C, 0x00},
	{0x87D, 0x00},
	{0x87E, 0x00},
	{0x87F, 0x00},
	{0x880, 0x00},
	{0x881, 0x00},
	{0x882, 0x00},
	{0x883, 0x00},
	{0x884, 0x00},
	{0x885, 0x00},
	{0x886, 0xF8},
	{0x887, 0x00},
	{0x888, 0x03},
	{0x889, 0x00},
	{0x88A, 0x64},
	{0x88B, 0x00},
	{0x88C, 0x03},
	{0x88D, 0x00},
	{0x88E, 0xB1},
	{0x88F, 0x00},
	{0x890, 0x03},
	{0x891, 0x01},
	{0x892, 0x1D},
	{0x893, 0x00},
	{0x894, 0x03},
	{0x895, 0x01},
	{0x896, 0x4B},
	{0x897, 0x00},
	{0x898, 0xE5},
	{0x899, 0x00},
	{0x89A, 0x01},
	{0x89B, 0x00},
	{0x89C, 0x01},
	{0x89D, 0x04},
	{0x89E, 0xC8},
	{0x89F, 0x00},
	{0x8A0, 0x01},
	{0x8A1, 0x01},
	{0x8A2, 0x61},
	{0x8A3, 0x00},
	{0x8A4, 0x01},
	{0x8A5, 0x00},
	{0x8A6, 0x00},
	{0x8A7, 0x00},
	{0x8A8, 0x00},
	{0x8A9, 0x00},
	{0x8AA, 0x7F},
	{0x8AB, 0x03},
	{0x8AC, 0x00},
	{0x8AD, 0x00},
	{0x8AE, 0x00},
	{0x8AF, 0x00},
	{0x8B0, 0x00},
	{0x8B1, 0x00},
	{0x8B6, 0x00},
	{0x8B7, 0x01},
	{0x8B8, 0x00},
	{0x8B9, 0x00},
	{0x8BA, 0x02},
	{0x8BB, 0x00},
	{0x8BC, 0xFF},
	{0x8BD, 0x00},
	{0x8FE, 2},
};

static const stwuct wj54n1_weg_vaw bank_10[] = {
	{0x10bf, 0x69}
};

/* Cwock dividews - these awe defauwt wegistew vawues, dividew = wegistew + 1 */
static const stwuct wj54n1_cwock_div cwk_div = {
	.watio_tg	= 3 /* defauwt: 5 */,
	.watio_t	= 4 /* defauwt: 1 */,
	.watio_w	= 4 /* defauwt: 0 */,
	.watio_op	= 1 /* defauwt: 5 */,
	.watio_o	= 9 /* defauwt: 0 */,
};

static stwuct wj54n1 *to_wj54n1(const stwuct i2c_cwient *cwient)
{
	wetuwn containew_of(i2c_get_cwientdata(cwient), stwuct wj54n1, subdev);
}

static int weg_wead(stwuct i2c_cwient *cwient, const u16 weg)
{
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	int wet;

	/* set bank */
	if (wj54n1->bank != weg >> 8) {
		dev_dbg(&cwient->dev, "[0x%x] = 0x%x\n", 0xff, weg >> 8);
		wet = i2c_smbus_wwite_byte_data(cwient, 0xff, weg >> 8);
		if (wet < 0)
			wetuwn wet;
		wj54n1->bank = weg >> 8;
	}
	wetuwn i2c_smbus_wead_byte_data(cwient, weg & 0xff);
}

static int weg_wwite(stwuct i2c_cwient *cwient, const u16 weg,
		     const u8 data)
{
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	int wet;

	/* set bank */
	if (wj54n1->bank != weg >> 8) {
		dev_dbg(&cwient->dev, "[0x%x] = 0x%x\n", 0xff, weg >> 8);
		wet = i2c_smbus_wwite_byte_data(cwient, 0xff, weg >> 8);
		if (wet < 0)
			wetuwn wet;
		wj54n1->bank = weg >> 8;
	}
	dev_dbg(&cwient->dev, "[0x%x] = 0x%x\n", weg & 0xff, data);
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg & 0xff, data);
}

static int weg_set(stwuct i2c_cwient *cwient, const u16 weg,
		   const u8 data, const u8 mask)
{
	int wet;

	wet = weg_wead(cwient, weg);
	if (wet < 0)
		wetuwn wet;
	wetuwn weg_wwite(cwient, weg, (wet & ~mask) | (data & mask));
}

static int weg_wwite_muwtipwe(stwuct i2c_cwient *cwient,
			      const stwuct wj54n1_weg_vaw *wv, const int n)
{
	int i, wet;

	fow (i = 0; i < n; i++) {
		wet = weg_wwite(cwient, wv->weg, wv->vaw);
		if (wet < 0)
			wetuwn wet;
		wv++;
	}

	wetuwn 0;
}

static int wj54n1_enum_mbus_code(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index >= AWWAY_SIZE(wj54n1_cowouw_fmts))
		wetuwn -EINVAW;

	code->code = wj54n1_cowouw_fmts[code->index].code;
	wetuwn 0;
}

static int wj54n1_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	/* Switch between pweview and stiww shot modes */
	wetuwn weg_set(cwient, WJ54N1_STIWW_CONTWOW, (!enabwe) << 7, 0x80);
}

static int wj54n1_set_wect(stwuct i2c_cwient *cwient,
			   u16 weg_x, u16 weg_y, u16 weg_xy,
			   u32 width, u32 height)
{
	int wet;

	wet = weg_wwite(cwient, weg_xy,
			((width >> 4) & 0x70) |
			((height >> 8) & 7));

	if (!wet)
		wet = weg_wwite(cwient, weg_x, width & 0xff);
	if (!wet)
		wet = weg_wwite(cwient, weg_y, height & 0xff);

	wetuwn wet;
}

/*
 * Some commands, specificawwy cewtain initiawisation sequences, wequiwe
 * a commit opewation.
 */
static int wj54n1_commit(stwuct i2c_cwient *cwient)
{
	int wet = weg_wwite(cwient, WJ54N1_INIT_STAWT, 1);
	msweep(10);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_INIT_STAWT, 0);
	wetuwn wet;
}

static int wj54n1_sensow_scawe(stwuct v4w2_subdev *sd, s32 *in_w, s32 *in_h,
			       s32 *out_w, s32 *out_h);

static int wj54n1_set_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	const stwuct v4w2_wect *wect = &sew->w;
	int output_w, output_h, input_w = wect->width, input_h = wect->height;
	int wet;

	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE ||
	    sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	/* awbitwawy minimum width and height, edges unimpowtant */
	v4w_bound_awign_image(&input_w, 8, WJ54N1_MAX_WIDTH, 0,
			      &input_h, 8, WJ54N1_MAX_HEIGHT, 0, 0);

	output_w = (input_w * 1024 + wj54n1->wesize / 2) / wj54n1->wesize;
	output_h = (input_h * 1024 + wj54n1->wesize / 2) / wj54n1->wesize;

	dev_dbg(&cwient->dev, "Scawing fow %dx%d : %u = %dx%d\n",
		input_w, input_h, wj54n1->wesize, output_w, output_h);

	wet = wj54n1_sensow_scawe(sd, &input_w, &input_h, &output_w, &output_h);
	if (wet < 0)
		wetuwn wet;

	wj54n1->width		= output_w;
	wj54n1->height		= output_h;
	wj54n1->wesize		= wet;
	wj54n1->wect.width	= input_w;
	wj54n1->wect.height	= input_h;

	wetuwn 0;
}

static int wj54n1_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);

	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.weft = WJ54N1_COWUMN_SKIP;
		sew->w.top = WJ54N1_WOW_SKIP;
		sew->w.width = WJ54N1_MAX_WIDTH;
		sew->w.height = WJ54N1_MAX_HEIGHT;
		wetuwn 0;
	case V4W2_SEW_TGT_CWOP:
		sew->w = wj54n1->wect;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wj54n1_get_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);

	if (fowmat->pad)
		wetuwn -EINVAW;

	mf->code	= wj54n1->fmt->code;
	mf->cowowspace	= wj54n1->fmt->cowowspace;
	mf->ycbcw_enc	= V4W2_YCBCW_ENC_601;
	mf->xfew_func	= V4W2_XFEW_FUNC_SWGB;
	mf->quantization = V4W2_QUANTIZATION_DEFAUWT;
	mf->fiewd	= V4W2_FIEWD_NONE;
	mf->width	= wj54n1->width;
	mf->height	= wj54n1->height;

	wetuwn 0;
}

/*
 * The actuaw geometwy configuwation woutine. It scawes the input window into
 * the output one, updates the window sizes and wetuwns an ewwow ow the wesize
 * coefficient on success. Note: we onwy use the "Fixed Scawing" on this camewa.
 */
static int wj54n1_sensow_scawe(stwuct v4w2_subdev *sd, s32 *in_w, s32 *in_h,
			       s32 *out_w, s32 *out_h)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	unsigned int skip, wesize, input_w = *in_w, input_h = *in_h,
		output_w = *out_w, output_h = *out_h;
	u16 inc_sew, wb_bit8, wb_weft, wb_wight, wb_top, wb_bottom;
	unsigned int peak, peak_50, peak_60;
	int wet;

	/*
	 * We have a pwobwem with cwops, whewe the window is wawgew than 512x384
	 * and output window is wawgew than a hawf of the input one. In this
	 * case we have to eithew weduce the input window to equaw ow bewow
	 * 512x384 ow the output window to equaw ow bewow 1/2 of the input.
	 */
	if (output_w > max(512U, input_w / 2)) {
		if (2 * output_w > WJ54N1_MAX_WIDTH) {
			input_w = WJ54N1_MAX_WIDTH;
			output_w = WJ54N1_MAX_WIDTH / 2;
		} ewse {
			input_w = output_w * 2;
		}

		dev_dbg(&cwient->dev, "Adjusted output width: in %u, out %u\n",
			input_w, output_w);
	}

	if (output_h > max(384U, input_h / 2)) {
		if (2 * output_h > WJ54N1_MAX_HEIGHT) {
			input_h = WJ54N1_MAX_HEIGHT;
			output_h = WJ54N1_MAX_HEIGHT / 2;
		} ewse {
			input_h = output_h * 2;
		}

		dev_dbg(&cwient->dev, "Adjusted output height: in %u, out %u\n",
			input_h, output_h);
	}

	/* Idea: use the wead mode fow snapshots, handwe sepawate geometwies */
	wet = wj54n1_set_wect(cwient, WJ54N1_X_OUTPUT_SIZE_S_W,
			      WJ54N1_Y_OUTPUT_SIZE_S_W,
			      WJ54N1_XY_OUTPUT_SIZE_S_H, output_w, output_h);
	if (!wet)
		wet = wj54n1_set_wect(cwient, WJ54N1_X_OUTPUT_SIZE_P_W,
			      WJ54N1_Y_OUTPUT_SIZE_P_W,
			      WJ54N1_XY_OUTPUT_SIZE_P_H, output_w, output_h);

	if (wet < 0)
		wetuwn wet;

	if (output_w > input_w && output_h > input_h) {
		input_w = output_w;
		input_h = output_h;

		wesize = 1024;
	} ewse {
		unsigned int wesize_x, wesize_y;
		wesize_x = (input_w * 1024 + output_w / 2) / output_w;
		wesize_y = (input_h * 1024 + output_h / 2) / output_h;

		/* We want max(wesize_x, wesize_y), check if it stiww fits */
		if (wesize_x > wesize_y &&
		    (output_h * wesize_x + 512) / 1024 > WJ54N1_MAX_HEIGHT)
			wesize = (WJ54N1_MAX_HEIGHT * 1024 + output_h / 2) /
				output_h;
		ewse if (wesize_y > wesize_x &&
			 (output_w * wesize_y + 512) / 1024 > WJ54N1_MAX_WIDTH)
			wesize = (WJ54N1_MAX_WIDTH * 1024 + output_w / 2) /
				output_w;
		ewse
			wesize = max(wesize_x, wesize_y);

		/* Pwohibited vawue wanges */
		switch (wesize) {
		case 2040 ... 2047:
			wesize = 2039;
			bweak;
		case 4080 ... 4095:
			wesize = 4079;
			bweak;
		case 8160 ... 8191:
			wesize = 8159;
			bweak;
		case 16320 ... 16384:
			wesize = 16319;
		}
	}

	/* Set scawing */
	wet = weg_wwite(cwient, WJ54N1_WESIZE_HOWD_W, wesize & 0xff);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESIZE_HOWD_H, wesize >> 8);

	if (wet < 0)
		wetuwn wet;

	/*
	 * Configuwe a skipping bitmask. The sensow wiww sewect a skipping vawue
	 * among set bits automaticawwy. This is vewy uncweaw in the datasheet
	 * too. I was towd, in this wegistew one enabwes aww skipping vawues,
	 * that awe wequiwed fow a specific wesize, and the camewa sewects
	 * automaticawwy, which ones to use. But it is uncweaw how to identify,
	 * which cwopping vawues awe needed. Secondwy, why don't we just set aww
	 * bits and wet the camewa choose? Wouwd it incwease pwocessing time and
	 * weduce the fwamewate? Using 0xfffc fow INC_USE_SEW doesn't seem to
	 * impwove the image quawity ow stabiwity fow wawgew fwames (see comment
	 * above), but I didn't check the fwamewate.
	 */
	skip = min(wesize / 1024, 15U);

	inc_sew = 1 << skip;

	if (inc_sew <= 2)
		inc_sew = 0xc;
	ewse if (wesize & 1023 && skip < 15)
		inc_sew |= 1 << (skip + 1);

	wet = weg_wwite(cwient, WJ54N1_INC_USE_SEW_W, inc_sew & 0xfc);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_INC_USE_SEW_H, inc_sew >> 8);

	if (!wj54n1->auto_wb) {
		/* Auto white bawance window */
		wb_weft	  = output_w / 16;
		wb_wight  = (3 * output_w / 4 - 3) / 4;
		wb_top	  = output_h / 16;
		wb_bottom = (3 * output_h / 4 - 3) / 4;
		wb_bit8	  = ((wb_weft >> 2) & 0x40) | ((wb_top >> 4) & 0x10) |
			((wb_wight >> 6) & 4) | ((wb_bottom >> 8) & 1);

		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_BIT8_WB, wb_bit8);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_HCAPS_WB, wb_weft);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_VCAPS_WB, wb_top);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_HCAPE_WB, wb_wight);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_VCAPE_WB, wb_bottom);
	}

	/* Antifwickew */
	peak = 12 * WJ54N1_MAX_WIDTH * (1 << 14) * wesize / wj54n1->tgcwk_mhz /
		10000;
	peak_50 = peak / 6;
	peak_60 = peak / 5;

	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PEAK_H,
				((peak_50 >> 4) & 0xf0) | (peak_60 >> 8));
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PEAK_50, peak_50);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PEAK_60, peak_60);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PEAK_DIFF, peak / 150);

	/* Stawt wesizing */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESIZE_CONTWOW,
				WESIZE_HOWD_SEW | WESIZE_GO | 1);

	if (wet < 0)
		wetuwn wet;

	/* Constant taken fwom manufactuwew's exampwe */
	msweep(230);

	wet = weg_wwite(cwient, WJ54N1_WESIZE_CONTWOW, WESIZE_HOWD_SEW | 1);
	if (wet < 0)
		wetuwn wet;

	*in_w = (output_w * wesize + 512) / 1024;
	*in_h = (output_h * wesize + 512) / 1024;
	*out_w = output_w;
	*out_h = output_h;

	dev_dbg(&cwient->dev, "Scawed fow %dx%d : %u = %ux%u, skip %u\n",
		*in_w, *in_h, wesize, output_w, output_h, skip);

	wetuwn wesize;
}

static int wj54n1_set_cwock(stwuct i2c_cwient *cwient)
{
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	int wet;

	/* Enabwe extewnaw cwock */
	wet = weg_wwite(cwient, WJ54N1_WESET_STANDBY, E_EXCWK | SOFT_STDBY);
	/* Weave stand-by. Note: use this when impwementing suspend / wesume */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESET_STANDBY, E_EXCWK);

	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PWW_W, PWW_W);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PWW_N, PWW_N);

	/* TGCWK dividews */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WATIO_TG,
				wj54n1->cwk_div.watio_tg);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WATIO_T,
				wj54n1->cwk_div.watio_t);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WATIO_W,
				wj54n1->cwk_div.watio_w);

	/* Enabwe TGCWK & WAMP */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WAMP_TGCWK_EN, 3);

	/* Disabwe cwock output */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_OCWK_DSP, 0);

	/* Set divisows */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WATIO_OP,
				wj54n1->cwk_div.watio_op);
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WATIO_O,
				wj54n1->cwk_div.watio_o);

	/* Enabwe OCWK */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_OCWK_SEW_EN, 1);

	/* Use PWW fow Timing Genewatow, wwite 2 to wesewved bits */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_TG_BYPASS, 2);

	/* Take sensow out of weset */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESET_STANDBY,
				E_EXCWK | SEN_WSTX);
	/* Enabwe PWW */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_PWW_EN, 1);

	/* Wait fow PWW to stabiwise */
	msweep(10);

	/* Enabwe cwock to fwequency dividew */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_CWK_WST, 1);

	if (!wet)
		wet = weg_wead(cwient, WJ54N1_CWK_WST);
	if (wet != 1) {
		dev_eww(&cwient->dev,
			"Wesetting WJ54N1CB0C cwock faiwed: %d!\n", wet);
		wetuwn -EIO;
	}

	/* Stawt the PWW */
	wet = weg_set(cwient, WJ54N1_OCWK_DSP, 1, 1);

	/* Enabwe OCWK */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_OCWK_SEW_EN, 1);

	wetuwn wet;
}

static int wj54n1_weg_init(stwuct i2c_cwient *cwient)
{
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	int wet = wj54n1_set_cwock(cwient);

	if (!wet)
		wet = weg_wwite_muwtipwe(cwient, bank_7, AWWAY_SIZE(bank_7));
	if (!wet)
		wet = weg_wwite_muwtipwe(cwient, bank_10, AWWAY_SIZE(bank_10));

	/* Set binning divisows */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_SCAWE_1_2_WEV, 3 | (7 << 4));
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_SCAWE_4_WEV, 0xf);

	/* Switch to fixed wesize mode */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESIZE_CONTWOW,
				WESIZE_HOWD_SEW | 1);

	/* Set gain */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_Y_GAIN, 0x84);

	/*
	 * Miwwow the image back: defauwt is upside down and weft-to-wight...
	 * Set manuaw pweview / stiww shot switching
	 */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_MIWWOW_STIWW_MODE, 0x27);

	if (!wet)
		wet = weg_wwite_muwtipwe(cwient, bank_4, AWWAY_SIZE(bank_4));

	/* Auto exposuwe awea */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_EXPOSUWE_CONTWOW, 0x80);
	/* Check cuwwent auto WB config */
	if (!wet)
		wet = weg_wead(cwient, WJ54N1_WB_SEW_WEIGHT_I);
	if (wet >= 0) {
		wj54n1->auto_wb = wet & 0x80;
		wet = weg_wwite_muwtipwe(cwient, bank_5, AWWAY_SIZE(bank_5));
	}
	if (!wet)
		wet = weg_wwite_muwtipwe(cwient, bank_8, AWWAY_SIZE(bank_8));

	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESET_STANDBY,
				E_EXCWK | DSP_WSTX | SEN_WSTX);

	/* Commit init */
	if (!wet)
		wet = wj54n1_commit(cwient);

	/* Take DSP, TG, sensow out of weset */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_WESET_STANDBY,
				E_EXCWK | DSP_WSTX | TG_WSTX | SEN_WSTX);

	/* Stawt wegistew update? Same wegistew as 0x?FE in many bank_* sets */
	if (!wet)
		wet = weg_wwite(cwient, WJ54N1_FWFWG, 2);

	/* Constant taken fwom manufactuwew's exampwe */
	msweep(700);

	wetuwn wet;
}

static int wj54n1_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	const stwuct wj54n1_datafmt *fmt;
	int output_w, output_h, max_w, max_h,
		input_w = wj54n1->wect.width, input_h = wj54n1->wect.height;
	int awign = mf->code == MEDIA_BUS_FMT_SBGGW10_1X10 ||
		mf->code == MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_BE ||
		mf->code == MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_BE ||
		mf->code == MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE ||
		mf->code == MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_WE;
	int wet;

	if (fowmat->pad)
		wetuwn -EINVAW;

	dev_dbg(&cwient->dev, "%s: code = %d, width = %u, height = %u\n",
		__func__, mf->code, mf->width, mf->height);

	fmt = wj54n1_find_datafmt(mf->code, wj54n1_cowouw_fmts,
				  AWWAY_SIZE(wj54n1_cowouw_fmts));
	if (!fmt) {
		fmt = wj54n1->fmt;
		mf->code = fmt->code;
	}

	mf->fiewd	= V4W2_FIEWD_NONE;
	mf->cowowspace	= fmt->cowowspace;

	v4w_bound_awign_image(&mf->width, 112, WJ54N1_MAX_WIDTH, awign,
			      &mf->height, 84, WJ54N1_MAX_HEIGHT, awign, 0);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	/*
	 * Vewify if the sensow has just been powewed on. TODO: wepwace this
	 * with pwopew PM, when a suitabwe API is avaiwabwe.
	 */
	wet = weg_wead(cwient, WJ54N1_WESET_STANDBY);
	if (wet < 0)
		wetuwn wet;

	if (!(wet & E_EXCWK)) {
		wet = wj54n1_weg_init(cwient);
		if (wet < 0)
			wetuwn wet;
	}

	/* WA_SEW_UW is onwy wewevant fow waw modes, ignowed othewwise. */
	switch (mf->code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 0);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 8, 8);
		bweak;
	case MEDIA_BUS_FMT_YVYU8_2X8:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 0);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 0, 8);
		bweak;
	case MEDIA_BUS_FMT_WGB565_2X8_WE:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 0x11);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 8, 8);
		bweak;
	case MEDIA_BUS_FMT_WGB565_2X8_BE:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 0x11);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 0, 8);
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_WE:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 4);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 8, 8);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_WA_SEW_UW, 0);
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 4);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 8, 8);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_WA_SEW_UW, 8);
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_BE:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 4);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 0, 8);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_WA_SEW_UW, 0);
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_BE:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 4);
		if (!wet)
			wet = weg_set(cwient, WJ54N1_BYTE_SWAP, 0, 8);
		if (!wet)
			wet = weg_wwite(cwient, WJ54N1_WA_SEW_UW, 8);
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_1X10:
		wet = weg_wwite(cwient, WJ54N1_OUT_SEW, 5);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	/* Speciaw case: a waw mode with 10 bits of data pew cwock tick */
	if (!wet)
		wet = weg_set(cwient, WJ54N1_OCWK_SEW_EN,
			      (mf->code == MEDIA_BUS_FMT_SBGGW10_1X10) << 1, 2);

	if (wet < 0)
		wetuwn wet;

	/* Suppowted scawes 1:1 >= scawe > 1:16 */
	max_w = mf->width * (16 * 1024 - 1) / 1024;
	if (input_w > max_w)
		input_w = max_w;
	max_h = mf->height * (16 * 1024 - 1) / 1024;
	if (input_h > max_h)
		input_h = max_h;

	output_w = mf->width;
	output_h = mf->height;

	wet = wj54n1_sensow_scawe(sd, &input_w, &input_h, &output_w, &output_h);
	if (wet < 0)
		wetuwn wet;

	fmt = wj54n1_find_datafmt(mf->code, wj54n1_cowouw_fmts,
				  AWWAY_SIZE(wj54n1_cowouw_fmts));

	wj54n1->fmt		= fmt;
	wj54n1->wesize		= wet;
	wj54n1->wect.width	= input_w;
	wj54n1->wect.height	= input_h;
	wj54n1->width		= output_w;
	wj54n1->height		= output_h;

	mf->width		= output_w;
	mf->height		= output_h;
	mf->fiewd		= V4W2_FIEWD_NONE;
	mf->cowowspace		= fmt->cowowspace;

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int wj54n1_g_wegistew(stwuct v4w2_subdev *sd,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	if (weg->weg < 0x400 || weg->weg > 0x1fff)
		/* Wegistews > 0x0800 awe onwy avaiwabwe fwom Shawp suppowt */
		wetuwn -EINVAW;

	weg->size = 1;
	weg->vaw = weg_wead(cwient, weg->weg);

	if (weg->vaw > 0xff)
		wetuwn -EIO;

	wetuwn 0;
}

static int wj54n1_s_wegistew(stwuct v4w2_subdev *sd,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	if (weg->weg < 0x400 || weg->weg > 0x1fff)
		/* Wegistews >= 0x0800 awe onwy avaiwabwe fwom Shawp suppowt */
		wetuwn -EINVAW;

	if (weg_wwite(cwient, weg->weg, weg->vaw) < 0)
		wetuwn -EIO;

	wetuwn 0;
}
#endif

static int wj54n1_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);

	if (on) {
		if (wj54n1->pwup_gpio)
			gpiod_set_vawue(wj54n1->pwup_gpio, 1);
		if (wj54n1->enabwe_gpio)
			gpiod_set_vawue(wj54n1->enabwe_gpio, 1);

		msweep(1);

		wetuwn cwk_pwepawe_enabwe(wj54n1->cwk);
	}

	cwk_disabwe_unpwepawe(wj54n1->cwk);

	if (wj54n1->enabwe_gpio)
		gpiod_set_vawue(wj54n1->enabwe_gpio, 0);
	if (wj54n1->pwup_gpio)
		gpiod_set_vawue(wj54n1->pwup_gpio, 0);

	wetuwn 0;
}

static int wj54n1_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wj54n1 *wj54n1 = containew_of(ctww->handwew, stwuct wj54n1, hdw);
	stwuct v4w2_subdev *sd = &wj54n1->subdev;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int data;

	switch (ctww->id) {
	case V4W2_CID_VFWIP:
		if (ctww->vaw)
			data = weg_set(cwient, WJ54N1_MIWWOW_STIWW_MODE, 0, 1);
		ewse
			data = weg_set(cwient, WJ54N1_MIWWOW_STIWW_MODE, 1, 1);
		if (data < 0)
			wetuwn -EIO;
		wetuwn 0;
	case V4W2_CID_HFWIP:
		if (ctww->vaw)
			data = weg_set(cwient, WJ54N1_MIWWOW_STIWW_MODE, 0, 2);
		ewse
			data = weg_set(cwient, WJ54N1_MIWWOW_STIWW_MODE, 2, 2);
		if (data < 0)
			wetuwn -EIO;
		wetuwn 0;
	case V4W2_CID_GAIN:
		if (weg_wwite(cwient, WJ54N1_Y_GAIN, ctww->vaw * 2) < 0)
			wetuwn -EIO;
		wetuwn 0;
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		/* Auto WB awea - whowe image */
		if (weg_set(cwient, WJ54N1_WB_SEW_WEIGHT_I, ctww->vaw << 7,
			    0x80) < 0)
			wetuwn -EIO;
		wj54n1->auto_wb = ctww->vaw;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops wj54n1_ctww_ops = {
	.s_ctww = wj54n1_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops wj54n1_subdev_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew	= wj54n1_g_wegistew,
	.s_wegistew	= wj54n1_s_wegistew,
#endif
	.s_powew	= wj54n1_s_powew,
};

static const stwuct v4w2_subdev_video_ops wj54n1_subdev_video_ops = {
	.s_stweam	= wj54n1_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops wj54n1_subdev_pad_ops = {
	.enum_mbus_code = wj54n1_enum_mbus_code,
	.get_sewection	= wj54n1_get_sewection,
	.set_sewection	= wj54n1_set_sewection,
	.get_fmt	= wj54n1_get_fmt,
	.set_fmt	= wj54n1_set_fmt,
};

static const stwuct v4w2_subdev_ops wj54n1_subdev_ops = {
	.cowe	= &wj54n1_subdev_cowe_ops,
	.video	= &wj54n1_subdev_video_ops,
	.pad	= &wj54n1_subdev_pad_ops,
};

/*
 * Intewface active, can use i2c. If it faiws, it can indeed mean, that
 * this wasn't ouw captuwe intewface, so, we wait fow the wight one
 */
static int wj54n1_video_pwobe(stwuct i2c_cwient *cwient,
			      stwuct wj54n1_pdata *pwiv)
{
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);
	int data1, data2;
	int wet;

	wet = wj54n1_s_powew(&wj54n1->subdev, 1);
	if (wet < 0)
		wetuwn wet;

	/* Wead out the chip vewsion wegistew */
	data1 = weg_wead(cwient, WJ54N1_DEV_CODE);
	data2 = weg_wead(cwient, WJ54N1_DEV_CODE2);

	if (data1 != 0x51 || data2 != 0x10) {
		wet = -ENODEV;
		dev_info(&cwient->dev, "No WJ54N1CB0C found, wead 0x%x:0x%x\n",
			 data1, data2);
		goto done;
	}

	/* Configuwe IOCTW powawity fwom the pwatfowm data: 0 ow 1 << 7. */
	wet = weg_wwite(cwient, WJ54N1_IOC, pwiv->ioctw_high << 7);
	if (wet < 0)
		goto done;

	dev_info(&cwient->dev, "Detected a WJ54N1CB0C chip ID 0x%x:0x%x\n",
		 data1, data2);

	wet = v4w2_ctww_handwew_setup(&wj54n1->hdw);

done:
	wj54n1_s_powew(&wj54n1->subdev, 0);
	wetuwn wet;
}

static int wj54n1_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wj54n1 *wj54n1;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct wj54n1_pdata *wj54n1_pwiv;
	int wet;

	if (!cwient->dev.pwatfowm_data) {
		dev_eww(&cwient->dev, "WJ54N1CB0C: missing pwatfowm data!\n");
		wetuwn -EINVAW;
	}

	wj54n1_pwiv = cwient->dev.pwatfowm_data;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_wawn(&adaptew->dev,
			 "I2C-Adaptew doesn't suppowt I2C_FUNC_SMBUS_BYTE\n");
		wetuwn -EIO;
	}

	wj54n1 = devm_kzawwoc(&cwient->dev, sizeof(stwuct wj54n1), GFP_KEWNEW);
	if (!wj54n1)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&wj54n1->subdev, cwient, &wj54n1_subdev_ops);
	v4w2_ctww_handwew_init(&wj54n1->hdw, 4);
	v4w2_ctww_new_std(&wj54n1->hdw, &wj54n1_ctww_ops,
			V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(&wj54n1->hdw, &wj54n1_ctww_ops,
			V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(&wj54n1->hdw, &wj54n1_ctww_ops,
			V4W2_CID_GAIN, 0, 127, 1, 66);
	v4w2_ctww_new_std(&wj54n1->hdw, &wj54n1_ctww_ops,
			V4W2_CID_AUTO_WHITE_BAWANCE, 0, 1, 1, 1);
	wj54n1->subdev.ctww_handwew = &wj54n1->hdw;
	if (wj54n1->hdw.ewwow)
		wetuwn wj54n1->hdw.ewwow;

	wj54n1->cwk_div		= cwk_div;
	wj54n1->wect.weft	= WJ54N1_COWUMN_SKIP;
	wj54n1->wect.top	= WJ54N1_WOW_SKIP;
	wj54n1->wect.width	= WJ54N1_MAX_WIDTH;
	wj54n1->wect.height	= WJ54N1_MAX_HEIGHT;
	wj54n1->width		= WJ54N1_MAX_WIDTH;
	wj54n1->height		= WJ54N1_MAX_HEIGHT;
	wj54n1->fmt		= &wj54n1_cowouw_fmts[0];
	wj54n1->wesize		= 1024;
	wj54n1->tgcwk_mhz	= (wj54n1_pwiv->mcwk_fweq / PWW_W * PWW_N) /
		(cwk_div.watio_tg + 1) / (cwk_div.watio_t + 1);

	wj54n1->cwk = cwk_get(&cwient->dev, NUWW);
	if (IS_EWW(wj54n1->cwk)) {
		wet = PTW_EWW(wj54n1->cwk);
		goto eww_fwee_ctww;
	}

	wj54n1->pwup_gpio = gpiod_get_optionaw(&cwient->dev, "powewup",
					       GPIOD_OUT_WOW);
	if (IS_EWW(wj54n1->pwup_gpio)) {
		dev_info(&cwient->dev, "Unabwe to get GPIO \"powewup\": %wd\n",
			 PTW_EWW(wj54n1->pwup_gpio));
		wet = PTW_EWW(wj54n1->pwup_gpio);
		goto eww_cwk_put;
	}

	wj54n1->enabwe_gpio = gpiod_get_optionaw(&cwient->dev, "enabwe",
						 GPIOD_OUT_WOW);
	if (IS_EWW(wj54n1->enabwe_gpio)) {
		dev_info(&cwient->dev, "Unabwe to get GPIO \"enabwe\": %wd\n",
			 PTW_EWW(wj54n1->enabwe_gpio));
		wet = PTW_EWW(wj54n1->enabwe_gpio);
		goto eww_gpio_put;
	}

	wet = wj54n1_video_pwobe(cwient, wj54n1_pwiv);
	if (wet < 0)
		goto eww_gpio_put;

	wet = v4w2_async_wegistew_subdev(&wj54n1->subdev);
	if (wet)
		goto eww_gpio_put;

	wetuwn 0;

eww_gpio_put:
	if (wj54n1->enabwe_gpio)
		gpiod_put(wj54n1->enabwe_gpio);

	if (wj54n1->pwup_gpio)
		gpiod_put(wj54n1->pwup_gpio);

eww_cwk_put:
	cwk_put(wj54n1->cwk);

eww_fwee_ctww:
	v4w2_ctww_handwew_fwee(&wj54n1->hdw);

	wetuwn wet;
}

static void wj54n1_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wj54n1 *wj54n1 = to_wj54n1(cwient);

	if (wj54n1->enabwe_gpio)
		gpiod_put(wj54n1->enabwe_gpio);
	if (wj54n1->pwup_gpio)
		gpiod_put(wj54n1->pwup_gpio);

	cwk_put(wj54n1->cwk);
	v4w2_ctww_handwew_fwee(&wj54n1->hdw);
	v4w2_async_unwegistew_subdev(&wj54n1->subdev);
}

static const stwuct i2c_device_id wj54n1_id[] = {
	{ "wj54n1cb0c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wj54n1_id);

static stwuct i2c_dwivew wj54n1_i2c_dwivew = {
	.dwivew = {
		.name = "wj54n1cb0c",
	},
	.pwobe		= wj54n1_pwobe,
	.wemove		= wj54n1_wemove,
	.id_tabwe	= wj54n1_id,
};

moduwe_i2c_dwivew(wj54n1_i2c_dwivew);

MODUWE_DESCWIPTION("Shawp WJ54N1CB0C Camewa dwivew");
MODUWE_AUTHOW("Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>");
MODUWE_WICENSE("GPW v2");
