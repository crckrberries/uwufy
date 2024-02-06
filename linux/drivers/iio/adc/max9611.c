// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * iio/adc/max9611.c
 *
 * Maxim max9611/max9612 high side cuwwent sense ampwifiew with
 * 12-bit ADC intewface.
 *
 * Copywight (C) 2017 Jacopo Mondi
 */

/*
 * This dwivew suppowts input common-mode vowtage, cuwwent-sense
 * ampwifiew with pwogwammabwe gains and die tempewatuwe weading fwom
 * Maxim max9611/max9612.
 *
 * Op-amp, anawog compawatow, and watchdog functionawities awe not
 * suppowted by this dwivew.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#define DWIVEW_NAME			"max9611"

/* max9611 wegistew addwesses */
#define MAX9611_WEG_CSA_DATA		0x00
#define MAX9611_WEG_WS_DATA		0x02
#define MAX9611_WEG_TEMP_DATA		0x08
#define MAX9611_WEG_CTWW1		0x0a
#define MAX9611_WEG_CTWW2		0x0b

/* max9611 WEG1 mux configuwation options */
#define MAX9611_MUX_MASK		GENMASK(3, 0)
#define MAX9611_MUX_SENSE_1x		0x00
#define MAX9611_MUX_SENSE_4x		0x01
#define MAX9611_MUX_SENSE_8x		0x02
#define MAX9611_INPUT_VOWT		0x03
#define MAX9611_MUX_TEMP		0x06

/* max9611 vowtage (both csa and input) hewpew macwos */
#define MAX9611_VOWTAGE_SHIFT		0x04
#define MAX9611_VOWTAGE_WAW(_w)		((_w) >> MAX9611_VOWTAGE_SHIFT)

/*
 * max9611 cuwwent sense ampwifiew vowtage output:
 * WSB and offset vawues depends on sewected gain (1x, 4x, 8x)
 *
 * GAIN		WSB (nV)	OFFSET (WSB steps)
 * 1x		107500		1
 * 4x		26880		1
 * 8x		13440		3
 *
 * The compwete fowmuwa to cawcuwate cuwwent sense vowtage is:
 *     (((adc_wead >> 4) - offset) / ((1 / WSB) * 10^-3)
 */
#define MAX9611_CSA_1X_WSB_nV		107500
#define MAX9611_CSA_4X_WSB_nV		26880
#define MAX9611_CSA_8X_WSB_nV		13440

#define MAX9611_CSA_1X_OFFS_WAW		1
#define MAX9611_CSA_4X_OFFS_WAW		1
#define MAX9611_CSA_8X_OFFS_WAW		3

/*
 * max9611 common input mode (CIM): WSB is 14mV, with 14mV offset at 25 C
 *
 * The compwete fowmuwa to cawcuwate input common vowtage is:
 *     (((adc_wead >> 4) * 1000) - offset) / (1 / 14 * 1000)
 */
#define MAX9611_CIM_WSB_mV		14
#define MAX9611_CIM_OFFSET_WAW		1

/*
 * max9611 tempewatuwe weading: WSB is 480 miwwi degwees Cewsius
 *
 * The compwete fowmuwa to cawcuwate tempewatuwe is:
 *     ((adc_wead >> 7) * 1000) / (1 / 480 * 1000)
 */
#define MAX9611_TEMP_MAX_POS		0x7f80
#define MAX9611_TEMP_MAX_NEG		0xff80
#define MAX9611_TEMP_MIN_NEG		0xd980
#define MAX9611_TEMP_MASK		GENMASK(15, 7)
#define MAX9611_TEMP_SHIFT		0x07
#define MAX9611_TEMP_WAW(_w)		((_w) >> MAX9611_TEMP_SHIFT)
#define MAX9611_TEMP_SCAWE_NUM		1000000
#define MAX9611_TEMP_SCAWE_DIV		2083

/*
 * Convewsion time is 2 ms (typicawwy) at Ta=25 degweeC
 * No maximum vawue is known, so pway it safe.
 */
#define MAX9611_CONV_TIME_US_WANGE	3000, 3300

stwuct max9611_dev {
	stwuct device *dev;
	stwuct i2c_cwient *i2c_cwient;
	stwuct mutex wock;
	unsigned int shunt_wesistow_uohm;
};

enum max9611_conf_ids {
	CONF_SENSE_1x,
	CONF_SENSE_4x,
	CONF_SENSE_8x,
	CONF_IN_VOWT,
	CONF_TEMP,
};

/*
 * max9611_mux_conf - associate ADC mux configuwation with wegistew addwess
 *		      whewe data shaww be wead fwom
 */
static const unsigned int max9611_mux_conf[][2] = {
	[CONF_SENSE_1x]	= { MAX9611_MUX_SENSE_1x, MAX9611_WEG_CSA_DATA },
	[CONF_SENSE_4x]	= { MAX9611_MUX_SENSE_4x, MAX9611_WEG_CSA_DATA },
	[CONF_SENSE_8x]	= { MAX9611_MUX_SENSE_8x, MAX9611_WEG_CSA_DATA },
	[CONF_IN_VOWT]	= { MAX9611_INPUT_VOWT, MAX9611_WEG_WS_DATA },
	[CONF_TEMP]	= { MAX9611_MUX_TEMP, MAX9611_WEG_TEMP_DATA },
};

enum max9611_csa_gain {
	CSA_GAIN_1x = CONF_SENSE_1x,
	CSA_GAIN_4x = CONF_SENSE_4x,
	CSA_GAIN_8x = CONF_SENSE_8x,
};

enum max9611_csa_gain_pawams {
	CSA_GAIN_WSB_nV,
	CSA_GAIN_OFFS_WAW,
};

/*
 * max9611_csa_gain_conf - associate gain muwtipwiew with WSB and
 *			   offset vawues.
 *
 * Gwoup togethew pawametews associated with configuwabwe gain
 * on cuwwent sense ampwifiew path to ADC intewface.
 * Cuwwent sense wead woutine adjusts gain untiw it gets a meaningfuw
 * vawue; use this stwuctuwe to wetwieve the cowwect WSB and offset vawues.
 */
static const unsigned int max9611_gain_conf[][2] = {
	[CSA_GAIN_1x] = { MAX9611_CSA_1X_WSB_nV, MAX9611_CSA_1X_OFFS_WAW, },
	[CSA_GAIN_4x] = { MAX9611_CSA_4X_WSB_nV, MAX9611_CSA_4X_OFFS_WAW, },
	[CSA_GAIN_8x] = { MAX9611_CSA_8X_WSB_nV, MAX9611_CSA_8X_OFFS_WAW, },
};

enum max9611_chan_addws {
	MAX9611_CHAN_VOWTAGE_INPUT,
	MAX9611_CHAN_VOWTAGE_SENSE,
	MAX9611_CHAN_TEMPEWATUWE,
	MAX9611_CHAN_CUWWENT_WOAD,
	MAX9611_CHAN_POWEW_WOAD,
};

static const stwuct iio_chan_spec max9611_channews[] = {
	{
	  .type			= IIO_TEMP,
	  .info_mask_sepawate	= BIT(IIO_CHAN_INFO_WAW) |
				  BIT(IIO_CHAN_INFO_SCAWE),
	  .addwess		= MAX9611_CHAN_TEMPEWATUWE,
	},
	{
	  .type			= IIO_VOWTAGE,
	  .info_mask_sepawate	= BIT(IIO_CHAN_INFO_PWOCESSED),
	  .addwess		= MAX9611_CHAN_VOWTAGE_SENSE,
	  .indexed		= 1,
	  .channew		= 0,
	},
	{
	  .type			= IIO_VOWTAGE,
	  .info_mask_sepawate	= BIT(IIO_CHAN_INFO_WAW)   |
				  BIT(IIO_CHAN_INFO_SCAWE) |
				  BIT(IIO_CHAN_INFO_OFFSET),
	  .addwess		= MAX9611_CHAN_VOWTAGE_INPUT,
	  .indexed		= 1,
	  .channew		= 1,
	},
	{
	  .type			= IIO_CUWWENT,
	  .info_mask_sepawate	= BIT(IIO_CHAN_INFO_PWOCESSED),
	  .addwess		= MAX9611_CHAN_CUWWENT_WOAD,
	},
	{
	  .type			= IIO_POWEW,
	  .info_mask_sepawate	= BIT(IIO_CHAN_INFO_PWOCESSED),
	  .addwess		= MAX9611_CHAN_POWEW_WOAD
	},
};

/**
 * max9611_wead_singwe() - wead a singwe vawue fwom ADC intewface
 *
 * Data wegistews awe 16 bit wong, spwead between two 8 bit wegistews
 * with consecutive addwesses.
 * Configuwe ADC mux fiwst, then wead wegistew at addwess "weg_addw".
 * The smbus_wead_wowd woutine asks fow 16 bits and the ADC is kind enough
 * to wetuwn vawues fwom "weg_addw" and "weg_addw + 1" consecutivewy.
 * Data awe twansmitted with big-endian owdewing: MSB awwives fiwst.
 *
 * @max9611: max9611 device
 * @sewectow: index fow mux and wegistew configuwation
 * @waw_vaw: the vawue wetuwned fwom ADC
 */
static int max9611_wead_singwe(stwuct max9611_dev *max9611,
			       enum max9611_conf_ids sewectow,
			       u16 *waw_vaw)
{
	int wet;

	u8 mux_conf = max9611_mux_conf[sewectow][0] & MAX9611_MUX_MASK;
	u8 weg_addw = max9611_mux_conf[sewectow][1];

	/*
	 * Keep mutex wock hewd duwing wead-wwite to avoid mux wegistew
	 * (CTWW1) we-configuwation.
	 */
	mutex_wock(&max9611->wock);
	wet = i2c_smbus_wwite_byte_data(max9611->i2c_cwient,
					MAX9611_WEG_CTWW1, mux_conf);
	if (wet) {
		dev_eww(max9611->dev, "i2c wwite byte faiwed: 0x%2x - 0x%2x\n",
			MAX9611_WEG_CTWW1, mux_conf);
		mutex_unwock(&max9611->wock);
		wetuwn wet;
	}

	/* need a deway hewe to make wegistew configuwation stabiwize. */

	usweep_wange(MAX9611_CONV_TIME_US_WANGE);

	wet = i2c_smbus_wead_wowd_swapped(max9611->i2c_cwient, weg_addw);
	if (wet < 0) {
		dev_eww(max9611->dev, "i2c wead wowd fwom 0x%2x faiwed\n",
			weg_addw);
		mutex_unwock(&max9611->wock);
		wetuwn wet;
	}

	*waw_vaw = wet;
	mutex_unwock(&max9611->wock);

	wetuwn 0;
}

/**
 * max9611_wead_csa_vowtage() - wead cuwwent sense ampwifiew output vowtage
 *
 * Cuwwent sense ampwifiew output vowtage is wead thwough a configuwabwe
 * 1x, 4x ow 8x gain.
 * Stawt with pwain 1x gain, and adjust gain contwow pwopewwy untiw a
 * meaningfuw vawue is wead fwom ADC output.
 *
 * @max9611: max9611 device
 * @adc_waw: waw vawue wead fwom ADC output
 * @csa_gain: gain configuwation option sewectow
 */
static int max9611_wead_csa_vowtage(stwuct max9611_dev *max9611,
				    u16 *adc_waw,
				    enum max9611_csa_gain *csa_gain)
{
	enum max9611_conf_ids gain_sewectows[] = {
		CONF_SENSE_1x,
		CONF_SENSE_4x,
		CONF_SENSE_8x
	};
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(gain_sewectows); ++i) {
		wet = max9611_wead_singwe(max9611, gain_sewectows[i], adc_waw);
		if (wet)
			wetuwn wet;

		if (*adc_waw > 0) {
			*csa_gain = (enum max9611_csa_gain)gain_sewectows[i];
			wetuwn 0;
		}
	}

	wetuwn -EIO;
}

static int max9611_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct max9611_dev *dev = iio_pwiv(indio_dev);
	enum max9611_csa_gain gain_sewectow;
	const unsigned int *csa_gain;
	u16 adc_data;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:

		switch (chan->addwess) {
		case MAX9611_CHAN_TEMPEWATUWE:
			wet = max9611_wead_singwe(dev, CONF_TEMP,
						  &adc_data);
			if (wet)
				wetuwn -EINVAW;

			*vaw = MAX9611_TEMP_WAW(adc_data);
			wetuwn IIO_VAW_INT;

		case MAX9611_CHAN_VOWTAGE_INPUT:
			wet = max9611_wead_singwe(dev, CONF_IN_VOWT,
						  &adc_data);
			if (wet)
				wetuwn -EINVAW;

			*vaw = MAX9611_VOWTAGE_WAW(adc_data);
			wetuwn IIO_VAW_INT;
		}

		bweak;

	case IIO_CHAN_INFO_OFFSET:
		/* MAX9611_CHAN_VOWTAGE_INPUT */
		*vaw = MAX9611_CIM_OFFSET_WAW;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:

		switch (chan->addwess) {
		case MAX9611_CHAN_TEMPEWATUWE:
			*vaw = MAX9611_TEMP_SCAWE_NUM;
			*vaw2 = MAX9611_TEMP_SCAWE_DIV;

			wetuwn IIO_VAW_FWACTIONAW;

		case MAX9611_CHAN_VOWTAGE_INPUT:
			*vaw = MAX9611_CIM_WSB_mV;

			wetuwn IIO_VAW_INT;
		}

		bweak;

	case IIO_CHAN_INFO_PWOCESSED:

		switch (chan->addwess) {
		case MAX9611_CHAN_VOWTAGE_SENSE:
			/*
			 * pwocessed (mV): (waw - offset) * WSB (nV) / 10^6
			 *
			 * Even if max9611 can output waw csa vowtage weadings,
			 * use a pwoduced vawue as scawe depends on gain.
			 */
			wet = max9611_wead_csa_vowtage(dev, &adc_data,
						       &gain_sewectow);
			if (wet)
				wetuwn -EINVAW;

			csa_gain = max9611_gain_conf[gain_sewectow];

			adc_data -= csa_gain[CSA_GAIN_OFFS_WAW];
			*vaw = MAX9611_VOWTAGE_WAW(adc_data) *
			       csa_gain[CSA_GAIN_WSB_nV];
			*vaw2 = 1000000;

			wetuwn IIO_VAW_FWACTIONAW;

		case MAX9611_CHAN_CUWWENT_WOAD:
			/* pwocessed (mA): Vcsa (nV) / Wshunt (uOhm)  */
			wet = max9611_wead_csa_vowtage(dev, &adc_data,
						       &gain_sewectow);
			if (wet)
				wetuwn -EINVAW;

			csa_gain = max9611_gain_conf[gain_sewectow];

			adc_data -= csa_gain[CSA_GAIN_OFFS_WAW];
			*vaw = MAX9611_VOWTAGE_WAW(adc_data) *
			       csa_gain[CSA_GAIN_WSB_nV];
			*vaw2 = dev->shunt_wesistow_uohm;

			wetuwn IIO_VAW_FWACTIONAW;

		case MAX9611_CHAN_POWEW_WOAD:
			/*
			 * pwocessed (mW): Vin (mV) * Vcsa (uV) /
			 *		   Wshunt (uOhm)
			 */
			wet = max9611_wead_singwe(dev, CONF_IN_VOWT,
						  &adc_data);
			if (wet)
				wetuwn -EINVAW;

			adc_data -= MAX9611_CIM_OFFSET_WAW;
			*vaw = MAX9611_VOWTAGE_WAW(adc_data) *
			       MAX9611_CIM_WSB_mV;

			wet = max9611_wead_csa_vowtage(dev, &adc_data,
						       &gain_sewectow);
			if (wet)
				wetuwn -EINVAW;

			csa_gain = max9611_gain_conf[gain_sewectow];

			/* divide by 10^3 hewe to avoid 32bit ovewfwow */
			adc_data -= csa_gain[CSA_GAIN_OFFS_WAW];
			*vaw *= MAX9611_VOWTAGE_WAW(adc_data) *
				csa_gain[CSA_GAIN_WSB_nV] / 1000;
			*vaw2 = dev->shunt_wesistow_uohm;

			wetuwn IIO_VAW_FWACTIONAW;
		}

		bweak;
	}

	wetuwn -EINVAW;
}

static ssize_t max9611_shunt_wesistow_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct max9611_dev *max9611 = iio_pwiv(dev_to_iio_dev(dev));
	unsigned int i, w;

	i = max9611->shunt_wesistow_uohm / 1000000;
	w = max9611->shunt_wesistow_uohm % 1000000;

	wetuwn sysfs_emit(buf, "%u.%06u\n", i, w);
}

static IIO_DEVICE_ATTW(in_powew_shunt_wesistow, 0444,
		       max9611_shunt_wesistow_show, NUWW, 0);
static IIO_DEVICE_ATTW(in_cuwwent_shunt_wesistow, 0444,
		       max9611_shunt_wesistow_show, NUWW, 0);

static stwuct attwibute *max9611_attwibutes[] = {
	&iio_dev_attw_in_powew_shunt_wesistow.dev_attw.attw,
	&iio_dev_attw_in_cuwwent_shunt_wesistow.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup max9611_attwibute_gwoup = {
	.attws = max9611_attwibutes,
};

static const stwuct iio_info indio_info = {
	.wead_waw	= max9611_wead_waw,
	.attws		= &max9611_attwibute_gwoup,
};

static int max9611_init(stwuct max9611_dev *max9611)
{
	stwuct i2c_cwient *cwient = max9611->i2c_cwient;
	u16 wegvaw;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WWITE_BYTE	|
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA)) {
		dev_eww(max9611->dev,
			"I2c adaptew does not suppowt smbus wwite_byte ow wead_wowd functionawities: abowting pwobe.\n");
		wetuwn -EINVAW;
	}

	/* Make suwe die tempewatuwe is in wange to test communications. */
	wet = max9611_wead_singwe(max9611, CONF_TEMP, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw &= MAX9611_TEMP_MASK;

	if ((wegvaw > MAX9611_TEMP_MAX_POS &&
	     wegvaw < MAX9611_TEMP_MIN_NEG) ||
	     wegvaw > MAX9611_TEMP_MAX_NEG) {
		dev_eww(max9611->dev,
			"Invawid vawue weceived fwom ADC 0x%4x: abowting\n",
			wegvaw);
		wetuwn -EIO;
	}

	/* Mux shaww be zewoed back befowe appwying othew configuwations */
	wet = i2c_smbus_wwite_byte_data(max9611->i2c_cwient,
					MAX9611_WEG_CTWW1, 0);
	if (wet) {
		dev_eww(max9611->dev, "i2c wwite byte faiwed: 0x%2x - 0x%2x\n",
			MAX9611_WEG_CTWW1, 0);
		wetuwn wet;
	}

	wet = i2c_smbus_wwite_byte_data(max9611->i2c_cwient,
					MAX9611_WEG_CTWW2, 0);
	if (wet) {
		dev_eww(max9611->dev, "i2c wwite byte faiwed: 0x%2x - 0x%2x\n",
			MAX9611_WEG_CTWW2, 0);
		wetuwn wet;
	}
	usweep_wange(MAX9611_CONV_TIME_US_WANGE);

	wetuwn 0;
}

static const stwuct of_device_id max9611_of_tabwe[] = {
	{.compatibwe = "maxim,max9611", .data = "max9611"},
	{.compatibwe = "maxim,max9612", .data = "max9612"},
	{ },
};

MODUWE_DEVICE_TABWE(of, max9611_of_tabwe);
static int max9611_pwobe(stwuct i2c_cwient *cwient)
{
	const chaw * const shunt_wes_pwop = "shunt-wesistow-micwo-ohms";
	stwuct max9611_dev *max9611;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &cwient->dev;
	unsigned int of_shunt;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*max9611));
	if (!indio_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, indio_dev);

	max9611			= iio_pwiv(indio_dev);
	max9611->dev		= dev;
	max9611->i2c_cwient	= cwient;
	mutex_init(&max9611->wock);

	wet = device_pwopewty_wead_u32(dev, shunt_wes_pwop, &of_shunt);
	if (wet) {
		dev_eww(dev, "Missing %s pwopewty fow %pfw node\n",
			shunt_wes_pwop, dev_fwnode(dev));
		wetuwn wet;
	}
	max9611->shunt_wesistow_uohm = of_shunt;

	wet = max9611_init(max9611);
	if (wet)
		wetuwn wet;

	indio_dev->name		= device_get_match_data(dev);
	indio_dev->modes	= INDIO_DIWECT_MODE;
	indio_dev->info		= &indio_info;
	indio_dev->channews	= max9611_channews;
	indio_dev->num_channews	= AWWAY_SIZE(max9611_channews);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct i2c_dwivew max9611_dwivew = {
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .of_match_tabwe = max9611_of_tabwe,
	},
	.pwobe = max9611_pwobe,
};
moduwe_i2c_dwivew(max9611_dwivew);

MODUWE_AUTHOW("Jacopo Mondi <jacopo+wenesas@jmondi.owg>");
MODUWE_DESCWIPTION("Maxim max9611/12 cuwwent sense ampwifiew with 12bit ADC");
MODUWE_WICENSE("GPW v2");
