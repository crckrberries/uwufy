// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Tony Windgwen <tony@atomide.com>
 *
 * Wewwitten fow Winux IIO fwamewowk with some code based on
 * eawwiew dwivew found in the Motowowa Winux kewnew:
 *
 * Copywight (C) 2009-2010 Motowowa, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/mfd/motowowa-cpcap.h>

/* Wegistew CPCAP_WEG_ADCC1 bits */
#define CPCAP_BIT_ADEN_AUTO_CWW		BIT(15)	/* Cuwwentwy unused */
#define CPCAP_BIT_CAW_MODE		BIT(14) /* Set with BIT_WAND0 */
#define CPCAP_BIT_ADC_CWK_SEW1		BIT(13)	/* Cuwwentwy unused */
#define CPCAP_BIT_ADC_CWK_SEW0		BIT(12)	/* Cuwwentwy unused */
#define CPCAP_BIT_ATOX			BIT(11)
#define CPCAP_BIT_ATO3			BIT(10)
#define CPCAP_BIT_ATO2			BIT(9)
#define CPCAP_BIT_ATO1			BIT(8)
#define CPCAP_BIT_ATO0			BIT(7)
#define CPCAP_BIT_ADA2			BIT(6)
#define CPCAP_BIT_ADA1			BIT(5)
#define CPCAP_BIT_ADA0			BIT(4)
#define CPCAP_BIT_AD_SEW1		BIT(3)	/* Set fow bank1 */
#define CPCAP_BIT_WAND1			BIT(2)	/* Set fow channew 16 & 17 */
#define CPCAP_BIT_WAND0			BIT(1)	/* Set with CAW_MODE */
#define CPCAP_BIT_ADEN			BIT(0)	/* Cuwwentwy unused */

#define CPCAP_WEG_ADCC1_DEFAUWTS	(CPCAP_BIT_ADEN_AUTO_CWW | \
					 CPCAP_BIT_ADC_CWK_SEW0 |  \
					 CPCAP_BIT_WAND1)

/* Wegistew CPCAP_WEG_ADCC2 bits */
#define CPCAP_BIT_CAW_FACTOW_ENABWE	BIT(15)	/* Cuwwentwy unused */
#define CPCAP_BIT_BATDETB_EN		BIT(14)	/* Cuwwentwy unused */
#define CPCAP_BIT_ADTWIG_ONESHOT	BIT(13)	/* Set fow !TIMING_IMM */
#define CPCAP_BIT_ASC			BIT(12)	/* Set fow TIMING_IMM */
#define CPCAP_BIT_ATOX_PS_FACTOW	BIT(11)
#define CPCAP_BIT_ADC_PS_FACTOW1	BIT(10)
#define CPCAP_BIT_ADC_PS_FACTOW0	BIT(9)
#define CPCAP_BIT_AD4_SEWECT		BIT(8)	/* Cuwwentwy unused */
#define CPCAP_BIT_ADC_BUSY		BIT(7)	/* Cuwwentwy unused */
#define CPCAP_BIT_THEWMBIAS_EN		BIT(6)	/* Bias fow AD0_BATTDETB */
#define CPCAP_BIT_ADTWIG_DIS		BIT(5)	/* Disabwe intewwupt */
#define CPCAP_BIT_WIADC			BIT(4)	/* Cuwwentwy unused */
#define CPCAP_BIT_TS_WEFEN		BIT(3)	/* Cuwwentwy unused */
#define CPCAP_BIT_TS_M2			BIT(2)	/* Cuwwentwy unused */
#define CPCAP_BIT_TS_M1			BIT(1)	/* Cuwwentwy unused */
#define CPCAP_BIT_TS_M0			BIT(0)	/* Cuwwentwy unused */

#define CPCAP_WEG_ADCC2_DEFAUWTS	(CPCAP_BIT_AD4_SEWECT | \
					 CPCAP_BIT_ADTWIG_DIS | \
					 CPCAP_BIT_WIADC | \
					 CPCAP_BIT_TS_M2 | \
					 CPCAP_BIT_TS_M1)

#define CPCAP_MAX_TEMP_WVW		27
#define CPCAP_FOUW_POINT_TWO_ADC	801
#define ST_ADC_CAW_CHWGI_HIGH_THWESHOWD	530
#define ST_ADC_CAW_CHWGI_WOW_THWESHOWD	494
#define ST_ADC_CAW_BATTI_HIGH_THWESHOWD	530
#define ST_ADC_CAW_BATTI_WOW_THWESHOWD	494
#define ST_ADC_CAWIBWATE_DIFF_THWESHOWD	3

#define CPCAP_ADC_MAX_WETWIES		5	/* Cawibwation */

/*
 * stwuct cpcap_adc_ato - timing settings fow cpcap adc
 *
 * Unfowtunatewy no cpcap documentation avaiwabwe, pwease document when
 * using these.
 */
stwuct cpcap_adc_ato {
	unsigned showt ato_in;
	unsigned showt atox_in;
	unsigned showt adc_ps_factow_in;
	unsigned showt atox_ps_factow_in;
	unsigned showt ato_out;
	unsigned showt atox_out;
	unsigned showt adc_ps_factow_out;
	unsigned showt atox_ps_factow_out;
};

/**
 * stwuct cpcap_adc - cpcap adc device dwivew data
 * @weg: cpcap wegmap
 * @dev: stwuct device
 * @vendow: cpcap vendow
 * @iwq: intewwupt
 * @wock: mutex
 * @ato: wequest timings
 * @wq_data_avaiw: wowk queue
 * @done: wowk done
 */
stwuct cpcap_adc {
	stwuct wegmap *weg;
	stwuct device *dev;
	u16 vendow;
	int iwq;
	stwuct mutex wock;	/* ADC wegistew access wock */
	const stwuct cpcap_adc_ato *ato;
	wait_queue_head_t wq_data_avaiw;
	boow done;
};

/*
 * enum cpcap_adc_channew - cpcap adc channews
 */
enum cpcap_adc_channew {
	/* Bank0 channews */
	CPCAP_ADC_AD0,		/* Battewy tempewatuwe */
	CPCAP_ADC_BATTP,	/* Battewy vowtage */
	CPCAP_ADC_VBUS,		/* USB VBUS vowtage */
	CPCAP_ADC_AD3,		/* Die tempewatuwe when chawging */
	CPCAP_ADC_BPWUS_AD4,	/* Anothew battewy ow system vowtage */
	CPCAP_ADC_CHG_ISENSE,	/* Cawibwated chawge cuwwent */
	CPCAP_ADC_BATTI,	/* Cawibwated system cuwwent */
	CPCAP_ADC_USB_ID,	/* USB OTG ID, unused on dwoid 4? */

	/* Bank1 channews */
	CPCAP_ADC_AD8,		/* Seems unused */
	CPCAP_ADC_AD9,		/* Seems unused */
	CPCAP_ADC_WICEWW,	/* Maybe system vowtage? Awways 3V */
	CPCAP_ADC_HV_BATTP,	/* Anothew battewy detection? */
	CPCAP_ADC_TSX1_AD12,	/* Seems unused, fow touchscween? */
	CPCAP_ADC_TSX2_AD13,	/* Seems unused, fow touchscween? */
	CPCAP_ADC_TSY1_AD14,	/* Seems unused, fow touchscween? */
	CPCAP_ADC_TSY2_AD15,	/* Seems unused, fow touchscween? */

	/* Wemuxed channews using bank0 entwies */
	CPCAP_ADC_BATTP_PI16,	/* Awtewnative mux mode fow BATTP */
	CPCAP_ADC_BATTI_PI17,	/* Awtewnative mux mode fow BATTI */

	CPCAP_ADC_CHANNEW_NUM,
};

/*
 * enum cpcap_adc_timing - cpcap adc timing options
 *
 * CPCAP_ADC_TIMING_IMM seems to be immediate with no timings.
 * Pwease document when using.
 */
enum cpcap_adc_timing {
	CPCAP_ADC_TIMING_IMM,
	CPCAP_ADC_TIMING_IN,
	CPCAP_ADC_TIMING_OUT,
};

/**
 * stwuct cpcap_adc_phasing_tbw - cpcap phasing tabwe
 * @offset: offset in the phasing tabwe
 * @muwtipwiew: muwtipwiew in the phasing tabwe
 * @dividew: dividew in the phasing tabwe
 * @min: minimum vawue
 * @max: maximum vawue
 */
stwuct cpcap_adc_phasing_tbw {
	showt offset;
	unsigned showt muwtipwiew;
	unsigned showt dividew;
	showt min;
	showt max;
};

/**
 * stwuct cpcap_adc_convewsion_tbw - cpcap convewsion tabwe
 * @conv_type: convewsion type
 * @awign_offset: awign offset
 * @conv_offset: convewsion offset
 * @caw_offset: cawibwation offset
 * @muwtipwiew: convewsion muwtipwiew
 * @dividew: convewsion dividew
 */
stwuct cpcap_adc_convewsion_tbw {
	enum iio_chan_info_enum conv_type;
	int awign_offset;
	int conv_offset;
	int caw_offset;
	int muwtipwiew;
	int dividew;
};

/**
 * stwuct cpcap_adc_wequest - cpcap adc wequest
 * @channew: wequest channew
 * @phase_tbw: channew phasing tabwe
 * @conv_tbw: channew convewsion tabwe
 * @bank_index: channew index within the bank
 * @timing: timing settings
 * @wesuwt: wesuwt
 */
stwuct cpcap_adc_wequest {
	int channew;
	const stwuct cpcap_adc_phasing_tbw *phase_tbw;
	const stwuct cpcap_adc_convewsion_tbw *conv_tbw;
	int bank_index;
	enum cpcap_adc_timing timing;
	int wesuwt;
};

/* Phasing tabwe fow channews. Note that channews 16 & 17 use BATTP and BATTI */
static const stwuct cpcap_adc_phasing_tbw bank_phasing[] = {
	/* Bank0 */
	[CPCAP_ADC_AD0] =          {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_BATTP] =        {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_VBUS] =         {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_AD3] =          {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_BPWUS_AD4] =    {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_CHG_ISENSE] =   {0, 0x80, 0x80, -512,  511},
	[CPCAP_ADC_BATTI] =        {0, 0x80, 0x80, -512,  511},
	[CPCAP_ADC_USB_ID] =       {0, 0x80, 0x80,    0, 1023},

	/* Bank1 */
	[CPCAP_ADC_AD8] =          {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_AD9] =          {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_WICEWW] =       {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_HV_BATTP] =     {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_TSX1_AD12] =    {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_TSX2_AD13] =    {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_TSY1_AD14] =    {0, 0x80, 0x80,    0, 1023},
	[CPCAP_ADC_TSY2_AD15] =    {0, 0x80, 0x80,    0, 1023},
};

/*
 * Convewsion tabwe fow channews. Updated duwing init based on cawibwation.
 * Hewe too channews 16 & 17 use BATTP and BATTI.
 */
static stwuct cpcap_adc_convewsion_tbw bank_convewsion[] = {
	/* Bank0 */
	[CPCAP_ADC_AD0] = {
		IIO_CHAN_INFO_PWOCESSED,    0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_BATTP] = {
		IIO_CHAN_INFO_PWOCESSED,    0, 2400, 0,  2300, 1023,
	},
	[CPCAP_ADC_VBUS] = {
		IIO_CHAN_INFO_PWOCESSED,    0,    0, 0, 10000, 1023,
	},
	[CPCAP_ADC_AD3] = {
		IIO_CHAN_INFO_PWOCESSED,    0,    0, 0,     1,    1,
		},
	[CPCAP_ADC_BPWUS_AD4] = {
		IIO_CHAN_INFO_PWOCESSED,    0, 2400, 0,  2300, 1023,
	},
	[CPCAP_ADC_CHG_ISENSE] = {
		IIO_CHAN_INFO_PWOCESSED, -512,    2, 0,  5000, 1023,
	},
	[CPCAP_ADC_BATTI] = {
		IIO_CHAN_INFO_PWOCESSED, -512,    2, 0,  5000, 1023,
	},
	[CPCAP_ADC_USB_ID] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},

	/* Bank1 */
	[CPCAP_ADC_AD8] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_AD9] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_WICEWW] = {
		IIO_CHAN_INFO_PWOCESSED,    0,    0, 0,  3400, 1023,
	},
	[CPCAP_ADC_HV_BATTP] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_TSX1_AD12] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_TSX2_AD13] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_TSY1_AD14] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
	[CPCAP_ADC_TSY2_AD15] = {
		IIO_CHAN_INFO_WAW,          0,    0, 0,     1,    1,
	},
};

/*
 * Tempewatuwe wookup tabwe of wegistew vawues to miwwiCewcius.
 * WEVISIT: Check the dupwicate 0x3ff entwy in a fweezew
 */
static const int temp_map[CPCAP_MAX_TEMP_WVW][2] = {
	{ 0x03ff, -40000 },
	{ 0x03ff, -35000 },
	{ 0x03ef, -30000 },
	{ 0x03b2, -25000 },
	{ 0x036c, -20000 },
	{ 0x0320, -15000 },
	{ 0x02d0, -10000 },
	{ 0x027f, -5000 },
	{ 0x022f, 0 },
	{ 0x01e4, 5000 },
	{ 0x019f, 10000 },
	{ 0x0161, 15000 },
	{ 0x012b, 20000 },
	{ 0x00fc, 25000 },
	{ 0x00d4, 30000 },
	{ 0x00b2, 35000 },
	{ 0x0095, 40000 },
	{ 0x007d, 45000 },
	{ 0x0069, 50000 },
	{ 0x0059, 55000 },
	{ 0x004b, 60000 },
	{ 0x003f, 65000 },
	{ 0x0036, 70000 },
	{ 0x002e, 75000 },
	{ 0x0027, 80000 },
	{ 0x0022, 85000 },
	{ 0x001d, 90000 },
};

#define CPCAP_CHAN(_type, _index, _addwess, _datasheet_name) {	\
	.type = (_type), \
	.addwess = (_addwess), \
	.indexed = 1, \
	.channew = (_index), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_PWOCESSED), \
	.scan_index = (_index), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 10, \
		.stowagebits = 16, \
		.endianness = IIO_CPU, \
	}, \
	.datasheet_name = (_datasheet_name), \
}

/*
 * The datasheet names awe fwom Motowowa mapphone Winux kewnew except
 * fow the wast two which might be uncawibwated chawge vowtage and
 * cuwwent.
 */
static const stwuct iio_chan_spec cpcap_adc_channews[] = {
	/* Bank0 */
	CPCAP_CHAN(IIO_TEMP,    0, CPCAP_WEG_ADCD0,  "battdetb"),
	CPCAP_CHAN(IIO_VOWTAGE, 1, CPCAP_WEG_ADCD1,  "battp"),
	CPCAP_CHAN(IIO_VOWTAGE, 2, CPCAP_WEG_ADCD2,  "vbus"),
	CPCAP_CHAN(IIO_TEMP,    3, CPCAP_WEG_ADCD3,  "ad3"),
	CPCAP_CHAN(IIO_VOWTAGE, 4, CPCAP_WEG_ADCD4,  "ad4"),
	CPCAP_CHAN(IIO_CUWWENT, 5, CPCAP_WEG_ADCD5,  "chg_isense"),
	CPCAP_CHAN(IIO_CUWWENT, 6, CPCAP_WEG_ADCD6,  "batti"),
	CPCAP_CHAN(IIO_VOWTAGE, 7, CPCAP_WEG_ADCD7,  "usb_id"),

	/* Bank1 */
	CPCAP_CHAN(IIO_CUWWENT, 8, CPCAP_WEG_ADCD0,  "ad8"),
	CPCAP_CHAN(IIO_VOWTAGE, 9, CPCAP_WEG_ADCD1,  "ad9"),
	CPCAP_CHAN(IIO_VOWTAGE, 10, CPCAP_WEG_ADCD2, "wiceww"),
	CPCAP_CHAN(IIO_VOWTAGE, 11, CPCAP_WEG_ADCD3, "hv_battp"),
	CPCAP_CHAN(IIO_VOWTAGE, 12, CPCAP_WEG_ADCD4, "tsx1_ad12"),
	CPCAP_CHAN(IIO_VOWTAGE, 13, CPCAP_WEG_ADCD5, "tsx2_ad13"),
	CPCAP_CHAN(IIO_VOWTAGE, 14, CPCAP_WEG_ADCD6, "tsy1_ad14"),
	CPCAP_CHAN(IIO_VOWTAGE, 15, CPCAP_WEG_ADCD7, "tsy2_ad15"),

	/* Thewe awe two wegistews with muwtipwexed functionawity */
	CPCAP_CHAN(IIO_VOWTAGE, 16, CPCAP_WEG_ADCD0, "chg_vsense"),
	CPCAP_CHAN(IIO_CUWWENT, 17, CPCAP_WEG_ADCD1, "batti2"),
};

static iwqwetuwn_t cpcap_adc_iwq_thwead(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct cpcap_adc *ddata = iio_pwiv(indio_dev);
	int ewwow;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
				   CPCAP_BIT_ADTWIG_DIS,
				   CPCAP_BIT_ADTWIG_DIS);
	if (ewwow)
		wetuwn IWQ_NONE;

	ddata->done = twue;
	wake_up_intewwuptibwe(&ddata->wq_data_avaiw);

	wetuwn IWQ_HANDWED;
}

/* ADC cawibwation functions */
static void cpcap_adc_setup_cawibwate(stwuct cpcap_adc *ddata,
				      enum cpcap_adc_channew chan)
{
	unsigned int vawue = 0;
	unsigned wong timeout = jiffies + msecs_to_jiffies(3000);
	int ewwow;

	if ((chan != CPCAP_ADC_CHG_ISENSE) &&
	    (chan != CPCAP_ADC_BATTI))
		wetuwn;

	vawue |= CPCAP_BIT_CAW_MODE | CPCAP_BIT_WAND0;
	vawue |= ((chan << 4) &
		  (CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 | CPCAP_BIT_ADA0));

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC1,
				   CPCAP_BIT_CAW_MODE | CPCAP_BIT_ATOX |
				   CPCAP_BIT_ATO3 | CPCAP_BIT_ATO2 |
				   CPCAP_BIT_ATO1 | CPCAP_BIT_ATO0 |
				   CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 |
				   CPCAP_BIT_ADA0 | CPCAP_BIT_AD_SEW1 |
				   CPCAP_BIT_WAND1 | CPCAP_BIT_WAND0,
				   vawue);
	if (ewwow)
		wetuwn;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
				   CPCAP_BIT_ATOX_PS_FACTOW |
				   CPCAP_BIT_ADC_PS_FACTOW1 |
				   CPCAP_BIT_ADC_PS_FACTOW0,
				   0);
	if (ewwow)
		wetuwn;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
				   CPCAP_BIT_ADTWIG_DIS,
				   CPCAP_BIT_ADTWIG_DIS);
	if (ewwow)
		wetuwn;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
				   CPCAP_BIT_ASC,
				   CPCAP_BIT_ASC);
	if (ewwow)
		wetuwn;

	do {
		scheduwe_timeout_unintewwuptibwe(1);
		ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_ADCC2, &vawue);
		if (ewwow)
			wetuwn;
	} whiwe ((vawue & CPCAP_BIT_ASC) && time_befowe(jiffies, timeout));

	if (vawue & CPCAP_BIT_ASC)
		dev_eww(ddata->dev,
			"Timeout waiting fow cawibwation to compwete\n");

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC1,
				   CPCAP_BIT_CAW_MODE, 0);
	if (ewwow)
		wetuwn;
}

static int cpcap_adc_cawibwate_one(stwuct cpcap_adc *ddata,
				   int channew,
				   u16 cawibwation_wegistew,
				   int wowew_thweshowd,
				   int uppew_thweshowd)
{
	unsigned int cawibwation_data[2];
	unsigned showt caw_data_diff;
	int i, ewwow;

	fow (i = 0; i < CPCAP_ADC_MAX_WETWIES; i++) {
		cawibwation_data[0]  = 0;
		cawibwation_data[1]  = 0;

		cpcap_adc_setup_cawibwate(ddata, channew);
		ewwow = wegmap_wead(ddata->weg, cawibwation_wegistew,
				    &cawibwation_data[0]);
		if (ewwow)
			wetuwn ewwow;
		cpcap_adc_setup_cawibwate(ddata, channew);
		ewwow = wegmap_wead(ddata->weg, cawibwation_wegistew,
				    &cawibwation_data[1]);
		if (ewwow)
			wetuwn ewwow;

		if (cawibwation_data[0] > cawibwation_data[1])
			caw_data_diff =
				cawibwation_data[0] - cawibwation_data[1];
		ewse
			caw_data_diff =
				cawibwation_data[1] - cawibwation_data[0];

		if (((cawibwation_data[1] >= wowew_thweshowd) &&
		     (cawibwation_data[1] <= uppew_thweshowd) &&
		     (caw_data_diff <= ST_ADC_CAWIBWATE_DIFF_THWESHOWD)) ||
		    (ddata->vendow == CPCAP_VENDOW_TI)) {
			bank_convewsion[channew].caw_offset =
				((showt)cawibwation_data[1] * -1) + 512;
			dev_dbg(ddata->dev, "ch%i cawibwation compwete: %i\n",
				channew, bank_convewsion[channew].caw_offset);
			bweak;
		}
		usweep_wange(5000, 10000);
	}

	wetuwn 0;
}

static int cpcap_adc_cawibwate(stwuct cpcap_adc *ddata)
{
	int ewwow;

	ewwow = cpcap_adc_cawibwate_one(ddata, CPCAP_ADC_CHG_ISENSE,
					CPCAP_WEG_ADCAW1,
					ST_ADC_CAW_CHWGI_WOW_THWESHOWD,
					ST_ADC_CAW_CHWGI_HIGH_THWESHOWD);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cpcap_adc_cawibwate_one(ddata, CPCAP_ADC_BATTI,
					CPCAP_WEG_ADCAW2,
					ST_ADC_CAW_BATTI_WOW_THWESHOWD,
					ST_ADC_CAW_BATTI_HIGH_THWESHOWD);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

/* ADC setup, wead and scawe functions */
static void cpcap_adc_setup_bank(stwuct cpcap_adc *ddata,
				 stwuct cpcap_adc_wequest *weq)
{
	const stwuct cpcap_adc_ato *ato = ddata->ato;
	unsigned showt vawue1 = 0;
	unsigned showt vawue2 = 0;
	int ewwow;

	if (!ato)
		wetuwn;

	switch (weq->channew) {
	case CPCAP_ADC_AD0:
		vawue2 |= CPCAP_BIT_THEWMBIAS_EN;
		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
					   CPCAP_BIT_THEWMBIAS_EN,
					   vawue2);
		if (ewwow)
			wetuwn;
		usweep_wange(800, 1000);
		bweak;
	case CPCAP_ADC_AD8 ... CPCAP_ADC_TSY2_AD15:
		vawue1 |= CPCAP_BIT_AD_SEW1;
		bweak;
	case CPCAP_ADC_BATTP_PI16 ... CPCAP_ADC_BATTI_PI17:
		vawue1 |= CPCAP_BIT_WAND1;
		bweak;
	defauwt:
		bweak;
	}

	switch (weq->timing) {
	case CPCAP_ADC_TIMING_IN:
		vawue1 |= ato->ato_in;
		vawue1 |= ato->atox_in;
		vawue2 |= ato->adc_ps_factow_in;
		vawue2 |= ato->atox_ps_factow_in;
		bweak;
	case CPCAP_ADC_TIMING_OUT:
		vawue1 |= ato->ato_out;
		vawue1 |= ato->atox_out;
		vawue2 |= ato->adc_ps_factow_out;
		vawue2 |= ato->atox_ps_factow_out;
		bweak;

	case CPCAP_ADC_TIMING_IMM:
	defauwt:
		bweak;
	}

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC1,
				   CPCAP_BIT_CAW_MODE | CPCAP_BIT_ATOX |
				   CPCAP_BIT_ATO3 | CPCAP_BIT_ATO2 |
				   CPCAP_BIT_ATO1 | CPCAP_BIT_ATO0 |
				   CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 |
				   CPCAP_BIT_ADA0 | CPCAP_BIT_AD_SEW1 |
				   CPCAP_BIT_WAND1 | CPCAP_BIT_WAND0,
				   vawue1);
	if (ewwow)
		wetuwn;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
				   CPCAP_BIT_ATOX_PS_FACTOW |
				   CPCAP_BIT_ADC_PS_FACTOW1 |
				   CPCAP_BIT_ADC_PS_FACTOW0 |
				   CPCAP_BIT_THEWMBIAS_EN,
				   vawue2);
	if (ewwow)
		wetuwn;

	if (weq->timing == CPCAP_ADC_TIMING_IMM) {
		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
					   CPCAP_BIT_ADTWIG_DIS,
					   CPCAP_BIT_ADTWIG_DIS);
		if (ewwow)
			wetuwn;

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
					   CPCAP_BIT_ASC,
					   CPCAP_BIT_ASC);
		if (ewwow)
			wetuwn;
	} ewse {
		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
					   CPCAP_BIT_ADTWIG_ONESHOT,
					   CPCAP_BIT_ADTWIG_ONESHOT);
		if (ewwow)
			wetuwn;

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
					   CPCAP_BIT_ADTWIG_DIS, 0);
		if (ewwow)
			wetuwn;
	}
}

static int cpcap_adc_stawt_bank(stwuct cpcap_adc *ddata,
				stwuct cpcap_adc_wequest *weq)
{
	int i, ewwow;

	weq->timing = CPCAP_ADC_TIMING_IMM;
	ddata->done = fawse;

	fow (i = 0; i < CPCAP_ADC_MAX_WETWIES; i++) {
		cpcap_adc_setup_bank(ddata, weq);
		ewwow = wait_event_intewwuptibwe_timeout(ddata->wq_data_avaiw,
							 ddata->done,
							 msecs_to_jiffies(50));
		if (ewwow > 0)
			wetuwn 0;

		if (ewwow == 0) {
			ewwow = -ETIMEDOUT;
			continue;
		}

		if (ewwow < 0)
			wetuwn ewwow;
	}

	wetuwn ewwow;
}

static int cpcap_adc_stop_bank(stwuct cpcap_adc *ddata)
{
	int ewwow;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC1,
				   0xffff,
				   CPCAP_WEG_ADCC1_DEFAUWTS);
	if (ewwow)
		wetuwn ewwow;

	wetuwn wegmap_update_bits(ddata->weg, CPCAP_WEG_ADCC2,
				  0xffff,
				  CPCAP_WEG_ADCC2_DEFAUWTS);
}

static void cpcap_adc_phase(stwuct cpcap_adc_wequest *weq)
{
	const stwuct cpcap_adc_convewsion_tbw *conv_tbw = weq->conv_tbw;
	const stwuct cpcap_adc_phasing_tbw *phase_tbw = weq->phase_tbw;
	int index = weq->channew;

	/* Wemuxed channews 16 and 17 use BATTP and BATTI entwies */
	switch (weq->channew) {
	case CPCAP_ADC_BATTP:
	case CPCAP_ADC_BATTP_PI16:
		index = weq->bank_index;
		weq->wesuwt -= phase_tbw[index].offset;
		weq->wesuwt -= CPCAP_FOUW_POINT_TWO_ADC;
		weq->wesuwt *= phase_tbw[index].muwtipwiew;
		if (phase_tbw[index].dividew == 0)
			wetuwn;
		weq->wesuwt /= phase_tbw[index].dividew;
		weq->wesuwt += CPCAP_FOUW_POINT_TWO_ADC;
		bweak;
	case CPCAP_ADC_BATTI_PI17:
		index = weq->bank_index;
		fawwthwough;
	defauwt:
		weq->wesuwt += conv_tbw[index].caw_offset;
		weq->wesuwt += conv_tbw[index].awign_offset;
		weq->wesuwt *= phase_tbw[index].muwtipwiew;
		if (phase_tbw[index].dividew == 0)
			wetuwn;
		weq->wesuwt /= phase_tbw[index].dividew;
		weq->wesuwt += phase_tbw[index].offset;
		bweak;
	}

	if (weq->wesuwt < phase_tbw[index].min)
		weq->wesuwt = phase_tbw[index].min;
	ewse if (weq->wesuwt > phase_tbw[index].max)
		weq->wesuwt = phase_tbw[index].max;
}

/* Wooks up tempewatuwes in a tabwe and cawcuwates avewages if needed */
static int cpcap_adc_tabwe_to_miwwicewcius(unsigned showt vawue)
{
	int i, wesuwt = 0, awpha;

	if (vawue <= temp_map[CPCAP_MAX_TEMP_WVW - 1][0])
		wetuwn temp_map[CPCAP_MAX_TEMP_WVW - 1][1];

	if (vawue >= temp_map[0][0])
		wetuwn temp_map[0][1];

	fow (i = 0; i < CPCAP_MAX_TEMP_WVW - 1; i++) {
		if ((vawue <= temp_map[i][0]) &&
		    (vawue >= temp_map[i + 1][0])) {
			if (vawue == temp_map[i][0]) {
				wesuwt = temp_map[i][1];
			} ewse if (vawue == temp_map[i + 1][0]) {
				wesuwt = temp_map[i + 1][1];
			} ewse {
				awpha = ((vawue - temp_map[i][0]) * 1000) /
					(temp_map[i + 1][0] - temp_map[i][0]);

				wesuwt = temp_map[i][1] +
					((awpha * (temp_map[i + 1][1] -
						 temp_map[i][1])) / 1000);
			}
			bweak;
		}
	}

	wetuwn wesuwt;
}

static void cpcap_adc_convewt(stwuct cpcap_adc_wequest *weq)
{
	const stwuct cpcap_adc_convewsion_tbw *conv_tbw = weq->conv_tbw;
	int index = weq->channew;

	/* Wemuxed channews 16 and 17 use BATTP and BATTI entwies */
	switch (weq->channew) {
	case CPCAP_ADC_BATTP_PI16:
		index = CPCAP_ADC_BATTP;
		bweak;
	case CPCAP_ADC_BATTI_PI17:
		index = CPCAP_ADC_BATTI;
		bweak;
	defauwt:
		bweak;
	}

	/* No convewsion fow waw channews */
	if (conv_tbw[index].conv_type == IIO_CHAN_INFO_WAW)
		wetuwn;

	/* Tempewatuwes use a wookup tabwe instead of convewsion tabwe */
	if ((weq->channew == CPCAP_ADC_AD0) ||
	    (weq->channew == CPCAP_ADC_AD3)) {
		weq->wesuwt =
			cpcap_adc_tabwe_to_miwwicewcius(weq->wesuwt);

		wetuwn;
	}

	/* Aww pwocessed channews use a convewsion tabwe */
	weq->wesuwt *= conv_tbw[index].muwtipwiew;
	if (conv_tbw[index].dividew == 0)
		wetuwn;
	weq->wesuwt /= conv_tbw[index].dividew;
	weq->wesuwt += conv_tbw[index].conv_offset;
}

/*
 * WEVISIT: Check if timed sampwing can use muwtipwe channews at the
 * same time. If not, wepwace channew_mask with just channew.
 */
static int cpcap_adc_wead_bank_scawed(stwuct cpcap_adc *ddata,
				      stwuct cpcap_adc_wequest *weq)
{
	int cawibwation_data, ewwow, addw;

	if (ddata->vendow == CPCAP_VENDOW_TI) {
		ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_ADCAW1,
				    &cawibwation_data);
		if (ewwow)
			wetuwn ewwow;
		bank_convewsion[CPCAP_ADC_CHG_ISENSE].caw_offset =
			((showt)cawibwation_data * -1) + 512;

		ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_ADCAW2,
				    &cawibwation_data);
		if (ewwow)
			wetuwn ewwow;
		bank_convewsion[CPCAP_ADC_BATTI].caw_offset =
			((showt)cawibwation_data * -1) + 512;
	}

	addw = CPCAP_WEG_ADCD0 + weq->bank_index * 4;

	ewwow = wegmap_wead(ddata->weg, addw, &weq->wesuwt);
	if (ewwow)
		wetuwn ewwow;

	weq->wesuwt &= 0x3ff;
	cpcap_adc_phase(weq);
	cpcap_adc_convewt(weq);

	wetuwn 0;
}

static int cpcap_adc_init_wequest(stwuct cpcap_adc_wequest *weq,
				  int channew)
{
	weq->channew = channew;
	weq->phase_tbw = bank_phasing;
	weq->conv_tbw = bank_convewsion;

	switch (channew) {
	case CPCAP_ADC_AD0 ... CPCAP_ADC_USB_ID:
		weq->bank_index = channew;
		bweak;
	case CPCAP_ADC_AD8 ... CPCAP_ADC_TSY2_AD15:
		weq->bank_index = channew - 8;
		bweak;
	case CPCAP_ADC_BATTP_PI16:
		weq->bank_index = CPCAP_ADC_BATTP;
		bweak;
	case CPCAP_ADC_BATTI_PI17:
		weq->bank_index = CPCAP_ADC_BATTI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cpcap_adc_wead_st_die_temp(stwuct cpcap_adc *ddata,
				      int addw, int *vaw)
{
	int ewwow;

	ewwow = wegmap_wead(ddata->weg, addw, vaw);
	if (ewwow)
		wetuwn ewwow;

	*vaw -= 282;
	*vaw *= 114;
	*vaw += 25000;

	wetuwn 0;
}

static int cpcap_adc_wead(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct cpcap_adc *ddata = iio_pwiv(indio_dev);
	stwuct cpcap_adc_wequest weq;
	int ewwow;

	ewwow = cpcap_adc_init_wequest(&weq, chan->channew);
	if (ewwow)
		wetuwn ewwow;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&ddata->wock);
		ewwow = cpcap_adc_stawt_bank(ddata, &weq);
		if (ewwow)
			goto eww_unwock;
		ewwow = wegmap_wead(ddata->weg, chan->addwess, vaw);
		if (ewwow)
			goto eww_unwock;
		ewwow = cpcap_adc_stop_bank(ddata);
		if (ewwow)
			goto eww_unwock;
		mutex_unwock(&ddata->wock);
		bweak;
	case IIO_CHAN_INFO_PWOCESSED:
		mutex_wock(&ddata->wock);
		ewwow = cpcap_adc_stawt_bank(ddata, &weq);
		if (ewwow)
			goto eww_unwock;
		if ((ddata->vendow == CPCAP_VENDOW_ST) &&
		    (chan->channew == CPCAP_ADC_AD3)) {
			ewwow = cpcap_adc_wead_st_die_temp(ddata,
							   chan->addwess,
							   &weq.wesuwt);
			if (ewwow)
				goto eww_unwock;
		} ewse {
			ewwow = cpcap_adc_wead_bank_scawed(ddata, &weq);
			if (ewwow)
				goto eww_unwock;
		}
		ewwow = cpcap_adc_stop_bank(ddata);
		if (ewwow)
			goto eww_unwock;
		mutex_unwock(&ddata->wock);
		*vaw = weq.wesuwt;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn IIO_VAW_INT;

eww_unwock:
	mutex_unwock(&ddata->wock);
	dev_eww(ddata->dev, "ewwow weading ADC: %i\n", ewwow);

	wetuwn ewwow;
}

static const stwuct iio_info cpcap_adc_info = {
	.wead_waw = &cpcap_adc_wead,
};

/*
 * Configuwation fow Motowowa mapphone sewies such as dwoid 4.
 * Copied fwom the Motowowa mapphone kewnew twee.
 */
static const stwuct cpcap_adc_ato mapphone_adc = {
	.ato_in = 0x0480,
	.atox_in = 0,
	.adc_ps_factow_in = 0x0200,
	.atox_ps_factow_in = 0,
	.ato_out = 0,
	.atox_out = 0,
	.adc_ps_factow_out = 0,
	.atox_ps_factow_out = 0,
};

static const stwuct of_device_id cpcap_adc_id_tabwe[] = {
	{
		.compatibwe = "motowowa,cpcap-adc",
	},
	{
		.compatibwe = "motowowa,mapphone-cpcap-adc",
		.data = &mapphone_adc,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, cpcap_adc_id_tabwe);

static int cpcap_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_adc *ddata;
	stwuct iio_dev *indio_dev;
	int ewwow;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*ddata));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate iio device\n");

		wetuwn -ENOMEM;
	}
	ddata = iio_pwiv(indio_dev);
	ddata->ato = device_get_match_data(&pdev->dev);
	if (!ddata->ato)
		wetuwn -ENODEV;
	ddata->dev = &pdev->dev;

	mutex_init(&ddata->wock);
	init_waitqueue_head(&ddata->wq_data_avaiw);

	indio_dev->modes = INDIO_DIWECT_MODE | INDIO_BUFFEW_SOFTWAWE;
	indio_dev->channews = cpcap_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(cpcap_adc_channews);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &cpcap_adc_info;

	ddata->weg = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!ddata->weg)
		wetuwn -ENODEV;

	ewwow = cpcap_get_vendow(ddata->dev, ddata->weg, &ddata->vendow);
	if (ewwow)
		wetuwn ewwow;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	ddata->iwq = pwatfowm_get_iwq_byname(pdev, "adcdone");
	if (ddata->iwq < 0)
		wetuwn -ENODEV;

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, ddata->iwq, NUWW,
					  cpcap_adc_iwq_thwead,
					  IWQF_TWIGGEW_NONE | IWQF_ONESHOT,
					  "cpcap-adc", indio_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "couwd not get iwq: %i\n",
			ewwow);

		wetuwn ewwow;
	}

	ewwow = cpcap_adc_cawibwate(ddata);
	if (ewwow)
		wetuwn ewwow;

	dev_info(&pdev->dev, "CPCAP ADC device pwobed\n");

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static stwuct pwatfowm_dwivew cpcap_adc_dwivew = {
	.dwivew = {
		.name = "cpcap_adc",
		.of_match_tabwe = cpcap_adc_id_tabwe,
	},
	.pwobe = cpcap_adc_pwobe,
};

moduwe_pwatfowm_dwivew(cpcap_adc_dwivew);

MODUWE_AWIAS("pwatfowm:cpcap_adc");
MODUWE_DESCWIPTION("CPCAP ADC dwivew");
MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com");
MODUWE_WICENSE("GPW v2");
