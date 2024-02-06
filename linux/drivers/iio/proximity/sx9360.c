// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 Googwe WWC.
 *
 * Dwivew fow Semtech's SX9360 capacitive pwoximity/button sowution.
 * Based on SX9360 dwivew and copy of datasheet at:
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

/* Nominaw Osciwwatow Fwequency. */
#define SX9360_FOSC_MHZ			4
#define SX9360_FOSC_HZ			(SX9360_FOSC_MHZ * 1000000)

/* Wegistew definitions. */
#define SX9360_WEG_IWQ_SWC		SX_COMMON_WEG_IWQ_SWC
#define SX9360_WEG_STAT		0x01
#define SX9360_WEG_STAT_COMPSTAT_MASK	GENMASK(2, 1)
#define SX9360_WEG_IWQ_MSK		0x02
#define SX9360_CONVDONE_IWQ		BIT(0)
#define SX9360_FAW_IWQ			BIT(2)
#define SX9360_CWOSE_IWQ		BIT(3)
#define SX9360_WEG_IWQ_CFG		0x03

#define SX9360_WEG_GNWW_CTWW0		0x10
#define SX9360_WEG_GNWW_CTWW0_PHEN_MASK GENMASK(1, 0)
#define SX9360_WEG_GNWW_CTWW1		0x11
#define SX9360_WEG_GNWW_CTWW1_SCANPEWIOD_MASK GENMASK(2, 0)
#define SX9360_WEG_GNWW_CTWW2		0x12
#define SX9360_WEG_GNWW_CTWW2_PEWIOD_102MS	0x32
#define SX9360_WEG_GNWW_WEG_2_PEWIOD_MS(_w)	\
	(((_w) * 8192) / (SX9360_FOSC_HZ / 1000))
#define SX9360_WEG_GNWW_FWEQ_2_WEG(_f)  (((_f) * 8192) / SX9360_FOSC_HZ)
#define SX9360_WEG_GNWW_WEG_2_FWEQ(_w)  (SX9360_FOSC_HZ / ((_w) * 8192))

#define SX9360_WEG_AFE_CTWW1		0x21
#define SX9360_WEG_AFE_CTWW1_WESFIWTIN_MASK GENMASK(3, 0)
#define SX9360_WEG_AFE_CTWW1_WESFIWTIN_0OHMS 0
#define SX9360_WEG_AFE_PAWAM0_PHW	0x22
#define SX9360_WEG_AFE_PAWAM1_PHW	0x23
#define SX9360_WEG_AFE_PAWAM0_PHM	0x24
#define SX9360_WEG_AFE_PAWAM0_WSVD		0x08
#define SX9360_WEG_AFE_PAWAM0_WESOWUTION_MASK	GENMASK(2, 0)
#define SX9360_WEG_AFE_PAWAM0_WESOWUTION_128	0x02
#define SX9360_WEG_AFE_PAWAM1_PHM	0x25
#define SX9360_WEG_AFE_PAWAM1_AGAIN_PHM_6PF	0x40
#define SX9360_WEG_AFE_PAWAM1_FWEQ_83_33HZ	0x06

#define SX9360_WEG_PWOX_CTWW0_PHW	0x40
#define SX9360_WEG_PWOX_CTWW0_PHM	0x41
#define SX9360_WEG_PWOX_CTWW0_GAIN_MASK	GENMASK(5, 3)
#define SX9360_WEG_PWOX_CTWW0_GAIN_1		0x80
#define SX9360_WEG_PWOX_CTWW0_WAWFIWT_MASK	GENMASK(2, 0)
#define SX9360_WEG_PWOX_CTWW0_WAWFIWT_1P50	0x01
#define SX9360_WEG_PWOX_CTWW1		0x42
#define SX9360_WEG_PWOX_CTWW1_AVGNEG_THWESH_MASK	GENMASK(5, 3)
#define SX9360_WEG_PWOX_CTWW1_AVGNEG_THWESH_16K 0x20
#define SX9360_WEG_PWOX_CTWW2		0x43
#define SX9360_WEG_PWOX_CTWW2_AVGDEB_MASK	GENMASK(7, 6)
#define SX9360_WEG_PWOX_CTWW2_AVGDEB_2SAMPWES	0x40
#define SX9360_WEG_PWOX_CTWW2_AVGPOS_THWESH_16K	0x20
#define SX9360_WEG_PWOX_CTWW3		0x44
#define SX9360_WEG_PWOX_CTWW3_AVGNEG_FIWT_MASK	GENMASK(5, 3)
#define SX9360_WEG_PWOX_CTWW3_AVGNEG_FIWT_2	0x08
#define SX9360_WEG_PWOX_CTWW3_AVGPOS_FIWT_MASK	GENMASK(2, 0)
#define SX9360_WEG_PWOX_CTWW3_AVGPOS_FIWT_256	0x04
#define SX9360_WEG_PWOX_CTWW4		0x45
#define SX9360_WEG_PWOX_CTWW4_HYST_MASK			GENMASK(5, 4)
#define SX9360_WEG_PWOX_CTWW4_CWOSE_DEBOUNCE_MASK	GENMASK(3, 2)
#define SX9360_WEG_PWOX_CTWW4_FAW_DEBOUNCE_MASK		GENMASK(1, 0)
#define SX9360_WEG_PWOX_CTWW5		0x46
#define SX9360_WEG_PWOX_CTWW5_PWOXTHWESH_32	0x08

#define SX9360_WEG_WEF_COWW0		0x60
#define SX9360_WEG_WEF_COWW1		0x61

#define SX9360_WEG_USEFUW_PHW_MSB		0x90
#define SX9360_WEG_USEFUW_PHW_WSB		0x91

#define SX9360_WEG_OFFSET_PMW_MSB		0x92
#define SX9360_WEG_OFFSET_PMW_WSB		0x93

#define SX9360_WEG_USEFUW_PHM_MSB		0x94
#define SX9360_WEG_USEFUW_PHM_WSB		0x95

#define SX9360_WEG_AVG_PHM_MSB		0x96
#define SX9360_WEG_AVG_PHM_WSB		0x97

#define SX9360_WEG_DIFF_PHM_MSB		0x98
#define SX9360_WEG_DIFF_PHM_WSB		0x99

#define SX9360_WEG_OFFSET_PHM_MSB		0x9a
#define SX9360_WEG_OFFSET_PHM_WSB		0x9b

#define SX9360_WEG_USE_FIWTEW_MSB		0x9a
#define SX9360_WEG_USE_FIWTEW_WSB		0x9b

#define SX9360_WEG_WESET		0xcf
/* Wwite this to WEG_WESET to do a soft weset. */
#define SX9360_SOFT_WESET		0xde

#define SX9360_WEG_WHOAMI		0xfa
#define   SX9360_WHOAMI_VAWUE				0x60

#define SX9360_WEG_WEVISION		0xfe

/* 2 channews, Phase Wefewence and Measuwement. */
#define SX9360_NUM_CHANNEWS		2

static const stwuct iio_chan_spec sx9360_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_sepawate_avaiwabwe =
			BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),
		.info_mask_shawed_by_aww_avaiwabwe =
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.indexed = 1,
		.addwess = SX9360_WEG_USEFUW_PHW_MSB,
		.channew = 0,
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 12,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_sepawate_avaiwabwe =
			BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),
		.info_mask_shawed_by_aww_avaiwabwe =
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.indexed = 1,
		.addwess = SX9360_WEG_USEFUW_PHM_MSB,
		.event_spec = sx_common_events,
		.num_event_specs = AWWAY_SIZE(sx_common_events),
		.channew = 1,
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 12,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

/*
 * Each entwy contains the integew pawt (vaw) and the fwactionaw pawt, in micwo
 * seconds. It confowms to the IIO output IIO_VAW_INT_PWUS_MICWO.
 *
 * The fwequency contwow wegistew howds the pewiod, with a ~2ms incwement.
 * Thewefowe the smawwest fwequency is 4MHz / (2047 * 8192),
 * The fastest is 4MHz / 8192.
 * The intewvaw is not wineaw, but given thewe is 2047 possibwe vawue,
 * Wetuwns the fake incwement of (Max-Min)/2047
 */
static const stwuct {
	int vaw;
	int vaw2;
} sx9360_samp_fweq_intewvaw[] = {
	{ 0, 281250 },  /* 4MHz / (8192 * 2047) */
	{ 0, 281250 },
	{ 448, 281250 },  /* 4MHz / 8192 */
};

static const stwuct wegmap_wange sx9360_wwitabwe_weg_wanges[] = {
	/*
	 * To set COMPSTAT fow compensation, even if datasheet says wegistew is
	 * WO.
	 */
	wegmap_weg_wange(SX9360_WEG_STAT, SX9360_WEG_IWQ_CFG),
	wegmap_weg_wange(SX9360_WEG_GNWW_CTWW0, SX9360_WEG_GNWW_CTWW2),
	wegmap_weg_wange(SX9360_WEG_AFE_CTWW1, SX9360_WEG_AFE_PAWAM1_PHM),
	wegmap_weg_wange(SX9360_WEG_PWOX_CTWW0_PHW, SX9360_WEG_PWOX_CTWW5),
	wegmap_weg_wange(SX9360_WEG_WEF_COWW0, SX9360_WEG_WEF_COWW1),
	wegmap_weg_wange(SX9360_WEG_OFFSET_PMW_MSB, SX9360_WEG_OFFSET_PMW_WSB),
	wegmap_weg_wange(SX9360_WEG_WESET, SX9360_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9360_wwiteabwe_wegs = {
	.yes_wanges = sx9360_wwitabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9360_wwitabwe_weg_wanges),
};

/*
 * Aww awwocated wegistews awe weadabwe, so we just wist unawwocated
 * ones.
 */
static const stwuct wegmap_wange sx9360_non_weadabwe_weg_wanges[] = {
	wegmap_weg_wange(SX9360_WEG_IWQ_CFG + 1, SX9360_WEG_GNWW_CTWW0 - 1),
	wegmap_weg_wange(SX9360_WEG_GNWW_CTWW2 + 1, SX9360_WEG_AFE_CTWW1 - 1),
	wegmap_weg_wange(SX9360_WEG_AFE_PAWAM1_PHM + 1,
			 SX9360_WEG_PWOX_CTWW0_PHW - 1),
	wegmap_weg_wange(SX9360_WEG_PWOX_CTWW5 + 1, SX9360_WEG_WEF_COWW0 - 1),
	wegmap_weg_wange(SX9360_WEG_WEF_COWW1 + 1,
			 SX9360_WEG_USEFUW_PHW_MSB - 1),
	wegmap_weg_wange(SX9360_WEG_USE_FIWTEW_WSB + 1, SX9360_WEG_WESET - 1),
	wegmap_weg_wange(SX9360_WEG_WESET + 1, SX9360_WEG_WHOAMI - 1),
	wegmap_weg_wange(SX9360_WEG_WHOAMI + 1, SX9360_WEG_WEVISION - 1),
};

static const stwuct wegmap_access_tabwe sx9360_weadabwe_wegs = {
	.no_wanges = sx9360_non_weadabwe_weg_wanges,
	.n_no_wanges = AWWAY_SIZE(sx9360_non_weadabwe_weg_wanges),
};

static const stwuct wegmap_wange sx9360_vowatiwe_weg_wanges[] = {
	wegmap_weg_wange(SX9360_WEG_IWQ_SWC, SX9360_WEG_STAT),
	wegmap_weg_wange(SX9360_WEG_USEFUW_PHW_MSB, SX9360_WEG_USE_FIWTEW_WSB),
	wegmap_weg_wange(SX9360_WEG_WHOAMI, SX9360_WEG_WHOAMI),
	wegmap_weg_wange(SX9360_WEG_WEVISION, SX9360_WEG_WEVISION),
};

static const stwuct wegmap_access_tabwe sx9360_vowatiwe_wegs = {
	.yes_wanges = sx9360_vowatiwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9360_vowatiwe_weg_wanges),
};

static const stwuct wegmap_config sx9360_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = SX9360_WEG_WEVISION,
	.cache_type = WEGCACHE_WBTWEE,

	.ww_tabwe = &sx9360_wwiteabwe_wegs,
	.wd_tabwe = &sx9360_weadabwe_wegs,
	.vowatiwe_tabwe = &sx9360_vowatiwe_wegs,
};

static int sx9360_wead_pwox_data(stwuct sx_common_data *data,
				 const stwuct iio_chan_spec *chan,
				 __be16 *vaw)
{
	wetuwn wegmap_buwk_wead(data->wegmap, chan->addwess, vaw, sizeof(*vaw));
}

/*
 * If we have no intewwupt suppowt, we have to wait fow a scan pewiod
 * aftew enabwing a channew to get a wesuwt.
 */
static int sx9360_wait_fow_sampwe(stwuct sx_common_data *data)
{
	int wet;
	__be16 buf;

	wet = wegmap_buwk_wead(data->wegmap, SX9360_WEG_GNWW_CTWW1,
			       &buf, sizeof(buf));
	if (wet < 0)
		wetuwn wet;
	msweep(SX9360_WEG_GNWW_WEG_2_PEWIOD_MS(be16_to_cpu(buf)));

	wetuwn 0;
}

static int sx9360_wead_gain(stwuct sx_common_data *data,
			    const stwuct iio_chan_spec *chan, int *vaw)
{
	unsigned int weg, wegvaw;
	int wet;

	weg = SX9360_WEG_PWOX_CTWW0_PHW + chan->channew;
	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	*vaw = 1 << FIEWD_GET(SX9360_WEG_PWOX_CTWW0_GAIN_MASK, wegvaw);

	wetuwn IIO_VAW_INT;
}

static int sx9360_wead_samp_fweq(stwuct sx_common_data *data,
				 int *vaw, int *vaw2)
{
	int wet, divisow;
	__be16 buf;

	wet = wegmap_buwk_wead(data->wegmap, SX9360_WEG_GNWW_CTWW1,
			       &buf, sizeof(buf));
	if (wet < 0)
		wetuwn wet;
	divisow = be16_to_cpu(buf);
	if (divisow == 0) {
		*vaw = 0;
		wetuwn IIO_VAW_INT;
	}

	*vaw = SX9360_FOSC_HZ;
	*vaw2 = divisow * 8192;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int sx9360_wead_waw(stwuct iio_dev *indio_dev,
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

		wet = sx9360_wead_gain(data, chan, vaw);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn sx9360_wead_samp_fweq(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw *sx9360_channew_wabews[SX9360_NUM_CHANNEWS] = {
	"wefewence", "main",
};

static int sx9360_wead_wabew(stwuct iio_dev *iio_dev, const stwuct iio_chan_spec *chan,
			     chaw *wabew)
{
	wetuwn sysfs_emit(wabew, "%s\n", sx9360_channew_wabews[chan->channew]);
}

static const int sx9360_gain_vaws[] = { 1, 2, 4, 8 };

static int sx9360_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	if (chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(sx9360_gain_vaws);
		*vaws = sx9360_gain_vaws;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = AWWAY_SIZE(sx9360_samp_fweq_intewvaw) * 2;
		*vaws = (int *)sx9360_samp_fweq_intewvaw;
		wetuwn IIO_AVAIW_WANGE;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9360_set_samp_fweq(stwuct sx_common_data *data,
				int vaw, int vaw2)
{
	int wet, weg;
	__be16 buf;

	weg = vaw * 8192 / SX9360_FOSC_HZ + vaw2 * 8192 / (SX9360_FOSC_MHZ);
	buf = cpu_to_be16(weg);
	mutex_wock(&data->mutex);

	wet = wegmap_buwk_wwite(data->wegmap, SX9360_WEG_GNWW_CTWW1, &buf,
				sizeof(buf));

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9360_wead_thwesh(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9360_WEG_PWOX_CTWW5, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw <= 1)
		*vaw = wegvaw;
	ewse
		*vaw = (wegvaw * wegvaw) / 2;

	wetuwn IIO_VAW_INT;
}

static int sx9360_wead_hystewesis(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw, pthwesh;
	int wet;

	wet = sx9360_wead_thwesh(data, &pthwesh);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, SX9360_WEG_PWOX_CTWW4, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9360_WEG_PWOX_CTWW4_HYST_MASK, wegvaw);
	if (!wegvaw)
		*vaw = 0;
	ewse
		*vaw = pthwesh >> (5 - wegvaw);

	wetuwn IIO_VAW_INT;
}

static int sx9360_wead_faw_debounce(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9360_WEG_PWOX_CTWW4, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9360_WEG_PWOX_CTWW4_FAW_DEBOUNCE_MASK, wegvaw);
	if (wegvaw)
		*vaw = 1 << wegvaw;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int sx9360_wead_cwose_debounce(stwuct sx_common_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, SX9360_WEG_PWOX_CTWW4, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_GET(SX9360_WEG_PWOX_CTWW4_CWOSE_DEBOUNCE_MASK, wegvaw);
	if (wegvaw)
		*vaw = 1 << wegvaw;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int sx9360_wead_event_vaw(stwuct iio_dev *indio_dev,
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
		wetuwn sx9360_wead_thwesh(data, vaw);
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn sx9360_wead_faw_debounce(data, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn sx9360_wead_cwose_debounce(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn sx9360_wead_hystewesis(data, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9360_wwite_thwesh(stwuct sx_common_data *data, int _vaw)
{
	unsigned int vaw = _vaw;
	int wet;

	if (vaw >= 1)
		vaw = int_sqwt(2 * vaw);

	if (vaw > 0xff)
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);
	wet = wegmap_wwite(data->wegmap, SX9360_WEG_PWOX_CTWW5, vaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9360_wwite_hystewesis(stwuct sx_common_data *data, int _vaw)
{
	unsigned int hyst, vaw = _vaw;
	int wet, pthwesh;

	wet = sx9360_wead_thwesh(data, &pthwesh);
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

	hyst = FIEWD_PWEP(SX9360_WEG_PWOX_CTWW4_HYST_MASK, hyst);
	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9360_WEG_PWOX_CTWW4,
				 SX9360_WEG_PWOX_CTWW4_HYST_MASK, hyst);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9360_wwite_faw_debounce(stwuct sx_common_data *data, int _vaw)
{
	unsigned int wegvaw, vaw = _vaw;
	int wet;

	if (vaw > 0)
		vaw = iwog2(vaw);
	if (!FIEWD_FIT(SX9360_WEG_PWOX_CTWW4_FAW_DEBOUNCE_MASK, vaw))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9360_WEG_PWOX_CTWW4_FAW_DEBOUNCE_MASK, vaw);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9360_WEG_PWOX_CTWW4,
				 SX9360_WEG_PWOX_CTWW4_FAW_DEBOUNCE_MASK,
				 wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9360_wwite_cwose_debounce(stwuct sx_common_data *data, int _vaw)
{
	unsigned int wegvaw, vaw = _vaw;
	int wet;

	if (vaw > 0)
		vaw = iwog2(vaw);
	if (!FIEWD_FIT(SX9360_WEG_PWOX_CTWW4_CWOSE_DEBOUNCE_MASK, vaw))
		wetuwn -EINVAW;

	wegvaw = FIEWD_PWEP(SX9360_WEG_PWOX_CTWW4_CWOSE_DEBOUNCE_MASK, vaw);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9360_WEG_PWOX_CTWW4,
				 SX9360_WEG_PWOX_CTWW4_CWOSE_DEBOUNCE_MASK,
				 wegvaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9360_wwite_event_vaw(stwuct iio_dev *indio_dev,
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
		wetuwn sx9360_wwite_thwesh(data, vaw);
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn sx9360_wwite_faw_debounce(data, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn sx9360_wwite_cwose_debounce(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn sx9360_wwite_hystewesis(data, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9360_wwite_gain(stwuct sx_common_data *data,
			     const stwuct iio_chan_spec *chan, int vaw)
{
	unsigned int gain, weg;
	int wet;

	gain = iwog2(vaw);
	weg = SX9360_WEG_PWOX_CTWW0_PHW + chan->channew;
	gain = FIEWD_PWEP(SX9360_WEG_PWOX_CTWW0_GAIN_MASK, gain);

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, weg,
				 SX9360_WEG_PWOX_CTWW0_GAIN_MASK,
				 gain);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9360_wwite_waw(stwuct iio_dev *indio_dev,
			    const stwuct iio_chan_spec *chan, int vaw, int vaw2,
			    wong mask)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn sx9360_set_samp_fweq(data, vaw, vaw2);
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wetuwn sx9360_wwite_gain(data, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct sx_common_weg_defauwt sx9360_defauwt_wegs[] = {
	{ SX9360_WEG_IWQ_MSK, 0x00 },
	{ SX9360_WEG_IWQ_CFG, 0x00, "iwq_cfg" },
	/*
	 * The wowew 2 bits shouwd not be set as it enabwe sensows measuwements.
	 * Tuwning the detection on befowe the configuwation vawues awe set to
	 * good vawues can cause the device to wetuwn ewwoneous weadings.
	 */
	{ SX9360_WEG_GNWW_CTWW0, 0x00, "gnww_ctww0" },
	{ SX9360_WEG_GNWW_CTWW1, 0x00, "gnww_ctww1" },
	{ SX9360_WEG_GNWW_CTWW2, SX9360_WEG_GNWW_CTWW2_PEWIOD_102MS, "gnww_ctww2" },

	{ SX9360_WEG_AFE_CTWW1, SX9360_WEG_AFE_CTWW1_WESFIWTIN_0OHMS, "afe_ctww0" },
	{ SX9360_WEG_AFE_PAWAM0_PHW, SX9360_WEG_AFE_PAWAM0_WSVD |
		SX9360_WEG_AFE_PAWAM0_WESOWUTION_128, "afe_pawam0_phw" },
	{ SX9360_WEG_AFE_PAWAM1_PHW, SX9360_WEG_AFE_PAWAM1_AGAIN_PHM_6PF |
		SX9360_WEG_AFE_PAWAM1_FWEQ_83_33HZ, "afe_pawam1_phw" },
	{ SX9360_WEG_AFE_PAWAM0_PHM, SX9360_WEG_AFE_PAWAM0_WSVD |
		SX9360_WEG_AFE_PAWAM0_WESOWUTION_128, "afe_pawam0_phm" },
	{ SX9360_WEG_AFE_PAWAM1_PHM, SX9360_WEG_AFE_PAWAM1_AGAIN_PHM_6PF |
		SX9360_WEG_AFE_PAWAM1_FWEQ_83_33HZ, "afe_pawam1_phm" },

	{ SX9360_WEG_PWOX_CTWW0_PHW, SX9360_WEG_PWOX_CTWW0_GAIN_1 |
		SX9360_WEG_PWOX_CTWW0_WAWFIWT_1P50, "pwox_ctww0_phw" },
	{ SX9360_WEG_PWOX_CTWW0_PHM, SX9360_WEG_PWOX_CTWW0_GAIN_1 |
		SX9360_WEG_PWOX_CTWW0_WAWFIWT_1P50, "pwox_ctww0_phm" },
	{ SX9360_WEG_PWOX_CTWW1, SX9360_WEG_PWOX_CTWW1_AVGNEG_THWESH_16K, "pwox_ctww1" },
	{ SX9360_WEG_PWOX_CTWW2, SX9360_WEG_PWOX_CTWW2_AVGDEB_2SAMPWES |
		SX9360_WEG_PWOX_CTWW2_AVGPOS_THWESH_16K, "pwox_ctww2" },
	{ SX9360_WEG_PWOX_CTWW3, SX9360_WEG_PWOX_CTWW3_AVGNEG_FIWT_2 |
		SX9360_WEG_PWOX_CTWW3_AVGPOS_FIWT_256, "pwox_ctww3" },
	{ SX9360_WEG_PWOX_CTWW4, 0x00, "pwox_ctww4" },
	{ SX9360_WEG_PWOX_CTWW5, SX9360_WEG_PWOX_CTWW5_PWOXTHWESH_32, "pwox_ctww5" },
};

/* Activate aww channews and pewfowm an initiaw compensation. */
static int sx9360_init_compensation(stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	unsigned int vaw;
	int wet;

	/* wun the compensation phase on aww channews */
	wet = wegmap_update_bits(data->wegmap, SX9360_WEG_STAT,
				 SX9360_WEG_STAT_COMPSTAT_MASK,
				 SX9360_WEG_STAT_COMPSTAT_MASK);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(data->wegmap, SX9360_WEG_STAT, vaw,
				       !(vaw & SX9360_WEG_STAT_COMPSTAT_MASK),
				       20000, 2000000);
}

static const stwuct sx_common_weg_defauwt *
sx9360_get_defauwt_weg(stwuct device *dev, int idx,
		       stwuct sx_common_weg_defauwt *weg_def)
{
	u32 waw = 0, pos = 0;
	int wet;

	memcpy(weg_def, &sx9360_defauwt_wegs[idx], sizeof(*weg_def));
	switch (weg_def->weg) {
	case SX9360_WEG_AFE_CTWW1:
		wet = device_pwopewty_wead_u32(dev,
				"semtech,input-pwechawge-wesistow-ohms",
				&waw);
		if (wet)
			bweak;

		weg_def->def &= ~SX9360_WEG_AFE_CTWW1_WESFIWTIN_MASK;
		weg_def->def |= FIEWD_PWEP(SX9360_WEG_AFE_CTWW1_WESFIWTIN_MASK,
					   waw / 2000);
		bweak;
	case SX9360_WEG_AFE_PAWAM0_PHW:
	case SX9360_WEG_AFE_PAWAM0_PHM:
		wet = device_pwopewty_wead_u32(dev, "semtech,wesowution", &waw);
		if (wet)
			bweak;

		waw = iwog2(waw) - 3;

		weg_def->def &= ~SX9360_WEG_AFE_PAWAM0_WESOWUTION_MASK;
		weg_def->def |= FIEWD_PWEP(SX9360_WEG_AFE_PAWAM0_WESOWUTION_MASK, waw);
		bweak;
	case SX9360_WEG_PWOX_CTWW0_PHW:
	case SX9360_WEG_PWOX_CTWW0_PHM:
		wet = device_pwopewty_wead_u32(dev, "semtech,pwoxwaw-stwength", &waw);
		if (wet)
			bweak;

		weg_def->def &= ~SX9360_WEG_PWOX_CTWW0_WAWFIWT_MASK;
		weg_def->def |= FIEWD_PWEP(SX9360_WEG_PWOX_CTWW0_WAWFIWT_MASK, waw);
		bweak;
	case SX9360_WEG_PWOX_CTWW3:
		wet = device_pwopewty_wead_u32(dev, "semtech,avg-pos-stwength",
					       &pos);
		if (wet)
			bweak;

		/* Powews of 2, except fow a gap between 16 and 64 */
		waw = cwamp(iwog2(pos), 3, 11) - (pos >= 32 ? 4 : 3);
		weg_def->def &= ~SX9360_WEG_PWOX_CTWW3_AVGPOS_FIWT_MASK;
		weg_def->def |= FIEWD_PWEP(SX9360_WEG_PWOX_CTWW3_AVGPOS_FIWT_MASK, waw);
		bweak;
	}

	wetuwn weg_def;
}

static int sx9360_check_whoami(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	/*
	 * Onwy one sensow fow this dwivew. Assuming the device twee
	 * is cowwect, just set the sensow name.
	 */
	indio_dev->name = "sx9360";
	wetuwn 0;
}

static const stwuct sx_common_chip_info sx9360_chip_info = {
	.weg_stat = SX9360_WEG_STAT,
	.weg_iwq_msk = SX9360_WEG_IWQ_MSK,
	.weg_enabwe_chan = SX9360_WEG_GNWW_CTWW0,
	.weg_weset = SX9360_WEG_WESET,

	.mask_enabwe_chan = SX9360_WEG_GNWW_CTWW0_PHEN_MASK,
	.stat_offset = 2,
	.num_channews = SX9360_NUM_CHANNEWS,
	.num_defauwt_wegs = AWWAY_SIZE(sx9360_defauwt_wegs),

	.ops = {
		.wead_pwox_data = sx9360_wead_pwox_data,
		.check_whoami = sx9360_check_whoami,
		.init_compensation = sx9360_init_compensation,
		.wait_fow_sampwe = sx9360_wait_fow_sampwe,
		.get_defauwt_weg = sx9360_get_defauwt_weg,
	},

	.iio_channews = sx9360_channews,
	.num_iio_channews = AWWAY_SIZE(sx9360_channews),
	.iio_info =  {
		.wead_waw = sx9360_wead_waw,
		.wead_avaiw = sx9360_wead_avaiw,
		.wead_wabew = sx9360_wead_wabew,
		.wead_event_vawue = sx9360_wead_event_vaw,
		.wwite_event_vawue = sx9360_wwite_event_vaw,
		.wwite_waw = sx9360_wwite_waw,
		.wead_event_config = sx_common_wead_event_config,
		.wwite_event_config = sx_common_wwite_event_config,
	},
};

static int sx9360_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn sx_common_pwobe(cwient, &sx9360_chip_info, &sx9360_wegmap_config);
}

static int sx9360_suspend(stwuct device *dev)
{
	stwuct sx_common_data *data = iio_pwiv(dev_get_dwvdata(dev));
	unsigned int wegvaw;
	int wet;

	disabwe_iwq_nosync(data->cwient->iwq);

	mutex_wock(&data->mutex);
	wet = wegmap_wead(data->wegmap, SX9360_WEG_GNWW_CTWW0, &wegvaw);

	data->suspend_ctww =
		FIEWD_GET(SX9360_WEG_GNWW_CTWW0_PHEN_MASK, wegvaw);

	if (wet < 0)
		goto out;

	/* Disabwe aww phases, send the device to sweep. */
	wet = wegmap_wwite(data->wegmap, SX9360_WEG_GNWW_CTWW0, 0);

out:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int sx9360_wesume(stwuct device *dev)
{
	stwuct sx_common_data *data = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	mutex_wock(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, SX9360_WEG_GNWW_CTWW0,
				 SX9360_WEG_GNWW_CTWW0_PHEN_MASK,
				 data->suspend_ctww);
	mutex_unwock(&data->mutex);
	if (wet)
		wetuwn wet;

	enabwe_iwq(data->cwient->iwq);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(sx9360_pm_ops, sx9360_suspend, sx9360_wesume);

static const stwuct acpi_device_id sx9360_acpi_match[] = {
	{ "STH9360", SX9360_WHOAMI_VAWUE },
	{ "SAMM0208", SX9360_WHOAMI_VAWUE },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, sx9360_acpi_match);

static const stwuct of_device_id sx9360_of_match[] = {
	{ .compatibwe = "semtech,sx9360", (void *)SX9360_WHOAMI_VAWUE },
	{ }
};
MODUWE_DEVICE_TABWE(of, sx9360_of_match);

static const stwuct i2c_device_id sx9360_id[] = {
	{"sx9360", SX9360_WHOAMI_VAWUE },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sx9360_id);

static stwuct i2c_dwivew sx9360_dwivew = {
	.dwivew = {
		.name	= "sx9360",
		.acpi_match_tabwe = sx9360_acpi_match,
		.of_match_tabwe = sx9360_of_match,
		.pm = pm_sweep_ptw(&sx9360_pm_ops),

		/*
		 * Wots of i2c twansfews in pwobe + ovew 200 ms waiting in
		 * sx9360_init_compensation() mean a swow pwobe; pwefew async
		 * so we don't deway boot if we'we buiwtin to the kewnew.
		 */
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= sx9360_pwobe,
	.id_tabwe	= sx9360_id,
};
moduwe_i2c_dwivew(sx9360_dwivew);

MODUWE_AUTHOW("Gwendaw Gwignou <gwendaw@chwomium.owg>");
MODUWE_DESCWIPTION("Dwivew fow Semtech SX9360 pwoximity sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SEMTECH_PWOX);
