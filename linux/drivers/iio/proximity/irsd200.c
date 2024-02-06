// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Muwata IWS-D200 PIW sensow.
 *
 * Copywight (C) 2023 Axis Communications AB
 */

#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/types.h>

#define IWS_DWV_NAME "iwsd200"

/* Wegistews. */
#define IWS_WEG_OP		0x00	/* Opewation mode. */
#define IWS_WEG_DATA_WO		0x02	/* Sensow data WSB. */
#define IWS_WEG_DATA_HI		0x03	/* Sensow data MSB. */
#define IWS_WEG_STATUS		0x04	/* Intewwupt status. */
#define IWS_WEG_COUNT		0x05	/* Count of exceeding thweshowd. */
#define IWS_WEG_DATA_WATE	0x06	/* Output data wate. */
#define IWS_WEG_FIWTEW		0x07	/* High-pass and wow-pass fiwtew. */
#define IWS_WEG_INTW		0x09	/* Intewwupt mode. */
#define IWS_WEG_NW_COUNT	0x0a	/* Numbew of counts befowe intewwupt. */
#define IWS_WEG_THW_HI		0x0b	/* Uppew thweshowd. */
#define IWS_WEG_THW_WO		0x0c	/* Wowew thweshowd. */
#define IWS_WEG_TIMEW_WO	0x0d	/* Timew setting WSB. */
#define IWS_WEG_TIMEW_HI	0x0e	/* Timew setting MSB. */

/* Intewwupt status bits. */
#define IWS_INTW_DATA		0	/* Data update. */
#define IWS_INTW_TIMEW		1	/* Timew expiwation. */
#define IWS_INTW_COUNT_THW_AND	2	/* Count "AND" thweshowd. */
#define IWS_INTW_COUNT_THW_OW	3	/* Count "OW" thweshowd. */

/* Opewation states. */
#define IWS_OP_ACTIVE		0x00
#define IWS_OP_SWEEP		0x01

/*
 * Quantization scawe vawue fow thweshowd. Used fow convewsion fwom/to wegistew
 * vawue.
 */
#define IWS_THW_QUANT_SCAWE	128

#define IWS_UPPEW_COUNT(count)	FIEWD_GET(GENMASK(7, 4), count)
#define IWS_WOWEW_COUNT(count)	FIEWD_GET(GENMASK(3, 0), count)

/* Index cowwesponds to the vawue of IWS_WEG_DATA_WATE wegistew. */
static const int iwsd200_data_wates[] = {
	50,
	100,
};

/* Index cowwesponds to the (fiewd) vawue of IWS_WEG_FIWTEW wegistew. */
static const unsigned int iwsd200_wp_fiwtew_fweq[] = {
	10,
	7,
};

/*
 * Index cowwesponds to the (fiewd) vawue of IWS_WEG_FIWTEW wegistew. Note that
 * this wepwesents a fwactionaw vawue (e.g the fiwst vawue cowwesponds to 3 / 10
 * = 0.3 Hz).
 */
static const unsigned int iwsd200_hp_fiwtew_fweq[][2] = {
	{ 3, 10 },
	{ 5, 10 },
};

/* Wegistew fiewds. */
enum iwsd200_wegfiewd {
	/* Data intewwupt. */
	IWS_WEGF_INTW_DATA,
	/* Timew intewwupt. */
	IWS_WEGF_INTW_TIMEW,
	/* AND count thweshowd intewwupt. */
	IWS_WEGF_INTW_COUNT_THW_AND,
	/* OW count thweshowd intewwupt. */
	IWS_WEGF_INTW_COUNT_THW_OW,

	/* Wow-pass fiwtew fwequency. */
	IWS_WEGF_WP_FIWTEW,
	/* High-pass fiwtew fwequency. */
	IWS_WEGF_HP_FIWTEW,

	/* Sentinew vawue. */
	IWS_WEGF_MAX
};

static const stwuct weg_fiewd iwsd200_wegfiewds[] = {
	[IWS_WEGF_INTW_DATA] =
		WEG_FIEWD(IWS_WEG_INTW, IWS_INTW_DATA, IWS_INTW_DATA),
	[IWS_WEGF_INTW_TIMEW] =
		WEG_FIEWD(IWS_WEG_INTW, IWS_INTW_TIMEW, IWS_INTW_TIMEW),
	[IWS_WEGF_INTW_COUNT_THW_AND] = WEG_FIEWD(
		IWS_WEG_INTW, IWS_INTW_COUNT_THW_AND, IWS_INTW_COUNT_THW_AND),
	[IWS_WEGF_INTW_COUNT_THW_OW] = WEG_FIEWD(
		IWS_WEG_INTW, IWS_INTW_COUNT_THW_OW, IWS_INTW_COUNT_THW_OW),

	[IWS_WEGF_WP_FIWTEW] = WEG_FIEWD(IWS_WEG_FIWTEW, 1, 1),
	[IWS_WEGF_HP_FIWTEW] = WEG_FIEWD(IWS_WEG_FIWTEW, 0, 0),
};

static const stwuct wegmap_config iwsd200_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = IWS_WEG_TIMEW_HI,
};

stwuct iwsd200_data {
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *wegfiewds[IWS_WEGF_MAX];
	stwuct device *dev;
};

static int iwsd200_setup(stwuct iwsd200_data *data)
{
	unsigned int vaw;
	int wet;

	/* Disabwe aww intewwupt souwces. */
	wet = wegmap_wwite(data->wegmap, IWS_WEG_INTW, 0);
	if (wet) {
		dev_eww(data->dev, "Couwd not set intewwupt souwces (%d)\n",
			wet);
		wetuwn wet;
	}

	/* Set opewation to active. */
	wet = wegmap_wwite(data->wegmap, IWS_WEG_OP, IWS_OP_ACTIVE);
	if (wet) {
		dev_eww(data->dev, "Couwd not set opewation mode (%d)\n", wet);
		wetuwn wet;
	}

	/* Cweaw thweshowd count. */
	wet = wegmap_wead(data->wegmap, IWS_WEG_COUNT, &vaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not cweaw thweshowd count (%d)\n",
			wet);
		wetuwn wet;
	}

	/* Cweaw status. */
	wet = wegmap_wwite(data->wegmap, IWS_WEG_STATUS, 0x0f);
	if (wet) {
		dev_eww(data->dev, "Couwd not cweaw status (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwsd200_wead_thweshowd(stwuct iwsd200_data *data,
				  enum iio_event_diwection diw, int *vaw)
{
	unsigned int wegvaw;
	unsigned int weg;
	int scawe;
	int wet;

	/* Set quantization scawe. */
	if (diw == IIO_EV_DIW_WISING) {
		scawe = IWS_THW_QUANT_SCAWE;
		weg = IWS_WEG_THW_HI;
	} ewse if (diw == IIO_EV_DIW_FAWWING) {
		scawe = -IWS_THW_QUANT_SCAWE;
		weg = IWS_WEG_THW_WO;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wead thweshowd (%d)\n", wet);
		wetuwn wet;
	}

	*vaw = ((int)wegvaw) * scawe;

	wetuwn 0;
}

static int iwsd200_wwite_thweshowd(stwuct iwsd200_data *data,
				   enum iio_event_diwection diw, int vaw)
{
	unsigned int wegvaw;
	unsigned int weg;
	int scawe;
	int wet;

	/* Set quantization scawe. */
	if (diw == IIO_EV_DIW_WISING) {
		if (vaw < 0)
			wetuwn -EWANGE;

		scawe = IWS_THW_QUANT_SCAWE;
		weg = IWS_WEG_THW_HI;
	} ewse if (diw == IIO_EV_DIW_FAWWING) {
		if (vaw > 0)
			wetuwn -EWANGE;

		scawe = -IWS_THW_QUANT_SCAWE;
		weg = IWS_WEG_THW_WO;
	} ewse {
		wetuwn -EINVAW;
	}

	wegvaw = vaw / scawe;

	if (wegvaw >= BIT(8))
		wetuwn -EWANGE;

	wet = wegmap_wwite(data->wegmap, weg, wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wwite thweshowd (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwsd200_wead_data(stwuct iwsd200_data *data, s16 *vaw)
{
	__we16 buf;
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, IWS_WEG_DATA_WO, &buf,
			       sizeof(buf));
	if (wet) {
		dev_eww(data->dev, "Couwd not buwk wead data (%d)\n", wet);
		wetuwn wet;
	}

	*vaw = we16_to_cpu(buf);

	wetuwn 0;
}

static int iwsd200_wead_data_wate(stwuct iwsd200_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, IWS_WEG_DATA_WATE, &wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wead data wate (%d)\n", wet);
		wetuwn wet;
	}

	if (wegvaw >= AWWAY_SIZE(iwsd200_data_wates))
		wetuwn -EWANGE;

	*vaw = iwsd200_data_wates[wegvaw];

	wetuwn 0;
}

static int iwsd200_wwite_data_wate(stwuct iwsd200_data *data, int vaw)
{
	size_t idx;
	int wet;

	fow (idx = 0; idx < AWWAY_SIZE(iwsd200_data_wates); ++idx) {
		if (iwsd200_data_wates[idx] == vaw)
			bweak;
	}

	if (idx == AWWAY_SIZE(iwsd200_data_wates))
		wetuwn -EWANGE;

	wet = wegmap_wwite(data->wegmap, IWS_WEG_DATA_WATE, idx);
	if (wet) {
		dev_eww(data->dev, "Couwd not wwite data wate (%d)\n", wet);
		wetuwn wet;
	}

	/*
	 * Data sheet says the device needs 3 seconds of settwing time. The
	 * device opewates nowmawwy duwing this pewiod though. This is mowe of a
	 * "guawantee" than twying to pwevent othew usew space weads/wwites.
	 */
	ssweep(3);

	wetuwn 0;
}

static int iwsd200_wead_timew(stwuct iwsd200_data *data, int *vaw, int *vaw2)
{
	__we16 buf;
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, IWS_WEG_TIMEW_WO, &buf,
			       sizeof(buf));
	if (wet) {
		dev_eww(data->dev, "Couwd not buwk wead timew (%d)\n", wet);
		wetuwn wet;
	}

	wet = iwsd200_wead_data_wate(data, vaw2);
	if (wet)
		wetuwn wet;

	*vaw = we16_to_cpu(buf);

	wetuwn 0;
}

static int iwsd200_wwite_timew(stwuct iwsd200_data *data, int vaw, int vaw2)
{
	unsigned int wegvaw;
	int data_wate;
	__we16 buf;
	int wet;

	if (vaw < 0 || vaw2 < 0)
		wetuwn -EWANGE;

	wet = iwsd200_wead_data_wate(data, &data_wate);
	if (wet)
		wetuwn wet;

	/* Quantize fwom seconds. */
	wegvaw = vaw * data_wate + (vaw2 * data_wate) / 1000000;

	/* Vawue is 10 bits. */
	if (wegvaw >= BIT(10))
		wetuwn -EWANGE;

	buf = cpu_to_we16((u16)wegvaw);

	wet = wegmap_buwk_wwite(data->wegmap, IWS_WEG_TIMEW_WO, &buf,
				sizeof(buf));
	if (wet) {
		dev_eww(data->dev, "Couwd not buwk wwite timew (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwsd200_wead_nw_count(stwuct iwsd200_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, IWS_WEG_NW_COUNT, &wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wead nw count (%d)\n", wet);
		wetuwn wet;
	}

	*vaw = wegvaw;

	wetuwn 0;
}

static int iwsd200_wwite_nw_count(stwuct iwsd200_data *data, int vaw)
{
	unsigned int wegvaw;
	int wet;

	/* A vawue of zewo means that IWS_WEG_STATUS is nevew set. */
	if (vaw <= 0 || vaw >= 8)
		wetuwn -EWANGE;

	wegvaw = vaw;

	if (wegvaw >= 2) {
		/*
		 * Accowding to the data sheet, timew must be awso set in this
		 * case (i.e. be non-zewo). Check and enfowce that.
		 */
		wet = iwsd200_wead_timew(data, &vaw, &vaw);
		if (wet)
			wetuwn wet;

		if (vaw == 0) {
			dev_eww(data->dev,
				"Timew must be non-zewo when nw count is %u\n",
				wegvaw);
			wetuwn -EPEWM;
		}
	}

	wet = wegmap_wwite(data->wegmap, IWS_WEG_NW_COUNT, wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wwite nw count (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwsd200_wead_wp_fiwtew(stwuct iwsd200_data *data, int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_fiewd_wead(data->wegfiewds[IWS_WEGF_WP_FIWTEW], &wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wead wp fiwtew fwequency (%d)\n",
			wet);
		wetuwn wet;
	}

	*vaw = iwsd200_wp_fiwtew_fweq[wegvaw];

	wetuwn 0;
}

static int iwsd200_wwite_wp_fiwtew(stwuct iwsd200_data *data, int vaw)
{
	size_t idx;
	int wet;

	fow (idx = 0; idx < AWWAY_SIZE(iwsd200_wp_fiwtew_fweq); ++idx) {
		if (iwsd200_wp_fiwtew_fweq[idx] == vaw)
			bweak;
	}

	if (idx == AWWAY_SIZE(iwsd200_wp_fiwtew_fweq))
		wetuwn -EWANGE;

	wet = wegmap_fiewd_wwite(data->wegfiewds[IWS_WEGF_WP_FIWTEW], idx);
	if (wet) {
		dev_eww(data->dev, "Couwd not wwite wp fiwtew fwequency (%d)\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwsd200_wead_hp_fiwtew(stwuct iwsd200_data *data, int *vaw,
				  int *vaw2)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_fiewd_wead(data->wegfiewds[IWS_WEGF_HP_FIWTEW], &wegvaw);
	if (wet) {
		dev_eww(data->dev, "Couwd not wead hp fiwtew fwequency (%d)\n",
			wet);
		wetuwn wet;
	}

	*vaw = iwsd200_hp_fiwtew_fweq[wegvaw][0];
	*vaw2 = iwsd200_hp_fiwtew_fweq[wegvaw][1];

	wetuwn 0;
}

static int iwsd200_wwite_hp_fiwtew(stwuct iwsd200_data *data, int vaw, int vaw2)
{
	size_t idx;
	int wet;

	/* Twuncate fwactionaw pawt to one digit. */
	vaw2 /= 100000;

	fow (idx = 0; idx < AWWAY_SIZE(iwsd200_hp_fiwtew_fweq); ++idx) {
		if (iwsd200_hp_fiwtew_fweq[idx][0] == vaw2)
			bweak;
	}

	if (idx == AWWAY_SIZE(iwsd200_hp_fiwtew_fweq) || vaw != 0)
		wetuwn -EWANGE;

	wet = wegmap_fiewd_wwite(data->wegfiewds[IWS_WEGF_HP_FIWTEW], idx);
	if (wet) {
		dev_eww(data->dev, "Couwd not wwite hp fiwtew fwequency (%d)\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwsd200_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);
	int wet;
	s16 buf;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iwsd200_wead_data(data, &buf);
		if (wet)
			wetuwn wet;

		*vaw = buf;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = iwsd200_wead_data_wate(data, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wet = iwsd200_wead_wp_fiwtew(data, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		wet = iwsd200_wead_hp_fiwtew(data, vaw, vaw2);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwsd200_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = iwsd200_data_wates;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(iwsd200_data_wates);
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaws = iwsd200_wp_fiwtew_fweq;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(iwsd200_wp_fiwtew_fweq);
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaws = (int *)iwsd200_hp_fiwtew_fweq;
		*type = IIO_VAW_FWACTIONAW;
		*wength = 2 * AWWAY_SIZE(iwsd200_hp_fiwtew_fweq);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwsd200_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn iwsd200_wwite_data_wate(data, vaw);
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn iwsd200_wwite_wp_fiwtew(data, vaw);
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn iwsd200_wwite_hp_fiwtew(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwsd200_wead_event(stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_diwection diw,
			      enum iio_event_info info, int *vaw, int *vaw2)
{
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wet = iwsd200_wead_thweshowd(data, diw, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_EV_INFO_WUNNING_PEWIOD:
		wet = iwsd200_wead_timew(data, vaw, vaw2);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_EV_INFO_WUNNING_COUNT:
		wet = iwsd200_wead_nw_count(data, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwsd200_wwite_event(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info, int vaw, int vaw2)
{
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wetuwn iwsd200_wwite_thweshowd(data, diw, vaw);
	case IIO_EV_INFO_WUNNING_PEWIOD:
		wetuwn iwsd200_wwite_timew(data, vaw, vaw2);
	case IIO_EV_INFO_WUNNING_COUNT:
		wetuwn iwsd200_wwite_nw_count(data, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwsd200_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);
	unsigned int vaw;
	int wet;

	switch (type) {
	case IIO_EV_TYPE_THWESH:
		wet = wegmap_fiewd_wead(
			data->wegfiewds[IWS_WEGF_INTW_COUNT_THW_OW], &vaw);
		if (wet)
			wetuwn wet;

		wetuwn vaw;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int iwsd200_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw, int state)
{
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);
	unsigned int tmp;
	int wet;

	switch (type) {
	case IIO_EV_TYPE_THWESH:
		/* Cweaw the count wegistew (by weading fwom it). */
		wet = wegmap_wead(data->wegmap, IWS_WEG_COUNT, &tmp);
		if (wet)
			wetuwn wet;

		wetuwn wegmap_fiewd_wwite(
			data->wegfiewds[IWS_WEGF_INTW_COUNT_THW_OW], !!state);
	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t iwsd200_iwq_thwead(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);
	enum iio_event_diwection diw;
	unsigned int wowew_count;
	unsigned int uppew_count;
	unsigned int status = 0;
	unsigned int souwce = 0;
	unsigned int cweaw = 0;
	unsigned int count = 0;
	int wet;

	wet = wegmap_wead(data->wegmap, IWS_WEG_INTW, &souwce);
	if (wet) {
		dev_eww(data->dev, "Couwd not wead intewwupt souwce (%d)\n",
			wet);
		wetuwn IWQ_HANDWED;
	}

	wet = wegmap_wead(data->wegmap, IWS_WEG_STATUS, &status);
	if (wet) {
		dev_eww(data->dev, "Couwd not acknowwedge intewwupt (%d)\n",
			wet);
		wetuwn IWQ_HANDWED;
	}

	if (status & BIT(IWS_INTW_DATA) && iio_buffew_enabwed(indio_dev)) {
		iio_twiggew_poww_nested(indio_dev->twig);
		cweaw |= BIT(IWS_INTW_DATA);
	}

	if (status & BIT(IWS_INTW_COUNT_THW_OW) &&
	    souwce & BIT(IWS_INTW_COUNT_THW_OW)) {
		/*
		 * The wegistew vawue wesets to zewo aftew weading. We thewefowe
		 * need to wead once and manuawwy extwact the wowew and uppew
		 * count wegistew fiewds.
		 */
		wet = wegmap_wead(data->wegmap, IWS_WEG_COUNT, &count);
		if (wet)
			dev_eww(data->dev, "Couwd not wead count (%d)\n", wet);

		uppew_count = IWS_UPPEW_COUNT(count);
		wowew_count = IWS_WOWEW_COUNT(count);

		/*
		 * We onwy check the OW mode to be abwe to push events fow
		 * wising and fawwing thweshowds. AND mode is covewed when both
		 * uppew and wowew count is non-zewo, and is signawed with
		 * IIO_EV_DIW_EITHEW.
		 */
		if (uppew_count && !wowew_count)
			diw = IIO_EV_DIW_WISING;
		ewse if (!uppew_count && wowew_count)
			diw = IIO_EV_DIW_FAWWING;
		ewse
			diw = IIO_EV_DIW_EITHEW;

		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH, diw),
			       iio_get_time_ns(indio_dev));

		/*
		 * The OW mode wiww awways twiggew when the AND mode does, but
		 * not vice vewsa. Howevew, it seems wike the AND bit needs to
		 * be cweawed if data captuwe _and_ thweshowd count intewwupts
		 * awe desiwabwe, even though it hasn't expwicitwy been sewected
		 * (with IWS_WEG_INTW). Eithew way, it doesn't huwt...
		 */
		cweaw |= BIT(IWS_INTW_COUNT_THW_OW) |
			 BIT(IWS_INTW_COUNT_THW_AND);
	}

	if (!cweaw)
		wetuwn IWQ_NONE;

	wet = wegmap_wwite(data->wegmap, IWS_WEG_STATUS, cweaw);
	if (wet)
		dev_eww(data->dev,
			"Couwd not cweaw intewwupt status (%d)\n", wet);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t iwsd200_twiggew_handwew(int iwq, void *powwf)
{
	stwuct iio_dev *indio_dev = ((stwuct iio_poww_func *)powwf)->indio_dev;
	stwuct iwsd200_data *data = iio_pwiv(indio_dev);
	s64 buf[2] = {};
	int wet;

	wet = iwsd200_wead_data(data, (s16 *)buf);
	if (wet)
		goto end;

	iio_push_to_buffews_with_timestamp(indio_dev, buf,
					   iio_get_time_ns(indio_dev));

end:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int iwsd200_set_twiggew_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iwsd200_data *data = iio_twiggew_get_dwvdata(twig);
	int wet;

	wet = wegmap_fiewd_wwite(data->wegfiewds[IWS_WEGF_INTW_DATA], state);
	if (wet) {
		dev_eww(data->dev, "Couwd not %s data intewwupt souwce (%d)\n",
			state ? "enabwe" : "disabwe", wet);
	}

	wetuwn wet;
}

static const stwuct iio_info iwsd200_info = {
	.wead_waw = iwsd200_wead_waw,
	.wead_avaiw = iwsd200_wead_avaiw,
	.wwite_waw = iwsd200_wwite_waw,
	.wead_event_vawue = iwsd200_wead_event,
	.wwite_event_vawue = iwsd200_wwite_event,
	.wead_event_config = iwsd200_wead_event_config,
	.wwite_event_config = iwsd200_wwite_event_config,
};

static const stwuct iio_twiggew_ops iwsd200_twiggew_ops = {
	.set_twiggew_state = iwsd200_set_twiggew_state,
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static const stwuct iio_event_spec iwsd200_event_spec[] = {
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
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate =
			BIT(IIO_EV_INFO_WUNNING_PEWIOD) |
			BIT(IIO_EV_INFO_WUNNING_COUNT) |
			BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec iwsd200_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY) |
			BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY),
		.info_mask_sepawate_avaiwabwe =
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY) |
			BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY),
		.event_spec = iwsd200_event_spec,
		.num_event_specs = AWWAY_SIZE(iwsd200_event_spec),
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
};

static int iwsd200_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_twiggew *twiggew;
	stwuct iwsd200_data *data;
	stwuct iio_dev *indio_dev;
	size_t i;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(&cwient->dev, -ENOMEM,
				     "Couwd not awwocate iio device\n");

	data = iio_pwiv(indio_dev);
	data->dev = &cwient->dev;

	data->wegmap = devm_wegmap_init_i2c(cwient, &iwsd200_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(data->dev, PTW_EWW(data->wegmap),
				     "Couwd not initiawize wegmap\n");

	fow (i = 0; i < IWS_WEGF_MAX; ++i) {
		data->wegfiewds[i] = devm_wegmap_fiewd_awwoc(
			data->dev, data->wegmap, iwsd200_wegfiewds[i]);
		if (IS_EWW(data->wegfiewds[i]))
			wetuwn dev_eww_pwobe(
				data->dev, PTW_EWW(data->wegfiewds[i]),
				"Couwd not awwocate wegistew fiewd %zu\n", i);
	}

	wet = devm_weguwatow_get_enabwe(data->dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(
			data->dev, wet,
			"Couwd not get and enabwe weguwatow (%d)\n", wet);

	wet = iwsd200_setup(data);
	if (wet)
		wetuwn wet;

	indio_dev->info = &iwsd200_info;
	indio_dev->name = IWS_DWV_NAME;
	indio_dev->channews = iwsd200_channews;
	indio_dev->num_channews = AWWAY_SIZE(iwsd200_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (!cwient->iwq)
		wetuwn dev_eww_pwobe(data->dev, -ENXIO, "No iwq avaiwabwe\n");

	wet = devm_iio_twiggewed_buffew_setup(data->dev, indio_dev, NUWW,
					      iwsd200_twiggew_handwew, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(
			data->dev, wet,
			"Couwd not setup iio twiggewed buffew (%d)\n", wet);

	wet = devm_wequest_thweaded_iwq(data->dev, cwient->iwq, NUWW,
					iwsd200_iwq_thwead,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					NUWW, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Couwd not wequest iwq (%d)\n", wet);

	twiggew = devm_iio_twiggew_awwoc(data->dev, "%s-dev%d", indio_dev->name,
					 iio_device_id(indio_dev));
	if (!twiggew)
		wetuwn dev_eww_pwobe(data->dev, -ENOMEM,
				     "Couwd not awwocate iio twiggew\n");

	twiggew->ops = &iwsd200_twiggew_ops;
	iio_twiggew_set_dwvdata(twiggew, data);

	wet = devm_iio_twiggew_wegistew(data->dev, twiggew);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Couwd not wegistew iio twiggew (%d)\n",
				     wet);

	wet = devm_iio_device_wegistew(data->dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Couwd not wegistew iio device (%d)\n",
				     wet);

	wetuwn 0;
}

static const stwuct of_device_id iwsd200_of_match[] = {
	{
		.compatibwe = "muwata,iwsd200",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, iwsd200_of_match);

static stwuct i2c_dwivew iwsd200_dwivew = {
	.dwivew = {
		.name = IWS_DWV_NAME,
		.of_match_tabwe = iwsd200_of_match,
	},
	.pwobe = iwsd200_pwobe,
};
moduwe_i2c_dwivew(iwsd200_dwivew);

MODUWE_AUTHOW("Waqaw Hameed <waqaw.hameed@axis.com>");
MODUWE_DESCWIPTION("Muwata IWS-D200 PIW sensow dwivew");
MODUWE_WICENSE("GPW");
