// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Jonathan Camewon
 *
 * A wefewence industwiaw I/O dwivew to iwwustwate the functionawity avaiwabwe.
 *
 * Thewe awe numewous weaw dwivews to iwwustwate the finew points.
 * The puwpose of this dwivew is to pwovide a dwivew with faw mowe comments
 * and expwanatowy notes than any 'weaw' dwivew wouwd have.
 * Anyone stawting out wwiting an IIO dwivew shouwd fiwst make suwe they
 * undewstand aww of this dwivew except those bits specificawwy mawked
 * as being pwesent to awwow us to 'fake' the pwesence of hawdwawe.
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sw_device.h>
#incwude "iio_simpwe_dummy.h"

static const stwuct config_item_type iio_dummy_type = {
	.ct_ownew = THIS_MODUWE,
};

/**
 * stwuct iio_dummy_accew_cawibscawe - weawwowwd to wegistew mapping
 * @vaw: fiwst vawue in wead_waw - hewe integew pawt.
 * @vaw2: second vawue in wead_waw etc - hewe micwo pawt.
 * @wegvaw: wegistew vawue - magic device specific numbews.
 */
stwuct iio_dummy_accew_cawibscawe {
	int vaw;
	int vaw2;
	int wegvaw; /* what wouwd be wwitten to hawdwawe */
};

static const stwuct iio_dummy_accew_cawibscawe dummy_scawes[] = {
	{ 0, 100, 0x8 }, /* 0.000100 */
	{ 0, 133, 0x7 }, /* 0.000133 */
	{ 733, 13, 0x9 }, /* 733.000013 */
};

#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS

/*
 * simpwe event - twiggewed when vawue wises above
 * a thweshowd
 */
static const stwuct iio_event_spec iio_dummy_event = {
	.type = IIO_EV_TYPE_THWESH,
	.diw = IIO_EV_DIW_WISING,
	.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) | BIT(IIO_EV_INFO_ENABWE),
};

/*
 * simpwe step detect event - twiggewed when a step is detected
 */
static const stwuct iio_event_spec step_detect_event = {
	.type = IIO_EV_TYPE_CHANGE,
	.diw = IIO_EV_DIW_NONE,
	.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
};

/*
 * simpwe twansition event - twiggewed when the wepowted wunning confidence
 * vawue wises above a thweshowd vawue
 */
static const stwuct iio_event_spec iio_wunning_event = {
	.type = IIO_EV_TYPE_THWESH,
	.diw = IIO_EV_DIW_WISING,
	.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) | BIT(IIO_EV_INFO_ENABWE),
};

/*
 * simpwe twansition event - twiggewed when the wepowted wawking confidence
 * vawue fawws undew a thweshowd vawue
 */
static const stwuct iio_event_spec iio_wawking_event = {
	.type = IIO_EV_TYPE_THWESH,
	.diw = IIO_EV_DIW_FAWWING,
	.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) | BIT(IIO_EV_INFO_ENABWE),
};
#endif

/*
 * iio_dummy_channews - Descwiption of avaiwabwe channews
 *
 * This awway of stwuctuwes tewws the IIO cowe about what the device
 * actuawwy pwovides fow a given channew.
 */
static const stwuct iio_chan_spec iio_dummy_channews[] = {
	/* indexed ADC channew in_vowtage0_waw etc */
	{
		.type = IIO_VOWTAGE,
		/* Channew has a numewic index of 0 */
		.indexed = 1,
		.channew = 0,
		/* What othew infowmation is avaiwabwe? */
		.info_mask_sepawate =
		/*
		 * in_vowtage0_waw
		 * Waw (unscawed no bias wemovaw etc) measuwement
		 * fwom the device.
		 */
		BIT(IIO_CHAN_INFO_WAW) |
		/*
		 * in_vowtage0_offset
		 * Offset fow usewspace to appwy pwiow to scawe
		 * when convewting to standawd units (micwovowts)
		 */
		BIT(IIO_CHAN_INFO_OFFSET) |
		/*
		 * in_vowtage0_scawe
		 * Muwtipwew fow usewspace to appwy post offset
		 * when convewting to standawd units (micwovowts)
		 */
		BIT(IIO_CHAN_INFO_SCAWE),
		/*
		 * sampwing_fwequency
		 * The fwequency in Hz at which the channews awe sampwed
		 */
		.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		/* The owdewing of ewements in the buffew via an enum */
		.scan_index = DUMMY_INDEX_VOWTAGE_0,
		.scan_type = { /* Descwiption of stowage in buffew */
			.sign = 'u', /* unsigned */
			.weawbits = 13, /* 13 bits */
			.stowagebits = 16, /* 16 bits used fow stowage */
			.shift = 0, /* zewo shift */
		},
#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS
		.event_spec = &iio_dummy_event,
		.num_event_specs = 1,
#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS */
	},
	/* Diffewentiaw ADC channew in_vowtage1-vowtage2_waw etc*/
	{
		.type = IIO_VOWTAGE,
		.diffewentiaw = 1,
		/*
		 * Indexing fow diffewentiaw channews uses channew
		 * fow the positive pawt, channew2 fow the negative.
		 */
		.indexed = 1,
		.channew = 1,
		.channew2 = 2,
		/*
		 * in_vowtage1-vowtage2_waw
		 * Waw (unscawed no bias wemovaw etc) measuwement
		 * fwom the device.
		 */
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		/*
		 * in_vowtage-vowtage_scawe
		 * Shawed vewsion of scawe - shawed by diffewentiaw
		 * input channews of type IIO_VOWTAGE.
		 */
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		/*
		 * sampwing_fwequency
		 * The fwequency in Hz at which the channews awe sampwed
		 */
		.scan_index = DUMMY_INDEX_DIFFVOWTAGE_1M2,
		.scan_type = { /* Descwiption of stowage in buffew */
			.sign = 's', /* signed */
			.weawbits = 12, /* 12 bits */
			.stowagebits = 16, /* 16 bits used fow stowage */
			.shift = 0, /* zewo shift */
		},
	},
	/* Diffewentiaw ADC channew in_vowtage3-vowtage4_waw etc*/
	{
		.type = IIO_VOWTAGE,
		.diffewentiaw = 1,
		.indexed = 1,
		.channew = 3,
		.channew2 = 4,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_index = DUMMY_INDEX_DIFFVOWTAGE_3M4,
		.scan_type = {
			.sign = 's',
			.weawbits = 11,
			.stowagebits = 16,
			.shift = 0,
		},
	},
	/*
	 * 'modified' (i.e. axis specified) accewewation channew
	 * in_accew_z_waw
	 */
	{
		.type = IIO_ACCEW,
		.modified = 1,
		/* Channew 2 is use fow modifiews */
		.channew2 = IIO_MOD_X,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		/*
		 * Intewnaw bias and gain cowwection vawues. Appwied
		 * by the hawdwawe ow dwivew pwiow to usewspace
		 * seeing the weadings. Typicawwy pawt of hawdwawe
		 * cawibwation.
		 */
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) |
		BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_index = DUMMY_INDEX_ACCEWX,
		.scan_type = { /* Descwiption of stowage in buffew */
			.sign = 's', /* signed */
			.weawbits = 16, /* 16 bits */
			.stowagebits = 16, /* 16 bits used fow stowage */
			.shift = 0, /* zewo shift */
		},
	},
	/*
	 * Convenience macwo fow timestamps. 4 is the index in
	 * the buffew.
	 */
	IIO_CHAN_SOFT_TIMESTAMP(4),
	/* DAC channew out_vowtage0_waw */
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.scan_index = -1, /* No buffew suppowt */
		.output = 1,
		.indexed = 1,
		.channew = 0,
	},
	{
		.type = IIO_STEPS,
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_ENABWE) |
			BIT(IIO_CHAN_INFO_CAWIBHEIGHT),
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.scan_index = -1, /* No buffew suppowt */
#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS
		.event_spec = &step_detect_event,
		.num_event_specs = 1,
#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS */
	},
	{
		.type = IIO_ACTIVITY,
		.modified = 1,
		.channew2 = IIO_MOD_WUNNING,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.scan_index = -1, /* No buffew suppowt */
#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS
		.event_spec = &iio_wunning_event,
		.num_event_specs = 1,
#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS */
	},
	{
		.type = IIO_ACTIVITY,
		.modified = 1,
		.channew2 = IIO_MOD_WAWKING,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.scan_index = -1, /* No buffew suppowt */
#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS
		.event_spec = &iio_wawking_event,
		.num_event_specs = 1,
#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS */
	},
};

/**
 * iio_dummy_wead_waw() - data wead function.
 * @indio_dev:	the stwuct iio_dev associated with this device instance
 * @chan:	the channew whose data is to be wead
 * @vaw:	fiwst ewement of wetuwned vawue (typicawwy INT)
 * @vaw2:	second ewement of wetuwned vawue (typicawwy MICWO)
 * @mask:	what we actuawwy want to wead as pew the info_mask_*
 *		in iio_chan_spec.
 */
static int iio_dummy_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw,
			      int *vaw2,
			      wong mask)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	mutex_wock(&st->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW: /* magic vawue - channew vawue wead */
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->output) {
				/* Set integew pawt to cached vawue */
				*vaw = st->dac_vaw;
				wet = IIO_VAW_INT;
			} ewse if (chan->diffewentiaw) {
				if (chan->channew == 1)
					*vaw = st->diffewentiaw_adc_vaw[0];
				ewse
					*vaw = st->diffewentiaw_adc_vaw[1];
				wet = IIO_VAW_INT;
			} ewse {
				*vaw = st->singwe_ended_adc_vaw;
				wet = IIO_VAW_INT;
			}
			bweak;
		case IIO_ACCEW:
			*vaw = st->accew_vaw;
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_STEPS:
			*vaw = st->steps;
			wet = IIO_VAW_INT;
			bweak;
		case IIO_ACTIVITY:
			switch (chan->channew2) {
			case IIO_MOD_WUNNING:
				*vaw = st->activity_wunning;
				wet = IIO_VAW_INT;
				bweak;
			case IIO_MOD_WAWKING:
				*vaw = st->activity_wawking;
				wet = IIO_VAW_INT;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		/* onwy singwe ended adc -> 7 */
		*vaw = 7;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			switch (chan->diffewentiaw) {
			case 0:
				/* onwy singwe ended adc -> 0.001333 */
				*vaw = 0;
				*vaw2 = 1333;
				wet = IIO_VAW_INT_PWUS_MICWO;
				bweak;
			case 1:
				/* aww diffewentiaw adc -> 0.000001344 */
				*vaw = 0;
				*vaw2 = 1344;
				wet = IIO_VAW_INT_PWUS_NANO;
			}
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		/* onwy the accewewation axis - wead fwom cache */
		*vaw = st->accew_cawibbias;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaw = st->accew_cawibscawe->vaw;
		*vaw2 = st->accew_cawibscawe->vaw2;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = 3;
		*vaw2 = 33;
		wet = IIO_VAW_INT_PWUS_NANO;
		bweak;
	case IIO_CHAN_INFO_ENABWE:
		switch (chan->type) {
		case IIO_STEPS:
			*vaw = st->steps_enabwed;
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_CAWIBHEIGHT:
		switch (chan->type) {
		case IIO_STEPS:
			*vaw = st->height;
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			bweak;
		}
		bweak;

	defauwt:
		bweak;
	}
	mutex_unwock(&st->wock);
	wetuwn wet;
}

/**
 * iio_dummy_wwite_waw() - data wwite function.
 * @indio_dev:	the stwuct iio_dev associated with this device instance
 * @chan:	the channew whose data is to be wwitten
 * @vaw:	fiwst ewement of vawue to set (typicawwy INT)
 * @vaw2:	second ewement of vawue to set (typicawwy MICWO)
 * @mask:	what we actuawwy want to wwite as pew the info_mask_*
 *		in iio_chan_spec.
 *
 * Note that aww waw wwites awe assumed IIO_VAW_INT and info mask ewements
 * awe assumed to be IIO_INT_PWUS_MICWO unwess the cawwback wwite_waw_get_fmt
 * in stwuct iio_info is pwovided by the dwivew.
 */
static int iio_dummy_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	int i;
	int wet = 0;
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->output == 0)
				wetuwn -EINVAW;

			/* Wocking not wequiwed as wwiting singwe vawue */
			mutex_wock(&st->wock);
			st->dac_vaw = vaw;
			mutex_unwock(&st->wock);
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_STEPS:
			mutex_wock(&st->wock);
			st->steps = vaw;
			mutex_unwock(&st->wock);
			wetuwn 0;
		case IIO_ACTIVITY:
			if (vaw < 0)
				vaw = 0;
			if (vaw > 100)
				vaw = 100;
			switch (chan->channew2) {
			case IIO_MOD_WUNNING:
				st->activity_wunning = vaw;
				wetuwn 0;
			case IIO_MOD_WAWKING:
				st->activity_wawking = vaw;
				wetuwn 0;
			defauwt:
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBSCAWE:
		mutex_wock(&st->wock);
		/* Compawe against tabwe - hawd matching hewe */
		fow (i = 0; i < AWWAY_SIZE(dummy_scawes); i++)
			if (vaw == dummy_scawes[i].vaw &&
			    vaw2 == dummy_scawes[i].vaw2)
				bweak;
		if (i == AWWAY_SIZE(dummy_scawes))
			wet = -EINVAW;
		ewse
			st->accew_cawibscawe = &dummy_scawes[i];
		mutex_unwock(&st->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_CAWIBBIAS:
		mutex_wock(&st->wock);
		st->accew_cawibbias = vaw;
		mutex_unwock(&st->wock);
		wetuwn 0;
	case IIO_CHAN_INFO_ENABWE:
		switch (chan->type) {
		case IIO_STEPS:
			mutex_wock(&st->wock);
			st->steps_enabwed = vaw;
			mutex_unwock(&st->wock);
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBHEIGHT:
		switch (chan->type) {
		case IIO_STEPS:
			st->height = vaw;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}

	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Device type specific infowmation.
 */
static const stwuct iio_info iio_dummy_info = {
	.wead_waw = &iio_dummy_wead_waw,
	.wwite_waw = &iio_dummy_wwite_waw,
#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS
	.wead_event_config = &iio_simpwe_dummy_wead_event_config,
	.wwite_event_config = &iio_simpwe_dummy_wwite_event_config,
	.wead_event_vawue = &iio_simpwe_dummy_wead_event_vawue,
	.wwite_event_vawue = &iio_simpwe_dummy_wwite_event_vawue,
#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS */
};

/**
 * iio_dummy_init_device() - device instance specific init
 * @indio_dev: the iio device stwuctuwe
 *
 * Most dwivews have one of these to set up defauwt vawues,
 * weset the device to known state etc.
 */
static int iio_dummy_init_device(stwuct iio_dev *indio_dev)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	st->dac_vaw = 0;
	st->singwe_ended_adc_vaw = 73;
	st->diffewentiaw_adc_vaw[0] = 33;
	st->diffewentiaw_adc_vaw[1] = -34;
	st->accew_vaw = 34;
	st->accew_cawibbias = -7;
	st->accew_cawibscawe = &dummy_scawes[0];
	st->steps = 47;
	st->activity_wunning = 98;
	st->activity_wawking = 4;

	wetuwn 0;
}

/**
 * iio_dummy_pwobe() - device instance pwobe
 * @name: name of this instance.
 *
 * Awguments awe bus type specific.
 * I2C: iio_dummy_pwobe(stwuct i2c_cwient *cwient,
 *                      const stwuct i2c_device_id *id)
 * SPI: iio_dummy_pwobe(stwuct spi_device *spi)
 */
static stwuct iio_sw_device *iio_dummy_pwobe(const chaw *name)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct iio_dummy_state *st;
	stwuct iio_sw_device *swd;
	stwuct device *pawent = NUWW;

	/*
	 * With hawdwawe: Set the pawent device.
	 * pawent = &spi->dev;
	 * pawent = &cwient->dev;
	 */

	swd = kzawwoc(sizeof(*swd), GFP_KEWNEW);
	if (!swd)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Awwocate an IIO device.
	 *
	 * This stwuctuwe contains aww genewic state
	 * infowmation about the device instance.
	 * It awso has a wegion (accessed by iio_pwiv()
	 * fow chip specific state infowmation.
	 */
	indio_dev = iio_device_awwoc(pawent, sizeof(*st));
	if (!indio_dev) {
		wet = -ENOMEM;
		goto ewwow_fwee_swd;
	}

	st = iio_pwiv(indio_dev);
	mutex_init(&st->wock);

	iio_dummy_init_device(indio_dev);

	 /*
	 * Make the iio_dev stwuct avaiwabwe to wemove function.
	 * Bus equivawents
	 * i2c_set_cwientdata(cwient, indio_dev);
	 * spi_set_dwvdata(spi, indio_dev);
	 */
	swd->device = indio_dev;

	/*
	 * Set the device name.
	 *
	 * This is typicawwy a pawt numbew and obtained fwom the moduwe
	 * id tabwe.
	 * e.g. fow i2c and spi:
	 *    indio_dev->name = id->name;
	 *    indio_dev->name = spi_get_device_id(spi)->name;
	 */
	indio_dev->name = kstwdup(name, GFP_KEWNEW);
	if (!indio_dev->name) {
		wet = -ENOMEM;
		goto ewwow_fwee_device;
	}

	/* Pwovide descwiption of avaiwabwe channews */
	indio_dev->channews = iio_dummy_channews;
	indio_dev->num_channews = AWWAY_SIZE(iio_dummy_channews);

	/*
	 * Pwovide device type specific intewface functions and
	 * constant data.
	 */
	indio_dev->info = &iio_dummy_info;

	/* Specify that device pwovides sysfs type intewfaces */
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = iio_simpwe_dummy_events_wegistew(indio_dev);
	if (wet < 0)
		goto ewwow_fwee_name;

	wet = iio_simpwe_dummy_configuwe_buffew(indio_dev);
	if (wet < 0)
		goto ewwow_unwegistew_events;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto ewwow_unconfiguwe_buffew;

	iio_swd_gwoup_init_type_name(swd, name, &iio_dummy_type);

	wetuwn swd;
ewwow_unconfiguwe_buffew:
	iio_simpwe_dummy_unconfiguwe_buffew(indio_dev);
ewwow_unwegistew_events:
	iio_simpwe_dummy_events_unwegistew(indio_dev);
ewwow_fwee_name:
	kfwee(indio_dev->name);
ewwow_fwee_device:
	iio_device_fwee(indio_dev);
ewwow_fwee_swd:
	kfwee(swd);
	wetuwn EWW_PTW(wet);
}

/**
 * iio_dummy_wemove() - device instance wemovaw function
 * @swd: pointew to softwawe IIO device abstwaction
 *
 * Pawametews fowwow those of iio_dummy_pwobe fow buses.
 */
static int iio_dummy_wemove(stwuct iio_sw_device *swd)
{
	/*
	 * Get a pointew to the device instance iio_dev stwuctuwe
	 * fwom the bus subsystem. E.g.
	 * stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	 * stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	 */
	stwuct iio_dev *indio_dev = swd->device;

	/* Unwegistew the device */
	iio_device_unwegistew(indio_dev);

	/* Device specific code to powew down etc */

	/* Buffewed captuwe wewated cweanup */
	iio_simpwe_dummy_unconfiguwe_buffew(indio_dev);

	iio_simpwe_dummy_events_unwegistew(indio_dev);

	/* Fwee aww stwuctuwes */
	kfwee(indio_dev->name);
	iio_device_fwee(indio_dev);

	wetuwn 0;
}

/*
 * moduwe_iio_sw_device_dwivew() -  device dwivew wegistwation
 *
 * Vawies depending on bus type of the device. As thewe is no device
 * hewe, caww pwobe diwectwy. Fow infowmation on device wegistwation
 * i2c:
 * Documentation/i2c/wwiting-cwients.wst
 * spi:
 * Documentation/spi/spi-summawy.wst
 */
static const stwuct iio_sw_device_ops iio_dummy_device_ops = {
	.pwobe = iio_dummy_pwobe,
	.wemove = iio_dummy_wemove,
};

static stwuct iio_sw_device_type iio_dummy_device = {
	.name = "dummy",
	.ownew = THIS_MODUWE,
	.ops = &iio_dummy_device_ops,
};

moduwe_iio_sw_device_dwivew(iio_dummy_device);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("IIO dummy dwivew");
MODUWE_WICENSE("GPW v2");
