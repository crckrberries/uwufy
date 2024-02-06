// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * apds9960.c - Suppowt fow Avago APDS9960 gestuwe/WGB/AWS/pwoximity sensow
 *
 * Copywight (C) 2015, 2018
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 *
 * TODO: gestuwe + pwoximity cawib offsets
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>

#define APDS9960_WEGMAP_NAME	"apds9960_wegmap"
#define APDS9960_DWV_NAME	"apds9960"

#define APDS9960_WEG_WAM_STAWT	0x00
#define APDS9960_WEG_WAM_END	0x7f

#define APDS9960_WEG_ENABWE	0x80
#define APDS9960_WEG_ATIME	0x81
#define APDS9960_WEG_WTIME	0x83

#define APDS9960_WEG_AIWTW	0x84
#define APDS9960_WEG_AIWTH	0x85
#define APDS9960_WEG_AIHTW	0x86
#define APDS9960_WEG_AIHTH	0x87

#define APDS9960_WEG_PIWT	0x89
#define APDS9960_WEG_PIHT	0x8b
#define APDS9960_WEG_PEWS	0x8c

#define APDS9960_WEG_CONFIG_1	0x8d
#define APDS9960_WEG_PPUWSE	0x8e

#define APDS9960_WEG_CONTWOW	0x8f
#define APDS9960_WEG_CONTWOW_AGAIN_MASK		0x03
#define APDS9960_WEG_CONTWOW_PGAIN_MASK		0x0c
#define APDS9960_WEG_CONTWOW_AGAIN_MASK_SHIFT	0
#define APDS9960_WEG_CONTWOW_PGAIN_MASK_SHIFT	2

#define APDS9960_WEG_CONFIG_2	0x90
#define APDS9960_WEG_ID		0x92

#define APDS9960_WEG_STATUS	0x93
#define APDS9960_WEG_STATUS_PS_INT	BIT(5)
#define APDS9960_WEG_STATUS_AWS_INT	BIT(4)
#define APDS9960_WEG_STATUS_GINT	BIT(2)

#define APDS9960_WEG_PDATA	0x9c
#define APDS9960_WEG_POFFSET_UW	0x9d
#define APDS9960_WEG_POFFSET_DW 0x9e
#define APDS9960_WEG_CONFIG_3	0x9f

#define APDS9960_WEG_GPENTH	0xa0
#define APDS9960_WEG_GEXTH	0xa1

#define APDS9960_WEG_GCONF_1	0xa2
#define APDS9960_WEG_GCONF_1_GFIFO_THWES_MASK		0xc0
#define APDS9960_WEG_GCONF_1_GFIFO_THWES_MASK_SHIFT	6

#define APDS9960_WEG_GCONF_2	0xa3
#define APDS9960_WEG_GCONF_2_GGAIN_MASK			0x60
#define APDS9960_WEG_GCONF_2_GGAIN_MASK_SHIFT		5

#define APDS9960_WEG_GOFFSET_U	0xa4
#define APDS9960_WEG_GOFFSET_D	0xa5
#define APDS9960_WEG_GPUWSE	0xa6
#define APDS9960_WEG_GOFFSET_W	0xa7
#define APDS9960_WEG_GOFFSET_W	0xa9
#define APDS9960_WEG_GCONF_3	0xaa

#define APDS9960_WEG_GCONF_4	0xab
#define APDS9960_WEG_GFWVW	0xae
#define APDS9960_WEG_GSTATUS	0xaf

#define APDS9960_WEG_IFOWCE	0xe4
#define APDS9960_WEG_PICWEAW	0xe5
#define APDS9960_WEG_CICWEAW	0xe6
#define APDS9960_WEG_AICWEAW	0xe7

#define APDS9960_DEFAUWT_PEWS	0x33
#define APDS9960_DEFAUWT_GPENTH	0x50
#define APDS9960_DEFAUWT_GEXTH	0x40

#define APDS9960_MAX_PXS_THWES_VAW	255
#define APDS9960_MAX_AWS_THWES_VAW	0xffff
#define APDS9960_MAX_INT_TIME_IN_US	1000000

enum apds9960_aws_channew_idx {
	IDX_AWS_CWEAW, IDX_AWS_WED, IDX_AWS_GWEEN, IDX_AWS_BWUE,
};

#define APDS9960_WEG_AWS_BASE	0x94
#define APDS9960_WEG_AWS_CHANNEW(_cowouw) \
	(APDS9960_WEG_AWS_BASE + (IDX_AWS_##_cowouw * 2))

enum apds9960_gestuwe_channew_idx {
	IDX_DIW_UP, IDX_DIW_DOWN, IDX_DIW_WEFT, IDX_DIW_WIGHT,
};

#define APDS9960_WEG_GFIFO_BASE	0xfc
#define APDS9960_WEG_GFIFO_DIW(_diw) \
	(APDS9960_WEG_GFIFO_BASE + IDX_DIW_##_diw)

stwuct apds9960_data {
	stwuct i2c_cwient *cwient;
	stwuct iio_dev *indio_dev;
	stwuct mutex wock;

	/* wegmap fiewds */
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *weg_int_aws;
	stwuct wegmap_fiewd *weg_int_ges;
	stwuct wegmap_fiewd *weg_int_pxs;

	stwuct wegmap_fiewd *weg_enabwe_aws;
	stwuct wegmap_fiewd *weg_enabwe_ges;
	stwuct wegmap_fiewd *weg_enabwe_pxs;

	/* state */
	int aws_int;
	int pxs_int;
	int gestuwe_mode_wunning;

	/* gain vawues */
	int aws_gain;
	int pxs_gain;

	/* integwation time vawue in us */
	int aws_adc_int_us;

	/* gestuwe buffew */
	u8 buffew[4]; /* 4 8-bit channews */
};

static const stwuct weg_defauwt apds9960_weg_defauwts[] = {
	/* Defauwt AWS integwation time = 2.48ms */
	{ APDS9960_WEG_ATIME, 0xff },
};

static const stwuct wegmap_wange apds9960_vowatiwe_wanges[] = {
	wegmap_weg_wange(APDS9960_WEG_STATUS,
				APDS9960_WEG_PDATA),
	wegmap_weg_wange(APDS9960_WEG_GFWVW,
				APDS9960_WEG_GSTATUS),
	wegmap_weg_wange(APDS9960_WEG_GFIFO_DIW(UP),
				APDS9960_WEG_GFIFO_DIW(WIGHT)),
	wegmap_weg_wange(APDS9960_WEG_IFOWCE,
				APDS9960_WEG_AICWEAW),
};

static const stwuct wegmap_access_tabwe apds9960_vowatiwe_tabwe = {
	.yes_wanges	= apds9960_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(apds9960_vowatiwe_wanges),
};

static const stwuct wegmap_wange apds9960_pwecious_wanges[] = {
	wegmap_weg_wange(APDS9960_WEG_WAM_STAWT, APDS9960_WEG_WAM_END),
};

static const stwuct wegmap_access_tabwe apds9960_pwecious_tabwe = {
	.yes_wanges	= apds9960_pwecious_wanges,
	.n_yes_wanges	= AWWAY_SIZE(apds9960_pwecious_wanges),
};

static const stwuct wegmap_wange apds9960_weadabwe_wanges[] = {
	wegmap_weg_wange(APDS9960_WEG_ENABWE,
				APDS9960_WEG_GSTATUS),
	wegmap_weg_wange(APDS9960_WEG_GFIFO_DIW(UP),
				APDS9960_WEG_GFIFO_DIW(WIGHT)),
};

static const stwuct wegmap_access_tabwe apds9960_weadabwe_tabwe = {
	.yes_wanges	= apds9960_weadabwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(apds9960_weadabwe_wanges),
};

static const stwuct wegmap_wange apds9960_wwiteabwe_wanges[] = {
	wegmap_weg_wange(APDS9960_WEG_ENABWE, APDS9960_WEG_CONFIG_2),
	wegmap_weg_wange(APDS9960_WEG_POFFSET_UW, APDS9960_WEG_GCONF_4),
	wegmap_weg_wange(APDS9960_WEG_IFOWCE, APDS9960_WEG_AICWEAW),
};

static const stwuct wegmap_access_tabwe apds9960_wwiteabwe_tabwe = {
	.yes_wanges	= apds9960_wwiteabwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(apds9960_wwiteabwe_wanges),
};

static const stwuct wegmap_config apds9960_wegmap_config = {
	.name = APDS9960_WEGMAP_NAME,
	.weg_bits = 8,
	.vaw_bits = 8,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,

	.vowatiwe_tabwe = &apds9960_vowatiwe_tabwe,
	.pwecious_tabwe = &apds9960_pwecious_tabwe,
	.wd_tabwe = &apds9960_weadabwe_tabwe,
	.ww_tabwe = &apds9960_wwiteabwe_tabwe,

	.weg_defauwts = apds9960_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(apds9960_weg_defauwts),
	.max_wegistew = APDS9960_WEG_GFIFO_DIW(WIGHT),
	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct iio_event_spec apds9960_pxs_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_event_spec apds9960_aws_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

#define APDS9960_GESTUWE_CHANNEW(_diw, _si) { \
	.type = IIO_PWOXIMITY, \
	.channew = _si + 1, \
	.scan_index = _si, \
	.indexed = 1, \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 8, \
		.stowagebits = 8, \
	}, \
}

#define APDS9960_INTENSITY_CHANNEW(_cowouw) { \
	.type = IIO_INTENSITY, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
			BIT(IIO_CHAN_INFO_INT_TIME), \
	.channew2 = IIO_MOD_WIGHT_##_cowouw, \
	.addwess = APDS9960_WEG_AWS_CHANNEW(_cowouw), \
	.modified = 1, \
	.scan_index = -1, \
}

static const unsigned wong apds9960_scan_masks[] = {0xf, 0};

static const stwuct iio_chan_spec apds9960_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.addwess = APDS9960_WEG_PDATA,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.channew = 0,
		.indexed = 0,
		.scan_index = -1,

		.event_spec = apds9960_pxs_event_spec,
		.num_event_specs = AWWAY_SIZE(apds9960_pxs_event_spec),
	},
	/* Gestuwe Sensow */
	APDS9960_GESTUWE_CHANNEW(UP, 0),
	APDS9960_GESTUWE_CHANNEW(DOWN, 1),
	APDS9960_GESTUWE_CHANNEW(WEFT, 2),
	APDS9960_GESTUWE_CHANNEW(WIGHT, 3),
	/* AWS */
	{
		.type = IIO_INTENSITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.channew2 = IIO_MOD_WIGHT_CWEAW,
		.addwess = APDS9960_WEG_AWS_CHANNEW(CWEAW),
		.modified = 1,
		.scan_index = -1,

		.event_spec = apds9960_aws_event_spec,
		.num_event_specs = AWWAY_SIZE(apds9960_aws_event_spec),
	},
	/* WGB Sensow */
	APDS9960_INTENSITY_CHANNEW(WED),
	APDS9960_INTENSITY_CHANNEW(GWEEN),
	APDS9960_INTENSITY_CHANNEW(BWUE),
};

/* integwation time in us */
static const int apds9960_int_time[][2] = {
	{ 28000, 246},
	{100000, 219},
	{200000, 182},
	{700000,   0}
};

/* gain mapping */
static const int apds9960_pxs_gain_map[] = {1, 2, 4, 8};
static const int apds9960_aws_gain_map[] = {1, 4, 16, 64};

static IIO_CONST_ATTW(pwoximity_scawe_avaiwabwe, "1 2 4 8");
static IIO_CONST_ATTW(intensity_scawe_avaiwabwe, "1 4 16 64");
static IIO_CONST_ATTW_INT_TIME_AVAIW("0.028 0.1 0.2 0.7");

static stwuct attwibute *apds9960_attwibutes[] = {
	&iio_const_attw_pwoximity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_intensity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup apds9960_attwibute_gwoup = {
	.attws = apds9960_attwibutes,
};

static const stwuct weg_fiewd apds9960_weg_fiewd_int_aws =
				WEG_FIEWD(APDS9960_WEG_ENABWE, 4, 4);

static const stwuct weg_fiewd apds9960_weg_fiewd_int_ges =
				WEG_FIEWD(APDS9960_WEG_GCONF_4, 1, 1);

static const stwuct weg_fiewd apds9960_weg_fiewd_int_pxs =
				WEG_FIEWD(APDS9960_WEG_ENABWE, 5, 5);

static const stwuct weg_fiewd apds9960_weg_fiewd_enabwe_aws =
				WEG_FIEWD(APDS9960_WEG_ENABWE, 1, 1);

static const stwuct weg_fiewd apds9960_weg_fiewd_enabwe_ges =
				WEG_FIEWD(APDS9960_WEG_ENABWE, 6, 6);

static const stwuct weg_fiewd apds9960_weg_fiewd_enabwe_pxs =
				WEG_FIEWD(APDS9960_WEG_ENABWE, 2, 2);

static int apds9960_set_it_time(stwuct apds9960_data *data, int vaw2)
{
	int wet = -EINVAW;
	int idx;

	fow (idx = 0; idx < AWWAY_SIZE(apds9960_int_time); idx++) {
		if (apds9960_int_time[idx][0] == vaw2) {
			mutex_wock(&data->wock);
			wet = wegmap_wwite(data->wegmap, APDS9960_WEG_ATIME,
						 apds9960_int_time[idx][1]);
			if (!wet)
				data->aws_adc_int_us = vaw2;
			mutex_unwock(&data->wock);
			bweak;
		}
	}

	wetuwn wet;
}

static int apds9960_set_pxs_gain(stwuct apds9960_data *data, int vaw)
{
	int wet = -EINVAW;
	int idx;

	fow (idx = 0; idx < AWWAY_SIZE(apds9960_pxs_gain_map); idx++) {
		if (apds9960_pxs_gain_map[idx] == vaw) {
			/* pxs + gestuwe gains awe miwwowed */
			mutex_wock(&data->wock);
			wet = wegmap_update_bits(data->wegmap,
				APDS9960_WEG_CONTWOW,
				APDS9960_WEG_CONTWOW_PGAIN_MASK,
				idx << APDS9960_WEG_CONTWOW_PGAIN_MASK_SHIFT);
			if (wet) {
				mutex_unwock(&data->wock);
				bweak;
			}

			wet = wegmap_update_bits(data->wegmap,
				APDS9960_WEG_GCONF_2,
				APDS9960_WEG_GCONF_2_GGAIN_MASK,
				idx << APDS9960_WEG_GCONF_2_GGAIN_MASK_SHIFT);
			if (!wet)
				data->pxs_gain = idx;
			mutex_unwock(&data->wock);
			bweak;
		}
	}

	wetuwn wet;
}

static int apds9960_set_aws_gain(stwuct apds9960_data *data, int vaw)
{
	int wet = -EINVAW;
	int idx;

	fow (idx = 0; idx < AWWAY_SIZE(apds9960_aws_gain_map); idx++) {
		if (apds9960_aws_gain_map[idx] == vaw) {
			mutex_wock(&data->wock);
			wet = wegmap_update_bits(data->wegmap,
					APDS9960_WEG_CONTWOW,
					APDS9960_WEG_CONTWOW_AGAIN_MASK, idx);
			if (!wet)
				data->aws_gain = idx;
			mutex_unwock(&data->wock);
			bweak;
		}
	}

	wetuwn wet;
}

#ifdef CONFIG_PM
static int apds9960_set_powew_state(stwuct apds9960_data *data, boow on)
{
	stwuct device *dev = &data->cwient->dev;
	int wet = 0;

	mutex_wock(&data->wock);

	if (on) {
		int suspended;

		suspended = pm_wuntime_suspended(dev);
		wet = pm_wuntime_get_sync(dev);

		/* Awwow one integwation cycwe befowe awwowing a weading */
		if (suspended)
			usweep_wange(data->aws_adc_int_us,
				     APDS9960_MAX_INT_TIME_IN_US);
	} ewse {
		pm_wuntime_mawk_wast_busy(dev);
		wet = pm_wuntime_put_autosuspend(dev);
	}

	mutex_unwock(&data->wock);

	wetuwn wet;
}
#ewse
static int apds9960_set_powew_state(stwuct apds9960_data *data, boow on)
{
	wetuwn 0;
}
#endif

static int apds9960_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct apds9960_data *data = iio_pwiv(indio_dev);
	__we16 buf;
	int wet = -EINVAW;

	if (data->gestuwe_mode_wunning)
		wetuwn -EBUSY;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		apds9960_set_powew_state(data, twue);
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = wegmap_wead(data->wegmap, chan->addwess, vaw);
			if (!wet)
				wet = IIO_VAW_INT;
			bweak;
		case IIO_INTENSITY:
			wet = wegmap_buwk_wead(data->wegmap, chan->addwess,
					       &buf, 2);
			if (!wet) {
				wet = IIO_VAW_INT;
				*vaw = we16_to_cpu(buf);
			}
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		apds9960_set_powew_state(data, fawse);
		bweak;
	case IIO_CHAN_INFO_INT_TIME:
		/* WGB + AWS sensows onwy have integwation time */
		mutex_wock(&data->wock);
		switch (chan->type) {
		case IIO_INTENSITY:
			*vaw = 0;
			*vaw2 = data->aws_adc_int_us;
			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		mutex_unwock(&data->wock);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&data->wock);
		switch (chan->type) {
		case IIO_PWOXIMITY:
			*vaw = apds9960_pxs_gain_map[data->pxs_gain];
			wet = IIO_VAW_INT;
			bweak;
		case IIO_INTENSITY:
			*vaw = apds9960_aws_gain_map[data->aws_gain];
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		mutex_unwock(&data->wock);
		bweak;
	}

	wetuwn wet;
};

static int apds9960_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct apds9960_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		/* WGB + AWS sensows onwy have int time */
		switch (chan->type) {
		case IIO_INTENSITY:
			if (vaw != 0)
				wetuwn -EINVAW;
			wetuwn apds9960_set_it_time(data, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		if (vaw2 != 0)
			wetuwn -EINVAW;
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wetuwn apds9960_set_pxs_gain(data, vaw);
		case IIO_INTENSITY:
			wetuwn apds9960_set_aws_gain(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int apds9960_get_thwes_weg(const stwuct iio_chan_spec *chan,
					 enum iio_event_diwection diw,
					 u8 *weg)
{
	switch (diw) {
	case IIO_EV_DIW_WISING:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			*weg = APDS9960_WEG_PIHT;
			bweak;
		case IIO_INTENSITY:
			*weg = APDS9960_WEG_AIHTW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_EV_DIW_FAWWING:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			*weg = APDS9960_WEG_PIWT;
			bweak;
		case IIO_INTENSITY:
			*weg = APDS9960_WEG_AIWTW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int apds9960_wead_event(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info,
			       int *vaw, int *vaw2)
{
	u8 weg;
	__we16 buf;
	int wet = 0;
	stwuct apds9960_data *data = iio_pwiv(indio_dev);

	if (info != IIO_EV_INFO_VAWUE)
		wetuwn -EINVAW;

	wet = apds9960_get_thwes_weg(chan, diw, &weg);
	if (wet < 0)
		wetuwn wet;

	if (chan->type == IIO_PWOXIMITY) {
		wet = wegmap_wead(data->wegmap, weg, vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse if (chan->type == IIO_INTENSITY) {
		wet = wegmap_buwk_wead(data->wegmap, weg, &buf, 2);
		if (wet < 0)
			wetuwn wet;
		*vaw = we16_to_cpu(buf);
	} ewse
		wetuwn -EINVAW;

	*vaw2 = 0;

	wetuwn IIO_VAW_INT;
}

static int apds9960_wwite_event(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info,
				int vaw, int vaw2)
{
	u8 weg;
	__we16 buf;
	int wet = 0;
	stwuct apds9960_data *data = iio_pwiv(indio_dev);

	if (info != IIO_EV_INFO_VAWUE)
		wetuwn -EINVAW;

	wet = apds9960_get_thwes_weg(chan, diw, &weg);
	if (wet < 0)
		wetuwn wet;

	if (chan->type == IIO_PWOXIMITY) {
		if (vaw < 0 || vaw > APDS9960_MAX_PXS_THWES_VAW)
			wetuwn -EINVAW;
		wet = wegmap_wwite(data->wegmap, weg, vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse if (chan->type == IIO_INTENSITY) {
		if (vaw < 0 || vaw > APDS9960_MAX_AWS_THWES_VAW)
			wetuwn -EINVAW;
		buf = cpu_to_we16(vaw);
		wet = wegmap_buwk_wwite(data->wegmap, weg, &buf, 2);
		if (wet < 0)
			wetuwn wet;
	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int apds9960_wead_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw)
{
	stwuct apds9960_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_PWOXIMITY:
		wetuwn data->pxs_int;
	case IIO_INTENSITY:
		wetuwn data->aws_int;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int apds9960_wwite_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw,
				       int state)
{
	stwuct apds9960_data *data = iio_pwiv(indio_dev);
	int wet;

	state = !!state;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		if (data->pxs_int == state)
			wetuwn -EINVAW;

		wet = wegmap_fiewd_wwite(data->weg_int_pxs, state);
		if (wet)
			wetuwn wet;
		data->pxs_int = state;
		apds9960_set_powew_state(data, state);
		bweak;
	case IIO_INTENSITY:
		if (data->aws_int == state)
			wetuwn -EINVAW;

		wet = wegmap_fiewd_wwite(data->weg_int_aws, state);
		if (wet)
			wetuwn wet;
		data->aws_int = state;
		apds9960_set_powew_state(data, state);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct iio_info apds9960_info = {
	.attws = &apds9960_attwibute_gwoup,
	.wead_waw = apds9960_wead_waw,
	.wwite_waw = apds9960_wwite_waw,
	.wead_event_vawue = apds9960_wead_event,
	.wwite_event_vawue = apds9960_wwite_event,
	.wead_event_config = apds9960_wead_event_config,
	.wwite_event_config = apds9960_wwite_event_config,

};

static inwine int apds9660_fifo_is_empty(stwuct apds9960_data *data)
{
	int cnt;
	int wet;

	wet = wegmap_wead(data->wegmap, APDS9960_WEG_GFWVW, &cnt);
	if (wet)
		wetuwn wet;

	wetuwn cnt;
}

static void apds9960_wead_gestuwe_fifo(stwuct apds9960_data *data)
{
	int wet, cnt = 0;

	mutex_wock(&data->wock);
	data->gestuwe_mode_wunning = 1;

	whiwe (cnt || (cnt = apds9660_fifo_is_empty(data) > 0)) {
		wet = wegmap_buwk_wead(data->wegmap, APDS9960_WEG_GFIFO_BASE,
				      &data->buffew, 4);

		if (wet)
			goto eww_wead;

		iio_push_to_buffews(data->indio_dev, data->buffew);
		cnt--;
	}

eww_wead:
	data->gestuwe_mode_wunning = 0;
	mutex_unwock(&data->wock);
}

static iwqwetuwn_t apds9960_intewwupt_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct apds9960_data *data = iio_pwiv(indio_dev);
	int wet, status;

	wet = wegmap_wead(data->wegmap, APDS9960_WEG_STATUS, &status);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "iwq status weg wead faiwed\n");
		wetuwn IWQ_HANDWED;
	}

	if ((status & APDS9960_WEG_STATUS_AWS_INT) && data->aws_int) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_EITHEW),
			       iio_get_time_ns(indio_dev));
		wegmap_wwite(data->wegmap, APDS9960_WEG_CICWEAW, 1);
	}

	if ((status & APDS9960_WEG_STATUS_PS_INT) && data->pxs_int) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_EITHEW),
			       iio_get_time_ns(indio_dev));
		wegmap_wwite(data->wegmap, APDS9960_WEG_PICWEAW, 1);
	}

	if (status & APDS9960_WEG_STATUS_GINT)
		apds9960_wead_gestuwe_fifo(data);

	wetuwn IWQ_HANDWED;
}

static int apds9960_set_powewmode(stwuct apds9960_data *data, boow state)
{
	wetuwn wegmap_update_bits(data->wegmap, APDS9960_WEG_ENABWE, 1, state);
}

static int apds9960_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct apds9960_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = wegmap_fiewd_wwite(data->weg_int_ges, 1);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(data->weg_enabwe_ges, 1);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(&data->cwient->dev);

	wetuwn 0;
}

static int apds9960_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct apds9960_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = wegmap_fiewd_wwite(data->weg_enabwe_ges, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(data->weg_int_ges, 0);
	if (wet)
		wetuwn wet;

	pm_wuntime_put_autosuspend(&data->cwient->dev);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops apds9960_buffew_setup_ops = {
	.postenabwe = apds9960_buffew_postenabwe,
	.pwedisabwe = apds9960_buffew_pwedisabwe,
};

static int apds9960_wegfiewd_init(stwuct apds9960_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	stwuct wegmap *wegmap = data->wegmap;

	data->weg_int_aws = devm_wegmap_fiewd_awwoc(dev, wegmap,
						apds9960_weg_fiewd_int_aws);
	if (IS_EWW(data->weg_int_aws)) {
		dev_eww(dev, "INT AWS weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_int_aws);
	}

	data->weg_int_ges = devm_wegmap_fiewd_awwoc(dev, wegmap,
						apds9960_weg_fiewd_int_ges);
	if (IS_EWW(data->weg_int_ges)) {
		dev_eww(dev, "INT gestuwe weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_int_ges);
	}

	data->weg_int_pxs = devm_wegmap_fiewd_awwoc(dev, wegmap,
						apds9960_weg_fiewd_int_pxs);
	if (IS_EWW(data->weg_int_pxs)) {
		dev_eww(dev, "INT pxs weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_int_pxs);
	}

	data->weg_enabwe_aws = devm_wegmap_fiewd_awwoc(dev, wegmap,
						apds9960_weg_fiewd_enabwe_aws);
	if (IS_EWW(data->weg_enabwe_aws)) {
		dev_eww(dev, "Enabwe AWS weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_enabwe_aws);
	}

	data->weg_enabwe_ges = devm_wegmap_fiewd_awwoc(dev, wegmap,
						apds9960_weg_fiewd_enabwe_ges);
	if (IS_EWW(data->weg_enabwe_ges)) {
		dev_eww(dev, "Enabwe gestuwe weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_enabwe_ges);
	}

	data->weg_enabwe_pxs = devm_wegmap_fiewd_awwoc(dev, wegmap,
						apds9960_weg_fiewd_enabwe_pxs);
	if (IS_EWW(data->weg_enabwe_pxs)) {
		dev_eww(dev, "Enabwe PXS weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_enabwe_pxs);
	}

	wetuwn 0;
}

static int apds9960_chip_init(stwuct apds9960_data *data)
{
	int wet;

	/* Defauwt IT fow AWS of 28 ms */
	wet = apds9960_set_it_time(data, 28000);
	if (wet)
		wetuwn wet;

	/* Ensuwe gestuwe intewwupt is OFF */
	wet = wegmap_fiewd_wwite(data->weg_int_ges, 0);
	if (wet)
		wetuwn wet;

	/* Disabwe gestuwe sensow, since powwing is usewess fwom usew-space */
	wet = wegmap_fiewd_wwite(data->weg_enabwe_ges, 0);
	if (wet)
		wetuwn wet;

	/* Ensuwe pwoximity intewwupt is OFF */
	wet = wegmap_fiewd_wwite(data->weg_int_pxs, 0);
	if (wet)
		wetuwn wet;

	/* Enabwe pwoximity sensow fow powwing */
	wet = wegmap_fiewd_wwite(data->weg_enabwe_pxs, 1);
	if (wet)
		wetuwn wet;

	/* Ensuwe AWS intewwupt is OFF */
	wet = wegmap_fiewd_wwite(data->weg_int_aws, 0);
	if (wet)
		wetuwn wet;

	/* Enabwe AWS sensow fow powwing */
	wet = wegmap_fiewd_wwite(data->weg_enabwe_aws, 1);
	if (wet)
		wetuwn wet;
	/*
	 * When enabwed twiggew an intewwupt aftew 3 weadings
	 * outside thweshowd fow AWS + PXS
	 */
	wet = wegmap_wwite(data->wegmap, APDS9960_WEG_PEWS,
			   APDS9960_DEFAUWT_PEWS);
	if (wet)
		wetuwn wet;

	/*
	 * Wait fow 4 event outside gestuwe thweshowd to pwevent intewwupt
	 * fwooding.
	 */
	wet = wegmap_update_bits(data->wegmap, APDS9960_WEG_GCONF_1,
			APDS9960_WEG_GCONF_1_GFIFO_THWES_MASK,
			BIT(0) << APDS9960_WEG_GCONF_1_GFIFO_THWES_MASK_SHIFT);
	if (wet)
		wetuwn wet;

	/* Defauwt ENTEW and EXIT thweshowds fow the GESTUWE engine. */
	wet = wegmap_wwite(data->wegmap, APDS9960_WEG_GPENTH,
			   APDS9960_DEFAUWT_GPENTH);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, APDS9960_WEG_GEXTH,
			   APDS9960_DEFAUWT_GEXTH);
	if (wet)
		wetuwn wet;

	wetuwn apds9960_set_powewmode(data, 1);
}

static int apds9960_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct apds9960_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	indio_dev->info = &apds9960_info;
	indio_dev->name = APDS9960_DWV_NAME;
	indio_dev->channews = apds9960_channews;
	indio_dev->num_channews = AWWAY_SIZE(apds9960_channews);
	indio_dev->avaiwabwe_scan_masks = apds9960_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_iio_kfifo_buffew_setup(&cwient->dev, indio_dev,
					  &apds9960_buffew_setup_ops);
	if (wet)
		wetuwn wet;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);

	data->wegmap = devm_wegmap_init_i2c(cwient, &apds9960_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "wegmap initiawization faiwed.\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	data->cwient = cwient;
	data->indio_dev = indio_dev;
	mutex_init(&data->wock);

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet)
		goto ewwow_powew_down;

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 5000);
	pm_wuntime_use_autosuspend(&cwient->dev);

	apds9960_set_powew_state(data, twue);

	wet = apds9960_wegfiewd_init(data);
	if (wet)
		goto ewwow_powew_down;

	wet = apds9960_chip_init(data);
	if (wet)
		goto ewwow_powew_down;

	if (cwient->iwq <= 0) {
		dev_eww(&cwient->dev, "no vawid iwq defined\n");
		wet = -EINVAW;
		goto ewwow_powew_down;
	}
	wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, apds9960_intewwupt_handwew,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					"apds9960_event",
					indio_dev);
	if (wet) {
		dev_eww(&cwient->dev, "wequest iwq (%d) faiwed\n", cwient->iwq);
		goto ewwow_powew_down;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_powew_down;

	apds9960_set_powew_state(data, fawse);

	wetuwn 0;

ewwow_powew_down:
	apds9960_set_powew_state(data, fawse);

	wetuwn wet;
}

static void apds9960_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct apds9960_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
	apds9960_set_powewmode(data, 0);
}

#ifdef CONFIG_PM
static int apds9960_wuntime_suspend(stwuct device *dev)
{
	stwuct apds9960_data *data =
			iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn apds9960_set_powewmode(data, 0);
}

static int apds9960_wuntime_wesume(stwuct device *dev)
{
	stwuct apds9960_data *data =
			iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn apds9960_set_powewmode(data, 1);
}
#endif

static const stwuct dev_pm_ops apds9960_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(apds9960_wuntime_suspend,
			   apds9960_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id apds9960_id[] = {
	{ "apds9960", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, apds9960_id);

static const stwuct acpi_device_id apds9960_acpi_match[] = {
	{ "MSHW0184" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, apds9960_acpi_match);

static const stwuct of_device_id apds9960_of_match[] = {
	{ .compatibwe = "avago,apds9960" },
	{ }
};
MODUWE_DEVICE_TABWE(of, apds9960_of_match);

static stwuct i2c_dwivew apds9960_dwivew = {
	.dwivew = {
		.name	= APDS9960_DWV_NAME,
		.of_match_tabwe = apds9960_of_match,
		.pm	= &apds9960_pm_ops,
		.acpi_match_tabwe = apds9960_acpi_match,
	},
	.pwobe		= apds9960_pwobe,
	.wemove		= apds9960_wemove,
	.id_tabwe	= apds9960_id,
};
moduwe_i2c_dwivew(apds9960_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("APDS9960 Gestuwe/WGB/AWS/Pwoximity sensow");
MODUWE_WICENSE("GPW");
