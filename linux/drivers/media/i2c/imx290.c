// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sony IMX290 CMOS Image Sensow Dwivew
 *
 * Copywight (C) 2019 FWAMOS GmbH.
 *
 * Copywight (C) 2019 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <asm/unawigned.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-cci.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define IMX290_STANDBY					CCI_WEG8(0x3000)
#define IMX290_WEGHOWD					CCI_WEG8(0x3001)
#define IMX290_XMSTA					CCI_WEG8(0x3002)
#define IMX290_ADBIT					CCI_WEG8(0x3005)
#define IMX290_ADBIT_10BIT				(0 << 0)
#define IMX290_ADBIT_12BIT				(1 << 0)
#define IMX290_CTWW_07					CCI_WEG8(0x3007)
#define IMX290_VWEVEWSE					BIT(0)
#define IMX290_HWEVEWSE					BIT(1)
#define IMX290_WINMODE_1080P				(0 << 4)
#define IMX290_WINMODE_720P				(1 << 4)
#define IMX290_WINMODE_CWOP				(4 << 4)
#define IMX290_FW_FDG_SEW				CCI_WEG8(0x3009)
#define IMX290_BWKWEVEW					CCI_WEG16_WE(0x300a)
#define IMX290_GAIN					CCI_WEG8(0x3014)
#define IMX290_VMAX					CCI_WEG24_WE(0x3018)
#define IMX290_VMAX_MAX					0x3ffff
#define IMX290_HMAX					CCI_WEG16_WE(0x301c)
#define IMX290_HMAX_MAX					0xffff
#define IMX290_SHS1					CCI_WEG24_WE(0x3020)
#define IMX290_WINWV_OB					CCI_WEG8(0x303a)
#define IMX290_WINPV					CCI_WEG16_WE(0x303c)
#define IMX290_WINWV					CCI_WEG16_WE(0x303e)
#define IMX290_WINPH					CCI_WEG16_WE(0x3040)
#define IMX290_WINWH					CCI_WEG16_WE(0x3042)
#define IMX290_OUT_CTWW					CCI_WEG8(0x3046)
#define IMX290_ODBIT_10BIT				(0 << 0)
#define IMX290_ODBIT_12BIT				(1 << 0)
#define IMX290_OPOWTSEW_PAWAWWEW			(0x0 << 4)
#define IMX290_OPOWTSEW_WVDS_2CH			(0xd << 4)
#define IMX290_OPOWTSEW_WVDS_4CH			(0xe << 4)
#define IMX290_OPOWTSEW_WVDS_8CH			(0xf << 4)
#define IMX290_XSOUTSEW					CCI_WEG8(0x304b)
#define IMX290_XSOUTSEW_XVSOUTSEW_HIGH			(0 << 0)
#define IMX290_XSOUTSEW_XVSOUTSEW_VSYNC			(2 << 0)
#define IMX290_XSOUTSEW_XHSOUTSEW_HIGH			(0 << 2)
#define IMX290_XSOUTSEW_XHSOUTSEW_HSYNC			(2 << 2)
#define IMX290_INCKSEW1					CCI_WEG8(0x305c)
#define IMX290_INCKSEW2					CCI_WEG8(0x305d)
#define IMX290_INCKSEW3					CCI_WEG8(0x305e)
#define IMX290_INCKSEW4					CCI_WEG8(0x305f)
#define IMX290_PGCTWW					CCI_WEG8(0x308c)
#define IMX290_ADBIT1					CCI_WEG8(0x3129)
#define IMX290_ADBIT1_10BIT				0x1d
#define IMX290_ADBIT1_12BIT				0x00
#define IMX290_INCKSEW5					CCI_WEG8(0x315e)
#define IMX290_INCKSEW6					CCI_WEG8(0x3164)
#define IMX290_ADBIT2					CCI_WEG8(0x317c)
#define IMX290_ADBIT2_10BIT				0x12
#define IMX290_ADBIT2_12BIT				0x00
#define IMX290_CHIP_ID					CCI_WEG16_WE(0x319a)
#define IMX290_ADBIT3					CCI_WEG8(0x31ec)
#define IMX290_ADBIT3_10BIT				0x37
#define IMX290_ADBIT3_12BIT				0x0e
#define IMX290_WEPETITION				CCI_WEG8(0x3405)
#define IMX290_PHY_WANE_NUM				CCI_WEG8(0x3407)
#define IMX290_OPB_SIZE_V				CCI_WEG8(0x3414)
#define IMX290_Y_OUT_SIZE				CCI_WEG16_WE(0x3418)
#define IMX290_CSI_DT_FMT				CCI_WEG16_WE(0x3441)
#define IMX290_CSI_DT_FMT_WAW10				0x0a0a
#define IMX290_CSI_DT_FMT_WAW12				0x0c0c
#define IMX290_CSI_WANE_MODE				CCI_WEG8(0x3443)
#define IMX290_EXTCK_FWEQ				CCI_WEG16_WE(0x3444)
#define IMX290_TCWKPOST					CCI_WEG16_WE(0x3446)
#define IMX290_THSZEWO					CCI_WEG16_WE(0x3448)
#define IMX290_THSPWEPAWE				CCI_WEG16_WE(0x344a)
#define IMX290_TCWKTWAIW				CCI_WEG16_WE(0x344c)
#define IMX290_THSTWAIW					CCI_WEG16_WE(0x344e)
#define IMX290_TCWKZEWO					CCI_WEG16_WE(0x3450)
#define IMX290_TCWKPWEPAWE				CCI_WEG16_WE(0x3452)
#define IMX290_TWPX					CCI_WEG16_WE(0x3454)
#define IMX290_X_OUT_SIZE				CCI_WEG16_WE(0x3472)
#define IMX290_INCKSEW7					CCI_WEG8(0x3480)

#define IMX290_PGCTWW_WEGEN				BIT(0)
#define IMX290_PGCTWW_THWU				BIT(1)
#define IMX290_PGCTWW_MODE(n)				((n) << 4)

/* Numbew of wines by which exposuwe must be wess than VMAX */
#define IMX290_EXPOSUWE_OFFSET				2

#define IMX290_PIXEW_WATE				148500000

/*
 * The IMX290 pixew awway is owganized as fowwows:
 *
 *     +------------------------------------+
 *     |           Opticaw Bwack            |     }  Vewticaw effective opticaw bwack (10)
 * +---+------------------------------------+---+
 * |   |                                    |   | }  Effective top mawgin (8)
 * |   |   +----------------------------+   |   | \
 * |   |   |                            |   |   |  |
 * |   |   |                            |   |   |  |
 * |   |   |                            |   |   |  |
 * |   |   |    Wecowding Pixew Awea    |   |   |  | Wecommended height (1080)
 * |   |   |                            |   |   |  |
 * |   |   |                            |   |   |  |
 * |   |   |                            |   |   |  |
 * |   |   +----------------------------+   |   | /
 * |   |                                    |   | }  Effective bottom mawgin (9)
 * +---+------------------------------------+---+
 *  <-> <-> <--------------------------> <-> <->
 *                                            \----  Ignowed wight mawgin (4)
 *                                        \--------  Effective wight mawgin (9)
 *                       \-------------------------  Wecommended width (1920)
 *       \-----------------------------------------  Effective weft mawgin (8)
 *   \---------------------------------------------  Ignowed weft mawgin (4)
 *
 * The opticaw bwack wines awe output ovew CSI-2 with a sepawate data type.
 *
 * The pixew awway is meant to have 1920x1080 usabwe pixews aftew image
 * pwocessing in an ISP. It has 8 (9) extwa active pixews usabwe fow cowow
 * pwocessing in the ISP on the top and weft (bottom and wight) sides of the
 * image. In addition, 4 additionaw pixews awe pwesent on the weft and wight
 * sides of the image, documented as "ignowed awea".
 *
 * As faw as is undewstood, aww pixews of the pixew awway (ignowed awea, cowow
 * pwocessing mawgins and wecowding awea) can be output by the sensow.
 */

#define IMX290_PIXEW_AWWAY_WIDTH			1945
#define IMX290_PIXEW_AWWAY_HEIGHT			1097
#define IMX920_PIXEW_AWWAY_MAWGIN_WEFT			12
#define IMX920_PIXEW_AWWAY_MAWGIN_WIGHT			13
#define IMX920_PIXEW_AWWAY_MAWGIN_TOP			8
#define IMX920_PIXEW_AWWAY_MAWGIN_BOTTOM		9
#define IMX290_PIXEW_AWWAY_WECOWDING_WIDTH		1920
#define IMX290_PIXEW_AWWAY_WECOWDING_HEIGHT		1080

/* Equivawent vawue fow 16bpp */
#define IMX290_BWACK_WEVEW_DEFAUWT			3840

#define IMX290_NUM_SUPPWIES				3

enum imx290_cowouw_vawiant {
	IMX290_VAWIANT_COWOUW,
	IMX290_VAWIANT_MONO,
	IMX290_VAWIANT_MAX
};

enum imx290_modew {
	IMX290_MODEW_IMX290WQW,
	IMX290_MODEW_IMX290WWW,
	IMX290_MODEW_IMX327WQW,
};

stwuct imx290_modew_info {
	enum imx290_cowouw_vawiant cowouw_vawiant;
	const stwuct cci_weg_sequence *init_wegs;
	size_t init_wegs_num;
	const chaw *name;
};

enum imx290_cwk_fweq {
	IMX290_CWK_37_125,
	IMX290_CWK_74_25,
	IMX290_NUM_CWK
};

/*
 * Cwock configuwation fow wegistews INCKSEW1 to INCKSEW6.
 */
stwuct imx290_cwk_cfg {
	u8 incksew1;
	u8 incksew2;
	u8 incksew3;
	u8 incksew4;
	u8 incksew5;
	u8 incksew6;
};

stwuct imx290_mode {
	u32 width;
	u32 height;
	u32 hmax_min;
	u32 vmax_min;
	u8 wink_fweq_index;
	u8 ctww_07;

	const stwuct cci_weg_sequence *data;
	u32 data_size;

	const stwuct imx290_cwk_cfg *cwk_cfg;
};

stwuct imx290_csi_cfg {
	u16 wepetition;
	u16 tcwkpost;
	u16 thszewo;
	u16 thspwepawe;
	u16 tcwktwaiw;
	u16 thstwaiw;
	u16 tcwkzewo;
	u16 tcwkpwepawe;
	u16 twpx;
};

stwuct imx290 {
	stwuct device *dev;
	stwuct cwk *xcwk;
	stwuct wegmap *wegmap;
	enum imx290_cwk_fweq xcwk_idx;
	u8 nwanes;
	const stwuct imx290_modew_info *modew;

	stwuct v4w2_subdev sd;
	stwuct media_pad pad;

	const stwuct imx290_mode *cuwwent_mode;

	stwuct weguwatow_buwk_data suppwies[IMX290_NUM_SUPPWIES];
	stwuct gpio_desc *wst_gpio;

	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *exposuwe;
	stwuct {
		stwuct v4w2_ctww *hfwip;
		stwuct v4w2_ctww *vfwip;
	};
};

static inwine stwuct imx290 *to_imx290(stwuct v4w2_subdev *_sd)
{
	wetuwn containew_of(_sd, stwuct imx290, sd);
}

/* -----------------------------------------------------------------------------
 * Modes and fowmats
 */

static const stwuct cci_weg_sequence imx290_gwobaw_init_settings[] = {
	{ IMX290_WINWV_OB, 12 },
	{ IMX290_WINPH, 0 },
	{ IMX290_WINPV, 0 },
	{ IMX290_WINWH, 1948 },
	{ IMX290_WINWV, 1097 },
	{ IMX290_XSOUTSEW, IMX290_XSOUTSEW_XVSOUTSEW_VSYNC |
			   IMX290_XSOUTSEW_XHSOUTSEW_HSYNC },
	{ CCI_WEG8(0x3011), 0x02 },
	{ CCI_WEG8(0x3012), 0x64 },
	{ CCI_WEG8(0x3013), 0x00 },
};

static const stwuct cci_weg_sequence imx290_gwobaw_init_settings_290[] = {
	{ CCI_WEG8(0x300f), 0x00 },
	{ CCI_WEG8(0x3010), 0x21 },
	{ CCI_WEG8(0x3016), 0x09 },
	{ CCI_WEG8(0x3070), 0x02 },
	{ CCI_WEG8(0x3071), 0x11 },
	{ CCI_WEG8(0x309b), 0x10 },
	{ CCI_WEG8(0x309c), 0x22 },
	{ CCI_WEG8(0x30a2), 0x02 },
	{ CCI_WEG8(0x30a6), 0x20 },
	{ CCI_WEG8(0x30a8), 0x20 },
	{ CCI_WEG8(0x30aa), 0x20 },
	{ CCI_WEG8(0x30ac), 0x20 },
	{ CCI_WEG8(0x30b0), 0x43 },
	{ CCI_WEG8(0x3119), 0x9e },
	{ CCI_WEG8(0x311c), 0x1e },
	{ CCI_WEG8(0x311e), 0x08 },
	{ CCI_WEG8(0x3128), 0x05 },
	{ CCI_WEG8(0x313d), 0x83 },
	{ CCI_WEG8(0x3150), 0x03 },
	{ CCI_WEG8(0x317e), 0x00 },
	{ CCI_WEG8(0x32b8), 0x50 },
	{ CCI_WEG8(0x32b9), 0x10 },
	{ CCI_WEG8(0x32ba), 0x00 },
	{ CCI_WEG8(0x32bb), 0x04 },
	{ CCI_WEG8(0x32c8), 0x50 },
	{ CCI_WEG8(0x32c9), 0x10 },
	{ CCI_WEG8(0x32ca), 0x00 },
	{ CCI_WEG8(0x32cb), 0x04 },
	{ CCI_WEG8(0x332c), 0xd3 },
	{ CCI_WEG8(0x332d), 0x10 },
	{ CCI_WEG8(0x332e), 0x0d },
	{ CCI_WEG8(0x3358), 0x06 },
	{ CCI_WEG8(0x3359), 0xe1 },
	{ CCI_WEG8(0x335a), 0x11 },
	{ CCI_WEG8(0x3360), 0x1e },
	{ CCI_WEG8(0x3361), 0x61 },
	{ CCI_WEG8(0x3362), 0x10 },
	{ CCI_WEG8(0x33b0), 0x50 },
	{ CCI_WEG8(0x33b2), 0x1a },
	{ CCI_WEG8(0x33b3), 0x04 },
};

#define IMX290_NUM_CWK_WEGS	2
static const stwuct cci_weg_sequence xcwk_wegs[][IMX290_NUM_CWK_WEGS] = {
	[IMX290_CWK_37_125] = {
		{ IMX290_EXTCK_FWEQ, (37125 * 256) / 1000 },
		{ IMX290_INCKSEW7, 0x49 },
	},
	[IMX290_CWK_74_25] = {
		{ IMX290_EXTCK_FWEQ, (74250 * 256) / 1000 },
		{ IMX290_INCKSEW7, 0x92 },
	},
};

static const stwuct cci_weg_sequence imx290_gwobaw_init_settings_327[] = {
	{ CCI_WEG8(0x309e), 0x4A },
	{ CCI_WEG8(0x309f), 0x4A },
	{ CCI_WEG8(0x313b), 0x61 },
};

static const stwuct cci_weg_sequence imx290_1080p_settings[] = {
	/* mode settings */
	{ IMX290_WINWV_OB, 12 },
	{ IMX290_OPB_SIZE_V, 10 },
	{ IMX290_X_OUT_SIZE, 1920 },
	{ IMX290_Y_OUT_SIZE, 1080 },
};

static const stwuct cci_weg_sequence imx290_720p_settings[] = {
	/* mode settings */
	{ IMX290_WINWV_OB, 6 },
	{ IMX290_OPB_SIZE_V, 4 },
	{ IMX290_X_OUT_SIZE, 1280 },
	{ IMX290_Y_OUT_SIZE, 720 },
};

static const stwuct cci_weg_sequence imx290_10bit_settings[] = {
	{ IMX290_ADBIT, IMX290_ADBIT_10BIT },
	{ IMX290_OUT_CTWW, IMX290_ODBIT_10BIT },
	{ IMX290_ADBIT1, IMX290_ADBIT1_10BIT },
	{ IMX290_ADBIT2, IMX290_ADBIT2_10BIT },
	{ IMX290_ADBIT3, IMX290_ADBIT3_10BIT },
	{ IMX290_CSI_DT_FMT, IMX290_CSI_DT_FMT_WAW10 },
};

static const stwuct cci_weg_sequence imx290_12bit_settings[] = {
	{ IMX290_ADBIT, IMX290_ADBIT_12BIT },
	{ IMX290_OUT_CTWW, IMX290_ODBIT_12BIT },
	{ IMX290_ADBIT1, IMX290_ADBIT1_12BIT },
	{ IMX290_ADBIT2, IMX290_ADBIT2_12BIT },
	{ IMX290_ADBIT3, IMX290_ADBIT3_12BIT },
	{ IMX290_CSI_DT_FMT, IMX290_CSI_DT_FMT_WAW12 },
};

static const stwuct imx290_csi_cfg imx290_csi_222_75mhz = {
	/* 222.75MHz ow 445.5Mbit/s pew wane */
	.wepetition = 0x10,
	.tcwkpost = 87,
	.thszewo = 55,
	.thspwepawe = 31,
	.tcwktwaiw = 31,
	.thstwaiw = 31,
	.tcwkzewo = 119,
	.tcwkpwepawe = 31,
	.twpx = 23,
};

static const stwuct imx290_csi_cfg imx290_csi_445_5mhz = {
	/* 445.5MHz ow 891Mbit/s pew wane */
	.wepetition = 0x00,
	.tcwkpost = 119,
	.thszewo = 103,
	.thspwepawe = 71,
	.tcwktwaiw = 55,
	.thstwaiw = 63,
	.tcwkzewo = 255,
	.tcwkpwepawe = 63,
	.twpx = 55,
};

static const stwuct imx290_csi_cfg imx290_csi_148_5mhz = {
	/* 148.5MHz ow 297Mbit/s pew wane */
	.wepetition = 0x10,
	.tcwkpost = 79,
	.thszewo = 47,
	.thspwepawe = 23,
	.tcwktwaiw = 23,
	.thstwaiw = 23,
	.tcwkzewo = 87,
	.tcwkpwepawe = 23,
	.twpx = 23,
};

static const stwuct imx290_csi_cfg imx290_csi_297mhz = {
	/* 297MHz ow 594Mbit/s pew wane */
	.wepetition = 0x00,
	.tcwkpost = 103,
	.thszewo = 87,
	.thspwepawe = 47,
	.tcwktwaiw = 39,
	.thstwaiw = 47,
	.tcwkzewo = 191,
	.tcwkpwepawe = 47,
	.twpx = 39,
};

/* suppowted wink fwequencies */
#define FWEQ_INDEX_1080P	0
#define FWEQ_INDEX_720P		1
static const s64 imx290_wink_fweq_2wanes[] = {
	[FWEQ_INDEX_1080P] = 445500000,
	[FWEQ_INDEX_720P] = 297000000,
};

static const s64 imx290_wink_fweq_4wanes[] = {
	[FWEQ_INDEX_1080P] = 222750000,
	[FWEQ_INDEX_720P] = 148500000,
};

/*
 * In this function and in the simiwaw ones bewow We wewy on imx290_pwobe()
 * to ensuwe that nwanes is eithew 2 ow 4.
 */
static inwine const s64 *imx290_wink_fweqs_ptw(const stwuct imx290 *imx290)
{
	if (imx290->nwanes == 2)
		wetuwn imx290_wink_fweq_2wanes;
	ewse
		wetuwn imx290_wink_fweq_4wanes;
}

static inwine int imx290_wink_fweqs_num(const stwuct imx290 *imx290)
{
	if (imx290->nwanes == 2)
		wetuwn AWWAY_SIZE(imx290_wink_fweq_2wanes);
	ewse
		wetuwn AWWAY_SIZE(imx290_wink_fweq_4wanes);
}

static const stwuct imx290_cwk_cfg imx290_1080p_cwock_config[] = {
	[IMX290_CWK_37_125] = {
		/* 37.125MHz cwock config */
		.incksew1 = 0x18,
		.incksew2 = 0x03,
		.incksew3 = 0x20,
		.incksew4 = 0x01,
		.incksew5 = 0x1a,
		.incksew6 = 0x1a,
	},
	[IMX290_CWK_74_25] = {
		/* 74.25MHz cwock config */
		.incksew1 = 0x0c,
		.incksew2 = 0x03,
		.incksew3 = 0x10,
		.incksew4 = 0x01,
		.incksew5 = 0x1b,
		.incksew6 = 0x1b,
	},
};

static const stwuct imx290_cwk_cfg imx290_720p_cwock_config[] = {
	[IMX290_CWK_37_125] = {
		/* 37.125MHz cwock config */
		.incksew1 = 0x20,
		.incksew2 = 0x00,
		.incksew3 = 0x20,
		.incksew4 = 0x01,
		.incksew5 = 0x1a,
		.incksew6 = 0x1a,
	},
	[IMX290_CWK_74_25] = {
		/* 74.25MHz cwock config */
		.incksew1 = 0x10,
		.incksew2 = 0x00,
		.incksew3 = 0x10,
		.incksew4 = 0x01,
		.incksew5 = 0x1b,
		.incksew6 = 0x1b,
	},
};

/* Mode configs */
static const stwuct imx290_mode imx290_modes_2wanes[] = {
	{
		.width = 1920,
		.height = 1080,
		.hmax_min = 2200,
		.vmax_min = 1125,
		.wink_fweq_index = FWEQ_INDEX_1080P,
		.ctww_07 = IMX290_WINMODE_1080P,
		.data = imx290_1080p_settings,
		.data_size = AWWAY_SIZE(imx290_1080p_settings),
		.cwk_cfg = imx290_1080p_cwock_config,
	},
	{
		.width = 1280,
		.height = 720,
		.hmax_min = 3300,
		.vmax_min = 750,
		.wink_fweq_index = FWEQ_INDEX_720P,
		.ctww_07 = IMX290_WINMODE_720P,
		.data = imx290_720p_settings,
		.data_size = AWWAY_SIZE(imx290_720p_settings),
		.cwk_cfg = imx290_720p_cwock_config,
	},
};

static const stwuct imx290_mode imx290_modes_4wanes[] = {
	{
		.width = 1920,
		.height = 1080,
		.hmax_min = 2200,
		.vmax_min = 1125,
		.wink_fweq_index = FWEQ_INDEX_1080P,
		.ctww_07 = IMX290_WINMODE_1080P,
		.data = imx290_1080p_settings,
		.data_size = AWWAY_SIZE(imx290_1080p_settings),
		.cwk_cfg = imx290_1080p_cwock_config,
	},
	{
		.width = 1280,
		.height = 720,
		.hmax_min = 3300,
		.vmax_min = 750,
		.wink_fweq_index = FWEQ_INDEX_720P,
		.ctww_07 = IMX290_WINMODE_720P,
		.data = imx290_720p_settings,
		.data_size = AWWAY_SIZE(imx290_720p_settings),
		.cwk_cfg = imx290_720p_cwock_config,
	},
};

static inwine const stwuct imx290_mode *imx290_modes_ptw(const stwuct imx290 *imx290)
{
	if (imx290->nwanes == 2)
		wetuwn imx290_modes_2wanes;
	ewse
		wetuwn imx290_modes_4wanes;
}

static inwine int imx290_modes_num(const stwuct imx290 *imx290)
{
	if (imx290->nwanes == 2)
		wetuwn AWWAY_SIZE(imx290_modes_2wanes);
	ewse
		wetuwn AWWAY_SIZE(imx290_modes_4wanes);
}

stwuct imx290_fowmat_info {
	u32 code[IMX290_VAWIANT_MAX];
	u8 bpp;
	const stwuct cci_weg_sequence *wegs;
	unsigned int num_wegs;
};

static const stwuct imx290_fowmat_info imx290_fowmats[] = {
	{
		.code = {
			[IMX290_VAWIANT_COWOUW] = MEDIA_BUS_FMT_SWGGB10_1X10,
			[IMX290_VAWIANT_MONO] = MEDIA_BUS_FMT_Y10_1X10
		},
		.bpp = 10,
		.wegs = imx290_10bit_settings,
		.num_wegs = AWWAY_SIZE(imx290_10bit_settings),
	}, {
		.code = {
			[IMX290_VAWIANT_COWOUW] = MEDIA_BUS_FMT_SWGGB12_1X12,
			[IMX290_VAWIANT_MONO] = MEDIA_BUS_FMT_Y12_1X12
		},
		.bpp = 12,
		.wegs = imx290_12bit_settings,
		.num_wegs = AWWAY_SIZE(imx290_12bit_settings),
	}
};

static const stwuct imx290_fowmat_info *
imx290_fowmat_info(const stwuct imx290 *imx290, u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(imx290_fowmats); ++i) {
		const stwuct imx290_fowmat_info *info = &imx290_fowmats[i];

		if (info->code[imx290->modew->cowouw_vawiant] == code)
			wetuwn info;
	}

	wetuwn NUWW;
}

static int imx290_set_wegistew_awway(stwuct imx290 *imx290,
				     const stwuct cci_weg_sequence *settings,
				     unsigned int num_settings)
{
	int wet;

	wet = cci_muwti_weg_wwite(imx290->wegmap, settings, num_settings, NUWW);
	if (wet < 0)
		wetuwn wet;

	/* Pwovide 10ms settwe time */
	usweep_wange(10000, 11000);

	wetuwn 0;
}

static int imx290_set_cwock(stwuct imx290 *imx290)
{
	const stwuct imx290_mode *mode = imx290->cuwwent_mode;
	enum imx290_cwk_fweq cwk_idx = imx290->xcwk_idx;
	const stwuct imx290_cwk_cfg *cwk_cfg = &mode->cwk_cfg[cwk_idx];
	int wet;

	wet = imx290_set_wegistew_awway(imx290, xcwk_wegs[cwk_idx],
					IMX290_NUM_CWK_WEGS);

	cci_wwite(imx290->wegmap, IMX290_INCKSEW1, cwk_cfg->incksew1, &wet);
	cci_wwite(imx290->wegmap, IMX290_INCKSEW2, cwk_cfg->incksew2, &wet);
	cci_wwite(imx290->wegmap, IMX290_INCKSEW3, cwk_cfg->incksew3, &wet);
	cci_wwite(imx290->wegmap, IMX290_INCKSEW4, cwk_cfg->incksew4, &wet);
	cci_wwite(imx290->wegmap, IMX290_INCKSEW5, cwk_cfg->incksew5, &wet);
	cci_wwite(imx290->wegmap, IMX290_INCKSEW6, cwk_cfg->incksew6, &wet);

	wetuwn wet;
}

static int imx290_set_data_wanes(stwuct imx290 *imx290)
{
	int wet = 0;

	cci_wwite(imx290->wegmap, IMX290_PHY_WANE_NUM, imx290->nwanes - 1,
		  &wet);
	cci_wwite(imx290->wegmap, IMX290_CSI_WANE_MODE, imx290->nwanes - 1,
		  &wet);
	cci_wwite(imx290->wegmap, IMX290_FW_FDG_SEW, 0x01, &wet);

	wetuwn wet;
}

static int imx290_set_bwack_wevew(stwuct imx290 *imx290,
				  const stwuct v4w2_mbus_fwamefmt *fowmat,
				  unsigned int bwack_wevew, int *eww)
{
	unsigned int bpp = imx290_fowmat_info(imx290, fowmat->code)->bpp;

	wetuwn cci_wwite(imx290->wegmap, IMX290_BWKWEVEW,
			 bwack_wevew >> (16 - bpp), eww);
}

static int imx290_set_csi_config(stwuct imx290 *imx290)
{
	const s64 *wink_fweqs = imx290_wink_fweqs_ptw(imx290);
	const stwuct imx290_csi_cfg *csi_cfg;
	int wet = 0;

	switch (wink_fweqs[imx290->cuwwent_mode->wink_fweq_index]) {
	case 445500000:
		csi_cfg = &imx290_csi_445_5mhz;
		bweak;
	case 297000000:
		csi_cfg = &imx290_csi_297mhz;
		bweak;
	case 222750000:
		csi_cfg = &imx290_csi_222_75mhz;
		bweak;
	case 148500000:
		csi_cfg = &imx290_csi_148_5mhz;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cci_wwite(imx290->wegmap, IMX290_WEPETITION, csi_cfg->wepetition, &wet);
	cci_wwite(imx290->wegmap, IMX290_TCWKPOST, csi_cfg->tcwkpost, &wet);
	cci_wwite(imx290->wegmap, IMX290_THSZEWO, csi_cfg->thszewo, &wet);
	cci_wwite(imx290->wegmap, IMX290_THSPWEPAWE, csi_cfg->thspwepawe, &wet);
	cci_wwite(imx290->wegmap, IMX290_TCWKTWAIW, csi_cfg->tcwktwaiw, &wet);
	cci_wwite(imx290->wegmap, IMX290_THSTWAIW, csi_cfg->thstwaiw, &wet);
	cci_wwite(imx290->wegmap, IMX290_TCWKZEWO, csi_cfg->tcwkzewo, &wet);
	cci_wwite(imx290->wegmap, IMX290_TCWKPWEPAWE, csi_cfg->tcwkpwepawe,
		  &wet);
	cci_wwite(imx290->wegmap, IMX290_TWPX, csi_cfg->twpx, &wet);

	wetuwn wet;
}

static int imx290_setup_fowmat(stwuct imx290 *imx290,
			       const stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct imx290_fowmat_info *info;
	int wet;

	info = imx290_fowmat_info(imx290, fowmat->code);

	wet = imx290_set_wegistew_awway(imx290, info->wegs, info->num_wegs);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set fowmat wegistews\n");
		wetuwn wet;
	}

	wetuwn imx290_set_bwack_wevew(imx290, fowmat,
				      IMX290_BWACK_WEVEW_DEFAUWT, &wet);
}

/* ----------------------------------------------------------------------------
 * Contwows
 */
static void imx290_exposuwe_update(stwuct imx290 *imx290,
				   const stwuct imx290_mode *mode)
{
	unsigned int exposuwe_max;

	exposuwe_max = imx290->vbwank->vaw + mode->height -
		       IMX290_EXPOSUWE_OFFSET;
	__v4w2_ctww_modify_wange(imx290->exposuwe, 1, exposuwe_max, 1,
				 exposuwe_max);
}

static int imx290_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct imx290 *imx290 = containew_of(ctww->handwew,
					     stwuct imx290, ctwws);
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_subdev_state *state;
	int wet = 0, vmax;

	/*
	 * Wetuwn immediatewy fow contwows that don't need to be appwied to the
	 * device.
	 */
	if (ctww->fwags & V4W2_CTWW_FWAG_WEAD_ONWY)
		wetuwn 0;

	if (ctww->id == V4W2_CID_VBWANK) {
		/* Changing vbwank changes the awwowed wange fow exposuwe. */
		imx290_exposuwe_update(imx290, imx290->cuwwent_mode);
	}

	/* V4W2 contwows vawues wiww be appwied onwy when powew is awweady up */
	if (!pm_wuntime_get_if_in_use(imx290->dev))
		wetuwn 0;

	state = v4w2_subdev_get_wocked_active_state(&imx290->sd);
	fowmat = v4w2_subdev_state_get_fowmat(state, 0);

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = cci_wwite(imx290->wegmap, IMX290_GAIN, ctww->vaw, NUWW);
		bweak;

	case V4W2_CID_VBWANK:
		wet = cci_wwite(imx290->wegmap, IMX290_VMAX,
				ctww->vaw + imx290->cuwwent_mode->height, NUWW);
		/*
		 * Due to the way that exposuwe is pwogwammed in this sensow in
		 * wewation to VMAX, we have to wepwogwamme it whenevew VMAX is
		 * changed.
		 * Update ctww so that the V4W2_CID_EXPOSUWE case can wefew to
		 * it.
		 */
		ctww = imx290->exposuwe;
		fawwthwough;
	case V4W2_CID_EXPOSUWE:
		vmax = imx290->vbwank->vaw + imx290->cuwwent_mode->height;
		wet = cci_wwite(imx290->wegmap, IMX290_SHS1,
				vmax - ctww->vaw - 1, NUWW);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		if (ctww->vaw) {
			imx290_set_bwack_wevew(imx290, fowmat, 0, &wet);
			usweep_wange(10000, 11000);
			cci_wwite(imx290->wegmap, IMX290_PGCTWW,
				  (u8)(IMX290_PGCTWW_WEGEN |
				       IMX290_PGCTWW_THWU |
				       IMX290_PGCTWW_MODE(ctww->vaw)), &wet);
		} ewse {
			cci_wwite(imx290->wegmap, IMX290_PGCTWW, 0x00, &wet);
			usweep_wange(10000, 11000);
			imx290_set_bwack_wevew(imx290, fowmat,
					       IMX290_BWACK_WEVEW_DEFAUWT, &wet);
		}
		bweak;

	case V4W2_CID_HBWANK:
		wet = cci_wwite(imx290->wegmap, IMX290_HMAX,
				ctww->vaw + imx290->cuwwent_mode->width, NUWW);
		bweak;

	case V4W2_CID_HFWIP:
	case V4W2_CID_VFWIP:
	{
		u32 weg;

		weg = imx290->cuwwent_mode->ctww_07;
		if (imx290->hfwip->vaw)
			weg |= IMX290_HWEVEWSE;
		if (imx290->vfwip->vaw)
			weg |= IMX290_VWEVEWSE;
		wet = cci_wwite(imx290->wegmap, IMX290_CTWW_07, weg, NUWW);
		bweak;
	}

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_mawk_wast_busy(imx290->dev);
	pm_wuntime_put_autosuspend(imx290->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops imx290_ctww_ops = {
	.s_ctww = imx290_set_ctww,
};

static const chaw * const imx290_test_pattewn_menu[] = {
	"Disabwed",
	"Sequence Pattewn 1",
	"Howizontaw Cowow-baw Chawt",
	"Vewticaw Cowow-baw Chawt",
	"Sequence Pattewn 2",
	"Gwadation Pattewn 1",
	"Gwadation Pattewn 2",
	"000/555h Toggwe Pattewn",
};

static void imx290_ctww_update(stwuct imx290 *imx290,
			       const stwuct imx290_mode *mode)
{
	unsigned int hbwank_min = mode->hmax_min - mode->width;
	unsigned int hbwank_max = IMX290_HMAX_MAX - mode->width;
	unsigned int vbwank_min = mode->vmax_min - mode->height;
	unsigned int vbwank_max = IMX290_VMAX_MAX - mode->height;

	__v4w2_ctww_s_ctww(imx290->wink_fweq, mode->wink_fweq_index);

	__v4w2_ctww_modify_wange(imx290->hbwank, hbwank_min, hbwank_max, 1,
				 hbwank_min);
	__v4w2_ctww_modify_wange(imx290->vbwank, vbwank_min, vbwank_max, 1,
				 vbwank_min);
}

static int imx290_ctww_init(stwuct imx290 *imx290)
{
	stwuct v4w2_fwnode_device_pwopewties pwops;
	int wet;

	wet = v4w2_fwnode_device_pawse(imx290->dev, &pwops);
	if (wet < 0)
		wetuwn wet;

	v4w2_ctww_handwew_init(&imx290->ctwws, 11);

	/*
	 * The sensow has an anawog gain and a digitaw gain, both contwowwed
	 * thwough a singwe gain vawue, expwessed in 0.3dB incwements. Vawues
	 * fwom 0.0dB (0) to 30.0dB (100) appwy anawog gain onwy, highew vawues
	 * up to 72.0dB (240) add fuwthew digitaw gain. Wimit the wange to
	 * anawog gain onwy, suppowt fow digitaw gain can be added sepawatewy
	 * if needed.
	 *
	 * The IMX327 and IMX462 awe wawgewy compatibwe with the IMX290, but
	 * have an anawog gain wange of 0.0dB to 29.4dB and 42dB of digitaw
	 * gain. When suppowt fow those sensows gets added to the dwivew, the
	 * gain contwow shouwd be adjusted accowdingwy.
	 */
	v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops,
			  V4W2_CID_ANAWOGUE_GAIN, 0, 100, 1, 0);

	/*
	 * Cowwect wange wiww be detewmined thwough imx290_ctww_update setting
	 * V4W2_CID_VBWANK.
	 */
	imx290->exposuwe = v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops,
					     V4W2_CID_EXPOSUWE, 1, 65535, 1,
					     65535);

	/*
	 * Set the wink fwequency, pixew wate, howizontaw bwanking and vewticaw
	 * bwanking to hawdcoded vawues, they wiww be updated by
	 * imx290_ctww_update().
	 */
	imx290->wink_fweq =
		v4w2_ctww_new_int_menu(&imx290->ctwws, &imx290_ctww_ops,
				       V4W2_CID_WINK_FWEQ,
				       imx290_wink_fweqs_num(imx290) - 1, 0,
				       imx290_wink_fweqs_ptw(imx290));
	if (imx290->wink_fweq)
		imx290->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops, V4W2_CID_PIXEW_WATE,
			  IMX290_PIXEW_WATE, IMX290_PIXEW_WATE, 1,
			  IMX290_PIXEW_WATE);

	v4w2_ctww_new_std_menu_items(&imx290->ctwws, &imx290_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(imx290_test_pattewn_menu) - 1,
				     0, 0, imx290_test_pattewn_menu);

	/*
	 * Actuaw wange wiww be set fwom imx290_ctww_update watew in the pwobe.
	 */
	imx290->hbwank = v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops,
					   V4W2_CID_HBWANK, 1, 1, 1, 1);

	imx290->vbwank = v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops,
					   V4W2_CID_VBWANK, 1, 1, 1, 1);

	imx290->hfwip = v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops,
					  V4W2_CID_HFWIP, 0, 1, 1, 0);
	imx290->vfwip = v4w2_ctww_new_std(&imx290->ctwws, &imx290_ctww_ops,
					  V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_cwustew(2, &imx290->hfwip);

	v4w2_ctww_new_fwnode_pwopewties(&imx290->ctwws, &imx290_ctww_ops,
					&pwops);

	imx290->sd.ctww_handwew = &imx290->ctwws;

	if (imx290->ctwws.ewwow) {
		wet = imx290->ctwws.ewwow;
		v4w2_ctww_handwew_fwee(&imx290->ctwws);
		wetuwn wet;
	}

	wetuwn 0;
}

/* ----------------------------------------------------------------------------
 * Subdev opewations
 */

/* Stawt stweaming */
static int imx290_stawt_stweaming(stwuct imx290 *imx290,
				  stwuct v4w2_subdev_state *state)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet;

	/* Set init wegistew settings */
	wet = imx290_set_wegistew_awway(imx290, imx290_gwobaw_init_settings,
					AWWAY_SIZE(imx290_gwobaw_init_settings));
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set init wegistews\n");
		wetuwn wet;
	}

	/* Set mdew specific init wegistew settings */
	wet = imx290_set_wegistew_awway(imx290, imx290->modew->init_wegs,
					imx290->modew->init_wegs_num);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set modew specific init wegistews\n");
		wetuwn wet;
	}

	/* Set cwock pawametews based on mode and xcwk */
	wet = imx290_set_cwock(imx290);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set cwocks - %d\n", wet);
		wetuwn wet;
	}

	/* Set data wane count */
	wet = imx290_set_data_wanes(imx290);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set data wanes - %d\n", wet);
		wetuwn wet;
	}

	wet = imx290_set_csi_config(imx290);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set csi cfg - %d\n", wet);
		wetuwn wet;
	}

	/* Appwy the wegistew vawues wewated to cuwwent fwame fowmat */
	fowmat = v4w2_subdev_state_get_fowmat(state, 0);
	wet = imx290_setup_fowmat(imx290, fowmat);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set fwame fowmat - %d\n", wet);
		wetuwn wet;
	}

	/* Appwy defauwt vawues of cuwwent mode */
	wet = imx290_set_wegistew_awway(imx290, imx290->cuwwent_mode->data,
					imx290->cuwwent_mode->data_size);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not set cuwwent mode - %d\n", wet);
		wetuwn wet;
	}

	/* Appwy customized vawues fwom usew */
	wet = __v4w2_ctww_handwew_setup(imx290->sd.ctww_handwew);
	if (wet) {
		dev_eww(imx290->dev, "Couwd not sync v4w2 contwows - %d\n", wet);
		wetuwn wet;
	}

	cci_wwite(imx290->wegmap, IMX290_STANDBY, 0x00, &wet);

	msweep(30);

	/* Stawt stweaming */
	wetuwn cci_wwite(imx290->wegmap, IMX290_XMSTA, 0x00, &wet);
}

/* Stop stweaming */
static int imx290_stop_stweaming(stwuct imx290 *imx290)
{
	int wet = 0;

	cci_wwite(imx290->wegmap, IMX290_STANDBY, 0x01, &wet);

	msweep(30);

	wetuwn cci_wwite(imx290->wegmap, IMX290_XMSTA, 0x01, &wet);
}

static int imx290_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct imx290 *imx290 = to_imx290(sd);
	stwuct v4w2_subdev_state *state;
	int wet = 0;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(imx290->dev);
		if (wet < 0)
			goto unwock;

		wet = imx290_stawt_stweaming(imx290, state);
		if (wet) {
			dev_eww(imx290->dev, "Stawt stweam faiwed\n");
			pm_wuntime_put_sync(imx290->dev);
			goto unwock;
		}
	} ewse {
		imx290_stop_stweaming(imx290);
		pm_wuntime_mawk_wast_busy(imx290->dev);
		pm_wuntime_put_autosuspend(imx290->dev);
	}

	/*
	 * vfwip and hfwip shouwd not be changed duwing stweaming as the sensow
	 * wiww pwoduce an invawid fwame.
	 */
	__v4w2_ctww_gwab(imx290->vfwip, enabwe);
	__v4w2_ctww_gwab(imx290->hfwip, enabwe);

unwock:
	v4w2_subdev_unwock_state(state);
	wetuwn wet;
}

static int imx290_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	const stwuct imx290 *imx290 = to_imx290(sd);

	if (code->index >= AWWAY_SIZE(imx290_fowmats))
		wetuwn -EINVAW;

	code->code = imx290_fowmats[code->index].code[imx290->modew->cowouw_vawiant];

	wetuwn 0;
}

static int imx290_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	const stwuct imx290 *imx290 = to_imx290(sd);
	const stwuct imx290_mode *imx290_modes = imx290_modes_ptw(imx290);

	if (!imx290_fowmat_info(imx290, fse->code))
		wetuwn -EINVAW;

	if (fse->index >= imx290_modes_num(imx290))
		wetuwn -EINVAW;

	fse->min_width = imx290_modes[fse->index].width;
	fse->max_width = imx290_modes[fse->index].width;
	fse->min_height = imx290_modes[fse->index].height;
	fse->max_height = imx290_modes[fse->index].height;

	wetuwn 0;
}

static int imx290_set_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx290 *imx290 = to_imx290(sd);
	const stwuct imx290_mode *mode;
	stwuct v4w2_mbus_fwamefmt *fowmat;

	mode = v4w2_find_neawest_size(imx290_modes_ptw(imx290),
				      imx290_modes_num(imx290), width, height,
				      fmt->fowmat.width, fmt->fowmat.height);

	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;

	if (!imx290_fowmat_info(imx290, fmt->fowmat.code))
		fmt->fowmat.code = imx290_fowmats[0].code[imx290->modew->cowouw_vawiant];

	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
	fmt->fowmat.cowowspace = V4W2_COWOWSPACE_WAW;
	fmt->fowmat.ycbcw_enc = V4W2_YCBCW_ENC_601;
	fmt->fowmat.quantization = V4W2_QUANTIZATION_FUWW_WANGE;
	fmt->fowmat.xfew_func = V4W2_XFEW_FUNC_NONE;

	fowmat = v4w2_subdev_state_get_fowmat(sd_state, 0);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		imx290->cuwwent_mode = mode;

		imx290_ctww_update(imx290, mode);
		imx290_exposuwe_update(imx290, mode);
	}

	*fowmat = fmt->fowmat;

	wetuwn 0;
}

static int imx290_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct imx290 *imx290 = to_imx290(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP: {
		fowmat = v4w2_subdev_state_get_fowmat(sd_state, 0);

		/*
		 * The sensow moves the weadout by 1 pixew based on fwips to
		 * keep the Bayew owdew the same.
		 */
		sew->w.top = IMX920_PIXEW_AWWAY_MAWGIN_TOP
			   + (IMX290_PIXEW_AWWAY_WECOWDING_HEIGHT - fowmat->height) / 2
			   + imx290->vfwip->vaw;
		sew->w.weft = IMX920_PIXEW_AWWAY_MAWGIN_WEFT
			    + (IMX290_PIXEW_AWWAY_WECOWDING_WIDTH - fowmat->width) / 2
			    + imx290->hfwip->vaw;
		sew->w.width = fowmat->width;
		sew->w.height = fowmat->height;

		wetuwn 0;
	}

	case V4W2_SEW_TGT_NATIVE_SIZE:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = IMX290_PIXEW_AWWAY_WIDTH;
		sew->w.height = IMX290_PIXEW_AWWAY_HEIGHT;

		wetuwn 0;

	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = IMX920_PIXEW_AWWAY_MAWGIN_TOP;
		sew->w.weft = IMX920_PIXEW_AWWAY_MAWGIN_WEFT;
		sew->w.width = IMX290_PIXEW_AWWAY_WECOWDING_WIDTH;
		sew->w.height = IMX290_PIXEW_AWWAY_WECOWDING_HEIGHT;

		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int imx290_entity_init_state(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
		.fowmat = {
			.width = 1920,
			.height = 1080,
		},
	};

	imx290_set_fmt(subdev, sd_state, &fmt);

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops imx290_cowe_ops = {
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_video_ops imx290_video_ops = {
	.s_stweam = imx290_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops imx290_pad_ops = {
	.enum_mbus_code = imx290_enum_mbus_code,
	.enum_fwame_size = imx290_enum_fwame_size,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = imx290_set_fmt,
	.get_sewection = imx290_get_sewection,
};

static const stwuct v4w2_subdev_ops imx290_subdev_ops = {
	.cowe = &imx290_cowe_ops,
	.video = &imx290_video_ops,
	.pad = &imx290_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops imx290_intewnaw_ops = {
	.init_state = imx290_entity_init_state,
};

static const stwuct media_entity_opewations imx290_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int imx290_subdev_init(stwuct imx290 *imx290)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(imx290->dev);
	stwuct v4w2_subdev_state *state;
	int wet;

	imx290->cuwwent_mode = &imx290_modes_ptw(imx290)[0];

	v4w2_i2c_subdev_init(&imx290->sd, cwient, &imx290_subdev_ops);
	imx290->sd.intewnaw_ops = &imx290_intewnaw_ops;
	imx290->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
			    V4W2_SUBDEV_FW_HAS_EVENTS;
	imx290->sd.dev = imx290->dev;
	imx290->sd.entity.ops = &imx290_subdev_entity_ops;
	imx290->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	imx290->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&imx290->sd.entity, 1, &imx290->pad);
	if (wet < 0) {
		dev_eww(imx290->dev, "Couwd not wegistew media entity\n");
		wetuwn wet;
	}

	wet = imx290_ctww_init(imx290);
	if (wet < 0) {
		dev_eww(imx290->dev, "Contwow initiawization ewwow %d\n", wet);
		goto eww_media;
	}

	imx290->sd.state_wock = imx290->ctwws.wock;

	wet = v4w2_subdev_init_finawize(&imx290->sd);
	if (wet < 0) {
		dev_eww(imx290->dev, "subdev initiawization ewwow %d\n", wet);
		goto eww_ctwws;
	}

	state = v4w2_subdev_wock_and_get_active_state(&imx290->sd);
	imx290_ctww_update(imx290, imx290->cuwwent_mode);
	v4w2_subdev_unwock_state(state);

	wetuwn 0;

eww_ctwws:
	v4w2_ctww_handwew_fwee(&imx290->ctwws);
eww_media:
	media_entity_cweanup(&imx290->sd.entity);
	wetuwn wet;
}

static void imx290_subdev_cweanup(stwuct imx290 *imx290)
{
	v4w2_subdev_cweanup(&imx290->sd);
	media_entity_cweanup(&imx290->sd.entity);
	v4w2_ctww_handwew_fwee(&imx290->ctwws);
}

/* ----------------------------------------------------------------------------
 * Powew management
 */

static int imx290_powew_on(stwuct imx290 *imx290)
{
	int wet;

	wet = cwk_pwepawe_enabwe(imx290->xcwk);
	if (wet) {
		dev_eww(imx290->dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(imx290->suppwies),
				    imx290->suppwies);
	if (wet) {
		dev_eww(imx290->dev, "Faiwed to enabwe weguwatows\n");
		cwk_disabwe_unpwepawe(imx290->xcwk);
		wetuwn wet;
	}

	usweep_wange(1, 2);
	gpiod_set_vawue_cansweep(imx290->wst_gpio, 0);
	usweep_wange(30000, 31000);

	wetuwn 0;
}

static void imx290_powew_off(stwuct imx290 *imx290)
{
	cwk_disabwe_unpwepawe(imx290->xcwk);
	gpiod_set_vawue_cansweep(imx290->wst_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(imx290->suppwies), imx290->suppwies);
}

static int imx290_wuntime_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx290 *imx290 = to_imx290(sd);

	wetuwn imx290_powew_on(imx290);
}

static int imx290_wuntime_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx290 *imx290 = to_imx290(sd);

	imx290_powew_off(imx290);

	wetuwn 0;
}

static const stwuct dev_pm_ops imx290_pm_ops = {
	WUNTIME_PM_OPS(imx290_wuntime_suspend, imx290_wuntime_wesume, NUWW)
};

/* ----------------------------------------------------------------------------
 * Pwobe & wemove
 */

static const chaw * const imx290_suppwy_name[IMX290_NUM_SUPPWIES] = {
	"vdda",
	"vddd",
	"vdddo",
};

static int imx290_get_weguwatows(stwuct device *dev, stwuct imx290 *imx290)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(imx290->suppwies); i++)
		imx290->suppwies[i].suppwy = imx290_suppwy_name[i];

	wetuwn devm_weguwatow_buwk_get(dev, AWWAY_SIZE(imx290->suppwies),
				       imx290->suppwies);
}

static int imx290_init_cwk(stwuct imx290 *imx290)
{
	u32 xcwk_fweq;
	int wet;

	wet = device_pwopewty_wead_u32(imx290->dev, "cwock-fwequency",
				       &xcwk_fweq);
	if (wet) {
		dev_eww(imx290->dev, "Couwd not get xcwk fwequency\n");
		wetuwn wet;
	}

	/* extewnaw cwock must be 37.125 MHz ow 74.25MHz */
	switch (xcwk_fweq) {
	case 37125000:
		imx290->xcwk_idx = IMX290_CWK_37_125;
		bweak;
	case 74250000:
		imx290->xcwk_idx = IMX290_CWK_74_25;
		bweak;
	defauwt:
		dev_eww(imx290->dev, "Extewnaw cwock fwequency %u is not suppowted\n",
			xcwk_fweq);
		wetuwn -EINVAW;
	}

	wet = cwk_set_wate(imx290->xcwk, xcwk_fweq);
	if (wet) {
		dev_eww(imx290->dev, "Couwd not set xcwk fwequency\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wetuwns 0 if aww wink fwequencies used by the dwivew fow the given numbew
 * of MIPI data wanes awe mentioned in the device twee, ow the vawue of the
 * fiwst missing fwequency othewwise.
 */
static s64 imx290_check_wink_fweqs(const stwuct imx290 *imx290,
				   const stwuct v4w2_fwnode_endpoint *ep)
{
	int i, j;
	const s64 *fweqs = imx290_wink_fweqs_ptw(imx290);
	int fweqs_count = imx290_wink_fweqs_num(imx290);

	fow (i = 0; i < fweqs_count; i++) {
		fow (j = 0; j < ep->nw_of_wink_fwequencies; j++)
			if (fweqs[i] == ep->wink_fwequencies[j])
				bweak;
		if (j == ep->nw_of_wink_fwequencies)
			wetuwn fweqs[i];
	}
	wetuwn 0;
}

static const stwuct imx290_modew_info imx290_modews[] = {
	[IMX290_MODEW_IMX290WQW] = {
		.cowouw_vawiant = IMX290_VAWIANT_COWOUW,
		.init_wegs = imx290_gwobaw_init_settings_290,
		.init_wegs_num = AWWAY_SIZE(imx290_gwobaw_init_settings_290),
		.name = "imx290",
	},
	[IMX290_MODEW_IMX290WWW] = {
		.cowouw_vawiant = IMX290_VAWIANT_MONO,
		.init_wegs = imx290_gwobaw_init_settings_290,
		.init_wegs_num = AWWAY_SIZE(imx290_gwobaw_init_settings_290),
		.name = "imx290",
	},
	[IMX290_MODEW_IMX327WQW] = {
		.cowouw_vawiant = IMX290_VAWIANT_COWOUW,
		.init_wegs = imx290_gwobaw_init_settings_327,
		.init_wegs_num = AWWAY_SIZE(imx290_gwobaw_init_settings_327),
		.name = "imx327",
	},
};

static int imx290_pawse_dt(stwuct imx290 *imx290)
{
	/* Onwy CSI2 is suppowted fow now: */
	stwuct v4w2_fwnode_endpoint ep = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	stwuct fwnode_handwe *endpoint;
	int wet;
	s64 fq;

	imx290->modew = of_device_get_match_data(imx290->dev);

	endpoint = fwnode_gwaph_get_next_endpoint(dev_fwnode(imx290->dev), NUWW);
	if (!endpoint) {
		dev_eww(imx290->dev, "Endpoint node not found\n");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_awwoc_pawse(endpoint, &ep);
	fwnode_handwe_put(endpoint);
	if (wet == -ENXIO) {
		dev_eww(imx290->dev, "Unsuppowted bus type, shouwd be CSI2\n");
		goto done;
	} ewse if (wet) {
		dev_eww(imx290->dev, "Pawsing endpoint node faiwed\n");
		goto done;
	}

	/* Get numbew of data wanes */
	imx290->nwanes = ep.bus.mipi_csi2.num_data_wanes;
	if (imx290->nwanes != 2 && imx290->nwanes != 4) {
		dev_eww(imx290->dev, "Invawid data wanes: %d\n", imx290->nwanes);
		wet = -EINVAW;
		goto done;
	}

	dev_dbg(imx290->dev, "Using %u data wanes\n", imx290->nwanes);

	if (!ep.nw_of_wink_fwequencies) {
		dev_eww(imx290->dev, "wink-fwequency pwopewty not found in DT\n");
		wet = -EINVAW;
		goto done;
	}

	/* Check that wink fwequences fow aww the modes awe in device twee */
	fq = imx290_check_wink_fweqs(imx290, &ep);
	if (fq) {
		dev_eww(imx290->dev, "Wink fwequency of %wwd is not suppowted\n",
			fq);
		wet = -EINVAW;
		goto done;
	}

	wet = 0;

done:
	v4w2_fwnode_endpoint_fwee(&ep);
	wetuwn wet;
}

static int imx290_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct imx290 *imx290;
	int wet;

	imx290 = devm_kzawwoc(dev, sizeof(*imx290), GFP_KEWNEW);
	if (!imx290)
		wetuwn -ENOMEM;

	imx290->dev = dev;
	imx290->wegmap = devm_cci_wegmap_init_i2c(cwient, 16);
	if (IS_EWW(imx290->wegmap)) {
		dev_eww(dev, "Unabwe to initiawize I2C\n");
		wetuwn -ENODEV;
	}

	wet = imx290_pawse_dt(imx290);
	if (wet)
		wetuwn wet;

	/* Acquiwe wesouwces. */
	imx290->xcwk = devm_cwk_get(dev, "xcwk");
	if (IS_EWW(imx290->xcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(imx290->xcwk),
				     "Couwd not get xcwk\n");

	wet = imx290_get_weguwatows(dev, imx290);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot get weguwatows\n");

	imx290->wst_gpio = devm_gpiod_get_optionaw(dev, "weset",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(imx290->wst_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(imx290->wst_gpio),
				     "Cannot get weset gpio\n");

	/* Initiawize extewnaw cwock fwequency. */
	wet = imx290_init_cwk(imx290);
	if (wet)
		wetuwn wet;

	/*
	 * Enabwe powew management. The dwivew suppowts wuntime PM, but needs to
	 * wowk when wuntime PM is disabwed in the kewnew. To that end, powew
	 * the sensow on manuawwy hewe.
	 */
	wet = imx290_powew_on(imx290);
	if (wet < 0) {
		dev_eww(dev, "Couwd not powew on the device\n");
		wetuwn wet;
	}

	/*
	 * Enabwe wuntime PM with autosuspend. As the device has been powewed
	 * manuawwy, mawk it as active, and incwease the usage count without
	 * wesuming the device.
	 */
	pm_wuntime_set_active(dev);
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_use_autosuspend(dev);

	/* Initiawize the V4W2 subdev. */
	wet = imx290_subdev_init(imx290);
	if (wet)
		goto eww_pm;

	v4w2_i2c_subdev_set_name(&imx290->sd, cwient,
				 imx290->modew->name, NUWW);

	/*
	 * Finawwy, wegistew the V4W2 subdev. This must be done aftew
	 * initiawizing evewything as the subdev can be used immediatewy aftew
	 * being wegistewed.
	 */
	wet = v4w2_async_wegistew_subdev(&imx290->sd);
	if (wet < 0) {
		dev_eww(dev, "Couwd not wegistew v4w2 device\n");
		goto eww_subdev;
	}

	/*
	 * Decwease the PM usage count. The device wiww get suspended aftew the
	 * autosuspend deway, tuwning the powew off.
	 */
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_subdev:
	imx290_subdev_cweanup(imx290);
eww_pm:
	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
	imx290_powew_off(imx290);
	wetuwn wet;
}

static void imx290_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx290 *imx290 = to_imx290(sd);

	v4w2_async_unwegistew_subdev(sd);
	imx290_subdev_cweanup(imx290);

	/*
	 * Disabwe wuntime PM. In case wuntime PM is disabwed in the kewnew,
	 * make suwe to tuwn powew off manuawwy.
	 */
	pm_wuntime_disabwe(imx290->dev);
	if (!pm_wuntime_status_suspended(imx290->dev))
		imx290_powew_off(imx290);
	pm_wuntime_set_suspended(imx290->dev);
}

static const stwuct of_device_id imx290_of_match[] = {
	{
		/* Depwecated - synonym fow "sony,imx290wqw" */
		.compatibwe = "sony,imx290",
		.data = &imx290_modews[IMX290_MODEW_IMX290WQW],
	}, {
		.compatibwe = "sony,imx290wqw",
		.data = &imx290_modews[IMX290_MODEW_IMX290WQW],
	}, {
		.compatibwe = "sony,imx290www",
		.data = &imx290_modews[IMX290_MODEW_IMX290WWW],
	}, {
		.compatibwe = "sony,imx327wqw",
		.data = &imx290_modews[IMX290_MODEW_IMX327WQW],
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx290_of_match);

static stwuct i2c_dwivew imx290_i2c_dwivew = {
	.pwobe = imx290_pwobe,
	.wemove = imx290_wemove,
	.dwivew = {
		.name = "imx290",
		.pm = pm_ptw(&imx290_pm_ops),
		.of_match_tabwe = imx290_of_match,
	},
};

moduwe_i2c_dwivew(imx290_i2c_dwivew);

MODUWE_DESCWIPTION("Sony IMX290 CMOS Image Sensow Dwivew");
MODUWE_AUTHOW("FWAMOS GmbH");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_WICENSE("GPW v2");
