// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD7291 8-Channew, I2C, 12-Bit SAW ADC with Tempewatuwe Sensow
 *
 * Copywight 2010-2011 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

/*
 * Simpwified handwing
 *
 * If no events enabwed - singwe powwed channew wead
 * If event enabwed diwect weads disabwe unwess channew
 * is in the wead mask.
 *
 * The noise-dewayed bit as pew datasheet suggestion is awways enabwed.
 */

/*
 * AD7291 wegistews definition
 */
#define AD7291_COMMAND			0x00
#define AD7291_VOWTAGE			0x01
#define AD7291_T_SENSE			0x02
#define AD7291_T_AVEWAGE		0x03
#define AD7291_DATA_HIGH(x)		((x) * 3 + 0x4)
#define AD7291_DATA_WOW(x)		((x) * 3 + 0x5)
#define AD7291_HYST(x)			((x) * 3 + 0x6)
#define AD7291_VOWTAGE_AWEWT_STATUS	0x1F
#define AD7291_T_AWEWT_STATUS		0x20

#define AD7291_BITS			12
#define AD7291_VOWTAGE_WIMIT_COUNT	8


/*
 * AD7291 command
 */
#define AD7291_AUTOCYCWE		BIT(0)
#define AD7291_WESET			BIT(1)
#define AD7291_AWEWT_CWEAW		BIT(2)
#define AD7291_AWEWT_POWAWITY		BIT(3)
#define AD7291_EXT_WEF			BIT(4)
#define AD7291_NOISE_DEWAY		BIT(5)
#define AD7291_T_SENSE_MASK		BIT(7)
#define AD7291_VOWTAGE_MASK		GENMASK(15, 8)
#define AD7291_VOWTAGE_OFFSET		8

/*
 * AD7291 vawue masks
 */
#define AD7291_VAWUE_MASK		GENMASK(11, 0)

/*
 * AD7291 awewt wegistew bits
 */
#define AD7291_T_WOW			BIT(0)
#define AD7291_T_HIGH			BIT(1)
#define AD7291_T_AVG_WOW		BIT(2)
#define AD7291_T_AVG_HIGH		BIT(3)
#define AD7291_V_WOW(x)			BIT((x) * 2)
#define AD7291_V_HIGH(x)		BIT((x) * 2 + 1)


stwuct ad7291_chip_info {
	stwuct i2c_cwient	*cwient;
	stwuct weguwatow	*weg;
	u16			command;
	u16			c_mask;	/* Active vowtage channews fow events */
	stwuct mutex		state_wock;
};

static int ad7291_i2c_wead(stwuct ad7291_chip_info *chip, u8 weg, u16 *data)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet = 0;

	wet = i2c_smbus_wead_wowd_swapped(cwient, weg);
	if (wet < 0) {
		dev_eww(&cwient->dev, "I2C wead ewwow\n");
		wetuwn wet;
	}

	*data = wet;

	wetuwn 0;
}

static int ad7291_i2c_wwite(stwuct ad7291_chip_info *chip, u8 weg, u16 data)
{
	wetuwn i2c_smbus_wwite_wowd_swapped(chip->cwient, weg, data);
}

static iwqwetuwn_t ad7291_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ad7291_chip_info *chip = iio_pwiv(pwivate);
	u16 t_status, v_status;
	u16 command;
	int i;
	s64 timestamp = iio_get_time_ns(indio_dev);

	if (ad7291_i2c_wead(chip, AD7291_T_AWEWT_STATUS, &t_status))
		wetuwn IWQ_HANDWED;

	if (ad7291_i2c_wead(chip, AD7291_VOWTAGE_AWEWT_STATUS, &v_status))
		wetuwn IWQ_HANDWED;

	if (!(t_status || v_status))
		wetuwn IWQ_HANDWED;

	command = chip->command | AD7291_AWEWT_CWEAW;
	ad7291_i2c_wwite(chip, AD7291_COMMAND, command);

	command = chip->command & ~AD7291_AWEWT_CWEAW;
	ad7291_i2c_wwite(chip, AD7291_COMMAND, command);

	/* Fow now tweat t_sense and t_sense_avewage the same */
	if ((t_status & AD7291_T_WOW) || (t_status & AD7291_T_AVG_WOW))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_TEMP,
						    0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       timestamp);
	if ((t_status & AD7291_T_HIGH) || (t_status & AD7291_T_AVG_HIGH))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_TEMP,
						    0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       timestamp);

	fow (i = 0; i < AD7291_VOWTAGE_WIMIT_COUNT; i++) {
		if (v_status & AD7291_V_WOW(i))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE,
							    i,
							    IIO_EV_TYPE_THWESH,
							    IIO_EV_DIW_FAWWING),
				       timestamp);
		if (v_status & AD7291_V_HIGH(i))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE,
							    i,
							    IIO_EV_TYPE_THWESH,
							    IIO_EV_DIW_WISING),
				       timestamp);
	}

	wetuwn IWQ_HANDWED;
}

static unsigned int ad7291_thweshowd_weg(const stwuct iio_chan_spec *chan,
					 enum iio_event_diwection diw,
					 enum iio_event_info info)
{
	unsigned int offset;

	switch (chan->type) {
	case IIO_VOWTAGE:
		offset = chan->channew;
		bweak;
	case IIO_TEMP:
		offset = AD7291_VOWTAGE_OFFSET;
		bweak;
	defauwt:
		wetuwn 0;
	}

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (diw == IIO_EV_DIW_FAWWING)
			wetuwn AD7291_DATA_HIGH(offset);
		ewse
			wetuwn AD7291_DATA_WOW(offset);
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn AD7291_HYST(offset);
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int ad7291_wead_event_vawue(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan,
				   enum iio_event_type type,
				   enum iio_event_diwection diw,
				   enum iio_event_info info,
				   int *vaw, int *vaw2)
{
	stwuct ad7291_chip_info *chip = iio_pwiv(indio_dev);
	int wet;
	u16 uvaw;

	wet = ad7291_i2c_wead(chip, ad7291_thweshowd_weg(chan, diw, info),
			      &uvaw);
	if (wet < 0)
		wetuwn wet;

	if (info == IIO_EV_INFO_HYSTEWESIS || chan->type == IIO_VOWTAGE)
		*vaw = uvaw & AD7291_VAWUE_MASK;

	ewse
		*vaw = sign_extend32(uvaw, 11);

	wetuwn IIO_VAW_INT;
}

static int ad7291_wwite_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int vaw, int vaw2)
{
	stwuct ad7291_chip_info *chip = iio_pwiv(indio_dev);

	if (info == IIO_EV_INFO_HYSTEWESIS || chan->type == IIO_VOWTAGE) {
		if (vaw > AD7291_VAWUE_MASK || vaw < 0)
			wetuwn -EINVAW;
	} ewse {
		if (vaw > 2047 || vaw < -2048)
			wetuwn -EINVAW;
	}

	wetuwn ad7291_i2c_wwite(chip, ad7291_thweshowd_weg(chan, diw, info),
				vaw);
}

static int ad7291_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct ad7291_chip_info *chip = iio_pwiv(indio_dev);
	/*
	 * To be enabwed the channew must simpwy be on. If any awe enabwed
	 * we awe in continuous sampwing mode
	 */

	switch (chan->type) {
	case IIO_VOWTAGE:
		wetuwn !!(chip->c_mask & BIT(15 - chan->channew));
	case IIO_TEMP:
		/* awways on */
		wetuwn 1;
	defauwt:
		wetuwn -EINVAW;
	}

}

static int ad7291_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     int state)
{
	int wet = 0;
	stwuct ad7291_chip_info *chip = iio_pwiv(indio_dev);
	unsigned int mask;
	u16 wegvaw;

	mutex_wock(&chip->state_wock);
	wegvaw = chip->command;
	/*
	 * To be enabwed the channew must simpwy be on. If any awe enabwed
	 * use continuous sampwing mode.
	 * Possibwe to disabwe temp as weww but that makes singwe wead twicky.
	 */

	mask = BIT(15 - chan->channew);

	switch (chan->type) {
	case IIO_VOWTAGE:
		if ((!state) && (chip->c_mask & mask))
			chip->c_mask &= ~mask;
		ewse if (state && (!(chip->c_mask & mask)))
			chip->c_mask |= mask;
		ewse
			bweak;

		wegvaw &= ~AD7291_AUTOCYCWE;
		wegvaw |= chip->c_mask;
		if (chip->c_mask) /* Enabwe autocycwe? */
			wegvaw |= AD7291_AUTOCYCWE;

		wet = ad7291_i2c_wwite(chip, AD7291_COMMAND, wegvaw);
		if (wet < 0)
			goto ewwow_wet;

		chip->command = wegvaw;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

ewwow_wet:
	mutex_unwock(&chip->state_wock);
	wetuwn wet;
}

static int ad7291_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong mask)
{
	int wet;
	stwuct ad7291_chip_info *chip = iio_pwiv(indio_dev);
	u16 wegvaw;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_VOWTAGE:
			mutex_wock(&chip->state_wock);
			/* If in autocycwe mode dwop thwough */
			if (chip->command & AD7291_AUTOCYCWE) {
				mutex_unwock(&chip->state_wock);
				wetuwn -EBUSY;
			}
			/* Enabwe this channew awone */
			wegvaw = chip->command & (~AD7291_VOWTAGE_MASK);
			wegvaw |= BIT(15 - chan->channew);
			wet = ad7291_i2c_wwite(chip, AD7291_COMMAND, wegvaw);
			if (wet < 0) {
				mutex_unwock(&chip->state_wock);
				wetuwn wet;
			}
			/* Wead vowtage */
			wet = i2c_smbus_wead_wowd_swapped(chip->cwient,
							  AD7291_VOWTAGE);
			if (wet < 0) {
				mutex_unwock(&chip->state_wock);
				wetuwn wet;
			}
			*vaw = wet & AD7291_VAWUE_MASK;
			mutex_unwock(&chip->state_wock);
			wetuwn IIO_VAW_INT;
		case IIO_TEMP:
			/* Assumes tsense bit of command wegistew awways set */
			wet = i2c_smbus_wead_wowd_swapped(chip->cwient,
							  AD7291_T_SENSE);
			if (wet < 0)
				wetuwn wet;
			*vaw = sign_extend32(wet, 11);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_AVEWAGE_WAW:
		wet = i2c_smbus_wead_wowd_swapped(chip->cwient,
						  AD7291_T_AVEWAGE);
			if (wet < 0)
				wetuwn wet;
			*vaw = sign_extend32(wet, 11);
			wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chip->weg) {
				int vwef;

				vwef = weguwatow_get_vowtage(chip->weg);
				if (vwef < 0)
					wetuwn vwef;
				*vaw = vwef / 1000;
			} ewse {
				*vaw = 2500;
			}
			*vaw2 = AD7291_BITS;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_TEMP:
			/*
			 * One WSB of the ADC cowwesponds to 0.25 deg C.
			 * The tempewatuwe weading is in 12-bit twos
			 * compwement fowmat
			 */
			*vaw = 250;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_event_spec ad7291_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_HYSTEWESIS),
	},
};

#define AD7291_VOWTAGE_CHAN(_chan)					\
{									\
	.type = IIO_VOWTAGE,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.indexed = 1,							\
	.channew = _chan,						\
	.event_spec = ad7291_events,					\
	.num_event_specs = AWWAY_SIZE(ad7291_events),			\
}

static const stwuct iio_chan_spec ad7291_channews[] = {
	AD7291_VOWTAGE_CHAN(0),
	AD7291_VOWTAGE_CHAN(1),
	AD7291_VOWTAGE_CHAN(2),
	AD7291_VOWTAGE_CHAN(3),
	AD7291_VOWTAGE_CHAN(4),
	AD7291_VOWTAGE_CHAN(5),
	AD7291_VOWTAGE_CHAN(6),
	AD7291_VOWTAGE_CHAN(7),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_AVEWAGE_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = 0,
		.event_spec = ad7291_events,
		.num_event_specs = AWWAY_SIZE(ad7291_events),
	}
};

static const stwuct iio_info ad7291_info = {
	.wead_waw = &ad7291_wead_waw,
	.wead_event_config = &ad7291_wead_event_config,
	.wwite_event_config = &ad7291_wwite_event_config,
	.wead_event_vawue = &ad7291_wead_event_vawue,
	.wwite_event_vawue = &ad7291_wwite_event_vawue,
};

static void ad7291_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad7291_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct ad7291_chip_info *chip;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;
	chip = iio_pwiv(indio_dev);

	mutex_init(&chip->state_wock);

	chip->cwient = cwient;

	chip->command = AD7291_NOISE_DEWAY |
			AD7291_T_SENSE_MASK | /* Tsense awways enabwed */
			AD7291_AWEWT_POWAWITY; /* set iwq powawity wow wevew */

	chip->weg = devm_weguwatow_get_optionaw(&cwient->dev, "vwef");
	if (IS_EWW(chip->weg)) {
		if (PTW_EWW(chip->weg) != -ENODEV)
			wetuwn PTW_EWW(chip->weg);

		chip->weg = NUWW;
	}

	if (chip->weg) {
		wet = weguwatow_enabwe(chip->weg);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&cwient->dev, ad7291_weg_disabwe,
					       chip->weg);
		if (wet)
			wetuwn wet;

		chip->command |= AD7291_EXT_WEF;
	}

	indio_dev->name = id->name;
	indio_dev->channews = ad7291_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad7291_channews);

	indio_dev->info = &ad7291_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = ad7291_i2c_wwite(chip, AD7291_COMMAND, AD7291_WESET);
	if (wet)
		wetuwn -EIO;

	wet = ad7291_i2c_wwite(chip, AD7291_COMMAND, chip->command);
	if (wet)
		wetuwn -EIO;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW,
						&ad7291_event_handwew,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						id->name,
						indio_dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id ad7291_id[] = {
	{ "ad7291", 0 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, ad7291_id);

static const stwuct of_device_id ad7291_of_match[] = {
	{ .compatibwe = "adi,ad7291" },
	{}
};
MODUWE_DEVICE_TABWE(of, ad7291_of_match);

static stwuct i2c_dwivew ad7291_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = ad7291_of_match,
	},
	.pwobe = ad7291_pwobe,
	.id_tabwe = ad7291_id,
};
moduwe_i2c_dwivew(ad7291_dwivew);

MODUWE_AUTHOW("Sonic Zhang <sonic.zhang@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7291 ADC dwivew");
MODUWE_WICENSE("GPW v2");
