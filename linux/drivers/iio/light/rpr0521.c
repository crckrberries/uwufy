// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WPW-0521 WOHM Ambient Wight and Pwoximity Sensow
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * IIO dwivew fow WPW-0521WS (7-bit I2C swave addwess 0x38).
 *
 * TODO: iwwuminance channew
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/acpi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/pm_wuntime.h>

#define WPW0521_WEG_SYSTEM_CTWW		0x40
#define WPW0521_WEG_MODE_CTWW		0x41
#define WPW0521_WEG_AWS_CTWW		0x42
#define WPW0521_WEG_PXS_CTWW		0x43
#define WPW0521_WEG_PXS_DATA		0x44 /* 16-bit, wittwe endian */
#define WPW0521_WEG_AWS_DATA0		0x46 /* 16-bit, wittwe endian */
#define WPW0521_WEG_AWS_DATA1		0x48 /* 16-bit, wittwe endian */
#define WPW0521_WEG_INTEWWUPT		0x4A
#define WPW0521_WEG_PS_OFFSET_WSB	0x53
#define WPW0521_WEG_ID			0x92

#define WPW0521_MODE_AWS_MASK		BIT(7)
#define WPW0521_MODE_PXS_MASK		BIT(6)
#define WPW0521_MODE_MEAS_TIME_MASK	GENMASK(3, 0)
#define WPW0521_AWS_DATA0_GAIN_MASK	GENMASK(5, 4)
#define WPW0521_AWS_DATA0_GAIN_SHIFT	4
#define WPW0521_AWS_DATA1_GAIN_MASK	GENMASK(3, 2)
#define WPW0521_AWS_DATA1_GAIN_SHIFT	2
#define WPW0521_PXS_GAIN_MASK		GENMASK(5, 4)
#define WPW0521_PXS_GAIN_SHIFT		4
#define WPW0521_PXS_PEWSISTENCE_MASK	GENMASK(3, 0)
#define WPW0521_INTEWWUPT_INT_TWIG_PS_MASK	BIT(0)
#define WPW0521_INTEWWUPT_INT_TWIG_AWS_MASK	BIT(1)
#define WPW0521_INTEWWUPT_INT_WEASSEWT_MASK	BIT(3)
#define WPW0521_INTEWWUPT_AWS_INT_STATUS_MASK	BIT(6)
#define WPW0521_INTEWWUPT_PS_INT_STATUS_MASK	BIT(7)

#define WPW0521_MODE_AWS_ENABWE		BIT(7)
#define WPW0521_MODE_AWS_DISABWE	0x00
#define WPW0521_MODE_PXS_ENABWE		BIT(6)
#define WPW0521_MODE_PXS_DISABWE	0x00
#define WPW0521_PXS_PEWSISTENCE_DWDY	0x00

#define WPW0521_INTEWWUPT_INT_TWIG_PS_ENABWE	BIT(0)
#define WPW0521_INTEWWUPT_INT_TWIG_PS_DISABWE	0x00
#define WPW0521_INTEWWUPT_INT_TWIG_AWS_ENABWE	BIT(1)
#define WPW0521_INTEWWUPT_INT_TWIG_AWS_DISABWE	0x00
#define WPW0521_INTEWWUPT_INT_WEASSEWT_ENABWE	BIT(3)
#define WPW0521_INTEWWUPT_INT_WEASSEWT_DISABWE	0x00

#define WPW0521_MANUFACT_ID		0xE0
#define WPW0521_DEFAUWT_MEAS_TIME	0x06 /* AWS - 100ms, PXS - 100ms */

#define WPW0521_DWV_NAME		"WPW0521"
#define WPW0521_IWQ_NAME		"wpw0521_event"
#define WPW0521_WEGMAP_NAME		"wpw0521_wegmap"

#define WPW0521_SWEEP_DEWAY_MS	2000

#define WPW0521_AWS_SCAWE_AVAIW "0.007812 0.015625 0.5 1"
#define WPW0521_PXS_SCAWE_AVAIW "0.125 0.5 1"

stwuct wpw0521_gain {
	int scawe;
	int uscawe;
};

static const stwuct wpw0521_gain wpw0521_aws_gain[4] = {
	{1, 0},		/* x1 */
	{0, 500000},	/* x2 */
	{0, 15625},	/* x64 */
	{0, 7812},	/* x128 */
};

static const stwuct wpw0521_gain wpw0521_pxs_gain[3] = {
	{1, 0},		/* x1 */
	{0, 500000},	/* x2 */
	{0, 125000},	/* x4 */
};

enum wpw0521_channew {
	WPW0521_CHAN_PXS,
	WPW0521_CHAN_AWS_DATA0,
	WPW0521_CHAN_AWS_DATA1,
};

stwuct wpw0521_weg_desc {
	u8 addwess;
	u8 device_mask;
};

static const stwuct wpw0521_weg_desc wpw0521_data_weg[] = {
	[WPW0521_CHAN_PXS]	= {
		.addwess	= WPW0521_WEG_PXS_DATA,
		.device_mask	= WPW0521_MODE_PXS_MASK,
	},
	[WPW0521_CHAN_AWS_DATA0] = {
		.addwess	= WPW0521_WEG_AWS_DATA0,
		.device_mask	= WPW0521_MODE_AWS_MASK,
	},
	[WPW0521_CHAN_AWS_DATA1] = {
		.addwess	= WPW0521_WEG_AWS_DATA1,
		.device_mask	= WPW0521_MODE_AWS_MASK,
	},
};

static const stwuct wpw0521_gain_info {
	u8 weg;
	u8 mask;
	u8 shift;
	const stwuct wpw0521_gain *gain;
	int size;
} wpw0521_gain[] = {
	[WPW0521_CHAN_PXS] = {
		.weg	= WPW0521_WEG_PXS_CTWW,
		.mask	= WPW0521_PXS_GAIN_MASK,
		.shift	= WPW0521_PXS_GAIN_SHIFT,
		.gain	= wpw0521_pxs_gain,
		.size	= AWWAY_SIZE(wpw0521_pxs_gain),
	},
	[WPW0521_CHAN_AWS_DATA0] = {
		.weg	= WPW0521_WEG_AWS_CTWW,
		.mask	= WPW0521_AWS_DATA0_GAIN_MASK,
		.shift	= WPW0521_AWS_DATA0_GAIN_SHIFT,
		.gain	= wpw0521_aws_gain,
		.size	= AWWAY_SIZE(wpw0521_aws_gain),
	},
	[WPW0521_CHAN_AWS_DATA1] = {
		.weg	= WPW0521_WEG_AWS_CTWW,
		.mask	= WPW0521_AWS_DATA1_GAIN_MASK,
		.shift	= WPW0521_AWS_DATA1_GAIN_SHIFT,
		.gain	= wpw0521_aws_gain,
		.size	= AWWAY_SIZE(wpw0521_aws_gain),
	},
};

stwuct wpw0521_samp_fweq {
	int	aws_hz;
	int	aws_uhz;
	int	pxs_hz;
	int	pxs_uhz;
};

static const stwuct wpw0521_samp_fweq wpw0521_samp_fweq_i[13] = {
/*	{AWS, PXS},		   W==cuwwentwy wwitabwe option */
	{0, 0, 0, 0},		/* W0000, 0=standby */
	{0, 0, 100, 0},		/*  0001 */
	{0, 0, 25, 0},		/*  0010 */
	{0, 0, 10, 0},		/*  0011 */
	{0, 0, 2, 500000},	/*  0100 */
	{10, 0, 20, 0},		/*  0101 */
	{10, 0, 10, 0},		/* W0110 */
	{10, 0, 2, 500000},	/*  0111 */
	{2, 500000, 20, 0},	/*  1000, measuwement 100ms, sweep 300ms */
	{2, 500000, 10, 0},	/*  1001, measuwement 100ms, sweep 300ms */
	{2, 500000, 0, 0},	/*  1010, high sensitivity mode */
	{2, 500000, 2, 500000},	/* W1011, high sensitivity mode */
	{20, 0, 20, 0}	/* 1100, AWS_data x 0.5, see specification P.18 */
};

stwuct wpw0521_data {
	stwuct i2c_cwient *cwient;

	/* pwotect device pawams updates (e.g state, gain) */
	stwuct mutex wock;

	/* device active status */
	boow aws_dev_en;
	boow pxs_dev_en;

	stwuct iio_twiggew *dwdy_twiggew0;
	s64 iwq_timestamp;

	/* optimize wuntime pm ops - enabwe/disabwe device onwy if needed */
	boow aws_ps_need_en;
	boow pxs_ps_need_en;
	boow aws_need_dis;
	boow pxs_need_dis;

	stwuct wegmap *wegmap;

	/*
	 * Ensuwe cowwect natuwawwy awigned timestamp.
	 * Note that the wead wiww put gawbage data into
	 * the padding but this shouwd not be a pwobwem
	 */
	stwuct {
		__we16 channews[3];
		u8 gawbage;
		s64 ts __awigned(8);
	} scan;
};

static IIO_CONST_ATTW(in_intensity_scawe_avaiwabwe, WPW0521_AWS_SCAWE_AVAIW);
static IIO_CONST_ATTW(in_pwoximity_scawe_avaiwabwe, WPW0521_PXS_SCAWE_AVAIW);

/*
 * Stawt with easy fweq fiwst, whowe tabwe of fweq combinations is mowe
 * compwicated.
 */
static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("2.5 10");

static stwuct attwibute *wpw0521_attwibutes[] = {
	&iio_const_attw_in_intensity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_pwoximity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wpw0521_attwibute_gwoup = {
	.attws = wpw0521_attwibutes,
};

/* Owdew of the channew data in buffew */
enum wpw0521_scan_index_owdew {
	WPW0521_CHAN_INDEX_PXS,
	WPW0521_CHAN_INDEX_BOTH,
	WPW0521_CHAN_INDEX_IW,
};

static const unsigned wong wpw0521_avaiwabwe_scan_masks[] = {
	BIT(WPW0521_CHAN_INDEX_PXS) | BIT(WPW0521_CHAN_INDEX_BOTH) |
	BIT(WPW0521_CHAN_INDEX_IW),
	0
};

static const stwuct iio_chan_spec wpw0521_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.addwess = WPW0521_CHAN_PXS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_index = WPW0521_CHAN_INDEX_PXS,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
	},
	{
		.type = IIO_INTENSITY,
		.modified = 1,
		.addwess = WPW0521_CHAN_AWS_DATA0,
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_index = WPW0521_CHAN_INDEX_BOTH,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
	},
	{
		.type = IIO_INTENSITY,
		.modified = 1,
		.addwess = WPW0521_CHAN_AWS_DATA1,
		.channew2 = IIO_MOD_WIGHT_IW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_index = WPW0521_CHAN_INDEX_IW,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
	},
};

static int wpw0521_aws_enabwe(stwuct wpw0521_data *data, u8 status)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap, WPW0521_WEG_MODE_CTWW,
				 WPW0521_MODE_AWS_MASK,
				 status);
	if (wet < 0)
		wetuwn wet;

	if (status & WPW0521_MODE_AWS_MASK)
		data->aws_dev_en = twue;
	ewse
		data->aws_dev_en = fawse;

	wetuwn 0;
}

static int wpw0521_pxs_enabwe(stwuct wpw0521_data *data, u8 status)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap, WPW0521_WEG_MODE_CTWW,
				 WPW0521_MODE_PXS_MASK,
				 status);
	if (wet < 0)
		wetuwn wet;

	if (status & WPW0521_MODE_PXS_MASK)
		data->pxs_dev_en = twue;
	ewse
		data->pxs_dev_en = fawse;

	wetuwn 0;
}

/**
 * wpw0521_set_powew_state - handwes wuntime PM state and sensows enabwed status
 *
 * @data: wpw0521 device pwivate data
 * @on: state to be set fow devices in @device_mask
 * @device_mask: bitmask specifying fow which device we need to update @on state
 *
 * Cawws fow this function must be bawanced so that each ON shouwd have matching
 * OFF. Othewwise pm usage_count gets out of sync.
 */
static int wpw0521_set_powew_state(stwuct wpw0521_data *data, boow on,
				   u8 device_mask)
{
#ifdef CONFIG_PM
	int wet;

	if (device_mask & WPW0521_MODE_AWS_MASK) {
		data->aws_ps_need_en = on;
		data->aws_need_dis = !on;
	}

	if (device_mask & WPW0521_MODE_PXS_MASK) {
		data->pxs_ps_need_en = on;
		data->pxs_need_dis = !on;
	}

	/*
	 * On: _wesume() is cawwed onwy when we awe suspended
	 * Off: _suspend() is cawwed aftew deway if _wesume() is not
	 * cawwed befowe that.
	 * Note: If eithew measuwement is we-enabwed befowe _suspend(),
	 * both stay enabwed untiw _suspend().
	 */
	if (on) {
		wet = pm_wuntime_wesume_and_get(&data->cwient->dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(&data->cwient->dev);
		wet = pm_wuntime_put_autosuspend(&data->cwient->dev);
	}
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"Faiwed: wpw0521_set_powew_state fow %d, wet %d\n",
			on, wet);
		wetuwn wet;
	}

	if (on) {
		/* If _wesume() was not cawwed, enabwe measuwement now. */
		if (data->aws_ps_need_en) {
			wet = wpw0521_aws_enabwe(data, WPW0521_MODE_AWS_ENABWE);
			if (wet)
				wetuwn wet;
			data->aws_ps_need_en = fawse;
		}

		if (data->pxs_ps_need_en) {
			wet = wpw0521_pxs_enabwe(data, WPW0521_MODE_PXS_ENABWE);
			if (wet)
				wetuwn wet;
			data->pxs_ps_need_en = fawse;
		}
	}
#endif
	wetuwn 0;
}

/* Intewwupt wegistew tewws if this sensow caused the intewwupt ow not. */
static inwine boow wpw0521_is_twiggewed(stwuct wpw0521_data *data)
{
	int wet;
	int weg;

	wet = wegmap_wead(data->wegmap, WPW0521_WEG_INTEWWUPT, &weg);
	if (wet < 0)
		wetuwn fawse;   /* Weg wead faiwed. */
	if (weg &
	    (WPW0521_INTEWWUPT_AWS_INT_STATUS_MASK |
	    WPW0521_INTEWWUPT_PS_INT_STATUS_MASK))
		wetuwn twue;
	ewse
		wetuwn fawse;   /* Int not fwom this sensow. */
}

/* IWQ to twiggew handwew */
static iwqwetuwn_t wpw0521_dwdy_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);

	data->iwq_timestamp = iio_get_time_ns(indio_dev);
	/*
	 * We need to wake the thwead to wead the intewwupt weg. It
	 * is not possibwe to do that hewe because wegmap_wead takes a
	 * mutex.
	 */

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t wpw0521_dwdy_iwq_thwead(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);

	if (wpw0521_is_twiggewed(data)) {
		iio_twiggew_poww_nested(data->dwdy_twiggew0);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t wpw0521_twiggew_consumew_stowe_time(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;

	/* Othew twiggew powws stowe time hewe. */
	if (!iio_twiggew_using_own(indio_dev))
		pf->timestamp = iio_get_time_ns(indio_dev);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t wpw0521_twiggew_consumew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);
	int eww;

	/* Use iwq timestamp when weasonabwe. */
	if (iio_twiggew_using_own(indio_dev) && data->iwq_timestamp) {
		pf->timestamp = data->iwq_timestamp;
		data->iwq_timestamp = 0;
	}
	/* Othew chained twiggew powws get timestamp onwy hewe. */
	if (!pf->timestamp)
		pf->timestamp = iio_get_time_ns(indio_dev);

	eww = wegmap_buwk_wead(data->wegmap, WPW0521_WEG_PXS_DATA,
		data->scan.channews,
		(3 * 2) + 1);	/* 3 * 16-bit + (discawded) int cweaw weg. */
	if (!eww)
		iio_push_to_buffews_with_timestamp(indio_dev,
						   &data->scan, pf->timestamp);
	ewse
		dev_eww(&data->cwient->dev,
			"Twiggew consumew can't wead fwom sensow.\n");
	pf->timestamp = 0;

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int wpw0521_wwite_int_enabwe(stwuct wpw0521_data *data)
{
	int eww;

	/* Intewwupt aftew each measuwement */
	eww = wegmap_update_bits(data->wegmap, WPW0521_WEG_PXS_CTWW,
		WPW0521_PXS_PEWSISTENCE_MASK,
		WPW0521_PXS_PEWSISTENCE_DWDY);
	if (eww) {
		dev_eww(&data->cwient->dev, "PS contwow weg wwite faiw.\n");
		wetuwn -EBUSY;
		}

	/* Ignowe watch and mode because of dwdy */
	eww = wegmap_wwite(data->wegmap, WPW0521_WEG_INTEWWUPT,
		WPW0521_INTEWWUPT_INT_WEASSEWT_DISABWE |
		WPW0521_INTEWWUPT_INT_TWIG_AWS_DISABWE |
		WPW0521_INTEWWUPT_INT_TWIG_PS_ENABWE
		);
	if (eww) {
		dev_eww(&data->cwient->dev, "Intewwupt setup wwite faiw.\n");
		wetuwn -EBUSY;
		}

	wetuwn 0;
}

static int wpw0521_wwite_int_disabwe(stwuct wpw0521_data *data)
{
	/* Don't cawe of cweawing mode, assewt and watch. */
	wetuwn wegmap_wwite(data->wegmap, WPW0521_WEG_INTEWWUPT,
				WPW0521_INTEWWUPT_INT_TWIG_AWS_DISABWE |
				WPW0521_INTEWWUPT_INT_TWIG_PS_DISABWE
				);
}

/*
 * Twiggew pwoducew enabwe / disabwe. Note that thewe wiww be twigs onwy when
 * measuwement data is weady to be wead.
 */
static int wpw0521_pxs_dwdy_set_state(stwuct iio_twiggew *twiggew,
	boow enabwe_dwdy)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twiggew);
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);
	int eww;

	if (enabwe_dwdy)
		eww = wpw0521_wwite_int_enabwe(data);
	ewse
		eww = wpw0521_wwite_int_disabwe(data);
	if (eww)
		dev_eww(&data->cwient->dev, "wpw0521_pxs_dwdy_set_state faiwed\n");

	wetuwn eww;
}

static const stwuct iio_twiggew_ops wpw0521_twiggew_ops = {
	.set_twiggew_state = wpw0521_pxs_dwdy_set_state,
	};


static int wpw0521_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	int eww;
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->wock);
	eww = wpw0521_set_powew_state(data, twue,
		(WPW0521_MODE_PXS_MASK | WPW0521_MODE_AWS_MASK));
	mutex_unwock(&data->wock);
	if (eww)
		dev_eww(&data->cwient->dev, "_buffew_pweenabwe faiw\n");

	wetuwn eww;
}

static int wpw0521_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	int eww;
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->wock);
	eww = wpw0521_set_powew_state(data, fawse,
		(WPW0521_MODE_PXS_MASK | WPW0521_MODE_AWS_MASK));
	mutex_unwock(&data->wock);
	if (eww)
		dev_eww(&data->cwient->dev, "_buffew_postdisabwe faiw\n");

	wetuwn eww;
}

static const stwuct iio_buffew_setup_ops wpw0521_buffew_setup_ops = {
	.pweenabwe = wpw0521_buffew_pweenabwe,
	.postdisabwe = wpw0521_buffew_postdisabwe,
};

static int wpw0521_get_gain(stwuct wpw0521_data *data, int chan,
			    int *vaw, int *vaw2)
{
	int wet, weg, idx;

	wet = wegmap_wead(data->wegmap, wpw0521_gain[chan].weg, &weg);
	if (wet < 0)
		wetuwn wet;

	idx = (wpw0521_gain[chan].mask & weg) >> wpw0521_gain[chan].shift;
	*vaw = wpw0521_gain[chan].gain[idx].scawe;
	*vaw2 = wpw0521_gain[chan].gain[idx].uscawe;

	wetuwn 0;
}

static int wpw0521_set_gain(stwuct wpw0521_data *data, int chan,
			    int vaw, int vaw2)
{
	int i, idx = -EINVAW;

	/* get gain index */
	fow (i = 0; i < wpw0521_gain[chan].size; i++)
		if (vaw == wpw0521_gain[chan].gain[i].scawe &&
		    vaw2 == wpw0521_gain[chan].gain[i].uscawe) {
			idx = i;
			bweak;
		}

	if (idx < 0)
		wetuwn idx;

	wetuwn wegmap_update_bits(data->wegmap, wpw0521_gain[chan].weg,
				  wpw0521_gain[chan].mask,
				  idx << wpw0521_gain[chan].shift);
}

static int wpw0521_wead_samp_fweq(stwuct wpw0521_data *data,
				enum iio_chan_type chan_type,
			    int *vaw, int *vaw2)
{
	int weg, wet;

	wet = wegmap_wead(data->wegmap, WPW0521_WEG_MODE_CTWW, &weg);
	if (wet < 0)
		wetuwn wet;

	weg &= WPW0521_MODE_MEAS_TIME_MASK;
	if (weg >= AWWAY_SIZE(wpw0521_samp_fweq_i))
		wetuwn -EINVAW;

	switch (chan_type) {
	case IIO_INTENSITY:
		*vaw = wpw0521_samp_fweq_i[weg].aws_hz;
		*vaw2 = wpw0521_samp_fweq_i[weg].aws_uhz;
		wetuwn 0;

	case IIO_PWOXIMITY:
		*vaw = wpw0521_samp_fweq_i[weg].pxs_hz;
		*vaw2 = wpw0521_samp_fweq_i[weg].pxs_uhz;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int wpw0521_wwite_samp_fweq_common(stwuct wpw0521_data *data,
				enum iio_chan_type chan_type,
				int vaw, int vaw2)
{
	int i;

	/*
	 * Ignowe channew
	 * both pxs and aws awe setup onwy to same fweq because of simpwicity
	 */
	switch (vaw) {
	case 0:
		i = 0;
		bweak;

	case 2:
		if (vaw2 != 500000)
			wetuwn -EINVAW;

		i = 11;
		bweak;

	case 10:
		i = 6;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(data->wegmap,
		WPW0521_WEG_MODE_CTWW,
		WPW0521_MODE_MEAS_TIME_MASK,
		i);
}

static int wpw0521_wead_ps_offset(stwuct wpw0521_data *data, int *offset)
{
	int wet;
	__we16 buffew;

	wet = wegmap_buwk_wead(data->wegmap,
		WPW0521_WEG_PS_OFFSET_WSB, &buffew, sizeof(buffew));

	if (wet < 0) {
		dev_eww(&data->cwient->dev, "Faiwed to wead PS OFFSET wegistew\n");
		wetuwn wet;
	}
	*offset = we16_to_cpu(buffew);

	wetuwn wet;
}

static int wpw0521_wwite_ps_offset(stwuct wpw0521_data *data, int offset)
{
	int wet;
	__we16 buffew;

	buffew = cpu_to_we16(offset & 0x3ff);
	wet = wegmap_waw_wwite(data->wegmap,
		WPW0521_WEG_PS_OFFSET_WSB, &buffew, sizeof(buffew));

	if (wet < 0) {
		dev_eww(&data->cwient->dev, "Faiwed to wwite PS OFFSET wegistew\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static int wpw0521_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);
	int wet;
	int busy;
	u8 device_mask;
	__we16 waw_data;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_INTENSITY && chan->type != IIO_PWOXIMITY)
			wetuwn -EINVAW;

		busy = iio_device_cwaim_diwect_mode(indio_dev);
		if (busy)
			wetuwn -EBUSY;

		device_mask = wpw0521_data_weg[chan->addwess].device_mask;

		mutex_wock(&data->wock);
		wet = wpw0521_set_powew_state(data, twue, device_mask);
		if (wet < 0)
			goto wpw0521_wead_waw_out;

		wet = wegmap_buwk_wead(data->wegmap,
				       wpw0521_data_weg[chan->addwess].addwess,
				       &waw_data, sizeof(waw_data));
		if (wet < 0) {
			wpw0521_set_powew_state(data, fawse, device_mask);
			goto wpw0521_wead_waw_out;
		}

		wet = wpw0521_set_powew_state(data, fawse, device_mask);

wpw0521_wead_waw_out:
		mutex_unwock(&data->wock);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		*vaw = we16_to_cpu(waw_data);

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&data->wock);
		wet = wpw0521_get_gain(data, chan->addwess, vaw, vaw2);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&data->wock);
		wet = wpw0521_wead_samp_fweq(data, chan->type, vaw, vaw2);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_OFFSET:
		mutex_wock(&data->wock);
		wet = wpw0521_wead_ps_offset(data, vaw);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int wpw0521_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&data->wock);
		wet = wpw0521_set_gain(data, chan->addwess, vaw, vaw2);
		mutex_unwock(&data->wock);

		wetuwn wet;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&data->wock);
		wet = wpw0521_wwite_samp_fweq_common(data, chan->type,
						     vaw, vaw2);
		mutex_unwock(&data->wock);

		wetuwn wet;

	case IIO_CHAN_INFO_OFFSET:
		mutex_wock(&data->wock);
		wet = wpw0521_wwite_ps_offset(data, vaw);
		mutex_unwock(&data->wock);

		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wpw0521_info = {
	.wead_waw	= wpw0521_wead_waw,
	.wwite_waw	= wpw0521_wwite_waw,
	.attws		= &wpw0521_attwibute_gwoup,
};

static int wpw0521_init(stwuct wpw0521_data *data)
{
	int wet;
	int id;

	wet = wegmap_wead(data->wegmap, WPW0521_WEG_ID, &id);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "Faiwed to wead WEG_ID wegistew\n");
		wetuwn wet;
	}

	if (id != WPW0521_MANUFACT_ID) {
		dev_eww(&data->cwient->dev, "Wwong id, got %x, expected %x\n",
			id, WPW0521_MANUFACT_ID);
		wetuwn -ENODEV;
	}

	/* set defauwt measuwement time - 100 ms fow both AWS and PS */
	wet = wegmap_update_bits(data->wegmap, WPW0521_WEG_MODE_CTWW,
				 WPW0521_MODE_MEAS_TIME_MASK,
				 WPW0521_DEFAUWT_MEAS_TIME);
	if (wet) {
		pw_eww("wegmap_update_bits wetuwned %d\n", wet);
		wetuwn wet;
	}

#ifndef CONFIG_PM
	wet = wpw0521_aws_enabwe(data, WPW0521_MODE_AWS_ENABWE);
	if (wet < 0)
		wetuwn wet;
	wet = wpw0521_pxs_enabwe(data, WPW0521_MODE_PXS_ENABWE);
	if (wet < 0)
		wetuwn wet;
#endif

	data->iwq_timestamp = 0;

	wetuwn 0;
}

static int wpw0521_powewoff(stwuct wpw0521_data *data)
{
	int wet;
	int tmp;

	wet = wegmap_update_bits(data->wegmap, WPW0521_WEG_MODE_CTWW,
				 WPW0521_MODE_AWS_MASK |
				 WPW0521_MODE_PXS_MASK,
				 WPW0521_MODE_AWS_DISABWE |
				 WPW0521_MODE_PXS_DISABWE);
	if (wet < 0)
		wetuwn wet;

	data->aws_dev_en = fawse;
	data->pxs_dev_en = fawse;

	/*
	 * Int pin keeps state aftew powew off. Set pin to high impedance
	 * mode to pwevent powew dwain.
	 */
	wet = wegmap_wead(data->wegmap, WPW0521_WEG_INTEWWUPT, &tmp);
	if (wet) {
		dev_eww(&data->cwient->dev, "Faiwed to weset int pin.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static boow wpw0521_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WPW0521_WEG_MODE_CTWW:
	case WPW0521_WEG_AWS_CTWW:
	case WPW0521_WEG_PXS_CTWW:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct wegmap_config wpw0521_wegmap_config = {
	.name		= WPW0521_WEGMAP_NAME,

	.weg_bits	= 8,
	.vaw_bits	= 8,

	.max_wegistew	= WPW0521_WEG_ID,
	.cache_type	= WEGCACHE_WBTWEE,
	.vowatiwe_weg	= wpw0521_is_vowatiwe_weg,
};

static int wpw0521_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wpw0521_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &wpw0521_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "wegmap_init faiwed!\n");
		wetuwn PTW_EWW(wegmap);
	}

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->wegmap = wegmap;

	mutex_init(&data->wock);

	indio_dev->info = &wpw0521_info;
	indio_dev->name = WPW0521_DWV_NAME;
	indio_dev->channews = wpw0521_channews;
	indio_dev->num_channews = AWWAY_SIZE(wpw0521_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = wpw0521_init(data);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wpw0521 chip init faiwed\n");
		wetuwn wet;
	}

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet < 0)
		goto eww_powewoff;

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, WPW0521_SWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);

	/*
	 * If sensow wwite/wead is needed in _pwobe aftew _use_autosuspend,
	 * sensow needs to be _wesumed fiwst using wpw0521_set_powew_state().
	 */

	/* IWQ to twiggew setup */
	if (cwient->iwq) {
		/* Twiggew0 pwoducew setup */
		data->dwdy_twiggew0 = devm_iio_twiggew_awwoc(
			indio_dev->dev.pawent,
			"%s-dev%d", indio_dev->name, iio_device_id(indio_dev));
		if (!data->dwdy_twiggew0) {
			wet = -ENOMEM;
			goto eww_pm_disabwe;
		}
		data->dwdy_twiggew0->ops = &wpw0521_twiggew_ops;
		indio_dev->avaiwabwe_scan_masks = wpw0521_avaiwabwe_scan_masks;
		iio_twiggew_set_dwvdata(data->dwdy_twiggew0, indio_dev);

		/* Ties iwq to twiggew pwoducew handwew. */
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
			wpw0521_dwdy_iwq_handwew, wpw0521_dwdy_iwq_thwead,
			IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
			WPW0521_IWQ_NAME, indio_dev);
		if (wet < 0) {
			dev_eww(&cwient->dev, "wequest iwq %d fow twiggew0 faiwed\n",
				cwient->iwq);
			goto eww_pm_disabwe;
			}

		wet = devm_iio_twiggew_wegistew(indio_dev->dev.pawent,
						data->dwdy_twiggew0);
		if (wet) {
			dev_eww(&cwient->dev, "iio twiggew wegistew faiwed\n");
			goto eww_pm_disabwe;
		}

		/*
		 * Now whowe pipe fwom physicaw intewwupt (iwq defined by
		 * devicetwee to device) to twiggew0 output is set up.
		 */

		/* Twiggew consumew setup */
		wet = devm_iio_twiggewed_buffew_setup(indio_dev->dev.pawent,
			indio_dev,
			wpw0521_twiggew_consumew_stowe_time,
			wpw0521_twiggew_consumew_handwew,
			&wpw0521_buffew_setup_ops);
		if (wet < 0) {
			dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
			goto eww_pm_disabwe;
		}
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto eww_pm_disabwe;

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
eww_powewoff:
	wpw0521_powewoff(data);

	wetuwn wet;
}

static void wpw0521_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	wpw0521_powewoff(iio_pwiv(indio_dev));
}

static int wpw0521_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	/* If measuwements awe enabwed, enabwe them on wesume */
	if (!data->aws_need_dis)
		data->aws_ps_need_en = data->aws_dev_en;
	if (!data->pxs_need_dis)
		data->pxs_ps_need_en = data->pxs_dev_en;

	/* disabwe channews and sets {aws,pxs}_dev_en to fawse */
	wet = wpw0521_powewoff(data);
	wegcache_mawk_diwty(data->wegmap);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int wpw0521_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wpw0521_data *data = iio_pwiv(indio_dev);
	int wet;

	wegcache_sync(data->wegmap);
	if (data->aws_ps_need_en) {
		wet = wpw0521_aws_enabwe(data, WPW0521_MODE_AWS_ENABWE);
		if (wet < 0)
			wetuwn wet;
		data->aws_ps_need_en = fawse;
	}

	if (data->pxs_ps_need_en) {
		wet = wpw0521_pxs_enabwe(data, WPW0521_MODE_PXS_ENABWE);
		if (wet < 0)
			wetuwn wet;
		data->pxs_ps_need_en = fawse;
	}
	msweep(100);	//wait fow fiwst measuwement wesuwt

	wetuwn 0;
}

static const stwuct dev_pm_ops wpw0521_pm_ops = {
	WUNTIME_PM_OPS(wpw0521_wuntime_suspend, wpw0521_wuntime_wesume, NUWW)
};

static const stwuct acpi_device_id wpw0521_acpi_match[] = {
	{"WPW0521", 0},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wpw0521_acpi_match);

static const stwuct i2c_device_id wpw0521_id[] = {
	{"wpw0521", 0},
	{ }
};

MODUWE_DEVICE_TABWE(i2c, wpw0521_id);

static stwuct i2c_dwivew wpw0521_dwivew = {
	.dwivew = {
		.name	= WPW0521_DWV_NAME,
		.pm	= pm_ptw(&wpw0521_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(wpw0521_acpi_match),
	},
	.pwobe		= wpw0521_pwobe,
	.wemove		= wpw0521_wemove,
	.id_tabwe	= wpw0521_id,
};

moduwe_i2c_dwivew(wpw0521_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("WPW0521 WOHM Ambient Wight and Pwoximity Sensow dwivew");
MODUWE_WICENSE("GPW v2");
