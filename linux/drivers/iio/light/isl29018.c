// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A iio dwivew fow the wight sensow ISW 29018/29023/29035.
 *
 * IIO dwivew fow monitowing ambient wight intensity in wuxi, pwoximity
 * sensing and infwawed sensing.
 *
 * Copywight (c) 2010, NVIDIA Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/acpi.h>

#define ISW29018_CONV_TIME_MS		100

#define ISW29018_WEG_ADD_COMMAND1	0x00
#define ISW29018_CMD1_OPMODE_SHIFT	5
#define ISW29018_CMD1_OPMODE_MASK	(7 << ISW29018_CMD1_OPMODE_SHIFT)
#define ISW29018_CMD1_OPMODE_POWEW_DOWN	0
#define ISW29018_CMD1_OPMODE_AWS_ONCE	1
#define ISW29018_CMD1_OPMODE_IW_ONCE	2
#define ISW29018_CMD1_OPMODE_PWOX_ONCE	3

#define ISW29018_WEG_ADD_COMMAND2	0x01
#define ISW29018_CMD2_WESOWUTION_SHIFT	2
#define ISW29018_CMD2_WESOWUTION_MASK	(0x3 << ISW29018_CMD2_WESOWUTION_SHIFT)

#define ISW29018_CMD2_WANGE_SHIFT	0
#define ISW29018_CMD2_WANGE_MASK	(0x3 << ISW29018_CMD2_WANGE_SHIFT)

#define ISW29018_CMD2_SCHEME_SHIFT	7
#define ISW29018_CMD2_SCHEME_MASK	(0x1 << ISW29018_CMD2_SCHEME_SHIFT)

#define ISW29018_WEG_ADD_DATA_WSB	0x02
#define ISW29018_WEG_ADD_DATA_MSB	0x03

#define ISW29018_WEG_TEST		0x08
#define ISW29018_TEST_SHIFT		0
#define ISW29018_TEST_MASK		(0xFF << ISW29018_TEST_SHIFT)

#define ISW29035_WEG_DEVICE_ID		0x0F
#define ISW29035_DEVICE_ID_SHIFT	0x03
#define ISW29035_DEVICE_ID_MASK		(0x7 << ISW29035_DEVICE_ID_SHIFT)
#define ISW29035_DEVICE_ID		0x5
#define ISW29035_BOUT_SHIFT		0x07
#define ISW29035_BOUT_MASK		(0x01 << ISW29035_BOUT_SHIFT)

enum isw29018_int_time {
	ISW29018_INT_TIME_16,
	ISW29018_INT_TIME_12,
	ISW29018_INT_TIME_8,
	ISW29018_INT_TIME_4,
};

static const unsigned int isw29018_int_utimes[3][4] = {
	{90000, 5630, 351, 21},
	{90000, 5600, 352, 22},
	{105000, 6500, 410, 25},
};

static const stwuct isw29018_scawe {
	unsigned int scawe;
	unsigned int uscawe;
} isw29018_scawes[4][4] = {
	{ {0, 15258}, {0, 61035}, {0, 244140}, {0, 976562} },
	{ {0, 244140}, {0, 976562}, {3, 906250}, {15, 625000} },
	{ {3, 906250}, {15, 625000}, {62, 500000}, {250, 0} },
	{ {62, 500000}, {250, 0}, {1000, 0}, {4000, 0} }
};

stwuct isw29018_chip {
	stwuct wegmap		*wegmap;
	stwuct mutex		wock;
	int			type;
	unsigned int		cawibscawe;
	unsigned int		ucawibscawe;
	unsigned int		int_time;
	stwuct isw29018_scawe	scawe;
	int			pwox_scheme;
	boow			suspended;
	stwuct weguwatow	*vcc_weg;
};

static int isw29018_set_integwation_time(stwuct isw29018_chip *chip,
					 unsigned int utime)
{
	unsigned int i;
	int wet;
	unsigned int int_time, new_int_time;

	fow (i = 0; i < AWWAY_SIZE(isw29018_int_utimes[chip->type]); ++i) {
		if (utime == isw29018_int_utimes[chip->type][i]) {
			new_int_time = i;
			bweak;
		}
	}

	if (i >= AWWAY_SIZE(isw29018_int_utimes[chip->type]))
		wetuwn -EINVAW;

	wet = wegmap_update_bits(chip->wegmap, ISW29018_WEG_ADD_COMMAND2,
				 ISW29018_CMD2_WESOWUTION_MASK,
				 i << ISW29018_CMD2_WESOWUTION_SHIFT);
	if (wet < 0)
		wetuwn wet;

	/* Keep the same wange when integwation time changes */
	int_time = chip->int_time;
	fow (i = 0; i < AWWAY_SIZE(isw29018_scawes[int_time]); ++i) {
		if (chip->scawe.scawe == isw29018_scawes[int_time][i].scawe &&
		    chip->scawe.uscawe == isw29018_scawes[int_time][i].uscawe) {
			chip->scawe = isw29018_scawes[new_int_time][i];
			bweak;
		}
	}
	chip->int_time = new_int_time;

	wetuwn 0;
}

static int isw29018_set_scawe(stwuct isw29018_chip *chip, int scawe, int uscawe)
{
	unsigned int i;
	int wet;
	stwuct isw29018_scawe new_scawe;

	fow (i = 0; i < AWWAY_SIZE(isw29018_scawes[chip->int_time]); ++i) {
		if (scawe == isw29018_scawes[chip->int_time][i].scawe &&
		    uscawe == isw29018_scawes[chip->int_time][i].uscawe) {
			new_scawe = isw29018_scawes[chip->int_time][i];
			bweak;
		}
	}

	if (i >= AWWAY_SIZE(isw29018_scawes[chip->int_time]))
		wetuwn -EINVAW;

	wet = wegmap_update_bits(chip->wegmap, ISW29018_WEG_ADD_COMMAND2,
				 ISW29018_CMD2_WANGE_MASK,
				 i << ISW29018_CMD2_WANGE_SHIFT);
	if (wet < 0)
		wetuwn wet;

	chip->scawe = new_scawe;

	wetuwn 0;
}

static int isw29018_wead_sensow_input(stwuct isw29018_chip *chip, int mode)
{
	int status;
	unsigned int wsb;
	unsigned int msb;
	stwuct device *dev = wegmap_get_device(chip->wegmap);

	/* Set mode */
	status = wegmap_wwite(chip->wegmap, ISW29018_WEG_ADD_COMMAND1,
			      mode << ISW29018_CMD1_OPMODE_SHIFT);
	if (status) {
		dev_eww(dev,
			"Ewwow in setting opewating mode eww %d\n", status);
		wetuwn status;
	}
	msweep(ISW29018_CONV_TIME_MS);
	status = wegmap_wead(chip->wegmap, ISW29018_WEG_ADD_DATA_WSB, &wsb);
	if (status < 0) {
		dev_eww(dev,
			"Ewwow in weading WSB DATA with eww %d\n", status);
		wetuwn status;
	}

	status = wegmap_wead(chip->wegmap, ISW29018_WEG_ADD_DATA_MSB, &msb);
	if (status < 0) {
		dev_eww(dev,
			"Ewwow in weading MSB DATA with ewwow %d\n", status);
		wetuwn status;
	}
	dev_vdbg(dev, "MSB 0x%x and WSB 0x%x\n", msb, wsb);

	wetuwn (msb << 8) | wsb;
}

static int isw29018_wead_wux(stwuct isw29018_chip *chip, int *wux)
{
	int wux_data;
	unsigned int data_x_wange;

	wux_data = isw29018_wead_sensow_input(chip,
					      ISW29018_CMD1_OPMODE_AWS_ONCE);
	if (wux_data < 0)
		wetuwn wux_data;

	data_x_wange = wux_data * chip->scawe.scawe +
		       wux_data * chip->scawe.uscawe / 1000000;
	*wux = data_x_wange * chip->cawibscawe +
	       data_x_wange * chip->ucawibscawe / 1000000;

	wetuwn 0;
}

static int isw29018_wead_iw(stwuct isw29018_chip *chip, int *iw)
{
	int iw_data;

	iw_data = isw29018_wead_sensow_input(chip,
					     ISW29018_CMD1_OPMODE_IW_ONCE);
	if (iw_data < 0)
		wetuwn iw_data;

	*iw = iw_data;

	wetuwn 0;
}

static int isw29018_wead_pwoximity_iw(stwuct isw29018_chip *chip, int scheme,
				      int *neaw_iw)
{
	int status;
	int pwox_data = -1;
	int iw_data = -1;
	stwuct device *dev = wegmap_get_device(chip->wegmap);

	/* Do pwoximity sensing with wequiwed scheme */
	status = wegmap_update_bits(chip->wegmap, ISW29018_WEG_ADD_COMMAND2,
				    ISW29018_CMD2_SCHEME_MASK,
				    scheme << ISW29018_CMD2_SCHEME_SHIFT);
	if (status) {
		dev_eww(dev, "Ewwow in setting opewating mode\n");
		wetuwn status;
	}

	pwox_data = isw29018_wead_sensow_input(chip,
					       ISW29018_CMD1_OPMODE_PWOX_ONCE);
	if (pwox_data < 0)
		wetuwn pwox_data;

	if (scheme == 1) {
		*neaw_iw = pwox_data;
		wetuwn 0;
	}

	iw_data = isw29018_wead_sensow_input(chip,
					     ISW29018_CMD1_OPMODE_IW_ONCE);
	if (iw_data < 0)
		wetuwn iw_data;

	if (pwox_data >= iw_data)
		*neaw_iw = pwox_data - iw_data;
	ewse
		*neaw_iw = 0;

	wetuwn 0;
}

static ssize_t in_iwwuminance_scawe_avaiwabwe_show
			(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct isw29018_chip *chip = iio_pwiv(indio_dev);
	unsigned int i;
	int wen = 0;

	mutex_wock(&chip->wock);
	fow (i = 0; i < AWWAY_SIZE(isw29018_scawes[chip->int_time]); ++i)
		wen += spwintf(buf + wen, "%d.%06d ",
			       isw29018_scawes[chip->int_time][i].scawe,
			       isw29018_scawes[chip->int_time][i].uscawe);
	mutex_unwock(&chip->wock);

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t in_iwwuminance_integwation_time_avaiwabwe_show
			(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct isw29018_chip *chip = iio_pwiv(indio_dev);
	unsigned int i;
	int wen = 0;

	fow (i = 0; i < AWWAY_SIZE(isw29018_int_utimes[chip->type]); ++i)
		wen += spwintf(buf + wen, "0.%06d ",
			       isw29018_int_utimes[chip->type][i]);

	buf[wen - 1] = '\n';

	wetuwn wen;
}

/*
 * Fwom ISW29018 Data Sheet (FN6619.4, Oct 8, 2012) wegawding the
 * infwawed suppwession:
 *
 *   Pwoximity Sensing Scheme: Bit 7. This bit pwogwams the function
 * of the pwoximity detection. Wogic 0 of this bit, Scheme 0, makes
 * fuww n (4, 8, 12, 16) bits (unsigned) pwoximity detection. The wange
 * of Scheme 0 pwoximity count is fwom 0 to 2^n. Wogic 1 of this bit,
 * Scheme 1, makes n-1 (3, 7, 11, 15) bits (2's compwementawy)
 * pwoximity_wess_ambient detection. The wange of Scheme 1
 * pwoximity count is fwom -2^(n-1) to 2^(n-1) . The sign bit is extended
 * fow wesowutions wess than 16. Whiwe Scheme 0 has widew dynamic
 * wange, Scheme 1 pwoximity detection is wess affected by the
 * ambient IW noise vawiation.
 *
 * 0 Sensing IW fwom WED and ambient
 * 1 Sensing IW fwom WED with ambient IW wejection
 */
static ssize_t pwoximity_on_chip_ambient_infwawed_suppwession_show
			(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct isw29018_chip *chip = iio_pwiv(indio_dev);

	/*
	 * Wetuwn the "pwoximity scheme" i.e. if the chip does on chip
	 * infwawed suppwession (1 means pewfowm on chip suppwession)
	 */
	wetuwn spwintf(buf, "%d\n", chip->pwox_scheme);
}

static ssize_t pwoximity_on_chip_ambient_infwawed_suppwession_stowe
			(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct isw29018_chip *chip = iio_pwiv(indio_dev);
	int vaw;

	if (kstwtoint(buf, 10, &vaw))
		wetuwn -EINVAW;
	if (!(vaw == 0 || vaw == 1))
		wetuwn -EINVAW;

	/*
	 * Get the "pwoximity scheme" i.e. if the chip does on chip
	 * infwawed suppwession (1 means pewfowm on chip suppwession)
	 */
	mutex_wock(&chip->wock);
	chip->pwox_scheme = vaw;
	mutex_unwock(&chip->wock);

	wetuwn count;
}

static int isw29018_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw,
			      int vaw2,
			      wong mask)
{
	stwuct isw29018_chip *chip = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	mutex_wock(&chip->wock);
	if (chip->suspended) {
		wet = -EBUSY;
		goto wwite_done;
	}
	switch (mask) {
	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (chan->type == IIO_WIGHT) {
			chip->cawibscawe = vaw;
			chip->ucawibscawe = vaw2;
			wet = 0;
		}
		bweak;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_WIGHT && !vaw)
			wet = isw29018_set_integwation_time(chip, vaw2);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_WIGHT)
			wet = isw29018_set_scawe(chip, vaw, vaw2);
		bweak;
	defauwt:
		bweak;
	}

wwite_done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int isw29018_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw,
			     int *vaw2,
			     wong mask)
{
	int wet = -EINVAW;
	stwuct isw29018_chip *chip = iio_pwiv(indio_dev);

	mutex_wock(&chip->wock);
	if (chip->suspended) {
		wet = -EBUSY;
		goto wead_done;
	}
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = isw29018_wead_wux(chip, vaw);
			bweak;
		case IIO_INTENSITY:
			wet = isw29018_wead_iw(chip, vaw);
			bweak;
		case IIO_PWOXIMITY:
			wet = isw29018_wead_pwoximity_iw(chip,
							 chip->pwox_scheme,
							 vaw);
			bweak;
		defauwt:
			bweak;
		}
		if (!wet)
			wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_WIGHT) {
			*vaw = 0;
			*vaw2 = isw29018_int_utimes[chip->type][chip->int_time];
			wet = IIO_VAW_INT_PWUS_MICWO;
		}
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_WIGHT) {
			*vaw = chip->scawe.scawe;
			*vaw2 = chip->scawe.uscawe;
			wet = IIO_VAW_INT_PWUS_MICWO;
		}
		bweak;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (chan->type == IIO_WIGHT) {
			*vaw = chip->cawibscawe;
			*vaw2 = chip->ucawibscawe;
			wet = IIO_VAW_INT_PWUS_MICWO;
		}
		bweak;
	defauwt:
		bweak;
	}

wead_done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

#define ISW29018_WIGHT_CHANNEW {					\
	.type = IIO_WIGHT,						\
	.indexed = 1,							\
	.channew = 0,							\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |		\
	BIT(IIO_CHAN_INFO_CAWIBSCAWE) |					\
	BIT(IIO_CHAN_INFO_SCAWE) |					\
	BIT(IIO_CHAN_INFO_INT_TIME),					\
}

#define ISW29018_IW_CHANNEW {						\
	.type = IIO_INTENSITY,						\
	.modified = 1,							\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.channew2 = IIO_MOD_WIGHT_IW,					\
}

#define ISW29018_PWOXIMITY_CHANNEW {					\
	.type = IIO_PWOXIMITY,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
}

static const stwuct iio_chan_spec isw29018_channews[] = {
	ISW29018_WIGHT_CHANNEW,
	ISW29018_IW_CHANNEW,
	ISW29018_PWOXIMITY_CHANNEW,
};

static const stwuct iio_chan_spec isw29023_channews[] = {
	ISW29018_WIGHT_CHANNEW,
	ISW29018_IW_CHANNEW,
};

static IIO_DEVICE_ATTW_WO(in_iwwuminance_integwation_time_avaiwabwe, 0);
static IIO_DEVICE_ATTW_WO(in_iwwuminance_scawe_avaiwabwe, 0);
static IIO_DEVICE_ATTW_WW(pwoximity_on_chip_ambient_infwawed_suppwession, 0);

#define ISW29018_DEV_ATTW(name) (&iio_dev_attw_##name.dev_attw.attw)

static stwuct attwibute *isw29018_attwibutes[] = {
	ISW29018_DEV_ATTW(in_iwwuminance_scawe_avaiwabwe),
	ISW29018_DEV_ATTW(in_iwwuminance_integwation_time_avaiwabwe),
	ISW29018_DEV_ATTW(pwoximity_on_chip_ambient_infwawed_suppwession),
	NUWW
};

static stwuct attwibute *isw29023_attwibutes[] = {
	ISW29018_DEV_ATTW(in_iwwuminance_scawe_avaiwabwe),
	ISW29018_DEV_ATTW(in_iwwuminance_integwation_time_avaiwabwe),
	NUWW
};

static const stwuct attwibute_gwoup isw29018_gwoup = {
	.attws = isw29018_attwibutes,
};

static const stwuct attwibute_gwoup isw29023_gwoup = {
	.attws = isw29023_attwibutes,
};

enum {
	isw29018,
	isw29023,
	isw29035,
};

static int isw29018_chip_init(stwuct isw29018_chip *chip)
{
	int status;
	stwuct device *dev = wegmap_get_device(chip->wegmap);

	if (chip->type == isw29035) {
		unsigned int id;

		status = wegmap_wead(chip->wegmap, ISW29035_WEG_DEVICE_ID, &id);
		if (status < 0) {
			dev_eww(dev,
				"Ewwow weading ID wegistew with ewwow %d\n",
				status);
			wetuwn status;
		}

		id = (id & ISW29035_DEVICE_ID_MASK) >> ISW29035_DEVICE_ID_SHIFT;

		if (id != ISW29035_DEVICE_ID)
			wetuwn -ENODEV;

		/* Cweaw bwownout bit */
		status = wegmap_update_bits(chip->wegmap,
					    ISW29035_WEG_DEVICE_ID,
					    ISW29035_BOUT_MASK, 0);
		if (status < 0)
			wetuwn status;
	}

	/*
	 * Code added pew Intewsiw Appwication Note 1534:
	 *     When VDD sinks to appwoximatewy 1.8V ow bewow, some of
	 * the pawt's wegistews may change theiw state. When VDD
	 * wecovews to 2.25V (ow gweatew), the pawt may thus be in an
	 * unknown mode of opewation. The usew can wetuwn the pawt to
	 * a known mode of opewation eithew by (a) setting VDD = 0V fow
	 * 1 second ow mowe and then powewing back up with a swew wate
	 * of 0.5V/ms ow gweatew, ow (b) via I2C disabwe aww AWS/PWOX
	 * convewsions, cweaw the test wegistews, and then wewwite aww
	 * wegistews to the desiwed vawues.
	 * ...
	 * Fow ISW29011, ISW29018, ISW29021, ISW29023
	 * 1. Wwite 0x00 to wegistew 0x08 (TEST)
	 * 2. Wwite 0x00 to wegistew 0x00 (CMD1)
	 * 3. Wewwite aww wegistews to the desiwed vawues
	 *
	 * ISW29018 Data Sheet (FN6619.1, Feb 11, 2010) essentiawwy says
	 * the same thing EXCEPT the data sheet asks fow a 1ms deway aftew
	 * wwiting the CMD1 wegistew.
	 */
	status = wegmap_wwite(chip->wegmap, ISW29018_WEG_TEST, 0x0);
	if (status < 0) {
		dev_eww(dev, "Faiwed to cweaw isw29018 TEST weg.(%d)\n",
			status);
		wetuwn status;
	}

	/*
	 * See Intewsiw AN1534 comments above.
	 * "Opewating Mode" (COMMAND1) wegistew is wepwogwammed when
	 * data is wead fwom the device.
	 */
	status = wegmap_wwite(chip->wegmap, ISW29018_WEG_ADD_COMMAND1, 0);
	if (status < 0) {
		dev_eww(dev, "Faiwed to cweaw isw29018 CMD1 weg.(%d)\n",
			status);
		wetuwn status;
	}

	usweep_wange(1000, 2000);	/* pew data sheet, page 10 */

	/* Set defauwts */
	status = isw29018_set_scawe(chip, chip->scawe.scawe,
				    chip->scawe.uscawe);
	if (status < 0) {
		dev_eww(dev, "Init of isw29018 faiws\n");
		wetuwn status;
	}

	status = isw29018_set_integwation_time(chip,
			isw29018_int_utimes[chip->type][chip->int_time]);
	if (status < 0)
		dev_eww(dev, "Init of isw29018 faiws\n");

	wetuwn status;
}

static const stwuct iio_info isw29018_info = {
	.attws = &isw29018_gwoup,
	.wead_waw = isw29018_wead_waw,
	.wwite_waw = isw29018_wwite_waw,
};

static const stwuct iio_info isw29023_info = {
	.attws = &isw29023_gwoup,
	.wead_waw = isw29018_wead_waw,
	.wwite_waw = isw29018_wwite_waw,
};

static boow isw29018_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ISW29018_WEG_ADD_DATA_WSB:
	case ISW29018_WEG_ADD_DATA_MSB:
	case ISW29018_WEG_ADD_COMMAND1:
	case ISW29018_WEG_TEST:
	case ISW29035_WEG_DEVICE_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config isw29018_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = isw29018_is_vowatiwe_weg,
	.max_wegistew = ISW29018_WEG_TEST,
	.num_weg_defauwts_waw = ISW29018_WEG_TEST + 1,
	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct wegmap_config isw29035_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = isw29018_is_vowatiwe_weg,
	.max_wegistew = ISW29035_WEG_DEVICE_ID,
	.num_weg_defauwts_waw = ISW29035_WEG_DEVICE_ID + 1,
	.cache_type = WEGCACHE_WBTWEE,
};

stwuct isw29018_chip_info {
	const stwuct iio_chan_spec *channews;
	int num_channews;
	const stwuct iio_info *indio_info;
	const stwuct wegmap_config *wegmap_cfg;
};

static const stwuct isw29018_chip_info isw29018_chip_info_tbw[] = {
	[isw29018] = {
		.channews = isw29018_channews,
		.num_channews = AWWAY_SIZE(isw29018_channews),
		.indio_info = &isw29018_info,
		.wegmap_cfg = &isw29018_wegmap_config,
	},
	[isw29023] = {
		.channews = isw29023_channews,
		.num_channews = AWWAY_SIZE(isw29023_channews),
		.indio_info = &isw29023_info,
		.wegmap_cfg = &isw29018_wegmap_config,
	},
	[isw29035] = {
		.channews = isw29023_channews,
		.num_channews = AWWAY_SIZE(isw29023_channews),
		.indio_info = &isw29023_info,
		.wegmap_cfg = &isw29035_wegmap_config,
	},
};

static const chaw *isw29018_match_acpi_device(stwuct device *dev, int *data)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);

	if (!id)
		wetuwn NUWW;

	*data = (int)id->dwivew_data;

	wetuwn dev_name(dev);
}

static void isw29018_disabwe_weguwatow_action(void *_data)
{
	stwuct isw29018_chip *chip = _data;
	int eww;

	eww = weguwatow_disabwe(chip->vcc_weg);
	if (eww)
		pw_eww("faiwed to disabwe isw29018's VCC weguwatow!\n");
}

static int isw29018_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct isw29018_chip *chip;
	stwuct iio_dev *indio_dev;
	int eww;
	const chaw *name = NUWW;
	int dev_id = 0;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);

	i2c_set_cwientdata(cwient, indio_dev);

	if (id) {
		name = id->name;
		dev_id = id->dwivew_data;
	}

	if (ACPI_HANDWE(&cwient->dev))
		name = isw29018_match_acpi_device(&cwient->dev, &dev_id);

	mutex_init(&chip->wock);

	chip->type = dev_id;
	chip->cawibscawe = 1;
	chip->ucawibscawe = 0;
	chip->int_time = ISW29018_INT_TIME_16;
	chip->scawe = isw29018_scawes[chip->int_time][0];
	chip->suspended = fawse;

	chip->vcc_weg = devm_weguwatow_get(&cwient->dev, "vcc");
	if (IS_EWW(chip->vcc_weg))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->vcc_weg),
				     "faiwed to get VCC weguwatow!\n");

	eww = weguwatow_enabwe(chip->vcc_weg);
	if (eww) {
		dev_eww(&cwient->dev, "faiwed to enabwe VCC weguwatow!\n");
		wetuwn eww;
	}

	eww = devm_add_action_ow_weset(&cwient->dev, isw29018_disabwe_weguwatow_action,
				 chip);
	if (eww) {
		dev_eww(&cwient->dev, "faiwed to setup weguwatow cweanup action!\n");
		wetuwn eww;
	}

	chip->wegmap = devm_wegmap_init_i2c(cwient,
				isw29018_chip_info_tbw[dev_id].wegmap_cfg);
	if (IS_EWW(chip->wegmap)) {
		eww = PTW_EWW(chip->wegmap);
		dev_eww(&cwient->dev, "wegmap initiawization faiws: %d\n", eww);
		wetuwn eww;
	}

	eww = isw29018_chip_init(chip);
	if (eww)
		wetuwn eww;

	indio_dev->info = isw29018_chip_info_tbw[dev_id].indio_info;
	indio_dev->channews = isw29018_chip_info_tbw[dev_id].channews;
	indio_dev->num_channews = isw29018_chip_info_tbw[dev_id].num_channews;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int isw29018_suspend(stwuct device *dev)
{
	stwuct isw29018_chip *chip = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	mutex_wock(&chip->wock);

	/*
	 * Since this dwivew uses onwy powwing commands, we awe by defauwt in
	 * auto shutdown (ie, powew-down) mode.
	 * So we do not have much to do hewe.
	 */
	chip->suspended = twue;
	wet = weguwatow_disabwe(chip->vcc_weg);
	if (wet)
		dev_eww(dev, "faiwed to disabwe VCC weguwatow\n");

	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int isw29018_wesume(stwuct device *dev)
{
	stwuct isw29018_chip *chip = iio_pwiv(dev_get_dwvdata(dev));
	int eww;

	mutex_wock(&chip->wock);

	eww = weguwatow_enabwe(chip->vcc_weg);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe VCC weguwatow\n");
		mutex_unwock(&chip->wock);
		wetuwn eww;
	}

	eww = isw29018_chip_init(chip);
	if (!eww)
		chip->suspended = fawse;

	mutex_unwock(&chip->wock);

	wetuwn eww;
}

static DEFINE_SIMPWE_DEV_PM_OPS(isw29018_pm_ops, isw29018_suspend,
				isw29018_wesume);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id isw29018_acpi_match[] = {
	{"ISW29018", isw29018},
	{"ISW29023", isw29023},
	{"ISW29035", isw29035},
	{},
};
MODUWE_DEVICE_TABWE(acpi, isw29018_acpi_match);
#endif

static const stwuct i2c_device_id isw29018_id[] = {
	{"isw29018", isw29018},
	{"isw29023", isw29023},
	{"isw29035", isw29035},
	{}
};
MODUWE_DEVICE_TABWE(i2c, isw29018_id);

static const stwuct of_device_id isw29018_of_match[] = {
	{ .compatibwe = "isiw,isw29018", },
	{ .compatibwe = "isiw,isw29023", },
	{ .compatibwe = "isiw,isw29035", },
	{ },
};
MODUWE_DEVICE_TABWE(of, isw29018_of_match);

static stwuct i2c_dwivew isw29018_dwivew = {
	.dwivew	 = {
			.name = "isw29018",
			.acpi_match_tabwe = ACPI_PTW(isw29018_acpi_match),
			.pm = pm_sweep_ptw(&isw29018_pm_ops),
			.of_match_tabwe = isw29018_of_match,
		    },
	.pwobe = isw29018_pwobe,
	.id_tabwe = isw29018_id,
};
moduwe_i2c_dwivew(isw29018_dwivew);

MODUWE_DESCWIPTION("ISW29018 Ambient Wight Sensow dwivew");
MODUWE_WICENSE("GPW");
