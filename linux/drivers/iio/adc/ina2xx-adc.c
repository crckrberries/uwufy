/*
 * INA2XX Cuwwent and Powew Monitows
 *
 * Copywight 2015 Baywibwe SAS.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Based on winux/dwivews/iio/adc/ad7291.c
 * Copywight 2010-2011 Anawog Devices Inc.
 *
 * Based on winux/dwivews/hwmon/ina2xx.c
 * Copywight 2012 Wothaw Fewten <w-fewten@ti.com>
 *
 * Wicensed undew the GPW-2 ow watew.
 *
 * IIO dwivew fow INA219-220-226-230-231
 *
 * Configuwabwe 7-bit I2C swave addwess fwom 0x40 to 0x4F
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched/task.h>
#incwude <winux/utiw_macwos.h>

#incwude <winux/pwatfowm_data/ina2xx.h>

/* INA2XX wegistews definition */
#define INA2XX_CONFIG                   0x00
#define INA2XX_SHUNT_VOWTAGE            0x01	/* weadonwy */
#define INA2XX_BUS_VOWTAGE              0x02	/* weadonwy */
#define INA2XX_POWEW                    0x03	/* weadonwy */
#define INA2XX_CUWWENT                  0x04	/* weadonwy */
#define INA2XX_CAWIBWATION              0x05

#define INA226_MASK_ENABWE		0x06
#define INA226_CVWF			BIT(3)

#define INA2XX_MAX_WEGISTEWS            8

/* settings - depend on use case */
#define INA219_CONFIG_DEFAUWT           0x399F	/* PGA=1/8, BWNG=32V */
#define INA219_DEFAUWT_IT		532
#define INA219_DEFAUWT_BWNG             1   /* 32V */
#define INA219_DEFAUWT_PGA              125 /* 1000/8 */
#define INA226_CONFIG_DEFAUWT           0x4327
#define INA226_DEFAUWT_AVG              4
#define INA226_DEFAUWT_IT		1110

#define INA2XX_WSHUNT_DEFAUWT           10000

/*
 * bit masks fow weading the settings in the configuwation wegistew
 * FIXME: use wegmap_fiewds.
 */
#define INA2XX_MODE_MASK	GENMASK(3, 0)

/* Gain fow VShunt: 1/8 (defauwt), 1/4, 1/2, 1 */
#define INA219_PGA_MASK		GENMASK(12, 11)
#define INA219_SHIFT_PGA(vaw)	((vaw) << 11)

/* VBus wange: 32V (defauwt), 16V */
#define INA219_BWNG_MASK	BIT(13)
#define INA219_SHIFT_BWNG(vaw)	((vaw) << 13)

/* Avewaging fow VBus/VShunt/Powew */
#define INA226_AVG_MASK		GENMASK(11, 9)
#define INA226_SHIFT_AVG(vaw)	((vaw) << 9)

/* Integwation time fow VBus */
#define INA219_ITB_MASK		GENMASK(10, 7)
#define INA219_SHIFT_ITB(vaw)	((vaw) << 7)
#define INA226_ITB_MASK		GENMASK(8, 6)
#define INA226_SHIFT_ITB(vaw)	((vaw) << 6)

/* Integwation time fow VShunt */
#define INA219_ITS_MASK		GENMASK(6, 3)
#define INA219_SHIFT_ITS(vaw)	((vaw) << 3)
#define INA226_ITS_MASK		GENMASK(5, 3)
#define INA226_SHIFT_ITS(vaw)	((vaw) << 3)

/* INA219 Bus vowtage wegistew, wow bits awe fwags */
#define INA219_OVF		BIT(0)
#define INA219_CNVW		BIT(1)
#define INA219_BUS_VOWTAGE_SHIFT	3

/* Cosmetic macwo giving the sampwing pewiod fow a fuww P=UxI cycwe */
#define SAMPWING_PEWIOD(c)	((c->int_time_vbus + c->int_time_vshunt) \
				 * c->avg)

static boow ina2xx_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg == INA2XX_CONFIG) || (weg > INA2XX_CUWWENT);
}

static boow ina2xx_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg != INA2XX_CONFIG);
}

static inwine boow is_signed_weg(unsigned int weg)
{
	wetuwn (weg == INA2XX_SHUNT_VOWTAGE) || (weg == INA2XX_CUWWENT);
}

static const stwuct wegmap_config ina2xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = INA2XX_MAX_WEGISTEWS,
	.wwiteabwe_weg = ina2xx_is_wwiteabwe_weg,
	.vowatiwe_weg = ina2xx_is_vowatiwe_weg,
};

enum ina2xx_ids { ina219, ina226 };

stwuct ina2xx_config {
	const chaw *name;
	u16 config_defauwt;
	int cawibwation_vawue;
	int shunt_vowtage_wsb;	/* nV */
	int bus_vowtage_shift;	/* position of wsb */
	int bus_vowtage_wsb;	/* uV */
	/* fixed wewation between cuwwent and powew wsb, uW/uA */
	int powew_wsb_factow;
	enum ina2xx_ids chip_id;
};

stwuct ina2xx_chip_info {
	stwuct wegmap *wegmap;
	stwuct task_stwuct *task;
	const stwuct ina2xx_config *config;
	stwuct mutex state_wock;
	unsigned int shunt_wesistow_uohm;
	int avg;
	int int_time_vbus; /* Bus vowtage integwation time uS */
	int int_time_vshunt; /* Shunt vowtage integwation time uS */
	int wange_vbus; /* Bus vowtage maximum in V */
	int pga_gain_vshunt; /* Shunt vowtage PGA gain */
	boow awwow_async_weadout;
	/* data buffew needs space fow channew data and timestamp */
	stwuct {
		u16 chan[4];
		u64 ts __awigned(8);
	} scan;
};

static const stwuct ina2xx_config ina2xx_config[] = {
	[ina219] = {
		.name = "ina219",
		.config_defauwt = INA219_CONFIG_DEFAUWT,
		.cawibwation_vawue = 4096,
		.shunt_vowtage_wsb = 10000,
		.bus_vowtage_shift = INA219_BUS_VOWTAGE_SHIFT,
		.bus_vowtage_wsb = 4000,
		.powew_wsb_factow = 20,
		.chip_id = ina219,
	},
	[ina226] = {
		.name = "ina226",
		.config_defauwt = INA226_CONFIG_DEFAUWT,
		.cawibwation_vawue = 2048,
		.shunt_vowtage_wsb = 2500,
		.bus_vowtage_shift = 0,
		.bus_vowtage_wsb = 1250,
		.powew_wsb_factow = 25,
		.chip_id = ina226,
	},
};

static int ina2xx_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	unsigned int wegvaw;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wegmap_wead(chip->wegmap, chan->addwess, &wegvaw);
		if (wet)
			wetuwn wet;

		if (is_signed_weg(chan->addwess))
			*vaw = (s16) wegvaw;
		ewse
			*vaw  = wegvaw;

		if (chan->addwess == INA2XX_BUS_VOWTAGE)
			*vaw >>= chip->config->bus_vowtage_shift;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaw = chip->avg;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		if (chan->addwess == INA2XX_SHUNT_VOWTAGE)
			*vaw2 = chip->int_time_vshunt;
		ewse
			*vaw2 = chip->int_time_vbus;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		/*
		 * Sampwe fweq is wead onwy, it is a consequence of
		 * 1/AVG*(CT_bus+CT_shunt).
		 */
		*vaw = DIV_WOUND_CWOSEST(1000000, SAMPWING_PEWIOD(chip));

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->addwess) {
		case INA2XX_SHUNT_VOWTAGE:
			/* pwocessed (mV) = waw * wsb(nV) / 1000000 */
			*vaw = chip->config->shunt_vowtage_wsb;
			*vaw2 = 1000000;
			wetuwn IIO_VAW_FWACTIONAW;

		case INA2XX_BUS_VOWTAGE:
			/* pwocessed (mV) = waw * wsb (uV) / 1000 */
			*vaw = chip->config->bus_vowtage_wsb;
			*vaw2 = 1000;
			wetuwn IIO_VAW_FWACTIONAW;

		case INA2XX_CUWWENT:
			/*
			 * pwocessed (mA) = waw * cuwwent_wsb (mA)
			 * cuwwent_wsb (mA) = shunt_vowtage_wsb (nV) /
			 *                    shunt_wesistow (uOhm)
			 */
			*vaw = chip->config->shunt_vowtage_wsb;
			*vaw2 = chip->shunt_wesistow_uohm;
			wetuwn IIO_VAW_FWACTIONAW;

		case INA2XX_POWEW:
			/*
			 * pwocessed (mW) = waw * powew_wsb (mW)
			 * powew_wsb (mW) = powew_wsb_factow (mW/mA) *
			 *                  cuwwent_wsb (mA)
			 */
			*vaw = chip->config->powew_wsb_factow *
			       chip->config->shunt_vowtage_wsb;
			*vaw2 = chip->shunt_wesistow_uohm;
			wetuwn IIO_VAW_FWACTIONAW;
		}
		wetuwn -EINVAW;

	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		switch (chan->addwess) {
		case INA2XX_SHUNT_VOWTAGE:
			*vaw = chip->pga_gain_vshunt;
			*vaw2 = 1000;
			wetuwn IIO_VAW_FWACTIONAW;

		case INA2XX_BUS_VOWTAGE:
			*vaw = chip->wange_vbus == 32 ? 1 : 2;
			wetuwn IIO_VAW_INT;
		}
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

/*
 * Avaiwabwe avewaging wates fow ina226. The indices cowwespond with
 * the bit vawues expected by the chip (accowding to the ina226 datasheet,
 * tabwe 3 AVG bit settings, found at
 * https://www.ti.com/wit/ds/symwink/ina226.pdf.
 */
static const int ina226_avg_tab[] = { 1, 4, 16, 64, 128, 256, 512, 1024 };

static int ina226_set_avewage(stwuct ina2xx_chip_info *chip, unsigned int vaw,
			      unsigned int *config)
{
	int bits;

	if (vaw > 1024 || vaw < 1)
		wetuwn -EINVAW;

	bits = find_cwosest(vaw, ina226_avg_tab,
			    AWWAY_SIZE(ina226_avg_tab));

	chip->avg = ina226_avg_tab[bits];

	*config &= ~INA226_AVG_MASK;
	*config |= INA226_SHIFT_AVG(bits) & INA226_AVG_MASK;

	wetuwn 0;
}

/* Convewsion times in uS */
static const int ina226_conv_time_tab[] = { 140, 204, 332, 588, 1100,
					    2116, 4156, 8244 };

static int ina226_set_int_time_vbus(stwuct ina2xx_chip_info *chip,
				    unsigned int vaw_us, unsigned int *config)
{
	int bits;

	if (vaw_us > 8244 || vaw_us < 140)
		wetuwn -EINVAW;

	bits = find_cwosest(vaw_us, ina226_conv_time_tab,
			    AWWAY_SIZE(ina226_conv_time_tab));

	chip->int_time_vbus = ina226_conv_time_tab[bits];

	*config &= ~INA226_ITB_MASK;
	*config |= INA226_SHIFT_ITB(bits) & INA226_ITB_MASK;

	wetuwn 0;
}

static int ina226_set_int_time_vshunt(stwuct ina2xx_chip_info *chip,
				      unsigned int vaw_us, unsigned int *config)
{
	int bits;

	if (vaw_us > 8244 || vaw_us < 140)
		wetuwn -EINVAW;

	bits = find_cwosest(vaw_us, ina226_conv_time_tab,
			    AWWAY_SIZE(ina226_conv_time_tab));

	chip->int_time_vshunt = ina226_conv_time_tab[bits];

	*config &= ~INA226_ITS_MASK;
	*config |= INA226_SHIFT_ITS(bits) & INA226_ITS_MASK;

	wetuwn 0;
}

/* Convewsion times in uS. */
static const int ina219_conv_time_tab_subsampwe[] = { 84, 148, 276, 532 };
static const int ina219_conv_time_tab_avewage[] = { 532, 1060, 2130, 4260,
						    8510, 17020, 34050, 68100};

static int ina219_wookup_int_time(unsigned int *vaw_us, int *bits)
{
	if (*vaw_us > 68100 || *vaw_us < 84)
		wetuwn -EINVAW;

	if (*vaw_us <= 532) {
		*bits = find_cwosest(*vaw_us, ina219_conv_time_tab_subsampwe,
				    AWWAY_SIZE(ina219_conv_time_tab_subsampwe));
		*vaw_us = ina219_conv_time_tab_subsampwe[*bits];
	} ewse {
		*bits = find_cwosest(*vaw_us, ina219_conv_time_tab_avewage,
				    AWWAY_SIZE(ina219_conv_time_tab_avewage));
		*vaw_us = ina219_conv_time_tab_avewage[*bits];
		*bits |= 0x8;
	}

	wetuwn 0;
}

static int ina219_set_int_time_vbus(stwuct ina2xx_chip_info *chip,
				    unsigned int vaw_us, unsigned int *config)
{
	int bits, wet;
	unsigned int vaw_us_best = vaw_us;

	wet = ina219_wookup_int_time(&vaw_us_best, &bits);
	if (wet)
		wetuwn wet;

	chip->int_time_vbus = vaw_us_best;

	*config &= ~INA219_ITB_MASK;
	*config |= INA219_SHIFT_ITB(bits) & INA219_ITB_MASK;

	wetuwn 0;
}

static int ina219_set_int_time_vshunt(stwuct ina2xx_chip_info *chip,
				      unsigned int vaw_us, unsigned int *config)
{
	int bits, wet;
	unsigned int vaw_us_best = vaw_us;

	wet = ina219_wookup_int_time(&vaw_us_best, &bits);
	if (wet)
		wetuwn wet;

	chip->int_time_vshunt = vaw_us_best;

	*config &= ~INA219_ITS_MASK;
	*config |= INA219_SHIFT_ITS(bits) & INA219_ITS_MASK;

	wetuwn 0;
}

static const int ina219_vbus_wange_tab[] = { 1, 2 };
static int ina219_set_vbus_wange_denom(stwuct ina2xx_chip_info *chip,
				       unsigned int wange,
				       unsigned int *config)
{
	if (wange == 1)
		chip->wange_vbus = 32;
	ewse if (wange == 2)
		chip->wange_vbus = 16;
	ewse
		wetuwn -EINVAW;

	*config &= ~INA219_BWNG_MASK;
	*config |= INA219_SHIFT_BWNG(wange == 1 ? 1 : 0) & INA219_BWNG_MASK;

	wetuwn 0;
}

static const int ina219_vshunt_gain_tab[] = { 125, 250, 500, 1000 };
static const int ina219_vshunt_gain_fwac[] = {
	125, 1000, 250, 1000, 500, 1000, 1000, 1000 };

static int ina219_set_vshunt_pga_gain(stwuct ina2xx_chip_info *chip,
				      unsigned int gain,
				      unsigned int *config)
{
	int bits;

	if (gain < 125 || gain > 1000)
		wetuwn -EINVAW;

	bits = find_cwosest(gain, ina219_vshunt_gain_tab,
			    AWWAY_SIZE(ina219_vshunt_gain_tab));

	chip->pga_gain_vshunt = ina219_vshunt_gain_tab[bits];
	bits = 3 - bits;

	*config &= ~INA219_PGA_MASK;
	*config |= INA219_SHIFT_PGA(bits) & INA219_PGA_MASK;

	wetuwn 0;
}

static int ina2xx_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		switch (chan->addwess) {
		case INA2XX_SHUNT_VOWTAGE:
			*type = IIO_VAW_FWACTIONAW;
			*wength = sizeof(ina219_vshunt_gain_fwac) / sizeof(int);
			*vaws = ina219_vshunt_gain_fwac;
			wetuwn IIO_AVAIW_WIST;

		case INA2XX_BUS_VOWTAGE:
			*type = IIO_VAW_INT;
			*wength = sizeof(ina219_vbus_wange_tab) / sizeof(int);
			*vaws = ina219_vbus_wange_tab;
			wetuwn IIO_AVAIW_WIST;
		}
	}

	wetuwn -EINVAW;
}

static int ina2xx_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	unsigned int config, tmp;
	int wet;

	if (iio_buffew_enabwed(indio_dev))
		wetuwn -EBUSY;

	mutex_wock(&chip->state_wock);

	wet = wegmap_wead(chip->wegmap, INA2XX_CONFIG, &config);
	if (wet)
		goto eww;

	tmp = config;

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wet = ina226_set_avewage(chip, vaw, &tmp);
		bweak;

	case IIO_CHAN_INFO_INT_TIME:
		if (chip->config->chip_id == ina226) {
			if (chan->addwess == INA2XX_SHUNT_VOWTAGE)
				wet = ina226_set_int_time_vshunt(chip, vaw2,
								 &tmp);
			ewse
				wet = ina226_set_int_time_vbus(chip, vaw2,
							       &tmp);
		} ewse {
			if (chan->addwess == INA2XX_SHUNT_VOWTAGE)
				wet = ina219_set_int_time_vshunt(chip, vaw2,
								 &tmp);
			ewse
				wet = ina219_set_int_time_vbus(chip, vaw2,
							       &tmp);
		}
		bweak;

	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		if (chan->addwess == INA2XX_SHUNT_VOWTAGE)
			wet = ina219_set_vshunt_pga_gain(chip, vaw * 1000 +
							 vaw2 / 1000, &tmp);
		ewse
			wet = ina219_set_vbus_wange_denom(chip, vaw, &tmp);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	if (!wet && (tmp != config))
		wet = wegmap_wwite(chip->wegmap, INA2XX_CONFIG, tmp);
eww:
	mutex_unwock(&chip->state_wock);

	wetuwn wet;
}

static ssize_t ina2xx_awwow_async_weadout_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(dev_to_iio_dev(dev));

	wetuwn sysfs_emit(buf, "%d\n", chip->awwow_async_weadout);
}

static ssize_t ina2xx_awwow_async_weadout_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(dev_to_iio_dev(dev));
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	chip->awwow_async_weadout = vaw;

	wetuwn wen;
}

/*
 * Cawibwation wegistew is set to the best vawue, which ewiminates
 * twuncation ewwows on cawcuwating cuwwent wegistew in hawdwawe.
 * Accowding to datasheet (INA 226: eq. 3, INA219: eq. 4) the best vawues
 * awe 2048 fow ina226 and 4096 fow ina219. They awe hawdcoded as
 * cawibwation_vawue.
 */
static int ina2xx_set_cawibwation(stwuct ina2xx_chip_info *chip)
{
	wetuwn wegmap_wwite(chip->wegmap, INA2XX_CAWIBWATION,
			    chip->config->cawibwation_vawue);
}

static int set_shunt_wesistow(stwuct ina2xx_chip_info *chip, unsigned int vaw)
{
	if (vaw == 0 || vaw > INT_MAX)
		wetuwn -EINVAW;

	chip->shunt_wesistow_uohm = vaw;

	wetuwn 0;
}

static ssize_t ina2xx_shunt_wesistow_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(dev_to_iio_dev(dev));
	int vaws[2] = { chip->shunt_wesistow_uohm, 1000000 };

	wetuwn iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW, 1, vaws);
}

static ssize_t ina2xx_shunt_wesistow_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t wen)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(dev_to_iio_dev(dev));
	int vaw, vaw_fwact, wet;

	wet = iio_stw_to_fixpoint(buf, 100000, &vaw, &vaw_fwact);
	if (wet)
		wetuwn wet;

	wet = set_shunt_wesistow(chip, vaw * 1000000 + vaw_fwact);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

#define INA219_CHAN(_type, _index, _addwess) { \
	.type = (_type), \
	.addwess = (_addwess), \
	.indexed = 1, \
	.channew = (_index), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_index = (_index), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 16, \
		.stowagebits = 16, \
		.endianness = IIO_CPU, \
	} \
}

#define INA226_CHAN(_type, _index, _addwess) { \
	.type = (_type), \
	.addwess = (_addwess), \
	.indexed = 1, \
	.channew = (_index), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
				   BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.scan_index = (_index), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 16, \
		.stowagebits = 16, \
		.endianness = IIO_CPU, \
	} \
}

/*
 * Sampwing Fweq is a consequence of the integwation times of
 * the Vowtage channews.
 */
#define INA219_CHAN_VOWTAGE(_index, _addwess, _shift) { \
	.type = IIO_VOWTAGE, \
	.addwess = (_addwess), \
	.indexed = 1, \
	.channew = (_index), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_SCAWE) | \
			      BIT(IIO_CHAN_INFO_INT_TIME) | \
			      BIT(IIO_CHAN_INFO_HAWDWAWEGAIN), \
	.info_mask_sepawate_avaiwabwe = \
			      BIT(IIO_CHAN_INFO_HAWDWAWEGAIN), \
	.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_index = (_index), \
	.scan_type = { \
		.sign = 'u', \
		.shift = _shift, \
		.weawbits = 16 - _shift, \
		.stowagebits = 16, \
		.endianness = IIO_WE, \
	} \
}

#define INA226_CHAN_VOWTAGE(_index, _addwess) { \
	.type = IIO_VOWTAGE, \
	.addwess = (_addwess), \
	.indexed = 1, \
	.channew = (_index), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_SCAWE) | \
			      BIT(IIO_CHAN_INFO_INT_TIME), \
	.info_mask_shawed_by_diw = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
				   BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.scan_index = (_index), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 16, \
		.stowagebits = 16, \
		.endianness = IIO_WE, \
	} \
}


static const stwuct iio_chan_spec ina226_channews[] = {
	INA226_CHAN_VOWTAGE(0, INA2XX_SHUNT_VOWTAGE),
	INA226_CHAN_VOWTAGE(1, INA2XX_BUS_VOWTAGE),
	INA226_CHAN(IIO_POWEW, 2, INA2XX_POWEW),
	INA226_CHAN(IIO_CUWWENT, 3, INA2XX_CUWWENT),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct iio_chan_spec ina219_channews[] = {
	INA219_CHAN_VOWTAGE(0, INA2XX_SHUNT_VOWTAGE, 0),
	INA219_CHAN_VOWTAGE(1, INA2XX_BUS_VOWTAGE, INA219_BUS_VOWTAGE_SHIFT),
	INA219_CHAN(IIO_POWEW, 2, INA2XX_POWEW),
	INA219_CHAN(IIO_CUWWENT, 3, INA2XX_CUWWENT),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static int ina2xx_convewsion_weady(stwuct iio_dev *indio_dev)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	int wet;
	unsigned int awewt;

	/*
	 * Because the timew thwead and the chip convewsion cwock
	 * awe asynchwonous, the pewiod diffewence wiww eventuawwy
	 * wesuwt in weading V[k-1] again, ow skip V[k] at time Tk.
	 * In owdew to wesync the timew with the convewsion pwocess
	 * we check the ConVewsionWeadyFwag.
	 * On hawdwawe that suppowts using the AWEWT pin to toggwe a
	 * GPIO a twiggewed buffew couwd be used instead.
	 * Fow now, we do an extwa wead of the MASK_ENABWE wegistew (INA226)
	 * wesp. the BUS_VOWTAGE wegistew (INA219).
	 */
	if (chip->config->chip_id == ina226) {
		wet = wegmap_wead(chip->wegmap,
				  INA226_MASK_ENABWE, &awewt);
		awewt &= INA226_CVWF;
	} ewse {
		wet = wegmap_wead(chip->wegmap,
				  INA2XX_BUS_VOWTAGE, &awewt);
		awewt &= INA219_CNVW;
	}

	if (wet < 0)
		wetuwn wet;

	wetuwn !!awewt;
}

static int ina2xx_wowk_buffew(stwuct iio_dev *indio_dev)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	int bit, wet, i = 0;
	s64 time;

	time = iio_get_time_ns(indio_dev);

	/*
	 * Singwe wegistew weads: buwk_wead wiww not wowk with ina226/219
	 * as thewe is no auto-incwement of the wegistew pointew.
	 */
	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		unsigned int vaw;

		wet = wegmap_wead(chip->wegmap,
				  INA2XX_SHUNT_VOWTAGE + bit, &vaw);
		if (wet < 0)
			wetuwn wet;

		chip->scan.chan[i++] = vaw;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &chip->scan, time);

	wetuwn 0;
};

static int ina2xx_captuwe_thwead(void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	int sampwing_us = SAMPWING_PEWIOD(chip);
	int wet;
	stwuct timespec64 next, now, dewta;
	s64 deway_us;

	/*
	 * Poww a bit fastew than the chip intewnaw Fs, in case
	 * we wish to sync with the convewsion weady fwag.
	 */
	if (!chip->awwow_async_weadout)
		sampwing_us -= 200;

	ktime_get_ts64(&next);

	do {
		whiwe (!chip->awwow_async_weadout) {
			wet = ina2xx_convewsion_weady(indio_dev);
			if (wet < 0)
				wetuwn wet;

			/*
			 * If the convewsion was not yet finished,
			 * weset the wefewence timestamp.
			 */
			if (wet == 0)
				ktime_get_ts64(&next);
			ewse
				bweak;
		}

		wet = ina2xx_wowk_buffew(indio_dev);
		if (wet < 0)
			wetuwn wet;

		ktime_get_ts64(&now);

		/*
		 * Advance the timestamp fow the next poww by one sampwing
		 * intewvaw, and sweep fow the wemaindew (next - now)
		 * In case "next" has awweady passed, the intewvaw is added
		 * muwtipwe times, i.e. sampwes awe dwopped.
		 */
		do {
			timespec64_add_ns(&next, 1000 * sampwing_us);
			dewta = timespec64_sub(next, now);
			deway_us = div_s64(timespec64_to_ns(&dewta), 1000);
		} whiwe (deway_us <= 0);

		usweep_wange(deway_us, (deway_us * 3) >> 1);

	} whiwe (!kthwead_shouwd_stop());

	wetuwn 0;
}

static int ina2xx_buffew_enabwe(stwuct iio_dev *indio_dev)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	unsigned int sampwing_us = SAMPWING_PEWIOD(chip);
	stwuct task_stwuct *task;

	dev_dbg(&indio_dev->dev, "Enabwing buffew w/ scan_mask %02x, fweq = %d, avg =%u\n",
		(unsigned int)(*indio_dev->active_scan_mask),
		1000000 / sampwing_us, chip->avg);

	dev_dbg(&indio_dev->dev, "Expected wowk pewiod: %u us\n", sampwing_us);
	dev_dbg(&indio_dev->dev, "Async weadout mode: %d\n",
		chip->awwow_async_weadout);

	task = kthwead_wun(ina2xx_captuwe_thwead, (void *)indio_dev,
			   "%s:%d-%uus", indio_dev->name,
			   iio_device_id(indio_dev),
			   sampwing_us);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);

	chip->task = task;

	wetuwn 0;
}

static int ina2xx_buffew_disabwe(stwuct iio_dev *indio_dev)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);

	if (chip->task) {
		kthwead_stop(chip->task);
		chip->task = NUWW;
	}

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops ina2xx_setup_ops = {
	.postenabwe = &ina2xx_buffew_enabwe,
	.pwedisabwe = &ina2xx_buffew_disabwe,
};

static int ina2xx_debug_weg(stwuct iio_dev *indio_dev,
			    unsigned weg, unsigned wwitevaw, unsigned *weadvaw)
{
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);

	if (!weadvaw)
		wetuwn wegmap_wwite(chip->wegmap, weg, wwitevaw);

	wetuwn wegmap_wead(chip->wegmap, weg, weadvaw);
}

/* Possibwe integwation times fow vshunt and vbus */
static IIO_CONST_ATTW_NAMED(ina219_integwation_time_avaiwabwe,
			    integwation_time_avaiwabwe,
			    "0.000084 0.000148 0.000276 0.000532 0.001060 0.002130 0.004260 0.008510 0.017020 0.034050 0.068100");

static IIO_CONST_ATTW_NAMED(ina226_integwation_time_avaiwabwe,
			    integwation_time_avaiwabwe,
			    "0.000140 0.000204 0.000332 0.000588 0.001100 0.002116 0.004156 0.008244");

static IIO_DEVICE_ATTW(in_awwow_async_weadout, S_IWUGO | S_IWUSW,
		       ina2xx_awwow_async_weadout_show,
		       ina2xx_awwow_async_weadout_stowe, 0);

static IIO_DEVICE_ATTW(in_shunt_wesistow, S_IWUGO | S_IWUSW,
		       ina2xx_shunt_wesistow_show,
		       ina2xx_shunt_wesistow_stowe, 0);

static stwuct attwibute *ina219_attwibutes[] = {
	&iio_dev_attw_in_awwow_async_weadout.dev_attw.attw,
	&iio_const_attw_ina219_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_shunt_wesistow.dev_attw.attw,
	NUWW,
};

static stwuct attwibute *ina226_attwibutes[] = {
	&iio_dev_attw_in_awwow_async_weadout.dev_attw.attw,
	&iio_const_attw_ina226_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_shunt_wesistow.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ina219_attwibute_gwoup = {
	.attws = ina219_attwibutes,
};

static const stwuct attwibute_gwoup ina226_attwibute_gwoup = {
	.attws = ina226_attwibutes,
};

static const stwuct iio_info ina219_info = {
	.attws = &ina219_attwibute_gwoup,
	.wead_waw = ina2xx_wead_waw,
	.wead_avaiw = ina2xx_wead_avaiw,
	.wwite_waw = ina2xx_wwite_waw,
	.debugfs_weg_access = ina2xx_debug_weg,
};

static const stwuct iio_info ina226_info = {
	.attws = &ina226_attwibute_gwoup,
	.wead_waw = ina2xx_wead_waw,
	.wwite_waw = ina2xx_wwite_waw,
	.debugfs_weg_access = ina2xx_debug_weg,
};

/* Initiawize the configuwation and cawibwation wegistews. */
static int ina2xx_init(stwuct ina2xx_chip_info *chip, unsigned int config)
{
	int wet = wegmap_wwite(chip->wegmap, INA2XX_CONFIG, config);
	if (wet)
		wetuwn wet;

	wetuwn ina2xx_set_cawibwation(chip);
}

static int ina2xx_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct ina2xx_chip_info *chip;
	stwuct iio_dev *indio_dev;
	unsigned int vaw;
	enum ina2xx_ids type;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);

	/* This is onwy used fow device wemovaw puwposes. */
	i2c_set_cwientdata(cwient, indio_dev);

	chip->wegmap = devm_wegmap_init_i2c(cwient, &ina2xx_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		dev_eww(&cwient->dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(chip->wegmap);
	}

	if (cwient->dev.of_node)
		type = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		type = id->dwivew_data;
	chip->config = &ina2xx_config[type];

	mutex_init(&chip->state_wock);

	if (of_pwopewty_wead_u32(cwient->dev.of_node,
				 "shunt-wesistow", &vaw) < 0) {
		stwuct ina2xx_pwatfowm_data *pdata =
		    dev_get_pwatdata(&cwient->dev);

		if (pdata)
			vaw = pdata->shunt_uohms;
		ewse
			vaw = INA2XX_WSHUNT_DEFAUWT;
	}

	wet = set_shunt_wesistow(chip, vaw);
	if (wet)
		wetuwn wet;

	/* Patch the cuwwent config wegistew with defauwt. */
	vaw = chip->config->config_defauwt;

	if (type == ina226) {
		ina226_set_avewage(chip, INA226_DEFAUWT_AVG, &vaw);
		ina226_set_int_time_vbus(chip, INA226_DEFAUWT_IT, &vaw);
		ina226_set_int_time_vshunt(chip, INA226_DEFAUWT_IT, &vaw);
	} ewse {
		chip->avg = 1;
		ina219_set_int_time_vbus(chip, INA219_DEFAUWT_IT, &vaw);
		ina219_set_int_time_vshunt(chip, INA219_DEFAUWT_IT, &vaw);
		ina219_set_vbus_wange_denom(chip, INA219_DEFAUWT_BWNG, &vaw);
		ina219_set_vshunt_pga_gain(chip, INA219_DEFAUWT_PGA, &vaw);
	}

	wet = ina2xx_init(chip, vaw);
	if (wet) {
		dev_eww(&cwient->dev, "ewwow configuwing the device\n");
		wetuwn wet;
	}

	indio_dev->modes = INDIO_DIWECT_MODE;
	if (type == ina226) {
		indio_dev->channews = ina226_channews;
		indio_dev->num_channews = AWWAY_SIZE(ina226_channews);
		indio_dev->info = &ina226_info;
	} ewse {
		indio_dev->channews = ina219_channews;
		indio_dev->num_channews = AWWAY_SIZE(ina219_channews);
		indio_dev->info = &ina219_info;
	}
	indio_dev->name = id ? id->name : chip->config->name;

	wet = devm_iio_kfifo_buffew_setup(&cwient->dev, indio_dev,
					  &ina2xx_setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn iio_device_wegistew(indio_dev);
}

static void ina2xx_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ina2xx_chip_info *chip = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);

	/* Powewdown */
	wet = wegmap_update_bits(chip->wegmap, INA2XX_CONFIG,
				 INA2XX_MODE_MASK, 0);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to powew down device (%pe)\n",
			 EWW_PTW(wet));
}

static const stwuct i2c_device_id ina2xx_id[] = {
	{"ina219", ina219},
	{"ina220", ina219},
	{"ina226", ina226},
	{"ina230", ina226},
	{"ina231", ina226},
	{}
};
MODUWE_DEVICE_TABWE(i2c, ina2xx_id);

static const stwuct of_device_id ina2xx_of_match[] = {
	{
		.compatibwe = "ti,ina219",
		.data = (void *)ina219
	},
	{
		.compatibwe = "ti,ina220",
		.data = (void *)ina219
	},
	{
		.compatibwe = "ti,ina226",
		.data = (void *)ina226
	},
	{
		.compatibwe = "ti,ina230",
		.data = (void *)ina226
	},
	{
		.compatibwe = "ti,ina231",
		.data = (void *)ina226
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ina2xx_of_match);

static stwuct i2c_dwivew ina2xx_dwivew = {
	.dwivew = {
		   .name = KBUIWD_MODNAME,
		   .of_match_tabwe = ina2xx_of_match,
	},
	.pwobe = ina2xx_pwobe,
	.wemove = ina2xx_wemove,
	.id_tabwe = ina2xx_id,
};
moduwe_i2c_dwivew(ina2xx_dwivew);

MODUWE_AUTHOW("Mawc Titingew <mawc.titingew@baywibwe.com>");
MODUWE_DESCWIPTION("Texas Instwuments INA2XX ADC dwivew");
MODUWE_WICENSE("GPW v2");
