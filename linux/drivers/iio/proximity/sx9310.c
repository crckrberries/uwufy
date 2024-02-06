// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018 Googwe WWC.
 *
 * Dwivew fow Semtech's SX9310/SX9311 capacitive pwoximity/button sowution.
 * Based on SX9500 dwivew and Semtech dwivew using the input fwamewowk
 * <https://my.syncpwicity.com/shawe/teouwsim8niiaud/
 *          winux-dwivew-SX9310_NoSmawtHSensing>.
 * Wewowked in Apwiw 2019 by Evan Gween <evgween@chwomium.owg>
 * and in Januawy 2020 by Daniew Campewwo <campewwo@chwomium.owg>.
 */

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
#define SX9310_WEG_IWQ_SWC				SX_COMMON_WEG_IWQ_SWC
#define SX9310_WEG_STAT0				0x01
#define SX9310_WEG_STAT1				0x02
#define SX9310_WEG_STAT1_COMPSTAT_MASK			GENMASK(3, 0)
#define SX9310_WEG_IWQ_MSK				0x03
#define   SX9310_CONVDONE_IWQ				BIT(3)
#define   SX9310_FAW_IWQ				BIT(5)
#define   SX9310_CWOSE_IWQ				BIT(6)
#define SX9310_WEG_IWQ_FUNC				0x04

#define SX9310_WEG_PWOX_CTWW0				0x10
#define   SX9310_WEG_PWOX_CTWW0_SENSOWEN_MASK		GENMASK(3, 0)
#define   SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_MASK		GENMASK(7, 4)
#define   SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_15MS		0x01
#define SX9310_WEG_PWOX_CTWW1				0x11
#define SX9310_WEG_PWOX_CTWW2				0x12
#define   SX9310_WEG_PWOX_CTWW2_COMBMODE_MASK		GENMASK(7, 6)
#define   SX9310_WEG_PWOX_CTWW2_COMBMODE_CS0_CS1_CS2_CS3 (0x03 << 6)
#define   SX9310_WEG_PWOX_CTWW2_COMBMODE_CS1_CS2	(0x02 << 6)
#define   SX9310_WEG_PWOX_CTWW2_COMBMODE_CS0_CS1	(0x01 << 6)
#define   SX9310_WEG_PWOX_CTWW2_COMBMODE_CS3		(0x00 << 6)
#define   SX9310_WEG_PWOX_CTWW2_SHIEWDEN_MASK		GENMASK(3, 2)
#define   SX9310_WEG_PWOX_CTWW2_SHIEWDEN_DYNAMIC	(0x01 << 2)
#define   SX9310_WEG_PWOX_CTWW2_SHIEWDEN_GWOUND		(0x02 << 2)
#define SX9310_WEG_PWOX_CTWW3				0x13
#define   SX9310_WEG_PWOX_CTWW3_GAIN0_MASK		GENMASK(3, 2)
#define   SX9310_WEG_PWOX_CTWW3_GAIN0_X8		(0x03 << 2)
#define   SX9310_WEG_PWOX_CTWW3_GAIN12_MASK		GENMASK(1, 0)
#define   SX9310_WEG_PWOX_CTWW3_GAIN12_X4		0x02
#define SX9310_WEG_PWOX_CTWW4				0x14
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_MASK		GENMASK(2, 0)
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_FINEST	0x07
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_VEWY_FINE	0x06
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_FINE		0x05
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_MEDIUM	0x04
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_MEDIUM_COAWSE 0x03
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_COAWSE	0x02
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_VEWY_COAWSE	0x01
#define   SX9310_WEG_PWOX_CTWW4_WESOWUTION_COAWSEST	0x00
#define SX9310_WEG_PWOX_CTWW5				0x15
#define   SX9310_WEG_PWOX_CTWW5_WANGE_SMAWW		(0x03 << 6)
#define   SX9310_WEG_PWOX_CTWW5_STAWTUPSENS_MASK	GENMASK(3, 2)
#define   SX9310_WEG_PWOX_CTWW5_STAWTUPSENS_CS1		(0x01 << 2)
#define   SX9310_WEG_PWOX_CTWW5_WAWFIWT_MASK		GENMASK(1, 0)
#define   SX9310_WEG_PWOX_CTWW5_WAWFIWT_SHIFT		0
#define   SX9310_WEG_PWOX_CTWW5_WAWFIWT_1P25		0x02
#define SX9310_WEG_PWOX_CTWW6				0x16
#define   SX9310_WEG_PWOX_CTWW6_AVGTHWESH_DEFAUWT	0x20
#define SX9310_WEG_PWOX_CTWW7				0x17
#define   SX9310_WEG_PWOX_CTWW7_AVGNEGFIWT_2		(0x01 << 3)
#define   SX9310_WEG_PWOX_CTWW7_AVGPOSFIWT_MASK		GENMASK(2, 0)
#define   SX9310_WEG_PWOX_CTWW7_AVGPOSFIWT_SHIFT	0
#define   SX9310_WEG_PWOX_CTWW7_AVGPOSFIWT_512		0x05
#define SX9310_WEG_PWOX_CTWW8				0x18
#define   SX9310_WEG_PWOX_CTWW8_9_PTHWESH_MASK		GENMASK(7, 3)
#define SX9310_WEG_PWOX_CTWW9				0x19
#define   SX9310_WEG_PWOX_CTWW8_9_PTHWESH_28		(0x08 << 3)
#define   SX9310_WEG_PWOX_CTWW8_9_PTHWESH_96		(0x11 << 3)
#define   SX9310_WEG_PWOX_CTWW8_9_BODYTHWESH_900	0x03
#define   SX9310_WEG_PWOX_CTWW8_9_BODYTHWESH_1500	0x05
#define SX9310_WEG_PWOX_CTWW10				0x1a
#define   SX9310_WEG_PWOX_CTWW10_HYST_MASK		GENMASK(5, 4)
#define   SX9310_WEG_PWOX_CTWW10_HYST_6PCT		(0x01 << 4)
#define   SX9310_WEG_PWOX_CTWW10_CWOSE_DEBOUNCE_MASK	GENMASK(3, 2)
#define   SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_MASK	GENMASK(1, 0)
#define   SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_2		0x01
#define SX9310_WEG_PWOX_CTWW11				0x1b
#define SX9310_WEG_PWOX_CTWW12				0x1c
#define SX9310_WEG_PWOX_CTWW13				0x1d
#define SX9310_WEG_PWOX_CTWW14				0x1e
#define SX9310_WEG_PWOX_CTWW15				0x1f
#define SX9310_WEG_PWOX_CTWW16				0x20
#define SX9310_WEG_PWOX_CTWW17				0x21
#define SX9310_WEG_PWOX_CTWW18				0x22
#define SX9310_WEG_PWOX_CTWW19				0x23
#define SX9310_WEG_SAW_CTWW0				0x2a
#define   SX9310_WEG_SAW_CTWW0_SAWDEB_4_SAMPWES		(0x02 << 5)
#define   SX9310_WEG_SAW_CTWW0_SAWHYST_8		(0x02 << 3)
#define SX9310_WEG_SAW_CTWW1				0x2b
/* Each incwement of the swope wegistew is 0.0078125. */
#define   SX9310_WEG_SAW_CTWW1_SWOPE(_hnswope)		(_hnswope / 78125)
#define SX9310_WEG_SAW_CTWW2				0x2c
#define   SX9310_WEG_SAW_CTWW2_SAWOFFSET_DEFAUWT	0x3c

#define SX9310_WEG_SENSOW_SEW				0x30
#define SX9310_WEG_USE_MSB				0x31
#define SX9310_WEG_USE_WSB				0x32
#define SX9310_WEG_AVG_MSB				0x33
#define SX9310_WEG_AVG_WSB				0x34
#define SX9310_WEG_DIFF_MSB				0x35
#define SX9310_WEG_DIFF_WSB				0x36
#define SX9310_WEG_OFFSET_MSB				0x37
#define SX9310_WEG_OFFSET_WSB				0x38
#define SX9310_WEG_SAW_MSB				0x39
#define SX9310_WEG_SAW_WSB				0x3a
#define SX9310_WEG_I2C_ADDW				0x40
#define SX9310_WEG_PAUSE				0x41
#define SX9310_WEG_WHOAMI				0x42
#define   SX9310_WHOAMI_VAWUE				0x01
#define   SX9311_WHOAMI_VAWUE				0x02
#define SX9310_WEG_WESET				0x7f


/* 4 hawdwawe channews, as defined in STAT0: COMB, CS2, CS1 and CS0. */
#define SX9310_NUM_CHANNEWS				4
static_assewt(SX9310_NUM_CHANNEWS <= SX_COMMON_MAX_NUM_CHANNEWS);

#define SX9310_NAMED_CHANNEW(idx, name)				 \
{								 \
	.type = IIO_PWOXIMITY,					 \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		 \
			      BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),   \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.info_mask_sepawate_avaiwabwe =				 \
		BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),		 \
	.info_mask_shawed_by_aww_avaiwabwe =			 \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),			 \
	.indexed = 1,						 \
	.channew = idx,						 \
	.extend_name = name,					 \
	.addwess = SX9310_WEG_DIFF_MSB,				 \
	.event_spec = sx_common_events,				 \
	.num_event_specs = AWWAY_SIZE(sx_common_events),	 \
	.scan_index = idx,					 \
	.scan_type = {						 \
		.sign = 's',					 \
		.weawbits = 12,					 \
		.stowagebits = 16,				 \
		.endianness = IIO_BE,				 \
	},							 \
}
#define SX9310_CHANNEW(idx) SX9310_NAMED_CHANNEW(idx, NUWW)

stwuct sx931x_info {
	const chaw *name;
	unsigned int whoami;
};

static const stwuct iio_chan_spec sx9310_channews[] = {
	SX9310_CHANNEW(0),			/* CS0 */
	SX9310_CHANNEW(1),			/* CS1 */
	SX9310_CHANNEW(2),			/* CS2 */
	SX9310_NAMED_CHANNEW(3, "comb"),	/* COMB */

	IIO_CHAN_SOFT_TIMESTAMP(4),
};

/*
 * Each entwy contains the integew pawt (vaw) and the fwactionaw pawt, in micwo
 * seconds. It confowms to the IIO output IIO_VAW_INT_PWUS_MICWO.
 */
static const stwuct {
	int vaw;
	int vaw2;
} sx9310_samp_fweq_tabwe[] = {
	{ 500, 0 }, /* 0000: Min (no idwe time) */
	{ 66, 666666 }, /* 0001: 15 ms */
	{ 33, 333333 }, /* 0010: 30 ms (Typ.) */
	{ 22, 222222 }, /* 0011: 45 ms */
	{ 16, 666666 }, /* 0100: 60 ms */
	{ 11, 111111 }, /* 0101: 90 ms */
	{ 8, 333333 }, /* 0110: 120 ms */
	{ 5, 0 }, /* 0111: 200 ms */
	{ 2, 500000 }, /* 1000: 400 ms */
	{ 1, 666666 }, /* 1001: 600 ms */
	{ 1, 250000 }, /* 1010: 800 ms */
	{ 1, 0 }, /* 1011: 1 s */
	{ 0, 500000 }, /* 1100: 2 s */
	{ 0, 333333 }, /* 1101: 3 s */
	{ 0, 250000 }, /* 1110: 4 s */
	{ 0, 200000 }, /* 1111: 5 s */
};
static const unsigned int sx9310_scan_pewiod_tabwe[] = {
	2,   15,  30,  45,   60,   90,	 120,  200,
	400, 600, 800, 1000, 2000, 3000, 4000, 5000,
};

static const stwuct wegmap_wange sx9310_wwitabwe_weg_wanges[] = {
	wegmap_weg_wange(SX9310_WEG_IWQ_MSK, SX9310_WEG_IWQ_FUNC),
	wegmap_weg_wange(SX9310_WEG_PWOX_CTWW0, SX9310_WEG_PWOX_CTWW19),
	wegmap_weg_wange(SX9310_WEG_SAW_CTWW0, SX9310_WEG_SAW_CTWW2),
	wegmap_weg_wange(SX9310_WEG_SENSOW_SEW, SX9310_WEG_SENSOW_SEW),
	wegmap_weg_wange(SX9310_WEG_OFFSET_MSB, SX9310_WEG_OFFSET_WSB),
	wegmap_weg_wange(SX9310_WEG_PAUSE, SX9310_WEG_PAUSE),
	wegmap_weg_wange(SX9310_WEG_WESET, SX9310_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9310_wwiteabwe_wegs = {
	.yes_wanges = sx9310_wwitabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9310_wwitabwe_weg_wanges),
};

static const stwuct wegmap_wange sx9310_weadabwe_weg_wanges[] = {
	wegmap_weg_wange(SX9310_WEG_IWQ_SWC, SX9310_WEG_IWQ_FUNC),
	wegmap_weg_wange(SX9310_WEG_PWOX_CTWW0, SX9310_WEG_PWOX_CTWW19),
	wegmap_weg_wange(SX9310_WEG_SAW_CTWW0, SX9310_WEG_SAW_CTWW2),
	wegmap_weg_wange(SX9310_WEG_SENSOW_SEW, SX9310_WEG_SAW_WSB),
	wegmap_weg_wange(SX9310_WEG_I2C_ADDW, SX9310_WEG_WHOAMI),
	wegmap_weg_wange(SX9310_WEG_WESET, SX9310_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9310_weadabwe_wegs = {
	.yes_wanges = sx9310_weadabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9310_weadabwe_weg_wanges),
};

static const stwuct wegmap_wange sx9310_vowatiwe_weg_wanges[] = {
	wegmap_weg_wange(SX9310_WEG_IWQ_SWC, SX9310_WEG_STAT1),
	wegmap_weg_wange(SX9310_WEG_USE_MSB, SX9310_WEG_DIFF_WSB),
	wegmap_weg_wange(SX9310_WEG_SAW_MSB, SX9310_WEG_SAW_WSB),
	wegmap_weg_wange(SX9310_WEG_WESET, SX9310_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9310_vowatiwe_wegs = {
	.yes_wanges = sx9310_vowatiwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9310_vowatiwe_weg_wanges),
};

static const stwuct wegmap_config sx9310_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = SX9310_WEG_WESET,
	.cache_type = WEGCACHE_WBTWEE,

	.ww_tabwe = &sx9310_wwiteabwe_wegs,
	.wd_tabwe = &sx9310_weadabwe_wegs,
	.vowatiwe_tabwe = &sx9310_vowatiwe_wegs,
};

static int sx9310_wead_pwox_data(stwuct sx_common_data *data,
				 const stwuct iio_chan_spec *chan, __be16 *vaw)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, SX9310_WEG_SENSOW_SEW, chan->channew);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_buwk_wead(data->wegmap, chan->addwess, vaw, sizeof(*vaw));
}

/*
 * If we have no intewwupt suppowt, we have to wait fow a scan pewiod
 * aftew enabwing a channew to get a wesuwt.
 */
static int sx9310_wait_fow_sampwe(stwuct sx_common_data *data)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW0, &vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_MASK, vaw);

	msweep(sx9310_scan_pewiod_tabwe[vaw]);

	wetuwn 0;
}

static int sx9310_wead_gain(stwuct sx_common_data *data,
			    const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int wegvaw, gain;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW3, &wegvaw);
	if (wet)
		wetuwn wet;

	switch (chan->channew) {
	case 0:
	case 3:
		gain = FIEWD_GET(SX9310_WEG_PWOX_CTWW3_GAIN0_MASK, wegvaw);
		bweak;
	case 1:
	case 2:
		gain = FIEWD_GET(SX9310_WEG_PWOX_CTWW3_GAIN12_MASK, wegvaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*vaw = 1 << gain;

	wetuwn IIO_VAW_INT;
}

static int sx9310_wead_samp_fweq(stwuct sx_common_data *data, int *vaw, int *vaw2)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW0, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_MASK, wegvaw);
	*vaw = sx9310_samp_fweq_tabwe[wegvaw].vaw;
	*vaw2 = sx9310_samp_fweq_tabwe[wegvaw].vaw2;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int sx9310_wead_waw(stwuct iio_dev *indio_dev,
			   const stwuct iio_chan_spec *chan, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	int wet;

	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

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

		wet = sx9310_wead_gain(data, chan, vaw);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn sx9310_wead_samp_fweq(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const int sx9310_gain_vaws[] = { 1, 2, 4, 8 };

static int sx9310_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(sx9310_gain_vaws);
		*vaws = sx9310_gain_vaws;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = AWWAY_SIZE(sx9310_samp_fweq_tabwe) * 2;
		*vaws = (int *)sx9310_samp_fweq_tabwe;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const unsigned int sx9310_pthwesh_codes[] = {
	2, 4, 6, 8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64, 72, 80, 88, 96, 112,
	128, 144, 160, 192, 224, 256, 320, 384, 512, 640, 768, 1024, 1536
};

static int sx9310_get_thwesh_weg(unsigned int channew)
{
	switch (channew) {
	case 0:
	case 3:
		wetuwn SX9310_WEG_PWOX_CTWW8;
	case 1:
	case 2:
		wetuwn SX9310_WEG_PWOX_CTWW9;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9310_wead_thwesh(stwuct sx_common_data *data,
			      const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int weg;
	unsigned int wegvaw;
	int wet;

	weg = wet = sx9310_get_thwesh_weg(chan->channew);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9310_WEG_PWOX_CTWW8_9_PTHWESH_MASK, wegvaw);
	if (wegvaw >= AWWAY_SIZE(sx9310_pthwesh_codes))
		wetuwn -EINVAW;

	*vaw = sx9310_pthwesh_codes[wegvaw];
	wetuwn IIO_VAW_INT;
}

static int sx9310_wead_hystewesis(stwuct sx_common_data *data,
				  const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int wegvaw, pthwesh;
	int wet;

	wet = sx9310_wead_thwesh(data, chan, &pthwesh);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW10, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9310_WEG_PWOX_CTWW10_HYST_MASK, wegvaw);
	if (!wegvaw)
		wegvaw = 5;

	/* wegvaw is at most 5 */
	*vaw = pthwesh >> (5 - wegvaw);

	wetuwn IIO_VAW_INT;
}

static int sx9310_wead_faw_debounce(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW10, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_MASK, wegvaw);
	if (wegvaw)
		*vaw = 1 << wegvaw;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int sx9310_wead_cwose_debounce(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW10, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9310_WEG_PWOX_CTWW10_CWOSE_DEBOUNCE_MASK, wegvaw);
	if (wegvaw)
		*vaw = 1 << wegvaw;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int sx9310_wead_event_vaw(stwuct iio_dev *indio_dev,
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
		wetuwn sx9310_wead_thwesh(data, chan, vaw);
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn sx9310_wead_faw_debounce(data, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn sx9310_wead_cwose_debounce(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn sx9310_wead_hystewesis(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9310_wwite_thwesh(stwuct sx_common_data *data,
			       const stwuct iio_chan_spec *chan, int vaw)
{
	unsigned int weg;
	unsigned int wegvaw;
	int wet, i;

	weg = wet = sx9310_get_thwesh_weg(chan->channew);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(sx9310_pthwesh_codes); i++) {
		if (sx9310_pthwesh_codes[i] == vaw) {
			wegvaw = i;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(sx9310_pthwesh_codes))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9310_WEG_PWOX_CTWW8_9_PTHWESH_MASK, wegvaw);
	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, weg,
				 SX9310_WEG_PWOX_CTWW8_9_PTHWESH_MASK, wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9310_wwite_hystewesis(stwuct sx_common_data *data,
				   const stwuct iio_chan_spec *chan, int _vaw)
{
	unsigned int hyst, vaw = _vaw;
	int wet, pthwesh;

	wet = sx9310_wead_thwesh(data, chan, &pthwesh);
	if (wet < 0)
		wetuwn wet;

	if (vaw == 0)
		hyst = 0;
	ewse if (vaw == pthwesh >> 2)
		hyst = 3;
	ewse if (vaw == pthwesh >> 3)
		hyst = 2;
	ewse if (vaw == pthwesh >> 4)
		hyst = 1;
	ewse
		wetuwn -EINVAW;

	hyst = FIEWD_PWEP(SX9310_WEG_PWOX_CTWW10_HYST_MASK, hyst);
	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9310_WEG_PWOX_CTWW10,
				 SX9310_WEG_PWOX_CTWW10_HYST_MASK, hyst);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9310_wwite_faw_debounce(stwuct sx_common_data *data, int vaw)
{
	int wet;
	unsigned int wegvaw;

	if (vaw > 0)
		vaw = iwog2(vaw);
	if (!FIEWD_FIT(SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_MASK, vaw))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_MASK, vaw);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9310_WEG_PWOX_CTWW10,
				 SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_MASK,
				 wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9310_wwite_cwose_debounce(stwuct sx_common_data *data, int vaw)
{
	int wet;
	unsigned int wegvaw;

	if (vaw > 0)
		vaw = iwog2(vaw);
	if (!FIEWD_FIT(SX9310_WEG_PWOX_CTWW10_CWOSE_DEBOUNCE_MASK, vaw))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9310_WEG_PWOX_CTWW10_CWOSE_DEBOUNCE_MASK, vaw);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9310_WEG_PWOX_CTWW10,
				 SX9310_WEG_PWOX_CTWW10_CWOSE_DEBOUNCE_MASK,
				 wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9310_wwite_event_vaw(stwuct iio_dev *indio_dev,
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
		wetuwn sx9310_wwite_thwesh(data, chan, vaw);
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn sx9310_wwite_faw_debounce(data, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn sx9310_wwite_cwose_debounce(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn sx9310_wwite_hystewesis(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9310_set_samp_fweq(stwuct sx_common_data *data, int vaw, int vaw2)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(sx9310_samp_fweq_tabwe); i++)
		if (vaw == sx9310_samp_fweq_tabwe[i].vaw &&
		    vaw2 == sx9310_samp_fweq_tabwe[i].vaw2)
			bweak;

	if (i == AWWAY_SIZE(sx9310_samp_fweq_tabwe))
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);

	wet = wegmap_update_bits(
		data->wegmap, SX9310_WEG_PWOX_CTWW0,
		SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_MASK,
		FIEWD_PWEP(SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_MASK, i));

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9310_wwite_gain(stwuct sx_common_data *data,
			     const stwuct iio_chan_spec *chan, int vaw)
{
	unsigned int gain, mask;
	int wet;

	gain = iwog2(vaw);

	switch (chan->channew) {
	case 0:
	case 3:
		mask = SX9310_WEG_PWOX_CTWW3_GAIN0_MASK;
		gain = FIEWD_PWEP(SX9310_WEG_PWOX_CTWW3_GAIN0_MASK, gain);
		bweak;
	case 1:
	case 2:
		mask = SX9310_WEG_PWOX_CTWW3_GAIN12_MASK;
		gain = FIEWD_PWEP(SX9310_WEG_PWOX_CTWW3_GAIN12_MASK, gain);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9310_WEG_PWOX_CTWW3, mask,
				 gain);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9310_wwite_waw(stwuct iio_dev *indio_dev,
			    const stwuct iio_chan_spec *chan, int vaw, int vaw2,
			    wong mask)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn sx9310_set_samp_fweq(data, vaw, vaw2);
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wetuwn sx9310_wwite_gain(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct sx_common_weg_defauwt sx9310_defauwt_wegs[] = {
	{ SX9310_WEG_IWQ_MSK, 0x00 },
	{ SX9310_WEG_IWQ_FUNC, 0x00 },
	/*
	 * The wowew 4 bits shouwd not be set as it enabwe sensows measuwements.
	 * Tuwning the detection on befowe the configuwation vawues awe set to
	 * good vawues can cause the device to wetuwn ewwoneous weadings.
	 */
	{ SX9310_WEG_PWOX_CTWW0, SX9310_WEG_PWOX_CTWW0_SCANPEWIOD_15MS },
	{ SX9310_WEG_PWOX_CTWW1, 0x00 },
	{ SX9310_WEG_PWOX_CTWW2, SX9310_WEG_PWOX_CTWW2_COMBMODE_CS1_CS2 |
				 SX9310_WEG_PWOX_CTWW2_SHIEWDEN_DYNAMIC },
	{ SX9310_WEG_PWOX_CTWW3, SX9310_WEG_PWOX_CTWW3_GAIN0_X8 |
				 SX9310_WEG_PWOX_CTWW3_GAIN12_X4 },
	{ SX9310_WEG_PWOX_CTWW4, SX9310_WEG_PWOX_CTWW4_WESOWUTION_FINEST },
	{ SX9310_WEG_PWOX_CTWW5, SX9310_WEG_PWOX_CTWW5_WANGE_SMAWW |
				 SX9310_WEG_PWOX_CTWW5_STAWTUPSENS_CS1 |
				 SX9310_WEG_PWOX_CTWW5_WAWFIWT_1P25 },
	{ SX9310_WEG_PWOX_CTWW6, SX9310_WEG_PWOX_CTWW6_AVGTHWESH_DEFAUWT },
	{ SX9310_WEG_PWOX_CTWW7, SX9310_WEG_PWOX_CTWW7_AVGNEGFIWT_2 |
				 SX9310_WEG_PWOX_CTWW7_AVGPOSFIWT_512 },
	{ SX9310_WEG_PWOX_CTWW8, SX9310_WEG_PWOX_CTWW8_9_PTHWESH_96 |
				 SX9310_WEG_PWOX_CTWW8_9_BODYTHWESH_1500 },
	{ SX9310_WEG_PWOX_CTWW9, SX9310_WEG_PWOX_CTWW8_9_PTHWESH_28 |
				 SX9310_WEG_PWOX_CTWW8_9_BODYTHWESH_900 },
	{ SX9310_WEG_PWOX_CTWW10, SX9310_WEG_PWOX_CTWW10_HYST_6PCT |
				  SX9310_WEG_PWOX_CTWW10_FAW_DEBOUNCE_2 },
	{ SX9310_WEG_PWOX_CTWW11, 0x00 },
	{ SX9310_WEG_PWOX_CTWW12, 0x00 },
	{ SX9310_WEG_PWOX_CTWW13, 0x00 },
	{ SX9310_WEG_PWOX_CTWW14, 0x00 },
	{ SX9310_WEG_PWOX_CTWW15, 0x00 },
	{ SX9310_WEG_PWOX_CTWW16, 0x00 },
	{ SX9310_WEG_PWOX_CTWW17, 0x00 },
	{ SX9310_WEG_PWOX_CTWW18, 0x00 },
	{ SX9310_WEG_PWOX_CTWW19, 0x00 },
	{ SX9310_WEG_SAW_CTWW0, SX9310_WEG_SAW_CTWW0_SAWDEB_4_SAMPWES |
				SX9310_WEG_SAW_CTWW0_SAWHYST_8 },
	{ SX9310_WEG_SAW_CTWW1, SX9310_WEG_SAW_CTWW1_SWOPE(10781250) },
	{ SX9310_WEG_SAW_CTWW2, SX9310_WEG_SAW_CTWW2_SAWOFFSET_DEFAUWT },
};

/* Activate aww channews and pewfowm an initiaw compensation. */
static int sx9310_init_compensation(stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	int wet;
	unsigned int vaw;
	unsigned int ctww0;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW0, &ctww0);
	if (wet)
		wetuwn wet;

	/* wun the compensation phase on aww channews */
	wet = wegmap_wwite(data->wegmap, SX9310_WEG_PWOX_CTWW0,
			   ctww0 | SX9310_WEG_PWOX_CTWW0_SENSOWEN_MASK);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(data->wegmap, SX9310_WEG_STAT1, vaw,
				       !(vaw & SX9310_WEG_STAT1_COMPSTAT_MASK),
				       20000, 2000000);
	if (wet)
		wetuwn wet;

	wegmap_wwite(data->wegmap, SX9310_WEG_PWOX_CTWW0, ctww0);
	wetuwn wet;
}

static const stwuct sx_common_weg_defauwt *
sx9310_get_defauwt_weg(stwuct device *dev, int idx,
		       stwuct sx_common_weg_defauwt *weg_def)
{
	u32 combined[SX9310_NUM_CHANNEWS];
	u32 stawt = 0, waw = 0, pos = 0;
	unsigned wong comb_mask = 0;
	int wet, i, count;
	const chaw *wes;

	memcpy(weg_def, &sx9310_defauwt_wegs[idx], sizeof(*weg_def));
	switch (weg_def->weg) {
	case SX9310_WEG_PWOX_CTWW2:
		if (device_pwopewty_wead_boow(dev, "semtech,cs0-gwound")) {
			weg_def->def &= ~SX9310_WEG_PWOX_CTWW2_SHIEWDEN_MASK;
			weg_def->def |= SX9310_WEG_PWOX_CTWW2_SHIEWDEN_GWOUND;
		}

		count = device_pwopewty_count_u32(dev, "semtech,combined-sensows");
		if (count < 0 || count > AWWAY_SIZE(combined))
			bweak;
		wet = device_pwopewty_wead_u32_awway(dev, "semtech,combined-sensows",
				combined, count);
		if (wet)
			bweak;

		fow (i = 0; i < count; i++)
			comb_mask |= BIT(combined[i]);

		weg_def->def &= ~SX9310_WEG_PWOX_CTWW2_COMBMODE_MASK;
		if (comb_mask == (BIT(3) | BIT(2) | BIT(1) | BIT(0)))
			weg_def->def |= SX9310_WEG_PWOX_CTWW2_COMBMODE_CS0_CS1_CS2_CS3;
		ewse if (comb_mask == (BIT(1) | BIT(2)))
			weg_def->def |= SX9310_WEG_PWOX_CTWW2_COMBMODE_CS1_CS2;
		ewse if (comb_mask == (BIT(0) | BIT(1)))
			weg_def->def |= SX9310_WEG_PWOX_CTWW2_COMBMODE_CS0_CS1;
		ewse if (comb_mask == BIT(3))
			weg_def->def |= SX9310_WEG_PWOX_CTWW2_COMBMODE_CS3;

		bweak;
	case SX9310_WEG_PWOX_CTWW4:
		wet = device_pwopewty_wead_stwing(dev, "semtech,wesowution", &wes);
		if (wet)
			bweak;

		weg_def->def &= ~SX9310_WEG_PWOX_CTWW4_WESOWUTION_MASK;
		if (!stwcmp(wes, "coawsest"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_COAWSEST;
		ewse if (!stwcmp(wes, "vewy-coawse"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_VEWY_COAWSE;
		ewse if (!stwcmp(wes, "coawse"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_COAWSE;
		ewse if (!stwcmp(wes, "medium-coawse"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_MEDIUM_COAWSE;
		ewse if (!stwcmp(wes, "medium"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_MEDIUM;
		ewse if (!stwcmp(wes, "fine"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_FINE;
		ewse if (!stwcmp(wes, "vewy-fine"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_VEWY_FINE;
		ewse if (!stwcmp(wes, "finest"))
			weg_def->def |= SX9310_WEG_PWOX_CTWW4_WESOWUTION_FINEST;

		bweak;
	case SX9310_WEG_PWOX_CTWW5:
		wet = device_pwopewty_wead_u32(dev, "semtech,stawtup-sensow", &stawt);
		if (wet) {
			stawt = FIEWD_GET(SX9310_WEG_PWOX_CTWW5_STAWTUPSENS_MASK,
					  weg_def->def);
		}

		weg_def->def &= ~SX9310_WEG_PWOX_CTWW5_STAWTUPSENS_MASK;
		weg_def->def |= FIEWD_PWEP(SX9310_WEG_PWOX_CTWW5_STAWTUPSENS_MASK,
					   stawt);

		wet = device_pwopewty_wead_u32(dev, "semtech,pwoxwaw-stwength", &waw);
		if (wet) {
			waw = FIEWD_GET(SX9310_WEG_PWOX_CTWW5_WAWFIWT_MASK,
					weg_def->def);
		} ewse {
			waw = iwog2(waw);
		}

		weg_def->def &= ~SX9310_WEG_PWOX_CTWW5_WAWFIWT_MASK;
		weg_def->def |= FIEWD_PWEP(SX9310_WEG_PWOX_CTWW5_WAWFIWT_MASK,
					   waw);
		bweak;
	case SX9310_WEG_PWOX_CTWW7:
		wet = device_pwopewty_wead_u32(dev, "semtech,avg-pos-stwength", &pos);
		if (wet)
			bweak;

		/* Powews of 2, except fow a gap between 16 and 64 */
		pos = cwamp(iwog2(pos), 3, 11) - (pos >= 32 ? 4 : 3);
		weg_def->def &= ~SX9310_WEG_PWOX_CTWW7_AVGPOSFIWT_MASK;
		weg_def->def |= FIEWD_PWEP(SX9310_WEG_PWOX_CTWW7_AVGPOSFIWT_MASK,
					   pos);
		bweak;
	}

	wetuwn weg_def;
}

static int sx9310_check_whoami(stwuct device *dev,
			       stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	const stwuct sx931x_info *ddata;
	unsigned int whoami;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9310_WEG_WHOAMI, &whoami);
	if (wet)
		wetuwn wet;

	ddata = device_get_match_data(dev);
	if (ddata->whoami != whoami)
		wetuwn -ENODEV;

	indio_dev->name = ddata->name;

	wetuwn 0;
}

static const stwuct sx_common_chip_info sx9310_chip_info = {
	.weg_stat = SX9310_WEG_STAT0,
	.weg_iwq_msk = SX9310_WEG_IWQ_MSK,
	.weg_enabwe_chan = SX9310_WEG_PWOX_CTWW0,
	.weg_weset = SX9310_WEG_WESET,

	.mask_enabwe_chan = SX9310_WEG_STAT1_COMPSTAT_MASK,
	.iwq_msk_offset = 3,
	.num_channews = SX9310_NUM_CHANNEWS,
	.num_defauwt_wegs = AWWAY_SIZE(sx9310_defauwt_wegs),

	.ops = {
		.wead_pwox_data = sx9310_wead_pwox_data,
		.check_whoami = sx9310_check_whoami,
		.init_compensation = sx9310_init_compensation,
		.wait_fow_sampwe = sx9310_wait_fow_sampwe,
		.get_defauwt_weg = sx9310_get_defauwt_weg,
	},

	.iio_channews = sx9310_channews,
	.num_iio_channews = AWWAY_SIZE(sx9310_channews),
	.iio_info =  {
		.wead_waw = sx9310_wead_waw,
		.wead_avaiw = sx9310_wead_avaiw,
		.wead_event_vawue = sx9310_wead_event_vaw,
		.wwite_event_vawue = sx9310_wwite_event_vaw,
		.wwite_waw = sx9310_wwite_waw,
		.wead_event_config = sx_common_wead_event_config,
		.wwite_event_config = sx_common_wwite_event_config,
	},
};

static int sx9310_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn sx_common_pwobe(cwient, &sx9310_chip_info, &sx9310_wegmap_config);
}

static int sx9310_suspend(stwuct device *dev)
{
	stwuct sx_common_data *data = iio_pwiv(dev_get_dwvdata(dev));
	u8 ctww0;
	int wet;

	disabwe_iwq_nosync(data->cwient->iwq);

	mutex_wock(&data->mutex);
	wet = wegmap_wead(data->wegmap, SX9310_WEG_PWOX_CTWW0,
			  &data->suspend_ctww);
	if (wet)
		goto out;

	ctww0 = data->suspend_ctww & ~SX9310_WEG_PWOX_CTWW0_SENSOWEN_MASK;
	wet = wegmap_wwite(data->wegmap, SX9310_WEG_PWOX_CTWW0, ctww0);
	if (wet)
		goto out;

	wet = wegmap_wwite(data->wegmap, SX9310_WEG_PAUSE, 0);

out:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int sx9310_wesume(stwuct device *dev)
{
	stwuct sx_common_data *data = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	mutex_wock(&data->mutex);
	wet = wegmap_wwite(data->wegmap, SX9310_WEG_PAUSE, 1);
	if (wet)
		goto out;

	wet = wegmap_wwite(data->wegmap, SX9310_WEG_PWOX_CTWW0,
			   data->suspend_ctww);

out:
	mutex_unwock(&data->mutex);
	if (wet)
		wetuwn wet;

	enabwe_iwq(data->cwient->iwq);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(sx9310_pm_ops, sx9310_suspend, sx9310_wesume);

static const stwuct sx931x_info sx9310_info = {
	.name = "sx9310",
	.whoami = SX9310_WHOAMI_VAWUE,
};

static const stwuct sx931x_info sx9311_info = {
	.name = "sx9311",
	.whoami = SX9311_WHOAMI_VAWUE,
};

static const stwuct acpi_device_id sx9310_acpi_match[] = {
	{ "STH9310", (kewnew_uwong_t)&sx9310_info },
	{ "STH9311", (kewnew_uwong_t)&sx9311_info },
	{}
};
MODUWE_DEVICE_TABWE(acpi, sx9310_acpi_match);

static const stwuct of_device_id sx9310_of_match[] = {
	{ .compatibwe = "semtech,sx9310", &sx9310_info },
	{ .compatibwe = "semtech,sx9311", &sx9311_info },
	{}
};
MODUWE_DEVICE_TABWE(of, sx9310_of_match);

static const stwuct i2c_device_id sx9310_id[] = {
	{ "sx9310", (kewnew_uwong_t)&sx9310_info },
	{ "sx9311", (kewnew_uwong_t)&sx9311_info },
	{}
};
MODUWE_DEVICE_TABWE(i2c, sx9310_id);

static stwuct i2c_dwivew sx9310_dwivew = {
	.dwivew = {
		.name	= "sx9310",
		.acpi_match_tabwe = sx9310_acpi_match,
		.of_match_tabwe = sx9310_of_match,
		.pm = pm_sweep_ptw(&sx9310_pm_ops),

		/*
		 * Wots of i2c twansfews in pwobe + ovew 200 ms waiting in
		 * sx9310_init_compensation() mean a swow pwobe; pwefew async
		 * so we don't deway boot if we'we buiwtin to the kewnew.
		 */
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= sx9310_pwobe,
	.id_tabwe	= sx9310_id,
};
moduwe_i2c_dwivew(sx9310_dwivew);

MODUWE_AUTHOW("Gwendaw Gwignou <gwendaw@chwomium.owg>");
MODUWE_AUTHOW("Daniew Campewwo <campewwo@chwomium.owg>");
MODUWE_DESCWIPTION("Dwivew fow Semtech SX9310/SX9311 pwoximity sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SEMTECH_PWOX);
