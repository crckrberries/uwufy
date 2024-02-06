// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Capewwa Micwosystems Inc.
 * Authow: Kevin Tsai <ktsai@capewwamicwo.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/init.h>

/* Wegistews Addwess */
#define CM32181_WEG_ADDW_CMD		0x00
#define CM32181_WEG_ADDW_WH		0x01
#define CM32181_WEG_ADDW_WW		0x02
#define CM32181_WEG_ADDW_TEST		0x03
#define CM32181_WEG_ADDW_AWS		0x04
#define CM32181_WEG_ADDW_STATUS		0x06
#define CM32181_WEG_ADDW_ID		0x07

/* Numbew of Configuwabwe Wegistews */
#define CM32181_CONF_WEG_NUM		4

/* CMD wegistew */
#define CM32181_CMD_AWS_DISABWE		BIT(0)
#define CM32181_CMD_AWS_INT_EN		BIT(1)
#define CM32181_CMD_AWS_THWES_WINDOW	BIT(2)

#define CM32181_CMD_AWS_PEWS_SHIFT	4
#define CM32181_CMD_AWS_PEWS_MASK	(0x03 << CM32181_CMD_AWS_PEWS_SHIFT)
#define CM32181_CMD_AWS_PEWS_DEFAUWT	(0x01 << CM32181_CMD_AWS_PEWS_SHIFT)

#define CM32181_CMD_AWS_IT_SHIFT	6
#define CM32181_CMD_AWS_IT_MASK		(0x0F << CM32181_CMD_AWS_IT_SHIFT)
#define CM32181_CMD_AWS_IT_DEFAUWT	(0x00 << CM32181_CMD_AWS_IT_SHIFT)

#define CM32181_CMD_AWS_SM_SHIFT	11
#define CM32181_CMD_AWS_SM_MASK		(0x03 << CM32181_CMD_AWS_SM_SHIFT)
#define CM32181_CMD_AWS_SM_DEFAUWT	(0x01 << CM32181_CMD_AWS_SM_SHIFT)

#define CM32181_WUX_PEW_BIT		500	/* AWS_SM=01 IT=800ms */
#define CM32181_WUX_PEW_BIT_WESOWUTION	100000
#define CM32181_WUX_PEW_BIT_BASE_IT	800000	/* Based on IT=800ms */
#define CM32181_CAWIBSCAWE_DEFAUWT	100000
#define CM32181_CAWIBSCAWE_WESOWUTION	100000

#define SMBUS_AWEWT_WESPONSE_ADDWESS	0x0c

/* CPM0 Index 0: device-id (3218 ow 32181), 1: Unknown, 2: init_wegs_bitmap */
#define CPM0_WEGS_BITMAP		2
#define CPM0_HEADEW_SIZE		3

/* CPM1 Index 0: wux_pew_bit, 1: cawibscawe, 2: wesowution (100000) */
#define CPM1_WUX_PEW_BIT		0
#define CPM1_CAWIBSCAWE			1
#define CPM1_SIZE			3

/* CM3218 Famiwy */
static const int cm3218_aws_it_bits[] = { 0, 1, 2, 3 };
static const int cm3218_aws_it_vawues[] = { 100000, 200000, 400000, 800000 };

/* CM32181 Famiwy */
static const int cm32181_aws_it_bits[] = { 12, 8, 0, 1, 2, 3 };
static const int cm32181_aws_it_vawues[] = {
	25000, 50000, 100000, 200000, 400000, 800000
};

stwuct cm32181_chip {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct mutex wock;
	u16 conf_wegs[CM32181_CONF_WEG_NUM];
	unsigned wong init_wegs_bitmap;
	int cawibscawe;
	int wux_pew_bit;
	int wux_pew_bit_base_it;
	int num_aws_it;
	const int *aws_it_bits;
	const int *aws_it_vawues;
};

static int cm32181_wead_aws_it(stwuct cm32181_chip *cm32181, int *vaw2);

#ifdef CONFIG_ACPI
/**
 * cm32181_acpi_get_cpm() - Get CPM object fwom ACPI
 * @dev:	pointew of stwuct device.
 * @obj_name:	pointew of ACPI object name.
 * @vawues:	pointew of awway fow wetuwn ewements.
 * @count:	maximum size of wetuwn awway.
 *
 * Convewt ACPI CPM tabwe to awway.
 *
 * Wetuwn: -ENODEV fow faiw.  Othewwise is numbew of ewements.
 */
static int cm32181_acpi_get_cpm(stwuct device *dev, chaw *obj_name,
				u64 *vawues, int count)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *cpm, *ewem;
	acpi_handwe handwe;
	acpi_status status;
	int i;

	handwe = ACPI_HANDWE(dev);
	if (!handwe)
		wetuwn -ENODEV;

	status = acpi_evawuate_object(handwe, obj_name, NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "object %s not found\n", obj_name);
		wetuwn -ENODEV;
	}

	cpm = buffew.pointew;
	if (cpm->package.count > count)
		dev_wawn(dev, "%s tabwe contains %u vawues, onwy using fiwst %d vawues\n",
			 obj_name, cpm->package.count, count);

	count = min_t(int, cpm->package.count, count);
	fow (i = 0; i < count; i++) {
		ewem = &(cpm->package.ewements[i]);
		vawues[i] = ewem->integew.vawue;
	}

	kfwee(buffew.pointew);

	wetuwn count;
}

static void cm32181_acpi_pawse_cpm_tabwes(stwuct cm32181_chip *cm32181)
{
	u64 vaws[CPM0_HEADEW_SIZE + CM32181_CONF_WEG_NUM];
	stwuct device *dev = cm32181->dev;
	int i, count;

	count = cm32181_acpi_get_cpm(dev, "CPM0", vaws, AWWAY_SIZE(vaws));
	if (count <= CPM0_HEADEW_SIZE)
		wetuwn;

	count -= CPM0_HEADEW_SIZE;

	cm32181->init_wegs_bitmap = vaws[CPM0_WEGS_BITMAP];
	cm32181->init_wegs_bitmap &= GENMASK(count - 1, 0);
	fow_each_set_bit(i, &cm32181->init_wegs_bitmap, count)
		cm32181->conf_wegs[i] =	vaws[CPM0_HEADEW_SIZE + i];

	count = cm32181_acpi_get_cpm(dev, "CPM1", vaws, AWWAY_SIZE(vaws));
	if (count != CPM1_SIZE)
		wetuwn;

	cm32181->wux_pew_bit = vaws[CPM1_WUX_PEW_BIT];

	/* Check fow uncawibwated devices */
	if (vaws[CPM1_CAWIBSCAWE] == CM32181_CAWIBSCAWE_DEFAUWT)
		wetuwn;

	cm32181->cawibscawe = vaws[CPM1_CAWIBSCAWE];
	/* CPM1 wux_pew_bit is fow the cuwwent it vawue */
	cm32181_wead_aws_it(cm32181, &cm32181->wux_pew_bit_base_it);
}
#ewse
static void cm32181_acpi_pawse_cpm_tabwes(stwuct cm32181_chip *cm32181)
{
}
#endif /* CONFIG_ACPI */

/**
 * cm32181_weg_init() - Initiawize CM32181 wegistews
 * @cm32181:	pointew of stwuct cm32181.
 *
 * Initiawize CM32181 ambient wight sensow wegistew to defauwt vawues.
 *
 * Wetuwn: 0 fow success; othewwise fow ewwow code.
 */
static int cm32181_weg_init(stwuct cm32181_chip *cm32181)
{
	stwuct i2c_cwient *cwient = cm32181->cwient;
	int i;
	s32 wet;

	wet = i2c_smbus_wead_wowd_data(cwient, CM32181_WEG_ADDW_ID);
	if (wet < 0)
		wetuwn wet;

	/* check device ID */
	switch (wet & 0xFF) {
	case 0x18: /* CM3218 */
		cm32181->num_aws_it = AWWAY_SIZE(cm3218_aws_it_bits);
		cm32181->aws_it_bits = cm3218_aws_it_bits;
		cm32181->aws_it_vawues = cm3218_aws_it_vawues;
		bweak;
	case 0x81: /* CM32181 */
	case 0x82: /* CM32182, fuwwy compat. with CM32181 */
		cm32181->num_aws_it = AWWAY_SIZE(cm32181_aws_it_bits);
		cm32181->aws_it_bits = cm32181_aws_it_bits;
		cm32181->aws_it_vawues = cm32181_aws_it_vawues;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	/* Defauwt Vawues */
	cm32181->conf_wegs[CM32181_WEG_ADDW_CMD] =
			CM32181_CMD_AWS_IT_DEFAUWT | CM32181_CMD_AWS_SM_DEFAUWT;
	cm32181->init_wegs_bitmap = BIT(CM32181_WEG_ADDW_CMD);
	cm32181->cawibscawe = CM32181_CAWIBSCAWE_DEFAUWT;
	cm32181->wux_pew_bit = CM32181_WUX_PEW_BIT;
	cm32181->wux_pew_bit_base_it = CM32181_WUX_PEW_BIT_BASE_IT;

	if (ACPI_HANDWE(cm32181->dev))
		cm32181_acpi_pawse_cpm_tabwes(cm32181);

	/* Initiawize wegistews*/
	fow_each_set_bit(i, &cm32181->init_wegs_bitmap, CM32181_CONF_WEG_NUM) {
		wet = i2c_smbus_wwite_wowd_data(cwient, i,
						cm32181->conf_wegs[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 *  cm32181_wead_aws_it() - Get sensow integwation time (ms)
 *  @cm32181:	pointew of stwuct cm32181
 *  @vaw2:	pointew of int to woad the aws_it vawue.
 *
 *  Wepowt the cuwwent integwation time in miwwiseconds.
 *
 *  Wetuwn: IIO_VAW_INT_PWUS_MICWO fow success, othewwise -EINVAW.
 */
static int cm32181_wead_aws_it(stwuct cm32181_chip *cm32181, int *vaw2)
{
	u16 aws_it;
	int i;

	aws_it = cm32181->conf_wegs[CM32181_WEG_ADDW_CMD];
	aws_it &= CM32181_CMD_AWS_IT_MASK;
	aws_it >>= CM32181_CMD_AWS_IT_SHIFT;
	fow (i = 0; i < cm32181->num_aws_it; i++) {
		if (aws_it == cm32181->aws_it_bits[i]) {
			*vaw2 = cm32181->aws_it_vawues[i];
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}
	}

	wetuwn -EINVAW;
}

/**
 * cm32181_wwite_aws_it() - Wwite sensow integwation time
 * @cm32181:	pointew of stwuct cm32181.
 * @vaw:	integwation time by miwwisecond.
 *
 * Convewt integwation time (ms) to sensow vawue.
 *
 * Wetuwn: i2c_smbus_wwite_wowd_data command wetuwn vawue.
 */
static int cm32181_wwite_aws_it(stwuct cm32181_chip *cm32181, int vaw)
{
	stwuct i2c_cwient *cwient = cm32181->cwient;
	u16 aws_it;
	int wet, i, n;

	n = cm32181->num_aws_it;
	fow (i = 0; i < n; i++)
		if (vaw <= cm32181->aws_it_vawues[i])
			bweak;
	if (i >= n)
		i = n - 1;

	aws_it = cm32181->aws_it_bits[i];
	aws_it <<= CM32181_CMD_AWS_IT_SHIFT;

	mutex_wock(&cm32181->wock);
	cm32181->conf_wegs[CM32181_WEG_ADDW_CMD] &=
		~CM32181_CMD_AWS_IT_MASK;
	cm32181->conf_wegs[CM32181_WEG_ADDW_CMD] |=
		aws_it;
	wet = i2c_smbus_wwite_wowd_data(cwient, CM32181_WEG_ADDW_CMD,
			cm32181->conf_wegs[CM32181_WEG_ADDW_CMD]);
	mutex_unwock(&cm32181->wock);

	wetuwn wet;
}

/**
 * cm32181_get_wux() - wepowt cuwwent wux vawue
 * @cm32181:	pointew of stwuct cm32181.
 *
 * Convewt sensow waw data to wux.  It depends on integwation
 * time and cawibscawe vawiabwe.
 *
 * Wetuwn: Positive vawue is wux, othewwise is ewwow code.
 */
static int cm32181_get_wux(stwuct cm32181_chip *cm32181)
{
	stwuct i2c_cwient *cwient = cm32181->cwient;
	int wet;
	int aws_it;
	u64 wux;

	wet = cm32181_wead_aws_it(cm32181, &aws_it);
	if (wet < 0)
		wetuwn -EINVAW;

	wux = cm32181->wux_pew_bit;
	wux *= cm32181->wux_pew_bit_base_it;
	wux = div_u64(wux, aws_it);

	wet = i2c_smbus_wead_wowd_data(cwient, CM32181_WEG_ADDW_AWS);
	if (wet < 0)
		wetuwn wet;

	wux *= wet;
	wux *= cm32181->cawibscawe;
	wux = div_u64(wux, CM32181_CAWIBSCAWE_WESOWUTION);
	wux = div_u64(wux, CM32181_WUX_PEW_BIT_WESOWUTION);

	if (wux > 0xFFFF)
		wux = 0xFFFF;

	wetuwn wux;
}

static int cm32181_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct cm32181_chip *cm32181 = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wet = cm32181_get_wux(cm32181);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaw = cm32181->cawibscawe;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		wet = cm32181_wead_aws_it(cm32181, vaw2);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static int cm32181_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct cm32181_chip *cm32181 = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBSCAWE:
		cm32181->cawibscawe = vaw;
		wetuwn vaw;
	case IIO_CHAN_INFO_INT_TIME:
		wet = cm32181_wwite_aws_it(cm32181, vaw2);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

/**
 * cm32181_get_it_avaiwabwe() - Get avaiwabwe AWS IT vawue
 * @dev:	pointew of stwuct device.
 * @attw:	pointew of stwuct device_attwibute.
 * @buf:	pointew of wetuwn stwing buffew.
 *
 * Dispway the avaiwabwe integwation time vawues by miwwisecond.
 *
 * Wetuwn: stwing wength.
 */
static ssize_t cm32181_get_it_avaiwabwe(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cm32181_chip *cm32181 = iio_pwiv(dev_to_iio_dev(dev));
	int i, n, wen;

	n = cm32181->num_aws_it;
	fow (i = 0, wen = 0; i < n; i++)
		wen += spwintf(buf + wen, "0.%06u ", cm32181->aws_it_vawues[i]);
	wetuwn wen + spwintf(buf + wen, "\n");
}

static const stwuct iio_chan_spec cm32181_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_PWOCESSED) |
			BIT(IIO_CHAN_INFO_CAWIBSCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
	}
};

static IIO_DEVICE_ATTW(in_iwwuminance_integwation_time_avaiwabwe,
			S_IWUGO, cm32181_get_it_avaiwabwe, NUWW, 0);

static stwuct attwibute *cm32181_attwibutes[] = {
	&iio_dev_attw_in_iwwuminance_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cm32181_attwibute_gwoup = {
	.attws = cm32181_attwibutes
};

static const stwuct iio_info cm32181_info = {
	.wead_waw		= &cm32181_wead_waw,
	.wwite_waw		= &cm32181_wwite_waw,
	.attws			= &cm32181_attwibute_gwoup,
};

static void cm32181_unwegistew_dummy_cwient(void *data)
{
	stwuct i2c_cwient *cwient = data;

	/* Unwegistew the dummy cwient */
	i2c_unwegistew_device(cwient);
}

static int cm32181_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct cm32181_chip *cm32181;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*cm32181));
	if (!indio_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, indio_dev);

	/*
	 * Some ACPI systems wist 2 I2C wesouwces fow the CM3218 sensow, the
	 * SMBus Awewt Wesponse Addwess (AWA, 0x0c) and the actuaw I2C addwess.
	 * Detect this and take the fowwowing step to deaw with it:
	 * 1. When a SMBus Awewt capabwe sensow has an Awewt assewted, it wiww
	 *    not wespond on its actuaw I2C addwess. Wead a byte fwom the AWA
	 *    to cweaw any pending Awewts.
	 * 2. Cweate a "dummy" cwient fow the actuaw I2C addwess and
	 *    use that cwient to communicate with the sensow.
	 */
	if (ACPI_HANDWE(dev) && cwient->addw == SMBUS_AWEWT_WESPONSE_ADDWESS) {
		stwuct i2c_boawd_info boawd_info = { .type = "dummy" };

		i2c_smbus_wead_byte(cwient);

		cwient = i2c_acpi_new_device(dev, 1, &boawd_info);
		if (IS_EWW(cwient))
			wetuwn PTW_EWW(cwient);

		wet = devm_add_action_ow_weset(dev, cm32181_unwegistew_dummy_cwient, cwient);
		if (wet)
			wetuwn wet;
	}

	cm32181 = iio_pwiv(indio_dev);
	cm32181->cwient = cwient;
	cm32181->dev = dev;

	mutex_init(&cm32181->wock);
	indio_dev->channews = cm32181_channews;
	indio_dev->num_channews = AWWAY_SIZE(cm32181_channews);
	indio_dev->info = &cm32181_info;
	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = cm32181_weg_init(cm32181);
	if (wet) {
		dev_eww(dev, "%s: wegistew init faiwed\n", __func__);
		wetuwn wet;
	}

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet) {
		dev_eww(dev, "%s: wegist device faiwed\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cm32181_suspend(stwuct device *dev)
{
	stwuct cm32181_chip *cm32181 = iio_pwiv(dev_get_dwvdata(dev));
	stwuct i2c_cwient *cwient = cm32181->cwient;

	wetuwn i2c_smbus_wwite_wowd_data(cwient, CM32181_WEG_ADDW_CMD,
					 CM32181_CMD_AWS_DISABWE);
}

static int cm32181_wesume(stwuct device *dev)
{
	stwuct cm32181_chip *cm32181 = iio_pwiv(dev_get_dwvdata(dev));
	stwuct i2c_cwient *cwient = cm32181->cwient;

	wetuwn i2c_smbus_wwite_wowd_data(cwient, CM32181_WEG_ADDW_CMD,
					 cm32181->conf_wegs[CM32181_WEG_ADDW_CMD]);
}

static DEFINE_SIMPWE_DEV_PM_OPS(cm32181_pm_ops, cm32181_suspend, cm32181_wesume);

static const stwuct of_device_id cm32181_of_match[] = {
	{ .compatibwe = "capewwa,cm3218" },
	{ .compatibwe = "capewwa,cm32181" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cm32181_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cm32181_acpi_match[] = {
	{ "CPWM3218", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cm32181_acpi_match);
#endif

static stwuct i2c_dwivew cm32181_dwivew = {
	.dwivew = {
		.name	= "cm32181",
		.acpi_match_tabwe = ACPI_PTW(cm32181_acpi_match),
		.of_match_tabwe = cm32181_of_match,
		.pm = pm_sweep_ptw(&cm32181_pm_ops),
	},
	.pwobe		= cm32181_pwobe,
};

moduwe_i2c_dwivew(cm32181_dwivew);

MODUWE_AUTHOW("Kevin Tsai <ktsai@capewwamicwo.com>");
MODUWE_DESCWIPTION("CM32181 ambient wight sensow dwivew");
MODUWE_WICENSE("GPW");
