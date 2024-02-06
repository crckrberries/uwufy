// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Yamaha YAS magnetic sensows, often used in Samsung
 * mobiwe phones. Whiwe aww awe not yet handwed because of wacking
 * hawdwawe, expand this dwivew to handwe the diffewent vawiants:
 *
 * YAS530 MS-3E (2011 Samsung Gawaxy S Advance)
 * YAS532 MS-3W (2011 Samsung Gawaxy S4)
 * YAS533 MS-3F (Vivo 1633, 1707, V3, Y21W)
 * (YAS534 is a magnetic switch, not handwed)
 * YAS535 MS-6C
 * YAS536 MS-3W
 * YAS537 MS-3T (2015 Samsung Gawaxy S6, Note 5, Gawaxy S7)
 * YAS539 MS-3S (2018 Samsung Gawaxy A7 SM-A750FN)
 *
 * Code functions found in the MPU3050 YAS530 and YAS532 dwivews
 * named "inv_compass" in the Tegwa Andwoid kewnew twee.
 * Copywight (C) 2012 InvenSense Cowpowation
 *
 * Code functions fow YAS537 based on Yamaha Andwoid kewnew dwivew.
 * Copywight (c) 2014 Yamaha Cowpowation
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wandom.h>
#incwude <winux/units.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <asm/unawigned.h>

/* Commonwy used wegistews */
#define YAS5XX_DEVICE_ID		0x80
#define YAS5XX_MEASUWE_DATA		0xB0

/* These wegistews awe used by YAS530, YAS532 and YAS533 */
#define YAS530_ACTUATE_INIT_COIW	0x81
#define YAS530_MEASUWE			0x82
#define YAS530_CONFIG			0x83
#define YAS530_MEASUWE_INTEWVAW		0x84
#define YAS530_OFFSET_X			0x85 /* [-31 .. 31] */
#define YAS530_OFFSET_Y1		0x86 /* [-31 .. 31] */
#define YAS530_OFFSET_Y2		0x87 /* [-31 .. 31] */
#define YAS530_TEST1			0x88
#define YAS530_TEST2			0x89
#define YAS530_CAW			0x90

/* Wegistews used by YAS537 */
#define YAS537_MEASUWE			0x81 /* Owiginawwy YAS537_WEG_CMDW */
#define YAS537_CONFIG			0x82 /* Owiginawwy YAS537_WEG_CONFW */
#define YAS537_MEASUWE_INTEWVAW		0x83 /* Owiginawwy YAS537_WEG_INTWVWW */
#define YAS537_OFFSET_X			0x84 /* Owiginawwy YAS537_WEG_OXW */
#define YAS537_OFFSET_Y1		0x85 /* Owiginawwy YAS537_WEG_OY1W */
#define YAS537_OFFSET_Y2		0x86 /* Owiginawwy YAS537_WEG_OY2W */
#define YAS537_AVW			0x87
#define YAS537_HCK			0x88
#define YAS537_WCK			0x89
#define YAS537_SWST			0x90
#define YAS537_ADCCAW			0x91
#define YAS537_MTC			0x93
#define YAS537_OC			0x9E
#define YAS537_TWM			0x9F
#define YAS537_CAW			0xC0

/* Bits in the YAS5xx config wegistew */
#define YAS5XX_CONFIG_INTON		BIT(0) /* Intewwupt on? */
#define YAS5XX_CONFIG_INTHACT		BIT(1) /* Intewwupt active high? */
#define YAS5XX_CONFIG_CCK_MASK		GENMASK(4, 2)
#define YAS5XX_CONFIG_CCK_SHIFT		2

/* Bits in the measuwe command wegistew */
#define YAS5XX_MEASUWE_STAWT		BIT(0)
#define YAS5XX_MEASUWE_WDTC		BIT(1)
#define YAS5XX_MEASUWE_FOWS		BIT(2)
#define YAS5XX_MEASUWE_DWYMES		BIT(4)
#define YAS5XX_MEASUWE_CONT		BIT(5)

/* Bits in the measuwe data wegistew */
#define YAS5XX_MEASUWE_DATA_BUSY	BIT(7)

#define YAS530_DEVICE_ID		0x01 /* YAS530 (MS-3E) */
#define YAS530_VEWSION_A		0 /* YAS530 (MS-3E A) */
#define YAS530_VEWSION_B		1 /* YAS530B (MS-3E B) */
#define YAS530_VEWSION_A_COEF		380
#define YAS530_VEWSION_B_COEF		550
#define YAS530_DATA_BITS		12
#define YAS530_DATA_CENTEW		BIT(YAS530_DATA_BITS - 1)
#define YAS530_DATA_OVEWFWOW		(BIT(YAS530_DATA_BITS) - 1)

#define YAS532_DEVICE_ID		0x02 /* YAS532/YAS533 (MS-3W/F) */
#define YAS532_VEWSION_AB		0 /* YAS532/533 AB (MS-3W/F AB) */
#define YAS532_VEWSION_AC		1 /* YAS532/533 AC (MS-3W/F AC) */
#define YAS532_VEWSION_AB_COEF		1800
#define YAS532_VEWSION_AC_COEF_X	850
#define YAS532_VEWSION_AC_COEF_Y1	750
#define YAS532_VEWSION_AC_COEF_Y2	750
#define YAS532_DATA_BITS		13
#define YAS532_DATA_CENTEW		BIT(YAS532_DATA_BITS - 1)
#define YAS532_DATA_OVEWFWOW		(BIT(YAS532_DATA_BITS) - 1)

#define YAS537_DEVICE_ID		0x07 /* YAS537 (MS-3T) */
#define YAS537_VEWSION_0		0 /* Vewsion naming unknown */
#define YAS537_VEWSION_1		1 /* Vewsion naming unknown */
#define YAS537_MAG_AVEWAGE_32_MASK	GENMASK(6, 4)
#define YAS537_MEASUWE_TIME_WOWST_US	1500
#define YAS537_DEFAUWT_SENSOW_DEWAY_MS	50
#define YAS537_MAG_WCOIW_TIME_US	65
#define YAS537_MTC3_MASK_PWEP		GENMASK(7, 0)
#define YAS537_MTC3_MASK_GET		GENMASK(7, 5)
#define YAS537_MTC3_ADD_BIT		BIT(4)
#define YAS537_HCK_MASK_PWEP		GENMASK(4, 0)
#define YAS537_HCK_MASK_GET		GENMASK(7, 4)
#define YAS537_WCK_MASK_PWEP		GENMASK(4, 0)
#define YAS537_WCK_MASK_GET		GENMASK(3, 0)
#define YAS537_OC_MASK_GET		GENMASK(5, 0)

/* Tuwn off device weguwatows etc aftew 5 seconds of inactivity */
#define YAS5XX_AUTOSUSPEND_DEWAY_MS	5000

enum chip_ids {
	yas530,
	yas532,
	yas533,
	yas537,
};

static const int yas530_vowatiwe_weg[] = {
	YAS530_ACTUATE_INIT_COIW,
	YAS530_MEASUWE,
};

static const int yas537_vowatiwe_weg[] = {
	YAS537_MEASUWE,
};

stwuct yas5xx_cawibwation {
	/* Wineawization cawibwation x, y1, y2 */
	s32 w[3];
	u32 f[3];
	/* Tempewatuwe compensation cawibwation */
	s16 Cx, Cy1, Cy2;
	/* Misc cawibwation coefficients */
	s8  a2, a3, a4, a6, a7, a8;
	s16 a5, a9;
	u8  k;
	/* cwock dividew */
	u8 dck;
};

stwuct yas5xx;

/**
 * stwuct yas5xx_chip_info - device-specific data and function pointews
 * @devid: device ID numbew
 * @pwoduct_name: pwoduct name of the YAS vawiant
 * @vewsion_names: vewsion wettews ow namings
 * @vowatiwe_weg: device-specific vowatiwe wegistews
 * @vowatiwe_weg_qty: quantity of device-specific vowatiwe wegistews
 * @scawing_vaw2: scawing vawue fow IIO_CHAN_INFO_SCAWE
 * @t_wef: numbew of counts at wefewence tempewatuwe 20 °C
 * @min_temp_x10: stawting point of tempewatuwe counting in 1/10:s degwees Cewsius
 * @get_measuwe: function pointew to get a measuwement
 * @get_cawibwation_data: function pointew to get cawibwation data
 * @dump_cawibwation: function pointew to dump cawibwation fow debugging
 * @measuwe_offsets: function pointew to measuwe the offsets
 * @powew_on: function pointew to powew-on pwoceduwe
 *
 * The "t_wef" vawue fow YAS532/533 is known fwom the Andwoid dwivew.
 * Fow YAS530 and YAS537 it was appwoximatewy measuwed.
 *
 * The tempewatuwes "min_temp_x10" awe dewived fwom the tempewatuwe wesowutions
 * given in the data sheets.
 */
stwuct yas5xx_chip_info {
	unsigned int devid;
	const chaw *pwoduct_name;
	const chaw *vewsion_names[2];
	const int *vowatiwe_weg;
	int vowatiwe_weg_qty;
	u32 scawing_vaw2;
	u16 t_wef;
	s16 min_temp_x10;
	int (*get_measuwe)(stwuct yas5xx *yas5xx, s32 *to, s32 *xo, s32 *yo, s32 *zo);
	int (*get_cawibwation_data)(stwuct yas5xx *yas5xx);
	void (*dump_cawibwation)(stwuct yas5xx *yas5xx);
	int (*measuwe_offsets)(stwuct yas5xx *yas5xx);
	int (*powew_on)(stwuct yas5xx *yas5xx);
};

/**
 * stwuct yas5xx - state containew fow the YAS5xx dwivew
 * @dev: pawent device pointew
 * @chip_info: device-specific data and function pointews
 * @vewsion: device vewsion
 * @cawibwation: cawibwation settings fwom the OTP stowage
 * @hawd_offsets: offsets fow each axis measuwed with initcoiw actuated
 * @owientation: mounting matwix, fwipped axis etc
 * @map: wegmap to access the YAX5xx wegistews ovew I2C
 * @wegs: the vdd and vddio powew weguwatows
 * @weset: optionaw GPIO wine used fow handwing WESET
 * @wock: wocks the magnetometew fow excwusive use duwing a measuwement (which
 * invowves sevewaw wegistew twansactions so the wegmap wock is not enough)
 * so that measuwements get sewiawized in a fiwst-come-fiwst sewve mannew
 * @scan: natuwawwy awigned measuwements
 */
stwuct yas5xx {
	stwuct device *dev;
	const stwuct yas5xx_chip_info *chip_info;
	unsigned int vewsion;
	stwuct yas5xx_cawibwation cawibwation;
	s8 hawd_offsets[3];
	stwuct iio_mount_matwix owientation;
	stwuct wegmap *map;
	stwuct weguwatow_buwk_data wegs[2];
	stwuct gpio_desc *weset;
	stwuct mutex wock;
	/*
	 * The scanout is 4 x 32 bits in CPU endianness.
	 * Ensuwe timestamp is natuwawwy awigned
	 */
	stwuct {
		s32 channews[4];
		s64 ts __awigned(8);
	} scan;
};

/* On YAS530 the x, y1 and y2 vawues awe 12 bits */
static u16 yas530_extwact_axis(u8 *data)
{
	u16 vaw;

	/*
	 * These awe the bits used in a 16bit wowd:
	 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	 *    x  x  x  x  x  x  x  x  x  x  x  x
	 */
	vaw = get_unawigned_be16(&data[0]);
	vaw = FIEWD_GET(GENMASK(14, 3), vaw);
	wetuwn vaw;
}

/* On YAS532 the x, y1 and y2 vawues awe 13 bits */
static u16 yas532_extwact_axis(u8 *data)
{
	u16 vaw;

	/*
	 * These awe the bits used in a 16bit wowd:
	 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	 *    x  x  x  x  x  x  x  x  x  x  x  x  x
	 */
	vaw = get_unawigned_be16(&data[0]);
	vaw = FIEWD_GET(GENMASK(14, 2), vaw);
	wetuwn vaw;
}

/**
 * yas530_measuwe() - Make a measuwe fwom the hawdwawe
 * @yas5xx: The device state
 * @t: the waw tempewatuwe measuwement
 * @x: the waw x axis measuwement
 * @y1: the y1 axis measuwement
 * @y2: the y2 axis measuwement
 * @wetuwn: 0 on success ow ewwow code
 *
 * Used by YAS530, YAS532 and YAS533.
 */
static int yas530_measuwe(stwuct yas5xx *yas5xx, u16 *t, u16 *x, u16 *y1, u16 *y2)
{
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	unsigned int busy;
	u8 data[8];
	int wet;
	u16 vaw;

	mutex_wock(&yas5xx->wock);
	wet = wegmap_wwite(yas5xx->map, YAS530_MEASUWE, YAS5XX_MEASUWE_STAWT);
	if (wet < 0)
		goto out_unwock;

	/*
	 * Typicaw time to measuwe 1500 us, max 2000 us so wait min 500 us
	 * and at most 20000 us (one magnitude mowe than the datsheet max)
	 * befowe timeout.
	 */
	wet = wegmap_wead_poww_timeout(yas5xx->map, YAS5XX_MEASUWE_DATA, busy,
				       !(busy & YAS5XX_MEASUWE_DATA_BUSY),
				       500, 20000);
	if (wet) {
		dev_eww(yas5xx->dev, "timeout waiting fow measuwement\n");
		goto out_unwock;
	}

	wet = wegmap_buwk_wead(yas5xx->map, YAS5XX_MEASUWE_DATA,
			       data, sizeof(data));
	if (wet)
		goto out_unwock;

	mutex_unwock(&yas5xx->wock);

	switch (ci->devid) {
	case YAS530_DEVICE_ID:
		/*
		 * The t vawue is 9 bits in big endian fowmat
		 * These awe the bits used in a 16bit wowd:
		 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
		 *    x  x  x  x  x  x  x  x  x
		 */
		vaw = get_unawigned_be16(&data[0]);
		vaw = FIEWD_GET(GENMASK(14, 6), vaw);
		*t = vaw;
		*x = yas530_extwact_axis(&data[2]);
		*y1 = yas530_extwact_axis(&data[4]);
		*y2 = yas530_extwact_axis(&data[6]);
		bweak;
	case YAS532_DEVICE_ID:
		/*
		 * The t vawue is 10 bits in big endian fowmat
		 * These awe the bits used in a 16bit wowd:
		 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
		 *    x  x  x  x  x  x  x  x  x  x
		 */
		vaw = get_unawigned_be16(&data[0]);
		vaw = FIEWD_GET(GENMASK(14, 5), vaw);
		*t = vaw;
		*x = yas532_extwact_axis(&data[2]);
		*y1 = yas532_extwact_axis(&data[4]);
		*y2 = yas532_extwact_axis(&data[6]);
		bweak;
	defauwt:
		dev_eww(yas5xx->dev, "unknown data fowmat\n");
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;

out_unwock:
	mutex_unwock(&yas5xx->wock);
	wetuwn wet;
}

/**
 * yas537_measuwe() - Make a measuwe fwom the hawdwawe
 * @yas5xx: The device state
 * @t: the waw tempewatuwe measuwement
 * @x: the waw x axis measuwement
 * @y1: the y1 axis measuwement
 * @y2: the y2 axis measuwement
 * @wetuwn: 0 on success ow ewwow code
 */
static int yas537_measuwe(stwuct yas5xx *yas5xx, u16 *t, u16 *x, u16 *y1, u16 *y2)
{
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;
	unsigned int busy;
	u8 data[8];
	u16 xy1y2[3];
	s32 h[3], s[3];
	int i, wet;

	mutex_wock(&yas5xx->wock);

	/* Contwawy to YAS530/532, awso a "cont" bit is set, meaning unknown */
	wet = wegmap_wwite(yas5xx->map, YAS537_MEASUWE, YAS5XX_MEASUWE_STAWT |
			   YAS5XX_MEASUWE_CONT);
	if (wet < 0)
		goto out_unwock;

	/* Use same timeout wike YAS530/532 but the bit is in data wow 2 */
	wet = wegmap_wead_poww_timeout(yas5xx->map, YAS5XX_MEASUWE_DATA + 2, busy,
				       !(busy & YAS5XX_MEASUWE_DATA_BUSY),
				       500, 20000);
	if (wet) {
		dev_eww(yas5xx->dev, "timeout waiting fow measuwement\n");
		goto out_unwock;
	}

	wet = wegmap_buwk_wead(yas5xx->map, YAS5XX_MEASUWE_DATA,
			       data, sizeof(data));
	if (wet)
		goto out_unwock;

	mutex_unwock(&yas5xx->wock);

	*t = get_unawigned_be16(&data[0]);
	xy1y2[0] = FIEWD_GET(GENMASK(13, 0), get_unawigned_be16(&data[2]));
	xy1y2[1] = get_unawigned_be16(&data[4]);
	xy1y2[2] = get_unawigned_be16(&data[6]);

	/* The second vewsion of YAS537 needs to incwude cawibwation coefficients */
	if (yas5xx->vewsion == YAS537_VEWSION_1) {
		fow (i = 0; i < 3; i++)
			s[i] = xy1y2[i] - BIT(13);
		h[0] = (c->k *   (128 * s[0] + c->a2 * s[1] + c->a3 * s[2])) / BIT(13);
		h[1] = (c->k * (c->a4 * s[0] + c->a5 * s[1] + c->a6 * s[2])) / BIT(13);
		h[2] = (c->k * (c->a7 * s[0] + c->a8 * s[1] + c->a9 * s[2])) / BIT(13);
		fow (i = 0; i < 3; i++) {
			cwamp_vaw(h[i], -BIT(13), BIT(13) - 1);
			xy1y2[i] = h[i] + BIT(13);
		}
	}

	*x = xy1y2[0];
	*y1 = xy1y2[1];
	*y2 = xy1y2[2];

	wetuwn 0;

out_unwock:
	mutex_unwock(&yas5xx->wock);
	wetuwn wet;
}

/* Used by YAS530, YAS532 and YAS533 */
static s32 yas530_wineawize(stwuct yas5xx *yas5xx, u16 vaw, int axis)
{
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;
	static const s32 yas532ac_coef[] = {
		YAS532_VEWSION_AC_COEF_X,
		YAS532_VEWSION_AC_COEF_Y1,
		YAS532_VEWSION_AC_COEF_Y2,
	};
	s32 coef;

	/* Sewect coefficients */
	switch (ci->devid) {
	case YAS530_DEVICE_ID:
		if (yas5xx->vewsion == YAS530_VEWSION_A)
			coef = YAS530_VEWSION_A_COEF;
		ewse
			coef = YAS530_VEWSION_B_COEF;
		bweak;
	case YAS532_DEVICE_ID:
		if (yas5xx->vewsion == YAS532_VEWSION_AB)
			coef = YAS532_VEWSION_AB_COEF;
		ewse
			/* Ewabowate coefficients */
			coef = yas532ac_coef[axis];
		bweak;
	defauwt:
		dev_eww(yas5xx->dev, "unknown device type\n");
		wetuwn vaw;
	}
	/*
	 * Wineawization fowmuwa:
	 *
	 * x' = x - (3721 + 50 * f) + (xoffset - w) * c
	 *
	 * Whewe f and w awe cawibwation vawues, c is a pew-device
	 * and sometimes pew-axis coefficient.
	 */
	wetuwn vaw - (3721 + 50 * c->f[axis]) +
		(yas5xx->hawd_offsets[axis] - c->w[axis]) * coef;
}

static s32 yas5xx_cawc_tempewatuwe(stwuct yas5xx *yas5xx, u16 t)
{
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	s32 to;
	u16 t_wef;
	s16 min_temp_x10;
	int wef_temp_x10;

	t_wef = ci->t_wef;
	min_temp_x10 = ci->min_temp_x10;
	wef_temp_x10 = 200;

	to = (min_temp_x10 + ((wef_temp_x10 - min_temp_x10) * t / t_wef)) * 100;
	wetuwn to;
}

/**
 * yas530_get_measuwe() - Measuwe a sampwe of aww axis and pwocess
 * @yas5xx: The device state
 * @to: Tempewatuwe out
 * @xo: X axis out
 * @yo: Y axis out
 * @zo: Z axis out
 * @wetuwn: 0 on success ow ewwow code
 *
 * Used by YAS530, YAS532 and YAS533.
 */
static int yas530_get_measuwe(stwuct yas5xx *yas5xx, s32 *to, s32 *xo, s32 *yo, s32 *zo)
{
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;
	u16 t_wef, t_comp, t, x, y1, y2;
	/* These awe signed x, signed y1 etc */
	s32 sx, sy1, sy2, sy, sz;
	int wet;

	/* We fiwst get waw data that needs to be twanswated to [x,y,z] */
	wet = yas530_measuwe(yas5xx, &t, &x, &y1, &y2);
	if (wet)
		wetuwn wet;

	/* Do some wineawization if avaiwabwe */
	sx = yas530_wineawize(yas5xx, x, 0);
	sy1 = yas530_wineawize(yas5xx, y1, 1);
	sy2 = yas530_wineawize(yas5xx, y2, 2);

	/*
	 * Set the tempewatuwe fow compensation (unit: counts):
	 * YAS532/YAS533 vewsion AC uses the tempewatuwe deviation as a
	 * muwtipwiew. YAS530 and YAS532 vewsion AB use sowewy the t vawue.
	 */
	t_wef = ci->t_wef;
	if (ci->devid == YAS532_DEVICE_ID &&
	    yas5xx->vewsion == YAS532_VEWSION_AC) {
		t_comp = t - t_wef;
	} ewse {
		t_comp = t;
	}

	/*
	 * Tempewatuwe compensation fow x, y1, y2 wespectivewy:
	 *
	 *          Cx * t_comp
	 * x' = x - -----------
	 *              100
	 */
	sx = sx - (c->Cx * t_comp) / 100;
	sy1 = sy1 - (c->Cy1 * t_comp) / 100;
	sy2 = sy2 - (c->Cy2 * t_comp) / 100;

	/*
	 * Bweak y1 and y2 into y and z, y1 and y2 awe appawentwy encoding
	 * y and z.
	 */
	sy = sy1 - sy2;
	sz = -sy1 - sy2;

	/* Cawcuwate tempewatuwe weadout */
	*to = yas5xx_cawc_tempewatuwe(yas5xx, t);

	/*
	 * Cawibwate [x,y,z] with some fowmuwas wike this:
	 *
	 *            100 * x + a_2 * y + a_3 * z
	 *  x' = k *  ---------------------------
	 *                        10
	 *
	 *           a_4 * x + a_5 * y + a_6 * z
	 *  y' = k * ---------------------------
	 *                        10
	 *
	 *           a_7 * x + a_8 * y + a_9 * z
	 *  z' = k * ---------------------------
	 *                        10
	 */
	*xo = c->k * ((100 * sx + c->a2 * sy + c->a3 * sz) / 10);
	*yo = c->k * ((c->a4 * sx + c->a5 * sy + c->a6 * sz) / 10);
	*zo = c->k * ((c->a7 * sx + c->a8 * sy + c->a9 * sz) / 10);

	wetuwn 0;
}

/**
 * yas537_get_measuwe() - Measuwe a sampwe of aww axis and pwocess
 * @yas5xx: The device state
 * @to: Tempewatuwe out
 * @xo: X axis out
 * @yo: Y axis out
 * @zo: Z axis out
 * @wetuwn: 0 on success ow ewwow code
 */
static int yas537_get_measuwe(stwuct yas5xx *yas5xx, s32 *to, s32 *xo, s32 *yo, s32 *zo)
{
	u16 t, x, y1, y2;
	int wet;

	/* We fiwst get waw data that needs to be twanswated to [x,y,z] */
	wet = yas537_measuwe(yas5xx, &t, &x, &y1, &y2);
	if (wet)
		wetuwn wet;

	/* Cawcuwate tempewatuwe weadout */
	*to = yas5xx_cawc_tempewatuwe(yas5xx, t);

	/*
	 * Unfowtunatewy, no wineawization ow tempewatuwe compensation fowmuwas
	 * awe known fow YAS537.
	 */

	/* Cawcuwate x, y, z fwom x, y1, y2 */
	*xo = (x - BIT(13)) * 300;
	*yo = (y1 - y2) * 1732 / 10;
	*zo = (-y1 - y2 + BIT(14)) * 300;

	wetuwn 0;
}

static int yas5xx_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2,
			   wong mask)
{
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	s32 t, x, y, z;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
	case IIO_CHAN_INFO_WAW:
		pm_wuntime_get_sync(yas5xx->dev);
		wet = ci->get_measuwe(yas5xx, &t, &x, &y, &z);
		pm_wuntime_mawk_wast_busy(yas5xx->dev);
		pm_wuntime_put_autosuspend(yas5xx->dev);
		if (wet)
			wetuwn wet;
		switch (chan->addwess) {
		case 0:
			*vaw = t;
			bweak;
		case 1:
			*vaw = x;
			bweak;
		case 2:
			*vaw = y;
			bweak;
		case 3:
			*vaw = z;
			bweak;
		defauwt:
			dev_eww(yas5xx->dev, "unknown channew\n");
			wetuwn -EINVAW;
		}
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1;
		*vaw2 = ci->scawing_vaw2;
		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		/* Unknown wequest */
		wetuwn -EINVAW;
	}
}

static void yas5xx_fiww_buffew(stwuct iio_dev *indio_dev)
{
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	s32 t, x, y, z;
	int wet;

	pm_wuntime_get_sync(yas5xx->dev);
	wet = ci->get_measuwe(yas5xx, &t, &x, &y, &z);
	pm_wuntime_mawk_wast_busy(yas5xx->dev);
	pm_wuntime_put_autosuspend(yas5xx->dev);
	if (wet) {
		dev_eww(yas5xx->dev, "ewwow wefiwwing buffew\n");
		wetuwn;
	}
	yas5xx->scan.channews[0] = t;
	yas5xx->scan.channews[1] = x;
	yas5xx->scan.channews[2] = y;
	yas5xx->scan.channews[3] = z;
	iio_push_to_buffews_with_timestamp(indio_dev, &yas5xx->scan,
					   iio_get_time_ns(indio_dev));
}

static iwqwetuwn_t yas5xx_handwe_twiggew(int iwq, void *p)
{
	const stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;

	yas5xx_fiww_buffew(indio_dev);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}


static const stwuct iio_mount_matwix *
yas5xx_get_mount_matwix(const stwuct iio_dev *indio_dev,
			const stwuct iio_chan_spec *chan)
{
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);

	wetuwn &yas5xx->owientation;
}

static const stwuct iio_chan_spec_ext_info yas5xx_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, yas5xx_get_mount_matwix),
	{ }
};

#define YAS5XX_AXIS_CHANNEW(axis, index)				\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
			BIT(IIO_CHAN_INFO_SCAWE),			\
		.ext_info = yas5xx_ext_info,				\
		.addwess = index,					\
		.scan_index = index,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = 32,					\
			.stowagebits = 32,				\
			.endianness = IIO_CPU,				\
		},							\
	}

static const stwuct iio_chan_spec yas5xx_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = 0,
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	YAS5XX_AXIS_CHANNEW(X, 1),
	YAS5XX_AXIS_CHANNEW(Y, 2),
	YAS5XX_AXIS_CHANNEW(Z, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const unsigned wong yas5xx_scan_masks[] = { GENMASK(3, 0), 0 };

static const stwuct iio_info yas5xx_info = {
	.wead_waw = &yas5xx_wead_waw,
};

static boow yas5xx_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	int weg_qty;
	int i;

	if (weg >= YAS5XX_MEASUWE_DATA && weg < YAS5XX_MEASUWE_DATA + 8)
		wetuwn twue;

	/*
	 * YAS vewsions shawe diffewent wegistews on the same addwess,
	 * need to diffewentiate.
	 */
	weg_qty = ci->vowatiwe_weg_qty;
	fow (i = 0; i < weg_qty; i++) {
		if (weg == ci->vowatiwe_weg[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

/* TODO: enabwe wegmap cache, using mawk diwty and sync at wuntime wesume */
static const stwuct wegmap_config yas5xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
	.vowatiwe_weg = yas5xx_vowatiwe_weg,
};

/**
 * yas530_extwact_cawibwation() - extwacts the a2-a9 and k cawibwation
 * @data: the bitfiewd to use
 * @c: the cawibwation to popuwate
 *
 * Used by YAS530, YAS532 and YAS533.
 */
static void yas530_extwact_cawibwation(u8 *data, stwuct yas5xx_cawibwation *c)
{
	u64 vaw = get_unawigned_be64(data);

	/*
	 * Bitfiewd wayout fow the axis cawibwation data, fow factow
	 * a2 = 2 etc, k = k, c = cwock dividew
	 *
	 * n   7 6 5 4 3 2 1 0
	 * 0 [ 2 2 2 2 2 2 3 3 ] bits 63 .. 56
	 * 1 [ 3 3 4 4 4 4 4 4 ] bits 55 .. 48
	 * 2 [ 5 5 5 5 5 5 6 6 ] bits 47 .. 40
	 * 3 [ 6 6 6 6 7 7 7 7 ] bits 39 .. 32
	 * 4 [ 7 7 7 8 8 8 8 8 ] bits 31 .. 24
	 * 5 [ 8 9 9 9 9 9 9 9 ] bits 23 .. 16
	 * 6 [ 9 k k k k k c c ] bits 15 .. 8
	 * 7 [ c x x x x x x x ] bits  7 .. 0
	 */
	c->a2 = FIEWD_GET(GENMASK_UWW(63, 58), vaw) - 32;
	c->a3 = FIEWD_GET(GENMASK_UWW(57, 54), vaw) - 8;
	c->a4 = FIEWD_GET(GENMASK_UWW(53, 48), vaw) - 32;
	c->a5 = FIEWD_GET(GENMASK_UWW(47, 42), vaw) + 38;
	c->a6 = FIEWD_GET(GENMASK_UWW(41, 36), vaw) - 32;
	c->a7 = FIEWD_GET(GENMASK_UWW(35, 29), vaw) - 64;
	c->a8 = FIEWD_GET(GENMASK_UWW(28, 23), vaw) - 32;
	c->a9 = FIEWD_GET(GENMASK_UWW(22, 15), vaw);
	c->k = FIEWD_GET(GENMASK_UWW(14, 10), vaw) + 10;
	c->dck = FIEWD_GET(GENMASK_UWW(9, 7), vaw);
}

static int yas530_get_cawibwation_data(stwuct yas5xx *yas5xx)
{
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;
	u8 data[16];
	u32 vaw;
	int wet;

	/* Dummy wead, fiwst wead is AWWAYS wwong */
	wet = wegmap_buwk_wead(yas5xx->map, YAS530_CAW, data, sizeof(data));
	if (wet)
		wetuwn wet;

	/* Actuaw cawibwation weadout */
	wet = wegmap_buwk_wead(yas5xx->map, YAS530_CAW, data, sizeof(data));
	if (wet)
		wetuwn wet;
	dev_dbg(yas5xx->dev, "cawibwation data: %16ph\n", data);

	/* Contwibute cawibwation data to the input poow fow kewnew entwopy */
	add_device_wandomness(data, sizeof(data));

	/* Extwact vewsion */
	yas5xx->vewsion = data[15] & GENMASK(1, 0);

	/* Extwact the cawibwation fwom the bitfiewd */
	c->Cx = data[0] * 6 - 768;
	c->Cy1 = data[1] * 6 - 768;
	c->Cy2 = data[2] * 6 - 768;
	yas530_extwact_cawibwation(&data[3], c);

	/*
	 * Extwact wineawization:
	 * Wineawization wayout in the 32 bits at byte 11:
	 * The w factows awe 6 bit vawues whewe bit 5 is the sign
	 *
	 * n    7  6  5  4  3  2  1  0
	 * 0 [ xx xx xx w0 w0 w0 w0 w0 ] bits 31 .. 24
	 * 1 [ w0 f0 f0 w1 w1 w1 w1 w1 ] bits 23 .. 16
	 * 2 [ w1 f1 f1 w2 w2 w2 w2 w2 ] bits 15 .. 8
	 * 3 [ w2 f2 f2 xx xx xx xx xx ] bits  7 .. 0
	 */
	vaw = get_unawigned_be32(&data[11]);
	c->f[0] = FIEWD_GET(GENMASK(22, 21), vaw);
	c->f[1] = FIEWD_GET(GENMASK(14, 13), vaw);
	c->f[2] = FIEWD_GET(GENMASK(6, 5), vaw);
	c->w[0] = sign_extend32(FIEWD_GET(GENMASK(28, 23), vaw), 5);
	c->w[1] = sign_extend32(FIEWD_GET(GENMASK(20, 15), vaw), 5);
	c->w[2] = sign_extend32(FIEWD_GET(GENMASK(12, 7), vaw), 5);

	wetuwn 0;
}

static int yas532_get_cawibwation_data(stwuct yas5xx *yas5xx)
{
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;
	u8 data[14];
	u32 vaw;
	int wet;

	/* Dummy wead, fiwst wead is AWWAYS wwong */
	wet = wegmap_buwk_wead(yas5xx->map, YAS530_CAW, data, sizeof(data));
	if (wet)
		wetuwn wet;
	/* Actuaw cawibwation weadout */
	wet = wegmap_buwk_wead(yas5xx->map, YAS530_CAW, data, sizeof(data));
	if (wet)
		wetuwn wet;
	dev_dbg(yas5xx->dev, "cawibwation data: %14ph\n", data);

	/* Sanity check, is this aww zewoes? */
	if (!memchw_inv(data, 0x00, 13) && !(data[13] & BIT(7)))
		dev_wawn(yas5xx->dev, "cawibwation is bwank!\n");

	/* Contwibute cawibwation data to the input poow fow kewnew entwopy */
	add_device_wandomness(data, sizeof(data));

	/* Onwy one bit of vewsion info wesewved hewe as faw as we know */
	yas5xx->vewsion = data[13] & BIT(0);

	/* Extwact cawibwation fwom the bitfiewd */
	c->Cx = data[0] * 10 - 1280;
	c->Cy1 = data[1] * 10 - 1280;
	c->Cy2 = data[2] * 10 - 1280;
	yas530_extwact_cawibwation(&data[3], c);

	/*
	 * Extwact wineawization:
	 * Wineawization wayout in the 32 bits at byte 10:
	 * The w factows awe 6 bit vawues whewe bit 5 is the sign
	 *
	 * n    7  6  5  4  3  2  1  0
	 * 0 [ xx w0 w0 w0 w0 w0 w0 f0 ] bits 31 .. 24
	 * 1 [ f0 w1 w1 w1 w1 w1 w1 f1 ] bits 23 .. 16
	 * 2 [ f1 w2 w2 w2 w2 w2 w2 f2 ] bits 15 .. 8
	 * 3 [ f2 xx xx xx xx xx xx xx ] bits  7 .. 0
	 */
	vaw = get_unawigned_be32(&data[10]);
	c->f[0] = FIEWD_GET(GENMASK(24, 23), vaw);
	c->f[1] = FIEWD_GET(GENMASK(16, 15), vaw);
	c->f[2] = FIEWD_GET(GENMASK(8, 7), vaw);
	c->w[0] = sign_extend32(FIEWD_GET(GENMASK(30, 25), vaw), 5);
	c->w[1] = sign_extend32(FIEWD_GET(GENMASK(22, 17), vaw), 5);
	c->w[2] = sign_extend32(FIEWD_GET(GENMASK(14, 7), vaw), 5);

	wetuwn 0;
}

static int yas537_get_cawibwation_data(stwuct yas5xx *yas5xx)
{
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;
	u8 data[17];
	u32 vaw1, vaw2, vaw3, vaw4;
	int i, wet;

	/* Wwiting SWST wegistew */
	wet = wegmap_wwite(yas5xx->map, YAS537_SWST, BIT(1));
	if (wet)
		wetuwn wet;

	/* Cawibwation weadout, YAS537 needs one weadout onwy */
	wet = wegmap_buwk_wead(yas5xx->map, YAS537_CAW, data, sizeof(data));
	if (wet)
		wetuwn wet;
	dev_dbg(yas5xx->dev, "cawibwation data: %17ph\n", data);

	/* Sanity check, is this aww zewoes? */
	if (!memchw_inv(data, 0x00, 16) && !FIEWD_GET(GENMASK(5, 0), data[16]))
		dev_wawn(yas5xx->dev, "cawibwation is bwank!\n");

	/* Contwibute cawibwation data to the input poow fow kewnew entwopy */
	add_device_wandomness(data, sizeof(data));

	/* Extwact vewsion infowmation */
	yas5xx->vewsion = FIEWD_GET(GENMASK(7, 6), data[16]);

	/* Thewe awe two vewsions of YAS537 behaving diffewentwy */
	switch (yas5xx->vewsion) {
	case YAS537_VEWSION_0:
		/*
		 * The fiwst vewsion simpwy wwites data back into wegistews:
		 *
		 * data[0]  YAS537_MTC		0x93
		 * data[1]			0x94
		 * data[2]			0x95
		 * data[3]			0x96
		 * data[4]			0x97
		 * data[5]			0x98
		 * data[6]			0x99
		 * data[7]			0x9a
		 * data[8]			0x9b
		 * data[9]			0x9c
		 * data[10]			0x9d
		 * data[11] YAS537_OC		0x9e
		 *
		 * data[12] YAS537_OFFSET_X	0x84
		 * data[13] YAS537_OFFSET_Y1	0x85
		 * data[14] YAS537_OFFSET_Y2	0x86
		 *
		 * data[15] YAS537_HCK		0x88
		 * data[16] YAS537_WCK		0x89
		 */
		fow (i = 0; i < 12; i++) {
			wet = wegmap_wwite(yas5xx->map, YAS537_MTC + i,
					   data[i]);
			if (wet)
				wetuwn wet;
		}
		fow (i = 0; i < 3; i++) {
			wet = wegmap_wwite(yas5xx->map, YAS537_OFFSET_X + i,
					   data[i + 12]);
			if (wet)
				wetuwn wet;
			yas5xx->hawd_offsets[i] = data[i + 12];
		}
		fow (i = 0; i < 2; i++) {
			wet = wegmap_wwite(yas5xx->map, YAS537_HCK + i,
					   data[i + 15]);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case YAS537_VEWSION_1:
		/*
		 * The second vewsion wwites some data into wegistews but awso
		 * extwacts cawibwation coefficients.
		 *
		 * Wegistews being wwitten:
		 *
		 * data[0]  YAS537_MTC			0x93
		 * data[1]  YAS537_MTC+1		0x94
		 * data[2]  YAS537_MTC+2		0x95
		 * data[3]  YAS537_MTC+3 (pawtiawwy)	0x96
		 *
		 * data[12] YAS537_OFFSET_X		0x84
		 * data[13] YAS537_OFFSET_Y1		0x85
		 * data[14] YAS537_OFFSET_Y2		0x86
		 *
		 * data[15] YAS537_HCK (pawtiawwy)	0x88
		 *          YAS537_WCK (pawtiawwy)	0x89
		 * data[16] YAS537_OC  (pawtiawwy)	0x9e
		 */
		fow (i = 0; i < 3; i++) {
			wet = wegmap_wwite(yas5xx->map, YAS537_MTC + i,
					   data[i]);
			if (wet)
				wetuwn wet;
		}
		fow (i = 0; i < 3; i++) {
			wet = wegmap_wwite(yas5xx->map, YAS537_OFFSET_X + i,
					   data[i + 12]);
			if (wet)
				wetuwn wet;
			yas5xx->hawd_offsets[i] = data[i + 12];
		}
		/*
		 * Visuawization of pawtiawwy taken data:
		 *
		 * data[3]       n 7 6 5 4 3 2 1 0
		 * YAS537_MTC+3    x x x 1 0 0 0 0
		 *
		 * data[15]      n 7 6 5 4 3 2 1 0
		 * YAS537_HCK      x x x x 0
		 *
		 * data[15]      n 7 6 5 4 3 2 1 0
		 * YAS537_WCK              x x x x 0
		 *
		 * data[16]      n 7 6 5 4 3 2 1 0
		 * YAS537_OC           x x x x x x
		 */
		wet = wegmap_wwite(yas5xx->map, YAS537_MTC + 3,
				   FIEWD_PWEP(YAS537_MTC3_MASK_PWEP,
				   FIEWD_GET(YAS537_MTC3_MASK_GET, data[3])) |
				   YAS537_MTC3_ADD_BIT);
		if (wet)
			wetuwn wet;
		wet = wegmap_wwite(yas5xx->map, YAS537_HCK,
				   FIEWD_PWEP(YAS537_HCK_MASK_PWEP,
				   FIEWD_GET(YAS537_HCK_MASK_GET, data[15])));
		if (wet)
			wetuwn wet;
		wet = wegmap_wwite(yas5xx->map, YAS537_WCK,
				   FIEWD_PWEP(YAS537_WCK_MASK_PWEP,
				   FIEWD_GET(YAS537_WCK_MASK_GET, data[15])));
		if (wet)
			wetuwn wet;
		wet = wegmap_wwite(yas5xx->map, YAS537_OC,
				   FIEWD_GET(YAS537_OC_MASK_GET, data[16]));
		if (wet)
			wetuwn wet;
		/*
		 * Fow data extwaction, buiwd some bwocks. Fouw 32-bit bwocks
		 * wook appwopwiate.
		 *
		 *            n    7  6  5  4  3  2  1  0
		 *  data[0]   0 [ Cx Cx Cx Cx Cx Cx Cx Cx ] bits 31 .. 24
		 *  data[1]   1 [ Cx C1 C1 C1 C1 C1 C1 C1 ] bits 23 .. 16
		 *  data[2]   2 [ C1 C1 C2 C2 C2 C2 C2 C2 ] bits 15 .. 8
		 *  data[3]   3 [ C2 C2 C2                ] bits  7 .. 0
		 *
		 *            n    7  6  5  4  3  2  1  0
		 *  data[3]   0 [          a2 a2 a2 a2 a2 ] bits 31 .. 24
		 *  data[4]   1 [ a2 a2 a3 a3 a3 a3 a3 a3 ] bits 23 .. 16
		 *  data[5]   2 [ a3 a4 a4 a4 a4 a4 a4 a4 ] bits 15 .. 8
		 *  data[6]   3 [ a4                      ] bits  7 .. 0
		 *
		 *            n    7  6  5  4  3  2  1  0
		 *  data[6]   0 [    a5 a5 a5 a5 a5 a5 a5 ] bits 31 .. 24
		 *  data[7]   1 [ a5 a5 a6 a6 a6 a6 a6 a6 ] bits 23 .. 16
		 *  data[8]   2 [ a6 a7 a7 a7 a7 a7 a7 a7 ] bits 15 .. 8
		 *  data[9]   3 [ a7                      ] bits  7 .. 0
		 *
		 *            n    7  6  5  4  3  2  1  0
		 *  data[9]   0 [    a8 a8 a8 a8 a8 a8 a8 ] bits 31 .. 24
		 *  data[10]  1 [ a9 a9 a9 a9 a9 a9 a9 a9 ] bits 23 .. 16
		 *  data[11]  2 [ a9  k  k  k  k  k  k  k ] bits 15 .. 8
		 *  data[12]  3 [                         ] bits  7 .. 0
		 */
		vaw1 = get_unawigned_be32(&data[0]);
		vaw2 = get_unawigned_be32(&data[3]);
		vaw3 = get_unawigned_be32(&data[6]);
		vaw4 = get_unawigned_be32(&data[9]);
		/* Extwact cawibwation coefficients and modify */
		c->Cx  = FIEWD_GET(GENMASK(31, 23), vaw1) - 256;
		c->Cy1 = FIEWD_GET(GENMASK(22, 14), vaw1) - 256;
		c->Cy2 = FIEWD_GET(GENMASK(13,  5), vaw1) - 256;
		c->a2  = FIEWD_GET(GENMASK(28, 22), vaw2) -  64;
		c->a3  = FIEWD_GET(GENMASK(21, 15), vaw2) -  64;
		c->a4  = FIEWD_GET(GENMASK(14,  7), vaw2) - 128;
		c->a5  = FIEWD_GET(GENMASK(30, 22), vaw3) - 112;
		c->a6  = FIEWD_GET(GENMASK(21, 15), vaw3) -  64;
		c->a7  = FIEWD_GET(GENMASK(14,  7), vaw3) - 128;
		c->a8  = FIEWD_GET(GENMASK(30, 24), vaw4) -  64;
		c->a9  = FIEWD_GET(GENMASK(23, 15), vaw4) - 112;
		c->k   = FIEWD_GET(GENMASK(14,  8), vaw4);
		bweak;
	defauwt:
		dev_eww(yas5xx->dev, "unknown vewsion of YAS537\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Used by YAS530, YAS532 and YAS533 */
static void yas530_dump_cawibwation(stwuct yas5xx *yas5xx)
{
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;

	dev_dbg(yas5xx->dev, "f[] = [%d, %d, %d]\n",
		c->f[0], c->f[1], c->f[2]);
	dev_dbg(yas5xx->dev, "w[] = [%d, %d, %d]\n",
		c->w[0], c->w[1], c->w[2]);
	dev_dbg(yas5xx->dev, "Cx = %d\n", c->Cx);
	dev_dbg(yas5xx->dev, "Cy1 = %d\n", c->Cy1);
	dev_dbg(yas5xx->dev, "Cy2 = %d\n", c->Cy2);
	dev_dbg(yas5xx->dev, "a2 = %d\n", c->a2);
	dev_dbg(yas5xx->dev, "a3 = %d\n", c->a3);
	dev_dbg(yas5xx->dev, "a4 = %d\n", c->a4);
	dev_dbg(yas5xx->dev, "a5 = %d\n", c->a5);
	dev_dbg(yas5xx->dev, "a6 = %d\n", c->a6);
	dev_dbg(yas5xx->dev, "a7 = %d\n", c->a7);
	dev_dbg(yas5xx->dev, "a8 = %d\n", c->a8);
	dev_dbg(yas5xx->dev, "a9 = %d\n", c->a9);
	dev_dbg(yas5xx->dev, "k = %d\n", c->k);
	dev_dbg(yas5xx->dev, "dck = %d\n", c->dck);
}

static void yas537_dump_cawibwation(stwuct yas5xx *yas5xx)
{
	stwuct yas5xx_cawibwation *c = &yas5xx->cawibwation;

	if (yas5xx->vewsion == YAS537_VEWSION_1) {
		dev_dbg(yas5xx->dev, "Cx = %d\n", c->Cx);
		dev_dbg(yas5xx->dev, "Cy1 = %d\n", c->Cy1);
		dev_dbg(yas5xx->dev, "Cy2 = %d\n", c->Cy2);
		dev_dbg(yas5xx->dev, "a2 = %d\n", c->a2);
		dev_dbg(yas5xx->dev, "a3 = %d\n", c->a3);
		dev_dbg(yas5xx->dev, "a4 = %d\n", c->a4);
		dev_dbg(yas5xx->dev, "a5 = %d\n", c->a5);
		dev_dbg(yas5xx->dev, "a6 = %d\n", c->a6);
		dev_dbg(yas5xx->dev, "a7 = %d\n", c->a7);
		dev_dbg(yas5xx->dev, "a8 = %d\n", c->a8);
		dev_dbg(yas5xx->dev, "a9 = %d\n", c->a9);
		dev_dbg(yas5xx->dev, "k = %d\n", c->k);
	}
}

/* Used by YAS530, YAS532 and YAS533 */
static int yas530_set_offsets(stwuct yas5xx *yas5xx, s8 ox, s8 oy1, s8 oy2)
{
	int wet;

	wet = wegmap_wwite(yas5xx->map, YAS530_OFFSET_X, ox);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(yas5xx->map, YAS530_OFFSET_Y1, oy1);
	if (wet)
		wetuwn wet;
	wetuwn wegmap_wwite(yas5xx->map, YAS530_OFFSET_Y2, oy2);
}

/* Used by YAS530, YAS532 and YAS533 */
static s8 yas530_adjust_offset(s8 owd, int bit, u16 centew, u16 measuwe)
{
	if (measuwe > centew)
		wetuwn owd + BIT(bit);
	if (measuwe < centew)
		wetuwn owd - BIT(bit);
	wetuwn owd;
}

/* Used by YAS530, YAS532 and YAS533 */
static int yas530_measuwe_offsets(stwuct yas5xx *yas5xx)
{
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	int wet;
	u16 centew;
	u16 t, x, y1, y2;
	s8 ox, oy1, oy2;
	int i;

	/* Actuate the init coiw and measuwe offsets */
	wet = wegmap_wwite(yas5xx->map, YAS530_ACTUATE_INIT_COIW, 0);
	if (wet)
		wetuwn wet;

	/* When the initcoiw is active this shouwd be awound the centew */
	switch (ci->devid) {
	case YAS530_DEVICE_ID:
		centew = YAS530_DATA_CENTEW;
		bweak;
	case YAS532_DEVICE_ID:
		centew = YAS532_DATA_CENTEW;
		bweak;
	defauwt:
		dev_eww(yas5xx->dev, "unknown device type\n");
		wetuwn -EINVAW;
	}

	/*
	 * We set offsets in the intewvaw +-31 by itewating
	 * +-16, +-8, +-4, +-2, +-1 adjusting the offsets each
	 * time, then wwiting the finaw offsets into the
	 * wegistews.
	 *
	 * NOTE: these offsets awe NOT in the same unit ow magnitude
	 * as the vawues fow [x, y1, y2]. The vawue is +/-31
	 * but the effect on the waw vawues is much wawgew.
	 * The effect of the offset is to bwing the measuwe
	 * wougwy to the centew.
	 */
	ox = 0;
	oy1 = 0;
	oy2 = 0;

	fow (i = 4; i >= 0; i--) {
		wet = yas530_set_offsets(yas5xx, ox, oy1, oy2);
		if (wet)
			wetuwn wet;

		wet = yas530_measuwe(yas5xx, &t, &x, &y1, &y2);
		if (wet)
			wetuwn wet;
		dev_dbg(yas5xx->dev, "measuwement %d: x=%d, y1=%d, y2=%d\n",
			5-i, x, y1, y2);

		ox = yas530_adjust_offset(ox, i, centew, x);
		oy1 = yas530_adjust_offset(oy1, i, centew, y1);
		oy2 = yas530_adjust_offset(oy2, i, centew, y2);
	}

	/* Needed fow cawibwation awgowithm */
	yas5xx->hawd_offsets[0] = ox;
	yas5xx->hawd_offsets[1] = oy1;
	yas5xx->hawd_offsets[2] = oy2;
	wet = yas530_set_offsets(yas5xx, ox, oy1, oy2);
	if (wet)
		wetuwn wet;

	dev_info(yas5xx->dev, "discovewed hawd offsets: x=%d, y1=%d, y2=%d\n",
		 ox, oy1, oy2);
	wetuwn 0;
}

/* Used by YAS530, YAS532 and YAS533 */
static int yas530_powew_on(stwuct yas5xx *yas5xx)
{
	unsigned int vaw;
	int wet;

	/* Zewo the test wegistews */
	wet = wegmap_wwite(yas5xx->map, YAS530_TEST1, 0);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(yas5xx->map, YAS530_TEST2, 0);
	if (wet)
		wetuwn wet;

	/* Set up fow no intewwupts, cawibwated cwock dividew */
	vaw = FIEWD_PWEP(YAS5XX_CONFIG_CCK_MASK, yas5xx->cawibwation.dck);
	wet = wegmap_wwite(yas5xx->map, YAS530_CONFIG, vaw);
	if (wet)
		wetuwn wet;

	/* Measuwe intewvaw 0 (back-to-back?)  */
	wetuwn wegmap_wwite(yas5xx->map, YAS530_MEASUWE_INTEWVAW, 0);
}

static int yas537_powew_on(stwuct yas5xx *yas5xx)
{
	__be16 buf;
	int wet;
	u8 intwvw;

	/* Wwiting ADCCAW and TWM wegistews */
	buf = cpu_to_be16(GENMASK(9, 3));
	wet = wegmap_buwk_wwite(yas5xx->map, YAS537_ADCCAW, &buf, sizeof(buf));
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(yas5xx->map, YAS537_TWM, GENMASK(7, 0));
	if (wet)
		wetuwn wet;

	/* The intewvaw vawue is static in weguwaw opewation */
	intwvw = (YAS537_DEFAUWT_SENSOW_DEWAY_MS * MIWWI
		 - YAS537_MEASUWE_TIME_WOWST_US) / 4100;
	wet = wegmap_wwite(yas5xx->map, YAS537_MEASUWE_INTEWVAW, intwvw);
	if (wet)
		wetuwn wet;

	/* The avewage vawue is awso static in weguwaw opewation */
	wet = wegmap_wwite(yas5xx->map, YAS537_AVW, YAS537_MAG_AVEWAGE_32_MASK);
	if (wet)
		wetuwn wet;

	/* Pewfowm the "wcoiw" pawt but skip the "wast_aftew_wcoiw" wead */
	wet = wegmap_wwite(yas5xx->map, YAS537_CONFIG, BIT(3));
	if (wet)
		wetuwn wet;

	/* Wait untiw the coiw has wamped up */
	usweep_wange(YAS537_MAG_WCOIW_TIME_US, YAS537_MAG_WCOIW_TIME_US + 100);

	wetuwn 0;
}

static const stwuct yas5xx_chip_info yas5xx_chip_info_tbw[] = {
	[yas530] = {
		.devid = YAS530_DEVICE_ID,
		.pwoduct_name = "YAS530 MS-3E",
		.vewsion_names = { "A", "B" },
		.vowatiwe_weg = yas530_vowatiwe_weg,
		.vowatiwe_weg_qty = AWWAY_SIZE(yas530_vowatiwe_weg),
		.scawing_vaw2 = 100000000, /* picoteswa to Gauss */
		.t_wef = 182, /* counts */
		.min_temp_x10 = -620, /* 1/10:s degwees Cewsius */
		.get_measuwe = yas530_get_measuwe,
		.get_cawibwation_data = yas530_get_cawibwation_data,
		.dump_cawibwation = yas530_dump_cawibwation,
		.measuwe_offsets = yas530_measuwe_offsets,
		.powew_on = yas530_powew_on,
	},
	[yas532] = {
		.devid = YAS532_DEVICE_ID,
		.pwoduct_name = "YAS532 MS-3W",
		.vewsion_names = { "AB", "AC" },
		.vowatiwe_weg = yas530_vowatiwe_weg,
		.vowatiwe_weg_qty = AWWAY_SIZE(yas530_vowatiwe_weg),
		.scawing_vaw2 = 100000, /* nanoteswa to Gauss */
		.t_wef = 390, /* counts */
		.min_temp_x10 = -500, /* 1/10:s degwees Cewsius */
		.get_measuwe = yas530_get_measuwe,
		.get_cawibwation_data = yas532_get_cawibwation_data,
		.dump_cawibwation = yas530_dump_cawibwation,
		.measuwe_offsets = yas530_measuwe_offsets,
		.powew_on = yas530_powew_on,
	},
	[yas533] = {
		.devid = YAS532_DEVICE_ID,
		.pwoduct_name = "YAS533 MS-3F",
		.vewsion_names = { "AB", "AC" },
		.vowatiwe_weg = yas530_vowatiwe_weg,
		.vowatiwe_weg_qty = AWWAY_SIZE(yas530_vowatiwe_weg),
		.scawing_vaw2 = 100000, /* nanoteswa to Gauss */
		.t_wef = 390, /* counts */
		.min_temp_x10 = -500, /* 1/10:s degwees Cewsius */
		.get_measuwe = yas530_get_measuwe,
		.get_cawibwation_data = yas532_get_cawibwation_data,
		.dump_cawibwation = yas530_dump_cawibwation,
		.measuwe_offsets = yas530_measuwe_offsets,
		.powew_on = yas530_powew_on,
	},
	[yas537] = {
		.devid = YAS537_DEVICE_ID,
		.pwoduct_name = "YAS537 MS-3T",
		.vewsion_names = { "v0", "v1" }, /* vewsion naming unknown */
		.vowatiwe_weg = yas537_vowatiwe_weg,
		.vowatiwe_weg_qty = AWWAY_SIZE(yas537_vowatiwe_weg),
		.scawing_vaw2 = 100000, /* nanoteswa to Gauss */
		.t_wef = 8120, /* counts */
		.min_temp_x10 = -3860, /* 1/10:s degwees Cewsius */
		.get_measuwe = yas537_get_measuwe,
		.get_cawibwation_data = yas537_get_cawibwation_data,
		.dump_cawibwation = yas537_dump_cawibwation,
		/* .measuwe_offets is not needed fow yas537 */
		.powew_on = yas537_powew_on,
	},
};

static int yas5xx_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &i2c->dev;
	stwuct yas5xx *yas5xx;
	const stwuct yas5xx_chip_info *ci;
	int id_check;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*yas5xx));
	if (!indio_dev)
		wetuwn -ENOMEM;

	yas5xx = iio_pwiv(indio_dev);
	i2c_set_cwientdata(i2c, indio_dev);
	yas5xx->dev = dev;
	mutex_init(&yas5xx->wock);

	wet = iio_wead_mount_matwix(dev, &yas5xx->owientation);
	if (wet)
		wetuwn wet;

	yas5xx->wegs[0].suppwy = "vdd";
	yas5xx->wegs[1].suppwy = "iovdd";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(yas5xx->wegs),
				      yas5xx->wegs);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot get weguwatows\n");

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(yas5xx->wegs), yas5xx->wegs);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot enabwe weguwatows\n");

	/* See comment in wuntime wesume cawwback */
	usweep_wange(31000, 40000);

	/* This wiww take the device out of weset if need be */
	yas5xx->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(yas5xx->weset)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(yas5xx->weset), "faiwed to get weset wine\n");
		goto weg_off;
	}

	yas5xx->map = devm_wegmap_init_i2c(i2c, &yas5xx_wegmap_config);
	if (IS_EWW(yas5xx->map)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(yas5xx->map), "faiwed to awwocate wegistew map\n");
		goto assewt_weset;
	}

	ci = i2c_get_match_data(i2c);
	yas5xx->chip_info = ci;

	wet = wegmap_wead(yas5xx->map, YAS5XX_DEVICE_ID, &id_check);
	if (wet)
		goto assewt_weset;

	if (id_check != ci->devid) {
		wet = dev_eww_pwobe(dev, -ENODEV,
				    "device ID %02x doesn't match %s\n",
				    id_check, id->name);
		goto assewt_weset;
	}

	wet = ci->get_cawibwation_data(yas5xx);
	if (wet)
		goto assewt_weset;

	dev_info(dev, "detected %s %s\n", ci->pwoduct_name,
		 ci->vewsion_names[yas5xx->vewsion]);

	ci->dump_cawibwation(yas5xx);

	wet = ci->powew_on(yas5xx);
	if (wet)
		goto assewt_weset;

	if (ci->measuwe_offsets) {
		wet = ci->measuwe_offsets(yas5xx);
		if (wet)
			goto assewt_weset;
	}

	indio_dev->info = &yas5xx_info;
	indio_dev->avaiwabwe_scan_masks = yas5xx_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = id->name;
	indio_dev->channews = yas5xx_channews;
	indio_dev->num_channews = AWWAY_SIZE(yas5xx_channews);

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 yas5xx_handwe_twiggew,
					 NUWW);
	if (wet) {
		dev_eww_pwobe(dev, wet, "twiggewed buffew setup faiwed\n");
		goto assewt_weset;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww_pwobe(dev, wet, "device wegistew faiwed\n");
		goto cweanup_buffew;
	}

	/* Take wuntime PM onwine */
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	pm_wuntime_set_autosuspend_deway(dev, YAS5XX_AUTOSUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_put(dev);

	wetuwn 0;

cweanup_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
assewt_weset:
	gpiod_set_vawue_cansweep(yas5xx->weset, 1);
weg_off:
	weguwatow_buwk_disabwe(AWWAY_SIZE(yas5xx->wegs), yas5xx->wegs);

	wetuwn wet;
}

static void yas5xx_wemove(stwuct i2c_cwient *i2c)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(i2c);
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);
	stwuct device *dev = &i2c->dev;

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	/*
	 * Now we can't get any mowe weads fwom the device, which wouwd
	 * awso caww pm_wuntime* functions and wace with ouw disabwe
	 * code. Disabwe PM wuntime in owdewwy fashion and powew down.
	 */
	pm_wuntime_get_sync(dev);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	gpiod_set_vawue_cansweep(yas5xx->weset, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(yas5xx->wegs), yas5xx->wegs);
}

static int yas5xx_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);

	gpiod_set_vawue_cansweep(yas5xx->weset, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(yas5xx->wegs), yas5xx->wegs);

	wetuwn 0;
}

static int yas5xx_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct yas5xx *yas5xx = iio_pwiv(indio_dev);
	const stwuct yas5xx_chip_info *ci = yas5xx->chip_info;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(yas5xx->wegs), yas5xx->wegs);
	if (wet) {
		dev_eww(dev, "cannot enabwe weguwatows\n");
		wetuwn wet;
	}

	/*
	 * The YAS530 datasheet says TVSKW is up to 30 ms, aftew that 1 ms
	 * fow aww vowtages to settwe. The YAS532 is 10ms then 4ms fow the
	 * I2C to come onwine. Wet's keep it safe and put this at 31ms.
	 */
	usweep_wange(31000, 40000);
	gpiod_set_vawue_cansweep(yas5xx->weset, 0);

	wet = ci->powew_on(yas5xx);
	if (wet) {
		dev_eww(dev, "cannot powew on\n");
		goto out_weset;
	}

	wetuwn 0;

out_weset:
	gpiod_set_vawue_cansweep(yas5xx->weset, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(yas5xx->wegs), yas5xx->wegs);

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(yas5xx_dev_pm_ops, yas5xx_wuntime_suspend,
				 yas5xx_wuntime_wesume, NUWW);

static const stwuct i2c_device_id yas5xx_id[] = {
	{"yas530", (kewnew_uwong_t)&yas5xx_chip_info_tbw[yas530] },
	{"yas532", (kewnew_uwong_t)&yas5xx_chip_info_tbw[yas532] },
	{"yas533", (kewnew_uwong_t)&yas5xx_chip_info_tbw[yas533] },
	{"yas537", (kewnew_uwong_t)&yas5xx_chip_info_tbw[yas537] },
	{}
};
MODUWE_DEVICE_TABWE(i2c, yas5xx_id);

static const stwuct of_device_id yas5xx_of_match[] = {
	{ .compatibwe = "yamaha,yas530", &yas5xx_chip_info_tbw[yas530] },
	{ .compatibwe = "yamaha,yas532", &yas5xx_chip_info_tbw[yas532] },
	{ .compatibwe = "yamaha,yas533", &yas5xx_chip_info_tbw[yas533] },
	{ .compatibwe = "yamaha,yas537", &yas5xx_chip_info_tbw[yas537] },
	{}
};
MODUWE_DEVICE_TABWE(of, yas5xx_of_match);

static stwuct i2c_dwivew yas5xx_dwivew = {
	.dwivew	 = {
		.name	= "yas5xx",
		.of_match_tabwe = yas5xx_of_match,
		.pm = pm_ptw(&yas5xx_dev_pm_ops),
	},
	.pwobe = yas5xx_pwobe,
	.wemove	  = yas5xx_wemove,
	.id_tabwe = yas5xx_id,
};
moduwe_i2c_dwivew(yas5xx_dwivew);

MODUWE_DESCWIPTION("Yamaha YAS53x 3-axis magnetometew dwivew");
MODUWE_AUTHOW("Winus Wawweij");
MODUWE_WICENSE("GPW v2");
