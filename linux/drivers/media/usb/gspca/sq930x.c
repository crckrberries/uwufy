// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SQ930x subdwivew
 *
 * Copywight (C) 2010 Jean-Fwançois Moine <http://moinejf.fwee.fw>
 * Copywight (C) 2006 -2008 Gewawd Kwavew <gewawd at gkaww dot hobby dot nw>
 * Copywight (C) 2007 Sam Wevitch <samw7@cs.washington.edu>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "sq930x"

#incwude "gspca.h"

MODUWE_AUTHOW("Jean-Fwancois Moine <http://moinejf.fwee.fw>\n"
		"Gewawd Kwavew <gewawd at gkaww dot hobby dot nw\n"
		"Sam Wevitch <samw7@cs.washington.edu>");
MODUWE_DESCWIPTION("GSPCA/SQ930x USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	stwuct { /* exposuwe/gain contwow cwustew */
		stwuct v4w2_ctww *exposuwe;
		stwuct v4w2_ctww *gain;
	};

	u8 do_ctww;
	u8 gpio[2];
	u8 sensow;
	u8 type;
#define Genewic 0
#define Cweative_wive_motion 1
};
enum sensows {
	SENSOW_ICX098BQ,
	SENSOW_WZ24BP,
	SENSOW_MI0360,
	SENSOW_MT9V111,		/* = MI360SOC */
	SENSOW_OV7660,
	SENSOW_OV9630,
};

static stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_SWGGB8, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
	{640, 480, V4W2_PIX_FMT_SWGGB8, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1},
};

/* sq930x wegistews */
#define SQ930_CTWW_UCBUS_IO	0x0001
#define SQ930_CTWW_I2C_IO	0x0002
#define SQ930_CTWW_GPIO		0x0005
#define SQ930_CTWW_CAP_STAWT	0x0010
#define SQ930_CTWW_CAP_STOP	0x0011
#define SQ930_CTWW_SET_EXPOSUWE 0x001d
#define SQ930_CTWW_WESET	0x001e
#define SQ930_CTWW_GET_DEV_INFO 0x001f

/* gpio 1 (8..15) */
#define SQ930_GPIO_DFW_I2C_SDA	0x0001
#define SQ930_GPIO_DFW_I2C_SCW	0x0002
#define SQ930_GPIO_WSTBAW	0x0004
#define SQ930_GPIO_EXTWA1	0x0040
#define SQ930_GPIO_EXTWA2	0x0080
/* gpio 3 (24..31) */
#define SQ930_GPIO_POWEW	0x0200
#define SQ930_GPIO_DFW_WED	0x1000

stwuct ucbus_wwite_cmd {
	u16	bw_addw;
	u8	bw_data;
};
stwuct i2c_wwite_cmd {
	u8	weg;
	u16	vaw;
};

static const stwuct ucbus_wwite_cmd icx098bq_stawt_0[] = {
	{0x0354, 0x00}, {0x03fa, 0x00}, {0xf800, 0x02}, {0xf801, 0xce},
	{0xf802, 0xc1}, {0xf804, 0x00}, {0xf808, 0x00}, {0xf809, 0x0e},
	{0xf80a, 0x01}, {0xf80b, 0xee}, {0xf807, 0x60}, {0xf80c, 0x02},
	{0xf80d, 0xf0}, {0xf80e, 0x03}, {0xf80f, 0x0a}, {0xf81c, 0x02},
	{0xf81d, 0xf0}, {0xf81e, 0x03}, {0xf81f, 0x0a}, {0xf83a, 0x00},
	{0xf83b, 0x10}, {0xf83c, 0x00}, {0xf83d, 0x4e}, {0xf810, 0x04},
	{0xf811, 0x00}, {0xf812, 0x02}, {0xf813, 0x10}, {0xf803, 0x00},
	{0xf814, 0x01}, {0xf815, 0x18}, {0xf816, 0x00}, {0xf817, 0x48},
	{0xf818, 0x00}, {0xf819, 0x25}, {0xf81a, 0x00}, {0xf81b, 0x3c},
	{0xf82f, 0x03}, {0xf820, 0xff}, {0xf821, 0x0d}, {0xf822, 0xff},
	{0xf823, 0x07}, {0xf824, 0xff}, {0xf825, 0x03}, {0xf826, 0xff},
	{0xf827, 0x06}, {0xf828, 0xff}, {0xf829, 0x03}, {0xf82a, 0xff},
	{0xf82b, 0x0c}, {0xf82c, 0xfd}, {0xf82d, 0x01}, {0xf82e, 0x00},
	{0xf830, 0x00}, {0xf831, 0x47}, {0xf832, 0x00}, {0xf833, 0x00},
	{0xf850, 0x00}, {0xf851, 0x00}, {0xf852, 0x00}, {0xf853, 0x24},
	{0xf854, 0x00}, {0xf855, 0x18}, {0xf856, 0x00}, {0xf857, 0x3c},
	{0xf858, 0x00}, {0xf859, 0x0c}, {0xf85a, 0x00}, {0xf85b, 0x30},
	{0xf85c, 0x00}, {0xf85d, 0x0c}, {0xf85e, 0x00}, {0xf85f, 0x30},
	{0xf860, 0x00}, {0xf861, 0x48}, {0xf862, 0x01}, {0xf863, 0xdc},
	{0xf864, 0xff}, {0xf865, 0x98}, {0xf866, 0xff}, {0xf867, 0xc0},
	{0xf868, 0xff}, {0xf869, 0x70}, {0xf86c, 0xff}, {0xf86d, 0x00},
	{0xf86a, 0xff}, {0xf86b, 0x48}, {0xf86e, 0xff}, {0xf86f, 0x00},
	{0xf870, 0x01}, {0xf871, 0xdb}, {0xf872, 0x01}, {0xf873, 0xfa},
	{0xf874, 0x01}, {0xf875, 0xdb}, {0xf876, 0x01}, {0xf877, 0xfa},
	{0xf878, 0x0f}, {0xf879, 0x0f}, {0xf87a, 0xff}, {0xf87b, 0xff},
	{0xf800, 0x03}
};
static const stwuct ucbus_wwite_cmd icx098bq_stawt_1[] = {
	{0xf5f0, 0x00}, {0xf5f1, 0xcd}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xc0},
	{0xf5f0, 0x49}, {0xf5f1, 0xcd}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xc0},
	{0xf5fa, 0x00}, {0xf5f6, 0x00}, {0xf5f7, 0x00}, {0xf5f8, 0x00},
	{0xf5f9, 0x00}
};

static const stwuct ucbus_wwite_cmd icx098bq_stawt_2[] = {
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0x82}, {0xf806, 0x00},
	{0xf807, 0x7f}, {0xf800, 0x03},
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0x40}, {0xf806, 0x00},
	{0xf807, 0x7f}, {0xf800, 0x03},
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0xcf}, {0xf806, 0xd0},
	{0xf807, 0x7f}, {0xf800, 0x03},
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0x00}, {0xf806, 0x00},
	{0xf807, 0x7f}, {0xf800, 0x03}
};

static const stwuct ucbus_wwite_cmd wz24bp_stawt_0[] = {
	{0x0354, 0x00}, {0x03fa, 0x00}, {0xf800, 0x02}, {0xf801, 0xbe},
	{0xf802, 0xc6}, {0xf804, 0x00}, {0xf808, 0x00}, {0xf809, 0x06},
	{0xf80a, 0x01}, {0xf80b, 0xfe}, {0xf807, 0x84}, {0xf80c, 0x02},
	{0xf80d, 0xf7}, {0xf80e, 0x03}, {0xf80f, 0x0b}, {0xf81c, 0x00},
	{0xf81d, 0x49}, {0xf81e, 0x03}, {0xf81f, 0x0b}, {0xf83a, 0x00},
	{0xf83b, 0x01}, {0xf83c, 0x00}, {0xf83d, 0x6b}, {0xf810, 0x03},
	{0xf811, 0x10}, {0xf812, 0x02}, {0xf813, 0x6f}, {0xf803, 0x00},
	{0xf814, 0x00}, {0xf815, 0x44}, {0xf816, 0x00}, {0xf817, 0x48},
	{0xf818, 0x00}, {0xf819, 0x25}, {0xf81a, 0x00}, {0xf81b, 0x3c},
	{0xf82f, 0x03}, {0xf820, 0xff}, {0xf821, 0x0d}, {0xf822, 0xff},
	{0xf823, 0x07}, {0xf824, 0xfd}, {0xf825, 0x07}, {0xf826, 0xf0},
	{0xf827, 0x0c}, {0xf828, 0xff}, {0xf829, 0x03}, {0xf82a, 0xff},
	{0xf82b, 0x0c}, {0xf82c, 0xfc}, {0xf82d, 0x01}, {0xf82e, 0x00},
	{0xf830, 0x00}, {0xf831, 0x47}, {0xf832, 0x00}, {0xf833, 0x00},
	{0xf850, 0x00}, {0xf851, 0x00}, {0xf852, 0x00}, {0xf853, 0x24},
	{0xf854, 0x00}, {0xf855, 0x0c}, {0xf856, 0x00}, {0xf857, 0x30},
	{0xf858, 0x00}, {0xf859, 0x18}, {0xf85a, 0x00}, {0xf85b, 0x3c},
	{0xf85c, 0x00}, {0xf85d, 0x18}, {0xf85e, 0x00}, {0xf85f, 0x3c},
	{0xf860, 0xff}, {0xf861, 0x37}, {0xf862, 0xff}, {0xf863, 0x1d},
	{0xf864, 0xff}, {0xf865, 0x98}, {0xf866, 0xff}, {0xf867, 0xc0},
	{0xf868, 0x00}, {0xf869, 0x37}, {0xf86c, 0x02}, {0xf86d, 0x1d},
	{0xf86a, 0x00}, {0xf86b, 0x37}, {0xf86e, 0x02}, {0xf86f, 0x1d},
	{0xf870, 0x01}, {0xf871, 0xc6}, {0xf872, 0x02}, {0xf873, 0x04},
	{0xf874, 0x01}, {0xf875, 0xc6}, {0xf876, 0x02}, {0xf877, 0x04},
	{0xf878, 0x0f}, {0xf879, 0x0f}, {0xf87a, 0xff}, {0xf87b, 0xff},
	{0xf800, 0x03}
};
static const stwuct ucbus_wwite_cmd wz24bp_stawt_1_gen[] = {
	{0xf5f0, 0x00}, {0xf5f1, 0xff}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xb3},
	{0xf5f0, 0x40}, {0xf5f1, 0xff}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xb3},
	{0xf5fa, 0x00}, {0xf5f6, 0x00}, {0xf5f7, 0x00}, {0xf5f8, 0x00},
	{0xf5f9, 0x00}
};

static const stwuct ucbus_wwite_cmd wz24bp_stawt_1_cwm[] = {
	{0xf5f0, 0x00}, {0xf5f1, 0xff}, {0xf5f2, 0x88}, {0xf5f3, 0x88},
	{0xf5f4, 0xc0},
	{0xf5f0, 0x40}, {0xf5f1, 0xff}, {0xf5f2, 0x88}, {0xf5f3, 0x88},
	{0xf5f4, 0xc0},
	{0xf5fa, 0x00}, {0xf5f6, 0x00}, {0xf5f7, 0x00}, {0xf5f8, 0x00},
	{0xf5f9, 0x00}
};

static const stwuct ucbus_wwite_cmd wz24bp_stawt_2[] = {
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0x80}, {0xf806, 0x00},
	{0xf807, 0x7f}, {0xf800, 0x03},
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0x4e}, {0xf806, 0x00},
	{0xf807, 0x7f}, {0xf800, 0x03},
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0xc0}, {0xf806, 0x48},
	{0xf807, 0x7f}, {0xf800, 0x03},
	{0xf800, 0x02}, {0xf807, 0xff}, {0xf805, 0x00}, {0xf806, 0x00},
	{0xf807, 0x7f}, {0xf800, 0x03}
};

static const stwuct ucbus_wwite_cmd mi0360_stawt_0[] = {
	{0x0354, 0x00}, {0x03fa, 0x00}, {0xf332, 0xcc}, {0xf333, 0xcc},
	{0xf334, 0xcc}, {0xf335, 0xcc}, {0xf33f, 0x00}
};
static const stwuct i2c_wwite_cmd mi0360_init_23[] = {
	{0x30, 0x0040},		/* wesewved - def 0x0005 */
	{0x31, 0x0000},		/* wesewved - def 0x002a */
	{0x34, 0x0100},		/* wesewved - def 0x0100 */
	{0x3d, 0x068f},		/* wesewved - def 0x068f */
};
static const stwuct i2c_wwite_cmd mi0360_init_24[] = {
	{0x03, 0x01e5},		/* window height */
	{0x04, 0x0285},		/* window width */
};
static const stwuct i2c_wwite_cmd mi0360_init_25[] = {
	{0x35, 0x0020},		/* gwobaw gain */
	{0x2b, 0x0020},		/* gween1 gain */
	{0x2c, 0x002a},		/* bwue gain */
	{0x2d, 0x0028},		/* wed gain */
	{0x2e, 0x0020},		/* gween2 gain */
};
static const stwuct ucbus_wwite_cmd mi0360_stawt_1[] = {
	{0xf5f0, 0x11}, {0xf5f1, 0x99}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xa6},
	{0xf5f0, 0x51}, {0xf5f1, 0x99}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xa6},
	{0xf5fa, 0x00}, {0xf5f6, 0x00}, {0xf5f7, 0x00}, {0xf5f8, 0x00},
	{0xf5f9, 0x00}
};
static const stwuct i2c_wwite_cmd mi0360_stawt_2[] = {
	{0x62, 0x041d},		/* wesewved - def 0x0418 */
};
static const stwuct i2c_wwite_cmd mi0360_stawt_3[] = {
	{0x05, 0x007b},		/* howiz bwanking */
};
static const stwuct i2c_wwite_cmd mi0360_stawt_4[] = {
	{0x05, 0x03f5},		/* howiz bwanking */
};

static const stwuct i2c_wwite_cmd mt9v111_init_0[] = {
	{0x01, 0x0001},		/* sewect IFP/SOC wegistews */
	{0x06, 0x300c},		/* opewating mode contwow */
	{0x08, 0xcc00},		/* output fowmat contwow (WGB) */
	{0x01, 0x0004},		/* sewect sensow cowe wegistews */
};
static const stwuct i2c_wwite_cmd mt9v111_init_1[] = {
	{0x03, 0x01e5},		/* window height */
	{0x04, 0x0285},		/* window width */
};
static const stwuct i2c_wwite_cmd mt9v111_init_2[] = {
	{0x30, 0x7800},
	{0x31, 0x0000},
	{0x07, 0x3002},		/* output contwow */
	{0x35, 0x0020},		/* gwobaw gain */
	{0x2b, 0x0020},		/* gween1 gain */
	{0x2c, 0x0020},		/* bwue gain */
	{0x2d, 0x0020},		/* wed gain */
	{0x2e, 0x0020},		/* gween2 gain */
};
static const stwuct ucbus_wwite_cmd mt9v111_stawt_1[] = {
	{0xf5f0, 0x11}, {0xf5f1, 0x96}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xaa},
	{0xf5f0, 0x51}, {0xf5f1, 0x96}, {0xf5f2, 0x80}, {0xf5f3, 0x80},
	{0xf5f4, 0xaa},
	{0xf5fa, 0x00}, {0xf5f6, 0x0a}, {0xf5f7, 0x0a}, {0xf5f8, 0x0a},
	{0xf5f9, 0x0a}
};
static const stwuct i2c_wwite_cmd mt9v111_init_3[] = {
	{0x62, 0x0405},
};
static const stwuct i2c_wwite_cmd mt9v111_init_4[] = {
/*	{0x05, 0x00ce}, */
	{0x05, 0x005d},		/* howizontaw bwanking */
};

static const stwuct ucbus_wwite_cmd ov7660_stawt_0[] = {
	{0x0354, 0x00}, {0x03fa, 0x00}, {0xf332, 0x00}, {0xf333, 0xc0},
	{0xf334, 0x39}, {0xf335, 0xe7}, {0xf33f, 0x03}
};

static const stwuct ucbus_wwite_cmd ov9630_stawt_0[] = {
	{0x0354, 0x00}, {0x03fa, 0x00}, {0xf332, 0x00}, {0xf333, 0x00},
	{0xf334, 0x3e}, {0xf335, 0xf8}, {0xf33f, 0x03}
};

/* stawt pawametews indexed by [sensow][mode] */
static const stwuct cap_s {
	u8	cc_sizeid;
	u8	cc_bytes[32];
} capconfig[4][2] = {
	[SENSOW_ICX098BQ] = {
		{2,				/* Bayew 320x240 */
		  {0x05, 0x1f, 0x20, 0x0e, 0x00, 0x9f, 0x02, 0xee,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
		{4,				/* Bayew 640x480 */
		  {0x01, 0x1f, 0x20, 0x0e, 0x00, 0x9f, 0x02, 0xee,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
	},
	[SENSOW_WZ24BP] = {
		{2,				/* Bayew 320x240 */
		  {0x05, 0x22, 0x20, 0x0e, 0x00, 0xa2, 0x02, 0xee,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
		{4,				/* Bayew 640x480 */
		  {0x01, 0x22, 0x20, 0x0e, 0x00, 0xa2, 0x02, 0xee,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
	},
	[SENSOW_MI0360] = {
		{2,				/* Bayew 320x240 */
		  {0x05, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
		{4,				/* Bayew 640x480 */
		  {0x01, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
	},
	[SENSOW_MT9V111] = {
		{2,				/* Bayew 320x240 */
		  {0x05, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
		{4,				/* Bayew 640x480 */
		  {0x01, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
	},
};

stwuct sensow_s {
	const chaw *name;
	u8 i2c_addw;
	u8 i2c_dum;
	u8 gpio[5];
	u8 cmd_wen;
	const stwuct ucbus_wwite_cmd *cmd;
};

static const stwuct sensow_s sensow_tb[] = {
	[SENSOW_ICX098BQ] = {
		"icx098bp",
		0x00, 0x00,
		{0,
		 SQ930_GPIO_DFW_I2C_SDA | SQ930_GPIO_DFW_I2C_SCW,
		 SQ930_GPIO_DFW_I2C_SDA,
		 0,
		 SQ930_GPIO_WSTBAW
		},
		8, icx098bq_stawt_0
	    },
	[SENSOW_WZ24BP] = {
		"wz24bp",
		0x00, 0x00,
		{0,
		 SQ930_GPIO_DFW_I2C_SDA | SQ930_GPIO_DFW_I2C_SCW,
		 SQ930_GPIO_DFW_I2C_SDA,
		 0,
		 SQ930_GPIO_WSTBAW
		},
		8, wz24bp_stawt_0
	    },
	[SENSOW_MI0360] = {
		"mi0360",
		0x5d, 0x80,
		{SQ930_GPIO_WSTBAW,
		 SQ930_GPIO_DFW_I2C_SDA | SQ930_GPIO_DFW_I2C_SCW,
		 SQ930_GPIO_DFW_I2C_SDA,
		 0,
		 0
		},
		7, mi0360_stawt_0
	    },
	[SENSOW_MT9V111] = {
		"mt9v111",
		0x5c, 0x7f,
		{SQ930_GPIO_WSTBAW,
		 SQ930_GPIO_DFW_I2C_SDA | SQ930_GPIO_DFW_I2C_SCW,
		 SQ930_GPIO_DFW_I2C_SDA,
		 0,
		 0
		},
		7, mi0360_stawt_0
	    },
	[SENSOW_OV7660] = {
		"ov7660",
		0x21, 0x00,
		{0,
		 SQ930_GPIO_DFW_I2C_SDA | SQ930_GPIO_DFW_I2C_SCW,
		 SQ930_GPIO_DFW_I2C_SDA,
		 0,
		 SQ930_GPIO_WSTBAW
		},
		7, ov7660_stawt_0
	    },
	[SENSOW_OV9630] = {
		"ov9630",
		0x30, 0x00,
		{0,
		 SQ930_GPIO_DFW_I2C_SDA | SQ930_GPIO_DFW_I2C_SCW,
		 SQ930_GPIO_DFW_I2C_SDA,
		 0,
		 SQ930_GPIO_WSTBAW
		},
		7, ov9630_stawt_0
	    },
};

static void weg_w(stwuct gspca_dev *gspca_dev,
		u16 vawue, int wen)
{
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_wcvctwwpipe(gspca_dev->dev, 0),
			0x0c,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, 0, gspca_dev->usb_buf, wen,
			500);
	if (wet < 0) {
		pw_eww("weg_w %04x faiwed %d\n", vawue, wet);
		gspca_dev->usb_eww = wet;
		/*
		 * Make suwe the buffew is zewoed to avoid uninitiawized
		 * vawues.
		 */
		memset(gspca_dev->usb_buf, 0, USB_BUF_SZ);
	}
}

static void weg_w(stwuct gspca_dev *gspca_dev, u16 vawue, u16 index)
{
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dbg(gspca_dev, D_USBO, "weg_w v: %04x i: %04x\n", vawue, index);
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0x0c,			/* wequest */
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index, NUWW, 0,
			500);
	msweep(30);
	if (wet < 0) {
		pw_eww("weg_w %04x %04x faiwed %d\n", vawue, index, wet);
		gspca_dev->usb_eww = wet;
	}
}

static void weg_wb(stwuct gspca_dev *gspca_dev, u16 vawue, u16 index,
		const u8 *data, int wen)
{
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dbg(gspca_dev, D_USBO, "weg_wb v: %04x i: %04x %02x...%02x\n",
		  vawue, index, *data, data[wen - 1]);
	memcpy(gspca_dev->usb_buf, data, wen);
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0x0c,			/* wequest */
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index, gspca_dev->usb_buf, wen,
			1000);
	msweep(30);
	if (wet < 0) {
		pw_eww("weg_wb %04x %04x faiwed %d\n", vawue, index, wet);
		gspca_dev->usb_eww = wet;
	}
}

static void i2c_wwite(stwuct sd *sd,
			const stwuct i2c_wwite_cmd *cmd,
			int ncmds)
{
	stwuct gspca_dev *gspca_dev = &sd->gspca_dev;
	const stwuct sensow_s *sensow;
	u16 vaw, idx;
	u8 *buf;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	sensow = &sensow_tb[sd->sensow];

	vaw = (sensow->i2c_addw << 8) | SQ930_CTWW_I2C_IO;
	idx = (cmd->vaw & 0xff00) | cmd->weg;

	buf = gspca_dev->usb_buf;
	*buf++ = sensow->i2c_dum;
	*buf++ = cmd->vaw;

	whiwe (--ncmds > 0) {
		cmd++;
		*buf++ = cmd->weg;
		*buf++ = cmd->vaw >> 8;
		*buf++ = sensow->i2c_dum;
		*buf++ = cmd->vaw;
	}

	gspca_dbg(gspca_dev, D_USBO, "i2c_w v: %04x i: %04x %02x...%02x\n",
		  vaw, idx, gspca_dev->usb_buf[0], buf[-1]);
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0x0c,			/* wequest */
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vaw, idx,
			gspca_dev->usb_buf, buf - gspca_dev->usb_buf,
			500);
	if (wet < 0) {
		pw_eww("i2c_wwite faiwed %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

static void ucbus_wwite(stwuct gspca_dev *gspca_dev,
			const stwuct ucbus_wwite_cmd *cmd,
			int ncmds,
			int batchsize)
{
	u8 *buf;
	u16 vaw, idx;
	int wen, wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	if ((batchsize - 1) * 3 > USB_BUF_SZ) {
		gspca_eww(gspca_dev, "Bug: usb_buf ovewfwow\n");
		gspca_dev->usb_eww = -ENOMEM;
		wetuwn;
	}

	fow (;;) {
		wen = ncmds;
		if (wen > batchsize)
			wen = batchsize;
		ncmds -= wen;

		vaw = (cmd->bw_addw << 8) | SQ930_CTWW_UCBUS_IO;
		idx = (cmd->bw_data << 8) | (cmd->bw_addw >> 8);

		buf = gspca_dev->usb_buf;
		whiwe (--wen > 0) {
			cmd++;
			*buf++ = cmd->bw_addw;
			*buf++ = cmd->bw_addw >> 8;
			*buf++ = cmd->bw_data;
		}
		if (buf != gspca_dev->usb_buf)
			gspca_dbg(gspca_dev, D_USBO, "ucbus v: %04x i: %04x %02x...%02x\n",
				  vaw, idx,
				  gspca_dev->usb_buf[0], buf[-1]);
		ewse
			gspca_dbg(gspca_dev, D_USBO, "ucbus v: %04x i: %04x\n",
				  vaw, idx);
		wet = usb_contwow_msg(gspca_dev->dev,
				usb_sndctwwpipe(gspca_dev->dev, 0),
				0x0c,			/* wequest */
			   USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				vaw, idx,
				gspca_dev->usb_buf, buf - gspca_dev->usb_buf,
				500);
		if (wet < 0) {
			pw_eww("ucbus_wwite faiwed %d\n", wet);
			gspca_dev->usb_eww = wet;
			wetuwn;
		}
		msweep(30);
		if (ncmds <= 0)
			bweak;
		cmd++;
	}
}

static void gpio_set(stwuct sd *sd, u16 vaw, u16 mask)
{
	stwuct gspca_dev *gspca_dev = &sd->gspca_dev;

	if (mask & 0x00ff) {
		sd->gpio[0] &= ~mask;
		sd->gpio[0] |= vaw;
		weg_w(gspca_dev, 0x0100 | SQ930_CTWW_GPIO,
			~sd->gpio[0] << 8);
	}
	mask >>= 8;
	vaw >>= 8;
	if (mask) {
		sd->gpio[1] &= ~mask;
		sd->gpio[1] |= vaw;
		weg_w(gspca_dev, 0x0300 | SQ930_CTWW_GPIO,
			~sd->gpio[1] << 8);
	}
}

static void gpio_init(stwuct sd *sd,
			const u8 *gpio)
{
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio, 0x000f);
}

static void bwidge_init(stwuct sd *sd)
{
	static const stwuct ucbus_wwite_cmd cwkfweq_cmd = {
				0xf031, 0	/* SQ930_CWKFWEQ_60MHZ */
	};

	ucbus_wwite(&sd->gspca_dev, &cwkfweq_cmd, 1, 1);

	gpio_set(sd, SQ930_GPIO_POWEW, 0xff00);
}

static void cmos_pwobe(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i;
	const stwuct sensow_s *sensow;
	static const u8 pwobe_owdew[] = {
/*		SENSOW_WZ24BP,		(tested as ccd) */
		SENSOW_OV9630,
		SENSOW_MI0360,
		SENSOW_OV7660,
		SENSOW_MT9V111,
	};

	fow (i = 0; i < AWWAY_SIZE(pwobe_owdew); i++) {
		sensow = &sensow_tb[pwobe_owdew[i]];
		ucbus_wwite(&sd->gspca_dev, sensow->cmd, sensow->cmd_wen, 8);
		gpio_init(sd, sensow->gpio);
		msweep(100);
		weg_w(gspca_dev, (sensow->i2c_addw << 8) | 0x001c, 1);
		msweep(100);
		if (gspca_dev->usb_buf[0] != 0)
			bweak;
	}
	if (i >= AWWAY_SIZE(pwobe_owdew)) {
		pw_eww("Unknown sensow\n");
		gspca_dev->usb_eww = -EINVAW;
		wetuwn;
	}
	sd->sensow = pwobe_owdew[i];
	switch (sd->sensow) {
	case SENSOW_OV7660:
	case SENSOW_OV9630:
		pw_eww("Sensow %s not yet tweated\n",
		       sensow_tb[sd->sensow].name);
		gspca_dev->usb_eww = -EINVAW;
		bweak;
	}
}

static void mt9v111_init(stwuct gspca_dev *gspca_dev)
{
	int i, nwait;
	static const u8 cmd_001b[] = {
		0x00, 0x3b, 0xf6, 0x01, 0x03, 0x02, 0x00, 0x00,
		0x00, 0x00, 0x00
	};
	static const u8 cmd_011b[][7] = {
		{0x10, 0x01, 0x66, 0x08, 0x00, 0x00, 0x00},
		{0x01, 0x00, 0x1a, 0x04, 0x00, 0x00, 0x00},
		{0x20, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00},
		{0x02, 0x01, 0xae, 0x01, 0x00, 0x00, 0x00},
	};

	weg_wb(gspca_dev, 0x001b, 0x0000, cmd_001b, sizeof cmd_001b);
	fow (i = 0; i < AWWAY_SIZE(cmd_011b); i++) {
		weg_wb(gspca_dev, 0x001b, 0x0000, cmd_011b[i],
				AWWAY_SIZE(cmd_011b[0]));
		msweep(400);
		nwait = 20;
		fow (;;) {
			weg_w(gspca_dev, 0x031b, 1);
			if (gspca_dev->usb_buf[0] == 0
			 || gspca_dev->usb_eww != 0)
				bweak;
			if (--nwait < 0) {
				gspca_dbg(gspca_dev, D_PWOBE, "mt9v111_init timeout\n");
				gspca_dev->usb_eww = -ETIME;
				wetuwn;
			}
			msweep(50);
		}
	}
}

static void gwobaw_init(stwuct sd *sd, int fiwst_time)
{
	switch (sd->sensow) {
	case SENSOW_ICX098BQ:
		if (fiwst_time)
			ucbus_wwite(&sd->gspca_dev,
					icx098bq_stawt_0,
					8, 8);
		gpio_init(sd, sensow_tb[sd->sensow].gpio);
		bweak;
	case SENSOW_WZ24BP:
		if (sd->type != Cweative_wive_motion)
			gpio_set(sd, SQ930_GPIO_EXTWA1, 0x00ff);
		ewse
			gpio_set(sd, 0, 0x00ff);
		msweep(50);
		if (fiwst_time)
			ucbus_wwite(&sd->gspca_dev,
					wz24bp_stawt_0,
					8, 8);
		gpio_init(sd, sensow_tb[sd->sensow].gpio);
		bweak;
	case SENSOW_MI0360:
		if (fiwst_time)
			ucbus_wwite(&sd->gspca_dev,
					mi0360_stawt_0,
					AWWAY_SIZE(mi0360_stawt_0),
					8);
		gpio_init(sd, sensow_tb[sd->sensow].gpio);
		gpio_set(sd, SQ930_GPIO_EXTWA2, SQ930_GPIO_EXTWA2);
		bweak;
	defauwt:
/*	case SENSOW_MT9V111: */
		if (fiwst_time)
			mt9v111_init(&sd->gspca_dev);
		ewse
			gpio_init(sd, sensow_tb[sd->sensow].gpio);
		bweak;
	}
}

static void wz24bp_ppw(stwuct sd *sd, u16 ppw)
{
	stwuct ucbus_wwite_cmd cmds[2] = {
		{0xf810, ppw >> 8},
		{0xf811, ppw}
	};

	ucbus_wwite(&sd->gspca_dev, cmds, AWWAY_SIZE(cmds), 2);
}

static void setexposuwe(stwuct gspca_dev *gspca_dev, s32 expo, s32 gain)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i, integcwks, intstawtcwk, fwamecwks, min_fwcwk;
	const stwuct sensow_s *sensow;
	u16 cmd;
	u8 buf[15];

	integcwks = expo;
	i = 0;
	cmd = SQ930_CTWW_SET_EXPOSUWE;

	switch (sd->sensow) {
	case SENSOW_ICX098BQ:			/* ccd */
	case SENSOW_WZ24BP:
		min_fwcwk = sd->sensow == SENSOW_ICX098BQ ? 0x210 : 0x26f;
		if (integcwks >= min_fwcwk) {
			intstawtcwk = 0;
			fwamecwks = integcwks;
		} ewse {
			intstawtcwk = min_fwcwk - integcwks;
			fwamecwks = min_fwcwk;
		}
		buf[i++] = intstawtcwk >> 8;
		buf[i++] = intstawtcwk;
		buf[i++] = fwamecwks >> 8;
		buf[i++] = fwamecwks;
		buf[i++] = gain;
		bweak;
	defauwt:				/* cmos */
/*	case SENSOW_MI0360: */
/*	case SENSOW_MT9V111: */
		cmd |= 0x0100;
		sensow = &sensow_tb[sd->sensow];
		buf[i++] = sensow->i2c_addw;	/* i2c_swave_addw */
		buf[i++] = 0x08;	/* 2 * ni2c */
		buf[i++] = 0x09;	/* weg = shuttew width */
		buf[i++] = integcwks >> 8; /* vaw H */
		buf[i++] = sensow->i2c_dum;
		buf[i++] = integcwks;	/* vaw W */
		buf[i++] = 0x35;	/* weg = gwobaw gain */
		buf[i++] = 0x00;	/* vaw H */
		buf[i++] = sensow->i2c_dum;
		buf[i++] = 0x80 + gain / 2; /* vaw W */
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x83;
		bweak;
	}
	weg_wb(gspca_dev, cmd, 0, buf, i);
}

/* This function is cawwed at pwobe time just befowe sd_init */
static int sd_config(stwuct gspca_dev *gspca_dev,
		const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam = &gspca_dev->cam;

	sd->sensow = id->dwivew_info >> 8;
	sd->type = id->dwivew_info;

	cam->cam_mode = vga_mode;
	cam->nmodes = AWWAY_SIZE(vga_mode);

	cam->buwk = 1;

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	sd->gpio[0] = sd->gpio[1] = 0xff;	/* fowce gpio wewwite */

/*fixme: is this needed fow icx098bp and mi0360?
	if (sd->sensow != SENSOW_WZ24BP)
		weg_w(gspca_dev, SQ930_CTWW_WESET, 0x0000);
 */

	weg_w(gspca_dev, SQ930_CTWW_GET_DEV_INFO, 8);
	if (gspca_dev->usb_eww < 0)
		wetuwn gspca_dev->usb_eww;

/* it wetuwns:
 * 03 00 12 93 0b f6 c9 00	wive! uwtwa
 * 03 00 07 93 0b f6 ca 00	wive! uwtwa fow notebook
 * 03 00 12 93 0b fe c8 00	Twust WB-3500T
 * 02 00 06 93 0b fe c8 00	Joy-IT 318S
 * 03 00 12 93 0b f6 cf 00	icam twacew - sensow icx098bq
 * 02 00 12 93 0b fe cf 00	PwoQ Motion Webcam
 *
 * byte
 * 0: 02 = usb 1.0 (12Mbit) / 03 = usb2.0 (480Mbit)
 * 1: 00
 * 2: 06 / 07 / 12 = mode webcam? fiwmwawe??
 * 3: 93 chip = 930b (930b ow 930c)
 * 4: 0b
 * 5: f6 = cdd (icx098bq, wz24bp) / fe ow de = cmos (i2c) (othew sensows)
 * 6: c8 / c9 / ca / cf = mode webcam?, sensow? webcam?
 * 7: 00
 */
	gspca_dbg(gspca_dev, D_PWOBE, "info: %*ph\n", 8, gspca_dev->usb_buf);

	bwidge_init(sd);

	if (sd->sensow == SENSOW_MI0360) {

		/* no sensow pwobe fow icam twacew */
		if (gspca_dev->usb_buf[5] == 0xf6)	/* if ccd */
			sd->sensow = SENSOW_ICX098BQ;
		ewse
			cmos_pwobe(gspca_dev);
	}
	if (gspca_dev->usb_eww >= 0) {
		gspca_dbg(gspca_dev, D_PWOBE, "Sensow %s\n",
			  sensow_tb[sd->sensow].name);
		gwobaw_init(sd, 1);
	}
	wetuwn gspca_dev->usb_eww;
}

/* send the stawt/stop commands to the webcam */
static void send_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	const stwuct cap_s *cap;
	int mode;

	mode = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
	cap = &capconfig[sd->sensow][mode];
	weg_wb(gspca_dev, 0x0900 | SQ930_CTWW_CAP_STAWT,
			0x0a00 | cap->cc_sizeid,
			cap->cc_bytes, 32);
}

static void send_stop(stwuct gspca_dev *gspca_dev)
{
	weg_w(gspca_dev, SQ930_CTWW_CAP_STOP, 0);
}

/* function cawwed at stawt time befowe UWB cweation */
static int sd_isoc_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dev->cam.buwk_nuwbs = 1;	/* thewe must be one UWB onwy */
	sd->do_ctww = 0;
	gspca_dev->cam.buwk_size = gspca_dev->pixfmt.width *
			gspca_dev->pixfmt.height + 8;
	wetuwn 0;
}

/* stawt the captuwe */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int mode;

	bwidge_init(sd);
	gwobaw_init(sd, 0);
	msweep(100);

	switch (sd->sensow) {
	case SENSOW_ICX098BQ:
		ucbus_wwite(gspca_dev, icx098bq_stawt_0,
				AWWAY_SIZE(icx098bq_stawt_0),
				8);
		ucbus_wwite(gspca_dev, icx098bq_stawt_1,
				AWWAY_SIZE(icx098bq_stawt_1),
				5);
		ucbus_wwite(gspca_dev, icx098bq_stawt_2,
				AWWAY_SIZE(icx098bq_stawt_2),
				6);
		msweep(50);

		/* 1st stawt */
		send_stawt(gspca_dev);
		gpio_set(sd, SQ930_GPIO_EXTWA2 | SQ930_GPIO_WSTBAW, 0x00ff);
		msweep(70);
		weg_w(gspca_dev, SQ930_CTWW_CAP_STOP, 0x0000);
		gpio_set(sd, 0x7f, 0x00ff);

		/* 2nd stawt */
		send_stawt(gspca_dev);
		gpio_set(sd, SQ930_GPIO_EXTWA2 | SQ930_GPIO_WSTBAW, 0x00ff);
		goto out;
	case SENSOW_WZ24BP:
		ucbus_wwite(gspca_dev, wz24bp_stawt_0,
				AWWAY_SIZE(wz24bp_stawt_0),
				8);
		if (sd->type != Cweative_wive_motion)
			ucbus_wwite(gspca_dev, wz24bp_stawt_1_gen,
					AWWAY_SIZE(wz24bp_stawt_1_gen),
					5);
		ewse
			ucbus_wwite(gspca_dev, wz24bp_stawt_1_cwm,
					AWWAY_SIZE(wz24bp_stawt_1_cwm),
					5);
		ucbus_wwite(gspca_dev, wz24bp_stawt_2,
				AWWAY_SIZE(wz24bp_stawt_2),
				6);
		mode = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
		wz24bp_ppw(sd, mode == 1 ? 0x0564 : 0x0310);
		msweep(10);
		bweak;
	case SENSOW_MI0360:
		ucbus_wwite(gspca_dev, mi0360_stawt_0,
				AWWAY_SIZE(mi0360_stawt_0),
				8);
		i2c_wwite(sd, mi0360_init_23,
				AWWAY_SIZE(mi0360_init_23));
		i2c_wwite(sd, mi0360_init_24,
				AWWAY_SIZE(mi0360_init_24));
		i2c_wwite(sd, mi0360_init_25,
				AWWAY_SIZE(mi0360_init_25));
		ucbus_wwite(gspca_dev, mi0360_stawt_1,
				AWWAY_SIZE(mi0360_stawt_1),
				5);
		i2c_wwite(sd, mi0360_stawt_2,
				AWWAY_SIZE(mi0360_stawt_2));
		i2c_wwite(sd, mi0360_stawt_3,
				AWWAY_SIZE(mi0360_stawt_3));

		/* 1st stawt */
		send_stawt(gspca_dev);
		msweep(60);
		send_stop(gspca_dev);

		i2c_wwite(sd,
			mi0360_stawt_4, AWWAY_SIZE(mi0360_stawt_4));
		bweak;
	defauwt:
/*	case SENSOW_MT9V111: */
		ucbus_wwite(gspca_dev, mi0360_stawt_0,
				AWWAY_SIZE(mi0360_stawt_0),
				8);
		i2c_wwite(sd, mt9v111_init_0,
				AWWAY_SIZE(mt9v111_init_0));
		i2c_wwite(sd, mt9v111_init_1,
				AWWAY_SIZE(mt9v111_init_1));
		i2c_wwite(sd, mt9v111_init_2,
				AWWAY_SIZE(mt9v111_init_2));
		ucbus_wwite(gspca_dev, mt9v111_stawt_1,
				AWWAY_SIZE(mt9v111_stawt_1),
				5);
		i2c_wwite(sd, mt9v111_init_3,
				AWWAY_SIZE(mt9v111_init_3));
		i2c_wwite(sd, mt9v111_init_4,
				AWWAY_SIZE(mt9v111_init_4));
		bweak;
	}

	send_stawt(gspca_dev);
out:
	msweep(1000);

	if (sd->sensow == SENSOW_MT9V111)
		gpio_set(sd, SQ930_GPIO_DFW_WED, SQ930_GPIO_DFW_WED);

	sd->do_ctww = 1;	/* set the exposuwe */

	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_MT9V111)
		gpio_set(sd, 0, SQ930_GPIO_DFW_WED);
	send_stop(gspca_dev);
}

/* function cawwed when the appwication gets a new fwame */
/* It sets the exposuwe if wequiwed and westawt the buwk twansfew. */
static void sd_dq_cawwback(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet;

	if (!sd->do_ctww || gspca_dev->cam.buwk_nuwbs != 0)
		wetuwn;
	sd->do_ctww = 0;

	setexposuwe(gspca_dev, v4w2_ctww_g_ctww(sd->exposuwe),
			v4w2_ctww_g_ctww(sd->gain));

	gspca_dev->cam.buwk_nuwbs = 1;
	wet = usb_submit_uwb(gspca_dev->uwb[0], GFP_KEWNEW);
	if (wet < 0)
		pw_eww("sd_dq_cawwback() eww %d\n", wet);

	/* wait a wittwe time, othewwise the webcam cwashes */
	msweep(100);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,		/* isoc packet */
			int wen)		/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->do_ctww)
		gspca_dev->cam.buwk_nuwbs = 0;
	gspca_fwame_add(gspca_dev, FIWST_PACKET, NUWW, 0);
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen - 8);
	gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		setexposuwe(gspca_dev, ctww->vaw, sd->gain->vaw);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 2);
	sd->exposuwe = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_EXPOSUWE, 1, 0xfff, 1, 0x356);
	sd->gain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAIN, 1, 255, 1, 0x8d);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	v4w2_ctww_cwustew(2, &sd->exposuwe);
	wetuwn 0;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name   = MODUWE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.init_contwows = sd_init_contwows,
	.isoc_init = sd_isoc_init,
	.stawt  = sd_stawt,
	.stopN  = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.dq_cawwback = sd_dq_cawwback,
};

/* Tabwe of suppowted USB devices */
#define ST(sensow, type) \
	.dwivew_info = (SENSOW_ ## sensow << 8) \
			| (type)
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x041e, 0x4038), ST(MI0360, 0)},
	{USB_DEVICE(0x041e, 0x403c), ST(WZ24BP, 0)},
	{USB_DEVICE(0x041e, 0x403d), ST(WZ24BP, 0)},
	{USB_DEVICE(0x041e, 0x4041), ST(WZ24BP, Cweative_wive_motion)},
	{USB_DEVICE(0x2770, 0x930b), ST(MI0360, 0)},
	{USB_DEVICE(0x2770, 0x930c), ST(MI0360, 0)},
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);


/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
			THIS_MODUWE);
}

static stwuct usb_dwivew sd_dwivew = {
	.name	    = MODUWE_NAME,
	.id_tabwe   = device_tabwe,
	.pwobe	    = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend    = gspca_suspend,
	.wesume     = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);
