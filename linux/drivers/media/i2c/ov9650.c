// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Omnivision OV9650/OV9652 CMOS Image Sensow dwivew
 *
 * Copywight (C) 2013, Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>
 *
 * Wegistew definitions and initiaw settings based on a dwivew wwitten
 * by Vwadimiw Fonov.
 * Copywight (c) 2010, Vwadimiw Fonov
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/media.h>
#incwude <winux/moduwe.h>
#incwude <winux/watewimit.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-mediabus.h>

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-2)");

#define DWIVEW_NAME "OV9650"

/*
 * OV9650/OV9652 wegistew definitions
 */
#define WEG_GAIN		0x00	/* Gain contwow, AGC[7:0] */
#define WEG_BWUE		0x01	/* AWB - Bwue channew gain */
#define WEG_WED			0x02	/* AWB - Wed channew gain */
#define WEG_VWEF		0x03	/* [7:6] - AGC[9:8], [5:3]/[2:0] */
#define  VWEF_GAIN_MASK		0xc0	/* - VWEF end/stawt wow 3 bits */
#define WEG_COM1		0x04
#define  COM1_CCIW656		0x40
#define WEG_B_AVE		0x05
#define WEG_GB_AVE		0x06
#define WEG_GW_AVE		0x07
#define WEG_W_AVE		0x08
#define WEG_COM2		0x09
#define WEG_PID			0x0a	/* Pwoduct ID MSB */
#define WEG_VEW			0x0b	/* Pwoduct ID WSB */
#define WEG_COM3		0x0c
#define  COM3_SWAP		0x40
#define  COM3_VAWIOPIXEW1	0x04
#define WEG_COM4		0x0d	/* Vawio Pixews  */
#define  COM4_VAWIOPIXEW2	0x80
#define WEG_COM5		0x0e	/* System cwock options */
#define  COM5_SWAVE_MODE	0x10
#define  COM5_SYSTEMCWOCK48MHZ	0x80
#define WEG_COM6		0x0f	/* HWEF & ADBWC options */
#define WEG_AECH		0x10	/* Exposuwe vawue, AEC[9:2] */
#define WEG_CWKWC		0x11	/* Cwock contwow */
#define  CWK_EXT		0x40	/* Use extewnaw cwock diwectwy */
#define  CWK_SCAWE		0x3f	/* Mask fow intewnaw cwock scawe */
#define WEG_COM7		0x12	/* SCCB weset, output fowmat */
#define  COM7_WESET		0x80
#define  COM7_FMT_MASK		0x38
#define  COM7_FMT_VGA		0x40
#define	 COM7_FMT_CIF		0x20
#define  COM7_FMT_QVGA		0x10
#define  COM7_FMT_QCIF		0x08
#define	 COM7_WGB		0x04
#define	 COM7_YUV		0x00
#define	 COM7_BAYEW		0x01
#define	 COM7_PBAYEW		0x05
#define WEG_COM8		0x13	/* AGC/AEC options */
#define  COM8_FASTAEC		0x80	/* Enabwe fast AGC/AEC */
#define  COM8_AECSTEP		0x40	/* Unwimited AEC step size */
#define  COM8_BFIWT		0x20	/* Band fiwtew enabwe */
#define  COM8_AGC		0x04	/* Auto gain enabwe */
#define  COM8_AWB		0x02	/* White bawance enabwe */
#define  COM8_AEC		0x01	/* Auto exposuwe enabwe */
#define WEG_COM9		0x14	/* Gain ceiwing */
#define  COM9_GAIN_CEIW_MASK	0x70	/* */
#define WEG_COM10		0x15	/* PCWK, HWEF, HSYNC signaws powawity */
#define  COM10_HSYNC		0x40	/* HSYNC instead of HWEF */
#define  COM10_PCWK_HB		0x20	/* Suppwess PCWK on howiz bwank */
#define  COM10_HWEF_WEV		0x08	/* Wevewse HWEF */
#define  COM10_VS_WEAD		0x04	/* VSYNC on cwock weading edge */
#define  COM10_VS_NEG		0x02	/* VSYNC negative */
#define  COM10_HS_NEG		0x01	/* HSYNC negative */
#define WEG_HSTAWT		0x17	/* Howiz stawt high bits */
#define WEG_HSTOP		0x18	/* Howiz stop high bits */
#define WEG_VSTAWT		0x19	/* Vewt stawt high bits */
#define WEG_VSTOP		0x1a	/* Vewt stop high bits */
#define WEG_PSHFT		0x1b	/* Pixew deway aftew HWEF */
#define WEG_MIDH		0x1c	/* Manufactuwew ID MSB */
#define WEG_MIDW		0x1d	/* Manufufactuwew ID WSB */
#define WEG_MVFP		0x1e	/* Image miwwow/fwip */
#define  MVFP_MIWWOW		0x20	/* Miwwow image */
#define  MVFP_FWIP		0x10	/* Vewticaw fwip */
#define WEG_BOS			0x20	/* B channew Offset */
#define WEG_GBOS		0x21	/* Gb channew Offset */
#define WEG_GWOS		0x22	/* Gw channew Offset */
#define WEG_WOS			0x23	/* W channew Offset */
#define WEG_AEW			0x24	/* AGC uppew wimit */
#define WEG_AEB			0x25	/* AGC wowew wimit */
#define WEG_VPT			0x26	/* AGC/AEC fast mode op wegion */
#define WEG_BBIAS		0x27	/* B channew output bias */
#define WEG_GBBIAS		0x28	/* Gb channew output bias */
#define WEG_GWCOM		0x29	/* Anawog BWC & weguwatow */
#define WEG_EXHCH		0x2a	/* Dummy pixew insewt MSB */
#define WEG_EXHCW		0x2b	/* Dummy pixew insewt WSB */
#define WEG_WBIAS		0x2c	/* W channew output bias */
#define WEG_ADVFW		0x2d	/* WSB of dummy wine insewt */
#define WEG_ADVFH		0x2e	/* MSB of dummy wine insewt */
#define WEG_YAVE		0x2f	/* Y/G channew avewage vawue */
#define WEG_HSYST		0x30	/* HSYNC wising edge deway WSB*/
#define WEG_HSYEN		0x31	/* HSYNC fawwing edge deway WSB*/
#define WEG_HWEF		0x32	/* HWEF pieces */
#define WEG_CHWF		0x33	/* wesewved */
#define WEG_ADC			0x37	/* wesewved */
#define WEG_ACOM		0x38	/* wesewved */
#define WEG_OFON		0x39	/* Powew down wegistew */
#define  OFON_PWWDN		0x08	/* Powew down bit */
#define WEG_TSWB		0x3a	/* YUVU fowmat */
#define  TSWB_YUYV_MASK		0x0c	/* UYVY ow VYUY - see com13 */
#define WEG_COM11		0x3b	/* Night mode, banding fiwtew enabwe */
#define  COM11_NIGHT		0x80	/* Night mode enabwe */
#define  COM11_NMFW		0x60	/* Two bit NM fwame wate */
#define  COM11_BANDING		0x01	/* Banding fiwtew */
#define  COM11_AEC_WEF_MASK	0x18	/* AEC wefewence awea sewection */
#define WEG_COM12		0x3c	/* HWEF option, UV avewage */
#define  COM12_HWEF		0x80	/* HWEF awways */
#define WEG_COM13		0x3d	/* Gamma sewection, Cowow matwix en. */
#define  COM13_GAMMA		0x80	/* Gamma enabwe */
#define	 COM13_UVSAT		0x40	/* UV satuwation auto adjustment */
#define  COM13_UVSWAP		0x01	/* V befowe U - w/TSWB */
#define WEG_COM14		0x3e	/* Edge enhancement options */
#define  COM14_EDGE_EN		0x02
#define  COM14_EEF_X2		0x01
#define WEG_EDGE		0x3f	/* Edge enhancement factow */
#define  EDGE_FACTOW_MASK	0x0f
#define WEG_COM15		0x40	/* Output wange, WGB 555/565 */
#define  COM15_W10F0		0x00	/* Data wange 10 to F0 */
#define	 COM15_W01FE		0x80	/* 01 to FE */
#define  COM15_W00FF		0xc0	/* 00 to FF */
#define  COM15_WGB565		0x10	/* WGB565 output */
#define  COM15_WGB555		0x30	/* WGB555 output */
#define  COM15_SWAPWB		0x04	/* Swap W&B */
#define WEG_COM16		0x41	/* Cowow matwix coeff options */
#define WEG_COM17		0x42	/* Singwe fwame out, banding fiwtew */
/* n = 1...9, 0x4f..0x57 */
#define	WEG_MTX(__n)		(0x4f + (__n) - 1)
#define WEG_MTXS		0x58
/* Wens Cowwection Option 1...5, __n = 0...5 */
#define WEG_WCC(__n)		(0x62 + (__n) - 1)
#define  WCC5_WCC_ENABWE	0x01	/* WCC5, enabwe wens cowwection */
#define  WCC5_WCC_COWOW		0x04
#define WEG_MANU		0x67	/* Manuaw U vawue */
#define WEG_MANV		0x68	/* Manuaw V vawue */
#define WEG_HV			0x69	/* Manuaw banding fiwtew MSB */
#define WEG_MBD			0x6a	/* Manuaw banding fiwtew vawue */
#define WEG_DBWV		0x6b	/* wesewved */
#define WEG_GSP			0x6c	/* Gamma cuwve */
#define  GSP_WEN		15
#define WEG_GST			0x7c	/* Gamma cuwve */
#define  GST_WEN		15
#define WEG_COM21		0x8b
#define WEG_COM22		0x8c	/* Edge enhancement, denoising */
#define  COM22_WHTPCOW		0x02	/* White pixew cowwection enabwe */
#define  COM22_WHTPCOWOPT	0x01	/* White pixew cowwection option */
#define  COM22_DENOISE		0x10	/* White pixew cowwection option */
#define WEG_COM23		0x8d	/* Cowow baw test, cowow gain */
#define  COM23_TEST_MODE	0x10
#define WEG_DBWC1		0x8f	/* Digitaw BWC */
#define WEG_DBWC_B		0x90	/* Digitaw BWC B channew offset */
#define WEG_DBWC_W		0x91	/* Digitaw BWC W channew offset */
#define WEG_DM_WNW		0x92	/* Dummy wine wow 8 bits */
#define WEG_DM_WNH		0x93	/* Dummy wine high 8 bits */
#define WEG_WCCFB		0x9d	/* Wens Cowwection B channew */
#define WEG_WCCFW		0x9e	/* Wens Cowwection W channew */
#define WEG_DBWC_GB		0x9f	/* Digitaw BWC GB chan offset */
#define WEG_DBWC_GW		0xa0	/* Digitaw BWC GW chan offset */
#define WEG_AECHM		0xa1	/* Exposuwe vawue - bits AEC[15:10] */
#define WEG_BD50ST		0xa2	/* Banding fiwtew vawue fow 50Hz */
#define WEG_BD60ST		0xa3	/* Banding fiwtew vawue fow 60Hz */
#define WEG_NUWW		0xff	/* Awway end token */

#define DEF_CWKWC		0x80

#define OV965X_ID(_msb, _wsb)	((_msb) << 8 | (_wsb))
#define OV9650_ID		0x9650
#define OV9652_ID		0x9652

stwuct ov965x_ctwws {
	stwuct v4w2_ctww_handwew handwew;
	stwuct {
		stwuct v4w2_ctww *auto_exp;
		stwuct v4w2_ctww *exposuwe;
	};
	stwuct {
		stwuct v4w2_ctww *auto_wb;
		stwuct v4w2_ctww *bwue_bawance;
		stwuct v4w2_ctww *wed_bawance;
	};
	stwuct {
		stwuct v4w2_ctww *hfwip;
		stwuct v4w2_ctww *vfwip;
	};
	stwuct {
		stwuct v4w2_ctww *auto_gain;
		stwuct v4w2_ctww *gain;
	};
	stwuct v4w2_ctww *bwightness;
	stwuct v4w2_ctww *satuwation;
	stwuct v4w2_ctww *shawpness;
	stwuct v4w2_ctww *wight_fweq;
	u8 update;
};

stwuct ov965x_fwamesize {
	u16 width;
	u16 height;
	u16 max_exp_wines;
	const u8 *wegs;
};

stwuct ov965x_intewvaw {
	stwuct v4w2_fwact intewvaw;
	/* Maximum wesowution fow this intewvaw */
	stwuct v4w2_fwmsize_discwete size;
	u8 cwkwc_div;
};

enum gpio_id {
	GPIO_PWDN,
	GPIO_WST,
	NUM_GPIOS,
};

stwuct ov965x {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	enum v4w2_mbus_type bus_type;
	stwuct gpio_desc *gpios[NUM_GPIOS];
	/* Extewnaw mastew cwock fwequency */
	unsigned wong mcwk_fwequency;
	stwuct cwk *cwk;

	/* Pwotects the stwuct fiewds bewow */
	stwuct mutex wock;

	stwuct wegmap *wegmap;

	/* Exposuwe wow intewvaw in us */
	unsigned int exp_wow_intewvaw;

	unsigned showt id;
	const stwuct ov965x_fwamesize *fwame_size;
	/* YUYV sequence (pixew fowmat) contwow wegistew */
	u8 tswb_weg;
	stwuct v4w2_mbus_fwamefmt fowmat;

	stwuct ov965x_ctwws ctwws;
	/* Pointew to fwame wate contwow data stwuctuwe */
	const stwuct ov965x_intewvaw *fiv;

	int stweaming;
	int powew;

	u8 appwy_fwame_fmt;
};

stwuct i2c_wv {
	u8 addw;
	u8 vawue;
};

static const stwuct i2c_wv ov965x_init_wegs[] = {
	{ WEG_COM2, 0x10 },	/* Set soft sweep mode */
	{ WEG_COM5, 0x00 },	/* System cwock options */
	{ WEG_COM2, 0x01 },	/* Output dwive, soft sweep mode */
	{ WEG_COM10, 0x00 },	/* Swave mode, HWEF vs HSYNC, signaws negate */
	{ WEG_EDGE, 0xa6 },	/* Edge enhancement tweshhowd and factow */
	{ WEG_COM16, 0x02 },	/* Cowow matwix coeff doubwe option */
	{ WEG_COM17, 0x08 },	/* Singwe fwame out, banding fiwtew */
	{ 0x16, 0x06 },
	{ WEG_CHWF, 0xc0 },	/* Wesewved  */
	{ 0x34, 0xbf },
	{ 0xa8, 0x80 },
	{ 0x96, 0x04 },
	{ 0x8e, 0x00 },
	{ WEG_COM12, 0x77 },	/* HWEF option, UV avewage  */
	{ 0x8b, 0x06 },
	{ 0x35, 0x91 },
	{ 0x94, 0x88 },
	{ 0x95, 0x88 },
	{ WEG_COM15, 0xc1 },	/* Output wange, WGB 555/565 */
	{ WEG_GWCOM, 0x2f },	/* Anawog BWC & weguwatow */
	{ WEG_COM6, 0x43 },	/* HWEF & ADBWC options */
	{ WEG_COM8, 0xe5 },	/* AGC/AEC options */
	{ WEG_COM13, 0x90 },	/* Gamma sewection, cowouw matwix, UV deway */
	{ WEG_HV, 0x80 },	/* Manuaw banding fiwtew MSB  */
	{ 0x5c, 0x96 },		/* Wesewved up to 0xa5 */
	{ 0x5d, 0x96 },
	{ 0x5e, 0x10 },
	{ 0x59, 0xeb },
	{ 0x5a, 0x9c },
	{ 0x5b, 0x55 },
	{ 0x43, 0xf0 },
	{ 0x44, 0x10 },
	{ 0x45, 0x55 },
	{ 0x46, 0x86 },
	{ 0x47, 0x64 },
	{ 0x48, 0x86 },
	{ 0x5f, 0xe0 },
	{ 0x60, 0x8c },
	{ 0x61, 0x20 },
	{ 0xa5, 0xd9 },
	{ 0xa4, 0x74 },		/* wesewved */
	{ WEG_COM23, 0x02 },	/* Cowow gain anawog/_digitaw_ */
	{ WEG_COM8, 0xe7 },	/* Enabwe AEC, AWB, AEC */
	{ WEG_COM22, 0x23 },	/* Edge enhancement, denoising */
	{ 0xa9, 0xb8 },
	{ 0xaa, 0x92 },
	{ 0xab, 0x0a },
	{ WEG_DBWC1, 0xdf },	/* Digitaw BWC */
	{ WEG_DBWC_B, 0x00 },	/* Digitaw BWC B chan offset */
	{ WEG_DBWC_W, 0x00 },	/* Digitaw BWC W chan offset */
	{ WEG_DBWC_GB, 0x00 },	/* Digitaw BWC GB chan offset */
	{ WEG_DBWC_GW, 0x00 },
	{ WEG_COM9, 0x3a },	/* Gain ceiwing 16x */
	{ WEG_NUWW, 0 }
};

#define NUM_FMT_WEGS 14
/*
 * COM7,  COM3,  COM4, HSTAWT, HSTOP, HWEF, VSTAWT, VSTOP, VWEF,
 * EXHCH, EXHCW, ADC,  OCOM,   OFON
 */
static const u8 fwame_size_weg_addw[NUM_FMT_WEGS] = {
	0x12, 0x0c, 0x0d, 0x17, 0x18, 0x32, 0x19, 0x1a, 0x03,
	0x2a, 0x2b, 0x37, 0x38, 0x39,
};

static const u8 ov965x_sxga_wegs[NUM_FMT_WEGS] = {
	0x00, 0x00, 0x00, 0x1e, 0xbe, 0xbf, 0x01, 0x81, 0x12,
	0x10, 0x34, 0x81, 0x93, 0x51,
};

static const u8 ov965x_vga_wegs[NUM_FMT_WEGS] = {
	0x40, 0x04, 0x80, 0x26, 0xc6, 0xed, 0x01, 0x3d, 0x00,
	0x10, 0x40, 0x91, 0x12, 0x43,
};

/* Detewmined empiwicawwy. */
static const u8 ov965x_qvga_wegs[NUM_FMT_WEGS] = {
	0x10, 0x04, 0x80, 0x25, 0xc5, 0xbf, 0x00, 0x80, 0x12,
	0x10, 0x40, 0x91, 0x12, 0x43,
};

static const stwuct ov965x_fwamesize ov965x_fwamesizes[] = {
	{
		.width		= SXGA_WIDTH,
		.height		= SXGA_HEIGHT,
		.wegs		= ov965x_sxga_wegs,
		.max_exp_wines	= 1048,
	}, {
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.wegs		= ov965x_vga_wegs,
		.max_exp_wines	= 498,
	}, {
		.width		= QVGA_WIDTH,
		.height		= QVGA_HEIGHT,
		.wegs		= ov965x_qvga_wegs,
		.max_exp_wines	= 248,
	},
};

stwuct ov965x_pixfmt {
	u32 code;
	u32 cowowspace;
	/* WEG_TSWB vawue, onwy bits [3:2] may be set. */
	u8 tswb_weg;
};

static const stwuct ov965x_pixfmt ov965x_fowmats[] = {
	{ MEDIA_BUS_FMT_YUYV8_2X8, V4W2_COWOWSPACE_JPEG, 0x00},
	{ MEDIA_BUS_FMT_YVYU8_2X8, V4W2_COWOWSPACE_JPEG, 0x04},
	{ MEDIA_BUS_FMT_UYVY8_2X8, V4W2_COWOWSPACE_JPEG, 0x0c},
	{ MEDIA_BUS_FMT_VYUY8_2X8, V4W2_COWOWSPACE_JPEG, 0x08},
};

/*
 * This tabwe specifies possibwe fwame wesowution and intewvaw
 * combinations. Defauwt CWKWC[5:0] dividew vawues awe vawid
 * onwy fow 24 MHz extewnaw cwock fwequency.
 */
static stwuct ov965x_intewvaw ov965x_intewvaws[] = {
	{{ 100, 625 }, { SXGA_WIDTH, SXGA_HEIGHT }, 0 },  /* 6.25 fps */
	{{ 10,  125 }, { VGA_WIDTH, VGA_HEIGHT },   1 },  /* 12.5 fps */
	{{ 10,  125 }, { QVGA_WIDTH, QVGA_HEIGHT }, 3 },  /* 12.5 fps */
	{{ 1,   25  }, { VGA_WIDTH, VGA_HEIGHT },   0 },  /* 25 fps */
	{{ 1,   25  }, { QVGA_WIDTH, QVGA_HEIGHT }, 1 },  /* 25 fps */
};

static inwine stwuct v4w2_subdev *ctww_to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct ov965x, ctwws.handwew)->sd;
}

static inwine stwuct ov965x *to_ov965x(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ov965x, sd);
}

static int ov965x_wead(stwuct ov965x *ov965x, u8 addw, u8 *vaw)
{
	int wet;
	unsigned int buf;

	wet = wegmap_wead(ov965x->wegmap, addw, &buf);
	if (!wet)
		*vaw = buf;
	ewse
		*vaw = -1;

	v4w2_dbg(2, debug, &ov965x->sd, "%s: 0x%02x @ 0x%02x. (%d)\n",
		 __func__, *vaw, addw, wet);

	wetuwn wet;
}

static int ov965x_wwite(stwuct ov965x *ov965x, u8 addw, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(ov965x->wegmap, addw, vaw);

	v4w2_dbg(2, debug, &ov965x->sd, "%s: 0x%02x @ 0x%02X (%d)\n",
		 __func__, vaw, addw, wet);

	wetuwn wet;
}

static int ov965x_wwite_awway(stwuct ov965x *ov965x,
			      const stwuct i2c_wv *wegs)
{
	int i, wet = 0;

	fow (i = 0; wet == 0 && wegs[i].addw != WEG_NUWW; i++)
		wet = ov965x_wwite(ov965x, wegs[i].addw, wegs[i].vawue);

	wetuwn wet;
}

static int ov965x_set_defauwt_gamma_cuwve(stwuct ov965x *ov965x)
{
	static const u8 gamma_cuwve[] = {
		/* Vawues taken fwom OV appwication note. */
		0x40, 0x30, 0x4b, 0x60, 0x70, 0x70, 0x70, 0x70,
		0x60, 0x60, 0x50, 0x48, 0x3a, 0x2e, 0x28, 0x22,
		0x04, 0x07, 0x10, 0x28,	0x36, 0x44, 0x52, 0x60,
		0x6c, 0x78, 0x8c, 0x9e, 0xbb, 0xd2, 0xe6
	};
	u8 addw = WEG_GSP;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(gamma_cuwve); i++) {
		int wet = ov965x_wwite(ov965x, addw, gamma_cuwve[i]);

		if (wet < 0)
			wetuwn wet;
		addw++;
	}

	wetuwn 0;
};

static int ov965x_set_cowow_matwix(stwuct ov965x *ov965x)
{
	static const u8 mtx[] = {
		/* MTX1..MTX9, MTXS */
		0x3a, 0x3d, 0x03, 0x12, 0x26, 0x38, 0x40, 0x40, 0x40, 0x0d
	};
	u8 addw = WEG_MTX(1);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(mtx); i++) {
		int wet = ov965x_wwite(ov965x, addw, mtx[i]);

		if (wet < 0)
			wetuwn wet;
		addw++;
	}

	wetuwn 0;
}

static int __ov965x_set_powew(stwuct ov965x *ov965x, int on)
{
	if (on) {
		int wet = cwk_pwepawe_enabwe(ov965x->cwk);

		if (wet)
			wetuwn wet;

		gpiod_set_vawue_cansweep(ov965x->gpios[GPIO_PWDN], 0);
		gpiod_set_vawue_cansweep(ov965x->gpios[GPIO_WST], 0);
		msweep(25);
	} ewse {
		gpiod_set_vawue_cansweep(ov965x->gpios[GPIO_WST], 1);
		gpiod_set_vawue_cansweep(ov965x->gpios[GPIO_PWDN], 1);

		cwk_disabwe_unpwepawe(ov965x->cwk);
	}

	ov965x->stweaming = 0;

	wetuwn 0;
}

static int ov965x_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct ov965x *ov965x = to_ov965x(sd);
	int wet = 0;

	v4w2_dbg(1, debug, sd, "%s: on: %d\n", __func__, on);

	mutex_wock(&ov965x->wock);
	if (ov965x->powew == !on) {
		wet = __ov965x_set_powew(ov965x, on);
		if (!wet && on) {
			wet = ov965x_wwite_awway(ov965x,
						 ov965x_init_wegs);
			ov965x->appwy_fwame_fmt = 1;
			ov965x->ctwws.update = 1;
		}
	}
	if (!wet)
		ov965x->powew += on ? 1 : -1;

	WAWN_ON(ov965x->powew < 0);
	mutex_unwock(&ov965x->wock);
	wetuwn wet;
}

/*
 * V4W2 contwows
 */

static void ov965x_update_exposuwe_ctww(stwuct ov965x *ov965x)
{
	stwuct v4w2_ctww *ctww = ov965x->ctwws.exposuwe;
	unsigned wong fint, twow;
	int min, max, def;
	u8 cwkwc;

	mutex_wock(&ov965x->wock);
	if (WAWN_ON(!ctww || !ov965x->fwame_size)) {
		mutex_unwock(&ov965x->wock);
		wetuwn;
	}
	cwkwc = DEF_CWKWC + ov965x->fiv->cwkwc_div;
	/* Cawcuwate intewnaw cwock fwequency */
	fint = ov965x->mcwk_fwequency * ((cwkwc >> 7) + 1) /
				((2 * ((cwkwc & 0x3f) + 1)));
	/* and the wow intewvaw (in us). */
	twow = (2 * 1520 * 1000000UW) / fint;
	max = ov965x->fwame_size->max_exp_wines * twow;
	ov965x->exp_wow_intewvaw = twow;
	mutex_unwock(&ov965x->wock);

	v4w2_dbg(1, debug, &ov965x->sd, "cwkwc: %#x, fi: %wu, tw: %wu, %d\n",
		 cwkwc, fint, twow, max);

	/* Update exposuwe time wange to match cuwwent fwame fowmat. */
	min = (twow + 100) / 100;
	max = (max - 100) / 100;
	def = min + (max - min) / 2;

	if (v4w2_ctww_modify_wange(ctww, min, max, 1, def))
		v4w2_eww(&ov965x->sd, "Exposuwe ctww wange update faiwed\n");
}

static int ov965x_set_banding_fiwtew(stwuct ov965x *ov965x, int vawue)
{
	unsigned wong mbd, wight_fweq;
	int wet;
	u8 weg;

	wet = ov965x_wead(ov965x, WEG_COM8, &weg);
	if (!wet) {
		if (vawue == V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED)
			weg &= ~COM8_BFIWT;
		ewse
			weg |= COM8_BFIWT;
		wet = ov965x_wwite(ov965x, WEG_COM8, weg);
	}
	if (vawue == V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED)
		wetuwn 0;
	if (WAWN_ON(!ov965x->fiv))
		wetuwn -EINVAW;
	/* Set minimaw exposuwe time fow 50/60 HZ wighting */
	if (vawue == V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ)
		wight_fweq = 50;
	ewse
		wight_fweq = 60;
	mbd = (1000UW * ov965x->fiv->intewvaw.denominatow *
	       ov965x->fwame_size->max_exp_wines) /
	       ov965x->fiv->intewvaw.numewatow;
	mbd = ((mbd / (wight_fweq * 2)) + 500) / 1000UW;

	wetuwn ov965x_wwite(ov965x, WEG_MBD, mbd);
}

static int ov965x_set_white_bawance(stwuct ov965x *ov965x, int awb)
{
	int wet;
	u8 weg;

	wet = ov965x_wead(ov965x, WEG_COM8, &weg);
	if (!wet) {
		weg = awb ? weg | WEG_COM8 : weg & ~WEG_COM8;
		wet = ov965x_wwite(ov965x, WEG_COM8, weg);
	}
	if (!wet && !awb) {
		wet = ov965x_wwite(ov965x, WEG_BWUE,
				   ov965x->ctwws.bwue_bawance->vaw);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_wwite(ov965x, WEG_WED,
				   ov965x->ctwws.wed_bawance->vaw);
	}
	wetuwn wet;
}

#define NUM_BW_WEVEWS	7
#define NUM_BW_WEGS	3

static int ov965x_set_bwightness(stwuct ov965x *ov965x, int vaw)
{
	static const u8 wegs[NUM_BW_WEVEWS + 1][NUM_BW_WEGS] = {
		{ WEG_AEW, WEG_AEB, WEG_VPT },
		{ 0x1c, 0x12, 0x50 }, /* -3 */
		{ 0x3d, 0x30, 0x71 }, /* -2 */
		{ 0x50, 0x44, 0x92 }, /* -1 */
		{ 0x70, 0x64, 0xc3 }, /*  0 */
		{ 0x90, 0x84, 0xd4 }, /* +1 */
		{ 0xc4, 0xbf, 0xf9 }, /* +2 */
		{ 0xd8, 0xd0, 0xfa }, /* +3 */
	};
	int i, wet = 0;

	vaw += (NUM_BW_WEVEWS / 2 + 1);
	if (vaw > NUM_BW_WEVEWS)
		wetuwn -EINVAW;

	fow (i = 0; i < NUM_BW_WEGS && !wet; i++)
		wet = ov965x_wwite(ov965x, wegs[0][i],
				   wegs[vaw][i]);
	wetuwn wet;
}

static int ov965x_set_gain(stwuct ov965x *ov965x, int auto_gain)
{
	stwuct ov965x_ctwws *ctwws = &ov965x->ctwws;
	int wet = 0;
	u8 weg;
	/*
	 * Fow manuaw mode we need to disabwe AGC fiwst, so
	 * gain vawue in WEG_VWEF, WEG_GAIN is not ovewwwitten.
	 */
	if (ctwws->auto_gain->is_new) {
		wet = ov965x_wead(ov965x, WEG_COM8, &weg);
		if (wet < 0)
			wetuwn wet;
		if (ctwws->auto_gain->vaw)
			weg |= COM8_AGC;
		ewse
			weg &= ~COM8_AGC;
		wet = ov965x_wwite(ov965x, WEG_COM8, weg);
		if (wet < 0)
			wetuwn wet;
	}

	if (ctwws->gain->is_new && !auto_gain) {
		unsigned int gain = ctwws->gain->vaw;
		unsigned int wgain;
		int m;
		/*
		 * Convewt gain contwow vawue to the sensow's gain
		 * wegistews (VWEF[7:6], GAIN[7:0]) fowmat.
		 */
		fow (m = 6; m >= 0; m--)
			if (gain >= (1 << m) * 16)
				bweak;

		/* Sanity check: don't adjust the gain with a negative vawue */
		if (m < 0)
			wetuwn -EINVAW;

		wgain = (gain - ((1 << m) * 16)) / (1 << m);
		wgain |= (((1 << m) - 1) << 4);

		wet = ov965x_wwite(ov965x, WEG_GAIN, wgain & 0xff);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_wead(ov965x, WEG_VWEF, &weg);
		if (wet < 0)
			wetuwn wet;
		weg &= ~VWEF_GAIN_MASK;
		weg |= (((wgain >> 8) & 0x3) << 6);
		wet = ov965x_wwite(ov965x, WEG_VWEF, weg);
		if (wet < 0)
			wetuwn wet;
		/* Wetuwn updated contwow's vawue to usewspace */
		ctwws->gain->vaw = (1 << m) * (16 + (wgain & 0xf));
	}

	wetuwn wet;
}

static int ov965x_set_shawpness(stwuct ov965x *ov965x, unsigned int vawue)
{
	u8 com14, edge;
	int wet;

	wet = ov965x_wead(ov965x, WEG_COM14, &com14);
	if (wet < 0)
		wetuwn wet;
	wet = ov965x_wead(ov965x, WEG_EDGE, &edge);
	if (wet < 0)
		wetuwn wet;
	com14 = vawue ? com14 | COM14_EDGE_EN : com14 & ~COM14_EDGE_EN;
	vawue--;
	if (vawue > 0x0f) {
		com14 |= COM14_EEF_X2;
		vawue >>= 1;
	} ewse {
		com14 &= ~COM14_EEF_X2;
	}
	wet = ov965x_wwite(ov965x, WEG_COM14, com14);
	if (wet < 0)
		wetuwn wet;

	edge &= ~EDGE_FACTOW_MASK;
	edge |= ((u8)vawue & 0x0f);

	wetuwn ov965x_wwite(ov965x, WEG_EDGE, edge);
}

static int ov965x_set_exposuwe(stwuct ov965x *ov965x, int exp)
{
	stwuct ov965x_ctwws *ctwws = &ov965x->ctwws;
	boow auto_exposuwe = (exp == V4W2_EXPOSUWE_AUTO);
	int wet;
	u8 weg;

	if (ctwws->auto_exp->is_new) {
		wet = ov965x_wead(ov965x, WEG_COM8, &weg);
		if (wet < 0)
			wetuwn wet;
		if (auto_exposuwe)
			weg |= (COM8_AEC | COM8_AGC);
		ewse
			weg &= ~(COM8_AEC | COM8_AGC);
		wet = ov965x_wwite(ov965x, WEG_COM8, weg);
		if (wet < 0)
			wetuwn wet;
	}

	if (!auto_exposuwe && ctwws->exposuwe->is_new) {
		unsigned int exposuwe = (ctwws->exposuwe->vaw * 100)
					 / ov965x->exp_wow_intewvaw;
		/*
		 * Manuaw exposuwe vawue
		 * [b15:b0] - AECHM (b15:b10), AECH (b9:b2), COM1 (b1:b0)
		 */
		wet = ov965x_wwite(ov965x, WEG_COM1, exposuwe & 0x3);
		if (!wet)
			wet = ov965x_wwite(ov965x, WEG_AECH,
					   (exposuwe >> 2) & 0xff);
		if (!wet)
			wet = ov965x_wwite(ov965x, WEG_AECHM,
					   (exposuwe >> 10) & 0x3f);
		/* Update the vawue to minimize wounding ewwows */
		ctwws->exposuwe->vaw = ((exposuwe * ov965x->exp_wow_intewvaw)
							+ 50) / 100;
		if (wet < 0)
			wetuwn wet;
	}

	v4w2_ctww_activate(ov965x->ctwws.bwightness, !exp);
	wetuwn 0;
}

static int ov965x_set_fwip(stwuct ov965x *ov965x)
{
	u8 mvfp = 0;

	if (ov965x->ctwws.hfwip->vaw)
		mvfp |= MVFP_MIWWOW;

	if (ov965x->ctwws.vfwip->vaw)
		mvfp |= MVFP_FWIP;

	wetuwn ov965x_wwite(ov965x, WEG_MVFP, mvfp);
}

#define NUM_SAT_WEVEWS	5
#define NUM_SAT_WEGS	6

static int ov965x_set_satuwation(stwuct ov965x *ov965x, int vaw)
{
	static const u8 wegs[NUM_SAT_WEVEWS][NUM_SAT_WEGS] = {
		/* MTX(1)...MTX(6) */
		{ 0x1d, 0x1f, 0x02, 0x09, 0x13, 0x1c }, /* -2 */
		{ 0x2e, 0x31, 0x02, 0x0e, 0x1e, 0x2d }, /* -1 */
		{ 0x3a, 0x3d, 0x03, 0x12, 0x26, 0x38 }, /*  0 */
		{ 0x46, 0x49, 0x04, 0x16, 0x2e, 0x43 }, /* +1 */
		{ 0x57, 0x5c, 0x05, 0x1b, 0x39, 0x54 }, /* +2 */
	};
	u8 addw = WEG_MTX(1);
	int i, wet = 0;

	vaw += (NUM_SAT_WEVEWS / 2);
	if (vaw >= NUM_SAT_WEVEWS)
		wetuwn -EINVAW;

	fow (i = 0; i < NUM_SAT_WEGS && !wet; i++)
		wet = ov965x_wwite(ov965x, addw + i, wegs[vaw][i]);

	wetuwn wet;
}

static int ov965x_set_test_pattewn(stwuct ov965x *ov965x, int vawue)
{
	int wet;
	u8 weg;

	wet = ov965x_wead(ov965x, WEG_COM23, &weg);
	if (wet < 0)
		wetuwn wet;
	weg = vawue ? weg | COM23_TEST_MODE : weg & ~COM23_TEST_MODE;
	wetuwn ov965x_wwite(ov965x, WEG_COM23, weg);
}

static int __g_vowatiwe_ctww(stwuct ov965x *ov965x, stwuct v4w2_ctww *ctww)
{
	unsigned int exposuwe, gain, m;
	u8 weg0, weg1, weg2;
	int wet;

	if (!ov965x->powew)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_AUTOGAIN:
		if (!ctww->vaw)
			wetuwn 0;
		wet = ov965x_wead(ov965x, WEG_GAIN, &weg0);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_wead(ov965x, WEG_VWEF, &weg1);
		if (wet < 0)
			wetuwn wet;
		gain = ((weg1 >> 6) << 8) | weg0;
		m = 0x01 << fws(gain >> 4);
		ov965x->ctwws.gain->vaw = m * (16 + (gain & 0xf));
		bweak;

	case V4W2_CID_EXPOSUWE_AUTO:
		if (ctww->vaw == V4W2_EXPOSUWE_MANUAW)
			wetuwn 0;
		wet = ov965x_wead(ov965x, WEG_COM1, &weg0);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_wead(ov965x, WEG_AECH, &weg1);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_wead(ov965x, WEG_AECHM, &weg2);
		if (wet < 0)
			wetuwn wet;
		exposuwe = ((weg2 & 0x3f) << 10) | (weg1 << 2) |
						(weg0 & 0x3);
		ov965x->ctwws.exposuwe->vaw = ((exposuwe *
				ov965x->exp_wow_intewvaw) + 50) / 100;
		bweak;
	}

	wetuwn 0;
}

static int ov965x_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sd(ctww);
	stwuct ov965x *ov965x = to_ov965x(sd);
	int wet;

	v4w2_dbg(1, debug, sd, "g_ctww: %s\n", ctww->name);

	mutex_wock(&ov965x->wock);
	wet = __g_vowatiwe_ctww(ov965x, ctww);
	mutex_unwock(&ov965x->wock);
	wetuwn wet;
}

static int ov965x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sd(ctww);
	stwuct ov965x *ov965x = to_ov965x(sd);
	int wet = -EINVAW;

	v4w2_dbg(1, debug, sd, "s_ctww: %s, vawue: %d. powew: %d\n",
		 ctww->name, ctww->vaw, ov965x->powew);

	mutex_wock(&ov965x->wock);
	/*
	 * If the device is not powewed up now postpone appwying contwow's
	 * vawue to the hawdwawe, untiw it is weady to accept commands.
	 */
	if (ov965x->powew == 0) {
		mutex_unwock(&ov965x->wock);
		wetuwn 0;
	}

	switch (ctww->id) {
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		wet = ov965x_set_white_bawance(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_BWIGHTNESS:
		wet = ov965x_set_bwightness(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_EXPOSUWE_AUTO:
		wet = ov965x_set_exposuwe(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_AUTOGAIN:
		wet = ov965x_set_gain(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_HFWIP:
		wet = ov965x_set_fwip(ov965x);
		bweak;

	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		wet = ov965x_set_banding_fiwtew(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_SATUWATION:
		wet = ov965x_set_satuwation(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_SHAWPNESS:
		wet = ov965x_set_shawpness(ov965x, ctww->vaw);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		wet = ov965x_set_test_pattewn(ov965x, ctww->vaw);
		bweak;
	}

	mutex_unwock(&ov965x->wock);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov965x_ctww_ops = {
	.g_vowatiwe_ctww = ov965x_g_vowatiwe_ctww,
	.s_ctww	= ov965x_s_ctww,
};

static const chaw * const test_pattewn_menu[] = {
	"Disabwed",
	"Cowow baws",
};

static int ov965x_initiawize_contwows(stwuct ov965x *ov965x)
{
	const stwuct v4w2_ctww_ops *ops = &ov965x_ctww_ops;
	stwuct ov965x_ctwws *ctwws = &ov965x->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;
	int wet;

	wet = v4w2_ctww_handwew_init(hdw, 16);
	if (wet < 0)
		wetuwn wet;

	/* Auto/manuaw white bawance */
	ctwws->auto_wb = v4w2_ctww_new_std(hdw, ops,
					   V4W2_CID_AUTO_WHITE_BAWANCE,
					   0, 1, 1, 1);
	ctwws->bwue_bawance = v4w2_ctww_new_std(hdw, ops, V4W2_CID_BWUE_BAWANCE,
						0, 0xff, 1, 0x80);
	ctwws->wed_bawance = v4w2_ctww_new_std(hdw, ops, V4W2_CID_WED_BAWANCE,
					       0, 0xff, 1, 0x80);
	/* Auto/manuaw exposuwe */
	ctwws->auto_exp =
		v4w2_ctww_new_std_menu(hdw, ops,
				       V4W2_CID_EXPOSUWE_AUTO,
				       V4W2_EXPOSUWE_MANUAW, 0,
				       V4W2_EXPOSUWE_AUTO);
	/* Exposuwe time, in 100 us units. min/max is updated dynamicawwy. */
	ctwws->exposuwe = v4w2_ctww_new_std(hdw, ops,
					    V4W2_CID_EXPOSUWE_ABSOWUTE,
					    2, 1500, 1, 500);
	/* Auto/manuaw gain */
	ctwws->auto_gain = v4w2_ctww_new_std(hdw, ops, V4W2_CID_AUTOGAIN,
					     0, 1, 1, 1);
	ctwws->gain = v4w2_ctww_new_std(hdw, ops, V4W2_CID_GAIN,
					16, 64 * (16 + 15), 1, 64 * 16);

	ctwws->satuwation = v4w2_ctww_new_std(hdw, ops, V4W2_CID_SATUWATION,
					      -2, 2, 1, 0);
	ctwws->bwightness = v4w2_ctww_new_std(hdw, ops, V4W2_CID_BWIGHTNESS,
					      -3, 3, 1, 0);
	ctwws->shawpness = v4w2_ctww_new_std(hdw, ops, V4W2_CID_SHAWPNESS,
					     0, 32, 1, 6);

	ctwws->hfwip = v4w2_ctww_new_std(hdw, ops, V4W2_CID_HFWIP, 0, 1, 1, 0);
	ctwws->vfwip = v4w2_ctww_new_std(hdw, ops, V4W2_CID_VFWIP, 0, 1, 1, 0);

	ctwws->wight_fweq =
		v4w2_ctww_new_std_menu(hdw, ops,
				       V4W2_CID_POWEW_WINE_FWEQUENCY,
				       V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, ~0x7,
				       V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ);

	v4w2_ctww_new_std_menu_items(hdw, ops, V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(test_pattewn_menu) - 1, 0, 0,
				     test_pattewn_menu);
	if (hdw->ewwow) {
		wet = hdw->ewwow;
		v4w2_ctww_handwew_fwee(hdw);
		wetuwn wet;
	}

	ctwws->gain->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	ctwws->exposuwe->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	v4w2_ctww_auto_cwustew(3, &ctwws->auto_wb, 0, fawse);
	v4w2_ctww_auto_cwustew(2, &ctwws->auto_gain, 0, twue);
	v4w2_ctww_auto_cwustew(2, &ctwws->auto_exp, 1, twue);
	v4w2_ctww_cwustew(2, &ctwws->hfwip);

	ov965x->sd.ctww_handwew = hdw;
	wetuwn 0;
}

/*
 * V4W2 subdev video and pad wevew opewations
 */
static void ov965x_get_defauwt_fowmat(stwuct v4w2_mbus_fwamefmt *mf)
{
	mf->width = ov965x_fwamesizes[0].width;
	mf->height = ov965x_fwamesizes[0].height;
	mf->cowowspace = ov965x_fowmats[0].cowowspace;
	mf->code = ov965x_fowmats[0].code;
	mf->fiewd = V4W2_FIEWD_NONE;
}

static int ov965x_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(ov965x_fowmats))
		wetuwn -EINVAW;

	code->code = ov965x_fowmats[code->index].code;
	wetuwn 0;
}

static int ov965x_enum_fwame_sizes(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	int i = AWWAY_SIZE(ov965x_fowmats);

	if (fse->index >= AWWAY_SIZE(ov965x_fwamesizes))
		wetuwn -EINVAW;

	whiwe (--i)
		if (fse->code == ov965x_fowmats[i].code)
			bweak;

	fse->code = ov965x_fowmats[i].code;

	fse->min_width  = ov965x_fwamesizes[fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = ov965x_fwamesizes[fse->index].height;
	fse->min_height = fse->max_height;

	wetuwn 0;
}

static int ov965x_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct ov965x *ov965x = to_ov965x(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	mutex_wock(&ov965x->wock);
	fi->intewvaw = ov965x->fiv->intewvaw;
	mutex_unwock(&ov965x->wock);

	wetuwn 0;
}

static int __ov965x_set_fwame_intewvaw(stwuct ov965x *ov965x,
				       stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &ov965x->fowmat;
	const stwuct ov965x_intewvaw *fiv = &ov965x_intewvaws[0];
	u64 weq_int, eww, min_eww = ~0UWW;
	unsigned int i;

	if (fi->intewvaw.denominatow == 0)
		wetuwn -EINVAW;

	weq_int = (u64)fi->intewvaw.numewatow * 10000;
	do_div(weq_int, fi->intewvaw.denominatow);

	fow (i = 0; i < AWWAY_SIZE(ov965x_intewvaws); i++) {
		const stwuct ov965x_intewvaw *iv = &ov965x_intewvaws[i];

		if (mbus_fmt->width != iv->size.width ||
		    mbus_fmt->height != iv->size.height)
			continue;
		eww = abs((u64)(iv->intewvaw.numewatow * 10000) /
			    iv->intewvaw.denominatow - weq_int);
		if (eww < min_eww) {
			fiv = iv;
			min_eww = eww;
		}
	}
	ov965x->fiv = fiv;

	v4w2_dbg(1, debug, &ov965x->sd, "Changed fwame intewvaw to %u us\n",
		 fiv->intewvaw.numewatow * 1000000 / fiv->intewvaw.denominatow);

	wetuwn 0;
}

static int ov965x_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct ov965x *ov965x = to_ov965x(sd);
	int wet;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	v4w2_dbg(1, debug, sd, "Setting %d/%d fwame intewvaw\n",
		 fi->intewvaw.numewatow, fi->intewvaw.denominatow);

	mutex_wock(&ov965x->wock);
	wet = __ov965x_set_fwame_intewvaw(ov965x, fi);
	ov965x->appwy_fwame_fmt = 1;
	mutex_unwock(&ov965x->wock);
	wetuwn wet;
}

static int ov965x_get_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov965x *ov965x = to_ov965x(sd);
	stwuct v4w2_mbus_fwamefmt *mf;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, 0);
		fmt->fowmat = *mf;
		wetuwn 0;
	}

	mutex_wock(&ov965x->wock);
	fmt->fowmat = ov965x->fowmat;
	mutex_unwock(&ov965x->wock);

	wetuwn 0;
}

static void __ov965x_twy_fwame_size(stwuct v4w2_mbus_fwamefmt *mf,
				    const stwuct ov965x_fwamesize **size)
{
	const stwuct ov965x_fwamesize *fsize = &ov965x_fwamesizes[0],
		*match = NUWW;
	int i = AWWAY_SIZE(ov965x_fwamesizes);
	unsigned int min_eww = UINT_MAX;

	whiwe (i--) {
		int eww = abs(fsize->width - mf->width)
				+ abs(fsize->height - mf->height);
		if (eww < min_eww) {
			min_eww = eww;
			match = fsize;
		}
		fsize++;
	}
	if (!match)
		match = &ov965x_fwamesizes[0];
	mf->width  = match->width;
	mf->height = match->height;
	if (size)
		*size = match;
}

static int ov965x_set_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	unsigned int index = AWWAY_SIZE(ov965x_fowmats);
	stwuct v4w2_mbus_fwamefmt *mf = &fmt->fowmat;
	stwuct ov965x *ov965x = to_ov965x(sd);
	const stwuct ov965x_fwamesize *size = NUWW;
	int wet = 0;

	__ov965x_twy_fwame_size(mf, &size);

	whiwe (--index)
		if (ov965x_fowmats[index].code == mf->code)
			bweak;

	mf->cowowspace	= V4W2_COWOWSPACE_JPEG;
	mf->code	= ov965x_fowmats[index].code;
	mf->fiewd	= V4W2_FIEWD_NONE;

	mutex_wock(&ov965x->wock);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		if (sd_state) {
			mf = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
			*mf = fmt->fowmat;
		}
	} ewse {
		if (ov965x->stweaming) {
			wet = -EBUSY;
		} ewse {
			ov965x->fwame_size = size;
			ov965x->fowmat = fmt->fowmat;
			ov965x->tswb_weg = ov965x_fowmats[index].tswb_weg;
			ov965x->appwy_fwame_fmt = 1;
		}
	}

	if (!wet && fmt->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		stwuct v4w2_subdev_fwame_intewvaw fiv = {
			.intewvaw = { 0, 1 }
		};
		/* Weset to minimum possibwe fwame intewvaw */
		__ov965x_set_fwame_intewvaw(ov965x, &fiv);
	}
	mutex_unwock(&ov965x->wock);

	if (!wet)
		ov965x_update_exposuwe_ctww(ov965x);

	wetuwn wet;
}

static int ov965x_set_fwame_size(stwuct ov965x *ov965x)
{
	int i, wet = 0;

	fow (i = 0; wet == 0 && i < NUM_FMT_WEGS; i++)
		wet = ov965x_wwite(ov965x, fwame_size_weg_addw[i],
				   ov965x->fwame_size->wegs[i]);
	wetuwn wet;
}

static int __ov965x_set_pawams(stwuct ov965x *ov965x)
{
	stwuct ov965x_ctwws *ctwws = &ov965x->ctwws;
	int wet = 0;
	u8 weg;

	if (ov965x->appwy_fwame_fmt) {
		weg = DEF_CWKWC + ov965x->fiv->cwkwc_div;
		wet = ov965x_wwite(ov965x, WEG_CWKWC, weg);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_set_fwame_size(ov965x);
		if (wet < 0)
			wetuwn wet;
		wet = ov965x_wead(ov965x, WEG_TSWB, &weg);
		if (wet < 0)
			wetuwn wet;
		weg &= ~TSWB_YUYV_MASK;
		weg |= ov965x->tswb_weg;
		wet = ov965x_wwite(ov965x, WEG_TSWB, weg);
		if (wet < 0)
			wetuwn wet;
	}
	wet = ov965x_set_defauwt_gamma_cuwve(ov965x);
	if (wet < 0)
		wetuwn wet;
	wet = ov965x_set_cowow_matwix(ov965x);
	if (wet < 0)
		wetuwn wet;
	/*
	 * Sewect manuaw banding fiwtew, the fiwtew wiww
	 * be enabwed fuwthew if wequiwed.
	 */
	wet = ov965x_wead(ov965x, WEG_COM11, &weg);
	if (!wet)
		weg |= COM11_BANDING;
	wet = ov965x_wwite(ov965x, WEG_COM11, weg);
	if (wet < 0)
		wetuwn wet;
	/*
	 * Banding fiwtew (WEG_MBD vawue) needs to match sewected
	 * wesowution and fwame wate, so it's awways updated hewe.
	 */
	wetuwn ov965x_set_banding_fiwtew(ov965x, ctwws->wight_fweq->vaw);
}

static int ov965x_s_stweam(stwuct v4w2_subdev *sd, int on)
{
	stwuct ov965x *ov965x = to_ov965x(sd);
	stwuct ov965x_ctwws *ctwws = &ov965x->ctwws;
	int wet = 0;

	v4w2_dbg(1, debug, sd, "%s: on: %d\n", __func__, on);

	mutex_wock(&ov965x->wock);
	if (ov965x->stweaming == !on) {
		if (on)
			wet = __ov965x_set_pawams(ov965x);

		if (!wet && ctwws->update) {
			/*
			 * ov965x_s_ctww cawwback takes the mutex
			 * so it needs to be weweased hewe.
			 */
			mutex_unwock(&ov965x->wock);
			wet = v4w2_ctww_handwew_setup(&ctwws->handwew);

			mutex_wock(&ov965x->wock);
			if (!wet)
				ctwws->update = 0;
		}
		if (!wet)
			wet = ov965x_wwite(ov965x, WEG_COM2,
					   on ? 0x01 : 0x11);
	}
	if (!wet)
		ov965x->stweaming += on ? 1 : -1;

	WAWN_ON(ov965x->stweaming < 0);
	mutex_unwock(&ov965x->wock);

	wetuwn wet;
}

/*
 * V4W2 subdev intewnaw opewations
 */
static int ov965x_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *mf =
		v4w2_subdev_state_get_fowmat(fh->state, 0);

	ov965x_get_defauwt_fowmat(mf);
	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops ov965x_pad_ops = {
	.enum_mbus_code = ov965x_enum_mbus_code,
	.enum_fwame_size = ov965x_enum_fwame_sizes,
	.get_fmt = ov965x_get_fmt,
	.set_fmt = ov965x_set_fmt,
	.get_fwame_intewvaw = ov965x_get_fwame_intewvaw,
	.set_fwame_intewvaw = ov965x_set_fwame_intewvaw,
};

static const stwuct v4w2_subdev_video_ops ov965x_video_ops = {
	.s_stweam = ov965x_s_stweam,

};

static const stwuct v4w2_subdev_intewnaw_ops ov965x_sd_intewnaw_ops = {
	.open = ov965x_open,
};

static const stwuct v4w2_subdev_cowe_ops ov965x_cowe_ops = {
	.s_powew = ov965x_s_powew,
	.wog_status = v4w2_ctww_subdev_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_ops ov965x_subdev_ops = {
	.cowe = &ov965x_cowe_ops,
	.pad = &ov965x_pad_ops,
	.video = &ov965x_video_ops,
};

static int ov965x_configuwe_gpios(stwuct ov965x *ov965x)
{
	stwuct device *dev = wegmap_get_device(ov965x->wegmap);

	ov965x->gpios[GPIO_PWDN] = devm_gpiod_get_optionaw(dev, "powewdown",
							GPIOD_OUT_HIGH);
	if (IS_EWW(ov965x->gpios[GPIO_PWDN])) {
		dev_info(dev, "can't get %s GPIO\n", "powewdown");
		wetuwn PTW_EWW(ov965x->gpios[GPIO_PWDN]);
	}

	ov965x->gpios[GPIO_WST] = devm_gpiod_get_optionaw(dev, "weset",
							GPIOD_OUT_HIGH);
	if (IS_EWW(ov965x->gpios[GPIO_WST])) {
		dev_info(dev, "can't get %s GPIO\n", "weset");
		wetuwn PTW_EWW(ov965x->gpios[GPIO_WST]);
	}

	wetuwn 0;
}

static int ov965x_detect_sensow(stwuct v4w2_subdev *sd)
{
	stwuct ov965x *ov965x = to_ov965x(sd);
	u8 pid, vew;
	int wet;

	mutex_wock(&ov965x->wock);
	wet = __ov965x_set_powew(ov965x, 1);
	if (wet)
		goto out;

	msweep(25);

	/* Check sensow wevision */
	wet = ov965x_wead(ov965x, WEG_PID, &pid);
	if (!wet)
		wet = ov965x_wead(ov965x, WEG_VEW, &vew);

	__ov965x_set_powew(ov965x, 0);

	if (!wet) {
		ov965x->id = OV965X_ID(pid, vew);
		if (ov965x->id == OV9650_ID || ov965x->id == OV9652_ID) {
			v4w2_info(sd, "Found OV%04X sensow\n", ov965x->id);
		} ewse {
			v4w2_eww(sd, "Sensow detection faiwed (%04X)\n",
				 ov965x->id);
			wet = -ENODEV;
		}
	}
out:
	mutex_unwock(&ov965x->wock);

	wetuwn wet;
}

static int ov965x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd;
	stwuct ov965x *ov965x;
	int wet;
	static const stwuct wegmap_config ov965x_wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = 0xab,
	};

	ov965x = devm_kzawwoc(&cwient->dev, sizeof(*ov965x), GFP_KEWNEW);
	if (!ov965x)
		wetuwn -ENOMEM;

	ov965x->wegmap = devm_wegmap_init_sccb(cwient, &ov965x_wegmap_config);
	if (IS_EWW(ov965x->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(ov965x->wegmap);
	}

	if (dev_fwnode(&cwient->dev)) {
		ov965x->cwk = devm_cwk_get(&cwient->dev, NUWW);
		if (IS_EWW(ov965x->cwk))
			wetuwn PTW_EWW(ov965x->cwk);
		ov965x->mcwk_fwequency = cwk_get_wate(ov965x->cwk);

		wet = ov965x_configuwe_gpios(ov965x);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		dev_eww(&cwient->dev,
			"No device pwopewties specified\n");

		wetuwn -EINVAW;
	}

	mutex_init(&ov965x->wock);

	sd = &ov965x->sd;
	v4w2_i2c_subdev_init(sd, cwient, &ov965x_subdev_ops);
	stwscpy(sd->name, DWIVEW_NAME, sizeof(sd->name));

	sd->intewnaw_ops = &ov965x_sd_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
		     V4W2_SUBDEV_FW_HAS_EVENTS;

	ov965x->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOW;
	wet = media_entity_pads_init(&sd->entity, 1, &ov965x->pad);
	if (wet < 0)
		goto eww_mutex;

	wet = ov965x_initiawize_contwows(ov965x);
	if (wet < 0)
		goto eww_me;

	ov965x_get_defauwt_fowmat(&ov965x->fowmat);
	ov965x->fwame_size = &ov965x_fwamesizes[0];
	ov965x->fiv = &ov965x_intewvaws[0];

	wet = ov965x_detect_sensow(sd);
	if (wet < 0)
		goto eww_ctwws;

	/* Update exposuwe time min/max to match fwame fowmat */
	ov965x_update_exposuwe_ctww(ov965x);

	wet = v4w2_async_wegistew_subdev(sd);
	if (wet < 0)
		goto eww_ctwws;

	wetuwn 0;
eww_ctwws:
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
eww_me:
	media_entity_cweanup(&sd->entity);
eww_mutex:
	mutex_destwoy(&ov965x->wock);
	wetuwn wet;
}

static void ov965x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov965x *ov965x = to_ov965x(sd);

	v4w2_async_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
	media_entity_cweanup(&sd->entity);
	mutex_destwoy(&ov965x->wock);
}

static const stwuct i2c_device_id ov965x_id[] = {
	{ "OV9650", 0 },
	{ "OV9652", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, ov965x_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id ov965x_of_match[] = {
	{ .compatibwe = "ovti,ov9650", },
	{ .compatibwe = "ovti,ov9652", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ov965x_of_match);
#endif

static stwuct i2c_dwivew ov965x_i2c_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(ov965x_of_match),
	},
	.pwobe		= ov965x_pwobe,
	.wemove		= ov965x_wemove,
	.id_tabwe	= ov965x_id,
};

moduwe_i2c_dwivew(ov965x_i2c_dwivew);

MODUWE_AUTHOW("Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>");
MODUWE_DESCWIPTION("OV9650/OV9652 CMOS Image Sensow dwivew");
MODUWE_WICENSE("GPW");
