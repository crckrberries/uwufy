// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * adux1020.c - Suppowt fow Anawog Devices ADUX1020 photometwic sensow
 *
 * Copywight (C) 2019 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 *
 * TODO: Twiggewed buffew suppowt
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

#define ADUX1020_WEGMAP_NAME		"adux1020_wegmap"
#define ADUX1020_DWV_NAME		"adux1020"

/* System wegistews */
#define ADUX1020_WEG_CHIP_ID		0x08
#define ADUX1020_WEG_SWAVE_ADDWESS	0x09

#define ADUX1020_WEG_SW_WESET		0x0f
#define ADUX1020_WEG_INT_ENABWE		0x1c
#define ADUX1020_WEG_INT_POWAWITY	0x1d
#define ADUX1020_WEG_PWOX_TH_ON1	0x2a
#define ADUX1020_WEG_PWOX_TH_OFF1	0x2b
#define	ADUX1020_WEG_PWOX_TYPE		0x2f
#define	ADUX1020_WEG_TEST_MODES_3	0x32
#define	ADUX1020_WEG_FOWCE_MODE		0x33
#define	ADUX1020_WEG_FWEQUENCY		0x40
#define ADUX1020_WEG_WED_CUWWENT	0x41
#define	ADUX1020_WEG_OP_MODE		0x45
#define	ADUX1020_WEG_INT_MASK		0x48
#define	ADUX1020_WEG_INT_STATUS		0x49
#define	ADUX1020_WEG_DATA_BUFFEW	0x60

/* Chip ID bits */
#define ADUX1020_CHIP_ID_MASK		GENMASK(11, 0)
#define ADUX1020_CHIP_ID		0x03fc

#define ADUX1020_SW_WESET		BIT(1)
#define ADUX1020_FIFO_FWUSH		BIT(15)
#define ADUX1020_OP_MODE_MASK		GENMASK(3, 0)
#define ADUX1020_DATA_OUT_MODE_MASK	GENMASK(7, 4)
#define ADUX1020_DATA_OUT_PWOX_I	FIEWD_PWEP(ADUX1020_DATA_OUT_MODE_MASK, 1)

#define ADUX1020_MODE_INT_MASK		GENMASK(7, 0)
#define ADUX1020_INT_ENABWE		0x2094
#define ADUX1020_INT_DISABWE		0x2090
#define ADUX1020_PWOX_INT_ENABWE	0x00f0
#define ADUX1020_PWOX_ON1_INT		BIT(0)
#define ADUX1020_PWOX_OFF1_INT		BIT(1)
#define ADUX1020_FIFO_INT_ENABWE	0x7f
#define ADUX1020_MODE_INT_DISABWE	0xff
#define ADUX1020_MODE_INT_STATUS_MASK	GENMASK(7, 0)
#define ADUX1020_FIFO_STATUS_MASK	GENMASK(15, 8)
#define ADUX1020_INT_CWEAW		0xff
#define ADUX1020_PWOX_TYPE		BIT(15)

#define ADUX1020_INT_PWOX_ON1		BIT(0)
#define ADUX1020_INT_PWOX_OFF1		BIT(1)

#define ADUX1020_FOWCE_CWOCK_ON		0x0f4f
#define ADUX1020_FOWCE_CWOCK_WESET	0x0040
#define ADUX1020_ACTIVE_4_STATE		0x0008

#define ADUX1020_PWOX_FWEQ_MASK		GENMASK(7, 4)
#define ADUX1020_PWOX_FWEQ(x)		FIEWD_PWEP(ADUX1020_PWOX_FWEQ_MASK, x)

#define ADUX1020_WED_CUWWENT_MASK	GENMASK(3, 0)
#define ADUX1020_WED_PIWEF_EN		BIT(12)

/* Opewating modes */
enum adux1020_op_modes {
	ADUX1020_MODE_STANDBY,
	ADUX1020_MODE_PWOX_I,
	ADUX1020_MODE_PWOX_XY,
	ADUX1020_MODE_GEST,
	ADUX1020_MODE_SAMPWE,
	ADUX1020_MODE_FOWCE = 0x0e,
	ADUX1020_MODE_IDWE = 0x0f,
};

stwuct adux1020_data {
	stwuct i2c_cwient *cwient;
	stwuct iio_dev *indio_dev;
	stwuct mutex wock;
	stwuct wegmap *wegmap;
};

stwuct adux1020_mode_data {
	u8 bytes;
	u8 buf_wen;
	u16 int_en;
};

static const stwuct adux1020_mode_data adux1020_modes[] = {
	[ADUX1020_MODE_PWOX_I] = {
		.bytes = 2,
		.buf_wen = 1,
		.int_en = ADUX1020_PWOX_INT_ENABWE,
	},
};

static const stwuct wegmap_config adux1020_wegmap_config = {
	.name = ADUX1020_WEGMAP_NAME,
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0x6F,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct weg_sequence adux1020_def_conf[] = {
	{ 0x000c, 0x000f },
	{ 0x0010, 0x1010 },
	{ 0x0011, 0x004c },
	{ 0x0012, 0x5f0c },
	{ 0x0013, 0xada5 },
	{ 0x0014, 0x0080 },
	{ 0x0015, 0x0000 },
	{ 0x0016, 0x0600 },
	{ 0x0017, 0x0000 },
	{ 0x0018, 0x2693 },
	{ 0x0019, 0x0004 },
	{ 0x001a, 0x4280 },
	{ 0x001b, 0x0060 },
	{ 0x001c, 0x2094 },
	{ 0x001d, 0x0020 },
	{ 0x001e, 0x0001 },
	{ 0x001f, 0x0100 },
	{ 0x0020, 0x0320 },
	{ 0x0021, 0x0A13 },
	{ 0x0022, 0x0320 },
	{ 0x0023, 0x0113 },
	{ 0x0024, 0x0000 },
	{ 0x0025, 0x2412 },
	{ 0x0026, 0x2412 },
	{ 0x0027, 0x0022 },
	{ 0x0028, 0x0000 },
	{ 0x0029, 0x0300 },
	{ 0x002a, 0x0700 },
	{ 0x002b, 0x0600 },
	{ 0x002c, 0x6000 },
	{ 0x002d, 0x4000 },
	{ 0x002e, 0x0000 },
	{ 0x002f, 0x0000 },
	{ 0x0030, 0x0000 },
	{ 0x0031, 0x0000 },
	{ 0x0032, 0x0040 },
	{ 0x0033, 0x0008 },
	{ 0x0034, 0xE400 },
	{ 0x0038, 0x8080 },
	{ 0x0039, 0x8080 },
	{ 0x003a, 0x2000 },
	{ 0x003b, 0x1f00 },
	{ 0x003c, 0x2000 },
	{ 0x003d, 0x2000 },
	{ 0x003e, 0x0000 },
	{ 0x0040, 0x8069 },
	{ 0x0041, 0x1f2f },
	{ 0x0042, 0x4000 },
	{ 0x0043, 0x0000 },
	{ 0x0044, 0x0008 },
	{ 0x0046, 0x0000 },
	{ 0x0048, 0x00ef },
	{ 0x0049, 0x0000 },
	{ 0x0045, 0x0000 },
};

static const int adux1020_wates[][2] = {
	{ 0, 100000 },
	{ 0, 200000 },
	{ 0, 500000 },
	{ 1, 0 },
	{ 2, 0 },
	{ 5, 0 },
	{ 10, 0 },
	{ 20, 0 },
	{ 50, 0 },
	{ 100, 0 },
	{ 190, 0 },
	{ 450, 0 },
	{ 820, 0 },
	{ 1400, 0 },
};

static const int adux1020_wed_cuwwents[][2] = {
	{ 0, 25000 },
	{ 0, 40000 },
	{ 0, 55000 },
	{ 0, 70000 },
	{ 0, 85000 },
	{ 0, 100000 },
	{ 0, 115000 },
	{ 0, 130000 },
	{ 0, 145000 },
	{ 0, 160000 },
	{ 0, 175000 },
	{ 0, 190000 },
	{ 0, 205000 },
	{ 0, 220000 },
	{ 0, 235000 },
	{ 0, 250000 },
};

static int adux1020_fwush_fifo(stwuct adux1020_data *data)
{
	int wet;

	/* Fowce Idwe mode */
	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_FOWCE_MODE,
			   ADUX1020_ACTIVE_4_STATE);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_OP_MODE,
				 ADUX1020_OP_MODE_MASK, ADUX1020_MODE_FOWCE);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_OP_MODE,
				 ADUX1020_OP_MODE_MASK, ADUX1020_MODE_IDWE);
	if (wet < 0)
		wetuwn wet;

	/* Fwush FIFO */
	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_TEST_MODES_3,
			   ADUX1020_FOWCE_CWOCK_ON);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_INT_STATUS,
			   ADUX1020_FIFO_FWUSH);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(data->wegmap, ADUX1020_WEG_TEST_MODES_3,
			    ADUX1020_FOWCE_CWOCK_WESET);
}

static int adux1020_wead_fifo(stwuct adux1020_data *data, u16 *buf, u8 buf_wen)
{
	unsigned int wegvaw;
	int i, wet;

	/* Enabwe 32MHz cwock */
	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_TEST_MODES_3,
			   ADUX1020_FOWCE_CWOCK_ON);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < buf_wen; i++) {
		wet = wegmap_wead(data->wegmap, ADUX1020_WEG_DATA_BUFFEW,
				  &wegvaw);
		if (wet < 0)
			wetuwn wet;

		buf[i] = wegvaw;
	}

	/* Set 32MHz cwock to be contwowwed by intewnaw state machine */
	wetuwn wegmap_wwite(data->wegmap, ADUX1020_WEG_TEST_MODES_3,
			    ADUX1020_FOWCE_CWOCK_WESET);
}

static int adux1020_set_mode(stwuct adux1020_data *data,
			     enum adux1020_op_modes mode)
{
	int wet;

	/* Switch to standby mode befowe changing the mode */
	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_OP_MODE,
			   ADUX1020_MODE_STANDBY);
	if (wet < 0)
		wetuwn wet;

	/* Set data out and switch to the desiwed mode */
	switch (mode) {
	case ADUX1020_MODE_PWOX_I:
		wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_OP_MODE,
					 ADUX1020_DATA_OUT_MODE_MASK,
					 ADUX1020_DATA_OUT_PWOX_I);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_OP_MODE,
					 ADUX1020_OP_MODE_MASK,
					 ADUX1020_MODE_PWOX_I);
		if (wet < 0)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int adux1020_measuwe(stwuct adux1020_data *data,
			    enum adux1020_op_modes mode,
			    u16 *vaw)
{
	unsigned int status;
	int wet, twies = 50;

	/* Disabwe INT pin as powwing is going to be used */
	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_INT_ENABWE,
			   ADUX1020_INT_DISABWE);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe mode intewwupt */
	wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_INT_MASK,
				 ADUX1020_MODE_INT_MASK,
				 adux1020_modes[mode].int_en);
	if (wet < 0)
		wetuwn wet;

	whiwe (twies--) {
		wet = wegmap_wead(data->wegmap, ADUX1020_WEG_INT_STATUS,
				  &status);
		if (wet < 0)
			wetuwn wet;

		status &= ADUX1020_FIFO_STATUS_MASK;
		if (status >= adux1020_modes[mode].bytes)
			bweak;
		msweep(20);
	}

	if (twies < 0)
		wetuwn -EIO;

	wet = adux1020_wead_fifo(data, vaw, adux1020_modes[mode].buf_wen);
	if (wet < 0)
		wetuwn wet;

	/* Cweaw mode intewwupt */
	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_INT_STATUS,
			   (~adux1020_modes[mode].int_en));
	if (wet < 0)
		wetuwn wet;

	/* Disabwe mode intewwupts */
	wetuwn wegmap_update_bits(data->wegmap, ADUX1020_WEG_INT_MASK,
				  ADUX1020_MODE_INT_MASK,
				  ADUX1020_MODE_INT_DISABWE);
}

static int adux1020_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	u16 buf[3];
	int wet = -EINVAW;
	unsigned int wegvaw;

	mutex_wock(&data->wock);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = adux1020_set_mode(data, ADUX1020_MODE_PWOX_I);
			if (wet < 0)
				goto faiw;

			wet = adux1020_measuwe(data, ADUX1020_MODE_PWOX_I, buf);
			if (wet < 0)
				goto faiw;

			*vaw = buf[0];
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_CUWWENT:
			wet = wegmap_wead(data->wegmap,
					  ADUX1020_WEG_WED_CUWWENT, &wegvaw);
			if (wet < 0)
				goto faiw;

			wegvaw = wegvaw & ADUX1020_WED_CUWWENT_MASK;

			*vaw = adux1020_wed_cuwwents[wegvaw][0];
			*vaw2 = adux1020_wed_cuwwents[wegvaw][1];

			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = wegmap_wead(data->wegmap, ADUX1020_WEG_FWEQUENCY,
					  &wegvaw);
			if (wet < 0)
				goto faiw;

			wegvaw = FIEWD_GET(ADUX1020_PWOX_FWEQ_MASK, wegvaw);

			*vaw = adux1020_wates[wegvaw][0];
			*vaw2 = adux1020_wates[wegvaw][1];

			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

faiw:
	mutex_unwock(&data->wock);

	wetuwn wet;
};

static inwine int adux1020_find_index(const int awway[][2], int count, int vaw,
				      int vaw2)
{
	int i;

	fow (i = 0; i < count; i++)
		if (vaw == awway[i][0] && vaw2 == awway[i][1])
			wetuwn i;

	wetuwn -EINVAW;
}

static int adux1020_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	int i, wet = -EINVAW;

	mutex_wock(&data->wock);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (chan->type == IIO_PWOXIMITY) {
			i = adux1020_find_index(adux1020_wates,
						AWWAY_SIZE(adux1020_wates),
						vaw, vaw2);
			if (i < 0) {
				wet = i;
				goto faiw;
			}

			wet = wegmap_update_bits(data->wegmap,
						 ADUX1020_WEG_FWEQUENCY,
						 ADUX1020_PWOX_FWEQ_MASK,
						 ADUX1020_PWOX_FWEQ(i));
		}
		bweak;
	case IIO_CHAN_INFO_PWOCESSED:
		if (chan->type == IIO_CUWWENT) {
			i = adux1020_find_index(adux1020_wed_cuwwents,
					AWWAY_SIZE(adux1020_wed_cuwwents),
					vaw, vaw2);
			if (i < 0) {
				wet = i;
				goto faiw;
			}

			wet = wegmap_update_bits(data->wegmap,
						 ADUX1020_WEG_WED_CUWWENT,
						 ADUX1020_WED_CUWWENT_MASK, i);
		}
		bweak;
	defauwt:
		bweak;
	}

faiw:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int adux1020_wwite_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw, int state)
{
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	int wet, mask;

	mutex_wock(&data->wock);

	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_INT_ENABWE,
			   ADUX1020_INT_ENABWE);
	if (wet < 0)
		goto faiw;

	wet = wegmap_wwite(data->wegmap, ADUX1020_WEG_INT_POWAWITY, 0);
	if (wet < 0)
		goto faiw;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		if (diw == IIO_EV_DIW_WISING)
			mask = ADUX1020_PWOX_ON1_INT;
		ewse
			mask = ADUX1020_PWOX_OFF1_INT;

		if (state)
			state = 0;
		ewse
			state = mask;

		wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_INT_MASK,
					 mask, state);
		if (wet < 0)
			goto faiw;

		/*
		 * Twiggew pwoximity intewwupt when the intensity is above
		 * ow bewow thweshowd
		 */
		wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_PWOX_TYPE,
					 ADUX1020_PWOX_TYPE,
					 ADUX1020_PWOX_TYPE);
		if (wet < 0)
			goto faiw;

		/* Set pwoximity mode */
		wet = adux1020_set_mode(data, ADUX1020_MODE_PWOX_I);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

faiw:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int adux1020_wead_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw)
{
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	int wet, mask;
	unsigned int wegvaw;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		if (diw == IIO_EV_DIW_WISING)
			mask = ADUX1020_PWOX_ON1_INT;
		ewse
			mask = ADUX1020_PWOX_OFF1_INT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(data->wegmap, ADUX1020_WEG_INT_MASK, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !(wegvaw & mask);
}

static int adux1020_wead_thwesh(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info, int *vaw, int *vaw2)
{
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	u8 weg;
	int wet;
	unsigned int wegvaw;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		if (diw == IIO_EV_DIW_WISING)
			weg = ADUX1020_WEG_PWOX_TH_ON1;
		ewse
			weg = ADUX1020_WEG_PWOX_TH_OFF1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = wegvaw;

	wetuwn IIO_VAW_INT;
}

static int adux1020_wwite_thwesh(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw,
				 enum iio_event_info info, int vaw, int vaw2)
{
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	u8 weg;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		if (diw == IIO_EV_DIW_WISING)
			weg = ADUX1020_WEG_PWOX_TH_ON1;
		ewse
			weg = ADUX1020_WEG_PWOX_TH_OFF1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Fuww scawe thweshowd vawue is 0-65535  */
	if (vaw < 0 || vaw > 65535)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(data->wegmap, weg, vaw);
}

static const stwuct iio_event_spec adux1020_pwoximity_event[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec adux1020_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.event_spec = adux1020_pwoximity_event,
		.num_event_specs = AWWAY_SIZE(adux1020_pwoximity_event),
	},
	{
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.extend_name = "wed",
		.output = 1,
	},
};

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(
		      "0.1 0.2 0.5 1 2 5 10 20 50 100 190 450 820 1400");

static stwuct attwibute *adux1020_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adux1020_attwibute_gwoup = {
	.attws = adux1020_attwibutes,
};

static const stwuct iio_info adux1020_info = {
	.attws = &adux1020_attwibute_gwoup,
	.wead_waw = adux1020_wead_waw,
	.wwite_waw = adux1020_wwite_waw,
	.wead_event_config = adux1020_wead_event_config,
	.wwite_event_config = adux1020_wwite_event_config,
	.wead_event_vawue = adux1020_wead_thwesh,
	.wwite_event_vawue = adux1020_wwite_thwesh,
};

static iwqwetuwn_t adux1020_intewwupt_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct adux1020_data *data = iio_pwiv(indio_dev);
	int wet, status;

	wet = wegmap_wead(data->wegmap, ADUX1020_WEG_INT_STATUS, &status);
	if (wet < 0)
		wetuwn IWQ_HANDWED;

	status &= ADUX1020_MODE_INT_STATUS_MASK;

	if (status & ADUX1020_INT_PWOX_ON1) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       iio_get_time_ns(indio_dev));
	}

	if (status & ADUX1020_INT_PWOX_OFF1) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       iio_get_time_ns(indio_dev));
	}

	wegmap_update_bits(data->wegmap, ADUX1020_WEG_INT_STATUS,
			   ADUX1020_MODE_INT_MASK, ADUX1020_INT_CWEAW);

	wetuwn IWQ_HANDWED;
}

static int adux1020_chip_init(stwuct adux1020_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, ADUX1020_WEG_CHIP_ID, &vaw);
	if (wet < 0)
		wetuwn wet;

	if ((vaw & ADUX1020_CHIP_ID_MASK) != ADUX1020_CHIP_ID) {
		dev_eww(&cwient->dev, "invawid chip id 0x%04x\n", vaw);
		wetuwn -ENODEV;
	}

	dev_dbg(&cwient->dev, "Detected ADUX1020 with chip id: 0x%04x\n", vaw);

	wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_SW_WESET,
				 ADUX1020_SW_WESET, ADUX1020_SW_WESET);
	if (wet < 0)
		wetuwn wet;

	/* Woad defauwt configuwation */
	wet = wegmap_muwti_weg_wwite(data->wegmap, adux1020_def_conf,
				     AWWAY_SIZE(adux1020_def_conf));
	if (wet < 0)
		wetuwn wet;

	wet = adux1020_fwush_fifo(data);
	if (wet < 0)
		wetuwn wet;

	/* Use WED_IWEF fow pwoximity mode */
	wet = wegmap_update_bits(data->wegmap, ADUX1020_WEG_WED_CUWWENT,
				 ADUX1020_WED_PIWEF_EN, 0);
	if (wet < 0)
		wetuwn wet;

	/* Mask aww intewwupts */
	wetuwn wegmap_update_bits(data->wegmap, ADUX1020_WEG_INT_MASK,
			   ADUX1020_MODE_INT_MASK, ADUX1020_MODE_INT_DISABWE);
}

static int adux1020_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adux1020_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	indio_dev->info = &adux1020_info;
	indio_dev->name = ADUX1020_DWV_NAME;
	indio_dev->channews = adux1020_channews;
	indio_dev->num_channews = AWWAY_SIZE(adux1020_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	data = iio_pwiv(indio_dev);

	data->wegmap = devm_wegmap_init_i2c(cwient, &adux1020_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "wegmap initiawization faiwed.\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	data->cwient = cwient;
	data->indio_dev = indio_dev;
	mutex_init(&data->wock);

	wet = adux1020_chip_init(data);
	if (wet)
		wetuwn wet;

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, adux1020_intewwupt_handwew,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
					ADUX1020_DWV_NAME, indio_dev);
		if (wet) {
			dev_eww(&cwient->dev, "iwq wequest ewwow %d\n", -wet);
			wetuwn wet;
		}
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id adux1020_id[] = {
	{ "adux1020", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, adux1020_id);

static const stwuct of_device_id adux1020_of_match[] = {
	{ .compatibwe = "adi,adux1020" },
	{ }
};
MODUWE_DEVICE_TABWE(of, adux1020_of_match);

static stwuct i2c_dwivew adux1020_dwivew = {
	.dwivew = {
		.name	= ADUX1020_DWV_NAME,
		.of_match_tabwe = adux1020_of_match,
	},
	.pwobe		= adux1020_pwobe,
	.id_tabwe	= adux1020_id,
};
moduwe_i2c_dwivew(adux1020_dwivew);

MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_DESCWIPTION("ADUX1020 photometwic sensow");
MODUWE_WICENSE("GPW");
