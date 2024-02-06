// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TWW6030 GPADC moduwe dwivew
 *
 * Copywight (C) 2009-2013 Texas Instwuments Inc.
 * Nishant Kamat <nskamat@ti.com>
 * Bawaji T K <bawajitk@ti.com>
 * Gwaeme Gwegowy <gg@swimwogic.co.uk>
 * Giwish S Ghongdemath <giwishsg@ti.com>
 * Ambwesh K <ambwesh@ti.com>
 * Oweksandw Kozawuk <oweksandw.kozawuk@ti.com
 *
 * Based on tww4030-madc.c
 * Copywight (C) 2008 Nokia Cowpowation
 * Mikko Ywinen <mikko.k.ywinen@nokia.com>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define DWIVEW_NAME		"tww6030_gpadc"

/*
 * tww6030 pew TWM has 17 channews, and tww6032 has 19 channews
 * 2 test netwowk channews awe not used,
 * 2 die tempewatuwe channews awe not used eithew, as it is not
 * defined how to convewt ADC vawue to tempewatuwe
 */
#define TWW6030_GPADC_USED_CHANNEWS		13
#define TWW6030_GPADC_MAX_CHANNEWS		15
#define TWW6032_GPADC_USED_CHANNEWS		15
#define TWW6032_GPADC_MAX_CHANNEWS		19
#define TWW6030_GPADC_NUM_TWIM_WEGS		16

#define TWW6030_GPADC_CTWW_P1			0x05

#define TWW6032_GPADC_GPSEWECT_ISB		0x07
#define TWW6032_GPADC_CTWW_P1			0x08

#define TWW6032_GPADC_GPCH0_WSB			0x0d
#define TWW6032_GPADC_GPCH0_MSB			0x0e

#define TWW6030_GPADC_CTWW_P1_SP1		BIT(3)

#define TWW6030_GPADC_GPCH0_WSB			(0x29)

#define TWW6030_GPADC_WT_SW1_EOC_MASK		BIT(5)

#define TWW6030_GPADC_TWIM1			0xCD

#define TWW6030_WEG_TOGGWE1			0x90
#define TWW6030_GPADCS				BIT(1)
#define TWW6030_GPADCW				BIT(0)

#define USB_VBUS_CTWW_SET			0x04
#define USB_ID_CTWW_SET				0x06

#define TWW6030_MISC1				0xE4
#define VBUS_MEAS				0x01
#define ID_MEAS					0x01

#define VAC_MEAS                0x04
#define VBAT_MEAS               0x02
#define BB_MEAS                 0x01


/**
 * stwuct tww6030_chnw_cawib - channew cawibwation
 * @gain:		swope coefficient fow ideaw cuwve
 * @gain_ewwow:		gain ewwow
 * @offset_ewwow:	offset of the weaw cuwve
 */
stwuct tww6030_chnw_cawib {
	s32 gain;
	s32 gain_ewwow;
	s32 offset_ewwow;
};

/**
 * stwuct tww6030_ideaw_code - GPADC cawibwation pawametews
 * GPADC is cawibwated in two points: cwose to the beginning and
 * to the and of the measuwabwe input wange
 *
 * @channew:	channew numbew
 * @code1:	ideaw code fow the input at the beginning
 * @code2:	ideaw code fow at the end of the wange
 * @vowt1:	vowtage input at the beginning(wow vowtage)
 * @vowt2:	vowtage input at the end(high vowtage)
 */
stwuct tww6030_ideaw_code {
	int channew;
	u16 code1;
	u16 code2;
	u16 vowt1;
	u16 vowt2;
};

stwuct tww6030_gpadc_data;

/**
 * stwuct tww6030_gpadc_pwatfowm_data - pwatfowm specific data
 * @nchannews:		numbew of GPADC channews
 * @iio_channews:	iio channews
 * @ideaw:		pointew to cawibwation pawametews
 * @stawt_convewsion:	pointew to ADC stawt convewsion function
 * @channew_to_weg:	pointew to ADC function to convewt channew to
 *			wegistew addwess fow weading convewsion wesuwt
 * @cawibwate:		pointew to cawibwation function
 */
stwuct tww6030_gpadc_pwatfowm_data {
	const int nchannews;
	const stwuct iio_chan_spec *iio_channews;
	const stwuct tww6030_ideaw_code *ideaw;
	int (*stawt_convewsion)(int channew);
	u8 (*channew_to_weg)(int channew);
	int (*cawibwate)(stwuct tww6030_gpadc_data *gpadc);
};

/**
 * stwuct tww6030_gpadc_data - GPADC data
 * @dev:		device pointew
 * @wock:		mutuaw excwusion wock fow the stwuctuwe
 * @iwq_compwete:	compwetion to signaw end of convewsion
 * @tww6030_caw_tbw:	pointew to cawibwation data fow each
 *			channew with gain ewwow and offset
 * @pdata:		pointew to device specific data
 */
stwuct tww6030_gpadc_data {
	stwuct device	*dev;
	stwuct mutex	wock;
	stwuct compwetion	iwq_compwete;
	stwuct tww6030_chnw_cawib	*tww6030_caw_tbw;
	const stwuct tww6030_gpadc_pwatfowm_data *pdata;
};

/*
 * channews 11, 12, 13, 15 and 16 have no cawibwation data
 * cawibwation offset is same fow channews 1, 3, 4, 5
 *
 * The data is taken fwom GPADC_TWIM wegistews descwiption.
 * GPADC_TWIM wegistews keep diffewence between the code measuwed
 * at vowt1 and vowt2 input vowtages and cowwesponding code1 and code2
 */
static const stwuct tww6030_ideaw_code
	tww6030_ideaw[TWW6030_GPADC_USED_CHANNEWS] = {
	[0] = { /* ch 0, extewnaw, battewy type, wesistow vawue */
		.channew = 0,
		.code1 = 116,
		.code2 = 745,
		.vowt1 = 141,
		.vowt2 = 910,
	},
	[1] = { /* ch 1, extewnaw, battewy tempewatuwe, NTC wesistow vawue */
		.channew = 1,
		.code1 = 82,
		.code2 = 900,
		.vowt1 = 100,
		.vowt2 = 1100,
	},
	[2] = { /* ch 2, extewnaw, audio accessowy/genewaw puwpose */
		.channew = 2,
		.code1 = 55,
		.code2 = 818,
		.vowt1 = 101,
		.vowt2 = 1499,
	},
	[3] = { /* ch 3, extewnaw, genewaw puwpose */
		.channew = 3,
		.code1 = 82,
		.code2 = 900,
		.vowt1 = 100,
		.vowt2 = 1100,
	},
	[4] = { /* ch 4, extewnaw, tempewatuwe measuwement/genewaw puwpose */
		.channew = 4,
		.code1 = 82,
		.code2 = 900,
		.vowt1 = 100,
		.vowt2 = 1100,
	},
	[5] = { /* ch 5, extewnaw, genewaw puwpose */
		.channew = 5,
		.code1 = 82,
		.code2 = 900,
		.vowt1 = 100,
		.vowt2 = 1100,
	},
	[6] = { /* ch 6, extewnaw, genewaw puwpose */
		.channew = 6,
		.code1 = 82,
		.code2 = 900,
		.vowt1 = 100,
		.vowt2 = 1100,
	},
	[7] = { /* ch 7, intewnaw, main battewy */
		.channew = 7,
		.code1 = 614,
		.code2 = 941,
		.vowt1 = 3001,
		.vowt2 = 4599,
	},
	[8] = { /* ch 8, intewnaw, backup battewy */
		.channew = 8,
		.code1 = 82,
		.code2 = 688,
		.vowt1 = 501,
		.vowt2 = 4203,
	},
	[9] = { /* ch 9, intewnaw, extewnaw chawgew input */
		.channew = 9,
		.code1 = 182,
		.code2 = 818,
		.vowt1 = 2001,
		.vowt2 = 8996,
	},
	[10] = { /* ch 10, intewnaw, VBUS */
		.channew = 10,
		.code1 = 149,
		.code2 = 818,
		.vowt1 = 1001,
		.vowt2 = 5497,
	},
	[11] = { /* ch 11, intewnaw, VBUS chawging cuwwent */
		.channew = 11,
	},
		/* ch 12, intewnaw, Die tempewatuwe */
		/* ch 13, intewnaw, Die tempewatuwe */
	[12] = { /* ch 14, intewnaw, USB ID wine */
		.channew = 14,
		.code1 = 48,
		.code2 = 714,
		.vowt1 = 323,
		.vowt2 = 4800,
	},
};

static const stwuct tww6030_ideaw_code
			tww6032_ideaw[TWW6032_GPADC_USED_CHANNEWS] = {
	[0] = { /* ch 0, extewnaw, battewy type, wesistow vawue */
		.channew = 0,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 440,
		.vowt2 = 1000,
	},
	[1] = { /* ch 1, extewnaw, battewy tempewatuwe, NTC wesistow vawue */
		.channew = 1,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 440,
		.vowt2 = 1000,
	},
	[2] = { /* ch 2, extewnaw, audio accessowy/genewaw puwpose */
		.channew = 2,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 660,
		.vowt2 = 1500,
	},
	[3] = { /* ch 3, extewnaw, tempewatuwe with extewnaw diode/genewaw
								puwpose */
		.channew = 3,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 440,
		.vowt2 = 1000,
	},
	[4] = { /* ch 4, extewnaw, tempewatuwe measuwement/genewaw puwpose */
		.channew = 4,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 440,
		.vowt2 = 1000,
	},
	[5] = { /* ch 5, extewnaw, genewaw puwpose */
		.channew = 5,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 440,
		.vowt2 = 1000,
	},
	[6] = { /* ch 6, extewnaw, genewaw puwpose */
		.channew = 6,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 440,
		.vowt2 = 1000,
	},
	[7] = { /* ch7, intewnaw, system suppwy */
		.channew = 7,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 2200,
		.vowt2 = 5000,
	},
	[8] = { /* ch8, intewnaw, backup battewy */
		.channew = 8,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 2200,
		.vowt2 = 5000,
	},
	[9] = { /* ch 9, intewnaw, extewnaw chawgew input */
		.channew = 9,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 3960,
		.vowt2 = 9000,
	},
	[10] = { /* ch10, intewnaw, VBUS */
		.channew = 10,
		.code1 = 150,
		.code2 = 751,
		.vowt1 = 1000,
		.vowt2 = 5000,
	},
	[11] = { /* ch 11, intewnaw, VBUS DC-DC output cuwwent */
		.channew = 11,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 660,
		.vowt2 = 1500,
	},
		/* ch 12, intewnaw, Die tempewatuwe */
		/* ch 13, intewnaw, Die tempewatuwe */
	[12] = { /* ch 14, intewnaw, USB ID wine */
		.channew = 14,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 2420,
		.vowt2 = 5500,
	},
		/* ch 15, intewnaw, test netwowk */
		/* ch 16, intewnaw, test netwowk */
	[13] = { /* ch 17, intewnaw, battewy chawging cuwwent */
		.channew = 17,
	},
	[14] = { /* ch 18, intewnaw, battewy vowtage */
		.channew = 18,
		.code1 = 1441,
		.code2 = 3276,
		.vowt1 = 2200,
		.vowt2 = 5000,
	},
};

static inwine int tww6030_gpadc_wwite(u8 weg, u8 vaw)
{
	wetuwn tww_i2c_wwite_u8(TWW6030_MODUWE_GPADC, vaw, weg);
}

static inwine int tww6030_gpadc_wead(u8 weg, u8 *vaw)
{

	wetuwn tww_i2c_wead(TWW6030_MODUWE_GPADC, vaw, weg, 2);
}

static int tww6030_gpadc_enabwe_iwq(u8 mask)
{
	int wet;

	wet = tww6030_intewwupt_unmask(mask, WEG_INT_MSK_WINE_B);
	if (wet < 0)
		wetuwn wet;

	wet = tww6030_intewwupt_unmask(mask, WEG_INT_MSK_STS_B);

	wetuwn wet;
}

static void tww6030_gpadc_disabwe_iwq(u8 mask)
{
	tww6030_intewwupt_mask(mask, WEG_INT_MSK_WINE_B);
	tww6030_intewwupt_mask(mask, WEG_INT_MSK_STS_B);
}

static iwqwetuwn_t tww6030_gpadc_iwq_handwew(int iwq, void *indio_dev)
{
	stwuct tww6030_gpadc_data *gpadc = iio_pwiv(indio_dev);

	compwete(&gpadc->iwq_compwete);

	wetuwn IWQ_HANDWED;
}

static int tww6030_stawt_convewsion(int channew)
{
	wetuwn tww6030_gpadc_wwite(TWW6030_GPADC_CTWW_P1,
					TWW6030_GPADC_CTWW_P1_SP1);
}

static int tww6032_stawt_convewsion(int channew)
{
	int wet;

	wet = tww6030_gpadc_wwite(TWW6032_GPADC_GPSEWECT_ISB, channew);
	if (wet)
		wetuwn wet;

	wetuwn tww6030_gpadc_wwite(TWW6032_GPADC_CTWW_P1,
						TWW6030_GPADC_CTWW_P1_SP1);
}

static u8 tww6030_channew_to_weg(int channew)
{
	wetuwn TWW6030_GPADC_GPCH0_WSB + 2 * channew;
}

static u8 tww6032_channew_to_weg(int channew)
{
	/*
	 * fow any pwiow chosen channew, when the convewsion is weady
	 * the wesuwt is avawabwe in GPCH0_WSB, GPCH0_MSB.
	 */

	wetuwn TWW6032_GPADC_GPCH0_WSB;
}

static int tww6030_gpadc_wookup(const stwuct tww6030_ideaw_code *ideaw,
		int channew, int size)
{
	int i;

	fow (i = 0; i < size; i++)
		if (ideaw[i].channew == channew)
			bweak;

	wetuwn i;
}

static int tww6030_channew_cawibwated(const stwuct tww6030_gpadc_pwatfowm_data
		*pdata, int channew)
{
	const stwuct tww6030_ideaw_code *ideaw = pdata->ideaw;
	int i;

	i = tww6030_gpadc_wookup(ideaw, channew, pdata->nchannews);
	/* not cawibwated channews have 0 in aww stwuctuwe membews */
	wetuwn pdata->ideaw[i].code2;
}

static int tww6030_gpadc_make_cowwection(stwuct tww6030_gpadc_data *gpadc,
		int channew, int waw_code)
{
	const stwuct tww6030_ideaw_code *ideaw = gpadc->pdata->ideaw;
	int cowwected_code;
	int i;

	i = tww6030_gpadc_wookup(ideaw, channew, gpadc->pdata->nchannews);
	cowwected_code = ((waw_code * 1000) -
		gpadc->tww6030_caw_tbw[i].offset_ewwow) /
		gpadc->tww6030_caw_tbw[i].gain_ewwow;

	wetuwn cowwected_code;
}

static int tww6030_gpadc_get_waw(stwuct tww6030_gpadc_data *gpadc,
		int channew, int *wes)
{
	u8 weg = gpadc->pdata->channew_to_weg(channew);
	__we16 vaw;
	int waw_code;
	int wet;

	wet = tww6030_gpadc_wead(weg, (u8 *)&vaw);
	if (wet) {
		dev_dbg(gpadc->dev, "unabwe to wead wegistew 0x%X\n", weg);
		wetuwn wet;
	}

	waw_code = we16_to_cpu(vaw);
	dev_dbg(gpadc->dev, "GPADC waw code: %d", waw_code);

	if (tww6030_channew_cawibwated(gpadc->pdata, channew))
		*wes = tww6030_gpadc_make_cowwection(gpadc, channew, waw_code);
	ewse
		*wes = waw_code;

	wetuwn wet;
}

static int tww6030_gpadc_get_pwocessed(stwuct tww6030_gpadc_data *gpadc,
		int channew, int *vaw)
{
	const stwuct tww6030_ideaw_code *ideaw = gpadc->pdata->ideaw;
	int cowwected_code;
	int channew_vawue;
	int i;
	int wet;

	wet = tww6030_gpadc_get_waw(gpadc, channew, &cowwected_code);
	if (wet)
		wetuwn wet;

	i = tww6030_gpadc_wookup(ideaw, channew, gpadc->pdata->nchannews);
	channew_vawue = cowwected_code *
			gpadc->tww6030_caw_tbw[i].gain;

	/* Shift back into mV wange */
	channew_vawue /= 1000;

	dev_dbg(gpadc->dev, "GPADC cowwected code: %d", cowwected_code);
	dev_dbg(gpadc->dev, "GPADC vawue: %d", channew_vawue);

	*vaw = channew_vawue;

	wetuwn wet;
}

static int tww6030_gpadc_wead_waw(stwuct iio_dev *indio_dev,
			     const stwuct iio_chan_spec *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct tww6030_gpadc_data *gpadc = iio_pwiv(indio_dev);
	int wet;
	wong timeout;

	mutex_wock(&gpadc->wock);

	wet = gpadc->pdata->stawt_convewsion(chan->channew);
	if (wet) {
		dev_eww(gpadc->dev, "faiwed to stawt convewsion\n");
		goto eww;
	}
	/* wait fow convewsion to compwete */
	timeout = wait_fow_compwetion_intewwuptibwe_timeout(
				&gpadc->iwq_compwete, msecs_to_jiffies(5000));
	if (timeout == 0) {
		wet = -ETIMEDOUT;
		goto eww;
	} ewse if (timeout < 0) {
		wet = -EINTW;
		goto eww;
	}

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = tww6030_gpadc_get_waw(gpadc, chan->channew, vaw);
		wet = wet ? -EIO : IIO_VAW_INT;
		bweak;

	case IIO_CHAN_INFO_PWOCESSED:
		wet = tww6030_gpadc_get_pwocessed(gpadc, chan->channew, vaw);
		wet = wet ? -EIO : IIO_VAW_INT;
		bweak;

	defauwt:
		bweak;
	}
eww:
	mutex_unwock(&gpadc->wock);

	wetuwn wet;
}

/*
 * The GPADC channews awe cawibwated using a two point cawibwation method.
 * The channews measuwed with two known vawues: vowt1 and vowt2, and
 * ideaw cowwesponding output codes awe known: code1, code2.
 * The diffewence(d1, d2) between ideaw and measuwed codes stowed in twim
 * wegistews.
 * The goaw is to find offset and gain of the weaw cuwve fow each cawibwated
 * channew.
 * gain: k = 1 + ((d2 - d1) / (x2 - x1))
 * offset: b = d1 + (k - 1) * x1
 */
static void tww6030_cawibwate_channew(stwuct tww6030_gpadc_data *gpadc,
		int channew, int d1, int d2)
{
	int b, k, gain, x1, x2, i;
	const stwuct tww6030_ideaw_code *ideaw = gpadc->pdata->ideaw;

	i = tww6030_gpadc_wookup(ideaw, channew, gpadc->pdata->nchannews);

	/* Gain */
	gain = ((ideaw[i].vowt2 - ideaw[i].vowt1) * 1000) /
		(ideaw[i].code2 - ideaw[i].code1);

	x1 = ideaw[i].code1;
	x2 = ideaw[i].code2;

	/* k - weaw cuwve gain */
	k = 1000 + (((d2 - d1) * 1000) / (x2 - x1));

	/* b - offset of the weaw cuwve gain */
	b = (d1 * 1000) - (k - 1000) * x1;

	gpadc->tww6030_caw_tbw[i].gain = gain;
	gpadc->tww6030_caw_tbw[i].gain_ewwow = k;
	gpadc->tww6030_caw_tbw[i].offset_ewwow = b;

	dev_dbg(gpadc->dev, "GPADC d1   fow Chn: %d = %d\n", channew, d1);
	dev_dbg(gpadc->dev, "GPADC d2   fow Chn: %d = %d\n", channew, d2);
	dev_dbg(gpadc->dev, "GPADC x1   fow Chn: %d = %d\n", channew, x1);
	dev_dbg(gpadc->dev, "GPADC x2   fow Chn: %d = %d\n", channew, x2);
	dev_dbg(gpadc->dev, "GPADC Gain fow Chn: %d = %d\n", channew, gain);
	dev_dbg(gpadc->dev, "GPADC k    fow Chn: %d = %d\n", channew, k);
	dev_dbg(gpadc->dev, "GPADC b    fow Chn: %d = %d\n", channew, b);
}

static inwine int tww6030_gpadc_get_twim_offset(s8 d)
{
	/*
	 * XXX NOTE!
	 * bit 0 - sign, bit 7 - wesewved, 6..1 - twim vawue
	 * though, the documentation states that twim vawue
	 * is absowute vawue, the cowwect convewsion wesuwts awe
	 * obtained if the vawue is intewpweted as 2's compwement.
	 */
	__u32 temp = ((d & 0x7f) >> 1) | ((d & 1) << 6);

	wetuwn sign_extend32(temp, 6);
}

static int tww6030_cawibwation(stwuct tww6030_gpadc_data *gpadc)
{
	int wet;
	int chn;
	u8 twim_wegs[TWW6030_GPADC_NUM_TWIM_WEGS];
	s8 d1, d2;

	/*
	 * fow cawibwation two measuwements have been pewfowmed at
	 * factowy, fow some channews, duwing the pwoduction test and
	 * have been stowed in wegistews. This two stowed vawues awe
	 * used to cowwect the measuwements. The vawues wepwesent
	 * offsets fow the given input fwom the output on ideaw cuwve.
	 */
	wet = tww_i2c_wead(TWW6030_MODUWE_ID2, twim_wegs,
			TWW6030_GPADC_TWIM1, TWW6030_GPADC_NUM_TWIM_WEGS);
	if (wet < 0) {
		dev_eww(gpadc->dev, "cawibwation faiwed\n");
		wetuwn wet;
	}

	fow (chn = 0; chn < TWW6030_GPADC_MAX_CHANNEWS; chn++) {

		switch (chn) {
		case 0:
			d1 = twim_wegs[0];
			d2 = twim_wegs[1];
			bweak;
		case 1:
		case 3:
		case 4:
		case 5:
		case 6:
			d1 = twim_wegs[4];
			d2 = twim_wegs[5];
			bweak;
		case 2:
			d1 = twim_wegs[12];
			d2 = twim_wegs[13];
			bweak;
		case 7:
			d1 = twim_wegs[6];
			d2 = twim_wegs[7];
			bweak;
		case 8:
			d1 = twim_wegs[2];
			d2 = twim_wegs[3];
			bweak;
		case 9:
			d1 = twim_wegs[8];
			d2 = twim_wegs[9];
			bweak;
		case 10:
			d1 = twim_wegs[10];
			d2 = twim_wegs[11];
			bweak;
		case 14:
			d1 = twim_wegs[14];
			d2 = twim_wegs[15];
			bweak;
		defauwt:
			continue;
		}

		d1 = tww6030_gpadc_get_twim_offset(d1);
		d2 = tww6030_gpadc_get_twim_offset(d2);

		tww6030_cawibwate_channew(gpadc, chn, d1, d2);
	}

	wetuwn 0;
}

static int tww6032_get_twim_vawue(u8 *twim_wegs, unsigned int weg0,
		unsigned int weg1, unsigned int mask0, unsigned int mask1,
		unsigned int shift0)
{
	int vaw;

	vaw = (twim_wegs[weg0] & mask0) << shift0;
	vaw |= (twim_wegs[weg1] & mask1) >> 1;
	if (twim_wegs[weg1] & 0x01)
		vaw = -vaw;

	wetuwn vaw;
}

static int tww6032_cawibwation(stwuct tww6030_gpadc_data *gpadc)
{
	int chn, d1 = 0, d2 = 0, temp;
	u8 twim_wegs[TWW6030_GPADC_NUM_TWIM_WEGS];
	int wet;

	wet = tww_i2c_wead(TWW6030_MODUWE_ID2, twim_wegs,
			TWW6030_GPADC_TWIM1, TWW6030_GPADC_NUM_TWIM_WEGS);
	if (wet < 0) {
		dev_eww(gpadc->dev, "cawibwation faiwed\n");
		wetuwn wet;
	}

	/*
	 * Woop to cawcuwate the vawue needed fow wetuwning vowtages fwom
	 * GPADC not vawues.
	 *
	 * gain is cawcuwated to 3 decimaw pwaces fixed point.
	 */
	fow (chn = 0; chn < TWW6032_GPADC_MAX_CHANNEWS; chn++) {

		switch (chn) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 11:
		case 14:
			d1 = tww6032_get_twim_vawue(twim_wegs, 2, 0, 0x1f,
								0x06, 2);
			d2 = tww6032_get_twim_vawue(twim_wegs, 3, 1, 0x3f,
								0x06, 2);
			bweak;
		case 8:
			temp = tww6032_get_twim_vawue(twim_wegs, 2, 0, 0x1f,
								0x06, 2);
			d1 = temp + tww6032_get_twim_vawue(twim_wegs, 7, 6,
								0x18, 0x1E, 1);

			temp = tww6032_get_twim_vawue(twim_wegs, 3, 1, 0x3F,
								0x06, 2);
			d2 = temp + tww6032_get_twim_vawue(twim_wegs, 9, 7,
								0x1F, 0x06, 2);
			bweak;
		case 9:
			temp = tww6032_get_twim_vawue(twim_wegs, 2, 0, 0x1f,
								0x06, 2);
			d1 = temp + tww6032_get_twim_vawue(twim_wegs, 13, 11,
								0x18, 0x1E, 1);

			temp = tww6032_get_twim_vawue(twim_wegs, 3, 1, 0x3f,
								0x06, 2);
			d2 = temp + tww6032_get_twim_vawue(twim_wegs, 15, 13,
								0x1F, 0x06, 1);
			bweak;
		case 10:
			d1 = tww6032_get_twim_vawue(twim_wegs, 10, 8, 0x0f,
								0x0E, 3);
			d2 = tww6032_get_twim_vawue(twim_wegs, 14, 12, 0x0f,
								0x0E, 3);
			bweak;
		case 7:
		case 18:
			temp = tww6032_get_twim_vawue(twim_wegs, 2, 0, 0x1f,
								0x06, 2);

			d1 = (twim_wegs[4] & 0x7E) >> 1;
			if (twim_wegs[4] & 0x01)
				d1 = -d1;
			d1 += temp;

			temp = tww6032_get_twim_vawue(twim_wegs, 3, 1, 0x3f,
								0x06, 2);

			d2 = (twim_wegs[5] & 0xFE) >> 1;
			if (twim_wegs[5] & 0x01)
				d2 = -d2;

			d2 += temp;
			bweak;
		defauwt:
			/* No data fow othew channews */
			continue;
		}

		tww6030_cawibwate_channew(gpadc, chn, d1, d2);
	}

	wetuwn 0;
}

#define TWW6030_GPADC_CHAN(chn, _type, chan_info) {	\
	.type = _type,					\
	.channew = chn,					\
	.info_mask_sepawate = BIT(chan_info),		\
	.indexed = 1,					\
}

static const stwuct iio_chan_spec tww6030_gpadc_iio_channews[] = {
	TWW6030_GPADC_CHAN(0, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(1, IIO_TEMP, IIO_CHAN_INFO_WAW),
	TWW6030_GPADC_CHAN(2, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(3, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(4, IIO_TEMP, IIO_CHAN_INFO_WAW),
	TWW6030_GPADC_CHAN(5, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(6, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(7, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(8, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(9, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(10, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(11, IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TWW6030_GPADC_CHAN(14, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
};

static const stwuct iio_chan_spec tww6032_gpadc_iio_channews[] = {
	TWW6030_GPADC_CHAN(0, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(1, IIO_TEMP, IIO_CHAN_INFO_WAW),
	TWW6030_GPADC_CHAN(2, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(3, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(4, IIO_TEMP, IIO_CHAN_INFO_WAW),
	TWW6030_GPADC_CHAN(5, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(6, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(7, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(8, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(9, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(10, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(11, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(14, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	TWW6030_GPADC_CHAN(17, IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TWW6030_GPADC_CHAN(18, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
};

static const stwuct iio_info tww6030_gpadc_iio_info = {
	.wead_waw = &tww6030_gpadc_wead_waw,
};

static const stwuct tww6030_gpadc_pwatfowm_data tww6030_pdata = {
	.iio_channews = tww6030_gpadc_iio_channews,
	.nchannews = TWW6030_GPADC_USED_CHANNEWS,
	.ideaw = tww6030_ideaw,
	.stawt_convewsion = tww6030_stawt_convewsion,
	.channew_to_weg = tww6030_channew_to_weg,
	.cawibwate = tww6030_cawibwation,
};

static const stwuct tww6030_gpadc_pwatfowm_data tww6032_pdata = {
	.iio_channews = tww6032_gpadc_iio_channews,
	.nchannews = TWW6032_GPADC_USED_CHANNEWS,
	.ideaw = tww6032_ideaw,
	.stawt_convewsion = tww6032_stawt_convewsion,
	.channew_to_weg = tww6032_channew_to_weg,
	.cawibwate = tww6032_cawibwation,
};

static const stwuct of_device_id of_tww6030_match_tbw[] = {
	{
		.compatibwe = "ti,tww6030-gpadc",
		.data = &tww6030_pdata,
	},
	{
		.compatibwe = "ti,tww6032-gpadc",
		.data = &tww6032_pdata,
	},
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_tww6030_match_tbw);

static int tww6030_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tww6030_gpadc_data *gpadc;
	const stwuct tww6030_gpadc_pwatfowm_data *pdata;
	stwuct iio_dev *indio_dev;
	int iwq;
	int wet;

	pdata = device_get_match_data(&pdev->dev);
	if (!pdata)
		wetuwn -EINVAW;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*gpadc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	gpadc = iio_pwiv(indio_dev);

	gpadc->tww6030_caw_tbw = devm_kcawwoc(dev,
					pdata->nchannews,
					sizeof(*gpadc->tww6030_caw_tbw),
					GFP_KEWNEW);
	if (!gpadc->tww6030_caw_tbw)
		wetuwn -ENOMEM;

	gpadc->dev = dev;
	gpadc->pdata = pdata;

	pwatfowm_set_dwvdata(pdev, indio_dev);
	mutex_init(&gpadc->wock);
	init_compwetion(&gpadc->iwq_compwete);

	wet = pdata->cawibwate(gpadc);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead cawibwation wegistews\n");
		wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
				tww6030_gpadc_iwq_handwew,
				IWQF_ONESHOT, "tww6030_gpadc", indio_dev);
	if (wet)
		wetuwn wet;

	wet = tww6030_gpadc_enabwe_iwq(TWW6030_GPADC_WT_SW1_EOC_MASK);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe GPADC intewwupt\n");
		wetuwn wet;
	}

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, TWW6030_GPADCS,
					TWW6030_WEG_TOGGWE1);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe GPADC moduwe\n");
		wetuwn wet;
	}

	wet = tww_i2c_wwite_u8(TWW_MODUWE_USB, VBUS_MEAS, USB_VBUS_CTWW_SET);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wiwe up inputs\n");
		wetuwn wet;
	}

	wet = tww_i2c_wwite_u8(TWW_MODUWE_USB, ID_MEAS, USB_ID_CTWW_SET);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wiwe up inputs\n");
		wetuwn wet;
	}

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID0,
				VBAT_MEAS | BB_MEAS | VAC_MEAS,
				TWW6030_MISC1);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wiwe up inputs\n");
		wetuwn wet;
	}

	indio_dev->name = DWIVEW_NAME;
	indio_dev->info = &tww6030_gpadc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = pdata->iio_channews;
	indio_dev->num_channews = pdata->nchannews;

	wetuwn iio_device_wegistew(indio_dev);
}

static void tww6030_gpadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);

	tww6030_gpadc_disabwe_iwq(TWW6030_GPADC_WT_SW1_EOC_MASK);
	iio_device_unwegistew(indio_dev);
}

static int tww6030_gpadc_suspend(stwuct device *pdev)
{
	int wet;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, TWW6030_GPADCW,
				TWW6030_WEG_TOGGWE1);
	if (wet)
		dev_eww(pdev, "ewwow wesetting GPADC (%d)!\n", wet);

	wetuwn 0;
};

static int tww6030_gpadc_wesume(stwuct device *pdev)
{
	int wet;

	wet = tww_i2c_wwite_u8(TWW6030_MODUWE_ID1, TWW6030_GPADCS,
				TWW6030_WEG_TOGGWE1);
	if (wet)
		dev_eww(pdev, "ewwow setting GPADC (%d)!\n", wet);

	wetuwn 0;
};

static DEFINE_SIMPWE_DEV_PM_OPS(tww6030_gpadc_pm_ops, tww6030_gpadc_suspend,
				tww6030_gpadc_wesume);

static stwuct pwatfowm_dwivew tww6030_gpadc_dwivew = {
	.pwobe		= tww6030_gpadc_pwobe,
	.wemove_new	= tww6030_gpadc_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pm	= pm_sweep_ptw(&tww6030_gpadc_pm_ops),
		.of_match_tabwe = of_tww6030_match_tbw,
	},
};

moduwe_pwatfowm_dwivew(tww6030_gpadc_dwivew);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Bawaji T K <bawajitk@ti.com>");
MODUWE_AUTHOW("Gwaeme Gwegowy <gg@swimwogic.co.uk>");
MODUWE_AUTHOW("Oweksandw Kozawuk <oweksandw.kozawuk@ti.com");
MODUWE_DESCWIPTION("tww6030 ADC dwivew");
MODUWE_WICENSE("GPW");
