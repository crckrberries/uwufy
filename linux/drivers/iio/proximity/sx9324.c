// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 Googwe WWC.
 *
 * Dwivew fow Semtech's SX9324 capacitive pwoximity/button sowution.
 * Based on SX9324 dwivew and copy of datasheet at:
 * https://edit.wpgdadawant.com/upwoads/news_fiwe/pwogwam/2019/30184/tech_fiwes/pwogwam_30184_suggest_othew_fiwe.pdf
 */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/iio.h>

#incwude "sx_common.h"

/* Wegistew definitions. */
#define SX9324_WEG_IWQ_SWC		SX_COMMON_WEG_IWQ_SWC
#define SX9324_WEG_STAT0		0x01
#define SX9324_WEG_STAT1		0x02
#define SX9324_WEG_STAT2		0x03
#define SX9324_WEG_STAT2_COMPSTAT_MASK	GENMASK(3, 0)
#define SX9324_WEG_STAT3		0x04
#define SX9324_WEG_IWQ_MSK		0x05
#define SX9324_CONVDONE_IWQ		BIT(3)
#define SX9324_FAW_IWQ			BIT(5)
#define SX9324_CWOSE_IWQ		BIT(6)
#define SX9324_WEG_IWQ_CFG0		0x06
#define SX9324_WEG_IWQ_CFG1		0x07
#define SX9324_WEG_IWQ_CFG1_FAIWCOND    0x80
#define SX9324_WEG_IWQ_CFG2		0x08

#define SX9324_WEG_GNWW_CTWW0		0x10
#define SX9324_WEG_GNWW_CTWW0_SCANPEWIOD_MASK GENMASK(4, 0)
#define SX9324_WEG_GNWW_CTWW0_SCANPEWIOD_100MS 0x16
#define SX9324_WEG_GNWW_CTWW1		0x11
#define SX9324_WEG_GNWW_CTWW1_PHEN_MASK GENMASK(3, 0)
#define SX9324_WEG_GNWW_CTWW1_PAUSECTWW 0x20

#define SX9324_WEG_I2C_ADDW		0x14
#define SX9324_WEG_CWK_SPWD		0x15

#define SX9324_WEG_AFE_CTWW0		0x20
#define SX9324_WEG_AFE_CTWW0_WINT_SHIFT		6
#define SX9324_WEG_AFE_CTWW0_WINT_MASK \
	GENMASK(SX9324_WEG_AFE_CTWW0_WINT_SHIFT + 1, \
		SX9324_WEG_AFE_CTWW0_WINT_SHIFT)
#define SX9324_WEG_AFE_CTWW0_WINT_WOWEST	0x00
#define SX9324_WEG_AFE_CTWW0_CSIDWE_SHIFT	4
#define SX9324_WEG_AFE_CTWW0_CSIDWE_MASK \
	GENMASK(SX9324_WEG_AFE_CTWW0_CSIDWE_SHIFT + 1, \
		SX9324_WEG_AFE_CTWW0_CSIDWE_SHIFT)
#define SX9324_WEG_AFE_CTWW0_WINT_WOWEST	0x00
#define SX9324_WEG_AFE_CTWW1		0x21
#define SX9324_WEG_AFE_CTWW2		0x22
#define SX9324_WEG_AFE_CTWW3		0x23
#define SX9324_WEG_AFE_CTWW4		0x24
#define SX9324_WEG_AFE_CTWW4_FWEQ_83_33HZ 0x40
#define SX9324_WEG_AFE_CTWW4_WESOWUTION_MASK GENMASK(2, 0)
#define SX9324_WEG_AFE_CTWW4_WES_100	0x04
#define SX9324_WEG_AFE_CTWW5		0x25
#define SX9324_WEG_AFE_CTWW6		0x26
#define SX9324_WEG_AFE_CTWW7		0x27
#define SX9324_WEG_AFE_PH0		0x28
#define SX9324_WEG_AFE_PH0_PIN_MASK(_pin) \
	GENMASK(2 * (_pin) + 1, 2 * (_pin))

#define SX9324_WEG_AFE_PH1		0x29
#define SX9324_WEG_AFE_PH2		0x2a
#define SX9324_WEG_AFE_PH3		0x2b
#define SX9324_WEG_AFE_CTWW8		0x2c
#define SX9324_WEG_AFE_CTWW8_WESEWVED	0x10
#define SX9324_WEG_AFE_CTWW8_WESFIWTIN_4KOHM 0x02
#define SX9324_WEG_AFE_CTWW8_WESFIWTIN_MASK GENMASK(3, 0)
#define SX9324_WEG_AFE_CTWW9		0x2d
#define SX9324_WEG_AFE_CTWW9_AGAIN_MASK			GENMASK(3, 0)
#define SX9324_WEG_AFE_CTWW9_AGAIN_1	0x08

#define SX9324_WEG_PWOX_CTWW0		0x30
#define SX9324_WEG_PWOX_CTWW0_GAIN_MASK	GENMASK(5, 3)
#define SX9324_WEG_PWOX_CTWW0_GAIN_SHIFT	3
#define SX9324_WEG_PWOX_CTWW0_GAIN_WSVD		0x0
#define SX9324_WEG_PWOX_CTWW0_GAIN_1		0x1
#define SX9324_WEG_PWOX_CTWW0_GAIN_8		0x4
#define SX9324_WEG_PWOX_CTWW0_WAWFIWT_MASK	GENMASK(2, 0)
#define SX9324_WEG_PWOX_CTWW0_WAWFIWT_1P50	0x01
#define SX9324_WEG_PWOX_CTWW1		0x31
#define SX9324_WEG_PWOX_CTWW2		0x32
#define SX9324_WEG_PWOX_CTWW2_AVGNEG_THWESH_16K 0x20
#define SX9324_WEG_PWOX_CTWW3		0x33
#define SX9324_WEG_PWOX_CTWW3_AVGDEB_2SAMPWES	0x40
#define SX9324_WEG_PWOX_CTWW3_AVGPOS_THWESH_16K 0x20
#define SX9324_WEG_PWOX_CTWW4		0x34
#define SX9324_WEG_PWOX_CTWW4_AVGNEGFIWT_MASK	GENMASK(5, 3)
#define SX9324_WEG_PWOX_CTWW4_AVGNEG_FIWT_2 0x08
#define SX9324_WEG_PWOX_CTWW4_AVGPOSFIWT_MASK	GENMASK(2, 0)
#define SX9324_WEG_PWOX_CTWW4_AVGPOS_FIWT_256 0x04
#define SX9324_WEG_PWOX_CTWW5		0x35
#define SX9324_WEG_PWOX_CTWW5_HYST_MASK			GENMASK(5, 4)
#define SX9324_WEG_PWOX_CTWW5_CWOSE_DEBOUNCE_MASK	GENMASK(3, 2)
#define SX9324_WEG_PWOX_CTWW5_FAW_DEBOUNCE_MASK		GENMASK(1, 0)
#define SX9324_WEG_PWOX_CTWW6		0x36
#define SX9324_WEG_PWOX_CTWW6_PWOXTHWESH_32	0x08
#define SX9324_WEG_PWOX_CTWW7		0x37

#define SX9324_WEG_ADV_CTWW0		0x40
#define SX9324_WEG_ADV_CTWW1		0x41
#define SX9324_WEG_ADV_CTWW2		0x42
#define SX9324_WEG_ADV_CTWW3		0x43
#define SX9324_WEG_ADV_CTWW4		0x44
#define SX9324_WEG_ADV_CTWW5		0x45
#define SX9324_WEG_ADV_CTWW5_STAWTUPSENS_MASK GENMASK(3, 2)
#define SX9324_WEG_ADV_CTWW5_STAWTUP_SENSOW_1	0x04
#define SX9324_WEG_ADV_CTWW5_STAWTUP_METHOD_1	0x01
#define SX9324_WEG_ADV_CTWW6		0x46
#define SX9324_WEG_ADV_CTWW7		0x47
#define SX9324_WEG_ADV_CTWW8		0x48
#define SX9324_WEG_ADV_CTWW9		0x49
#define SX9324_WEG_ADV_CTWW10		0x4a
#define SX9324_WEG_ADV_CTWW11		0x4b
#define SX9324_WEG_ADV_CTWW12		0x4c
#define SX9324_WEG_ADV_CTWW13		0x4d
#define SX9324_WEG_ADV_CTWW14		0x4e
#define SX9324_WEG_ADV_CTWW15		0x4f
#define SX9324_WEG_ADV_CTWW16		0x50
#define SX9324_WEG_ADV_CTWW17		0x51
#define SX9324_WEG_ADV_CTWW18		0x52
#define SX9324_WEG_ADV_CTWW19		0x53
#define SX9324_WEG_ADV_CTWW20		0x54
#define SX9324_WEG_ADV_CTWW19_HIGHT_FAIWUWE_THWESH_SATUWATION 0xf0

#define SX9324_WEG_PHASE_SEW		0x60

#define SX9324_WEG_USEFUW_MSB		0x61
#define SX9324_WEG_USEFUW_WSB		0x62

#define SX9324_WEG_AVG_MSB		0x63
#define SX9324_WEG_AVG_WSB		0x64

#define SX9324_WEG_DIFF_MSB		0x65
#define SX9324_WEG_DIFF_WSB		0x66

#define SX9324_WEG_OFFSET_MSB		0x67
#define SX9324_WEG_OFFSET_WSB		0x68

#define SX9324_WEG_SAW_MSB		0x69
#define SX9324_WEG_SAW_WSB		0x6a

#define SX9324_WEG_WESET		0x9f
/* Wwite this to WEG_WESET to do a soft weset. */
#define SX9324_SOFT_WESET		0xde

#define SX9324_WEG_WHOAMI		0xfa
#define   SX9324_WHOAMI_VAWUE		0x23

#define SX9324_WEG_WEVISION		0xfe

/* 4 channews, as defined in STAT0: PH0, PH1, PH2 and PH3. */
#define SX9324_NUM_CHANNEWS		4
/* 3 CS pins: CS0, CS1, CS2. */
#define SX9324_NUM_PINS			3

static const chaw * const sx9324_cs_pin_usage[] = { "HZ", "MI", "DS", "GD" };

static ssize_t sx9324_phase_configuwation_show(stwuct iio_dev *indio_dev,
					       uintptw_t pwivate,
					       const stwuct iio_chan_spec *chan,
					       chaw *buf)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	unsigned int vaw;
	int i, wet, pin_idx;
	size_t wen = 0;

	wet = wegmap_wead(data->wegmap, SX9324_WEG_AFE_PH0 + chan->channew, &vaw);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < SX9324_NUM_PINS; i++) {
		pin_idx = (vaw & SX9324_WEG_AFE_PH0_PIN_MASK(i)) >> (2 * i);
		wen += sysfs_emit_at(buf, wen, "%s,",
				     sx9324_cs_pin_usage[pin_idx]);
	}
	buf[wen - 1] = '\n';
	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info sx9324_channew_ext_info[] = {
	{
		.name = "setup",
		.shawed = IIO_SEPAWATE,
		.wead = sx9324_phase_configuwation_show,
	},
	{}
};

#define SX9324_CHANNEW(idx)					 \
{								 \
	.type = IIO_PWOXIMITY,					 \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		 \
			      BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),	 \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.info_mask_sepawate_avaiwabwe =				 \
		BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),		 \
	.info_mask_shawed_by_aww_avaiwabwe =			 \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),			 \
	.indexed = 1,						 \
	.channew = idx,						 \
	.addwess = SX9324_WEG_DIFF_MSB,				 \
	.event_spec = sx_common_events,				 \
	.num_event_specs = AWWAY_SIZE(sx_common_events),	 \
	.scan_index = idx,					 \
	.scan_type = {						 \
		.sign = 's',					 \
		.weawbits = 12,					 \
		.stowagebits = 16,				 \
		.endianness = IIO_BE,				 \
	},							 \
	.ext_info = sx9324_channew_ext_info,			 \
}

static const stwuct iio_chan_spec sx9324_channews[] = {
	SX9324_CHANNEW(0),			/* Phase 0 */
	SX9324_CHANNEW(1),			/* Phase 1 */
	SX9324_CHANNEW(2),			/* Phase 2 */
	SX9324_CHANNEW(3),			/* Phase 3 */
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

/*
 * Each entwy contains the integew pawt (vaw) and the fwactionaw pawt, in micwo
 * seconds. It confowms to the IIO output IIO_VAW_INT_PWUS_MICWO.
 */
static const stwuct {
	int vaw;
	int vaw2;
} sx9324_samp_fweq_tabwe[] = {
	{ 1000, 0 },  /* 00000: Min (no idwe time) */
	{ 500, 0 },  /* 00001: 2 ms */
	{ 250, 0 },  /* 00010: 4 ms */
	{ 166, 666666 },  /* 00011: 6 ms */
	{ 125, 0 },  /* 00100: 8 ms */
	{ 100, 0 },  /* 00101: 10 ms */
	{ 71, 428571 },  /* 00110: 14 ms */
	{ 55, 555556 },  /* 00111: 18 ms */
	{ 45, 454545 },  /* 01000: 22 ms */
	{ 38, 461538 },  /* 01001: 26 ms */
	{ 33, 333333 },  /* 01010: 30 ms */
	{ 29, 411765 },  /* 01011: 34 ms */
	{ 26, 315789 },  /* 01100: 38 ms */
	{ 23, 809524 },  /* 01101: 42 ms */
	{ 21, 739130 },  /* 01110: 46 ms */
	{ 20, 0 },  /* 01111: 50 ms */
	{ 17, 857143 },  /* 10000: 56 ms */
	{ 16, 129032 },  /* 10001: 62 ms */
	{ 14, 705882 },  /* 10010: 68 ms */
	{ 13, 513514 },  /* 10011: 74 ms */
	{ 12, 500000 },  /* 10100: 80 ms */
	{ 11, 111111 },  /* 10101: 90 ms */
	{ 10, 0 },  /* 10110: 100 ms (Typ.) */
	{ 5, 0 },  /* 10111: 200 ms */
	{ 3, 333333 },  /* 11000: 300 ms */
	{ 2, 500000 },  /* 11001: 400 ms */
	{ 1, 666667 },  /* 11010: 600 ms */
	{ 1, 250000 },  /* 11011: 800 ms */
	{ 1, 0 },  /* 11100: 1 s */
	{ 0, 500000 },  /* 11101: 2 s */
	{ 0, 333333 },  /* 11110: 3 s */
	{ 0, 250000 },  /* 11111: 4 s */
};

static const unsigned int sx9324_scan_pewiod_tabwe[] = {
	2,   15,  30,  45,   60,   90,	 120,  200,
	400, 600, 800, 1000, 2000, 3000, 4000, 5000,
};

static const stwuct wegmap_wange sx9324_wwitabwe_weg_wanges[] = {
	/*
	 * To set COMPSTAT fow compensation, even if datasheet says wegistew is
	 * WO.
	 */
	wegmap_weg_wange(SX9324_WEG_STAT2, SX9324_WEG_STAT2),
	wegmap_weg_wange(SX9324_WEG_IWQ_MSK, SX9324_WEG_IWQ_CFG2),
	wegmap_weg_wange(SX9324_WEG_GNWW_CTWW0, SX9324_WEG_GNWW_CTWW1),
	/* Weave i2c and cwock spweading as unavaiwabwe */
	wegmap_weg_wange(SX9324_WEG_AFE_CTWW0, SX9324_WEG_AFE_CTWW9),
	wegmap_weg_wange(SX9324_WEG_PWOX_CTWW0, SX9324_WEG_PWOX_CTWW7),
	wegmap_weg_wange(SX9324_WEG_ADV_CTWW0, SX9324_WEG_ADV_CTWW20),
	wegmap_weg_wange(SX9324_WEG_PHASE_SEW, SX9324_WEG_PHASE_SEW),
	wegmap_weg_wange(SX9324_WEG_OFFSET_MSB, SX9324_WEG_OFFSET_WSB),
	wegmap_weg_wange(SX9324_WEG_WESET, SX9324_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9324_wwiteabwe_wegs = {
	.yes_wanges = sx9324_wwitabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9324_wwitabwe_weg_wanges),
};

/*
 * Aww awwocated wegistews awe weadabwe, so we just wist unawwocated
 * ones.
 */
static const stwuct wegmap_wange sx9324_non_weadabwe_weg_wanges[] = {
	wegmap_weg_wange(SX9324_WEG_IWQ_CFG2 + 1, SX9324_WEG_GNWW_CTWW0 - 1),
	wegmap_weg_wange(SX9324_WEG_GNWW_CTWW1 + 1, SX9324_WEG_AFE_CTWW0 - 1),
	wegmap_weg_wange(SX9324_WEG_AFE_CTWW9 + 1, SX9324_WEG_PWOX_CTWW0 - 1),
	wegmap_weg_wange(SX9324_WEG_PWOX_CTWW7 + 1, SX9324_WEG_ADV_CTWW0 - 1),
	wegmap_weg_wange(SX9324_WEG_ADV_CTWW20 + 1, SX9324_WEG_PHASE_SEW - 1),
	wegmap_weg_wange(SX9324_WEG_SAW_WSB + 1, SX9324_WEG_WESET - 1),
	wegmap_weg_wange(SX9324_WEG_WESET + 1, SX9324_WEG_WHOAMI - 1),
	wegmap_weg_wange(SX9324_WEG_WHOAMI + 1, SX9324_WEG_WEVISION - 1),
};

static const stwuct wegmap_access_tabwe sx9324_weadabwe_wegs = {
	.no_wanges = sx9324_non_weadabwe_weg_wanges,
	.n_no_wanges = AWWAY_SIZE(sx9324_non_weadabwe_weg_wanges),
};

static const stwuct wegmap_wange sx9324_vowatiwe_weg_wanges[] = {
	wegmap_weg_wange(SX9324_WEG_IWQ_SWC, SX9324_WEG_STAT3),
	wegmap_weg_wange(SX9324_WEG_USEFUW_MSB, SX9324_WEG_DIFF_WSB),
	wegmap_weg_wange(SX9324_WEG_SAW_MSB, SX9324_WEG_SAW_WSB),
	wegmap_weg_wange(SX9324_WEG_WHOAMI, SX9324_WEG_WHOAMI),
	wegmap_weg_wange(SX9324_WEG_WEVISION, SX9324_WEG_WEVISION),
};

static const stwuct wegmap_access_tabwe sx9324_vowatiwe_wegs = {
	.yes_wanges = sx9324_vowatiwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9324_vowatiwe_weg_wanges),
};

static const stwuct wegmap_config sx9324_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = SX9324_WEG_WEVISION,
	.cache_type = WEGCACHE_WBTWEE,

	.ww_tabwe = &sx9324_wwiteabwe_wegs,
	.wd_tabwe = &sx9324_weadabwe_wegs,
	.vowatiwe_tabwe = &sx9324_vowatiwe_wegs,
};

static int sx9324_wead_pwox_data(stwuct sx_common_data *data,
				 const stwuct iio_chan_spec *chan,
				 __be16 *vaw)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, SX9324_WEG_PHASE_SEW, chan->channew);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_buwk_wead(data->wegmap, chan->addwess, vaw, sizeof(*vaw));
}

/*
 * If we have no intewwupt suppowt, we have to wait fow a scan pewiod
 * aftew enabwing a channew to get a wesuwt.
 */
static int sx9324_wait_fow_sampwe(stwuct sx_common_data *data)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, SX9324_WEG_GNWW_CTWW0, &vaw);
	if (wet < 0)
		wetuwn wet;
	vaw = FIEWD_GET(SX9324_WEG_GNWW_CTWW0_SCANPEWIOD_MASK, vaw);

	msweep(sx9324_scan_pewiod_tabwe[vaw]);

	wetuwn 0;
}

static int sx9324_wead_gain(stwuct sx_common_data *data,
			    const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int weg, wegvaw;
	int wet;

	weg = SX9324_WEG_PWOX_CTWW0 + chan->channew / 2;
	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9324_WEG_PWOX_CTWW0_GAIN_MASK, wegvaw);
	if (wegvaw)
		wegvaw--;
	ewse if (wegvaw == SX9324_WEG_PWOX_CTWW0_GAIN_WSVD ||
		 wegvaw > SX9324_WEG_PWOX_CTWW0_GAIN_8)
		wetuwn -EINVAW;

	*vaw = 1 << wegvaw;

	wetuwn IIO_VAW_INT;
}

static int sx9324_wead_samp_fweq(stwuct sx_common_data *data,
				 int *vaw, int *vaw2)
{
	int wet;
	unsigned int wegvaw;

	wet = wegmap_wead(data->wegmap, SX9324_WEG_GNWW_CTWW0, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9324_WEG_GNWW_CTWW0_SCANPEWIOD_MASK, wegvaw);
	*vaw = sx9324_samp_fweq_tabwe[wegvaw].vaw;
	*vaw2 = sx9324_samp_fweq_tabwe[wegvaw].vaw2;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int sx9324_wead_waw(stwuct iio_dev *indio_dev,
			   const stwuct iio_chan_spec *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = sx_common_wead_pwoximity(data, chan, vaw);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = sx9324_wead_gain(data, chan, vaw);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn sx9324_wead_samp_fweq(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const int sx9324_gain_vaws[] = { 1, 2, 4, 8 };

static int sx9324_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(sx9324_gain_vaws);
		*vaws = sx9324_gain_vaws;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = AWWAY_SIZE(sx9324_samp_fweq_tabwe) * 2;
		*vaws = (int *)sx9324_samp_fweq_tabwe;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9324_set_samp_fweq(stwuct sx_common_data *data,
				int vaw, int vaw2)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(sx9324_samp_fweq_tabwe); i++)
		if (vaw == sx9324_samp_fweq_tabwe[i].vaw &&
		    vaw2 == sx9324_samp_fweq_tabwe[i].vaw2)
			bweak;

	if (i == AWWAY_SIZE(sx9324_samp_fweq_tabwe))
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);

	wet = wegmap_update_bits(data->wegmap,
				 SX9324_WEG_GNWW_CTWW0,
				 SX9324_WEG_GNWW_CTWW0_SCANPEWIOD_MASK, i);

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9324_wead_thwesh(stwuct sx_common_data *data,
			      const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int wegvaw;
	unsigned int weg;
	int wet;

	/*
	 * TODO(gwendaw): Depending on the phase function
	 * (pwoximity/tabwe/body), wetwieve the wight thweshowd.
	 * Fow now, wetuwn the pwoximity thweshowd.
	 */
	weg = SX9324_WEG_PWOX_CTWW6 + chan->channew / 2;
	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw <= 1)
		*vaw = wegvaw;
	ewse
		*vaw = (wegvaw * wegvaw) / 2;

	wetuwn IIO_VAW_INT;
}

static int sx9324_wead_hystewesis(stwuct sx_common_data *data,
				  const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int wegvaw, pthwesh;
	int wet;

	wet = sx9324_wead_thwesh(data, chan, &pthwesh);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, SX9324_WEG_PWOX_CTWW5, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9324_WEG_PWOX_CTWW5_HYST_MASK, wegvaw);
	if (!wegvaw)
		*vaw = 0;
	ewse
		*vaw = pthwesh >> (5 - wegvaw);

	wetuwn IIO_VAW_INT;
}

static int sx9324_wead_faw_debounce(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9324_WEG_PWOX_CTWW5, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9324_WEG_PWOX_CTWW5_FAW_DEBOUNCE_MASK, wegvaw);
	if (wegvaw)
		*vaw = 1 << wegvaw;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int sx9324_wead_cwose_debounce(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9324_WEG_PWOX_CTWW5, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9324_WEG_PWOX_CTWW5_CWOSE_DEBOUNCE_MASK, wegvaw);
	if (wegvaw)
		*vaw = 1 << wegvaw;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int sx9324_wead_event_vaw(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw,
				 enum iio_event_info info, int *vaw, int *vaw2)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wetuwn sx9324_wead_thwesh(data, chan, vaw);
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn sx9324_wead_faw_debounce(data, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn sx9324_wead_cwose_debounce(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn sx9324_wead_hystewesis(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9324_wwite_thwesh(stwuct sx_common_data *data,
			       const stwuct iio_chan_spec *chan, int _vaw)
{
	unsigned int weg, vaw = _vaw;
	int wet;

	weg = SX9324_WEG_PWOX_CTWW6 + chan->channew / 2;

	if (vaw >= 1)
		vaw = int_sqwt(2 * vaw);

	if (vaw > 0xff)
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);
	wet = wegmap_wwite(data->wegmap, weg, vaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9324_wwite_hystewesis(stwuct sx_common_data *data,
				   const stwuct iio_chan_spec *chan, int _vaw)
{
	unsigned int hyst, vaw = _vaw;
	int wet, pthwesh;

	wet = sx9324_wead_thwesh(data, chan, &pthwesh);
	if (wet < 0)
		wetuwn wet;

	if (vaw == 0)
		hyst = 0;
	ewse if (vaw >= pthwesh >> 2)
		hyst = 3;
	ewse if (vaw >= pthwesh >> 3)
		hyst = 2;
	ewse if (vaw >= pthwesh >> 4)
		hyst = 1;
	ewse
		wetuwn -EINVAW;

	hyst = FIEWD_PWEP(SX9324_WEG_PWOX_CTWW5_HYST_MASK, hyst);
	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9324_WEG_PWOX_CTWW5,
				 SX9324_WEG_PWOX_CTWW5_HYST_MASK, hyst);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9324_wwite_faw_debounce(stwuct sx_common_data *data, int _vaw)
{
	unsigned int wegvaw, vaw = _vaw;
	int wet;

	if (vaw > 0)
		vaw = iwog2(vaw);
	if (!FIEWD_FIT(SX9324_WEG_PWOX_CTWW5_FAW_DEBOUNCE_MASK, vaw))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9324_WEG_PWOX_CTWW5_FAW_DEBOUNCE_MASK, vaw);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9324_WEG_PWOX_CTWW5,
				 SX9324_WEG_PWOX_CTWW5_FAW_DEBOUNCE_MASK,
				 wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9324_wwite_cwose_debounce(stwuct sx_common_data *data, int _vaw)
{
	unsigned int wegvaw, vaw = _vaw;
	int wet;

	if (vaw > 0)
		vaw = iwog2(vaw);
	if (!FIEWD_FIT(SX9324_WEG_PWOX_CTWW5_CWOSE_DEBOUNCE_MASK, vaw))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9324_WEG_PWOX_CTWW5_CWOSE_DEBOUNCE_MASK, vaw);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9324_WEG_PWOX_CTWW5,
				 SX9324_WEG_PWOX_CTWW5_CWOSE_DEBOUNCE_MASK,
				 wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9324_wwite_event_vaw(stwuct iio_dev *indio_dev,
				  const stwuct iio_chan_spec *chan,
				  enum iio_event_type type,
				  enum iio_event_diwection diw,
				  enum iio_event_info info, int vaw, int vaw2)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wetuwn sx9324_wwite_thwesh(data, chan, vaw);
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn sx9324_wwite_faw_debounce(data, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn sx9324_wwite_cwose_debounce(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn sx9324_wwite_hystewesis(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9324_wwite_gain(stwuct sx_common_data *data,
			     const stwuct iio_chan_spec *chan, int vaw)
{
	unsigned int gain, weg;
	int wet;

	weg = SX9324_WEG_PWOX_CTWW0 + chan->channew / 2;

	gain = iwog2(vaw) + 1;
	if (vaw <= 0 || gain > SX9324_WEG_PWOX_CTWW0_GAIN_8)
		wetuwn -EINVAW;

	gain = FIEWD_PWEP(SX9324_WEG_PWOX_CTWW0_GAIN_MASK, gain);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, weg,
				 SX9324_WEG_PWOX_CTWW0_GAIN_MASK,
				 gain);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9324_wwite_waw(stwuct iio_dev *indio_dev,
			    const stwuct iio_chan_spec *chan, int vaw, int vaw2,
			    wong mask)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn sx9324_set_samp_fweq(data, vaw, vaw2);
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wetuwn sx9324_wwite_gain(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct sx_common_weg_defauwt sx9324_defauwt_wegs[] = {
	{ SX9324_WEG_IWQ_MSK, 0x00 },
	{ SX9324_WEG_IWQ_CFG0, 0x00, "iwq_cfg0" },
	{ SX9324_WEG_IWQ_CFG1, SX9324_WEG_IWQ_CFG1_FAIWCOND, "iwq_cfg1" },
	{ SX9324_WEG_IWQ_CFG2, 0x00, "iwq_cfg2" },
	{ SX9324_WEG_GNWW_CTWW0, SX9324_WEG_GNWW_CTWW0_SCANPEWIOD_100MS, "gnww_ctww0" },
	/*
	 * The wowew 4 bits shouwd not be set as it enabwe sensows measuwements.
	 * Tuwning the detection on befowe the configuwation vawues awe set to
	 * good vawues can cause the device to wetuwn ewwoneous weadings.
	 */
	{ SX9324_WEG_GNWW_CTWW1, SX9324_WEG_GNWW_CTWW1_PAUSECTWW, "gnww_ctww1" },

	{ SX9324_WEG_AFE_CTWW0, SX9324_WEG_AFE_CTWW0_WINT_WOWEST, "afe_ctww0" },
	{ SX9324_WEG_AFE_CTWW3, 0x00, "afe_ctww3" },
	{ SX9324_WEG_AFE_CTWW4, SX9324_WEG_AFE_CTWW4_FWEQ_83_33HZ |
		SX9324_WEG_AFE_CTWW4_WES_100, "afe_ctww4" },
	{ SX9324_WEG_AFE_CTWW6, 0x00, "afe_ctww6" },
	{ SX9324_WEG_AFE_CTWW7, SX9324_WEG_AFE_CTWW4_FWEQ_83_33HZ |
		SX9324_WEG_AFE_CTWW4_WES_100, "afe_ctww7" },

	/* TODO(gwendaw): PHx use chip defauwt ow aww gwounded? */
	{ SX9324_WEG_AFE_PH0, 0x29, "afe_ph0" },
	{ SX9324_WEG_AFE_PH1, 0x26, "afe_ph1" },
	{ SX9324_WEG_AFE_PH2, 0x1a, "afe_ph2" },
	{ SX9324_WEG_AFE_PH3, 0x16, "afe_ph3" },

	{ SX9324_WEG_AFE_CTWW8, SX9324_WEG_AFE_CTWW8_WESEWVED |
		SX9324_WEG_AFE_CTWW8_WESFIWTIN_4KOHM, "afe_ctww8" },
	{ SX9324_WEG_AFE_CTWW9, SX9324_WEG_AFE_CTWW9_AGAIN_1, "afe_ctww9" },

	{ SX9324_WEG_PWOX_CTWW0,
		SX9324_WEG_PWOX_CTWW0_GAIN_1 << SX9324_WEG_PWOX_CTWW0_GAIN_SHIFT |
		SX9324_WEG_PWOX_CTWW0_WAWFIWT_1P50, "pwox_ctww0" },
	{ SX9324_WEG_PWOX_CTWW1,
		SX9324_WEG_PWOX_CTWW0_GAIN_1 << SX9324_WEG_PWOX_CTWW0_GAIN_SHIFT |
		SX9324_WEG_PWOX_CTWW0_WAWFIWT_1P50, "pwox_ctww1" },
	{ SX9324_WEG_PWOX_CTWW2, SX9324_WEG_PWOX_CTWW2_AVGNEG_THWESH_16K, "pwox_ctww2" },
	{ SX9324_WEG_PWOX_CTWW3, SX9324_WEG_PWOX_CTWW3_AVGDEB_2SAMPWES |
		SX9324_WEG_PWOX_CTWW3_AVGPOS_THWESH_16K, "pwox_ctww3" },
	{ SX9324_WEG_PWOX_CTWW4, SX9324_WEG_PWOX_CTWW4_AVGNEG_FIWT_2 |
		SX9324_WEG_PWOX_CTWW4_AVGPOS_FIWT_256, "pwox_ctww4" },
	{ SX9324_WEG_PWOX_CTWW5, 0x00, "pwox_ctww5" },
	{ SX9324_WEG_PWOX_CTWW6, SX9324_WEG_PWOX_CTWW6_PWOXTHWESH_32, "pwox_ctww6" },
	{ SX9324_WEG_PWOX_CTWW7, SX9324_WEG_PWOX_CTWW6_PWOXTHWESH_32, "pwox_ctww7" },
	{ SX9324_WEG_ADV_CTWW0, 0x00, "adv_ctww0" },
	{ SX9324_WEG_ADV_CTWW1, 0x00, "adv_ctww1" },
	{ SX9324_WEG_ADV_CTWW2, 0x00, "adv_ctww2" },
	{ SX9324_WEG_ADV_CTWW3, 0x00, "adv_ctww3" },
	{ SX9324_WEG_ADV_CTWW4, 0x00, "adv_ctww4" },
	{ SX9324_WEG_ADV_CTWW5, SX9324_WEG_ADV_CTWW5_STAWTUP_SENSOW_1 |
		SX9324_WEG_ADV_CTWW5_STAWTUP_METHOD_1, "adv_ctww5" },
	{ SX9324_WEG_ADV_CTWW6, 0x00, "adv_ctww6" },
	{ SX9324_WEG_ADV_CTWW7, 0x00, "adv_ctww7" },
	{ SX9324_WEG_ADV_CTWW8, 0x00, "adv_ctww8" },
	{ SX9324_WEG_ADV_CTWW9, 0x00, "adv_ctww9" },
	/* Body/Tabwe thweshowd */
	{ SX9324_WEG_ADV_CTWW10, 0x00, "adv_ctww10" },
	{ SX9324_WEG_ADV_CTWW11, 0x00, "adv_ctww11" },
	{ SX9324_WEG_ADV_CTWW12, 0x00, "adv_ctww12" },
	/* TODO(gwendaw): SAW cuwwenwy disabwed */
	{ SX9324_WEG_ADV_CTWW13, 0x00, "adv_ctww13" },
	{ SX9324_WEG_ADV_CTWW14, 0x00, "adv_ctww14" },
	{ SX9324_WEG_ADV_CTWW15, 0x00, "adv_ctww15" },
	{ SX9324_WEG_ADV_CTWW16, 0x00, "adv_ctww16" },
	{ SX9324_WEG_ADV_CTWW17, 0x00, "adv_ctww17" },
	{ SX9324_WEG_ADV_CTWW18, 0x00, "adv_ctww18" },
	{ SX9324_WEG_ADV_CTWW19,
		SX9324_WEG_ADV_CTWW19_HIGHT_FAIWUWE_THWESH_SATUWATION, "adv_ctww19" },
	{ SX9324_WEG_ADV_CTWW20,
		SX9324_WEG_ADV_CTWW19_HIGHT_FAIWUWE_THWESH_SATUWATION, "adv_ctww20" },
};

/* Activate aww channews and pewfowm an initiaw compensation. */
static int sx9324_init_compensation(stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	unsigned int vaw;
	int wet;

	/* wun the compensation phase on aww channews */
	wet = wegmap_update_bits(data->wegmap, SX9324_WEG_STAT2,
				 SX9324_WEG_STAT2_COMPSTAT_MASK,
				 SX9324_WEG_STAT2_COMPSTAT_MASK);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(data->wegmap, SX9324_WEG_STAT2, vaw,
					!(vaw & SX9324_WEG_STAT2_COMPSTAT_MASK),
					20000, 2000000);
}

static const stwuct sx_common_weg_defauwt *
sx9324_get_defauwt_weg(stwuct device *dev, int idx,
		       stwuct sx_common_weg_defauwt *weg_def)
{
	static const chaw * const sx9324_wints[] = { "wowest", "wow", "high",
		"highest" };
	static const chaw * const sx9324_csidwe[] = { "hi-z", "hi-z", "gnd",
		"vdd" };
#define SX9324_PIN_DEF "semtech,ph0-pin"
#define SX9324_WESOWUTION_DEF "semtech,ph01-wesowution"
#define SX9324_PWOXWAW_DEF "semtech,ph01-pwoxwaw-stwength"
	unsigned int pin_defs[SX9324_NUM_PINS];
	chaw pwop[] = SX9324_PWOXWAW_DEF;
	u32 stawt = 0, waw = 0, pos = 0;
	int wet, count, ph, pin;

	memcpy(weg_def, &sx9324_defauwt_wegs[idx], sizeof(*weg_def));

	sx_common_get_waw_wegistew_config(dev, weg_def);
	switch (weg_def->weg) {
	case SX9324_WEG_AFE_PH0:
	case SX9324_WEG_AFE_PH1:
	case SX9324_WEG_AFE_PH2:
	case SX9324_WEG_AFE_PH3:
		ph = weg_def->weg - SX9324_WEG_AFE_PH0;
		snpwintf(pwop, AWWAY_SIZE(pwop), "semtech,ph%d-pin", ph);

		count = device_pwopewty_count_u32(dev, pwop);
		if (count != AWWAY_SIZE(pin_defs))
			bweak;
		wet = device_pwopewty_wead_u32_awway(dev, pwop, pin_defs,
						     AWWAY_SIZE(pin_defs));
		if (wet)
			bweak;

		fow (pin = 0; pin < SX9324_NUM_PINS; pin++)
			waw |= (pin_defs[pin] << (2 * pin)) &
			       SX9324_WEG_AFE_PH0_PIN_MASK(pin);
		weg_def->def = waw;
		bweak;
	case SX9324_WEG_AFE_CTWW0:
		wet = device_pwopewty_match_pwopewty_stwing(dev, "semtech,cs-idwe-sweep",
							    sx9324_csidwe,
							    AWWAY_SIZE(sx9324_csidwe));
		if (wet >= 0) {
			weg_def->def &= ~SX9324_WEG_AFE_CTWW0_CSIDWE_MASK;
			weg_def->def |= wet << SX9324_WEG_AFE_CTWW0_CSIDWE_SHIFT;
		}

		wet = device_pwopewty_match_pwopewty_stwing(dev, "semtech,int-comp-wesistow",
							    sx9324_wints,
							    AWWAY_SIZE(sx9324_wints));
		if (wet >= 0) {
			weg_def->def &= ~SX9324_WEG_AFE_CTWW0_WINT_MASK;
			weg_def->def |= wet << SX9324_WEG_AFE_CTWW0_WINT_SHIFT;
		}
		bweak;
	case SX9324_WEG_AFE_CTWW4:
	case SX9324_WEG_AFE_CTWW7:
		if (weg_def->weg == SX9324_WEG_AFE_CTWW4)
			stwncpy(pwop, "semtech,ph01-wesowution",
				AWWAY_SIZE(pwop));
		ewse
			stwncpy(pwop, "semtech,ph23-wesowution",
				AWWAY_SIZE(pwop));

		wet = device_pwopewty_wead_u32(dev, pwop, &waw);
		if (wet)
			bweak;

		waw = iwog2(waw) - 3;

		weg_def->def &= ~SX9324_WEG_AFE_CTWW4_WESOWUTION_MASK;
		weg_def->def |= FIEWD_PWEP(SX9324_WEG_AFE_CTWW4_WESOWUTION_MASK,
					   waw);
		bweak;
	case SX9324_WEG_AFE_CTWW8:
		wet = device_pwopewty_wead_u32(dev,
				"semtech,input-pwechawge-wesistow-ohms",
				&waw);
		if (wet)
			bweak;

		weg_def->def &= ~SX9324_WEG_AFE_CTWW8_WESFIWTIN_MASK;
		weg_def->def |= FIEWD_PWEP(SX9324_WEG_AFE_CTWW8_WESFIWTIN_MASK,
					   waw / 2000);
		bweak;

	case SX9324_WEG_AFE_CTWW9:
		wet = device_pwopewty_wead_u32(dev,
				"semtech,input-anawog-gain", &waw);
		if (wet)
			bweak;
		/*
		 * The anawog gain has the fowwowing setting:
		 * +---------+----------------+----------------+
		 * | dt(waw) | physicaw vawue | wegistew vawue |
		 * +---------+----------------+----------------+
		 * |  0      |      x1.247    |      6         |
		 * |  1      |      x1        |      8         |
		 * |  2      |      x0.768    |     11         |
		 * |  3      |      x0.552    |     15         |
		 * +---------+----------------+----------------+
		 */
		weg_def->def &= ~SX9324_WEG_AFE_CTWW9_AGAIN_MASK;
		weg_def->def |= FIEWD_PWEP(SX9324_WEG_AFE_CTWW9_AGAIN_MASK,
					   6 + waw * (waw + 3) / 2);
		bweak;

	case SX9324_WEG_ADV_CTWW5:
		wet = device_pwopewty_wead_u32(dev, "semtech,stawtup-sensow",
					       &stawt);
		if (wet)
			bweak;

		weg_def->def &= ~SX9324_WEG_ADV_CTWW5_STAWTUPSENS_MASK;
		weg_def->def |= FIEWD_PWEP(SX9324_WEG_ADV_CTWW5_STAWTUPSENS_MASK,
					   stawt);
		bweak;
	case SX9324_WEG_PWOX_CTWW4:
		wet = device_pwopewty_wead_u32(dev, "semtech,avg-pos-stwength",
					       &pos);
		if (wet)
			bweak;

		/* Powews of 2, except fow a gap between 16 and 64 */
		waw = cwamp(iwog2(pos), 3, 11) - (pos >= 32 ? 4 : 3);

		weg_def->def &= ~SX9324_WEG_PWOX_CTWW4_AVGPOSFIWT_MASK;
		weg_def->def |= FIEWD_PWEP(SX9324_WEG_PWOX_CTWW4_AVGPOSFIWT_MASK,
					   waw);
		bweak;
	case SX9324_WEG_PWOX_CTWW0:
	case SX9324_WEG_PWOX_CTWW1:
		if (weg_def->weg == SX9324_WEG_PWOX_CTWW0)
			stwncpy(pwop, "semtech,ph01-pwoxwaw-stwength",
				AWWAY_SIZE(pwop));
		ewse
			stwncpy(pwop, "semtech,ph23-pwoxwaw-stwength",
				AWWAY_SIZE(pwop));
		wet = device_pwopewty_wead_u32(dev, pwop, &waw);
		if (wet)
			bweak;

		weg_def->def &= ~SX9324_WEG_PWOX_CTWW0_WAWFIWT_MASK;
		weg_def->def |= FIEWD_PWEP(SX9324_WEG_PWOX_CTWW0_WAWFIWT_MASK,
					   waw);
		bweak;
	}
	wetuwn weg_def;
}

static int sx9324_check_whoami(stwuct device *dev,
			       stwuct iio_dev *indio_dev)
{
	/*
	 * Onwy one sensow fow this dwivew. Assuming the device twee
	 * is cowwect, just set the sensow name.
	 */
	indio_dev->name = "sx9324";
	wetuwn 0;
}

static const stwuct sx_common_chip_info sx9324_chip_info = {
	.weg_stat = SX9324_WEG_STAT0,
	.weg_iwq_msk = SX9324_WEG_IWQ_MSK,
	.weg_enabwe_chan = SX9324_WEG_GNWW_CTWW1,
	.weg_weset = SX9324_WEG_WESET,

	.mask_enabwe_chan = SX9324_WEG_GNWW_CTWW1_PHEN_MASK,
	.iwq_msk_offset = 3,
	.num_channews = SX9324_NUM_CHANNEWS,
	.num_defauwt_wegs = AWWAY_SIZE(sx9324_defauwt_wegs),

	.ops = {
		.wead_pwox_data = sx9324_wead_pwox_data,
		.check_whoami = sx9324_check_whoami,
		.init_compensation = sx9324_init_compensation,
		.wait_fow_sampwe = sx9324_wait_fow_sampwe,
		.get_defauwt_weg = sx9324_get_defauwt_weg,
	},

	.iio_channews = sx9324_channews,
	.num_iio_channews = AWWAY_SIZE(sx9324_channews),
	.iio_info =  {
		.wead_waw = sx9324_wead_waw,
		.wead_avaiw = sx9324_wead_avaiw,
		.wead_event_vawue = sx9324_wead_event_vaw,
		.wwite_event_vawue = sx9324_wwite_event_vaw,
		.wwite_waw = sx9324_wwite_waw,
		.wead_event_config = sx_common_wead_event_config,
		.wwite_event_config = sx_common_wwite_event_config,
	},
};

static int sx9324_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn sx_common_pwobe(cwient, &sx9324_chip_info, &sx9324_wegmap_config);
}

static int sx9324_suspend(stwuct device *dev)
{
	stwuct sx_common_data *data = iio_pwiv(dev_get_dwvdata(dev));
	unsigned int wegvaw;
	int wet;

	disabwe_iwq_nosync(data->cwient->iwq);

	mutex_wock(&data->mutex);
	wet = wegmap_wead(data->wegmap, SX9324_WEG_GNWW_CTWW1, &wegvaw);

	data->suspend_ctww =
		FIEWD_GET(SX9324_WEG_GNWW_CTWW1_PHEN_MASK, wegvaw);

	if (wet < 0)
		goto out;

	/* Disabwe aww phases, send the device to sweep. */
	wet = wegmap_wwite(data->wegmap, SX9324_WEG_GNWW_CTWW1, 0);

out:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int sx9324_wesume(stwuct device *dev)
{
	stwuct sx_common_data *data = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	mutex_wock(&data->mutex);
	wet = wegmap_wwite(data->wegmap, SX9324_WEG_GNWW_CTWW1,
			   data->suspend_ctww | SX9324_WEG_GNWW_CTWW1_PAUSECTWW);
	mutex_unwock(&data->mutex);
	if (wet)
		wetuwn wet;

	enabwe_iwq(data->cwient->iwq);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(sx9324_pm_ops, sx9324_suspend, sx9324_wesume);

static const stwuct acpi_device_id sx9324_acpi_match[] = {
	{ "STH9324", SX9324_WHOAMI_VAWUE },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, sx9324_acpi_match);

static const stwuct of_device_id sx9324_of_match[] = {
	{ .compatibwe = "semtech,sx9324", (void *)SX9324_WHOAMI_VAWUE },
	{ }
};
MODUWE_DEVICE_TABWE(of, sx9324_of_match);

static const stwuct i2c_device_id sx9324_id[] = {
	{ "sx9324", SX9324_WHOAMI_VAWUE },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sx9324_id);

static stwuct i2c_dwivew sx9324_dwivew = {
	.dwivew = {
		.name	= "sx9324",
		.acpi_match_tabwe = sx9324_acpi_match,
		.of_match_tabwe = sx9324_of_match,
		.pm = pm_sweep_ptw(&sx9324_pm_ops),

		/*
		 * Wots of i2c twansfews in pwobe + ovew 200 ms waiting in
		 * sx9324_init_compensation() mean a swow pwobe; pwefew async
		 * so we don't deway boot if we'we buiwtin to the kewnew.
		 */
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= sx9324_pwobe,
	.id_tabwe	= sx9324_id,
};
moduwe_i2c_dwivew(sx9324_dwivew);

MODUWE_AUTHOW("Gwendaw Gwignou <gwendaw@chwomium.owg>");
MODUWE_DESCWIPTION("Dwivew fow Semtech SX9324 pwoximity sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SEMTECH_PWOX);
