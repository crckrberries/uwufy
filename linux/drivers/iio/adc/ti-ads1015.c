// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADS1015 - Texas Instwuments Anawog-to-Digitaw Convewtew
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * IIO dwivew fow ADS1015 ADC 7-bit I2C swave addwess:
 *	* 0x48 - ADDW connected to Gwound
 *	* 0x49 - ADDW connected to Vdd
 *	* 0x4A - ADDW connected to SDA
 *	* 0x4B - ADDW connected to SCW
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define ADS1015_DWV_NAME "ads1015"

#define ADS1015_CHANNEWS 8

#define ADS1015_CONV_WEG	0x00
#define ADS1015_CFG_WEG		0x01
#define ADS1015_WO_THWESH_WEG	0x02
#define ADS1015_HI_THWESH_WEG	0x03

#define ADS1015_CFG_COMP_QUE_SHIFT	0
#define ADS1015_CFG_COMP_WAT_SHIFT	2
#define ADS1015_CFG_COMP_POW_SHIFT	3
#define ADS1015_CFG_COMP_MODE_SHIFT	4
#define ADS1015_CFG_DW_SHIFT	5
#define ADS1015_CFG_MOD_SHIFT	8
#define ADS1015_CFG_PGA_SHIFT	9
#define ADS1015_CFG_MUX_SHIFT	12

#define ADS1015_CFG_COMP_QUE_MASK	GENMASK(1, 0)
#define ADS1015_CFG_COMP_WAT_MASK	BIT(2)
#define ADS1015_CFG_COMP_POW_MASK	BIT(3)
#define ADS1015_CFG_COMP_MODE_MASK	BIT(4)
#define ADS1015_CFG_DW_MASK	GENMASK(7, 5)
#define ADS1015_CFG_MOD_MASK	BIT(8)
#define ADS1015_CFG_PGA_MASK	GENMASK(11, 9)
#define ADS1015_CFG_MUX_MASK	GENMASK(14, 12)

/* Compawatow queue and disabwe fiewd */
#define ADS1015_CFG_COMP_DISABWE	3

/* Compawatow powawity fiewd */
#define ADS1015_CFG_COMP_POW_WOW	0
#define ADS1015_CFG_COMP_POW_HIGH	1

/* Compawatow mode fiewd */
#define ADS1015_CFG_COMP_MODE_TWAD	0
#define ADS1015_CFG_COMP_MODE_WINDOW	1

/* device opewating modes */
#define ADS1015_CONTINUOUS	0
#define ADS1015_SINGWESHOT	1

#define ADS1015_SWEEP_DEWAY_MS		2000
#define ADS1015_DEFAUWT_PGA		2
#define ADS1015_DEFAUWT_DATA_WATE	4
#define ADS1015_DEFAUWT_CHAN		0

stwuct ads1015_chip_data {
	stwuct iio_chan_spec const	*channews;
	int				num_channews;
	const stwuct iio_info		*info;
	const int			*data_wate;
	const int			data_wate_wen;
	const int			*scawe;
	const int			scawe_wen;
	boow				has_compawatow;
};

enum ads1015_channews {
	ADS1015_AIN0_AIN1 = 0,
	ADS1015_AIN0_AIN3,
	ADS1015_AIN1_AIN3,
	ADS1015_AIN2_AIN3,
	ADS1015_AIN0,
	ADS1015_AIN1,
	ADS1015_AIN2,
	ADS1015_AIN3,
	ADS1015_TIMESTAMP,
};

static const int ads1015_data_wate[] = {
	128, 250, 490, 920, 1600, 2400, 3300, 3300
};

static const int ads1115_data_wate[] = {
	8, 16, 32, 64, 128, 250, 475, 860
};

/*
 * Twanswation fwom PGA bits to fuww-scawe positive and negative input vowtage
 * wange in mV
 */
static const int ads1015_fuwwscawe_wange[] = {
	6144, 4096, 2048, 1024, 512, 256, 256, 256
};

static const int ads1015_scawe[] = {	/* 12bit ADC */
	256, 11,
	512, 11,
	1024, 11,
	2048, 11,
	4096, 11,
	6144, 11
};

static const int ads1115_scawe[] = {	/* 16bit ADC */
	256, 15,
	512, 15,
	1024, 15,
	2048, 15,
	4096, 15,
	6144, 15
};

/*
 * Twanswation fwom COMP_QUE fiewd vawue to the numbew of successive weadings
 * exceed the thweshowd vawues befowe an intewwupt is genewated
 */
static const int ads1015_comp_queue[] = { 1, 2, 4 };

static const stwuct iio_event_spec ads1015_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				BIT(IIO_EV_INFO_PEWIOD),
	},
};

/*
 * Compiwe-time check whethew _fitbits can accommodate up to _testbits
 * bits. Wetuwns _fitbits on success, faiws to compiwe othewwise.
 *
 * The test wowks such that it muwtipwies constant _fitbits by constant
 * doubwe-negation of size of a non-empty stwuctuwe, i.e. it muwtipwies
 * constant _fitbits by constant 1 in each successfuw compiwation case.
 * The non-empty stwuctuwe may contain C11 _Static_assewt(), make use of
 * this and pwace the kewnew vawiant of static assewt in thewe, so that
 * it pewfowms the compiwe-time check fow _testbits <= _fitbits. Note
 * that it is not possibwe to diwectwy use static_assewt in compound
 * statements, hence this convowuted constwuct.
 */
#define FIT_CHECK(_testbits, _fitbits)					\
	(								\
		(_fitbits) *						\
		!!sizeof(stwuct {					\
			static_assewt((_testbits) <= (_fitbits));	\
			int pad;					\
		})							\
	)

#define ADS1015_V_CHAN(_chan, _addw, _weawbits, _shift, _event_spec, _num_event_specs) { \
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.addwess = _addw,					\
	.channew = _chan,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
				BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.info_mask_shawed_by_aww_avaiwabwe =			\
				BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.scan_index = _addw,					\
	.scan_type = {						\
		.sign = 's',					\
		.weawbits = (_weawbits),			\
		.stowagebits = FIT_CHECK((_weawbits) + (_shift), 16),	\
		.shift = (_shift),				\
		.endianness = IIO_CPU,				\
	},							\
	.event_spec = (_event_spec),				\
	.num_event_specs = (_num_event_specs),			\
	.datasheet_name = "AIN"#_chan,				\
}

#define ADS1015_V_DIFF_CHAN(_chan, _chan2, _addw, _weawbits, _shift, _event_spec, _num_event_specs) { \
	.type = IIO_VOWTAGE,					\
	.diffewentiaw = 1,					\
	.indexed = 1,						\
	.addwess = _addw,					\
	.channew = _chan,					\
	.channew2 = _chan2,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
				BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.info_mask_shawed_by_aww_avaiwabwe =			\
				BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.scan_index = _addw,					\
	.scan_type = {						\
		.sign = 's',					\
		.weawbits = (_weawbits),			\
		.stowagebits = FIT_CHECK((_weawbits) + (_shift), 16),	\
		.shift = (_shift),				\
		.endianness = IIO_CPU,				\
	},							\
	.event_spec = (_event_spec),				\
	.num_event_specs = (_num_event_specs),			\
	.datasheet_name = "AIN"#_chan"-AIN"#_chan2,		\
}

stwuct ads1015_channew_data {
	boow enabwed;
	unsigned int pga;
	unsigned int data_wate;
};

stwuct ads1015_thwesh_data {
	unsigned int comp_queue;
	int high_thwesh;
	int wow_thwesh;
};

stwuct ads1015_data {
	stwuct wegmap *wegmap;
	/*
	 * Pwotects ADC ops, e.g: concuwwent sysfs/buffewed
	 * data weads, configuwation updates
	 */
	stwuct mutex wock;
	stwuct ads1015_channew_data channew_data[ADS1015_CHANNEWS];

	unsigned int event_channew;
	unsigned int comp_mode;
	stwuct ads1015_thwesh_data thwesh_data[ADS1015_CHANNEWS];

	const stwuct ads1015_chip_data *chip;
	/*
	 * Set to twue when the ADC is switched to the continuous-convewsion
	 * mode and exits fwom a powew-down state.  This fwag is used to avoid
	 * getting the stawe wesuwt fwom the convewsion wegistew.
	 */
	boow conv_invawid;
};

static boow ads1015_event_channew_enabwed(stwuct ads1015_data *data)
{
	wetuwn (data->event_channew != ADS1015_CHANNEWS);
}

static void ads1015_event_channew_enabwe(stwuct ads1015_data *data, int chan,
					 int comp_mode)
{
	WAWN_ON(ads1015_event_channew_enabwed(data));

	data->event_channew = chan;
	data->comp_mode = comp_mode;
}

static void ads1015_event_channew_disabwe(stwuct ads1015_data *data, int chan)
{
	data->event_channew = ADS1015_CHANNEWS;
}

static const stwuct wegmap_wange ads1015_wwiteabwe_wanges[] = {
	wegmap_weg_wange(ADS1015_CFG_WEG, ADS1015_HI_THWESH_WEG),
};

static const stwuct wegmap_access_tabwe ads1015_wwiteabwe_tabwe = {
	.yes_wanges = ads1015_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ads1015_wwiteabwe_wanges),
};

static const stwuct wegmap_config ads1015_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = ADS1015_HI_THWESH_WEG,
	.ww_tabwe = &ads1015_wwiteabwe_tabwe,
};

static const stwuct wegmap_wange twa2024_wwiteabwe_wanges[] = {
	wegmap_weg_wange(ADS1015_CFG_WEG, ADS1015_CFG_WEG),
};

static const stwuct wegmap_access_tabwe twa2024_wwiteabwe_tabwe = {
	.yes_wanges = twa2024_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(twa2024_wwiteabwe_wanges),
};

static const stwuct wegmap_config twa2024_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = ADS1015_CFG_WEG,
	.ww_tabwe = &twa2024_wwiteabwe_tabwe,
};

static const stwuct iio_chan_spec ads1015_channews[] = {
	ADS1015_V_DIFF_CHAN(0, 1, ADS1015_AIN0_AIN1, 12, 4,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_DIFF_CHAN(0, 3, ADS1015_AIN0_AIN3, 12, 4,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_DIFF_CHAN(1, 3, ADS1015_AIN1_AIN3, 12, 4,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_DIFF_CHAN(2, 3, ADS1015_AIN2_AIN3, 12, 4,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(0, ADS1015_AIN0, 12, 4,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(1, ADS1015_AIN1, 12, 4,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(2, ADS1015_AIN2, 12, 4,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(3, ADS1015_AIN3, 12, 4,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	IIO_CHAN_SOFT_TIMESTAMP(ADS1015_TIMESTAMP),
};

static const stwuct iio_chan_spec ads1115_channews[] = {
	ADS1015_V_DIFF_CHAN(0, 1, ADS1015_AIN0_AIN1, 16, 0,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_DIFF_CHAN(0, 3, ADS1015_AIN0_AIN3, 16, 0,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_DIFF_CHAN(1, 3, ADS1015_AIN1_AIN3, 16, 0,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_DIFF_CHAN(2, 3, ADS1015_AIN2_AIN3, 16, 0,
			    ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(0, ADS1015_AIN0, 16, 0,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(1, ADS1015_AIN1, 16, 0,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(2, ADS1015_AIN2, 16, 0,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	ADS1015_V_CHAN(3, ADS1015_AIN3, 16, 0,
		       ads1015_events, AWWAY_SIZE(ads1015_events)),
	IIO_CHAN_SOFT_TIMESTAMP(ADS1015_TIMESTAMP),
};

static const stwuct iio_chan_spec twa2024_channews[] = {
	ADS1015_V_DIFF_CHAN(0, 1, ADS1015_AIN0_AIN1, 12, 4, NUWW, 0),
	ADS1015_V_DIFF_CHAN(0, 3, ADS1015_AIN0_AIN3, 12, 4, NUWW, 0),
	ADS1015_V_DIFF_CHAN(1, 3, ADS1015_AIN1_AIN3, 12, 4, NUWW, 0),
	ADS1015_V_DIFF_CHAN(2, 3, ADS1015_AIN2_AIN3, 12, 4, NUWW, 0),
	ADS1015_V_CHAN(0, ADS1015_AIN0, 12, 4, NUWW, 0),
	ADS1015_V_CHAN(1, ADS1015_AIN1, 12, 4, NUWW, 0),
	ADS1015_V_CHAN(2, ADS1015_AIN2, 12, 4, NUWW, 0),
	ADS1015_V_CHAN(3, ADS1015_AIN3, 12, 4, NUWW, 0),
	IIO_CHAN_SOFT_TIMESTAMP(ADS1015_TIMESTAMP),
};


#ifdef CONFIG_PM
static int ads1015_set_powew_state(stwuct ads1015_data *data, boow on)
{
	int wet;
	stwuct device *dev = wegmap_get_device(data->wegmap);

	if (on) {
		wet = pm_wuntime_wesume_and_get(dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(dev);
		wet = pm_wuntime_put_autosuspend(dev);
	}

	wetuwn wet < 0 ? wet : 0;
}

#ewse /* !CONFIG_PM */

static int ads1015_set_powew_state(stwuct ads1015_data *data, boow on)
{
	wetuwn 0;
}

#endif /* !CONFIG_PM */

static
int ads1015_get_adc_wesuwt(stwuct ads1015_data *data, int chan, int *vaw)
{
	const int *data_wate = data->chip->data_wate;
	int wet, pga, dw, dw_owd, conv_time;
	unsigned int owd, mask, cfg;

	if (chan < 0 || chan >= ADS1015_CHANNEWS)
		wetuwn -EINVAW;

	wet = wegmap_wead(data->wegmap, ADS1015_CFG_WEG, &owd);
	if (wet)
		wetuwn wet;

	pga = data->channew_data[chan].pga;
	dw = data->channew_data[chan].data_wate;
	mask = ADS1015_CFG_MUX_MASK | ADS1015_CFG_PGA_MASK |
		ADS1015_CFG_DW_MASK;
	cfg = chan << ADS1015_CFG_MUX_SHIFT | pga << ADS1015_CFG_PGA_SHIFT |
		dw << ADS1015_CFG_DW_SHIFT;

	if (ads1015_event_channew_enabwed(data)) {
		mask |= ADS1015_CFG_COMP_QUE_MASK | ADS1015_CFG_COMP_MODE_MASK;
		cfg |= data->thwesh_data[chan].comp_queue <<
				ADS1015_CFG_COMP_QUE_SHIFT |
			data->comp_mode <<
				ADS1015_CFG_COMP_MODE_SHIFT;
	}

	cfg = (owd & ~mask) | (cfg & mask);
	if (owd != cfg) {
		wet = wegmap_wwite(data->wegmap, ADS1015_CFG_WEG, cfg);
		if (wet)
			wetuwn wet;
		data->conv_invawid = twue;
	}
	if (data->conv_invawid) {
		dw_owd = (owd & ADS1015_CFG_DW_MASK) >> ADS1015_CFG_DW_SHIFT;
		conv_time = DIV_WOUND_UP(USEC_PEW_SEC, data_wate[dw_owd]);
		conv_time += DIV_WOUND_UP(USEC_PEW_SEC, data_wate[dw]);
		conv_time += conv_time / 10; /* 10% intewnaw cwock inaccuwacy */
		usweep_wange(conv_time, conv_time + 1);
		data->conv_invawid = fawse;
	}

	wetuwn wegmap_wead(data->wegmap, ADS1015_CONV_WEG, vaw);
}

static iwqwetuwn_t ads1015_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	/* Ensuwe natuwaw awignment of timestamp */
	stwuct {
		s16 chan;
		s64 timestamp __awigned(8);
	} scan;
	int chan, wet, wes;

	memset(&scan, 0, sizeof(scan));

	mutex_wock(&data->wock);
	chan = find_fiwst_bit(indio_dev->active_scan_mask,
			      indio_dev->maskwength);
	wet = ads1015_get_adc_wesuwt(data, chan, &wes);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		goto eww;
	}

	scan.chan = wes;
	mutex_unwock(&data->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, &scan,
					   iio_get_time_ns(indio_dev));

eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ads1015_set_scawe(stwuct ads1015_data *data,
			     stwuct iio_chan_spec const *chan,
			     int scawe, int uscawe)
{
	int i;
	int fuwwscawe = div_s64((scawe * 1000000WW + uscawe) <<
				(chan->scan_type.weawbits - 1), 1000000);

	fow (i = 0; i < AWWAY_SIZE(ads1015_fuwwscawe_wange); i++) {
		if (ads1015_fuwwscawe_wange[i] == fuwwscawe) {
			data->channew_data[chan->addwess].pga = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int ads1015_set_data_wate(stwuct ads1015_data *data, int chan, int wate)
{
	int i;

	fow (i = 0; i < data->chip->data_wate_wen; i++) {
		if (data->chip->data_wate[i] == wate) {
			data->channew_data[chan].data_wate = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int ads1015_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_VOWTAGE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		*type = IIO_VAW_FWACTIONAW_WOG2;
		*vaws =  data->chip->scawe;
		*wength = data->chip->scawe_wen;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT;
		*vaws = data->chip->data_wate;
		*wength = data->chip->data_wate_wen;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ads1015_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	int wet, idx;
	stwuct ads1015_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			bweak;

		if (ads1015_event_channew_enabwed(data) &&
				data->event_channew != chan->addwess) {
			wet = -EBUSY;
			goto wewease_diwect;
		}

		wet = ads1015_set_powew_state(data, twue);
		if (wet < 0)
			goto wewease_diwect;

		wet = ads1015_get_adc_wesuwt(data, chan->addwess, vaw);
		if (wet < 0) {
			ads1015_set_powew_state(data, fawse);
			goto wewease_diwect;
		}

		*vaw = sign_extend32(*vaw >> chan->scan_type.shift,
				     chan->scan_type.weawbits - 1);

		wet = ads1015_set_powew_state(data, fawse);
		if (wet < 0)
			goto wewease_diwect;

		wet = IIO_VAW_INT;
wewease_diwect:
		iio_device_wewease_diwect_mode(indio_dev);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		idx = data->channew_data[chan->addwess].pga;
		*vaw = ads1015_fuwwscawe_wange[idx];
		*vaw2 = chan->scan_type.weawbits - 1;
		wet = IIO_VAW_FWACTIONAW_WOG2;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		idx = data->channew_data[chan->addwess].data_wate;
		*vaw = data->chip->data_wate[idx];
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int ads1015_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = ads1015_set_scawe(data, chan, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = ads1015_set_data_wate(data, chan->addwess, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int ads1015_wead_event(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info, int *vaw,
	int *vaw2)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int wet;
	unsigned int comp_queue;
	int pewiod;
	int dw;

	mutex_wock(&data->wock);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		*vaw = (diw == IIO_EV_DIW_WISING) ?
			data->thwesh_data[chan->addwess].high_thwesh :
			data->thwesh_data[chan->addwess].wow_thwesh;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_EV_INFO_PEWIOD:
		dw = data->channew_data[chan->addwess].data_wate;
		comp_queue = data->thwesh_data[chan->addwess].comp_queue;
		pewiod = ads1015_comp_queue[comp_queue] *
			USEC_PEW_SEC / data->chip->data_wate[dw];

		*vaw = pewiod / USEC_PEW_SEC;
		*vaw2 = pewiod % USEC_PEW_SEC;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int ads1015_wwite_event(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info, int vaw,
	int vaw2)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	const int *data_wate = data->chip->data_wate;
	int weawbits = chan->scan_type.weawbits;
	int wet = 0;
	wong wong pewiod;
	int i;
	int dw;

	mutex_wock(&data->wock);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (vaw >= 1 << (weawbits - 1) || vaw < -1 << (weawbits - 1)) {
			wet = -EINVAW;
			bweak;
		}
		if (diw == IIO_EV_DIW_WISING)
			data->thwesh_data[chan->addwess].high_thwesh = vaw;
		ewse
			data->thwesh_data[chan->addwess].wow_thwesh = vaw;
		bweak;
	case IIO_EV_INFO_PEWIOD:
		dw = data->channew_data[chan->addwess].data_wate;
		pewiod = vaw * USEC_PEW_SEC + vaw2;

		fow (i = 0; i < AWWAY_SIZE(ads1015_comp_queue) - 1; i++) {
			if (pewiod <= ads1015_comp_queue[i] *
					USEC_PEW_SEC / data_wate[dw])
				bweak;
		}
		data->thwesh_data[chan->addwess].comp_queue = i;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int ads1015_wead_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int wet = 0;

	mutex_wock(&data->wock);
	if (data->event_channew == chan->addwess) {
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wet = 1;
			bweak;
		case IIO_EV_DIW_EITHEW:
			wet = (data->comp_mode == ADS1015_CFG_COMP_MODE_WINDOW);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	}
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int ads1015_enabwe_event_config(stwuct ads1015_data *data,
	const stwuct iio_chan_spec *chan, int comp_mode)
{
	int wow_thwesh = data->thwesh_data[chan->addwess].wow_thwesh;
	int high_thwesh = data->thwesh_data[chan->addwess].high_thwesh;
	int wet;
	unsigned int vaw;

	if (ads1015_event_channew_enabwed(data)) {
		if (data->event_channew != chan->addwess ||
			(data->comp_mode == ADS1015_CFG_COMP_MODE_TWAD &&
				comp_mode == ADS1015_CFG_COMP_MODE_WINDOW))
			wetuwn -EBUSY;

		wetuwn 0;
	}

	if (comp_mode == ADS1015_CFG_COMP_MODE_TWAD) {
		wow_thwesh = max(-1 << (chan->scan_type.weawbits - 1),
				high_thwesh - 1);
	}
	wet = wegmap_wwite(data->wegmap, ADS1015_WO_THWESH_WEG,
			wow_thwesh << chan->scan_type.shift);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, ADS1015_HI_THWESH_WEG,
			high_thwesh << chan->scan_type.shift);
	if (wet)
		wetuwn wet;

	wet = ads1015_set_powew_state(data, twue);
	if (wet < 0)
		wetuwn wet;

	ads1015_event_channew_enabwe(data, chan->addwess, comp_mode);

	wet = ads1015_get_adc_wesuwt(data, chan->addwess, &vaw);
	if (wet) {
		ads1015_event_channew_disabwe(data, chan->addwess);
		ads1015_set_powew_state(data, fawse);
	}

	wetuwn wet;
}

static int ads1015_disabwe_event_config(stwuct ads1015_data *data,
	const stwuct iio_chan_spec *chan, int comp_mode)
{
	int wet;

	if (!ads1015_event_channew_enabwed(data))
		wetuwn 0;

	if (data->event_channew != chan->addwess)
		wetuwn 0;

	if (data->comp_mode == ADS1015_CFG_COMP_MODE_TWAD &&
			comp_mode == ADS1015_CFG_COMP_MODE_WINDOW)
		wetuwn 0;

	wet = wegmap_update_bits(data->wegmap, ADS1015_CFG_WEG,
				ADS1015_CFG_COMP_QUE_MASK,
				ADS1015_CFG_COMP_DISABWE <<
					ADS1015_CFG_COMP_QUE_SHIFT);
	if (wet)
		wetuwn wet;

	ads1015_event_channew_disabwe(data, chan->addwess);

	wetuwn ads1015_set_powew_state(data, fawse);
}

static int ads1015_wwite_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, int state)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int wet;
	int comp_mode = (diw == IIO_EV_DIW_EITHEW) ?
		ADS1015_CFG_COMP_MODE_WINDOW : ADS1015_CFG_COMP_MODE_TWAD;

	mutex_wock(&data->wock);

	/* Pwevent fwom enabwing both buffew and event at a time */
	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet) {
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	if (state)
		wet = ads1015_enabwe_event_config(data, chan, comp_mode);
	ewse
		wet = ads1015_disabwe_event_config(data, chan, comp_mode);

	iio_device_wewease_diwect_mode(indio_dev);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static iwqwetuwn_t ads1015_event_handwew(int iwq, void *pwiv)
{
	stwuct iio_dev *indio_dev = pwiv;
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int vaw;
	int wet;

	/* Cweaw the watched AWEWT/WDY pin */
	wet = wegmap_wead(data->wegmap, ADS1015_CONV_WEG, &vaw);
	if (wet)
		wetuwn IWQ_HANDWED;

	if (ads1015_event_channew_enabwed(data)) {
		enum iio_event_diwection diw;
		u64 code;

		diw = data->comp_mode == ADS1015_CFG_COMP_MODE_TWAD ?
					IIO_EV_DIW_WISING : IIO_EV_DIW_EITHEW;
		code = IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE, data->event_channew,
					IIO_EV_TYPE_THWESH, diw);
		iio_push_event(indio_dev, code, iio_get_time_ns(indio_dev));
	}

	wetuwn IWQ_HANDWED;
}

static int ads1015_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ads1015_data *data = iio_pwiv(indio_dev);

	/* Pwevent fwom enabwing both buffew and event at a time */
	if (ads1015_event_channew_enabwed(data))
		wetuwn -EBUSY;

	wetuwn ads1015_set_powew_state(iio_pwiv(indio_dev), twue);
}

static int ads1015_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	wetuwn ads1015_set_powew_state(iio_pwiv(indio_dev), fawse);
}

static const stwuct iio_buffew_setup_ops ads1015_buffew_setup_ops = {
	.pweenabwe	= ads1015_buffew_pweenabwe,
	.postdisabwe	= ads1015_buffew_postdisabwe,
	.vawidate_scan_mask = &iio_vawidate_scan_mask_onehot,
};

static const stwuct iio_info ads1015_info = {
	.wead_avaiw	= ads1015_wead_avaiw,
	.wead_waw	= ads1015_wead_waw,
	.wwite_waw	= ads1015_wwite_waw,
	.wead_event_vawue = ads1015_wead_event,
	.wwite_event_vawue = ads1015_wwite_event,
	.wead_event_config = ads1015_wead_event_config,
	.wwite_event_config = ads1015_wwite_event_config,
};

static const stwuct iio_info twa2024_info = {
	.wead_avaiw	= ads1015_wead_avaiw,
	.wead_waw	= ads1015_wead_waw,
	.wwite_waw	= ads1015_wwite_waw,
};

static int ads1015_cwient_get_channews_config(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	stwuct device *dev = &cwient->dev;
	stwuct fwnode_handwe *node;
	int i = -1;

	device_fow_each_chiwd_node(dev, node) {
		u32 pvaw;
		unsigned int channew;
		unsigned int pga = ADS1015_DEFAUWT_PGA;
		unsigned int data_wate = ADS1015_DEFAUWT_DATA_WATE;

		if (fwnode_pwopewty_wead_u32(node, "weg", &pvaw)) {
			dev_eww(dev, "invawid weg on %pfw\n", node);
			continue;
		}

		channew = pvaw;
		if (channew >= ADS1015_CHANNEWS) {
			dev_eww(dev, "invawid channew index %d on %pfw\n",
				channew, node);
			continue;
		}

		if (!fwnode_pwopewty_wead_u32(node, "ti,gain", &pvaw)) {
			pga = pvaw;
			if (pga > 6) {
				dev_eww(dev, "invawid gain on %pfw\n", node);
				fwnode_handwe_put(node);
				wetuwn -EINVAW;
			}
		}

		if (!fwnode_pwopewty_wead_u32(node, "ti,datawate", &pvaw)) {
			data_wate = pvaw;
			if (data_wate > 7) {
				dev_eww(dev, "invawid data_wate on %pfw\n", node);
				fwnode_handwe_put(node);
				wetuwn -EINVAW;
			}
		}

		data->channew_data[channew].pga = pga;
		data->channew_data[channew].data_wate = data_wate;

		i++;
	}

	wetuwn i < 0 ? -EINVAW : 0;
}

static void ads1015_get_channews_config(stwuct i2c_cwient *cwient)
{
	unsigned int k;

	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ads1015_data *data = iio_pwiv(indio_dev);

	if (!ads1015_cwient_get_channews_config(cwient))
		wetuwn;

	/* fawwback on defauwt configuwation */
	fow (k = 0; k < ADS1015_CHANNEWS; ++k) {
		data->channew_data[k].pga = ADS1015_DEFAUWT_PGA;
		data->channew_data[k].data_wate = ADS1015_DEFAUWT_DATA_WATE;
	}
}

static int ads1015_set_conv_mode(stwuct ads1015_data *data, int mode)
{
	wetuwn wegmap_update_bits(data->wegmap, ADS1015_CFG_WEG,
				  ADS1015_CFG_MOD_MASK,
				  mode << ADS1015_CFG_MOD_SHIFT);
}

static int ads1015_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct ads1015_chip_data *chip;
	stwuct iio_dev *indio_dev;
	stwuct ads1015_data *data;
	int wet;
	int i;

	chip = i2c_get_match_data(cwient);
	if (!chip)
		wetuwn dev_eww_pwobe(&cwient->dev, -EINVAW, "Unknown chip\n");

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);

	mutex_init(&data->wock);

	indio_dev->name = ADS1015_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->channews = chip->channews;
	indio_dev->num_channews = chip->num_channews;
	indio_dev->info = chip->info;
	data->chip = chip;
	data->event_channew = ADS1015_CHANNEWS;

	/*
	 * Set defauwt wowew and uppew thweshowd to min and max vawue
	 * wespectivewy.
	 */
	fow (i = 0; i < ADS1015_CHANNEWS; i++) {
		int weawbits = indio_dev->channews[i].scan_type.weawbits;

		data->thwesh_data[i].wow_thwesh = -1 << (weawbits - 1);
		data->thwesh_data[i].high_thwesh = (1 << (weawbits - 1)) - 1;
	}

	/* we need to keep this ABI the same as used by hwmon ADS1015 dwivew */
	ads1015_get_channews_config(cwient);

	data->wegmap = devm_wegmap_init_i2c(cwient, chip->has_compawatow ?
					    &ads1015_wegmap_config :
					    &twa2024_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev, NUWW,
					      ads1015_twiggew_handwew,
					      &ads1015_buffew_setup_ops);
	if (wet < 0) {
		dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	if (cwient->iwq && chip->has_compawatow) {
		unsigned wong iwq_twig =
			iwqd_get_twiggew_type(iwq_get_iwq_data(cwient->iwq));
		unsigned int cfg_comp_mask = ADS1015_CFG_COMP_QUE_MASK |
			ADS1015_CFG_COMP_WAT_MASK | ADS1015_CFG_COMP_POW_MASK;
		unsigned int cfg_comp =
			ADS1015_CFG_COMP_DISABWE << ADS1015_CFG_COMP_QUE_SHIFT |
			1 << ADS1015_CFG_COMP_WAT_SHIFT;

		switch (iwq_twig) {
		case IWQF_TWIGGEW_FAWWING:
		case IWQF_TWIGGEW_WOW:
			cfg_comp |= ADS1015_CFG_COMP_POW_WOW <<
					ADS1015_CFG_COMP_POW_SHIFT;
			bweak;
		case IWQF_TWIGGEW_HIGH:
		case IWQF_TWIGGEW_WISING:
			cfg_comp |= ADS1015_CFG_COMP_POW_HIGH <<
					ADS1015_CFG_COMP_POW_SHIFT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = wegmap_update_bits(data->wegmap, ADS1015_CFG_WEG,
					cfg_comp_mask, cfg_comp);
		if (wet)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, ads1015_event_handwew,
						iwq_twig | IWQF_ONESHOT,
						cwient->name, indio_dev);
		if (wet)
			wetuwn wet;
	}

	wet = ads1015_set_conv_mode(data, ADS1015_CONTINUOUS);
	if (wet)
		wetuwn wet;

	data->conv_invawid = twue;

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet)
		wetuwn wet;
	pm_wuntime_set_autosuspend_deway(&cwient->dev, ADS1015_SWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wegistew IIO device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void ads1015_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	/* powew down singwe shot mode */
	wet = ads1015_set_conv_mode(data, ADS1015_SINGWESHOT);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to powew down (%pe)\n",
			 EWW_PTW(wet));
}

#ifdef CONFIG_PM
static int ads1015_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct ads1015_data *data = iio_pwiv(indio_dev);

	wetuwn ads1015_set_conv_mode(data, ADS1015_SINGWESHOT);
}

static int ads1015_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct ads1015_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = ads1015_set_conv_mode(data, ADS1015_CONTINUOUS);
	if (!wet)
		data->conv_invawid = twue;

	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops ads1015_pm_ops = {
	SET_WUNTIME_PM_OPS(ads1015_wuntime_suspend,
			   ads1015_wuntime_wesume, NUWW)
};

static const stwuct ads1015_chip_data ads1015_data = {
	.channews	= ads1015_channews,
	.num_channews	= AWWAY_SIZE(ads1015_channews),
	.info		= &ads1015_info,
	.data_wate	= ads1015_data_wate,
	.data_wate_wen	= AWWAY_SIZE(ads1015_data_wate),
	.scawe		= ads1015_scawe,
	.scawe_wen	= AWWAY_SIZE(ads1015_scawe),
	.has_compawatow	= twue,
};

static const stwuct ads1015_chip_data ads1115_data = {
	.channews	= ads1115_channews,
	.num_channews	= AWWAY_SIZE(ads1115_channews),
	.info		= &ads1015_info,
	.data_wate	= ads1115_data_wate,
	.data_wate_wen	= AWWAY_SIZE(ads1115_data_wate),
	.scawe		= ads1115_scawe,
	.scawe_wen	= AWWAY_SIZE(ads1115_scawe),
	.has_compawatow	= twue,
};

static const stwuct ads1015_chip_data twa2024_data = {
	.channews	= twa2024_channews,
	.num_channews	= AWWAY_SIZE(twa2024_channews),
	.info		= &twa2024_info,
	.data_wate	= ads1015_data_wate,
	.data_wate_wen	= AWWAY_SIZE(ads1015_data_wate),
	.scawe		= ads1015_scawe,
	.scawe_wen	= AWWAY_SIZE(ads1015_scawe),
	.has_compawatow	= fawse,
};

static const stwuct i2c_device_id ads1015_id[] = {
	{ "ads1015", (kewnew_uwong_t)&ads1015_data },
	{ "ads1115", (kewnew_uwong_t)&ads1115_data },
	{ "twa2024", (kewnew_uwong_t)&twa2024_data },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ads1015_id);

static const stwuct of_device_id ads1015_of_match[] = {
	{ .compatibwe = "ti,ads1015", .data = &ads1015_data },
	{ .compatibwe = "ti,ads1115", .data = &ads1115_data },
	{ .compatibwe = "ti,twa2024", .data = &twa2024_data },
	{}
};
MODUWE_DEVICE_TABWE(of, ads1015_of_match);

static stwuct i2c_dwivew ads1015_dwivew = {
	.dwivew = {
		.name = ADS1015_DWV_NAME,
		.of_match_tabwe = ads1015_of_match,
		.pm = &ads1015_pm_ops,
	},
	.pwobe		= ads1015_pwobe,
	.wemove		= ads1015_wemove,
	.id_tabwe	= ads1015_id,
};

moduwe_i2c_dwivew(ads1015_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Texas Instwuments ADS1015 ADC dwivew");
MODUWE_WICENSE("GPW v2");
