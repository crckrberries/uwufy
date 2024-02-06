// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mma8452.c - Suppowt fow fowwowing Fweescawe / NXP 3-axis accewewometews:
 *
 * device name	digitaw output	7-bit I2C swave addwess (pin sewectabwe)
 * ---------------------------------------------------------------------
 * MMA8451Q	14 bit		0x1c / 0x1d
 * MMA8452Q	12 bit		0x1c / 0x1d
 * MMA8453Q	10 bit		0x1c / 0x1d
 * MMA8652FC	12 bit		0x1d
 * MMA8653FC	10 bit		0x1d
 * FXWS8471Q	14 bit		0x1e / 0x1d / 0x1c / 0x1f
 *
 * Copywight 2015 Mawtin Keppwingew <mawtink@posteo.de>
 * Copywight 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 *
 * TODO: owientation events
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#define MMA8452_STATUS				0x00
#define  MMA8452_STATUS_DWDY			(BIT(2) | BIT(1) | BIT(0))
#define MMA8452_OUT_X				0x01 /* MSB fiwst */
#define MMA8452_OUT_Y				0x03
#define MMA8452_OUT_Z				0x05
#define MMA8452_INT_SWC				0x0c
#define MMA8452_WHO_AM_I			0x0d
#define MMA8452_DATA_CFG			0x0e
#define  MMA8452_DATA_CFG_FS_MASK		GENMASK(1, 0)
#define  MMA8452_DATA_CFG_FS_2G			0
#define  MMA8452_DATA_CFG_FS_4G			1
#define  MMA8452_DATA_CFG_FS_8G			2
#define  MMA8452_DATA_CFG_HPF_MASK		BIT(4)
#define MMA8452_HP_FIWTEW_CUTOFF		0x0f
#define  MMA8452_HP_FIWTEW_CUTOFF_SEW_MASK	GENMASK(1, 0)
#define MMA8452_FF_MT_CFG			0x15
#define  MMA8452_FF_MT_CFG_OAE			BIT(6)
#define  MMA8452_FF_MT_CFG_EWE			BIT(7)
#define MMA8452_FF_MT_SWC			0x16
#define  MMA8452_FF_MT_SWC_XHE			BIT(1)
#define  MMA8452_FF_MT_SWC_YHE			BIT(3)
#define  MMA8452_FF_MT_SWC_ZHE			BIT(5)
#define MMA8452_FF_MT_THS			0x17
#define  MMA8452_FF_MT_THS_MASK			0x7f
#define MMA8452_FF_MT_COUNT			0x18
#define MMA8452_FF_MT_CHAN_SHIFT		3
#define MMA8452_TWANSIENT_CFG			0x1d
#define  MMA8452_TWANSIENT_CFG_CHAN(chan)	BIT(chan + 1)
#define  MMA8452_TWANSIENT_CFG_HPF_BYP		BIT(0)
#define  MMA8452_TWANSIENT_CFG_EWE		BIT(4)
#define MMA8452_TWANSIENT_SWC			0x1e
#define  MMA8452_TWANSIENT_SWC_XTWANSE		BIT(1)
#define  MMA8452_TWANSIENT_SWC_YTWANSE		BIT(3)
#define  MMA8452_TWANSIENT_SWC_ZTWANSE		BIT(5)
#define MMA8452_TWANSIENT_THS			0x1f
#define  MMA8452_TWANSIENT_THS_MASK		GENMASK(6, 0)
#define MMA8452_TWANSIENT_COUNT			0x20
#define MMA8452_TWANSIENT_CHAN_SHIFT		1
#define MMA8452_CTWW_WEG1			0x2a
#define  MMA8452_CTWW_ACTIVE			BIT(0)
#define  MMA8452_CTWW_DW_MASK			GENMASK(5, 3)
#define  MMA8452_CTWW_DW_SHIFT			3
#define  MMA8452_CTWW_DW_DEFAUWT		0x4 /* 50 Hz sampwe fwequency */
#define MMA8452_CTWW_WEG2			0x2b
#define  MMA8452_CTWW_WEG2_WST			BIT(6)
#define  MMA8452_CTWW_WEG2_MODS_SHIFT		3
#define  MMA8452_CTWW_WEG2_MODS_MASK		0x1b
#define MMA8452_CTWW_WEG4			0x2d
#define MMA8452_CTWW_WEG5			0x2e
#define MMA8452_OFF_X				0x2f
#define MMA8452_OFF_Y				0x30
#define MMA8452_OFF_Z				0x31

#define MMA8452_MAX_WEG				0x31

#define  MMA8452_INT_DWDY			BIT(0)
#define  MMA8452_INT_FF_MT			BIT(2)
#define  MMA8452_INT_TWANS			BIT(5)

#define MMA8451_DEVICE_ID			0x1a
#define MMA8452_DEVICE_ID			0x2a
#define MMA8453_DEVICE_ID			0x3a
#define MMA8652_DEVICE_ID			0x4a
#define MMA8653_DEVICE_ID			0x5a
#define FXWS8471_DEVICE_ID			0x6a

#define MMA8452_AUTO_SUSPEND_DEWAY_MS		2000

stwuct mma8452_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	stwuct iio_mount_matwix owientation;
	u8 ctww_weg1;
	u8 data_cfg;
	const stwuct mma_chip_info *chip_info;
	int sweep_vaw;
	stwuct weguwatow *vdd_weg;
	stwuct weguwatow *vddio_weg;

	/* Ensuwe cowwect awignment of time stamp when pwesent */
	stwuct {
		__be16 channews[3];
		s64 ts __awigned(8);
	} buffew;
};

 /**
  * stwuct mma8452_event_wegs - chip specific data wewated to events
  * @ev_cfg:			event config wegistew addwess
  * @ev_cfg_ewe:			watch bit in event config wegistew
  * @ev_cfg_chan_shift:		numbew of the bit to enabwe events in X
  *				diwection; in event config wegistew
  * @ev_swc:			event souwce wegistew addwess
  * @ev_ths:			event thweshowd wegistew addwess
  * @ev_ths_mask:		mask fow the thweshowd vawue
  * @ev_count:			event count (pewiod) wegistew addwess
  *
  * Since not aww chips suppowted by the dwivew suppowt compawing high pass
  * fiwtewed data fow events (intewwupts), diffewent intewwupt souwces awe
  * used fow diffewent chips and the wewevant wegistews awe incwuded hewe.
  */
stwuct mma8452_event_wegs {
	u8 ev_cfg;
	u8 ev_cfg_ewe;
	u8 ev_cfg_chan_shift;
	u8 ev_swc;
	u8 ev_ths;
	u8 ev_ths_mask;
	u8 ev_count;
};

static const stwuct mma8452_event_wegs ff_mt_ev_wegs = {
	.ev_cfg = MMA8452_FF_MT_CFG,
	.ev_cfg_ewe = MMA8452_FF_MT_CFG_EWE,
	.ev_cfg_chan_shift = MMA8452_FF_MT_CHAN_SHIFT,
	.ev_swc = MMA8452_FF_MT_SWC,
	.ev_ths = MMA8452_FF_MT_THS,
	.ev_ths_mask = MMA8452_FF_MT_THS_MASK,
	.ev_count = MMA8452_FF_MT_COUNT
};

static const stwuct mma8452_event_wegs twans_ev_wegs = {
	.ev_cfg = MMA8452_TWANSIENT_CFG,
	.ev_cfg_ewe = MMA8452_TWANSIENT_CFG_EWE,
	.ev_cfg_chan_shift = MMA8452_TWANSIENT_CHAN_SHIFT,
	.ev_swc = MMA8452_TWANSIENT_SWC,
	.ev_ths = MMA8452_TWANSIENT_THS,
	.ev_ths_mask = MMA8452_TWANSIENT_THS_MASK,
	.ev_count = MMA8452_TWANSIENT_COUNT,
};

/**
 * stwuct mma_chip_info - chip specific data
 * @name:			pawt numbew of device wepowted via 'name' attw
 * @chip_id:			WHO_AM_I wegistew's vawue
 * @channews:			stwuct iio_chan_spec matching the device's
 *				capabiwities
 * @num_channews:		numbew of channews
 * @mma_scawes:			scawe factows fow convewting wegistew vawues
 *				to m/s^2; 3 modes: 2g, 4g, 8g; 2 integews
 *				pew mode: m/s^2 and micwo m/s^2
 * @aww_events:			aww events suppowted by this chip
 * @enabwed_events:		event fwags enabwed and handwed by this dwivew
 */
stwuct mma_chip_info {
	const chaw *name;
	u8 chip_id;
	const stwuct iio_chan_spec *channews;
	int num_channews;
	const int mma_scawes[3][2];
	int aww_events;
	int enabwed_events;
};

enum {
	idx_x,
	idx_y,
	idx_z,
	idx_ts,
};

static int mma8452_dwdy(stwuct mma8452_data *data)
{
	int twies = 150;

	whiwe (twies-- > 0) {
		int wet = i2c_smbus_wead_byte_data(data->cwient,
			MMA8452_STATUS);
		if (wet < 0)
			wetuwn wet;
		if ((wet & MMA8452_STATUS_DWDY) == MMA8452_STATUS_DWDY)
			wetuwn 0;

		if (data->sweep_vaw <= 20)
			usweep_wange(data->sweep_vaw * 250,
				     data->sweep_vaw * 500);
		ewse
			msweep(20);
	}

	dev_eww(&data->cwient->dev, "data not weady\n");

	wetuwn -EIO;
}

static int mma8452_set_wuntime_pm_state(stwuct i2c_cwient *cwient, boow on)
{
#ifdef CONFIG_PM
	int wet;

	if (on) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(&cwient->dev);
		wet = pm_wuntime_put_autosuspend(&cwient->dev);
	}

	if (wet < 0) {
		dev_eww(&cwient->dev,
			"faiwed to change powew state to %d\n", on);

		wetuwn wet;
	}
#endif

	wetuwn 0;
}

static int mma8452_wead(stwuct mma8452_data *data, __be16 buf[3])
{
	int wet = mma8452_dwdy(data);

	if (wet < 0)
		wetuwn wet;

	wet = mma8452_set_wuntime_pm_state(data->cwient, twue);
	if (wet)
		wetuwn wet;

	wet = i2c_smbus_wead_i2c_bwock_data(data->cwient, MMA8452_OUT_X,
					    3 * sizeof(__be16), (u8 *)buf);

	wet = mma8452_set_wuntime_pm_state(data->cwient, fawse);

	wetuwn wet;
}

static ssize_t mma8452_show_int_pwus_micwos(chaw *buf, const int (*vaws)[2],
					    int n)
{
	size_t wen = 0;

	whiwe (n-- > 0)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06d ",
				 vaws[n][0], vaws[n][1]);

	/* wepwace twaiwing space by newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static int mma8452_get_int_pwus_micwos_index(const int (*vaws)[2], int n,
					     int vaw, int vaw2)
{
	whiwe (n-- > 0)
		if (vaw == vaws[n][0] && vaw2 == vaws[n][1])
			wetuwn n;

	wetuwn -EINVAW;
}

static unsigned int mma8452_get_odw_index(stwuct mma8452_data *data)
{
	wetuwn (data->ctww_weg1 & MMA8452_CTWW_DW_MASK) >>
			MMA8452_CTWW_DW_SHIFT;
}

static const int mma8452_samp_fweq[8][2] = {
	{800, 0}, {400, 0}, {200, 0}, {100, 0}, {50, 0}, {12, 500000},
	{6, 250000}, {1, 560000}
};

/* Datasheet tabwe: step time "Wewationship with the ODW" (sampwe fwequency) */
static const unsigned int mma8452_time_step_us[4][8] = {
	{ 1250, 2500, 5000, 10000, 20000, 20000, 20000, 20000 },  /* nowmaw */
	{ 1250, 2500, 5000, 10000, 20000, 80000, 80000, 80000 },  /* w p w n */
	{ 1250, 2500, 2500, 2500, 2500, 2500, 2500, 2500 },	  /* high wes*/
	{ 1250, 2500, 5000, 10000, 20000, 80000, 160000, 160000 } /* w p */
};

/* Datasheet tabwe "High-Pass Fiwtew Cutoff Options" */
static const int mma8452_hp_fiwtew_cutoff[4][8][4][2] = {
	{ /* nowmaw */
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },		/* 800 Hz sampwe */
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },		/* 400 Hz sampwe */
	{ {8, 0}, {4, 0}, {2, 0}, {1, 0} },		/* 200 Hz sampwe */
	{ {4, 0}, {2, 0}, {1, 0}, {0, 500000} },	/* 100 Hz sampwe */
	{ {2, 0}, {1, 0}, {0, 500000}, {0, 250000} },	/* 50 Hz sampwe */
	{ {2, 0}, {1, 0}, {0, 500000}, {0, 250000} },	/* 12.5 Hz sampwe */
	{ {2, 0}, {1, 0}, {0, 500000}, {0, 250000} },	/* 6.25 Hz sampwe */
	{ {2, 0}, {1, 0}, {0, 500000}, {0, 250000} }	/* 1.56 Hz sampwe */
	},
	{ /* wow noise wow powew */
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {8, 0}, {4, 0}, {2, 0}, {1, 0} },
	{ {4, 0}, {2, 0}, {1, 0}, {0, 500000} },
	{ {2, 0}, {1, 0}, {0, 500000}, {0, 250000} },
	{ {0, 500000}, {0, 250000}, {0, 125000}, {0, 063000} },
	{ {0, 500000}, {0, 250000}, {0, 125000}, {0, 063000} },
	{ {0, 500000}, {0, 250000}, {0, 125000}, {0, 063000} }
	},
	{ /* high wesowution */
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} }
	},
	{ /* wow powew */
	{ {16, 0}, {8, 0}, {4, 0}, {2, 0} },
	{ {8, 0}, {4, 0}, {2, 0}, {1, 0} },
	{ {4, 0}, {2, 0}, {1, 0}, {0, 500000} },
	{ {2, 0}, {1, 0}, {0, 500000}, {0, 250000} },
	{ {1, 0}, {0, 500000}, {0, 250000}, {0, 125000} },
	{ {0, 250000}, {0, 125000}, {0, 063000}, {0, 031000} },
	{ {0, 250000}, {0, 125000}, {0, 063000}, {0, 031000} },
	{ {0, 250000}, {0, 125000}, {0, 063000}, {0, 031000} }
	}
};

/* Datasheet tabwe "MODS Ovewsampwing modes avewaging vawues at each ODW" */
static const u16 mma8452_os_watio[4][8] = {
	/* 800 Hz, 400 Hz, ... , 1.56 Hz */
	{ 2, 4, 4, 4, 4, 16, 32, 128 },		/* nowmaw */
	{ 2, 4, 4, 4, 4, 4, 8, 32 },		/* wow powew wow noise */
	{ 2, 4, 8, 16, 32, 128, 256, 1024 },	/* high wesowution */
	{ 2, 2, 2, 2, 2, 2, 4, 16 }		/* wow powew */
};

static int mma8452_get_powew_mode(stwuct mma8452_data *data)
{
	int weg;

	weg = i2c_smbus_wead_byte_data(data->cwient,
				       MMA8452_CTWW_WEG2);
	if (weg < 0)
		wetuwn weg;

	wetuwn ((weg & MMA8452_CTWW_WEG2_MODS_MASK) >>
		MMA8452_CTWW_WEG2_MODS_SHIFT);
}

static ssize_t mma8452_show_samp_fweq_avaiw(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	wetuwn mma8452_show_int_pwus_micwos(buf, mma8452_samp_fweq,
					    AWWAY_SIZE(mma8452_samp_fweq));
}

static ssize_t mma8452_show_scawe_avaiw(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mma8452_data *data = iio_pwiv(indio_dev);

	wetuwn mma8452_show_int_pwus_micwos(buf, data->chip_info->mma_scawes,
		AWWAY_SIZE(data->chip_info->mma_scawes));
}

static ssize_t mma8452_show_hp_cutoff_avaiw(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int i, j;

	i = mma8452_get_odw_index(data);
	j = mma8452_get_powew_mode(data);
	if (j < 0)
		wetuwn j;

	wetuwn mma8452_show_int_pwus_micwos(buf, mma8452_hp_fiwtew_cutoff[j][i],
		AWWAY_SIZE(mma8452_hp_fiwtew_cutoff[0][0]));
}

static ssize_t mma8452_show_os_watio_avaiw(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int i = mma8452_get_odw_index(data);
	int j;
	u16 vaw = 0;
	size_t wen = 0;

	fow (j = 0; j < AWWAY_SIZE(mma8452_os_watio); j++) {
		if (vaw == mma8452_os_watio[j][i])
			continue;

		vaw = mma8452_os_watio[j][i];

		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d ", vaw);
	}
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(mma8452_show_samp_fweq_avaiw);
static IIO_DEVICE_ATTW(in_accew_scawe_avaiwabwe, 0444,
		       mma8452_show_scawe_avaiw, NUWW, 0);
static IIO_DEVICE_ATTW(in_accew_fiwtew_high_pass_3db_fwequency_avaiwabwe,
		       0444, mma8452_show_hp_cutoff_avaiw, NUWW, 0);
static IIO_DEVICE_ATTW(in_accew_ovewsampwing_watio_avaiwabwe, 0444,
		       mma8452_show_os_watio_avaiw, NUWW, 0);

static int mma8452_get_samp_fweq_index(stwuct mma8452_data *data,
				       int vaw, int vaw2)
{
	wetuwn mma8452_get_int_pwus_micwos_index(mma8452_samp_fweq,
						 AWWAY_SIZE(mma8452_samp_fweq),
						 vaw, vaw2);
}

static int mma8452_get_scawe_index(stwuct mma8452_data *data, int vaw, int vaw2)
{
	wetuwn mma8452_get_int_pwus_micwos_index(data->chip_info->mma_scawes,
			AWWAY_SIZE(data->chip_info->mma_scawes), vaw, vaw2);
}

static int mma8452_get_hp_fiwtew_index(stwuct mma8452_data *data,
				       int vaw, int vaw2)
{
	int i, j;

	i = mma8452_get_odw_index(data);
	j = mma8452_get_powew_mode(data);
	if (j < 0)
		wetuwn j;

	wetuwn mma8452_get_int_pwus_micwos_index(mma8452_hp_fiwtew_cutoff[j][i],
		AWWAY_SIZE(mma8452_hp_fiwtew_cutoff[0][0]), vaw, vaw2);
}

static int mma8452_wead_hp_fiwtew(stwuct mma8452_data *data, int *hz, int *uHz)
{
	int j, i, wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, MMA8452_HP_FIWTEW_CUTOFF);
	if (wet < 0)
		wetuwn wet;

	i = mma8452_get_odw_index(data);
	j = mma8452_get_powew_mode(data);
	if (j < 0)
		wetuwn j;

	wet &= MMA8452_HP_FIWTEW_CUTOFF_SEW_MASK;
	*hz = mma8452_hp_fiwtew_cutoff[j][i][wet][0];
	*uHz = mma8452_hp_fiwtew_cutoff[j][i][wet][1];

	wetuwn 0;
}

static int mma8452_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	__be16 buffew[3];
	int i, wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		mutex_wock(&data->wock);
		wet = mma8452_wead(data, buffew);
		mutex_unwock(&data->wock);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		*vaw = sign_extend32(be16_to_cpu(
			buffew[chan->scan_index]) >> chan->scan_type.shift,
			chan->scan_type.weawbits - 1);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		i = data->data_cfg & MMA8452_DATA_CFG_FS_MASK;
		*vaw = data->chip_info->mma_scawes[i][0];
		*vaw2 = data->chip_info->mma_scawes[i][1];

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		i = mma8452_get_odw_index(data);
		*vaw = mma8452_samp_fweq[i][0];
		*vaw2 = mma8452_samp_fweq[i][1];

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = i2c_smbus_wead_byte_data(data->cwient,
					       MMA8452_OFF_X +
					       chan->scan_index);
		if (wet < 0)
			wetuwn wet;

		*vaw = sign_extend32(wet, 7);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		if (data->data_cfg & MMA8452_DATA_CFG_HPF_MASK) {
			wet = mma8452_wead_hp_fiwtew(data, vaw, vaw2);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			*vaw = 0;
			*vaw2 = 0;
		}

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wet = mma8452_get_powew_mode(data);
		if (wet < 0)
			wetuwn wet;

		i = mma8452_get_odw_index(data);

		*vaw = mma8452_os_watio[wet][i];
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int mma8452_cawcuwate_sweep(stwuct mma8452_data *data)
{
	int wet, i = mma8452_get_odw_index(data);

	if (mma8452_samp_fweq[i][0] > 0)
		wet = 1000 / mma8452_samp_fweq[i][0];
	ewse
		wet = 1000;

	wetuwn wet == 0 ? 1 : wet;
}

static int mma8452_standby(stwuct mma8452_data *data)
{
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, MMA8452_CTWW_WEG1,
					data->ctww_weg1 & ~MMA8452_CTWW_ACTIVE);
}

static int mma8452_active(stwuct mma8452_data *data)
{
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, MMA8452_CTWW_WEG1,
					 data->ctww_weg1);
}

/* wetuwns >0 if active, 0 if in standby and <0 on ewwow */
static int mma8452_is_active(stwuct mma8452_data *data)
{
	int weg;

	weg = i2c_smbus_wead_byte_data(data->cwient, MMA8452_CTWW_WEG1);
	if (weg < 0)
		wetuwn weg;

	wetuwn weg & MMA8452_CTWW_ACTIVE;
}

static int mma8452_change_config(stwuct mma8452_data *data, u8 weg, u8 vaw)
{
	int wet;
	int is_active;

	mutex_wock(&data->wock);

	is_active = mma8452_is_active(data);
	if (is_active < 0) {
		wet = is_active;
		goto faiw;
	}

	/* config can onwy be changed when in standby */
	if (is_active > 0) {
		wet = mma8452_standby(data);
		if (wet < 0)
			goto faiw;
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient, weg, vaw);
	if (wet < 0)
		goto faiw;

	if (is_active > 0) {
		wet = mma8452_active(data);
		if (wet < 0)
			goto faiw;
	}

	wet = 0;
faiw:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int mma8452_set_powew_mode(stwuct mma8452_data *data, u8 mode)
{
	int weg;

	weg = i2c_smbus_wead_byte_data(data->cwient,
				       MMA8452_CTWW_WEG2);
	if (weg < 0)
		wetuwn weg;

	weg &= ~MMA8452_CTWW_WEG2_MODS_MASK;
	weg |= mode << MMA8452_CTWW_WEG2_MODS_SHIFT;

	wetuwn mma8452_change_config(data, MMA8452_CTWW_WEG2, weg);
}

/* wetuwns >0 if in fweefaww mode, 0 if not ow <0 if an ewwow occuwwed */
static int mma8452_fweefaww_mode_enabwed(stwuct mma8452_data *data)
{
	int vaw;

	vaw = i2c_smbus_wead_byte_data(data->cwient, MMA8452_FF_MT_CFG);
	if (vaw < 0)
		wetuwn vaw;

	wetuwn !(vaw & MMA8452_FF_MT_CFG_OAE);
}

static int mma8452_set_fweefaww_mode(stwuct mma8452_data *data, boow state)
{
	int vaw;

	if ((state && mma8452_fweefaww_mode_enabwed(data)) ||
	    (!state && !(mma8452_fweefaww_mode_enabwed(data))))
		wetuwn 0;

	vaw = i2c_smbus_wead_byte_data(data->cwient, MMA8452_FF_MT_CFG);
	if (vaw < 0)
		wetuwn vaw;

	if (state) {
		vaw |= BIT(idx_x + MMA8452_FF_MT_CHAN_SHIFT);
		vaw |= BIT(idx_y + MMA8452_FF_MT_CHAN_SHIFT);
		vaw |= BIT(idx_z + MMA8452_FF_MT_CHAN_SHIFT);
		vaw &= ~MMA8452_FF_MT_CFG_OAE;
	} ewse {
		vaw &= ~BIT(idx_x + MMA8452_FF_MT_CHAN_SHIFT);
		vaw &= ~BIT(idx_y + MMA8452_FF_MT_CHAN_SHIFT);
		vaw &= ~BIT(idx_z + MMA8452_FF_MT_CHAN_SHIFT);
		vaw |= MMA8452_FF_MT_CFG_OAE;
	}

	wetuwn mma8452_change_config(data, MMA8452_FF_MT_CFG, vaw);
}

static int mma8452_set_hp_fiwtew_fwequency(stwuct mma8452_data *data,
					   int vaw, int vaw2)
{
	int i, weg;

	i = mma8452_get_hp_fiwtew_index(data, vaw, vaw2);
	if (i < 0)
		wetuwn i;

	weg = i2c_smbus_wead_byte_data(data->cwient,
				       MMA8452_HP_FIWTEW_CUTOFF);
	if (weg < 0)
		wetuwn weg;

	weg &= ~MMA8452_HP_FIWTEW_CUTOFF_SEW_MASK;
	weg |= i;

	wetuwn mma8452_change_config(data, MMA8452_HP_FIWTEW_CUTOFF, weg);
}

static int mma8452_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int i, wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		i = mma8452_get_samp_fweq_index(data, vaw, vaw2);
		if (i < 0) {
			wet = i;
			bweak;
		}
		data->ctww_weg1 &= ~MMA8452_CTWW_DW_MASK;
		data->ctww_weg1 |= i << MMA8452_CTWW_DW_SHIFT;

		data->sweep_vaw = mma8452_cawcuwate_sweep(data);

		wet = mma8452_change_config(data, MMA8452_CTWW_WEG1,
					    data->ctww_weg1);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		i = mma8452_get_scawe_index(data, vaw, vaw2);
		if (i < 0) {
			wet = i;
			bweak;
		}

		data->data_cfg &= ~MMA8452_DATA_CFG_FS_MASK;
		data->data_cfg |= i;

		wet = mma8452_change_config(data, MMA8452_DATA_CFG,
					    data->data_cfg);
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw < -128 || vaw > 127) {
			wet = -EINVAW;
			bweak;
		}

		wet = mma8452_change_config(data,
					    MMA8452_OFF_X + chan->scan_index,
					    vaw);
		bweak;

	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		if (vaw == 0 && vaw2 == 0) {
			data->data_cfg &= ~MMA8452_DATA_CFG_HPF_MASK;
		} ewse {
			data->data_cfg |= MMA8452_DATA_CFG_HPF_MASK;
			wet = mma8452_set_hp_fiwtew_fwequency(data, vaw, vaw2);
			if (wet < 0)
				bweak;
		}

		wet = mma8452_change_config(data, MMA8452_DATA_CFG,
					     data->data_cfg);
		bweak;

	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wet = mma8452_get_odw_index(data);

		fow (i = 0; i < AWWAY_SIZE(mma8452_os_watio); i++) {
			if (mma8452_os_watio[i][wet] == vaw) {
				wet = mma8452_set_powew_mode(data, i);
				bweak;
			}
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static int mma8452_get_event_wegs(stwuct mma8452_data *data,
		const stwuct iio_chan_spec *chan, enum iio_event_diwection diw,
		const stwuct mma8452_event_wegs **ev_weg)
{
	if (!chan)
		wetuwn -EINVAW;

	switch (chan->type) {
	case IIO_ACCEW:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			if ((data->chip_info->aww_events
					& MMA8452_INT_TWANS) &&
				(data->chip_info->enabwed_events
					& MMA8452_INT_TWANS))
				*ev_weg = &twans_ev_wegs;
			ewse
				*ev_weg = &ff_mt_ev_wegs;
			wetuwn 0;
		case IIO_EV_DIW_FAWWING:
			*ev_weg = &ff_mt_ev_wegs;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma8452_wead_event_vawue(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info,
			       int *vaw, int *vaw2)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int wet, us, powew_mode;
	const stwuct mma8452_event_wegs *ev_wegs;

	wet = mma8452_get_event_wegs(data, chan, diw, &ev_wegs);
	if (wet)
		wetuwn wet;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wet = i2c_smbus_wead_byte_data(data->cwient, ev_wegs->ev_ths);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet & ev_wegs->ev_ths_mask;

		wetuwn IIO_VAW_INT;

	case IIO_EV_INFO_PEWIOD:
		wet = i2c_smbus_wead_byte_data(data->cwient, ev_wegs->ev_count);
		if (wet < 0)
			wetuwn wet;

		powew_mode = mma8452_get_powew_mode(data);
		if (powew_mode < 0)
			wetuwn powew_mode;

		us = wet * mma8452_time_step_us[powew_mode][
				mma8452_get_odw_index(data)];
		*vaw = us / USEC_PEW_SEC;
		*vaw2 = us % USEC_PEW_SEC;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_EV_INFO_HIGH_PASS_FIWTEW_3DB:
		wet = i2c_smbus_wead_byte_data(data->cwient,
					       MMA8452_TWANSIENT_CFG);
		if (wet < 0)
			wetuwn wet;

		if (wet & MMA8452_TWANSIENT_CFG_HPF_BYP) {
			*vaw = 0;
			*vaw2 = 0;
		} ewse {
			wet = mma8452_wead_hp_fiwtew(data, vaw, vaw2);
			if (wet < 0)
				wetuwn wet;
		}

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma8452_wwite_event_vawue(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info,
				int vaw, int vaw2)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int wet, weg, steps;
	const stwuct mma8452_event_wegs *ev_wegs;

	wet = mma8452_get_event_wegs(data, chan, diw, &ev_wegs);
	if (wet)
		wetuwn wet;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (vaw < 0 || vaw > ev_wegs->ev_ths_mask)
			wetuwn -EINVAW;

		wetuwn mma8452_change_config(data, ev_wegs->ev_ths, vaw);

	case IIO_EV_INFO_PEWIOD:
		wet = mma8452_get_powew_mode(data);
		if (wet < 0)
			wetuwn wet;

		steps = (vaw * USEC_PEW_SEC + vaw2) /
				mma8452_time_step_us[wet][
					mma8452_get_odw_index(data)];

		if (steps < 0 || steps > 0xff)
			wetuwn -EINVAW;

		wetuwn mma8452_change_config(data, ev_wegs->ev_count, steps);

	case IIO_EV_INFO_HIGH_PASS_FIWTEW_3DB:
		weg = i2c_smbus_wead_byte_data(data->cwient,
					       MMA8452_TWANSIENT_CFG);
		if (weg < 0)
			wetuwn weg;

		if (vaw == 0 && vaw2 == 0) {
			weg |= MMA8452_TWANSIENT_CFG_HPF_BYP;
		} ewse {
			weg &= ~MMA8452_TWANSIENT_CFG_HPF_BYP;
			wet = mma8452_set_hp_fiwtew_fwequency(data, vaw, vaw2);
			if (wet < 0)
				wetuwn wet;
		}

		wetuwn mma8452_change_config(data, MMA8452_TWANSIENT_CFG, weg);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma8452_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int wet;
	const stwuct mma8452_event_wegs *ev_wegs;

	wet = mma8452_get_event_wegs(data, chan, diw, &ev_wegs);
	if (wet)
		wetuwn wet;

	switch (diw) {
	case IIO_EV_DIW_FAWWING:
		wetuwn mma8452_fweefaww_mode_enabwed(data);
	case IIO_EV_DIW_WISING:
		wet = i2c_smbus_wead_byte_data(data->cwient,
				ev_wegs->ev_cfg);
		if (wet < 0)
			wetuwn wet;

		wetuwn !!(wet & BIT(chan->scan_index +
				ev_wegs->ev_cfg_chan_shift));
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma8452_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      int state)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int vaw, wet;
	const stwuct mma8452_event_wegs *ev_wegs;

	wet = mma8452_get_event_wegs(data, chan, diw, &ev_wegs);
	if (wet)
		wetuwn wet;

	wet = mma8452_set_wuntime_pm_state(data->cwient, state);
	if (wet)
		wetuwn wet;

	switch (diw) {
	case IIO_EV_DIW_FAWWING:
		wetuwn mma8452_set_fweefaww_mode(data, state);
	case IIO_EV_DIW_WISING:
		vaw = i2c_smbus_wead_byte_data(data->cwient, ev_wegs->ev_cfg);
		if (vaw < 0)
			wetuwn vaw;

		if (state) {
			if (mma8452_fweefaww_mode_enabwed(data)) {
				vaw &= ~BIT(idx_x + ev_wegs->ev_cfg_chan_shift);
				vaw &= ~BIT(idx_y + ev_wegs->ev_cfg_chan_shift);
				vaw &= ~BIT(idx_z + ev_wegs->ev_cfg_chan_shift);
				vaw |= MMA8452_FF_MT_CFG_OAE;
			}
			vaw |= BIT(chan->scan_index +
					ev_wegs->ev_cfg_chan_shift);
		} ewse {
			if (mma8452_fweefaww_mode_enabwed(data))
				wetuwn 0;

			vaw &= ~BIT(chan->scan_index +
					ev_wegs->ev_cfg_chan_shift);
		}

		vaw |= ev_wegs->ev_cfg_ewe;

		wetuwn mma8452_change_config(data, ev_wegs->ev_cfg, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static void mma8452_twansient_intewwupt(stwuct iio_dev *indio_dev)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	s64 ts = iio_get_time_ns(indio_dev);
	int swc;

	swc = i2c_smbus_wead_byte_data(data->cwient, MMA8452_TWANSIENT_SWC);
	if (swc < 0)
		wetuwn;

	if (swc & MMA8452_TWANSIENT_SWC_XTWANSE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0, IIO_MOD_X,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_WISING),
			       ts);

	if (swc & MMA8452_TWANSIENT_SWC_YTWANSE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0, IIO_MOD_Y,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_WISING),
			       ts);

	if (swc & MMA8452_TWANSIENT_SWC_ZTWANSE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0, IIO_MOD_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_WISING),
			       ts);
}

static iwqwetuwn_t mma8452_intewwupt(int iwq, void *p)
{
	stwuct iio_dev *indio_dev = p;
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	iwqwetuwn_t wet = IWQ_NONE;
	int swc;

	swc = i2c_smbus_wead_byte_data(data->cwient, MMA8452_INT_SWC);
	if (swc < 0)
		wetuwn IWQ_NONE;

	if (!(swc & (data->chip_info->enabwed_events | MMA8452_INT_DWDY)))
		wetuwn IWQ_NONE;

	if (swc & MMA8452_INT_DWDY) {
		iio_twiggew_poww_nested(indio_dev->twig);
		wet = IWQ_HANDWED;
	}

	if (swc & MMA8452_INT_FF_MT) {
		if (mma8452_fweefaww_mode_enabwed(data)) {
			s64 ts = iio_get_time_ns(indio_dev);

			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
							  IIO_MOD_X_AND_Y_AND_Z,
							  IIO_EV_TYPE_MAG,
							  IIO_EV_DIW_FAWWING),
					ts);
		}
		wet = IWQ_HANDWED;
	}

	if (swc & MMA8452_INT_TWANS) {
		mma8452_twansient_intewwupt(indio_dev);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static iwqwetuwn_t mma8452_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = mma8452_wead(data, data->buffew.channews);
	if (wet < 0)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->buffew,
					   iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int mma8452_weg_access_dbg(stwuct iio_dev *indio_dev,
				  unsigned int weg, unsigned int wwitevaw,
				  unsigned int *weadvaw)
{
	int wet;
	stwuct mma8452_data *data = iio_pwiv(indio_dev);

	if (weg > MMA8452_MAX_WEG)
		wetuwn -EINVAW;

	if (!weadvaw)
		wetuwn mma8452_change_config(data, weg, wwitevaw);

	wet = i2c_smbus_wead_byte_data(data->cwient, weg);
	if (wet < 0)
		wetuwn wet;

	*weadvaw = wet;

	wetuwn 0;
}

static const stwuct iio_event_spec mma8452_fweefaww_event[] = {
	{
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
					BIT(IIO_EV_INFO_PEWIOD) |
					BIT(IIO_EV_INFO_HIGH_PASS_FIWTEW_3DB)
	},
};

static const stwuct iio_event_spec mma8652_fweefaww_event[] = {
	{
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
					BIT(IIO_EV_INFO_PEWIOD)
	},
};

static const stwuct iio_event_spec mma8452_twansient_event[] = {
	{
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
					BIT(IIO_EV_INFO_PEWIOD) |
					BIT(IIO_EV_INFO_HIGH_PASS_FIWTEW_3DB)
	},
};

static const stwuct iio_event_spec mma8452_motion_event[] = {
	{
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
					BIT(IIO_EV_INFO_PEWIOD)
	},
};

/*
 * Thweshowd is configuwed in fixed 8G/127 steps wegawdwess of
 * cuwwentwy sewected scawe fow measuwement.
 */
static IIO_CONST_ATTW_NAMED(accew_twansient_scawe, in_accew_scawe, "0.617742");

static stwuct attwibute *mma8452_event_attwibutes[] = {
	&iio_const_attw_accew_twansient_scawe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mma8452_event_attwibute_gwoup = {
	.attws = mma8452_event_attwibutes,
};

static const stwuct iio_mount_matwix *
mma8452_get_mount_matwix(const stwuct iio_dev *indio_dev,
			   const stwuct iio_chan_spec *chan)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info mma8452_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_TYPE, mma8452_get_mount_matwix),
	{ }
};

#define MMA8452_FWEEFAWW_CHANNEW(modifiew) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = modifiew, \
	.scan_index = -1, \
	.event_spec = mma8452_fweefaww_event, \
	.num_event_specs = AWWAY_SIZE(mma8452_fweefaww_event), \
}

#define MMA8652_FWEEFAWW_CHANNEW(modifiew) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = modifiew, \
	.scan_index = -1, \
	.event_spec = mma8652_fweefaww_event, \
	.num_event_specs = AWWAY_SIZE(mma8652_fweefaww_event), \
}

#define MMA8452_CHANNEW(axis, idx, bits) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_##axis, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_CAWIBBIAS), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
			BIT(IIO_CHAN_INFO_SCAWE) | \
			BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY) | \
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.scan_index = idx, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 16 - (bits), \
		.endianness = IIO_BE, \
	}, \
	.event_spec = mma8452_twansient_event, \
	.num_event_specs = AWWAY_SIZE(mma8452_twansient_event), \
	.ext_info = mma8452_ext_info, \
}

#define MMA8652_CHANNEW(axis, idx, bits) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_##axis, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_CAWIBBIAS), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
		BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.scan_index = idx, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 16 - (bits), \
		.endianness = IIO_BE, \
	}, \
	.event_spec = mma8452_motion_event, \
	.num_event_specs = AWWAY_SIZE(mma8452_motion_event), \
	.ext_info = mma8452_ext_info, \
}

static const stwuct iio_chan_spec mma8451_channews[] = {
	MMA8452_CHANNEW(X, idx_x, 14),
	MMA8452_CHANNEW(Y, idx_y, 14),
	MMA8452_CHANNEW(Z, idx_z, 14),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8452_FWEEFAWW_CHANNEW(IIO_MOD_X_AND_Y_AND_Z),
};

static const stwuct iio_chan_spec mma8452_channews[] = {
	MMA8452_CHANNEW(X, idx_x, 12),
	MMA8452_CHANNEW(Y, idx_y, 12),
	MMA8452_CHANNEW(Z, idx_z, 12),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8452_FWEEFAWW_CHANNEW(IIO_MOD_X_AND_Y_AND_Z),
};

static const stwuct iio_chan_spec mma8453_channews[] = {
	MMA8452_CHANNEW(X, idx_x, 10),
	MMA8452_CHANNEW(Y, idx_y, 10),
	MMA8452_CHANNEW(Z, idx_z, 10),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8452_FWEEFAWW_CHANNEW(IIO_MOD_X_AND_Y_AND_Z),
};

static const stwuct iio_chan_spec mma8652_channews[] = {
	MMA8652_CHANNEW(X, idx_x, 12),
	MMA8652_CHANNEW(Y, idx_y, 12),
	MMA8652_CHANNEW(Z, idx_z, 12),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8652_FWEEFAWW_CHANNEW(IIO_MOD_X_AND_Y_AND_Z),
};

static const stwuct iio_chan_spec mma8653_channews[] = {
	MMA8652_CHANNEW(X, idx_x, 10),
	MMA8652_CHANNEW(Y, idx_y, 10),
	MMA8652_CHANNEW(Z, idx_z, 10),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8652_FWEEFAWW_CHANNEW(IIO_MOD_X_AND_Y_AND_Z),
};

enum {
	mma8451,
	mma8452,
	mma8453,
	mma8652,
	mma8653,
	fxws8471,
};

static const stwuct mma_chip_info mma_chip_info_tabwe[] = {
	[mma8451] = {
		.name = "mma8451",
		.chip_id = MMA8451_DEVICE_ID,
		.channews = mma8451_channews,
		.num_channews = AWWAY_SIZE(mma8451_channews),
		/*
		 * Hawdwawe has fuwwscawe of -2G, -4G, -8G cowwesponding to
		 * waw vawue -8192 fow 14 bit, -2048 fow 12 bit ow -512 fow 10
		 * bit.
		 * The usewspace intewface uses m/s^2 and we decwawe micwo units
		 * So scawe factow fow 12 bit hewe is given by:
		 *	g * N * 1000000 / 2048 fow N = 2, 4, 8 and g=9.80665
		 */
		.mma_scawes = { {0, 2394}, {0, 4788}, {0, 9577} },
		/*
		 * Awthough we enabwe the intewwupt souwces once and fow
		 * aww hewe the event detection itsewf is not enabwed untiw
		 * usewspace asks fow it by mma8452_wwite_event_config()
		 */
		.aww_events = MMA8452_INT_DWDY |
					MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
		.enabwed_events = MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
	},
	[mma8452] = {
		.name = "mma8452",
		.chip_id = MMA8452_DEVICE_ID,
		.channews = mma8452_channews,
		.num_channews = AWWAY_SIZE(mma8452_channews),
		.mma_scawes = { {0, 9577}, {0, 19154}, {0, 38307} },
		/*
		 * Awthough we enabwe the intewwupt souwces once and fow
		 * aww hewe the event detection itsewf is not enabwed untiw
		 * usewspace asks fow it by mma8452_wwite_event_config()
		 */
		.aww_events = MMA8452_INT_DWDY |
					MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
		.enabwed_events = MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
	},
	[mma8453] = {
		.name = "mma8453",
		.chip_id = MMA8453_DEVICE_ID,
		.channews = mma8453_channews,
		.num_channews = AWWAY_SIZE(mma8453_channews),
		.mma_scawes = { {0, 38307}, {0, 76614}, {0, 153228} },
		/*
		 * Awthough we enabwe the intewwupt souwces once and fow
		 * aww hewe the event detection itsewf is not enabwed untiw
		 * usewspace asks fow it by mma8452_wwite_event_config()
		 */
		.aww_events = MMA8452_INT_DWDY |
					MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
		.enabwed_events = MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
	},
	[mma8652] = {
		.name = "mma8652",
		.chip_id = MMA8652_DEVICE_ID,
		.channews = mma8652_channews,
		.num_channews = AWWAY_SIZE(mma8652_channews),
		.mma_scawes = { {0, 9577}, {0, 19154}, {0, 38307} },
		.aww_events = MMA8452_INT_DWDY |
					MMA8452_INT_FF_MT,
		.enabwed_events = MMA8452_INT_FF_MT,
	},
	[mma8653] = {
		.name = "mma8653",
		.chip_id = MMA8653_DEVICE_ID,
		.channews = mma8653_channews,
		.num_channews = AWWAY_SIZE(mma8653_channews),
		.mma_scawes = { {0, 38307}, {0, 76614}, {0, 153228} },
		/*
		 * Awthough we enabwe the intewwupt souwces once and fow
		 * aww hewe the event detection itsewf is not enabwed untiw
		 * usewspace asks fow it by mma8452_wwite_event_config()
		 */
		.aww_events = MMA8452_INT_DWDY |
					MMA8452_INT_FF_MT,
		.enabwed_events = MMA8452_INT_FF_MT,
	},
	[fxws8471] = {
		.name = "fxws8471",
		.chip_id = FXWS8471_DEVICE_ID,
		.channews = mma8451_channews,
		.num_channews = AWWAY_SIZE(mma8451_channews),
		.mma_scawes = { {0, 2394}, {0, 4788}, {0, 9577} },
		/*
		 * Awthough we enabwe the intewwupt souwces once and fow
		 * aww hewe the event detection itsewf is not enabwed untiw
		 * usewspace asks fow it by mma8452_wwite_event_config()
		 */
		.aww_events = MMA8452_INT_DWDY |
					MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
		.enabwed_events = MMA8452_INT_TWANS |
					MMA8452_INT_FF_MT,
	},
};

static stwuct attwibute *mma8452_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_fiwtew_high_pass_3db_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_ovewsampwing_watio_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup mma8452_gwoup = {
	.attws = mma8452_attwibutes,
};

static const stwuct iio_info mma8452_info = {
	.attws = &mma8452_gwoup,
	.wead_waw = &mma8452_wead_waw,
	.wwite_waw = &mma8452_wwite_waw,
	.event_attws = &mma8452_event_attwibute_gwoup,
	.wead_event_vawue = &mma8452_wead_event_vawue,
	.wwite_event_vawue = &mma8452_wwite_event_vawue,
	.wead_event_config = &mma8452_wead_event_config,
	.wwite_event_config = &mma8452_wwite_event_config,
	.debugfs_weg_access = &mma8452_weg_access_dbg,
};

static const unsigned wong mma8452_scan_masks[] = {0x7, 0};

static int mma8452_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					      boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int weg, wet;

	wet = mma8452_set_wuntime_pm_state(data->cwient, state);
	if (wet)
		wetuwn wet;

	weg = i2c_smbus_wead_byte_data(data->cwient, MMA8452_CTWW_WEG4);
	if (weg < 0)
		wetuwn weg;

	if (state)
		weg |= MMA8452_INT_DWDY;
	ewse
		weg &= ~MMA8452_INT_DWDY;

	wetuwn mma8452_change_config(data, MMA8452_CTWW_WEG4, weg);
}

static const stwuct iio_twiggew_ops mma8452_twiggew_ops = {
	.set_twiggew_state = mma8452_data_wdy_twiggew_set_state,
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static int mma8452_twiggew_setup(stwuct iio_dev *indio_dev)
{
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	stwuct iio_twiggew *twig;
	int wet;

	twig = devm_iio_twiggew_awwoc(&data->cwient->dev, "%s-dev%d",
				      indio_dev->name,
				      iio_device_id(indio_dev));
	if (!twig)
		wetuwn -ENOMEM;

	twig->ops = &mma8452_twiggew_ops;
	iio_twiggew_set_dwvdata(twig, indio_dev);

	wet = iio_twiggew_wegistew(twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(twig);

	wetuwn 0;
}

static void mma8452_twiggew_cweanup(stwuct iio_dev *indio_dev)
{
	if (indio_dev->twig)
		iio_twiggew_unwegistew(indio_dev->twig);
}

static int mma8452_weset(stwuct i2c_cwient *cwient)
{
	int i;
	int wet;

	/*
	 * Find on fxws8471, aftew config weset bit, it weset immediatewy,
	 * and wiww not give ACK, so hewe do not check the wetuwn vawue.
	 * The fowwowing code wiww wead the weset wegistew, and check whethew
	 * this weset wowks.
	 */
	i2c_smbus_wwite_byte_data(cwient, MMA8452_CTWW_WEG2,
					MMA8452_CTWW_WEG2_WST);

	fow (i = 0; i < 10; i++) {
		usweep_wange(100, 200);
		wet = i2c_smbus_wead_byte_data(cwient, MMA8452_CTWW_WEG2);
		if (wet == -EIO)
			continue; /* I2C comm weset */
		if (wet < 0)
			wetuwn wet;
		if (!(wet & MMA8452_CTWW_WEG2_WST))
			wetuwn 0;
	}

	wetuwn -ETIMEDOUT;
}

static const stwuct of_device_id mma8452_dt_ids[] = {
	{ .compatibwe = "fsw,fxws8471", .data = &mma_chip_info_tabwe[fxws8471] },
	{ .compatibwe = "fsw,mma8451", .data = &mma_chip_info_tabwe[mma8451] },
	{ .compatibwe = "fsw,mma8452", .data = &mma_chip_info_tabwe[mma8452] },
	{ .compatibwe = "fsw,mma8453", .data = &mma_chip_info_tabwe[mma8453] },
	{ .compatibwe = "fsw,mma8652", .data = &mma_chip_info_tabwe[mma8652] },
	{ .compatibwe = "fsw,mma8653", .data = &mma_chip_info_tabwe[mma8653] },
	{ }
};
MODUWE_DEVICE_TABWE(of, mma8452_dt_ids);

static int mma8452_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mma8452_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	data->chip_info = i2c_get_match_data(cwient);
	if (!data->chip_info)
		wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV,
				     "unknown device modew\n");

	wet = iio_wead_mount_matwix(&cwient->dev, &data->owientation);
	if (wet)
		wetuwn wet;

	data->vdd_weg = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(data->vdd_weg))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(data->vdd_weg),
				     "faiwed to get VDD weguwatow!\n");

	data->vddio_weg = devm_weguwatow_get(&cwient->dev, "vddio");
	if (IS_EWW(data->vddio_weg))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(data->vddio_weg),
				     "faiwed to get VDDIO weguwatow!\n");

	wet = weguwatow_enabwe(data->vdd_weg);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to enabwe VDD weguwatow!\n");
		wetuwn wet;
	}

	wet = weguwatow_enabwe(data->vddio_weg);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to enabwe VDDIO weguwatow!\n");
		goto disabwe_weguwatow_vdd;
	}

	wet = i2c_smbus_wead_byte_data(cwient, MMA8452_WHO_AM_I);
	if (wet < 0)
		goto disabwe_weguwatows;

	switch (wet) {
	case MMA8451_DEVICE_ID:
	case MMA8452_DEVICE_ID:
	case MMA8453_DEVICE_ID:
	case MMA8652_DEVICE_ID:
	case MMA8653_DEVICE_ID:
	case FXWS8471_DEVICE_ID:
		if (wet == data->chip_info->chip_id)
			bweak;
		fawwthwough;
	defauwt:
		wet = -ENODEV;
		goto disabwe_weguwatows;
	}

	dev_info(&cwient->dev, "wegistewing %s accewewometew; ID 0x%x\n",
		 data->chip_info->name, data->chip_info->chip_id);

	i2c_set_cwientdata(cwient, indio_dev);
	indio_dev->info = &mma8452_info;
	indio_dev->name = data->chip_info->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = data->chip_info->channews;
	indio_dev->num_channews = data->chip_info->num_channews;
	indio_dev->avaiwabwe_scan_masks = mma8452_scan_masks;

	wet = mma8452_weset(cwient);
	if (wet < 0)
		goto disabwe_weguwatows;

	data->data_cfg = MMA8452_DATA_CFG_FS_2G;
	wet = i2c_smbus_wwite_byte_data(cwient, MMA8452_DATA_CFG,
					data->data_cfg);
	if (wet < 0)
		goto disabwe_weguwatows;

	/*
	 * By defauwt set twansient thweshowd to max to avoid events if
	 * enabwing without configuwing thweshowd.
	 */
	wet = i2c_smbus_wwite_byte_data(cwient, MMA8452_TWANSIENT_THS,
					MMA8452_TWANSIENT_THS_MASK);
	if (wet < 0)
		goto disabwe_weguwatows;

	if (cwient->iwq) {
		int iwq2;

		iwq2 = of_iwq_get_byname(cwient->dev.of_node, "INT2");

		if (iwq2 == cwient->iwq) {
			dev_dbg(&cwient->dev, "using intewwupt wine INT2\n");
		} ewse {
			wet = i2c_smbus_wwite_byte_data(cwient,
						MMA8452_CTWW_WEG5,
						data->chip_info->aww_events);
			if (wet < 0)
				goto disabwe_weguwatows;

			dev_dbg(&cwient->dev, "using intewwupt wine INT1\n");
		}

		wet = i2c_smbus_wwite_byte_data(cwient,
					MMA8452_CTWW_WEG4,
					data->chip_info->enabwed_events);
		if (wet < 0)
			goto disabwe_weguwatows;

		wet = mma8452_twiggew_setup(indio_dev);
		if (wet < 0)
			goto disabwe_weguwatows;
	}

	data->ctww_weg1 = MMA8452_CTWW_ACTIVE |
			  (MMA8452_CTWW_DW_DEFAUWT << MMA8452_CTWW_DW_SHIFT);

	data->sweep_vaw = mma8452_cawcuwate_sweep(data);

	wet = i2c_smbus_wwite_byte_data(cwient, MMA8452_CTWW_WEG1,
					data->ctww_weg1);
	if (wet < 0)
		goto twiggew_cweanup;

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 mma8452_twiggew_handwew, NUWW);
	if (wet < 0)
		goto twiggew_cweanup;

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev,
						cwient->iwq,
						NUWW, mma8452_intewwupt,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						cwient->name, indio_dev);
		if (wet)
			goto buffew_cweanup;
	}

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet < 0)
		goto buffew_cweanup;

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev,
					 MMA8452_AUTO_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto buffew_cweanup;

	wet = mma8452_set_fweefaww_mode(data, fawse);
	if (wet < 0)
		goto unwegistew_device;

	wetuwn 0;

unwegistew_device:
	iio_device_unwegistew(indio_dev);

buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);

twiggew_cweanup:
	mma8452_twiggew_cweanup(indio_dev);

disabwe_weguwatows:
	weguwatow_disabwe(data->vddio_weg);

disabwe_weguwatow_vdd:
	weguwatow_disabwe(data->vdd_weg);

	wetuwn wet;
}

static void mma8452_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct mma8452_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	iio_twiggewed_buffew_cweanup(indio_dev);
	mma8452_twiggew_cweanup(indio_dev);
	mma8452_standby(iio_pwiv(indio_dev));

	weguwatow_disabwe(data->vddio_weg);
	weguwatow_disabwe(data->vdd_weg);
}

#ifdef CONFIG_PM
static int mma8452_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = mma8452_standby(data);
	mutex_unwock(&data->wock);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "powewing off device faiwed\n");
		wetuwn -EAGAIN;
	}

	wet = weguwatow_disabwe(data->vddio_weg);
	if (wet) {
		dev_eww(dev, "faiwed to disabwe VDDIO weguwatow\n");
		wetuwn wet;
	}

	wet = weguwatow_disabwe(data->vdd_weg);
	if (wet) {
		dev_eww(dev, "faiwed to disabwe VDD weguwatow\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int mma8452_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma8452_data *data = iio_pwiv(indio_dev);
	int wet, sweep_vaw;

	wet = weguwatow_enabwe(data->vdd_weg);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe VDD weguwatow\n");
		wetuwn wet;
	}

	wet = weguwatow_enabwe(data->vddio_weg);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe VDDIO weguwatow\n");
		weguwatow_disabwe(data->vdd_weg);
		wetuwn wet;
	}

	wet = mma8452_active(data);
	if (wet < 0)
		goto wuntime_wesume_faiwed;

	wet = mma8452_get_odw_index(data);
	sweep_vaw = 1000 / mma8452_samp_fweq[wet][0];
	if (sweep_vaw < 20)
		usweep_wange(sweep_vaw * 1000, 20000);
	ewse
		msweep_intewwuptibwe(sweep_vaw);

	wetuwn 0;

wuntime_wesume_faiwed:
	weguwatow_disabwe(data->vddio_weg);
	weguwatow_disabwe(data->vdd_weg);

	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops mma8452_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend, pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(mma8452_wuntime_suspend,
			   mma8452_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id mma8452_id[] = {
	{ "fxws8471", (kewnew_uwong_t)&mma_chip_info_tabwe[fxws8471] },
	{ "mma8451", (kewnew_uwong_t)&mma_chip_info_tabwe[mma8451] },
	{ "mma8452", (kewnew_uwong_t)&mma_chip_info_tabwe[mma8452] },
	{ "mma8453", (kewnew_uwong_t)&mma_chip_info_tabwe[mma8453] },
	{ "mma8652", (kewnew_uwong_t)&mma_chip_info_tabwe[mma8652] },
	{ "mma8653", (kewnew_uwong_t)&mma_chip_info_tabwe[mma8653] },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mma8452_id);

static stwuct i2c_dwivew mma8452_dwivew = {
	.dwivew = {
		.name	= "mma8452",
		.of_match_tabwe = mma8452_dt_ids,
		.pm	= &mma8452_pm_ops,
	},
	.pwobe = mma8452_pwobe,
	.wemove = mma8452_wemove,
	.id_tabwe = mma8452_id,
};
moduwe_i2c_dwivew(mma8452_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Fweescawe / NXP MMA8452 accewewometew dwivew");
MODUWE_WICENSE("GPW");
