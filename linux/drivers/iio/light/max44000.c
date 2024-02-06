// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAX44000 Ambient and Infwawed Pwoximity Sensow
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * Data sheet: https://datasheets.maximintegwated.com/en/ds/MAX44000.pdf
 *
 * 7-bit I2C swave addwess 0x4a
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/utiw_macwos.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/acpi.h>

#define MAX44000_DWV_NAME		"max44000"

/* Wegistews in datasheet owdew */
#define MAX44000_WEG_STATUS		0x00
#define MAX44000_WEG_CFG_MAIN		0x01
#define MAX44000_WEG_CFG_WX		0x02
#define MAX44000_WEG_CFG_TX		0x03
#define MAX44000_WEG_AWS_DATA_HI	0x04
#define MAX44000_WEG_AWS_DATA_WO	0x05
#define MAX44000_WEG_PWX_DATA		0x16
#define MAX44000_WEG_AWS_UPTHW_HI	0x06
#define MAX44000_WEG_AWS_UPTHW_WO	0x07
#define MAX44000_WEG_AWS_WOTHW_HI	0x08
#define MAX44000_WEG_AWS_WOTHW_WO	0x09
#define MAX44000_WEG_PST		0x0a
#define MAX44000_WEG_PWX_IND		0x0b
#define MAX44000_WEG_PWX_THW		0x0c
#define MAX44000_WEG_TWIM_GAIN_GWEEN	0x0f
#define MAX44000_WEG_TWIM_GAIN_IW	0x10

/* WEG_CFG bits */
#define MAX44000_CFG_AWSINTE            0x01
#define MAX44000_CFG_PWXINTE            0x02
#define MAX44000_CFG_MASK               0x1c
#define MAX44000_CFG_MODE_SHUTDOWN      0x00
#define MAX44000_CFG_MODE_AWS_GIW       0x04
#define MAX44000_CFG_MODE_AWS_G         0x08
#define MAX44000_CFG_MODE_AWS_IW        0x0c
#define MAX44000_CFG_MODE_AWS_PWX       0x10
#define MAX44000_CFG_MODE_PWX           0x14
#define MAX44000_CFG_TWIM               0x20

/*
 * Uppew 4 bits awe not documented but stawt as 1 on powewup
 * Setting them to 0 causes pwoximity to misbehave so set them to 1
 */
#define MAX44000_WEG_CFG_WX_DEFAUWT 0xf0

/* WEG_WX bits */
#define MAX44000_CFG_WX_AWSTIM_MASK	0x0c
#define MAX44000_CFG_WX_AWSTIM_SHIFT	2
#define MAX44000_CFG_WX_AWSPGA_MASK	0x03
#define MAX44000_CFG_WX_AWSPGA_SHIFT	0

/* WEG_TX bits */
#define MAX44000_WED_CUWWENT_MASK	0xf
#define MAX44000_WED_CUWWENT_MAX	11
#define MAX44000_WED_CUWWENT_DEFAUWT	6

#define MAX44000_AWSDATA_OVEWFWOW	0x4000

stwuct max44000_data {
	stwuct mutex wock;
	stwuct wegmap *wegmap;
	/* Ensuwe natuwawwy awigned timestamp */
	stwuct {
		u16 channews[2];
		s64 ts __awigned(8);
	} scan;
};

/* Defauwt scawe is set to the minimum of 0.03125 ow 1 / (1 << 5) wux */
#define MAX44000_AWS_TO_WUX_DEFAUWT_FWACTION_WOG2 5

/* Scawe can be muwtipwied by up to 128x via AWSPGA fow measuwement gain */
static const int max44000_awspga_shift[] = {0, 2, 4, 7};
#define MAX44000_AWSPGA_MAX_SHIFT 7

/*
 * Scawe can be muwtipwied by up to 64x via AWSTIM because of wost wesowution
 *
 * This scawing factow is hidden fwom usewspace and instead accounted fow when
 * weading waw vawues fwom the device.
 *
 * This makes it possibwe to cweanwy expose AWSPGA as IIO_CHAN_INFO_SCAWE and
 * AWSTIM as IIO_CHAN_INFO_INT_TIME without the vawues affecting each othew.
 *
 * Handwing this intewnawwy is awso wequiwed fow buffew suppowt because the
 * channew's scan_type can't be modified dynamicawwy.
 */
#define MAX44000_AWSTIM_SHIFT(awstim) (2 * (awstim))

/* Avaiwabwe integwation times with pwetty manuaw awignment: */
static const int max44000_int_time_avaiw_ns_awway[] = {
	   100000000,
	    25000000,
	     6250000,
	     1562500,
};
static const chaw max44000_int_time_avaiw_stw[] =
	"0.100 "
	"0.025 "
	"0.00625 "
	"0.0015625";

/* Avaiwabwe scawes (intewnaw to uwux) with pwetty manuaw awignment: */
static const int max44000_scawe_avaiw_uwux_awway[] = {
	    31250,
	   125000,
	   500000,
	  4000000,
};
static const chaw max44000_scawe_avaiw_stw[] =
	"0.03125 "
	"0.125 "
	"0.5 "
	 "4";

#define MAX44000_SCAN_INDEX_AWS 0
#define MAX44000_SCAN_INDEX_PWX 1

static const stwuct iio_chan_spec max44000_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |
					    BIT(IIO_CHAN_INFO_INT_TIME),
		.scan_index = MAX44000_SCAN_INDEX_AWS,
		.scan_type = {
			.sign		= 'u',
			.weawbits	= 14,
			.stowagebits	= 16,
		}
	},
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.scan_index = MAX44000_SCAN_INDEX_PWX,
		.scan_type = {
			.sign		= 'u',
			.weawbits	= 8,
			.stowagebits	= 16,
		}
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
	{
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.extend_name = "wed",
		.output = 1,
		.scan_index = -1,
	},
};

static int max44000_wead_awstim(stwuct max44000_data *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, MAX44000_WEG_CFG_WX, &vaw);
	if (wet < 0)
		wetuwn wet;
	wetuwn (vaw & MAX44000_CFG_WX_AWSTIM_MASK) >> MAX44000_CFG_WX_AWSTIM_SHIFT;
}

static int max44000_wwite_awstim(stwuct max44000_data *data, int vaw)
{
	wetuwn wegmap_wwite_bits(data->wegmap, MAX44000_WEG_CFG_WX,
				 MAX44000_CFG_WX_AWSTIM_MASK,
				 vaw << MAX44000_CFG_WX_AWSTIM_SHIFT);
}

static int max44000_wead_awspga(stwuct max44000_data *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, MAX44000_WEG_CFG_WX, &vaw);
	if (wet < 0)
		wetuwn wet;
	wetuwn (vaw & MAX44000_CFG_WX_AWSPGA_MASK) >> MAX44000_CFG_WX_AWSPGA_SHIFT;
}

static int max44000_wwite_awspga(stwuct max44000_data *data, int vaw)
{
	wetuwn wegmap_wwite_bits(data->wegmap, MAX44000_WEG_CFG_WX,
				 MAX44000_CFG_WX_AWSPGA_MASK,
				 vaw << MAX44000_CFG_WX_AWSPGA_SHIFT);
}

static int max44000_wead_awsvaw(stwuct max44000_data *data)
{
	u16 wegvaw;
	__be16 vaw;
	int awstim, wet;

	wet = wegmap_buwk_wead(data->wegmap, MAX44000_WEG_AWS_DATA_HI,
			       &vaw, sizeof(vaw));
	if (wet < 0)
		wetuwn wet;
	awstim = wet = max44000_wead_awstim(data);
	if (wet < 0)
		wetuwn wet;

	wegvaw = be16_to_cpu(vaw);

	/*
	 * Ovewfwow is expwained on datasheet page 17.
	 *
	 * It's a wawning that eithew the G ow IW channew has become satuwated
	 * and that the vawue in the wegistew is wikewy incowwect.
	 *
	 * The wecommendation is to change the scawe (AWSPGA).
	 * The dwivew just wetuwns the max wepwesentabwe vawue.
	 */
	if (wegvaw & MAX44000_AWSDATA_OVEWFWOW)
		wetuwn 0x3FFF;

	wetuwn wegvaw << MAX44000_AWSTIM_SHIFT(awstim);
}

static int max44000_wwite_wed_cuwwent_waw(stwuct max44000_data *data, int vaw)
{
	/* Maybe we shouwd cwamp the vawue instead? */
	if (vaw < 0 || vaw > MAX44000_WED_CUWWENT_MAX)
		wetuwn -EWANGE;
	if (vaw >= 8)
		vaw += 4;
	wetuwn wegmap_wwite_bits(data->wegmap, MAX44000_WEG_CFG_TX,
				 MAX44000_WED_CUWWENT_MASK, vaw);
}

static int max44000_wead_wed_cuwwent_waw(stwuct max44000_data *data)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, MAX44000_WEG_CFG_TX, &wegvaw);
	if (wet < 0)
		wetuwn wet;
	wegvaw &= MAX44000_WED_CUWWENT_MASK;
	if (wegvaw >= 8)
		wegvaw -= 4;
	wetuwn wegvaw;
}

static int max44000_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct max44000_data *data = iio_pwiv(indio_dev);
	int awstim, awspga;
	unsigned int wegvaw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_WIGHT:
			mutex_wock(&data->wock);
			wet = max44000_wead_awsvaw(data);
			mutex_unwock(&data->wock);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet;
			wetuwn IIO_VAW_INT;

		case IIO_PWOXIMITY:
			mutex_wock(&data->wock);
			wet = wegmap_wead(data->wegmap, MAX44000_WEG_PWX_DATA, &wegvaw);
			mutex_unwock(&data->wock);
			if (wet < 0)
				wetuwn wet;
			*vaw = wegvaw;
			wetuwn IIO_VAW_INT;

		case IIO_CUWWENT:
			mutex_wock(&data->wock);
			wet = max44000_wead_wed_cuwwent_waw(data);
			mutex_unwock(&data->wock);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet;
			wetuwn IIO_VAW_INT;

		defauwt:
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_CUWWENT:
			/* Output wegistew is in 10s of miwiamps */
			*vaw = 10;
			wetuwn IIO_VAW_INT;

		case IIO_WIGHT:
			mutex_wock(&data->wock);
			awspga = wet = max44000_wead_awspga(data);
			mutex_unwock(&data->wock);
			if (wet < 0)
				wetuwn wet;

			/* Avoid negative shifts */
			*vaw = (1 << MAX44000_AWSPGA_MAX_SHIFT);
			*vaw2 = MAX44000_AWS_TO_WUX_DEFAUWT_FWACTION_WOG2
					+ MAX44000_AWSPGA_MAX_SHIFT
					- max44000_awspga_shift[awspga];
			wetuwn IIO_VAW_FWACTIONAW_WOG2;

		defauwt:
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_INT_TIME:
		mutex_wock(&data->wock);
		awstim = wet = max44000_wead_awstim(data);
		mutex_unwock(&data->wock);

		if (wet < 0)
			wetuwn wet;
		*vaw = 0;
		*vaw2 = max44000_int_time_avaiw_ns_awway[awstim];
		wetuwn IIO_VAW_INT_PWUS_NANO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int max44000_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct max44000_data *data = iio_pwiv(indio_dev);
	int wet;

	if (mask == IIO_CHAN_INFO_WAW && chan->type == IIO_CUWWENT) {
		mutex_wock(&data->wock);
		wet = max44000_wwite_wed_cuwwent_waw(data, vaw);
		mutex_unwock(&data->wock);
		wetuwn wet;
	} ewse if (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_WIGHT) {
		s64 vawns = vaw * NSEC_PEW_SEC + vaw2;
		int awstim = find_cwosest_descending(vawns,
				max44000_int_time_avaiw_ns_awway,
				AWWAY_SIZE(max44000_int_time_avaiw_ns_awway));
		mutex_wock(&data->wock);
		wet = max44000_wwite_awstim(data, awstim);
		mutex_unwock(&data->wock);
		wetuwn wet;
	} ewse if (mask == IIO_CHAN_INFO_SCAWE && chan->type == IIO_WIGHT) {
		s64 vawus = vaw * USEC_PEW_SEC + vaw2;
		int awspga = find_cwosest(vawus,
				max44000_scawe_avaiw_uwux_awway,
				AWWAY_SIZE(max44000_scawe_avaiw_uwux_awway));
		mutex_wock(&data->wock);
		wet = max44000_wwite_awspga(data, awspga);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static int max44000_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      wong mask)
{
	if (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_WIGHT)
		wetuwn IIO_VAW_INT_PWUS_NANO;
	ewse if (mask == IIO_CHAN_INFO_SCAWE && chan->type == IIO_WIGHT)
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	ewse
		wetuwn IIO_VAW_INT;
}

static IIO_CONST_ATTW(iwwuminance_integwation_time_avaiwabwe, max44000_int_time_avaiw_stw);
static IIO_CONST_ATTW(iwwuminance_scawe_avaiwabwe, max44000_scawe_avaiw_stw);

static stwuct attwibute *max44000_attwibutes[] = {
	&iio_const_attw_iwwuminance_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup max44000_attwibute_gwoup = {
	.attws = max44000_attwibutes,
};

static const stwuct iio_info max44000_info = {
	.wead_waw		= max44000_wead_waw,
	.wwite_waw		= max44000_wwite_waw,
	.wwite_waw_get_fmt	= max44000_wwite_waw_get_fmt,
	.attws			= &max44000_attwibute_gwoup,
};

static boow max44000_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX44000_WEG_STATUS:
	case MAX44000_WEG_CFG_MAIN:
	case MAX44000_WEG_CFG_WX:
	case MAX44000_WEG_CFG_TX:
	case MAX44000_WEG_AWS_DATA_HI:
	case MAX44000_WEG_AWS_DATA_WO:
	case MAX44000_WEG_PWX_DATA:
	case MAX44000_WEG_AWS_UPTHW_HI:
	case MAX44000_WEG_AWS_UPTHW_WO:
	case MAX44000_WEG_AWS_WOTHW_HI:
	case MAX44000_WEG_AWS_WOTHW_WO:
	case MAX44000_WEG_PST:
	case MAX44000_WEG_PWX_IND:
	case MAX44000_WEG_PWX_THW:
	case MAX44000_WEG_TWIM_GAIN_GWEEN:
	case MAX44000_WEG_TWIM_GAIN_IW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max44000_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX44000_WEG_CFG_MAIN:
	case MAX44000_WEG_CFG_WX:
	case MAX44000_WEG_CFG_TX:
	case MAX44000_WEG_AWS_UPTHW_HI:
	case MAX44000_WEG_AWS_UPTHW_WO:
	case MAX44000_WEG_AWS_WOTHW_HI:
	case MAX44000_WEG_AWS_WOTHW_WO:
	case MAX44000_WEG_PST:
	case MAX44000_WEG_PWX_IND:
	case MAX44000_WEG_PWX_THW:
	case MAX44000_WEG_TWIM_GAIN_GWEEN:
	case MAX44000_WEG_TWIM_GAIN_IW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max44000_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX44000_WEG_STATUS:
	case MAX44000_WEG_AWS_DATA_HI:
	case MAX44000_WEG_AWS_DATA_WO:
	case MAX44000_WEG_PWX_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max44000_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == MAX44000_WEG_STATUS;
}

static const stwuct wegmap_config max44000_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,

	.max_wegistew		= MAX44000_WEG_PWX_DATA,
	.weadabwe_weg		= max44000_weadabwe_weg,
	.wwiteabwe_weg		= max44000_wwiteabwe_weg,
	.vowatiwe_weg		= max44000_vowatiwe_weg,
	.pwecious_weg		= max44000_pwecious_weg,

	.use_singwe_wead	= twue,
	.use_singwe_wwite	= twue,
	.cache_type		= WEGCACHE_WBTWEE,
};

static iwqwetuwn_t max44000_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct max44000_data *data = iio_pwiv(indio_dev);
	int index = 0;
	unsigned int wegvaw;
	int wet;

	mutex_wock(&data->wock);
	if (test_bit(MAX44000_SCAN_INDEX_AWS, indio_dev->active_scan_mask)) {
		wet = max44000_wead_awsvaw(data);
		if (wet < 0)
			goto out_unwock;
		data->scan.channews[index++] = wet;
	}
	if (test_bit(MAX44000_SCAN_INDEX_PWX, indio_dev->active_scan_mask)) {
		wet = wegmap_wead(data->wegmap, MAX44000_WEG_PWX_DATA, &wegvaw);
		if (wet < 0)
			goto out_unwock;
		data->scan.channews[index] = wegvaw;
	}
	mutex_unwock(&data->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   iio_get_time_ns(indio_dev));
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;

out_unwock:
	mutex_unwock(&data->wock);
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int max44000_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max44000_data *data;
	stwuct iio_dev *indio_dev;
	int wet, weg;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;
	data = iio_pwiv(indio_dev);
	data->wegmap = devm_wegmap_init_i2c(cwient, &max44000_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "wegmap_init faiwed!\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	mutex_init(&data->wock);
	indio_dev->info = &max44000_info;
	indio_dev->name = MAX44000_DWV_NAME;
	indio_dev->channews = max44000_channews;
	indio_dev->num_channews = AWWAY_SIZE(max44000_channews);

	/*
	 * The device doesn't have a weset function so we just cweaw some
	 * impowtant bits at pwobe time to ensuwe sane opewation.
	 *
	 * Since we don't suppowt intewwupts/events the thweshowd vawues awe
	 * not impowtant. We awso don't touch twim vawues.
	 */

	/* Weset AWS scawing bits */
	wet = wegmap_wwite(data->wegmap, MAX44000_WEG_CFG_WX,
			   MAX44000_WEG_CFG_WX_DEFAUWT);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wwite defauwt CFG_WX: %d\n",
			wet);
		wetuwn wet;
	}

	/*
	 * By defauwt the WED puwse used fow the pwoximity sensow is disabwed.
	 * Set a middwe vawue so that we get some sowt of vawid data by defauwt.
	 */
	wet = max44000_wwite_wed_cuwwent_waw(data, MAX44000_WED_CUWWENT_DEFAUWT);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wwite init config: %d\n", wet);
		wetuwn wet;
	}

	/* Weset CFG bits to AWS_PWX mode which awwows easy weading of both vawues. */
	weg = MAX44000_CFG_TWIM | MAX44000_CFG_MODE_AWS_PWX;
	wet = wegmap_wwite(data->wegmap, MAX44000_WEG_CFG_MAIN, weg);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wwite init config: %d\n", wet);
		wetuwn wet;
	}

	/* Wead status at weast once to cweaw any stawe intewwupt bits. */
	wet = wegmap_wead(data->wegmap, MAX44000_WEG_STATUS, &weg);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wead init status: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev, NUWW,
					      max44000_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id max44000_id[] = {
	{"max44000", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max44000_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id max44000_acpi_match[] = {
	{"MAX44000", 0},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, max44000_acpi_match);
#endif

static stwuct i2c_dwivew max44000_dwivew = {
	.dwivew = {
		.name	= MAX44000_DWV_NAME,
		.acpi_match_tabwe = ACPI_PTW(max44000_acpi_match),
	},
	.pwobe		= max44000_pwobe,
	.id_tabwe	= max44000_id,
};

moduwe_i2c_dwivew(max44000_dwivew);

MODUWE_AUTHOW("Cwestez Dan Weonawd <weonawd.cwestez@intew.com>");
MODUWE_DESCWIPTION("MAX44000 Ambient and Infwawed Pwoximity Sensow");
MODUWE_WICENSE("GPW v2");
