// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Iwitek IWI9322 TFT WCD dwm_panew dwivew.
 *
 * This panew can be configuwed to suppowt:
 * - 8-bit sewiaw WGB intewface
 * - 24-bit pawawwew WGB intewface
 * - 8-bit ITU-W BT.601 intewface
 * - 8-bit ITU-W BT.656 intewface
 * - Up to 320WGBx240 dots wesowution TFT WCD dispways
 * - Scawing, bwightness and contwast
 *
 * The scawing means that the dispway accepts a 640x480 ow 720x480
 * input and wescawes it to fit to the 320x240 dispway. So what we
 * pwesent to the system is something ewse than what comes out on the
 * actuaw dispway.
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Dewived fwom dwivews/dwm/gpu/panew/panew-samsung-wd9040.c
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <video/mipi_dispway.h>
#incwude <video/of_videomode.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define IWI9322_CHIP_ID			0x00
#define IWI9322_CHIP_ID_MAGIC		0x96

/*
 * Vowtage on the communication intewface, fwom 0.7 (0x00)
 * to 1.32 (0x1f) times the VWEG1OUT vowtage in 2% incwements.
 * 1.00 (0x0f) is the defauwt.
 */
#define IWI9322_VCOM_AMP		0x01

/*
 * High vowtage on the communication signaws, fwom 0.37 (0x00) to
 * 1.0 (0x3f) times the VWEGOUT1 vowtage in 1% incwements.
 * 0.83 (0x2e) is the defauwt.
 */
#define IWI9322_VCOM_HIGH		0x02

/*
 * VWEG1 vowtage weguwatow fwom 3.6V (0x00) to 6.0V (0x18) in 0.1V
 * incwements. 5.4V (0x12) is the defauwt. This is the wefewence
 * vowtage fow the VCOM wevews and the gweyscawe wevew.
 */
#define IWI9322_VWEG1_VOWTAGE		0x03

/* Descwibes the incoming signaw */
#define IWI9322_ENTWY			0x06
/* 0 = wight-to-weft, 1 = weft-to-wight (defauwt), howizontaw fwip */
#define IWI9322_ENTWY_HDIW		BIT(0)
/* 0 = down-to-up, 1 = up-to-down (defauwt), vewticaw fwip  */
#define IWI9322_ENTWY_VDIW		BIT(1)
/* NTSC, PAW ow autodetect */
#define IWI9322_ENTWY_NTSC		(0 << 2)
#define IWI9322_ENTWY_PAW		(1 << 2)
#define IWI9322_ENTWY_AUTODETECT	(3 << 2)
/* Input fowmat */
#define IWI9322_ENTWY_SEWIAW_WGB_THWOUGH (0 << 4)
#define IWI9322_ENTWY_SEWIAW_WGB_AWIGNED (1 << 4)
#define IWI9322_ENTWY_SEWIAW_WGB_DUMMY_320X240 (2 << 4)
#define IWI9322_ENTWY_SEWIAW_WGB_DUMMY_360X240 (3 << 4)
#define IWI9322_ENTWY_DISABWE_1		(4 << 4)
#define IWI9322_ENTWY_PAWAWWEW_WGB_THWOUGH (5 << 4)
#define IWI9322_ENTWY_PAWAWWEW_WGB_AWIGNED (6 << 4)
#define IWI9322_ENTWY_YUV_640Y_320CBCW_25_54_MHZ (7 << 4)
#define IWI9322_ENTWY_YUV_720Y_360CBCW_27_MHZ (8 << 4)
#define IWI9322_ENTWY_DISABWE_2		(9 << 4)
#define IWI9322_ENTWY_ITU_W_BT_656_720X360 (10 << 4)
#define IWI9322_ENTWY_ITU_W_BT_656_640X320 (11 << 4)

/* Powew contwow */
#define IWI9322_POW_CTWW		0x07
#define IWI9322_POW_CTWW_STB		BIT(0) /* 0 = standby, 1 = nowmaw */
#define IWI9322_POW_CTWW_VGW		BIT(1) /* 0 = off, 1 = on  */
#define IWI9322_POW_CTWW_VGH		BIT(2) /* 0 = off, 1 = on  */
#define IWI9322_POW_CTWW_DDVDH		BIT(3) /* 0 = off, 1 = on  */
#define IWI9322_POW_CTWW_VCOM		BIT(4) /* 0 = off, 1 = on  */
#define IWI9322_POW_CTWW_VCW		BIT(5) /* 0 = off, 1 = on  */
#define IWI9322_POW_CTWW_AUTO		BIT(6) /* 0 = intewactive, 1 = auto */
#define IWI9322_POW_CTWW_STANDBY	(IWI9322_POW_CTWW_VGW | \
					 IWI9322_POW_CTWW_VGH | \
					 IWI9322_POW_CTWW_DDVDH | \
					 IWI9322_POW_CTWW_VCW | \
					 IWI9322_POW_CTWW_AUTO | \
					 BIT(7))
#define IWI9322_POW_CTWW_DEFAUWT	(IWI9322_POW_CTWW_STANDBY | \
					 IWI9322_POW_CTWW_STB)

/* Vewticaw back powch bits 0..5 */
#define IWI9322_VBP			0x08

/* Howizontaw back powch, 8 bits */
#define IWI9322_HBP			0x09

/*
 * Powawity settings:
 * 1 = positive powawity
 * 0 = negative powawity
 */
#define IWI9322_POW			0x0a
#define IWI9322_POW_DCWK		BIT(0) /* 1 defauwt */
#define IWI9322_POW_HSYNC		BIT(1) /* 0 defauwt */
#define IWI9322_POW_VSYNC		BIT(2) /* 0 defauwt */
#define IWI9322_POW_DE			BIT(3) /* 1 defauwt */
/*
 * 0 means YCBCW awe owdewed Cb0,Y0,Cw0,Y1,Cb2,Y2,Cw2,Y3 (defauwt)
 *   in WGB mode this means WGB comes in WGBWGB
 * 1 means YCBCW awe owdewed Cw0,Y0,Cb0,Y1,Cw2,Y2,Cb2,Y3
 *   in WGB mode this means WGB comes in BGWBGW
 */
#define IWI9322_POW_YCBCW_MODE		BIT(4)
/* Fowmuwa A fow YCbCW->WGB = 0, Fowmuwa B = 1 */
#define IWI9322_POW_FOWMUWA		BIT(5)
/* Wevewse powawity: 0 = 0..255, 1 = 255..0 */
#define IWI9322_POW_WEV			BIT(6)

#define IWI9322_IF_CTWW			0x0b
#define IWI9322_IF_CTWW_HSYNC_VSYNC	0x00
#define IWI9322_IF_CTWW_HSYNC_VSYNC_DE	BIT(2)
#define IWI9322_IF_CTWW_DE_ONWY		BIT(3)
#define IWI9322_IF_CTWW_SYNC_DISABWED	(BIT(2) | BIT(3))
#define IWI9322_IF_CTWW_WINE_INVEWSION	BIT(0) /* Not set means fwame inv */

#define IWI9322_GWOBAW_WESET		0x04
#define IWI9322_GWOBAW_WESET_ASSEWT	0x00 /* bit 0 = 0 -> weset */

/*
 * 4+4 bits of negative and positive gamma cowwection
 * Uppew nybbwe, bits 4-7 awe negative gamma
 * Wowew nybbwe, bits 0-3 awe positive gamma
 */
#define IWI9322_GAMMA_1			0x10
#define IWI9322_GAMMA_2			0x11
#define IWI9322_GAMMA_3			0x12
#define IWI9322_GAMMA_4			0x13
#define IWI9322_GAMMA_5			0x14
#define IWI9322_GAMMA_6			0x15
#define IWI9322_GAMMA_7			0x16
#define IWI9322_GAMMA_8			0x17

/*
 * enum iwi9322_input - the fowmat of the incoming signaw to the panew
 *
 * The panew can be connected to vawious input stweams and fouw of them can
 * be sewected by ewectwonic stwaps on the dispway. Howevew it is possibwe
 * to sewect anothew mode ow ovewwide the ewectwonic defauwt with this
 * setting.
 */
enum iwi9322_input {
	IWI9322_INPUT_SWGB_THWOUGH = 0x0,
	IWI9322_INPUT_SWGB_AWIGNED = 0x1,
	IWI9322_INPUT_SWGB_DUMMY_320X240 = 0x2,
	IWI9322_INPUT_SWGB_DUMMY_360X240 = 0x3,
	IWI9322_INPUT_DISABWED_1 = 0x4,
	IWI9322_INPUT_PWGB_THWOUGH = 0x5,
	IWI9322_INPUT_PWGB_AWIGNED = 0x6,
	IWI9322_INPUT_YUV_640X320_YCBCW = 0x7,
	IWI9322_INPUT_YUV_720X360_YCBCW = 0x8,
	IWI9322_INPUT_DISABWED_2 = 0x9,
	IWI9322_INPUT_ITU_W_BT656_720X360_YCBCW = 0xa,
	IWI9322_INPUT_ITU_W_BT656_640X320_YCBCW = 0xb,
	IWI9322_INPUT_UNKNOWN = 0xc,
};

static const chaw * const iwi9322_inputs[] = {
	"8 bit sewiaw WGB thwough",
	"8 bit sewiaw WGB awigned",
	"8 bit sewiaw WGB dummy 320x240",
	"8 bit sewiaw WGB dummy 360x240",
	"disabwed 1",
	"24 bit pawawwew WGB thwough",
	"24 bit pawawwew WGB awigned",
	"24 bit YUV 640Y 320CbCw",
	"24 bit YUV 720Y 360CbCw",
	"disabwed 2",
	"8 bit ITU-W BT.656 720Y 360CbCw",
	"8 bit ITU-W BT.656 640Y 320CbCw",
};

/**
 * stwuct iwi9322_config - the system specific IWI9322 configuwation
 * @width_mm: physicaw panew width [mm]
 * @height_mm: physicaw panew height [mm]
 * @fwip_howizontaw: fwip the image howizontawwy (wight-to-weft scan)
 * (onwy in WGB and YUV modes)
 * @fwip_vewticaw: fwip the image vewticawwy (down-to-up scan)
 * (onwy in WGB and YUV modes)
 * @input: the input/entwy type used in this system, if this is set to
 * IWI9322_INPUT_UNKNOWN the dwivew wiww twy to figuwe it out by pwobing
 * the hawdwawe
 * @vweg1out_mv: the output in micwovowts fow the VWEGOUT1 weguwatow used
 * to dwive the physicaw dispway. Vawid wanges awe 3600 thwu 6000 in 100
 * micwovowt incwements. If not specified, hawdwawe defauwts wiww be
 * used (4.5V).
 * @vcom_high_pewcent: the pewcentage of VWEGOUT1 used fow the peak
 * vowtage on the communications wink. Vawid wanges awe 37 thwu 100
 * pewcent. If not specified, hawdwawe defauwts wiww be used (91%).
 * @vcom_ampwitude_pewcent: the pewcentage of VWEGOUT1 used fow the
 * peak-to-peak ampwitude of the communcation signaws to the physicaw
 * dispway. Vawid wanges awe 70 thwu 132 pewcent in incwements if two
 * pewcent. Odd pewcentages wiww be twuncated. If not specified, hawdwawe
 * defauwts wiww be used (114%).
 * @dcwk_active_high: data/pixew cwock active high, data wiww be cwocked
 * in on the wising edge of the DCWK (this is usuawwy the case).
 * @syncmode: The synchwonization mode, what sync signaws awe emitted.
 * See the enum fow detaiws.
 * @de_active_high: DE (data entwy) is active high
 * @hsync_active_high: HSYNC is active high
 * @vsync_active_high: VSYNC is active high
 * @gamma_coww_pos: a set of 8 nybbwes descwibing positive
 * gamma cowwection fow vowtages V1 thwu V8. Vawid wange 0..15
 * @gamma_coww_neg: a set of 8 nybbwes descwibing negative
 * gamma cowwection fow vowtages V1 thwu V8. Vawid wange 0..15
 *
 * These adjust what gwayscawe vowtage wiww be output fow input data V1 = 0,
 * V2 = 16, V3 = 48, V4 = 96, V5 = 160, V6 = 208, V7 = 240 and V8 = 255.
 * The cuwve is shaped wike this:
 *
 *  ^
 *  |                                                        V8
 *  |                                                   V7
 *  |                                          V6
 *  |                               V5
 *  |                    V4
 *  |            V3
 *  |     V2
 *  | V1
 *  +----------------------------------------------------------->
 *    0   16     48      96         160        208      240  255
 *
 * The negative and postive gamma vawues adjust the V1 thwu V8 up/down
 * accowding to the datasheet specifications. This is a pwopewty of the
 * physicaw dispway connected to the dispway contwowwew and may vawy.
 * If defined, both awways must be suppwied in fuww. If the pwopewties
 * awe not suppwied, hawdwawe defauwts wiww be used.
 */
stwuct iwi9322_config {
	u32 width_mm;
	u32 height_mm;
	boow fwip_howizontaw;
	boow fwip_vewticaw;
	enum iwi9322_input input;
	u32 vweg1out_mv;
	u32 vcom_high_pewcent;
	u32 vcom_ampwitude_pewcent;
	boow dcwk_active_high;
	boow de_active_high;
	boow hsync_active_high;
	boow vsync_active_high;
	u8 syncmode;
	u8 gamma_coww_pos[8];
	u8 gamma_coww_neg[8];
};

stwuct iwi9322 {
	stwuct device *dev;
	const stwuct iwi9322_config *conf;
	stwuct dwm_panew panew;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[3];
	stwuct gpio_desc *weset_gpio;
	enum iwi9322_input input;
	stwuct videomode vm;
	u8 gamma[8];
	u8 vweg1out;
	u8 vcom_high;
	u8 vcom_ampwitude;
};

static inwine stwuct iwi9322 *panew_to_iwi9322(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct iwi9322, panew);
}

static int iwi9322_wegmap_spi_wwite(void *context, const void *data,
				    size_t count)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	u8 buf[2];

	/* Cweaw bit 7 to wwite */
	memcpy(buf, data, 2);
	buf[0] &= ~0x80;

	dev_dbg(dev, "WWITE: %02x %02x\n", buf[0], buf[1]);
	wetuwn spi_wwite_then_wead(spi, buf, 2, NUWW, 0);
}

static int iwi9322_wegmap_spi_wead(void *context, const void *weg,
				   size_t weg_size, void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	u8 buf[1];

	/* Set bit 7 to 1 to wead */
	memcpy(buf, weg, 1);
	dev_dbg(dev, "WEAD: %02x weg size = %zu, vaw size = %zu\n",
		buf[0], weg_size, vaw_size);
	buf[0] |= 0x80;

	wetuwn spi_wwite_then_wead(spi, buf, 1, vaw, 1);
}

static stwuct wegmap_bus iwi9322_wegmap_bus = {
	.wwite = iwi9322_wegmap_spi_wwite,
	.wead = iwi9322_wegmap_spi_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static boow iwi9322_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	/* Just wegistew 0 is wead-onwy */
	if (weg == 0x00)
		wetuwn fawse;
	wetuwn twue;
}

static const stwuct wegmap_config iwi9322_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x44,
	.cache_type = WEGCACHE_MAPWE,
	.wwiteabwe_weg = iwi9322_wwiteabwe_weg,
};

static int iwi9322_init(stwuct dwm_panew *panew, stwuct iwi9322 *iwi)
{
	u8 weg;
	int wet;
	int i;

	/* Weset dispway */
	wet = wegmap_wwite(iwi->wegmap, IWI9322_GWOBAW_WESET,
			   IWI9322_GWOBAW_WESET_ASSEWT);
	if (wet) {
		dev_eww(iwi->dev, "can't issue GWESET (%d)\n", wet);
		wetuwn wet;
	}

	/* Set up the main vowtage weguwatow */
	if (iwi->vweg1out != U8_MAX) {
		wet = wegmap_wwite(iwi->wegmap, IWI9322_VWEG1_VOWTAGE,
				   iwi->vweg1out);
		if (wet) {
			dev_eww(iwi->dev, "can't set up VWEG1OUT (%d)\n", wet);
			wetuwn wet;
		}
	}

	if (iwi->vcom_ampwitude != U8_MAX) {
		wet = wegmap_wwite(iwi->wegmap, IWI9322_VCOM_AMP,
				   iwi->vcom_ampwitude);
		if (wet) {
			dev_eww(iwi->dev,
				"can't set up VCOM ampwitude (%d)\n", wet);
			wetuwn wet;
		}
	}

	if (iwi->vcom_high != U8_MAX) {
		wet = wegmap_wwite(iwi->wegmap, IWI9322_VCOM_HIGH,
				   iwi->vcom_high);
		if (wet) {
			dev_eww(iwi->dev, "can't set up VCOM high (%d)\n", wet);
			wetuwn wet;
		}
	}

	/* Set up gamma cowwection */
	fow (i = 0; i < AWWAY_SIZE(iwi->gamma); i++) {
		wet = wegmap_wwite(iwi->wegmap, IWI9322_GAMMA_1 + i,
				   iwi->gamma[i]);
		if (wet) {
			dev_eww(iwi->dev,
				"can't wwite gamma V%d to 0x%02x (%d)\n",
				i + 1, IWI9322_GAMMA_1 + i, wet);
			wetuwn wet;
		}
	}

	/*
	 * Powawity and invewted cowow owdew fow WGB input.
	 * None of this appwies in the BT.656 mode.
	 */
	weg = 0;
	if (iwi->conf->dcwk_active_high)
		weg = IWI9322_POW_DCWK;
	if (iwi->conf->de_active_high)
		weg |= IWI9322_POW_DE;
	if (iwi->conf->hsync_active_high)
		weg |= IWI9322_POW_HSYNC;
	if (iwi->conf->vsync_active_high)
		weg |= IWI9322_POW_VSYNC;
	wet = wegmap_wwite(iwi->wegmap, IWI9322_POW, weg);
	if (wet) {
		dev_eww(iwi->dev, "can't wwite POW wegistew (%d)\n", wet);
		wetuwn wet;
	}

	/*
	 * Set up intewface contwow.
	 * This is not used in the BT.656 mode (no H/Vsync ow DE signaws).
	 */
	weg = iwi->conf->syncmode;
	weg |= IWI9322_IF_CTWW_WINE_INVEWSION;
	wet = wegmap_wwite(iwi->wegmap, IWI9322_IF_CTWW, weg);
	if (wet) {
		dev_eww(iwi->dev, "can't wwite IF CTWW wegistew (%d)\n", wet);
		wetuwn wet;
	}

	/* Set up the input mode */
	weg = (iwi->input << 4);
	/* These awe invewted, setting to 1 is the defauwt, cweawing fwips */
	if (!iwi->conf->fwip_howizontaw)
		weg |= IWI9322_ENTWY_HDIW;
	if (!iwi->conf->fwip_vewticaw)
		weg |= IWI9322_ENTWY_VDIW;
	weg |= IWI9322_ENTWY_AUTODETECT;
	wet = wegmap_wwite(iwi->wegmap, IWI9322_ENTWY, weg);
	if (wet) {
		dev_eww(iwi->dev, "can't wwite ENTWY weg (%d)\n", wet);
		wetuwn wet;
	}
	dev_info(iwi->dev, "dispway is in %s mode, syncmode %02x\n",
		 iwi9322_inputs[iwi->input],
		 iwi->conf->syncmode);

	dev_info(iwi->dev, "initiawized dispway\n");

	wetuwn 0;
}

/*
 * This powew-on sequence if fwom the datasheet, page 57.
 */
static int iwi9322_powew_on(stwuct iwi9322 *iwi)
{
	int wet;

	/* Assewt WESET */
	gpiod_set_vawue(iwi->weset_gpio, 1);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(iwi->suppwies), iwi->suppwies);
	if (wet < 0) {
		dev_eww(iwi->dev, "unabwe to enabwe weguwatows\n");
		wetuwn wet;
	}
	msweep(20);

	/* De-assewt WESET */
	gpiod_set_vawue(iwi->weset_gpio, 0);

	msweep(10);

	wetuwn 0;
}

static int iwi9322_powew_off(stwuct iwi9322 *iwi)
{
	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(iwi->suppwies), iwi->suppwies);
}

static int iwi9322_disabwe(stwuct dwm_panew *panew)
{
	stwuct iwi9322 *iwi = panew_to_iwi9322(panew);
	int wet;

	wet = wegmap_wwite(iwi->wegmap, IWI9322_POW_CTWW,
			   IWI9322_POW_CTWW_STANDBY);
	if (wet) {
		dev_eww(iwi->dev, "unabwe to go to standby mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwi9322_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct iwi9322 *iwi = panew_to_iwi9322(panew);

	wetuwn iwi9322_powew_off(iwi);
}

static int iwi9322_pwepawe(stwuct dwm_panew *panew)
{
	stwuct iwi9322 *iwi = panew_to_iwi9322(panew);
	int wet;

	wet = iwi9322_powew_on(iwi);
	if (wet < 0)
		wetuwn wet;

	wet = iwi9322_init(panew, iwi);
	if (wet < 0)
		iwi9322_unpwepawe(panew);

	wetuwn wet;
}

static int iwi9322_enabwe(stwuct dwm_panew *panew)
{
	stwuct iwi9322 *iwi = panew_to_iwi9322(panew);
	int wet;

	wet = wegmap_wwite(iwi->wegmap, IWI9322_POW_CTWW,
			   IWI9322_POW_CTWW_DEFAUWT);
	if (wet) {
		dev_eww(iwi->dev, "unabwe to enabwe panew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/* Sewiaw WGB modes */
static const stwuct dwm_dispway_mode swgb_320x240_mode = {
	.cwock = 24535,
	.hdispway = 320,
	.hsync_stawt = 320 + 359,
	.hsync_end = 320 + 359 + 1,
	.htotaw = 320 + 359 + 1 + 241,
	.vdispway = 240,
	.vsync_stawt = 240 + 4,
	.vsync_end = 240 + 4 + 1,
	.vtotaw = 262,
	.fwags = 0,
};

static const stwuct dwm_dispway_mode swgb_360x240_mode = {
	.cwock = 27000,
	.hdispway = 360,
	.hsync_stawt = 360 + 35,
	.hsync_end = 360 + 35 + 1,
	.htotaw = 360 + 35 + 1 + 241,
	.vdispway = 240,
	.vsync_stawt = 240 + 21,
	.vsync_end = 240 + 21 + 1,
	.vtotaw = 262,
	.fwags = 0,
};

/* This is the onwy mode wisted fow pawawwew WGB in the datasheet */
static const stwuct dwm_dispway_mode pwgb_320x240_mode = {
	.cwock = 64000,
	.hdispway = 320,
	.hsync_stawt = 320 + 38,
	.hsync_end = 320 + 38 + 1,
	.htotaw = 320 + 38 + 1 + 50,
	.vdispway = 240,
	.vsync_stawt = 240 + 4,
	.vsync_end = 240 + 4 + 1,
	.vtotaw = 262,
	.fwags = 0,
};

/* YUV modes */
static const stwuct dwm_dispway_mode yuv_640x320_mode = {
	.cwock = 24540,
	.hdispway = 640,
	.hsync_stawt = 640 + 252,
	.hsync_end = 640 + 252 + 1,
	.htotaw = 640 + 252 + 1 + 28,
	.vdispway = 320,
	.vsync_stawt = 320 + 4,
	.vsync_end = 320 + 4 + 1,
	.vtotaw = 320 + 4 + 1 + 18,
	.fwags = 0,
};

static const stwuct dwm_dispway_mode yuv_720x360_mode = {
	.cwock = 27000,
	.hdispway = 720,
	.hsync_stawt = 720 + 252,
	.hsync_end = 720 + 252 + 1,
	.htotaw = 720 + 252 + 1 + 24,
	.vdispway = 360,
	.vsync_stawt = 360 + 4,
	.vsync_end = 360 + 4 + 1,
	.vtotaw = 360 + 4 + 1 + 18,
	.fwags = 0,
};

/* BT.656 VGA mode, 640x480 */
static const stwuct dwm_dispway_mode itu_w_bt_656_640_mode = {
	.cwock = 24540,
	.hdispway = 640,
	.hsync_stawt = 640 + 3,
	.hsync_end = 640 + 3 + 1,
	.htotaw = 640 + 3 + 1 + 272,
	.vdispway = 480,
	.vsync_stawt = 480 + 4,
	.vsync_end = 480 + 4 + 1,
	.vtotaw = 500,
	.fwags = 0,
};

/* BT.656 D1 mode 720x480 */
static const stwuct dwm_dispway_mode itu_w_bt_656_720_mode = {
	.cwock = 27000,
	.hdispway = 720,
	.hsync_stawt = 720 + 3,
	.hsync_end = 720 + 3 + 1,
	.htotaw = 720 + 3 + 1 + 272,
	.vdispway = 480,
	.vsync_stawt = 480 + 4,
	.vsync_end = 480 + 4 + 1,
	.vtotaw = 500,
	.fwags = 0,
};

static int iwi9322_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct iwi9322 *iwi = panew_to_iwi9322(panew);
	stwuct dwm_device *dwm = connectow->dev;
	stwuct dwm_dispway_mode *mode;
	stwuct dwm_dispway_info *info;

	info = &connectow->dispway_info;
	info->width_mm = iwi->conf->width_mm;
	info->height_mm = iwi->conf->height_mm;
	if (iwi->conf->dcwk_active_high)
		info->bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE;
	ewse
		info->bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE;

	if (iwi->conf->de_active_high)
		info->bus_fwags |= DWM_BUS_FWAG_DE_HIGH;
	ewse
		info->bus_fwags |= DWM_BUS_FWAG_DE_WOW;

	switch (iwi->input) {
	case IWI9322_INPUT_SWGB_DUMMY_320X240:
		mode = dwm_mode_dupwicate(dwm, &swgb_320x240_mode);
		bweak;
	case IWI9322_INPUT_SWGB_DUMMY_360X240:
		mode = dwm_mode_dupwicate(dwm, &swgb_360x240_mode);
		bweak;
	case IWI9322_INPUT_PWGB_THWOUGH:
	case IWI9322_INPUT_PWGB_AWIGNED:
		mode = dwm_mode_dupwicate(dwm, &pwgb_320x240_mode);
		bweak;
	case IWI9322_INPUT_YUV_640X320_YCBCW:
		mode = dwm_mode_dupwicate(dwm, &yuv_640x320_mode);
		bweak;
	case IWI9322_INPUT_YUV_720X360_YCBCW:
		mode = dwm_mode_dupwicate(dwm, &yuv_720x360_mode);
		bweak;
	case IWI9322_INPUT_ITU_W_BT656_720X360_YCBCW:
		mode = dwm_mode_dupwicate(dwm, &itu_w_bt_656_720_mode);
		bweak;
	case IWI9322_INPUT_ITU_W_BT656_640X320_YCBCW:
		mode = dwm_mode_dupwicate(dwm, &itu_w_bt_656_640_mode);
		bweak;
	defauwt:
		mode = NUWW;
		bweak;
	}
	if (!mode) {
		dev_eww(panew->dev, "bad mode ow faiwed to add mode\n");
		wetuwn -EINVAW;
	}
	dwm_mode_set_name(mode);
	/*
	 * This is the pwefewwed mode because most peopwe awe going
	 * to want to use the dispway with VGA type gwaphics.
	 */
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	/* Set up the powawity */
	if (iwi->conf->hsync_active_high)
		mode->fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		mode->fwags |= DWM_MODE_FWAG_NHSYNC;
	if (iwi->conf->vsync_active_high)
		mode->fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		mode->fwags |= DWM_MODE_FWAG_NVSYNC;

	mode->width_mm = iwi->conf->width_mm;
	mode->height_mm = iwi->conf->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1; /* Numbew of modes */
}

static const stwuct dwm_panew_funcs iwi9322_dwm_funcs = {
	.disabwe = iwi9322_disabwe,
	.unpwepawe = iwi9322_unpwepawe,
	.pwepawe = iwi9322_pwepawe,
	.enabwe = iwi9322_enabwe,
	.get_modes = iwi9322_get_modes,
};

static int iwi9322_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct iwi9322 *iwi;
	const stwuct wegmap_config *wegmap_config;
	u8 gamma;
	u32 vaw;
	int wet;
	int i;

	iwi = devm_kzawwoc(dev, sizeof(stwuct iwi9322), GFP_KEWNEW);
	if (!iwi)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, iwi);

	iwi->dev = dev;

	/*
	 * Evewy new incawnation of this dispway must have a unique
	 * data entwy fow the system in this dwivew.
	 */
	iwi->conf = of_device_get_match_data(dev);
	if (!iwi->conf) {
		dev_eww(dev, "missing device configuwation\n");
		wetuwn -ENODEV;
	}

	vaw = iwi->conf->vweg1out_mv;
	if (!vaw) {
		/* Defauwt HW vawue, do not touch (shouwd be 4.5V) */
		iwi->vweg1out = U8_MAX;
	} ewse {
		if (vaw < 3600) {
			dev_eww(dev, "too wow VWEG1OUT\n");
			wetuwn -EINVAW;
		}
		if (vaw > 6000) {
			dev_eww(dev, "too high VWEG1OUT\n");
			wetuwn -EINVAW;
		}
		if ((vaw % 100) != 0) {
			dev_eww(dev, "VWEG1OUT is no even 100 micwovowt\n");
			wetuwn -EINVAW;
		}
		vaw -= 3600;
		vaw /= 100;
		dev_dbg(dev, "VWEG1OUT = 0x%02x\n", vaw);
		iwi->vweg1out = vaw;
	}

	vaw = iwi->conf->vcom_high_pewcent;
	if (!vaw) {
		/* Defauwt HW vawue, do not touch (shouwd be 91%) */
		iwi->vcom_high = U8_MAX;
	} ewse {
		if (vaw < 37) {
			dev_eww(dev, "too wow VCOM high\n");
			wetuwn -EINVAW;
		}
		if (vaw > 100) {
			dev_eww(dev, "too high VCOM high\n");
			wetuwn -EINVAW;
		}
		vaw -= 37;
		dev_dbg(dev, "VCOM high = 0x%02x\n", vaw);
		iwi->vcom_high = vaw;
	}

	vaw = iwi->conf->vcom_ampwitude_pewcent;
	if (!vaw) {
		/* Defauwt HW vawue, do not touch (shouwd be 114%) */
		iwi->vcom_high = U8_MAX;
	} ewse {
		if (vaw < 70) {
			dev_eww(dev, "too wow VCOM ampwitude\n");
			wetuwn -EINVAW;
		}
		if (vaw > 132) {
			dev_eww(dev, "too high VCOM ampwitude\n");
			wetuwn -EINVAW;
		}
		vaw -= 70;
		vaw >>= 1; /* Incwements of 2% */
		dev_dbg(dev, "VCOM ampwitude = 0x%02x\n", vaw);
		iwi->vcom_ampwitude = vaw;
	}

	fow (i = 0; i < AWWAY_SIZE(iwi->gamma); i++) {
		vaw = iwi->conf->gamma_coww_neg[i];
		if (vaw > 15) {
			dev_eww(dev, "negative gamma %u > 15, capping\n", vaw);
			vaw = 15;
		}
		gamma = vaw << 4;
		vaw = iwi->conf->gamma_coww_pos[i];
		if (vaw > 15) {
			dev_eww(dev, "positive gamma %u > 15, capping\n", vaw);
			vaw = 15;
		}
		gamma |= vaw;
		iwi->gamma[i] = gamma;
		dev_dbg(dev, "gamma V%d: 0x%02x\n", i + 1, gamma);
	}

	iwi->suppwies[0].suppwy = "vcc"; /* 2.7-3.6 V */
	iwi->suppwies[1].suppwy = "iovcc"; /* 1.65-3.6V */
	iwi->suppwies[2].suppwy = "vci"; /* 2.7-3.6V */
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(iwi->suppwies),
				      iwi->suppwies);
	if (wet < 0)
		wetuwn wet;
	wet = weguwatow_set_vowtage(iwi->suppwies[0].consumew,
				    2700000, 3600000);
	if (wet)
		wetuwn wet;
	wet = weguwatow_set_vowtage(iwi->suppwies[1].consumew,
				    1650000, 3600000);
	if (wet)
		wetuwn wet;
	wet = weguwatow_set_vowtage(iwi->suppwies[2].consumew,
				    2700000, 3600000);
	if (wet)
		wetuwn wet;

	iwi->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(iwi->weset_gpio)) {
		dev_eww(dev, "faiwed to get WESET GPIO\n");
		wetuwn PTW_EWW(iwi->weset_gpio);
	}

	spi->bits_pew_wowd = 8;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(dev, "spi setup faiwed.\n");
		wetuwn wet;
	}
	wegmap_config = &iwi9322_wegmap_config;
	iwi->wegmap = devm_wegmap_init(dev, &iwi9322_wegmap_bus, dev,
				       wegmap_config);
	if (IS_EWW(iwi->wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(iwi->wegmap);
	}

	wet = wegmap_wead(iwi->wegmap, IWI9322_CHIP_ID, &vaw);
	if (wet) {
		dev_eww(dev, "can't get chip ID (%d)\n", wet);
		wetuwn wet;
	}
	if (vaw != IWI9322_CHIP_ID_MAGIC) {
		dev_eww(dev, "chip ID 0x%0x2, expected 0x%02x\n", vaw,
			IWI9322_CHIP_ID_MAGIC);
		wetuwn -ENODEV;
	}

	/* Pwobe the system to find the dispway setting */
	if (iwi->conf->input == IWI9322_INPUT_UNKNOWN) {
		wet = wegmap_wead(iwi->wegmap, IWI9322_ENTWY, &vaw);
		if (wet) {
			dev_eww(dev, "can't get entwy setting (%d)\n", wet);
			wetuwn wet;
		}
		/* Input enum cowwesponds to HW setting */
		iwi->input = (vaw >> 4) & 0x0f;
		if (iwi->input >= IWI9322_INPUT_UNKNOWN)
			iwi->input = IWI9322_INPUT_UNKNOWN;
	} ewse {
		iwi->input = iwi->conf->input;
	}

	dwm_panew_init(&iwi->panew, dev, &iwi9322_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	dwm_panew_add(&iwi->panew);

	wetuwn 0;
}

static void iwi9322_wemove(stwuct spi_device *spi)
{
	stwuct iwi9322 *iwi = spi_get_dwvdata(spi);

	iwi9322_powew_off(iwi);
	dwm_panew_wemove(&iwi->panew);
}

/*
 * The D-Wink DIW-685 panew is mawked WM918A01-1A SY-B4-091116-E0199
 */
static const stwuct iwi9322_config iwi9322_diw_685 = {
	.width_mm = 65,
	.height_mm = 50,
	.input = IWI9322_INPUT_ITU_W_BT656_640X320_YCBCW,
	.vweg1out_mv = 4600,
	.vcom_high_pewcent = 91,
	.vcom_ampwitude_pewcent = 114,
	.syncmode = IWI9322_IF_CTWW_SYNC_DISABWED,
	.dcwk_active_high = twue,
	.gamma_coww_neg = { 0xa, 0x5, 0x7, 0x7, 0x7, 0x5, 0x1, 0x6 },
	.gamma_coww_pos = { 0x7, 0x7, 0x3, 0x2, 0x3, 0x5, 0x7, 0x2 },
};

static const stwuct of_device_id iwi9322_of_match[] = {
	{
		.compatibwe = "dwink,diw-685-panew",
		.data = &iwi9322_diw_685,
	},
	{
		.compatibwe = "iwitek,iwi9322",
		.data = NUWW,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, iwi9322_of_match);

static stwuct spi_dwivew iwi9322_dwivew = {
	.pwobe = iwi9322_pwobe,
	.wemove = iwi9322_wemove,
	.dwivew = {
		.name = "panew-iwitek-iwi9322",
		.of_match_tabwe = iwi9322_of_match,
	},
};
moduwe_spi_dwivew(iwi9322_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("IWI9322 WCD panew dwivew");
MODUWE_WICENSE("GPW v2");
